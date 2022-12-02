//=================================================================================================================
/**
 *  @file       rasterization.cpp
 *  @brief      Implementation file of functions of the nct::geometry::rasterization namespace.
 *  @details    This file contains the implementation of the functions defined in the
 *              nct::geometry::rasterization namespace.            
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
#include <nct/geometry/rasterization.h>
#include <nct/math/math.h>

//=================================================================================================================
//        FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::SparseArray2D<bool> nct::geometry::rasterization::rasterize(
    const Array<Point2D>& points, double min, double max, unsigned int div)
{
    if ( (min>=max) )
        throw ArgumentException("min, max", exc_bad_grid_limits, SOURCE_INFO);

    if ( (div<1) )
        throw ArgumentException("div", div, (unsigned int)2, RelationalOperator::GreaterThanOrEqualTo,
            SOURCE_INFO);

    // Calculate grid.
    RealVector x(static_cast<size_t>(div) + 1);
    for (unsigned int i=0; i<=div; i++)
        x[i] = min + i*(max - min)/div;

    // Rasterize points.
    SparseArray2D<bool> pixels(div, div);
    auto np = points.size();

    for (index_t p = 0; p<np; p++) {
        double c1 = points[p].v1();
        int i1 = -1;
        for (unsigned int i=0; i<div; i++) {
            if ( (c1>=x[i]) && (c1<x[i+(size_t)1]) ) {
                i1 = i;
                break;
            }
        }

        double c2 = points[p].v2();
        int i2 = -1;
        for (unsigned int j=0; j<div; j++) {
            if ( (c2>=x[j]) && (c2<x[j+(size_t)1]) ) {
                i2 = j;
                break;
            }
        }

        if ( (i1>=0)&&(i2>=0) )
            pixels.modify(i1, i2, true);
    }

    return pixels;
}

//-----------------------------------------------------------------------------------------------------------------
nct::SparseArray2D<bool> nct::geometry::rasterization::rasterize(
    const Array<Line>& lines, double min, double max, unsigned int div, NConnectivity2D connectivity)
{
    if ( (min>=max) )
        throw ArgumentException("min, max", exc_bad_grid_limits, SOURCE_INFO);

    if ( (div<1) )
        throw ArgumentException("div", div, (unsigned int)2, RelationalOperator::GreaterThanOrEqualTo,
            SOURCE_INFO);

    if ( (connectivity != NConnectivity2D::FourConnected) &&
         (connectivity != NConnectivity2D::EightConnected) )
        throw ArgumentException("connectivity", exc_bad_n_connectivity, 
            SOURCE_INFO);

    // Calculate grid and centers.
    double lL = (max-min)/div;

    RealVector x(static_cast<size_t>(div) + 1);
    for (unsigned int i=0; i<=div; i++)
        x[i] = min + i*(max - min)/div;

    RealVector xc(div);
    for (unsigned int i=0; i<div; i++)
        xc[i] = x[i] + lL/2;

    // Unitary vectors to the vertices of each pixel.
    Point2D v1(-1, 1);
    Point2D v2(1, 1);
    Point2D v3(1, -1);
    Point2D v4(-1, -1);

    v1.normalize();
    v2.normalize();
    v3.normalize();
    v4.normalize();

    // Unitary vectors to the edges of each pixel.
    Point2D e1(1, 0);
    Point2D e2(0, 1);
    Point2D e3(-1, 0);
    Point2D e4(0, -1);
    
    // Rasterize lines.
    SparseArray2D<bool> pixels(div, div);
    auto nl = lines.size();

    for (index_t l = 0; l<nl; l++) {
        // Points of the line.
        Vector2D<int> p1Ind(-1, -1);
        Vector2D<int> p2Ind(-1, -1);
        for (int p=0; p<2; p++) {
            double c1 = 0;
            double c2 = 0;
            if (p == 0) {
                c1 = lines[l][0].v1();
                c2 = lines[l][0].v2();
            }
            else {
                c1 = lines[l][1].v1();
                c2 = lines[l][1].v2();
            }

            int i1 = -1;
            for (unsigned int i=0; i<div; i++) {
                if ( (c1>=x[i]) && (c1<=x[i+(size_t)1]) ) {
                    i1 = i;
                    break;
                }
            }

            
            int i2 = -1;
            for (unsigned int j=0; j<div; j++) {
                if ( (c2>=x[j]) && (c2<x[j+(size_t)1]) ) {
                    i2 = j;
                    break;
                }
            }

            if ( (i1>=0)&&(i2>=0) )
                pixels.modify(i1, i2, true);

            if (p == 0)
                p1Ind.setCoefficients(i1, i2);
            else if (p == 1)
                p2Ind.setCoefficients(i1, i2);
        }        

        // Limits of the search.
        
        int imin = 0;
        int imax = div-1;
        if (p1Ind[0]>=0 && p2Ind[0]>=0) {
            // The point is inside the grid.
            imin = math::min(p1Ind[0], p2Ind[0]);
            imax = math::max(p1Ind[0], p2Ind[0]);
        }
        else {
            // The points are outside the grid.
            if ( (lines[l][0].v1()<min) && (lines[l][1].v1()<min) ) {
                imin = -1;
                imax = -1;
            }

            if ( (lines[l][0].v1()>max) && (lines[l][1].v1()>max) ) {
                imin = -1;
                imax = -1;
            }

            // One point is outside the grid.
            if ( ((lines[l][0].v1()<min) && (lines[l][1].v1()>=min) && (lines[l][1].v1()<=max)) ||
                 ((lines[l][1].v1()<min) && (lines[l][0].v1()>=min) && (lines[l][0].v1()<=max)) )
            {
                imin = 0;
                imax = math::max(p1Ind[0], p2Ind[0]);
            }

            if ( ((lines[l][0].v1()>max) && (lines[l][1].v1()<=max) && (lines[l][1].v1()>=min)) ||
                 ((lines[l][1].v1()>max) && (lines[l][0].v1()<=max) && (lines[l][0].v1()>=min)) )
            {
                imin = math::min(p1Ind[0], p2Ind[0]);
                imax = div-1;
            }
        }
    
        int jmin = 0;
        int jmax = div-1;
        if (p1Ind[1]>=0 && p2Ind[1]>=0) {
            // The point is inside the grid.
            jmin = math::min(p1Ind[1], p2Ind[1]);
            jmax = math::max(p1Ind[1], p2Ind[1]);
        }
        else {
            // The points are outside the grid.
            if ( (lines[l][0].v2()<min) && (lines[l][1].v2()<min) ) {
                jmin = -1;
                jmax = -1;
            }

            if ( (lines[l][0].v2()>max) && (lines[l][1].v2()>max) ) {
                jmin = -1;
                jmax = -1;
            }

            // One point is outside the grid.
            if ( ((lines[l][0].v2()<min) && (lines[l][1].v2()>=min) && (lines[l][1].v2()<=max)) ||
                 ((lines[l][1].v2()<min) && (lines[l][0].v2()>=min) && (lines[l][0].v2()<=max)) )
            {
                jmin = 0;
                jmax = math::max(p1Ind[1], p2Ind[1]);
            }

            if ( ((lines[l][0].v2()>max) && (lines[l][1].v2()<=max) && (lines[l][1].v2()>=min)) ||
                 ((lines[l][1].v2()>max) && (lines[l][0].v2()<=max) && (lines[l][0].v2()>=min)) )
            {
                jmin = math::min(p1Ind[1], p2Ind[1]);
                jmax = div-1;
            }
        }

        // Line.
        auto v = lines[l][1] - lines[l][0];
        v.normalize();
        Point2D n(v.v2(), -v.v1());
        double coeff = -n[0]*lines[l][0][0] -n[1]*lines[l][0][1];
        double normS = n.magnitude();

        double t = 0;
        if (connectivity == NConnectivity2D::FourConnected) {
            double a1 = angleBetweenVectors(n, e1);
            double a2 = angleBetweenVectors(n, e2);
            double a3 = angleBetweenVectors(n, e3);
            double a4 = angleBetweenVectors(n, e4);

            if ( (a1>=0) && (a1<=PI/4) )
                t = (lL/2)*std::cos(a1);
            else if ( (a2>=0) && (a2<=PI/4) )
                t = (lL/2)*std::cos(a2);
            else if ( (a3>=0) && (a3<=PI/4) )
                t = (lL/2)*std::cos(a3);
            else if ( (a4>=0) && (a4<=PI/4) )
                t = (lL/2)*std::cos(a4);
        }
        else if (connectivity == NConnectivity2D::EightConnected) {
            double a1 = angleBetweenVectors(n, v1);
            double a2 = angleBetweenVectors(n, v2);
            double a3 = angleBetweenVectors(n, v3);
            double a4 = angleBetweenVectors(n, v4);

            if ( (a1>=0) && (a1<=PI/4) )
                t = (lL/2)*std::sqrt(2.)*std::cos(a1);
            else if ( (a2>=0) && (a2<=PI/4) )
                t = (lL/2)*std::sqrt(2.)*std::cos(a2);
            else if ( (a3>=0) && (a3<=PI/4) )
                t = (lL/2)*std::sqrt(2.)*std::cos(a3);
            else if ( (a4>=0) && (a4<=PI/4) )
                t = (lL/2)*std::sqrt(2.)*std::cos(a4);
        }

        for (int i=imin; i<=imax; i++) {
            for (int j=jmin; j<=jmax; j++) {
                double s = std::abs(n[0] * xc[i] + n[1] * xc[j] + coeff) / normS;
                if (s<=t)
                    pixels.modify(i, j, true);
            }
        }
    }

    return pixels;
}

//-----------------------------------------------------------------------------------------------------------------
nct::SparseArray3D<bool> nct::geometry::rasterization::rasterize(
    const Array<Point3D>& points, double min, double max, unsigned int div)
{
    if ( (min>=max) )
        throw ArgumentException("min, max", exc_bad_grid_limits, SOURCE_INFO);

    if ( (div<1) )
        throw ArgumentException("div", div, (unsigned int)2, RelationalOperator::GreaterThanOrEqualTo,
            SOURCE_INFO);

    // Calculate grid.
    RealVector x(static_cast<size_t>(div) + 1);
    for (unsigned int i=0; i<=div; i++)
        x[i] = min + i*(max - min)/div;

    // Rasterize points.
    SparseArray3D<bool> voxels(div, div, div);
    auto np = points.size();

    for (index_t p = 0; p<np; p++) {
        double c1 = points[p].v1();
        int i1 = -1;
        for (unsigned int i=0; i<div; i++) {
            if ( (c1>=x[i]) && (c1<x[i+(size_t)1]) ) {
                i1 = i;
                break;
            }
        }

        double c2 = points[p].v2();
        int i2 = -1;
        for (unsigned int j=0; j<div; j++) {
            if ( (c2>=x[j]) && (c2<x[j+(size_t)1]) ) {
                i2 = j;
                break;
            }
        }

        double c3 = points[p].v3();
        int i3 = -1;
        for (unsigned int k=0; k<div; k++) {
            if ( (c3>=x[k]) && (c3<x[k+(size_t)1]) ) {
                i3 = k;
                break;
            }
        }

        if ( (i1>=0)&&(i2>=0)&&(i3>=0) )
            voxels.modify(i1, i2, i3, true);
    }

    return voxels;
}

//-----------------------------------------------------------------------------------------------------------------
nct::SparseArray3D<bool> nct::geometry::rasterization::rasterize(const Array<Line3D>& lines,
    double min, double max, unsigned int div, NConnectivity3D connectivity)
{
    if ( (min>=max) )
        throw ArgumentException("min, max", exc_bad_grid_limits, SOURCE_INFO);

    if ( (div<1) )
        throw ArgumentException("div", div, (unsigned int)2, RelationalOperator::GreaterThanOrEqualTo,
            SOURCE_INFO);

    if ( (connectivity != NConnectivity3D::SixConnected) && 
         (connectivity != NConnectivity3D::TwentySixConnected) )
        throw ArgumentException("connectivity", exc_bad_n_connectivity, 
        SOURCE_INFO);

    // Calculate grid and centers.
    double lL = (max-min)/div;

    RealVector x(div + (size_t)1);
    for (unsigned int i=0; i<=div; i++)
        x[i] = min + i*(max - min)/div;

    RealVector xc(div);
    for (unsigned int i=0; i<div; i++)
        xc[i] = x[i] + lL/2;

    // Distance factor.
    double rc = 0;
    if (connectivity == NConnectivity3D::SixConnected) 
        rc = lL/2.0;
    else if (connectivity == NConnectivity3D::TwentySixConnected)
        rc = std::sqrt(3.0)*lL/2.0;    

    // Rasterize lines.
    SparseArray3D<bool> voxels(div, div, div);
    auto nl = lines.size();
    int idiv= static_cast<int>(div);
    for (index_t l = 0; l<nl; l++) {
        // Points of the line.
        Vector3D<int> p1Ind(-1, -1, -1);
        Vector3D<int> p2Ind(-1, -1, -1);
        for (int p=0; p<2; p++) {
            Point3D pp;
            if (p == 0)
                pp = lines[l][0];
            else
                pp = lines[l][1];

            int i1 = -1;
            for (unsigned int i=0; i<div; i++) {
                if ( (pp[0]>=x[i]) && (pp[0]<=x[i+(size_t)1]) ) {
                    i1 = i;
                    break;
                }
            }
            
            int i2 = -1;
            for (unsigned int j=0; j<div; j++) {
                if ( (pp[1]>=x[j]) && (pp[1]<x[j+(size_t)1]) ) {
                    i2 = j;
                    break;
                }
            }

            int i3 = -1;
            for (unsigned int k=0; k<div; k++) {
                if ( (pp[2]>=x[k]) && (pp[2]<x[k+(size_t)1]) ) {
                    i3 = k;
                    break;
                }
            }

            if ( (i1>=0)&&(i2>=0)&&(i3>=0) ) {
                voxels.modify(i1, i2, i3, true);
                
                // Check neighbors.
                for (int i=(i1-1); i<=(i1+1); i++) {
                    if ((i<0) || (i>=idiv))
                        continue;

                    for (int j=(i2-1); j<=(i2+1); j++) {
                        if ((j<0) || (j>=idiv))
                            continue;

                        for (int k=(i2-1); k<=(i2+1); k++) {
                            if ((k<0) || (k>=idiv))
                                continue;

                            Point3D center(xc[i], xc[j], xc[k]);
                            double dist = (pp - center).magnitude();
                            if (dist <= rc)
                                voxels.modify(i, j, k, true);
                        }
                    }
                }
            }

            if (p == 0)
                p1Ind.setCoefficients(i1, i2, i3);
            else if (p == 1)
                p2Ind.setCoefficients(i1, i2, i3);
        }        

        // Limits of the search.
        int imin = 0;
        int imax = div-1;
        if (p1Ind[0]>=0 && p2Ind[0]>=0) {
            // The point is inside the grid.
            imin = math::min(p1Ind[0], p2Ind[0]);
            imax = math::max(p1Ind[0], p2Ind[0]);
        }
        else {
            // One point is outside the grid.
            if ( ((lines[l][0].v1()<min) && (lines[l][1].v1()>=min) && (lines[l][1].v1()<=max)) ||
                 ((lines[l][1].v1()<min) && (lines[l][0].v1()>=min) && (lines[l][0].v1()<=max)) )
            {
                imin = 0;
                imax = math::max(p1Ind[0], p2Ind[0]);
            }

            if ( ((lines[l][0].v1()>max) && (lines[l][1].v1()<=max) && (lines[l][1].v1()>=min)) ||
                 ((lines[l][1].v1()>max) && (lines[l][0].v1()<=max) && (lines[l][0].v1()>=min)) )
            {
                imin = math::min(p1Ind[0], p2Ind[0]);
                imax = div-1;
            }
        }
    
        int jmin = 0;
        int jmax = div-1;
        if (p1Ind[1]>=0 && p2Ind[1]>=0) {
            // The point is inside the grid.
            jmin = math::min(p1Ind[1], p2Ind[1]);
            jmax = math::max(p1Ind[1], p2Ind[1]);
        }
        else {
            // One point is outside the grid.
            if ( ((lines[l][0].v2()<min) && (lines[l][1].v2()>=min) && (lines[l][1].v2()<=max)) ||
                 ((lines[l][1].v2()<min) && (lines[l][0].v2()>=min) && (lines[l][0].v2()<=max)) )
            {
                jmin = 0;
                jmax = math::max(p1Ind[1], p2Ind[1]);
            }

            if ( ((lines[l][0].v2()>max) && (lines[l][1].v2()<=max) && (lines[l][1].v2()>=min)) ||
                 ((lines[l][1].v2()>max) && (lines[l][0].v2()<=max) && (lines[l][0].v2()>=min)) )
            {
                jmin = math::min(p1Ind[1], p2Ind[1]);
                jmax = div-1;
            }
        }

        int kmin = 0;
        int kmax = div-1;
        if (p1Ind[2]>=0 && p2Ind[2]>=0) {
            // The point is inside the grid.
            kmin = math::min(p1Ind[2], p2Ind[2]);
            kmax = math::max(p1Ind[2], p2Ind[2]);
        }
        else {
            // One point is outside the grid.
            if ( ((lines[l][0].v3()<min) && (lines[l][1].v3()>=min) && (lines[l][1].v3()<=max)) ||
                 ((lines[l][1].v3()<min) && (lines[l][0].v3()>=min) && (lines[l][0].v3()<=max)) )
            {
                kmin = 0;
                kmax = math::max(p1Ind[2], p2Ind[2]);
            }

            if ( ((lines[l][0].v3()>max) && (lines[l][1].v3()<=max) && (lines[l][1].v3()>=min)) ||
                 ((lines[l][1].v3()>max) && (lines[l][0].v3()<=max) && (lines[l][0].v3()>=min)) )
            {
                kmin = math::min(p1Ind[2], p2Ind[2]);
                kmax = div-1;
            }
        }

        // Line.
        auto v = lines[l][1] - lines[l][0];
        v.normalize();
            
        for (int i=imin; i<=imax; i++) {
            for (int j=jmin; j<=jmax; j++) {
                for (int k=kmin; k<=kmax; k++) {
                    Point3D center(xc[i], xc[j], xc[k]);
                    auto pq = center - lines[l][0];
                    auto pq_x_v = crossProduct(pq, v);
                    double s = pq_x_v.magnitude();
                    if (s<=rc)
                        voxels.modify(i, j, k, true);
                }
            }
        }
    }

    return voxels;
}

//-----------------------------------------------------------------------------------------------------------------
nct::SparseArray3D<bool> nct::geometry::rasterization::rasterize(const Array<Triangle3D>& triangles,
    double min, double max, unsigned int div, NConnectivity3D connectivity)
{
    if ( (min>=max) )
        throw ArgumentException("min, max", exc_bad_grid_limits, SOURCE_INFO);

    if ( (div<1) )
        throw ArgumentException("div", div, (unsigned int)2, RelationalOperator::GreaterThanOrEqualTo,
            SOURCE_INFO);

    if ( (connectivity != NConnectivity3D::SixConnected) && 
         (connectivity != NConnectivity3D::TwentySixConnected) )
        throw ArgumentException("connectivity", exc_bad_n_connectivity, SOURCE_INFO);

    // Calculate grid and centers.
    double lL = (max-min)/div;

    RealVector x(div + (size_t)1);
    for (unsigned int i=0; i<=div; i++)
        x[i] = min + i*(max - min)/div;

    RealVector xc(div);
    for (unsigned int i=0; i<div; i++)
        xc[i] = x[i] + lL/2;

    // Unitary vectors to the vertices of each voxel.
    Array<Point3D> vv(8);
    vv[0] = Point3D(1, 1, 1);
    vv[1] = Point3D(-1, 1, 1);
    vv[2] = Point3D(1, -1, 1);
    vv[3] = Point3D(-1, -1, 1);
    vv[4] = Point3D(1, 1, -1);
    vv[5] = Point3D(-1, 1, -1);
    vv[6] = Point3D(1, -1, -1);
    vv[7] = Point3D(-1, -1, -1);

    for (int i=0; i<8; i++)
        vv[i].normalize();

    // Unitary vectors to the edges of each pixel.
    Array<Point3D> ve(6);
    ve[0] = Point3D(1, 0, 0);
    ve[1] = Point3D(-1, 0, 0);
    ve[2] = Point3D(0, 1, 0);
    ve[3] = Point3D(0, -1, 0);
    ve[4] = Point3D(0, 0, 1);
    ve[5] = Point3D(0, 0, -1);

    for (int i=0; i<6; i++)
        ve[i].normalize();

    // Rasterize lines and points.
    auto nt = triangles.size();
    Array<Line3D> lines(nt * 3);

    for (index_t t = 0; t<nt; t++) {
        lines[3*t][0] = triangles[t][0];
        lines[3 * t][1] = triangles[t][1];

        lines[3 * t + 1][0] = triangles[t][0];
        lines[3 * t + 1][1] = triangles[t][2];

        lines[3 * t + 2][0] = triangles[t][1];
        lines[3 * t + 2][1] = triangles[t][2];
    }

    SparseArray3D<bool> voxels = rasterize(lines, min, max, div, connectivity);

    // Rasterize triangles.
    for (index_t t = 0; t<nt; t++) {
        // Find limits of the search.
        Vector3D<int> p1Ind(-1, -1, -1);
        Vector3D<int> p2Ind(-1, -1, -1);
        Vector3D<int> p3Ind(-1, -1, -1);

        for (int p=0; p<3; p++) {
            Point3D pp;
            if (p == 0)
                pp = triangles[t][0];
            else if (p == 1)
                pp = triangles[t][1];
            else if (p == 2)
                pp = triangles[t][2];

            int i1 = -1;
            for (unsigned int i=0; i<div; i++) {
                if ( (pp[0]>=x[i]) && (pp[0]<=x[i+(size_t)1]) ) {
                    i1 = i;
                    break;
                }
            }
            
            int i2 = -1;
            for (unsigned int j=0; j<div; j++) {
                if ( (pp[1]>=x[j]) && (pp[1]<x[j+(size_t)1]) ) {
                    i2 = j;
                    break;
                }
            }

            int i3 = -1;
            for (unsigned int k=0; k<div; k++) {
                if ( (pp[2]>=x[k]) && (pp[2]<x[k+(size_t)1]) ) {
                    i3 = k;
                    break;
                }
            }

            if (p == 0)
                p1Ind.setCoefficients(i1, i2, i3);
            else if (p == 1)
                p2Ind.setCoefficients(i1, i2, i3);
            else if (p == 2)
                p3Ind.setCoefficients(i1, i2, i3);
        }        

        int imin = 0;
        int imax = div-1;
        if ( p1Ind[0]>=0 && p2Ind[0]>=0 && p3Ind[0]>=0 ) {
            imin = math::min(p1Ind[0], p2Ind[0], p3Ind[0]);
            imax = math::max(p1Ind[0], p2Ind[0], p3Ind[0]);
        }
        else {
            continue;
        }
    
        int jmin = 0;
        int jmax = div-1;
        if ( p1Ind[1]>=0 && p2Ind[1]>=0 && p3Ind[1]>=0 ) {
            jmin = math::min(p1Ind[1], p2Ind[1], p3Ind[1]);
            jmax = math::max(p1Ind[1], p2Ind[1], p3Ind[1]);
        }
        else {
            continue;
        }

        int kmin = 0;
        int kmax = div-1;
        if (p1Ind[2]>=0 && p2Ind[2]>=0 && p3Ind[2]>=0) {
            kmin = math::min(p1Ind[2], p2Ind[2], p3Ind[2]);
            kmax = math::max(p1Ind[2], p2Ind[2], p3Ind[2]);
        }
        else {
            continue;
        }

        // Plane equation.
        auto l1 = triangles[t][1] - triangles[t][0];
        auto l2 = triangles[t][2] - triangles[t][0];
        auto l3 = triangles[t][2] - triangles[t][1];

        auto n = crossProduct(l1,l2);
        n.normalize();
        double dd = -dotProduct(n, triangles[t][0]);

        // Planes that limit the triangle.
        auto n1 = crossProduct(l1, n);
        n1.normalize();
        double dd1 = -dotProduct(n1, triangles[t][1]);

        auto n2 = crossProduct(l2, n);
        n2.normalize();
        n2*=-1.0;
        double dd2 = -dotProduct(n2, triangles[t][2]);

        auto n3 = crossProduct(l3, n);
        n3.normalize();
        double dd3 = -dotProduct(n3, triangles[t][2]);

        // Threshold value for distances.
        double tf = 0;
        if (connectivity == NConnectivity3D::SixConnected) {
            RealVector ang(6);
            for (int i = 0; i<6; i++)
                ang[i] = angleBetweenVectors(n, ve[i]);
            tf = (lL/2.0)*std::cos(ang.min());
        }
        else if (connectivity == NConnectivity3D::TwentySixConnected) {
            RealVector ang(8);
            for (int i = 0; i<8; i++)
                ang[i] = angleBetweenVectors(n, vv[i]);
            tf = std::sqrt(3.0)*(lL/2.0)*std::cos(ang.min());
        }

        // Add voxels in the body.
        for (int i=imin; i<=imax; i++) {
            for (int j=jmin; j<=jmax; j++) {
                for (int k=kmin; k<=kmax; k++) {
                    Point3D center(xc[i], xc[j], xc[k]);

                    double dist = std::abs(dotProduct(center, n) + dd);

                    double dist1 = (dotProduct(center, n1) + dd1);
                    double dist2 = (dotProduct(center, n2) + dd2);
                    double dist3 = (dotProduct(center, n3) + dd3);

                    if ( (dist<=tf) && (dist1<0) && (dist2<0) && (dist3<0) )
                        voxels.modify(i, j, k, true);
                }
            }
        }
    }
    return voxels;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
