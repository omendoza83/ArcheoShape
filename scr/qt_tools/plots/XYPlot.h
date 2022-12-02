//=================================================================================================================
/**
 *  @file       XYPlot.h
 *  @brief      qt_tools::plots::XYPlot class.
 *  @details    Declaration of the qt_tools::plots::XYPlot class.   
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

#ifndef QT_TOOLS_XY_PLOT_H_INCLUDE
#define QT_TOOLS_XY_PLOT_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <qt_tools/qt_tools.h>
#include <nct/nct_exception.h>
#include <qt_tools/plots/PlotScene.h>

//=================================================================================================================
namespace qt_tools {
namespace plots {

/**
 *  @brief      X-Y plot base class.
 *  @details    Base class for X-Y plots.
 */
class QT_TOOLS_EXPIMP XYPlot : public PlotScene {
    Q_OBJECT

public:

    ////////// Constructors //////////
    
    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes the scene. 
     *  @param[in]  parent  Parent object.
     */
    XYPlot(QObject* parent = 0);
    
    /**
     *  @brief      Copy constructor.
     *  @details    This constructor is deleted.
     */
    XYPlot(const XYPlot&) = delete;
    
    /**
     *  @brief      Move constructor.
     *  @details    This constructor is deleted.
     */
    XYPlot(XYPlot&&) = delete;
    
    ////////// Destructor //////////

    /**
     *  @brief      Destructor.
     *  @details    Class destructor. 
     */
    ~XYPlot() = default;

    ////////// Operators //////////
    
    /**
     *  @brief      Assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    XYPlot& operator=(const XYPlot&) = delete;
    
    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    XYPlot& operator=(XYPlot&&) = delete;

    ////////// Member functions //////////                

    /**
     *  @brief      Is the scene ready?
     *  @details    This function returns whether the scene is ready with all the graphical elements.
     *  @returns    True if the scene is ready.
     */
    bool isReady() const noexcept;

    /**
     *  @brief      Plot background brush.
     *  @details    This function returns the brush that is used to fill the background.
     *  @returns    The background brush.
     */
    const QBrush& plotBackgroundBrush() const noexcept;

    /**
     *  @brief      Set plot background brush.
     *  @details    This function sets the brush to be used to fill the background.
     *  @param[in]  brush  The new background brush.
     */
    void setPlotBackgroundBrush(const QBrush& brush = QColor(255, 255, 255, 255));

    /**
     *  @brief      Margins.
     *  @details    This function returns the margins of the plot.
     *  @returns    The plot margins.
     */
    const Margins& margins() const noexcept;

    /**
     *  @brief      Set margins.
     *  @details    This function modifies the margins of the plot.
     *  @param[in]  left  Left margin.
     *  @param[in]  right  Right margin.
     *  @param[in]  top  top margin.
     *  @param[in]  botton  botton margin.
     */
    void setMargins(double left = 5, double right = 5,
        double top = 5, double botton = 5) noexcept;

    /**
     *  @brief      Title properties.
     *  @details    This function returns the properties of the title section.
     *  @returns    The title properties.
     */
    const TextSection& titleProperties() const noexcept;

    /**
     *  @brief      Set title properties.
     *  @details    This function modifies the properties of the title section.
     *  @param[in]  font  Font of the text elements.
     *  @param[in]  color  Color of the text elements.
     *  @param[in]  framePen  Pen that is used to draw the frame of the section.
     *  @param[in]  framebrush  Brush that is used to fill the frame of the section.
     */
    void setTitleProperties(
        const QFont& font = QFont(QtConfig::instance().defaultFontName(), 
        QtConfig::instance().defaultBigPlotFontSize(), QFont::Bold),
        const QColor& color = QColor(0, 0, 0),
        const QPen& framePen = QPen(Qt::PenStyle::NoPen),
        const QBrush& framebrush = QBrush(Qt::BrushStyle::NoBrush));

    /**
     *  @brief      Set title.
     *  @details    This function modifies the title of the plot.
     *  @param[in]  title  The new title.
     */
    void setTitle(const QString& title = "");

    /**
     *  @brief      Plotting area properties.
     *  @details    This function returns the properties of the plotting area.
     *  @returns    The plotting area properties.
     */
    const PlottingArea& plottingAreaProperties() const noexcept;

    /**
     *  @brief      Set plotting area properties.
     *  @details    This function modifies the properties of the plotting area.
     *  @param[in]  framePen  Pen that is used to draw the frame of the section.
     *  @param[in]  framebrush  Brush that is used to fill the frame of the section.
     */
    void setPlottingAreaProperties(
        const QPen& framePen = QPen(QColor(60, 60, 60), 2, Qt::PenStyle::SolidLine),
        const QBrush& backgroundBrush = QBrush(QColor(255, 255, 255),
            Qt::BrushStyle::SolidPattern));
        
