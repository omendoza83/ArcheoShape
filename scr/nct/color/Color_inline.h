//=================================================================================================================
/**
 *  @file       Color_inline.h
 *  @brief      Inline functions of the nct::color::Color class.
 *  @details    Implementation of inline functions of the nct::color::Color class.
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
constexpr nct::color::Color::Color(double comp1, double comp2, double comp3,
    double alpha, ColorSpace sp)
{
    if ((comp1 < 0.0) || (comp1 > 1.0))
        throw ArgumentException("comp1", comp1, 0.0, 1.0,
            RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    if ((comp2 < 0.0) || (comp2 > 1.0))
        throw ArgumentException("comp2", comp2, 0.0, 1.0,
            RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    if ((comp3 < 0.0) || (comp3 > 1.0))
        throw ArgumentException("comp3", comp3, 0.0, 1.0,
            RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    if ((alpha < 0.0) || (alpha > 1.0))
        throw ArgumentException("alpha", alpha, 0.0, 1.0,
            RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    if ((sp != ColorSpace::RGBA) && (sp != ColorSpace::HSVA) && (sp != ColorSpace::HSLA))
        throw ArgumentException("sp", exc_bad_color_space, SOURCE_INFO);

    colorSpace_ = sp;
    c_[0] = comp1;
    c_[1] = comp2;
    c_[2] = comp3;
    c_[3] = alpha;
}

//-----------------------------------------------------------------------------------------------------------------
constexpr nct::color::Color::Color(unsigned char comp1, unsigned char comp2, unsigned char comp3,
    unsigned char alpha, ColorSpace sp)
{
    if ((sp != ColorSpace::RGBA) && (sp != ColorSpace::HSVA) && (sp != ColorSpace::HSLA))
        throw ArgumentException("sp", exc_bad_color_space, SOURCE_INFO);

    colorSpace_ = sp;
    c_[0] = nct::UINT8_ESC * comp1;
    c_[1] = nct::UINT8_ESC * comp2;
    c_[2] = nct::UINT8_ESC * comp3;
    c_[3] = nct::UINT8_ESC * alpha;
}

//-----------------------------------------------------------------------------------------------------------------
constexpr nct::color::Color::Color(unsigned short comp1, unsigned short comp2, unsigned short comp3,
    unsigned short alpha, ColorSpace sp)
{
    if ((sp != ColorSpace::RGBA) && (sp != ColorSpace::HSVA) && (sp != ColorSpace::HSLA))
        throw ArgumentException("sp", exc_bad_color_space, SOURCE_INFO);

    colorSpace_ = sp;
    c_[0] = nct::UINT16_ESC * comp1;
    c_[1] = nct::UINT16_ESC * comp2;
    c_[2] = nct::UINT16_ESC * comp3;
    c_[3] = nct::UINT16_ESC * alpha;
}


//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
constexpr double nct::color::Color::operator[](size_t i) const
{
    if (i >= 4)
        throw IndexOutOfRangeException("i", SOURCE_INFO);
    return c_[i];
}

//-----------------------------------------------------------------------------------------------------------------
constexpr bool nct::color::Color::operator==(const Color& right) const noexcept
{
    if (colorSpace_ != right.colorSpace_)
        return convertTo(ColorSpace::RGBA) == right.convertTo(ColorSpace::RGBA);

    if (c_[0] != right.c_[0])
        return false;

    if (c_[1] != right.c_[1])
        return false;

    if (c_[2] != right.c_[2])
        return false;

    if (c_[3] != right.c_[3])
        return false;

    return true;
}

//-----------------------------------------------------------------------------------------------------------------
constexpr bool nct::color::Color::operator!=(const Color& right) const noexcept
{
    return !operator==(right);
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setRGBA_UI8(unsigned char r, unsigned char g, unsigned char b,
    unsigned char alpha) noexcept
{
    colorSpace_ = ColorSpace::RGBA;
    c_[0] = nct::UINT8_ESC * r;
    c_[1] = nct::UINT8_ESC * g;
    c_[2] = nct::UINT8_ESC * b;
    c_[3] = nct::UINT8_ESC * alpha;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setRGBA_UI16(unsigned short r, unsigned short g, unsigned short b,
    unsigned short alpha) noexcept
{
    colorSpace_ = ColorSpace::RGBA;
    c_[0] = nct::UINT16_ESC * r;
    c_[1] = nct::UINT16_ESC * g;
    c_[2] = nct::UINT16_ESC * b;
    c_[3] = nct::UINT16_ESC * alpha;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setHSLA_UI8(unsigned char h, unsigned char s, unsigned char l,
    unsigned char alpha) noexcept
{
    colorSpace_ = ColorSpace::HSLA;
    c_[0] = nct::UINT8_ESC * h;
    c_[1] = nct::UINT8_ESC * s;
    c_[2] = nct::UINT8_ESC * l;
    c_[3] = nct::UINT8_ESC * alpha;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setHSLA_UI16(unsigned short h, unsigned short s, unsigned short l,
    unsigned short alpha) noexcept
{
    colorSpace_ = ColorSpace::HSLA;
    c_[0] = nct::UINT16_ESC * h;
    c_[1] = nct::UINT16_ESC * s;
    c_[2] = nct::UINT16_ESC * l;
    c_[3] = nct::UINT16_ESC * alpha;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setHSVA_UI8(unsigned char h, unsigned char s, unsigned char v,
    unsigned char alpha) noexcept
{
    colorSpace_ = ColorSpace::HSVA;
    c_[0] = nct::UINT8_ESC * h;
    c_[1] = nct::UINT8_ESC * s;
    c_[2] = nct::UINT8_ESC * v;
    c_[3] = nct::UINT8_ESC * alpha;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setHSVA_UI16(unsigned short h, unsigned short s, unsigned short v,
    unsigned short alpha) noexcept
{
    colorSpace_ = ColorSpace::HSVA;
    c_[0] = nct::UINT16_ESC * h;
    c_[1] = nct::UINT16_ESC * s;
    c_[2] = nct::UINT16_ESC * v;
    c_[3] = nct::UINT16_ESC * alpha;
}

//-----------------------------------------------------------------------------------------------------------------
constexpr nct::color::Color::ColorSpace nct::color::Color::colorSpace() const noexcept
{
    return colorSpace_;
}

//-----------------------------------------------------------------------------------------------------------------
constexpr double nct::color::Color::opacity() const noexcept
{
    return c_[3];
}

//-----------------------------------------------------------------------------------------------------------------
constexpr unsigned char nct::color::Color::opacity_UI8() const noexcept
{
    return static_cast<unsigned char>(c_[3] * UINT8_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
constexpr unsigned short nct::color::Color::opacity_UI16() const noexcept
{
    return static_cast<unsigned short>(c_[3] * UINT16_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setOpacity(double val)
{
    if ((val<0.0) || (val>1.0))
        throw ArgumentException("val", val, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    c_[3] = val;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setOpacity_UI8(unsigned char val) noexcept
{
    c_[3] = nct::UINT8_ESC*val;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setOpacity_UI16(unsigned short val) noexcept
{
    c_[3] = nct::UINT16_ESC*val;
}

//-----------------------------------------------------------------------------------------------------------------
constexpr double nct::color::Color::component1() const noexcept
{
    return c_[0];
}

//-----------------------------------------------------------------------------------------------------------------
constexpr unsigned char nct::color::Color::component1_UI8() const noexcept
{
    return static_cast<unsigned char>(c_[0]*UINT8_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
constexpr unsigned short nct::color::Color::component1_UI16() const noexcept
{
    return static_cast<unsigned short>(c_[0]*UINT16_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setComponent1(double val)
{
    if ((val<0.0) || (val>1.0))
        throw ArgumentException("val", val, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    c_[0] = val;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setComponent1_UI8(unsigned char val) noexcept
{
    c_[0] = nct::UINT8_ESC*val;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setComponent1_UI16(unsigned short val) noexcept
{
    c_[0] = nct::UINT16_ESC*val;
}

//-----------------------------------------------------------------------------------------------------------------
constexpr double nct::color::Color::component2() const noexcept
{
    return c_[1];
}

//-----------------------------------------------------------------------------------------------------------------
constexpr unsigned char nct::color::Color::component2_UI8() const noexcept
{
    return static_cast<unsigned char>(c_[1]*UINT8_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
constexpr unsigned short nct::color::Color::component2_UI16() const noexcept
{
    return static_cast<unsigned short>(c_[1]*UINT16_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setComponent2(double val)
{
    if ((val<0.0) || (val>1.0))
        throw ArgumentException("val", val, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    c_[1] = val;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setComponent2_UI8(unsigned char val) noexcept
{
    c_[1] = nct::UINT8_ESC*val;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setComponent2_UI16(unsigned short val) noexcept
{
    c_[1] = nct::UINT16_ESC*val;
}

//-----------------------------------------------------------------------------------------------------------------
constexpr double nct::color::Color::component3() const noexcept
{
    return c_[2];
}

//-----------------------------------------------------------------------------------------------------------------
constexpr unsigned char nct::color::Color::component3_UI8() const noexcept
{
    return static_cast<unsigned char>(c_[2]*UINT8_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
constexpr unsigned short nct::color::Color::component3_UI16() const noexcept
{
    return static_cast<unsigned short>(c_[2]*UINT16_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setComponent3(double val)
{
    if ((val<0.0) || (val>1.0))
        throw ArgumentException("val", val, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    c_[2] = val;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setComponent3_UI8(unsigned char val) noexcept
{
    c_[2] = nct::UINT8_ESC*val;
}

//-----------------------------------------------------------------------------------------------------------------
inline void nct::color::Color::setComponent3_UI16(unsigned short val) noexcept
{
    c_[2] = nct::UINT16_ESC*val;
}

//-----------------------------------------------------------------------------------------------------------------
inline double nct::color::Color::red() const
{
    if (colorSpace_ == ColorSpace::RGBA)
        return c_[0];

    return convertTo(ColorSpace::RGBA).c_[0];
}

//-----------------------------------------------------------------------------------------------------------------
inline unsigned char nct::color::Color::red_UI8() const
{
    return static_cast<unsigned char>(red()*UINT8_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline unsigned short nct::color::Color::red_UI16() const
{
    return static_cast<unsigned short>(red()*UINT16_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline double nct::color::Color::green() const
{
    if (colorSpace_ == ColorSpace::RGBA)
        return c_[1];

    return convertTo(ColorSpace::RGBA).c_[1];
}

//-----------------------------------------------------------------------------------------------------------------
inline unsigned char nct::color::Color::green_UI8() const
{
    return static_cast<unsigned char>(green()*UINT8_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline unsigned short nct::color::Color::green_UI16() const
{
    return static_cast<unsigned short>(green()*UINT16_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline double nct::color::Color::blue() const
{
    if (colorSpace_ == ColorSpace::RGBA)
        return c_[2];

    return convertTo(ColorSpace::RGBA).c_[2];
}

//-----------------------------------------------------------------------------------------------------------------
inline unsigned char nct::color::Color::blue_UI8() const
{
    return static_cast<unsigned char>(blue()*UINT8_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline unsigned short nct::color::Color::blue_UI16() const
{
    return static_cast<unsigned short>(blue()*UINT16_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline double nct::color::Color::hue() const
{
    if ((colorSpace_ == ColorSpace::HSLA) || (colorSpace_ == ColorSpace::HSVA))
        return c_[0];

    return convertTo(ColorSpace::HSLA).c_[0];
}

//-----------------------------------------------------------------------------------------------------------------
inline unsigned char nct::color::Color::hue_UI8() const
{
    return static_cast<unsigned char>(hue()*UINT8_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline unsigned short nct::color::Color::hue_UI16() const
{
    return static_cast<unsigned short>(hue()*UINT16_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline double nct::color::Color::saturationHSL() const
{
    if (colorSpace_ == ColorSpace::HSLA)
        return c_[1];

    return convertTo(ColorSpace::HSLA).c_[1];
}

//-----------------------------------------------------------------------------------------------------------------
inline unsigned char nct::color::Color::saturationHSL_UI8() const
{
    return static_cast<unsigned char>(saturationHSL()*UINT8_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline unsigned short nct::color::Color::saturationHSL_UI16() const
{
    return static_cast<unsigned short>(saturationHSL()*UINT16_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline double nct::color::Color::saturationHSV() const
{
    if (colorSpace_ == ColorSpace::HSVA)
        return c_[1];

    return convertTo(ColorSpace::HSVA).c_[1];
}

//-----------------------------------------------------------------------------------------------------------------
inline unsigned char nct::color::Color::saturationHSV_UI8() const
{
    return static_cast<unsigned char>(saturationHSV()*UINT8_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline unsigned short nct::color::Color::saturationHSV_UI16() const
{
    return static_cast<unsigned short>(saturationHSV()*UINT16_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline double nct::color::Color::brightness() const
{
    if (colorSpace_ == ColorSpace::HSVA)
        return c_[2];

    return convertTo(ColorSpace::HSVA).c_[2];
}

//-----------------------------------------------------------------------------------------------------------------
inline unsigned char nct::color::Color::brightness_UI8() const
{
    return static_cast<unsigned char>(brightness()*UINT8_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline unsigned short nct::color::Color::brightness_UI16() const
{
    return static_cast<unsigned short>(brightness()*UINT16_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline double nct::color::Color::lightness() const
{
    if (colorSpace_ == ColorSpace::HSLA)
        return c_[2];

    return convertTo(ColorSpace::HSLA).c_[2];
}

//-----------------------------------------------------------------------------------------------------------------
inline unsigned char nct::color::Color::lightness_UI8() const
{
    return static_cast<unsigned char>(lightness()*UINT8_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline unsigned short nct::color::Color::lightness_UI16() const
{
    return static_cast<unsigned short>(lightness()*UINT16_MAX);
}

//-----------------------------------------------------------------------------------------------------------------
inline nct::color::Color nct::color::Color::fromRGBA(double r, double g, double b, double alpha)
{
    Color col;
    col.setRGBA(r, g, b, alpha);
    return col;
}

//-----------------------------------------------------------------------------------------------------------------
inline nct::color::Color nct::color::Color::fromRGBA_UI8(unsigned char r, unsigned char g, unsigned char b,
    unsigned char alpha)
{
    Color col;
    col.setRGBA_UI8(r, g, b, alpha);
    return col;
}

//-----------------------------------------------------------------------------------------------------------------
inline nct::color::Color nct::color::Color::fromRGBA_UI16(unsigned short r, unsigned short g, unsigned short b,
    unsigned short alpha)
{
    Color col;
    col.setRGBA_UI16(r, g, b, alpha);
    return col;
}

//-----------------------------------------------------------------------------------------------------------------
inline nct::color::Color nct::color::Color::fromHSLA(double h, double s, double l, double alpha)
{
    Color col;
    col.setHSLA(h, s, l, alpha);
    return col;
}

//-----------------------------------------------------------------------------------------------------------------
inline nct::color::Color nct::color::Color::fromHSLA_UI8(unsigned char h, unsigned char s, unsigned char l,
    unsigned char alpha)
{
    Color col;
    col.setHSLA_UI8(h, s, l, alpha);
    return col;
}

//-----------------------------------------------------------------------------------------------------------------
inline nct::color::Color nct::color::Color::fromHSLA_UI16(unsigned short h, unsigned short s, unsigned short l,
    unsigned short alpha)
{
    Color col;
    col.setHSLA_UI16(h, s, l, alpha);
    return col;
}

//-----------------------------------------------------------------------------------------------------------------
inline nct::color::Color nct::color::Color::fromHSVA(double h, double s, double v, double alpha)
{
    Color col;
    col.setHSVA(h, s, v, alpha);
    return col;
}

//-----------------------------------------------------------------------------------------------------------------
inline nct::color::Color nct::color::Color::fromHSVA_UI8(unsigned char h, unsigned char s, unsigned char v,
    unsigned char alpha)
{
    Color col;
    col.setHSVA_UI8(h, s, v, alpha);
    return col;
}

//-----------------------------------------------------------------------------------------------------------------
inline nct::color::Color nct::color::Color::fromHSVA_UI16(unsigned short h, unsigned short s, unsigned short v,
    unsigned short alpha)
{
    Color col;
    col.setHSVA_UI16(h, s, v, alpha);
    return col;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
