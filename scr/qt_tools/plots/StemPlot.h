//=================================================================================================================
/**
 *  @file       StemPlot.h
 *  @brief      qt_tools::plots::StemPlot class.
 *  @details    Declaration of the qt_tools::plots::StemPlot class.   
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

#ifndef QT_TOOLS_STEM_PLOT_H_INCLUDE
#define QT_TOOLS_STEM_PLOT_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <qt_tools/plots/XYPlot.h>
#include <nct/Array.h>

//=================================================================================================================
namespace qt_tools {
namespace plots {

/**
 *  @brief      Stem plot.
 *  @details    This class is used for drawing stem plots. The plot
 *              consists of vertical lines that connect the horizontal axis with the points
 *              located at the specified coordinates.
 */
class QT_TOOLS_EXPIMP StemPlot final : public XYPlot {
    Q_OBJECT

public:

    ////////// Structures //////////    

    /**
     *  @brief      Data properties.
     *  @details    This structure defines the properties of one set of data.
     */
    struct DataProperties final {

        QString name;           /**< Name of the data set. */

        double pointWidth {0};  /**< Width of the lines. */

        QPen pen;               /**< Pen that is used to draw the graphical elements
                                     that represent the data. */
        QBrush brush;           /**< Brush that is used to fill the graphical elements
                                     that represent the data. */
        std::shared_ptr<nct::RealVector> x;     /**< Array with the horizontal values. */

        std::shared_ptr<nct::RealVector> y;     /**< Array with the vertical values. */
    };

    ////////// Constructors //////////
    
    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes the scene. 
     *  @param[in]  parent  Parent object.
     */
    StemPlot(QObject* parent = 0);
    
    /**
     *  @brief      Copy constructor.
     *  @details    This constructor is deleted.
     */
    StemPlot(const StemPlot&) = delete;
    
    /**
     *  @brief      Move constructor.
     *  @details    This constructor is deleted.
     */
    StemPlot(StemPlot&&) = delete;
    
    ////////// Destructor //////////

    /**
     *  @brief      Destructor.
     *  @details    Class destructor. 
     */
    ~StemPlot() = default;

    ////////// Operators //////////
    
    /**
     *  @brief      Assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    StemPlot& operator=(const StemPlot&) = delete;
    
    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    StemPlot& operator=(StemPlot&&) = delete;

    ////////// Member functions //////////

    /**
     *  @brief      Clear data.
     *  @details    This function clears all the data sets.
     */
    void clearData();

    /**
     *  @brief      Add a data set.
     *  @details    This function adds one data set to the plot.
     *  @param[in]  x  The X values of the data set.
     *  @param[in]  y  The Y values of the data set.
     *  @param[in]  name  The name of the data set.
     *  @param[in]  pointWidth  Width of the points that will represent the data set.
     *  @param[in]  pen  Pen that is used to draw the items that represent the data.
     *  @param[in]  brush  Brush that is used to fill the items that represent the data.
     */
    void addDataSet(const nct::RealVector& x,
        const nct::RealVector& y,
        const QString& name = "", double pointWidth = 5.0,
        const QPen& pen = QPen(QColor(10, 25, 120), 2.0, Qt::SolidLine),
        const QBrush& brush = QBrush(QColor(10, 25, 120), Qt::BrushStyle::SolidPattern));

    /**
     *  @brief      Add a data set.
     *  @details    This function adds one data set to the plot.
     *  @param[in]  x  The X values of the data set.
     *  @param[in]  y  The Y values of the data set.
     *  @param[in]  name  The name of the data set.
     *  @param[in]  pointWidth  Width of the points that will represent the data set.
     *  @param[in]  pen  Pen that is used to draw the items that represent the data.
     *  @param[in]  brush  Brush that is used to fill the items that represent the data.
     */
    void addDataSet(nct::RealVector&& x,
        nct::RealVector&& y,
        const QString& name = "", double pointWidth = 5.0,
        const QPen& pen = QPen(QColor(10, 25, 120), 2.0, Qt::SolidLine),
        const QBrush& brush = QBrush(QColor(10, 25, 120), Qt::BrushStyle::SolidPattern));

