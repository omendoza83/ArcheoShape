//=================================================================================================================
/**
 *  @file       ResultsDialog.cpp
 *  @brief      ResultsDialog class implementation file.
 *  @details    This file contains the implementation of the ResultsDialog class.          
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
#include "ResultsDialog.h"

#include <fstream>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>

using namespace std;
using namespace nct;


//=================================================================================================================
//        HELPER FUNCTIONS
//=================================================================================================================

/**
 *  @brief      Minimun of two numbers.
 *  @details    This function calculates the minimum of two numbers.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v1  The first number to be compared.
 *  @param[in]  v2  The second number to be compared.
 *  @returns    The smallest of the input numbers.
 */
template<std::totally_ordered T>
constexpr const T& min(const T& v1, const T& v2) noexcept
{
    return v2 < v1 ? (v2) : (v1);
}

//=================================================================================================================
//        CONSTRUCTORS AND DESTRUCTOR
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
ResultsDialog::ResultsDialog(QWidget *objFather): QDialog(objFather)
{
    ui_.setupUi(this);        

    ui_.img1View->setScene(new QGraphicsScene());
    ui_.img2View->setScene(new QGraphicsScene());
    ui_.img3View->setScene(new QGraphicsScene());
    ui_.img4View->setScene(new QGraphicsScene());
    ui_.img5View->setScene(new QGraphicsScene());
    ui_.img6View->setScene(new QGraphicsScene());
    ui_.img7View->setScene(new QGraphicsScene());
    ui_.img8View->setScene(new QGraphicsScene());
    ui_.img9View->setScene(new QGraphicsScene());
    ui_.img10View->setScene(new QGraphicsScene());

    connect(ui_.saveButton, &QPushButton::clicked, this, &ResultsDialog::save);
    connect(ui_.openButton, &QPushButton::clicked, this, &ResultsDialog::open);
    connect(ui_.pageSpinBox, &QSpinBox::valueChanged, this, &ResultsDialog::showPage);

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
}

//=================================================================================================================
//        METHODS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void ResultsDialog::setResults(const nct::Array<unsigned int>& sItems)
{
    if (sItems.size()==0)
        return;

    sortedItems_ = sItems;
    ui_.pageSpinBox->setMinimum(1);
    ui_.pageSpinBox->setMaximum(static_cast<int>(sortedItems_.size()/10 + ( (sortedItems_.size()%10) > 0)));
    showPage(1);
}

//-----------------------------------------------------------------------------------------------------------------
void ResultsDialog::setMeshData(const MainWindow::MeshData& meshData)
{
    meshData_ = meshData;
}

//-----------------------------------------------------------------------------------------------------------------
void ResultsDialog::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Results data file.", "",
        tr("Results file (*.A3R)"));
    if (fileName.length() == 0)
        return;

    try
    {
        ifstream file;
        file.open(fileName.toLatin1().data(), ios_base::binary);
        Array<unsigned int> results = Array<unsigned int>::read(file);
        file.close();
        setResults(results);
    }
    catch (const std::exception& err)
    {
        showErrorMessage("Error loading results file.\n"
            "Make sure the specified path is a valid results file.", &err);
        return;
    }    
}

//-----------------------------------------------------------------------------------------------------------------
void ResultsDialog::save()
{
    if (sortedItems_.size()==0)
        return;

    QString fileNameS = QFileDialog::getSaveFileName(this, "Results data file.", "", 
        tr("Results file (*.A3R)"));
    if (fileNameS.length() == 0)
        return;
    
    QApplication::setOverrideCursor(Qt::WaitCursor);
    try
    {
        ofstream file;
        file.open(fileNameS.toLatin1().data(), ios_base::binary);
        sortedItems_.write(file);
        file.close();

        QApplication::restoreOverrideCursor();
    }
    catch (const std::exception& err)
    {
        QApplication::restoreOverrideCursor();    
        showErrorMessage("Error saving results file. \n"
            "Make sure the specified path is valid.", &err);
    }                
}

