//=================================================================================================================
/**
 *  @file       Line.h
 *  @brief      nct::geometry::Line class.
 *  @details    Declaration of the nct::geometry::Line class.
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

#ifndef NCT_LINE_H_INCLUDE
#define NCT_LINE_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/Array.h>
#include <nct/geometry/Rectangle.h>
#include <nct/geometry/AffineTransformation.h>

//=================================================================================================================
namespace nct {
namespace geometry {

/**
 *  @brief      Line class.
 *  @details    This class defines a line in the plane.
 */
class NCT_EXPIMP Line final {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the default configuration. 
     *              The line is initialized at the origin and its lenght is set to zero.
     */
    Line() noexcept = default;

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes a line using the specified points.
     *  @param[in]  p1x  x coordinate of the first point.
     *  @param[in]  p1y  y coordinate of the first point.
     *  @param[in]  p2x  x coordinate of the second point.
     *  @param[in]  p2y  y coordinate of the second point.
     */
    Line(double p1x, double p1y, double p2x, double p2y) noexcept;

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes a line using the specified points.
     *  @param[in]  p1  Point 1.
     *  @param[in]  p2  Point 2.
     */
    Line(const Point2D& p1, const Point2D& p2) noexcept;
    
    ////////// Operators //////////        
    
    /**
     *  @brief      Point.
     *  @details    This operator returns the specified point of the line.
     *  @param[in]  i  Point index (0 or 1).
     *  @returns    A reference to the point.
     */
    Point2D& operator[](size_t i);

    /**
     *  @brief      Point.
     *  @details    This operator returns the specified point of the line.
     *  @param[in]  i  Point index (0 or 1).
     *  @returns    A const reference to the point.
     */
    const Point2D& operator[](size_t i) const;

    /**
     *  @brief      Evaluate parametric function.
     *  @details    This operator evaluates the parametric function that defines the line.
     *  @param[in]  t  Parameter of the line function. Any value between 0 and 1 returns a point inside
     *              the segment. Values outside this range correspond to points outside the
     *              segment.
     *  @returns    The point that corresponds to the specified value of t.
     */
    Point2D operator()(double t) const noexcept;

    ////////// Member functions //////////

    /**
     *  @brief      Set line points.
     *  @details    This function modifies the points that define the line.
     *  @param[in]  p1x  x coordinate of the first point.
     *  @param[in]  p1y  y coordinate of the first point.
     *  @param[in]  p2x  x coordinate of the second point.
     *  @param[in]  p2y  y coordinate of the second point.
     */
    void setPoints(double p1x, double p1y, double p2x, double p2y) noexcept;

    /**
     *  @brief      Set line points.
     *  @details    This function modifies the points that define the line.
     *  @param[in]  p1  Point 1.
     *  @param[in]  p2  Point 2.
     */
    void setPoints(const Point2D& p1, const Point2D& p2) noexcept;

    /**
     *  @brief      Line point 1.
     *  @details    This function returns the first point that defines the line.
     *  @returns    The first line point.
     */
    const Point2D& point1() const noexcept;

    /**
     *  @brief      Set line point 1.
     *  @details    This function modifies the first point that defines the line.
     *  @param[in]  x  x coordinate of the new point.
     *  @param[in]  y  y coordinate of the new point.
     */
    void setPoint1(double x, double y) noexcept;

    /**
     *  @brief      Set line point 1.
     *  @details    This function modifies the first point that defines the line.
     *  @param[in]  p  The new point.
     */
    void setPoint1(const Point2D& p) noexcept;

    /**
     *  @brief      Line point 2.
     *  @details    This function returns the second point that defines the line.
     *  @returns    The second line point.
     */
    const Point2D& point2() const noexcept;

    /**
     *  @brief      Set line point 2.
     *  @details    This function modifies the second point that defines the line.
     *  @param[in]  x  x coordinate of the new point.
     *  @param[in]  y  y coordinate of the new point.
     */
    void setPoint2(double x, double y) noexcept;

    /**
     *  @brief      Set line point 2.
     *  @details    This function modifies the second point that defines the line.
     *  @param[in]  p  The new point.
     */
    void setPoint2(const Point2D& p) noexcept;

    /**
     *  @brief      Unitary vector.
     *  @details    This function returns a unitary in the direction of the line.
     *  @returns    An unitary vector parallel to the line.
     */
    Vector2D<double> directionalVector() const;

    /**
     *  @brief      Unitary normal vector.
     *  @details    This function returns a unitary perpendicular to the line.
     *  @returns    An unitary vector perpendicular to the line.
     */
    Vector2D<double> normal() const;

    /**
     *  @brief      Slope.
     *  @details    This function returns the slope of the line.
     *  @returns    The slope.
     */
    double slope() const noexcept;

    /**
     *  @brief      Intercept.
     *  @details    This function returns the intercept of the line.
     *  @returns    The intercept.
     */
    double intercept() const noexcept;

    /**
     *  @brief      Segment lenght.
     *  @details    This function returns the lenght of the segment limited by the two points that
     *              define the line.
     *  @returns    The segment lenght.
     */
    double lenght() const noexcept;

    /**
     *  @brief      Distance to a point.
     *  @details    This function returns the distance to the specified point.
     *  @oaram[in] p    Point.
     *  @returns    The distance to the specified point.
     */
    double distance(const Point2D& p) const;

