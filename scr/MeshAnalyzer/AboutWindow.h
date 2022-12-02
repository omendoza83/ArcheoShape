//=================================================================================================================
/**
 *  @file       AboutWindow.h
 *  @brief      AboutWindow class. 
 *  @details    Declaration file of the AboutWindow class.              
 *  @author     Omar Mendoza Montoya (email: omendoz@live.com.mx).
 * 
 *  @copyright  Copyright (c) 2022 Omar Mendoza Montoya \n \n
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

#ifndef ABOUT_WINDOW_H_INCLUDE
#define ABOUT_WINDOW_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================

#include "ui_AboutWindow.h"

//=================================================================================================================

/**
 *  @class      AboutWindow
 *  @brief      About dialog.
 *  @details    Defines the about dialog box of the application.
 */
class AboutWindow : public QDialog
{        
    Q_OBJECT

public:    

    //// Constructors and destructor /////

    /**
     *  @brief      Default constructor.
     *  @details    Initializes the dialog.
     *  @param[in]  objFather  Parent object.
     */
    AboutWindow(QWidget *objFather = 0):QDialog(objFather)
    {
        ui_.setupUi(this);    
    }
    
    /**
     *  @brief      Copy constructor.
     *  @details    This constructor is deleted.
     */
    AboutWindow(const AboutWindow&) = delete;

    /**
     *  @brief      Move constructor.
     *  @details    This constructor is deleted.
     */
    AboutWindow(AboutWindow&&) = delete;

    /**
     *  @brief      Destructor.
     *  @details    Class destructor.
     */
    ~AboutWindow() = default;

    ////////// Operators //////////

    /**
     *  @brief      Assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    AboutWindow& operator=(const AboutWindow&) = delete;

    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    AboutWindow& operator=(AboutWindow&&) = delete;

    //// Member variables ////            

    Ui::AboutWindow ui_;      /**< User interface. */

};

#endif
//===========================================================================================================
//        END OF FILE
//===========================================================================================================
