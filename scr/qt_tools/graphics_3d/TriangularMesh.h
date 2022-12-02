//=================================================================================================================
/**
 *  @file       TriangularMesh.h
 *  @brief      qt_tools::graphics_3d::TriangularMesh class.
 *  @details    Declaration of the qt_tools::graphics_3d::TriangularMesh class. 
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

#ifndef QT_TOOLS_TRIANGULAR_MESH_H_INCLUDE
#define QT_TOOLS_TRIANGULAR_MESH_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <qt_tools/graphics_3d/Object3D.h>
#include <nct/Array.h>
#include <nct/Array2D.h>
#include <nct/color/RgbColor.h>
#include <nct/Vector3D.h>

//=================================================================================================================
namespace qt_tools {
namespace graphics_3d {

/**
 *  @brief      Test geometry class.
 *  @details    This class is used to draw a triangular mesh.
 */
class QT_TOOLS_EXPIMP TriangularMesh final : public Object3D {

public:

    ////////// Constructors //////////
    
    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the default configuration.
     */
    TriangularMesh();

    /**
     *  @brief      Class constructor.
     *  @details    This constructor builds an object with the specified geometry. 
     *  @param[in]  vertices  Array of vertices of the mesh.        
     *  @param[in]  normals  Array of vertex normals. It must containt the same number of elements than 
     *              the vextex array.        
     *  @param[in]  triangles  Array of indices of the vertices of each triangle in the mesh.     
     *  @param[in]  color  Color of the solid.
     */
    TriangularMesh(const nct::Array<nct::Point3D>& vertices,
        const nct::Array<nct::Vector3D<double>>& normals,
        const nct::Array<nct::Vector3D<unsigned int>>& triangles,
        const nct::color::RgbColor& color);

    /**
     *  @brief      Class constructor.
     *  @details    This constructor builds an object with the specified geometry. 
     *  @param[in]  vertices  Array of vertices of the mesh.        
     *  @param[in]  normals  Array of vertex normals. It must containt the same number of elements than 
     *              the vextex array.        
     *  @param[in]  triangles  Array of indices of the vertices of each triangle in the mesh.     
     *  @param[in]  colors  Colors of each point.
     */
    TriangularMesh(const nct::Array<nct::Point3D>& vertices,
        const nct::Array<nct::Vector3D<double>>& normals,
        const nct::Array<nct::Vector3D<unsigned int>>& triangles,
        const nct::Array<nct::color::RgbColor>& colors);

    /**
     *  @brief      Class constructor.
     *  @details    This constructor builds an object with the specified geometry. 
     *  @param[in]  vertices  Array of vertices of the mesh.        
     *  @param[in]  normals  Array of vertex normals. It must containt the same number of elements than 
     *              the vextex array.        
     *  @param[in]  triangles  Array of indices of the vertices of each triangle in the mesh.     
     *  @param[in]  color  Color of the solid.
     */
    TriangularMesh(const std::shared_ptr<nct::Array<nct::Point3D>>& vertices,
        const std::shared_ptr<nct::Array<nct::Vector3D<double>>>& normals,
        const std::shared_ptr<nct::Array<nct::Vector3D<unsigned int>>>& triangles,
        const nct::color::RgbColor& color);

    /**
     *  @brief      Class constructor.
     *  @details    This constructor builds an object with the specified geometry. 
     *  @param[in]  vertices  Array of vertices of the mesh.        
     *  @param[in]  normals  Array of vertex normals. It must containt the same number of elements than 
     *              the vextex array.        
     *  @param[in]  triangles  Array of indices of the vertices of each triangle in the mesh.     
     *  @param[in]  colors  Colors of each point.
     */
    TriangularMesh(const std::shared_ptr<nct::Array<nct::Point3D>>& vertices,
        const std::shared_ptr<nct::Array<nct::Vector3D<double>>>& normals,
        const std::shared_ptr<nct::Array<nct::Vector3D<unsigned int>>>& triangles,
        const std::shared_ptr<nct::Array<nct::color::RgbColor>>& colors);
    
    /**
     *  @brief      Copy constructor.
     *  @details    This constructor is deleted.
     */
    TriangularMesh(const TriangularMesh&) = delete;
    
    /**
     *  @brief      Move constructor.
     *  @details    This constructor is deleted.
     */
    TriangularMesh(TriangularMesh&&) = delete;
    
    ////////// Destructor //////////

    /**
     *  @brief      Destructor.
     *  @details    Class destructor. 
     */
    ~TriangularMesh();

    ////////// Operators //////////
    
    /**
     *  @brief      Assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    TriangularMesh& operator=(const TriangularMesh&) = delete;
    
    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    TriangularMesh& operator=(TriangularMesh&&) = delete;

    ////////// Member functions //////////        

    /**
     *  @brief      Array of triangles.
     *  @details    This function returns the array of indices that indicate which vertices
     *              correspond to each triangle.
     *  @returns    The array of triangles.
     */
    const std::shared_ptr<nct::Array<nct::Vector3D<unsigned int>>>& meshTriangles() const noexcept;

    /**
     *  @brief      Vertices.
     *  @details    This function returns the array of vertices of the mesh.
     *  @returns    The array of vertices.
     */
    const std::shared_ptr<nct::Array<nct::Point3D>>& vertexPositions() const noexcept;

    /**
     *  @brief      Normals.
     *  @details    This function returns the array of normal vectors of the vertices.
     *  @returns    The array of normal vectors.
     */
    const std::shared_ptr<nct::Array<nct::Vector3D<double>>>& vertexNormals() const noexcept;

    /**
     *  @brief      Colors.
     *  @details    This function returns the colors of each vertex.
     *  @returns    The array of colors.
     */
    const std::shared_ptr<nct::Array<nct::color::RgbColor>>& vertexColors() const noexcept;

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

    float pointSize_ {0};       /**< Point size. */

    float lineWidth_ {0};       /**< Line width. */

    std::shared_ptr<nct::Array<nct::Vector3D<unsigned int>>> triangles_;    /**< Triangles. */

    std::shared_ptr<nct::Array<nct::Point3D>> vertices_;                    /**< Vertices. */

    std::shared_ptr<nct::Array<nct::Vector3D<double>>> normals_;            /**< Vertex normals. */

    std::shared_ptr<nct::Array<nct::color::RgbColor>> colors_;              /**< Colors. */

    QOpenGLBuffer triangleBuffer_;      /**< Triangle buffer. */

    QOpenGLBuffer vertexBuffer_;        /**< Vertex buffer. */

    QOpenGLBuffer normalBuffer_;        /**< Normal buffer. */

    QOpenGLBuffer colorBuffer_;         /**< Color buffer. */

};

}}

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
