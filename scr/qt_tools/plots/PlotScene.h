//=================================================================================================================
/**
 *  @file       PlotScene.h
 *  @brief      qt_tools::plots::PlotScene class.
 *  @details    Declaration of the qt_tools::plots::PlotScene class. 
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

#ifndef QT_TOOLS_PLOT_SCENE_H_INCLUDE
#define QT_TOOLS_PLOT_SCENE_H_INCLUDE

//=================================================================================================================
//        HEADERS 
//=================================================================================================================
#include <qt_tools/qt_tools.h>
#include <nct/nct_exception.h>
#include <nct/color/ColorPalette.h>
#include <qt_tools/QtConfig.h>

#include <QtGui/QtGui>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtGui/QImage>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsSceneMouseEvent>

//=================================================================================================================
namespace qt_tools {
/**
 *  @brief      Plots and charts namespace.
 *  @details    This namespace contains classes and functions for 1-D and 2-D data charts.
 */
namespace plots {

////////// Enumerations //////////    

/**
 *  @brief      Vertical axis position.
 *  @details    The different positions of the vertical axis.
 */
enum class VerticalAxisPosition : unsigned char {

    Left,                /**< Left side. */

    Right,               /**< Right side. */
};

/**
 *  @brief      Horizontal axis position.
 *  @details    The different positions of the horizontal axis.
 */
enum class HorizontalAxisPosition : unsigned char {

    Top,                /**< Top side. */

    Bottom,             /**< Bottom side. */
};

/**
 *  @brief      Colorbar position.
 *  @details    The different positions of the colorbar.
 */
enum class ColorbarPosition : unsigned char {

    Hidden,             /**< Hidden. */

    Top,                /**< Top side. */

    Bottom,             /**< Bottom side. */

    Left,               /**< Left side. */

    Right,              /**< Right side. */
};

/**
 *  @brief      Legend box position.
 *  @details    The different positions of the legend box.
 */
enum class LegendBoxPosition : unsigned char {

    Hidden,             /**< Hidden item. */

    Top,                /**< Top side. */

    Bottom,             /**< Bottom side. */

    Left,               /**< Left side. */

    Right,              /**< Right side. */

    TopLeftCorner,      /**< Top left corner. */

    TopRightCorner,     /**< Top right corner. */

    BottomLeftCorner,   /**< Bottom left corner. */

    BottomRightCorner,  /**< Bottom right corner. */

};

////////// Structures //////////                

/**
 *  @brief      Chart margins.
 *  @details    This structure defines the margins of a plotting area.
 */
struct Margins final {

    double l {0};    /**< Left margin. */

    double r {0};    /**< Right margin */

    double t {0};    /**< Top margin. */

    double b {0};    /**< Botton margin. */
};

/**
 *  @brief      Axis properties.
 *  @details    This structure defines the properties of an axis.
 */
struct Axis final {

    bool adjustRange = false;   /**< True indicates the axis is adjusted according to the data. */

    double m {0};       /**< The slope that is used to transform one point to a coordinate value. */

    double a {0};       /**< the intercept that is used to transform one point to a coordinate value. */

    double p1 {0};      /**< Extreme value of the axis in the plotting area (left or bottom side). */

    double p2 {0};      /**< Extreme value of the axis in the plotting area (right or top side). */

    QPen pen;           /**< The pen that draws the elements of the axis. */

    QPen gridPen;       /**< The pen that draws the grid. */

    QString name;       /**< Axis name. */

    QColor nameColor;   /**< The color of the axis name label. */

    QFont nameFont;     /**< The font of the axis name label. */

    QColor labelColor;  /**< The color of the labels. */

    QFont labelFont;    /**< The font of the labels. */

    QList<double> marks;    /**< Mark positions. */

    QList<std::pair<double, QString>> labels;   /**< The list of labels (and their positions). */
};

/**
 *  @brief      Colorbar properties.
 *  @details    This structure defines the properties of a colorbar.
 */
struct Colorbar final {

    bool adjustRange {false};   /**< True indicates the colorbar is adjusted according to the data. */

