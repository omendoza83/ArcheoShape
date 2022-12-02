//=================================================================================================================
/**
 *  @file       RgbColor_inline.h
 *  @brief      Inline functions of the nct::color::RgbColor class.
 *  @details    Implementation of inline functions of the nct::color::RgbColor class.
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
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
constexpr nct::color::RgbColor::RgbColor(double r, double g, double b)
{
    if ((r < 0.0) || (r > 1.0))
        throw ArgumentException("r", r, 0.0, 1.0,
            RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    if ((g < 0.0) || (g > 1.0))
        throw ArgumentException("g", g, 0.0, 1.0,
            RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    if ((b < 0.0) || (b > 1.0))
        throw ArgumentException("b", b, 0.0, 1.0,
            RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    c_[0] = r;
    c_[1] = g;
    c_[2] = b;
}

//-----------------------------------------------------------------------------------------------------------------
constexpr nct::color::RgbColor::RgbColor(unsigned char r, unsigned char g, unsigned char b) noexcept
{
    c_[0] = nct::UINT8_ESC * r;
    c_[1] = nct::UINT8_ESC * g;
    c_[2] = nct::UINT8_ESC * b;
}

//-----------------------------------------------------------------------------------------------------------------
constexpr nct::color::RgbColor::RgbColor(unsigned short r, unsigned short g, unsigned short b) noexcept
{
    c_[0] = nct::UINT16_ESC * r;
    c_[1] = nct::UINT16_ESC * g;
    c_[2] = nct::UINT16_ESC * b;
}

//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
constexpr bool nct::color::RgbColor::operator==(const RgbColor& right) const noexcept
{
    if (c_[0] != right.c_[0])
        return false;

    if (c_[1] != right.c_[1])
        return false;

    if (c_[2] != right.c_[2])
        return false;

    return true;
}

//-----------------------------------------------------------------------------------------------------------------
constexpr bool nct::color::RgbColor::operator!=(const RgbColor& right) const noexcept
{
    return !operator==(right);
}

//-----------------------------------------------------------------------------------------------------------------
constexpr double nct::color::RgbColor::operator[](size_t i) const
{
    if (i >= 3)
        throw IndexOutOfRangeException("i", SOURCE_INFO);
    return c_[i];
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::RgbColor::setColor_UI8(unsigned char r, unsigned char g, unsigned char b) noexcept
{
    c_[0] = nct::UINT8_ESC * r;
    c_[1] = nct::UINT8_ESC * g;
    c_[2] = nct::UINT8_ESC * b;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::RgbColor::setColor_UI16(unsigned short r, unsigned short g, unsigned short b) noexcept
{
    c_[0] = nct::UINT16_ESC * r;
    c_[1] = nct::UINT16_ESC * g;
    c_[2] = nct::UINT16_ESC * b;
}

//-----------------------------------------------------------------------------------------------------------------
constexpr double nct::color::RgbColor::red() const noexcept
{
    return c_[0];
}

//-----------------------------------------------------------------------------------------------------------------
constexpr unsigned char nct::color::RgbColor::red_UI8() const noexcept
{
    return static_cast<unsigned char>(c_[0] * UINT8_MAX + 0.5);
}

//-----------------------------------------------------------------------------------------------------------------
constexpr unsigned short nct::color::RgbColor::red_UI16() const noexcept
{
    return static_cast<unsigned short>(c_[0] * UINT16_MAX + 0.5);
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::RgbColor::setRed(double val)
{
    if ((val<0.0) || (val>1.0))
        throw ArgumentException("val", val, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    c_[0] = val;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::RgbColor::setRed_UI8(unsigned char val) noexcept
{
    c_[0] = nct::UINT8_ESC*val;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::RgbColor::setRed_UI16(unsigned short val) noexcept
{
    c_[0] = nct::UINT16_ESC*val;
}

//-----------------------------------------------------------------------------------------------------------------
constexpr double nct::color::RgbColor::green() const noexcept
{
    return c_[1];
}

//-----------------------------------------------------------------------------------------------------------------
constexpr unsigned char nct::color::RgbColor::green_UI8() const noexcept
{
    return static_cast<unsigned char>(c_[1] * UINT8_MAX + 0.5);
}

//-----------------------------------------------------------------------------------------------------------------
constexpr unsigned short nct::color::RgbColor::green_UI16() const noexcept
{
    return static_cast<unsigned short>(c_[1] * UINT16_MAX + 0.5);
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::RgbColor::setGreen(double val)
{
    if ((val<0.0) || (val>1.0))
        throw ArgumentException("val", val, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    c_[1] = val;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::RgbColor::setGreen_UI8(unsigned char val) noexcept
{
    c_[1] = nct::UINT8_ESC*val;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::RgbColor::setGreen_UI16(unsigned short val) noexcept
{
    c_[1] = nct::UINT16_ESC*val;
}

//-----------------------------------------------------------------------------------------------------------------
constexpr double nct::color::RgbColor::blue() const noexcept
{
    return c_[2];
}

//-----------------------------------------------------------------------------------------------------------------
constexpr unsigned char nct::color::RgbColor::blue_UI8() const noexcept
{
    return static_cast<unsigned char>(c_[2] * UINT8_MAX + 0.5);
}

//-----------------------------------------------------------------------------------------------------------------
constexpr unsigned short nct::color::RgbColor::blue_UI16() const noexcept
{
    return static_cast<unsigned short>(c_[2] * UINT16_MAX + 0.5);
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::RgbColor::setBlue(double val)
{
    if ((val<0.0) || (val>1.0))
        throw ArgumentException("val", val, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    c_[2] = val;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::RgbColor::setBlue_UI8(unsigned char val) noexcept
{
    c_[2] = nct::UINT8_ESC*val;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::RgbColor::setBlue_UI16(unsigned short val) noexcept
{
    c_[2] = nct::UINT16_ESC*val;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
