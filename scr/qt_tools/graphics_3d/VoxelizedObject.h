//=================================================================================================================
/**
 *  @file       VoxelizedObject.h
 *  @brief      qt_tools::graphics_3d::VoxelizedObject class.
 *  @details    Declaration of the qt_tools::graphics_3d::VoxelizedObject class. 
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

#ifndef QT_TOOLS_VOXELIZED_OBJECT_H_INCLUDE
#define QT_TOOLS_VOXELIZED_OBJECT_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <qt_tools/graphics_3d/Object3D.h>
#include <nct/Array2D.h>
#include <nct/SparseArray3D.h>
#include <nct/color/RgbColor.h>

//=================================================================================================================
namespace qt_tools {
namespace graphics_3d {

/**
 *  @brief      class to manage and draw voxelized objects.
 *  @details    This class is used to draw a cube centered in the origin with unitary size.
 */
class QT_TOOLS_EXPIMP VoxelizedObject final : public Object3D {

public:

    ////////// Constructors //////////
    
    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the default configuration.
     */
    VoxelizedObject();

    /**
     *  @brief      Class constructor.
     *  @details    This constructor builds an object with the specified face colors and voxels. 
     *  @param[in]  voxels  Voxels to add to the scene.
     *  @param[in]  faceColor  Color of each cube in RGB format.
     */
    VoxelizedObject(const nct::SparseArray3D<bool>& voxels,
        const nct::color::RgbColor& faceColor);
    
    /**
     *  @brief      Copy constructor.
     *  @details    This constructor is deleted.
     */
    VoxelizedObject(const VoxelizedObject&) = delete;
    
    /**
     *  @brief      Move constructor.
     *  @details    This constructor is deleted.
     */
    VoxelizedObject(VoxelizedObject&&) = delete;
    
    ////////// Destructor //////////

    /**
     *  @brief      Destructor.
     *  @details    Class destructor. 
     */
    ~VoxelizedObject();

    ////////// Operators //////////
    
    /**
     *  @brief      Assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    VoxelizedObject& operator=(const VoxelizedObject&) = delete;
    
    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    VoxelizedObject& operator=(VoxelizedObject&&) = delete;

    ////////// Member functions //////////        

    /**
     *  @brief      Voxel indices.
     *  @details    This function returns the indices of the voxels that are rendered in the scene.
     *  @returns    The voxel indices.
     */
    const nct::Array<nct::Vector3D<size_t>>& voxelIndices() const noexcept;

    /**
     *  @brief      Point size.
     *  @details    This function returns the size of the points.
     *  @returns    The current point size.
     */
    float pointSize() const noexcept;

    /**
     *  @brief      Set point size.
     *  @details    This function modifies the size of the points.
     *  @param[in]  size  The new size of the points.
     */
    void setPointSize(float size);

    /**
     *  @brief      Line width.
     *  @details    This function returns the width of the lines.
     *  @returns    The current line with.
     */
    float lineWidth() const noexcept;

    /**
     *  @brief      Set line with.
     *  @details    This function modifies the with of the lines.
     *  @param[in]  size  The new width of the lines.
     */
    void setLineWidth(float width);

    /**
     *  @brief      Initialize object.
     *  @details    This function is used to allocate memory, bind arrays and create other stuff
     *              needed by the geometry in order to be drawn.
     */
    void initialize() override;

    /**
     *  @brief      Release object.
     *  @details    This function is used to clear all the memory allocated by the object (arrays
     *              and buffers). 
     */
    void clear() override;

    /**
     *  @brief      Draw faces.
     *  @details    This function draws the faces of the shape. 
     *  @param[in]  program  The program that executes the shader code.
     */
    void drawFaces(QOpenGLShaderProgram& program) override;

    /**
     *  @brief      Draw lines.
     *  @details    This function draws the lines of the shape. 
     *  @param[in]  program  The program that executes the shader code.
     */
    void drawLines(QOpenGLShaderProgram& program) override;

    /**
     *  @brief      Draw points.
     *  @details    This function draws the points of the shape. 
     *  @param[in]  program  The program that executes the shader code.
     */
    void drawPoints(QOpenGLShaderProgram& program) override;

private:

    ////////// Data members //////////                

    float pointSize_ {0};           /**< Point size. */

    float lineWidth_ {0};           /**< Line width. */

    nct::Array<nct::Vector3D<size_t>> voxels_;    /**< Voxel indices. */

    nct::RealVector scales_;        /**< Scales. */

    nct::RealVector centersX_;      /**< Centers of each voxel for the first variable. */

    nct::RealVector centersY_;      /**< Centers of each voxel for the second variable. */

    nct::RealVector centersZ_;      /**< Centers of each voxel for the third variable. */

    nct::color::RgbColor color_;    /**< Model color. */

    QOpenGLBuffer triangleBuffer_;  /**< Buffer for triangles. */

    QOpenGLBuffer lineBuffer_;      /**< Buffer for lines. */

    QOpenGLBuffer vertexBuffer_;    /**< Vertex buffer. */

    QOpenGLBuffer normalBuffer_;    /**< Normal buffer. */

    QOpenGLBuffer colorBuffer_;     /**< Color buffer. */

};

}}

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
