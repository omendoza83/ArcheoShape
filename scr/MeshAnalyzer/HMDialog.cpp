//=================================================================================================================
/**
 *  @file       HMDialog.cpp
 *  @brief      HMDialog class implementation file.
 *  @details    This file contains the implementation of the HMDialog class.     
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

//=================================================================================================================
//        HEADERS AND NAMESPACES
//=================================================================================================================
#include "HMDialog.h"
#include "ResultsDialog.h"

#include "nct/color/RgbColor.h"
#include "nct/geometry/mesh.h"
#include "nct/geometry/RasterizedObject3D.h"
#include "nct/signal/spherical_harmonics.h"

#include <qt_tools/plots/ArrayPlot.h>
#include "qt_tools/graphics_3d/Graphics3DWidget.h"
#include "qt_tools/graphics_3d/TriangularMesh.h"
#include "qt_tools/QtConfig.h"

#include <fstream>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>

using namespace std;
using namespace nct;
using namespace nct::geometry;
using namespace nct::geometry::mesh;
using namespace nct::geometry::rasterization;
using namespace nct::signal::spherical_harmonics;
using namespace qt_tools;
using namespace qt_tools::plots;
using namespace qt_tools::graphics_3d;

//=================================================================================================================
//        CONSTRUCTORS AND DESTRUCTOR
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
HMDialog::HMDialog(QWidget *objFather): QDialog(objFather)
{
    ui_.setupUi(this);        
    ui_.saveButton->setVisible(false);

    connect(ui_.calculateButton, &QPushButton::clicked, this, &HMDialog::calculate);
    connect(ui_.compareButton, &QPushButton::clicked, this, &HMDialog::compare);
    connect(ui_.saveButton, &QPushButton::clicked, this, &HMDialog::save);


    auto descriptorScene = std::make_shared<ArrayPlot>(this);
    ui_.descriptorView->setScene(descriptorScene);    
    descriptorScene->setColorPalette(color::ColorPalette::ColorPaletteName::Jet);
    descriptorScene->setColorbarPosition(ColorbarPosition::Hidden);
    descriptorScene->setXAxisName("Radio");
    descriptorScene->setYAxisName("Order");
    descriptorScene->setLegendBoxPosition(qt_tools::plots::LegendBoxPosition::Hidden);
    descriptorScene->setXAxisProperties(
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultPlotFontSize(), QFont::Bold),
        QColor(0, 0, 0),
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultSmallPlotFontSize(), QFont::Normal),
        QColor(0, 0, 0),
        QPen(QColor(0, 0, 0), 2, Qt::PenStyle::SolidLine),
        QPen(QColor(120, 120, 120), 0, Qt::PenStyle::NoPen));
    descriptorScene->setYAxisProperties(
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultPlotFontSize(), QFont::Bold),
        QColor(0, 0, 0),
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultSmallPlotFontSize(), QFont::Normal),
        QColor(0, 0, 0),
        QPen(QColor(0, 0, 0), 2, Qt::PenStyle::SolidLine),
        QPen(QColor(120, 120, 120), 0, Qt::PenStyle::NoPen));
    descriptorScene->drawPlot();

    vertices_ = nullptr;
    triangles_ = nullptr;
}

//=================================================================================================================
//        SLOTS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void HMDialog::calculate()
{
    if ( (vertices_ == nullptr) || (triangles_ == nullptr))
        return;

    if ( (vertices_->size() == 0) || (triangles_->size() == 0))
        return;

    // Calculate descriptor
    QApplication::setOverrideCursor(Qt::WaitCursor);   

    auto descriptorScene = dynamic_pointer_cast<ArrayPlot>(ui_.descriptorView->plotScene());

    try
    {   
        descriptorScene->clear();

        // Scale model
        auto scVertices = mesh::centerAndScaleVertices(*vertices_);
        auto triang = mesh::triangleCoord(scVertices, *triangles_);

        // Voxelize model
        RasterizedObject3D rr(triang, -1, 1, ui_.voxelsSpinBox->value(), NConnectivity3D::TwentySixConnected);        

        // Calculate descriptor
        descriptor_ = rr.harmonicDescriptor();

        // Descriptor 3D plot
        auto descMesh = mesh::gridMesh(
            static_cast<unsigned int>(descriptor_.rows()), static_cast<unsigned int>(descriptor_.columns()));
        auto& verticesGr = std::get<0>(descMesh);
        auto& trianglesGr = std::get<1>(descMesh);

        Array<color::RgbColor> colors(verticesGr.size());

        Array2D<double> d = descriptor_;
        d /= d.max();
        for (unsigned int i = 0; i < verticesGr.size(); i++)
        {
            double val = d[i];
            colors[i] = color::RgbColor(static_cast<double>(val), static_cast<double>(1 - val), static_cast<double>(0));
            verticesGr[i][2] = static_cast<float>(val);
        }
                
        auto normalsGr = calculateVertexNormals(verticesGr, trianglesGr);
        
        ui_.descriptor3DView->addShape(std::make_shared<TriangularMesh>(verticesGr, normalsGr, trianglesGr, colors));
        ui_.descriptor3DView->setDrawLinesEnabled(true);
        ui_.descriptor3DView->setFillFacesEnabled(true);

        // Descriptor 2D plot
        descriptorScene->configPlot(descriptor_, "", false);
        descriptorScene->setXAxisRange(1. / descriptor_.rows(), 1.0, 5);
        descriptorScene->setYAxisRange(0, descriptor_.rows(), 5);
        
        descriptorScene->setColorbarRange(0, descriptor_.max());
        descriptorScene->drawPlot();

        QApplication::restoreOverrideCursor();
        
    }
    catch (const std::exception& ex)
    {
        QApplication::restoreOverrideCursor();
        ui_.descriptor3DView->removeShapes();
        descriptorScene->clear();
        descriptor_.clear();
        showErrorMessage("Unable to calculate model features.", &ex);
    }

    ui_.descriptor3DView->repaint();
}

//-----------------------------------------------------------------------------------------------------------------
void HMDialog::compare()
{
    if ( (vertices_ == nullptr) || (triangles_ == nullptr))
        return;

    if ( (vertices_->size() == 0) || (triangles_->size() == 0))
        return;

    if (meshData_.nModels == 0)
    {
        showErrorMessage("This operation requires a mesh collection loaded in memory. ", nullptr);
        return;
    }

    try
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);        

        // Decode parameters
        auto f = mesh::DistanceFunction::EuclideanDistance;

        if (ui_.distanceMetricComboBox->currentIndex() == 0)
            f = mesh::DistanceFunction::EuclideanDistance;
        else if (ui_.distanceMetricComboBox->currentIndex() == 1)
            f = mesh::DistanceFunction::CityBlockDistance;
        else if (ui_.distanceMetricComboBox->currentIndex() == 2)
            f = mesh::DistanceFunction::ChebychevDistance;
        else if (ui_.distanceMetricComboBox->currentIndex() == 3)
            f = mesh::DistanceFunction::MinDistance;

        // Download transformation matrices
        RasterizedObject3D::HarmonicMatrices hmat;
        hmat.hB = MainWindow::decodeHarmonicFile(meshData_.featurePath + "hB.bin");
        hmat.theta = MainWindow::decodeVectorFile(meshData_.featurePath + "theta.bin");
        hmat.phi = MainWindow::decodeVectorFile(meshData_.featurePath + "phi.bin");
        hmat.Bt = MainWindow::decodeMatrixFile(meshData_.featurePath + "Bt.bin");
        hmat.BtBI = MainWindow::decodeMatrixFile(meshData_.featurePath + "BtBI.bin");
               

        // Download descriptors of collection
        auto modelNames = meshData_.models.selectColumn(0);

        Array<Array2D<double>> hm(meshData_.nModels);
        for (unsigned int i=0; i<meshData_.nModels; i++)
            hm[i] = MainWindow::decodeMatrixFile(meshData_.featurePath + modelNames[i] + "_HM.bin");

        // Calculate descriptor of loaded object according to the configuration file
        auto scVertices = mesh::centerAndScaleVertices(*vertices_);
        auto triang = mesh::triangleCoord(scVertices, *triangles_);
        RasterizedObject3D rr(triang, -1, 1, meshData_.nVox, NConnectivity3D::TwentySixConnected);
        auto hmRef = rr.harmonicDescriptor(hmat);

        // Compare descriptor with the rest and get the minimum distances
        Array<std::pair<double, int>> ranks(meshData_.nModels);
        
        for (unsigned int i=0; i<meshData_.nModels; i++)
        {
            ranks[i].second = i;
            ranks[i].first = mesh::compareFeatures(Array<double>(hmRef.begin(), hmRef.end()), 
                Array<double>(hm[i].begin(), hm[i].end()), f);
        }

        sort(ranks.begin(), ranks.end(), [](const std::pair<double, int>& p1, const std::pair<double, int>& p2)
            {return p1.first<p2.first;});

        // Update progress
        QApplication::restoreOverrideCursor();

        // Show results
        Array<unsigned int> results(meshData_.nModels);
        for (unsigned int i=0; i<meshData_.nModels; i++)
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
void HMDialog::save()
{
    if (descriptor_.size() > 0)
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Output data file.", "Descriptor.bin");
        if (fileName.length() == 0)
            return;
        try
        {
            ofstream file;
            file.open(fileName.toLatin1().data(), ios_base::binary);
            descriptor_.write(file);
            file.close();
        }
        catch (const std::exception& ex)
        {
            showErrorMessage("Unable to save descriptor file. ", &ex);
        }

    }
}

//=================================================================================================================
//        METHODS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void HMDialog::setModel(const std::shared_ptr<nct::Array<nct::Point3D>>& vertices,
    const std::shared_ptr<nct::Array<nct::Vector3D<unsigned int>>>& triangles)
{
    descriptor_.clear();
    
    auto descriptorScene = dynamic_pointer_cast<ArrayPlot>(ui_.descriptorView->plotScene());
    descriptorScene->clear();
    descriptorScene->clearData();
    descriptorScene->drawPlot();


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
void HMDialog::setMeshData(const MainWindow::MeshData& meshData)
{
    meshData_ = meshData;
}

//-----------------------------------------------------------------------------------------------------------------
void HMDialog::showErrorMessage(const QString& message, const std::exception* exception)
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

//===========================================================================================================
//        END OF FILE
//===========================================================================================================