    double p1 {0};      /**< Extreme value of the colorbar (left or bottom side). */

    double p2 {0};      /**< Extreme value of the colorbar (right or top side). */

    double width {0};   /**< The width of the colorbar. */

    QPen pen;           /**< The pen that draws the elements of the colorbar. */

    QString name;       /**< The name of the color bar. */

    QColor nameColor;   /**< The color of the name text. */

    QFont nameFont;     /**< The font of the name text. */

    QColor labelColor;  /**< The color of the labels. */

    QFont labelFont;    /**< The font of the labels. */

    QList<double> marks;    /**< Mark positions. */

    QList<std::pair<double, QString>> labels;   /**< The list of labels (and their positions). */

    QList<QColor> palette;  /**< The color palette (color map). */
};

/**
 *  @brief      Text section.
 *  @details    This structure defines the properties of one text section
 *              of a plot.
 */
struct TextSection final {

    QString text;       /**< The text to display in the section. */

    QFont font;         /**< The font of the section text. */

    QColor color;       /**< The color of the section text. */

    QPen framePen;      /**< The pen that draws the section frame. */

    QBrush frameBrush;  /**< The brush that fills the section frame. */
};

/**
 *  @brief      Plotting area.
 *  @details    This structure defines the properties of the plotting area.
 */
struct PlottingArea final {

    QPen framePen;              /**< The pen that draws the plotting area frame. */

    QBrush backgroundBrush;     /**< The brush that fills the plotting area background. */
};

/**
 *  @brief      Legend box item.
 *  @details    This structure defines one item into the legend box.
 */
struct LegendBoxItem final {

    QColor color;           /**< The color that represents the item. */

    QString text;           /**< The text that represents the item. */

    QString description;    /**< The description of the item. */
};

/**
 *  @brief      Legend box item.
 *  @details    This structure defines the properties of a legend box.
 */
struct LegendBox final {

    QString text;       /**< The main text of the legend box. */

    QFont font;         /**< The font of the main text. */

    QColor color;       /**< The color of the main text. */

    QPen framePen;      /**< The pen that draws the frame. */

    QBrush frameBrush;  /**< The brush that fills the area of the frame. */

    QList<LegendBoxItem> items;    /**< The list of items. */
};

/**
 *  @brief      Plot base scene.
 *  @details    Base class for plotting objects.
 *              The PlotScene class provides a custom scene that manages QGraphicsItems.
 *              It allows adding basic forms to the scene using mouse events.
 */
class QT_TOOLS_EXPIMP PlotScene : public QGraphicsScene {
    Q_OBJECT
public:

    ////////// Enumerations //////////        

    /**
     *  @brief      Scene operation mode.
     *  @details    Different modes how the scene operates.
     */
    enum class SelectionMode : unsigned char {

        Locked,             /**< The scene is locked and it is not possible to select or insert items. */

        ItemSelection,      /**< The scene is ready to allow the selection of one item. */

        ItemInsertion,      /**< The scene is ready to allow the rectangular selection of graphical items. */

        OneItemInsertion,   /**< The scene is ready to allow the insertion of one item. */
    };

    /**
     *  @brief      Graphics items.
     *  @details    This enumeration defines the items that can be added to the scene with the mouse.
     */
    enum class GraphicsItem : unsigned char {

        Point,          /**< Point. */

        Mark,           /**< Mark. */

        CompleteMark,   /**< Complete mark. */

        HorizontalLine, /**< Horizontal line. */

        VerticalLine,   /**< Vertical line. */

        Line,           /**< Line. */

        Segment,        /**< Segment. */

        Arrow,          /**< Arrow. */

        CenteredLine,   /**< Centered line. */

        CenteredCircle, /**< Centered circle. */

        Rectangle,      /**< Rectangle. */

        Ellipse,        /**< Ellipse. */

        FilledRectangle,/**< Filled rectangle. */

        FilledEllipse,  /**< Filled ellipse. */

        Text,           /**< Text. */
    };

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes the widget with the specified scene.
     *  @param[in]  scene  Scene to be added to the view port.
     *  @param[in]  parent  Parent object.
     */
    PlotScene(QObject* parent = nullptr);
    
