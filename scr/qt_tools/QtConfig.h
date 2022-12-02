//=================================================================================================================
/**
 *  @file       QtConfig.h
 *  @brief      qt_tools::QtConfig class.
 *  @details    Declaration of the qt_tools::QtConfig class.
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

#ifndef QT_TOOLS_QT_CONFIG_H_INCLUDE
#define QT_TOOLS_QT_CONFIG_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <qt_tools/qt_tools.h>
#include <nct/nct_exception.h>

#include<QtCore/QString>

//=================================================================================================================
namespace qt_tools {

/**
 *  @brief      QT configuration.
 *  @details    This singleton class manages the global configuration of the implemented widgets. 
 *              Any application can use this class to obtain the global parameters of this library.
 */
class QT_TOOLS_EXPIMP QtConfig {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Copy constructor.
     *  @details    This constructor is deleted.
     */
    QtConfig(const QtConfig&) = delete;
    
    /**
     *  @brief      Move constructor.
     *  @details    This constructor is deleted.
     */
    QtConfig(QtConfig&&) = delete;
    
    ////////// Destructor //////////

    /**
     *  @brief      Destructor.
     *  @details    Class destructor. 
     */
    ~QtConfig() = default;

    ////////// Operators //////////
    
    /**
     *  @brief      Assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    QtConfig& operator=(const QtConfig&) = delete;
    
    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    QtConfig& operator=(QtConfig&&) = delete;

    ////////// Member functions //////////

    /**
     *  @brief      Return single instance.
     *  @details    This function returns the unique instance of this class.
     *  @returns    The unique instance of the class.
     */
    static QtConfig& instance();

    /**
     *  @brief      Set default font name.
     *  @details    This function sets the default font name.
     *  @param[in]  name  The new default font name.
     */
    void setDefaultFontName(const QString& name);

    /**
     *  @brief      Default font name.
     *  @details    This function returns the default font name.
     *  @returns    The default font name.
     */
    QString defaultFontName();

    /**
     *  @brief      Set default font size.
     *  @details    This function sets the default font size.
     *  @param[in]  size  The new font size.
     */
    void setDefaultFontSize(double size) noexcept;

    /**
     *  @brief      Default font size.
     *  @details    This function returns the default font size.
     *  @returns    The default font size.
     */
    double defaultFontSize() noexcept;

    /**
     *  @brief      Set default small font size.
     *  @details    This function sets the default small font size.
     *  @param[in]  size  The new font size.
     */
    void setDefaultSmallFontSize(double size) noexcept;

    /**
     *  @brief      Default small font size.
     *  @details    This function returns the default small font size.
     *  @returns    The default small font size.
     */
    double defaultSmallFontSize() noexcept;

    /**
     *  @brief      Set default big font size.
     *  @details    This function sets the default big font size.
     *  @param[in]  size  The new font size.
     */
    void setDefaultBigFontSize(double size) noexcept;

    /**
     *  @brief      Default big font size.
     *  @details    This function returns the default big font size.
     *  @returns    The default big font size.
     */
    double defaultBigFontSize() noexcept;

    /**
     *  @brief      Set default font size for plots.
     *  @details    This function sets the default font size for plots.
     *  @param[in]  size  The new font size.
     */
    void setDefaultPlotFontSize(double size) noexcept;

    /**
     *  @brief      Default font size for plots.
     *  @details    This function returns the default font size for plots.
     *  @returns    The default font size for plots.
     */
    double defaultPlotFontSize() noexcept;

    /**
     *  @brief      Set default small font size for plots.
     *  @details    This function sets the default small font size for plots.
     *  @param[in]  size  The new font size.
     */
    void setDefaultSmallPlotFontSize(double size) noexcept;

    /**
     *  @brief      Default small font size for plots.
     *  @details    This function returns the default small font size for plots.
     *  @returns    The default small font size for plots.
     */
    double defaultSmallPlotFontSize() noexcept;

    /**
     *  @brief      Set default big font size for plots.
     *  @details    This function sets the default big font size for plots.
     *  @param[in]  size  The new font size.
     */
    void setDefaultBigPlotFontSize(double size) noexcept;

    /**
     *  @brief      Default big font size for plots.
     *  @details    This function returns the default big font size for plots.
     *  @returns    The default big font size for plots.
     */
    double defaultBigPlotFontSize() noexcept;

private:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the default configuration.
     */
    QtConfig();

    ////////// Data members //////////

    QString defaultFont_;               /**< Default font used by the  */


    double fontSize_ {0};               /**< Default font size. */

    double smallFontSize_ {0};          /**< Default small font size. */

    double bigFontSize_ {0};            /**< Default big font size. */


    double plotFontSize_ {0};           /**< Default plot font size. */

    double smallPlotFontSize_ {0};      /**< Default small plot font size. */

    double bigPlotFontSize_ {0};        /**< Default big plot font size. */

};

}

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
