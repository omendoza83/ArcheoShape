//=================================================================================================================
/**
 *  @file       Color.h
 *  @brief      nct::color::Color class.
 *  @details    Declaration file of the nct::color::Color class.
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

#ifndef NCT_COLOR_H_INCLUDE
#define NCT_COLOR_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_constants.h>
#include <nct/nct_exception.h>

#include <string>
#include <vector>

//=================================================================================================================
namespace nct {
/**
 *  @brief      Color namespace.
 *  @details    This namespace contains classes that are used to define and manipulate colors 
 *              in different spaces. 
 */
namespace color {

/**
 *  @brief      Multi-space color class.
 *  @details    This class is used to represent colors in RGBA, HSLA and HSVA spaces. Internally, each
 *              component is stored in double precision format in the range [0, 1] regardless the
 *              color space. Values are set using this range. If a color space uses a different range,
 *              values must be scaled in this range before set any element. The parameters can be
 *              specified in 8-bit and 16-bit integer formats. For 8-bit integers, the full range
 *              is represented by numbers from 0 to 255, while the range [0 65535] is used for 16-bit
 *              integers.
 *              Four components are used in this class. Three represent the color space and the
 *              other one the opacity.
 *              Use this class if it is needed to represent one color in different spaces. If one
 *              function or class only supports one kind of color, use the respective class that
 *              implements the specific color space instead.
 */
class NCT_EXPIMP Color final {

public:

    ////////// Enumerations //////////

    /**
     *  @brief      Color spaces.
     *  @details    Color spaces that can be represented by the color class.
     */
    enum class ColorSpace : unsigned char {

        RGBA,   /**< Red-Green-Blue-Alpha.*/

        HSLA,   /**< Hue-Saturation-Lightness-Alpha */

        HSVA,   /**< Hue-Saturation-Brightness-Alpha.*/
    };

    /**
     *  @brief      Default colors.
     *  @details    Different pre-defined colors recognized by this library.
     */
    enum class ColorName : unsigned char {

