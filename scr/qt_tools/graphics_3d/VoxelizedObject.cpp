//=================================================================================================================
/**
 *  @file       VoxelizedObject.cpp
 *  @brief      qt_tools::graphics_3d::VoxelizedObject class implementation file.
 *  @details    This file contains the implementation of the qt_tools::graphics_3d::VoxelizedObject class.
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
#include <qt_tools/graphics_3d/VoxelizedObject.h>
#include <nct/Vector2D.h>
#include <nct/geometry/mesh.h>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
qt_tools::graphics_3d::VoxelizedObject::VoxelizedObject()
{
    pointSize_ = 1.0;
    lineWidth_ = 1.0;
    color_ = nct::color::RgbColor((unsigned char)255, (unsigned char)255, (unsigned char)255);
}

//-----------------------------------------------------------------------------------------------------------------
qt_tools::graphics_3d::VoxelizedObject::VoxelizedObject(const nct::SparseArray3D<bool>& voxels,
    const nct::color::RgbColor& faceColor)
{
    pointSize_ = 1.0;
    lineWidth_ = 1.0;
    color_ = faceColor;
    
    // Voxels.
    auto vv = voxels.nonNullElements();
    auto nv = vv.size();

    voxels_.clear();
    voxels_.resize(nv);
    for (index_t i=0; i<nv; i++)
        voxels_[i] = vv[i].first;

    // Centers.
    auto divX = voxels.dimension1();
    auto divY = voxels.dimension2();
    auto divZ = voxels.dimension3();

    centersX_.assign(divX, 0.0);
    centersY_.assign(divY, 0.0);
    centersZ_.assign(divZ, 0.0);

    scales_.assign(3, 0.0);

    scales_[0] = 2.f/divX;
    for (index_t i=0; i<divX; i++)
        centersX_[i] = -1.0 + i*2.0/divX + scales_[0]/2;

    scales_[1] = 2.f/divY;
    for (index_t i=0; i<divY; i++)
        centersY_[i] = -1.0 + i*2.0/divY + scales_[1]/2;

    scales_[2] = 2.f/divZ;
    for (index_t i=0; i<divZ; i++)
        centersZ_[i] = -1.0 + i*2.0/divZ + scales_[2]/2;
}

//=================================================================================================================
//        DESTRUCTOR
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
qt_tools::graphics_3d::VoxelizedObject::~VoxelizedObject()
{
    voxels_.clear();
    scales_.clear();
    centersX_.clear();
    centersY_.clear();
    centersZ_.clear();

    triangleBuffer_.destroy();
    lineBuffer_.destroy();
    vertexBuffer_.destroy();
    normalBuffer_.destroy();
    colorBuffer_.destroy();
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
const nct::Array<nct::Vector3D<qt_tools::size_t>>& 
qt_tools::graphics_3d::VoxelizedObject::voxelIndices() const noexcept
{
    return voxels_;
}

//-----------------------------------------------------------------------------------------------------------------
float qt_tools::graphics_3d::VoxelizedObject::pointSize() const noexcept
{
    return pointSize_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::VoxelizedObject::setPointSize(float size)
{
    pointSize_ = size;
}

//-----------------------------------------------------------------------------------------------------------------
float qt_tools::graphics_3d::VoxelizedObject::lineWidth() const noexcept
{
    return lineWidth_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::VoxelizedObject::setLineWidth(float width)
{
    lineWidth_ = width;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::VoxelizedObject::initialize()
{
    if (QOpenGLContext::currentContext() == nullptr)
        return;

    if (geometryOk_)
        return;

    initializeOpenGLFunctions();

    // Vertices, triangles, lines and colors.
    int nPoints = 8;
    
    nct::Array<nct::Point3D> vertices(nPoints);
    vertices[0] = nct::Point3D(-0.5, -0.5,  0.5);
    vertices[1] = nct::Point3D( 0.5, -0.5,  0.5);
    vertices[2] = nct::Point3D(-0.5,  0.5,  0.5);
    vertices[3] = nct::Point3D( 0.5,  0.5,  0.5);
    vertices[4] = nct::Point3D(-0.5, -0.5, -0.5);
    vertices[5] = nct::Point3D( 0.5, -0.5, -0.5);
    vertices[6] = nct::Point3D(-0.5,  0.5, -0.5);
    vertices[7] = nct::Point3D( 0.5,  0.5, -0.5);

    nct::Array<nct::Vector3D<unsigned int>> triangles(12);
    triangles[0] = nct::Vector3D<unsigned int>(0, 1, 2);
    triangles[1] = nct::Vector3D<unsigned int>(2, 1, 3);
    triangles[2] = nct::Vector3D<unsigned int>(3, 1, 5);
    triangles[3] = nct::Vector3D<unsigned int>(3, 5, 7);
    triangles[4] = nct::Vector3D<unsigned int>(4, 6, 5);
    triangles[5] = nct::Vector3D<unsigned int>(5, 6, 7);
    triangles[6] = nct::Vector3D<unsigned int>(4, 0, 6);
    triangles[7] = nct::Vector3D<unsigned int>(6, 0, 2);
    triangles[8] = nct::Vector3D<unsigned int>(6, 2, 7);
    triangles[9] = nct::Vector3D<unsigned int>(7, 2, 3);
    triangles[10]= nct::Vector3D<unsigned int>(4, 5, 0);
    triangles[11]= nct::Vector3D<unsigned int>(0, 5, 1);
    
    auto normals = nct::geometry::mesh::calculateVertexNormals(vertices, triangles);
    
    nct::Array<nct::Vector2D<unsigned int>> lines(12);
    lines[0] = nct::Vector2D<unsigned int>(0, 2);
    lines[1] = nct::Vector2D<unsigned int>(2, 3);
    lines[2] = nct::Vector2D<unsigned int>(3, 1);
    lines[3] = nct::Vector2D<unsigned int>(1, 0);
    lines[4] = nct::Vector2D<unsigned int>(4, 6);
    lines[5] = nct::Vector2D<unsigned int>(6, 7);
    lines[6] = nct::Vector2D<unsigned int>(7, 5);
    lines[7] = nct::Vector2D<unsigned int>(5, 4);
    lines[8] = nct::Vector2D<unsigned int>(0, 4);
    lines[9] = nct::Vector2D<unsigned int>(1, 5);
    lines[10]= nct::Vector2D<unsigned int>(2, 6);
    lines[11]= nct::Vector2D<unsigned int>(3, 7);

    nct::Array<nct::color::RgbColor> colors(nPoints, color_);

    // Create buffers.
    vertexBuffer_.create();
    vertexBuffer_.bind();
    vertexBuffer_.allocate(vertices.data(), static_cast<int>(sizeof(nct::Point3D) * vertices.size()));

    normalBuffer_.create();
    normalBuffer_.bind();
    normalBuffer_.allocate(normals.data(), static_cast<int>(sizeof(nct::Vector3D<double>) * normals.size()));

    colorBuffer_.create();
    colorBuffer_.bind();
    colorBuffer_.allocate(colors.data(), static_cast<int>(sizeof(nct::color::RgbColor) * colors.size()));

    triangleBuffer_ = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    triangleBuffer_.create();
    triangleBuffer_.bind();
    triangleBuffer_.allocate(triangles.data(),
        static_cast<int>(sizeof(nct::Vector3D<unsigned int>) * triangles.size()));

    lineBuffer_ = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    lineBuffer_.create();
    lineBuffer_.bind();
    lineBuffer_.allocate(lines.data(),
        static_cast<int>(sizeof(nct::Vector2D<unsigned int>) * lines.size()));

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
void qt_tools::graphics_3d::VoxelizedObject::clear()
{
    geometryOk_ = false;
    pointSize_ = 1.0;
    lineWidth_ = 1.0;

    voxels_.clear();
    scales_.clear();
    centersX_.clear();
    centersY_.clear();
    centersZ_.clear();
    
    triangleBuffer_.destroy();
    lineBuffer_.destroy();
    vertexBuffer_.destroy();
    normalBuffer_.destroy();
    colorBuffer_.destroy();
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::VoxelizedObject::drawFaces(QOpenGLShaderProgram& program)
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
    auto nv = voxels_.size();
    for (index_t v = 0; v<nv; v++) {
        QMatrix4x4 model;
        model.setToIdentity();
        model.scale(scales_[0], scales_[1], scales_[2]);
        model.translate(centersX_[voxels_[v][0]] / scales_[0],
            centersY_[voxels_[v][1]] / scales_[1],
            centersZ_[voxels_[v][2]] / scales_[2]);

        program.setUniformValue("modelMatrix", model);
        program.setUniformValue("normalMatrix", model.normalMatrix());
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(36), GL_UNSIGNED_INT, 0);
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
void qt_tools::graphics_3d::VoxelizedObject::drawLines(QOpenGLShaderProgram& program)
{
    // Verify whether the object was initialized previously.
    if (!geometryOk_)
        return;

    lineBuffer_.bind();

    vertexBuffer_.bind();
    int vertexLocation = program.attributeLocation("vertexPosition");
    program.enableAttributeArray(vertexLocation);
    program.setAttributeBuffer(vertexLocation, GL_DOUBLE, 0, 3, 0);

    colorBuffer_.bind();
    int colorLocation = program.attributeLocation("vertexColor");
    program.enableAttributeArray(colorLocation);
    program.setAttributeBuffer(colorLocation, GL_DOUBLE, 0, 3, 0);

    // Set culling properties
    glDisable(GL_CULL_FACE);

    // Draw shape.
    auto nv = voxels_.size();
    for (index_t v = 0; v<nv; v++) {
        QMatrix4x4 model;
        model.setToIdentity();
        model.scale(scales_[0], scales_[1], scales_[2]);
        model.translate(centersX_[voxels_[v][0]] / scales_[0],
            centersY_[voxels_[v][1]] / scales_[1],
            centersZ_[voxels_[v][2]] / scales_[2]);

        program.setUniformValue("modelMatrix", model);
        program.setUniformValue("normalMatrix", model.normalMatrix());
        glDrawElements(GL_LINES, static_cast<GLsizei>(24), GL_UNSIGNED_INT, 0);
    }

    // Disable vertex arrays.
    program.disableAttributeArray(vertexLocation);
    program.disableAttributeArray(colorLocation);

    // Check for errors.
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
        throw nct::OperationException(std::string(exc_error_drawing_object) +
            std::to_string(err), SOURCE_INFO);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::VoxelizedObject::drawPoints(QOpenGLShaderProgram& program)
{
    // Verify whether the object was initialized previously.
    if (!geometryOk_)
        return;

    vertexBuffer_.bind();
    int vertexLocation = program.attributeLocation("vertexPosition");
    program.enableAttributeArray(vertexLocation);
    program.setAttributeBuffer(vertexLocation, GL_DOUBLE, 0, 3, 0);

    colorBuffer_.bind();
    int colorLocation = program.attributeLocation("vertexColor");
    program.enableAttributeArray(colorLocation);
    program.setAttributeBuffer(colorLocation, GL_DOUBLE, 0, 3, 0);

    // Set culling properties
    glDisable(GL_CULL_FACE);

    // Draw shape.
    auto nv = voxels_.size();
    for (index_t v = 0; v<nv; v++) {
        QMatrix4x4 model;
        model.setToIdentity();
        model.scale(scales_[0], scales_[1], scales_[2]);
        model.translate(centersX_[voxels_[v][0]] / scales_[0],
            centersY_[voxels_[v][1]] / scales_[1],
            centersZ_[voxels_[v][2]] / scales_[2]);

        program.setUniformValue("modelMatrix", model);
        program.setUniformValue("normalMatrix", model.normalMatrix());

        glDrawArrays(GL_POINTS, 0, 24);
    }

    // Disable vertex arrays.
    program.disableAttributeArray(vertexLocation);
    program.disableAttributeArray(colorLocation);

    // Check for errors.
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
        throw nct::OperationException(std::string(exc_error_drawing_object) +
            std::to_string(err), SOURCE_INFO);
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
