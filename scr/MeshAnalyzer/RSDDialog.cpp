//=================================================================================================================
/**
 *  @file       RSDDialog.cpp
 *  @brief      RSDDialog class implementation file.
 *  @details    This file contains the implementation of the RSDDialog class.           
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
#include "RSDDialog.h"
#include "ResultsDialog.h"

#include "nct/color/RgbColor.h"
#include "nct/geometry/mesh.h"

#include "qt_tools/graphics_3d/Graphics3DWidget.h"
#include "qt_tools/graphics_3d/TriangularMesh.h"

#include <fstream>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>

using namespace std;
using namespace nct;
using namespace nct::geometry;
using namespace nct::geometry::mesh;
using namespace nct::geometry::rasterization;
using namespace qt_tools::graphics_3d;

//=================================================================================================================
//        CONSTRUCTORS AND DESTRUCTOR
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
RSDDialog::RSDDialog(QWidget *objFather): QDialog(objFather)
{
    vertices_ = nullptr;
    triangles_ = nullptr;

    ui_.setupUi(this);
    ui_.saveButton->setVisible(false);
    
    connect(ui_.calculateButton, &QPushButton::clicked, this, &RSDDialog::calculate);
    connect(ui_.compareButton, &QPushButton::clicked, this, &RSDDialog::compare);
    connect(ui_.saveButton, &QPushButton::clicked, this, &RSDDialog::save);
}

//=================================================================================================================
//        SLOTS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void RSDDialog::calculate()
{
    if ( (vertices_ == nullptr) || (triangles_ == nullptr))
        return;

    if ( (vertices_->size() == 0) || (triangles_->size() == 0))
        return;

    // Calculate descriptor
    QApplication::setOverrideCursor(Qt::WaitCursor);
    


    try
    {    
        // Scale model
        auto scVertices = mesh::centerAndScaleVertices(*vertices_);
        auto triang = mesh::triangleCoord(scVertices, *triangles_);

        // Voxelize model
        RasterizedObject3D rr(triang, -1, 1, ui_.voxelsSpinBox->value(), NConnectivity3D::TwentySixConnected);

        // Calculate descriptor
        descriptor_ = rr.symmetryDescriptor();

        // Descriptor plot
        auto descMesh = mesh::sphereMesh(2 * rr.numberOfDivisions(), rr.numberOfDivisions());
        auto& verticesSph = std::get<0>(descMesh);
        auto& trianglesSph = std::get<1>(descMesh);

        Array<color::RgbColor> colors(verticesSph.size());

        for (unsigned int i = 0; i < verticesSph.size(); i++)
        {
            double rad = 1 - descriptor_.rsd(i, 1);
            colors[i] = color::RgbColor(static_cast<float>(rad), static_cast<float>(1.0 - rad),
                static_cast<float>(0));
            verticesSph[i] *= static_cast<float>(rad);
        }

        auto normalsSph = calculateVertexNormals(verticesSph, trianglesSph);
                
        ui_.descriptor3DView->addShape(std::make_shared<TriangularMesh>(verticesSph, normalsSph, trianglesSph, colors));
        ui_.descriptor3DView->setDrawLinesEnabled(true);
        ui_.descriptor3DView->setFillFacesEnabled(true);        

        QApplication::restoreOverrideCursor();        
    }
    catch (const std::exception& ex)
    {
        QApplication::restoreOverrideCursor();
        ui_.descriptor3DView->removeShapes();
        showErrorMessage("Unable to calculate model features.", &ex);
    }

    ui_.descriptor3DView->repaint();

}

//-----------------------------------------------------------------------------------------------------------------
void RSDDialog::compare()
{
    if ( (vertices_ == nullptr) || (triangles_ == nullptr))
        return;

    if ( (vertices_->size() == 0) || (triangles_->size() == 0))
        return;

    if (meshData_.nModels == 0)
    {
        showErrorMessage("This operation requires a mesh collection loaded in memory.",nullptr);
        return;
    }

    try
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
       
    
        // Decode parameters
        unsigned int nRot = static_cast<unsigned int>(ui_.rotationsSpinBox->value());
        
        auto f = mesh::DistanceFunction::EuclideanDistance;
        if (ui_.distanceMetricComboBox->currentIndex() == 0)
            f = mesh::DistanceFunction::EuclideanDistance;
        else if (ui_.distanceMetricComboBox->currentIndex() == 1)
            f = mesh::DistanceFunction::CityBlockDistance;
        else if (ui_.distanceMetricComboBox->currentIndex() == 2)
            f = mesh::DistanceFunction::ChebychevDistance;
        else if (ui_.distanceMetricComboBox->currentIndex() == 3)
            f = mesh::DistanceFunction::MinDistance;

        // Download descriptors of collection
        auto modelNames = meshData_.models.selectColumn(0);

        Array<Array2D<double>> rsd(meshData_.nModels);
        for (unsigned int i=0; i<meshData_.nModels; i++)
            rsd[i] = MainWindow::decodeMatrixFile(meshData_.featurePath + modelNames[i] + "_RSD_RSD.bin");

        // Calculate descriptor of loaded object according to the configuration file
        auto scVertices = mesh::centerAndScaleVertices(*vertices_);
        auto triang = mesh::triangleCoord(scVertices, *triangles_);
        RasterizedObject3D rr(triang, -1, 1, meshData_.nVox, NConnectivity3D::TwentySixConnected);
        auto descriptor = rr.symmetryDescriptor();

        // Compare descriptor with the rest and get the minimum distances        
        auto indices = mesh::findRotationIndices(descriptor.norms, nRot);

        Array<std::pair<double, int>> ranks(meshData_.nModels);
        
        for (unsigned int i=0; i<meshData_.nModels; i++)
        {
            ranks[i].second = i;
            ranks[i].first = mesh::compareSymmetryDescriptors(descriptor.rsd, rsd[i], indices, f);
        }

        sort(ranks.begin(), ranks.end(), [](const std::pair<double, int>& p1, const std::pair<double, int>& p2)
            {return p1.first<p2.first;});

        // Update progress
        QApplication::restoreOverrideCursor();

        // Show results
        Array<unsigned int> results(meshData_.nModels);
        for (unsigned int i = 0; i < meshData_.nModels; i++)
            results[i] = ranks[i].second;

        ResultsDialog rDialog;
        rDialog.setMeshData(meshData_);
        rDialog.setResults(results);
        rDialog.exec();

    }
    catch (const std::exception& ex)
    {
        QApplication::restoreOverrideCursor();
        showErrorMessage("Unable to compare object descriptor with the collection. "
            "Make shure the collection data is valid.", &ex);
    }
}



//-----------------------------------------------------------------------------------------------------------------
void RSDDialog::save()
{
    if (descriptor_.sd.size() > 0 && descriptor_.rsd.size() > 0)
    {
        QFileDialog dialog;
        dialog.setLabelText(QFileDialog::LookIn,"Select a directory path.");
        dialog.setFileMode(QFileDialog::Directory);
        dialog.setOption(QFileDialog::ShowDirsOnly); 
        if (dialog.exec())
        {
            QStringList list = dialog.selectedFiles();
            QString path = list.at(0);
            string pst = path.toLatin1().data();
            try
            {
                ofstream file;
                file.open(pst + "\\sd.dat", ios_base::binary);
                descriptor_.sd.write(file);
                file.close();

                file.open(pst + "\\rsd.dat", ios_base::binary);
                descriptor_.rsd.write(file);
                file.close();        
            }
            catch (const std::exception& ex)
            {
                showErrorMessage("Unable to save descriptor files.", &ex);
            }
        }    

    }
}

//=================================================================================================================
//        METHODS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void RSDDialog::setModel(const std::shared_ptr<nct::Array<nct::Point3D>>& vertices,
    const std::shared_ptr<nct::Array<nct::Vector3D<unsigned int>>>& triangles)
{
    descriptor_.sd.clear();
    descriptor_.rsd.clear();
    descriptor_.norms.clear();

    ui_.descriptor3DView->removeShapes();

    if ( (vertices != nullptr) && (triangles != nullptr))
    {
        vertices_ = vertices;
        triangles_ = triangles;
    }
    else
    {
        vertices_ = nullptr;
        triangles_ = nullptr;
    }
}

//-----------------------------------------------------------------------------------------------------------------
void RSDDialog::setMeshData(const MainWindow::MeshData& meshData)
{
    meshData_ = meshData;
}

//-----------------------------------------------------------------------------------------------------------------
void RSDDialog::showErrorMessage(const QString& message, const std::exception* exception)
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
