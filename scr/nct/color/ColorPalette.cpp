//=================================================================================================================
/**
 *  @file       ColorPalette.cpp
 *  @brief      nct::color::ColorPalette class implementation file.
 *  @details    This file contains the implementation of the nct::color::ColorPalette class.
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
#include <nct/color/ColorPalette.h>

#include <array>
#include <iomanip>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::color::ColorPalette::ColorPalette(ColorPaletteName palette)
{
    switch (palette) {
        case ColorPaletteName::Rainbow:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(255,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0 / 6.0, Color::fromRGBA_UI8(255, 255,   0, 255)));
            pivots_.push_back(std::make_pair(1.0 / 3.0, Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(1.0 / 2.0, Color::fromRGBA_UI8(  0, 255, 255, 255)));
            pivots_.push_back(std::make_pair(2.0 / 3.0, Color::fromRGBA_UI8(  0,   0, 255, 255)));
            pivots_.push_back(std::make_pair(5.0 / 6.0, Color::fromRGBA_UI8(255,   0, 255, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0, 255)));

            break;

        case ColorPaletteName::Heat:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0 / 3.5, Color::fromRGBA_UI8(255,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0 / 2.0, Color::fromRGBA_UI8(255, 160,   0, 255)));
            pivots_.push_back(std::make_pair(1.0 / 1.5, Color::fromRGBA_UI8(255, 255,   0, 255)));
            pivots_.push_back(std::make_pair(1.0 / 1.16,Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(  0, 255, 255, 255)));

            break;

        case ColorPaletteName::Bone:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0,   0,   0, 255)));
            pivots_.push_back(std::make_pair(3.0 / 8.0, Color::fromRGBA_UI8( 81,  81, 113, 255)));
            pivots_.push_back(std::make_pair(1.0 / 1.31,Color::fromRGBA_UI8(166, 198, 198, 255)));            
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));

            break;

        case ColorPaletteName::Cool:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0, 255, 255, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0, 255, 255)));

            break;

        case ColorPaletteName::Cooper:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0 /1.255,Color::fromRGBA_UI8(255, 158, 100, 255)));
            pivots_.push_back(std::make_pair(1.0 / 1.23,Color::fromRGBA_UI8(255, 161, 103, 255)));            
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255, 199, 127, 255)));


        case ColorPaletteName::Gray:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));

            break;

        case ColorPaletteName::Hot:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0 /1.255,Color::fromRGBA_UI8(255,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0 / 1.23,Color::fromRGBA_UI8(255, 255,   0, 255)));            
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));

            break;

        case ColorPaletteName::Spring:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(255,   0, 255, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255, 255,   0, 255)));

            break;

        case ColorPaletteName::Summer:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0, 128, 102, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255, 255, 102, 255)));

            break;

        case ColorPaletteName::Autumn:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(255,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255, 255,   0, 255)));

            break;

        case ColorPaletteName::Winter:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0,   0, 255, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(  0, 255, 128, 255)));

            break;

        case ColorPaletteName::Jet:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0,   0, 143, 255)));
            pivots_.push_back(std::make_pair(1.0 / 8.0, Color::fromRGBA_UI8(  0,   0, 255, 255)));
            pivots_.push_back(std::make_pair(3.0 / 8.0, Color::fromRGBA_UI8(  0, 255, 255, 255)));
            pivots_.push_back(std::make_pair(5.0 / 8.0, Color::fromRGBA_UI8(255, 255,   0, 255)));
            pivots_.push_back(std::make_pair(7.0 / 8.0, Color::fromRGBA_UI8(255,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(128,   0,   0, 255)));

            break;

        case ColorPaletteName::SignalQuality:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(255,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0 /2.0,  Color::fromRGBA_UI8(255, 255,   0, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(  0, 255,   0, 255)));

            break;

        case ColorPaletteName::NegativePositive:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0,   0, 255, 255)));
            pivots_.push_back(std::make_pair(1.0 /2.0,  Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0, 255)));

            break;

        case ColorPaletteName::WhiteToRed:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0, 255)));

            break;

        case ColorPaletteName::WhiteToGreen:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(  0, 255,   0, 255)));

            break;

        case ColorPaletteName::WhiteToBlue:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(  0,   0, 255, 255)));

            break;

        case ColorPaletteName::Gcwyr:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(1.0 / 4.0, Color::fromRGBA_UI8(  0, 255, 255, 255)));
            pivots_.push_back(std::make_pair(1.0 / 2.0, Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(3.0 / 4.0, Color::fromRGBA_UI8(255, 255,   0, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0, 255)));

            break;

        case ColorPaletteName::Wygbor:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.12,      Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.16,      Color::fromRGBA_UI8(255, 255,   0, 255)));
            pivots_.push_back(std::make_pair(1.0 / 4.0, Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(1.0 / 2.0, Color::fromRGBA_UI8(  0, 100, 255, 255)));
            pivots_.push_back(std::make_pair(3.0 / 4.0, Color::fromRGBA_UI8(255, 100,  40, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0, 255)));

            break;

        case ColorPaletteName::Spectrum:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(255,   0, 255, 255)));
            pivots_.push_back(std::make_pair(2.0 / 15., Color::fromRGBA_UI8(  0,   0, 255, 255)));
            pivots_.push_back(std::make_pair(0.3,       Color::fromRGBA_UI8(  0, 255, 255, 255)));
            pivots_.push_back(std::make_pair(11. / 30., Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.6,       Color::fromRGBA_UI8(255, 255,   0, 255)));
            pivots_.push_back(std::make_pair(49. / 60., Color::fromRGBA_UI8(255,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0, 255)));

            break;

        case ColorPaletteName::Extreme:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(1.0 / 20., Color::fromRGBA_UI8(  0, 255, 255, 255)));
            pivots_.push_back(std::make_pair(1.0 / 10., Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(9.0 / 10., Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(19. / 20., Color::fromRGBA_UI8(255, 255,   0, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0, 255)));

            break;

        case ColorPaletteName::Extreme2:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(1.0 / 20., Color::fromRGBA_UI8(  0,   0, 255, 255)));
            pivots_.push_back(std::make_pair(1.0 / 10., Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(9.0 / 10., Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(19. / 20., Color::fromRGBA_UI8(255,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255, 255,   0, 255)));

            break;

        case ColorPaletteName::Extreme0P1:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.001,     Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.0015,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.9985,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.999,     Color::fromRGBA_UI8(255,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0, 255)));

            break;

        case ColorPaletteName::Extreme0P5:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.005,     Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.0055,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.9945,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.995,     Color::fromRGBA_UI8(255,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0, 255)));

            break;

        case ColorPaletteName::Extreme1:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.01,      Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.0105,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.9895,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.99,      Color::fromRGBA_UI8(255,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0, 255)));

            break;

        case ColorPaletteName::Extreme2P5:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.025,     Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.0255,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.9745,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.975,     Color::fromRGBA_UI8(255,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0, 255)));

            break;

        case ColorPaletteName::Extreme5:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.050,     Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.0505,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.9495,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.950,     Color::fromRGBA_UI8(255,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0, 255)));

            break;

        case ColorPaletteName::Extreme10:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.1,       Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.1005,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.8995,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.9,       Color::fromRGBA_UI8(255,   0,   0, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0, 255)));

            break;

        case ColorPaletteName::ExtremeL0P1:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.001,     Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.0015,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));
                        
            break;

        case ColorPaletteName::ExtremeL0P5:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.005,     Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.0055,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));

            break;

        case ColorPaletteName::ExtremeL1:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.01,      Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.0105,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));
            
            break;

        case ColorPaletteName::ExtremeL2P5:            
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.025,     Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.0255,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));

            break;

        case ColorPaletteName::ExtremeL5:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.05,      Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.0505,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));

            break;

        case ColorPaletteName::ExtremeL10:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.1,       Color::fromRGBA_UI8(  0, 255,   0, 255)));
            pivots_.push_back(std::make_pair(0.1005,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));
                        
            break;

        case ColorPaletteName::ExtremeU0P1:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.9985,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.999,     Color::fromRGBA_UI8(255,   0,   0,   0)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0,   0)));

            break;

        case ColorPaletteName::ExtremeU0P5:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.9945,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.995,     Color::fromRGBA_UI8(255,   0,   0,   0)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0,   0)));
            
            break;

        case ColorPaletteName::ExtremeU1:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.9895,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.99,      Color::fromRGBA_UI8(255,   0,   0,   0)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0,   0)));

            break;

        case ColorPaletteName::ExtremeU2P5:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.9745,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.975,     Color::fromRGBA_UI8(255,   0,   0,   0)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0,   0)));
                    
            break;

        case ColorPaletteName::ExtremeU5:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.9495,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.95,      Color::fromRGBA_UI8(255,   0,   0,   0)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0,   0)));

            break;

        case ColorPaletteName::ExtremeU10:
            pivots_.push_back(std::make_pair(0.0,       Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.8995,    Color::fromRGBA_UI8(255, 255, 255, 255)));
            pivots_.push_back(std::make_pair(0.9,       Color::fromRGBA_UI8(255,   0,   0,   0)));
            pivots_.push_back(std::make_pair(1.0,       Color::fromRGBA_UI8(255,   0,   0,   0)));
            
            break;

        default:
            throw ArgumentException("colorPalette", exc_bad_color_palette, SOURCE_INFO);
    }
}

//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::color::Color nct::color::ColorPalette::operator()(double t)
{
    auto c = evalColor(t);
    auto a = evalAlpha(t);
    c.setOpacity(c.opacity() * a);

    return c;
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void nct::color::ColorPalette::clear()
{
    pivots_.clear();
    alphaPivots_.clear();
}

//-----------------------------------------------------------------------------------------------------------------
const std::vector<std::pair<double, nct::color::Color>>& nct::color::ColorPalette::colorPivots() noexcept
{
    return pivots_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::color::ColorPalette::addPivot(double t, const Color& color)
{
    if (pivots_.size() == 0) {
        pivots_.push_back(std::make_pair(t, color));
    }
    else {
        bool eq = false;
        auto pos = pivots_.begin();
        for (; pos != pivots_.end(); ++pos) {
            if (pos->first == t) {
                eq = true;
                break;
            }
            else if (pos->first > t) {
                break;
            }
        }

        if (pos != pivots_.end()) {
            if (eq) {
                pos->second = color;
            }
            else {
                pivots_.insert(pos, std::make_pair(t, color));
            }    
        }
        else {
            pivots_.push_back(std::make_pair(t, color));
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
void nct::color::ColorPalette::clearPivots()
{
    pivots_.clear();
}

//-----------------------------------------------------------------------------------------------------------------
const std::vector<std::pair<double, double>>& nct::color::ColorPalette::alphaPivots() noexcept
{
    return alphaPivots_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::color::ColorPalette::addAlphaPivot(double t, double alpha)
{
    if (alphaPivots_.size() == 0) {
        alphaPivots_.push_back(std::make_pair(t, alpha));
    }
    else {
        bool eq = false;
        auto pos = alphaPivots_.begin();
        for (; pos != alphaPivots_.end(); ++pos) {
            if (pos->first == t) {
                eq = true;
                break;
            }
            else if (pos->first > t) {
                break;
            }
        }

        if (pos != alphaPivots_.end()) {
            if (eq) {
                pos->second = alpha;
            }
            else {
                alphaPivots_.insert(pos, std::make_pair(t, alpha));
            }
        }
        else {
            alphaPivots_.push_back(std::make_pair(t, alpha));
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
void nct::color::ColorPalette::clearAlphaPivots()
{
    alphaPivots_.clear();
}

//-----------------------------------------------------------------------------------------------------------------
nct::color::Color nct::color::ColorPalette::eval(double t)
{
    auto c = evalColor(t);
    auto a = evalAlpha(t);
    c.setOpacity(c.opacity() * a);

    return c;
}

//-----------------------------------------------------------------------------------------------------------------
nct::color::Color nct::color::ColorPalette::evalColor(double t)
{
    if (pivots_.size() == 0)
        return Color();

    auto cs = pivots_[0].second.colorSpace();
    if (pivots_.size() == 1) {
        if (t < pivots_[0].first)
            return Color(0., 0., 0., 1.0, cs);
        else
            return pivots_[0].second;
    }

    auto n = pivots_.size();

    if (t <= pivots_[0].first)
        return pivots_[0].second;
    else if (t >= pivots_[n-1].first)
        return pivots_[n-1].second;

    size_t index = 0;
    n--;
    for (index = 1; index < n; index++) {
        if (t < pivots_[index].first)
            break;
    }

    auto tt = (t - pivots_[index - 1].first) / (pivots_[index].first - pivots_[index - 1].first);
    if (tt < 0.0)
        tt = 0.0;
    if (tt > 1.0)
        tt = 1.0;
    
    if ((pivots_[index - 1].second.colorSpace() != cs) || (pivots_[index].second.colorSpace() != cs)) {
        auto c1 = pivots_[index - 1].second.convertTo(cs);
        auto c2 = pivots_[index].second.convertTo(cs);

        return Color(
            (1 - tt)*c1.component1() + tt*c2.component1(), 
            (1 - tt)*c1.component2() + tt*c2.component2(), 
            (1 - tt)*c1.component3() + tt*c2.component3(), 
            (1 - tt)*c1.opacity() + tt*c2.opacity(), cs);

    }

    auto& c1 = pivots_[index - 1].second;
    auto& c2 = pivots_[index].second;

    return Color(
        (1 - tt)*c1.component1() + tt * c2.component1(),
        (1 - tt)*c1.component2() + tt * c2.component2(),
        (1 - tt)*c1.component3() + tt * c2.component3(),
        (1 - tt)*c1.opacity() + tt * c2.opacity(), cs);    
}

//-----------------------------------------------------------------------------------------------------------------
double nct::color::ColorPalette::evalAlpha(double t)
{
    if (alphaPivots_.size() == 0)
        return 1.0;

    if (alphaPivots_.size() == 1) {
        if (t < alphaPivots_[0].first)
            return 1.0;
        else
            return alphaPivots_[0].second;
    }

    auto n = alphaPivots_.size();

    if (t <= alphaPivots_[0].first)
        return alphaPivots_[0].second;
    else if (t >= alphaPivots_[n - 1].first)
        return alphaPivots_[n - 1].second;

    size_t index = 0;
    n--;
    for (index = 1; index < n; index++) {
        if (t < alphaPivots_[index].first)
            break;
    }

    auto tt = (t - alphaPivots_[index - 1].first) / (alphaPivots_[index].first - alphaPivots_[index - 1].first);
    if (tt < 0.0)
        tt = 0.0;
    if (tt > 1.0)
        tt = 1.0;

    return (1-tt)*alphaPivots_[index - 1].second + tt* alphaPivots_[index].second;
}

//-----------------------------------------------------------------------------------------------------------------
std::vector<nct::color::Color> nct::color::ColorPalette::palette(size_t size)
{
    if (alphaPivots_.size() == 0)
        return paletteColors(size);

    auto cols = paletteColors(size);

    if (pivots_.size() == 0) {
        auto alpha = evalAlpha(0);
        for (index_t i = 0; i < size; i++)
            cols[i].setOpacity(alpha * cols[i].opacity());
    }
    if (pivots_.size() == 1) {
        auto alpha = evalAlpha(pivots_[0].first);
        for (index_t i = 0; i < size; i++)
            cols[i].setOpacity(alpha * cols[i].opacity());
    }
    else {
        double mint = pivots_[0].first;
        double maxt = pivots_[pivots_.size() - 1].first;

        if (alphaPivots_.size() == 1) {
            for (index_t i = 0; i < size; i++) {
                auto t = mint + (maxt - mint) * (static_cast<double>(i) / static_cast<double>(size - 1));
                auto alpha = (t >= alphaPivots_[0].first) ? alphaPivots_[0].first : 1.0;
                cols[i].setOpacity(alpha * cols[i].opacity());

            }
        }
        else {
            size_t index = 1;
            auto n = alphaPivots_.size() - 1;
            for (index_t i = 0; i < size; i++) {
                auto t = mint + (maxt - mint) * (static_cast<double>(i) / static_cast<double>(size - 1));

                for (; index < n; index++) {
                    if (t < alphaPivots_[index].first)
                        break;
                }

                auto tt = (t - alphaPivots_[index - 1].first) / 
                    (alphaPivots_[index].first - alphaPivots_[index - 1].first);
                auto alpha = (1 - tt)*alphaPivots_[index - 1].second + tt * alphaPivots_[index].second;
                if (tt < 0.0)
                    tt = 0.0;
                if (tt > 1.0)
                    tt = 1.0;

                cols[i].setOpacity(alpha * cols[i].opacity());
            }
        }        
    }

    return cols;

}

//-----------------------------------------------------------------------------------------------------------------
std::vector<nct::color::Color> nct::color::ColorPalette::paletteColors(size_t size)
{
    if (pivots_.size() == 0)
        return std::vector<nct::color::Color>(size, Color());
    else if (pivots_.size() == 1)
        return std::vector<nct::color::Color>(size, pivots_[0].second);

    double mint = pivots_[0].first;
    double maxt = pivots_[pivots_.size() - 1].first;
    auto cs = pivots_[0].second.colorSpace();
    std::vector<nct::color::Color> cols(size);

    size_t index = 1;
    auto n = pivots_.size() - 1;
    for (index_t i = 0; i < size; i++) {
        auto t = mint + (maxt - mint) * (static_cast<double>(i) / static_cast<double>(size - 1));
        
        
        for (; index < n; index++) {
            if (t < pivots_[index].first)
                break;
        }

        auto tt = (t - pivots_[index - 1].first) / (pivots_[index].first - pivots_[index - 1].first);
        if (tt < 0.0)
            tt = 0.0;
        if (tt > 1.0)
            tt = 1.0;

        if ((pivots_[index - 1].second.colorSpace() != cs) || (pivots_[index].second.colorSpace() != cs)) {
            auto c1 = pivots_[index - 1].second.convertTo(cs);
            auto c2 = pivots_[index].second.convertTo(cs);

            cols[i] = Color(
                (1 - tt)*c1.component1() + tt * c2.component1(),
                (1 - tt)*c1.component2() + tt * c2.component2(),
                (1 - tt)*c1.component3() + tt * c2.component3(),
                (1 - tt)*c1.opacity() + tt * c2.opacity(), cs);

        }

        auto& c1 = pivots_[index - 1].second;
        auto& c2 = pivots_[index].second;

        cols[i] = Color(
            (1 - tt)*c1.component1() + tt * c2.component1(),
            (1 - tt)*c1.component2() + tt * c2.component2(),
            (1 - tt)*c1.component3() + tt * c2.component3(),
            (1 - tt)*c1.opacity() + tt * c2.opacity(), cs);
    }

    return cols;
}

//-----------------------------------------------------------------------------------------------------------------
std::vector<double> nct::color::ColorPalette::paletteAlphas(size_t size)
{
    if (alphaPivots_.size() == 0)
        return std::vector<double>(size, 1.0);
    else if (alphaPivots_.size() == 1)
        return std::vector<double>(size, alphaPivots_[0].second);

    double mint = alphaPivots_[0].first;
    double maxt = alphaPivots_[alphaPivots_.size() - 1].first;
    std::vector<double> alphas(size);

    size_t index = 1;
    auto n = alphaPivots_.size() - 1;
    for (index_t i = 0; i < size; i++) {
        auto t = mint + (maxt - mint) * (static_cast<double>(i) / static_cast<double>(size - 1));


        for (; index < n; index++) {
            if (t < alphaPivots_[index].first)
                break;
        }

        auto tt = (t - alphaPivots_[index - 1].first) / 
            (alphaPivots_[index].first - alphaPivots_[index - 1].first);
        if (tt < 0.0)
            tt = 0.0;
        if (tt > 1.0)
            tt = 1.0;

        alphas[i] = (1 - tt)*alphaPivots_[index - 1].second + tt * alphaPivots_[index].second;
    }
    return alphas;
}

//-----------------------------------------------------------------------------------------------------------------
std::vector<std::string> nct::color::ColorPalette::rgbStrings(size_t size)
{
    std::vector<std::string> str(size);
    auto cols = paletteColors(size);
    for (index_t i = 0; i < size; i++)
        str[i] = cols[i].hexString(true, false);

    return str;
}

//-----------------------------------------------------------------------------------------------------------------
std::vector<std::string> nct::color::ColorPalette::rgbaStrings(size_t size)
{
    std::vector<std::string> str(size);
    auto cols = palette(size);
    for (index_t i = 0; i < size; i++)
        str[i] = cols[i].hexString(true, true);

    return str;
}

//-----------------------------------------------------------------------------------------------------------------
std::vector<nct::color::ColorPalette::ColorPaletteName> nct::color::ColorPalette::colorPalettes()
{
    std::vector<ColorPaletteName> pal(40);
    for (index_t i = 0; i < pal.size(); i++)
        pal[i] = static_cast<ColorPaletteName>(i);
    return pal;
}

//-----------------------------------------------------------------------------------------------------------------
std::vector<std::string> nct::color::ColorPalette::colorPaletteNames()
{
    std::vector<std::string> pal(40);

    pal[static_cast<size_t>(ColorPaletteName::Rainbow)] = "Rainbow";
    pal[static_cast<size_t>(ColorPaletteName::Heat)] = "Heat";
    pal[static_cast<size_t>(ColorPaletteName::Bone)] = "Bone";
    pal[static_cast<size_t>(ColorPaletteName::Cool)] = "Cool";
    pal[static_cast<size_t>(ColorPaletteName::Cooper)] = "Cooper";
    pal[static_cast<size_t>(ColorPaletteName::Gray)] = "Gray";
    pal[static_cast<size_t>(ColorPaletteName::Hot)] = "Hot";
    pal[static_cast<size_t>(ColorPaletteName::Spring)] = "Spring";
    pal[static_cast<size_t>(ColorPaletteName::Summer)] = "Summer";
    pal[static_cast<size_t>(ColorPaletteName::Autumn)] = "Autumn";
    pal[static_cast<size_t>(ColorPaletteName::Winter)] = "Winter";
    pal[static_cast<size_t>(ColorPaletteName::Jet)] = "Jet";
    pal[static_cast<size_t>(ColorPaletteName::SignalQuality)] = "Signal quality";
    pal[static_cast<size_t>(ColorPaletteName::NegativePositive)] = "Negative-Positive";
    pal[static_cast<size_t>(ColorPaletteName::WhiteToRed)] = "White to red";
    pal[static_cast<size_t>(ColorPaletteName::WhiteToGreen)] = "White to green";
    pal[static_cast<size_t>(ColorPaletteName::WhiteToBlue)] = "White to blue";
    pal[static_cast<size_t>(ColorPaletteName::Gcwyr)] = "Green-Cyan-White-Yellow-Red";
    pal[static_cast<size_t>(ColorPaletteName::Wygbor)] = "White-Yellow-Green-Blue-Orange-Red";
    pal[static_cast<size_t>(ColorPaletteName::Spectrum)] = "Color Spectrum";
    pal[static_cast<size_t>(ColorPaletteName::Extreme)] = "Extreme values";
    pal[static_cast<size_t>(ColorPaletteName::Extreme2)] = "Extreme values 2";
    pal[static_cast<size_t>(ColorPaletteName::Extreme0P1)] = "Extreme values 0.1%";
    pal[static_cast<size_t>(ColorPaletteName::Extreme0P5)] = "Extreme values 0.5%";
    pal[static_cast<size_t>(ColorPaletteName::Extreme1)] = "Extreme values 1.0%";
    pal[static_cast<size_t>(ColorPaletteName::Extreme2P5)] = "Extreme values 2.5%";
    pal[static_cast<size_t>(ColorPaletteName::Extreme5)] = "Extreme values 5.0%";
    pal[static_cast<size_t>(ColorPaletteName::Extreme10)] = "Extreme values 10.0%";
    pal[static_cast<size_t>(ColorPaletteName::ExtremeL0P1)] = "Lower extreme values 0.1%";
    pal[static_cast<size_t>(ColorPaletteName::ExtremeL0P5)] = "Lower extreme values 0.5%";
    pal[static_cast<size_t>(ColorPaletteName::ExtremeL1)] = "Lower extreme values 1.0%";
    pal[static_cast<size_t>(ColorPaletteName::ExtremeL2P5)] = "Lower extreme values 2.5%";
    pal[static_cast<size_t>(ColorPaletteName::ExtremeL5)] = "Lower extreme values 5.0%";
    pal[static_cast<size_t>(ColorPaletteName::ExtremeL10)] = "Lower extreme values 10.0%";
    pal[static_cast<size_t>(ColorPaletteName::ExtremeU0P1)] = "Upper extreme values 0.1%";
    pal[static_cast<size_t>(ColorPaletteName::ExtremeU0P5)] = "Upper extreme values 0.5%";
    pal[static_cast<size_t>(ColorPaletteName::ExtremeU1)] = "Upper extreme values 1.0%";
    pal[static_cast<size_t>(ColorPaletteName::ExtremeU2P5)] = "Upper extreme values 2.5%";
    pal[static_cast<size_t>(ColorPaletteName::ExtremeU5)] = "Upper extreme values 5.0%";
    pal[static_cast<size_t>(ColorPaletteName::ExtremeU10)] = "Upper extreme values 10.0%";

    return pal;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