    /**
     *  @brief      Add a data set.
     *  @details    This function adds one data set to the plot.
     *  @param[in]  x  The X values of the data set.
     *  @param[in]  y  The Y values of the data set.
     *  @param[in]  name  The name of the data set.
     *  @param[in]  pointWidth  Width of the points that will represent the data set.
     *  @param[in]  pen  Pen that is used to draw the items that represent the data.
     *  @param[in]  brush  Brush that is used to fill the items that represent the data.
     */
    void addDataSet(const std::shared_ptr<nct::RealVector>& x,
        const std::shared_ptr<nct::RealVector>& y,
        const QString& name = "", double pointWidth = 5.0,
        const QPen& pen = QPen(QColor(10, 25, 120), 2.0, Qt::SolidLine),
        const QBrush& brush = QBrush(QColor(10, 25, 120), Qt::BrushStyle::SolidPattern));

    /**
     *  @brief      Add a data set.
     *  @details    This function adds one data set to the plot.
     *  @param[in]  y  The Y values of the data set.
     *  @param[in]  name  The name of the data set.
     *  @param[in]  pointWidth  Width of the points that will represent the data set.
     *  @param[in]  pen  Pen that is used to draw the items that represent the data.
     *  @param[in]  brush  Brush that is used to fill the items that represent the data.
     */
    void addDataSet(const nct::RealVector& y,
        const QString& name = "", double pointWidth = 5.0,
        const QPen& pen = QPen(QColor(10, 25, 120), 2.0, Qt::SolidLine),
        const QBrush& brush = QBrush(QColor(10, 25, 120), Qt::BrushStyle::SolidPattern));

    /**
     *  @brief      Add a data set.
     *  @details    This function adds one data set to the plot.
     *  @param[in]  y  The Y values of the data set.
     *  @param[in]  name  The name of the data set.
     *  @param[in]  pointWidth  Width of the points that will represent the data set.
     *  @param[in]  pen  Pen that is used to draw the items that represent the data.
     *  @param[in]  brush  Brush that is used to fill the items that represent the data.
     */
    void addDataSet(nct::RealVector&& y,
        const QString& name = "", double pointWidth = 5.0,
        const QPen& pen = QPen(QColor(10, 25, 120), 2.0, Qt::SolidLine),
        const QBrush& brush = QBrush(QColor(10, 25, 120), Qt::BrushStyle::SolidPattern));

    /**
     *  @brief      Add a data set.
     *  @details    This function adds one data set to the plot.
     *  @param[in]  y  The Y values of the data set.
     *  @param[in]  name  The name of the data set.
     *  @param[in]  pointWidth  Width of the points that will represent the data set.
     *  @param[in]  pen  Pen that is used to draw the items that represent the data.
     *  @param[in]  brush  Brush that is used to fill the items that represent the data.
     */
    void addDataSet(const std::shared_ptr<nct::RealVector>& y,
        const QString& name = "", double pointWidth = 5.0,
        const QPen& pen = QPen(QColor(10, 25, 120), 2.0, Qt::SolidLine),
        const QBrush& brush = QBrush(QColor(10, 25, 120), Qt::BrushStyle::SolidPattern));

    /**
     *  @brief      Config data set.
     *  @details    This function modifies the properties of one data set.
     *  @param[in]  i  Data set index.
     *  @param[in]  name  The name of the data set.
     *  @param[in]  pointWidth  Width of the points that will represent the data set.
     *  @param[in]  pen  Pen that is used to draw the items that represent the data.
     *  @param[in]  brush  Brush that is used to fill the items that represent the data.
     */
    void configDataSet(unsigned int i,
        const QString& name = "", double pointWidth = 5.0,
        const QPen& pen = QPen(QColor(10, 25, 120), 2.0, Qt::SolidLine),
        const QBrush& brush = QBrush(QColor(10, 25, 120), Qt::BrushStyle::SolidPattern));

    /**
     *  @brief      Data set count.
     *  @details    This function returns the number of data sets that are configured in the scene.
     *  @returns    The number of data sets.
     */
    unsigned int dataSetCount() const noexcept;

    /**
     *  @brief      Data set.
     *  @details    This function returns the specified data set indexed by dataSet.
     *  @param[in]  i  Index of the data set that will be returned.  
     *  @returns    The specified data set.
     */
    const DataProperties& dataSet(unsigned int i) const;

    /**
     *  @brief      Draw plot.
     *  @details    This function renders the elements of the plot.
     */
    void drawPlot() override;

private:

    ////////// Data members //////////

    QList<DataProperties> data_;    /**< The properties of the data to be plotted. */

};

}}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================

