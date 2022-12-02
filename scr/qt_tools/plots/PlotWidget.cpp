//=================================================================================================================
/**
 *  @file       PlotWidget.cpp
 *  @brief      qt_tools::plots::PlotWidget class implementation file.
 *  @details    This file contains the implementation of the qt_tools::plots::PlotWidget class.
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
#include <qt_tools/qt_tools.h>
#include "ui_PlotWidget.h"

#include <qt_tools/plots/PlotWidget.h>
#include <qt_tools/BaseDialog.h>

#include <QtWidgets/QFileDialog>
#include <QtGui/QClipboard>

/** Definition to address the user interface. */
#define UI reinterpret_cast<Ui::PlotWidget*>(ui_.get())

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
qt_tools::plots::PlotWidget::PlotWidget(QWidget* parent) : QWidget{parent}
{
    ui_ = std::make_shared<Ui::PlotWidget>();
    UI->setupUi(this);
    UI->plotView->addAction(UI->saveAction);
    UI->plotView->addAction(UI->clipboardAction);
    connect(UI->saveAction, &QAction::triggered, this, &PlotWidget::saveImage);
    connect(UI->clipboardAction, &QAction::triggered, this, &PlotWidget::toClipboard);

    if (QFile::exists(":/icons/save")) {
        QIcon icon;
        icon.addFile(":/icons/save", QSize(), QIcon::Normal, QIcon::Off);
        UI->saveAction->setIcon(icon);
    }

    if (QFile::exists(":/icons/clipBoard")) {
        QIcon icon;
        icon.addFile(":/icons/clipBoard", QSize(), QIcon::Normal, QIcon::Off);
        UI->clipboardAction->setIcon(icon);
    }

    configWidget();
}

//-----------------------------------------------------------------------------------------------------------------
qt_tools::plots::PlotWidget::PlotWidget(
    const std::shared_ptr<plots::PlotScene>& plot, ResizePolicy policy,
    const QString& mainText, const QString& infoText,
    const QString& saveText, const QString& clipboardText,
    QWidget* parent) : QWidget{parent}
{
    ui_ = std::make_shared<Ui::PlotWidget>();
    UI->setupUi(this);
    UI->plotView->addAction(UI->saveAction);
    UI->plotView->addAction(UI->clipboardAction);

    connect(UI->saveAction, &QAction::triggered, this, &PlotWidget::saveImage);
    connect(UI->clipboardAction, &QAction::triggered, this, &PlotWidget::toClipboard);

    configWidget(plot, policy, mainText, infoText, saveText, clipboardText);
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotWidget::configWidget(
    const std::shared_ptr<plots::PlotScene>& plot, ResizePolicy policy,
    const QString& mainText, const QString& infoText,
    const QString& saveText, const QString& clipboardText)
{
    if ((policy != ResizePolicy::Ignore) &&
        (policy != ResizePolicy::Resize))
        throw nct::ArgumentException("policy", exc_bad_resize_policy, SOURCE_INFO);

    UI->mainTextLabel->setText(mainText);
    if (mainText.size() == 0)
        UI->mainTextLabel->setVisible(false);
    UI->infoTextLabel->setText(infoText);
    if (infoText.size() == 0)
        UI->infoTextLabel->setVisible(false);
    
    UI->saveAction->setText(saveText);
    UI->clipboardAction->setText(clipboardText);

    scene_ = plot;
    UI->plotView->setScene(scene_.get());

    resizePolicy_ = policy;
    if (resizePolicy_ == ResizePolicy::Resize) {
        UI->plotView->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        UI->plotView->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        if (scene_ != nullptr)
            scene_->setSize(UI->plotView->width(), UI->plotView->height());        
    }
    else {
        UI->plotView->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        UI->plotView->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
    }
    
    // Draw plot for first time.
    if (scene_ != nullptr)
        scene_->drawPlot();
}

//-----------------------------------------------------------------------------------------------------------------
qt_tools::plots::PlotWidget::ResizePolicy qt_tools::plots::PlotWidget::resizePolicy() const
{
    return resizePolicy_;
}

//-----------------------------------------------------------------------------------------------------------------
std::shared_ptr<qt_tools::plots::PlotScene>& qt_tools::plots::PlotWidget::plotScene()
{
    return scene_;
}

//-----------------------------------------------------------------------------------------------------------------
const std::shared_ptr<qt_tools::plots::PlotScene>& 
qt_tools::plots::PlotWidget::plotScene() const
{
    return scene_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotWidget::resizeEvent(QResizeEvent* e)
{    
    if (scene_ == nullptr)
        return;

    if (resizePolicy_ == ResizePolicy::Resize) {
        scene_->setSize(UI->plotView->width(), UI->plotView->height());
        scene_->drawPlot();
    }

    QWidget::resizeEvent(e);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotWidget::closeEvent(QCloseEvent* e)
{
    emit closed();
    e->accept();
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotWidget::showPlot(QWidget* parent,
    const std::shared_ptr<plots::PlotScene>& plot, ResizePolicy policy,
    const QString& mainText, const QString& infoText,
    const QString& saveText, const QString& clipboardText,
    const QString& title)
{
    PlotWidget* content = new PlotWidget(plot, policy, mainText, infoText, saveText, clipboardText);

    BaseDialog dialog(content, 800, 600, title,parent);
    dialog.exec();
}

//=================================================================================================================
//        SLOTS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotWidget::setResizePolicy(ResizePolicy policy)
{
    if ((policy != ResizePolicy::Ignore) &&
        (policy != ResizePolicy::Resize))
        throw nct::ArgumentException("policy", exc_bad_resize_policy, SOURCE_INFO);
    
    resizePolicy_ = policy;
    if (resizePolicy_ == ResizePolicy::Resize) {
        UI->plotView->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        UI->plotView->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scene_->setSize(UI->plotView->width(), UI->plotView->height());
        scene_->drawPlot();
    }
    else {
        UI->plotView->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        UI->plotView->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
    }
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotWidget::setScene(const std::shared_ptr<plots::PlotScene>& plot)
{
    scene_ = plot;
    UI->plotView->setScene(scene_.get());
    if (scene_ != nullptr) {
        if (resizePolicy_ == ResizePolicy::Resize)
            scene_->setSize(UI->plotView->width(), UI->plotView->height());
        scene_->drawPlot();
    }
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotWidget::saveImage()
{
    if (scene_ == nullptr)
        return;

    QString file = QFileDialog::getSaveFileName(this, "", "",
        tr("Bitmap file (*.bmp);;JPG file (*.jpg);;PNG file (*.png)"));
    if (file.isEmpty())
        return;

    scene_->toImage().save(file);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::plots::PlotWidget::toClipboard()
{
    if (scene_ == nullptr)
        return;

    QApplication::clipboard()->setImage(scene_->toImage());
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
