//=================================================================================================================
/**
 *  @file       Object3D.h
 *  @brief      qt_tools::graphics_3d::Object3D class.
 *  @details    Declaration of the qt_tools::graphics_3d::Object3D class. 
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

#ifndef QT_TOOLS_OBJECT3D_H_INCLUDE
#define QT_TOOLS_OBJECT3D_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <qt_tools/qt_tools.h>
#include <nct/nct_exception.h>

#include <QtOpenGL/QtOpenGL>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>

//=================================================================================================================
namespace qt_tools {
namespace graphics_3d {

/**
 *  @brief      Object3D class.
 *  @details    This abstract class is used to define geometries that are rendered thru OpenGL. In
 *              order to show the geometry, the method draw() must be called. The function initialize()
 *              is used to create the buffers, arrays, etc., that are needed to build the object into
 *              the scene. The constructor DO NOT calls the initialization method, so it's necessary
 *              to call it before using the object (if the specific class need an special
 *              initialization). The function clear() releases the allocated
 *              resources and re-initializes the scene.
 */
class QT_TOOLS_EXPIMP Object3D : protected QOpenGLFunctions {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the default configuration.
     */
    Object3D() = default;
    
    /**
     *  @brief      Copy constructor.
     *  @details    This constructor is deleted.
     */
    Object3D(const Object3D& other) = delete;
    
    /**
     *  @brief      Move constructor.
     *  @details    This constructor is deleted.
     */
    Object3D(Object3D&& other) = delete;
    
    ////////// Destructor //////////

    /**
     *  @brief      Destructor.
     *  @details    Class destructor. 
     */
    virtual ~Object3D() = default;

    ////////// Operators //////////
    
    /**
     *  @brief      Assignment operator.
     *  @details    This operator is deleted.
     *  @returns    A reference to the object.
     */
    Object3D& operator=(const Object3D& other) = delete;
    
    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator is deleted.
     *  @returns    N/A.
     */
    Object3D& operator=(Object3D&& other) = delete;

    ////////// Member functions //////////        

    /**
     *  @brief      Initialize object.
     *  @details    This function is used to allocate memory, bind arrays and create other stuff
     *              needed by the geometry in order to be drawn.
     */
    virtual void initialize() = 0;

    /**
     *  @brief      Release object.
     *  @details    This function is used to clear the resources used by the object. 
     */
    virtual void clear() = 0;

    /**
     *  @brief      Draw faces.
     *  @details    This function draws the faces of the shape. 
     *  @param[in]  program  The program that executes the shader code.
     */
    virtual void drawFaces(QOpenGLShaderProgram& program);

    /**
     *  @brief      Draw lines.
     *  @details    This function draws the lines of the shape. 
     *  @param[in]  program  The program that executes the shader code.
     */
    virtual void drawLines(QOpenGLShaderProgram& program);

    /**
     *  @brief      Draw lines.
     *  @details    This function draws the points of the shape. 
     *  @param[in]  program  The program that executes the shader code.
     */
    virtual void drawPoints(QOpenGLShaderProgram& program);

    /**
     *  @brief      Is the object ready?.
     *  @details    This function indicates whether the object is ready to be drawn in the scene.
     *  @returns    True if the object is ready.
     */
    virtual bool isReady() noexcept;

protected:

    ////////// Data members //////////

    bool geometryOk_ {false};   /**< True to indicate that the object was initialized properly. */

};

}}

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