    /**
     *  @brief      Legend box position.
     *  @details    This function returns the position of the legend box.
     *  @returns    The legend box position.
     */
    LegendBoxPosition legendBoxPosition() const noexcept;
    
    /**
     *  @brief      Set legend box position.
     *  @details    This function modifies the position of the legend box.
     *  @param[in]  pos  The new position.
     */
    void setLegendBoxPosition(LegendBoxPosition pos = LegendBoxPosition::TopRightCorner);

    /**
     *  @brief      Legend box properties.
     *  @details    This function returns the properties of the legend box.
     *  @returns    The legend box properties.
     */
    LegendBox legendBoxProperties() const noexcept;
    
    /**
     *  @brief      Set legend box properties.
     *  @details    This function modifies the properties of the legend box.
     *  @param[in]  font  Font of the text elements.
     *  @param[in]  color  Color of the text elements.
     *  @param[in]  framePen  Pen that is used to draw the frame of the section.
     *  @param[in]  framebrush  Brush that is used to fill the frame of the section.
     */
    void setLegendBoxProperties(
        const QFont& font = QFont(QtConfig::instance().defaultFontName(), 
        QtConfig::instance().defaultSmallPlotFontSize(), QFont::Normal),
        const QColor& color = QColor(0, 0, 0),
        const QPen& framePen = QPen(QColor(0, 0, 0), 2, Qt::PenStyle::SolidLine),
        const QBrush& framebrush = QBrush(QColor(255, 255, 255), Qt::BrushStyle::SolidPattern));

    /**
     *  @brief      Set legend box text.
     *  @details    This function modifies the main text of the legend box.
     *  @param[in]  text  The new text of the legend box.
     */
    void setLegendBoxText(const QString& text = "");

    /**
     *  @brief      Legend box items.
     *  @details    This function returns the current list of items that contains the legend box.
     *  @returns    The legend box items.
     */
    const QList<LegendBoxItem>& legendBoxItems() const noexcept;

    /**
     *  @brief      Clear legend box items.
     *  @details    This function clears the list of items that contains the legend box.
     */
    void clearLegendBoxItems();

    /**
     *  @brief      Add legend box item.
     *  @details    This function adds a new item to the legend box.
     *  @param[in]  item  The new item.
     */
    void addLegendBoxItem(const LegendBoxItem& item);

    /**
     *  @brief      Add legend box item.
     *  @details    This function adds a new item to the legend box.
     *  @param[in]  color  The color that represents the item.
     *  @param[in]  text  The text that represents the item.
     *  @param[in]  description  The description of the new item.
     */
    void addLegendBoxItem(const QColor& color, const QString& text,
        const QString& description);

    /**
     *  @brief      x-axis position.
     *  @details    This function returns the position of thex-axis.
     *  @returns    The x-axis position.
     */
    HorizontalAxisPosition xAxisPosition() const noexcept;

    /**
     *  @brief      Set x-axis position.
     *  @details    This function modifies the position of the y-axis.
     *  @param[in]  pos  The new position.
     */
    void setXAxisPosition(HorizontalAxisPosition pos = HorizontalAxisPosition::Bottom);

    /**
     *  @brief      x-axis properties.
     *  @details    This function returns the properties of the x-axis.
     *  @returns    The x-axis properties.
     */
    const Axis& xAxisProperties() const noexcept;

    /**
     *  @brief      Set x-axis properties.
     *  @details    This function modifies the properties of the x-axis.
     *  @param[in]  nameFont  Font of the axis' name.
     *  @param[in]  nameColor  Color of the axis' name.
     *  @param[in]  labelFont  Font of the labels.
     *  @param[in]  labelColor  Color of the labels.
     *  @param[in]  pen  Pen that is used to draw all the graphical elements.
     *  @param[in]  gridPen  Pen that is used to draw the grid.
     */
    void setXAxisProperties(
        const QFont& nameFont = QFont(QtConfig::instance().defaultFontName(), 
        QtConfig::instance().defaultPlotFontSize(), QFont::Bold),
        const QColor& nameColor = QColor(0, 0, 0),
        const QFont& labelFont = QFont(QtConfig::instance().defaultFontName(), 
        QtConfig::instance().defaultSmallPlotFontSize(), QFont::Normal),
        const QColor& labelColor = QColor(0, 0, 0),
        const QPen& pen = QPen(QColor(0, 0, 0), 2, Qt::PenStyle::SolidLine),
        const QPen& gridPen = QPen(QColor(120, 120, 120), 2, Qt::PenStyle::DashLine));

    /**
     *  @brief      Set x-axis name.
     *  @details    This function modifies the name of the x-axis.
     *  @param[in]  name  The name of the axis.
     */
    void setXAxisName(const QString& name = "x");

