//=================================================================================================================
/**
 *  @file       nct_constants.h
 *  @brief      nct constant values.
 *  @details    Declaration file for constant values of the nct namespace.
 *  @author     Omar Mendoza Montoya (email: omendoz@live.com.mx).
 *  @copyright  Copyright (c) 2020 Omar Mendoza Montoya \n \n
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

#ifndef NCT_CONSTANTS_H_INCLUDE
#define NCT_CONSTANTS_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <limits>
#include <complex>

//=================================================================================================================

namespace nct {

////////// Machine constants //////////    

/** Machine epsilon. */
inline constexpr double EPS {std::numeric_limits<double>::epsilon()};

/** Machine epsilon times 100. */
inline constexpr double EPS_100 {100 * std::numeric_limits<double>::epsilon()};

/** Machine epsilon times 1000. */
inline constexpr double EPS_1000 {1000 * std::numeric_limits<double>::epsilon()};

/** Machine epsilon times 10000. */
inline constexpr double EPS_10000 {10000 * std::numeric_limits<double>::epsilon()};

////////// Scale factors //////////

/** Integral base used to represent a double. */
inline constexpr double RADIX {std::numeric_limits<double>::radix};

/** Factor to scale an unsigned long long to the range of [0,1]. */
inline constexpr double UINT64_ESC {1.0 / 0xffffffffffffffffui64};

/** Factor to scale an unsigned int to the range of [0,1]. */
inline constexpr double UINT32_ESC {1.0 / 0xffffffffui32};

/** Factor to scale an unsigned short to the range of [0,1]. */
inline constexpr double UINT16_ESC {1.0 / 0xffffui16};

/** Factor to scale an unsigned char to the range of [0,1]. */
inline constexpr double UINT8_ESC {1.0 / 0xffui8};

////////// Constants that control the execution of numerical algorithms //////////

/**< Small floating point value. */
inline constexpr double SMALL_FP {
    std::numeric_limits<double>::min() / std::numeric_limits<double>::epsilon()};


inline constexpr double PLUS_INF {+1E+100};        /**< Value that represents +inf. */

inline constexpr double MINUS_INF {-1E+100};       /**< Value that represents -inf. */


inline constexpr double ZERO_TOL {0.0};            /**< No tolerance. */

inline constexpr double VERY_SMALL_TOL {1E-64};    /**< Very small tolerance. */

inline constexpr double SMALL_TOL {1E-12};         /**< Small tolerance. */

inline constexpr double MEDIUM_TOL {1E-8};         /**< Medium tolerance. */

inline constexpr double BIG_TOL {1E-4};            /**< Big tolerance. */


inline constexpr double VERY_HIGH_ACC {1E-64};     /**< Very high accuracy. */

inline constexpr double HIGH_ACC {1E-12};          /**< High accuracy. */

inline constexpr double MEDIUM_ACC {1E-8};         /**< Medium accuracy. */

inline constexpr double LOW_ACC {1E-4};            /**< Low accuracy. */


inline constexpr double MICRO_STEP {1E-64};        /**< Micro step. */

inline constexpr double SMALL_STEP {1E-12};        /**< Small step. */

inline constexpr double MEDIUM_STEP {1E-8};        /**< Medimum step. */

inline constexpr double BIG_STEP {1E-4};           /**< Big step. */


////////// Numerical constants //////////

inline constexpr double PI {3.14159265358979323846};                   /**< Pi. */

inline constexpr double TWO_PI {6.28318530717958647693};               /**< 2*Pi. */

inline constexpr double THREE_PI {9.42477796076937971539};             /**< 3*Pi. */

inline constexpr double FOUR_PI {12.5663706143591729539};              /**< 4*Pi. */

inline constexpr double PI_DIV_TWO {1.57079632679489661923};           /**< Pi divided by 2. */

inline constexpr double PI_DIV_THREE {1.04719755119659774615};         /**< Pi divided by 3. */

inline constexpr double PI_DIV_FOUR {0.785398163397448309616};         /**< Pi divided by 4. */

inline constexpr double THREE_PI_DIV_TWO {4.712388980384689857694};    /**< 3*Pi divided by 2. */

inline constexpr double INV_PI {0.318309886183790671538};              /**< Inverse of pi. */

inline constexpr double ONE_DIV_PI {0.318309886183790671538};          /**< Two divided by pi. */

inline constexpr double TWO_DIV_PI {0.636619772367581343076};          /**< Two divided by pi. */

inline constexpr double THREE_DIV_PI {0.954929658551372014613};        /**< Three divided by pi. */

inline constexpr double FOUR_DIV_PI {1.27323954473516268615};          /**< Four divided by pi. */

inline constexpr double SQR_PI {9.86960440108935861883};               /**< Pi*Pi. */

inline constexpr double SQRT_PI {1.77245385090551602730};              /**< Square root of pi. */

inline constexpr double SQRT_TWO_PI {2.50662827463100050242};          /**< Square root of 2*pi. */

inline constexpr double TWO_DIV_SQRT_PI {1.12837916709551257390};      /**< Two divided by the root of pi. */

inline constexpr double INV_SQRT_TWO_PI {0.398942280401432677940};     /**< Inverse of the square root of 2*pi. */

inline constexpr double PI_DIV_SQRT3 {1.81379936423421785059};         /**< Pi divided by the square root of 3. */

inline constexpr double SQRT3_DIV_PI {0.551328895421792049511};        /**< Square root of 3 divided by pi. */

inline constexpr double SQRT2 {1.41421356237309504880};                /**< Square root of 2. */

inline constexpr double INV_SQRT2 {0.707106781186547524401};           /**< Inverse of the square root of 2. */

inline constexpr double SQRT3 {1.73205080756887729353};                /**< Square root of 3. */

inline constexpr double INV_SQRT3 {0.577350269189625764509};           /**< Inverse of the square root of 3. */

inline constexpr double E_1 {2.71828182845904523536};                  /**< e. */

inline constexpr double LOG2_E {1.44269504088896340736};               /**< log_2 e. */

inline constexpr double LOG10_E {0.434294481903251827651};             /**< log_10 e. */

inline constexpr double LN_2 {0.693147180559945309417};                /**< ln 2. */

inline constexpr double LN_10 {2.30258509299404568402};                /**< ln 10. */

inline constexpr std::complex<double> I1 {0, 1};                       /**< Complex i. */

/**< Square root of i. */
inline constexpr std::complex<double> SQRT_I {0.7071067811865475244, 0.7071067811865475244}; 

inline constexpr std::complex<double> CUBERT_I {0.866025403784438646763, 0.5};  /**< Cube root of i. */

}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
