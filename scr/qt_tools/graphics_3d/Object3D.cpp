//=================================================================================================================
/**
 *  @file       Object3D.cpp
 *  @brief      qt_tools::graphics_3d::Object3D class implementation file.
 *  @details    This file contains the implementation of the qt_tools::graphics_3d::Object3D class.
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
#include <qt_tools/graphics_3d/Object3D.h>

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Object3D::drawFaces(QOpenGLShaderProgram&)
{

}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Object3D::drawLines(QOpenGLShaderProgram&)
{

}

//-----------------------------------------------------------------------------------------------------------------
void qt_tools::graphics_3d::Object3D::drawPoints(QOpenGLShaderProgram&)
{

}

//-----------------------------------------------------------------------------------------------------------------
bool qt_tools::graphics_3d::Object3D::isReady() noexcept
{
    return geometryOk_;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
