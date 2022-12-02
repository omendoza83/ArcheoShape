//=================================================================================================================
/**
 *  @file       Triangle3D.h
 *  @brief      nct::geometry::Triangle3D class.
 *  @details    Declaration of the nct::geometry::Triangle3D class.
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

#ifndef NCT_TRIANGLE_3D_H_INCLUDE
#define NCT_TRIANGLE_3D_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/Array.h>
#include <nct/geometry/Line3D.h>
#include <nct/geometry/Plane.h>
#include <nct/geometry/AffineTransformation3D.h>

//=================================================================================================================
namespace nct {
namespace geometry {

/**
 *  @brief      Triangle class.
 *  @details    This class defines a triangle in the space.
 */
class NCT_EXPIMP Triangle3D final {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the default configuration. 
     *              The triangle is initialized at the origin and its size is set to zero.
     */
    Triangle3D() noexcept = default;

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes a triangle using the specified points.
     *  @param[in]  p1  Point 1.
     *  @param[in]  p2  Point 2.
     *  @param[in]  p3  Point 3.
     */
    Triangle3D(const Point3D& p1, const Point3D& p2, const Point3D& p3) noexcept;
    
    ////////// Operators //////////        
    
    /**
     *  @brief      Vertex.
     *  @details    This operator returns the specified vertex of the triangle.
     *  @param[in]  i  Vertex index (0, 1 or 2).
     *  @returns    A reference to the vertex.
     */
    Point3D& operator[](size_t i);

    /**
     *  @brief      Vertex.
     *  @details    This operator returns the specified vertex of the triangle.
     *  @param[in]  i  Vertex index (0, 1 or 2).
     *  @returns    A const reference to the vertex.
     */
    const Point3D& operator[](size_t i) const;

    ////////// Member functions //////////

    /**
     *  @brief      Set vertices.
     *  @details    This function modifies the vertices that define the triangle.
     *  @param[in]  p1  Point 1.
     *  @param[in]  p2  Point 2.
     *  @param[in]  p3  Point 3.
     */
    void setVertices(const Point3D& p1, const Point3D& p2, const Point3D& p3) noexcept;

    /**
     *  @brief      Vertex 1.
     *  @details    This function returns the first vertex that defines the triangle.
     *  @returns    The first vertex.
     */
    const Point3D& vertex1() const noexcept;

    /**
     *  @brief      Set vertex 1.
     *  @details    This function modifies the first vertex that defines the triangle.
     *  @param[in]  x  x coordinate of the new point.
     *  @param[in]  y  y coordinate of the new point.
     *  @param[in]  z  z coordinate of the new point.
     */
    void setVertex1(double x, double y, double z) noexcept;

    /**
     *  @brief      Set vertex 1.
     *  @details    This function modifies the vertex point that defines the triangle.
     *  @param[in]  p  The new point.
     */
    void setVertex1(const Point3D& p) noexcept;

    /**
     *  @brief      Vertex 2.
     *  @details    This function returns the second vertex that defines the triangle.
     *  @returns    The first vertex.
     */
    const Point3D& vertex2() const noexcept;

    /**
     *  @brief      Set vertex 2.
     *  @details    This function modifies the second vertex that defines the triangle.
     *  @param[in]  x  x coordinate of the new point.
     *  @param[in]  y  y coordinate of the new point.
     *  @param[in]  z  z coordinate of the new point.
     */
    void setVertex2(double x, double y, double z) noexcept;

    /**
     *  @brief      Set vertex 2.
     *  @details    This function modifies the second vertex that defines the triangle.
     *  @param[in]  p  The new point.
     */
    void setVertex2(const Point3D& p) noexcept;

    /**
     *  @brief      Vertex 3.
     *  @details    This function returns the third vertex that defines the triangle.
     *  @returns    The first vertex.
     */
    const Point3D& vertex3() const noexcept;

    /**
     *  @brief      Set vertex 3.
     *  @details    This function modifies the third vertex that defines the triangle.
     *  @param[in]  x  x coordinate of the new point.
     *  @param[in]  y  y coordinate of the new point.
     *  @param[in]  z  z coordinate of the new point.
     */
    void setVertex3(double x, double y, double z) noexcept;

    /**
     *  @brief      Set vertex 3.
     *  @details    This function modifies the third vertex that defines the triangle.
     *  @param[in]  p  The new point.
     */
    void setVertex3(const Point3D& p) noexcept;

    /**
     *  @brief      Triangle perimeter.
     *  @details    This function returns the perimeter of the triangle.
     *  @returns    The triangle perimeter.
     */
    double perimeter() const noexcept;

    /**
     *  @brief      Triangle area.
     *  @details    This function returns the area of the triangle.
     *  @returns    The triangle area.
     */
    double area() const noexcept;

    /**
     *  @brief      Triangle center.
     *  @details    This function returns the center of the triangle.
     *  @returns    The center of the triangle.
     */
    Point3D center() const noexcept;

    /**
     *  @brief      Normal vector.
     *  @details    This function returns an unitary vector that is normal to the plane
     *              where the triangle lies.
     *  @returns    Normal vector.
     */
    Vector3D<double> normal() const;

    /**
     *  @brief      Plane.
     *  @details    This function returns the plane where the triangle lies.
     *  @returns    The plane where the triangle lies.
     */
    Plane plane() const;

    /**
     *  @brief      Vertices of the triangle.
     *  @details    This function returns the vertices of the triangle.
     *  @returns    The vertices of the triangle.
     */
    Array<Point3D> vertices() const;

    /**
     *  @brief      Lines of the triangle.
     *  @details    This function returns the lines that limit the triangle.
     *  @returns    The lines of the triangle.
     */
    Array<Line3D> lines() const;

    /**
     *  @brief      Rotate object.
     *  @details    This function returns a rotated version of the object. The
     *              rotation is done around the origin.
     *  @param[in]  w  Rotation axis.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    The rotated object.
     */
    Triangle3D rotate(const Vector3D<double>& w, double theta) const;

    /**
     *  @brief      Traslate object.
     *  @details    This function returns a translated version of the object. 
     *  @param[in]  dx  Translation of the first coordinate.
     *  @param[in]  dy  Translation of the second coordinate.
     *  @param[in]  dz  Translation of the third coordinate.
     *  @returns    The transformed object.
     */
    Triangle3D translate(double dx, double dy, double dz) const;

    /**
     *  @brief      Scale object.
     *  @details    This function returns a scaled version of the object. 
     *  @param[in]  sx  Scale factor of the first coordinate.
     *  @param[in]  sy  Scale factor of the second coordinate.
     *  @param[in]  sz  Scale factor of the third coordinate.
     *  @returns    The transformed object.
     */
    Triangle3D scale(double sx, double sy, double sz) const;

    /**
     *  @brief      Transform object.
     *  @details    This function returns a transformed version of the object. 
     *  @param[in]  tm  Transformation object.
     *  @returns    The transformed object.
     */
    Triangle3D transform(const AffineTransformation3D& tm) const;

protected:

    ////////// Data members //////////

    Point3D v1_;    /**< Vertex 1. */

    Point3D v2_;    /**< Vertex 2. */

    Point3D v3_;    /**< Vertex 3. */
};

}}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
