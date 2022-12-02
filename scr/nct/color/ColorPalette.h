//=================================================================================================================
/**
 *  @file       ColorPalette.h
 *  @brief      nct::color::ColorPalette class.
 *  @details    Declaration file of the nct::color::ColorPalette class.
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

#ifndef NCT_COLOR_PALETTE_H_INCLUDE
#define NCT_COLOR_PALETTE_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/color/Color.h>

#include <string>
#include <vector>

//=================================================================================================================
namespace nct {        
namespace color {

/**
 *  @brief      Color palette class.
 *  @details    This class represents a color palette. Elements between pivot colors are estimated by linear 
 *              ramping of the color componentes of consecutive pivots. The first pivot defines the color 
 *              space of the color palette. 
 *              Each pivot has a position value (any real number) and the corresponding color. Usually, 
 *              the color positions are defined in the range between 0 and 1, but any other range is valid. 
 *              Colors between positions are calculated by linear interpolation between the two colors
 *              that bound each position value. Any position below the lowest pivot is asigned to the first
 *              pivot, whereas that any position above the last pivot is set to the last color.
 *              In addition to the color pivots, this class also uses alpha pivots to calculate  
 *              the opacity component independly. The final alpha value is calculated as the product of the
 *              opacity obtained with the alpha pivots and the opacity calculated with the color pivots.
 *              If the object does not have alpha pivots, the opacity value is calculated only using the color
 *              pivots.
 */
class NCT_EXPIMP ColorPalette final {

public:

    /**
     *  @brief      Color palettes.
     *  @details    Pre-defined color palettes.
     */
    enum class ColorPaletteName : unsigned char {

        Rainbow,            /**< Rainbow. */
        Heat,               /**< Heat. */
        Bone,               /**< Bone. */
        Cool,               /**< Cool. */
        Cooper,             /**< Coopper. */
        Gray,               /**< Gray. */
        Hot,                /**< Hot. */
        Spring,             /**< Spring. */
        Summer,             /**< Summer. */
        Autumn,             /**< Autumn. */
        Winter,             /**< Winter. */
        Jet,                /**< Jet. */
        SignalQuality,      /**< Signal quality. */
        NegativePositive,   /**< Negative-positive. */
        WhiteToRed,         /**< White to red. */
        WhiteToGreen,       /**< White to green. */
        WhiteToBlue,        /**< White to blue. */
        Gcwyr,              /**< Green-Cyan-White-Yellow-Red. */
        Wygbor,             /**< White-Yellow-Green-Blue-Orange-Red. */
        Spectrum,           /**< Color spectrum. */
        Extreme,            /**< Extreme values. */
        Extreme2,           /**< Extreme values 2. */
        Extreme0P1,         /**< Extreme values (0.1%, two sides). */
        Extreme0P5,         /**< Extreme values (0.5%, two sides). */
        Extreme1,           /**< Extreme values (1.0%, two sides). */
        Extreme2P5,         /**< Extreme values (2.5%, two sides). */
        Extreme5,           /**< Extreme values (5.0%, two sides). */
        Extreme10,          /**< Extreme values (10.0%, two sides). */
        ExtremeL0P1,        /**< Extreme values (0.1%, lower side). */
        ExtremeL0P5,        /**< Extreme values (0.5%, lower side). */
        ExtremeL1,          /**< Extreme values (1.0%, lower side). */
        ExtremeL2P5 ,       /**< Extreme values (2.5%, lower side). */
        ExtremeL5,          /**< Extreme values (5.0%, lower side). */
        ExtremeL10,         /**< Extreme values (10.0%, lower side). */
        ExtremeU0P1,        /**< Extreme values (0.1%, upper side). */
        ExtremeU0P5,        /**< Extreme values (0.5%, upper side). */
        ExtremeU1,          /**< Extreme values (1.0%, upper side). */
        ExtremeU2P5,        /**< Extreme values (2.5%, upper side). */
        ExtremeU5,          /**< Extreme values (5.0%, upper side). */
        ExtremeU10,         /**< Extreme values (10.0%, upper side). */
    };        

    ////////// Constructors //////////
    
    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes a new color palette without pivot colors.
     */
    ColorPalette() noexcept = default;

    /**
     *  @brief      Class constructor.
     *  @details    This function initializes the pivots according to the specified color palette.
     *  @param[in]  palette  The palette type.
     */
    ColorPalette(ColorPaletteName palette);    

    ////////// Operators //////////        
    
    /**
     *  @brief      Evaluate palette.
     *  @details    This operator returns the color that corresponds to the specified position value.
     *  @param[in]  t  The position to be evaluated.
     *  @returns    The color that corresponds to the given position.
     */
    Color operator()(double t);

