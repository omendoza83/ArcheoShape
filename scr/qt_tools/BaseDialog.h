//=================================================================================================================
/**
 *  @file       BaseDialog.h
 *  @brief      qt_tools::BaseDialog class.
 *  @details    Declaration of the qt_tools::BaseDialog class.
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

#ifndef QT_TOOLS_BASE_DIALOG_H_INCLUDE
#define QT_TOOLS_BASE_DIALOG_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <qt_tools/qt_tools.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>

//=================================================================================================================
namespace qt_tools {

/**
 *  @brief      Base dialog.
 *  @details    Dialog which content is specified by an external widget.
 */
class QT_TOOLS_EXPIMP BaseDialog : public QDialog {
    Q_OBJECT

public:

    ////////// Constructors //////////

    /**
     *  @brief      Class constructor.
     *  @details    This constructor builds a dialog with a title and a secondary text around the
     *              contents.
     *  @param[in]  contents  Widget that defines the contents of the dialog.
     *  @param[in]  mainText  Main text of the dialog.
     *  @param[in]  secondaryText  Secondary text of the dialog.
     *  @param[in]  width  Dialog width.
     *  @param[in]  height  Dialog height.
     *  @param[in]  title  The title of the dialog.
     *  @param[in]  parent  The parent widget.
     */
    BaseDialog(QWidget* contents, const QString& mainText,
        const QString& secondaryText = "", unsigned int width = 400,
        unsigned int height = 200, const QString& title = tr("Dialog"),
        QWidget* parent = nullptr);
    
    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the specified arguments.
     *  @param[in]  contents  Widget that defines the contents of the dialog.
     *  @param[in]  width  Dialog width.
     *  @param[in]  height  Dialog height.
     *  @param[in]  title  The title of the dialog.
     *  @param[in]  parent  The parent widget.
     */
    BaseDialog(QWidget* contents, unsigned int width = 400,
        unsigned int height = 200, const QString& title = tr("Dialog"),
        QWidget* parent = nullptr);

    /**
     *  @brief      Copy constructor.
     *  @details    This constructor is deleted.
     */
    BaseDialog(const BaseDialog&) = delete;
    
    /**
     *  @brief      Move constructor.
     *  @details    This constructor is deleted.
     */
    BaseDialog(BaseDialog&&) = delete;
    
    ////////// Destructor //////////

    /**
     *  @brief      Destructor.
     *  @details    Class destructor. 
     */
    ~BaseDialog() = default;

    ////////// Operators //////////
    
    /**
     *  @brief      Assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    BaseDialog& operator=(const BaseDialog&) = delete;
    
    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    BaseDialog& operator=(BaseDialog&&) = delete;

signals:

    ////////// Signals //////////

    /**
     *  @brief      Dialog closed.
     *  @details    This signal is produced whenever the dialog is closed.
     */
    void closed();

private:

    ////////// Member functions //////////

    /**
     *  @brief      Close event.
     *  @details    This function is called whenever the widget is closed.
     *  @param[in]  e  Object that contains the information of the event.
     */
    void closeEvent(QCloseEvent* e) override;

    ////////// Data members //////////

};

}

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
