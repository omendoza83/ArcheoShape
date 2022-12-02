//=================================================================================================================
/**
 *  @file       RasterizedObject3D.cpp
 *  @brief      nct::geometry::RasterizedObject3D class implementation file.
 *  @details    This file contains the implementation of the nct::geometry::RasterizedObject3D class.
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
#include <nct/geometry/RasterizedObject3D.h>
#include <nct/geometry/mesh.h>
#include <nct/math/math_functions.h>
#include <nct/statistics/distance_metrics.h>
#include <nct/math/math.h>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::RasterizedObject3D::RasterizedObject3D(unsigned int div) : voxels_{false} 
{
    try {
        voxels_.resize(div, div, div);
    }
    catch (const nct_exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw InitializationException(SOURCE_INFO);
    }
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::RasterizedObject3D::RasterizedObject3D(const Array<Point3D>& points,
    double min, double max, unsigned int div) : voxels_{false}
{
    try {
        voxels_ = geometry::rasterization::rasterize(points, min, max, div);
    }
    catch (const nct_exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw InitializationException(SOURCE_INFO);
    }
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::RasterizedObject3D::RasterizedObject3D(const Array<geometry::Line3D>& lines,
    double min, double max,  unsigned int div, 
    rasterization::NConnectivity3D connectivity) : voxels_{false}
{
    try {
        voxels_ = geometry::rasterization::rasterize(lines, min, max, div, connectivity);
    }
    catch (const nct_exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw InitializationException(SOURCE_INFO);
    }
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::RasterizedObject3D::RasterizedObject3D(
    const Array<geometry::Triangle3D>& triangles,
    double min, double max, unsigned int div,
    rasterization::NConnectivity3D connectivity) : voxels_{false}
{
    try {
        voxels_ = geometry::rasterization::rasterize(triangles, min, max, div, connectivity);
    }
    catch (const nct_exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw InitializationException(SOURCE_INFO);
    }
}

//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::RasterizedObject3D::operator()(double x, double y, double z) const 
{
    unsigned int nd = static_cast<unsigned int>(voxels_.dimension1());

    if ( (std::abs(x) > 1) || (std::abs(y) > 1) || (std::abs(z) > 1))
        throw ArgumentException("x, y, z", exc_point_out_of_bounds, SOURCE_INFO);

    unsigned int i = static_cast<unsigned int>(nd*(x + 1.0)/(2.));
    if (i>=nd)
        i--;

    unsigned int j = static_cast<unsigned int>(nd*(y + 1.0)/(2.));
    if (j>=nd)
        j--;

    unsigned int k = static_cast<unsigned int>(nd*(z + 1.0)/(2.));
    if (k>=nd)
        k--;

    return voxels_(i, j, k);
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::RasterizedObject3D::operator()(unsigned int i, 
    unsigned int j, unsigned int k) const 
{
    return voxels_(i, j, k);
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
unsigned int nct::geometry::RasterizedObject3D::numberOfDivisions() const noexcept 
{
    return static_cast<unsigned int>(voxels_.dimension1());
}

//-----------------------------------------------------------------------------------------------------------------
const nct::SparseArray3D<bool>& nct::geometry::RasterizedObject3D::voxelArray() const noexcept 
{
    return voxels_;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Point3D nct::geometry::RasterizedObject3D::voxelCenter(
    unsigned int i, unsigned int j, unsigned int k) const
{
    unsigned int nd = static_cast<unsigned int>(voxels_.dimension1());

    double c = (nd)/2.0;
    return Point3D(i+0.5-c, j+0.5-c, k+0.5-c);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::RasterizedObject3D::meanDistance() const 
{
    double mean = 0;
    auto ne = voxels_.nonNullElements();
    auto nne = ne.size();

    Point3D coord;
    for (index_t i=0; i<nne; i++) {
        coord = voxelCenter(static_cast<unsigned int>(ne[i].first[0]), 
            static_cast<unsigned int>(ne[i].first[1]), 
            static_cast<unsigned int>(ne[i].first[2]));
        mean+=coord.magnitude();
    }

    return mean/nne;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<bool> nct::geometry::RasterizedObject3D::evalXYZ(
    const Array<Point3D>& points) const
{
    auto nt = points.size();
    Array<bool> f(nt);

    for (index_t i=0; i<nt; i++)
        f[i] = this->operator()(points[i][0], points[i][1], points[i][2]);

    return f;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<bool> nct::geometry::RasterizedObject3D::evalSph(
    const Array<Point3D>& points) const
{
    auto nt = points.size();
    Array<bool>  f(nt);
    
    Point3D xyz;
    for (index_t i=0; i<nt; i++) {
        xyz = points[i].sphericalToCartesian();
        f[i] = this->operator()(xyz[0], xyz[1], xyz[2]);
    }

    return f;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::RasterizedObject3D::Surface nct::geometry::RasterizedObject3D::surface(
    double r) const
{
    unsigned int nd = static_cast<unsigned int>(voxels_.dimension1());

    auto nTheta = 2*nd;
    auto nPhi = nd;
    auto nt = nPhi*nTheta - 2*nTheta + 2;    
    
    Surface ev;
    RealVector theta(nTheta);
    for (unsigned int i=0; i<nTheta; i++)
        theta[i] = i*(TWO_PI)/(nTheta);

    RealVector phi(nPhi-2);
    for (unsigned int i=0; i<(nPhi-2); i++)
        phi[i] = (i+1.)*(PI)/(nPhi-1.);

    unsigned int c = 0;
    ev.points.assign(nt, Point3D());

    ev.points[c++].setCoefficients(r, 0, 0);
    for (unsigned int i=0; i<(nPhi-2); i++)
        for (unsigned int j=0; j<nTheta; j++)        
            ev.points[c++].setCoefficients(r, theta[j], phi[i]);
    ev.points[c++].setCoefficients(r, 0, PI);

    ev.f = evalSph(ev.points);

    return ev;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::RasterizedObject3D::Surfaces nct::geometry::RasterizedObject3D::surfaces() const 
{
    unsigned int nd = static_cast<unsigned int>(voxels_.dimension1());
    Surfaces ev;

    // Radii.
    auto nr = nd/2;
    ev.r.assign(nr, 0.0);
    for (unsigned int i=0; i<nr; i++) {
        ev.r[i] = (i+1.0)/(nr);
        if (ev.r[i] > 1)
            ev.r[i] = 1;
    }

    // Angles.
    auto nTheta = 2*nd;
    auto nPhi = nd;
    auto nAngT = nPhi*nTheta - 2*nTheta + 2;    
    
    RealVector thetaT(nTheta);
    for (unsigned int i=0; i<nTheta; i++)
        thetaT[i] = i*(TWO_PI)/(nTheta);

    RealVector phiT(nPhi-2);
    for (unsigned int i=0; i<(nPhi-2); i++)
        phiT[i] = (i+1.)*(PI)/(nPhi-1.);

    unsigned int c = 0;
    ev.theta.assign(nAngT, 0.0);
    ev.phi.assign(nAngT, 0.0);

    ev.theta[c] = 0;
    ev.phi[c++] = 0;
    for (unsigned int i=0; i<(nPhi-2); i++) {
        for (unsigned int j=0; j<nTheta; j++) {
            ev.theta[c] = thetaT[j];
            ev.phi[c++] = phiT[i];
        }
    }
    ev.theta[c] = 0;
    ev.phi[c++] = PI;

    // Evaluate function.
    ev.f.assign(nr, nAngT, 0.0);        
    for (unsigned int i=0; i<nr; i++) {
        for (unsigned int j=0; j<nAngT; j++) {            
            Vector3D<double> pointSp(ev.r[i], ev.theta[j], ev.phi[j]);
            auto pointXYZ = pointSp.sphericalToCartesian();
            ev.f(i,j) = this->operator()(pointXYZ[0], pointXYZ[1], pointXYZ[2]);
        }
    }

    return ev;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::RasterizedObject3D nct::geometry::RasterizedObject3D::rasterizedSurface(double r) const 
{
    unsigned int nd = static_cast<unsigned int>(voxels_.dimension1());

    auto model = surface(r);

    RasterizedObject3D surf(nd);

    Point3D xyz;
    auto nt = model.points.size();
    for (index_t i = 0; i < nt; i++) {
        if (model.f[i]) {
            xyz = model.points[i].sphericalToCartesian();

            unsigned int ii = static_cast<unsigned int>(nd * (xyz[0] + 1.0) / (2.));
            if (ii >= nd)
                ii--;

            unsigned int jj = static_cast<unsigned int>(nd * (xyz[1] + 1.0) / (2.));
            if (jj >= nd)
                jj--;

            unsigned int kk = static_cast<unsigned int>(nd * (xyz[2] + 1.0) / (2.));

            if (kk >= nd)
                kk--;

            surf.voxels_.modify(ii, jj, kk, true);
        }
    }

    return surf;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::RasterizedObject3D::HarmonicDecomposition
nct::geometry::RasterizedObject3D::harmonicDecomposition(double tol) const 
{
    unsigned int nd = static_cast<unsigned int>(voxels_.dimension1());
    return harmonicDecomposition(harmonicMatrices(nd, tol));
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::RasterizedObject3D::HarmonicDecomposition
nct::geometry::RasterizedObject3D::harmonicDecomposition(const HarmonicMatrices& hm) const 
{
    unsigned int nd = static_cast<unsigned int>(voxels_.dimension1());

    if (hm.hB.size()==1)
        throw EmptyArrayException("hb", SOURCE_INFO);

    unsigned int maxl = hm.hB[hm.hB.size()-1].l;
    
    // Points where the function will be evaluated.
    auto nr = nd/2;
    RealVector r(nr);
    for (unsigned int i=0; i<nr; i++) {
        r[i] = (i+1.0)/(nr);
        if (r[i] > 1)
            r[i] = 1;
    }

    auto nAngT = hm.theta.size();
    Array<Vector3D<double>> points(nAngT);
    for (index_t i=0; i<nAngT; i++)
        points[i].setCoefficients(0, hm.theta[i], hm.phi[i]);

    // Compute degree of harmonics.
    HarmonicDecomposition hc;

    auto nhs = hm.hB.size();
    auto nhT = (maxl + 1)*(maxl + 1);
    hc.h.assign(nhT, signal::spherical_harmonics::SphericalHarmonic());
    
    unsigned int cont = 0;
    for (int l = 0; l<=static_cast<int>(maxl); l++) {
        for (int m = -l; m<=l; m++) {            
            hc.h[cont].l = l;
            hc.h[cont].m = m;
            cont++;
        }
    }

    // For each surface.
    hc.c.assign(nr, nhT, 0.0);
    
    for (unsigned int s=0; s<nr; s++) {
        // Evaluate surface.
        for (index_t i=0; i<nAngT; i++)
            points[i][0] = r[s];
        
        Array<bool> f = evalSph(points);
        RealVector ff = f.toArray<double>();
        
        // Compute coefficients.
        auto cc = matrixVectorProduct(hm.BtBI,(matrixVectorProduct(hm.Bt, ff)));
        
        // Compute coefficients for negative m.
        cont = 0;
        for (int l = 0; l<=static_cast<int>(maxl); l++) {
            for (int m = -l; m<=l; m++) {
                // Find harmonic in the solution.
                unsigned int i;
                for (i = 0; i<nhs; i++) {
                    if ((hm.hB[i].l) == l && (hm.hB[i].m) == std::abs(m))
                        break;
                }
                if (i == nhs) {
                    cont++;
                    continue;
                }

                if (m<0) {
                    double sign = std::abs(m)%2 ? (-1): 1; 
                    hc.c(s,cont) = Complex(sign*cc[i], -sign*cc[i+(size_t)1]);
                }
                else if (m == 0) {
                    hc.c(s,cont) = Complex(cc[i], 0);
                }
                else {
                    hc.c(s,cont) = Complex(cc[i], cc[i+(size_t)1]);
                }
            
                cont++;
            }
        }        
    }

    return hc;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Matrix nct::geometry::RasterizedObject3D::harmonicDescriptor(double tol) const 
{
    unsigned int nd = static_cast<unsigned int>(voxels_.dimension1());
    return harmonicDescriptor(harmonicMatrices(nd, tol));
}

//-----------------------------------------------------------------------------------------------------------------
nct::Matrix nct::geometry::RasterizedObject3D::harmonicDescriptor(const HarmonicMatrices& hm) const 
{
    // Harmonic decomposition.
    auto hc = harmonicDecomposition(hm);

    unsigned int maxl = hm.hB[hm.hB.size()-1].l;

    // Radii to evaluate model function.
    auto nr = hc.c.rows();
    RealVector r(nr);
    for (index_t i=0; i<nr; i++) {
        r[i] = (i+1.0)/(nr);
        if (r[i] > 1)
            r[i] = 1;
    }    
    
    // Evaluate harmonics.
    auto htot = hc.h.size();
    auto nPoints = hm.theta.size();
    ComplexMatrix ylm(htot, nPoints);
    for (index_t hi=0; hi<htot; hi++)
        for (index_t i=0; i<nPoints; i++)
            ylm(hi, i) = math::sphericalHarmonic(
                hc.h[hi].l, hc.h[hi].m, hm.theta[i], hm.phi[i]);

    // Calculate descriptor.
    Matrix d(nr, maxl + (size_t)1, 0);

    // for each radius.
    for (index_t ri=0; ri<nr; ri++) {
        // Evaluate frm.    
        ComplexMatrix frm(maxl + (size_t)1, nPoints, 0);

        for (index_t hi=0; hi<htot; hi++)
            for (index_t i=0; i<nPoints; i++)
                frm(hc.h[hi].l, i) += hc.c(ri, hi)*ylm(hi, i);

        for (unsigned int hi=0; hi<=maxl; hi++) {
            for (index_t i=0; i<nPoints; i++)
                d(ri, hi) += norm(frm(hi, i));
            d(ri, hi) = std::sqrt(d(ri, hi));
        }        
    }

    return d;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array3D<double> nct::geometry::RasterizedObject3D::eddt() const 
{
    unsigned int nd = static_cast<unsigned int>(voxels_.dimension1());

    double ts = meanDistance();
    auto voxelizedObj = voxels_.toArray();
    auto tr = statistics::distance_metrics::fastSquaredEuclideanDT(voxelizedObj);

    for (unsigned int i=0; i<nd; i++)
        for (unsigned int j=0; j<nd; j++)
            for (unsigned int k=0; k<nd; k++)
                tr(i,j,k) = exp(-(tr(i,j,k))/ts);    
    return tr;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::RasterizedObject3D::SymmetryDescriptor
nct::geometry::RasterizedObject3D::symmetryDescriptor() const 
{
    unsigned int nd = static_cast<unsigned int>(voxels_.dimension1());

    // Calculate similarity tansform.
    auto tr = eddt();

    double c = nd/2.0;    
    Point3D vCenter;
    
    auto trSph = tr;
    for (unsigned int i=0; i<nd; i++) {
        for (unsigned int j=0; j<nd; j++) {
            for (unsigned int k=0; k<nd; k++) {
                vCenter = Point3D(i+0.5-c, j+0.5-c, k+0.5-c);
                if (vCenter.magnitude() > c)
                    trSph(i,j,k) = 0;
            }
        }
    }
    
    // Calculate points on the sphere.
    SymmetryDescriptor symmDescriptor;

    symmDescriptor.norms = mesh::sphereVertices(2*nd, nd);
    
    auto np = symmDescriptor.norms.size();
    symmDescriptor.sd.assign(np, 1, 0.0);
    symmDescriptor.rsd.assign(np, 2, 0);

    // Compute symmetry descriptor.
    Array<bool> planeOk(np, false);
    Array3D<bool> voxOk(nd, nd, nd);
    
    double d;
    
    Point3D newCenter;
    Array3D<double> reflex(nd, nd, nd);
    int ii, ji, ki;
    for (index_t p = 0; p<np; p++) {
        if (!planeOk[p]) {
            voxOk.fill(false);
            Point3D& norm = symmDescriptor.norms[p];
            reflex.fill(0);

            // Compute reflexions.
            for (unsigned int i=0; i<nd; i++) {
                for (unsigned int j=0; j<nd; j++) {
                    for (unsigned int k=0; k<nd; k++) {
                        if (!(voxOk(i,j,k))) {
                            // Compute center of the voxel.
                            vCenter = Point3D(i+0.5-c, j+0.5-c, k+0.5-c);
                    
                            // Compute distance of the voxel to the plane.
                            d = dotProduct(vCenter, norm);

                            // Compute new index of the reflexion.
                            newCenter = vCenter - 2*d*norm;
                            
                            ii = static_cast<int>(newCenter[0] + c);
                            if (ii<0)
                                ii = 0;
                            if (ii>=static_cast<int>(nd))
                                ii = static_cast<int>(nd-1);

                            ji = static_cast<int>(newCenter[1] + c);
                            if (ji<0)
                                ji = 0;
                            if (ji>=static_cast<int>(nd))
                                ji = static_cast<int>(nd-1);

                            ki = static_cast<int>(newCenter[2] + c);
                            if (ki<0)
                                ki = 0;
                            if (ki>=static_cast<int>(nd))
                                ki = static_cast<int>(nd-1);

                            if ( (vCenter.magnitude() <= c) ||  (newCenter.magnitude() <=c) ) {
                                reflex(i, j, k) = tr(ii, ji, ki);
                                reflex(ii, ji, ki) = tr(i, j, k);
                            }

                            voxOk(i,j,k) = true;
                            voxOk(ii,ji,ki) = true;
                        }
                    }
                }
            }

            // Compute sd.
            double mag = 0;
            for (unsigned int i=0; i<nd; i++)
                for (unsigned int j=0; j<nd; j++)
                    for (unsigned int k=0; k<nd; k++)
                        mag+=math::sqr(reflex(i,j,k) - trSph(i,j,k));
            symmDescriptor.sd[p] = std::sqrt(mag)/2;
            
            // Verify the plane in the opposite direction.
            auto opPlane = mesh::findClosestVertex((-1.*norm), symmDescriptor.norms);
            symmDescriptor.sd[opPlane] = symmDescriptor.sd[p];

            planeOk[p] = true;
            planeOk[opPlane] = true;
        }
    }

    // Compute reflexive symmetry destriptor.
    double fsd = 0;
    for (unsigned int i=0; i<nd; i++)
        for (unsigned int j=0; j<nd; j++)
            for (unsigned int k=0; k<nd; k++)
                fsd+=math::sqr(trSph(i,j,k));
    fsd = std::sqrt(fsd);
    for (index_t p = 0; p<np; p++) {
        symmDescriptor.rsd(p, 0) = std::sqrt(math::sqr(fsd) - math::sqr(symmDescriptor.sd[p]))/fsd;
        symmDescriptor.rsd(p, 1) = symmDescriptor.sd[p]/fsd;
    }

    return symmDescriptor;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::RasterizedObject3D::HarmonicMatrices 
nct::geometry::RasterizedObject3D::harmonicMatrices(unsigned int div, double tol) 
{
    HarmonicMatrices mat;

    // Angles.
    auto nTheta = 2*div;
    auto nPhi = div;
    auto nAngT = nPhi*nTheta - 2*nTheta + 2;    
    
    RealVector thetaT(nTheta);
    for (unsigned int i=0; i<nTheta; i++)
        thetaT[i] = i*(TWO_PI)/(nTheta);

    RealVector phiT(nPhi-2);
    for (unsigned int i=0; i<(nPhi-2); i++)
        phiT[i] = (i+1.)*(PI)/(nPhi-1.);

    unsigned int c = 0;
    mat.theta.assign(nAngT, 0.0);
    mat.phi.assign(nAngT, 0.0);

    mat.theta[c] = 0;
    mat.phi[c++] = 0;
    for (unsigned int i=0; i<(nPhi-2); i++) {
        for (unsigned int j=0; j<nTheta; j++) {
            mat.theta[c] = thetaT[j];
            mat.phi[c++] = phiT[i];
        }
    }
    mat.theta[c] = 0;
    mat.phi[c++] = PI;

    // Compute matrix of harmonics.
    mat.maxl = static_cast<int>((div-1)/2);
    
    auto sphMatrix = signal::spherical_harmonics::orthogonalHarmonicMatrix(mat.maxl, mat.theta, mat.phi);
    auto B = std::move(sphMatrix.mat);
    mat.hB = std::move(sphMatrix.harmonics);

    mat.Bt = B.transpose();
    mat.BtBI = math::linear_algebra::inverse(mat.Bt*B, tol);

    return mat;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