        AliceBlue,              /**< Alice blue. */
        AntiqueWhite,           /**< Antique white. */
        Aqua,                   /**< Aqua. */
        Aquamarine,             /**< Aquamarine. */
        Azure,                  /**< Azure. */
        Beige,                  /**< Beige. */
        Bisque,                 /**< Bisque. */
        Black,                  /**< Black. */
        BlanchedAlmond,         /**< Blanched almond. */
        Blue,                   /**< Blue. */
        BlueViolet,             /**< Blue violet. */
        Brown,                  /**< Brown. */
        BurlyWood,              /**< Burly wood. */
        CadetBlue,              /**< Cadet blue. */
        Chartreuse,             /**< Chartreuse. */
        Chocolate,              /**< Chocolate. */
        Coral,                  /**< Coral. */
        CornflowerBlue,         /**< Cornflower blue. */
        Cornsilk,               /**< Cornsilk. */
        Crimson,                /**< Crimson. */
        Cyan,                   /**< Cyan. */
        DarkBlue,               /**< Dark blue. */
        DarkCyan,               /**< Dark cyan. */
        DarkGoldenRod,          /**< Dark golden rod. */
        DarkGray,               /**< Dark gray. */
        DarkGreen,              /**< Dark green. */
        DarkKhaki,              /**< Dark khaki. */
        DarkMagenta,            /**< Dark magenta. */
        DarkOliveGreen,         /**< Dark olive green. */
        DarkOrange,             /**< Dark orange. */
        DarkOrchid,             /**< Dark orchid. */
        DarkRed,                /**< Dark red. */
        DarkSalmon,             /**< Dark salmon. */
        DarkSeaGreen,           /**< Dark sea green. */
        DarkSlateBlue,          /**< Dark slate blue. */
        DarkSlateGray,          /**< Dark slate gray. */
        DarkTurquoise,          /**< Dark turquoise. */
        DarkViolet,             /**< Dark violet. */
        DeepPink,               /**< Deep pink. */
        DeepSkyBlue,            /**< Deep sky blue. */
        DimGray,                /**< Dim gray. */
        DodgerBlue,             /**< Dodger blue. */
        FireBrick,              /**< Fire brick. */
        FloralWhite,            /**< Floral white. */
        ForestGreen,            /**< Forest green. */
        Fuchsia,                /**< Fuchsia. */
        Gainsboro,              /**< Gainsboro. */
        GhostWhite,             /**< GhostWhite. */
        Gold,                   /**< Gold. */
        GoldenRod,              /**< Golden rod. */
        Gray,                   /**< Gray. */
        Green,                  /**< Green. */
        GreenYellow,            /**< Green yellow. */
        HoneyDew,               /**< Honey dew. */
        HotPink,                /**< Hot pink. */
        IndianRed,              /**< Indian red. */
        Indigo,                 /**< Indigo. */
        Ivory,                  /**< Ivory. */
        Khaki,                  /**< Khaki. */
        Lavender,               /**< Lavender. */
        LavenderBlush,          /**< Lavender blush. */
        LawnGreen,              /**< Lawn green. */
        LemonChiffon,           /**< Lemon chiffon. */
        LightBlue,              /**< Light blue. */
        LightCoral,             /**< Light coral. */
        LightCyan,              /**< Light cyan. */
        LightGoldenRodYellow,   /**< Light golden rod yellow. */
        LightGray,              /**< Light gray. */
        LightGreen,             /**< Light green. */
        LightPink,              /**< Light pink. */
        LightSalmon,            /**< Light salmon. */
        LightSeaGreen,          /**< Light sea green. */
        LightSkyBlue,           /**< Light sky blue. */
        LightSlateGray,         /**< Light slate gray. */
        LightSteelBlue,         /**< Light steel blue. */
        LightYellow,            /**< Light yellow. */
        Lime,                   /**< Lime. */
        LimeGreen,              /**< Lime green. */
        Linen,                  /**< Linen. */
        Magenta,                /**< Magenta. */
        Maroon,                 /**< Maroon. */
        MediumAquaMarine,       /**< Medium aqua marine. */
        MediumBlue,             /**< Medium blue. */
        MediumOrchid,           /**< Medium orchid. */
        MediumPurple,           /**< Medium purple. */
        MediumSeaGreen,         /**< Medium sea green. */
        MediumSlateBlue,        /**< Medium slate blue. */
        MediumSpringGreen,      /**< Medium spring green. */
        MediumTurquoise,        /**< Medium turquoise. */
        MediumVioletRed,        /**< Medium violet red. */
        MidnightBlue,           /**< Midnight blue. */
        MintCream,              /**< Mint cream. */
        MistyRose,              /**< Misty rose. */
        Moccasin,               /**< Moccasin. */
        NavajoWhite,            /**< Navajo white. */
        Navy,                   /**< Navy. */
        OldLace,                /**< Old lace. */
        Olive,                  /**< Olive. */
        OliveDrab,              /**< Olive drab. */
        Orange,                 /**< Orange. */
        OrangeRed,              /**< Orange red. */
        Orchid,                 /**< Orchid. */
        PaleGoldenRod,          /**< Pale golden rod. */
        PaleGreen,              /**< Pale green. */
        PaleTurquoise,          /**< Pale turquoise. */
        PaleVioletRed,          /**< Pale violet red. */
        PapayaWhip,             /**< Papaya whip. */
        PeachPuff,              /**< Peach puff. */
        Peru,                   /**< Peru. */
        Pink,                   /**< Pink. */
        Plum,                   /**< Plum. */
        PowderBlue,             /**< Powder blue. */
        Purple,                 /**< Purple. */
        Red,                    /**< Red. */
        RosyBrown,              /**< Rosy brown. */
        RoyalBlue,              /**< Royal blue. */
        SaddleBrown,            /**< Saddle brown. */
        Salmon,                 /**< Salmon. */
        SandyBrown,             /**< Sandy brown. */
        SeaGreen,               /**< Sea green. */
        SeaShell,               /**< Sea shell. */
        Sienna,                 /**< Sienna. */
        Silver,                 /**< Silver. */
        SkyBlue,                /**< Sky blue. */
        SlateBlue,              /**< Slate blue. */
        SlateGray,              /**< Slate gray. */
        Snow,                   /**< Snow. */
        SpringGreen,            /**< Spring green. */
        SteelBlue,              /**< Steel blue. */
        Tan,                    /**< Tan. */
        Teal,                   /**< Teal. */
        Thistle,                /**< Thistle. */
        Tomato,                 /**< Tomato. */
        Turquoise,              /**< Turquoise. */
        Violet,                 /**< Violet. */
        Wheat,                  /**< Wheat. */
        White,                  /**< White. */
        WhiteSmoke,             /**< White smoke. */
        Yellow,                 /**< Yellow. */
        YellowGreen,            /**< Yellow green. */
    };

