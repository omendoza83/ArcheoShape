//=================================================================================================================
/**
 *  @file       math_functions.h
 *  @brief      Mathematical functions of the nct::math namespace.
 *  @details    Declaration of the mathematical functions of the nct::math namespace.
 *  @author     Omar Mendoza Montoya (email: omendoz@live.com.mx).
 *  @copyright  Copyright (c) 2016 Omar Mendoza Montoya \n \n
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

#ifndef NCT_MATH_FUNCTIONS_H_INCLUDE
#define NCT_MATH_FUNCTIONS_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/nct_constants.h>
#include <functional>

//=================================================================================================================
namespace nct {
namespace math {

////////// Structures //////////

/**
 *  @brief      Jacobian elliptic function evaluation.
 *  @details    This structure defines the elements obtained by evaluating the 
 *              Jacobian elliptic function.
 */
struct NCT_EXPIMP JacobianEllipticFunction {

    double sn {0};  /**< The result obtained by evaluating the sn. */

    double cn {0};  /**< The result obtained by evaluating the cn. */

    double dn {0};  /**< The result obtained by evaluating the dn. */
};

/**
 *  @brief      Bessen jy function evaluation.
 *  @details    This structure defines the elements obtained by evaluating a
 *              Bessel jy function.
 */
struct NCT_EXPIMP BesseljyFunction {

    double j {0};   /**< Evaluation of Jn(x).  */

    double y {0};   /**< Evaluation of Yn(x).  */ 
        
    double jp {0};  /**< Evaluation of Jn'(x).  */
    
    double yp {0};  /**< Evaluation of Yn'(x).  */
};

/**
 *  @brief      Bessen ik function evaluation.
 *  @details    This structure defines the elements obtained by evaluating a
 *              Bessel ik function.
 */
struct NCT_EXPIMP BesselikFunction {

    double i {0};   /**< Evaluation of In(x).  */

    double k {0};   /**< Evaluation of Kn(x).  */

    double ip {0};  /**< Evaluation of In'(x).  */

    double kp {0};  /**< Evaluation of Kn'(x).  */
};

/**
 *  @brief      Airy function evaluation.
 *  @details    This structure defines the elements obtained by evaluating a
 *              Airy function.
 */
struct NCT_EXPIMP AiryFunction {

    double ai {0};  /**< Evaluation of Ai(x).  */

    double bi {0};  /**< Evaluation of Bi(x).  */

    double aip {0}; /**< Evaluation of Ai'(x).  */

    double bip {0}; /**< Evaluation of Bi'(x).  */
};

////////// General purpose functions //////////

/**
 *  @brief      Halton function.
 *  @details    This function evaluates the Halton function for one sample index and one dimension.
 *  @param[in]  i  The sample index to be evaluated.
 *  @param[in]  j  The index of the dimension to be evaluated.
 *  @returns    The value of the Halton function.
 */
NCT_EXPIMP double halton(unsigned int i, unsigned int j);

/**
 *  @brief      Evaluate continued fraction.
 *  @details    This function evaluates a continued fraction, which is defined in the following way:
 *              b0 + a1/(b1 + a2/(b2 + a3/(b3 + a4/(b4 + ...)))).
 *  @param[in]  a  Function that is used to evaluate ai, where i = 1,2,3,4,...
 *  @param[in]  b  Function that is used to evaluate bi, where i = 0,1,2,3,4,...
 *  @param[in]  tiny  Number that must be less than typical values of bj.
 *  @returns    The evaluation of the continued function.
 */
NCT_EXPIMP double continuedFraction(const std::function<double(unsigned int)>& a,
    const std::function<double(unsigned int)>& b, double tiny = EPS_100);

/**
 *  @brief      Evaluate continued complex fraction.
 *  @details    This function evaluates a continued fraction, which is defined in the following way:
 *              b0 + a1/(b1 + a2/(b2 + a3/(b3 + a4/(b4 + ...)))).
 *  @param[in]  a  Function that is used to evaluate ai, where i = 1,2,3,4,...
 *  @param[in]  b  Function that is used to evaluate bi, where i = 0,1,2,3,4,...
 *  @param[in]  tiny  Number that must be less than typical values of bj.
 *  @returns    The evaluation of the continued function.
 */
NCT_EXPIMP Complex continuedFraction(const std::function<Complex(unsigned int)>& a,
    const std::function<Complex(unsigned int)>& b, double tiny = EPS_100);

////////// Special functions //////////