    /**
     *  @brief      Copy constructor.
     *  @details    This constructor is deleted.
     */
    PlotScene(const PlotScene&) = delete;
    
    /**
     *  @brief      Move constructor.
     *  @details    This constructor is deleted.
     */
    PlotScene(PlotScene&&) = delete;

    ////////// Destructor //////////

    /**
     *  @brief      Destructor.
     *  @details    Class destructor. 
     */
    ~PlotScene();

    ////////// Operators //////////
    
    /**
     *  @brief      Assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    PlotScene& operator=(const PlotScene&) = delete;
    
    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    PlotScene& operator=(PlotScene&&) = delete;

    ////////// Member functions //////////

    /**
     *  @brief      Operation mode.
     *  @details    This function returns the operation mode of the scene.
     *  @returns    The current operation mode.
     */
    SelectionMode operationMode() const noexcept;

    /**
     *  @brief      Set operation mode.
     *  @details    This function modifies the operation mode of the scene.
     *  @param [in]  selectionMode  The new operation mode.
     */
    void setOperationMode(SelectionMode selectionMode);

    /**
     *  @brief      Item count.
     *  @details    This function indicates the number of graphics items added to the scene.
     *  @returns    The number of graphics items.
     */
    unsigned int graphicsItemCount() const noexcept;

    /**
     *  @brief      Graphics item.
     *  @details    This function returns the specified graphics item.
     *  @param[in]  index  The item index.
     *  @returns    The specified of graphics items.
     */
    const QGraphicsItem* graphicsItem(int index) const;

    /**
     *  @brief      Remove item.
     *  @details    This function removes and deletes one graphics item from the scene.
     *  @param[in]  index  Item index.
     */
    void removeItem(int index);

    /**
     *  @brief      Remove item.
     *  @details    This function removes and deletes one item from the scene. If the
     *              item is one of the graphics items added previously, this function
     *              deletes it.
     *  @param[in]  index  Graphics item.
     */
    void removeItem(QGraphicsItem* item);

    /**
     *  @brief      Graphics item type.
     *  @details    This function returns the type of item that is being added to the scene.
     *  @returns    The type of new gracphics items.
     */
    GraphicsItem itemType() const noexcept;

    /**
     *  @brief      Set item type.
     *  @details    This function sets the type of the new interactive items.
     *  @param[in]  itemType  Item type.
     */
    void setItemType(GraphicsItem itemType);

    /**
     *  @brief      Are new interactive items selectable?
     *  @details    This function returns wether new items are selectable.
     *  @returns    True if new items are selectable.
     */
    bool itemSelectable() const noexcept;

    /**
     *  @brief      Set item selectable.
     *  @details    This function sets whether the new items are selectable.
     *  @param[in]  select  Selectable flag value.
     */
    void setItemSelectable(bool select = true);

    /**
     *  @brief      Are new interactive items movable?
     *  @details    This function returns wether new items are movable.
     *  @returns    True if new items are movable.
     */
    bool itemMovable() const noexcept;

    /**
     *  @brief      Set item movable.
     *  @details    This function sets whether the new items are movable.
     *  @param[in]  select  Movable flag value.
     */
    void setItemMovable(bool mov = true);

    /**
     *  @brief      Item Z-Value.
     *  @details    This function returns the Z-value of the new items.
     *  @returns    The item z-value.
     */
    double itemZValue() const noexcept;

    /**
     *  @brief      Set item Z-Value.
     *  @details    This function modifies the Z-value of the new items.
     *  @param[in]  z  The new z-value.
     */
    void setItemZValue(double z);

    /**
     *  @brief      Item size.
     *  @details    This function returns the size of the new items.
     *  @returns    The item size.
     */
    double itemSize() const noexcept;

    /**
     *  @brief      Set item size.
     *  @details    This function sets the size of the new items.
     *  @param[in]  w  The new item size.
     */
    void setItemSize(double s);