    ////////// Constructors //////////
    
    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the default configuration. 
     *              It builds a color whose components are set to zero except the alpha channel.
     */
    constexpr Color() noexcept = default;

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes the color and sets all its components according to 
     *              the specified input parameters. The values are specified as real numbers in the 
     *              range between 0 and 1.
     *  @param[in]  comp1  The value of the first component.
     *  @param[in]  comp2  The value of the second component.
     *  @param[in]  comp3  The value of the third component.
     *  @param[in]  alpha  The value of the color opacity.
     *  @param[in]  sp  The color space.
     */
    constexpr Color(double comp1, double comp2, double comp3, double alpha = 1.0,
        ColorSpace sp = ColorSpace::RGBA);

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes the color and sets all its components according to 
     *              the specified input parameters. The input arguments are specified as 8-bit integers.
     *  @param[in]  comp1  The value of the first component.
     *  @param[in]  comp2  The value of the second component.
     *  @param[in]  comp3  The value of the third component.
     *  @param[in]  alpha  The value of the color opacity.
     *  @param[in]  sp  The color space.
     */
    constexpr Color(unsigned char comp1, unsigned char comp2, unsigned char comp3,
        unsigned char alpha = UINT8_MAX, ColorSpace sp = ColorSpace::RGBA);

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes the color and sets all its components according to 
     *              the specified input parameters. The input arguments are specified as 16-bit integers.
     *  @param[in]  comp1  The value of the first component.
     *  @param[in]  comp2  The value of the second component.
     *  @param[in]  comp3  The value of the third component.
     *  @param[in]  alpha  The value of the color opacity.
     *  @param[in]  sp  The color space.
     */
    constexpr Color(unsigned short comp1, unsigned short comp2, unsigned short comp3,
        unsigned short alpha = UINT16_MAX, ColorSpace sp = ColorSpace::RGBA);
    
    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes the color and sets all its components according to
     *              the specified pre-defined color.
     *  @param[in]  color  The pre-defined color.
     *  @param[in]  sp  The color space.
     */
    Color(ColorName color, ColorSpace sp = ColorSpace::RGBA);

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes the color and sets all its components according to 
     *              the specified hexadecimal string.
     *  @param[in]  color  The color components in hexadecimal string.
     *  @param[in]  sp  The color space.
     */
    Color(const std::string& color, ColorSpace sp = ColorSpace::RGBA);    

    ////////// Operators //////////

    /**
     *  @brief      Equality operator.
     *  @details    Two colors are equal if both have the same components and opacity. If the
     *              colors are specified in different spaces, both are transformed into their 
     *              RGB representation and then they are compared.
     *  @param[in]  right  Color on the right side of the operation.
     *  @returns    True if both colors are the same.
     */
    constexpr bool operator==(const Color& right) const noexcept;

    /**
     *  @brief      Inequality operator.
     *  @details    Two colors are not equal if they have at least one component different. If the
     *              colors are specified in different spaces, both are transformed into their 
     *              RGB representation and then they are compared.
     *  @param[in]  right  Color on the right side of the operation.
     *  @returns    True if both colors are not the same.
     */
    constexpr bool operator!=(const Color& right) const noexcept;

    /**
     *  @brief      Color component.
     *  @details    This operator returns the specified color component.
     *  @param[in]  i  Component index (0, 1, 2 or 3).
     *  @returns    The selected color component.
     */
    constexpr double operator[](size_t i) const;

    ////////// Member functions //////////       

    /**
     *  @brief      Set RBGA color.
     *  @details    This function modifies the current color and sets the color space to RGBA.
     *  @param[in]  r  The value of the red component.
     *  @param[in]  g  The value of the green component.
     *  @param[in]  b  The value of the blue component.
     *  @param[in]  alpha  The value of the color opacity.
     */
    void setRGBA(double r, double g, double b, double alpha = 1.0);

