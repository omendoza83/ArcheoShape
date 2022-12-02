//=================================================================================================================
/**
 *  @file       RgbColor.h
 *  @brief      nct::color::RgbColor class.
 *  @details    Declaration file of the nct::color::RgbColor class.
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

#ifndef NCT_RGB_COLOR_H_INCLUDE
#define NCT_RGB_COLOR_H_INCLUDE

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
namespace color {

/**
 *  @brief      RGB color class.
 *  @details    This class is used to represent colors in the RGB space. Internally, each
 *              component is stored in double precision format in the range [0, 1].
 *              The parameters can be specified in 8 bit and 16 bit integer formats.
 *              For 8-bit integers, the full range is represented by numbers from 0 to 255,
 *              while the range [0 65535] is used for 16-bit integers.
 */
class NCT_EXPIMP RgbColor final {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes a new color object using the default color (black).
     */
    constexpr RgbColor() noexcept = default;

    /**
     *  @brief      Class constructor.
     *  @details    This function initializes a new color and sets all its components to the
     *              specified input values.
     *  @param[in]  r  The value of the red component.
     *  @param[in]  g  The value of the green component.
     *  @param[in]  b  The value of the blue component.
     */
    constexpr RgbColor(double r, double g, double b);

    /**
     *  @brief      Class constructor.
     *  @details    This function initializes a new color and sets all its components to the
     *              specified input values in 8-bit integer format.
     *  @param[in]  r  The value of the red component.
     *  @param[in]  g  The value of the green component.
     *  @param[in]  b  The value of the blue component.
     */
    constexpr RgbColor(unsigned char r, unsigned char g, unsigned char b) noexcept;

    /**
     *  @brief      Class constructor.
     *  @details    This function initializes a new color and sets all its components to the
     *              specified input values in 16-bit integer format.
     *  @param[in]  r  The value of the red component.
     *  @param[in]  g  The value of the green component.
     *  @param[in]  b  The value of the blue component.
     */
    constexpr RgbColor(unsigned short r, unsigned short g, unsigned short b) noexcept;

    /**
     *  @brief      Class constructor.
     *  @details    This function initializes a new color and sets all its components according to
     *              the specified hexadecimal string.
     *  @param[in]  color  Hexadecimal string that represents the color.
     */
    explicit RgbColor(const std::string& color);
    
    ////////// Operators //////////        
    
    /**
     *  @brief      Equality operator.
     *  @details    Two colors are equal if both have the same components and opacity. If the
     *              colors are specified in different spaces, both are transformed into their 
     *              RGB representation and then they are compared.
     *  @param[in]  right  Color on the right side of the operation.
     *  @returns    True if both colors are the same.
     */
    constexpr bool operator==(const RgbColor& right) const noexcept;

    /**
     *  @brief      Inequality operator.
     *  @details    Two colors are not equal if they have at least one component different. If the
     *              colors are specified in different spaces, both are transformed into their 
     *              RGB representation and then they are compared.
     *  @param[in]  right  Color on the right side of the operation.
     *  @returns    True if both colors are not the same.
     */
    constexpr bool operator!=(const RgbColor& right) const noexcept;

    /**
     *  @brief      Color component.
     *  @details    This operator returns the specified color component.
     *  @param[in]  i  Component index (0, 1, or 2).
     *  @returns    The selected color component.
     */
    constexpr double operator[](size_t i) const;

    ////////// Member functions //////////    

    /**
     *  @brief      Set color.
     *  @details    This function modifies all the components of the color.
     *  @param[in]  r  The value of the red component.
     *  @param[in]  g  The value of the green component.
     *  @param[in]  b  The value of the blue component.
     */
    void setColor(double r, double g, double b);

    /**
     *  @brief      Set color.
     *  @details    This function modifies all the components of the color. The component
     *              values in this function are specified in 8-bit integer format.
     *  @param[in]  r  The value of the red component.
     *  @param[in]  g  The value of the green component.
     *  @param[in]  b  The value of the blue component.
     */
    void setColor_UI8(unsigned char r, unsigned char g, unsigned char b) noexcept;

