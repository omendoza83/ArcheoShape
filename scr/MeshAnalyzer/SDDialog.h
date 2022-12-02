//===========================================================================================================
/**
 *  @file       SDDialog.h
 *  @brief      SDDialog class.
 *  @details    SDDialog file of the RSDDialog class.      
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
//===========================================================================================================

#ifndef SD_DIALOG_H_INCLUDE
#define SD_DIALOG_H_INCLUDE

//===========================================================================================================
//        HEADERS
//===========================================================================================================
#include "ui_SDDialog.h"
#include "MainWindow.h"

#include "nct/nct.h"
#include "nct/Array.h"
#include "nct/Vector3D.h"

//===========================================================================================================

/**
 *  @class      SDDialog
 *  @brief      Shape distributions dialog.
 *  @details    This dialog is used to calculate the shape distributions of one model.
 */
class SDDialog : public QDialog
{        
    Q_OBJECT

public:    
    
    //// Constructors and destructor /////
      
    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes the dialog.
     *  @param[in]  objFather  The father object.
     */
    SDDialog(QWidget* objFather = 0);

    /**
     *  @brief      Copy constructor.
     *  @details    This constructor is deleted.
     */
    SDDialog(const SDDialog&) = delete;

    /**
     *  @brief      Move constructor.
     *  @details    This constructor is deleted.
     */
    SDDialog(SDDialog&&) = delete;

    /**
     *  @brief      Destructor.
     *  @details    Class destructor.
     */
    ~SDDialog() = default;

    ////////// Operators //////////

    /**
     *  @brief      Assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    SDDialog& operator=(const SDDialog&) = delete;

    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    SDDialog& operator=(SDDialog&&) = delete;

    //// Methods /////
    
    /**
     *  @brief      Set model.
     *  @details    This function sets the model to be processed.
     *  @param[in]  vertices  If non-null, indicates the vertices of the model.
     *  @param[in]  triangles  If non-null, the triangles that define the mesh.
     */
    void setModel(const std::shared_ptr<nct::Array<nct::Point3D>>& vertices,
        const std::shared_ptr<nct::Array<nct::Vector3D<unsigned int>>>& triangles);

    /**
     *  @brief      Set mesh data.
     *  @details    This function sets the mesh data of the model collection.
     *  @param[in]  meshData  The new configuration data.
     */
    void setMeshData(const MainWindow::MeshData& meshData);

public slots:

    //// Slots /////    
        
    /**
     *  @brief      Calculate the descriptor.
     *  @details    This method calculates the descriptor and shows it in the user interface.
     */
    void calculate();

    /**
     *  @brief      Compare descriptor.
     *  @details    This method compares the descriptor with the mesh collection.
     */
    void compare();

    /**
     *  @brief      Save descriptor.
     *  @details    This method saves the calculated descriptor.
     */
    void save();
    
private:
    
    //// Methods /////

    void showErrorMessage(const QString& message, const std::exception* exception);    

    //// Member variables ////    

    Ui::SDDialog ui_;                                           /**< User interface. */

    nct::Array<double> histograms_[5];                          /**< Histograms.*/

    nct::Array<double> bins_[5];                                /**< Histogram bins.*/

    MainWindow::MeshData meshData_;                             /**< Mesh data of the collection.*/

    std::shared_ptr<nct::Array<nct::Point3D>> vertices_;                    /**< Array with the vertices of the model. */

    std::shared_ptr<nct::Array<nct::Vector3D<unsigned int>>> triangles_;    /**< Array with the triangles of the model. */
};

#endif
//===========================================================================================================
//        END OF FILE
//===========================================================================================================