    /**
     *  @brief      Set RGBA color.
     *  @details    This function modifies the current color and sets the color space to RGBA. 
     *              The component values in this function are specified in 8-bit integer format.
     *  @param[in]  r  The value of the red component.
     *  @param[in]  g  The value of the green component.
     *  @param[in]  b  The value of the blue component.
     *  @param[in]  alpha  The value of the color opacity.
     */
    void setRGBA_UI8(unsigned char r, unsigned char g, unsigned char b,
        unsigned char alpha = UINT8_MAX) noexcept;

    /**
     *  @brief      Set RBGA color.
     *  @details    This function modifies the current color and sets the color space to RGBA. 
     *              The component values in this function are specified in 16-bit integer format.
     *  @param[in]  r  The value of the red component.
     *  @param[in]  g  The value of the green component.
     *  @param[in]  b  The value of the blue component.
     *  @param[in]  alpha  The value of the color opacity.
     */
    void setRGBA_UI16(unsigned short r, unsigned short g, unsigned short b,
        unsigned short alpha = UINT16_MAX) noexcept;

    /**
     *  @brief      Set HSLA color.
     *  @details    This function modifies the current color and sets the color space to HSLA.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  l  The value of the lightness component.
     *  @param[in]  alpha  The value of the color opacity.
     */
    void setHSLA(double h, double s, double l, double alpha = 1.0);

    /**
     *  @brief      Set HSLA color.
     *  @details    This function modifies the current color and sets the color space to HSLA. 
     *              The component values in this function are specified in 8-bit integer format.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  l  The value of the lightness component.
     *  @param[in]  alpha  The value of the color opacity.
     */
    void setHSLA_UI8(unsigned char h, unsigned char s, unsigned char l,
        unsigned char alpha = UINT8_MAX) noexcept;

    /**
     *  @brief      Set HSLA color.
     *  @details    This function modifies the current color and sets the color space to HSLA. 
     *              The component values in this function are specified in 16-bit integer format.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  l  The value of the lightness component.
     *  @param[in]  alpha  The value of the color opacity.
     */
    void setHSLA_UI16(unsigned short h, unsigned short s, unsigned short l,
        unsigned short alpha = UINT16_MAX) noexcept;

    /**
     *  @brief      Set HSVA color.
     *  @details    This function modifies the current color and sets the color space to HSVA.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  v  The value of the brightness component.
     *  @param[in]  alpha  The value of the color opacity.
     */
    void setHSVA(double h, double s, double v, double alpha = 1.0);

    /**
     *  @brief      Set HSVA color.
     *  @details    This function modifies the current color and sets the color space to HSVA. 
     *              The component values in this function are specified in 8-bit integer format.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  v  The value of the brightness component.
     *  @param[in]  alpha  The value of the color opacity.
     */
    void setHSVA_UI8(unsigned char h, unsigned char s, unsigned char v,
        unsigned char alpha = UINT8_MAX) noexcept;

    /**
     *  @brief      Set HSVA color.
     *  @details    This function modifies the current color and sets the color space to HSVA. 
     *              The component values in this function are specified in 16-bit integer format.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  v  The value of the brightness component.
     *  @param[in]  alpha  The value of the color opacity.
     */
    void setHSVA_UI16(unsigned short h, unsigned short s, unsigned short v,
        unsigned short alpha = UINT16_MAX) noexcept;

    /**
     *  @brief      Convert to.
     *  @details    This function transforms the current color to the specified color space.
     *  @param[in]  sp  The color space.
     *  @returns    The new color in the specified color space.
     */
    Color convertTo(ColorSpace sp) const;

    /**
     *  @brief      Color space.
     *  @details    This function returns the color space in which the color is represented.
     *  @returns    The color space.
     */
    constexpr ColorSpace colorSpace() const noexcept;

    /**
     *  @brief      Color opacity.
     *  @details    This function returns the color opacity (alpha channel).
     *  @returns    The color opacity.
     */
    constexpr double opacity() const noexcept;

    /**
     *  @brief      Color opacity.
     *  @details    This function returns the color opacity (alpha channel) in 8-bit integer format.
     *  @returns    The color opacity.
     */
    constexpr unsigned char opacity_UI8() const noexcept;

