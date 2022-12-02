//=================================================================================================================
/**
 *  @file       PlotWidget.h
 *  @brief      qt_tools::plots::PlotWidget class.
 *  @details    Declaration of the qt_tools::plots::PlotWidget class.
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

#ifndef QT_TOOLS_PLOT_WIDGET_H_INCLUDE
#define QT_TOOLS_PLOT_WIDGET_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <qt_tools/qt_tools.h>
#include <nct/nct_exception.h>
#include <qt_tools/plots/PlotScene.h>

#include <QtWidgets/QWidget>
#include <QtGui/QPen>

#include <tuple>

//=================================================================================================================
namespace qt_tools {
namespace plots {

/**
 *  @brief      Plot widget.
 *  @details    Basic widget that shows a plot.
 */
class QT_TOOLS_EXPIMP PlotWidget : public QWidget {
    Q_OBJECT

public:

    ////////// Enumerations //////////        

    /**
     *  @brief      Resize policies.
     *  @details    Different ways how the plot is resized when the widget dimensions
     *              have changed.
     */
    enum class ResizePolicy : unsigned char {

        Ignore,     /**< Ignore resizing. */

        Resize,     /**< Resize scene to fit into the scene. */
    };

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    Default constructor of the widget.
     *  @param[in]  parent  The parent widget.
     */
    PlotWidget(QWidget* parent = nullptr);

    /**
     *  @brief      Class constructor.
     *  @details    Class constructor that initializes the properties of the widget.
     *  @param[in]  plot  Plot scene.
     *  @param[in]  policy  Resize policy.
     *  @param[in]  mainText  The main text to be shown in the widget.
     *  @param[in]  infoText  The text with the information about the widget.
     *  @param[in]  saveText  Text that is shown next with the "save image" option.
     *  @param[in]  clipboardText  Text that is shown with the "copy to clipboard" option.
     *  @param[in]  parent  The parent widget.
     */
    PlotWidget(
        const std::shared_ptr<plots::PlotScene>& plot,
        ResizePolicy policy,
        const QString& mainText = "",
        const QString& infoText = "",
        const QString& saveText = tr("Save Plot"),
        const QString& clipboardText = tr("To Clipboard"),
        QWidget* parent = nullptr);
    
    /**
     *  @brief      Copy constructor.
     *  @details    This constructor is deleted.
     */
    PlotWidget(const PlotWidget&) = delete;
    
    /**
     *  @brief      Move constructor.
     *  @details    This constructor is deleted.
     */
    PlotWidget(PlotWidget&&) = delete;
    
    ////////// Destructor //////////

    /**
     *  @brief      Destructor.
     *  @details    Class destructor. 
     */
    ~PlotWidget() = default;

    ////////// Operators //////////
    
    /**
     *  @brief      Assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    PlotWidget& operator=(const PlotWidget&) = delete;
    
    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    PlotWidget& operator=(PlotWidget&&) = delete;

    ////////// Member functions //////////

    /**
     *  @brief      Configure widget.
     *  @details    This function configures the main properties of the widget.
     *  @param[in]  plot  Plot scene.
     *  @param[in]  policy  Resize policy.
     *  @param[in]  mainText  The main text to be shown in the widget.
     *  @param[in]  infoText  The text with the information about the widget.
     *  @param[in]  saveText  Text that is shown next with the "save image" option.
     *  @param[in]  clipboardText  Text that is shown with the "copy to clipboard" option.
     */
    void configWidget(
        const std::shared_ptr<plots::PlotScene>& plot = nullptr,
        ResizePolicy policy = ResizePolicy::Resize,
        const QString& mainText = "",
        const QString& infoText = "",
        const QString& saveText = tr("Save Plot"),
        const QString& clipboardText = tr("To Clipboard"));

    /**
     *  @brief      Resize policy.
     *  @details    This function returns whether the plot is resized when the widget's dimensions
     *              have changed.
     *  @returns    The resize policy.
     */
    ResizePolicy resizePolicy() const;

    /**
     *  @brief      Current plot scene.
     *  @details    This function returns the current plot scene.
     *  @returns    The current plot.
     */
    std::shared_ptr<plots::PlotScene>& plotScene();

    /**
     *  @brief      Current plot scene.
     *  @details    This function returns the current plot scene.
     *  @returns    The current plot.
     */
    const std::shared_ptr<plots::PlotScene>& plotScene() const;

    /**
     *  @brief      Show plot.
     *  @details    This function shows a dialog with a plot.
     *  @param[in]  parent  The parent widget.
     *  @param[in]  plot  Plot scene.
     *  @param[in]  policy  Resize policy.
     *  @param[in]  mainText  The main text to be shown in the widget.
     *  @param[in]  infoText  The text with the information about the widget.
     *  @param[in]  saveText  Text that is shown next with the "save image" option.
     *  @param[in]  clipboardText  Text that is shown with the "copy to clipboard" option.
     *  @param[in]  title  The title of the dialog.
     */
    static void showPlot(
        QWidget* parent,
        const std::shared_ptr<plots::PlotScene>& plot = nullptr,
        ResizePolicy policy = ResizePolicy::Resize,
        const QString& mainText = "",
        const QString& infoText = "",
        const QString& saveText = tr("Save Plot"),
        const QString& clipboardText = tr("To Clipboard"),
        const QString& title = tr("Plot Dialog"));

    public slots:

    ////////// Slots //////////

    /**
     *  @brief      Set resize policy.
     *  @details    This function modifies the resize policy of the widget.
     *  @param[in]  policy  The new policy of the plot widget.
     */
    void setResizePolicy(ResizePolicy policy);

    /**
     *  @brief      Set scene.
     *  @details    This function modifies the scene that is being shown in the widget.
     *  @param[in]  plot  The new scene.
     */
    void setScene(const std::shared_ptr<plots::PlotScene>& plot);

signals:

    ////////// Signals //////////

    /**
     *  @brief      Widget closed.
     *  @details    This signal is produced whenever the widget is shown on the screen as a window and
     *              the user closed it.
     */
    void closed();

protected:

    ////////// Member functions //////////

    /**
     *  @brief      Resize event.
     *  @details    This function is called whenever the widget is resized.
     *  @param[in]  e  Object with the information of the event.    
     */
    void resizeEvent(QResizeEvent* e) override;

    /**
     *  @brief      Close event.
     *  @details    This function is called whenever the widget is closed.
     *  @param[in]  e  Object that contains the information of the event.
     */
    void closeEvent(QCloseEvent* e) override;

protected slots:

    ////////// Slots //////////

    /**
     *  @brief      Save image.
     *  @details    This function saves in one image file the current plot.
     */
    void saveImage();

    /**
     *  @brief      Copy to clipboard.
     *  @details    This function copies the plot to the clipboard.
     */
    void toClipboard();

protected:

    ////////// Data members //////////            

    std::shared_ptr<void> ui_;                              /**< User interface. */

    std::shared_ptr<plots::PlotScene> scene_;               /**< Plot scene. */

    ResizePolicy resizePolicy_ {ResizePolicy::Ignore};      /**< Resize policy. */
};

}}

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
