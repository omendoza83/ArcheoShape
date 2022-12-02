//=================================================================================================================
/**
 *  @file       XYPlot.cpp
 *  @brief      qt_tools::plots::XYPlot class implementation file.
 *  @details    This file contains the implementation of the qt_tools::plots::XYPlot class.
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
#include <qt_tools/plots/XYPlot.h>
#include <nct/math/math.h>

#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsLineItem>
#include <QtWidgets/QGraphicsEllipseItem>
#include <QtWidgets/QGraphicsPixmapItem>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
qt_tools::plots::XYPlot::XYPlot(QObject* parent) : PlotScene{parent}
{
    try {
        setPlotBackgroundBrush(QColor(255, 255, 255));

        // Set properties to default values.
        setSize();
        
        setPlotBackgroundBrush();

        setMargins();

        setTitle();
        setTitleProperties();

        setPlottingAreaProperties();

        setLegendBoxPosition();
        setLegendBoxText();
        setLegendBoxProperties();    

        setXAxisPosition();
        setXAxisProperties();
        setXAxisName();
        setXAxisAutoAdjustentEnabled();
        setXAxisRange(0.0, 1.0, 5);

        setYAxisPosition();
        setYAxisProperties();
        setYAxisName();
        setYAxisAutoAdjustentEnabled();
        setYAxisRange(0.0, 1.0, 5);
        
    }
    catch (const nct::nct_exception& ex) {
        throw nct::InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw nct::InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }    
    catch (...) {
        throw nct::InitializationException(SOURCE_INFO);
    }    
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
bool qt_tools::plots::XYPlot::isReady() const noexcept
{
    return ready_;
}

//-----------------------------------------------------------------------------------------------------------------
const QBrush& qt_tools::plots::XYPlot::plotBackgroundBrush() const noexcept
{
    return plotBackgroundBrush_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setPlotBackgroundBrush(const QBrush& brush)
{
    plotBackgroundBrush_ = brush;
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
const qt_tools::plots::Margins& qt_tools::plots::XYPlot::margins() const noexcept
{
    return margins_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setMargins(double left, double right,
    double top, double botton) noexcept
{
    margins_.l = nct::math::max(left, 0.0);
    margins_.r = nct::math::max(right, 0.0);
    margins_.t = nct::math::max(top, 0.0);
    margins_.b = nct::math::max(botton, 0.0);
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
const qt_tools::plots::TextSection& qt_tools::plots::XYPlot::titleProperties() const noexcept
{
    return titleSection_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setTitleProperties(const QFont& font,
    const QColor& color, const QPen& framePen, const QBrush& framebrush)
{
    titleSection_.font = font;
    titleSection_.color = color;
    titleSection_.framePen = framePen;
    titleSection_.frameBrush = framebrush;
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setTitle(const QString& title)
{
    titleSection_.text = title;
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
qt_tools::plots::LegendBoxPosition qt_tools::plots::XYPlot::legendBoxPosition() const noexcept
{
    return legendBoxPosition_;
}

//-----------------------------------------------------------------------------------------------------------------
void  qt_tools::plots::XYPlot::setLegendBoxPosition(LegendBoxPosition pos)
{
    if ((pos != LegendBoxPosition::Bottom) && (pos != LegendBoxPosition::BottomLeftCorner) &&
        (pos != LegendBoxPosition::BottomRightCorner) && (pos != LegendBoxPosition::Hidden) &&
        (pos != LegendBoxPosition::Left) && (pos != LegendBoxPosition::Right) &&
        (pos != LegendBoxPosition::Top) && (pos != LegendBoxPosition::TopLeftCorner) &&
        (pos != LegendBoxPosition::TopRightCorner))
        throw nct::ArgumentException("pos", exc_bad_legend_box_position, SOURCE_INFO);
    legendBoxPosition_ = pos;
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
qt_tools::plots::LegendBox qt_tools::plots::XYPlot::legendBoxProperties() const noexcept
{
    return legendBoxSection_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setLegendBoxProperties(
    const QFont& font, const QColor& color, const QPen& framePen, const QBrush& framebrush)
{
    legendBoxSection_.font = font;
    legendBoxSection_.color = color;
    legendBoxSection_.framePen = framePen;
    legendBoxSection_.frameBrush = framebrush;
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setLegendBoxText(const QString& text)
{
    legendBoxSection_.text = text;
}

//-----------------------------------------------------------------------------------------------------------------
const QList<qt_tools::plots::LegendBoxItem>& qt_tools::plots::XYPlot::legendBoxItems() const noexcept
{
    return legendBoxSection_.items;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::clearLegendBoxItems()
{
    legendBoxSection_.items.clear();
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::addLegendBoxItem(const LegendBoxItem& item)
{
    legendBoxSection_.items.append(item);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::addLegendBoxItem(const QColor& color, const QString& text,
    const QString& description)
{
    LegendBoxItem tmpItem;
    tmpItem.color = color;
    tmpItem.text = text;
    tmpItem.description = description;
    legendBoxSection_.items.append(tmpItem);
}

//-----------------------------------------------------------------------------------------------------------------
const qt_tools::plots::PlottingArea& qt_tools::plots::XYPlot::plottingAreaProperties() const noexcept
{
    return plottingSection_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setPlottingAreaProperties(
    const QPen& framePen, const QBrush& backgroundBrush)
{
    plottingSection_.framePen = framePen;
    plottingSection_.backgroundBrush = backgroundBrush;
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
qt_tools::plots::HorizontalAxisPosition qt_tools::plots::XYPlot::xAxisPosition() const noexcept
{
    return xAxisPosition_;
}

//-----------------------------------------------------------------------------------------------------------------
void  qt_tools::plots::XYPlot::setXAxisPosition(HorizontalAxisPosition pos)
{
    if ((pos != HorizontalAxisPosition::Top) && (pos != HorizontalAxisPosition::Bottom))
        throw nct::ArgumentException("pos", exc_bad_axis_position, SOURCE_INFO);
    xAxisPosition_ = pos;
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
const qt_tools::plots::Axis& qt_tools::plots::XYPlot::xAxisProperties() const noexcept
{
    return xAxis_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setXAxisProperties(
    const QFont& nameFont, const QColor& nameColor,
    const QFont& labelFont, const QColor& labelColor, const QPen& pen,
    const QPen& gridPen)
{
    xAxis_.nameFont = nameFont;
    xAxis_.nameColor = nameColor;
    xAxis_.labelFont = labelFont;
    xAxis_.labelColor = labelColor;
    xAxis_.pen = pen;
    xAxis_.gridPen = gridPen;
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setXAxisName(const QString& name)
{
    xAxis_.name = name;
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setXAxisAutoAdjustentEnabled(bool enable) noexcept
{
    xAxis_.adjustRange = enable;
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setXAxisRange(double p1, double p2)
{
    if (p1 == p2)
        p2 += nct::EPS;

    if ((xAxis_.p1 != p1) || (xAxis_.p2 != p2)) {
        xAxis_.p1 = p1;
        xAxis_.p2 = p2;
        xAxis_.m = 1.0;
        xAxis_.a = 0.0;

        ready_ = false;
    }
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setXAxisRange(double p1, double p2, unsigned int nMarks)
{
    setXAxisRange(p1, p2);

    if (xAxis_.p1 < xAxis_.p2)
        xAxis_.labels = labels(xAxis_.p1, xAxis_.p2, nMarks, 4);
    else
        xAxis_.labels = labels(xAxis_.p2, xAxis_.p1, nMarks, 4);

    xAxis_.marks.clear();
    for (const auto& l : xAxis_.labels)
        xAxis_.marks.append(l.first);

    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
const QList<double>& qt_tools::plots::XYPlot::xAxisMarks() const noexcept
{
    return xAxis_.marks;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::clearXAxisMarks()
{
    xAxis_.marks.clear();
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::addXAxisMark(double pos)
{
    xAxis_.marks.append(pos);
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
const QList<std::pair<double, QString>>& qt_tools::plots::XYPlot::xAxisLabels() const noexcept
{
    return xAxis_.labels;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::clearXAxisLabels()
{
    xAxis_.labels.clear();
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::addXAxisLabel(double pos, const QString& text)
{
    xAxis_.labels.append(std::make_pair(pos, text));
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
double qt_tools::plots::XYPlot::horizontalCoordinate(double x) const noexcept
{
    return xAxis_.m*x + xAxis_.a;
}

//-----------------------------------------------------------------------------------------------------------------
double qt_tools::plots::XYPlot::xValue(double p) const noexcept
{
    return (p - xAxis_.a) / xAxis_.m;
}

//-----------------------------------------------------------------------------------------------------------------
qt_tools::plots::VerticalAxisPosition qt_tools::plots::XYPlot::yAxisPosition() const noexcept
{
    return yAxisPosition_;
}

//-----------------------------------------------------------------------------------------------------------------
void  qt_tools::plots::XYPlot::setYAxisPosition(VerticalAxisPosition pos)
{
    if ((pos != VerticalAxisPosition::Left) && (pos != VerticalAxisPosition::Right))
        throw nct::ArgumentException("pos", exc_bad_axis_position, SOURCE_INFO);
    yAxisPosition_ = pos;
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
const qt_tools::plots::Axis& qt_tools::plots::XYPlot::yAxisProperties() const noexcept
{
    return yAxis_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setYAxisProperties(
    const QFont& nameFont, const QColor& nameColor, const QFont& labelFont, 
    const QColor& labelColor, const QPen& pen, const QPen& gridPen)
{
    yAxis_.nameFont = nameFont;
    yAxis_.nameColor = nameColor;
    yAxis_.labelFont = labelFont;
    yAxis_.labelColor = labelColor;
    yAxis_.pen = pen;
    yAxis_.gridPen = gridPen;
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setYAxisName(const QString& name)
{
    yAxis_.name = name;
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setYAxisAutoAdjustentEnabled(bool enable) noexcept
{
    yAxis_.adjustRange = enable;
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setYAxisRange(double p1, double p2)
{
    if (p1 == p2)
        throw nct::ArgumentException("p1, p2", exc_two_variables_have_the_same_value,
        SOURCE_INFO);

    if ((yAxis_.p1 != p1) || (yAxis_.p2 != p2)) {
        yAxis_.p1 = p1;
        yAxis_.p2 = p2;
        yAxis_.m = 1.0;
        yAxis_.a = 0.0;

        ready_ = false;
    }
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setYAxisRange(double p1, double p2, unsigned int nMarks)
{
    setYAxisRange(p1, p2);

    if (yAxis_.p1 < yAxis_.p2)
        yAxis_.labels = labels(yAxis_.p1, yAxis_.p2, nMarks, 4);
    else
        yAxis_.labels = labels(yAxis_.p2, yAxis_.p1, nMarks, 4);

    yAxis_.marks.clear();
    for (const auto& l : yAxis_.labels)
        yAxis_.marks.append(l.first);

    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
const QList<double>& qt_tools::plots::XYPlot::yAxisMarks() const noexcept
{
    return yAxis_.marks;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::clearYAxisMarks()
{
    yAxis_.marks.clear();
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::addYAxisMark(double pos)
{
    yAxis_.marks.append(pos);
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
const QList<std::pair<double, QString>>& qt_tools::plots::XYPlot::yAxisLabels() const noexcept
{
    return yAxis_.labels;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::clearYAxisLabels()
{
    yAxis_.labels.clear();
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::addYAxisLabel(double pos, const QString& text)
{
    yAxis_.labels.append(std::make_pair(pos, text));
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
double qt_tools::plots::XYPlot::verticalCoordinate(double y) const noexcept
{
    return yAxis_.m*y + yAxis_.a;
}

//-----------------------------------------------------------------------------------------------------------------
double qt_tools::plots::XYPlot::yValue(double p) const noexcept
{
    return (p - yAxis_.a) / yAxis_.m;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setPlotImage(const QImage& img)
{
    img_ = img;
}

//=================================================================================================================
//        SLOTS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::setSize(unsigned int w, unsigned int h)
{
    PlotScene::setSize(w, h);
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::clear()
{
    PlotScene::clear();
    ready_ = false;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::XYPlot::drawPlot()
{
    if (ready_)
        return;

    clear();
    setBackgroundBrush(plotBackgroundBrush_);

    try {
        ////////////// Size of the plot /////////////
        double h = height();
        double w = width();

        ////////////// Margins /////////////

        // Title area.
        auto titleVerticalSize = (1.25*QFontMetricsF(titleSection_.font).height())*(
            titleSection_.text.size() > 0);

        // x-axis area.
        int labXMaxWidth = 0;
        for (int i = 0; i < xAxis_.labels.size(); i++) {
            auto labelWidth = QFontMetricsF(xAxis_.labelFont).horizontalAdvance(xAxis_.labels[i].second);
            if (labXMaxWidth < labelWidth)
                labXMaxWidth = labelWidth;
        }
        
        double xMarkLength = xAxis_.marks.size() > 0 ?
            nct::math::max(5.0, QFontMetricsF(xAxis_.labelFont).height() / 2.0) : 0.0;
        double xAxisMargin = labXMaxWidth / 2.;
        double xAxisSize = xMarkLength +
            1.25*QFontMetricsF(xAxis_.nameFont).height()*(xAxis_.name.size() > 0) +
            1.25*QFontMetricsF(xAxis_.labelFont).height()*(xAxis_.labels.size() > 0);

        // y-axis area.
        int labYMaxWidth = 0;
        for (int i = 0; i < yAxis_.labels.size(); i++) {
            auto labelWidth = QFontMetricsF(yAxis_.labelFont).horizontalAdvance(yAxis_.labels[i].second);
            if (labYMaxWidth < labelWidth)
                labYMaxWidth = labelWidth;        
        }

        double yMarkLength = yAxis_.marks.size() > 0 ?
            nct::math::max(5.0, QFontMetricsF(yAxis_.labelFont).height() / 2.0) : 0.0;
        double yAxisSize = yMarkLength +
            QFontMetricsF(yAxis_.nameFont).horizontalAdvance(yAxis_.name) +
            labYMaxWidth + 5 + QFontMetricsF(yAxis_.labelFont).height();
        double yAxisMargin = QFontMetricsF(yAxis_.labelFont).height()*(labYMaxWidth>0);

        // ROI (plotting area).
        double tm = margins_.t + titleVerticalSize + 
            nct::math::max(yAxisMargin, xAxisSize*(xAxisPosition_ == HorizontalAxisPosition::Top));

        double bm = margins_.b + 
            nct::math::max(yAxisMargin, xAxisSize*(xAxisPosition_ == HorizontalAxisPosition::Bottom));
        
        double lm = margins_.l + 
            nct::math::max(xAxisMargin, yAxisSize*(yAxisPosition_ == VerticalAxisPosition::Left));
        
        double rm = margins_.r + 
            nct::math::max(xAxisMargin, yAxisSize*(yAxisPosition_ == VerticalAxisPosition::Right));

        setPlottingAreaRect(lm, tm, w - lm - rm, h - tm - bm);

        ////////////// Add plotting area /////////////
        if ((roi.width() > 0) && (roi.height() > 0)) {
            auto rec = new QGraphicsRectItem(roi);
            rec->setPen(plottingSection_.framePen);
            rec->setBrush(Qt::BrushStyle::NoBrush);
            rec->setZValue(111);
            addItem(rec);

            rec = new QGraphicsRectItem(roi);
            rec->setPen(Qt::PenStyle::NoPen);
            rec->setBrush(plottingSection_.backgroundBrush);
            rec->setZValue(-1);
            addItem(rec);
        }

        ////////////// Add title /////////////
        if ((roi.width() > 0) && (roi.height() > 0) &&
            (titleSection_.text.size() > 0))
        {
            QGraphicsRectItem* rec = new QGraphicsRectItem(margins_.l, margins_.t,
                w - margins_.l - margins_.r, titleVerticalSize);
            rec->setPen(titleSection_.framePen);
            rec->setBrush(titleSection_.frameBrush);
            rec->setZValue(112);
            addItem(rec);

            QGraphicsTextItem* text = new QGraphicsTextItem(titleSection_.text);
            text->setFont(titleSection_.font);
            text->setPos(margins_.l + (w - margins_.l - margins_.r) / 2. - 
                text->boundingRect().width() / 2., margins_.t);
            text->setDefaultTextColor(titleSection_.color);
            text->setZValue(113);
            addItem(text);
        }

        ////////////// Add legend box /////////////
        if ((roi.width() > 0) && (roi.height() > 0) &&
            (legendBoxPosition_ != LegendBoxPosition::Hidden))
        {
            QList<QGraphicsItem *> items;
            auto nItems = legendBoxSection_.items.size();
            double fs = QFontMetricsF(legendBoxSection_.font).height();
            bool addText = (legendBoxSection_.text.size() > 0);

            auto maxWidth = legendBoxSection_.text.size();
            auto maxItemWidth = 0;            
            for (int i = 0; i<nItems; i++) {
                auto ns1 = QFontMetricsF(legendBoxSection_.font).horizontalAdvance(legendBoxSection_.items[i].text) + 0.5*fs;
                auto ns2 = QFontMetricsF(legendBoxSection_.font).horizontalAdvance(legendBoxSection_.items[i].description);

                auto ns = ns1 + ns2;
                if (maxWidth < ns)
                    maxWidth = ns;
                                
                if (maxItemWidth < ns1)
                    maxItemWidth = ns1;
            }

            if ((maxWidth > 0) || (maxItemWidth > 0)) {

                double lbw = fs + maxWidth;
                double lbh = ((double)nItems + addText + 0.5)*fs;

                double x = 0;
                double y = 0;
                switch (legendBoxPosition_) {
                    case LegendBoxPosition::Top:
                        x = roi.x() + roi.width() / 2 - lbw / 2;
                        y = roi.y();
                        break;
                    case LegendBoxPosition::Bottom:
                        x = roi.x() + roi.width() / 2 - lbw / 2;
                        y = roi.y() + roi.height() - lbh;
                        break;
                    case LegendBoxPosition::Left:
                        x = roi.x();
                        y = roi.y() + roi.height()/2. - lbh / 2;
                        break;
                    case LegendBoxPosition::Right:
                        x = roi.x() + roi.width() - lbw;
                        y = roi.y() + roi.height() / 2. - lbh / 2;
                        break;
                    case LegendBoxPosition::TopLeftCorner:
                        x = roi.x();
                        y = roi.y();
                        break;
                    case LegendBoxPosition::TopRightCorner:
                        x = roi.x() + roi.width() - lbw;
                        y = roi.y();
                        break;
                    case LegendBoxPosition::BottomLeftCorner:
                        x = roi.x();
                        y = roi.y() + roi.height() - lbh;
                        break;
                    case LegendBoxPosition::BottomRightCorner:
                        x = roi.x() + roi.width() - lbw;
                        y = roi.y() + roi.height() - lbh;
                        break;
                    case LegendBoxPosition::Hidden:
                        // Do nothing.
                        break;
                }

                QGraphicsRectItem* rec = new QGraphicsRectItem(x, y, lbw, lbh);
                rec->setPen(legendBoxSection_.framePen);
                rec->setBrush(legendBoxSection_.frameBrush);
                items.push_back(rec);

                QGraphicsTextItem* text = new QGraphicsTextItem(legendBoxSection_.text);
                text->setFont(legendBoxSection_.font);
                text->setPos(x + lbw / 2 - text->boundingRect().width() / 2, y);
                text->setDefaultTextColor(legendBoxSection_.color);
                items.push_back(text);

                for (int i = 0; i<nItems; i++) {
                    text = new QGraphicsTextItem(legendBoxSection_.items[i].text);
                    text->setFont(legendBoxSection_.font);
                    text->setDefaultTextColor(legendBoxSection_.items[i].color);
                    text->setPos(x + 0.25*fs, y + ((double)i + addText)*fs);
                    items.push_back(text);

                    text = new QGraphicsTextItem(legendBoxSection_.items[i].description);
                    text->setFont(legendBoxSection_.font);
                    text->setDefaultTextColor(legendBoxSection_.color);
                    text->setPos(x + 0.25*fs + maxItemWidth, y + ((double)i + addText)*fs);
                    items.push_back(text);
                }

                QGraphicsItemGroup* group = createItemGroup(items);
                if (!group)
                    throw nct::OperationException(exc_error_rendering_legend_box, SOURCE_INFO);
                group->setZValue(114);
                group->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
            }
        }        

        ////////////// Add background elements /////////////
        if ((roi.width() > 0) && (roi.height() > 0)) {
            auto rec = new QGraphicsRectItem(margins_.l, margins_.t,
                roi.x() - margins_.l, h - (margins_.l + margins_.r));
            rec->setPen(QPen(plotBackgroundBrush_.color(), Qt::NoPen));
            rec->setBrush(plotBackgroundBrush_);
            rec->setZValue(101);
            addItem(rec);

            rec = new QGraphicsRectItem(roi.x() + roi.width(), margins_.t,
                w - (roi.x() + roi.width() + margins_.r), h - (margins_.l + margins_.r));
            rec->setPen(QPen(plotBackgroundBrush_.color(), Qt::NoPen));
            rec->setBrush(plotBackgroundBrush_);
            rec->setZValue(101);
            addItem(rec);

            rec = new QGraphicsRectItem(margins_.l, margins_.t,
                w - (margins_.l + margins_.r), roi.y() - margins_.t);
            rec->setPen(QPen(plotBackgroundBrush_.color(), Qt::NoPen));
            rec->setBrush(plotBackgroundBrush_);
            rec->setZValue(101);
            addItem(rec);

            rec = new QGraphicsRectItem(margins_.l, roi.y() + roi.height(),
                w - (margins_.l + margins_.r), h - (roi.y() + roi.height() + margins_.b));
            rec->setPen(QPen(plotBackgroundBrush_.color(), Qt::NoPen));
            rec->setBrush(plotBackgroundBrush_);
            rec->setZValue(101);
            addItem(rec);
        }

        ////////////// Add X Axis /////////////
        if ((roi.width() > 0) && (roi.height() > 0)) {
            Axis& ax = xAxis_;
            QList<QGraphicsItem*> items;

            double epsTol = nct::EPS_10000*((std::abs(ax.p1) + std::abs(ax.p2)) / 2.0);
            double min = nct::math::min(ax.p1, ax.p2) - epsTol;
            double max = nct::math::max(ax.p1, ax.p2) + epsTol;

            switch (xAxisPosition_) {
                case HorizontalAxisPosition::Top: {
                    double x = roi.x();
                    double y = roi.y();                    

                    // Transformation parameters.
                    ax.m = (roi.width()) / (ax.p2 - ax.p1);
                    ax.a = x - ax.m*ax.p1;                    

                    // Add line.
                    QGraphicsLineItem* line = new QGraphicsLineItem(x, y, x + roi.width(), y);
                    line->setPen(ax.pen);
                    addItem(line);

                    // Add name.
                    if (ax.name.size() > 0) {
                        QGraphicsTextItem* text = new QGraphicsTextItem(ax.name);
                        text->setFont(ax.nameFont);

                        text->setPos(roi.x() + roi.width() / 2.0 - text->boundingRect().width() / 2,
                            y - xAxisSize);                            

                        text->setDefaultTextColor(ax.nameColor);
                        items.push_back(text);
                    }

                    // Add marks and grid.                        
                    for (int i = 0; i<ax.marks.size(); i++) {
                        if ((ax.marks[i] >= min) && (ax.marks[i] <= max)) {
                            double c = horizontalCoordinate(ax.marks[i]);

                            if (ax.gridPen.style() != Qt::PenStyle::NoPen) {
                                auto gridLine = new QGraphicsLineItem(c, y, c, y + roi.height());
                                gridLine->setPen(ax.gridPen);
                                items.push_back(gridLine);
                            }

                            auto axisLine = new QGraphicsLineItem(c, y, c, y - xMarkLength);
                            axisLine->setPen(ax.pen);
                            items.push_back(axisLine);
                        }
                    }

                    // Add labels.
                    for (int i = 0; i<ax.labels.size(); i++) {
                        if ((ax.labels[i].first >= min) && (ax.labels[i].first <= max)) {
                            double c = horizontalCoordinate(ax.labels[i].first);

                            QGraphicsTextItem* text = new QGraphicsTextItem(ax.labels[i].second);
                            text->setFont(ax.labelFont);

                            text->setPos(c - text->boundingRect().width() / 2, y - xMarkLength -
                                text->boundingRect().height());                                

                            text->setDefaultTextColor(ax.labelColor);
                            items.push_back(text);
                        }
                    }                    
                    break;
                }
                case HorizontalAxisPosition::Bottom: {
                    double x = roi.x();
                    double y = roi.y() + roi.height();

                    // Transformation parameters.
                    ax.m = (roi.width()) / (ax.p2 - ax.p1);
                    ax.a = x - ax.m*ax.p1;

                    // Add line.
                    QGraphicsLineItem* line = new QGraphicsLineItem(x, y, x + roi.width(), y);
                    line->setPen(ax.pen);
                    addItem(line);

                    // Add name.
                    if (ax.name.size() > 0) {
                        QGraphicsTextItem* text = new QGraphicsTextItem(ax.name);
                        text->setFont(ax.nameFont);

                        text->setPos(roi.x() + roi.width() / 2.0 - text->boundingRect().width() / 2,
                            y + xAxisSize - text->boundingRect().height());

                        text->setDefaultTextColor(ax.nameColor);
                        items.push_back(text);
                    }

                    // Add marks and grid.                        
                    for (int i = 0; i<ax.marks.size(); i++) {
                        if ((ax.marks[i] >= min) && (ax.marks[i] <= max)) {
                            double c = horizontalCoordinate(ax.marks[i]);

                            if (ax.gridPen.style() != Qt::PenStyle::NoPen) {
                                auto gridLine = new QGraphicsLineItem(c, y, c, y - roi.height());
                                gridLine->setPen(ax.gridPen);
                                items.push_back(gridLine);
                            }

                            auto axisLine = new QGraphicsLineItem(c, y, c, y + xMarkLength);
                            axisLine->setPen(ax.pen);
                            items.push_back(axisLine);

                        }
                    }

                    // Add labels.
                    for (int i = 0; i<ax.labels.size(); i++) {
                        if ((ax.labels[i].first >= min) && (ax.labels[i].first <= max)) {
                            double c = horizontalCoordinate(ax.labels[i].first);

                            QGraphicsTextItem* text = new QGraphicsTextItem(ax.labels[i].second);
                            text->setFont(ax.labelFont);

                            text->setPos(c - text->boundingRect().width() / 2, y + xMarkLength);

                            text->setDefaultTextColor(ax.labelColor);
                            items.push_back(text);
                        }
                    }                    
                    break;
                }
            }            

            // Add items to the scene.
            QGraphicsItemGroup* group = createItemGroup(items);
            if (!group)
                throw nct::OperationException(exc_error_rendering_horizontal_axis, SOURCE_INFO);
            group->setZValue(102);            
        }

        ////////////// Add Y Axis /////////////
        if ((roi.width() > 0) && (roi.height() > 0)) {
            Axis& ax = yAxis_;
            QList<QGraphicsItem*> items;

            double epsTol = nct::EPS_10000*((std::abs(ax.p1) + std::abs(ax.p2)) / 2.0);
            double min = nct::math::min(ax.p1, ax.p2) - epsTol;
            double max = nct::math::max(ax.p1, ax.p2) + epsTol;

            switch (yAxisPosition_) {
                case VerticalAxisPosition::Left: {
                    double x = roi.x();
                    double y = roi.y() + roi.height();

                    // Transformation parameters.
                    ax.m = -(roi.height()) / (ax.p2 - ax.p1);
                    ax.a = y - ax.m*ax.p1;

                    // Add line.
                    QGraphicsLineItem* line = new QGraphicsLineItem(x, y, x, y - roi.height());
                    line->setPen(ax.pen);
                    addItem(line);

                    // Add name.
                    if (ax.name.size() > 0) {
                        QGraphicsTextItem* text = new QGraphicsTextItem(ax.name);
                        text->setFont(ax.nameFont);

                        text->setPos(x - yAxisSize + 5,
                            roi.y() + roi.height() / 2 - text->boundingRect().height() / 2);

                        text->setDefaultTextColor(ax.nameColor);
                        items.push_back(text);
                    }

                    // Add marks and grid.            
                    for (int i = 0; i<ax.marks.size(); i++) {
                        if ((ax.marks[i] >= min) && (ax.marks[i] <= max)) {
                            double c = verticalCoordinate(ax.marks[i]);

                            if (ax.gridPen.style() != Qt::PenStyle::NoPen) {
                                auto gridLine = new QGraphicsLineItem(x, c, x + roi.width(), c);
                                gridLine->setPen(ax.gridPen);
                                items.push_back(gridLine);
                            }

                            auto axisLine = new QGraphicsLineItem(x, c, x - yMarkLength, c);
                            axisLine->setPen(ax.pen);
                            items.push_back(axisLine);
                        }
                    }

                    // Add labels.
                    for (int i = 0; i<ax.labels.size(); i++) {
                        if ((ax.labels[i].first >= min) && (ax.labels[i].first <= max)) {
                            double c = verticalCoordinate(ax.labels[i].first);

                            QGraphicsTextItem* text = new QGraphicsTextItem(ax.labels[i].second);
                            text->setFont(ax.labelFont);

                            text->setPos(x - text->boundingRect().width() - yMarkLength - 
                                QFontMetricsF(ax.labelFont).height()/8,
                                c - text->boundingRect().height() / 2);

                            text->setDefaultTextColor(ax.labelColor);
                            items.push_back(text);
                        }
                    }                    
                    break;
                }
                case VerticalAxisPosition::Right: {
                    double x = roi.x() + roi.width();
                    double y = roi.y() + roi.height();

                    // Transformation parameters.
                    ax.m = -(roi.height()) / (ax.p2 - ax.p1);
                    ax.a = y - ax.m*ax.p1;

                    // Add line.
                    QGraphicsLineItem* line = new QGraphicsLineItem(x, y, x, y - roi.height());
                    line->setPen(ax.pen);
                    addItem(line);

                    // Add name.
                    if (ax.name.size() > 0) {
                        QGraphicsTextItem* text = new QGraphicsTextItem(ax.name);
                        text->setFont(ax.nameFont);

                        text->setPos(x + yAxisSize - text->boundingRect().width() - 5,
                            roi.y() + roi.height() / 2 - text->boundingRect().height() / 2);

                        text->setDefaultTextColor(ax.nameColor);
                        items.push_back(text);
                    }

                    // Add marks and grid.            
                    for (int i = 0; i<ax.marks.size(); i++) {
                        if ((ax.marks[i] >= min) && (ax.marks[i] <= max)) {
                            double c = verticalCoordinate(ax.marks[i]);

                            if (ax.gridPen.style() != Qt::PenStyle::NoPen) {
                                auto gridLine = new QGraphicsLineItem(x, c, x - roi.width(), c);
                                gridLine->setPen(ax.gridPen);
                                items.push_back(gridLine);
                            }

                            auto axisLine = new QGraphicsLineItem(x, c, x + yMarkLength, c);
                            axisLine->setPen(ax.pen);
                            items.push_back(axisLine);
                        }
                    }

                    // Add labels.
                    for (int i = 0; i<ax.labels.size(); i++) {
                        if ((ax.labels[i].first >= min) && (ax.labels[i].first <= max)) {
                            double c = verticalCoordinate(ax.labels[i].first);

                            QGraphicsTextItem* text = new QGraphicsTextItem(ax.labels[i].second);
                            text->setFont(ax.labelFont);

                            text->setPos(x + yMarkLength + QFontMetricsF(ax.labelFont).height() / 8, 
                                c - text->boundingRect().height() / 2);

                            text->setDefaultTextColor(ax.labelColor);
                            items.push_back(text);
                        }
                    }                    
                    break;
                }
            }

            // Add items to the scene.
            QGraphicsItemGroup* group = createItemGroup(items);
            if (!group)
                throw nct::OperationException(exc_error_rendering_vertical_axis, SOURCE_INFO);
            group->setZValue(103);        
            
        }    

        ////////////// Add plotting image /////////////
        if ((roi.width() > 0) && (roi.height() > 0) && (!img_.isNull())) {
            auto imgItem = addImage(img_);
            imgItem->setZValue(0);
        }

        ////////////// Set ready flag /////////////
        ready_ = true;
    }
    catch (const nct::nct_exception& ex) {
        throw nct::OperationException(exc_error_initialing_plot_scene,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw nct::OperationException(exc_error_initialing_plot_scene,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw nct::OperationException(exc_unknown, SOURCE_INFO);
    }
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
