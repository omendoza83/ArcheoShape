//=================================================================================================================
/**
 *  @file       BaseDialog.cpp
 *  @brief      qt_tools::BaseDialog class implementation file.
 *  @details    This file contains the implementation of the qt_tools::BaseDialog class.
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
#include <qt_tools/BaseDialog.h>

#include <QtCore/QFile>
#include <QtGui/QIcon>
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFrame>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QApplication>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
qt_tools::BaseDialog::BaseDialog(QWidget* contents, const QString& mainText,
    const QString& secondaryText, unsigned int width,
    unsigned int height, const QString& title, QWidget* parent) : QDialog{parent}
{
    // Set dialog properties.
    setWindowTitle(title);
    resize(width, height);
    setMinimumSize(width, height);
    setContextMenuPolicy(Qt::NoContextMenu);
    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

    if (QFile::exists(":/icons/message")) {
        QIcon icon;
        icon.addFile(":/icons/message", QSize(), QIcon::Normal, QIcon::Off);
        setWindowIcon(icon);
    }

    // Build elements of the dialog.
    auto mainLayout = new QVBoxLayout(this);

    if (mainText.size() > 0) {
        auto mainLabel = new QLabel(this);
        QFont font;
        font.setBold(true);
        font.setWeight(QFont::Weight::Bold);
        mainLabel->setFont(font);
        mainLabel->setAlignment(Qt::AlignCenter);
        mainLabel->setWordWrap(true);
        mainLabel->setText(mainText);
        mainLayout->addWidget(mainLabel);
    }

    auto contentsFrame = new QFrame(this);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(contentsFrame->sizePolicy().hasHeightForWidth());
    contentsFrame->setSizePolicy(sizePolicy);
    contentsFrame->setFrameShape(QFrame::StyledPanel);
    contentsFrame->setFrameShadow(QFrame::Raised);
    mainLayout->addWidget(contentsFrame);

    if (secondaryText.size() > 0) {
        auto secondaryLabel = new QLabel(this);
        secondaryLabel->setAlignment(Qt::AlignJustify | Qt::AlignVCenter);
        secondaryLabel->setWordWrap(true);
        secondaryLabel->setText(secondaryText);
        mainLayout->addWidget(secondaryLabel);
    }

    if (contents != nullptr) {        
        contents->setParent(this);
        auto contentsLayout = new QGridLayout(contentsFrame);
        contentsLayout->addWidget(contents, 0, 0);
        contentsLayout->setSpacing(0);
        contentsLayout->setContentsMargins(6, 6, 6, 6);
    }

    // Update styles and size of dialog.
    ensurePolished();
    adjustSize();
    move(QGuiApplication::primaryScreen()->availableGeometry().center() - rect().center());
}

//-----------------------------------------------------------------------------------------------------------------
qt_tools::BaseDialog::BaseDialog(QWidget* contents, unsigned int width,
    unsigned int height, const QString& title, QWidget* parent) :
    BaseDialog{contents, "", "", width, height, title, parent}
{

}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::BaseDialog::closeEvent(QCloseEvent* e)
{
    emit closed();
    QDialog::closeEvent(e);
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
