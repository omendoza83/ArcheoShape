//=================================================================================================================
/**
 *  @file       qt_tools.h
 *  @brief      qt_tools namespace.
 *  @details    Declaration file of the qt_tools namespace. This is the main header file of this library.
 *              It contains basic definitions and data types that are used among the different classes and
 *              functions implemented in the library.
 *  @author     Omar Mendoza Montoya (email: omendoz@live.com.mx).
 *  @copyright  Copyright (c) 2018 Omar Mendoza Montoya \n \n
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

#ifndef QT_TOOLS_H_INCLUDE
#define QT_TOOLS_H_INCLUDE

////////// Definitions that control the behaviour of the library //////////

// QT_TOOLS_DLL_EXPORT       Use this define to create a DLL for this library.
// QT_TOOLS_DLL_IMPORT       Use this define to import a DLL of this library.

////////// Macro for DLL exporting and importing //////////
#ifdef QT_TOOLS_DLL_EXPORT                                
    // Export dll.
    #define QT_TOOLS_EXP __declspec(dllexport)
    #define QT_TOOLS_IMP __declspec(dllimport)
    #define QT_TOOLS_EXPIMP QT_TOOLS_EXP
#elif QT_TOOLS_DLL_IMPORT
    // Import dll.
    #define QT_TOOLS_EXP __declspec(dllexport)
    #define QT_TOOLS_IMP __declspec(dllimport)
    #define QT_TOOLS_EXPIMP QT_TOOLS_IMP
#else
    #define QT_TOOLS_EXP
    #define QT_TOOLS_IMP
    #define QT_TOOLS_EXPIMP 
#endif

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <qt_tools/qt_tools_exception_strings.h>

//=================================================================================================================

/**
 *  @brief      QT tools library.
 *  @details    Complementary library of the NCT and NIT projects. This library contains custom widgets
 *              and helper classes for QT applications. Additionally, some implemented widgets work as
 *              front-ends of some processing modules of the NCT and NIT projects. Finally, this project
 *              contains ploting tools for 2D and 3D data. 
 */
namespace qt_tools {

/**
 *  @brief      Library version.
 *  @details    Namespace that contains information about the library version.
 */
namespace version {

inline constexpr int YEAR {2022};   /**< Year.*/

inline constexpr int MONTH {1};     /**< Month.*/

inline constexpr int DAY {25};      /**< Day.*/

}

////////// Type definitions //////////

using size_t = nct::size_t;         /**< Unsigned integer type used for indexing and allocating memory.
                                         It is equivalent to std::size_t*/
using diff_t = nct::diff_t;         /**< Signed integer type used for representing the difference
                                         between indices. It is equivalent to std::ptrdiff_t. */
using index_t = nct::size_t;        /**< Unsigned integer type for subscripting and counting.
                                         It is equivalent to std::size_t*/
using Complex = nct::Complex;       /**< Complex number class that is used in this library. */

}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
