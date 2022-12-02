//=================================================================================================================
/**
 *  @file       Plane.h
 *  @brief      nct::geometry::Plane class.
 *  @details    Declaration of the nct::geometry::Plane class.
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

#ifndef NCT_PLANE_H_INCLUDE
#define NCT_PLANE_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/Array.h>
#include <nct/Array2D.h>
#include <nct/geometry/Line3D.h>
#include <nct/geometry/AffineTransformation3D.h>

//=================================================================================================================
namespace nct {
namespace geometry {

/**
 *  @brief      Plane class.
 *  @details    This class defines a plane in the space. The characteristics of the plane
 *              are set by three points that are indicated when the object is built.
 *              These points are used to compute the normal and parallel axis of the plane
 *              which are used to evaluate the parametric surface.
 */
class NCT_EXPIMP Plane final {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the default configuration. 
     *              The plane is initialized at the origin and its normal vector is not well defined.
     */
    Plane() noexcept = default;

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes a plane using the specified points.
     *  @param[in]  p1  Point 1.
     *  @param[in]  p2  Point 2.
     *  @param[in]  p3  Point 3.
     */
    Plane(const Point3D& p1, const Point3D& p2, const Point3D& p3);

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes a plane using the specified point and normal vector.
     *  @param[in]  p  Point on the plane.
     *  @param[in]  n  Normal vector to the plane.
     */
    Plane(const Point3D& p, const Vector3D<double>& n);
    
    ////////// Operators //////////        
    
    /**
     *  @brief      Point.
     *  @details    This operator returns the specified point of the plane tat.
     *  @param[in]  i  Point index (0, 1 or 2).
     *  @returns    A reference to the point.
     */
    Point3D& operator[](size_t i);

    /**
     *  @brief      Point.
     *  @details    This operator returns the specified point of the triangle.
     *  @param[in]  i  Point index (0 or 1).
     *  @returns    A const reference to the point.
     */
    const Point3D& operator[](size_t i) const;

    /**
     *  @brief      Evaluate parametric surface.
     *  @details    This operator evaluates the parametric surface that is defined by the plane. The
     *              surface is evaluated by two parameters, s and t. The parameter s indicates the 
     *              position relative to the axis 1, while the parameter t specifies the displacement
     *              relative to the axis 2. The origin is set to point 1.
     *  @param[in]  s  Displacement on the direction of axis 1.
     *  @param[in]  t  Displacement on the direction of axis 2.
     *  @returns    The point that corresponds to the specified values of s and t.
     */
    Point3D operator()(double s, double t) const noexcept;

    ////////// Member functions //////////

    /**
     *  @brief      Set line points.
     *  @details    This function modifies the points that define the triangle.
     *  @param[in]  p1  Point 1.
     *  @param[in]  p2  Point 2.
     *  @param[in]  p3  Point 3.
     */
    void setPoints(const Point3D& p1, const Point3D& p2, const Point3D& p3);

    /**
     *  @brief      Plane point 1.
     *  @details    This function returns the first point that defines the triangle.
     *  @returns    The first point.
     */
    const Point3D& point1() const noexcept;

    /**
     *  @brief      Set point 1.
     *  @details    This function modifies the first point that defines the triangle.
     *  @param[in]  x  x coordinate of the new point.
     *  @param[in]  y  y coordinate of the new point.
     *  @param[in]  z  z coordinate of the new point.
     */
    void setPoint1(double x, double y, double z);

    /**
     *  @brief      Set point 1.
     *  @details    This function modifies the first point that defines the triangle.
     *  @param[in]  p  The new point.
     */
    void setPoint1(const Point3D& p);

    /**
     *  @brief      Plane point 2.
     *  @details    This function returns the second point that defines the triangle.
     *  @returns    The second point.
     */
    const Point3D& point2() const noexcept;

    /**
     *  @brief      Set point 2.
     *  @details    This function modifies the second point that defines the triangle.
     *  @param[in]  x  x coordinate of the new point.
     *  @param[in]  y  y coordinate of the new point.
     *  @param[in]  z  z coordinate of the new point.
     */
    void setPoint2(double x, double y, double z);

    /**
     *  @brief      Set point 2.
     *  @details    This function modifies the second point that defines the triangle.
     *  @param[in]  p  The new point.
     */
    void setPoint2(const Point3D& p);

    /**
     *  @brief      Plane point 3.
     *  @details    This function returns the third point that defines the triangle.
     *  @returns    The third point.
     */
    const Point3D& point3() const noexcept;

    /**
     *  @brief      Set point 3.
     *  @details    This function modifies the third point that defines the triangle.
     *  @param[in]  x  x coordinate of the new point.
     *  @param[in]  y  y coordinate of the new point.
     *  @param[in]  z  z coordinate of the new point.
     */
    void setPoint3(double x, double y, double z);

    /**
     *  @brief      Set line point 2.
     *  @details    This function modifies the third point that defines the triangle.
     *  @param[in]  p  The new point.
     */
    void setPoint3(const Point3D& p);

    /**
     *  @brief      Normal vector.
     *  @details    This function returns an unitary vector that is normal to the plane. 
     *  @returns    Normal vector.
     */
    const Vector3D<double>& normal() const noexcept;

