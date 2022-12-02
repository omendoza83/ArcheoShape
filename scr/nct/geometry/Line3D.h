//=================================================================================================================
/**
 *  @file       Line3D.h
 *  @brief      nct::geometry::Line3D class.
 *  @details    Declaration of the nct::geometry::Line3D class.
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

#ifndef NCT_LINE_3D_H_INCLUDE
#define NCT_LINE_3D_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/Array.h>
#include <nct/geometry/AffineTransformation3D.h>

//=================================================================================================================
namespace nct {
namespace geometry {

/**
 *  @brief      Line3D class.
 *  @details    This class defines a line in the space.
 */
class NCT_EXPIMP Line3D final {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the default configuration. 
     *              The line is initialized at the origin and its lenght is set to zero.
     */
    Line3D() noexcept = default;

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes a line using the specified points.
     *  @param[in]  p1x  x coordinate of the first point.
     *  @param[in]  p1y  y coordinate of the first point.
     *  @param[in]  p1z  z coordinate of the first point.
     *  @param[in]  p2x  x coordinate of the second point.
     *  @param[in]  p2y  y coordinate of the second point.
     *  @param[in]  p2z  z coordinate of the second point.
     */
    Line3D(double p1x, double p1y, double p1z, double p2x, double p2y, double p2z) noexcept;

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes a line using the specified points.
     *  @param[in]  p1  Point 1.
     *  @param[in]  p2  Point 2.
     */
    Line3D(const Point3D& p1, const Point3D& p2) noexcept;
    
    ////////// Operators //////////        

    /**
     *  @brief      Point.
     *  @details    This operator returns the specified point of the line.
     *  @param[in]  i  Point index (0 or 1).
     *  @returns    A reference to the point.
     */
    Point3D& operator[](size_t i);

    /**
     *  @brief      Point.
     *  @details    This operator returns the specified point of the line.
     *  @param[in]  i  Point index (0 or 1).
     *  @returns    A const reference to the point.
     */
    const Point3D& operator[](size_t i) const;

    /**
     *  @brief      Evaluate parametric function.
     *  @details    This operator evaluates the parametric function that defines the line.
     *  @param[in]  t  Parameter of the line function. Any value between 0 and 1 returns a point inside
     *              the segment. Values outside this range correspond to points outside the
     *              segment.
     *  @returns    The point that corresponds to the specified value of t.
     */
    Point3D operator()(double t) const noexcept;

    ////////// Member functions //////////

    /**
     *  @brief      Set line points.
     *  @details    This function modifies the points that define the line.
     *  @param[in]  p1x  x coordinate of the first point.
     *  @param[in]  p1y  y coordinate of the first point.
     *  @param[in]  p1z  z coordinate of the first point.
     *  @param[in]  p2x  x coordinate of the second point.
     *  @param[in]  p2y  y coordinate of the second point.
     *  @param[in]  p2z  z coordinate of the second point.
     */
    void setPoints(double p1x, double p1y, double p1z, double p2x, double p2y, double p2z) noexcept;

    /**
     *  @brief      Set line points.
     *  @details    This function modifies the points that define the line.
     *  @param[in]  p1  Point 1.
     *  @param[in]  p2  Point 2.
     */
    void setPoints(const Point3D& p1, const Point3D& p2) noexcept;

    /**
     *  @brief      Line point 1.
     *  @details    This function returns the first point that defines the line.
     *  @returns    The first line point.
     */
    const Point3D& point1() const noexcept;

    /**
     *  @brief      Set line point 1.
     *  @details    This function modifies the first point that defines the line.
     *  @param[in]  x  x coordinate of the new point.
     *  @param[in]  y  y coordinate of the new point.
     *  @param[in]  z  z coordinate of the new point.
     */
    void setPoint1(double x, double y, double z) noexcept;

    /**
     *  @brief      Set line point 1.
     *  @details    This function modifies the first point that defines the line.
     *  @param[in]  p  The new point.
     */
    void setPoint1(const Point3D& p) noexcept;

    /**
     *  @brief      Line point 2.
     *  @details    This function returns the second point that defines the line.
     *  @returns    The second line point.
     */
    const Point3D& point2() const noexcept;

