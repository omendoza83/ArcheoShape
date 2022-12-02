//=================================================================================================================
/**
 *  @file       Line.cpp
 *  @brief      nct::geometry::Line class implementation file.
 *  @details    This file contains the implementation of the nct::geometry::Line class.
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
#include <nct/geometry/Line.h>
#include <nct/math/math.h>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Line::Line(double p1x, double p1y, double p2x, double p2y) noexcept : 
    point1_{p1x, p1y}, point2_{p2x, p2y} {

}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Line::Line(const Point2D& p1, const Point2D& p2) noexcept : point1_{p1}, point2_{p2} 
{

}

//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::Point2D& nct::geometry::Line::operator[](size_t i) 
{
    if (i == 0)
        return point1_;
    else if (i == 1)
        return point2_;

    throw IndexOutOfRangeException("i", SOURCE_INFO);
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Point2D& nct::geometry::Line::operator[](size_t i) const 
{
    if (i == 0)
        return point1_;
    else if (i == 1)
        return point2_;

    throw IndexOutOfRangeException("i", SOURCE_INFO);
}

//-----------------------------------------------------------------------------------------------------------------
nct::Point2D nct::geometry::Line::operator()(double t) const noexcept 
{
    return (point2_ - point1_)*t + point1_;
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Line::setPoints(double p1x, double p1y, double p2x, double p2y) noexcept 
{
    point1_[0] = p1x;
    point1_[1] = p1y;
    point2_[0] = p2x;
    point2_[1] = p2y;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Line::setPoints(const Point2D& p1, const Point2D& p2) noexcept 
{
    point1_ = p1;
    point2_ = p2;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Point2D& nct::geometry::Line::point1() const noexcept 
{
    return point1_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Line::setPoint1(double x, double y) noexcept 
{
    point1_[0] = x;
    point1_[1] = y;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Line::setPoint1(const Point2D& p) noexcept 
{
    point1_ = p;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Point2D& nct::geometry::Line::point2() const noexcept 
{
    return point2_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Line::setPoint2(double x, double y) noexcept 
{
    point2_[0] = x;
    point2_[1] = y;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Line::setPoint2(const Point2D& p) noexcept 
{
    point2_ = p;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Vector2D<double> nct::geometry::Line::directionalVector() const 
{
    if (point1_ == point2_)
        throw ConfigurationException(exc_bad_line, SOURCE_INFO);
    return (point2_ - point1_).unitaryVector();
}

//-----------------------------------------------------------------------------------------------------------------
nct::Vector2D<double> nct::geometry::Line::normal() const 
{
    if (point1_ == point2_)
        throw ConfigurationException(exc_bad_line, SOURCE_INFO);
    auto r = directionalVector();
    return Point2D(r[1], -r[0]);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::Line::slope() const noexcept 
{
    return (point2_[1] - point1_[1]) / (point2_[0] - point1_[0]);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::Line::intercept() const noexcept 
{
    return point1_[1] - point1_[0]*(point2_[1] - point1_[1]) / (point2_[0] - point1_[0]);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::Line::lenght() const noexcept 
{
    return (point2_-point1_).magnitude();
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::Line::distance(const Point2D& p) const 
{
    if (point1_ == point2_)
        throw ConfigurationException(exc_bad_line, SOURCE_INFO);
    auto r = directionalVector();

    return std::abs(crossProduct(r, (p - point1_)));
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::Line::distance(const Line& l) const 
{
    if (point1_ == point2_)
        throw ConfigurationException(exc_bad_line, SOURCE_INFO);

    if (l.point1_ == l.point2_)
        throw ArgumentException("l", exc_bad_line, SOURCE_INFO);

    auto r1 = directionalVector();
    auto r2 = l.directionalVector();

    if (crossProduct(r1, r2) == 0)
        return std::abs(crossProduct(r1, (l.point1_ - point1_)));

    return 0.0;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Vector2D<double> nct::geometry::Line::d1(double) const noexcept 
{
    return (point2_ - point1_);
}

//-----------------------------------------------------------------------------------------------------------------
nct::Vector2D<double> nct::geometry::Line::tangent(double t) const noexcept 
{
    return d1(t).unitaryVector();
}

//-----------------------------------------------------------------------------------------------------------------
nct::Vector2D<double> nct::geometry::Line::normal(double t) const noexcept 
{
    auto tn = d1(t).unitaryVector();
    return Vector2D<double>(-tn.v2(), tn.v1());
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::Line::contains(const Point2D& p, double tol) const 
{
    tol = tol >= 0 ? tol : MEDIUM_TOL;
    return distance(p) <= tol;
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::Line::segmentContains(const Point2D& p, double tol) const 
{
    tol = tol >= 0 ? tol : MEDIUM_TOL;
    if (distance(p) > tol)
        return false;

    auto v = point2_ - point1_;
    double t = 0.0;
    if (v[0] != 0)
        t = (p[0] - point1_[0]) / v[0];
    else
        t = (p[1] - point1_[1]) / v[1];

    return (t >= 0) && (t <= 1);
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::Line::collidesWith(const Line& l, bool segment) const 
{
    if (point1_ == point2_)
        throw ConfigurationException(exc_bad_line, SOURCE_INFO);

    if (l.point1_ == l.point2_)
        throw ArgumentException("l", exc_bad_line, SOURCE_INFO);
    
    auto v1 = point2_ - point1_;
    auto v2 = l.point2_ - l.point1_;
    double d = v1[1] * v2[0] - v1[0] * v2[1];

    if (d == 0) {
        // Parallel lines, test if both are the same.
        auto test1 = v1[1] * (l.point1_[0] - point1_[0]);
        auto test2 = v1[0] * (l.point1_[1] - point1_[1]);
        return (test1 == test2);
    }
    
    ////////// Test line vs line //////////
    if (!segment)        
        return true;        

    ////////// Test line vs segment //////////
    double t2 = (v1[0] * (l.point1_[1] - point1_[1]) - v1[1] * (l.point1_[0] - point1_[0])) / d;
    return (t2 >= 0) && (t2 <= 1);
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::Line::segmentCollidesWith(const Line& l, bool segment) const 
{
    ////////// Test segment vs line //////////
    if (!segment)
        return l.collidesWith((*this), true);

    ////////// Test segment vs segment //////////
    if (point1_ == point2_)
        throw ConfigurationException(exc_bad_line, SOURCE_INFO);

    if (l.point1_ == l.point2_)
        throw ArgumentException("l", exc_bad_line, SOURCE_INFO);

    // Auxiliar functions.
    auto calct1 = [&](double t2, const Vector2D<double>& v1, const Vector2D<double>& v2)->double
    {
        double t1 = 0.0;
        if (v1[0] != 0)
            t1 = (v2[0] * t2 + l.point1_[0] - point1_[0]) / v1[0];
        else
            t1 = (v2[1] * t2 + l.point1_[1] - point1_[1]) / v1[1];
        return t1;
    };

    auto calct2 = [&](double t1, const Vector2D<double>& v1, const Vector2D<double>& v2)->double
    {
        double t2 = 0.0;
        if (v2[0] != 0)
            t2 = (v1[0] * t1 + point1_[0] - l.point1_[0]) / v2[0];
        else
            t2 = (v1[1] * t1 + point1_[1] - l.point1_[1]) / v2[1];
        return t2;
    };

    // Directional vectors and determinant of linear system.
    auto v1 = point2_ - point1_;
    auto v2 = l.point2_ - l.point1_;
    double d = v1[1] * v2[0] - v1[0] * v2[1];
    
    if (d == 0) {
        // Parallel directional vectors.

        auto test1 = v1[1] * (l.point1_[0] - point1_[0]);
        auto test2 = v1[0] * (l.point1_[1] - point1_[1]);
        if (test1 != test2)
            return false;    // Parallel lines.

        // Test if one of the exteme points of l1 are included in l2.
        auto t = calct2(0.0, v1, v2);
        if ((t >= 0) && (t <= 1))
            return true;

        t = calct2(1.0, v1, v2);
        if ((t >= 0) && (t <= 1))
            return true;

        // Test if one of the exteme points of l2 are included in l1.
        t = calct1(0.0, v1, v2);
        if ((t >= 0) && (t <= 1))
            return true;

        t = calct1(1.0, v1, v2);
        if ((t >= 0) && (t <= 1))
            return true;

        // The segments are disjoint.
        return false;
    }

    // Lines intercept in one point.
    auto t2 = (v1[0] * (l.point1_[1] - point1_[1]) - v1[1] * (l.point1_[0] - point1_[0])) / d;
    auto t1 = calct1(t2, v1, v2);    
    return ((t1 >= 0) && (t1 <= 1) && (t2 >= 0) && (t2 <= 1));
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::Line::collidesWith(const Rectangle& r, bool segment) const 
{
    // Test points of input line.
    if (segment) {
        if (r.contains(point1_))
            return true;

        if (r.contains(point2_))
            return true;
    }

    // Verify if the line collides with one of the edges.
    auto rp = r.vertices();
    for (unsigned int i = 0; i < 4; i++) {
        auto vi = i + 1;
        if (vi >= 4)
            vi = 0;

        auto lri = Line(rp[i], rp[vi]);
        if (segmentCollidesWith(lri, segment))
            return true;
    }

    return false;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::Point2D> nct::geometry::Line::samplePoints(size_t np) const 
{
    Array<Point2D> sp(np);
    auto r = point2_ - point1_;
    double dnp = math::max(np - 1., 1.);
    for (index_t i = 0; i < np; i++)
        sp[i] = r * (i / dnp) + point1_;

    return sp;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Line nct::geometry::Line::rotate(double theta) const 
{
    Line t;
    t.point1_ = AffineTransformation::rotate(point1_, theta);
    t.point2_ = AffineTransformation::rotate(point2_, theta);
    return t;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Line nct::geometry::Line::rotateAround(const Point2D& pv, double theta) const 
{
    Line t;
    t.point1_ = AffineTransformation::rotateAround(point1_, pv, theta);
    t.point2_ = AffineTransformation::rotateAround(point2_, pv, theta);
    return t;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Line nct::geometry::Line::translate(double dx, double dy) const 
{
    Line t;
    t.point1_ = AffineTransformation::translate(point1_, dx, dy);
    t.point2_ = AffineTransformation::translate(point2_, dx, dy);
    return t;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Line nct::geometry::Line::scale(double sx, double sy) const 
{
    Line t;
    t.point1_ = AffineTransformation::scale(point1_, sx, sy);
    t.point2_ = AffineTransformation::scale(point2_, sx, sy);
    return t;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Line nct::geometry::Line::skew(double alphax, double alphay) const 
{
    Line t;
    t.point1_ = AffineTransformation::skew(point1_, alphax, alphay);
    t.point2_ = AffineTransformation::skew(point2_, alphax, alphay);
    return t;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Line nct::geometry::Line::transform(const AffineTransformation& tm) const 
{
    Line t;
    t.point1_ = tm.transform(point1_);
    t.point2_ = tm.transform(point2_);
    return t;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Rectangle nct::geometry::Line::boundingRect() const 
{
    double xmin = math::min(point1_[0], point2_[0]);
    double xmax = math::max(point1_[0], point2_[0]);
    double ymin = math::min(point1_[1], point2_[1]);
    double ymax = math::max(point1_[1], point2_[1]);

    return Rectangle(xmin, ymin, xmax - xmin, ymax - ymin);
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
