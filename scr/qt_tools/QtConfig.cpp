//=================================================================================================================
/**
 *  @file       QtConfig.cpp
 *  @brief      qt_tools::QtConfig class implementation file.
 *  @details    This file contains the implementation of the qt_tools::QtConfig class.
 *  @author     Omar Mendoza Montoya (email: omendoz@live.com.mx).
 *  @copyright  Copyright (c) 2014 Omar Mendoza Montoya \n \n
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
#include <qt_tools/QtConfig.h>
#include <nct/math/math.h>

#include <QtGui/QFontInfo>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
qt_tools::QtConfig::QtConfig()
{
    defaultFont_ = "";            


    fontSize_ = 14.0;            

    smallFontSize_ = 10.0;            

    bigFontSize_ = 18.0;            


    plotFontSize_ = 18.0;        

    smallPlotFontSize_ = 14.0;    
    
    bigPlotFontSize_ = 20.0;    
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
qt_tools::QtConfig& qt_tools::QtConfig::instance()
{
    static QtConfig bciConfig;                                 
    return bciConfig;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::QtConfig::setDefaultFontName(const QString& name)
{
    defaultFont_ = name;
}

//-----------------------------------------------------------------------------------------------------------------
QString qt_tools::QtConfig::defaultFontName()
{
    if (defaultFont_.length() > 0)
        return defaultFont_;

    if (QFontInfo(QFont("Roboto Medium")).exactMatch())
        defaultFont_ = "Roboto Medium";    
    else if (QFontInfo(QFont("Helvetica")).exactMatch())
        defaultFont_ = "Helvetica";
    else if (QFontInfo(QFont("Calibri")).exactMatch())
        defaultFont_ = "Calibri";
    else
        defaultFont_ = "Arial";

    return defaultFont_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::QtConfig::setDefaultFontSize(double size) noexcept
{
    fontSize_ = nct::math::max(0.0, size);
}

//-----------------------------------------------------------------------------------------------------------------
double qt_tools::QtConfig::defaultFontSize() noexcept
{
    return fontSize_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::QtConfig::setDefaultSmallFontSize(double size) noexcept
{
    smallFontSize_ = nct::math::max(0.0, size);
}

//-----------------------------------------------------------------------------------------------------------------
double qt_tools::QtConfig::defaultSmallFontSize() noexcept
{
    return smallFontSize_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::QtConfig::setDefaultBigFontSize(double size) noexcept
{
    bigFontSize_ = nct::math::max(0.0, size);
}

//-----------------------------------------------------------------------------------------------------------------
double qt_tools::QtConfig::defaultBigFontSize() noexcept
{
    return bigFontSize_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::QtConfig::setDefaultPlotFontSize(double size) noexcept
{
    plotFontSize_ = nct::math::max(0.0, size);
}

//-----------------------------------------------------------------------------------------------------------------
double qt_tools::QtConfig::defaultPlotFontSize() noexcept
{
    return plotFontSize_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::QtConfig::setDefaultSmallPlotFontSize(double size) noexcept
{
    smallPlotFontSize_ = nct::math::max(0.0, size);
}

//-----------------------------------------------------------------------------------------------------------------
double qt_tools::QtConfig::defaultSmallPlotFontSize() noexcept
{
    return smallPlotFontSize_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::QtConfig::setDefaultBigPlotFontSize(double size) noexcept
{
    bigPlotFontSize_ = nct::math::max(0.0, size);
}

//-----------------------------------------------------------------------------------------------------------------
double qt_tools::QtConfig::defaultBigPlotFontSize() noexcept
{
    return bigPlotFontSize_;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