    /**
     *  @brief      Set x-axis auto-adjustment enabled.
     *  @details    This function enables/disables the auto-adjustment property.
     *  @param[in]  enable  True to enable the auto-adjustment property.
     */
    void setXAxisAutoAdjustentEnabled(bool enable = true) noexcept;

    /**
     *  @brief      Set x-axis range.
     *  @details    This function modifies the range of values represented in the axis.
     *  @param[in]  p1  Value represented at the left side of the axis.
     *  @param[in]  p2  Value represented at the right side of the axis.
     */
    void setXAxisRange(double p1, double p2);

    /**
     *  @brief      Set x-axis range.
     *  @details    This function modifies the range of values represented in the axis. It also
     *              adds the labels and marks that corresponds to the range.
     *  @param[in]  p1  Value represented at the left side of the axis.
     *  @param[in]  p2  Value represented at the right side of the axis.
     *  @param[in]  nMarks  Number of marks and labels of the axis.
     */
    void setXAxisRange(double p1, double p2, unsigned int nMarks);

    /**
     *  @brief      x-axis mark.
     *  @details    This function returns the marks of the x-axis.
     *  @returns    The x-axis mark.
     */
    const QList<double>& xAxisMarks() const noexcept;

    /**
     *  @brief      Clear x-axis marks.
     *  @details    This function removes the marks of the x-axis.
     */
    void clearXAxisMarks();

    /**
     *  @brief      Add x-axis mark.
     *  @details    This function adds a new mark to the x-axis.
     *  @param[in]  pos  The position of the new mark.
     */
    void addXAxisMark(double pos);

    /**
     *  @brief      x-axis label.
     *  @details    This function returns the labels of the x-axis.
     *  @returns    The x-axis labels.
     */
    const QList<std::pair<double, QString>>& xAxisLabels() const noexcept;

    /**
     *  @brief      Clear x-axis labels.
     *  @details    This function removes the labels of the x-axis.
     */
    void clearXAxisLabels();

    /**
     *  @brief      Add x-axis label.
     *  @details    This function adds a new label to the x-axis.
     *  @param[in]  pos  The position of the new label.
     *  @param[in]  text  The text of the new label.
     */
    void addXAxisLabel(double pos, const QString& text);

    /**
     *  @brief      Horizontal coordinate.
     *  @details    This function calculates the horizontal coordinate into the scene that corresponds to
     *              the specified point.
     *  @param[in]  x  The point to be converted.
     *  @returns    The value of the coordinate.
     */
    double horizontalCoordinate(double x) const noexcept;

    /**
     *  @brief      x value.
     *  @details    This function calculates the point that corresponds to the specified horizontal
     *              coordinate value into the scene.
     *  @param[in]  p  The coordinate value to be converted.
     *  @returns    The value of the point.
     */
    double xValue(double p) const noexcept;

    /**
     *  @brief      y-axis position.
     *  @details    This function returns the position of the y-axis.
     *  @returns    The y-axis position.
     */
    VerticalAxisPosition yAxisPosition() const noexcept;

    /**
     *  @brief      Set y-axis position.
     *  @details    This function modifies the position of the y-axis.
     *  @param[in]  pos  The new position.
     */
    void setYAxisPosition(VerticalAxisPosition pos = VerticalAxisPosition::Left);

    /**
     *  @brief      y-axis properties.
     *  @details    This function returns the properties of the y-axis.
     *  @returns    The y-axis properties.
     */
    const Axis& yAxisProperties() const noexcept;

    /**
     *  @brief      Set y-Axis properties.
     *  @details    This function modifies the properties of the y-axis.
     *  @param[in]  nameFont  Font of the axis' name.
     *  @param[in]  nameColor  Color of the axis' name.
     *  @param[in]  labelFont  Font of the labels.
     *  @param[in]  labelColor  Color of the labels.
     *  @param[in]  pen  Pen that is used to draw all the graphical elements.
     *  @param[in]  gridPen  Pen that is used to draw the grid.
     */
    void setYAxisProperties(
        const QFont& nameFont = QFont(QtConfig::instance().defaultFontName(), 
        QtConfig::instance().defaultPlotFontSize(), QFont::Bold),
        const QColor& nameColor = QColor(0, 0, 0),
        const QFont& labelFont = QFont(QtConfig::instance().defaultFontName(),
        QtConfig::instance().defaultSmallPlotFontSize(), QFont::Normal),
        const QColor& labelColor = QColor(0, 0, 0),
        const QPen& pen = QPen(QColor(0, 0, 0), 2, Qt::PenStyle::SolidLine),
        const QPen& gridPen = QPen(QColor(120, 120, 120), 2, Qt::PenStyle::DashLine));

