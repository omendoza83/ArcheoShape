//=================================================================================================================
/**
 *  @file       PlotScene.cpp
 *  @brief      qt_tools::plots::PlotScene class implementation file.
 *  @details    This file contains the implementation of the qt_tools::plots::PlotScene class.
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
#include <qt_tools/plots/PlotScene.h>
#include <nct/math/math.h>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
qt_tools::plots::PlotScene::PlotScene(QObject* parent) : QGraphicsScene{parent}
{    
    roi = QRectF(nct::MINUS_INF, nct::MINUS_INF, nct::PLUS_INF - nct::MINUS_INF,
        nct::PLUS_INF - nct::MINUS_INF);
        
    previewPen_ = QColor(50, 60, 40);
    previewPen_.setStyle(Qt::PenStyle::DashLine);
    previewPen_.setWidth(3);
    
    itemPen_ = QColor(60, 50, 200);
    itemPen_.setWidth(3);

    itemBrush_ = QColor(180, 180, 180, 60);

    itemFont_ = QFont(QtConfig::instance().defaultFontName(), 
        QtConfig::instance().defaultPlotFontSize(), QFont::Normal);

    itemText_ = "text";
}

//=================================================================================================================
//        DESTRUCTOR
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
qt_tools::plots::PlotScene::~PlotScene()
{
    clear();
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
qt_tools::plots::PlotScene::SelectionMode qt_tools::plots::PlotScene::operationMode() const noexcept
{
    return selectionMode_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::setOperationMode(SelectionMode selectionMode)
{
    if ((selectionMode != SelectionMode::Locked) &&
        (selectionMode != SelectionMode::ItemSelection) &&
        (selectionMode != SelectionMode::ItemInsertion) &&
        (selectionMode != SelectionMode::OneItemInsertion))
        throw nct::ArgumentException("selectionMode", exc_bad_selection_mode, SOURCE_INFO);

    if (selectionMode_ == selectionMode)
        return;

    selectionMode_ = selectionMode;
}

//-----------------------------------------------------------------------------------------------------------------
unsigned int qt_tools::plots::PlotScene::graphicsItemCount() const noexcept
{
    return items_.count();
}

//-----------------------------------------------------------------------------------------------------------------
const QGraphicsItem* qt_tools::plots::PlotScene::graphicsItem(int index) const
{
    if ((index < 0) || (index >= items_.count()))
        throw nct::IndexOutOfRangeException("index", SOURCE_INFO);

    return items_[index];
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::removeItem(int index)
{
    if ((index < 0) || (index >= items_.count()))
        throw nct::IndexOutOfRangeException("index", SOURCE_INFO);

    auto item = items_[index];
    if (item->scene() == this)
        removeItem(item);
    
    items_.removeAt(index);
    delete item;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::removeItem(QGraphicsItem* item)
{
    if (item == nullptr)
        return;

    if (item->scene() == this)
        QGraphicsScene::removeItem(item);

    if (item == previewItem_) {
        delete previewItem_;
        previewItem_ = nullptr;
    }
    else {
        auto index = items_.indexOf(item);
        if ((index >= 0) && (index < items_.count())) {
            items_.removeAt(index);
            delete item;
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
qt_tools::plots::PlotScene::GraphicsItem qt_tools::plots::PlotScene::itemType() const noexcept
{
    return itemType_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::setItemType(GraphicsItem itemType)
{
    if ((itemType != GraphicsItem::Point) &&
        (itemType != GraphicsItem::Mark) &&
        (itemType != GraphicsItem::CompleteMark) &&
        (itemType != GraphicsItem::HorizontalLine) &&
        (itemType != GraphicsItem::VerticalLine) &&
        (itemType != GraphicsItem::Line) &&
        (itemType != GraphicsItem::Segment) &&
        (itemType != GraphicsItem::Arrow) &&
        (itemType != GraphicsItem::CenteredLine) &&
        (itemType != GraphicsItem::CenteredCircle) &&
        (itemType != GraphicsItem::Rectangle) &&
        (itemType != GraphicsItem::Ellipse) &&
        (itemType != GraphicsItem::FilledRectangle) &&
        (itemType != GraphicsItem::FilledEllipse) &&
        (itemType != GraphicsItem::Text))
        throw nct::ArgumentException("itemType", exc_bad_item_type, SOURCE_INFO);

    itemType_ = itemType;
}

//-----------------------------------------------------------------------------------------------------------------
bool qt_tools::plots::PlotScene::itemSelectable() const noexcept
{
    return itemSelectable_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::setItemSelectable(bool select)
{
    itemSelectable_ = select;
}

//-----------------------------------------------------------------------------------------------------------------
bool qt_tools::plots::PlotScene::itemMovable() const noexcept
{
    return itemMovable_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::setItemMovable(bool mov)
{
    itemMovable_ = mov;
}

//-----------------------------------------------------------------------------------------------------------------
double qt_tools::plots::PlotScene::itemZValue() const noexcept
{
    return itemZValue_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::setItemZValue(double z)
{
    itemZValue_ = z;
}

//-----------------------------------------------------------------------------------------------------------------
double qt_tools::plots::PlotScene::itemSize() const noexcept
{
    return itemSize_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::setItemSize(double s)
{
    itemSize_ = s;
}

//-----------------------------------------------------------------------------------------------------------------
const QPen& qt_tools::plots::PlotScene::itemPen() const noexcept
{
    return itemPen_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::setItemPen(const QPen& p)
{
    itemPen_ = p;
}

//-----------------------------------------------------------------------------------------------------------------
const QBrush& qt_tools::plots::PlotScene::itemBrush() const noexcept
{
    return itemBrush_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::setItemBrush(const QBrush& b)
{
    itemBrush_ = b;
}

//-----------------------------------------------------------------------------------------------------------------
const QFont& qt_tools::plots::PlotScene::itemFont() const noexcept
{
    return itemFont_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::setItemFont(const QFont& f)
{
    itemFont_ = f;
}

//-----------------------------------------------------------------------------------------------------------------
const QString& qt_tools::plots::PlotScene::itemText() const noexcept
{
    return itemText_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::setItemText(const QString& t)
{
    itemText_ = t;
}

//-----------------------------------------------------------------------------------------------------------------
const QPen& qt_tools::plots::PlotScene::previewPen() const noexcept
{
    return previewPen_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::setPreviewPen(const QPen& p)
{
    previewPen_ = p;
}

//-----------------------------------------------------------------------------------------------------------------
const QRectF& qt_tools::plots::PlotScene::plottingAreaRect() const noexcept
{
    return roi;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::setPlottingAreaRect(double x, double y, double w, double h)
{
    roi.setRect(x, y, w, h);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::setPlottingAreaRect(const QRectF& rect)
{
    roi = rect;
}

//-----------------------------------------------------------------------------------------------------------------
QImage qt_tools::plots::PlotScene::toImage()
{
     QImage img(static_cast<unsigned int>(width()), static_cast<unsigned int>(height()), 
         QImage::Format_RGB32);
     img.fill(QColor(255,255,255).rgb());
     
     QPainter painter(&img);
     painter.setRenderHints(QPainter::RenderHint::Antialiasing | QPainter::RenderHint::TextAntialiasing |
         QPainter::RenderHint::SmoothPixmapTransform);
     QGraphicsScene::render(&painter);

     return img;
}

//-----------------------------------------------------------------------------------------------------------------
QList<std::pair<double, QString>> qt_tools::plots::PlotScene::labels(
    double min, double max, unsigned int nLabels, unsigned int prec)
{
    if (min >= max)
        throw nct::ArgumentException("min, max", exc_bad_bounds, SOURCE_INFO);

    QList<std::pair<double, QString>> lab;
    
    if (nLabels>1) {
        double sp = (max - min) / (nLabels - 1);
        double epss = std::abs(sp)*std::sqrt(nct::EPS);
        if ((min<0) && (max>0)) {
            double exp = std::pow(10, static_cast<double>(nct::math::mostSignificantDigitPosition(sp)));
            double step = 0.0;
            for (double nnt = 0.0; nnt<10.00; nnt += 0.10) {
                double spp = nnt*exp;
                unsigned int nn = static_cast<unsigned int>(std::abs(min - epss) / spp);
                unsigned int np = static_cast<unsigned int>((max + epss) / spp);
                unsigned int nt = nn + np + 1;
                if (nt >= nLabels)
                    step = nnt;
            }

            double spp = step*exp;
            double ini = -static_cast<int>(epss + std::abs(min) / spp)*spp;
            for (unsigned int i = 0; i<nLabels; i++)
                lab.append(std::make_pair(ini + spp*i, QString::number(ini + spp*i, 'g', prec)));
        }
        else {
            double ini = 0, end = 0;

            if (min<0) {
                double msd = nct::math::mostSignificantDigit(min);
                double exp = std::pow(10, static_cast<double>(
                    nct::math::mostSignificantDigitPosition(min)));
                double step = 0.0;
                ini = -msd*exp;
                for (double nnt = 0.0; nnt <= 10.00; nnt += 0.10) {
                    if ((ini - nnt*exp) >= (min - epss))
                        step = nnt*exp;
                }
                ini -= step;
            }
            else if (min > 0) {
                double msd = nct::math::mostSignificantDigit(min);
                double exp = std::pow(10, static_cast<double>(
                    nct::math::mostSignificantDigitPosition(min)));
                double step = 10.00;
                ini = msd*exp;
                for (double nnt = 10.00; nnt >= 0.00; nnt -= 0.10) {
                    if ((ini + nnt*exp) >= (min - epss))
                        step = nnt*exp;
                }
                ini += step;
            }

            if (max<0) {
                double msd = nct::math::mostSignificantDigit(max);
                double exp = std::pow(10, static_cast<double>(
                    nct::math::mostSignificantDigitPosition(max)));
                double step = 10.0;
                end = -msd*exp;
                for (double nnt = 10.0; nnt >= 0.00; nnt -= 0.10) {
                    if ((end - nnt*exp) <= (max + epss))
                        step = nnt*exp;
                }
                end -= step;
            }
            else if (max>0) {
                double msd = nct::math::mostSignificantDigit(max);
                double exp = std::pow(10, static_cast<double>(
                    nct::math::mostSignificantDigitPosition(max)));
                double step = 0.0;
                end = msd*exp;
                for (double nnt = 0.0; nnt <= 10.00; nnt += 0.10) {
                    if ((end + nnt*exp) <= (max + epss))
                        step = nnt*exp;
                }
                end += step;
            }

            double spp = (end - ini) / (nLabels - 1);
            for (unsigned int i = 0; i<nLabels; i++)
                lab.append(std::make_pair(ini + spp*i, QString::number(ini + spp*i, 'g', prec)));
        }
    }
    else if (nLabels == 1) {
        if ((min<0) && (max>0)) {
            lab.append(std::make_pair(0., QString::number(0., 'g', prec)));
        }
        else {
            lab.append(std::make_pair(min, QString::number(min, 'g', prec)));
        }
    }

    return lab;
}

//-----------------------------------------------------------------------------------------------------------------
QList<QColor> qt_tools::plots::PlotScene::colorPalette(nct::color::ColorPalette::ColorPaletteName palette,
    unsigned int size)
{
    auto pal = nct::color::ColorPalette(palette).rgbStrings(size);
    QList<QColor> p;
    for (index_t i = 0; i < pal.size(); i++)
        p.append(QColor(pal[i].c_str()));
    return p;
}

//-----------------------------------------------------------------------------------------------------------------
QImage qt_tools::plots::PlotScene::drawPalette(const QList<QColor>& palette, unsigned int w,
    bool vertical, bool reverse)
{
    // Check colors.
    unsigned int size = static_cast<unsigned int>(palette.size());

    // Create image.
    QImage newImage;

    if (vertical) {
        newImage = QImage(w, size, QImage::Format::Format_RGB32);
        if (!reverse) {
            for (unsigned int i=0; i<size; i++)
                for (unsigned int j = 0; j<w; j++)
                    newImage.setPixel(j, size - i - 1, palette[i].rgba());
        }
        else {
            for (unsigned int i=0; i<size; i++)
                for (unsigned int j = 0; j<w; j++)
                    newImage.setPixel(j, size - i - 1, palette[size - i - 1].rgba());
        }
    }
    else {
        newImage = QImage(size, w, QImage::Format::Format_RGB32);
        if (!reverse) {
            for (unsigned int i=0; i<size; i++)
                for (unsigned int j = 0; j<w; j++)
                    newImage.setPixel(i, j, palette[i].rgba());
        }
        else {
            for (unsigned int i=0; i<size; i++)
                for (unsigned int j = 0; j<w; j++)
                    newImage.setPixel(i, j, palette[size - i - 1].rgba());
        }
    }

    return newImage;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::keyPressEvent(QKeyEvent* e)
{
    if (selectionMode_ != SelectionMode::Locked) {
        switch (e->key()) {
            case Qt::Key_Delete:
                clearSelectedItems();
                break;
            case Qt::Key_Backspace:
                clearSelectedItems();
                break;
        }
    }

    QGraphicsScene::keyPressEvent(e);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::keyReleaseEvent(QKeyEvent* e)
{
    QGraphicsScene::keyReleaseEvent(e);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    if (e->button() != Qt::LeftButton) {
        QGraphicsScene::mousePressEvent(e);
        return;
    }

    QPointF pos = e->scenePos();
    if (selectionMode_ == SelectionMode::Locked) {
        if ((pos.rx() >= roi.x()) && (pos.rx() <= (roi.x() + roi.width())) &&
            (pos.ry() >= roi.y()) && (pos.ry() <= (roi.y() + roi.height())))
            emit mousePressed(pos.x(), pos.y());
    }
    else if (selectionMode_ == SelectionMode::ItemSelection) {
        if ((pos.rx() >= roi.x()) && (pos.rx() <= (roi.x() + roi.width())) &&
            (pos.ry() >= roi.y()) && (pos.ry() <= (roi.y() + roi.height())))
        {
            if (previewItem_ != nullptr) {
                QGraphicsScene::removeItem(previewItem_);
                delete previewItem_;
                previewItem_ = nullptr;
            }

            mx_ = pos.rx();
            my_ = pos.ry();
            mousePressed_ = true;

            emit mousePressed(pos.x(), pos.y());
        }
    }
    else {
        if ((pos.rx() >= roi.x()) && (pos.rx() <= (roi.x() + roi.width())) &&
            (pos.ry() >= roi.y()) && (pos.ry() <= (roi.y() + roi.height())))
        {
            if (previewItem_ != nullptr) {
                QGraphicsScene::removeItem(previewItem_);
                delete previewItem_;
                previewItem_ = nullptr;
            }

            mx_ = pos.rx();
            my_ = pos.ry();
            mousePressed_ = true;

            emit mousePressed(pos.x(), pos.y());
        }
    }

    QGraphicsScene::mousePressEvent(e);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::mouseMoveEvent(QGraphicsSceneMouseEvent* e)
{
    QPointF pos = e->scenePos();
    if (selectionMode_ == SelectionMode::Locked) {
        if ((pos.rx() >= roi.x()) && (pos.rx() <= (roi.x() + roi.width())) &&
            (pos.ry() >= roi.y()) && (pos.ry() <= (roi.y() + roi.height())))
            emit mouseMoved(pos.x(), pos.y());
    }
    else if (selectionMode_ == SelectionMode::ItemSelection) {
        if ((pos.rx() >= roi.x()) && (pos.rx() <= (roi.x() + roi.width())) &&
            (pos.ry() >= roi.y()) && (pos.ry() <= (roi.y() + roi.height())))
        {
            if (mousePressed_) {
                if (previewItem_ != nullptr) {
                    QGraphicsScene::removeItem(previewItem_);
                    delete previewItem_;
                    previewItem_ = nullptr;
                }

                double w = pos.rx() - mx_;
                double h = pos.ry() - my_;
                previewItem_ = addRectangle(mx_, my_, w, h, previewPen_);                
            }
            emit mouseMoved(pos.x(), pos.y());
        }        
    }
    else {
        if (previewItem_ != nullptr) {
            QGraphicsScene::removeItem(previewItem_);
            delete previewItem_;
            previewItem_ = nullptr;
        }

        if ((pos.rx() >= roi.x()) && (pos.rx() <= (roi.x() + roi.width())) &&
            (pos.ry() >= roi.y()) && (pos.ry() <= (roi.y() + roi.height())))
        {
            if (mousePressed_) {
                if (itemType_ == GraphicsItem::Point) {
                    previewItem_ = addPoint(pos.rx(), pos.ry(), itemSize_, previewPen_);
                }
                else if (itemType_ == GraphicsItem::Mark) {
                    previewItem_ = addMark(pos.rx(), pos.ry(), itemSize_, previewPen_);
                }
                else if (itemType_ == GraphicsItem::CompleteMark) {
                    previewItem_ = addCompleteMark(pos.rx(), pos.ry(), previewPen_);
                }
                else if (itemType_ == GraphicsItem::HorizontalLine) {
                    previewItem_ = addHorizontalLine(pos.ry(), previewPen_);
                }
                else if (itemType_ == GraphicsItem::VerticalLine) {
                    previewItem_ = addVerticalLine(pos.rx(), previewPen_);
                }
                else if (itemType_ == GraphicsItem::Line) {
                    previewItem_ = addLine(mx_, my_, pos.rx(), pos.ry(), previewPen_);
                }
                else if (itemType_ == GraphicsItem::Segment) {
                    previewItem_ = addSegment(mx_, my_, pos.rx(), pos.ry(), itemSize_, previewPen_);
                }
                else if (itemType_ == GraphicsItem::Arrow) {
                    previewItem_ = addArrow(mx_, my_, pos.rx(), pos.ry(), itemSize_, previewPen_);
                }
                else if (itemType_ == GraphicsItem::CenteredLine) {
                    previewItem_ = addCenteredLine(pos.rx(), pos.ry(), previewPen_);
                }
                else if (itemType_ == GraphicsItem::CenteredCircle) {
                    previewItem_ = addCenteredCircle(pos.rx(), pos.ry(), previewPen_);
                }
                else if (itemType_ == GraphicsItem::Rectangle) {
                    double w = pos.rx() - mx_;
                    double h = pos.ry() - my_;
                    previewItem_ = addRectangle(mx_, my_, w, h, previewPen_);
                }
                else if (itemType_ == GraphicsItem::Ellipse) {
                    double w = pos.rx() - mx_;
                    double h = pos.ry() - my_;
                    previewItem_ = addEllipse(mx_, my_, w, h, previewPen_);
                }
                else if (itemType_ == GraphicsItem::FilledRectangle) {
                    double w = pos.rx() - mx_;
                    double h = pos.ry() - my_;
                    previewItem_ = addRectangle(mx_, my_, w, h, previewPen_);
                }
                else if (itemType_ == GraphicsItem::FilledEllipse) {
                    double w = pos.rx() - mx_;
                    double h = pos.ry() - my_;
                    previewItem_ = addEllipse(mx_, my_, w, h, previewPen_);
                }
                else if (itemType_ == GraphicsItem::Text) {
                    previewItem_ = addText(pos.rx(), pos.ry(), itemText_, itemFont_, previewPen_.color());
                }

                if (previewItem_!=nullptr) {
                    previewItem_->setZValue(1000);
                    previewItem_->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable, false);
                    previewItem_->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable, false);
                }                
            }
            emit mouseMoved(pos.x(), pos.y());
        }
    }

    QGraphicsScene::mouseMoveEvent(e);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* e)
{
    if (e->button() != Qt::LeftButton) {
        QGraphicsScene::mouseReleaseEvent(e);
        return;
    }
        
    QPointF pos = e->scenePos();
    if (selectionMode_ == SelectionMode::Locked) {
        if ((pos.rx() >= roi.x()) && (pos.rx() <= (roi.x() + roi.width())) &&
            (pos.ry() >= roi.y()) && (pos.ry() <= (roi.y() + roi.height())))
            emit mouseReleased(pos.x(), pos.y());        
    }
    else if (selectionMode_ == SelectionMode::ItemSelection) {
        if (previewItem_ != nullptr) {
            QPainterPath path;
            path.addRect(previewItem_->boundingRect());
            setSelectionArea(path);

            QGraphicsScene::removeItem(previewItem_);
            delete previewItem_;
            previewItem_ = nullptr;
        }
        
        if ((pos.rx() >= roi.x()) && (pos.rx() <= (roi.x() + roi.width())) &&
            (pos.ry() >= roi.y()) && (pos.ry() <= (roi.y() + roi.height())))
            emit mouseReleased(pos.x(), pos.y());
    }
    else {
        if (previewItem_ != nullptr) {
            QGraphicsScene::removeItem(previewItem_);
            delete previewItem_;
            previewItem_ = nullptr;
        }

        if ((pos.rx() >= roi.x()) && (pos.rx() <= (roi.x() + roi.width())) &&
            (pos.ry() >= roi.y()) && (pos.ry() <= (roi.y() + roi.height())))
        {
            if (mousePressed_) {
                QGraphicsItem* item = nullptr;
                if (itemType_ == GraphicsItem::Point) {
                    item = addPoint(pos.rx(), pos.ry(), itemSize_, itemPen_);
                }
                else if (itemType_ == GraphicsItem::Mark) {
                    item = addMark(pos.rx(), pos.ry(), itemSize_, itemPen_);
                }
                else if (itemType_ == GraphicsItem::CompleteMark) {
                    item = addCompleteMark(pos.rx(), pos.ry(), itemPen_);
                }
                else if (itemType_ == GraphicsItem::HorizontalLine) {
                    item = addHorizontalLine(pos.ry(), itemPen_);
                }
                else if (itemType_ == GraphicsItem::VerticalLine) {
                    item = addVerticalLine(pos.rx(), itemPen_);
                }
                else if (itemType_ == GraphicsItem::CenteredCircle) {
                    item = addCenteredCircle(pos.rx(), pos.ry(), itemPen_);
                }
                else if (itemType_ == GraphicsItem::Line) {
                    item = addLine(mx_, my_, pos.rx(), pos.ry(), itemPen_);
                }
                else if (itemType_ == GraphicsItem::Segment) {
                    item = addSegment(mx_, my_, pos.rx(), pos.ry(), itemSize_, itemPen_);
                }
                else if (itemType_ == GraphicsItem::Arrow) {
                    item = addArrow(mx_, my_, pos.rx(), pos.ry(), itemSize_, itemPen_);
                }
                else if (itemType_ == GraphicsItem::CenteredLine) {
                    item = addCenteredLine(pos.rx(), pos.ry(), itemPen_);
                }
                else if (itemType_ == GraphicsItem::Rectangle) {
                    double w = pos.rx() - mx_;
                    double h = pos.ry() - my_;
                    item = addRectangle(mx_, my_, w, h, itemPen_);
                }
                else if (itemType_ == GraphicsItem::Ellipse) {
                    double w = pos.rx() - mx_;
                    double h = pos.ry() - my_;
                    item = addEllipse(mx_, my_, w, h, itemPen_);
                }
                else if (itemType_ == GraphicsItem::FilledRectangle) {
                    double w = pos.rx() - mx_;
                    double h = pos.ry() - my_;
                    item = addFilledRectangle(mx_, my_, w, h, itemBrush_, itemPen_);
                }
                else if (itemType_ == GraphicsItem::FilledEllipse) {
                    double w = pos.rx() - mx_;
                    double h = pos.ry() - my_;
                    item = addFilledEllipse(mx_, my_, w, h, itemBrush_, itemPen_);
                }
                else if (itemType_ == GraphicsItem::Text) {
                    item = addText(pos.rx(), pos.ry(), itemText_, itemFont_, itemPen_.color());
                }

                if (item != nullptr) {
                    if (selectionMode_ == SelectionMode::OneItemInsertion) {
                        // Clear previous items.
                        for (int index = 0; index < items_.count(); index++) {
                            auto oldItem = items_[index];
                            if (oldItem->scene() == this)
                                removeItem(oldItem);
                        }
                        items_.clear();
                    }

                    item->setZValue(itemZValue_);
                    item->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable, itemMovable_);
                    item->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable, itemSelectable_);
                    items_.push_back(item);
                }
            }
            emit mouseReleased(pos.x(), pos.y());
        }
    }
        
    mousePressed_ = false;
    QGraphicsScene::mouseReleaseEvent(e);    
}

//-----------------------------------------------------------------------------------------------------------------
QGraphicsItem* qt_tools::plots::PlotScene::addPoint(double x, double y, double pointWidth, 
    const QPen& p)
{
    if (pointWidth == 0)
        return nullptr;

    if (pointWidth < 0)
        throw nct::ArgumentException("pointWidth", pointWidth, 0.,
        nct::RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    QBrush b(p.color(), Qt::SolidPattern);
                
    QGraphicsEllipseItem* ell = new QGraphicsEllipseItem(x-pointWidth/2, y-pointWidth/2, 
        pointWidth, pointWidth);
    ell->setPen(p);
    ell->setBrush(b);
    
    addItem(ell);

    return ell;
}

//-----------------------------------------------------------------------------------------------------------------
QGraphicsItem* qt_tools::plots::PlotScene::addMark(double x, double y, double lineLength, 
    const QPen& p)
{
    if (lineLength < 0)
        throw nct::ArgumentException("lineLength", lineLength, 0.,
        nct::RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    QList<QGraphicsItem *> items;
                        
    QGraphicsLineItem* line = new QGraphicsLineItem(x-lineLength/2, y, x+lineLength/2, y);
    line->setPen(p);
    items.push_back(line);

    line = new QGraphicsLineItem(x, y-lineLength/2, x, y + lineLength/2);
    line->setPen(p);
    items.push_back(line);

    QGraphicsItemGroup* group = createItemGroup(items);
    if (!group)
        throw nct::OperationException(exc_error_adding_mark, SOURCE_INFO);

    return group;
}

//-----------------------------------------------------------------------------------------------------------------
QGraphicsItem* qt_tools::plots::PlotScene::addCompleteMark(double x, double y,
    const QPen& p)
{
    QList<QGraphicsItem *> items;
    QGraphicsLineItem* line = new QGraphicsLineItem(roi.x(), y, roi.x() + roi.width(), y);
    line->setPen(p);
    items.push_back(line);

    line = new QGraphicsLineItem(x, roi.y(), x, roi.y() + roi.height());
    line->setPen(p);
    items.push_back(line);

    QGraphicsItemGroup* group = createItemGroup(items);
    if (!group)
        throw nct::OperationException(exc_error_adding_mark, SOURCE_INFO);

    return group;
}

//-----------------------------------------------------------------------------------------------------------------
QGraphicsItem* qt_tools::plots::PlotScene::addVerticalLine(double x, const QPen& p)
{
    QGraphicsLineItem* line = new QGraphicsLineItem(x, roi.y(), x, roi.y() + roi.height());
    line->setPen(p);
    addItem(line);

    return line;
}

//-----------------------------------------------------------------------------------------------------------------
QGraphicsItem* qt_tools::plots::PlotScene::addHorizontalLine(double y, const QPen& p)
{
    QGraphicsLineItem* line = new QGraphicsLineItem(roi.x(), y, roi.x() + roi.width(), y);
    line->setPen(p);
    addItem(line);    

    return line;
}

//-----------------------------------------------------------------------------------------------------------------
QGraphicsItem* qt_tools::plots::PlotScene::addLine(double x1, double y1, double x2, double y2, 
    const QPen& p)
{
    QGraphicsLineItem* line = new QGraphicsLineItem(x1, y1, x2, y2);
    line->setPen(p);
    addItem(line);

    return line;
}

//-----------------------------------------------------------------------------------------------------------------
QGraphicsItem* qt_tools::plots::PlotScene::addSegment(double x1, double y1, double x2, double y2, 
    double endLength, const QPen& p)
{
    if (endLength < 0)
        throw nct::ArgumentException("endLength", endLength, 0.,
        nct::RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    QList<QGraphicsItem *> items;
    QGraphicsLineItem* line = new QGraphicsLineItem(x1, y1, x2, y2);
    line->setPen(p);
    items.push_back(line);

    double v = std::sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
    if (v > 0) {
        double xsc = (endLength/2.)*(y2-y1)/v;
        double ysc = (endLength/2.)*(x2-x1)/v;

        double x3 = x1 + xsc; double x4 = 2*x1 - x3;
        double y3 = y1 - ysc; double y4 = 2*y1 - y3;

        double x5 = x2 - xsc; double x6 = 2*x2 - x5;
        double y5 = y2 + ysc; double y6 = 2*y2 - y5;

        line = new QGraphicsLineItem(x3, y3, x4, y4);
        line->setPen(p);
        items.push_back(line);

        line = new QGraphicsLineItem(x5, y5, x6, y6);
        line->setPen(p);
        items.push_back(line);
    }

    QGraphicsItemGroup* group = createItemGroup(items);
    if (!group)
        throw nct::OperationException(exc_error_adding_line, SOURCE_INFO);

    return group;
}

//-----------------------------------------------------------------------------------------------------------------
QGraphicsItem* qt_tools::plots::PlotScene::addArrow(double x1, double y1, double x2, double y2, 
    double endLength, const QPen& p)
{
    if (endLength < 0)
        throw nct::ArgumentException("endLength", endLength, 0.,
        nct::RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    QList<QGraphicsItem *> items;
    QGraphicsLineItem* line = new QGraphicsLineItem(x1, y1, x2, y2);
    line->setPen(p);
    items.push_back(line);

    double v = std::sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
    if (v > 0) {
        double v1 = endLength*(x1-x2)/v;
        double v2 = endLength*(y1-y2)/v;
        double xsc = (endLength/2.)*(y2-y1)/v;
        double ysc = (endLength/2.)*(x2-x1)/v;

        double x1t = x2 - xsc; double x2t = 2*x2 - x1t;
        double y1t = y2 + ysc; double y2t = 2*y2 - y1t;

        double x3 = x1t + v1; double x4 = x2t + v1;
        double y3 = y1t + v2; double y4 = y2t + v2;
                

        line = new QGraphicsLineItem(x2, y2, x3, y3);
        line->setPen(p);
        items.push_back(line);

        line = new QGraphicsLineItem(x2, y2, x4, y4);
        line->setPen(p);
        items.push_back(line);
    }

    QGraphicsItemGroup* group = createItemGroup(items);
    if (!group)
        throw nct::OperationException(exc_error_adding_line, SOURCE_INFO);

    return group;
}

//-----------------------------------------------------------------------------------------------------------------
QGraphicsItem* qt_tools::plots::PlotScene::addCenteredLine(double x, double y,
    const QPen& p)
{
    double cx = roi.x() + roi.width()/2.;
    double cy = roi.y() + roi.height() / 2.;
    
    QGraphicsLineItem* line = new QGraphicsLineItem(cx, cy, x, y);
    line->setPen(p);
    addItem(line);

    return line;
}

//-----------------------------------------------------------------------------------------------------------------
QGraphicsItem* qt_tools::plots::PlotScene::addCenteredCircle(double x, double y, 
    const QPen& p)
{
    double cx = roi.x() + roi.width() / 2.;
    double cy = roi.y() + roi.height() / 2.;

    double r = std::sqrt((x - cx)*(x - cx) + (y - cy)*(y - cy));
    return addCenteredCircle(r, p);
}

//-----------------------------------------------------------------------------------------------------------------
QGraphicsItem* qt_tools::plots::PlotScene::addCenteredCircle(double r, const QPen& p)
{
    double cx = roi.x() + roi.width() / 2.;
    double cy = roi.y() + roi.height() / 2.;
    double w = roi.width();
    double h = roi.height();

    if (r < 0)
        throw nct::ArgumentException("r", r, 0.,
        nct::RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    double maxR = (w<h? w : h) / 2.0;
    if (r > maxR)
        r = maxR;    

    QGraphicsEllipseItem* ell = new QGraphicsEllipseItem(cx-r, cy-r, 2*r, 2*r);
    ell->setPen(p);    
    addItem(ell);

    return ell;
}

//-----------------------------------------------------------------------------------------------------------------
QGraphicsItem* qt_tools::plots::PlotScene::addRectangle(double x, double y, double w, double h,
    const QPen& p)
{
    QList<QGraphicsItem *> items;
        
    QGraphicsLineItem* line = new QGraphicsLineItem(x, y, x+w, y);
    line->setPen(p);
    items.push_back(line);

    line = new QGraphicsLineItem(x, y, x, y + h);
    line->setPen(p);
    items.push_back(line);

    line = new QGraphicsLineItem(x+w, y, x+w, y + h);
    line->setPen(p);
    items.push_back(line);

    line = new QGraphicsLineItem(x, y+h, x+w, y + h);
    line->setPen(p);
    items.push_back(line);

    QGraphicsItemGroup* group = createItemGroup(items);
    if (!group)
        throw nct::OperationException(exc_error_adding_rectangle,  SOURCE_INFO);

    return group;
}

//-----------------------------------------------------------------------------------------------------------------
QGraphicsItem* qt_tools::plots::PlotScene::addEllipse(double x, double y, double w, double h,
    const QPen& p)
{
    QGraphicsEllipseItem* ell = new QGraphicsEllipseItem(x, y, w, h);
    ell->setPen(p);
    addItem(ell);

    return ell;
}

//-----------------------------------------------------------------------------------------------------------------
QGraphicsItem* qt_tools::plots::PlotScene::addFilledRectangle(double x, double y, double w, 
    double h, const QBrush& b, const QPen& p)
{
    QGraphicsRectItem* rect = new QGraphicsRectItem(x, y, w, h);
    rect->setPen(p);
    rect->setBrush(b);
    addItem(rect);

    return rect;
}

//-----------------------------------------------------------------------------------------------------------------
QGraphicsItem* qt_tools::plots::PlotScene::addFilledEllipse(double x, double y, double w, 
    double h, const QBrush& b, const QPen& p)
{
    QGraphicsEllipseItem* ell = new QGraphicsEllipseItem(x, y, w, h);
    ell->setPen(p);
    ell->setBrush(b);
    addItem(ell);

    return ell;
}

//-----------------------------------------------------------------------------------------------------------------
QGraphicsItem* qt_tools::plots::PlotScene::addText(double x, double y, QString& text, 
    const QFont& font, const QColor& color)
{
    QGraphicsTextItem* txt = new QGraphicsTextItem(text);
    txt->setFont(font);
    txt->setDefaultTextColor(color);
    txt->setPos(x, y);
    addItem(txt);

    return txt;
}

//-----------------------------------------------------------------------------------------------------------------
QGraphicsPixmapItem* qt_tools::plots::PlotScene::addImage(const QImage& img)
{
    if (img.isNull())
        return nullptr;

    QGraphicsPixmapItem* item = nullptr;
    if ((static_cast<int>(roi.width()) == img.width()) &&
        (static_cast<int>(roi.height()) == img.height()))
    {
        QPixmap px = QPixmap::fromImage(img, Qt::AutoColor);
        item = addPixmap(px);        
    }
    else {
        auto scaledImage = img.scaled(static_cast<int>(roi.width()), static_cast<int>(roi.height()),
            Qt::AspectRatioMode::IgnoreAspectRatio, Qt::TransformationMode::FastTransformation);
        QPixmap px = QPixmap::fromImage(scaledImage, Qt::AutoColor);
        item = addPixmap(px);
    }
    
    if (item == nullptr)
        throw nct::OperationException(exc_error_adding_image, SOURCE_INFO);
    item->setPos(roi.x(), roi.y());

    return item;
}

//=================================================================================================================
//        SLOTS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::setSize(unsigned int w, unsigned int h)
{
    if (w == 0)
        throw nct::ArgumentException("w", w, 0U,
        nct::RelationalOperator::GreaterThan, SOURCE_INFO);

    if (h == 0)
        throw nct::ArgumentException("h", h, 0U,
        nct::RelationalOperator::GreaterThan, SOURCE_INFO);

    clear();
    setSceneRect(0, 0, w, h);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::clear()
{
    mx_ = 0;
    my_ = 0;
    mousePressed_ = false;
    items_.clear();
    if (previewItem_ != nullptr) {
        QGraphicsScene::removeItem(previewItem_);
        delete previewItem_;
        previewItem_ = nullptr;
    }

    QGraphicsScene::clear();    

    emit sceneCleared();
    emit interactiveItemsCleared();
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::drawPlot()
{
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::lockScene()
{
    setOperationMode(SelectionMode::Locked);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::setSelectionOn()
{
    setOperationMode(SelectionMode::ItemSelection);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::setInsertionOn()
{
    setOperationMode(SelectionMode::ItemInsertion);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::setUnitaryInsertionOn()
{
    setOperationMode(SelectionMode::OneItemInsertion);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::clearInteractiveItems()
{
    mx_ = 0;
    my_ = 0;
    mousePressed_ = false;
    if (previewItem_ != nullptr) {
        QGraphicsScene::removeItem(previewItem_);
        delete previewItem_;
        previewItem_ = nullptr;
    }

    for (int index = 0; index < items_.count(); index++) {
        auto item = items_[index];
        if (item->scene() == this)
            removeItem(item);
    }
    items_.clear();
    
    emit interactiveItemsCleared();
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotScene::clearSelectedItems()
{
    mx_ = 0;
    my_ = 0;
    mousePressed_ = false;
    if (previewItem_ != nullptr) {
        QGraphicsScene::removeItem(previewItem_);
        delete previewItem_;
        previewItem_ = nullptr;
    }

    auto selItems = selectedItems();

    for (auto selItem : selItems) {
        auto index = items_.indexOf(selItem);
        if ((index >= 0) && (index < items_.count()))
            items_.removeAt(index);
        
        QGraphicsScene::removeItem(selItem);
        delete selItem;        
    }
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
