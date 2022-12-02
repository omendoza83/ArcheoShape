//=================================================================================================================
/**
 *  @file       math.h
 *  @brief      nct::math namespace.
 *  @details    Declaration of the nct::math namespace.
 *  @author     Omar Mendoza Montoya (email: omendoz@live.com.mx).
 *  @copyright  Copyright (c) 2012 Omar Mendoza Montoya \n \n
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

#ifndef NCT_MATH_H_INCLUDE
#define NCT_MATH_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_constants.h>
#include <nct/nct_exception.h>

#include <vector>

//=================================================================================================================
namespace nct {

////////// Enumerators //////////   

/**
 *  @brief      Classes and functions for mathematical operations.
 *  @details    This namespace contains classes and functions for mathematical operations.
 */
namespace math {

/**
 *  @brief      Threshold types.
 *  @details    Types of threshold operations.
 */
enum class ThresholdType : unsigned char {

    UpperThreshold,     /**< Set to 1 all the items above a limit. */

    LowerThreshold,     /**< Set to 1 all the items below a limit. */

    AbsUpperThreshold,  /**< Set to 1 all the items with absolute value above a limit. */

    AbsLowerThreshold,  /**< Set to 1 all the items with absolute value below a limit. */
};

////////// Mathematical functions for scalar values //////////   

/**
 *  @brief      Absolute value.
 *  @details    This function calculates the absolute value of a real number.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  The number whose absolute value will be calculated.
 *  @returns    The absolute value of the given number.
 */
template<nct::Signed T>
constexpr T absolute(const T& v) noexcept;

/**
 *  @brief      Square of a number.
 *  @details    This function calculates the square of a number.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  The number whose square value is going to be calculated.
 *  @returns    The square of the input number.
 */
template<nct::Numeric T>
constexpr T sqr(const T& v) noexcept;

/**
 *  @brief      Cube of a number.
 *  @details    This function calculates the cube of a number.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  The number whose cube value is going to be calculated.
 *  @returns    The cube of the input number.
 */
template<nct::Numeric T>
constexpr T cube(const T& v) noexcept;

/**
 *  @brief      Fourth power of a number.
 *  @details    This function calculates the fourth power of a number.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  The number whose fourth power is going to be calculated.
 *  @returns    The fourth power of the input number.
 */
template<nct::Numeric T>
constexpr T fourth_pwr(const T& v) noexcept;

/**
 *  @brief      Fifth power of a number.
 *  @details    This function calculates the fifth power of a number.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  The number whose fifth power is going to be calculated.
 *  @returns    The fifth power of the input number.
 */
template<nct::Numeric T>
constexpr T fifth_pwr(const T& v) noexcept;

/**
 *  @brief      Maximun of two numbers.
 *  @details    This function calculates the maximum of two numbers.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v1  The first number to be compared.
 *  @param[in]  v2  The second number to be compared.
 *  @returns    The largest of the input numbers.
 */
template<std::totally_ordered T>
constexpr const T& max(const T& v1, const T& v2) noexcept;

/**
 *  @brief      Maximun of three numbers.
 *  @details    This function calculates the maximum of three numbers.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v1  The first number to be compared.
 *  @param[in]  v2  The second number to be compared.
 *  @param[in]  v3  The third number to be compared.
 *  @returns    The largest of the input numbers.
 */
template<std::totally_ordered T>
constexpr const T& max(const T& v1, const T& v2, const T& v3) noexcept;

/**
 *  @brief      Maximun of four numbers.
 *  @details    This function calculates the maximum of four numbers.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v1  The first number to be compared.
 *  @param[in]  v2  The second number to be compared.
 *  @param[in]  v3  The third number to be compared.
 *  @param[in]  v4  The fourth number to be compared.
 *  @returns    The largest of the input numbers.
 */
template<std::totally_ordered T>
constexpr const T& max(const T& v1, const T& v2, const T& v3, const T& v4) noexcept;

/**
 *  @brief      Minimun of two numbers.
 *  @details    This function calculates the minimum of two numbers.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v1  The first number to be compared.
 *  @param[in]  v2  The second number to be compared.
 *  @returns    The smallest of the input numbers.
 */
template<std::totally_ordered T>
constexpr const T& min(const T& v1, const T& v2) noexcept;

/**
 *  @brief      Minimun of three numbers.
 *  @details    This function calculates the minimum of three numbers.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v1  The first number to be compared.
 *  @param[in]  v2  The second number to be compared.
 *  @param[in]  v3  The third number to be compared.
 *  @returns    The smallest of the input numbers.
 */
template<std::totally_ordered T>
constexpr const T& min(const T& v1, const T& v2, const T& v3) noexcept;

/**
 *  @brief      Minimun of four numbers.
 *  @details    This function calculates the minimum of four numbers.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v1  The first number to be compared.
 *  @param[in]  v2  The second number to be compared.
 *  @param[in]  v3  The third number to be compared.
 *  @param[in]  v4  The fourth number to be compared.
 *  @returns    The smallest of the input numbers.
 */
template<std::totally_ordered T>
constexpr const T& min(const T& v1, const T& v2, const T& v3, const T& v4) noexcept;

/**
 *  @brief      Sign of a number.
 *  @details    This function returns the sign of a number.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  The input number whose sign is going to be obtained.
 *  @returns    1 if the input number is positive, -1 if it is negative, otherwise 0.
 */
template<nct::Signed T>
constexpr T sign(const T& v) noexcept;

/**
 *  @brief      Sign of b.
 *  @details    This function returns sign(b)*abs(a).
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  a  The value of a in the operation.
 *  @param[in]  b  The value of b in the operation.
 *  @returns    A number with the magnitude of a and the sign of b.
 */
template<nct::Signed T>
constexpr T sign(const T& a, const T& b) noexcept;

/**
 *  @brief      Positive part of a number.
 *  @details    This function returns zero if the input number is negative, otherwise it returns
 *              its original value.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  The input value whose positive part is going to be extracted.
 *  @returns    The positive part of the argument.
 */
template<nct::Signed T>
constexpr T positivePart(const T& v) noexcept;

/**
 *  @brief      Negative part of a number.
 *  @details    This function returns zero if the input number is positive, otherwise it returns
 *              its original absolute value.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  The input value whose negative part is going to be extracted.
 *  @returns    The negative part of the argument.
 */
template<nct::Signed T>
constexpr T negativePart(const T& v) noexcept;

/**
 *  @brief      Pythagoras theorem.
 *  @details    This function calculates the square root of the sum of two squares.
 *  @tparam     T  The data type of the input variables.
 *  @param[in]  a  The first number which square value is going to be calculated.
 *  @param[in]  b  The second number which square value is going to be calculated.
 *  @returns    The result of the operation.
 */
template<nct::Arithmetic T>
double pythag(const T& a, const T& b) noexcept;

/**
 *  @brief      Lerp function.
 *  @details    This function evaluates a function of time that interpolates between an initial and an
 *              end point.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  t  The time point to be evaluated.
 *  @param[in]  t0  The time of the start point.
 *  @param[in]  x0  The function evaluation at t0.
 *  @param[in]  t1  The time of the end point.
 *  @param[in]  x1  The function evaluation at t1.
 *  @returns    The function evaluation at the time t.
 */
template<nct::Numeric T>
constexpr T lerp(double t, double t0, const T& x0, double t1, const T& x1);

/**
 *  @brief      Linear function.
 *  @details    This function evaluates the linear function of time: \n
 *              x = m*t + a.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  t  The time point to be evaluated.
 *  @param[in]  m  The slope of the function.
 *  @param[in]  a  The constant term of the function.
 *  @returns    The function evaluation at the time t.
 */
template<nct::Numeric T>
constexpr T linear(double t, const T& m, const T& a);

/**
 *  @brief      Quadratic function.
 *  @details    This function evaluates the quadratic function of time: \n
 *              x = a*t*t + b*t + c.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  t  The time point to be evaluated.
 *  @param[in]  a  The quadratic term of the function.
 *  @param[in]  b  The linear term of the function.
 *  @param[in]  c  The constant term of the function.
 *  @returns    The function evaluation at the time t.
 */
template<nct::Numeric T>
constexpr T quadratic(double t, const T& a, const T& b, const T& c);

/**
 *  @brief      Cubic function.
 *  @details    This function evaluates the cubic function of time: \n
 *              x = a*t*t*t + b*t*t + c*t + d.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  t  The time point to be evaluated.
 *  @param[in]  a  The cubic term of the function.
 *  @param[in]  b  The quadratic term of the function.
 *  @param[in]  c  The linear term of the function.
 *  @param[in]  d  The constant term of the function.
 *  @returns    The function evaluation at the time t.
 */
template<nct::Numeric T>
constexpr T cubic(double t, const T& a, const T& b, const T& c, const T& d);

/**
 *  @brief      Exponential function.
 *  @details    This function evaluates the exponential function evaluated over time: \n
 *              x = x_0*exp(-t/Tau) + x_t*(1-exp(-t/Tau)).
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  t  The time point to be evaluated.
 *  @param[in]  x0  The function evaluation at t = 0.
 *  @param[in]  xt  The function evaluation at t = inf.
 *  @param[in]  tau  The time constant of the function.
 *  @returns    The function evaluation at the time t.
 */
template<nct::Numeric T>
T exponential(double t, const T& x0, const T& xt, const T& tau);

/**
 *  @brief      Factorial.
 *  @details    This function evaluates the factorial of a number.
 *  @param[in]  n  The number for which the factorial is calculated.
 *  @returns    The factorial of n.
 */
NCT_EXPIMP double factorial(unsigned int n);

/**
 *  @brief      Log-factorial.
 *  @details    This function evaluates the logaritm of the factorial of a number.
 *  @param[in]  n  The number for which the log-factorial is calculated.
 *  @returns    The log-factorial of n.
 */
NCT_EXPIMP double logFactorial(unsigned int n) noexcept;

/**
 *  @brief      Binomial coefficient.
 *  @details    This function calculates the binomial coefficient nCk.
 *  @param[in]  n  Total number of elements.
 *  @param[in]  k  Number of elements that are chosen.
 *  @returns    The binomial coefficient.
 */
NCT_EXPIMP double binCoefficient(unsigned int n, unsigned int k);

/**
 *  @brief      Root of complex number.
 *  @details    This function computes one of the nth roots of a complex number.
 *  @param[in]  z  The complex number whose root is computed.
 *  @param[in]  n  n-th root to compute.
 *  @param[in]  k  Index of the root to compute (from 0 to n-1).
 *  @returns    Wrapped angle.
 */
NCT_EXPIMP Complex rootOfComplex(const Complex& z, unsigned int n, unsigned int i) noexcept;

/**
 *  @brief      Absolute difference between two numbers.
 *  @details    This function calculates the absolute difference between two numbers.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v1  The first number of the operation.
 *  @param[in]  v2  The second number of the operation.
 *  @returns    The absolute diffence between the given numbers.
 */
template<nct::Arithmetic T>
constexpr T absDifference(const T& v1, const T& v2) noexcept;

/**
 *  @brief      Absolute difference between two numbers.
 *  @details    This function calculates the absolute difference between two numbers. The result is
 *              returned in double precision format.
 *  @tparam     T  The data type of the input variables.
 *  @param[in]  v1  The first number of the operation.
 *  @param[in]  v2  The second number of the operation.
 *  @returns    The absolute diffence between the given numbers.
 */
template<nct::Arithmetic T>
constexpr double absRealDifference(const T& v1, const T& v2) noexcept;

/**
 *  @brief      Absolute relative difference between two numbers.
 *  @details    This function calculates the absolute difference between two numbers scaled by
 *              the average of the absolute values of the numbers.
 *  @tparam     T  The data type of the input variables.
 *  @param[in]  v1  The first number of the operation.
 *  @param[in]  v2  The second number of the operation.
 *  @returns    The difference between the given numbers.
 */
template<nct::Numeric T>
constexpr double absRelativeDifference(const T& v1, const T& v2) noexcept;

/**
 *  @brief      Absolute relative difference between two numbers.
 *  @details    This function calculates the absolute difference between two numbers scaled by
 *              the average of the absolute values of the numbers.
 *  @param[in]  v1  The first number of the operation.
 *  @param[in]  v2  The second number of the operation.
 *  @returns    The difference between the given numbers.
 */
template<>
double absRelativeDifference(const Complex& v1, const Complex& v2) noexcept;

/**
 *  @brief      Modified version of the absolute relative difference between two numbers.
 *  @details    This function calculates the absolute difference between two numbers scaled by
 *              the average of the absolute values of the numbers only when the difference is greater 
 *              than 1.
 *  @tparam     T  The data type of the input variables.
 *  @param[in]  v1  The first number of the operation.
 *  @param[in]  v2  The second number of the operation.
 *  @returns    The difference between the given numbers.
 */
template<nct::Numeric T>
constexpr double absRelativeDifferenceMod(const T& v1, const T& v2) noexcept;

/**
 *  @brief      Modified version of the absolute relative difference between two numbers.
 *  @details    This function calculates the absolute difference between two numbers scaled by
 *              the average of the absolute values of the numbers only when the difference is greater 
 *              than 1.
 *  @param[in]  v1  The first number of the operation.
 *  @param[in]  v2  The second number of the operation.
 *  @returns    The difference between the given numbers.
 */
template<>
double absRelativeDifferenceMod(const Complex& v1, const Complex& v2) noexcept;

////////// Mathematical transformations of sequences //////////   

/**
 *  @brief      N-th order difference.
 *  @details    This function calculates the n-th order difference between consecutive
 *              elements of a sequence. This operation is equivalent to the n-order forward 
 *              derivative.
 *  @note       The length of the output sequence must be at
 *              least N-n, where N is the length of the input sequence. 
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[out] out  Output iterator defining the beginning of the destination container.
 *  @paran[in]  The order of the difference to be calculated.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> &&
    nct::Numeric<typename InputIt::value_type>
void diff(InputIt first, InputIt last, OutIt out, unsigned int n);

////////// Threshold operations //////////

/**
 *  @brief      Threshold operator.
 *  @details    This function returns 1 if the input number is above (or below) the specified threshold,
 *              otherwise, the function returns 0. The threshold type indicates the way this
 *              function computes the result.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  The input number to be compared.
 *  @param[in]  tr  The threshold value to be used in the comparison.
 *  @param[in]  thresholdType  The type of threshold operation to be computed.
 *  @returns    The result of the operation.
 */
template<std::totally_ordered T>
constexpr T threshold(const T& v, const T& tr, 
    ThresholdType thresholdType = ThresholdType::UpperThreshold);

/**
 *  @brief      Threshold operator.
 *  @details    This function sets to 1 all the elements of one sequence whose value is above 
 *              (or below) the specified threshold. The rest of the elements are set to 0.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[out] out  Output iterator defining the beginning of the destination container.
 *  @param[in]  The threshold value to be used in the comparison.
 *  @param[in]  thresholdType  The type of threshold operation to be computed.
 */
template<std::random_access_iterator InputIt, typename OutIt> 
requires std::output_iterator<OutIt, typename InputIt::value_type> &&
    std::totally_ordered<typename InputIt::value_type>
void threshold(InputIt first, InputIt last, OutIt out, 
    const typename InputIt::value_type& tr, ThresholdType thresholdType = ThresholdType::UpperThreshold);

/**
 *  @brief      Upper threshold.
 *  @details    This function returns 1 if the input number is above the specified threshold,
 *              otherwise, the function returns 0.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  The input number to be compared.
 *  @param[in]  tr  The threshold value to be used in the comparison.
 *  @returns    The result of the operation.
 */
template<std::totally_ordered T>
constexpr T upperThreshold(const T& v, const T& tr) noexcept;

/**
 *  @brief      Upper threshold.
 *  @details    This function sets to 1 all the elements whose value is above the specified threshold.
 *              The rest of the elements are set to 0.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[out] out  Output iterator defining the beginning of the destination container.
 *  @param[in]  The threshold value to be used in the comparison.
 */
template<std::random_access_iterator InputIt, typename OutIt> 
requires std::output_iterator<OutIt, typename InputIt::value_type> &&
    std::totally_ordered<typename InputIt::value_type>
void upperThreshold(InputIt first, InputIt last, OutIt out, 
    const typename InputIt::value_type& tr);

/**
 *  @brief      Absolute upper threshold.
 *  @details    This function returns 1 if the absolute value of the input number is above the
 *              specified threshold, otherwise, the function returns 0.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  The input number to be compared.
 *  @param[in]  tr  The threshold value to be used in the comparison.
 *  @returns    The result of the operation.
 */
template<nct::Signed T>
constexpr T absUpperThreshold(const T& v, const T& tr) noexcept;

/**
 *  @brief      Absolute upper threshold.
 *  @details    This function sets to 1 all the elements whose absolute value is above the specified
 *              threshold. The rest of the elements are set to 0.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[out] out  Output iterator defining the beginning of the destination container.
 *  @param[in]  The threshold value to be used in the comparison.
 */
template<std::random_access_iterator InputIt, typename OutIt> 
requires std::output_iterator<OutIt, typename InputIt::value_type> &&
    std::totally_ordered<typename InputIt::value_type>
void absUpperThreshold(InputIt first, InputIt last, OutIt out, 
    const typename InputIt::value_type& tr);

/**
 *  @brief      Lower threshold.
 *  @details    This function returns 1 if the absolute value of the input number is above the
 *              specified threshold, otherwise, the function returns 0.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  The input number to be compared.
 *  @param[in]  tr  The threshold value to be used in the comparison.
 *  @returns    The result of the operation.
 */
template<std::totally_ordered T>
constexpr T lowerThreshold(const T& v, const T& tr) noexcept;

/**
 *  @brief      Lower threshold.
 *  @details    This function sets to 1 all the elements whose value is below the specified
 *              threshold. The rest of the elements are set to 0.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[out] out  Output iterator defining the beginning of the destination container.
 *  @param[in]  The threshold value to be used in the comparison.
 */
template<std::random_access_iterator InputIt, typename OutIt> 
requires std::output_iterator<OutIt, typename InputIt::value_type> &&
    std::totally_ordered<typename InputIt::value_type>
void lowerThreshold(InputIt first, InputIt last, OutIt out, 
    const typename InputIt::value_type& tr);

/**
 *  @brief      Absolute lower threshold.
 *  @details    This function returns 1 if the absolute value of the input number is below the
 *              specified threshold, otherwise, the function returns 0.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  The input number to be compared.
 *  @param[in]  The threshold value to be used in the comparison.
 *  @returns    The result of the operation.
 */
template<nct::Signed T>
constexpr T absLowerThreshold(const T& v, const T& tr) noexcept;

/**
 *  @brief      Absolute lower threshold.
 *  @details    This function sets to 1 all the elements whose absolute value is below the
 *              specified threshold. The rest of the elements are set to 0.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[out] out  Output iterator defining the beginning of the destination container.
 *  @param[in]  The threshold value to be used in the comparison.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires nct::Signed<typename InputIt::value_type> &&
    std::output_iterator<OutIt, typename InputIt::value_type>
void absLowerThreshold(InputIt first, InputIt last,
    OutIt out, const typename InputIt::value_type& tr);

////////// Modulo operations //////////  

/**
 *  @brief      Power modulo n.
 *  @details    This function calculates the result of (x^n)%p.
 *  @param[in]  x  The base of the operation.
 *  @param[in]  n  The exponent of the operation.
 *  @param[in]  p  The modulo of the operation.
 *  @returns    The result of the operatoin.
 */
NCT_EXPIMP unsigned int powerMod(unsigned int x, unsigned int n, unsigned int p) noexcept;

/**
 *  @brief      Power modulo n.
 *  @details    This function calculates the result of (x^n)%p.
 *  @param[in]  x  The base of the operation.
 *  @param[in]  n  The exponent of the operation.
 *  @param[in]  p  The modulo of the operation.
 *  @returns    The result of the operatoin.
 */
NCT_EXPIMP unsigned long long powerMod(unsigned long long x, 
    unsigned long long n, unsigned long long p) noexcept;

/**
 *  @brief      Multiplicative inverse modulo.
 *  @details    This function calculates the number k such that kx = 1 (mod p). It is assumed that
 *              x and p are co-primes.
 *  @param[in]  x  The number for which the multiplicative inverse modulo is going to be calculated.
 *  @param[in]  p  The modulo of the operation.
 *  @returns    The result of the operatoin.
 */
NCT_EXPIMP unsigned int inverseMod(unsigned int x, unsigned int p);

/**
 *  @brief      Multiplicative inverse modulo.
 *  @details    This function calculates the number k such that kx = 1 (mod p). It is assumed that
 *              x and p are co-primes.
 *  @param[in]  x  The number for which the multiplicative inverse modulo is going to be calculated.
 *  @param[in]  p  The modulo of the operation.
 *  @returns    The result of the operatoin.
 */
NCT_EXPIMP unsigned long long inverseMod(unsigned long long x, unsigned long long p);

////////// Functions for prime numbers //////////   

/**
 *  @brief      Is a number a prime?
 *  @details    This function returns whether the given number is a prime.
 *  @param[in]  n  The number to be tested.
 *  @returns    True, if the given number is a prime, otherwise, false.
 */
NCT_EXPIMP bool isPrime(unsigned int n) noexcept;

/**
 *  @brief      Is a number a prime?
 *  @details    This function returns whether the given number is a prime.
 *  @param[in]  n  The number to be tested.
 *  @returns    True, if the given number is a prime, otherwise, false.
 */
NCT_EXPIMP bool isPrime(unsigned long long n) noexcept;

/**
 *  @brief      Next prime of an integer number.
 *  @details    This function calculates the prime number greater than the given number.
 *  @param[in]  n  The number for which the next prime is going to be calculated.
 *  @returns    The next prime of n.
 */
NCT_EXPIMP unsigned int nextPrime(unsigned int n) noexcept;

/**
 *  @brief      Next prime of an integer number.
 *  @details    This function calculates the prime number greater than the given number. 
 *  @param[in]  n  The number for which the next prime is going to be calculated.
 *  @returns    The next prime of n.
 */
NCT_EXPIMP unsigned long long nextPrime(unsigned long long n) noexcept;

/**
 *  @brief      Prime numbers lower than or equal to n.
 *  @details    This function returns the primes that are lower than or equal to the given number.
 *  @param[in]  n  The upper bound of the primes to be obtained.
 *  @returns    The list of primes.
 */
NCT_EXPIMP std::vector<unsigned int> primeNumbers(unsigned int n);

/**
 *  @brief      Prime numbers lower than or equal to n.
 *  @details    This function returns the primes that are lower than or equal to the given number.
 *  @param[in]  n  The upper bound of the primes to be obtained.
 *  @returns    The list of primes.
 */
NCT_EXPIMP std::vector<unsigned long long> primeNumbers(unsigned long long n);

/**
 *  @brief      Prime factors.
 *  @details    This function calculates the prime factors of the given number.
 *  @param[in]  n  The number for which the prime factos are going to be calculated.
 *  @returns    The prime factors of n.
 */
NCT_EXPIMP std::vector<unsigned int> primeFactors(unsigned int n);

/**
 *  @brief      Prime factors.
 *  @details    This function calculates the prime factors of the given number.
 *  @param[in]  n  The number for which the prime factos are going to be calculated.
 *  @returns    The prime factors of n.
 */
NCT_EXPIMP std::vector<unsigned long long> primeFactors(unsigned long long n);

/**
 *  @brief      Primitive root modulo n of a prime.
 *  @details    This function calculates the smallest primitive root modulo n of a prime.
 *  @param[in]  n  The number for which the primitive root is going to be calculated.
 *  @returns    The smallest primitive root modulo n of the given number.
 */
NCT_EXPIMP unsigned int primitiveRoot(unsigned int n);

/**
 *  @brief      Primitive root modulo n of a prime.
 *  @details    This function calculates the smallest primitive root modulo n of a prime.
 *  @param[in]  n  The number for which the primitive root is going to be calculated.
 *  @returns    The smallest primitive root modulo n of the given number.
 */
NCT_EXPIMP unsigned long long primitiveRoot(unsigned long long n);

/**
 *  @brief      Are two numbers co-primes?
 *  @details    This function returns whether the given numbers are co-primes.
 *  @param[in]  a  The first number to be tested.
 *  @param[in]  b  The second number to be tested.
 *  @returns    True, if the given numbers are co-primes, otherwise, false.
 */
NCT_EXPIMP bool areCoprimes(unsigned int a, unsigned int b) noexcept;

/**
 *  @brief      Are two numbers co-primes?
 *  @details    This function returns whether the given numbers are co-primes.
 *  @param[in]  a  The first number to be tested.
 *  @param[in]  b  The second number to be tested.
 *  @returns    True, if the given numbers are co-primes, otherwise, false.
 */
NCT_EXPIMP bool areCoprimes(unsigned long long a, unsigned long long b) noexcept;

////////// Functions for combinations ////////// 

/**
 *  @brief      Next combination.
 *  @details    This function computes the next combination of size (rend-rbegin) of a container n.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @tparam     BidirectionalIterator  The type of the iterators to be used to store the result.
 *  @param[in]  nbegin  Iterator defining the initial position of a container with the original elements.
 *  @param[in]  nend  Iterator defining the final position of a container with the original elements.
 *  @param[in, out]  rbegin  Iterator defining the initial position of a container with the current combination.
 *  @param[in, out]  rend  Iterator defining the final position of a container with the current combination.
 *  @returns    True, if the new function was able to determine the next combination, otherwise, false.
 */
template<std::random_access_iterator InputIt, std::input_or_output_iterator BidirectionalIterator>
bool nextCombination(InputIt nbegin, InputIt nend,
    BidirectionalIterator rbegin, BidirectionalIterator rend);

/**
 *  @brief      Previous combination.
 *  @details    This function computes the previous combination of size (rend-rbegin) of a container n.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @tparam     BidirectionalIterator  The type of the iterators to be used to store the result.
 *  @param[in]  nbegin  Iterator defining the initial position of a container with the original elements.
 *  @param[in]  nend  Iterator defining the final position of a container with the original elements.
 *  @param[in, out]  rbegin  Iterator defining the initial position of a container with the current combination.
 *  @param[in, out]  rend  Iterator defining the final position of a container with the current combination.
 *  @returns    True, if the new function was able to determine the previous combination, otherwise, false.
 */
template<std::random_access_iterator InputIt, std::input_or_output_iterator BidirectionalIterator>
bool previousCombination(InputIt nbegin, InputIt nend,
    BidirectionalIterator rbegin, BidirectionalIterator rend);

////////// Vectorial norms //////////   

/**
 *  @brief      Squared norm.
 *  @details    For one-dimensional arrays, this method computes the square of the L2 norm.
 *              For two-dimensional arrays, this method obtains the Frobenius norm.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first  Iterator to the initial position of a container.
 *  @param[in]  last  Iterator to the final position of a container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
requires nct::Numeric<typename InputIt::value_type>
auto squaredNorm(InputIt first, InputIt last) -> decltype(std::norm(*first));

/**
 *  @brief      Squared norm.
 *  @details    This function computes the euclidean norm of a container.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
requires nct::Numeric<typename InputIt::value_type>
double euclidianNorm(InputIt first, InputIt last);

/**
 *  @brief      Vectorial LP-norm.
 *  @details    This function computes the LP-norm of a one-dimensional arrays.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  p  The norm to be calculated.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
requires nct::Numeric<typename InputIt::value_type>
double lpNorm(InputIt first, InputIt last, double p);

/**
 *  @brief      Infinity norm.
 *  @details    This function computes the infinity norm of a one-dimensional arrays.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
requires nct::Numeric<typename InputIt::value_type>
auto infinityNorm(InputIt first, InputIt last) -> decltype(std::abs(*first));

/**
 *  @brief      Squared norm of difference between sequences.
 *  @details    For one-dimensional arrays, this method computes the square of the L2 norm
 *              of the difference between two sequences.
 *              For two-dimensional arrays, this method obtains the Frobenius norm
 *              of the difference between two sequences.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first1  Iterator defining the beginning of the first container.
 *  @param[in]  last1 Iterator defining the end of the first container.
 *  @param[in]  first2  Iterator defining the beginning of the second container.
 *  @param[in]  last2 Iterator defining the end of the second container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
requires nct::Numeric<typename InputIt::value_type>
auto squaredNormOfDifference(InputIt first1, InputIt last1,
    InputIt first2, InputIt last2) -> decltype(std::norm(*first1));

/**
 *  @brief      Squared norm of difference between sequences.
 *  @details    This function computes the euclidean norm of the difference between two sequences.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first1  Iterator defining the beginning of the first container.
 *  @param[in]  last1 Iterator defining the end of the first container.
 *  @param[in]  first2  Iterator defining the beginning of the second container.
 *  @param[in]  last2 Iterator defining the end of the second container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
requires nct::SignedNumeric<typename InputIt::value_type>
double euclidianNormOfDifference(InputIt first1, InputIt last1,
    InputIt first2, InputIt last2);

/**
 *  @brief      Vectorial LP-norm of difference between sequences.
 *  @details    This function computes the LP-norm of the difference between two sequences.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first1  Iterator defining the beginning of the first container.
 *  @param[in]  last1 Iterator defining the end of the first container.
 *  @param[in]  first2  Iterator defining the beginning of the second container.
 *  @param[in]  last2 Iterator defining the end of the second container.
 *  @param[in]  p  The norm to be calculated.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
requires nct::SignedNumeric<typename InputIt::value_type>
double lpNormOfDifference(InputIt first1, InputIt last1,
    InputIt first2, InputIt last2, double p);

/**
 *  @brief      Infinity norm of difference between sequences.
 *  @details    This function computes the infinity norm of the difference between two sequences.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first1  Iterator defining the beginning of the first container.
 *  @param[in]  last1 Iterator defining the end of the first container.
 *  @param[in]  first2  Iterator defining the beginning of the second container.
 *  @param[in]  last2 Iterator defining the end of the second container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
requires nct::SignedNumeric<typename InputIt::value_type>
auto infinityNormOfDifference(InputIt first1, InputIt last1,
    InputIt first2, InputIt last2) -> decltype(std::abs(*first1));


////////// Functions that normalize the elements of a container //////////

/**
 *  @brief      Normalize by max.
 *  @details    This function normalizes a sequence by dividing all the elements
 *              by the maximum absolute value of the sequence.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[out] out  Output iterator defining the beginning of the destination container.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> &&
    std::totally_ordered<typename InputIt::value_type>
void normalizeByMax(InputIt first, InputIt last, OutIt out);

/**
 *  @brief      Normalize by sum.
 *  @details    This function normalizes a sequence by dividing all the elements
 *              by the total sum of all the elements in the sequence.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[out] out  Output iterator defining the beginning of the destination container.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> &&
    nct::Numeric<typename InputIt::value_type>
void normalizeBySum(InputIt first, InputIt last, OutIt out);

////////// Functions that transform containers into scalar values //////////

/**
 *  @brief      Dot product.
 *  @details    This function computes the dot product of two sequences.
 *  @tparam     InputIt1  The type of the iterators to be used to traverse the first container.
 *  @tparam     InputIt2  The type of the iterators to be used to traverse the second container.
 *  @param[in]  first1  Iterator defining the beginning of the first container.
 *  @param[in]  last1 Iterator defining the end of the first container.
 *  @param[in]  first2  Iterator defining the beginning of the second container.
 *  @param[in]  last2 Iterator defining the end of the second container.
 *  @returns    The variance of the observations.
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Numeric<typename InputIt1::value_type> && 
    nct::Numeric<typename InputIt2::value_type>
auto dotProduct(InputIt1 first1, InputIt1 last1,
    InputIt2 first2, InputIt2 last2) -> decltype((*first1)* (*first2));

/**
 *  @brief      Sum of all the members of a range.
 *  @details    This function returns the sum of the elements of a container.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data. 
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The sum.
 */
template<std::random_access_iterator InputIt> requires nct::Numeric<typename InputIt::value_type>
auto sum(InputIt first, InputIt last) -> typename std::remove_cvref_t<decltype(*first)>;

/**
 *  @brief      Sum of all the members of a range.
 *  @details    This function transforms each element of a container to double and computes its sum.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The sum.
 */
template<std::random_access_iterator InputIt>
requires std::convertible_to<typename InputIt::value_type, double>
double castSum(InputIt first, InputIt last);

/**
 *  @brief      Minimum of all the members of a range.
 *  @details    This function returns the minimum value of a container.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
requires std::totally_ordered<typename InputIt::value_type>
auto minimum(InputIt first, InputIt last) -> typename std::remove_cvref_t<decltype(*first)>;

/**
 *  @brief      Index of the minimum of all the members of a range.
 *  @details    This function returns the index of the minimum value of a container.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
requires std::totally_ordered<typename InputIt::value_type>
auto minimumValueIndex(InputIt first, InputIt last) -> decltype(last - first);

/**
 *  @brief      Minimum absolute value of all the members of a range.
 *  @details    This function returns the minimum absolute value of a container.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
auto minimumAbs(InputIt first, InputIt last) -> decltype(std::abs(*first));

/**
 *  @brief      Index of the minimum absolute value of all the members of a range.
 *  @details    This function returns the index of the minimum absolute value in a container.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
auto minimumAbsValueIndex(InputIt first, InputIt last) -> decltype(last - first);

/**
 *  @brief      Maximum of all the members of a range.
 *  @details    This function returns the maximum value in a container.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
requires std::totally_ordered<typename InputIt::value_type>
auto maximum(InputIt first, InputIt last) -> typename std::remove_cvref_t<decltype(*first)>;

/**
 *  @brief      Index of the maximum of all the members of a range.
 *  @details    This function returns the index of the maximum value in a container.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
requires std::totally_ordered<typename InputIt::value_type>
auto maximumValueIndex(InputIt first, InputIt last) -> decltype(last - first);

/**
 *  @brief      Maximum absolute value of all the members of a range.
 *  @details    This function returns the maximum absolute value in a container.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
requires nct::SignedNumeric<typename InputIt::value_type>
auto maximumAbs(InputIt first, InputIt last) -> decltype(std::abs(*first));

/**
 *  @brief      Index of the maximum absolute value of all the members of a range.
 *  @details    This function returns the index of the maximum absolute value in a container.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
requires nct::SignedNumeric<typename InputIt::value_type>
auto maximumAbsValueIndex(InputIt first, InputIt last) -> decltype(last - first);

/**
 *  @brief      Maximum absolute difference.
 *  @details    This function returns the maximum absolute difference between to containers of the
 *              same size.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first1  Iterator defining the beginning of the first container.
 *  @param[in]  last1 Iterator defining the end of the first container.
 *  @param[in]  first2  Iterator defining the beginning of the second container.
 *  @param[in]  last2 Iterator defining the end of the second container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
requires nct::SignedNumeric<typename InputIt::value_type>
auto maximumAbsDifference(InputIt first1, InputIt last1,
    InputIt first2, InputIt last2) -> typename std::remove_cvref_t<decltype(*first1)>;

/**
 *  @brief      Maximum absolute relative difference.
 *  @details    This function returns the maximum absolute relative difference between to containers 
 *              of the same size.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first1  Iterator defining the beginning of the first container.
 *  @param[in]  last1 Iterator defining the end of the first container.
 *  @param[in]  first2  Iterator defining the beginning of the second container.
 *  @param[in]  last2 Iterator defining the end of the second container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
requires nct::SignedNumeric<typename InputIt::value_type>
double maximumAbsRelativeDifference(InputIt first1, InputIt last1,
    InputIt first2, InputIt last2);

/**
 *  @brief      Maximum modified absolute relative difference.
 *  @details    This function returns the maximum modified absolute relative difference between to 
 *              containers of the same size.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first1  Iterator defining the beginning of the first container.
 *  @param[in]  last1 Iterator defining the end of the first container.
 *  @param[in]  first2  Iterator defining the beginning of the second container.
 *  @param[in]  last2 Iterator defining the end of the second container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt>
requires nct::SignedNumeric<typename InputIt::value_type>
double maximumAbsRelativeDifferenceMod(InputIt first1, InputIt last1,
    InputIt first2, InputIt last2);

/**
 *  @brief      Logical And.
 *  @details    This function returns the logical AND operation of the elements in a container.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt> 
requires std::integral<typename InputIt::value_type>
auto logicalAnd(InputIt first, InputIt last) -> typename std::remove_cvref_t<decltype(*first)>;

/**
 *  @brief      Logicla Or.
 *  @details    This function returns the logical OR operation of the elements in a container.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The result of the operation.
 */
template<std::random_access_iterator InputIt> 
requires std::integral<typename InputIt::value_type>
auto logicalOr(InputIt first, InputIt last) -> typename std::remove_cvref_t<decltype(*first)>;

////////// Functions for rounding numbers ////////// 

/**
 *  @brief      Half round up.
 *  @details    This function rounds a number up, i.e. 7.5 rounds to 8 and 7.4 rounds to 7.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  Input number.
 *  @returns    The result of the operation.
 */
template<std::floating_point T>
T halfRoundUp(const T& v) noexcept;

/**
 *  @brief      Half round down.
 *  @details    This function rounds a number down, i.e. 7.5 rounds to 7 and 7.6 rounds to 8.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  Input number.
 *  @returns    The result of the operation.
 */
template<std::floating_point T>
T halfRoundDown(const T& v) noexcept;

/**
 *  @brief      Round half away from zero.
 *  @details    This function rounds a number so it's further away from zero.
 *              7.5 rounds to 8 and -7.5 rounds to -8.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  Input number.
 *  @returns    The result of the operation.
 */
template<std::floating_point T>
T roundHalfAwayFromZero(const T& v) noexcept;

/**
 *  @brief      Round half towards zero.
 *  @details    This function rounds a number so it's closer to zero.
 *              7.5 rounds to 7 and -7.5 rounds to -7.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  Input number.
 *  @returns    The result of the operation.
 */
template<std::floating_point T>
T roundHalfTowardsZero(const T& v) noexcept;

/**
 *  @brief      Round away from zero.
 *  @details    This function rounds a number so it's further away from zero.
 *              7.4 rounds to 8 and -7.4 rounds to -8.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  Input number.
 *  @returns    The result of the operation.
 */
template<std::floating_point T>
T roundAwayFromZero(const T& v) noexcept;

/**
 *  @brief      Round towards zero.
 *  @details    This function rounds a number so it's closer to zero.
 *              7.4 rounds to 7 and -7.4 rounds to -7.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  Input number.
 *  @returns    The result of the operation.
 */
template<std::floating_point T>
T roundTowardsZero(const T& v) noexcept;

////////// Functions for wrapping numbers ////////// 

/**
 *  @brief      Wrap value.
 *  @details    This function wraps a value between [l, u).
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  v  Input number.
 *  @param[in]  l  The lower limit where the variable will be wrapped.
 *  @param[in]  u  The upper limit where the variable will be wrapped.
 *  @returns    The result of the operation.
 */
template<nct::Arithmetic T>
constexpr T wrap(const T& v, const T& l, const T& u);

/**
 *  @brief      Wrapped angle between -pi and pi.
 *  @details    This function wraps an angle between -pi and pi.
 *  @tparam     T  The data type of the input variable.
 *  @param[in]  angle  The angle in radians to be converted.
 *  @returns    Wrapped angle.
 */
template<nct::Arithmetic T>
constexpr double wrapToPi(const T& angle) noexcept;

/**
 *  @brief      Wrapped angle between 0 and 2pi.
 *  @details    This function wraps an angle between 0 and 2pi.
 *  @tparam     T  The data type of the input variable.
 *  @param[in]  angle  The angle in radians to be converted.
 *  @returns    Wrapped angle.
 */
template<nct::Arithmetic T>
constexpr double wrapTo2Pi(const T& angle) noexcept;

/**
 *  @brief      Wrapped angle between -180 and 180.
 *  @details    This function wraps an angle between -180 and 180.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  angle  The angle in degrees to be converted.
 *  @returns    Wrapped angle.
 */
template<nct::Arithmetic T>
constexpr T wrapTo180(const T& angle) noexcept;

/**
 *  @brief      Wrapped angle between 0 and 360.
 *  @details    This function wraps an angle between 0 and 360.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  angle  The angle in degrees to be converted.
 *  @returns    Wrapped angle.
 */
template<nct::Arithmetic T>
constexpr T wrapTo360(const T& angle) noexcept;

/**
 *  @brief      Unwrap sequence.
 *  @details    This function unwraps the values of the given sequence by changing
 *              absolute jumps greater than cutoff to their 2*cutoff complement.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[out] out  Output iterator defining the beginning of the destination container.
 *  @param[out] cutoff  The cutoff values used to unwrap the sequence. Typically, this
 *              parameter is the half of the range used to wrap the original values.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> &&
    nct::Arithmetic<typename InputIt::value_type>
void unwrap(InputIt first, InputIt last, OutIt out, double cutoff);

/**
 *  @brief      Unwrap phase angles.
 *  @details    This function unwraps a sequence of phase angles by changing
 *              absolute jumps greater than pi to their 2*pi complement.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[out] out  Output iterator defining the beginning of the destination container.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> &&
    nct::Arithmetic<typename InputIt::value_type>
void unwrapPhaseAngles(InputIt first, InputIt last,
    OutIt out);

////////// Functions for manipulating angles ////////// 

/**
 *  @brief      Radians to degrees.
 *  @details    This function converts an angle in radians to degrees.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  angle  The angle in radians to be converted.
 *  @returns    The angle in degrees.
 */
template<nct::Arithmetic T>
constexpr double radToDeg(const T& angle) noexcept;

/**
 *  @brief      Degrees to radians.
 *  @details    This function converts an angle in degrees to radians.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  angle  The angle in degrees to be converted.
 *  @returns    The angle in radians.
 */
template<nct::Arithmetic T>
constexpr double degToRad(const T& angle) noexcept;

/**
 *  @brief      Angular distance.
 *  @details    This function calculates the shortest distance between two angles in radians.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  angle1  An angle in radians.
 *  @param[in]  angle2  An angle in radians.
 *  @returns    The distance between angles in radians (angle1 - angle2).
 */
template<nct::Arithmetic T>
double angularDistance(const T& angle1, const T& angle2) noexcept;


////////// Functions for manipulating real numbers ////////// 

/**
 *  @brief      Calculate increment.
 *  @details    This function calculates the increment in one number x when it is
 *              added to another number h.
 *  @tparam     T  The data type of the input/output variables.
 *  @param[in]  x  The number to be incremented.
 *  @param[in]  h  The incremented to be tested.
 *  @returns    The increment in x.
 */
template<nct::Numeric T>
constexpr T calculateDelta(const T& x, const T& h) noexcept;

/**
 *  @brief      Most significant digit.
 *  @details    This function returns the most significant digit of a real number.
 *  @param[in]  num  Input number.
 *  @returns    The most significant digit of num.
 */
NCT_EXPIMP double mostSignificantDigit(double num) noexcept;

/**
 *  @brief      Most significant digit position.
 *  @details    This function returns the most significant digit position of a real number.
 *  @param[in]  num  Input number.
 *  @returns    The most significant digit position of num.
 */
NCT_EXPIMP int mostSignificantDigitPosition(double num) noexcept;

////////// Polynomial root finding functions ////////// 

/**
 *  @brief      Solve quadratic equation.
 *  @details    This function finds the roots of the equation ax^2 + bx + c.
 *  @param[in]  a  The coefficient of the second order term.
 *  @param[in]  b  The coefficient of the first order term.
 *  @param[in]  c  The constant term. 
 *  @returns    The roots of the specified equation.
 */
NCT_EXPIMP std::pair<double, double> solveQuadraticEq(double a, double b, double c);

/**
 *  @brief      Solve complex quadratic equation.
 *  @details    This function finds the roots of the equation complex az^2 + bz + c.
 *  @param[in]  a  The coefficient of the second order term.
 *  @param[in]  b  The coefficient of the first order term.
 *  @param[in]  c  The constant term.  
 */
NCT_EXPIMP std::pair<Complex, Complex> solveQuadraticEq(const Complex& a,
    const Complex& b, const Complex& c);

/**
 *  @brief      Solve quadratic equation.
 *  @details    This function finds the roots of the equation ax^2 + bx + c.
 *  @param[in]  a  The coefficient of the second order term.
 *  @param[in]  b  The coefficient of the first order term.
 *  @param[in]  c  The constant term.
 *  @returns    The roots of the specified equation.
 */
NCT_EXPIMP std::pair<Complex, Complex> solveQuadraticEqC(double a, double b, double c);

/**
 *  @brief      Solve cubic equation.
 *  @details    This function finds the roots of the equation ax^3 + bx^2 + cx + d.
 *  @param[in]  a  The coefficient of the third order term.
 *  @param[in]  b  The coefficient of the second order term.
 *  @param[in]  c  The coefficient of the first order term.
 *  @param[in]  d  The constant term. 
 *  @returns    The roots of the specified equation.
 */
NCT_EXPIMP std::tuple<double, double, double> solveCubicEq(
    double a, double b, double c, double d);

/**
 *  @brief      Solve complex cubic equation.
 *  @details    This function finds the roots of the complex equation az^3 + bz^2 + cz + d.
 *  @param[in]  a  The coefficient of the third order term.
 *  @param[in]  b  The coefficient of the second order term.
 *  @param[in]  c  The coefficient of the first order term.
 *  @param[in]  d  The constant term.
 *  @returns    The roots of the specified equation.
 */
NCT_EXPIMP std::tuple<Complex, Complex, Complex> solveCubicEq(
    const Complex& a, const Complex& b, const Complex& c, const Complex& d);

/**
 *  @brief      Solve cubic equation.
 *  @details    This function finds the roots of the equation ax^3 + bx^2 + cx + d.
 *  @param[in]  a  The coefficient of the third order term.
 *  @param[in]  b  The coefficient of the second order term.
 *  @param[in]  c  The coefficient of the first order term.
 *  @param[in]  d  The constant term. 
 *  @returns    The roots of the specified equation.
 */
NCT_EXPIMP std::tuple<Complex, Complex, Complex> solveCubicEqC(
    double a, double b, double c, double d);

/**
 *  @brief      Solve quartic equation.
 *  @details    This function finds the roots of the equation ax^4 + bx^3 + cx^2 + dx + e.
 *  @param[in]  a  The coefficient of the quartic order term.
 *  @param[in]  b  The coefficient of the third order term.
 *  @param[in]  c  The coefficient of the second order term.
 *  @param[in]  d  The coefficient of the first order term.
 *  @param[in]  e  The constant term. 
 *  @returns    The roots of the specified equation.
 */
NCT_EXPIMP std::tuple<double, double, double, double> solveQuarticEq(
    double a, double b, double c, double d, double e);

/**
 *  @brief      Solve quartic complex equation.
 *  @details    This function finds the roots of the equation az^4 + bz^3 + cz^2 + dz + e.
 *  @param[in]  a  The coefficient of the quartic order term.
 *  @param[in]  b  The coefficient of the third order term.
 *  @param[in]  c  The coefficient of the second order term.
 *  @param[in]  d  The coefficient of the first order term.
 *  @param[in]  e  The constant term.
 *  @returns    The roots of the specified equation.
 */
NCT_EXPIMP std::tuple<Complex, Complex, Complex, Complex> solveQuarticEq(
    const Complex& a, const Complex& b, const Complex& c, const Complex& d, const Complex& e);

/**
 *  @brief      Solve quartic equation.
 *  @details    This function finds the roots of the equation ax^4 + bx^3 + cx^2 + dx + e.
 *  @param[in]  a  The coefficient of the quartic order term.
 *  @param[in]  b  The coefficient of the third order term.
 *  @param[in]  c  The coefficient of the second order term.
 *  @param[in]  d  The coefficient of the first order term.
 *  @param[in]  e  The constant term. 
 *  @returns    The roots of the specified equation.
 */
NCT_EXPIMP std::tuple<Complex, Complex, Complex, Complex> solveQuarticEqC(
    double a, double b, double c, double d, double e);

/**
 *  @brief      Number of real roots.
 *  @details    This function returns the number of distinct real roots of the equation ax^2 + bx + c. 
 *  @param[in]  a  The coefficient of the second order term.
 *  @param[in]  b  The coefficient of the first order term.
 *  @param[in]  c  The constant term. 
 *  @returns    The number of real roots.
 */
NCT_EXPIMP unsigned int numberOfRealDinstinctRoots(double a, double b, double c);

/**
 *  @brief      Number of real roots.
 *  @details    This function returns the number of distinct real roots of the equation 
 *              ax^3 + bx^2 + cx + d.
 *  @param[in]  a  The coefficient of the third order term.
 *  @param[in]  b  The coefficient of the second order term.
 *  @param[in]  c  The coefficient of the first order term.
 *  @param[in]  d  The constant term.
 */
NCT_EXPIMP unsigned int numberOfRealDinstinctRoots(double a, double b, double c, double d);

/**
 *  @brief      Number of real roots.
 *  @details    This function returns the number of distinct real roots of the equation
 *              ax^4 + bx^3 + cx^2 + dx + e.
 *  @param[in]  b  The coefficient of the quartic order term.
 *  @param[in]  b  The coefficient of the third order term.
 *  @param[in]  c  The coefficient of the second order term.
 *  @param[in]  d  The coefficient of the first order term.
 *  @param[in]  e  The constant term.
 */
NCT_EXPIMP unsigned int numberOfRealDinstinctRoots(double a, double b, double c, double d, double e);

}}

////////// Template functions //////////
#include <nct/math/math_template.h>

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
