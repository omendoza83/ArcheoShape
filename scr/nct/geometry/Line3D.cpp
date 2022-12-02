//=================================================================================================================
/**
 *  @file       Line3D.cpp
 *  @brief      nct::geometry::Line3D class implementation file.
 *  @details    This file contains the implementation of the nct::geometry::Line3D class.
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
#include <nct/geometry/Line3D.h>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Line3D::Line3D(double p1x, double p1y, double p1z, double p2x, double p2y, double p2z) noexcept :
    point1_{p1x, p1y, p1z}, point2_{p2x, p2y, p2z}
{

}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Line3D::Line3D(const Point3D& p1, const Point3D& p2) noexcept : point1_{p1}, point2_{p2} 
{

}

//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::Point3D& nct::geometry::Line3D::operator[](size_t i) 
{
    if (i == 0)
        return point1_;
    else if (i == 1)
        return point2_;

    throw IndexOutOfRangeException("i", SOURCE_INFO);
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Point3D& nct::geometry::Line3D::operator[](size_t i) const 
{
    if (i == 0)
        return point1_;
    else if (i == 1)
        return point2_;

    throw IndexOutOfRangeException("i", SOURCE_INFO);
}

//-----------------------------------------------------------------------------------------------------------------
nct::Point3D nct::geometry::Line3D::operator()(double t) const noexcept 
{
    return (point2_ - point1_)*t + point1_;
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Line3D::setPoints(double p1x, double p1y, double p1z, 
    double p2x, double p2y, double p2z) noexcept 
{
    point1_[0] = p1x;
    point1_[1] = p1y;
    point1_[2] = p1z;
    point2_[0] = p2x;
    point2_[1] = p2y;
    point2_[2] = p2z;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Line3D::setPoints(const Point3D& p1, const Point3D& p2) noexcept 
{
    point1_ = p1;
    point2_ = p2;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Point3D& nct::geometry::Line3D::point1() const noexcept 
{
    return point1_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Line3D::setPoint1(double x, double y, double z) noexcept 
{
    point1_[0] = x;
    point1_[1] = y;
    point1_[2] = z;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Line3D::setPoint1(const Point3D& p) noexcept 
{
    point1_ = p;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Point3D& nct::geometry::Line3D::point2() const noexcept 
{
    return point2_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Line3D::setPoint2(double x, double y, double z) noexcept 
{
    point2_[0] = x;
    point2_[1] = y;
    point2_[2] = z;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Line3D::setPoint2(const Point3D& p) noexcept 
{
    point2_ = p;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Vector3D<double> nct::geometry::Line3D::directionalVector() const 
{
    if (point1_ == point2_)
        throw ConfigurationException(exc_bad_line, SOURCE_INFO);
    return (point2_ - point1_).unitaryVector();
}


//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::Line3D::lenght() const noexcept 
{
    return (point2_ - point1_).magnitude();
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::Line3D::distance(const Point3D& p) const 
{
    if (point1_ == point2_)
        throw ConfigurationException(exc_bad_line, SOURCE_INFO);
    auto r = directionalVector();

    return crossProduct(r, (p - point1_)).magnitude();
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::Line3D::distance(const Line3D& l) const 
{
    if (point1_ == point2_)
        throw ConfigurationException(exc_bad_line, SOURCE_INFO);

    if (l.point1_ == l.point2_)
        throw ArgumentException("l", exc_bad_line, SOURCE_INFO);

    auto r1 = directionalVector();
    auto r2 = l.directionalVector();

    auto norm = crossProduct(r1, r2);
    auto nomrm = norm.sqrMagnitude();
    if (nomrm == 0)
        return distance(l.point1_);


    return std::abs(dotProduct(norm, point1_ - l.point1_) / nomrm);
}

//-----------------------------------------------------------------------------------------------------------------
nct::Vector3D<double> nct::geometry::Line3D::d1(double) const noexcept 
{
    return (point2_ - point1_);
}

//-----------------------------------------------------------------------------------------------------------------
nct::Vector3D<double> nct::geometry::Line3D::tangent(double t) const noexcept 
{
    return d1(t).unitaryVector();
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::Line3D::contains(const Point3D& p, double tol) const 
{
    tol = tol >= 0 ? tol : MEDIUM_TOL;
    return distance(p) <= tol;
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::Line3D::collidesWith(const Line3D& l, double tol) const 
{
    tol = tol >= 0 ? tol : MEDIUM_TOL;
    return distance(l) <= tol;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::Point3D> nct::geometry::Line3D::samplePoints(size_t np) const 
{
    Array<Point3D> sp(np);
    auto r = point2_ - point1_;
    double dnp = np - 1.;
    if (dnp < 1)
        dnp = 1.0;

    for (index_t i = 0; i < np; i++)        
        sp[i] = r * (i/dnp) + point1_;

    return sp;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Line3D nct::geometry::Line3D::rotate(const Vector3D<double>& w, double theta) const 
{
    Line3D t;
    t.point1_ = AffineTransformation3D::rotate(point1_, w, theta);
    t.point2_ = AffineTransformation3D::rotate(point2_, w, theta);
    return t;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Line3D nct::geometry::Line3D::translate(double dx, double dy, double dz) const 
{
    Line3D t;
    t.point1_ = AffineTransformation3D::translate(point1_, dx, dy, dz);
    t.point2_ = AffineTransformation3D::translate(point2_, dx, dy, dz);
    return t;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Line3D nct::geometry::Line3D::scale(double sx, double sy, double sz) const 
{
    Line3D t;
    t.point1_ = AffineTransformation3D::scale(point1_, sx, sy, sz);
    t.point2_ = AffineTransformation3D::scale(point2_, sx, sy, sz);
    return t;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Line3D nct::geometry::Line3D::transform(const AffineTransformation3D& tm) const 
{
    Line3D t;
    t.point1_ = tm.transform(point1_);
    t.point2_ = tm.transform(point2_);
    return t;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
