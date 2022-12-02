//=================================================================================================================
/**
 *  @file       ResultsDialog.h
 *  @brief      ResultsDialog class.
 *  @details    Declaration file of the ResultsDialog class.  
 *  @author     Omar Mendoza Montoya (email: omendoz@live.com.mx).
 *
 *  @copyright  Copyright (c) 2022 Omar Mendoza Montoya. All rights reserved. \n \n
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

#ifndef RESULTS_DIALOG_H_INCLUDE
#define RESULTS_DIALOG_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include "ui_ResultsDialog.h"
#include "MainWindow.h"

#include "nct/nct.h"
#include "nct/Array.h"
#include "nct/Vector3D.h"

//=================================================================================================================
/**
 *  @class      ResultsDialog
 *  @brief      Results dialog.
 *  @details    This dialog is used to show the results of a comparison with a collection.
 */
class ResultsDialog : public QDialog
{        
    Q_OBJECT

public:    

    //// Constructors and destructor /////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes the dialog.
     *  @param[in]  objFather  The father object.
     */
    ResultsDialog(QWidget* objFather = 0);

    /**
     *  @brief      Copy constructor.
     *  @details    This constructor is deleted.
     */
    ResultsDialog(const ResultsDialog&) = delete;

    /**
     *  @brief      Move constructor.
     *  @details    This constructor is deleted.
     */
    ResultsDialog(ResultsDialog&&) = delete;

    /**
     *  @brief      Destructor.
     *  @details    Class destructor.
     */
    ~ResultsDialog() = default;

    ////////// Operators //////////

    /**
     *  @brief      Assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    ResultsDialog& operator=(const ResultsDialog&) = delete;

    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    ResultsDialog& operator=(ResultsDialog&&) = delete;

    //// Methods /////
        
    /**
     *  @brief      Set results.
     *  @details    This function configures the results to be shown in the interface
     *  @param[in]  sItems  Initides with the sorted items.
     */
    void setResults(const nct::Array<unsigned int>& sItems);

    /**
     *  @brief      Set mesh data.
     *  @details    This function sets the mesh data of the model collection.
     *  @param[in]  data  The new configuration data.
     */
    void setMeshData(const MainWindow::MeshData& meshData);

public slots:

    /**
     *  @brief      Open results.
     *  @details    This method opens a results file.
     */
    void open();

    /**
     *  @brief      Save results.
     *  @details    This method save a results file.
     */
    void save();

    /**
     *  @brief      Show page.
     *  @details    This method shows the selected page.
     *  @param[in]  i  The index of the selected page.
     */
    void showPage(int i);

private:
    
    //// Methods /////

    /**
     *  @brief      Show error message.
     *  @details    Shows a dialog with the information of the last error that ocurred in the
     *              user interface.
     *  @param[in]  message  Message to be shown.
     *  @param[in]  exception  Data of the exception.
     */
    void showErrorMessage(const QString& message, const std::exception* exception);

    //// Member variables ////    

    Ui::ResultsDialog ui_;                      /**< User interface. */

    MainWindow::MeshData meshData_;             /**< Mesh data of the collection.*/

    nct::Array<unsigned int> sortedItems_;      /**< Sorted items.*/

};

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
