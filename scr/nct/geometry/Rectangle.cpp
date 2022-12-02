//=================================================================================================================
/**
 *  @file       Rectangle.cpp
 *  @brief      nct::geometry::Rectangle class implementation file.
 *  @details    This file contains the implementation of the nct::geometry::Rectangle class.
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
#include <nct/geometry/Rectangle.h>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Rectangle::Rectangle(double x, double y, double w, double h) noexcept :
    position_{x, y}, width_{w}, height_{h}
{
    if (width_ < 0) {
        width_ = -width_;
        position_[0] -= width_;        
    }

    if (height_ < 0) {
        height_ = -height_;
        position_[1] -= height_;        
    }
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Rectangle::Rectangle(const Point2D& p, double w, double h) noexcept : 
    position_{p}, width_{w}, height_{h} {
    if (width_ < 0) {
        width_ = -width_;
        position_[0] -= width_;        
    }

    if (height_ < 0) {
        height_ = -height_;
        position_[1] -= height_;        
    }
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Rectangle::Rectangle(const Point2D& p1, const Point2D& p2) noexcept :
position_{p1}, width_{p2[0] - p1[0]}, height_{p2[1] - p1[1]}
{
    if (width_ < 0) {
        width_ = -width_;
        position_[0] -= width_;        
    }

    if (height_ < 0) {
        height_ = -height_;
        position_[1] -= height_;        
    }
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
const nct::Point2D& nct::geometry::Rectangle::position() const noexcept 
{
    return position_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Rectangle::setPosition(double x, double y) noexcept 
{
    position_[0] = x;
    position_[1] = y;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Rectangle::setPosition(const Point2D& p) noexcept 
{
    position_ = p;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::Rectangle::width() const noexcept 
{
    return width_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Rectangle::setWidth(double w) noexcept 
{
    width_ = w;
    if (width_ < 0) {
        width_ = -width_;
        position_[0] -= width_;        
    }
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::Rectangle::height() const noexcept 
{
    return height_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::Rectangle::setHeight(double h) noexcept 
{
    height_ = h;
    if (height_ < 0) {
        height_ = -height_;
        position_[1] -= height_;        
    }
}

//-----------------------------------------------------------------------------------------------------------------
nct::Point2D nct::geometry::Rectangle::center() const noexcept 
{
    return Point2D(position_[0] + width_ / 2.0, position_[1] + height_ / 2.0);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::Rectangle::perimeter() const noexcept 
{
    return 2.0*width_ + 2.0*height_;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::Rectangle::area() const noexcept 
{
    return width_*height_;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::Point2D> nct::geometry::Rectangle::vertices() const 
{
    nct::Array<nct::Point2D> v =
    { 
        Point2D(position_[0],      position_[1]), 
        Point2D(position_[0] + width_, position_[1]), 
        Point2D(position_[0] + width_, position_[1] + height_), 
        Point2D(position_[0],      position_[1] + height_) 
    };

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::Rectangle::contains(const Point2D& point) const 
{
    if ((point[0] >=  position_[0]) &&
        (point[0] <= (position_[0] + width_)) &&
        (point[1] >=  position_[1]) &&
        (point[1] <= (position_[1] + height_)))
        return true;

    return false;
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::Rectangle::collidesWith(const Rectangle& r) const 
{
    auto valueInRange = [](double value, double min, double max) -> bool
    {
        return (value >= min) && (value <= max);
    };

    bool xOverlap = valueInRange(position_[0], r.position_[0], r.position_[0] + r.width_) ||
        valueInRange(r.position_[0], position_[0], position_[0] + width_);

    bool yOverlap = valueInRange(position_[1], r.position_[1], r.position_[1] + r.height_) ||
        valueInRange(r.position_[1], position_[1], position_[1] + height_);

    return xOverlap && yOverlap;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Rectangle nct::geometry::Rectangle::translate(double dx, double dy) const 
{
    Rectangle r(*this);
    r.position_ = AffineTransformation::translate(r.position_, dx, dy);
    return r;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Rectangle nct::geometry::Rectangle::scale(double sx, double sy) const 
{
    auto pos1 = AffineTransformation::scale(position_, sx, sy);
    auto pos2 = AffineTransformation::scale(position_ + Point2D(width_, height_), sx, sy);

    
    return Rectangle(pos1, pos2);
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
