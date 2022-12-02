//=================================================================================================================
/**
 *  @file       Graphics3DWidget.h
 *  @brief      qt_tools::graphics_3d::Graphics3DWidget class.
 *  @details    Declaration of the qt_tools::graphics_3d::Graphics3DWidget class. 
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

#ifndef QT_TOOLS_GRAPHICS_3D_WIDGET_H_INCLUDE
#define QT_TOOLS_GRAPHICS_3D_WIDGET_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <qt_tools/qt_tools.h>
#include <nct/nct_exception.h>
#include <qt_tools/graphics_3d/Object3D.h>

#include <QtCore/QList>
#include <QtGui/QMatrix4x4>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>

#include <QtOpenGL/QtOpenGL>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>

//=================================================================================================================
namespace qt_tools {
/**
 *  @brief      Graphics 3D namespace.
 *  @details    This namespaces contains classes and functions to manipulate and show 3D scenes.
 */
namespace graphics_3d {

/**
 *  @brief      Graphics 3D widget class.
 *  @details    This class is a widget for rendering basic 3D shapes. The class also provides
 *              a camera that can be manipulated with the mouse, and three lighting types:
 *              ambient lighting, difuse lighting and specular lighting.
 */
class QT_TOOLS_EXPIMP Graphics3DWidget : public QOpenGLWidget, protected QOpenGLFunctions {

    Q_OBJECT

public:

    ////////// Constructors //////////

    /**
     *  @brief      Class constructor.
     *  @details    Contructs an Graphics3DWidget with default rendering options.
     *  @param[in]  parent  The parent widget.
     *  @param[in]  f  Window-system properties of the widget. 
     */
    Graphics3DWidget(QWidget* parent = 0, Qt::WindowFlags f = Qt::WindowFlags());
    
    /**
     *  @brief      Copy constructor.
     *  @details    This constructor is deleted.
     */
    Graphics3DWidget(const Graphics3DWidget&) = delete;
    
    /**
     *  @brief      Move constructor.
     *  @details    This constructor is deleted.
     */
    Graphics3DWidget(Graphics3DWidget&&) = delete;
    
    ////////// Destructor //////////

    /**
     *  @brief      Destructor.
     *  @details    Class destructor. 
     */
    ~Graphics3DWidget() = default;

    ////////// Operators //////////
    
    /**
     *  @brief      Assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    Graphics3DWidget& operator=(const Graphics3DWidget&) = delete;
    
    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    Graphics3DWidget& operator=(Graphics3DWidget&&) = delete;

    ////////// Member functions //////////

    /**
     *  @brief      Add 3D shape.
     *  @details    This function adds a 3D object to the scene. Before rendering the scene,
     *              it's necesary to call the initializeGl method.
     *  @param[in]  obj3D  The new object to render in the scene.
     */
    void addShape(const std::shared_ptr<graphics_3d::Object3D>& obj3D);

    /**
     *  @brief      Remove 3D shape.
     *  @details    This function removes a 3D object from the scene. 
     *  @param[in]  obj3D  The object to be removed.
     */
    void removeShape(const std::shared_ptr<graphics_3d::Object3D>& obj3D);

    /**
     *  @brief      Clean shapes.
     *  @details    This function removes all the 3D objects that are rendered in the scene.
     */
    void removeShapes();

    /**
     *  @brief      Keyboard enabled.
     *  @details    This function returns whether the keyboard events are enabled.
     *  @returns    True if the keyboard events are enabled, false otherwise.
     */
    bool keyboardEnabled() const noexcept;

    /**
     *  @brief      Mouse enabled.
     *  @details    This function returns whether the mouse events are enabled.
     *  @returns    True if the mouse events are enabled, false otherwise.
     */
    bool mouseEnabled() const noexcept;

    /**
     *  @brief      Camera position.
     *  @details    This function returns the current position of the camera.
     *  @returns    The current position of the camera.
     */
    const QVector3D& cameraPosition() const noexcept;

    /**
     *  @brief      Set camera position.
     *  @details    This function modifies the current position of the camera.
     *  @param[in]  pos  The new position.
     */
    void setCameraPosition(const QVector3D& pos);

    /**
     *  @brief      Target position.
     *  @details    This function returns the current target position (origin) of the coordinate system.
     *  @returns    The current target position.
     */
    const QVector3D& targetPosition() const noexcept;

    /**
     *  @brief      Set target position.
     *  @details    This function modifies the current target position (origin) of the coordinate system.
     *  @param[in]  pos  The new position.
     */
    void setTargetPosition(const QVector3D& pos);

