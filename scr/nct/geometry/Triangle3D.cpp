//=================================================================================================================
/**
 *  @file       Triangle3D.cpp
 *  @brief      nct::geometry::Triangle3D class implementation file.
 *  @details    This file contains the implementation of the nct::geometry::Triangle3D class.
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
#include <nct/geometry/Triangle3D.h>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Triangle3D::Triangle3D(const Point3D& p1, const Point3D& p2, const Point3D& p3) noexcept :
    v1_{p1}, v2_{p2}, v3_{p3}
{

}

//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::Point3D& nct::geometry::Triangle3D::operator[](size_t i) 
{
    if (i == 0)
        return v1_;
    else if (i == 1)
        return v2_;
    else if (i == 2)
        return v3_;

    throw IndexOutOfRangeException("i", SOURCE_INFO);
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Point3D& nct::geometry::Triangle3D::operator[](size_t i) const 
{
    if (i == 0)
        return v1_;
    else if (i == 1)
        return v2_;
    else if (i == 2)
        return v3_;

    throw IndexOutOfRangeException("i", SOURCE_INFO);
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Triangle3D::setVertices(const Point3D& p1, const Point3D& p2, const Point3D& p3) noexcept 
{
    v1_ = p1;
    v2_ = p2;
    v3_ = p3;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Point3D& nct::geometry::Triangle3D::vertex1() const noexcept 
{
    return v1_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Triangle3D::setVertex1(double x, double y, double z) noexcept 
{
    v1_[0] = x;
    v1_[1] = y;
    v1_[2] = z;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Triangle3D::setVertex1(const Point3D& p) noexcept 
{
    v1_ = p;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Point3D& nct::geometry::Triangle3D::vertex2() const noexcept 
{
    return v2_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Triangle3D::setVertex2(double x, double y, double z) noexcept 
{
    v2_[0] = x;
    v2_[1] = y;
    v2_[2] = z;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Triangle3D::setVertex2(const Point3D& p) noexcept 
{
    v2_ = p;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Point3D& nct::geometry::Triangle3D::vertex3() const noexcept 
{
    return v3_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Triangle3D::setVertex3(double x, double y, double z) noexcept 
{
    v3_[0] = x;
    v3_[1] = y;
    v3_[2] = z;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Triangle3D::setVertex3(const Point3D& p) noexcept 
{
    v3_ = p;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::Triangle3D::perimeter() const noexcept 
{
    return (v1_ - v2_).magnitude() + (v1_ - v3_).magnitude() + (v2_ - v3_).magnitude();;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::Triangle3D::area() const noexcept 
{
    return 0.5*(crossProduct(v2_ - v1_, v3_ - v1_).magnitude());
}

//-----------------------------------------------------------------------------------------------------------------
nct::Point3D nct::geometry::Triangle3D::center() const noexcept 
{
    return (v1_ + v2_ + v3_) / 3.0;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Vector3D<double> nct::geometry::Triangle3D::normal() const 
{    
    return crossProduct(v2_ - v1_, v3_ - v1_).unitaryVector();
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Plane nct::geometry::Triangle3D::plane() const 
{
    return Plane(v1_, v2_, v3_);
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::Point3D> nct::geometry::Triangle3D::vertices() const 
{
    return Array<Point3D>({ v1_, v2_, v3_ });
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::geometry::Line3D> nct::geometry::Triangle3D::lines() const 
{
    return Array<Line3D>({ Line3D(v1_, v2_), Line3D(v2_, v3_), Line3D(v3_, v1_) });
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Triangle3D nct::geometry::Triangle3D::rotate(
    const Vector3D<double>& w, double theta) const
{
    Triangle3D triangle;
    triangle.v1_ = AffineTransformation3D::rotate(v1_, w, theta);
    triangle.v2_ = AffineTransformation3D::rotate(v2_, w, theta);
    triangle.v3_ = AffineTransformation3D::rotate(v3_, w, theta);
    return triangle;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Triangle3D nct::geometry::Triangle3D::translate(double dx, double dy, double dz) const 
{
    Triangle3D triangle;
    triangle.v1_ = AffineTransformation3D::translate(v1_, dx, dy, dz);
    triangle.v2_ = AffineTransformation3D::translate(v2_, dx, dy, dz);
    triangle.v3_ = AffineTransformation3D::translate(v3_, dx, dy, dz);
    return triangle;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Triangle3D nct::geometry::Triangle3D::scale(double sx, double sy, double sz) const 
{
    Triangle3D triangle;
    triangle.v1_ = AffineTransformation3D::scale(v1_, sx, sy, sz);
    triangle.v2_ = AffineTransformation3D::scale(v2_, sx, sy, sz);
    triangle.v3_ = AffineTransformation3D::scale(v3_, sx, sy, sz);
    return triangle;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Triangle3D nct::geometry::Triangle3D::transform(const AffineTransformation3D& tm) const 
{
    Triangle3D triangle;
    triangle.v1_ = tm.transform(v1_);
    triangle.v2_ = tm.transform(v2_);
    triangle.v3_ = tm.transform(v3_);
    return triangle;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