    /**
     *  @brief      Color opacity.
     *  @details    This function returns the color opacity (alpha channel) in 16-bit integer format.
     *  @returns    The color opacity.
     */
    constexpr unsigned short opacity_UI16() const noexcept;

    /**
     *  @brief      Set color opacity.
     *  @details    This function modifies the color opacity (alpha channel).
     *  @param[in]  val  The new color opacity.
     */
    void setOpacity(double val);

    /**
     *  @brief      Set color opacity.
     *  @details    This function modifies the color opacity (alpha channel).
     *  @param[in]  val  The new color opacity in 8-bit format.
     */
    void setOpacity_UI8(unsigned char val) noexcept;

    /**
     *  @brief      Set color opacity.
     *  @details    This function modifies the color opacity (alpha channel).
     *  @param[in]  val  The new color opacity in 16-bit format.
     */
    void setOpacity_UI16(unsigned short val) noexcept;

    /**
     *  @brief      Component 1.
     *  @details    This function returns the first color component.
     *  @returns    The color component value.
     */
    constexpr double component1() const noexcept;

    /**
     *  @brief      Component 1.
     *  @details    This function returns the first color component in 8-bit integer format.
     *  @returns    The color component value.
     */
    constexpr unsigned char component1_UI8() const noexcept;

    /**
     *  @brief      Component 1.
     *  @details    This function returns the first color component in 16-bit integer format.
     *  @returns    The color component value.
     */
    constexpr unsigned short component1_UI16() const noexcept;

    /**
     *  @brief      Set color component 1.
     *  @details    This function modifies the first color component.
     *  @param[in]  val  The new value of the color component.
     */
    void setComponent1(double val);

    /**
     *  @brief      Set color component 1.
     *  @details    This function modifies the first color component.
     *  @param[in]  val  The new value of the color component in 8-bit format.
     */
    void setComponent1_UI8(unsigned char val) noexcept;

    /**
     *  @brief      Set color component 1.
     *  @details    This function modifies the first color component.
     *  @param[in]  val  The new value of the color component in 16-bit format.
     */
    void setComponent1_UI16(unsigned short val) noexcept;

    /**
     *  @brief      Component 2.
     *  @details    This function returns the second color component.
     *  @returns    The color component value.
     */
    constexpr double component2() const noexcept;

    /**
     *  @brief      Component 2.
     *  @details    This function returns the second color component in 8-bit integer format.
     *  @returns    The color component value.
     */
    constexpr unsigned char component2_UI8() const noexcept;

    /**
     *  @brief      Component 2.
     *  @details    This function returns the second color component in 16-bit integer format.
     *  @returns    The color component value.
     */
    constexpr unsigned short component2_UI16() const noexcept;

    /**
     *  @brief      Set color component 2.
     *  @details    This function modifies the second color component.
     *  @param[in]  val  The new value of the color component.
     */
    void setComponent2(double val);

    /**
     *  @brief      Set color component 2.
     *  @details    This function modifies the second color component.
     *  @param[in]  val  The new value of the color component in 8-bit format.
     */
    void setComponent2_UI8(unsigned char val) noexcept;

    /**
     *  @brief      Set color component 2.
     *  @details    This function modifies the second color component.
     *  @param[in]  val  The new value of the color component in 16-bit format.
     */
    void setComponent2_UI16(unsigned short val) noexcept;

    /**
     *  @brief      Component 3.
     *  @details    This function returns the third color component.
     *  @returns    The color component value.
     */
    constexpr double component3() const noexcept;

    /**
     *  @brief      Component 3.
     *  @details    This function returns the third color component in 8-bit integer format.
     *  @returns    The color component value.
     */
    constexpr unsigned char component3_UI8() const noexcept;

    /**
     *  @brief      Component 3.
     *  @details    This function returns the third color component in 16-bit integer format.
     *  @returns    The color component value.
     */
    constexpr unsigned short component3_UI16() const noexcept;

    /**
     *  @brief      Set color component 3.
     *  @details    This function modifies the third color component.
     *  @param[in]  val  The new value of the color component.
     */
    void setComponent3(double val);