    /**
     *  @brief      Up direction.
     *  @details    This function returns the current vector that indicates the up direction.
     *  @returns    The current up direction.
     */
    const QVector3D& upDirection() const noexcept;

    /**
     *  @brief      Set up direction.
     *  @details    This function modifies the current vector that indicates the up direction.
     *  @param[in]  direction  The new direction.
     */
    void setUpDirection(const QVector3D& direction);

    /**
     *  @brief      Ambient lighting color.
     *  @details    This function returns the color of the ambient lighting.
     *  @returns    The color of the ambient lighting.
     */
    const QVector4D& ambientLightingColor() const noexcept;

    /**
     *  @brief      Set ambient lighting color.
     *  @details    This function sets the color of the ambient lighting.
     *  @param[in]  color  The new color of the ambient lighting.
     */
    void setAmbientLightingColor(const QVector4D& color);

    /**
     *  @brief      Camera lighting color.
     *  @details    This function returns the color of the camera lighting.
     *  @returns    The color of the camera lighting.
     */
    const QVector4D& cameraLightingColor() const noexcept;

    /**
     *  @brief      Set camera lighting color.
     *  @details    This function sets the color of the camera lighting.
     *  @param[in]  color  The new color of the camera lighting.
     */
    void setCameraLightingColor(const QVector4D& color);

    /**
     *  @brief      Specular lighting color.
     *  @details    This function returns the color of the specular lighting.
     *  @returns    The specular lighting color.
     */
    const QVector4D& specularLightingColor() const noexcept;

    /**
     *  @brief      Set specular lighting color.
     *  @details    This function sets the color of the specular lighting.
     *  @param[in]  color  The new specular lighting color.
     */
    void setSpecularLightingColor(const QVector4D& color);

    /**
     *  @brief      Shininess.
     *  @details    This function returns the of the shininess that is used to represent the specular lighting.
     *  @returns    The value of the shininess.
     */
    float shininess() const noexcept;

    /**
     *  @brief      Set shininess.
     *  @details    This function sets the value of the shininess that is used to represent the specular lighting.
     *  @param[in]  val  New value of the shininess.
     */
    void setShininess(float val);

    /**
     *  @brief      Attenuation factor.
     *  @details    This function returns the of the attenuation that is used to represent the diffuse lighting.
     *  @returns    The value of the shininess.
     */
    float attenuation() const noexcept;

    /**
     *  @brief      Set attenuation factor.
     *  @details    This function sets the value of the attenuation factor that is used to represent the diffuse
     *              lighting.
     *  @param[in]  val  New value of the attenuation factor.
     */
    void setAttenuation(float val);

    /**
     *  @brief      Fill faces flag.
     *  @details    This function returns if the faces of the triangular mesh are filled.
     *  @returns    True if the faces of the triangular mesh are filled.
     */
    bool fillFacesEnabled() const noexcept;

    /**
     *  @brief      Draw object lines flag.
     *  @details    This function returns if the lines of the object are drawn.
     *  @returns    True if the lines of the object are drawn.
     */
    bool drawLinesEnabled() const noexcept;

    /**
     *  @brief      Draw object points flag.
     *  @details    This function returns if the points of the object are drawn.
     *  @returns    True  if the points of the object are drawn.
     */
    bool drawPointsEnabled() const noexcept;

public slots:

    /**
     *  @brief      Reset scene.
     *  @details    This function sets the properties of the scene (camera, lighting, etc.) to the
     *              default configuration and clears the contents of the scene.
     */
    void resetScene();

    /**
     *  @brief      Reset lighting.
     *  @details    This function sets the properties of the lighting to its default
     *              values.
     */
    void resetLighting();

    /**
     *  @brief      Reset camera.
     *  @details    This function sets the properties of the camera to its default
     *              values.
     */
    void resetCamera();

    /**
     *  @brief      Set keyboard enabled.
     *  @details    This function sets whether the keyboard events are enabled/disabled.
     *  @param[in]  enabled  True to enabled the keyboard events.
     */
    void setKeyboardEnabled(bool enabled);

    /**
     *  @brief      Set keyboard disbaled.
     *  @details    This function sets whether the keyboard events are disabled/enabled.
     *  @param[in]  disabled  True to disable the keyboard events.
     */
    void setKeyboardDisabled(bool disabled);

    /**
     *  @brief      Set mouse enabled.
     *  @details    This function sets whether the mouse events are enabled/disabled.
     *  @param[in]  enabled  True to enabled the mouse events.
     */
    void setMouseEnabled(bool enabled);