    /**
     *  @brief      Item pen.
     *  @details    This function returns the pen of new items.
     *  @returns    The item pen.
     */
    const QPen& itemPen() const noexcept;

    /**
     *  @brief      Set item pen.
     *  @details    This function sets the pen that is used to draw new items.
     *  @param[in]  p  The new item pen.
     */
    void setItemPen(const QPen& p);

    /**
     *  @brief      Item brush.
     *  @details    This function returns the brush of new items.
     *  @returns    The item brush.
     */
    const QBrush& itemBrush() const noexcept;

    /**
     *  @brief      Set item brush.
     *  @details    This function sets the pen that is used to fill new items.
     *  @param[in]  b  The new item brush.
     */
    void setItemBrush(const QBrush& b);

    /**
     *  @brief      Item font.
     *  @details    This function returns the font of new items.
     *  @returns    The item font.
     */
    const QFont& itemFont() const noexcept;

    /**
     *  @brief      Set item font.
     *  @details    This function sets the font that is used to define new text items.
     *  @param[in]  f  The new item font.
     */
    void setItemFont(const QFont& f);
    
    /**
     *  @brief      Item text.
     *  @details    This function returns the text of new items.
     *  @returns    The item text.
     */
    const QString& itemText() const noexcept;

    /**
     *  @brief      Set item text.
     *  @details    This function sets the text that is used to define new items.
     *  @param[in]  t  The new item text.
     */
    void setItemText(const QString& t);

    /**
     *  @brief      Item preview pen.
     *  @details    This function returns the pen of the preview of new items.
     *  @returns    The preview pen.
     */
    const QPen& previewPen() const noexcept;

    /**
     *  @brief      Set preview pen.
     *  @details    This function sets the pen that is used to draw the preview of new items.
     *  @param[in]  p  The new preview pen.
     */
    void setPreviewPen(const QPen& p);

    /**
     *  @brief      Interactive rectangle.
     *  @details    This function returns the area into the scene where new items
     *              can be added.
     *  @returns    The interactive rect.
     */
    const QRectF& plottingAreaRect() const noexcept;

    /**
     *  @brief      To image.
     *  @details    This function draws the scene in an image.
     *  @returns    The image with the current scene.
     */
    QImage toImage();

    /**
     *  @brief      Labels of range.
     *  @details    This function generates the labels that corresponds to n divisions of the
     *              specified range.
     *  @param[in]  min  Minimum value of the range.
     *  @param[in]  max  Maximum value of the range.
     *  @param[in]  nLabels  Number of labels.
     *  @param[in]  prec  Precision.
     *  @returns    An array that indicates the labels and their corresponding positions into the range.
     */
    static QList<std::pair<double, QString>> labels(
        double min, double max, unsigned int nLabels, unsigned int prec = 4);

    /**
     *  @brief      Color palette.
     *  @details    This function returns the palette that corresponds to the given name.
     *  @param[in]  palette  Color palette name.
     *  @param[in]  size  Size of the palette.
     *  @returns    The container that represents the color palette.
     */
    static QList<QColor> colorPalette(nct::color::ColorPalette::ColorPaletteName palette,
        unsigned int size = 256);

    /**
     *  @brief      Draw color palette.
     *  @details    This function creates an image with the specified color palette.
     *  @param[in]  palette  Color palette to draw.
     *  @param[in]  w  Width in pixels of the output image.
     *  @param[in]  vertical  True to draw the palette vertically.
     *  @param[in]  reverse  True to read the palette in reverse order.
     *  @returns    The image with the palette.
     */
    static QImage drawPalette(const QList<QColor>& palette, unsigned int w,
        bool vertical = true, bool reverse = false);

    /**
     *  @brief      Add a point to the scene.
     *  @details    This function adds one point in the scene. The new item can be deleted by 
     *              selecting it and calling the clearSelectedItems() method.
     *  @param[in]  x  The x coordinate where the new item will be inserted.
     *  @param[in]  y  The y coordinate where the new item will be inserted.
     *  @param[in]  pointWidth  Width of the point.
     *  @param[in]  p  Pen that is used to draw the element.
     *  @returns    The new item that was added to the scene.
     */
    QGraphicsItem* addPoint(double x, double y, double pointWidth, const QPen& p);

