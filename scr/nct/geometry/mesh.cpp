//=================================================================================================================
/**
 *  @file       mesh.cpp
 *  @brief      nct::geometry::mesh namespace implementation file.
 *  @details    This file contains the implementation of the nct::geometry::mesh namespace.
 *  @author     Omar Mendoza Montoya (email: omendoz@live.com.mx).
 *  @copyright  Copyright (c) 2012 Omar Mendoza Montoya \n \n
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 *  associated documentation files (the "Software"), to deal in the Software without restriction,  
 *  including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,  
 *  and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
 *  subject to the following conditions: \n
 *  The above copyright notice and this permission notice shall be included in all copies or substantial 
 *  portions of the Software. \n
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 *  LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 *  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
//=================================================================================================================

//=================================================================================================================
//        HEADERS AND NAMESPACES
//=================================================================================================================
#include <nct/geometry/mesh.h>
#include <nct/statistics/statistics.h>
#include <nct/statistics/distance_metrics.h>
#include <nct/interpolation/CubicSpline.h>
#include <nct/geometry/AffineTransformation3D.h>
#include <nct/math/math.h>

//=================================================================================================================
//        AUXILIAR FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::size_t nct::geometry::mesh::findClosestVertex(const Point3D& v, 
    const Array<Point3D>& vA)
{
    auto n = vA.size();
    if (n == 0)
        throw EmptyArrayException("vA", SOURCE_INFO);

    size_t ind = 0;
    Point3D d = v - vA[0];
    double dMin = d.sqrMagnitude();
    double dc = 0;
    for (index_t i=0; i<n; i++) {
        d = v - vA[i];
        dc = d.sqrMagnitude();
        if (dc < dMin) {
            ind = i;
            dMin = dc;
        }        
    }
    return ind;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::size_t> nct::geometry::mesh::findClosestVertex(
    const Array<Point3D>& v1, const Array<Point3D>& v2)
{
    auto n1 = v1.size();
    if (n1 == 0)
        throw EmptyArrayException("v1", SOURCE_INFO);

    auto n2 = v1.size();
    if (n2 == 0)
        throw EmptyArrayException("v2", SOURCE_INFO);

    double dMin;
    double dc;
    Point3D d;
    Array<size_t> ind(n1);
    for (index_t i=0; i<n1; i++) {
        d = v1[i] - v2[0];
        dMin = d.sqrMagnitude();
        dc = 0;
        ind[i] = 0;
        for (index_t j=1; j<n2; j++) {
            d = v1[i] - v2[j];
            dc = d.sqrMagnitude();
            if (dc < dMin) {
                ind[i] = j;
                dMin = dc;
            }        
        }        
    }

    return ind;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::Point3D> nct::geometry::mesh::gridVertices(unsigned int nx, 
    unsigned int ny)
{
    // Check input arguments.
    if (nx < 2)
        throw ArgumentException("nx", nx, 2U,
        RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    if (ny < 2)
        throw ArgumentException("ny", ny, 2U,
        RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    Array<Point3D> vertices((size_t)nx*ny);
    for (index_t i=0; i<nx; i++) {
        double x = -1 + i*(2.0)/(nx-1.0);
        for (unsigned int j=0; j<ny; j++) {
            double y = -1 + j*(2.0)/(ny-1.0);
            vertices[i*ny + j].setCoefficients(x, y, 0);
        }
    }

    return vertices;
}


//-----------------------------------------------------------------------------------------------------------------
std::tuple<nct::Array<nct::Point3D>, nct::Array<nct::Vector3D<unsigned int>>>
nct::geometry::mesh::gridMesh(unsigned int nx, unsigned int ny) 
{
    // Check input arguments.
    if (nx < 2)
        throw ArgumentException("nx", nx, 2U,
        RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    if (ny < 2)
        throw ArgumentException("ny", ny, 2U,
        RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    // Calculate vertices.
    Array<Point3D> vertices((size_t)nx*ny, Point3D());
    for (index_t i=0; i<nx; i++) {
        double x = -1 + i*(2.0)/(nx-1.0);
        for (unsigned int j=0; j<ny; j++) {
            double y = -1 + j*(2.0)/(ny-1.0);
            vertices[i*ny + j].setCoefficients(x, y, 0.0);
        }
    }

    // Calculate mesh.
    Array<Vector3D<unsigned int>> triangles(2*((size_t)nx-1)*((size_t)ny-1), Vector3D<unsigned int>());
    unsigned int c = 0;
    for (unsigned int i=0; i<(nx-1); i++) {
        for (unsigned int j=0; j<(ny-1); j++) {
            triangles[c][0] = (i)*ny + (j+1);
            triangles[c][1] = (i)*ny + (j);
            triangles[c][2] = (i+1)*ny + (j);
            c++;

            triangles[c][0] = (i+1)*ny + (j+1);
            triangles[c][1] = (i)*ny + (j+1);
            triangles[c][2] = (i+1)*ny + (j);
            c++;
        }
    }    

    return std::make_tuple(vertices, triangles);
}
//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::Point3D> nct::geometry::mesh::sphereVertices(
    unsigned int nTheta, unsigned int nPhi)
{
    // Check input arguments.
    if (nTheta < 2)
        throw ArgumentException("nTheta", nTheta, 2U,
        RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    if (nPhi < 3)
        throw ArgumentException("nPhi", nPhi, 3U,
        RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    // Compute angles.
    auto nAngT = nPhi*nTheta - 2*nTheta + 2;    
    
    RealVector thetaT(nTheta);
    for (unsigned int i=0; i<nTheta; i++)
        thetaT[i] = i*(TWO_PI)/(nTheta);

    RealVector phiT(nPhi-2);
    for (index_t i=0; i<(nPhi-2); i++)
        phiT[i] = (i+1.)*(PI)/(nPhi-1.);

    unsigned int c = 0;
    RealVector theta(nAngT);
    RealVector phi(nAngT);

    theta[c] = 0;
    phi[c++] = 0;
    for (unsigned int i=0; i<(nPhi-2); i++) {
        for (unsigned int j=0; j<nTheta; j++) {
            theta[c] = thetaT[j];
            phi[c++] = phiT[i];
        }
    }
    theta[c] = 0;
    phi[c++] = PI;

    // Compute points.
    Point3D pointSp;
    Array<Point3D> vertices(nAngT);
    for (unsigned int j=0; j<nAngT; j++) {            
        pointSp.setCoefficients(1.0, theta[j], phi[j]);
        vertices[j] = pointSp.sphericalToCartesian();        
    }    

    return vertices;
} 

//-----------------------------------------------------------------------------------------------------------------
std::tuple<nct::Array<nct::Point3D>, nct::Array<nct::Vector3D<unsigned int>>> 
nct::geometry::mesh::sphereMesh(unsigned int nTheta, unsigned int nPhi)
{
    // Check input arguments.
    if (nTheta < 2)
        throw ArgumentException("nTheta", nTheta, 2U,
        RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    if (nPhi < 3)
        throw ArgumentException("nPhi", nPhi, 3U,
        RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    // Compute angles.
    auto nAngT = nPhi*nTheta - 2*nTheta + 2;    
    
    RealVector thetaT(nTheta);
    for (unsigned int i=0; i<nTheta; i++)
        thetaT[i] = i*(TWO_PI)/(nTheta);

    RealVector phiT(nPhi-2);
    for (index_t i=0; i<(nPhi-2); i++)
        phiT[i] = (i+1.)*(PI)/(nPhi-1.);

    unsigned int c = 0;
    RealVector theta(nAngT);
    RealVector phi(nAngT);

    theta[c] = 0;
    phi[c++] = 0;
    for (unsigned int i=0; i<(nPhi-2); i++) {
        for (unsigned int j=0; j<nTheta; j++) {
            theta[c] = thetaT[j];
            phi[c++] = phiT[i];
        }
    }
    theta[c] = 0;
    phi[c++] = PI;

    // Compute points.
    Point3D pointSp;
    Point3D pointXYZ;
    Array<Point3D> vertices(nAngT, Point3D());
    for (unsigned int j=0; j<nAngT; j++) {            
        pointSp.setCoefficients(1.0, theta[j], phi[j]);
        pointXYZ = pointSp.sphericalToCartesian();
        vertices[j].setCoefficients(pointXYZ[0], pointXYZ[1], pointXYZ[2]);
    }

    // Compute triangles.
    auto ntr = 2*nTheta*(nPhi-2);
    Array<Vector3D<unsigned int>> triangles(ntr, Vector3D<unsigned int>());
    c = 0;
    for (unsigned int i=0; i<(nPhi-1); i++) {
        if (i == 0) {
            unsigned int u = 0;
            unsigned int iL = 1;
            unsigned int eL = nTheta;
            for (unsigned int j=0; j<nTheta; j++) {
                triangles[c][0] = u;
                triangles[c][1] = iL + j;
                triangles[c][2] = iL + j+1;
                if (triangles[c][2] > eL)
                    triangles[c][2] -=  nTheta;
                c++;
            }
        }
        else if (i == (nPhi-2)) {
            unsigned int iU = (nPhi-3)*nTheta + 1;
            unsigned int eU = (nPhi-2)*nTheta;
            unsigned int l = (nPhi-2)*nTheta + 1;
            for (unsigned int j=0; j<nTheta; j++) {
                triangles[c][0] = iU + j;
                triangles[c][1] = l;
                triangles[c][2] = iU + j + 1;
                if (triangles[c][2] > eU)
                    triangles[c][2] -=  nTheta;
                c++;
            }
        }
        else {
            unsigned int iU = (i-1)*nTheta + 1;
            unsigned int eU = i*nTheta;
            unsigned int iL = i*nTheta + 1;
            unsigned int eL = (i+1)*nTheta;
            for (unsigned int j=0; j<nTheta; j++) {
                triangles[c][0] = j + iU;
                triangles[c][1] = j + iL;
                triangles[c][2] = j + iL + 1;
                if (triangles[c][2] > eL)
                    triangles[c][2] -=  nTheta;
                c++;

                triangles[c][0] = j + iU;
                triangles[c][1] = j + iL + 1;
                triangles[c][2] = j + iU + 1;
                if (triangles[c][1] > eL)
                    triangles[c][1] -=  nTheta;
                if (triangles[c][2] > eU)
                    triangles[c][2] -=  nTheta;
                c++;
            }
        }
    }

    return std::make_tuple(vertices, triangles);
} 

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::Vector3D<double>> nct::geometry::mesh::calculateFaceNormals(
    const Array<Point3D>& vertices, 
    const Array<Vector3D<unsigned int>>& triangles)
{
    auto nTr = triangles.size();
    Array<Vector3D<double>> normals(nTr);
    for (index_t i=0; i<nTr; i++) {
        normals[i] = crossProduct(vertices[triangles[i][1]] - vertices[triangles[i][0]],
            vertices[triangles[i][2]] - vertices[triangles[i][0]]);
        normals[i].normalize();
    }

    return normals;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::Vector3D<double>> nct::geometry::mesh::calculateVertexNormals(
    const Array<Point3D>& vertices, 
    const Array<Vector3D<unsigned int>>& triangles)
{
    Array<Vector3D<double>> faceNormals;
    faceNormals = calculateFaceNormals(vertices, triangles);

    auto nV = vertices.size();
    Array<Vector3D<double>> normals(nV, Vector3D<double>(0, 0, 0));
    Array<float> nN(nV, 0);

    auto nTr = triangles.size();
    for (index_t i=0; i<nTr; i++) {
        for (unsigned int j=0; j<3; j++) {
            normals[triangles[i][j]] += faceNormals[i];
            nN[triangles[i][j]]++;
        }
    }
        
    for (index_t i=0; i<nV; i++) {
        if (nN[i]>0) {
            normals[i] *= 1.f/nN[i];
            normals[i].normalize();
        }
    }

    return normals;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::Point3D> nct::geometry::mesh::centerAndScaleVertices(
    const Array<Point3D>& vertices)
{
    auto nV = vertices.size();
    Array<Point3D> scVertices(nV);

    // Center vertices.
    Point3D mean(0,0,0);
    for (index_t i=0; i<nV; i++)
        mean += vertices[i];
    mean *= 1.0f/nV;

    for (index_t i=0; i<nV; i++)
        scVertices[i] = vertices[i] - mean;

    // Scale vertices.
    double maxdist = 0;
    double dist = 0;
    for (index_t i=0; i<nV; i++) {
        dist = scVertices[i][0]*scVertices[i][0] +
               scVertices[i][1]*scVertices[i][1] +
               scVertices[i][2]*scVertices[i][2];
        if (dist > maxdist)
                maxdist = dist; 
    }
    maxdist = std::sqrt(maxdist);

    double sc = 1;
    if (maxdist > 0)
        sc = 1.0f/maxdist;
    for (index_t i=0; i<nV; i++)
        scVertices[i] *= sc;

    return scVertices;
}


//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::Point3D> nct::geometry::mesh::centerAndScaleVertices(
    const Array<Point3D>& vertices, 
    const Array<Vector3D<unsigned int>>& triangles)
{
    auto nV = vertices.size();
    Array<Point3D> scVertices(nV);

    // Center vertices.
    Point3D mean = calculateCentroid(vertices, triangles);

    for (index_t i=0; i<nV; i++)
        scVertices[i] = vertices[i] - mean;

    // Scale vertices.
    double maxdist = 0;
    double dist = 0;
    for (index_t i=0; i<nV; i++) {
        dist = scVertices[i][0]*scVertices[i][0] +
               scVertices[i][1]*scVertices[i][1] +
               scVertices[i][2]*scVertices[i][2];
        if (dist > maxdist)
                maxdist = dist; 
    }
    maxdist = std::sqrt(maxdist);

    double sc = 1;
    if (maxdist > 0)
        sc = 1.0f/maxdist;
    for (index_t i=0; i<nV; i++)
        scVertices[i] *= sc;

    return scVertices;
}

//-----------------------------------------------------------------------------------------------------------------
nct::RealVector nct::geometry::mesh::calculateAreas(
    const Array<Point3D>& vertices, 
    const Array<Vector3D<unsigned int>>& triangles)
{
    auto nt = triangles.size();
    RealVector areas(nt);

    for (index_t i=0; i<nt; i++)
        areas[i] = triangleArea(
            vertices[triangles[i].v1()], 
            vertices[triangles[i].v2()], 
            vertices[triangles[i].v3()]);

    return areas;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::Point3D> nct::geometry::mesh::samplePoints(
    const Array<Point3D>& vertices, 
    const Array<Vector3D<unsigned int>>& triangles,
    unsigned int nSamples, random::RandomNumber& rnd)
{
    if (nSamples == 0)
        throw ArgumentException("nSamples", nSamples, 0U, 
        RelationalOperator::GreaterThan, SOURCE_INFO);

    // Calculate areas.
    RealVector areas = calculateAreas(vertices, triangles);    
    double totArea = areas.sum();

    // Sample N points.
    RealVector x(nSamples);
    for (unsigned int i=0; i<nSamples; i++)
        x[i] = totArea*rnd.random();

    Array<std::pair<double, unsigned int>> sortedX(nSamples);
    for (unsigned int i=0; i<nSamples; i++)
        sortedX[i] = std::make_pair(x[i], i);

    std::sort(sortedX.begin(), sortedX.end(), 
        [](const std::pair<double, unsigned int>& x1, 
        const std::pair<double, unsigned int>& x2){return x1.first < x2.first;});
    
    // Find the triangle where each sample point is located.
    auto nt = triangles.size();
    Array<size_t> tIndex(nSamples, nt);

    size_t cIndex = 0;
    double acc =  areas[0];
    for (unsigned int i=0; i<nSamples; i++) {
        while ( sortedX[i].first > (acc + VERY_SMALL_TOL) ) {
            cIndex++;
            acc += areas[cIndex];            
        }
        tIndex[sortedX[i].second] = cIndex;
    }

    // Find a random point into each selected triangle.
    Array<Point3D> points(nSamples);
    double r1, r2;
    for (unsigned int i=0; i<nSamples; i++) {
        r1 = std::sqrt(rnd.random());
        r2 = rnd.random();

        const auto& v1 = vertices[triangles[tIndex[i]].v1()];
        const auto& v2 = vertices[triangles[tIndex[i]].v2()];
        const auto& v3 = vertices[triangles[tIndex[i]].v3()];

        points[i] = (1-r1)*v1 + r1*(1-r2)*v2 + r1*r2*v3;
    }

    return points;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Point3D nct::geometry::mesh::calculateCentroid(
    const Array<Point3D>& vertices)
{
    auto nv = vertices.size();
    Point3D c = Point3D(0.0, 0.0, 0.0);
    for (index_t i=0; i<nv; i++)
        c += vertices[i];

    return c / static_cast<double>(nv);
}

//-----------------------------------------------------------------------------------------------------------------
nct::Point3D nct::geometry::mesh::calculateCentroid(
    const Array<Point3D>& vertices, 
    const Array<Vector3D<unsigned int>>& triangles)
{
    RealVector areas = calculateAreas(vertices, triangles);
    double tSum =  areas.sum();

    if (tSum == 0)
        throw ArithmeticException(exc_div_by_zero, SOURCE_INFO);

    Point3D c = Point3D(0.0, 0.0, 0.0);
    auto nt = triangles.size();
    for (index_t i=0; i<nt; i++) {
        const auto& v1 = vertices[triangles[i].v1()];
        const auto& v2 = vertices[triangles[i].v2()];
        const auto& v3 = vertices[triangles[i].v3()];

        c += ( (v1 + v2 + v3) * (areas[i]/3.0));
    }

    return c/tSum;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Point3D nct::geometry::mesh::calculateCentroid(
    const Array<Point3D>& vertices, 
    const Array<Vector3D<unsigned int>>& triangles,
    unsigned int nSamples, random::RandomNumber& rnd)
{
    Array<Point3D> points = samplePoints(vertices, triangles, nSamples, rnd);
    return calculateCentroid(points);
}

//-----------------------------------------------------------------------------------------------------------------
std::tuple<nct::RealVector, nct::RealVector> nct::geometry::mesh::calculateShapeDistribution(
    const Array<Point3D>& vertices, const Array<Vector3D<unsigned int>>& triangles,
    random::RandomNumber& rnd, ShapeDistribution dist, unsigned int nSamples, unsigned int nBins)
{
    RealVector histogram;
    RealVector bins;

    // Calculate random samples and the histogram of the selected distribution.
    switch (dist) {
        case ShapeDistribution::TwoVectorsAngle: {
                RealVector samps(nSamples);
                Array<Point3D> points = samplePoints(
                    vertices, triangles, nSamples*3, rnd);
                for (unsigned int i=0; i<nSamples; i++)
                    samps[i] = math::wrapToPi(angleBetweenVectors(
                    points[i * (size_t)3 + 1] - points[i * (size_t)3 + 0],
                        points[i * (size_t)3 + 2] - points[i * (size_t)3 + 0]));

                histogram.assign(nBins, 0.0);
                bins.assign(nBins, 0.0);
                statistics::histogram(samps.begin(), samps.end(), histogram.begin(),
                    bins.begin(), nBins, 0, PI);
                histogram /= static_cast<double>(nSamples);
            }
            break;

        case ShapeDistribution::CentroidDistance: {
                Vector3D<double> c = calculateCentroid( vertices, triangles);

                RealVector samps(nSamples);
                Array<Point3D> points = samplePoints(
                    vertices, triangles, nSamples, rnd);
                for (unsigned int i=0; i<nSamples; i++)
                    samps[i] = (points[i] - c).magnitude();  

                histogram.assign(nBins, 0.0);
                bins.assign(nBins, 0.0);
                statistics::histogram(samps.begin(), samps.end(), histogram.begin(),
                    bins.begin(), nBins);

                histogram /= static_cast<double>(nSamples);
            }
            break;

        case ShapeDistribution::TwoPointDistance: {
                RealVector samps(nSamples);
                Array<Point3D> points = samplePoints(
                    vertices, triangles, nSamples * 2, rnd);
                for (unsigned int i=0; i<nSamples; i++)
                    samps[i] = (points[i * (size_t)2 + 1] - points[i * (size_t)2 + 0]).magnitude();

                histogram.assign(nBins, 0.0);
                bins.assign(nBins, 0.0);
                statistics::histogram(samps.begin(), samps.end(), histogram.begin(),
                    bins.begin(), nBins);

                histogram /= static_cast<double>(nSamples);
            }
            break;

        case ShapeDistribution::ThreePointArea: {
                RealVector samps(nSamples);
                Array<Point3D> points = samplePoints(
                    vertices, triangles, nSamples * 3, rnd);
                for (unsigned int i=0; i<nSamples; i++)
                    samps[i] = std::sqrt(triangleArea(points[i * (size_t)3 + 0],
                    points[i * (size_t)3 + 1], points[i * (size_t)3 + 2]));

                histogram.assign(nBins, 0.0);
                bins.assign(nBins, 0.0);
                statistics::histogram(samps.begin(), samps.end(), histogram.begin(),
                    bins.begin(), nBins);

                histogram /= static_cast<double>(nSamples);
            }
            break;

        case ShapeDistribution::FourPointVolume: {
                RealVector samps(nSamples);
                Array<Point3D> points = samplePoints(
                    vertices, triangles, nSamples * 4, rnd);
                for (unsigned int i=0; i<nSamples; i++)
                    samps[i] = std::pow(tetrahedronVolume(points[i * (size_t)4 + 0],
                    points[i * (size_t)4 + 1], points[i * (size_t)4 + 2], 
                        points[i * (size_t)4 + 3]), 1.0 / 3.0);

                histogram.assign(nBins, 0.0);
                bins.assign(nBins, 0.0);
                statistics::histogram(samps.begin(), samps.end(), histogram.begin(),
                    bins.begin(), nBins);

                histogram /= static_cast<double>(nSamples);
            }
            break;
        default:
            throw ArgumentException("dist", exc_bad_shape_distribution, SOURCE_INFO);
    }

    return std::make_tuple(histogram, bins);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::mesh::compareFeatures(const RealVector& h1, 
    const RealVector& h2, DistanceFunction distFunction)
{
    if (h1.size() == 0)
        throw EmptyArrayException("h1", SOURCE_INFO);
    
    if (h2.size() == 0)
        throw EmptyArrayException("h2", SOURCE_INFO);
    
    if (h1.size() != h2.size())
        throw ArgumentException("h1, h2", exc_arrays_of_different_lengths, SOURCE_INFO);

    double d = 0;
    switch (distFunction) {
        case DistanceFunction::EuclideanDistance:    
            d = statistics::distance_metrics::euclideanDistance(h1.begin(), h1.end(), h2.begin(), h2.end());
            break;
        
        case DistanceFunction::CityBlockDistance:    
            d = statistics::distance_metrics::cityBlockDistance(h1.begin(), h1.end(), h2.begin(), h2.end());
            break;

        case DistanceFunction::ChebychevDistance:    
            d = statistics::distance_metrics::chebychevDistance(h1.begin(), h1.end(), h2.begin(), h2.end());
            break;

        case DistanceFunction::MinDistance:    
            d = statistics::distance_metrics::minDistance(h1.begin(), h1.end(), h2.begin(), h2.end());
            break;

        case DistanceFunction::BhattacharyyaDistance:
            d = statistics::distance_metrics::bhattacharrayDistance(h1.begin(), h1.end(), 
                h2.begin(), h2.end());
            break;

        default:
            throw ArgumentException("distFunction", exc_bad_distance_function,
                SOURCE_INFO);
    }

    return d;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::mesh::calculateShapeDistributionDistance(const RealVector& h1, 
    const RealVector& h2, DistanceFunction distFunction, bool useCumulativeDistribution)
{
    if (h1.size() == 0)
        throw EmptyArrayException("h1", SOURCE_INFO);
    
    if (h2.size() == 0)
        throw EmptyArrayException("h2", SOURCE_INFO);
    
    if (h1.size() != h2.size())
        throw ArgumentException("h1, h2", exc_arrays_of_different_lengths, SOURCE_INFO);

    auto n = h1.size();
    RealVector t1(n), t2(n);

    if (useCumulativeDistribution) {
        statistics::cumulativeData(h1.begin(), h1.end(), t1.begin());
        statistics::cumulativeData(h2.begin(), h2.end(), t2.begin());
    }
    else {
        t1 = h1;
        t2 = h2;
    }

    double d = 0;
    switch (distFunction) {
        case DistanceFunction::EuclideanDistance:    
            d = statistics::distance_metrics::euclideanDistance(t1.begin(), t1.end(), t2.begin(), t2.end());
            break;
        
        case DistanceFunction::CityBlockDistance:    
            d = statistics::distance_metrics::cityBlockDistance(t1.begin(), t1.end(), t2.begin(), t2.end());
            break;

        case DistanceFunction::ChebychevDistance:    
            d = statistics::distance_metrics::chebychevDistance(t1.begin(), t1.end(), t2.begin(), t2.end());
            break;

        case DistanceFunction::MinDistance:    
            d = statistics::distance_metrics::minDistance(t1.begin(), t1.end(), t2.begin(), t2.end());
            break;

        case DistanceFunction::BhattacharyyaDistance:
            d = statistics::distance_metrics::bhattacharrayDistance(t1.begin(), t1.end(), 
                t2.begin(), t2.end());
            break;

        default:
            throw ArgumentException("distFunction", exc_bad_distance_function,
                SOURCE_INFO);
    }

    return d;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::mesh::calculateShapeDistributionDistance(const RealVector& h1,
    const RealVector& b1, const RealVector& h2,
    const RealVector& b2, DistanceFunction distFunction, 
    bool useCumulativeDistribution, unsigned int nPoints, unsigned int nScales, 
    double minDbScale, double maxDbScale)
{
    if (h1.size() == 0)
        throw EmptyArrayException("h1", SOURCE_INFO);

    if (b1.size() == 0)
        throw EmptyArrayException("b1", SOURCE_INFO);

    if (h1.size() != b1.size())
        throw ArgumentException("h1, b1", exc_arrays_of_different_lengths, SOURCE_INFO);

    if (h2.size() == 0)
        throw EmptyArrayException("h2", SOURCE_INFO);

    if (b2.size() == 0)
        throw EmptyArrayException("b2", SOURCE_INFO);

    if (h2.size() != b2.size())
        throw ArgumentException("h2, b2", exc_arrays_of_different_lengths, SOURCE_INFO);

    if (nPoints == 0)
        throw ArgumentException("nPoints", nPoints, 0U, RelationalOperator::GreaterThan, 
        SOURCE_INFO);

    if (nScales == 0)
        throw ArgumentException("nScales", nScales, 0U, RelationalOperator::GreaterThan, 
        SOURCE_INFO);

    if (minDbScale > maxDbScale)
        throw ArgumentException("minDbScale, maxDbScale", exc_bad_bounds, SOURCE_INFO);


    RealVector scales(nScales);
    for (unsigned int i=0; i<nScales; i++)
        scales[i] = exp(minDbScale + i * (maxDbScale - minDbScale)/(nScales - 1.0));

    interpolation::CubicSpline f1(b1, h1);
    interpolation::CubicSpline f2(b2, h2);
    double m1 = dotProduct(b1, h1);
    double m2 = dotProduct(b2, h2);
    
    double s1 = 1;
    if (m1!=0)
        s1 = 1.0/m1;
    
    double s2 = 1;
    if (m2!=0)
        s2 = 1.0/m2;

    double xmin = math::min(s1*b1.min(), s2*b2.min());
    double xmax = math::max(s1*b1.max(), s2*b2.max());
    
    RealVector xts(nPoints);
    for (unsigned int i=0; i<nPoints; i++)
        xts[i] = xmin + i * (xmax - xmin)/(nPoints - 1.0);

    auto tmp = f1.eval(xts/s1);

    RealVector ht1(tmp.size());
    std::transform(tmp.begin(), tmp.end(), ht1.begin(), math::positivePart<double>);
    double sum1 = ht1.sum();
    if (sum1 > 0)
        ht1 /= sum1;
    
    tmp = f2.eval(xts/s2);
    RealVector ht2(tmp.size());
    std::transform(tmp.begin(), tmp.end(), ht2.begin(), math::positivePart<double>);
    double sum2 = ht2.sum();
    if (sum2 > 0)
        ht2 /= sum2;

    RealVector d(nScales);
    for (unsigned int s = 0; s<nScales; s++) {
        s2 = scales[s];

        xmin = math::min(s1*b1.min(), s2*b2.min());
        xmax = math::max(s1*b1.max(), s2*b2.max());
    
        for (unsigned int i=0; i<nPoints; i++)
            xts[i] = xmin + i * (xmax - xmin)/(nPoints - 1.0);

        tmp = f1.eval(xts/s1);
        ht1.assign(tmp.size(), 0.0);
        std::transform(tmp.begin(), tmp.end(), ht1.begin(), math::positivePart<double>);
        sum1 = ht1.sum();
        if (sum1 > 0)
            ht1 /= sum1;
    
        tmp = f2.eval(xts/s2);
        ht2.assign(tmp.size(), 0.0);
        std::transform(tmp.begin(), tmp.end(), ht2.begin(), math::positivePart<double>);
        sum2 = ht2.sum();
        if (sum2 > 0)
            ht2 /= sum2;        
        
        d[s] = calculateShapeDistributionDistance(ht1, ht2, distFunction, useCumulativeDistribution);        
    }

    return d.min();
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::Array<nct::size_t>> nct::geometry::mesh::findRotationIndices(
    const Array<Vector3D<double>>& dirVectors, unsigned int nTestAngles)
{
    // Verify arguments.
    auto nDir = dirVectors.size();
    if (nDir<1)
        throw EmptyArrayException("dirVectors", SOURCE_INFO);

    // Rotation angles.
    unsigned int nAng = nTestAngles;
    unsigned int nRot = nAng*nAng*nAng;
    Matrix angles(nRot, 3);
    unsigned int c = 0;
    for (unsigned int i = 0; i<nAng; i++) {
        double tx = i*TWO_PI/(nAng);
        for (unsigned int j = 0; j<nAng; j++) {
            double ty = j*TWO_PI/(nAng);
            for (unsigned int k = 0; k<nAng; k++) {
                double tz = k*TWO_PI/(nAng);
                angles(c, 0) = tx;
                angles(c, 1) = ty;
                angles(c, 2) = tz;
                c++;
            }
        }
    }

    // For each rotation.
    Array<Array<size_t>> indices(nRot);
    Array<Vector3D<double>> newVectors;
    
    for (unsigned int i=0; i<nRot; i++) {
        // Create rotation matrix.
        auto rm = geometry::AffineTransformation3D::rotationMatrixXYZ(
            angles(i, 0), angles(i, 1), angles(i, 2));
        
        // Rotate vectors
        newVectors = rm.transform(dirVectors);

        // Check indices of the closest positions and fill the rotated array.
        indices[i] = findClosestVertex(newVectors, dirVectors);
        
    }

    return indices;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::mesh::compareSymmetryDescriptors(const Matrix& rsd1,
    const Matrix& rsd2, const Array<Vector3D<double>>& dirVectors,
    DistanceFunction distFunction, unsigned int nTestAngles)
{
    // Verify arguments.
    auto nDir = dirVectors.size();
    if (nDir<1)
        throw EmptyArrayException("dirVectors", SOURCE_INFO);

    if ( (rsd1.rows() != nDir) || (rsd1.columns() != 2))
        throw ArgumentException("rsd1", exc_bad_array_dimensions, SOURCE_INFO);

    if ( (rsd2.rows() != nDir) || (rsd2.columns() != 2))
        throw ArgumentException("rsd2", exc_bad_array_dimensions, SOURCE_INFO);
    
    // Rotation angles.
    unsigned int nAng = nTestAngles;
    unsigned int nRot = nAng*nAng*nAng;
    Matrix angles(nRot, 3);
    unsigned int c = 0;
    for (unsigned int i = 0; i<nAng; i++) {
        double tx = i*TWO_PI/(nAng);
        for (unsigned int j = 0; j<nAng; j++) {
            double ty = j*TWO_PI/(nAng);
            for (unsigned int k = 0; k<nAng; k++) {
                double tz = k*TWO_PI/(nAng);
                angles(c, 0) = tx;
                angles(c, 1) = ty;
                angles(c, 2) = tz;
                c++;
            }
        }

    }

    // For each rotation.
    Array<size_t> ind;
    Array<Vector3D<double>> newVectors;
    RealVector dist(nRot);
    Matrix rotrsd(nDir, 2);

    for (unsigned int i=0; i<nRot; i++) {
        // Create rotation matrix.
        auto rm = geometry::AffineTransformation3D::rotationMatrixXYZ(
            angles(i, 0), angles(i, 1), angles(i, 2));
    
        // Rotate vectors
        newVectors = rm.transform(dirVectors);

        // Check indices of the closest positions and fill the rotated array.
        ind = findClosestVertex(newVectors, dirVectors);
        
        // Fill temp array with the rotated descriptor.
        for (index_t j = 0; j<nDir; j++) {
            rotrsd(ind[j], 0) = rsd2(j, 0);
            rotrsd(ind[j], 1) = rsd2(j, 1);
        }
                
        // Calculate distance.
        const auto& r2 = rotrsd;
        switch (distFunction) {
            case DistanceFunction::EuclideanDistance:    
                dist[i] = statistics::distance_metrics::euclideanDistance(
                    rsd1.begin(), rsd1.end(), r2.begin(), r2.end());
                break;
        
            case DistanceFunction::CityBlockDistance:    
                dist[i] = statistics::distance_metrics::cityBlockDistance(
                    rsd1.begin(), rsd1.end(), r2.begin(), r2.end());
                break;

            case DistanceFunction::ChebychevDistance:    
                dist[i] = statistics::distance_metrics::chebychevDistance(
                    rsd1.begin(), rsd1.end(), r2.begin(), r2.end());
                break;

            case DistanceFunction::MinDistance:    
                dist[i] = statistics::distance_metrics::minDistance(
                    rsd1.begin(), rsd1.end(), r2.begin(), r2.end());
                break;

            default:
                throw ArgumentException("distFunction", exc_bad_distance_function,
                    SOURCE_INFO);
        }
    }
    
    return dist.min();
    
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::mesh::compareSymmetryDescriptors(const Matrix& rsd1,
    const Matrix& rsd2, Array<Array<size_t>>& rotIndices,
    DistanceFunction distFunction)
{
    // Verify arguments.
    auto nDir = rsd1.rows();
    auto nRot = rotIndices.size();

    if (nRot<1)
        throw EmptyArrayException("rotIndices", SOURCE_INFO);

    if (nDir<1)
        throw EmptyArrayException("dirVectors", SOURCE_INFO);

    if ( (rsd1.columns() != 2))
        throw ArgumentException("rsd1", exc_bad_array_dimensions, SOURCE_INFO);

    if ( (rsd2.rows() != nDir) || (rsd2.columns() != 2))
        throw ArgumentException("rsd2", exc_bad_array_dimensions, SOURCE_INFO);
    
    for (unsigned int i=0; i<nRot; i++) {
        if ( (rotIndices[i].size() != nDir))
            throw ArgumentException("rotIndices", exc_bad_array_dimensions, SOURCE_INFO);
    }

    // For each rotation.
    RealVector dist(nRot);
    Matrix rotrsd(nDir, 2);

    for (unsigned int i=0; i<nRot; i++) {                
        // Fill temp array with the rotated descriptor.
        for (index_t j = 0; j<nDir; j++) {
            rotrsd(rotIndices[i][j], 0) = rsd2(j, 0);
            rotrsd(rotIndices[i][j], 1) = rsd2(j, 1);
        }
                
        // Calculate distance.
        const auto& r2 = rotrsd;
        switch (distFunction) {
            case DistanceFunction::EuclideanDistance:    
                dist[i] = statistics::distance_metrics::euclideanDistance(
                    rsd1.begin(), rsd1.end(), r2.begin(), r2.end());
                break;
        
            case DistanceFunction::CityBlockDistance:    
                dist[i] = statistics::distance_metrics::cityBlockDistance(
                    rsd1.begin(), rsd1.end(), r2.begin(), r2.end());
                break;

            case DistanceFunction::ChebychevDistance:    
                dist[i] = statistics::distance_metrics::chebychevDistance(
                    rsd1.begin(), rsd1.end(), r2.begin(), r2.end());
                break;

            case DistanceFunction::MinDistance:    
                dist[i] = statistics::distance_metrics::minDistance(
                    rsd1.begin(), rsd1.end(), r2.begin(), r2.end());
                break;

            default:
                throw ArgumentException("distFunction", exc_bad_distance_function,
                    SOURCE_INFO);
        }
    }
    
    return dist.min();
    
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::geometry::Triangle3D> nct::geometry::mesh::triangleCoord(
    const Array<Point3D>& vertices, 
    const Array<Vector3D<unsigned int>>& triangles)
{
    auto nt = triangles.size();
    Array<geometry::Triangle3D> trianglCoord(nt);

    for (index_t i=0; i<nt; i++) {
        trianglCoord[i][0].setCoefficients(
            vertices[triangles[i][0]][0],
            vertices[triangles[i][0]][1],
            vertices[triangles[i][0]][2]);

        trianglCoord[i][1].setCoefficients(
            vertices[triangles[i][1]][0],
            vertices[triangles[i][1]][1],
            vertices[triangles[i][1]][2]);

        trianglCoord[i][2].setCoefficients(
            vertices[triangles[i][2]][0],
            vertices[triangles[i][2]][1],
            vertices[triangles[i][2]][2]);
    }

    return trianglCoord;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::geometry::Line3D> nct::geometry::mesh::lineCoord(
    const Array<Point3D>& vertices, 
    const Array<Vector3D<unsigned int>>& triangles)
{
    auto nt = triangles.size();
    Array<geometry::Line3D> lines(nt * 3);

    for (index_t i=0; i<nt; i++) {
        lines[i*3 + 0][0].setCoefficients(
            vertices[triangles[i][0]][0],
            vertices[triangles[i][0]][1],
            vertices[triangles[i][0]][2]);

        lines[i * 3 + 0][1].setCoefficients(
            vertices[triangles[i][1]][0],
            vertices[triangles[i][1]][1],
            vertices[triangles[i][1]][2]);

        lines[i * 3 + 1][0].setCoefficients(
            vertices[triangles[i][0]][0],
            vertices[triangles[i][0]][1],
            vertices[triangles[i][0]][2]);

        lines[i * 3 + 1][1].setCoefficients(
            vertices[triangles[i][2]][0],
            vertices[triangles[i][2]][1],
            vertices[triangles[i][2]][2]);

        lines[i * 3 + 2][0].setCoefficients(
            vertices[triangles[i][1]][0],
            vertices[triangles[i][1]][1],
            vertices[triangles[i][1 ]][2]);

        lines[i * 3 + 2][1].setCoefficients(
            vertices[triangles[i][2]][0],
            vertices[triangles[i][2]][1],
            vertices[triangles[i][2]][2]);
    }
    
    return lines;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