/**
 *  @brief      Sinc function.
 *  @details    This function evaluates the sinc function, that is defined in the following way:
 *              sin(x)/x if x !=0, and 1 if x = 1.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the sinc function at the specified point.
 */
NCT_EXPIMP double sinc(double x);

/**
 *  @brief      Error function (ERF).
 *  @details    This function evaluates the ERF function.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the ERF function at the specified point.
 */
NCT_EXPIMP double erf(double x);

/**
 *  @brief      Complementary error function (ERF).
 *  @details    This function evaluates the complementary ERF function.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the complementary ERF function at the specified point.
 */
NCT_EXPIMP double erfc(double x);

/**
 *  @brief      Inverse of the error function.
 *  @details    This function evaluates the inverse of the ERF function.
 *  @param[in]  p  The point to be evaluated.
 *  @returns    The evaluation of the inverse of the ERF function at the specified point.
 */
NCT_EXPIMP double inverf(double p);

/**
 *  @brief      Inverse of the complementary error function.
 *  @details    This function evaluates the inverse of the complementary ERF function.
 *  @param[in]  p  The point to be evaluated.
 *  @returns    The evaluation of the inverse of the complementary ERF function at the specified point.
 */
NCT_EXPIMP double inverfc(double p);

/**
 *  @brief      Logarithm of the Gamma function.
 *  @details    This function evaluates the logarithm of the Gamma function
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the logarithm of the Gamma function at the specified point.
 */
NCT_EXPIMP double gammaln(double x);

/**
 *  @brief      Incomplete gamma function.
 *  @details    This function evaluates the incomplete Gamma function.
 *  @param[in]  x  The point to be evaluated.
 *  @param[in]  alpha  Alpha parameter in the Gamma function.
 *  @returns    The evaluation of the incomplete Gamma function at the specified point.
 */
NCT_EXPIMP double gammap(double x, double alpha);

/**
 *  @brief      Right tail of the Incomplete gamma function.
 *  @details    This function evaluates the right tail of the incomplete Gamma function.
 *  @param[in]  x  The point to be evaluated.
 *  @param[in]  alpha  Alpha parameter in the Gamma function.
 *  @returns    The evaluation of the right tail of the incomplete Gamma function at the specified point.
 */
NCT_EXPIMP double gammaq(double x, double alpha);

/**
 *  @brief      Inverse gamma function.
 *  @details    This function evaluates the inverse Gamma function.
 *  @param[in]  p  The point to be evaluated.
 *  @param[in]  alpha  Alpha parameter in the Gamma function.
 *  @returns    The evaluation of the inverse Gamma function at the specified point.
 */
NCT_EXPIMP double invgamma(double p, double alpha);

/**
 *  @brief      Beta function.
 *  @details    This function evaluates the Beta function.
 *  @param[in]  alpha  Alpha parameter in the Beta function.
 *  @param[in]  beta  Beta parameter in the Beta function.
 *  @returns    The evaluation of the Beta function at the specified point.
 */
NCT_EXPIMP double beta(double alpha, double beta);

/**
 *  @brief      Incomplete Beta function.
 *  @details    This function evaluates the Incomplete Beta function.
 *  @param[in]  x  The point to be evaluated.
 *  @param[in]  alpha  Alpha parameter in the Beta function.
 *  @param[in]  beta  Beta parameter in the Beta function.
 *  @returns    The evaluation of the Incomplete Beta function at the specified point.
 */
NCT_EXPIMP double betai(double x, double alpha, double beta);

/**
 *  @brief      Inverse of the Incomplete Beta function.
 *  @details    This function evaluates the Inverse of the Incomplete Beta function.
 *  @param[in]  p  The point to be evaluated.
 *  @param[in]  alpha  Alpha parameter in the Beta function.
 *  @param[in]  beta  Beta parameter in the Beta function.
 *  @returns    The evaluation of the Inverse of the Incomplete Beta function at the specified point.
 */
NCT_EXPIMP double invbetai(double p, double alpha, double beta);