    /**
     *  @brief      Add a mark to the scene.
     *  @details    This function adds one mark in the scene. The new item can be deleted by 
     *              selecting it and calling the clearSelectedItems() method.
     *  @param[in]  x  The x coordinate where the new item will be inserted.
     *  @param[in]  y  The y coordinate where the new item will be inserted.
     *  @param[in]  lineLength  Length of the line of the new item.
     *  @param[in]  p  Pen that is used to draw the element.
     *  @returns    The new item that was added to the scene.
     */
    QGraphicsItem* addMark(double x, double y, double lineLength, const QPen& p);

    /**
     *  @brief      Add a complete mark to the scene.
     *  @details    This function adds one complete mark in the scene. The new item can be deleted
     *              by selecting it and calling the clearSelectedItems() method.
     *  @param[in]  x  The x coordinate where the new item will be inserted.
     *  @param[in]  y  The y coordinate where the new item will be inserted.
     *  @param[in]  p  Pen that is used to draw the element.
     *  @returns    The new item that was added to the scene.
     */
    QGraphicsItem* addCompleteMark(double x, double y, const QPen& p);

    /**
     *  @brief      Add a vertical line to the scene.
     *  @details    This function adds one vertical line in the scene. The new item can be deleted
     *              by selecting it and calling the clearSelectedItems() method.
     *  @param[in]  x  The x coordinate where the new item will be inserted.
     *  @param[in]  p  Pen that is used to draw the element.
     *  @param[in]  solidLine  True to draw a solid line, otherwise a dashed lines are drawn instead.
     *  @returns    The new item that was added to the scene.
     */
    QGraphicsItem* addVerticalLine(double x, const QPen& p);

    /**
     *  @brief      Add a horizontal line to the scene.
     *  @details    This function adds one horizontal line in the scene. The new item can be
     *              deleted by selecting it and calling the clearSelectedItems() method.
     *  @param[in]  y  The y coordinate where the new item will be inserted.
     *  @param[in]  p  Pen that is used to draw the element.
     *  @param[in]  solidLine  True to draw a solid line, otherwise a dashed lines are drawn instead.
     *  @returns    The new item that was added to the scene.
     */
    QGraphicsItem* addHorizontalLine(double y, const QPen& p);

    /**
     *  @brief      Add a line to the scene.
     *  @details    This function adds one line in the scene. The new item can be deleted by 
     *              selecting it and calling the clearSelectedItems() method.
     *  @param[in]  x1  The x coordinate of the first point of the line.
     *  @param[in]  y1  The y coordinate of the first point of the line.
     *  @param[in]  x2  The x coordinate of the second point of the line.
     *  @param[in]  y2  The y coordinate of the second point of the line.
     *  @param[in]  p  Pen that is used to draw the element.
     *  @returns    The new item that was added to the scene.
     */
    QGraphicsItem* addLine(double x1, double y1, double x2, double y2,
        const QPen& p);

    /**
     *  @brief      Add a segment to the scene.
     *  @details    This function adds one segment in the scene. The new item can be deleted by 
     *              selecting it and calling the clearSelectedItems() method.
     *  @param[in]  x1  The x coordinate of the first point of the line.
     *  @param[in]  y1  The y coordinate of the first point of the line.
     *  @param[in]  x2  The x coordinate of the second point of the line.
     *  @param[in]  y2  The y coordinate of the second point of the line.
     *  @param[in]  endLength  Length of the end of the segment.
     *  @param[in]  p  Pen that is used to draw the element.
     *  @returns    The new item that was added to the scene.
     */
    QGraphicsItem* addSegment(double x1, double y1, double x2, double y2,
        double endLength, const QPen& p);

