//=================================================================================================================
/**
 *  @file       StemPlot.cpp
 *  @brief      qt_tools::plots::StemPlot class implementation file.
 *  @details    This file contains the implementation of the qt_tools::plots::StemPlot class.
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
#include <qt_tools/plots/StemPlot.h>
#include <nct/math/math.h>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
qt_tools::plots::StemPlot::StemPlot(QObject* parent) : XYPlot{parent}
{
    
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::StemPlot::clearData()
{
    clear();
    data_.clear();
    
    clearLegendBoxItems();
    clearXAxisMarks();
    clearXAxisLabels();
    clearYAxisMarks();
    clearYAxisLabels();

    setXAxisRange(0, 1, 5);
    setYAxisRange(0, 1, 5);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::StemPlot::addDataSet(const nct::RealVector& x, 
    const nct::RealVector& y,
    const QString& name, double pointWidth, 
    const QPen& pen, const QBrush& brush)
{
    addDataSet(std::make_shared<nct::RealVector>(x), 
        std::make_shared<nct::RealVector>(y),
        name, pointWidth, pen, brush);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::StemPlot::addDataSet(nct::RealVector&& x, 
    nct::RealVector&& y,
    const QString& name, double pointWidth, 
    const QPen& pen, const QBrush& brush)
{
    addDataSet(std::make_shared<nct::RealVector>(std::move(x)),
        std::make_shared<nct::RealVector>(std::move(y)),
        name, pointWidth, pen, brush);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::StemPlot::addDataSet(const std::shared_ptr<nct::RealVector>& x, 
    const std::shared_ptr<nct::RealVector>& y,
    const QString& name, double pointWidth, 
    const QPen& pen, const QBrush& brush)
{
    if (pointWidth<0)
        throw nct::ArgumentException("pointWidth", pointWidth, 0.0,
        nct::RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    if (x == nullptr)
        throw nct::NullPointerException("x", SOURCE_INFO);

    if (y == nullptr)
        throw nct::NullPointerException("y", SOURCE_INFO);

    if (x->size() != y->size())
        throw nct::ArgumentException("x, y", exc_arrays_of_different_lengths,
        SOURCE_INFO);

    DataProperties newDataSet;
    newDataSet.pointWidth = pointWidth;
    newDataSet.pen = pen;
    newDataSet.brush = brush;
    newDataSet.name = name;
    newDataSet.x = x;
    newDataSet.y = y;
    data_.push_back(newDataSet);

    ready_ = false;
    addLegendBoxItem(pen.color(), QChar(0x25CF), name);

}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::StemPlot::addDataSet(const nct::RealVector& y,
    const QString& name, double pointWidth, 
    const QPen& pen, const QBrush& brush)
{
    addDataSet(std::make_shared<nct::RealVector>(y),
        name, pointWidth, pen, brush);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::StemPlot::addDataSet(nct::RealVector&& y,
    const QString& name, double pointWidth, 
    const QPen& pen, const QBrush& brush)
{
    addDataSet(std::make_shared<nct::RealVector>(std::move(y)),
        name, pointWidth, pen, brush);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::StemPlot::addDataSet(const std::shared_ptr<nct::RealVector>& y,
    const QString& name, double pointWidth, 
    const QPen& pen, const QBrush& brush)
{
    if (y == nullptr) {
        addDataSet(nullptr, nullptr, name, pointWidth, pen, brush);
    }
    else {
        auto n = y->size();
        auto x = std::make_shared<nct::RealVector>(n);
        for (index_t i = 0; i<n; i++)
            x->at(i) = static_cast<double>(i);

        addDataSet(x, y, name, pointWidth, pen, brush);
    }
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::StemPlot::configDataSet(unsigned int i,
    const QString& name, double pointWidth, const QPen& pen, const QBrush& brush)
{
    if (i >= static_cast<unsigned int>(data_.size()))
        throw nct::IndexOutOfRangeException("i", SOURCE_INFO);

    if (pointWidth<0)
        throw nct::ArgumentException("pointWidth", pointWidth, 0.0,
        nct::RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);
    
    data_[i].pen = pen;
    data_[i].brush = brush;
    data_[i].name = name;    
    data_[i].pointWidth = pointWidth;
    
    ready_ = false;

    clearLegendBoxItems();
    for (const auto& set : data_)
        addLegendBoxItem(set.pen.color(), QChar(0x25CF), set.name);
}

//-----------------------------------------------------------------------------------------------------------------
unsigned int qt_tools::plots::StemPlot::dataSetCount() const noexcept
{
    return static_cast<unsigned int>(data_.size());
}

//-----------------------------------------------------------------------------------------------------------------
const qt_tools::plots::StemPlot::DataProperties& qt_tools::plots::StemPlot::dataSet(
    unsigned int i) const
{
    auto size = static_cast<unsigned int>(data_.size());
    if (i >= size)
        throw nct::IndexOutOfRangeException("i", SOURCE_INFO);

    return data_[static_cast<int>(i)];
}                

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::StemPlot::drawPlot()
{
    try {
        for (const auto& di : data_) {
            if (di.x->size() != di.y->size())
                throw nct::ArgumentException(exc_bad_arrays_for_plotting,
                SOURCE_INFO);
        }

        //  Compute new limits.
        int nSets = data_.size();
        if ((nSets > 0) && xAxis_.adjustRange) {
            double min = nct::PLUS_INF;
            double max = nct::MINUS_INF;
        
            for (int p = 0; p<nSets; p++) {
                auto n = data_[p].x->size();
                if (n == 0)
                    continue;

                double mint = data_[p].x->min();
                double maxt = data_[p].x->max();

                if (mint < min)
                    min = mint;

                if (maxt > max)
                    max = maxt;        
            }

            double diff = max - min;
            if (diff>0) {
                double exp = std::pow(10, (nct::math::mostSignificantDigitPosition(diff) - 1.));
                min-=exp;
                max+=exp;
            }
            else {
                max++;
            }

            setXAxisRange(min, max, xAxis_.marks.size());
        }

        if ((nSets > 0) && yAxis_.adjustRange) {
            double min = nct::PLUS_INF;
            double max = nct::MINUS_INF;
        
            for (int p = 0; p<nSets; p++) {
                auto n = data_[p].y->size();
                if (n == 0)
                    continue;

                double mint = data_[p].y->min();
                double maxt = data_[p].y->max();

                if (mint < min)
                    min = mint;

                if (maxt > max)
                    max = maxt;        
            }

            double diff = max - min;
            if (diff>0) {
                double exp = std::pow(10, (nct::math::mostSignificantDigitPosition(diff) - 1.));
                min-=exp;
                max+=exp;
            }
            else {
                max++;
            }    

            setYAxisRange(min, max, yAxis_.marks.size());
        }

        // Render elements of the plot.
        XYPlot::drawPlot();
        if ((roi.width() < 0) || (roi.height() < 0))
            return;

        // Draw data.
        for (int p = 0; p<nSets; p++) {
            DataProperties& set = data_[p];
            auto n = set.x->size();
            if (n == 0)
                continue;

            QList<QGraphicsItem*> items;

            double y0 = verticalCoordinate(0);
            for (index_t i=0; i<n; i++) {
                auto x = horizontalCoordinate(set.x->at(i));
                auto y = verticalCoordinate(set.y->at(i));
                
                auto line = new QGraphicsLineItem(x, y0, x, y);
                line->setPen(set.pen);
                items.push_back(line);
                
                auto mark = new QGraphicsEllipseItem(x-set.pointWidth/2., y-set.pointWidth/2.,
                    set.pointWidth, set.pointWidth);
                mark->setPen(set.pen);
                mark->setBrush(set.brush);
                items.push_back(mark);
            }

            // Add chart to the scene.
            auto group = createItemGroup(items);
            group->setZValue(p + 1);
        }
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
