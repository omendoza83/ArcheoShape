//=================================================================================================================
/**
 *  @file       MainWindow.h
 *  @brief      MainWindow class.
 *  @details    Declaration file of the MainWindow class.
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

#ifndef MAIN_WINDOW_H_INCLUDE
#define MAIN_WINDOW_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include "ui_MainWindow.h"

#include "nct/nct.h"
#include "nct/Array.h"
#include "nct/Array2D.h"
#include "nct/Vector3D.h"
#include "nct/color/RgbColor.h"
#include <nct/signal/spherical_harmonics.h>

#include <QtGui/QtGui>
#include <QtCore/QVector>
#include <QtCore/QList>

//=================================================================================================================

/**
 *  @brief      Main window class.
 *  @details    This class is used to define and control the user interface of the program.
 */
class MainWindow : public QMainWindow
{        
    Q_OBJECT

public:    

    //// Structures /////

    /**
     *  @brief      Mesh data.
     *  @details    This structure defines the data of the mesh collection to analyze.
     */
    struct MeshData
    {
        QString featurePath;                /**< Path of the feature files. */        
        QString screenshotsPath;            /**< Path of the screenshot files. */
        
        unsigned int nModels;               /**<  Number of models. */
        unsigned int nInfo;                 /**<  Number of info fields. */
        nct::Array2D<QString> models;       /**<  Array of models. */
        std::vector<QString> infoFields;    /**<  Array of fields that describes the models. */

        unsigned int nSamps;                /**<  Number of samples that are used to calculate the shape distributions. */
        unsigned int nBins;                 /**<  Number of bins of the shape distributions. */
        unsigned int nVox;                  /**<  Array of divisions that are used in the model rasterization. */
        unsigned int nTestAng;              /**<  Number of test angles to compare symmetry descriptors. */
        unsigned int nTestSteps;            /**<  Number of steps to compare shape dsitributions. */
        double iniStep;                     /**<  Initial step to compare shape dsitributions. */
        double endStep;                     /**<  Final step to compare shape dsitributions. */
    };

    //// Constructors and destructor /////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes the window.
     *  @param[in]  objFather  The father object.
     */
    MainWindow(QWidget* objFather = 0);

    /**
     *  @brief      Copy constructor.
     *  @details    This constructor is deleted.
     */
    MainWindow(const MainWindow&) = delete;

    /**
     *  @brief      Move constructor.
     *  @details    This constructor is deleted.
     */
    MainWindow(MainWindow&&) = delete;

    /**
     *  @brief      Destructor.
     *  @details    Class destructor.
     */
    ~MainWindow() = default;

    ////////// Operators //////////

    /**
     *  @brief      Assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    MainWindow& operator=(const MainWindow&) = delete;

    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    MainWindow& operator=(MainWindow&&) = delete;
    
    //// Methods /////

    /**
     *  @brief      Block signals.
     *  @details    Sets the disabled the signals of several controls.
     *  @param[in]  blockSignals New state of the signals. True to disable them.
     */
    void blockControlSignals(bool blockSignals);

    /**
     *  @brief      Decode mesh data.
     *  @details    This function decodes the mesh data stored in a byte array.
     *  @param[in]  meshData  The array with the mesh data.
     */
    static MeshData decodeMeshData(const QByteArray& meshData);

    /**
     *  @brief      Decode matrix.
     *  @details    This function decodes a matrix stored in a binary array file.
     *  @param[in]  arrayData  The binary array with the data.
     *  @returns    The decoded matrix.
     */
    static nct::Matrix decodeMatrixFile(const QString& arrayFile);

    /**
     *  @brief      Decode vector.
     *  @details    This function decodes a vector stored in a binary array file.
     *  @param[in]  arrayData  The binary array with the data.
     *  @returns    The decoded vector.
     */
    static nct::RealVector decodeVectorFile(const QString& arrayFile);

    /**
     *  @brief      Decode harmonic array.
     *  @details    This function decodes an array of harmonic funtions stored in a binary array file.
     *  @param[in]  arrayData  The binary array with the data.
     *  @returns    The decoded array.
     */
    static nct::Array<nct::signal::spherical_harmonics::SphericalHarmonic> decodeHarmonicFile(const QString& arrayFile);

private slots:

    //// Slots /////
    
    /**
     *  @brief      About box dialog.
     *  @details    Shows the about dialog.
     */
    void about();

    /**
     *  @brief      Load data.
     *  @details    Loads one model.
     */
    void loadModel();

    /**
     *    @brief    Load config file.
     *    @details  This function shows the open file dialog to select a configuration file.
     */
    void loadConfigFile();

    /**
     *  @brief      Load config file.
     *  @details    Loads the specified configuration file. 
     *  @param[in]  fileName  The file to open and load.  
     */
    void loadConfigFile(const QString& fileName);

    /**
     *  @brief      Redraw scene.
     *  @details    Redraws the complete scene.
     */
    void redraw();
    
    /**
     *  @brief      Reset scene.
     *  @details    Resets the scene and sets the properties to their default values.
     */
    void reset();

    /**
     *  @brief      Change color.
     *  @details    Modifies the color of the solid object.
     */
    void changeColor();

    /**
     *  @brief      Change lightning.
     *  @details    Changes the properties of the lightning.
     */
    void changeLight();

    /**
     *  @brief      Changed drawing mode.
     *  @details    Modifies the drawing mode of the solid.
     */
    void changeMode();

    /**
     *  @brief      Show SD dialog.
     *  @details    Shows the SD dialog.
     */
    void showSDDialog();

    /**
     *  @brief      Show RSD dialog.
     *  @details    Shows the RSD dialog.
     */
    void showRSDDialog();

    /**
     *  @brief      Show HM dialog.
     *  @details    Shows the HM dialog.
     */
    void showHMDialog();

    /**
     *  @brief      Show the results dialog.
     *  @details    Shows the results dialog.
     */
    void showResultsDialog();    

private:

    //// Methods /////

    /**
     *  @brief      Show error message.
     *  @details    Shows a dialog with the information of the last error that ocurred in the
     *              user interface.
     *  @param[in]  message  Message to be shown.
     *  @param[in]  exception  Data of the exception.
     */
    void showErrorMessage(const QString& message, const std::exception* exception = nullptr);        
    
    //// Member variables ////        

    Ui::MainWindow ui_;                                             /**< User interface. */

    MainWindow::MeshData meshData_;                                 /**< Mesh data of the collection.*/

    std::shared_ptr<nct::Array<nct::Point3D>> vertices_;           /**< Array with the vertices of the model. */
    
    std::shared_ptr<nct::Array<nct::Vector3D<double>>> normals_;     /**< Array with the normals of the model. */
    
    std::shared_ptr<nct::Array<nct::Vector3D<unsigned int>>> triangles_;    /**< Array with the triangles of the model. */

    QString modelName_;                                             /**< Model name. */

    nct::color::RgbColor color_;                                    /**< Model color. */
};

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