    /**
     *  @brief      Set line point 2.
     *  @details    This function modifies the second point that defines the line.
     *  @param[in]  x  x coordinate of the new point.
     *  @param[in]  y  y coordinate of the new point.
     *  @param[in]  z  z coordinate of the new point.
     */
    void setPoint2(double x, double y, double z) noexcept;

    /**
     *  @brief      Set line point 2.
     *  @details    This function modifies the second point that defines the line.
     *  @param[in]  p  The new point.
     */
    void setPoint2(const Point3D& p) noexcept;

    /**
     *  @brief      Unitary vector.
     *  @details    This function returns a unitary in the direction of the line.
     *  @returns    An unitary vector parallel to the line.
     */
    Vector3D<double> directionalVector() const;

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
    double distance(const Point3D& p) const;

    /**
     *  @brief      Distance to a line.
     *  @details    This function returns the distance to the specified line.
     *  @oaram[in] l    Line.
     *  @returns    The distance to the specified line.
     */
    double distance(const Line3D& l) const;

    /**
     *  @brief      Evaluate the first derivatives of the parametric function.
     *  @details    This operator evaluates the first derivatives of the parametric function that
     *              defines the bezier curve.
     *  @param[in]  t  The parameter of the function.
     *  @returns    The vector with the derivatives. 
     */
    Vector3D<double> d1(double t) const noexcept;

    /**
     *  @brief      Tangent vector.
     *  @details    This operator finds the tangent vector at the specified point.
     *  @param[in]  t  The point to be evaluated.
     *  @returns    The tangent vector.
     */
    Vector3D<double> tangent(double t) const noexcept;

    /**
     *  @brief      Contains point?
     *  @details    This function tests whether the object contains the specified point.
     *  @param[in]  p  Point to test.
     *  @param[in]  tol  Tolerance that is used to accept the point.
     *  @returns    True, if the point is contained by the object.
     */
    bool contains(const Point3D& p, double tol = MEDIUM_TOL) const;

    /**
     *  @brief      Collides width?
     *  @details    This function tests whether the object collides with the specified line.
     *  @param[in]  l  Line to test.
     *  @param[in]  tol  Tolerance that is used to accept the point.
     *  @returns    True, if the line collides with the object.
     */
    bool collidesWith(const Line3D& l, double tol = MEDIUM_TOL) const;

    /**
     *  @brief      Sample points.
     *  @details    This function returns an array of points that are on the line between the
     *              two points that define the object.
     *  @param[in]  np  Total number of points that will be computed.
     *  @returns    An array with the sampled points.
     */
    Array<Point3D> samplePoints(size_t np) const;

    /**
     *  @brief      Rotate object.
     *  @details    This function returns a rotated version of the object. The
     *              rotation is done around the origin.
     *  @param[in]  w  Rotation axis.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    The rotated object.
     */
    Line3D rotate(const Vector3D<double>& w, double theta) const;

    /**
     *  @brief      Traslate object.
     *  @details    This function returns a translated version of the object. 
     *  @param[in]  dx  Translation of the first coordinate.
     *  @param[in]  dy  Translation of the second coordinate.
     *  @param[in]  dz  Translation of the third coordinate.
     *  @returns    The transformed object.
     */
    Line3D translate(double dx, double dy, double dz) const;

    /**
     *  @brief      Scale object.
     *  @details    This function returns a scaled version of the object. 
     *  @param[in]  sx  Scale factor of the first coordinate.
     *  @param[in]  sy  Scale factor of the second coordinate.
     *  @param[in]  sz  Scale factor of the third coordinate.
     *  @returns    The transformed object.
     */
    Line3D scale(double sx, double sy, double sz) const;

    /**
     *  @brief      Transform object.
     *  @details    This function returns a transformed version of the object. 
     *  @param[in]  tm  Transformation object.
     *  @returns    The transformed object.
     */
    Line3D transform(const AffineTransformation3D& tm) const;

protected:

    ////////// Data members //////////

    Point3D point1_;    /**< Point 1. */

    Point3D point2_;    /**< Point 2. */
};

}}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