    /**
     *  @brief      Set color component 3.
     *  @details    This function modifies the third color component.
     *  @param[in]  val  The new value of the color component in 8-bit format.
     */
    void setComponent3_UI8(unsigned char val) noexcept;

    /**
     *  @brief      Set color component 3.
     *  @details    This function modifies the third color component.
     *  @param[in]  val  The new value of the color component in 16-bit format.
     */
    void setComponent3_UI16(unsigned short val) noexcept;

    /**
     *  @brief      Red component.
     *  @details    This function returns the red component value in the RGB color space.
     *  @returns    The red component.
     */
    double red() const;

    /**
     *  @brief      Red component.
     *  @details    This function returns the red component value in the RGB color space.
     *              The result is expressed in 8-bit integer format.
     *  @returns    The red component.
     */
    unsigned char red_UI8() const;

    /**
     *  @brief      Red component.
     *  @details    This function returns the red component value in the RGB color space.
     *              The result is expressed in 16-bit integer format.
     *  @returns    The red component.
     */
    unsigned short red_UI16() const;

    /**
     *  @brief      Green component.
     *  @details    This function returns the green component value in the RGB color space.
     *  @returns    The green component.
     */
    double green() const;

    /**
     *  @brief      Green component.
     *  @details    This function returns the green component value in the RGB color space.
     *              The result is expressed in 8-bit integer format.
     *  @returns    The green component.
     */
    unsigned char green_UI8() const;

    /**
     *  @brief      Green component.
     *  @details    This function returns the green component value in the RGB color space.
     *              The result is expressed in 16-bit integer format.
     *  @returns    The green component.
     */
    unsigned short green_UI16() const;

    /**
     *  @brief      Blue component.
     *  @details    This function returns the blue component value in the RGB color space.
     *  @returns    The blue component.
     */
    double blue() const;

    /**
     *  @brief      Blue component.
     *  @details    This function returns the blue component value in the RGB color space.
     *              The result is expressed in 8-bit integer format.
     *  @returns    The blue component.
     */
    unsigned char blue_UI8() const;
    
    /**
     *  @brief      Blue component.
     *  @details    This function returns the blue component value in the RGB color space.
     *              The result is expressed in 16-bit integer format.
     *  @returns    The blue component.
     */
    unsigned short blue_UI16() const;

    /**
     *  @brief      Hue component.
     *  @details    This function returns the hue component value in the HSL and HSV color spaces.
     *  @returns    The hue component.
     */
    double hue() const;

    /**
     *  @brief      Hue component.
     *  @details    This function returns the hue component value in the HSL and HSV color spaces.
     *              The result is expressed in 8-bit integer format.
     *  @returns    The hue component.
     */
    unsigned char hue_UI8() const;

    /**
     *  @brief      Hue component.
     *  @details    This function returns the hue component value in the HSL and HSV color spaces.
     *              The result is expressed in 16-bit integer format.
     *  @returns    The hue component.
     */
    unsigned short hue_UI16() const;

    /**
     *  @brief      Saturation component.
     *  @details    This function returns the saturation component value in the HSL color space.
     *  @returns    The saturation component.
     */
    double saturationHSL() const;

    /**
     *  @brief      Saturation component.
     *  @details    This function returns the saturation component value in the HSL color space.
     *              The result is expressed in 8-bit integer format.
     *  @returns    The saturation component.
     */
    unsigned char saturationHSL_UI8() const;

    /**
     *  @brief      Saturation component.
     *  @details    This function returns the saturation component value in the HSL color space.
     *              The result is expressed in 16-bit integer format.
     *  @returns    The saturation component.
     */
    unsigned short saturationHSL_UI16() const;

    /**
     *  @brief      Saturation component.
     *  @details    This function returns the saturation component value in the HSV color space.
     *  @returns    The saturation component.
     */
    double saturationHSV() const;

    /**
     *  @brief      Saturation component.
     *  @details    This function returns the saturation component value in the HSV color space.
     *              The result is expressed in 8-bit integer format.
     *  @returns    The saturation component.
     */
    unsigned char saturationHSV_UI8() const;

    /**
     *  @brief      Saturation component.
     *  @details    This function returns the saturation component value in the HSV color space.
     *              The result is expressed in 16-bit integer format.
     *  @returns    The saturation component.
     */
    unsigned short saturationHSV_UI16() const;