    /**
     *  @brief      Set color.
     *  @details    This function modifies all the components of the color. The component
     *              values in this function are specified in 16-bit integer format.
     *  @param[in]  r  The value of the red component.
     *  @param[in]  g  The value of the green component.
     *  @param[in]  b  The value of the blue component.
     */
    void setColor_UI16(unsigned short r, unsigned short g, unsigned short b) noexcept;

    /**
     *  @brief      Red component.
     *  @details    This function returns the red component value in the RGB color space.
     *  @returns    The red component.
     */
    constexpr double red() const noexcept;

    /**
     *  @brief      Red component.
     *  @details    This function returns the red component value in the RGB color space.
     *              The result is expressed in 8-bit integer format.
     *  @returns    The red component.
     */
    constexpr unsigned char red_UI8() const noexcept;

    /**
     *  @brief      Red component.
     *  @details    This function returns the red component value in the RGB color space.
     *              The result is expressed in 16-bit integer format.
     *  @returns    The red component.
     */
    constexpr unsigned short red_UI16() const noexcept;

    /**
     *  @brief      Set red component.
     *  @details    This function modifies the red component.
     *  @param[in]  val  The new value of the component.
     */
    void setRed(double val);

    /**
     *  @brief      Set red component.
     *  @details    This function modifies the red component.
     *  @param[in]  val  The new value of the color component in 8-bit format.
     */
    void setRed_UI8(unsigned char val) noexcept;

    /**
     *  @brief      Set red component.
     *  @details    This function modifies the red component.
     *  @param[in]  val  The new value of the color component in 16-bit format.
     */
    void setRed_UI16(unsigned short val) noexcept;

    /**
     *  @brief      Green component.
     *  @details    This function returns the green component value in the RGB color space.
     *  @returns    The green component.
     */
    constexpr double green() const noexcept;

    /**
     *  @brief      Green component.
     *  @details    This function returns the green component value in the RGB color space.
     *              The result is expressed in 8-bit integer format.
     *  @returns    The green component.
     */
    constexpr unsigned char green_UI8() const noexcept;

    /**
     *  @brief      Green component.
     *  @details    This function returns the green component value in the RGB color space.
     *              The result is expressed in 16-bit integer format.
     *  @returns    The green component.
     */
    constexpr unsigned short green_UI16() const noexcept;

    /**
     *  @brief      Set green component.
     *  @details    This function modifies the green component.
     *  @param[in]  val  The new value of the component.
     */
    void setGreen(double val);

    /**
     *  @brief      Set green component.
     *  @details    This function modifies the green component.
     *  @param[in]  val  The new value of the color component in 8-bit format.
     */
    void setGreen_UI8(unsigned char val) noexcept;

    /**
     *  @brief      Set green component.
     *  @details    This function modifies the green component.
     *  @param[in]  val  The new value of the color component in 16-bit format.
     */
    void setGreen_UI16(unsigned short val) noexcept;

    /**
     *  @brief      Blue component.
     *  @details    This function returns the blue component value in the RGB color space.
     *  @returns    The blue component.
     */
    constexpr double blue() const noexcept;

    /**
     *  @brief      Blue component.
     *  @details    This function returns the blue component value in the RGB color space.
     *              The result is expressed in 8-bit integer format.
     *  @returns    The blue component.
     */
    constexpr unsigned char blue_UI8() const noexcept;

    /**
     *  @brief      Blue component.
     *  @details    This function returns the blue component value in the RGB color space.
     *              The result is expressed in 16-bit integer format.
     *  @returns    The blue component.
     */
    constexpr unsigned short blue_UI16() const noexcept;

    /**
     *  @brief      Set blue component.
     *  @details    This function modifies the blue component.
     *  @param[in]  val  The new value of the component.
     */
    void setBlue(double val);

    /**
     *  @brief      Set blue component.
     *  @details    This function modifies the blue component.
     *  @param[in]  val  The new value of the color component in 8-bit format.
     */
    void setBlue_UI8(unsigned char val) noexcept;

    /**
     *  @brief      Set blue component.
     *  @details    This function modifies the blue component.
     *  @param[in]  val  The new value of the color component in 16-bit format.
     */
    void setBlue_UI16(unsigned short val) noexcept;

