//=================================================================================================================
/**
 *  @file       TriangularMesh.cpp
 *  @brief      qt_tools::graphics_3d::TriangularMesh class implementation file.
 *  @details    This file contains the implementation of the qt_tools::graphics_3d::TriangularMesh class.
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
#include <qt_tools/graphics_3d/TriangularMesh.h>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
qt_tools::graphics_3d::TriangularMesh::TriangularMesh()
{    
    pointSize_ = 1.0;
    lineWidth_ = 1.0;

    vertices_ = std::make_shared<nct::Array<nct::Point3D>>();
    normals_ = std::make_shared<nct::Array<nct::Vector3D<double>>>();
    triangles_ = std::make_shared<nct::Array<nct::Vector3D<unsigned int>>>();
    colors_ = std::make_shared<nct::Array<nct::color::RgbColor>>();
}


//-----------------------------------------------------------------------------------------------------------------
qt_tools::graphics_3d::TriangularMesh::TriangularMesh(
    const nct::Array<nct::Point3D>& vertices,
    const nct::Array<nct::Vector3D<double>>& normals,
    const nct::Array<nct::Vector3D<unsigned int>>& triangles,
    const nct::color::RgbColor& color)
{
    pointSize_ = 1.0;
    lineWidth_ = 1.0;

    auto nV = vertices.size();
    auto nT = triangles.size();
    
    if (normals.size() != nV)
        throw nct::ArgumentException("normals", exc_bad_array_of_normals, SOURCE_INFO);

    for (index_t i=0; i<nT; i++) {
        if (triangles.at(i)[0]>=nV)
            throw nct::IndexOutOfRangeException("triangles", SOURCE_INFO);

        if (triangles.at(i)[1] >= nV)
            throw nct::IndexOutOfRangeException("triangles", SOURCE_INFO);

        if (triangles.at(i)[2] >= nV)
            throw nct::IndexOutOfRangeException("triangles", SOURCE_INFO);
    }

    // Initialize containers.
    vertices_ = std::make_shared<nct::Array<nct::Point3D>>(vertices);
    normals_ = std::make_shared<nct::Array<nct::Vector3D<double>>>(normals);
    triangles_ = std::make_shared<nct::Array<nct::Vector3D<unsigned int>>>(triangles);
    colors_ = std::make_shared<nct::Array<nct::color::RgbColor>>(nV, color);    
}

//-----------------------------------------------------------------------------------------------------------------
qt_tools::graphics_3d::TriangularMesh::TriangularMesh(
    const nct::Array<nct::Point3D>& vertices,
    const nct::Array<nct::Vector3D<double>>& normals,
    const nct::Array<nct::Vector3D<unsigned int>>& triangles,
    const nct::Array<nct::color::RgbColor>& colors)
{
    pointSize_ = 1.0;
    lineWidth_ = 1.0;

    auto nV = vertices.size();
    auto nT = triangles.size();
    
    if (normals.size() != nV)
        throw nct::ArgumentException("normals",    exc_bad_array_of_normals, SOURCE_INFO);

    if (colors.size() != nV)
        throw nct::ArgumentException("colors", exc_bad_color_array, SOURCE_INFO);

    for (index_t i = 0; i<nT; i++) {
        if (triangles.at(i)[0] >= nV)
            throw nct::IndexOutOfRangeException("triangles", SOURCE_INFO);

        if (triangles.at(i)[1] >= nV)
            throw nct::IndexOutOfRangeException("triangles", SOURCE_INFO);

        if (triangles.at(i)[2] >= nV)
            throw nct::IndexOutOfRangeException("triangles", SOURCE_INFO);
    }

    // Vertices.
    vertices_ = std::make_shared<nct::Array<nct::Point3D>>(vertices);
    normals_ = std::make_shared<nct::Array<nct::Vector3D<double>>>(normals);
    triangles_ = std::make_shared<nct::Array<nct::Vector3D<unsigned int>>>(triangles);
    colors_ = std::make_shared<nct::Array<nct::color::RgbColor>>(colors);
}

//-----------------------------------------------------------------------------------------------------------------
qt_tools::graphics_3d::TriangularMesh::TriangularMesh(
    const std::shared_ptr<nct::Array<nct::Point3D>>& vertices,
    const std::shared_ptr<nct::Array<nct::Vector3D<double>>>& normals,
    const std::shared_ptr<nct::Array<nct::Vector3D<unsigned int>>>& triangles,
    const nct::color::RgbColor& color)
{
    pointSize_ = 1.0;
    lineWidth_ = 1.0;

    if (vertices == nullptr)
        throw nct::NullPointerException("vertices", SOURCE_INFO);

    if (normals == nullptr)
        throw nct::NullPointerException("normals", SOURCE_INFO);

    if (triangles == nullptr)
        throw nct::NullPointerException("triangles", SOURCE_INFO);

    auto nV = vertices->size();
    auto nT = triangles->size();
    
    if (normals->size() != nV)
        throw nct::ArgumentException("normals", exc_bad_array_of_normals, SOURCE_INFO);

    for (index_t i=0; i<nT; i++) {
        if (triangles->at(i)[0]>=nV)
            throw nct::IndexOutOfRangeException("triangles", SOURCE_INFO);

        if (triangles->at(i)[1] >= nV)
            throw nct::IndexOutOfRangeException("triangles", SOURCE_INFO);

        if (triangles->at(i)[2] >= nV)
            throw nct::IndexOutOfRangeException("triangles", SOURCE_INFO);
    }

    // Initialize containers.
    vertices_ = vertices;
    normals_ = normals;
    triangles_ = triangles;
    colors_ = std::make_shared<nct::Array<nct::color::RgbColor>>(nV, color);    
}

//-----------------------------------------------------------------------------------------------------------------
qt_tools::graphics_3d::TriangularMesh::TriangularMesh(
    const std::shared_ptr<nct::Array<nct::Point3D>>& vertices,
    const std::shared_ptr<nct::Array<nct::Vector3D<double>>>& normals,
    const std::shared_ptr<nct::Array<nct::Vector3D<unsigned int>>>& triangles,
    const std::shared_ptr<nct::Array<nct::color::RgbColor>>& colors)
{
    pointSize_ = 1.0;
    lineWidth_ = 1.0;

    if (vertices == nullptr)
        throw nct::NullPointerException("vertices", SOURCE_INFO);

    if (normals == nullptr)
        throw nct::NullPointerException("normals", SOURCE_INFO);

    if (triangles == nullptr)
        throw nct::NullPointerException("triangles", SOURCE_INFO);

    if (colors == nullptr)
        throw nct::NullPointerException("colors", SOURCE_INFO);

    auto nV = vertices->size();
    auto nT = triangles->size();
    
    if (normals->size() != nV)
        throw nct::ArgumentException("normals",    exc_bad_array_of_normals, SOURCE_INFO);

    if (colors->size() != nV)
        throw nct::ArgumentException("colors", exc_bad_color_array, SOURCE_INFO);

    for (index_t i = 0; i<nT; i++) {
        if (triangles->at(i)[0] >= nV)
            throw nct::IndexOutOfRangeException("triangles", SOURCE_INFO);

        if (triangles->at(i)[1] >= nV)
            throw nct::IndexOutOfRangeException("triangles", SOURCE_INFO);

        if (triangles->at(i)[2] >= nV)
            throw nct::IndexOutOfRangeException("triangles", SOURCE_INFO);
    }

    // Vertices.
    vertices_ = vertices;
    normals_ = normals;
    triangles_ = triangles;
    colors_ = colors;
}

//=================================================================================================================
//        DESTRUCTOR
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
qt_tools::graphics_3d::TriangularMesh::~TriangularMesh()
{
    triangles_.reset();
    vertices_.reset();
    normals_.reset();
    colors_.reset();

    vertexBuffer_.destroy();
    normalBuffer_.destroy();
    colorBuffer_.destroy();
    triangleBuffer_.destroy();
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
const std::shared_ptr<nct::Array<nct::Vector3D<unsigned int>>>&
qt_tools::graphics_3d::TriangularMesh::meshTriangles() const noexcept
{
    return triangles_;
}

//-----------------------------------------------------------------------------------------------------------------
const std::shared_ptr<nct::Array<nct::Point3D>>& 
qt_tools::graphics_3d::TriangularMesh::vertexPositions() const noexcept
{
    return vertices_;
}

//-----------------------------------------------------------------------------------------------------------------
const std::shared_ptr<nct::Array<nct::Vector3D<double>>>& 
qt_tools::graphics_3d::TriangularMesh::vertexNormals() const noexcept
{
    return normals_;
}

//-----------------------------------------------------------------------------------------------------------------
const std::shared_ptr<nct::Array<nct::color::RgbColor>>& 
qt_tools::graphics_3d::TriangularMesh::vertexColors() const noexcept
{
    return colors_;
}

//-----------------------------------------------------------------------------------------------------------------
float qt_tools::graphics_3d::TriangularMesh::pointSize() const noexcept
{
    return pointSize_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::TriangularMesh::setPointSize(float size)
{
    pointSize_ = size;
}

//-----------------------------------------------------------------------------------------------------------------
float qt_tools::graphics_3d::TriangularMesh::lineWidth() const noexcept
{
    return lineWidth_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::TriangularMesh::setLineWidth(float width)
{
    lineWidth_ = width;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::TriangularMesh::initialize()
{
    if (QOpenGLContext::currentContext() == nullptr)
        return;

    if (geometryOk_)
        return;

    initializeOpenGLFunctions();

    auto nv = vertices_->size();
    auto nt = triangles_->size();
    if ((nt == 0) || (nv == 0) || (colors_->size() != nv) || (normals_->size() != nv))
        return;

    // Create buffers.
    vertexBuffer_.create();
    vertexBuffer_.bind();
    vertexBuffer_.allocate(vertices_->data(), static_cast<int>(sizeof(nct::Point3D) * vertices_->size()));

    normalBuffer_.create();
    normalBuffer_.bind();
    normalBuffer_.allocate(normals_->data(), static_cast<int>(sizeof(nct::Vector3D<double>) * normals_->size()));
    
    colorBuffer_.create();
    colorBuffer_.bind();
    colorBuffer_.allocate(colors_->data(), static_cast<int>(sizeof(nct::color::RgbColor) * colors_->size()));
    
    triangleBuffer_ = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    triangleBuffer_.create();
    triangleBuffer_.bind();
    triangleBuffer_.allocate(triangles_->data(), 
        static_cast<int>(sizeof(nct::Vector3D<unsigned int>) * triangles_->size()));

    // Check for errors.
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        clear();
        throw nct::OperationException(std::string(exc_error_initializing_vbo) + 
            std::to_string(err), SOURCE_INFO);
    }

    geometryOk_ = true;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::TriangularMesh::clear()
{
    geometryOk_ = false;
    pointSize_ = 1.0;
    lineWidth_ = 1.0;

    triangles_.reset();
    vertices_.reset();
    normals_.reset();
    colors_.reset();

    vertexBuffer_.destroy();
    normalBuffer_.destroy();
    colorBuffer_.destroy();
    triangleBuffer_.destroy();
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::TriangularMesh::drawFaces(QOpenGLShaderProgram& program)
{
    // Verify whether the object was initialized previously.
    if (!geometryOk_)
        return;

    triangleBuffer_.bind();

    vertexBuffer_.bind();    
    int vertexLocation = program.attributeLocation("vertexPosition");
    program.enableAttributeArray(vertexLocation);
    program.setAttributeBuffer(vertexLocation, GL_DOUBLE, 0, 3, 0);

    normalBuffer_.bind();
    int normalLocation = program.attributeLocation("vertexNormal");
    program.enableAttributeArray(normalLocation);
    program.setAttributeBuffer(normalLocation, GL_DOUBLE, 0, 3, 0);

    colorBuffer_.bind();
    int colorLocation = program.attributeLocation("vertexColor");
    program.enableAttributeArray(colorLocation);
    program.setAttributeBuffer(colorLocation, GL_DOUBLE, 0, 3, 0);

    // Set culling properties
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Draw shape.
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(3 * triangles_->size()), GL_UNSIGNED_INT, 0);

    // Disable vertex arrays.
    program.disableAttributeArray(vertexLocation);
    program.disableAttributeArray(colorLocation);
    program.disableAttributeArray(normalLocation);

    // Check for errors.
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
        throw nct::OperationException(std::string(exc_error_drawing_object) +
            std::to_string(err), SOURCE_INFO);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::TriangularMesh::drawLines(QOpenGLShaderProgram& program)
{
    // Verify whether the object was initialized previously.
    if (!geometryOk_)
        return;

    vertexBuffer_.bind();
    triangleBuffer_.bind();
    int vertexLocation = program.attributeLocation("vertexPosition");
    program.enableAttributeArray(vertexLocation);
    program.setAttributeBuffer(vertexLocation, GL_DOUBLE, 0, 3, 0);

    normalBuffer_.bind();
    int normalLocation = program.attributeLocation("vertexNormal");
    program.enableAttributeArray(normalLocation);
    program.setAttributeBuffer(normalLocation, GL_DOUBLE, 0, 3, 0);

    colorBuffer_.bind();
    int colorLocation = program.attributeLocation("vertexColor");
    program.enableAttributeArray(colorLocation);
    program.setAttributeBuffer(colorLocation, GL_DOUBLE, 0, 3, 0);

    // Set culling properties
    glDisable(GL_CULL_FACE);

    // Draw shape.
    glLineWidth(lineWidth_);
    for (index_t i = 0; i < triangles_->size(); i++) {
        int offset = static_cast<int>(i * 3);
        glDrawElements(GL_LINE_LOOP, static_cast<GLsizei>(3), GL_UNSIGNED_INT, 
            (void*)(offset * sizeof(GLuint)));
    }

    // Disable vertex arrays.
    program.disableAttributeArray(vertexLocation);
    program.disableAttributeArray(colorLocation);
    program.disableAttributeArray(normalLocation);

    // Check for errors.
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
        throw nct::OperationException(std::string(exc_error_drawing_object) +
            std::to_string(err), SOURCE_INFO);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::TriangularMesh::drawPoints(QOpenGLShaderProgram& program)
{
    // Verify whether the object was initialized previously.
    if (!geometryOk_)
        return;

    vertexBuffer_.bind();
    triangleBuffer_.bind();
    int vertexLocation = program.attributeLocation("vertexPosition");
    program.enableAttributeArray(vertexLocation);
    program.setAttributeBuffer(vertexLocation, GL_DOUBLE, 0, 3, 0);

    normalBuffer_.bind();
    int normalLocation = program.attributeLocation("vertexNormal");
    program.enableAttributeArray(normalLocation);
    program.setAttributeBuffer(normalLocation, GL_DOUBLE, 0, 3, 0);

    colorBuffer_.bind();
    int colorLocation = program.attributeLocation("vertexColor");
    program.enableAttributeArray(colorLocation);
    program.setAttributeBuffer(colorLocation, GL_DOUBLE, 0, 3, 0);

    // Set culling properties
    glDisable(GL_CULL_FACE);

    // Draw shape.
    glPointSize(pointSize_);
    glDrawElements(GL_POINTS, static_cast<GLsizei>(3 * triangles_->size()), GL_UNSIGNED_INT, 0);

    // Disable vertex arrays.
    program.disableAttributeArray(vertexLocation);
    program.disableAttributeArray(colorLocation);
    program.disableAttributeArray(normalLocation);

    // Check for errors.
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
        throw nct::OperationException(std::string(exc_error_drawing_object) +
            std::to_string(err), SOURCE_INFO);
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