    /**
     *  @brief      Brightness component.
     *  @details    This function returns the brightness component value in the HSL color space.
     *  @returns    The brightness component.
     */
    double brightness() const;

    /**
     *  @brief      Brightness component.
     *  @details    This function returns the brightness component value in the HSL color space.
     *              The result is expressed in 8-bit integer format.
     *  @returns    The brightness component.
     */
    unsigned char brightness_UI8() const;

    /**
     *  @brief      Brightness component.
     *  @details    This function returns the brightness component value in the HSL color space.
     *              The result is expressed in 16-bit integer format.
     *  @returns    The brightness component.
     */
    unsigned short brightness_UI16() const;

    /**
     *  @brief      Lightness component.
     *  @details    This function returns the lightness component value in the HSL color space.
     *  @returns    The lightness component.
     */
    double lightness() const;

    /**
     *  @brief      Lightness component.
     *  @details    This function returns the lightness component value in the HSL color space.
     *              The result is expressed in 8-bit integer format.
     *  @returns    The lightness component.
     */
    unsigned char lightness_UI8() const;

    /**
     *  @brief      Lightness component.
     *  @details    This function returns the lightness component value in the HSL color space.
     *              The result is expressed in 16-bit integer format.
     *  @returns    The lightness component.
     */
    unsigned short lightness_UI16() const;

    /**
     *  @brief      Hexadecimal string.
     *  @details    This function returns a string that represents the color in hexadecimal format.
     *              The color space is not returned by this representation.
     *  @param[in]  ui8  True, if the output string represents a color in 8-bit format. False indicates
     *              that the output string represents a color in 16-bit format.
     *  @param[in]  addOpacity  True indicates that the alpha channel is also included in the
     *              hexadecimal string.
     *  @returns    A string that represents the color.
     */
    std::string hexString(bool ui8 = true, bool addOpacity = true) const;

    /**
     *  @brief      RGB string.
     *  @details    This function returns a string that represents the color in the RGB space.
     *              This string has the following structure: rgb(r, g, b).
     *  @returns    A string that represents the color.
     */
    std::string rgbString() const;

    /**
     *  @brief      RGBA string.
     *  @details    This function returns a string that represents the color in the RGBA space.
     *              This string has the following structure: rgba(r, g, b, a).
     *  @returns    A string that represents the color.
     */
    std::string rgbaString() const;

    /**
     *  @brief      HSL string.
     *  @details    This function returns a string that represents the color in the HSL space.
     *              This string has the following structure: hsl(h, s, l).
     *  @returns    A string that represents the color.
     */
    std::string hslString() const;

    /**
     *  @brief      HSLA string.
     *  @details    This function returns a string that represents the color in the HSLA space.
     *              This string has the following structure: hsla(h, s, l, a).
     *  @returns    A string that represents the color.
     */
    std::string hslaString() const;

    /**
     *  @brief      HSV string.
     *  @details    This function returns a string that represents the color in the HSV space.
     *              This string has the following structure: hsv(h, s, v).
     *  @returns    A string that represents the color.
     */
    std::string hsvString() const;

    /**
     *  @brief      HSVA string.
     *  @details    This function returns a string that represents the color in the HSVA space.
     *              This string has the following structure: hsva(h, s, v).
     *  @returns    A string that represents the color.
     */
    std::string hsvaString() const;

    /**
     *  @brief      RBGA color.
     *  @details    This function initializes a new RGBA color and sets all its components to 
     *              the specified input values.
     *  @param[in]  r  The value of the red component.
     *  @param[in]  g  The value of the green component.
     *  @param[in]  b  The value of the blue component.
     *  @param[in]  alpha  The value of the color opacity.
     *  @returns    The new color.
     */
    static Color fromRGBA(double r, double g, double b, double alpha = 1.0);

    /**
     *  @brief      RBGA color.
     *  @details    This function initializes a new RGBA color and sets all its components to 
     *              the specified input values in 8-bit integer format.
     *  @param[in]  r  The value of the red component.
     *  @param[in]  g  The value of the green component.
     *  @param[in]  b  The value of the blue component.
     *  @param[in]  alpha  The value of the color opacity.
     *  @returns    The new color.
     */
    static Color fromRGBA_UI8(unsigned char r, unsigned char g, unsigned char b,
        unsigned char alpha = UINT8_MAX);

