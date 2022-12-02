//=================================================================================================================
/**
 *  @file       MainWindow.cpp
 *  @brief      MainWindow class implementation file.
 *  @details    This file contains the implementation of the MainWindow class.                  
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

//=================================================================================================================
//        HEADERS AND NAMESPACES
//=================================================================================================================
#include <fstream>
#include <string>

#include "MainWindow.h"
#include "AboutWindow.h"
#include "ResultsDialog.h"
#include "HMDialog.h"
#include "RSDDialog.h"
#include "SDDialog.h"

#include "nct/nct_utils.h"
#include "nct/nct_exception.h"
#include "nct/geometry/mesh.h"
#include "nct/geometry/StlMesh.h"
#include "nct/geometry/PlyMesh.h"
#include "nct/geometry/RasterizedObject3D.h"
#include "qt_tools/graphics_3d/TriangularMesh.h"
#include "qt_tools/graphics_3d/VoxelizedObject.h"
#include "qt_tools/QtConfig.h"

#include <QtCore/QFileInfo>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QColorDialog>

using namespace std;
using namespace nct;
using namespace nct::geometry;
using namespace qt_tools;
using namespace qt_tools::graphics_3d;

//=================================================================================================================
//        CONSTRUCTORS AND DESTRUCTOR
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *objFather): QMainWindow(objFather)
{
    ui_.setupUi(this);        
    
    connect(ui_.aboutAction, &QAction::triggered, this, &MainWindow::about);

    connect(ui_.loadAction, &QAction::triggered, this, &MainWindow::loadModel);

    connect(ui_.loadConfigFileAction, &QAction::triggered, this, qOverload<>(&MainWindow::loadConfigFile));
    
    connect(ui_.resetButton, &QPushButton::clicked, this, &MainWindow::reset);

    connect(ui_.colorToolButton, &QToolButton::clicked, this, &MainWindow::changeColor);

    connect(ui_.shininessSpinBox, &QSpinBox::valueChanged, this, &MainWindow::changeLight);

    connect(ui_.fillCheckbox, &QCheckBox::toggled, this, &MainWindow::changeMode);
    connect(ui_.linesCheckbox, &QCheckBox::toggled, this, &MainWindow::changeMode);
    connect(ui_.pointsCheckbox, &QCheckBox::toggled, this, &MainWindow::changeMode);

    connect(ui_.meshRadioButton, &QRadioButton::clicked, this, &MainWindow::redraw);
    connect(ui_.voxelizedRadioButton, &QRadioButton::clicked, this, &MainWindow::redraw);
    connect(ui_.voxelsSpinBox, &QSpinBox::editingFinished, this, &MainWindow::redraw);

    connect(ui_.shapeDistributionsAction, &QAction::triggered, this, &MainWindow::showSDDialog);
    connect(ui_.symmetryDescriptorAction, &QAction::triggered, this, &MainWindow::showRSDDialog);
    connect(ui_.harmonicDescriptorAction, &QAction::triggered, this, &MainWindow::showHMDialog);
    connect(ui_.openResultsDialogAction, &QAction::triggered, this, &MainWindow::showResultsDialog);

    
    QtConfig::instance().setDefaultBigPlotFontSize(12);
    QtConfig::instance().setDefaultPlotFontSize(10);
    QtConfig::instance().setDefaultSmallPlotFontSize(8);
    

    modelName_ = "";

    meshData_.featurePath = "";    
    meshData_.screenshotsPath = "";    
    meshData_.nModels = 0;
    meshData_.nInfo = 0;
    meshData_.nSamps = 0;
    meshData_.nBins = 0;
    meshData_.nVox = 0;
    meshData_.nTestAng = 0;
    meshData_.nTestAng = 0;
    meshData_.nTestSteps = 0;
    meshData_.iniStep = 0;
    meshData_.endStep = 0;
    meshData_.models.clear();
    meshData_.infoFields.clear();
      
    blockControlSignals(true);

    ui_.propertiesWidget->setVisible(false);
    ui_.fillCheckbox->setChecked(ui_.modelWidget->fillFacesEnabled());
    ui_.linesCheckbox->setChecked(ui_.modelWidget->drawLinesEnabled());
    ui_.pointsCheckbox->setChecked(ui_.modelWidget->drawPointsEnabled());
    ui_.shininessSpinBox->setValue(static_cast<int>(ui_.modelWidget->shininess() + 0.5));

    color_ = nct::color::RgbColor(0.5, 0.7, 0.4);
    int r = static_cast<int>(color_[0]*255+0.5);
    int g = static_cast<int>(color_[1]*255+0.5);
    int b = static_cast<int>(color_[2]*255+0.5);
    ui_.colorToolButton->setStyleSheet("background-color: rgb(" + QString::number(r) + "," 
        + QString::number(g) + "," + QString::number(b) + ");");

    blockControlSignals(false);    

    vertices_ = std::make_shared<nct::Array<nct::Point3D>>();
    normals_ = std::make_shared<nct::Array<nct::Vector3D<double>>>();
    triangles_ = std::make_shared<nct::Array<nct::Vector3D<unsigned int>>>();

    ui_.loadConfigFileAction->setVisible(false);
    loadConfigFile(":/config/config/model_data_embeded.txt");
}

//=================================================================================================================
//        SLOTS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::about()
{
    AboutWindow about;
    about.setModal(true);
    about.exec();
} 

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::loadModel()
{
    QString fileName = QFileDialog::getOpenFileName( this, tr( "Select a 3D model file" ), "", 
        tr( "Mesh files (*.stl *.ply)" ) );
    if( !fileName.isNull() )
    {
        try
        {
            QApplication::setOverrideCursor(Qt::WaitCursor);
            
            vertices_->clear();
            normals_->clear();
            triangles_->clear();
            modelName_ = "";

            QFileInfo file(fileName);
            if (file.suffix().toLower() == "stl")
            {
                mesh::StlMesh model(fileName.toLatin1().data());
                auto mesh = model.triangularMesh();

                vertices_ = std::make_shared<nct::Array<nct::Point3D>>(std::get<0>(mesh));
                normals_ = std::make_shared<nct::Array<nct::Vector3D<double>>>(std::get<1>(mesh));
                triangles_ = std::make_shared<nct::Array<nct::Vector3D<unsigned int>>>(std::get<2>(mesh));
                
                modelName_ = file.baseName();
            }
            else if (file.suffix().toLower() == "ply")
            {
                mesh::PlyMesh model(fileName.toLatin1().data());
                auto mesh = model.triangularMesh();

                vertices_ = std::make_shared<nct::Array<nct::Point3D>>(std::get<0>(mesh));                
                triangles_ = std::make_shared<nct::Array<nct::Vector3D<unsigned int>>>(std::get<1>(mesh));
                normals_ = std::make_shared<nct::Array<nct::Vector3D<double>>>(mesh::calculateVertexNormals(*vertices_, *triangles_));

                modelName_ = file.baseName().toLatin1().data();
            }
            else
            {
                throw OperationException("File extension not supported by this application",    "");
            }        

            this->setWindowTitle(file.baseName() + QString(" - Mesh analizer"));
            QApplication::restoreOverrideCursor();
        }
        catch (const std::exception& ex)
        {
            vertices_->clear();
            normals_->clear();
            triangles_->clear();
            modelName_ = "";
            this->setWindowTitle("Mesh analizer");            

            QApplication::restoreOverrideCursor();    
            showErrorMessage("Unable to load the specified file", &ex);
        }
    }    

    redraw();
}

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::loadConfigFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select object info file"));
    if (!fileName.isNull())
        loadConfigFile(fileName);
}

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::loadConfigFile(const QString& fileName)
{
    try
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);

        // Load "Config file"
        QFile file(fileName);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray fileData = file.readAll();

        if (fileData.size() == 0)
            throw OperationException("Bad input file", "");

        meshData_ = decodeMeshData(fileData);

        QApplication::restoreOverrideCursor();
    }
    catch (const std::exception& ex)
    {
        meshData_.featurePath = "";
        meshData_.screenshotsPath = "";
        meshData_.nModels = 0;
        meshData_.nInfo = 0;
        meshData_.nSamps = 0;
        meshData_.nBins = 0;
        meshData_.nVox = 0;
        meshData_.nTestAng = 0;
        meshData_.nTestAng = 0;
        meshData_.nTestSteps = 0;
        meshData_.iniStep = 0;
        meshData_.endStep = 0;
        meshData_.models.clear();
        meshData_.infoFields.clear();

        QApplication::restoreOverrideCursor();
        showErrorMessage("Unable to load the specified configuration file", &ex);
    }
}

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::redraw()
{        
    try
    {    
        QApplication::setOverrideCursor(Qt::WaitCursor);
        ui_.modelWidget->removeShapes();

        if (vertices_->size() > 0)
        {        
            if (ui_.meshRadioButton->isChecked())
            {
                auto scVertices =  mesh::centerAndScaleVertices(*vertices_);                
                ui_.modelWidget->addShape(std::make_shared<TriangularMesh>(
                    scVertices, *normals_, *triangles_, color_));
            }
            else
            {
                auto scVertices = mesh::centerAndScaleVertices(*vertices_);
                auto triang = mesh::triangleCoord(scVertices, *triangles_);
                RasterizedObject3D rr(triang, -1, 1, ui_.voxelsSpinBox->value(), 
                    geometry::rasterization::NConnectivity3D::TwentySixConnected);
                
                
                ui_.modelWidget->addShape(
                    std::make_shared<VoxelizedObject>(rr.voxelArray(), color_));
            }
        }
        else
        {
            ui_.modelWidget->removeShapes();            
        }     

        ui_.modelWidget->repaint();

        QApplication::restoreOverrideCursor();        
    }
    catch (const std::exception& ex)
    {
        QApplication::restoreOverrideCursor();    
        showErrorMessage("Unable to update graphics scene", &ex);    
    }        

    blockControlSignals(true);
    ui_.vertexValueLabel->setText(QString::number(vertices_->size()));
    ui_.polygonValueLabel->setText(QString::number(triangles_->size()));
    ui_.fillCheckbox->setChecked(ui_.modelWidget->fillFacesEnabled());
    ui_.linesCheckbox->setChecked(ui_.modelWidget->drawLinesEnabled());
    ui_.pointsCheckbox->setChecked(ui_.modelWidget->drawPointsEnabled());
    ui_.shininessSpinBox->setValue(static_cast<int>(ui_.modelWidget->shininess() + 0.5));
    blockControlSignals(false);    
}

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::reset()
{
    ui_.modelWidget->resetScene();    

    blockControlSignals(true);
    ui_.fillCheckbox->setChecked(ui_.modelWidget->fillFacesEnabled());
    ui_.linesCheckbox->setChecked(ui_.modelWidget->drawLinesEnabled());
    ui_.pointsCheckbox->setChecked(ui_.modelWidget->drawPointsEnabled());
    ui_.shininessSpinBox->setValue(static_cast<int>(ui_.modelWidget->shininess() + 0.5));
    blockControlSignals(false);

    redraw();
}

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::changeColor()
{
    int r = static_cast<int>(color_[0]*255+0.5);
    int g = static_cast<int>(color_[1]*255+0.5);
    int b = static_cast<int>(color_[2]*255+0.5);
    QColor ini(r, g, b);
    QColor newColor = QColorDialog::getColor(ini, this);
    if (newColor.isValid())
    {    
        color_ = nct::color::RgbColor(newColor.red() / 255., newColor.green() / 255., newColor.blue() / 255.);

        ui_.colorToolButton->setStyleSheet("background-color: rgb(" + QString::number(newColor.red()) + "," 
        + QString::number(newColor.green()) + "," + QString::number(newColor.blue()) + ");");

        redraw();
    }
}

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::changeLight()
{    
    ui_.modelWidget->setShininess(ui_.shininessSpinBox->value()+0.01);
    ui_.modelWidget->repaint();
}

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::changeMode()
{
    ui_.modelWidget->setFillFacesEnabled(ui_.fillCheckbox->isChecked());
    ui_.modelWidget->setDrawLinesEnabled(ui_.linesCheckbox->isChecked());
    ui_.modelWidget->setDrawPointsEnabled(ui_.pointsCheckbox->isChecked());
    ui_.modelWidget->repaint();
}

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::showSDDialog()
{
    SDDialog dialog;
    dialog.setModal(true);
    dialog.setModel(vertices_, triangles_);
    dialog.setMeshData(meshData_);
    dialog.exec();
}

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::showRSDDialog()
{
    RSDDialog dialog;
    dialog.setModal(true);
    dialog.setModel(vertices_, triangles_);
    dialog.setMeshData(meshData_);
    dialog.exec();
}

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::showHMDialog()
{
    HMDialog dialog;
    dialog.setModal(true);
    dialog.setModel(vertices_, triangles_);
    dialog.setMeshData(meshData_);
    dialog.exec();
}

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::showResultsDialog()
{
    ResultsDialog dialog;
    dialog.setModal(true);
    dialog.setMeshData(meshData_);
    dialog.exec();
}

//=================================================================================================================
//        METHODS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::blockControlSignals(bool blockSignals)
{
    ui_.aboutAction->blockSignals(blockSignals);
    ui_.loadAction->blockSignals(blockSignals);
    ui_.resetButton->blockSignals(blockSignals);
    ui_.colorToolButton->blockSignals(blockSignals);
    ui_.shininessSpinBox->blockSignals(blockSignals);
    ui_.fillCheckbox->blockSignals(blockSignals);
    ui_.linesCheckbox->blockSignals(blockSignals);
    ui_.pointsCheckbox->blockSignals(blockSignals);
    ui_.meshRadioButton->blockSignals(blockSignals);
    ui_.voxelizedRadioButton->blockSignals(blockSignals);
    ui_.voxelsSpinBox->blockSignals(blockSignals);
}

//-----------------------------------------------------------------------------------------------------------------
MainWindow::MeshData MainWindow::decodeMeshData(const QByteArray& meshData)
{
    MeshData data;

    data.featurePath = "";
    data.screenshotsPath = "";
    data.nModels = 0;
    data.models.clear();

    data.nSamps = 0;
    data.nBins = 0;
    data.nVox = 0;
    data.nTestAng = 0;
    data.nTestSteps = 0;
    data.iniStep = 0;
    data.endStep = 0;

    // Read header and secret key
    stringstream file(meshData.data());

    string line;
    string entry = "A-TOOLS MESH DATA V1.0";
    getline(file, line);
    line = nct::trim(line);
    if (file.fail() || line != entry)
        throw OperationException("Bad header", "");

    // Paths
    entry = "Feature-Path:";
    getline(file, line);
    line = nct::trim(line);
    if (file.fail() || line.find(entry) == string::npos)
        throw OperationException("Bad feature file path", "");
    data.featurePath = QString(line.substr(entry.length() + 1).c_str());

    entry = "Screenshot-Path:";
    getline(file, line);
    line = nct::trim(line);
    if (file.fail() || line.find(entry) == string::npos)
        throw OperationException("Bad screenshot file path", "");
    data.screenshotsPath = QString(line.substr(entry.length() + 1).c_str());

    // Read configuration of descriptors
    entry = "N-Samples:";
    getline(file, line);
    line = nct::trim(line);
    if (file.fail() || line.find(entry) == string::npos)
        throw OperationException("Bad number of samples", "");
    data.nSamps = atoi(line.substr(entry.length()).c_str());

    entry = "N-Bins:";
    getline(file, line);
    line = nct::trim(line);
    if (file.fail() || line.find(entry) == string::npos)
        throw OperationException("Bad number of bins", "");
    data.nBins = atoi(line.substr(entry.length()).c_str());

    entry = "N-Vox:";
    getline(file, line);
    line = nct::trim(line);
    if (file.fail() || line.find(entry) == string::npos)
        throw OperationException("Bad number of voxels", "");
    data.nVox = atoi(line.substr(entry.length()).c_str());

    entry = "N-Test-Angles:";
    getline(file, line);
    line = nct::trim(line);
    if (file.fail() || line.find(entry) == string::npos)
        throw OperationException("Bad number of test angles", "");
    data.nTestAng = atoi(line.substr(entry.length()).c_str());

    entry = "N-Test-Steps:";
    getline(file, line);
    line = nct::trim(line);
    if (file.fail() || line.find(entry) == string::npos)
        throw OperationException("Bad number of test angles", "");
    data.nTestSteps = atoi(line.substr(entry.length()).c_str());

    entry = "Ini-Step:";
    getline(file, line);
    line = nct::trim(line);
    if (file.fail() || line.find(entry) == string::npos)
        throw OperationException("Bad number of test angles", "");
    data.iniStep = atof(line.substr(entry.length()).c_str());

    entry = "End-Step:";
    getline(file, line);
    line = nct::trim(line);
    if (file.fail() || line.find(entry) == string::npos)
        throw OperationException("Bad number of test angles", "");
    data.endStep = atof(line.substr(entry.length()).c_str());

    entry = "N-Models:";
    getline(file, line);
    line = nct::trim(line);
    if (file.fail() || line.find(entry) == string::npos)
        throw OperationException("Bad number of models", "");
    data.nModels = atoi(line.substr(entry.length()).c_str());

    entry = "N-Info:";
    getline(file, line);
    line = nct::trim(line);
    if (file.fail() || line.find(entry) == string::npos)
        throw OperationException("Bad number of info fields", "");
    data.nInfo = atoi(line.substr(entry.length()).c_str());

    // Read info fields
    entry = "----Info---";
    getline(file, line);
    if (file.fail() || line.find(entry) == string::npos)
        throw OperationException("Bad info section", "");

    data.infoFields.resize(data.nInfo);
    for (unsigned int i = 0; i < data.nInfo; i++)
    {
        getline(file, entry);
        entry = nct::trim(entry);
        if (file.fail())
            throw OperationException("Bad field", "");
        data.infoFields[i] = QString::fromLatin1(entry.c_str());
    }

    // Read models        
    entry = "----Data----";
    getline(file, line);
    line = nct::trim(line);
    if (file.fail() || line.find(entry) == string::npos)
        throw OperationException("Bad model section", "");

    data.models.resize(data.nModels, 9);
    for (unsigned int i = 0; i < data.nModels; i++)
    {
        getline(file, entry);
        entry = nct::trim(entry);
        if (file.fail())
            throw OperationException("Bad model", "");

        std::size_t posIni = 0;
        std::size_t posEnd = 0;
        for (unsigned int j = 0; j < 9; j++)
        {
            if (j < 8)
                posEnd = entry.find(',', posIni);
            else
                posEnd = entry.size();

            if (posEnd != string::npos)
                data.models(i, j) = QString::fromLatin1(entry.substr(posIni, posEnd - posIni).c_str()).trimmed();
            posIni = posEnd + 1;
        }
    }


    return data;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Matrix MainWindow::decodeMatrixFile(const QString& arrayFile)
{
    QFile file(arrayFile);
    file.open(QIODevice::ReadOnly);
    QDataStream i(&file);

    if (!i.status() == QDataStream::Ok)
        throw IOException(exc_bad_input_stream, SOURCE_INFO);

    // Read number of rows and number of columns.
    size_t r = 0;
    size_t c = 0;
    i.readRawData(reinterpret_cast<char*> (&r), sizeof(size_t));
    if (!i.status() == QDataStream::Ok)
        throw IOException(exc_error_reading_number_of_rows, SOURCE_INFO);

    i.readRawData(reinterpret_cast<char*> (&c), sizeof(size_t));
    if (!i.status() == QDataStream::Ok)
        throw IOException(exc_error_reading_number_of_columns, SOURCE_INFO);

    // Read data.
    Array2D<double> arr(r, c);
    i.readRawData(reinterpret_cast<char*> (arr.data()), sizeof(double) * arr.size());
    if (!i.status() == QDataStream::Ok)
        throw IOException(exc_error_reading_data, SOURCE_INFO);

    return arr;
}

//-----------------------------------------------------------------------------------------------------------------
nct::RealVector MainWindow::decodeVectorFile(const QString& arrayFile)
{
    QFile file(arrayFile);    
    file.open(QIODevice::ReadOnly);
    QDataStream i(&file);

    if (!i.status() == QDataStream::Ok)
        throw IOException(exc_bad_input_stream, SOURCE_INFO);

    // Read number of rows and number of columns.
    nct::size_t n_ = 0;

    i.readRawData(reinterpret_cast<char*> (&n_), sizeof(nct::size_t));

    if (!i.status() == QDataStream::Ok)
        throw IOException(exc_error_reading_array_size, SOURCE_INFO);

    // Read data.
    Array<double> arr(n_);
    i.readRawData(reinterpret_cast<char*> (arr.data()), sizeof(double) * arr.size());
    if (!i.status() == QDataStream::Ok)
        throw IOException(exc_error_reading_data, SOURCE_INFO);

    return arr;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::signal::spherical_harmonics::SphericalHarmonic> MainWindow::decodeHarmonicFile(const QString& arrayFile)
{
    QFile file(arrayFile);
    file.open(QIODevice::ReadOnly);
    QDataStream i(&file);

    if (!i.status() == QDataStream::Ok)
        throw IOException(exc_bad_input_stream, SOURCE_INFO);

    // Read number of rows and number of columns.
    nct::size_t n_ = 0;

    i.readRawData(reinterpret_cast<char*> (&n_), sizeof(nct::size_t));

    if (!i.status() == QDataStream::Ok)
        throw IOException(exc_error_reading_array_size, SOURCE_INFO);

    // Read data.
    Array<nct::signal::spherical_harmonics::SphericalHarmonic> arr(n_);
    i.readRawData(reinterpret_cast<char*> (arr.data()), sizeof(nct::signal::spherical_harmonics::SphericalHarmonic) * arr.size());
    if (!i.status() == QDataStream::Ok)
        throw IOException(exc_error_reading_data, SOURCE_INFO);

    return arr;
}

//-----------------------------------------------------------------------------------------------------------------
void MainWindow::showErrorMessage(const QString& message, const std::exception* exception)
{
    QMessageBox dialog(this);
    dialog.setModal(true);
    dialog.setWindowTitle("Application error");
    dialog.setText(message);
    if (exception != nullptr)
        dialog.setDetailedText(exception->what());
    dialog.setIcon(QMessageBox::Critical);
    dialog.exec();
}        

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