/**
 *  @brief      Exponential integral function.
 *  @details    This function evaluates the integral from x to Inf of (exp(-t)/t) dt, for x > 0.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double expint(double x);

/**
 *  @brief      Exponential integral function.
 *  @details    This function evaluates the integral from z to Inf of (exp(-t)/t) dt for z complex.
 *  @param[in]  z  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP Complex expint(Complex x);

////////// Elliptic functions //////////    

/**
 *  @brief      Elliptic integral of the first kind.
 *  @details    This function evaluates the Carlson's elliptic integral of the first kind.
 *  @param[in]  x  The x coordinate of the point to be evaluated.
 *  @param[in]  y  The y coordinate of the point to be evaluated.
 *  @param[in]  z  The z coordinate of the point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double ellirf(double x, double y, double z);

/**
 *  @brief      Elliptic integral of the second kind.
 *  @details    This function evaluates the Carlson's elliptic integral of the second kind.
 *  @param[in]  x  The x coordinate of the point to be evaluated.
 *  @param[in]  y  The y coordinate of the point to be evaluated.
 *  @param[in]  z  The z coordinate of the point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double ellird(double x, double y, double z);

/**
 *  @brief      Elliptic integral of the third kind.
 *  @details    This function evaluates the Carlson's elliptic integral of the third kind.
 *  @param[in]  x  The x coordinate of the point to be evaluated.
 *  @param[in]  y  The y coordinate of the point to be evaluated.
 *  @param[in]  z  The z coordinate of the point to be evaluated.
 *  @param[in]  p  The p coordinate of the point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double ellirj(double x, double y, double z, double p);

/**
 *  @brief      Degenerate elliptic integral.
 *  @details    This function evaluates the degenerate Carlson's elliptic integral.
 *  @param[in]  x  The x coordinate of the point to be evaluated.
 *  @param[in]  y  The y coordinate of the point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double ellirc(double x, double y);

/**
 *  @brief      Legendre elliptic integral of the first kind.
 *  @details    This function evaluates the degenerate Legendre elliptic integral of the first kind.
 *  @param[in]  phi  The phi coordinate of the point to be evaluated.
 *  @param[in]  k  The k value of the point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double ellif(double phi, double k);

/**
 *  @brief      Legendre elliptic integral of the second kind.
 *  @details    This function evaluates the degenerate Legendre elliptic integral of the second kind.
 *  @param[in]  phi  The phi coordinate of the point to be evaluated.
 *  @param[in]  k  The k value of the point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double ellie(double phi, double k);

/**
 *  @brief      Legendre elliptic integral of the third kind.
 *  @details    This function evaluates the degenerate Legendre elliptic integral of the third kind.
 *  @param[in]  phi  The phi coordinate of the point to be evaluated.
 *  @param[in]  n  The n value of the point to be evaluated.
 *  @param[in]  k  The k value of the point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double ellipi(double phi, double n, double k);

/**
 *  @brief      Jacobian elliptic functions.
 *  @details    This function evaluates the Jacobian elliptic function sn, cn and dn.
 *  @param[in]  u  The point to be evaluated.
 *  @param[in]  m  The value of 1-k*k.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP JacobianEllipticFunction sncndn(double u, double m);

////////// Bessel functions //////////

/**
 *  @brief      Bessel function J0(x).
 *  @details    This function evaluates the Bessel function J0(x) for any real x.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double besselj0(double x);

/**
 *  @brief      Bessel function J1(x).
 *  @details    This function evaluates the Bessel function J1(x) for any real x.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double besselj1(double x);

/**
 *  @brief      Bessel function Jn(x).
 *  @details    This function evaluates the Bessel function Jn(x) for any real x.
 *  @param[in]  n  Order of the bessel function.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double besseljn(int n, double x);

/**
 *  @brief      Bessel function Y0(x).
 *  @details    This function evaluates the Bessel function Y0(x) for positive real x.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double bessely0(double x);

/**
 *  @brief      Bessel function Y1(x).
 *  @details    This function evaluates the Bessel function Y1(x) for positive real x.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double bessely1(double x);

/**
 *  @brief      Bessel function Yn(x).
 *  @details    This function evaluates the Bessel function Yn(x) for positive real x.
 *  @param[in]  n  Order of the bessel function.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double besselyn(int n, double x);

/**
 *  @brief      Bessel function I0(x).
 *  @details    This function evaluates the Bessel function I0(x) for any real x.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double besseli0(double x);

/**
 *  @brief      Bessel function I1(x).
 *  @details    This function evaluates the Bessel function I1(x) for any real x.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double besseli1(double x);

/**
 *  @brief      Bessel function In(x).
 *  @details    This function evaluates the Bessel function In(x) for any real x.
 *  @param[in]  n  Order of the bessel function.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double besselin(int n, double x);

/**
 *  @brief      Bessel function K0(x).
 *  @details    This function evaluates the Bessel function K0(x) for positive real x.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double besselk0(double x);

/**
 *  @brief      Bessel function K1(x).
 *  @details    This function evaluates the Bessel function K1(x) for positive real x.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double besselk1(double x);

/**
 *  @brief      Bessel function Kn(x).
 *  @details    This function evaluates the Bessel function Kn(x) for positive real x.
 *  @param[in]  n  Order of the bessel function.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double besselkn(int n, double x);

/**
 *  @brief      Bessel function Jn(x) and Yn(x).
 *  @details    This function evaluates Bessel functions Jn(x) and Yn(x) and their num_differentiation.
 *  @param[in]  n  Order of the bessel function.
 *  @param[in]  x  The point to be evaluated. 
 *  @returns    The result of the function evaluation. 
 */