    /**
     *  @brief      Set y-axis name.
     *  @details    This function modifies the name of the y-axis.
     *  @param[in]  name  The name of the axis.
     */
    void setYAxisName(const QString& name = "y");

    /**
     *  @brief      Set y-axis auto-adjustment enabled.
     *  @details    This function enables/disables the auto-adjustment property.
     *  @param[in]  enable  True to enable the auto-adjustment property.
     */
    void setYAxisAutoAdjustentEnabled(bool enable = true) noexcept;

    /**
     *  @brief      Set y-axis range.
     *  @details    This function modifies the range of values represented in the axis.
     *  @param[in]  p1  Value represented at the bottom side of the axis.
     *  @param[in]  p2  Value represented at the top side of the axis.
     */
    void setYAxisRange(double p1, double p2);

    /**
     *  @brief      Set y-axis range.
     *  @details    This function modifies the range of values represented in the axis. It also
     *              adds the labels and marks that corresponds to the range.
     *  @param[in]  p1  Value represented at the bottom side of the axis.
     *  @param[in]  p2  Value represented at the top side of the axis.
     *  @param[in]  nMarks  Number of marks and labels of the axis.
     */
    void setYAxisRange(double p1, double p2, unsigned int nMarks);

    /**
     *  @brief      y-axis mark.
     *  @details    This function returns the marks of the y-axis.
     *  @returns    The y-axis mark.
     */
    const QList<double>& yAxisMarks() const noexcept;

    /**
     *  @brief      Clear y-axis marks.
     *  @details    This function removes the marks of the y-axis.
     */
    void clearYAxisMarks();

    /**
     *  @brief      Add y-axis mark.
     *  @details    This function adds a new mark to the y-axis.
     *  @param[in]  pos  The position of the new mark.
     */
    void addYAxisMark(double pos);

    /**
     *  @brief      y-axis label.
     *  @details    This function returns the labels of the y-axis.
     *  @returns    The y-axis labels.
     */
    const QList<std::pair<double, QString>>& yAxisLabels() const noexcept;

    /**
     *  @brief      Clear y-axis labels.
     *  @details    This function removes the labels of the y-axis.
     */
    void clearYAxisLabels();

    /**
     *  @brief      Add y-axis label.
     *  @details    This function adds a new label to the y-axis.
     *  @param[in]  pos  The position of the new label.
     *  @param[in]  text  The text of the new label.
     */
    void addYAxisLabel(double pos, const QString& text);

    /**
     *  @brief      Vertical coordinate.
     *  @details    This function calculates the vertical coordinate into the scene that corresponds to
     *              the specified point.
     *  @param[in]  y  The point to be converted.
     *  @returns    The value of the coordinate.
     */
    double verticalCoordinate(double y) const noexcept;

    /**
     *  @brief      y-value.
     *  @details    This function calculates the point that corresponds to the specified vertical
     *              coordinate into the scene.
     *  @param[in]  y  The coordinate value to be converted.
     *  @returns    The value of the point.
     */
    double yValue(double p) const noexcept;

    /**
     *  @brief      Set plot image.
     *  @details    This function sets the image that is shown in the plotting area.
     *  @param[in]  img  The new image to be shown.     
     */
    void setPlotImage(const QImage& img);

public slots:

    ////////// Slots //////////

    /**
     *  @brief      Set plot size.
     *  @details    This function set the size of the plot.
     *  @param[in]  w  The width of the rectangle that defines the plot.
     *  @param[in]  h  The height of the rectangle that defines the plot.
     */
    void setSize(unsigned int w = 800, unsigned int h = 600) override;

    /**
     *  @brief      Clear scene.
     *  @details    This function clears the scene.
     */
    void clear() override;

    /**
     *  @brief      Draw plot.
     *  @details    This function generates the scene that represents the plot.
     */
    void drawPlot() override;

protected:

    ////////// Data members //////////

    bool ready_ {false};                    /**< True indicates that the scene is ready. */

    QBrush plotBackgroundBrush_;            /**< The brush that is used to fill the background. */

    Margins margins_;                       /**< The margins of the scene. */

    TextSection titleSection_;              /**< The title of the chart. */

    PlottingArea plottingSection_;          /**< The plotting area properties. */

    LegendBox legendBoxSection_;            /**< The legend box properties. */

    LegendBoxPosition legendBoxPosition_ {LegendBoxPosition::Hidden};   /**< The legend box position. */

    Axis xAxis_;                            /**< The X-axis properties. */

    HorizontalAxisPosition xAxisPosition_;  /**< The X-axis position. */

    Axis yAxis_;                            /**< The Y-axis properties. */

    VerticalAxisPosition yAxisPosition_;    /**< The Y-axis position. */

    QImage img_;                            /**< The image that is shown in the plotting area. */
};

}}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================