    ////////// Member functions ////////// 

    /**
     *  @brief      Clear palette.
     *  @details    This function clears the color palette.
     */
    void clear();

    /**
     *  @brief      Color pivots.
     *  @details    This function returns the color pivots.
     *  @returns    The color pivots.
     */
    const std::vector<std::pair<double, Color>>& colorPivots() noexcept;

    /**
     *  @brief      Add color pivot.
     *  @details    This function adds a new color pivot.
     *  @param[in]  t  The position of the pivot.
     *  @param[in]  color  The color at the given position.
     */
    void addPivot(double t, const Color& color);

    /**
     *  @brief      Clear color pivots.
     *  @details    This function clears the color pivots.
     */
    void clearPivots();

    /**
     *  @brief      Alpha pivots.
     *  @details    This function returns the alpha pivots.
     *  @returns    The alpha pivots.
     */
    const std::vector<std::pair<double, double>>& alphaPivots() noexcept;

    /**
     *  @brief      Add alpha pivot.
     *  @details    This function adds a new alpha pivot.
     *  @param[in]  t  The position of the pivot.
     *  @param[in]  color  The alpha value at the given position.
     */
    void addAlphaPivot(double t, double alpha);

    /**
     *  @brief      Clear alpha pivots.
     *  @details    This function clears the alpha pivots.
     */
    void clearAlphaPivots();

    /**
     *  @brief      Evaluate palette function.
     *  @details    This function finds the color palette at the given position.
     *  @param[in]  t  The position to be evaluated.
     *  @returns    The color at the specified position.
     */
    Color eval(double t);

    /**
     *  @brief      Evaluate color function.
     *  @details    This function finds the color at the given position. in this function,
     *              only the color pivots are used to find the color.
     *  @param[in]  t  The position to be evaluated.
     *  @returns    The color at the specified position.
     */
    Color evalColor(double t);

    /**
     *  @brief      Evaluate alpha function.
     *  @details    This function calculates the alpha value at the given position. 
     *  @param[in]  t  The position to be evaluated.
     *  @returns    The alpha value at the specified position.
     */
    double evalAlpha(double t);

    /**
     *  @brief      Evaluate palette function at multiple positions.
     *  @details    This function calculates "size" colors from the first pivot position to the last pivot.
     *  @param[in]  size  The size of the output palette or the number of times that the palette function
     *              will be evaluated.
     *  @returns    The calculated colors of the palette.
     */
    std::vector<Color> palette(size_t size);

    /**
     *  @brief      Evaluate color function at multiple positions.
     *  @details    This function calculates "size" colors from the first color pivot position to 
     *              the last color pivot.
     *  @param[in]  size  The size of the output palette or the number of times that the palette function
     *              will be evaluated.
     *  @returns    The calculated colors.
     */
    std::vector<Color> paletteColors(size_t size);

    /**
     *  @brief      Evaluate alpha function at multiple positions.
     *  @details    This function calculates "size" alphas from the first alpha pivot position to 
     *              the last alpha pivot.
     *  @param[in]  size  The size of the output array or the number of times that the alpha function
     *              will be evaluated.
     *  @returns    The calculated alphas.
     */
    std::vector<double> paletteAlphas(size_t size);

    /**
     *  @brief      RGB strings.
     *  @details    This function retursn the RGB representation of a color palette evaluated at
     *              "size" positions.
     *  @param[in]  size  The size of the output array or the number of times that the palette function
     *              will be evaluated.
     *  @returns    The RGB representation of the color palette.
     */
    std::vector<std::string> rgbStrings(size_t size);

    /**
     *  @brief      RGBA strings.
     *  @details    This function retursn the RGBA representation of a color palette evaluated 
     *              at "size" positions.
     *  @param[in]  size  The size of the output array or the number of times that the palette function
     *              will be evaluated.
     *  @returns    The RGBA representation of the color palette.
     */
    std::vector<std::string> rgbaStrings(size_t size);

    /**
     *  @brief      Color palettes.
     *  @details    This function returns the color palettes implemented in the library.
     *  @returns    The color palettes.
     */
    static std::vector<ColorPaletteName> colorPalettes();

    /**
     *  @brief      Color palette names.
     *  @details    This function returns the names in string format of the color palettes 
     *              implemented in the library.
     *  @returns    The color palette names.
     */
    static std::vector<std::string> colorPaletteNames();

private:
    
    ////////// Data members //////////     

    std::vector<std::pair<double, Color>> pivots_;          /**< Pivot colors. */

    std::vector<std::pair<double, double>> alphaPivots_;    /**< Pivor values for alpha channel. */

};

}}

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