NCT_EXPIMP BesseljyFunction besseljy(double n, double x);

/**
 *  @brief      Bessel function In(x) and Kn(x).
 *  @details    This function evaluates Bessel functions In(x) and Kn(x) and their num_differentiation.
 *  @param[in]  n  Order of the bessel function.
 *  @param[in]  x  The point to be evaluated. 
 *  @returns    The result of the function evaluation. 
 */
NCT_EXPIMP BesselikFunction besselik(double n, double x);

/**
 *  @brief      Airy functions.
 *  @details    This function evaluates Airy functions Ai(x) and Bi(x) and their num_differentiation.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The result of the function evaluation.  
 */
NCT_EXPIMP AiryFunction airy(double x);

/**
 *  @brief      Spherical bessel function Jn(x) and Yn(x).
 *  @details    This function evaluates spherical Bessel functions Jn(x) and Yn(x) and their
 *              num_differentiation.
 *  @param[in]  n  Order of the spherical bessel function.
 *  @param[in]  x  The point to be evaluated. 
 *  @returns    The result of the function evaluation.  
 */
NCT_EXPIMP BesseljyFunction sphericalBessel(double n, double x);

////////// Chebyshev polynomials //////////    

/**
 *  @brief      Chebyshev polynomial of the first kind.
 *  @details    This function evaluates the Chebyshev polynomial of the first kind for any real x.
 *  @param[in]  n  Order of the polynomial.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double chebyshevPolFirst(int n, double x);

/**
 *  @brief      Chebyshev polynomial of the first kind.
 *  @details    This function evaluates the Chebyshev polynomial of the first kind for any complex z.
 *  @param[in]  n  Order of the polynomial.
 *  @param[in]  z  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP Complex chebyshevPolFirst(int n, Complex x);

/**
 *  @brief      Chebyshev polynomial of the second kind.
 *  @details    This function evaluates the Chebyshev polynomial of the second kind for any real x.
 *  @param[in]  n  Order of the polynomial.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double chebyshevPolSecond(int n, double x);

/**
 *  @brief      Chebyshev polynomial of the second kind.
 *  @details    This function evaluates the Chebyshev polynomial of the second kind for any complex z.
 *  @param[in]  n  Order of the polynomial.
 *  @param[in]  z  The point to be evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP Complex chebyshevPolSecond(int n, Complex x);

////////// Legrende polynomials //////////

/**
 *  @brief      Renormalized associated Legendre polynomial.
 *  @details    This function computes the renormalized associated Legendre polynomial (magnitud of
 *              Spherical Harmonic functions). Here m and l are integers satisfying 0<=m<=l, while x lies
 *              in the range -1<=x<=1.
 *  @param[in]  l  Order of the polynomial.
 *  @param[in]  m  Order of the polynomial.
 *  @param[in]  x  Point where the functions is evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double spLegendre(int l, int m, double x);

/**
 *  @brief      Legendre polynomial.
 *  @details    This function computes the Legendre polynomial of order l and m. Here m and l are integers 
 *              satisfying 0<=m<=l, while x lies in the range -1<=x<=1.
 *  @param[in]  l  Degree of the polynomial.
 *  @param[in]  m  Order of the polynomial.
 *  @param[in]  x  Point where the functions is evaluated.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP double legendre(int l, int m, double x);

////////// Spherical harmonics //////////

/**
 *  @brief      Spherical Harmonic.
 *  @details    This function computes the spherical harmonic of order l and m at the specified point.
 *  @param[in]  l  Degree of the function.
 *  @param[in]  m  Order of the function.
 *  @param[in]  theta  Longitudinal angle, for which 0 <= theta < 2*PI.
 *  @param[in]  phi  Polar angle, for which 0 <= theta <= PI.
 *  @returns    The evaluation of the function.
 */
NCT_EXPIMP Complex sphericalHarmonic(int l, int m, double theta, double phi);

}}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
