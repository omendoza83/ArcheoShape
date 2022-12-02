//=================================================================================================================
/**
 *  @file       Color.cpp
 *  @brief      nct::color::Color class implementation file.
 *  @details    This file contains the implementation of the nct::color::Color class.
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
#include <nct/color/Color.h>

#include <sstream>
#include <iomanip>
#include <array>

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
nct::color::Color::Color(ColorName color, ColorSpace sp)
{
    try {
        auto colString = colorString(color);
        auto tmpc = Color(colString, ColorSpace::RGBA);
        
        if (sp == ColorSpace::RGBA)
            *this = tmpc;            
        else
            *this = tmpc.convertTo(sp);
    }
    catch (const nct_exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw InitializationException(SOURCE_INFO);
    }

}

//-----------------------------------------------------------------------------------------------------------------
nct::color::Color::Color(const std::string& color, ColorSpace sp)
{
    if ((sp != ColorSpace::RGBA) && (sp != ColorSpace::HSVA) && (sp != ColorSpace::HSLA))
        throw ArgumentException("sp", exc_bad_color_space, SOURCE_INFO);

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
    c_[3] = 0;
    colorSpace_ = sp;

    if (color.size() == 7) {
        c_[0] = nct::UINT8_ESC * static_cast<unsigned char>((val >> 16) & 0xff);
        c_[1] = nct::UINT8_ESC * static_cast<unsigned char>((val >> 8) & 0xff);
        c_[2] = nct::UINT8_ESC * static_cast<unsigned char>((val) & 0xff);
        c_[3] = 1.0;
    }
    else if (color.size() == 9) {
        c_[0] = nct::UINT8_ESC * static_cast<unsigned char>((val >> 24) & 0xff);
        c_[1] = nct::UINT8_ESC * static_cast<unsigned char>((val >> 16) & 0xff);
        c_[2] = nct::UINT8_ESC * static_cast<unsigned char>((val >> 8) & 0xff);
        c_[3] = nct::UINT8_ESC * static_cast<unsigned char>((val) & 0xff);
    }
    else if (color.size() == 13) {
        c_[0] = nct::UINT16_ESC * static_cast<unsigned short>((val >> 32) & 0xffff);
        c_[1] = nct::UINT16_ESC * static_cast<unsigned short>((val >> 16) & 0xffff);
        c_[2] = nct::UINT16_ESC * static_cast<unsigned short>((val) & 0xffff);
        c_[3] = 1.0;
    }
    else if (color.size() == 17) {
        c_[0] = nct::UINT16_ESC * static_cast<unsigned short>((val >> 48) & 0xffff);
        c_[1] = nct::UINT16_ESC * static_cast<unsigned short>((val >> 32) & 0xffff);
        c_[2] = nct::UINT16_ESC * static_cast<unsigned short>((val >> 16) & 0xffff);
        c_[3] = nct::UINT16_ESC * static_cast<unsigned short>((val) & 0xffff);
    }
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void nct::color::Color::setRGBA(double r, double g, double b, double alpha)
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

    if ((alpha<0.0) || (alpha>1.0))
        throw ArgumentException("alpha", alpha, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    colorSpace_ = ColorSpace::RGBA;
    c_[0] = r;
    c_[1] = g;
    c_[2] = b;
    c_[3] = alpha;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::color::Color::setHSLA(double h, double s, double l, double alpha)
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

    if ((alpha<0.0) || (alpha>1.0))
        throw ArgumentException("alpha", alpha, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    colorSpace_ = ColorSpace::HSLA;
    c_[0] = h;
    c_[1] = s;
    c_[2] = l;
    c_[3] = alpha;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::color::Color::setHSVA(double h, double s, double v, double alpha)
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

    if ((alpha<0.0) || (alpha>1.0))
        throw ArgumentException("alpha", alpha, 0.0, 1.0,
        RelationalOperator::GreaterThanOrEqualTo, RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    colorSpace_ = ColorSpace::HSVA;
    c_[0] = h;
    c_[1] = s;
    c_[2] = v;
    c_[3] = alpha;
}

//-----------------------------------------------------------------------------------------------------------------
nct::color::Color nct::color::Color::convertTo(ColorSpace sp) const
{
    // No transformation is needed here.
    if (colorSpace_ == sp)
        return *this;

    // Verify output space.
    if ((sp != ColorSpace::RGBA) && (sp != ColorSpace::HSLA) && (sp != ColorSpace::HSVA))
        throw ArgumentException("sp", exc_bad_color_space, SOURCE_INFO);    

    // Transform to RGB before any other operation.
    if (colorSpace_ != ColorSpace::RGBA) {
        Color tmpc;
        tmpc.c_[3] = c_[3];
        switch (colorSpace_) {
            case ColorSpace::RGBA:
                // Do nothing. This condition is never reached.
                break;
            case ColorSpace::HSLA: {
                    if (c_[1] != 0) {
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

                        double q = c_[2] < 0.5 ? (c_[2] * (1 + c_[1])) : (c_[2] + c_[1] - c_[2] * c_[1]);
                        double p = 2 * c_[2] - q;
                        tmpc.c_[0] = hue2rgb(p, q, c_[0] + 1./3.);
                        tmpc.c_[1] = hue2rgb(p, q, c_[0]);
                        tmpc.c_[2] = hue2rgb(p, q, c_[0] - 1./3.);
                        
                    }
                    else {
                        // Achromatic.
                        tmpc.c_[0] = c_[2];
                        tmpc.c_[1] = c_[2];
                        tmpc.c_[2] = c_[2];
                    }
                    
                }

                break;

            case ColorSpace::HSVA: {
                    int i = static_cast<int>(std::floor(c_[0] * 6.0));
                    double f = c_[0] * 6.0 - i;
                    double p = c_[2] * (1.0 - c_[1]);
                    double q = c_[2] * (1.0 - f * c_[1]);
                    double t = c_[2] * (1.0 - (1.0 - f) * c_[1]);

                    switch (i % 6) {
                        case 0: 
                            tmpc.c_[0] = c_[2];
                            tmpc.c_[1] = t;
                            tmpc.c_[2] = p;
                            break;
                        case 1: 
                            tmpc.c_[0] = q;
                            tmpc.c_[1] = c_[2];
                            tmpc.c_[2] = p;
                            break;
                        case 2: 
                            tmpc.c_[0] = p;
                            tmpc.c_[1] = c_[2];
                            tmpc.c_[2] = t;
                            break;
                        case 3: 
                            tmpc.c_[0] = p;
                            tmpc.c_[1] = q;
                            tmpc.c_[2] = c_[2];
                            break;
                        case 4:
                            tmpc.c_[0] = t;
                            tmpc.c_[1] = p;
                            tmpc.c_[2] = c_[2];
                            break;
                        case 5: 
                            tmpc.c_[0] = c_[2];
                            tmpc.c_[1] = p;
                            tmpc.c_[2] = q;
                            break;
                    }                
                }
                break;
        }
        tmpc.c_[0] = minimum(maximum(0.0, tmpc.c_[0]), 1.0);
        tmpc.c_[1] = minimum(maximum(0.0, tmpc.c_[1]), 1.0);
        tmpc.c_[2] = minimum(maximum(0.0, tmpc.c_[2]), 1.0);
        return tmpc.convertTo(sp);
    }

    // Transform from RGB to the desired space.
    Color tmpc;
    tmpc.colorSpace_ = sp;
    tmpc.c_[3] = c_[3];
    switch (tmpc.colorSpace_) {
        case ColorSpace::RGBA:
            // This option is not needed, but is included just for style.
            tmpc = *this;
            break;
        case ColorSpace::HSLA: {
                auto max = maximum(maximum(c_[0], c_[1]), c_[2]);
                auto min = minimum(minimum(c_[0], c_[1]), c_[2]);
                tmpc.c_[2] = (max + min) / 2;

                if (max == min) {
                    // Achromatic.
                    tmpc.c_[0] = 0.0;
                    tmpc.c_[1] = 0.0;
                }
                else {
                    double d = max - min;
                    tmpc.c_[1] = (tmpc.c_[2] > 0.5) ? (d / (2 - max - min)) : (d / (max + min));
                    if (max == c_[0])
                        tmpc.c_[0] = (c_[1] - c_[2]) / d + ((c_[1] < c_[2]) ? 6.0 : 0.0);
                    else if (max == c_[1])
                        tmpc.c_[0] = (c_[2] - c_[0]) / d + 2.0;
                    else
                        tmpc.c_[0] = (c_[0] - c_[1]) / d + 4;                
                    tmpc.c_[0] /= 6.0;
                }
            }
            break;
        case ColorSpace::HSVA: {
                auto max = maximum(maximum(c_[0], c_[1]), c_[2]);
                auto min = minimum(minimum(c_[0], c_[1]), c_[2]);
                tmpc.c_[2] = max;

                double d = max - min;
                tmpc.c_[1] = (max == 0) ? 0 : d / max;

                if (max == min) {
                    // Achromatic.
                    tmpc.c_[0] = 0;
                }
                else {
                    if (max == c_[0])
                        tmpc.c_[0] = (c_[1] - c_[2]) / d + ((c_[1] < c_[2]) ? 6.0 : 0.0);
                    else if (max == c_[1])
                        tmpc.c_[0] = (c_[2] - c_[0]) / d + 2.0;
                    else
                        tmpc.c_[0] = (c_[0] - c_[1]) / d + 4;
                    tmpc.c_[0] /= 6.0;
                }
            }
            break;        
    }

    tmpc.c_[0] = minimum(maximum(0.0, tmpc.c_[0]), 1.0);
    tmpc.c_[1] = minimum(maximum(0.0, tmpc.c_[1]), 1.0);
    tmpc.c_[2] = minimum(maximum(0.0, tmpc.c_[2]), 1.0);
    return tmpc;
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::color::Color::hexString(bool ui8, bool addOpacity) const
{
    std::stringstream ss;

    if (addOpacity) {
        if (ui8) {
            auto num =
                static_cast<unsigned int>(opacity_UI8()) +
                static_cast<unsigned int>(component3_UI8()) * 0x100 +
                static_cast<unsigned int>(component2_UI8()) * 0x10000 +
                static_cast<unsigned int>(component1_UI8()) * 0x1000000;

            ss << "#" << std::hex << std::uppercase << std::setfill('0') << std::setw(8) << num;
        }
        else {
            auto num = 
                static_cast<unsigned long long>(opacity_UI16()) +
                static_cast<unsigned long long>(component3_UI16()) * 0x10000LL +
                static_cast<unsigned long long>(component2_UI16()) * 0x100000000LL +
                static_cast<unsigned long long>(component1_UI16()) * 0x1000000000000LL;

            ss << "#" << std::hex << std::uppercase << std::setfill('0') << std::setw(16) << num;
        }
    }
    else {
        if (ui8) {
            auto num = 
                static_cast<unsigned int>(component3_UI8()) +
                static_cast<unsigned int>(component2_UI8()) * 0x100 +
                static_cast<unsigned int>(component1_UI8()) * 0x10000;
            ss << "#" << std::hex << std::uppercase << std::setfill('0') << std::setw(6) << num;

        }
        else {
            auto num = 
                static_cast<unsigned long long>(component3_UI16()) +
                static_cast<unsigned long long>(component2_UI16()) * 0x10000LL +
                static_cast<unsigned long long>(component1_UI16()) * 0x100000000LL;
            ss << "#" << std::hex << std::uppercase << std::setfill('0') << std::setw(12) << num;
        }
    }

    return ss.str();
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::color::Color::rgbString() const
{
    std::stringstream ss;
    auto rgbColor = convertTo(ColorSpace::RGBA);

    ss << "rgb(" 
        << static_cast<unsigned int>(rgbColor.red_UI8()) << ","
        << static_cast<unsigned int>(rgbColor.green_UI8()) << ","
        << static_cast<unsigned int>(rgbColor.blue_UI8()) << ")";

    return ss.str();
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::color::Color::rgbaString() const
{
    std::stringstream ss;
    auto rgbColor = convertTo(ColorSpace::RGBA);

    ss << std::setprecision(3)
       << "rgba("
       << static_cast<unsigned int>(rgbColor.red_UI8()) << ","
       << static_cast<unsigned int>(rgbColor.green_UI8()) << ","
       << static_cast<unsigned int>(rgbColor.blue_UI8()) << ","
       << rgbColor.opacity() << ")";

    return ss.str();
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::color::Color::hslString() const
{
    std::stringstream ss;
    auto hslColor = convertTo(ColorSpace::HSLA);

    ss << std::setprecision(3)
        << "hsl("
        << static_cast<unsigned int>(hslColor.hue() * 360) << ","
        << static_cast<unsigned int>(hslColor.saturationHSL() * 100) << "%,"
        << static_cast<unsigned int>(hslColor.lightness() * 100) << "%)";

    return ss.str();
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::color::Color::hslaString() const
{
    std::stringstream ss;
    auto hslColor = convertTo(ColorSpace::HSLA);

    ss << std::setprecision(3)
        << "hsla("
        << static_cast<unsigned int>(hslColor.hue() * 360) << ","
        << static_cast<unsigned int>(hslColor.saturationHSL() * 100) << "%,"
        << static_cast<unsigned int>(hslColor.lightness() * 100) << "%,"
        << hslColor.opacity() << ")";

    return ss.str();
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::color::Color::hsvString() const
{
    std::stringstream ss;
    auto hsvColor = convertTo(ColorSpace::HSVA);

    ss << std::setprecision(3)
        << "hsv("
        << static_cast<unsigned int>(hsvColor.hue() * 360) << ","
        << static_cast<unsigned int>(hsvColor.saturationHSV() * 100) << "%,"
        << static_cast<unsigned int>(hsvColor.brightness() * 100) << "%)";

    return ss.str();
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::color::Color::hsvaString() const
{
    std::stringstream ss;
    auto hsvColor = convertTo(ColorSpace::HSVA);

    ss << std::setprecision(3)
        << "hsva("
        << static_cast<unsigned int>(hsvColor.hue() * 360) << ","
        << static_cast<unsigned int>(hsvColor.saturationHSV() * 100) << "%,"
        << static_cast<unsigned int>(hsvColor.brightness() * 100) << "%,"
        << hsvColor.opacity() << ")";

    return ss.str();
}

//-----------------------------------------------------------------------------------------------------------------
std::vector<nct::color::Color::ColorName> nct::color::Color::colors()
{
    std::vector<ColorName> col(140);
    for (index_t i = 0; i < col.size(); i++)
        col[i] = static_cast<ColorName>(i);    
    return col;
}

//-----------------------------------------------------------------------------------------------------------------
std::vector<std::string> nct::color::Color::colorNames()
{
    std::vector<std::string> col(140);

    col[static_cast<size_t>(ColorName::AliceBlue)] = "Alice blue";
    col[static_cast<size_t>(ColorName::AntiqueWhite)] = "Antique white";
    col[static_cast<size_t>(ColorName::Aqua)] = "Aqua";
    col[static_cast<size_t>(ColorName::Aquamarine)] = "Aquamarine";
    col[static_cast<size_t>(ColorName::Azure)] = "Azure";
    col[static_cast<size_t>(ColorName::Beige)] = "Beige";
    col[static_cast<size_t>(ColorName::Bisque)] = "Bisque";
    col[static_cast<size_t>(ColorName::Black)] = "Black";
    col[static_cast<size_t>(ColorName::BlanchedAlmond)] = "Blanched almond";
    col[static_cast<size_t>(ColorName::Blue)] = "Blue";
    col[static_cast<size_t>(ColorName::BlueViolet)] = "Blue violet";
    col[static_cast<size_t>(ColorName::Brown)] = "Brown";
    col[static_cast<size_t>(ColorName::BurlyWood)] = "Burly wood";
    col[static_cast<size_t>(ColorName::CadetBlue)] = "Cadet blue";
    col[static_cast<size_t>(ColorName::Chartreuse)] = "Chartreuse";
    col[static_cast<size_t>(ColorName::Chocolate)] = "Chocolate";
    col[static_cast<size_t>(ColorName::Coral)] = "Coral";
    col[static_cast<size_t>(ColorName::CornflowerBlue)] = "Cornflower blue";
    col[static_cast<size_t>(ColorName::Cornsilk)] = "Cornsilk";
    col[static_cast<size_t>(ColorName::Crimson)] = "Crimson";
    col[static_cast<size_t>(ColorName::Cyan)] = "Cyan";
    col[static_cast<size_t>(ColorName::DarkBlue)] = "Dark blue";
    col[static_cast<size_t>(ColorName::DarkCyan)] = "Dark cyan";
    col[static_cast<size_t>(ColorName::DarkGoldenRod)] = "Dark golden rod";
    col[static_cast<size_t>(ColorName::DarkGray)] = "Dark gray";
    col[static_cast<size_t>(ColorName::DarkGreen)] = "Dark green";
    col[static_cast<size_t>(ColorName::DarkKhaki)] = "Dark khaki";
    col[static_cast<size_t>(ColorName::DarkMagenta)] = "Dark magenta";
    col[static_cast<size_t>(ColorName::DarkOliveGreen)] = "Dark olive green";
    col[static_cast<size_t>(ColorName::DarkOrange)] = "Dark orange";
    col[static_cast<size_t>(ColorName::DarkOrchid)] = "Dark orchid";
    col[static_cast<size_t>(ColorName::DarkRed)] = "Dark red";
    col[static_cast<size_t>(ColorName::DarkSalmon)] = "Dark salmon";
    col[static_cast<size_t>(ColorName::DarkSeaGreen)] = "Dark sea green";
    col[static_cast<size_t>(ColorName::DarkSlateBlue)] = "Dark slate blue";
    col[static_cast<size_t>(ColorName::DarkSlateGray)] = "Dark slate gray";
    col[static_cast<size_t>(ColorName::DarkTurquoise)] = "Dark turquoise";
    col[static_cast<size_t>(ColorName::DarkViolet)] = "Dark violet";
    col[static_cast<size_t>(ColorName::DeepPink)] = "Deep pink";
    col[static_cast<size_t>(ColorName::DeepSkyBlue)] = "Deep sky blue";
    col[static_cast<size_t>(ColorName::DimGray)] = "Dim gray";
    col[static_cast<size_t>(ColorName::DodgerBlue)] = "Dodger blue";
    col[static_cast<size_t>(ColorName::FireBrick)] = "Fire brick";
    col[static_cast<size_t>(ColorName::FloralWhite)] = "Floral white";
    col[static_cast<size_t>(ColorName::ForestGreen)] = "Forest green";
    col[static_cast<size_t>(ColorName::Fuchsia)] = "Fuchsia";
    col[static_cast<size_t>(ColorName::Gainsboro)] = "Gainsboro";
    col[static_cast<size_t>(ColorName::GhostWhite)] = "GhostWhite";
    col[static_cast<size_t>(ColorName::Gold)] = "Gold";
    col[static_cast<size_t>(ColorName::GoldenRod)] = "Golden rod";
    col[static_cast<size_t>(ColorName::Gray)] = "Gray";
    col[static_cast<size_t>(ColorName::Green)] = "Green";
    col[static_cast<size_t>(ColorName::GreenYellow)] = "Green yellow";
    col[static_cast<size_t>(ColorName::HoneyDew)] = "Honey dew";
    col[static_cast<size_t>(ColorName::HotPink)] = "Hot pink";
    col[static_cast<size_t>(ColorName::IndianRed)] = "Indian red";
    col[static_cast<size_t>(ColorName::Indigo)] = "Indigo";
    col[static_cast<size_t>(ColorName::Ivory)] = "Ivory";
    col[static_cast<size_t>(ColorName::Khaki)] = "Khaki";
    col[static_cast<size_t>(ColorName::Lavender)] = "Lavender";
    col[static_cast<size_t>(ColorName::LavenderBlush)] = "Lavender blush";
    col[static_cast<size_t>(ColorName::LawnGreen)] = "Lawn green";
    col[static_cast<size_t>(ColorName::LemonChiffon)] = "Lemon chiffon";
    col[static_cast<size_t>(ColorName::LightBlue)] = "Light blue";
    col[static_cast<size_t>(ColorName::LightCoral)] = "Light coral";
    col[static_cast<size_t>(ColorName::LightCyan)] = "Light cyan";
    col[static_cast<size_t>(ColorName::LightGoldenRodYellow)] = "Light golden rod yellow";
    col[static_cast<size_t>(ColorName::LightGray)] = "Light gray";
    col[static_cast<size_t>(ColorName::LightGreen)] = "Light green";
    col[static_cast<size_t>(ColorName::LightPink)] = "Light pink";
    col[static_cast<size_t>(ColorName::LightSalmon)] = "Light salmon";
    col[static_cast<size_t>(ColorName::LightSeaGreen)] = "Light sea green";
    col[static_cast<size_t>(ColorName::LightSkyBlue)] = "Light sky blue";
    col[static_cast<size_t>(ColorName::LightSlateGray)] = "Light slate gray";
    col[static_cast<size_t>(ColorName::LightSteelBlue)] = "Light steel blue";
    col[static_cast<size_t>(ColorName::LightYellow)] = "Light yellow";
    col[static_cast<size_t>(ColorName::Lime)] = "Lime";
    col[static_cast<size_t>(ColorName::LimeGreen)] = "Lime green";
    col[static_cast<size_t>(ColorName::Linen)] = "Linen";
    col[static_cast<size_t>(ColorName::Magenta)] = "Magenta";
    col[static_cast<size_t>(ColorName::Maroon)] = "Maroon";
    col[static_cast<size_t>(ColorName::MediumAquaMarine)] = "Medium aqua marine";
    col[static_cast<size_t>(ColorName::MediumBlue)] = "Medium blue";
    col[static_cast<size_t>(ColorName::MediumOrchid)] = "Medium orchid";
    col[static_cast<size_t>(ColorName::MediumPurple)] = "Medium purple";
    col[static_cast<size_t>(ColorName::MediumSeaGreen)] = "Medium sea green";
    col[static_cast<size_t>(ColorName::MediumSlateBlue)] = "Medium slate blue";
    col[static_cast<size_t>(ColorName::MediumSpringGreen)] = "Medium spring green";
    col[static_cast<size_t>(ColorName::MediumTurquoise)] = "Medium turquoise";
    col[static_cast<size_t>(ColorName::MediumVioletRed)] = "Medium violet red";
    col[static_cast<size_t>(ColorName::MidnightBlue)] = "Midnight blue";
    col[static_cast<size_t>(ColorName::MintCream)] = "Mint cream";
    col[static_cast<size_t>(ColorName::MistyRose)] = "Misty rose";
    col[static_cast<size_t>(ColorName::Moccasin)] = "Moccasin";
    col[static_cast<size_t>(ColorName::NavajoWhite)] = "Navajo white";
    col[static_cast<size_t>(ColorName::Navy)] = "Navy";
    col[static_cast<size_t>(ColorName::OldLace)] = "Old lace";
    col[static_cast<size_t>(ColorName::Olive)] = "Olive";
    col[static_cast<size_t>(ColorName::OliveDrab)] = "Olive drab";
    col[static_cast<size_t>(ColorName::Orange)] = "Orange";
    col[static_cast<size_t>(ColorName::OrangeRed)] = "Orange red";
    col[static_cast<size_t>(ColorName::Orchid)] = "Orchid";
    col[static_cast<size_t>(ColorName::PaleGoldenRod)] = "Pale golden rod";
    col[static_cast<size_t>(ColorName::PaleGreen)] = "Pale green";
    col[static_cast<size_t>(ColorName::PaleTurquoise)] = "Pale turquoise";
    col[static_cast<size_t>(ColorName::PaleVioletRed)] = "Pale violet red";
    col[static_cast<size_t>(ColorName::PapayaWhip)] = "Papaya whip";
    col[static_cast<size_t>(ColorName::PeachPuff)] = "Peach puff";
    col[static_cast<size_t>(ColorName::Peru)] = "Peru";
    col[static_cast<size_t>(ColorName::Pink)] = "Pink";
    col[static_cast<size_t>(ColorName::Plum)] = "Plum";
    col[static_cast<size_t>(ColorName::PowderBlue)] = "Powder blue";
    col[static_cast<size_t>(ColorName::Purple)] = "Purple";
    col[static_cast<size_t>(ColorName::Red)] = "Red";
    col[static_cast<size_t>(ColorName::RosyBrown)] = "Rosy brown";
    col[static_cast<size_t>(ColorName::RoyalBlue)] = "Royal blue";
    col[static_cast<size_t>(ColorName::SaddleBrown)] = "Saddle brown";
    col[static_cast<size_t>(ColorName::Salmon)] = "Salmon";
    col[static_cast<size_t>(ColorName::SandyBrown)] = "Sandy brown";
    col[static_cast<size_t>(ColorName::SeaGreen)] = "Sea green";
    col[static_cast<size_t>(ColorName::SeaShell)] = "Sea shell";
    col[static_cast<size_t>(ColorName::Sienna)] = "Sienna";
    col[static_cast<size_t>(ColorName::Silver)] = "Silver";
    col[static_cast<size_t>(ColorName::SkyBlue)] = "Sky blue";
    col[static_cast<size_t>(ColorName::SlateBlue)] = "Slate blue";
    col[static_cast<size_t>(ColorName::SlateGray)] = "Slate gray";
    col[static_cast<size_t>(ColorName::Snow)] = "Snow";
    col[static_cast<size_t>(ColorName::SpringGreen)] = "Spring green";
    col[static_cast<size_t>(ColorName::SteelBlue)] = "Steel blue";
    col[static_cast<size_t>(ColorName::Tan)] = "Tan";
    col[static_cast<size_t>(ColorName::Teal)] = "Teal";
    col[static_cast<size_t>(ColorName::Thistle)] = "Thistle";
    col[static_cast<size_t>(ColorName::Tomato)] = "Tomato";
    col[static_cast<size_t>(ColorName::Turquoise)] = "Turquoise";
    col[static_cast<size_t>(ColorName::Violet)] = "Violet";
    col[static_cast<size_t>(ColorName::Wheat)] = "Wheat";
    col[static_cast<size_t>(ColorName::White)] = "White";
    col[static_cast<size_t>(ColorName::WhiteSmoke)] = "White smoke";
    col[static_cast<size_t>(ColorName::Yellow)] = "Yellow";
    col[static_cast<size_t>(ColorName::YellowGreen)] = "Yellow green";
    
    return col;
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::color::Color::colorString(ColorName color)
{
    std::string col;

    switch (color) {
        case ColorName::AliceBlue:
            col = "#F0F8FF";
            break;
        case ColorName::AntiqueWhite:    
            col = "#FAEBD7"; 
            break;
        case ColorName::Aqua:    
            col = "#00FFFF"; 
            break;
        case ColorName::Aquamarine:    
            col = "#7FFFD4"; 
            break;
        case ColorName::Azure:    
            col = "#F0FFFF";
            break;
        case ColorName::Beige:    
            col = "#F5F5DC"; 
            break;
        case ColorName::Bisque:
            col = "#FFE4C4";
            break;
        case ColorName::Black:    
            col = "#000000"; 
            break;
        case ColorName::BlanchedAlmond:    
            col = "#FFEBCD";
            break;
        case ColorName::Blue:    
            col = "#0000FF"; 
            break;
        case ColorName::BlueViolet:    
            col = "#8A2BE2";
            break;
        case ColorName::Brown:    
            col = "#A52A2A"; 
            break;
        case ColorName::BurlyWood:
            col = "#DEB887"; 
            break;
        case ColorName::CadetBlue:    
            col = "#5F9EA0";
            break;
        case ColorName::Chartreuse:    
            col = "#7FFF00";
            break;
        case ColorName::Chocolate:    
            col = "#D2691E"; 
            break;
        case ColorName::Coral:    
            col = "#FF7F50";
            break;
        case ColorName::CornflowerBlue:    
            col = "#6495ED";
            break;
        case ColorName::Cornsilk:    
            col = "#FFF8DC"; 
            break;
        case ColorName::Crimson:    
            col = "#DC143C"; 
            break;
        case ColorName::Cyan:    
            col = "#00FFFF"; 
            break;
        case ColorName::DarkBlue:    
            col = "#00008B"; 
            break;
        case ColorName::DarkCyan:    
            col = "#008B8B";
            break;
        case ColorName::DarkGoldenRod:    
            col = "#B8860B";
            break;
        case ColorName::DarkGray:    
            col = "#A9A9A9"; 
            break;
        case ColorName::DarkGreen:    
            col = "#006400"; 
            break;
        case ColorName::DarkKhaki:    
            col = "#BDB76B"; 
            break;
        case ColorName::DarkMagenta:    
            col = "#8B008B";
            break;
        case ColorName::DarkOliveGreen:    
            col = "#556B2F"; 
            break;
        case ColorName::DarkOrange:    
            col = "#FF8C00";
            break;
        case ColorName::DarkOrchid:    
            col = "#9932CC";
            break;
        case ColorName::DarkRed:    
            col = "#8B0000";
            break;
        case ColorName::DarkSalmon:    
            col = "#E9967A";
            break;
        case ColorName::DarkSeaGreen:    
            col = "#8FBC8F";
            break;
        case ColorName::DarkSlateBlue:    
            col = "#483D8B"; 
            break;
        case ColorName::DarkSlateGray:    
            col = "#2F4F4F"; 
            break;
        case ColorName::DarkTurquoise:    
            col = "#00CED1"; 
            break;
        case ColorName::DarkViolet:    
            col = "#9400D3";
            break;
        case ColorName::DeepPink:    
            col = "#FF1493"; 
            break;
        case ColorName::DeepSkyBlue:    
            col = "#00BFFF"; 
            break;
        case ColorName::DimGray:    
            col = "#696969"; 
            break;
        case ColorName::DodgerBlue:    
            col = "#1E90FF";
            break;
        case ColorName::FireBrick:    
            col = "#B22222"; 
            break;
        case ColorName::FloralWhite:    
            col = "#FFFAF0";
            break;
        case ColorName::ForestGreen:
            col = "#228B22";
            break;
        case ColorName::Fuchsia:    
            col = "#FF00FF"; 
            break;
        case ColorName::Gainsboro:    
            col = "#DCDCDC";
            break;
        case ColorName::GhostWhite:
            col = "#F8F8FF";
            break;
        case ColorName::Gold:    
            col = "#FFD700";
            break;
        case ColorName::GoldenRod:
            col = "#DAA520";
            break;
        case ColorName::Gray:    
            col = "#808080";
            break;
        case ColorName::Green:
            col = "#008000";
            break;
        case ColorName::GreenYellow:    
            col = "#ADFF2F"; 
            break;
        case ColorName::HoneyDew:    
            col = "#F0FFF0"; 
            break;
        case ColorName::HotPink:    
            col = "#FF69B4"; 
            break;
        case ColorName::IndianRed:
            col = "#CD5C5C";
            break;
        case ColorName::Indigo:
            col = "#4B0082"; 
            break;
        case ColorName::Ivory:    
            col = "#FFFFF0";
            break;
        case ColorName::Khaki:
            col = "#F0E68C";
            break;
        case ColorName::Lavender:    
            col = "#E6E6FA";
            break;
        case ColorName::LavenderBlush:    
            col = "#FFF0F5";
            break;
        case ColorName::LawnGreen:    
            col = "#7CFC00";
            break;
        case ColorName::LemonChiffon:    
            col = "#FFFACD";
            break;
        case ColorName::LightBlue:    
            col = "#ADD8E6";
            break;
        case ColorName::LightCoral:    
            col = "#F08080"; 
            break;
        case ColorName::LightCyan:    
            col = "#E0FFFF";
            break;
        case ColorName::LightGoldenRodYellow:    
            col = "#FAFAD2";
            break;
        case ColorName::LightGray:    
            col = "#D3D3D3";
            break;
        case ColorName::LightGreen:    
            col = "#90EE90";
            break;
        case ColorName::LightPink:    
            col = "#FFB6C1";
            break;
        case ColorName::LightSalmon:    
            col = "#FFA07A";
            break;
        case ColorName::LightSeaGreen:    
            col = "#20B2AA"; 
            break;
        case ColorName::LightSkyBlue:    
            col = "#87CEFA"; 
            break;
        case ColorName::LightSlateGray:
            col = "#778899";
            break;
        case ColorName::LightSteelBlue:
            col = "#B0C4DE";
            break;
        case ColorName::LightYellow:    
            col = "#FFFFE0";
            break;
        case ColorName::Lime:    
            col = "#00FF00";
            break;
        case ColorName::LimeGreen:    
            col = "#32CD32"; 
            break;
        case ColorName::Linen:
            col = "#FAF0E6"; 
            break;
        case ColorName::Magenta:    
            col = "#FF00FF";
            break;
        case ColorName::Maroon:
            col = "#800000";
            break;
        case ColorName::MediumAquaMarine:    
            col = "#66CDAA"; 
            break;
        case ColorName::MediumBlue:    
            col = "#0000CD"; 
            break;
        case ColorName::MediumOrchid:    
            col = "#BA55D3";
            break;
        case ColorName::MediumPurple:    
            col = "#9370DB"; 
            break;
        case ColorName::MediumSeaGreen:
            col = "#3CB371"; 
            break;
        case ColorName::MediumSlateBlue:    
            col = "#7B68EE";
            break;
        case ColorName::MediumSpringGreen:    
            col = "#00FA9A"; 
            break;
        case ColorName::MediumTurquoise:    
            col = "#48D1CC"; 
            break;
        case ColorName::MediumVioletRed:
            col = "#C71585"; 
            break;
        case ColorName::MidnightBlue:    
            col = "#191970";
            break;
        case ColorName::MintCream:    
            col = "#F5FFFA"; 
            break;
        case ColorName::MistyRose:
            col = "#FFE4E1"; 
            break;
        case ColorName::Moccasin:
            col = "#FFE4B5";
            break;
        case ColorName::NavajoWhite:    
            col = "#FFDEAD"; 
            break;
        case ColorName::Navy:    
            col = "#000080"; 
            break;
        case ColorName::OldLace:
            col = "#FDF5E6"; 
            break;
        case ColorName::Olive:    
            col = "#808000";
            break;
        case ColorName::OliveDrab:    
            col = "#6B8E23";
            break;
        case ColorName::Orange:    
            col = "#FFA500";
            break;
        case ColorName::OrangeRed:    
            col = "#FF4500";
            break;
        case ColorName::Orchid:
            col = "#DA70D6";
            break;
        case ColorName::PaleGoldenRod:    
            col = "#EEE8AA"; 
            break;
        case ColorName::PaleGreen:    
            col = "#98FB98";
            break;
        case ColorName::PaleTurquoise:    
            col = "#AFEEEE";
            break;
        case ColorName::PaleVioletRed:    
            col = "#DB7093";
            break;
        case ColorName::PapayaWhip:
            col = "#FFEFD5";
            break;
        case ColorName::PeachPuff:    
            col = "#FFDAB9";
            break;
        case ColorName::Peru:    
            col = "#CD853F";
            break;
        case ColorName::Pink:    
            col = "#FFC0CB";
            break;
        case ColorName::Plum:
            col = "#DDA0DD";
            break;
        case ColorName::PowderBlue:    
            col = "#B0E0E6"; 
            break;
        case ColorName::Purple:
            col = "#800080";
            break;
        case ColorName::Red:    
            col = "#FF0000";
            break;
        case ColorName::RosyBrown:    
            col = "#BC8F8F"; 
            break;
        case ColorName::RoyalBlue:    
            col = "#4169E1";
            break;
        case ColorName::SaddleBrown:
            col = "#8B4513"; 
            break;
        case ColorName::Salmon:
            col = "#FA8072";
            break;
        case ColorName::SandyBrown:
            col = "#F4A460";
            break;
        case ColorName::SeaGreen:    
            col = "#2E8B57"; 
            break;
        case ColorName::SeaShell:
            col = "#FFF5EE"; 
            break;
        case ColorName::Sienna:    
            col = "#A0522D";
            break;
        case ColorName::Silver:    
            col = "#C0C0C0";
            break;
        case ColorName::SkyBlue:    
            col = "#87CEEB";
            break;
        case ColorName::SlateBlue:
            col = "#6A5ACD";
            break;
        case ColorName::SlateGray:
            col = "#708090"; 
            break;
        case ColorName::Snow:    
            col = "#FFFAFA";
            break;
        case ColorName::SpringGreen:
            col = "#00FF7F";
            break;
        case ColorName::SteelBlue:
            col = "#4682B4";
            break;
        case ColorName::Tan:    
            col = "#D2B48C";
            break;
        case ColorName::Teal:    
            col = "#008080"; 
            break;
        case ColorName::Thistle:    
            col = "#D8BFD8"; 
            break;
        case ColorName::Tomato:    
            col = "#FF6347"; 
            break;
        case ColorName::Turquoise:    
            col = "#40E0D0";
            break;
        case ColorName::Violet:
            col = "#EE82EE";
            break;
        case ColorName::Wheat:
            col = "#F5DEB3";
            break;
        case ColorName::White:
            col = "#FFFFFF";
            break;
        case ColorName::WhiteSmoke:
            col = "#F5F5F5";
            break;
        case ColorName::Yellow:
            col = "#FFFF00";
            break;
        case ColorName::YellowGreen:
            col = "#9ACD32"; 
            break;
        default:
            throw ArgumentException("color", exc_bad_color, SOURCE_INFO);
    }

    return col;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
