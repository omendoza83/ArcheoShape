//=================================================================================================================
/**
 *  @file       Plane.cpp
 *  @brief      nct::geometry::Plane class implementation file.
 *  @details    This file contains the implementation of the nct::geometry::Plane class.
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
#include <nct/geometry/Plane.h>
#include <nct/math/math.h>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Plane::Plane(const Point3D& p1, const Point3D& p2, const Point3D& p3) : 
    point1_{p1}, point2_{p2}, point3_{p3}
{
    auto v1 = point2_ - point1_;
    auto v2 = point3_ - point1_;
    axis1_ = v1.unitaryVector();
    axis2_ = (v2 - projection(v2, v1)).unitaryVector();
    axis3_ = crossProduct(v1, v2).unitaryVector();
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Plane::Plane(const Point3D& p, const Vector3D<double>& n) 
{
    auto nn = n.unitaryVector();
    
    auto c = 1 - nn[3];
    auto s2 = nn[0]* nn[0] + nn[1]* nn[1];
    auto d = c / s2;

    if (s2 > 0) {
        AffineTransformation3D tr(
            1 - d * nn[0] * nn[0], -d * nn[0] * nn[1], nn[0], p[0],
            -d * nn[0] * nn[1], 1 - d * nn[1] * nn[1], nn[1], p[1],
            -nn[0], -nn[1], nn[2], p[2]);

        point1_ = p;
        point2_ = tr.transform(Point3D(1, 0, 0));
        point3_ = tr.transform(Point3D(0, 1, 0));
    }
    else {
        point1_ = p;
        point2_ = p + Point3D(-1, 0, 0);
        point3_ = p + Point3D(0, 1, 0);
    }

    auto v1 = point2_ - point1_;
    auto v2 = point3_ - point1_;
    axis1_ = v1.unitaryVector();
    axis2_ = (v2 - projection(v2, v1)).unitaryVector();
    axis3_ = crossProduct(v1, v2).unitaryVector();
}

//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::Point3D& nct::geometry::Plane::operator[](size_t i) 
{
    if (i == 0)
        return point1_;
    else if (i == 1)
        return point2_;
    else if (i == 2)
        return point3_;

    throw IndexOutOfRangeException("i", SOURCE_INFO);
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Point3D& nct::geometry::Plane::operator[](size_t i) const 
{
    if (i == 0)
        return point1_;
    else if (i == 1)
        return point2_;
    else if (i == 2)
        return point3_;

    throw IndexOutOfRangeException("i", SOURCE_INFO);
}

//-----------------------------------------------------------------------------------------------------------------
nct::Point3D nct::geometry::Plane::operator()(double s, double t) const noexcept 
{
    return point1_ + s*axis1_ + t*axis2_;
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Plane::setPoints(const Point3D& p1, const Point3D& p2, const Point3D& p3) 
{
    point1_ = p1;
    point2_ = p2;
    point3_ = p3;

    auto v1 = point2_ - point1_;
    auto v2 = point3_ - point1_;
    axis1_ = v1.unitaryVector();
    axis2_ = (v2 - projection(v2, v1)).unitaryVector();
    axis3_ = crossProduct(v1, v2).unitaryVector();
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Point3D& nct::geometry::Plane::point1() const noexcept 
{
    return point1_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Plane::setPoint1(double x, double y, double z) 
{
    point1_[0] = x;
    point1_[1] = y;
    point1_[2] = z;

    auto v1 = point2_ - point1_;
    auto v2 = point3_ - point1_;
    axis1_ = v1.unitaryVector();
    axis2_ = (v2 - projection(v2, v1)).unitaryVector();
    axis3_ = crossProduct(v1, v2).unitaryVector();
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Plane::setPoint1(const Point3D& p) 
{
    point1_ = p;

    auto v1 = point2_ - point1_;
    auto v2 = point3_ - point1_;
    axis1_ = v1.unitaryVector();
    axis2_ = (v2 - projection(v2, v1)).unitaryVector();
    axis3_ = crossProduct(v1, v2).unitaryVector();
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Point3D& nct::geometry::Plane::point2() const noexcept 
{
    return point2_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Plane::setPoint2(double x, double y, double z) 
{
    point2_[0] = x;
    point2_[1] = y;
    point2_[2] = z;

    auto v1 = point2_ - point1_;
    auto v2 = point3_ - point1_;
    axis1_ = v1.unitaryVector();
    axis2_ = (v2 - projection(v2, v1)).unitaryVector();
    axis3_ = crossProduct(v1, v2).unitaryVector();
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Plane::setPoint2(const Point3D& p) 
{
    point2_ = p;

    auto v1 = point2_ - point1_;
    auto v2 = point3_ - point1_;
    axis1_ = v1.unitaryVector();
    axis2_ = (v2 - projection(v2, v1)).unitaryVector();
    axis3_ = crossProduct(v1, v2).unitaryVector();
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Point3D& nct::geometry::Plane::point3() const noexcept 
{
    return point3_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Plane::setPoint3(double x, double y, double z) 
{
    point3_[0] = x;
    point3_[1] = y;
    point3_[2] = z;

    auto v1 = point2_ - point1_;
    auto v2 = point3_ - point1_;
    axis1_ = v1.unitaryVector();
    axis2_ = (v2 - projection(v2, v1)).unitaryVector();
    axis3_ = crossProduct(v1, v2).unitaryVector();
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Plane::setPoint3(const Point3D& p) 
{
    point3_ = p;

    auto v1 = point2_ - point1_;
    auto v2 = point3_ - point1_;
    axis1_ = v1.unitaryVector();
    axis2_ = (v2 - projection(v2, v1)).unitaryVector();
    axis3_ = crossProduct(v1, v2).unitaryVector();
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Vector3D<double>& nct::geometry::Plane::normal() const noexcept 
{    
    return axis3_;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Vector3D<double>& nct::geometry::Plane::axis1() const noexcept 
{
    return axis1_;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Vector3D<double>& nct::geometry::Plane::axis2() const noexcept 
{
    return axis2_;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Vector3D<double>& nct::geometry::Plane::axis3() const noexcept 
{
    return axis3_;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::Plane::distance(const Point3D& p) const 
{
    auto n = normal();
    auto d = -(n[0] * point1_[0] + n[1] * point1_[1] + n[2] * point1_[2]);
    return std::abs(n[0] * p[0] + n[1] * p[1] + n[2] * p[2] + d);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::Plane::distance(const Line3D& l) const 
{
    if (l.point1() == l.point2())
        throw ConfigurationException(exc_bad_line, SOURCE_INFO);

    auto n = normal();
    auto lv = l.point2() - l.point1();

    if (dotProduct(n, lv) == 0) {
        auto d = -(n[0] * point1_[0] + n[1] * point1_[1] + n[2] * point1_[2]);
        auto d1 = std::abs(n[0] * l.point1()[0] + n[1] * l.point1()[1] + n[2] * l.point1()[2] + d);
        auto d2 = std::abs(n[0] * l.point2()[0] + n[1] * l.point2()[1] + n[2] * l.point2()[2] + d);
        return (d1 + d2) * 0.5;
    }

    return 0.0;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::Plane::distance(const Plane& plane) const 
{
    auto n1 = normal();
    auto n2 = plane.normal();
    
    if (crossProduct(n1, n2).sqrMagnitude() == 0) {
        auto n = normal();
        auto d = -(n[0] * point1_[0] + n[1] * point1_[1] + n[2] * point1_[2]);
        auto d1 = std::abs(n[0] * plane.point1_[0] + 
            n[1] * plane.point1_[1] + n[2] * plane.point1_[2] + d);
        auto d2 = std::abs(n[0] * plane.point2_[0] +
            n[1] * plane.point2_[1] + n[2] * plane.point2_[2] + d);
        auto d3 = std::abs(n[0] * plane.point3_[0] +
            n[1] * plane.point3_[1] + n[2] * plane.point3_[2] + d);
        return (d1 + d2 + d3) / 3.0;
    }

    return 0.0;
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::Plane::contains(const Point3D& point, double tol) const 
{
    tol = tol >= 0 ? tol : MEDIUM_TOL;
    return distance(point) <= tol;
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::Plane::contains(const Line3D& l, double tol) const 
{
    auto n = normal();
    auto lv = l.point2() - l.point1();

    if (dotProduct(n, lv) == 0) {
        auto d = -(n[0] * point1_[0] + n[1] * point1_[1] + n[2] * point1_[2]);
        auto d1 = std::abs(n[0] * l.point1()[0] + n[1] * l.point1()[1] + n[2] * l.point1()[2] + d);
        auto d2 = std::abs(n[0] * l.point2()[0] + n[1] * l.point2()[1] + n[2] * l.point2()[2] + d);
        auto dt = (d1 + d2) * 0.5;

        tol = tol >= 0 ? tol : MEDIUM_TOL;
        return dt <= tol;
    }

    return false;
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::Plane::collidesWith(const Line3D& line, double tol) const 
{
    tol = tol >= 0 ? tol : MEDIUM_TOL;
    return distance(line) <= tol;
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::Plane::collidesWith(const Plane& plane, double tol) const 
{
    tol = tol >= 0 ? tol : MEDIUM_TOL;
    return distance(plane) <= tol;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array2D<nct::Point3D> nct::geometry::Plane::rectangularGrid(double mins, double maxs,
    double mint, double maxt, size_t ns, size_t nt) const
{
    Array2D<Point3D> grid(ns, nt);

    double dns = math::max(ns - 1., 1.0);
    double dnt = math::max(nt - 1., 1.0);    

    for (index_t i = 0; i < ns; i++) {
        auto s = mins + (maxs - mins) *(i / dns);
        for (index_t j = 0; j < nt; j++) {            
            auto t = mint + (maxt - mint) *(j / dnt);
            grid(i, j) = (*this)(s, t);
        }
    }

    return grid;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Plane nct::geometry::Plane::rotate(const Vector3D<double>& w, double theta) const 
{
    Plane plane;
    plane.point1_ = AffineTransformation3D::rotate(point1_, w, theta);
    plane.point2_ = AffineTransformation3D::rotate(point2_, w, theta);
    plane.point3_ = AffineTransformation3D::rotate(point3_, w, theta);
    return plane;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Plane nct::geometry::Plane::translate(double dx, double dy, double dz) const 
{
    Plane plane;
    plane.point1_ = AffineTransformation3D::translate(point1_, dx, dy, dz);
    plane.point2_ = AffineTransformation3D::translate(point2_, dx, dy, dz);
    plane.point3_ = AffineTransformation3D::translate(point3_, dx, dy, dz);
    return plane;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Plane nct::geometry::Plane::scale(double sx, double sy, double sz) const 
{
    Plane plane;
    plane.point1_ = AffineTransformation3D::scale(point1_, sx, sy, sz);
    plane.point2_ = AffineTransformation3D::scale(point2_, sx, sy, sz);
    plane.point3_ = AffineTransformation3D::scale(point3_, sx, sy, sz);
    return plane;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Plane nct::geometry::Plane::transform(const AffineTransformation3D& tm) const 
{
    Plane plane;
    plane.point1_ = tm.transform(point1_);
    plane.point2_ = tm.transform(point2_);
    plane.point3_ = tm.transform(point3_);
    return plane;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