    /**
     *  @brief      Axis 1.
     *  @details    This function returns an unitary vector on the direction of the line defined
     *              by p2-p1.
     *  @returns    The axis 1.
     */
    const Vector3D<double>& axis1() const noexcept;

    /**
     *  @brief      Axis 2.
     *  @details    This function returns an unitary vector that lies on the plane
     *              and is normal to the axis 1.
     *  @returns    The axis 2.
     */
    const Vector3D<double>& axis2() const noexcept;

    /**
     *  @brief      Axis 3.
     *  @details    This function returns an unitary vector that is normal to the plane.
     *  @returns    The axis 3.
     */
    const Vector3D<double>& axis3() const noexcept;

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
     *  @brief      Distance to a plane.
     *  @details    This function returns the distance to the specified plane.
     *  @oaram[in] plane    Plane.
     *  @returns    The distance to the specified plane.
     */
    double distance(const Plane& plane) const;

    /**
     *  @brief      Contains point?
     *  @details    This function tests whether the object contains the specified point.
     *  @param[in]  point  Point to test.
     *  @param[in]  tol  Tolerance that is used to accept the point.
     *  @returns    True, if the point is contained by the object.
     */
    bool contains(const Point3D& p, double tol = MEDIUM_TOL) const;

    /**
     *  @brief      Contains line?
     *  @details    This function tests whether the object contains the specified line.
     *  @param[in]  l  Line to test.
     *  @param[in]  tol  Tolerance that is used to accept the line.
     *  @returns    True, if the line is inside the object.
     */
    bool contains(const Line3D& l, double tol = MEDIUM_TOL) const;

    /**
     *  @brief      Collides with line?
     *  @details    This function determines whether the plane collides with one line.
     *  @param[in]  line  Line to test.
     *  @param[in]  tol  Tolerance that is used to accept the line.
     *  @returns    True, if the plane collides with the specified object.
     */
    bool collidesWith(const Line3D& l, double tol = MEDIUM_TOL) const;

    /**
     *  @brief      Collides with plane?
     *  @details    This function determines whether the plane collides with another plane.
     *  @param[in]  plane  Plane to test.
     *  @param[in]  tol  Tolerance that is used to accept the plane.
     *  @returns    True, if the plane collides with the specified object.
     */
    bool collidesWith(const Plane& plane, double tol = MEDIUM_TOL) const;

    /**
     *  @brief      Rectangular grid.
     *  @details    This function returns a 2D array with the points that corresponds to the
     *              specified range of values of the parametric surface.
     *  @param[in]  mins  The minimum value of the parameter s.
     *  @param[in]  maxs  The maximum value of the parameter s.
     *  @param[in]  mint  The minimum value of the parameter t.
     *  @param[in]  maxt  The maximum value of the parameter t.
     *  @param[in]  ns  The number of divisions of the parameter s.
     *  @param[in]  nt  The number of divisions of the parameter t.
     *  @returns    The ns*nt rectangular grid.
     */
    Array2D<Point3D> rectangularGrid(double mins, double maxs,
        double mint, double maxt, size_t ns, size_t nt) const;

    /**
     *  @brief      Rotate object.
     *  @details    This function returns a rotated version of the object. The
     *              rotation is done around the origin.
     *  @param[in]  w  Rotation axis.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    The rotated object.
     */
    Plane rotate(const Vector3D<double>& w, double theta) const;

    /**
     *  @brief      Traslate object.
     *  @details    This function returns a translated version of the object. 
     *  @param[in]  dx  Translation of the first coordinate.
     *  @param[in]  dy  Translation of the second coordinate.
     *  @param[in]  dz  Translation of the third coordinate.
     *  @returns    The transformed object.
     */
    Plane translate(double dx, double dy, double dz) const;

    /**
     *  @brief      Scale object.
     *  @details    This function returns a scaled version of the object. 
     *  @param[in]  sx  Scale factor of the first coordinate.
     *  @param[in]  sy  Scale factor of the second coordinate.
     *  @param[in]  sz  Scale factor of the third coordinate.
     *  @returns    The transformed object.
     */
    Plane scale(double sx, double sy, double sz) const;

    /**
     *  @brief      Transform object.
     *  @details    This function returns a transformed version of the object. 
     *  @param[in]  tm  Transformation object.
     *  @returns    The transformed object.
     */
    Plane transform(const AffineTransformation3D& tm) const;

protected:

    ////////// Data members //////////

    Point3D point1_;            /**< Point 1. */

    Point3D point2_;            /**< Point 2. */

    Point3D point3_;            /**< Point 3. */

    Vector3D<double> axis1_;    /**< Axis 1 (unitary vector on the direction of point2_-point1_). */

    Vector3D<double> axis2_;    /**< Axis 2 (unitary vector on the direction of (point3_-point2_)
                                     - proy(point3_-point1_, point2_-point1_) ). */
    Vector3D<double> axis3_;    /**< Axis 3 (unitary vector on the direction of (point2_-point1_) X
                                    (point3_-point1_). * /. */
};

}}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
