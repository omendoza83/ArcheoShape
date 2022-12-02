//=================================================================================================================
/**
 *  @file       Graphics3DWidget.cpp
 *  @brief      qt_tools::graphics_3d::Graphics3DWidget class implementation file.
 *  @details    This file contains the implementation of the qt_tools::graphics_3d::Graphics3DWidget class.
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
#include <qt_tools/graphics_3d/Graphics3DWidget.h>

#include <QtOpenGL/QtOpenGL>

//=================================================================================================================
//        FRAGMENT SHADERS
//=================================================================================================================

/** Fragment shader for difuse lighting. */
inline constexpr const char* diffuseLighting{
"// Transformation matrices\n"
"uniform mat3 normalMatrix;"
"uniform mat4 modelMatrix;"
"uniform vec3 cameraPosition;"

"// Lighting properties\n"
"uniform bool useLighting;"
"uniform float modelLighting;"
"uniform vec4 lightingColor;"
"uniform vec3 lightingPosition;"
"uniform vec4 ambientLightingColor;"
"uniform vec4 specularLightingColor;"
"uniform float shininess;"
"uniform float attenuation;"

"// Fragment properties\n"
"varying vec4 fragmentColor;"
"varying vec3 fragmentPosition;"
"varying vec3 fragmentNormal;"

"// Main function\n"
"void main()"
"{"
"    if (useLighting) {"
"        // Use lighting model\n"

"        vec3 normal = normalize(normalMatrix * fragmentNormal);"
"        vec3 surfacePos = vec3(modelMatrix * vec4(fragmentPosition, 1));"
"        vec3 surfaceToLight = normalize(lightingPosition - surfacePos);"
"        vec3 surfaceToCamera = normalize(cameraPosition - surfacePos);"
"        vec3 ambient = vec3(fragmentColor * ambientLightingColor);"
"        float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));"
"        vec3 diffuse = diffuseCoefficient * fragmentColor.rgb * lightingColor.rgb;"
"        float specularCoefficient = 0.0;"

"        if (diffuseCoefficient > 0.0)"
"            specularCoefficient = pow(max(0.0, dot(surfaceToCamera,"
"                reflect(-surfaceToLight, normal))), shininess);"

"        vec3 specular = specularCoefficient * vec3(specularLightingColor * lightingColor);"
"        float distanceToLight = length(lightingPosition - surfacePos);"
"        float attenuationFactor = 1.0 / (1.0 + attenuation * pow(distanceToLight, float(2)));"

"        vec3 linearColor = ambient + attenuationFactor * (diffuse + specular);"
"        vec3 gamma = vec3(1.0 / 2.2);"
"        gl_FragColor = modelLighting * vec4(pow(linearColor, gamma), fragmentColor.a);"
"    }"
"    else {"
"        // No lighting, just use the fragment color\n"
"        gl_FragColor = modelLighting * fragmentColor;"
"    }"
"}"};

//=================================================================================================================
//        VERTEX SHADERS
//=================================================================================================================

