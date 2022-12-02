//=================================================================================================================
/**
 *  @file       ArrayPlot.h
 *  @brief      qt_tools::plots::ArrayPlot class.
 *  @details    Declaration of the qt_tools::plots::ArrayPlot class.   
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

#ifndef QT_TOOLS_ARRAY_PLOT_H_INCLUDE
#define QT_TOOLS_ARRAY_PLOT_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <qt_tools/plots/XYColorPlot.h>
#include <nct/Array.h>
#include <nct/Array2D.h>

//=================================================================================================================
namespace qt_tools {
namespace plots {

/**
 *  @brief      Array plot.
 *  @details    This class is used for drawing array plots. This plot consists of one image
 *              in fake color that is created according to the values of one
 *              rectangular array. The colors are calculated according to the current
 *              color palette that is configured in the scene.
 */
class QT_TOOLS_EXPIMP ArrayPlot final : public XYColorPlot {
    Q_OBJECT

public:

    ////////// Structures //////////    

    /**
     *  @brief      Plot properties.
     *  @details    This structure defines the properties of the plot.
     */
    struct PlotProperties final {

        QString name;                       /**< Name of the data set. */

        bool reverseVerticalAxis {false};   /**< True indicates that the vertical values change 
                                                 their order. */
        QColor defaultColor;                /**< Default color. */

        std::shared_ptr<nct::Matrix> arr;   /**< Data array. */

        /** Array that indicates which elements will use
            the default color instead of the colorbar. */
        std::shared_ptr<nct::Array2D<bool>> useDefaultColor;
    };

    ////////// Constructors //////////
    
    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes the scene. 
     *  @param[in]  parent  Parent object.
     */
    ArrayPlot(QObject* parent = 0);
    
    /**
     *  @brief      Copy constructor.
     *  @details    This constructor is deleted.
     */
    ArrayPlot(const ArrayPlot&) = delete;
    
    /**
     *  @brief      Move constructor.
     *  @details    This constructor is deleted.
     */
    ArrayPlot(ArrayPlot&&) = delete;
    
    ////////// Destructor //////////

    /**
     *  @brief      Destructor.
     *  @details    Class destructor. 
     */
    ~ArrayPlot() = default;

    ////////// Operators //////////
    
    /**
     *  @brief      Assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    ArrayPlot& operator=(const ArrayPlot&) = delete;
    
    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    ArrayPlot& operator=(ArrayPlot&&) = delete;

    ////////// Member functions //////////

    /**
     *  @brief      Clear data.
     *  @details    This function clears the data set.
     */
    void clearData();

    /**
     *  @brief      Configure plot.
     *  @details    This function configures how the plot shows the data.
     *  @param[in]  arr  Array of values.
     *  @param[in]  name  The name of the data set.
     *  @param[in]  reverse  True indicates that the vertical values are shown in 
     *              reverse order.
     */
    void configPlot(const nct::Matrix& arr,
        const QString& name = "", bool reverse = false);

    /**
     *  @brief      Configure plot.
     *  @details    This function configures how the plot shows the data.
     *  @param[in]  arr  Array of values.
     *  @param[in]  name  The name of the data set.
     *  @param[in]  reverse  True indicates that the vertical values are shown in 
     *              reverse order.
     */
    void configPlot(nct::Matrix&& arr,
        const QString& name = "", bool reverse = false);

    /**
     *  @brief      Configure plot.
     *  @details    This function configures how the plot shows the data.
     *  @param[in]  arr  Array of values.
     *  @param[in]  name  The name of the data set.
     *  @param[in]  reverse  True indicates that the vertical values are shown in 
     *              reverse order.
     */
    void configPlot(const std::shared_ptr<nct::Matrix>& arr,
        const QString& name = "", bool reverse = false);

    /**
     *  @brief      Configure plot.
     *  @details    This function configures how the plot shows the data.
     *  @param[in]  arr  Array of values.
     *  @param[in]  useDefaultColor  An array that indicates which elements will use the default color
     *              instead of the colorbar.
     *  @param[in]  defaultColor  Default color of the observations.
     *  @param[in]  name  The name of the data set.
     *  @param[in]  reverse  True indicates that the vertical values are shown in 
     *              reverse order.
     */
    void configPlot(const nct::Matrix& arr,
        const nct::Array2D<bool>& useDefaultColor,
        const QColor& defaultColor = QColor(0, 0, 0, 255),
        const QString& name = "", bool reverse = false);

    /**
     *  @brief      Configure plot.
     *  @details    This function configures how the plot shows the data.
     *  @param[in]  arr  Array of values.
     *  @param[in]  useDefaultColor  An array that indicates which elements will use the default color
     *              instead of the colorbar.
     *  @param[in]  defaultColor  Default color of the observations.
     *  @param[in]  name  The name of the data set.
     *  @param[in]  reverse  True indicates that the vertical values are shown in 
     *              reverse order.
     */
    void configPlot(nct::Matrix&& arr,
        nct::Array2D<bool>&& useDefaultColor,
        const QColor& defaultColor = QColor(0, 0, 0, 255),
        const QString& name = "", bool reverse = false);

    /**
     *  @brief      Configure plot.
     *  @details    This function configures how the plot shows the data.
     *  @param[in]  arr  Array of values.
     *  @param[in]  useDefaultColor  An array that indicates which elements will use the default color
     *              instead of the colorbar.
     *  @param[in]  defaultColor  Default color of the observations.
     *  @param[in]  name  The name of the data set.
     *  @param[in]  reverse  True indicates that the vertical values are shown in 
     *              reverse order.
     */
    void configPlot(const std::shared_ptr<nct::Matrix>& arr,
        const std::shared_ptr<nct::Array2D<bool>>& useDefaultColor,
        const QColor& defaultColor = QColor(0, 0, 0, 255),
        const QString& name = "", bool reverse = false);

    /**
     *  @brief      Configure plot.
     *  @details    This function configures how the plot shows the data.
     *  @param[in]  defaultColor  Default color of the observations.
     *  @param[in]  name  The name of the data set.
     *  @param[in]  reverse  True indicates that the vertical values are shown in 
     *              reverse order.
     */
    void configPlot(const QColor& defaultColor = QColor(0, 0, 0, 255),
        const QString& name = "", bool reverse = false);

    /**
     *  @brief      Plot properties.
     *  @details    This function returns an object with the properties of the plot.
     *  @returns    The properties of the data set. 
     */      
    const PlotProperties& plotProperties() const noexcept;

    /**
     *  @brief      Draw plot.
     *  @details    This function renders the elements of the plot.
     */
    void drawPlot() override;

private:

    ////////// Data members //////////

    PlotProperties data_;       /**< Properties of the plot. */
};

}}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================

