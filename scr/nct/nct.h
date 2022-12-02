//=================================================================================================================
/**
 *  @file       nct.h
 *  @brief      nct namespace.
 *  @details    Declaration file of the nct namespace. This is the main header file of this library.
 *              It contains definitions of data types that are used in different classes and
 *              functions implemented in the library.
 *  @author     Omar Mendoza Montoya (email: omendoz@live.com.mx).
 *  @copyright  Copyright (c) 2010 Omar Mendoza Montoya \n \n
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

#ifndef NCT_H_INCLUDE
#define NCT_H_INCLUDE

////////// Definitions for exporting/importing the library //////////

// NCT_DLL_EXPORT       Use this define to create a DLL for this library.
// NCT_DLL_IMPORT       Use this define to import a DLL of this library.

////////// Macro for DLL exporting and importing //////////
#ifdef NCT_DLL_EXPORT                                
    // Export dll.
    #define NCT_EXP __declspec(dllexport)
    #define NCT_IMP __declspec(dllimport)
    #define NCT_EXPIMP NCT_EXP
#elif NCT_DLL_IMPORT
    // Import dll.
    #define NCT_EXP __declspec(dllexport)
    #define NCT_IMP __declspec(dllimport)
    #define NCT_EXPIMP NCT_IMP
#else
    #define NCT_EXP
    #define NCT_IMP
    #define NCT_EXPIMP 
#endif

////////// Macro that specifies the source of one exception //////////
#if defined(_MSC_VER) && defined(_DEBUG)
    #define SOURCE_INFO ( std::string(__FUNCSIG__) + std::string(" File: ")  \
                        + std::string(__FILE__) + std::string(" Line: ")  \
                        + std::to_string(__LINE__) )
#elif defined(_MSC_VER)
    #define SOURCE_INFO __FUNCSIG__
#else
    #define SOURCE_INFO __PRETTY_FUNCTION__
#endif

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <cmath>
#include <complex>
#include <concepts>
#include <type_traits>

//=================================================================================================================

/**
 *  @brief      Numerical and computational tools library (NCT).
 *  @details    This library contains classes and functions for numerical analysis. The 
 *              algorithms implemented in this library cover the following areas: \n
 *              - Linear algebra. \n
 *              - Numerical differentiation and integration. \n
 *              - Root finding. \n
 *              - Descriptive and inferential statistics. \n
 *              - Numerical optimization. \n
 *              - Signal processing. \n
 *              - Image processing.  \n
 *              - Geometry. \n
 *              - Pattern recognition and machine learning. \n
 *              - Fininte element. \n
 *               Additionally, the library provides helper classes for representing containers and some 
 *               design patterns. \n
 *               The main purpose of this library is merely academic, and it's not optimized for  
 *               comercial applications.
 */
namespace nct {

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

using Complex = std::complex<double>;   /**< Complex number. It is equivalent to std::complex<double>. */

using size_t = std::size_t;         /**< Unsigned integer type used for indexing and allocating memory.
                                         It is equivalent to std::size_t. */
using diff_t = std::ptrdiff_t;      /**< Signed integer type used for representing the difference
                                         between indices. It is equivalent to std::ptrdiff_t. */
using index_t = std::size_t;        /**< Unsigned integer type for subscripting and counting.
                                         It is equivalent to std::size_t. */

////////// Concepts for template constraints //////////

/**
 *  @brief      Signed number type.
 *  @details    Concept for signed numbers: signed integral types and floating-point types.
 *  @tparam     T  The variable type to be tested.
 */
template<typename T>
concept Signed = std::is_signed<T>::value;

/**
 *  @brief      Arithmetic type.
 *  @details    Concept for arithmetic types: integral types and floating-point types.
 *  @tparam     T  The variable type to be tested.
 */
template<typename T>
concept Arithmetic = std::is_arithmetic<T>::value;

/**
 *  @brief      Numeric type.
 *  @details    Concept for numeric types: integral types, floating-point
 *              types and complex type, or custom numeric types.
 *  @tparam     T  The variable type to be tested.
 */
template<typename T>
concept Numeric = Arithmetic<T> || std::same_as<T, Complex> || T::is_numeric;

/**
 *  @brief      Signed numeric type.
 *  @details    Concept for signed numbers: signed integral types, floating-point
 *              types and complex type, or custom numeric types.
 *  @tparam     T  The variable type to be tested.
 */
template<typename T>
concept SignedNumeric = std::is_signed<T>::value || std::same_as<T, Complex> || T::is_signed_numeric;

/**
 *  @brief      Addable type.
 *  @details    Concept for types for whom the operators + and += are well defined.
 *  @tparam     T  The variable type to be tested.
 */
template<typename T>
concept Addable = Numeric<T> || requires (T a, T b) {
    {a + b} -> std::same_as<T>;
    {a += b} -> std::same_as<const T&>;
};

/**
 *  @brief      Substractable type.
 *  @details    Concept for types for whom the operators - and -= are well defined.
 *  @tparam     T  The variable type to be tested.
 */
template<typename T>
concept Substractable = Numeric<T> || requires (T a, T b) {
    {a - b} -> std::same_as<T>;
    {a -= b} -> std::same_as<const T&>;
};

}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