    /**
     *  @brief      RBGA color.
     *  @details    This function initializes a new RGBA color and sets all its components to 
     *              the specified input values in 16-bit integer format.
     *  @param[in]  r  The value of the red component.
     *  @param[in]  g  The value of the green component.
     *  @param[in]  b  The value of the blue component.
     *  @param[in]  alpha  The value of the color opacity.
     *  @returns    The new color.
     */
    static Color fromRGBA_UI16(unsigned short r, unsigned short g, unsigned short b,
        unsigned short alpha = UINT16_MAX);

    /**
     *  @brief      HSLA color.
     *  @details    This function initializes a new HSLA color and sets all its components to 
     *              the specified input values.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  l  The value of the lightness component.
     *  @param[in]  alpha  The value of the color opacity.
     *  @returns    The new color.
     */
    static Color fromHSLA(double h, double s, double l, double alpha = 1.0);

    /**
     *  @brief      HSLA color.
     *  @details    This function initializes a new HSLA color and sets all its components to 
     *              the specified input values in 8-bit integer format.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  l  The value of the lightness component.
     *  @param[in]  alpha  The value of the color opacity.
     *  @returns    The new color.
     */
    static Color fromHSLA_UI8(unsigned char h, unsigned char s, unsigned char l,
        unsigned char alpha = UINT8_MAX);

    /**
     *  @brief      HSLA color.
     *  @details    This function initializes a new HSLA color and sets all its components to 
     *              the specified input values in 16-bit integer format.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  l  The value of the lightness component.
     *  @param[in]  alpha  The value of the color opacity.
     *  @returns    The new color.
     */
    static Color fromHSLA_UI16(unsigned short h, unsigned short s, unsigned short l,
        unsigned short alpha = UINT16_MAX);

    /**
     *  @brief      HSVA color.
     *  @details    This function initializes a new HSVA color and sets all its components to 
     *              the specified input values.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  v  The value of the brightness component.
     *  @param[in]  alpha  The value of the color opacity.
     *  @returns    The new color.
     */
    static Color fromHSVA(double h, double s, double v, double alpha = 1.0);

    /**
     *  @brief      HSVA color.
     *  @details    This function initializes a new HSVA color and sets all its components to 
     *              the specified input values in 8-bit integer format.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  v  The value of the brightness component.
     *  @param[in]  alpha  The value of the color opacity.
     *  @returns    The new color.
     */
    static Color fromHSVA_UI8(unsigned char h, unsigned char s, unsigned char v,
        unsigned char alpha = UINT8_MAX);

    /**
     *  @brief      HSVA color.
     *  @details    This function initializes a new HSVA color and sets all its components to 
     *              the specified input values in 16-bit integer format.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  v  The value of the brightness component.
     *  @param[in]  alpha  The value of the color opacity.
     *  @returns    The new color.
     */
    static Color fromHSVA_UI16(unsigned short h, unsigned short s, unsigned short v,
        unsigned short alpha = UINT16_MAX);

    /**
     *  @brief      Pre-defined colors.
     *  @details    This function returns the pre-defined colors that are recognized by the library.
     *  @returns    A container with the pre-defined colors.
     */
    static std::vector<ColorName> colors();

    /**
     *  @brief      Pre-defined color names.
     *  @details    This function returns the names of the pre-defined colors that are recognized 
     *              by the library.
     *  @returns    A container with the pre-defined color names.
     */
    static std::vector<std::string> colorNames();

    /**
     *  @brief      Color string.
     *  @details    This function returns a string that represents the specified color in the RGB space.
     *  @param[in]  color  The pre-defined color whose string will be returned.
     *  @returns    The string of the specified color.
     */
    static std::string colorString(ColorName color);

protected:

    ////////// Data members //////////        

    ColorSpace colorSpace_ {ColorSpace::RGBA};  /**< Color space. */

    double c_[4] {0.0, 0.0, 0.0, 1.0};          /**< Color components. */

};

}}

////////// Inline functions //////////
#include <nct/color/Color_inline.h>

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