/** Vertex shader for standard models. */
inline constexpr const char* modelGeometry{
"// Transformation matrices\n"
"uniform mat4 modelMatrix;"
"uniform mat4 cameraMatrix;"

"// Vertex properties\n"
"attribute vec4 vertexColor;"
"attribute vec3 vertexPosition;"
"attribute vec3 vertexNormal;"

"// Variables that are interpolated\n"
"varying vec4 fragmentColor;"
"varying vec3 fragmentPosition;"
"varying vec3 fragmentNormal;"

"// Main function\n"
"void main()"
"{"
"    fragmentColor = vertexColor;"
"    fragmentPosition = vertexPosition;"
"    fragmentNormal = vertexNormal;"
"    gl_Position = cameraMatrix * modelMatrix * vec4(vertexPosition, 1);"
"}"};

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
qt_tools::graphics_3d::Graphics3DWidget::Graphics3DWidget(QWidget* parent,
    Qt::WindowFlags f) : QOpenGLWidget{parent, f}
{
    // Initialize basic variables.
    keyboardOn_ = true;
    mouseOn_ = true;
    objects_.clear();
    projection_.setToIdentity();

    // Variables that control the position of the camera.
    mouseRotation_ = false;
    mouseLastPosition_ = QPoint(0,0);
    cameraPosition_ = QVector3D(0,0,2);
    targetPosition_ = QVector3D(0,0,0);
    upDirection_ = QVector3D(0,1,0);    
    
    // Variables that control de lighting.
    ambientLightingColor_ = QVector4D(0.2f, 0.2f, 0.2f, 1);
    cameraLightingColor_ = QVector4D(1.0f, 1.0f, 1.0f, 1);
    specularLightingColor_ = QVector4D(1.0f, 1.0f, 1.0f, 1);
    materialShininess_ = 20.0f;
    lightingAttenuation_ = 0.25f;
    
    // Variables that control the elements rendered into the scene.
    drawPoints_ = false;
    drawLines_ = false;
    fillFaces_ = true;            
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::addShape(
    const std::shared_ptr<graphics_3d::Object3D>& obj3D)
{
    if (obj3D == nullptr)
        throw nct::NullPointerException("obj3D", SOURCE_INFO);

    for (int i=0; i<objects_.count(); i++) {
        if (obj3D==objects_[i])
            return;
    }

    objects_.push_back(obj3D);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::removeShape(
    const std::shared_ptr<graphics_3d::Object3D>& obj3D)
{
    if (obj3D == nullptr)
        throw nct::NullPointerException("obj3D", SOURCE_INFO);

    for (int i=0; i<objects_.count(); i++) {
        if (obj3D==objects_[i]) {
            objects_.removeAt(i);
            break;
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::removeShapes()
{
    objects_.clear();
}

//-----------------------------------------------------------------------------------------------------------------
bool qt_tools::graphics_3d::Graphics3DWidget::keyboardEnabled() const noexcept
{
    return keyboardOn_;
}

//-----------------------------------------------------------------------------------------------------------------
bool qt_tools::graphics_3d::Graphics3DWidget::mouseEnabled() const noexcept
{
    return mouseOn_;
}

//-----------------------------------------------------------------------------------------------------------------
const QVector3D& qt_tools::graphics_3d::Graphics3DWidget::cameraPosition() const noexcept
{
    return cameraPosition_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::setCameraPosition(const QVector3D& pos)
{
    cameraPosition_ = pos;
}

//-----------------------------------------------------------------------------------------------------------------
const QVector3D& qt_tools::graphics_3d::Graphics3DWidget::targetPosition() const noexcept
{
    return targetPosition_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::setTargetPosition(const QVector3D& pos)
{
    targetPosition_ = pos;
}

//-----------------------------------------------------------------------------------------------------------------
const QVector3D& qt_tools::graphics_3d::Graphics3DWidget::upDirection() const noexcept
{
    return upDirection_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::setUpDirection(const QVector3D& direction)
{
    upDirection_ =  direction;
}

//-----------------------------------------------------------------------------------------------------------------
const QVector4D& qt_tools::graphics_3d::Graphics3DWidget::ambientLightingColor() const noexcept
{
    return ambientLightingColor_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::setAmbientLightingColor(const QVector4D& color)
{
    if ((color[0]<0.0) || (color[0]>1.0) ||
        (color[1]<0.0) || (color[1]>1.0) ||
        (color[2]<0.0) || (color[2]>1.0) ||
        (color[3]<0.0) || (color[3]>1.0))
        throw nct::ArgumentException("color", exc_bad_color_object, SOURCE_INFO);
    ambientLightingColor_ = color;
}

//-----------------------------------------------------------------------------------------------------------------
const QVector4D& qt_tools::graphics_3d::Graphics3DWidget::cameraLightingColor() const noexcept
{
    return cameraLightingColor_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::setCameraLightingColor(const QVector4D& color)
{
    if ((color[0]<0.0) || (color[0]>1.0) ||
        (color[1]<0.0) || (color[1]>1.0) ||
        (color[2]<0.0) || (color[2]>1.0) ||
        (color[3]<0.0) || (color[3]>1.0))
        throw nct::ArgumentException("color", exc_bad_color_object, SOURCE_INFO);
    cameraLightingColor_ = color;
}

//-----------------------------------------------------------------------------------------------------------------
const QVector4D& qt_tools::graphics_3d::Graphics3DWidget::specularLightingColor() const noexcept
{
    return specularLightingColor_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::setSpecularLightingColor(const QVector4D& color)
{
    if ((color[0]<0.0) || (color[0]>1.0) ||
        (color[1]<0.0) || (color[1]>1.0) ||
        (color[2]<0.0) || (color[2]>1.0) ||
        (color[3]<0.0) || (color[3]>1.0))
        throw nct::ArgumentException("color", exc_bad_color_object, SOURCE_INFO);
    specularLightingColor_ = color;
}

//-----------------------------------------------------------------------------------------------------------------
float qt_tools::graphics_3d::Graphics3DWidget::shininess() const noexcept
{
    return materialShininess_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::setShininess(float val)
{
    if (val < 0)
        throw nct::ArgumentException("val", val, 0.0, 
            nct::RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);
    materialShininess_ = val;
}

//-----------------------------------------------------------------------------------------------------------------
float qt_tools::graphics_3d::Graphics3DWidget::attenuation() const noexcept
{
    return lightingAttenuation_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::setAttenuation(float val)
{
    if (val < 0)
        throw nct::ArgumentException("val", val, 0.0,
            nct::RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);
    lightingAttenuation_ = val;
}

//-----------------------------------------------------------------------------------------------------------------
bool qt_tools::graphics_3d::Graphics3DWidget::fillFacesEnabled() const noexcept
{
    return fillFaces_;
}

//-----------------------------------------------------------------------------------------------------------------
bool qt_tools::graphics_3d::Graphics3DWidget::drawLinesEnabled() const noexcept
{
    return drawLines_;
}

//-----------------------------------------------------------------------------------------------------------------
bool qt_tools::graphics_3d::Graphics3DWidget::drawPointsEnabled() const noexcept
{
    return drawPoints_;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::initializeGL()
{
    initializeOpenGLFunctions();
    if ((!hasOpenGLFeature(QOpenGLFunctions::OpenGLFeature::Buffers)) ||
        (!hasOpenGLFeature(QOpenGLFunctions::OpenGLFeature::Framebuffers)))
        throw nct::InitializationException(SOURCE_INFO);

    // Allow depth testing (This enables the Z-buffer).
    glEnable(GL_DEPTH_TEST);
    auto err = glGetError();
    if (err != GL_NO_ERROR)
        throw nct::OperationException(std::string(exc_error_in_glenable) + 
        std::to_string(err), SOURCE_INFO);

    // Set clear color to black.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    err = glGetError();
    if (err != GL_NO_ERROR)
        throw nct::OperationException(std::string(exc_error_in_glClearColor) + 
        std::to_string(err), SOURCE_INFO);

    // Set flags.
    glEnable(GL_POINT_SMOOTH);
    err = glGetError();
    if (err != GL_NO_ERROR)
        throw nct::OperationException(std::string(exc_error_in_glenable) + 
        std::to_string(err), SOURCE_INFO);

    glEnable(GL_LINE_SMOOTH);
    err = glGetError();
    if (err != GL_NO_ERROR)
        throw nct::OperationException(std::string(exc_error_in_glenable) + 
        std::to_string(err), SOURCE_INFO);

    glEnable(GL_POLYGON_SMOOTH);
    err = glGetError();
    if (err != GL_NO_ERROR)
        throw nct::OperationException(std::string(exc_error_in_glenable) + 
        std::to_string(err), SOURCE_INFO);

    // Initialize shaders.
    if (!shaderProgram_.isLinked()) {
        shaderProgram_.removeAllShaders();
        if (!shaderProgram_.addShaderFromSourceCode(QOpenGLShader::Vertex, modelGeometry))
            throw nct::OperationException(exc_error_initializing_vertex_shader, SOURCE_INFO);

        if (!shaderProgram_.addShaderFromSourceCode(QOpenGLShader::Fragment, diffuseLighting))
            throw nct::OperationException(exc_error_initializing_fragment_shader, SOURCE_INFO);

        // Link shader pipeline
        if (!shaderProgram_.link())
            throw nct::OperationException(exc_error_linking_shaders, SOURCE_INFO);

        // Bind shader pipeline for use
        if (!shaderProgram_.bind())
            throw nct::OperationException(exc_error_linking_shaders, SOURCE_INFO);
    }
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    // Configure projection matix.
    projection_.setToIdentity();
    projection_.perspective(60.0f, static_cast<float>(w) / static_cast<float>(h), 1.0f, 100.0f);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::paintGL()
{
    ////////// Clear the buffer with the current clearing color //////////
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    ////////// Calculate Movel-View matrix //////////

    // Vector from center point to eye point.
    QVector3D ff = targetPosition_ - cameraPosition_;
    ff.normalize();

    // Normalize up vector.
    QVector3D u = upDirection_.normalized();
    
    // Right vector.
    QVector3D s = QVector3D::crossProduct(ff, u);

    // Create model view matrix.
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    auto normalMatrix = modelMatrix.normalMatrix();

    QMatrix4x4 viewMatrix(
        s[0], s[1], s[2], 0,
        u[0], u[1], u[2], 0,
        -ff[0], -ff[1], -ff[2], 0,
        0, 0, 0, 1);
    viewMatrix.translate(-cameraPosition_[0], -cameraPosition_[1], -cameraPosition_[2]);
    
    ////////// Set variables of shader program //////////
    shaderProgram_.setUniformValue("cameraMatrix", projection_*viewMatrix);
    shaderProgram_.setUniformValue("cameraPosition", cameraPosition_);
    shaderProgram_.setUniformValue("modelLighting", 1.f);
    shaderProgram_.setUniformValue("lightingPosition", cameraPosition_);
    shaderProgram_.setUniformValue("attenuation", lightingAttenuation_);
    shaderProgram_.setUniformValue("shininess", materialShininess_);
    shaderProgram_.setUniformValue("ambientLightingColor", ambientLightingColor_);
    shaderProgram_.setUniformValue("lightingColor", cameraLightingColor_);
    shaderProgram_.setUniformValue("specularLightingColor", specularLightingColor_);

    ////////// Draw objects //////////    
    for (int i=0; i<objects_.size(); i++) {
        if (objects_[i] != nullptr) {            
            shaderProgram_.setUniformValue("modelMatrix", modelMatrix);
            shaderProgram_.setUniformValue("normalMatrix", normalMatrix);            
            
            if (!objects_[i]->isReady())
                objects_[i]->initialize();            

            if (fillFaces_) {
                shaderProgram_.setUniformValue("useLighting", true);
                objects_[i]->drawFaces(shaderProgram_);
            }

            if (drawLines_) {
                shaderProgram_.setUniformValue("useLighting", false);
                objects_[i]->drawLines(shaderProgram_);
            }

            if (drawPoints_) {
                shaderProgram_.setUniformValue("useLighting", false);
                objects_[i]->drawPoints(shaderProgram_);
            }
        }    
    }
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::paintEvent(QPaintEvent* e)
{
    QOpenGLWidget::paintEvent(e);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::keyPressEvent(QKeyEvent* e)
{
    if (!keyboardOn_)
        return;

    switch (e->key()) {
        case Qt::Key_Q:
            materialShininess_+=0.05f;
            if (materialShininess_>20)
                materialShininess_ = 20;
            update();
            break;

        case Qt::Key_W:
            materialShininess_-=0.05f;
            if (materialShininess_<0)
                materialShininess_ = 0;
            update();
            break;

        case Qt::Key_E:
            lightingAttenuation_+=0.05f;
            if (lightingAttenuation_>20)
                lightingAttenuation_ = 20;
            update();
            break;

        case Qt::Key_R:
            lightingAttenuation_-=0.05f;
            if (lightingAttenuation_<0)
                lightingAttenuation_ = 0;
            update();
            break;

        case Qt::Key_A:
            ambientLightingColor_ = QVector4D(1.0f, 1.0f, 1.0f, 1.0f);
            update();
            break;

        case Qt::Key_S:
            ambientLightingColor_ = QVector4D(0.0f, 0.0f, 0.0f, 1.0f);
            update();
            break;

        case Qt::Key_D:
            cameraLightingColor_ = QVector4D(1.0f, 1.0f, 1.0f, 1.0f);
            update();
            break;

        case Qt::Key_F:
            cameraLightingColor_ = QVector4D(0.0f, 0.0f, 0.0f, 1.0f);
            update();
            break;

        case Qt::Key_Z:
            fillFaces_ = !fillFaces_;        
            update();
            break;

        case Qt::Key_X:
            drawLines_ = !drawLines_;        
            update();
            break;

        case Qt::Key_C:
            drawPoints_ = !drawPoints_;    
            update();
            break;

        case Qt::Key_V:
            resetScene();    
            update();
            break;

        case Qt::Key_B:
            resetCamera();    
            update();
            break;

        case Qt::Key_N:
            resetLighting();    
            update();
            break;

        default:
            break;
    }

    QOpenGLWidget::keyPressEvent(e);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::keyReleaseEvent(QKeyEvent* e)
{
    QOpenGLWidget::keyReleaseEvent(e);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::mouseMoveEvent(QMouseEvent* e)
{
    if (!mouseOn_)
        return;

    if (mouseRotation_) {
        mouseRotation_ = false;        
        auto mPos = e->pos();
        
        // Calculate inverse of mvp matrix.
        QVector3D ff = (targetPosition_ - cameraPosition_).normalized();
        QVector3D u = upDirection_.normalized();
        QVector3D s = QVector3D::crossProduct(ff, u);
        QMatrix4x4 modelViewMatrix(s[0], s[1], s[2], 0,
        u[0], u[1], u[2], 0, -ff[0], -ff[1], -ff[2], 0, 0, 0, 0, 1);
        modelViewMatrix.translate(-cameraPosition_[0], -cameraPosition_[1], -cameraPosition_[2]);

        bool iok = true;
        auto imvp = (projection_*modelViewMatrix).inverted(&iok);

        // Calculate points in the real space.
        if (iok) {
            auto w = width();
            auto h = height();

            double x0 = 2.0 * mouseLastPosition_.x() / static_cast<double>(w) - 1;
            double y0 = -2.0 * mouseLastPosition_.y() / static_cast<double>(h) + 1;
            double z0 = 1;
            auto p0 = imvp.mapVector(QVector3D(x0, y0, z0));

            double x1 = 2.0 * mPos.x() / static_cast<double>(w) - 1;
            double y1 = -2.0 * mPos.y() / static_cast<double>(h) + 1;
            double z1 = 1;
            auto p1 = imvp.mapVector(QVector3D(x1, y1, z1));

            QVector3D diff = p1 - p0;
            QVector3D newC = cameraPosition_ - 2.5*cameraPosition_.length()*diff;
            newC.normalize();
            newC = cameraPosition_.length()*newC;
            cameraPosition_ = newC;

            ff = (targetPosition_ - cameraPosition_).normalized();
            u = upDirection_.normalized();
            s = QVector3D::crossProduct(ff, u);
            upDirection_ = QVector3D::crossProduct(s, ff);

            update();
        }
        
        mouseLastPosition_ = mPos;
        mouseRotation_ = true;
    }
    QOpenGLWidget::mouseMoveEvent(e);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::mousePressEvent(QMouseEvent* e)
{
    if (!mouseOn_)
        return;

    switch (e->button()) {
        case Qt::LeftButton: {
                mouseRotation_ = true;
                mouseLastPosition_ = e->pos();        
            }
            break;
        case Qt::RightButton:
            break;
        case Qt::MiddleButton:
            break;
        case Qt::NoButton:
            break;
        default:
            //Do nothing.
            break;
    }
    QOpenGLWidget::mousePressEvent(e);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::mouseReleaseEvent(QMouseEvent* e)
{
    if (!mouseOn_)
        return;

    switch (e->button()) {
        case Qt::LeftButton:
            mouseRotation_ = false;
            break;
        case Qt::RightButton:
            break;
        case Qt::MiddleButton:
            break;
        case Qt::NoButton:
            break;
        default:
            //Do nothing.
            break;
    }    
    QOpenGLWidget::mouseReleaseEvent(e);
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::wheelEvent(QWheelEvent* e)
{
    if (!mouseOn_)
        return;

    auto l = cameraPosition_.length();
    l += (-e->angleDelta().y() / 480.0);
    if (l<=0)
        l = 0.00001f;
    cameraPosition_ = cameraPosition_.normalized() * l;
    
    update();

    QOpenGLWidget::wheelEvent(e);
}

//=================================================================================================================
//        SLOTS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::resetScene()
{
    objects_.clear();
    resetCamera();
    resetLighting();
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::resetLighting()
{
    ambientLightingColor_ = QVector4D(0.2f, 0.2f, 0.2f, 1);
    cameraLightingColor_ = QVector4D(1.0f, 1.0f, 1.0f, 1);
    specularLightingColor_ = QVector4D(0.1f, 0.1f, 0.1f, 1);
    materialShininess_ = 20.0f;
    lightingAttenuation_ = 0.25f;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::resetCamera()
{
    mouseRotation_ = false;
    mouseLastPosition_ = QPoint(0,0);
    cameraPosition_ = QVector3D(0,0,2);
    targetPosition_ = QVector3D(0,0,0);
    upDirection_ = QVector3D(0,1,0);    
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::setKeyboardEnabled(bool enabled)
{
    keyboardOn_ = enabled;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::setKeyboardDisabled(bool disabled)
{
    keyboardOn_ = !disabled;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::setMouseEnabled(bool enabled)
{
    mouseOn_ = enabled;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::setMouseDisabled(bool disabled)
{
    mouseOn_ = !disabled;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::setFillFacesEnabled(bool enabled)
{
    fillFaces_ = enabled;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::setDrawLinesEnabled(bool enabled)
{
    drawLines_ = enabled;
}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Graphics3DWidget::setDrawPointsEnabled(bool enabled)
{
    drawPoints_ = enabled;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