    /**
     *  @brief      Distance to a line.
     *  @details    This function returns the distance to the specified line.
     *  @oaram[in] l    Line.
     *  @returns    The distance to the specified point.
     */
    double distance(const Line& p) const;

    /**
     *  @brief      Evaluate the first derivatives of the parametric function.
     *  @details    This operator evaluates the first derivatives of the parametric function that
     *              defines the bezier curve.
     *  @param[in]  t  The parameter of the function.
     *  @returns    The vector with the derivatives. 
     */
    Vector2D<double> d1(double t) const noexcept;

    /**
     *  @brief      Tangent vector.
     *  @details    This operator finds the tangent vector at the specified point.
     *  @param[in]  t  The point to be evaluated.
     *  @returns    The tangent vector.
     */
    Vector2D<double> tangent(double t) const noexcept;

    /**
     *  @brief      Normal vector.
     *  @details    This operator finds the normal vector at the specified point.
     *  @param[in]  t  The point to be evaluated.
     *  @returns    The normal vector.
     */
    Vector2D<double> normal(double t) const noexcept;

    /**
     *  @brief      Contains point?
     *  @details    This function tests whether the object contains the specified point.
     *  @param[in]  p  Point to test.
     *  @param[in]  tol  Tolerance that is used to accept the point.
     *  @returns    True, if the point is contained by the object.
     */
    bool contains(const Point2D& p, double tol = MEDIUM_TOL) const;

    /**
     *  @brief      Segment contains point?
     *  @details    This function tests whether the segment contains the specified point.
     *  @param[in]  p  Point to test.
     *  @param[in]  tol  Tolerance that is used to accept the point.
     *  @returns    True, if the point is contained by the object.
     */
    bool segmentContains(const Point2D& p, double tol = MEDIUM_TOL) const;

    /**
     *  @brief      Collides with?
     *  @details    This function determines whether the line collides with another line or segment.
     *  @param[in]  l  Line to test.
     *  @param[in]  segment  True indicates that the input object is a segment instead of
     *              an infinite line.
     *  @returns    True, if the line collides with the specified object.
     */
    bool collidesWith(const Line& l, bool segment) const;

    /**
     *  @brief      Collides segment with?
     *  @details    This function determines whether the segment collides with another line or
     *              segment. in this function the segment limited by the two points that define the line
     *              is tested instead of the infinite line.
     *  @param[in]  l  Line to test.
     *  @param[in]  segment  True indicates that the segments are tested instead of the complete infinite
     *              lines.
     *  @returns    True, if the line collides with the specified object.
     */
    bool segmentCollidesWith(const Line& l, bool segment) const;

    /**
     *  @brief      Collides with rectangle?
     *  @details    This function tests whether the line collides with a rectangle.
     *  @param[in]  r  Rectangle to test.
     *  @returns    True, if the line collides.
     */
    bool collidesWith(const Rectangle& r, bool segment) const;

    /**
     *  @brief      Sample points.
     *  @details    This function returns an array of points that are on the line between the
     *              two points that define the object.
     *  @param[in]  np  Total number of points that will be computed.
     *  @returns    An array with the sampled points.
     */
    Array<Point2D> samplePoints(size_t np) const;

    /**
     *  @brief      Rotate object.
     *  @details    This function returns a rotated version of the object. The
     *              rotation is done around the origin.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    The rotated object.
     */
    Line rotate(double theta) const;

    /**
     *  @brief      Rotate object around a point.
     *  @details    This function returns a rotated version of the object. The
     *              rotation is done around a point.
     *  @param[in]  pv  Pivot point.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    The transformed object.
     */
    Line rotateAround(const Point2D& pv, double theta) const;

    /**
     *  @brief      Traslate object.
     *  @details    This function returns a translated version of the object. 
     *  @param[in]  dx  Translation of the first coordinate.
     *  @param[in]  dy  Translation of the second coordinate.
     *  @returns    The transformed object.
     */
    Line translate(double dx, double dy) const;

    /**
     *  @brief      Scale object.
     *  @details    This function returns a scaled version of the object. 
     *  @param[in]  sx  Scale factor of the first coordinate.
     *  @param[in]  sy  Scale factor of the second coordinate.
     *  @returns    The transformed object.
     */
    Line scale(double sx, double sy) const;

    /**
     *  @brief      Skew object.
     *  @details    This function returns a skewed version of the object. 
     *  @param[in]  alphax  Angle in radians by which the vector is skewed along the x-axis.
     *  @param[in]  alphay  Angle in radians by which the vector is skewed along the y-axis.
     *  @returns    The transformed object.
     */
    Line skew(double alphax, double alphay) const;

    /**
     *  @brief      Transform object.
     *  @details    This function returns a transformed version of the object. 
     *  @param[in]  tm  Transformation object.
     *  @returns    The transformed object.
     */
    Line transform(const AffineTransformation& tm) const;

    /**
     *  @brief      Bounding rectangle.
     *  @details    This function returns the bounding rectangle of the shape.
     *  @returns    The bounding rectangle.
     */
    Rectangle boundingRect() const;

protected:

    ////////// Data members //////////

    Point2D point1_;    /**< Point 1. */

    Point2D point2_;    /**< Point 2. */
};

}}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