    /**
     *  @brief      Add an arrow to the scene.
     *  @details    This function adds one arrow in the scene. The new item can be deleted by 
     *              selecting it and calling the clearSelectedItems() method.
     *  @param[in]  x1  The x coordinate of the first point of the line.
     *  @param[in]  y1  The y coordinate of the first point of the line.
     *  @param[in]  x2  The x coordinate of the second point of the line.
     *  @param[in]  y2  The y coordinate of the second point of the line.
     *  @param[in]  endLength  Length of the end of the arrow.
     *  @param[in]  p  Pen that is used to draw the element.
     *  @returns    The new item that was added to the scene.
     */
    QGraphicsItem* addArrow(double x1, double y1, double x2, double y2,
        double endLength, const QPen& p);

    /**
     *  @brief      Add a centered line to the scene.
     *  @details    This function adds one centered line in the scene. The line is formed by the 
     *              center of the scene and the specified point. The new item can be deleted by 
     *              selecting it and calling the clearSelectedItems() method.
     *  @param[in]  x  The x coordinate of the end point of the line.
     *  @param[in]  y  The y coordinate of the end point of the line.
     *  @param[in]  p  Pen that is used to draw the element.
     *  @param[in]  solidLine  True to draw a solid line, otherwise a dashed lines are 
     *              drawn instead.
     *  @returns    The new item that was added to the scene.
     */
    QGraphicsItem* addCenteredLine(double x, double y, const QPen& p);

    /**
     *  @brief      Add a centered circle to the scene.
     *  @details    This function adds one centered circle that passes through the specified point. 
     *              The new item can be deleted by selecting it and calling the 
     *              clearSelectedItems() method.
     *  @param[in]  x  The x coordinate of the end point.
     *  @param[in]  y  The y coordinate of the end point.
     *  @param[in]  p  Pen that is used to draw the element.
     *  @returns    The new item that was added to the scene.
     */
    QGraphicsItem* addCenteredCircle(double x, double y, const QPen& p);

    /**
     *  @brief      Add a centered circle to the scene.
     *  @details    This function adds one centered circle in the scene. The new item can be
     *              deleted by selecting it and calling the clearSelectedItems() method.
     *  @param[in]  r  The radius of the circle.
     *  @param[in]  p  Pen that is used to draw the element.
     *  @returns    The new item that was added to the scene.
     */
    QGraphicsItem* addCenteredCircle(double r, const QPen& p);

    /**
     *  @brief      Add a rectangle to the scene.
     *  @details    This function adds one rectangle in the scene. The new item can be deleted by 
     *              selecting it and calling the clearSelectedItems() method.
     *  @param[in]  x  The x coordinate where the new item will be inserted.
     *  @param[in]  y  The y coordinate where the new item will be inserted.
     *  @param[in]  w  The width of the new item.
     *  @param[in]  h  The height of the new item.
     *  @param[in]  p  Pen that is used to draw the element.
     *  @returns    The new item that was added to the scene.
     */
    QGraphicsItem* addRectangle(double x, double y, double w, double h, const QPen& p);

    /**
     *  @brief      Add an ellipse to the scene.
     *  @details    This function adds one ellipse in the scene. The new item can be deleted by 
     *              selecting it and calling the clearSelectedItems() method.
     *  @param[in]  x  The x coordinate where the new item will be inserted.
     *  @param[in]  y  The y coordinate where the new item will be inserted.
     *  @param[in]  w  The width of the new item.
     *  @param[in]  h  The height of the new item.
     *  @param[in]  p  Pen that is used to draw the element.
     *  @returns    The new item that was added to the scene.
     */
    QGraphicsItem* addEllipse(double x, double y, double w, double h, const QPen& p);

    /**
     *  @brief      Add a filled rectangle to the scene.
     *  @details    This function adds one filled rectangle in the scene. The new item can be
     *              deleted by selecting it and calling the clearSelectedItems() method.
     *  @param[in]  x  The x coordinate where the new item will be inserted.
     *  @param[in]  y  The y coordinate where the new item will be inserted.
     *  @param[in]  w  The width of the new item.
     *  @param[in]  h  The height of the new item.
     *  @param[in]  b  Brush that is used to fill the shape.
     *  @param[in]  p  Pen that defines the shape. 
     *  @returns    The new item that was added to the scene.
     */
    QGraphicsItem* addFilledRectangle(double x, double y, double w,
        double h, const QBrush& b, const QPen& p);

