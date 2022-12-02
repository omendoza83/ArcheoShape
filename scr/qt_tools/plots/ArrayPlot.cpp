//=================================================================================================================
/**
 *  @file       ArrayPlot.cpp
 *  @brief      qt_tools::plots::ArrayPlot class implementation file.
 *  @details    This file contains the implementation of the qt_tools::plots::ArrayPlot class.
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

//=================================================================================================================
//        HEADERS AND NAMESPACES
//=================================================================================================================
#include <qt_tools/plots/ArrayPlot.h>

#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsLineItem>
#include <QtWidgets/QGraphicsEllipseItem>
#include <QtWidgets/QGraphicsPixmapItem>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
qt_tools::plots::ArrayPlot::ArrayPlot(QObject* parent) : XYColorPlot{parent}
{

}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::ArrayPlot::clearData()
{
    clear();
    
    data_.reverseVerticalAxis = false;
    data_.name = "";
    data_.defaultColor = QColor(0, 0, 0, 255);    
    data_.arr = std::make_shared<nct::Matrix>();
    data_.useDefaultColor = std::make_shared<nct::Array2D<bool>>();

    clearLegendBoxItems();
    clearColorbarMarks();
    clearColorbarLabels();
    clearXAxisMarks();
    clearXAxisLabels();
    clearYAxisMarks();
    clearYAxisLabels();

    setXAxisRange(0, 1, 5);
    setYAxisRange(0, 1, 5);
    setColorbarRange(-1, 1, 3);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::ArrayPlot::configPlot(const nct::Matrix& arr, 
    const QString& name, bool reverse)
{
    configPlot(std::make_shared<nct::Matrix>(arr),
        std::make_shared<nct::Array2D<bool>>(arr.rows(), arr.columns(), false),
        QColor(0, 0, 0, 255), name, reverse);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::ArrayPlot::configPlot(nct::Matrix&& arr,
    const QString& name, bool reverse)
{
    configPlot(std::make_shared<nct::Matrix>(std::move(arr)),
        std::make_shared<nct::Array2D<bool>>(arr.rows(), arr.columns(), false),
        QColor(0, 0, 0, 255), name, reverse);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::ArrayPlot::configPlot(const std::shared_ptr<nct::Matrix>& arr,
    const QString& name, bool reverse)
{
    if (arr == nullptr) {
        configPlot(nullptr, nullptr, QColor(0, 0, 0, 255), name, reverse);
    }
    else {
        configPlot(arr, std::make_shared<nct::Array2D<bool>>(arr->rows(), arr->columns(), false),
            QColor(0, 0, 0, 255), name, reverse);
    }
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::ArrayPlot::configPlot(const nct::Matrix& arr,
    const nct::Array2D<bool>& useDefaultColor, 
    const QColor& defaultColor, const QString& name, bool reverse)
{
    configPlot(std::make_shared<nct::Matrix>(arr),
        std::make_shared<nct::Array2D<bool>>(useDefaultColor),
        defaultColor, name, reverse);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::ArrayPlot::configPlot(nct::Matrix&& arr,
    nct::Array2D<bool>&& useDefaultColor, 
    const QColor& defaultColor, const QString& name, bool reverse)
{
    configPlot(std::make_shared<nct::Matrix>(std::move(arr)),
        std::make_shared<nct::Array2D<bool>>(std::move(useDefaultColor)),
        defaultColor, name, reverse);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::ArrayPlot::configPlot(const std::shared_ptr<nct::Matrix>& arr,
    const std::shared_ptr<nct::Array2D<bool>>& useDefaultColor,
    const QColor& defaultColor, const QString& name, bool reverse)
{
    if (arr == nullptr)
        throw nct::NullPointerException("arr", SOURCE_INFO);

    if (useDefaultColor == nullptr)
        throw nct::NullPointerException("useDefaultColor", SOURCE_INFO);

    if ((arr->rows() != useDefaultColor->rows()) || (arr->columns() != useDefaultColor->columns()))
        throw nct::ArgumentException("arr, useDefaultColor", exc_arrays_of_different_lengths, SOURCE_INFO);

    data_.reverseVerticalAxis = reverse;
    data_.name = name;
    data_.defaultColor = defaultColor;
    data_.arr = arr;
    data_.useDefaultColor = useDefaultColor;

    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::ArrayPlot::configPlot(
    const QColor& defaultColor, const QString& name, bool reverse)
{
    data_.reverseVerticalAxis = reverse;
    data_.name = name;
    data_.defaultColor = defaultColor;
    
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
const qt_tools::plots::ArrayPlot::PlotProperties& 
qt_tools::plots::ArrayPlot::plotProperties() const noexcept
{
    return data_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::ArrayPlot::drawPlot()
{
    try {
        bool validData = false;
        if (data_.arr != nullptr) {
            validData = data_.arr->size() > 0;
            if ((data_.arr->rows() != data_.useDefaultColor->rows()) ||
                (data_.arr->columns() != data_.useDefaultColor->columns()))
                throw nct::ConfigurationException(exc_bad_arrays_for_plotting, SOURCE_INFO);

            // Set colorbar limits.
            if (data_.arr->size() > 0 && colorbar_.adjustRange) {
                double min = data_.arr->min();
                double max = data_.arr->max();
                if (min == max)
                    max++;
                setColorbarRange(min, max, colorbar_.marks.size());
            }
        }
        // Render elements of the plot.
        XYColorPlot::drawPlot();
        if ((roi.width() < 0) || (roi.height() < 0))
            return;

        if (!validData)
            return;

        // Draw data.
        unsigned int rows = static_cast<unsigned int>(data_.arr->rows());
        unsigned int columns = static_cast<unsigned int>(data_.arr->columns());
        QImage plotImg(rows, columns, QImage::Format::Format_RGB32);
        QRgb pColor;
        for (unsigned int i=0; i<rows; i++) {
            for (unsigned int j=0; j<columns; j++) {
                if (!data_.useDefaultColor->at(i,j)) {
                    pColor = valueToColor(data_.arr->at(i, j)).rgb();
                }
                else {
                    pColor = data_.defaultColor.rgb();
                }

                if (!data_.reverseVerticalAxis)
                    plotImg.setPixel(i, columns - j - 1, pColor);
                else
                    plotImg.setPixel(i, j, pColor);
            }
        }    
        
        // Add image to the scene and scale it.
        auto plotItem = addImage(plotImg);
        plotItem->setZValue(1);

    }
    catch (const nct::nct_exception& ex) {
        throw nct::OperationException(exc_error_rendering_plot,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw nct::OperationException(exc_error_rendering_plot, 
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw nct::OperationException(exc_unknown, SOURCE_INFO);
    }
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
