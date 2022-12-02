//=================================================================================================================
/**
 *  @file       SDDialog.cpp
 *  @brief      SDDialog class implementation file.
 *  @details    This file contains the implementation of the SDDialog class.          
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
#include "SDDialog.h"
#include "ResultsDialog.h"

#include "nct/color/RgbColor.h"
#include "nct/random/MersenneTwister.h"
#include "nct/geometry/mesh.h"
#include "nct/geometry/RasterizedObject3D.h"

#include <qt_tools/plots/StemPlot.h>
#include "qt_tools/graphics_3d/Graphics3DWidget.h"
#include "qt_tools/graphics_3d/TriangularMesh.h"
#include "qt_tools/QtConfig.h"

#include <ctime>
#include <fstream>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>

using namespace std;
using namespace nct;
using namespace nct::geometry;
using namespace nct::geometry::mesh;
using namespace nct::geometry::rasterization;
using namespace qt_tools;
using namespace qt_tools::plots;
using namespace qt_tools::graphics_3d;

//=================================================================================================================
//        CONSTRUCTORS AND DESTRUCTOR
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
SDDialog::SDDialog(QWidget *objFather): QDialog(objFather)
{
    vertices_ = nullptr;
    triangles_ = nullptr;

    ui_.setupUi(this);
    ui_.saveButton->setVisible(false);        

    auto scene = std::make_shared<StemPlot>();
    ui_.opDistanceView->setScene(scene);
    scene->clear();            
    scene->setTitle("Distances to the centroid");
    scene->setXAxisName("");
    scene->setYAxisName("");
    scene->setLegendBoxPosition(qt_tools::plots::LegendBoxPosition::Hidden);
    scene->setXAxisProperties(
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultPlotFontSize(), QFont::Bold),
        QColor(0, 0, 0),
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultSmallPlotFontSize(), QFont::Normal),
        QColor(0, 0, 0),
        QPen(QColor(0, 0, 0), 2, Qt::PenStyle::SolidLine),
        QPen(QColor(120, 120, 120), 0, Qt::PenStyle::NoPen));
    scene->setYAxisProperties(
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultPlotFontSize(), QFont::Bold),
        QColor(0, 0, 0),
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultSmallPlotFontSize(), QFont::Normal),
        QColor(0, 0, 0),
        QPen(QColor(0, 0, 0), 2, Qt::PenStyle::SolidLine),
        QPen(QColor(120, 120, 120), 0, Qt::PenStyle::NoPen));
    scene->drawPlot();
    
    scene = std::make_shared<StemPlot>();
    ui_.tpDistanceView->setScene(scene);
    scene->clear();
    scene->setTitle("Distances between points");
    scene->setXAxisName("");
    scene->setYAxisName("");
    scene->setLegendBoxPosition(qt_tools::plots::LegendBoxPosition::Hidden);
    scene->setXAxisProperties(
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultPlotFontSize(), QFont::Bold),
        QColor(0, 0, 0),
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultSmallPlotFontSize(), QFont::Normal),
        QColor(0, 0, 0),
        QPen(QColor(0, 0, 0), 2, Qt::PenStyle::SolidLine),
        QPen(QColor(120, 120, 120), 0, Qt::PenStyle::NoPen));
    scene->setYAxisProperties(
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultPlotFontSize(), QFont::Bold),
        QColor(0, 0, 0),
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultSmallPlotFontSize(), QFont::Normal),
        QColor(0, 0, 0),
        QPen(QColor(0, 0, 0), 2, Qt::PenStyle::SolidLine),
        QPen(QColor(120, 120, 120), 0, Qt::PenStyle::NoPen));
    scene->drawPlot();

    scene = std::make_shared<StemPlot>();
    ui_.tpAreaView->setScene(scene);
    scene->clear();
    scene->setTitle("Area of triangles");
    scene->setXAxisName("");
    scene->setYAxisName("");
    scene->setLegendBoxPosition(qt_tools::plots::LegendBoxPosition::Hidden);
    scene->setXAxisProperties(
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultPlotFontSize(), QFont::Bold),
        QColor(0, 0, 0),
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultSmallPlotFontSize(), QFont::Normal),
        QColor(0, 0, 0),
        QPen(QColor(0, 0, 0), 2, Qt::PenStyle::SolidLine),
        QPen(QColor(120, 120, 120), 0, Qt::PenStyle::NoPen));
    scene->setYAxisProperties(
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultPlotFontSize(), QFont::Bold),
        QColor(0, 0, 0),
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultSmallPlotFontSize(), QFont::Normal),
        QColor(0, 0, 0),
        QPen(QColor(0, 0, 0), 2, Qt::PenStyle::SolidLine),
        QPen(QColor(120, 120, 120), 0, Qt::PenStyle::NoPen));
    scene->drawPlot();

    scene = std::make_shared<StemPlot>();
    ui_.fpVolumeView->setScene(scene);
    scene->clear();
    scene->setTitle("Volume of tetrahedra");
    scene->setXAxisName("");
    scene->setYAxisName("");
    scene->setLegendBoxPosition(qt_tools::plots::LegendBoxPosition::Hidden);
    scene->setXAxisProperties(
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultPlotFontSize(), QFont::Bold),
        QColor(0, 0, 0),
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultSmallPlotFontSize(), QFont::Normal),
        QColor(0, 0, 0),
        QPen(QColor(0, 0, 0), 2, Qt::PenStyle::SolidLine),
        QPen(QColor(120, 120, 120), 0, Qt::PenStyle::NoPen));
    scene->setYAxisProperties(
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultPlotFontSize(), QFont::Bold),
        QColor(0, 0, 0),
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultSmallPlotFontSize(), QFont::Normal),
        QColor(0, 0, 0),
        QPen(QColor(0, 0, 0), 2, Qt::PenStyle::SolidLine),
        QPen(QColor(120, 120, 120), 0, Qt::PenStyle::NoPen));
    scene->drawPlot();

    scene = std::make_shared<StemPlot>();
    ui_.tvAngleView->setScene(scene);
    scene->clear();
    scene->setTitle("Angles between vectors");
    scene->setXAxisName("");
    scene->setYAxisName("");
    scene->setLegendBoxPosition(qt_tools::plots::LegendBoxPosition::Hidden);
    scene->setXAxisProperties(
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultPlotFontSize(), QFont::Bold),
        QColor(0, 0, 0),
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultSmallPlotFontSize(), QFont::Normal),
        QColor(0, 0, 0),
        QPen(QColor(0, 0, 0), 2, Qt::PenStyle::SolidLine),
        QPen(QColor(120, 120, 120), 0, Qt::PenStyle::NoPen));
    scene->setYAxisProperties(
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultPlotFontSize(), QFont::Bold),
        QColor(0, 0, 0),
        QFont(QtConfig::instance().defaultFontName(), QtConfig::instance().defaultSmallPlotFontSize(), QFont::Normal),
        QColor(0, 0, 0),
        QPen(QColor(0, 0, 0), 2, Qt::PenStyle::SolidLine),
        QPen(QColor(120, 120, 120), 0, Qt::PenStyle::NoPen));
    scene->drawPlot();   

    connect(ui_.calculateButton, &QPushButton::clicked, this, &SDDialog::calculate);
    connect(ui_.compareButton, &QPushButton::clicked, this, &SDDialog::compare);
    connect(ui_.saveButton, &QPushButton::clicked, this, &SDDialog::save);
}

//=================================================================================================================
//        SLOTS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void SDDialog::calculate()
{
    if ( (vertices_ == nullptr) || (triangles_ == nullptr))
        return;

    if ( (vertices_->size() == 0) || (triangles_->size() == 0))
        return;

    // Calculate descriptor
    random::MersenneTwister gnd(time(0));

    QApplication::setOverrideCursor(Qt::WaitCursor);    

    std::shared_ptr<StemPlot> scenes[5];
    scenes[0] = dynamic_pointer_cast<StemPlot>(ui_.opDistanceView->plotScene());
    scenes[1] = dynamic_pointer_cast<StemPlot>(ui_.tpDistanceView->plotScene());
    scenes[2] = dynamic_pointer_cast<StemPlot>(ui_.tpAreaView->plotScene());
    scenes[3] = dynamic_pointer_cast<StemPlot>(ui_.fpVolumeView->plotScene());
    scenes[4] = dynamic_pointer_cast<StemPlot>(ui_.tvAngleView->plotScene());

    try
    {        

        mesh::ShapeDistribution functions[5] = 
        {
            mesh::ShapeDistribution::CentroidDistance, 
            mesh::ShapeDistribution::TwoPointDistance,
            mesh::ShapeDistribution::ThreePointArea,
            mesh::ShapeDistribution::FourPointVolume, 
            mesh::ShapeDistribution::TwoVectorsAngle
        };        

        unsigned int nSamps = ui_.samplesSpinBox->value();
        unsigned int nBins = ui_.binsSpinBox->value();
        
        for (unsigned int i=0; i<5; i++)
        {
            auto desc = mesh::calculateShapeDistribution(*vertices_, *triangles_, gnd,
                functions[i], nSamps, nBins);    

            histograms_[i] = std::get<0>(desc);
            bins_[i] = std::get<1>(desc);

            scenes[i]->clearData();
            scenes[i]->addDataSet(bins_[i], histograms_[i], "", 0, 
                QPen(QColor(0, 158, 115), 1.0, Qt::PenStyle::SolidLine), QBrush(QColor(0, 158, 115)));
            scenes[i]->drawPlot();
        }        

        QApplication::restoreOverrideCursor();
    }
    catch (const std::exception& ex)
    {
        QApplication::restoreOverrideCursor();
        for (unsigned int i=0; i<5; i++)
        {
            histograms_[i].clear();
            bins_[i].clear();
            scenes[i]->clearData();
        }    
        showErrorMessage("Unable to calculate model features.", &ex);
    }    
}

//-----------------------------------------------------------------------------------------------------------------
void SDDialog::compare()
{
    if ( (vertices_ == nullptr) || (triangles_ == nullptr))
        return;

    if ( (vertices_->size() == 0) || (triangles_->size() == 0))
        return;

    if (meshData_.nModels == 0)
    {
        showErrorMessage("This operation requires a mesh collection loaded in memory.", nullptr);
        return;
    }

    try
    {
        random::MersenneTwister gnd(time(0));

        QApplication::setOverrideCursor(Qt::WaitCursor);

        // Decode parameters
        unsigned int nS = static_cast<unsigned int>(ui_.stepsSpinBox->value());
        double sIni = static_cast<double>(ui_.iniStepSpinBox->value());
        double sEnd = static_cast<double>(ui_.endStepSpinBox->value());

        auto dist = mesh::ShapeDistribution::ThreePointArea;
        QString sufix = "";
        if (ui_.descriptorComboBox->currentIndex() == 0)
        {
            dist = mesh::ShapeDistribution::CentroidDistance;
            sufix = "_SD_CD";
        }
        else if (ui_.descriptorComboBox->currentIndex() == 1)
        {
            dist = mesh::ShapeDistribution::TwoPointDistance;
            sufix = "_SD_TPD";
        }
        else if (ui_.descriptorComboBox->currentIndex() == 2)
        {
            dist = mesh::ShapeDistribution::ThreePointArea;
            sufix = "_SD_TPA";
        }
        else if (ui_.descriptorComboBox->currentIndex() == 3)
        {
            dist = mesh::ShapeDistribution::FourPointVolume;
            sufix = "_SD_FPV";
        }
        else if (ui_.descriptorComboBox->currentIndex() == 4)
        {
            dist = mesh::ShapeDistribution::TwoVectorsAngle;
            sufix = "_SD_TVA";
        }

        bool cdf = false;
        auto f = mesh::DistanceFunction::EuclideanDistance;
        if (ui_.distanceMetricComboBox->currentIndex() == 0)
        {
            f = mesh::DistanceFunction::EuclideanDistance;
        }
        else if (ui_.distanceMetricComboBox->currentIndex() == 1)
        {
            f = mesh::DistanceFunction::EuclideanDistance;
            cdf = true;
        }
        else if (ui_.distanceMetricComboBox->currentIndex() == 2)
        {
            f = mesh::DistanceFunction::CityBlockDistance;
        }
        else if (ui_.distanceMetricComboBox->currentIndex() == 3)
        {
            f = mesh::DistanceFunction::CityBlockDistance;
            cdf = true;
        }
        else if (ui_.distanceMetricComboBox->currentIndex() == 4)
        {
            f = mesh::DistanceFunction::ChebychevDistance;
        }
        else if (ui_.distanceMetricComboBox->currentIndex() == 5)
        {
            f = mesh::DistanceFunction::ChebychevDistance;
            cdf = true;
        }
        else if (ui_.distanceMetricComboBox->currentIndex() == 6)
        {
            f = mesh::DistanceFunction::MinDistance;
        }
        else if (ui_.distanceMetricComboBox->currentIndex() == 7)
        {
            f = mesh::DistanceFunction::MinDistance;
            cdf = true;
        }    

        // Download descriptors of collection
        auto modelNames = meshData_.models.selectColumn(0);

        Array<Array<double>> hist(meshData_.nModels);
        Array<Array<double>> bin(meshData_.nModels);
        for (unsigned int i=0; i<meshData_.nModels; i++)
        {
            bin[i] = MainWindow::decodeVectorFile(meshData_.featurePath + modelNames[i] + sufix + "_b.bin");
            hist[i] = MainWindow::decodeVectorFile(meshData_.featurePath + modelNames[i] + sufix + "_h.bin");
        }

        // Calculate descriptor of this object according to the contiguracion
        auto descriptor = mesh::calculateShapeDistribution(*vertices_, *triangles_, gnd, 
            dist, meshData_.nSamps, meshData_.nBins);    

        auto histRef = std::get<0>(descriptor);
        auto binsRef = std::get<1>(descriptor);

        // Compare descriptor with the rest and get the minimum distances
        Array<std::pair<double, int>> ranks(meshData_.nModels);
        
        for (unsigned int i=0; i<meshData_.nModels; i++)
        {
            ranks[i].second = i;
            if (dist == mesh::ShapeDistribution::TwoVectorsAngle)
                ranks[i].first = mesh::calculateShapeDistributionDistance(histRef, hist[i], f, cdf);
            else
                ranks[i].first = mesh::calculateShapeDistributionDistance(histRef, binsRef, hist[i], bin[i], f, cdf,
                meshData_.nBins, nS, sIni, sEnd);
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
void SDDialog::save()
{
    if (histograms_[0].size() > 0 && bins_[0].size() > 0)
    {
        QFileDialog dialog;
        dialog.setLabelText(QFileDialog::LookIn, "Select a directory path.");
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

                for (unsigned int i=0; i<5; i++)
                {
                    file.open(pst + "\\h_" + std::to_string(i) + ".dat", ios_base::binary);
                    histograms_[i].write(file);
                    file.close();

                    file.open(pst + "\\b_" + std::to_string(i) + ".dat", ios_base::binary);
                    bins_[i].write(file);
                    file.close();
                }
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
void SDDialog::setModel(const std::shared_ptr<nct::Array<nct::Point3D>>& vertices,
    const std::shared_ptr<nct::Array<nct::Vector3D<unsigned int>>>& triangles)
{
    for (unsigned int i=0; i<5; i++)
    {        
        histograms_[i].clear();
        bins_[i].clear();
    }    

    ui_.opDistanceView->plotScene()->clear();
    ui_.tpDistanceView->plotScene()->clear();
    ui_.tpAreaView->plotScene()->clear();
    ui_.fpVolumeView->plotScene()->clear();
    ui_.tvAngleView->plotScene()->clear();
    
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
void SDDialog::setMeshData(const MainWindow::MeshData& meshData)
{
    meshData_ = meshData;
}

//-----------------------------------------------------------------------------------------------------------------
void SDDialog::showErrorMessage(const QString& message, const std::exception* exception)
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
