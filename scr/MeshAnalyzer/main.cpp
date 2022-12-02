//===========================================================================================================
/**
 *  @file       main.cpp
 *  @brief      Mesh analyzer program.
 *  @details    This program analyzes 3D meshes and calculate features that characterize the meshes.
 *  @author     Omar Mendoza Montoya (email: omendoz@live.com.mx).
 *
 *  @copyright  Copyright (c) 2022 Omar Mendoza Montoya. All rights reserved. \n \n
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
//===========================================================================================================

//===========================================================================================================
//        HEADERS AND NAMESPACES
//===========================================================================================================
#include <cstdlib>
#include "MainWindow.h"

using namespace std;

//===========================================================================================================
//        FUNCTIONS
//===========================================================================================================

/**
 *  @brief      Main function.
 *  @details    Function where the program starts execution. 
 *  @param[in]  argc  Number of command-line arguments.
 *  @param[in]  argv  Array with the command-line arguments.
 *  @returns    Exit status of the process.
 */
int main(int argc,char **argv)
{        
    QApplication app(argc, argv);        
    
    // Application window
    MainWindow mainWindow;        
    auto screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    mainWindow.setGeometry((screenGeometry.width()-mainWindow.width())/2, 
        (screenGeometry.height()-mainWindow.height())/2, 
        mainWindow.width(), mainWindow.height());

    // Run the interface    
    mainWindow.show();    
    return app.exec();
}

//===========================================================================================================
//        END OF FILE
//===========================================================================================================