//-----------------------------------------------------------------------------------------------------------------
void ResultsDialog::showPage(int i)
{
    if (i<1)
        return;

    if ( (sortedItems_.size() == 0) || (meshData_.nModels == 0) )
        return;

    QGraphicsScene* scenes[10];
    QTableWidget* tables[10];
    QLabel* labels[10];

    scenes[0] = ui_.img1View->scene();
    scenes[1] = ui_.img2View->scene();
    scenes[2] = ui_.img3View->scene();
    scenes[3] = ui_.img4View->scene();
    scenes[4] = ui_.img5View->scene();
    scenes[5] = ui_.img6View->scene();
    scenes[6] = ui_.img7View->scene();
    scenes[7] = ui_.img8View->scene();
    scenes[8] = ui_.img9View->scene();
    scenes[9] = ui_.img10View->scene();

    tables[0] = ui_.res1Table;
    tables[1] = ui_.res2Table;
    tables[2] = ui_.res3Table;
    tables[3] = ui_.res4Table;
    tables[4] = ui_.res5Table;
    tables[5] = ui_.res6Table;
    tables[6] = ui_.res7Table;
    tables[7] = ui_.res8Table;
    tables[8] = ui_.res9Table;
    tables[9] = ui_.res10Table;

    labels[0] = ui_.res1Label;
    labels[1] = ui_.res2Label;
    labels[2] = ui_.res3Label;
    labels[3] = ui_.res4Label;
    labels[4] = ui_.res5Label;
    labels[5] = ui_.res6Label;
    labels[6] = ui_.res7Label;
    labels[7] = ui_.res8Label;
    labels[8] = ui_.res9Label;
    labels[9] = ui_.res10Label;

    unsigned int iniIndex = (i-1)*10;
    unsigned int endIndex = iniIndex + 9;
    endIndex = min(endIndex, min(static_cast<unsigned int>(sortedItems_.size())-1, meshData_.nModels-1));
    unsigned int nItems = endIndex - iniIndex + 1;

    for (unsigned int l=0; l<10; l++)
    {
        labels[l]->setText(QString("Object #") + QString::number(l+iniIndex+1));
        scenes[l]->clear();
        tables[l]->clear();

        tables[l]->setColumnCount(1);
        tables[l]->setRowCount(meshData_.nInfo + 1);

        tables[l]->setVerticalHeaderItem(0, new QTableWidgetItem(QString("Model")));
        tables[l]->verticalHeaderItem(0)->setTextAlignment(Qt::AlignCenter);

        for (unsigned int j=0; j<meshData_.nInfo; j++)
        {
            tables[l]->setVerticalHeaderItem(j+1, new QTableWidgetItem(meshData_.infoFields[j]));
            tables[l]->verticalHeaderItem(j+1)->setTextAlignment(Qt::AlignCenter);        
        }
    }

    for (unsigned int l=0; l<nItems; l++)
    {
        if (sortedItems_[l] < meshData_.nModels)
        {
            tables[l]->setItem(0, 0, new QTableWidgetItem(meshData_.models(sortedItems_[l+iniIndex],0)));
            tables[l]->item(0, 0)->setTextAlignment(Qt::AlignCenter);
            for (unsigned int j=0; j<meshData_.nInfo; j++)
            {
                tables[l]->setItem(j+1, 0, new QTableWidgetItem(meshData_.models(sortedItems_[l+iniIndex],j+1)));    
                tables[l]->item(j+1, 0)->setTextAlignment(Qt::AlignCenter);
            }    
            
            QPixmap img(meshData_.screenshotsPath + meshData_.models(sortedItems_[l + iniIndex], 0) + QString(".jpg"));
            scenes[l]->addPixmap(img.scaled(128,128, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
void ResultsDialog::showErrorMessage(const QString& message, const std::exception* exception)
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
