//=================================================================================================================
/**
 *  @file       Rectangle.h
 *  @brief      nct::geometry::Rectangle class.
 *  @details    Declaration of the nct::geometry::Rectangle class.
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

#ifndef NCT_RECTANGLE_H_INCLUDE
#define NCT_RECTANGLE_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/Array.h>
#include <nct/geometry/AffineTransformation.h>

//=================================================================================================================
namespace nct {
namespace geometry {

/**
 *  @brief      Rectangle class.
 *  @details    This class defines a rectangle in the plane.
 */
class NCT_EXPIMP Rectangle final {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the default configuration. 
     *              The rectangle is initialized at the origin and its width and height are set to zero.
     */
    Rectangle() noexcept =  default;

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes a rectangle using the specified position, width and height.
     *  @param[in]  x  Horizontal position.
     *  @param[in]  y  Vertical position.
     *  @param[in]  w  Width.
     *  @param[in]  h  Height.
     */
    Rectangle(double x, double y, double w, double h) noexcept;

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes a rectangle using the specified position, width and height.
     *  @param[in]  p  Point where the rectangle is located.
     *  @param[in]  w  Width.
     *  @param[in]  h  Height.
     */
    Rectangle(const Point2D& p, double w, double h) noexcept;

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes a rectangle using the specified points. These point
     *              represent opposite corners of the rectangle.
     *  @param[in]  p1  Point one.
     *  @param[in]  p2  Point two.
     */
    Rectangle(const Point2D& p1, const Point2D& p2) noexcept;
    
    ////////// Member functions //////////

    /**
     *  @brief      Position of the rectangle.
     *  @returns    The position of the rectangle.
     */
    const Point2D& position() const noexcept;

    /**
     *  @brief      Modify position of the rectangle.
     *  @details    This function modifies the current position of the rectangle.
     *  @param[in]  x  The new horizontal position.
     *  @param[in]  y  The new vertical position.
     */
    void setPosition(double x, double y) noexcept;

    /**
     *  @brief      Modify Position of the rectangle.
     *  @details    This function modifies the current position of the rectangle.
     *  @param[in]  p  The new position.
     */
    void setPosition(const Point2D& p) noexcept;

    /**
     *  @brief      Width of the rectangle.
     *  @details    This function returns the current width of the rectangle.
     *  @returns    The width of the rectangle.
     */
    double width() const noexcept;

    /**
     *  @brief      Modify width of the rectangle.
     *  @details    This function modifies the current width of the rectangle.
     *  @param[in]  w  The new width.
     */
    void setWidth(double w) noexcept;

    /**
     *  @brief      Height of the rectangle.
     *  @details    This function returns the current height of the rectangle.
     *  @returns    The height of the rectangle.
     */
    double height() const noexcept;

    /**
     *  @brief      Modify height of the rectangle.
     *  @details    This function modifies the current height of the rectangle.
     *  @param[in]  h  The new height.
     */
    void setHeight(double h) noexcept;

    /**
     *  @brief      Rectangle center.
     *  @details    This function returns the center of the rectangle.
     *  @returns    The center of the rectangle.
     */
    Point2D center() const noexcept;

    /**
     *  @brief      Rectangle perimeter.
     *  @details    This function computes the perimeter of the rectangle.
     *  @returns    The perimeter of the geometric object.
     */
    double perimeter() const noexcept;

    /**
     *  @brief      Rectangle area.
     *  @details    This function computes the area of the rectangle.
     *  @returns    The area of the geometric object.
     */
    double area() const noexcept;

    /**
     *  @brief      Vertices.
     *  @details    This function returns the vertices of the rectangle.
     *  @returns    The vertices of the rectangle.
     */
    Array<Point2D> vertices() const;

    /**
     *  @brief      Contains point?
     *  @details    This function tests whether the current rectangle contains the specified point.
     *  @param[in]  point  Point to test.
     *  @returns    True, if the point is contained by the object.
     */
    bool contains(const Point2D& p) const;

    /**
     *  @brief      Collides with rectangle?
     *  @details    This function tests whether the current rectangle collides with another
     *              rectangle.
     *  @param[in]  r  Rectangle to test.
     *  @returns    True, if the rectangles collide.
     */
    bool collidesWith(const Rectangle& r) const;

    /**
     *  @brief      Traslate object.
     *  @details    This function returns a translated version of the object. 
     *  @param[in]  dx  Translation of the first coordinate.
     *  @param[in]  dy  Translation of the second coordinate.
     *  @returns    The transformed object.
     */
    Rectangle translate(double dx, double dy) const;

    /**
     *  @brief      Scale object.
     *  @details    This function returns a scaled version of the object. 
     *  @param[in]  sx  Scale factor of the first coordinate.
     *  @param[in]  sy  Scale factor of the second coordinate.
     *  @returns    The transformed object.
     */
    Rectangle scale(double sx, double sy) const;

protected:

    ////////// Data members //////////

    Point2D position_;      /**< Position. */

    double width_ {0};      /**< Width. */

    double height_ {0};     /**< Height. */

};

}}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