    /**
     *  @brief      Hexadecimal string.
     *  @details    This function returns a string that represents the color in hexadecimal format.
     *  @param[in]  ui8  True, if the output string represents a color in 8-bit format. False indicates
     *              that the output string represents a color in 16-bit format.
     *  @returns    A string that represents the color.
     */
    std::string hexString(bool ui8 = true) const;

    /**
     *  @brief      Color string.
     *  @details    This function returns a string that represents the color in the RGB space.
     *              This string has the following structure: rgb(r, g, b).
     *  @returns    A string that represents the color.
     */
    std::string colorString() const;

    /**
     *  @brief      From HSL color.
     *  @details    This function initializes a new color taking the values of another color 
     *              in HSL format specified in its hexadecimal representation.
     *  @param[in]  color  The hexadecimanl representation of the input color.
     *  @returns    The new color.
     */
    static RgbColor fromHSL(const std::string& color);

    /**
     *  @brief      From HSL color.
     *  @details    This function returns a new color that corresponds to the HSL color indicated
     *              in the inputs arguments.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  l  The value of the lightness component.
     *  @returns    The new color.
     */
    static RgbColor fromHSL(double h, double s, double l);

    /**
     *  @brief      From HSL color.
     *  @details    This function returns a new color that corresponds to the HSL color indicated
     *              in the inputs arguments.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  l  The value of the lightness component.
     *  @returns    The new color.
     */
    static RgbColor fromHSL_UI8(unsigned char h, unsigned char s, unsigned char l);

    /**
     *  @brief      From HSL color.
     *  @details    This function returns a new color that corresponds to the HSL color indicated
     *              in the inputs arguments.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  l  The value of the lightness component.
     *  @returns    The new color.
     */
    static RgbColor fromHSL_UI16(unsigned short h, unsigned short s, unsigned short l);

    /**
     *  @brief      From HSV color.
     *  @details    This function initializes a new color taking the values of another color 
     *              in HSV format specified in its hexadecimal representation.
     *  @param[in]  color  The hexadecimanl representation of the input color.
     *  @returns    The new color.
     */
    static RgbColor fromHSV(const std::string& color);

    /**
     *  @brief      From HSV color.
     *  @details    This function returns a new color that corresponds to the HSV color indicated
     *              in the inputs arguments.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  v  The value of the brightness component.
     *  @returns    The new color.
     */
    static RgbColor fromHSV(double h, double s, double v);

    /**
     *  @brief      From HSV color.
     *  @details    This function returns a new color that corresponds to the HSV color indicated
     *              in the inputs arguments.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  v  The value of the brightness component.
     *  @returns    The new color.
     */
    static RgbColor fromHSV_UI8(unsigned char h, unsigned char s, unsigned char v);

    /**
     *  @brief      From HSV color.
     *  @details    This function returns a new color that corresponds to the HSV color indicated
     *              in the inputs arguments.
     *  @param[in]  h  The value of the hue component.
     *  @param[in]  s  The value of the saturation component.
     *  @param[in]  v  The value of the brightness component.
     *  @returns    The new color.
     */
    static RgbColor fromHSV_UI16(unsigned short h, unsigned short s, unsigned short v);

    /**
     *  @brief      Color palette.
     *  @details    This function creates a color palette using linear ramping between two
     *              consecutive pivot colors. The size of the palette is set according to the index of
     *              the last pivot.
     *  @note       The positions must be sorted in ascending order, otherwise, this function produces an
     *              exception. Also, the first index must be zero. Finally, two pivots can't share the
     *              same index.
     *  @param[in]  colors  Pivot colors and indices.
     *  @returns    The color palette.
     */
    static std::vector<RgbColor> colorPalette(
        const std::vector<std::pair<RgbColor, size_t>>& pivotColors);

protected:

    ////////// Data members //////////        

    double c_[3] {0.0, 0.0, 0.0};     /**< Color components (Red-Green-Blue). */

};

}}

////////// Inline functions //////////
#include <nct/color/RgbColor_inline.h>

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