    /**
     *  @brief      Add a filled ellipse to the scene.
     *  @details    This function adds one filled ellipse in the scene. The new item can be
     *              deleted by selecting it and calling the clearSelectedItems() method.
     *  @param[in]  x  The x coordinate where the new item will be inserted.
     *  @param[in]  y  The y coordinate where the new item will be inserted.
     *  @param[in]  w  The width of the new item.
     *  @param[in]  h  The height of the new item.
     *  @param[in]  b  Brush that is used to fill the shape.
     *  @param[in]  p  Pen that defines the shape.
     *  @returns    The new item that was added to the scene.
     */
    QGraphicsItem* addFilledEllipse(double x, double y, double w,
        double h, const QBrush& b, const QPen& p);

    /**
     *  @brief      Add a text to the scene.
     *  @details    This function adds text in the scene. The new item can be deleted by 
     *              selecting it and calling the clearSelectedItems() method.
     *  @param[in]  x  The x coordinate where the new item will be inserted.
     *  @param[in]  y  The y coordinate where the new item will be inserted.
     *  @param[in]  text  String of the text to be added.
     *  @param[in]  font  Font of the new item.
     *  @param[in]  color Text color.
     *  @returns    The new item that was added to the scene.
     */
    QGraphicsItem* addText(double x, double y, QString& text,
        const QFont& font, const QColor& color);

    /**
     *  @brief      Add scaled image.
     *  @details    This function scales an image and adds it to the plotting area.
     *  @param[in]  img  The image to add to the plotting area.
     *  @returns    The object added to the scene.
     */
    QGraphicsPixmapItem* addImage(const QImage& img);

public slots:

    ////////// Slots //////////

    /**
     *  @brief      Clear scene.
     *  @details    This function clears the complete scene.
     */
    virtual void clear();

    /**
     *  @brief      Set plot size.
     *  @details    This function sets the size of the plot scene.
     *  @param[in]  w  The width of the rectangle that defines the plot.
     *  @param[in]  h  The height of the rectangle that defines the plot.
     */
    virtual void setSize(unsigned int w = 800, unsigned int h = 600);

    /**
     *  @brief      Draw plot.
     *  @details    This function updates the interface to render all the elements of the plot.
     */
    virtual void drawPlot();

    /**
     *  @brief      Lock scene.
     *  @details    This function locks the scene.
     */
    void lockScene();

    /**
     *  @brief      Selection on.
     *  @details    This function enables the selection of items.
     */
    void setSelectionOn();

    /**
     *  @brief      Insertion on.
     *  @details    This function enables the insertion of items.
     */
    void setInsertionOn();

    /**
     *  @brief      Unitary insertion on.
     *  @details    This function enables the unitary insertion of items.
     */
    void setUnitaryInsertionOn();

    /**
     *  @brief      Clear interactive items.
     *  @details    This function clears the interactive items of the scene.
     */
    void clearInteractiveItems();

    /**
     *  @brief      Clear selected items.
     *  @details    This function clears all the selected items of the scene.
     */
    void clearSelectedItems();

signals:

    ////////// Signals //////////

    /**
     *  @brief      Mouse pressed.
     *  @details    This signal is produced whenever the left button of the mouse is pressed 
     *              into the ROI area.
     *  @param[in]  x  X position of the cursor in the scene.
     *  @param[in]  y  Y position of the cursor in the scene.
     */
    void mousePressed(double x, double y);

    /**
     *  @brief      Mouse moved.
     *  @details    This signal is produced whenever the position of the mouse pointer changed
     *              into the ROI area.
     *  @param[in]  x  X position of the cursor in the scene.
     *  @param[in]  y  Y position of the cursor in the scene.
     */
    void mouseMoved(double x, double y);

    /**
     *  @brief      Mouse released.
     *  @details    This signal is produced whenever the left button of the mouse is released 
     *              into the ROI area.
     *  @param[in]  x  X position of the cursor in the scene.
     *  @param[in]  y  Y position of the cursor in the scene.
     */
    void mouseReleased(double x, double y);