    /**
     *  @brief      Set mouse disabled.
     *  @details    This function sets whether the mouse events are disabled/enabled.
     *  @param[in]  disabled  True to disable the keyboard events.
     */
    void setMouseDisabled(bool disabled);

    /**
     *  @brief      Set the flag to fill faces.
     *  @details    This function sets whether the faces of the triangular mesh are filled.
     *  @param[in]  enabled  True to fill faces.
     */
    void setFillFacesEnabled(bool enabled);

    /**
     *  @brief      Set the flag to draw lines.
     *  @details    This function sets whether the lines of the object are drawn.
     *  @param[in]  enabled  True to draw lines.
     */
    void setDrawLinesEnabled(bool enabled);

    /**
     *  @brief      Set the flag to draw points.
     *  @details    This function sets whether the points of the object are drawn.
     *  @param[in]  enabled  True to draw points.
     */
    void setDrawPointsEnabled(bool enabled);

protected:

    /**
     *  @brief      Initialize GL object.
     *  @details    This function is called once before the first call to paintGL() or resizeGL(),
     *              and then once whenever the widget has been assigned a new QGLContext.
     */
    void initializeGL() override;

    /**
     *  @brief      Resize widget.
     *  @details    This function is called whenever the widget has been resized. The new size is
     *              passed in width and height.
     *  @param w    New width of the widget.
     *  @param h    New heigh of the widget.
     */
    void resizeGL(int w, int h) override;

    /**
     *  @brief      Paint widget.
     *  @details    This function is called whenever the widget needs to be painted.
     */
    void paintGL() override;

    /**
     *  @brief      Paint widget.
     *  @details    This function handle the paint events of the widget. Will cause the paintGL() 
     *              function to be called.
     *  @param[in]  e  Data poduced in the event.
     */
    void paintEvent(QPaintEvent* e) override;

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
    void keyReleaseEvent(QKeyEvent* e) override;

    /**
     *  @brief      Mouse-move event.
     *  @details    This function is called whenever the mouse is moved over the widget.
     *  @param[in]  e  Object with the information of the event.            
     */
    void mouseMoveEvent(QMouseEvent* e) override;

    /**
     *  @brief      Mouse-press event.
     *  @details    This function is called whenever the mouse is pressed over the widget.
     *  @param[in]  e  Object with the information of the event.            
     */
    void mousePressEvent(QMouseEvent* e) override;

    /**
     *  @brief      Mouse-press event.
     *  @details    This function is called whenever a button of the mouse is released and the
     *              mouse pointer is over the widget.
     *  @param[in]  e  Object with the information of the event.            
     */
    void mouseReleaseEvent(QMouseEvent* e) override;

    /**
     *  @brief      Mouse-wheel event.
     *  @details    This function is called whenever the wheel of the mouse is moved and the mouse
     *              pointer is over the widget.
     *  @param[in]  e  Object with the information of the event.            
     */
    void wheelEvent(QWheelEvent* e) override;

private:

    ////////// Data members //////////        

    QList<std::shared_ptr<graphics_3d::Object3D>> objects_; /**< Objects into the scene.*/

    QOpenGLShaderProgram shaderProgram_;        /**< Open GL program. */

    QMatrix4x4 projection_;                     /**< Projection matrix. */

    // Variables that control the mouse and keyboard events

    bool keyboardOn_ {false};   /**< Keyboard events enabled flag. */

    bool mouseOn_ {false};      /**< Mouse events enabled flag. */

    // Variables that control de camera position

    bool mouseRotation_ {false};    /**< The flag that indicates whether the camera
                                         position is being modified with the mouse. */
    QPoint mouseLastPosition_;      /**< Last position of the pointer on the window. */

    QVector3D cameraPosition_;      /**< Current vector position of the camera. */

    QVector3D targetPosition_;      /**< Position of the reference point (target). */

    QVector3D upDirection_;         /**< Up direction. */

    // Variables that control de lighting

    QVector4D ambientLightingColor_;    /**< Ambient lighting color. */

    QVector4D cameraLightingColor_;     /**< Camera lighting color. */

    QVector4D specularLightingColor_;   /**< Specular color of the objects. */

    float materialShininess_ {0};       /**< Shininess of the objects. */

    float lightingAttenuation_ {0};     /**< Lighting attenuation factor. */

    // Variables that control the rendering

    bool drawPoints_ {false};   /**< True to add the points of the solid. */

    bool drawLines_ {false};    /**< True to add the lines of the solid. */

    bool fillFaces_ {false};    /**< True to fill the mesh. */
};

}}

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
