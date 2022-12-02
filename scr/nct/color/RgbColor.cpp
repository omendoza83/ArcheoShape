//=================================================================================================================
/**
 *  @file       RgbColor.cpp
 *  @brief      nct::color::RgbColor class implementation file.
 *  @details    This file contains the implementation of the nct::color::RgbColor class.
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
#include <nct/color/RgbColor.h>

#include <sstream>
#include <iomanip>

//=================================================================================================================
//        HELPER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Maximun of two numbers.
 *  @details    This function calculates the maximum of two numbers.
 *  @param[in]  v1  The first number to be compared.
 *  @param[in]  v2  The second number to be compared.
 *  @returns    The largest of the input numbers.
 */
static double maximum(double v1, double v2) noexcept
{
    return v2 > v1 ? (v2) : (v1);
}

//-----------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Minimun of two numbers.
 *  @details    This function calculates the minimum of two numbers.
 *  @param[in]  v1  The first number to be compared.
 *  @param[in]  v2  The second number to be compared.
 *  @returns    The smallest of the input numbers.
 */
static double minimum(double v1, double v2) noexcept
{
    return v2 < v1 ? (v2) : (v1);
}

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::color::RgbColor::RgbColor(const std::string& color)
{
    if ((color.size() != 7) && (color.size() != 9) && (color.size() != 13) && (color.size() != 17))
        throw ArgumentException("color", exc_bad_color_string_length, SOURCE_INFO);

    if (color[0] != '#')
        throw ArgumentException("color", exc_bad_color_string, SOURCE_INFO);

    std::stringstream ss;
    ss << std::hex << color.substr(1);
    unsigned long long val = 0;
    ss >> val;
    if ((ss.fail()))
        throw ArgumentException("color", exc_bad_color_string, SOURCE_INFO);

    c_[0] = 0;
    c_[1] = 0;
    c_[2] = 0;

    if (color.size() == 7) {
        c_[0] = nct::UINT8_ESC*static_cast<unsigned char>((val >> 16) & 0xff);
        c_[1] = nct::UINT8_ESC*static_cast<unsigned char>((val >> 8) & 0xff);
        c_[2] = nct::UINT8_ESC*static_cast<unsigned char>((val) & 0xff);
    }
    else if (color.size() == 9) {
        c_[0] = nct::UINT8_ESC*static_cast<unsigned char>((val >> 24) & 0xff);
        c_[1] = nct::UINT8_ESC*static_cast<unsigned char>((val >> 16) & 0xff);
        c_[2] = nct::UINT8_ESC*static_cast<unsigned char>((val >> 8) & 0xff);
    }
    else if (color.size() == 13) {
        c_[0] = nct::UINT16_ESC*static_cast<unsigned short>((val >> 32) & 0xffff);
        c_[1] = nct::UINT16_ESC*static_cast<unsigned short>((val >> 16) & 0xffff);
        c_[2] = nct::UINT16_ESC*static_cast<unsigned short>((val) & 0xffff);
    }
    else if (color.size() == 17) {
        c_[0] = nct::UINT16_ESC*static_cast<unsigned short>((val >> 48) & 0xffff);
        c_[1] = nct::UINT16_ESC*static_cast<unsigned short>((val >> 32) & 0xffff);
        c_[2] = nct::UINT16_ESC*static_cast<unsigned short>((val >> 16) & 0xffff);
    }
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void nct::color::RgbColor::setColor(double r, double g, double b)
{
    if ((r<0.0) || (r>1.0))
        throw ArgumentException("r", r, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    if ((g<0.0) || (g>1.0))
        throw ArgumentException("g", g, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    if ((b<0.0) || (b>1.0))
        throw ArgumentException("b", b, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);
    
    c_[0] = r;
    c_[1] = g;
    c_[2] = b;
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::color::RgbColor::hexString(bool ui8) const
{
    std::stringstream ss;

    if (ui8) {
        auto num = static_cast<unsigned int>(blue_UI8()) +
            static_cast<unsigned int>(green_UI8()) * 0x100 +
            static_cast<unsigned int>(red_UI8()) * 0x10000;

        ss << "#" << std::hex << std::uppercase << std::setfill('0') << std::setw(6) << num;
    }
    else {
        auto num = static_cast<unsigned long long>(blue_UI16()) +
            static_cast<unsigned long long>(green_UI16()) * 0x10000LL +
            static_cast<unsigned long long>(red_UI16()) * 0x100000000LL;

        ss << "#" << std::hex << std::uppercase << std::setfill('0') << std::setw(12) << num;
    }

    return ss.str();
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::color::RgbColor::colorString() const
{
    std::stringstream ss;
    ss << "rgb(" 
        << static_cast<unsigned int>(red_UI8()) << ","
        << static_cast<unsigned int>(green_UI8()) << ","
        << static_cast<unsigned int>(blue_UI8()) << ")";

    return ss.str();
}

//-----------------------------------------------------------------------------------------------------------------
nct::color::RgbColor nct::color::RgbColor::fromHSL(const std::string& color)
{
    if ((color.size() != 7) && (color.size() != 9) && (color.size() != 13) && (color.size() != 17))
        throw ArgumentException("color", exc_bad_color_string_length, SOURCE_INFO);

    if (color[0] != '#')
        throw ArgumentException("color", exc_bad_color_string, SOURCE_INFO);

    std::stringstream ss;
    ss << std::hex << color.substr(1);
    unsigned long long val = 0;
    ss >> val;
    if ((ss.fail()))
        throw ArgumentException("color", exc_bad_color_string, SOURCE_INFO);

    double c_[] = { 0, 0, 0 };

    if (color.size() == 7) {
        c_[0] = nct::UINT8_ESC*static_cast<unsigned char>((val >> 16) & 0xff);
        c_[1] = nct::UINT8_ESC*static_cast<unsigned char>((val >> 8) & 0xff);
        c_[2] = nct::UINT8_ESC*static_cast<unsigned char>((val) & 0xff);
    }
    else if (color.size() == 9) {
        c_[0] = nct::UINT8_ESC*static_cast<unsigned char>((val >> 24) & 0xff);
        c_[1] = nct::UINT8_ESC*static_cast<unsigned char>((val >> 16) & 0xff);
        c_[2] = nct::UINT8_ESC*static_cast<unsigned char>((val >> 8) & 0xff);
    }
    else if (color.size() == 13) {
        c_[0] = nct::UINT16_ESC*static_cast<unsigned short>((val >> 32) & 0xffff);
        c_[1] = nct::UINT16_ESC*static_cast<unsigned short>((val >> 16) & 0xffff);
        c_[2] = nct::UINT16_ESC*static_cast<unsigned short>((val) & 0xffff);
    }
    else if (color.size() == 17) {
        c_[0] = nct::UINT16_ESC*static_cast<unsigned short>((val >> 48) & 0xffff);
        c_[1] = nct::UINT16_ESC*static_cast<unsigned short>((val >> 32) & 0xffff);
        c_[2] = nct::UINT16_ESC*static_cast<unsigned short>((val >> 16) & 0xffff);
    }

    return fromHSL(c_[0], c_[1], c_[2]);
}

//-----------------------------------------------------------------------------------------------------------------
nct::color::RgbColor nct::color::RgbColor::fromHSL(double h, double s, double l)
{
    if ((h<0.0) || (h>1.0))
        throw ArgumentException("h", h, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    if ((s<0.0) || (s>1.0))
        throw ArgumentException("s", s, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    if ((l<0.0) || (l>1.0))
        throw ArgumentException("l", l, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    RgbColor col;

    if (s != 0) {
        auto hue2rgb = [](double p, double q, double t) -> double
        {
            if (t < 0)
                t += 1.;
            if (t > 1.)
                t -= 1.;
            if (t < 1. / 6.)
                return p + (q - p) * 6. * t;
            if (t < 1. / 2.)
                return q;
            if (t < 2. / 3.)
                return p + (q - p) * (2. / 3. - t) * 6.;
            return p;
        };

        double q = l < 0.5 ? (l * (1 + s)) : (l + s - l * s);
        double p = 2 * l - q;
        col.c_[0] = hue2rgb(p, q, h + 1. / 3.);
        col.c_[1] = hue2rgb(p, q, h);
        col.c_[2] = hue2rgb(p, q, h - 1. / 3.);

    }
    else {
        // Achromatic.
        col.c_[0] = l;
        col.c_[1] = l;
        col.c_[2] = l;
    }

    col.c_[0] = minimum(maximum(0.0, col.c_[0]), 1.0);
    col.c_[1] = minimum(maximum(0.0, col.c_[1]), 1.0);
    col.c_[2] = minimum(maximum(0.0, col.c_[2]), 1.0);

    return col;
}

//-----------------------------------------------------------------------------------------------------------------
nct::color::RgbColor nct::color::RgbColor::fromHSL_UI8(unsigned char h, unsigned char s, unsigned char l)
{
    return fromHSL(nct::UINT8_ESC*h, nct::UINT8_ESC*s, nct::UINT8_ESC*l);
}

//-----------------------------------------------------------------------------------------------------------------
nct::color::RgbColor nct::color::RgbColor::fromHSL_UI16(unsigned short h, unsigned short s, unsigned short l)
{
    return fromHSL(nct::UINT16_ESC*h, nct::UINT16_ESC*s, nct::UINT16_ESC*l);
}

//-----------------------------------------------------------------------------------------------------------------
nct::color::RgbColor nct::color::RgbColor::fromHSV(const std::string& color)
{
    if ((color.size() != 7) && (color.size() != 9) && (color.size() != 13) && (color.size() != 17))
        throw ArgumentException("color", exc_bad_color_string_length, SOURCE_INFO);

    if (color[0] != '#')
        throw ArgumentException("color", exc_bad_color_string, SOURCE_INFO);

    std::stringstream ss;
    ss << std::hex << color.substr(1);
    unsigned long long val = 0;
    ss >> val;
    if ((ss.fail()))
        throw ArgumentException("color", exc_bad_color_string, SOURCE_INFO);

    double c_[] = { 0, 0, 0 };

    if (color.size() == 7) {
        c_[0] = nct::UINT8_ESC*static_cast<unsigned char>((val >> 16) & 0xff);
        c_[1] = nct::UINT8_ESC*static_cast<unsigned char>((val >> 8) & 0xff);
        c_[2] = nct::UINT8_ESC*static_cast<unsigned char>((val) & 0xff);
    }
    else if (color.size() == 9) {
        c_[0] = nct::UINT8_ESC*static_cast<unsigned char>((val >> 24) & 0xff);
        c_[1] = nct::UINT8_ESC*static_cast<unsigned char>((val >> 16) & 0xff);
        c_[2] = nct::UINT8_ESC*static_cast<unsigned char>((val >> 8) & 0xff);
    }
    else if (color.size() == 13) {
        c_[0] = nct::UINT16_ESC*static_cast<unsigned short>((val >> 32) & 0xffff);
        c_[1] = nct::UINT16_ESC*static_cast<unsigned short>((val >> 16) & 0xffff);
        c_[2] = nct::UINT16_ESC*static_cast<unsigned short>((val) & 0xffff);
    }
    else if (color.size() == 17) {
        c_[0] = nct::UINT16_ESC*static_cast<unsigned short>((val >> 48) & 0xffff);
        c_[1] = nct::UINT16_ESC*static_cast<unsigned short>((val >> 32) & 0xffff);
        c_[2] = nct::UINT16_ESC*static_cast<unsigned short>((val >> 16) & 0xffff);
    }

    return fromHSV(c_[0], c_[1], c_[2]);
}

//-----------------------------------------------------------------------------------------------------------------
nct::color::RgbColor nct::color::RgbColor::fromHSV(double h, double s, double v)
{
    if ((h<0.0) || (h>1.0))
        throw ArgumentException("h", h, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    if ((s<0.0) || (s>1.0))
        throw ArgumentException("s", s, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    if ((v<0.0) || (v>1.0))
        throw ArgumentException("v", v, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    RgbColor col;

    int i = static_cast<int>(std::floor(h * 6.0));
    double f = h * 6.0 - i;
    double p = v * (1.0 - s);
    double q = v * (1.0 - f * s);
    double t = v * (1.0 - (1.0 - f) * s);

    switch (i % 6) {
        case 0:
            col.c_[0] = v;
            col.c_[1] = t;
            col.c_[2] = p;
            break;
        case 1:
            col.c_[0] = q;
            col.c_[1] = v;
            col.c_[2] = p;
            break;
        case 2:
            col.c_[0] = p;
            col.c_[1] = v;
            col.c_[2] = t;
            break;
        case 3:
            col.c_[0] = p;
            col.c_[1] = q;
            col.c_[2] = v;
            break;
        case 4:
            col.c_[0] = t;
            col.c_[1] = p;
            col.c_[2] = v;
            break;
        case 5:
            col.c_[0] = v;
            col.c_[1] = p;
            col.c_[2] = q;
            break;
    }

    col.c_[0] = minimum(maximum(0.0, col.c_[0]), 1.0);
    col.c_[1] = minimum(maximum(0.0, col.c_[1]), 1.0);
    col.c_[2] = minimum(maximum(0.0, col.c_[2]), 1.0);

    return col;
}

//-----------------------------------------------------------------------------------------------------------------
nct::color::RgbColor nct::color::RgbColor::fromHSV_UI8(unsigned char h, unsigned char s, unsigned char v)
{
    return fromHSV(nct::UINT8_ESC*h, nct::UINT8_ESC*s, nct::UINT8_ESC*v);
}

//-----------------------------------------------------------------------------------------------------------------
nct::color::RgbColor nct::color::RgbColor::fromHSV_UI16(unsigned short h, unsigned short s, unsigned short v)
{
    return fromHSV(nct::UINT16_ESC*h, nct::UINT16_ESC*s, nct::UINT16_ESC*v);
}

//-----------------------------------------------------------------------------------------------------------------
std::vector<nct::color::RgbColor> nct::color::RgbColor::colorPalette(
    const std::vector<std::pair<RgbColor, size_t>>& pivotColors)
{
    // Check arguments.
    auto nPiv = pivotColors.size();
    
    if (nPiv < 2)
        throw ArgumentException("pivotColors", exc_less_than_two_pivot_colors, SOURCE_INFO);

    if ((pivotColors[0].second != 0) || (pivotColors[nPiv - 1].second == 0))
        throw ArgumentException("pivotColors", exc_bad_pivot_color_indices, SOURCE_INFO);

    auto size = pivotColors[nPiv - 1].second + 1;
    for (index_t i = 0; i<nPiv; i++) {
        if (pivotColors[i].second >= size)
            throw ArgumentException("pivotColors", exc_indices_out_of_range, SOURCE_INFO);
        if (i>0) {
            if (pivotColors[i].second == pivotColors[i - 1].second)
                throw ArgumentException("pivotColors", exc_bad_pivot_color_indices,
                SOURCE_INFO);

            if (pivotColors[i].second < pivotColors[i - 1].second)
                throw ArgumentException("pivotColors", exc_bad_pivot_color_indices, SOURCE_INFO);
        }
    }

    // Build palette.
    std::vector<RgbColor> palette(size);

    double inc = 1 / static_cast<double>(pivotColors[1].second - pivotColors[0].second);
    double t = 0;
    size_t pivIndex = 0;
    for (index_t i = 0; i<size; i++) {
        // Verify whether it is time to change the pivot.
        if ((i >= pivotColors[pivIndex + 1].second) && (i != (size - 1))) {
            pivIndex++;
            inc = 1 / static_cast<double>(pivotColors[pivIndex + 1].second - pivotColors[pivIndex].second);
            t = 0;
        }

        // Interpolation.
        palette[i].c_[0] = pivotColors[pivIndex].first.c_[0] * (1 - t) + 
            pivotColors[pivIndex + 1].first.c_[0] * t;
        palette[i].c_[0] = minimum(maximum(0.0, palette[i].c_[0]), 1.0);

        palette[i].c_[1] = pivotColors[pivIndex].first.c_[1] * (1 - t) + 
            pivotColors[pivIndex + 1].first.c_[1] * t;
        palette[i].c_[1] = minimum(maximum(0.0, palette[i].c_[1]), 1.0);

        palette[i].c_[2] = pivotColors[pivIndex].first.c_[2] * (1 - t) + 
            pivotColors[pivIndex + 1].first.c_[2] * t;
        palette[i].c_[2] = minimum(maximum(0.0, palette[i].c_[2]), 1.0);
        
        t += inc;
    }

    return palette;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