    /**
     *  @brief      Scene cleared.
     *  @details    This signal is produced whenever the scene has been cleared.
     */
    void sceneCleared();

    /**
     *  @brief      Interactive items cleared.
     *  @details    This signal is produced whenever the interactive items have been cleared.
     */
    void interactiveItemsCleared();

    /**
     *  @brief      New item rect.
     *  @details    This signal is produced whenever the rectangular area where the items can be
     *              added has been changed.
     *  @param[in]  rect  The new item rect.
     */
    void plottingAreaRectChanged(const QRectF& rect);

protected:

    ////////// Member functions //////////

    /**
     *  @brief      Set interactive rectangle.
     *  @details    This function modifies the area into the scene where new items
     *              can be added.
     *  @param[in]  x  x position of the new rectangle.
     *  @param[in]  y  y position of the new rectangle.
     *  @param[in]  w  The width of the new rectangle.
     *  @param[in]  h  The height of the new rectangle.
     */
    void setPlottingAreaRect(double x, double y, double w, double h);

    /**
     *  @brief      Set interactive rectangle.
     *  @details    This function modifies the area into the scene where new items
     *              can be added.
     *  @param[in]  rect  The new rectangle area.
     */
    void setPlottingAreaRect(const QRectF& rect);

    /**
     *  @brief      Key-press event.
     *  @details    This function is called whenever the keybord is pressed and the widget has the
     *              focus in the application.
     *  @param[in]  e  Object with the information of the event.            
     */
    void keyPressEvent(QKeyEvent* e) override;

    /**
     *  @brief      Key-release event.
     *  @details    This function is called whenever the keybord is released and the widget has
     *              the focus in the application.
     *  @param[in]  e  Object with the information of the event.            
     */
    void keyReleaseEvent(QKeyEvent * e) override;

    /**
     *  @brief      Mouse-press event.
     *  @details    This function is called whenever the mouse is pressed over the scene.
     *  @param[in]  e  Object with the information of the event.            
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent* e) override;

    /**
     *  @brief      Mouse-move event.
     *  @details    This function is called whenever the mouse is moved over the scene.
     *  @param[in]  e  Object with the information of the event.            
     */
    void mousePressEvent(QGraphicsSceneMouseEvent* e) override;

    /**
     *  @brief      Mouse-press event.
     *  @details    This function is called whenever a button of the mouse is released and the
     *              mouse pointer is over the scene.
     *  @param[in]  e  Object with the information of the event.            
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* e) override;

protected:

    ////////// Data members //////////

    QRectF roi;     /**< The area where the graphical items can be added. */

private:

    ////////// Data members //////////

    SelectionMode selectionMode_ {SelectionMode::Locked};   /**< The selection mode. */

    double mx_ {0};                             /**< X coordinate where the mouse was pressed. */

    double my_ {0};                             /**< Y coordinate where the mouse was pressed. */

    bool mousePressed_ {false};                 /**< True indicates that the mouse was pressed. */

    QGraphicsItem* previewItem_ {nullptr};      /**< The item that represents the preview of a graphics items. */

    QPen previewPen_;                   /**< The pen used to draw the preview item. */

    QList<QGraphicsItem*> items_;       /**< The list of added items. */

    GraphicsItem itemType_ {GraphicsItem::Point};   /**< The item type that can be added to the scene. */

    bool itemSelectable_ {true};        /**< The flag that indicates if new items are selectable. */

    bool itemMovable_ {false};          /**< The flag that indicates if new items are movable. */

    double itemZValue_ {200};           /**< The Z-Value of the new items to be added. */

    double itemSize_ {5};               /**< The size of the new items to be added. */

    QPen itemPen_;                      /**< The pen that will be used to draw new items. */

    QBrush itemBrush_;                  /**< The brush that will be used to draw new items. */

    QFont itemFont_;                    /**< The font of new text items. */

    QString itemText_ {"text"};         /**< The string of the new items. */

};

}}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
