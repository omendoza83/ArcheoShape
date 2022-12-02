//=================================================================================================================
/**
 *  @file       math_functions.cpp
 *  @brief      Implementation of the mathematical functions defined in the nct::math namespace.
 *  @details    This file contains the implementation of the functions declared in the
 *              nct::math namespace. 
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


//=================================================================================================================
//        HEADERS AND NAMESPACES
//=================================================================================================================
#include <nct/math/math_functions.h>
#include <nct/math/math.h>
#include <array>

//=================================================================================================================
//        STRUCTURES
//=================================================================================================================

namespace nct {

/**
 *  @brief      Rational aproximation.
 *  @details    This structure defines the elements obtained by computing a
 *              rational approximation of the Bessen function.
 */
struct  RationalAproximation {

    double nump {0};    /**< Value of the numerator.  */

    double denp {0};    /**< Value of the denominator.  */

    double y {0};       /**< Value of x*x.  */

    double z {0};       /**< Value of 64.0-y.   */
};

/**
 *  @brief      Asintotic aproximation.
 *  @details    This structure defines the elements obtained by computing an
 *              asintotic approximation of the Bessen function.
 */
struct  AsintoticAproximation {

    double nump {0};    /**< Value of numerator P.  */

    double denp {0};    /**< Value of denominator P.  */

    double numq {0};    /**< Value of numerator P.  */

    double denq {0};    /**< Value of denominator P.  */

    double y {0};       /**< Value of z*z  */

    double z {0};       /**< Value of8.0/ax.   */

    double xx {0};      /**< Value of ax-fac*pi/4.  */
};

}

//=================================================================================================================
//        AUXILIAR FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Evaluation of the ERF function by using Chebyshev coefficients.
 *  @details    This function evaluates the ERF function by using Chebyshev coefficients.
 *  @param[in]  z  The point to be evaluated.
 *  @returns    The evaluation of the ERF function at the specified point.
 */
static double erfccheb(double z)
{
    // Coefficients to calculate the ERF function.
    static constinit const std::array coeff
    {
        -1.3026537197817094, 6.4196979235649026e-1, 1.9476473204185836e-2, -9.561514786808631e-3,
        -9.46595344482036e-4, 3.66839497852761e-4, 4.2523324806907e-5,-2.0278578112534e-5,
        -1.624290004647e-6, 1.303655835580e-6, 1.5626441722e-8, -8.5238095915e-8, 6.529054439e-9,
        5.059343495e-9, -9.91364156e-10, -2.27365122e-10, 9.6467911e-11, 2.394038e-12, -6.886027e-12,
        8.94487e-13, 3.13092e-13, -1.12708e-13, 3.81e-16, 7.106e-15, -1.523e-15, -9.4e-17, 1.21e-16,-2.8e-17
    };

    if (z < 0.) 
        throw nct::ArgumentException("z", z, 0., 
        nct::RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    double d = 0., dd = 0.;
    auto t = 2./(2.+z);
    auto ty = 4.*t - 2.;
    for (int j=static_cast<int>(coeff.size())-1;j>0;j--) {
        auto tmp = d;
        d = ty*d - dd + coeff[j];
        dd = tmp;
    }
    return t*exp(-z*z + 0.5*(coeff[0] + ty*d) - dd);
}

//-----------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Evaluation of the incomplete Gamma function by using series expansion.
 *  @details    This function evaluates the incomplete Gamma function by using series expansion.
 *  @param[in]  alpha  Alpha parameter in the Gamma function.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the incomplete Gamma function at the specified point.
 */
static double gser(double alpha, double x) 
{
    double sum, el, ap;
    double gln = nct::math::gammaln(alpha);

    ap=alpha;
    el=sum=1.0/alpha;
    for (;;) {
        ++ap;
        el *= x/ap;
        sum += el;
        if (std::abs(el) < std::abs(sum)*nct::EPS_100) {
            return sum*exp(-x+alpha*log(x)-gln);
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Evaluation of the incomplete Gamma function by using fractions.
 *  @details    This function evaluates the incomplete Gamma function by using fractions.
 *  @param[in]  alpha  Alpha parameter in the Gamma function.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the incomplete Gamma function at the specified point.
 */
static double gcf(double alpha, double x) 
{
    auto gln = nct::math::gammaln(alpha);

    auto b=x+1.0-alpha;
    auto c = 1.0 / nct::SMALL_FP;
    auto d=1.0/b;
    auto h=d;
    for (int i=1;;i++) {
        auto an = -i*(i-alpha);
        b += 2.0;
        d=an*d+b;
        if (std::abs(d) < nct::SMALL_FP)
            d = nct::SMALL_FP;
        c=b+an/c;
        if (std::abs(c) < nct::SMALL_FP)
            c = nct::SMALL_FP;
        d=1.0/d;
        auto el=d*c;
        h *= el;
        if (std::abs(el - 1.0) <= nct::EPS_100)
            break;
    }
    return exp(-x+alpha*log(x)-gln)*h;
}

//-----------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Evaluation of the incomplete Gamma function by using the Gauss-Legrenge quadrature.
 *  @details    This function evaluates the incomplete Gamma function by using the Gauss-Legrenge quadrature.
 *  @param[in]  alpha  Alpha parameter in the Gamma function.
 *  @param[in]  x  The point to be evaluated.
 *  @param[in]  sgn  1 to calculate P or 0 to calculate Q.
 *  @returns    The evaluation of the incomplete Gamma function at the specified point.
 */
static double gammpapprox(double alpha, double x, int sgn) 
{
    // Coefficients to calculate the gamma function.
    static constinit const std::array coeffy
    {        
        0.0021695375159141994, 0.011413521097787704, 0.027972308950302116, 0.051727015600492421,
        0.082502225484340941, 0.12007019910960293, 0.16415283300752470, 0.21442376986779355,
        0.27051082840644336, 0.33199876341447887, 0.39843234186401943, 0.46931971407375483,
        0.54413605556657973, 0.62232745288031077, 0.70331500465597174, 0.78649910768313447,
        0.87126389619061517, 0.95698180152629142
        
    };

    // Weights to calculate the gamma function.
    static constinit const std::array coeffw
    {        
        0.0055657196642445571, 0.012915947284065419, 0.020181515297735382, 0.027298621498568734,
        0.034213810770299537, 0.040875750923643261, 0.047235083490265582, 0.053244713977759692,
        0.058860144245324798, 0.064039797355015485, 0.068745323835736408, 0.072941885005653087,
        0.076598410645870640, 0.079687828912071670, 0.082187266704339706, 0.084078218979661945,
        0.085346685739338721, 0.085983275670394821        
    };

    auto a1 = alpha - 1.0;
    auto lna1 = log(a1);
    auto sqrta1 = std::sqrt(a1);
    auto gln = nct::math::gammaln(alpha);
    
    double xu = 0;
    if (x > a1) 
        xu = nct::math::max(a1 + 11.5*sqrta1, x + 6.0*sqrta1);
    else 
        xu = nct::math::max(0., nct::math::min(a1 - 7.5*sqrta1, x - 5.0*sqrta1));
    
    double sum = 0;
    for (nct::index_t j=0;j<coeffy.size();j++) {
        auto t = x + (xu-x)*coeffy[j];
        sum += coeffw[j]*exp(-(t-a1)+a1*(log(t)-lna1));
    }

    auto ans = sum*(xu-x)*exp(a1*(lna1-1.)-gln);
    return (sgn?(ans>0.0? 1.0-ans:-ans):(ans>=0.0? ans:1.0+ans));
}

//-----------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Evaluation of the Beta function by using the Lentz method.
 *  @details    This function evaluates the Beta function by using the Lentz method.
 *  @param[in]  alpha  Alpha parameter in the Beta function.
 *  @param[in]  beta  Beta parameter in the Beta function.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the Beta function at the specified point.
 */
static double betacf(double alpha, double beta, double x) 
{
    static constinit const int maxIt {10000};

    auto qab=alpha+beta;
    auto qap=alpha+1.0;
    auto qam=alpha-1.0;
    auto c=1.0;
    auto d=1.0-qab*x/qap;
    
    if (std::abs(d) < nct::SMALL_FP)
        d = nct::SMALL_FP;
    d=1.0/d;
    
    auto h=d;
    for (int m=1;m<maxIt;m++) {
        auto m2=2*m;
        auto aa=m*(beta-m)*x/((qam+m2)*(alpha+m2));
        d=1.0+aa*d;
        if (std::abs(d) < nct::SMALL_FP)
            d = nct::SMALL_FP;
        c=1.0+aa/c;
        if (std::abs(c) < nct::SMALL_FP)
            c = nct::SMALL_FP;
        d=1.0/d;
        h *= d*c;
        aa = -(alpha+m)*(qab+m)*x/((alpha+m2)*(qap+m2));
        d=1.0+aa*d;
        if (std::abs(d) < nct::SMALL_FP)
            d = nct::SMALL_FP;
        c=1.0+aa/c;
        if (std::abs(c) < nct::SMALL_FP)
            c = nct::SMALL_FP;
        d=1.0/d;
        auto el=d*c;
        h *= el;
        if (std::abs(el - 1.0) <= nct::EPS_100)
            break;
    }
    return h;
}

//-----------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Evaluation of the Beta function by using the Gauss-Legrenge quadrature.
 *  @details    This function evaluates the Beta function by using the Gauss-Legrenge quadrature.
 *  @param[in]  alpha  Alpha parameter in the Beta function.
 *  @param[in]  beta  Beta parameter in the Beta function.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the Beta function at the specified point.
 */
static double betaiapprox(double alpha, double beta, double x) 
{
    // Coefficients to calculate the beta function
    static constinit const std::array coeffy
    {        
        0.0021695375159141994, 0.011413521097787704, 0.027972308950302116, 0.051727015600492421,
        0.082502225484340941, 0.12007019910960293, 0.16415283300752470, 0.21442376986779355,
        0.27051082840644336, 0.33199876341447887, 0.39843234186401943, 0.46931971407375483,
        0.54413605556657973, 0.62232745288031077, 0.70331500465597174, 0.78649910768313447,
        0.87126389619061517, 0.95698180152629142
    };

    // Weights to calculate the beta function
    static constinit const std::array coeffw
    {        
        0.0055657196642445571, 0.012915947284065419, 0.020181515297735382, 0.027298621498568734,
        0.034213810770299537, 0.040875750923643261, 0.047235083490265582, 0.053244713977759692,
        0.058860144245324798, 0.064039797355015485, 0.068745323835736408, 0.072941885005653087,
        0.076598410645870640, 0.079687828912071670, 0.082187266704339706, 0.084078218979661945,
        0.085346685739338721, 0.085983275670394821        
    };

    double a1 = alpha - 1.0;
    double b1 = beta - 1.0;
    double mu = alpha / (alpha + beta);
    double lnmu=log(mu), lnmuc=log(1.-mu);

    double xu = 0;
    auto t = std::sqrt(alpha*beta/(nct::math::sqr(alpha+beta)*(alpha+beta+1.0)));
    if (x > alpha/(alpha+beta)) {
        if (x >= 1.0) 
            return 1.0;
        xu = nct::math::min(1., nct::math::max(mu + 10.*t, x + 5.0*t));
    } 
    else  {
        if (x <= 0.0) 
            return 0.0;
        xu = nct::math::max(0., nct::math::min(mu - 10.*t, x - 5.0*t));
    }

    double sum = 0;
    for (int j=0;j<static_cast<int>(coeffy.size());j++) {
        t = x + (xu-x)*coeffy[j];
        sum += coeffw[j]*exp(a1*(log(t)-lnmu)+b1*(log(1-t)-lnmuc));
    }

    auto ans = sum*(xu-x)*exp(a1*lnmu-nct::math::gammaln(alpha)+b1*lnmuc-
        nct::math::gammaln(beta)+nct::math::gammaln(alpha+beta));
    return ans>0.0? 1.0-ans : -ans;
}

//-----------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Rational approximation.
 *  @details    This function evaluates the rational approximation of the Bessen function.
 *  @param[in]  x  The point to be evaluated.
 *  @param[in]  r  Coefficients of the polynomial of the numerator.
 *  @param[in]  s  Coefficients of the polynomial of the denominator.
 *  @param[in]  n  Point to be evaluated.
 */
static nct::RationalAproximation rat(double x, const double* r, const double* s, int n) noexcept
{
    nct::RationalAproximation feval;

    feval.y = x*x;
    feval.z=64.0- feval.y;
    feval.nump=r[n];
    feval.denp=s[n];
    for (int i=n-1;i>=0;i--) {
        feval.nump= feval.nump * feval.z+r[i];
        feval.denp= feval.denp * feval.y+s[i];
    }

    return feval;
}

//-----------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Asintotic approximation.
 *  @details    This function evaluates the asintotic approximation of a Bessen function.
 *  @param[in]  pn  Coefficients of the numerator of P.
 *  @param[in]  pd  Coefficients of the denominator of P.
 *  @param[in]  qn  Coefficients of the numerator of Q.
 *  @param[in]  qd  Coefficients of the denominator of Q.
 *  @param[in]  fac  Factor in multiplication.
 *  @param[in]  ax  The point to be evaluated.
 */
static nct::AsintoticAproximation asp(const double* pn, const double* pd, const double* qn, const double* qd,
    double fac, double ax) noexcept 
{
    nct::AsintoticAproximation feval;
    feval.z=8.0/ax;
    feval.y= feval.z* feval.z;
    feval.xx = ax - fac*nct::PI_DIV_FOUR;
    feval.nump=pn[4];
    feval.denp=pd[4];
    feval.numq=qn[4];
    feval.denq=qd[4];
    for (int i=3;i>=0;i--) {
        feval.nump = feval.nump * feval.y + pn[i];
        feval.denp = feval.denp * feval.y + pd[i];
        feval.numq = feval.numq * feval.y + qn[i];
        feval.denq = feval.denq * feval.y + qd[i];
    }    

    return feval;
}

//-----------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Polynomial.
 *  @details    This function evaluates a polynomial.
 *  @param[in]  cof  Coefficients of the polynomial.
 *  @param[in]  n  Degree of the polynomial.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the polynomial at the specified point.
 */
static double poly(const double* cof, int n, double x) noexcept
{
    double ans = cof[n];
    for (int i=n-1;i>=0;i--) 
        ans = ans*x+cof[i];
    return ans;
}

//-----------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Chebyshev series.
 *  @details    Utility used to evaluate chebyshev series.
 *  @param[in]  c  Coefficients of the serie.
 *  @param[in]  m  Degree of the serie.
 *  @param[in]  x  The point to be evaluated.
 *  @returns    The evaluation of the serie at the specified point.
 */
static double chebev(const double *c, int m, double x) noexcept
{
    double d=0.0,dd=0.0,sv;
    int j;
    for (j=m-1;j>0;j--) {
        sv=d;
        d=2.*x*d-dd+c[j];
        dd=sv;
    
    }
    return x*d-dd+0.5*c[0];
}

//=================================================================================================================
//        FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
double nct::math::sinc(double x)
{
    if (x == 0)
        return 1;
    return std::sin(x) / x;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::erf(double x)
{
    if (x >=0.) 
        return 1.0 - erfccheb(x);
    else 
        return erfccheb(-x) - 1.0;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::erfc(double x)
{
    if (x >= 0.) 
        return erfccheb(x);
    else 
        return 2.0 - erfccheb(-x);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::inverf(double p)
{
    return inverfc(1.-p);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::inverfc(double p)
{
    if (p <= 0.0 || p >= 2.0) 
        throw ArgumentException("p", p, 0., 2.0,
        RelationalOperator::GreaterThan, 
        RelationalOperator::LowerThan, SOURCE_INFO);    
    
    auto pp = (p < 1.0)? p : 2. - p;
    auto t = std::sqrt(-2.*log(pp/2.));
    auto x = -INV_SQRT2*((2.30753+t*0.27061)/(1.+t*(0.99229+t*0.04481)) - t);
    for (int j=0;j<2;j++) {
        auto err = erfc(x) - pp;
        x += err/(1.12837916709551257*exp(-(x*x))-x*err);
    }
    return (p < 1.0? x : -x);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::gammaln(double x)
{
    // Weights to calculate the log-gamma function.
    static constinit const std::array coeff
    {        
        57.1562356658629235, -59.5979603554754912, 14.1360979747417471, -0.491913816097620199,
        0.339946499848118887e-4, 0.465236289270485756e-4, -0.983744753048795646e-4,
        0.158088703224912494e-3, -0.210264441724104883e-3, 0.217439618115212643e-3,
        -0.164318106536763890e-3, 0.844182239838527433e-4, -0.261908384015814087e-4,
        0.368991826595316234e-5        
    };

    if (x <= 0) 
        throw ArgumentException("x", x, 0.,
        RelationalOperator::GreaterThan, SOURCE_INFO);
    
    auto y=x;
    
    auto tmp = x+5.24218750000000000; 
    tmp = (x+0.5)*log(tmp)-tmp;

    auto ser = 0.999999999999997092;
    for (nct::index_t j=0; j< coeff.size(); j++)
        ser += coeff[j]/++y;

    return tmp+log(2.5066282746310005*ser/x);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::gammap(double x, double alpha)
{
    if (x < 0.0) 
        throw ArgumentException("x", x, 0.,
        RelationalOperator::GreaterThanOrEqualTo, 
            SOURCE_INFO);
    if (alpha <= 0.0) 
        throw ArgumentException("alpha", alpha, 0.,
        RelationalOperator::GreaterThan, 
            SOURCE_INFO);
    
    if (x == 0.0) 
        return 0.0;
    else if (alpha >= 100) 
        return gammpapprox(alpha, x, 1);    // Quadrature.
    else if (x < alpha+1.0) 
        return gser(alpha, x);              // Expansion in series.

    return 1.0-gcf(alpha, x);               // Fractions.
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::gammaq(double x, double alpha)
{
    if (x < 0.0) 
        throw ArgumentException("x", x, 0.,
        RelationalOperator::GreaterThanOrEqualTo, 
        SOURCE_INFO);
    if (alpha <= 0.0) 
        throw ArgumentException("alpha", alpha, 0.,
        RelationalOperator::GreaterThan, 
        SOURCE_INFO);

    if (x == 0.0) 
        return 1.0;
    else if (alpha >= 100) 
        return gammpapprox(alpha, x, 0);     // Quadrature.
    else if (x < alpha+1.0) 
        return 1.0-gser(alpha, x);            // Expansion in series.

    return gcf(alpha, x);                     // Fractions.
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::invgamma(double p, double alpha)
{
    static const double eps = std::sqrt(EPS);

    if (alpha <= 0.) 
        throw ArgumentException("alpha", alpha, 0.,
        RelationalOperator::GreaterThan, 
            SOURCE_INFO);

    if (p >= 1.) 
        return math::max(100.,alpha + 100.*std::sqrt(alpha));
    if (p <= 0.) 
        return 0.0;
    
    double x = 0;
    double lna1 = 1;
    double afac = 1;
    double a1 = alpha - 1;
    double gln = gammaln(alpha);
    
    if (alpha > 1.) {
        lna1=log(a1);
        afac = exp(a1*(lna1-1.)-gln);
        auto pp = (p < 0.5)? p : 1. - p;
        auto t = std::sqrt(-2.*log(pp));
        x = (2.30753+t*0.27061)/(1.+t*(0.99229+t*0.04481)) - t;
        if (p < 0.5) x = -x;
        x = math::max(1.e-3, alpha*std::pow(1.-1./(9.*alpha)-x/(3.*std::sqrt(alpha)),3));
    }
    else  {
        auto t = 1.0 - alpha*(0.253+alpha*0.12);
        if (p < t) 
            x = std::pow(p/t,1./alpha);
        else 
            x = 1.-log(1.-(p-t)/(1.-t));
    }

    for (int j=0;j<12;j++) {
        if (x <= 0.0) 
            return 0.0;
        auto err = gammap(x,alpha) - p;

        double t = 0;
        if (alpha > 1.) 
            t = afac*exp(-(x-a1)+a1*(log(x)-lna1));
        else 
            t = exp(-x+a1*log(x)-gln);

        auto u = err/t;
        x -= (t = u/(1.-0.5*math::min(1.,u*((alpha-1.)/x - 1)))); 
        if (x <= 0.) 
            x = 0.5*(x + t);         
        if (std::abs(t) < eps*x) 
            break;
    }
    return x;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::beta(double alpha, double beta)
{
    return exp(gammaln(alpha)+gammaln(beta)-gammaln(alpha+beta));
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::betai(double x, double alpha, double beta)
{
    if (alpha <= 0.0) 
        throw ArgumentException("alpha", alpha, 0., RelationalOperator::GreaterThan,
            SOURCE_INFO);
    if (beta <= 0.0) 
        throw ArgumentException("beta", alpha, 0., RelationalOperator::GreaterThan,
            SOURCE_INFO);

    if (x < 0.0 || x > 1.0) 
        throw ArgumentException("x", x, 0., 1., RelationalOperator::GreaterThanOrEqualTo,
        RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    if (x == 0.0 || x == 1.0) 
        return x;

    if (alpha > 300 && beta > 300) 
        return betaiapprox(alpha, beta, x);      // Quadrature.
    
    // Lentz method.
    auto bt = exp(gammaln(alpha+beta)-gammaln(alpha)-gammaln(beta)+alpha*log(x)+beta*log(1.0-x));
    if (x < (alpha+1.0)/(alpha+beta+2.0)) 
        return bt*betacf(alpha,beta,x)/alpha;
    return 1.0-bt*betacf(beta,alpha,1.0-x)/beta;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::invbetai(double p, double alpha, double beta)
{
    static const double eps = std::sqrt(EPS);

    double x = 0;
    double a1 = alpha - 1.;
    double b1 = beta - 1.;
    
    if (p <= 0.) {
        return 0.;
    }
    else if (p >= 1.) {
        return 1.;
    }
    else if (alpha >= 1. && beta >= 1.) {
        auto pp = (p < 0.5)? p : 1. - p;
        auto t = std::sqrt(-2.*log(pp));
        x = (2.30753+t*0.27061)/(1.+t*(0.99229+t*0.04481)) - t;
        if (p < 0.5) 
            x = -x;
        auto al = (math::sqr(x)-3.)/6.;
        auto h = 2./(1./(2.*alpha-1.)+1./(2.*beta-1.));
        auto w = (x*std::sqrt(al+h)/h)-(1./(2.*beta-1)-1./(2.*alpha-1.))*(al+5./6.-2./(3.*h));
        x = alpha/(alpha+beta*exp(2.*w));
    } 
    else  {
        double lna = log(alpha/(alpha+beta)), lnb = log(beta/(alpha+beta));
        auto t = exp(alpha*lna)/alpha;
        auto u = exp(beta*lnb)/beta;
        auto w = t + u;
        if (p < t/w) 
            x = std::pow(alpha*w*p,1./alpha);
        else 
            x = 1. - std::pow(beta*w*(1.-p),1./beta);
    }

    auto afac = -gammaln(alpha)-gammaln(beta)+gammaln(alpha+beta);
    for (int j=0;j<10;j++) {
        if (x == 0. || x == 1.) 
            return x;

        auto err = betai(x, alpha,beta) - p;
        auto t = exp(a1*log(x)+b1*log(1.-x) + afac);
        auto u = err/t;
        x -= (t = u/(1.-0.5*math::min(1.,u*(a1/x - b1/(1.-x)))));
        if (x <= 0.) 
            x = 0.5*(x + t);
        if (x >= 1.) 
            x = 0.5*(x + t + 1.);
        if (std::abs(t) < eps*x && j > 0) 
            break;
    }
    return x;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::expint(double x)
{
    static constinit const double egamma {0.57721566490153286061};

    if (x < 0)
        throw ArgumentException("x", x, 0.0, RelationalOperator::GreaterThan, SOURCE_INFO);
    
    auto y = -egamma - std::log(x);    
    double j = 1;
    auto pterm = x;
    auto term = x;

    while (std::abs(term) >(nct::EPS*std::abs(y))) {
        y = y + term;
        j = j + 1;
        pterm = -x*pterm / j;
        term = pterm / j;
    }

    return y;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Complex nct::math::expint(Complex z)
{
    // Points used to calculate the exponential integral function.
    static constinit const std::array p {
        -3.602693626336023e-09, -4.819538452140960e-07, -2.569498322115933e-05,
        -6.973790859534190e-04, -1.019573529845792e-02, -7.811863559248197e-02,
        -3.012432892762715e-01, -7.773807325735529e-01,  8.267661952366478e+00 };

    static constinit const double egamma {0.57721566490153286061};

    auto polyv = poly(p.data(), static_cast<int>(p.size()), z.real());
    Complex y = 0;

    if (std::abs(z.imag()) <= polyv) {
        y = -egamma - std::log(z);
        double j = 1;
        auto pterm = z;
        auto term = z;

        while (std::abs(term) > (nct::EPS*std::abs(y))) {
            y = y + term;
            j = j + 1;
            pterm = -z*pterm / j;
            term = pterm / j;
        }
    }
    else {
        double n = 1; 
        double j = 2;

        Complex am2 = 0;
        Complex bm2 = 1;
        Complex am1 = 1;
        Complex bm1 = z;

        Complex f = am1/bm1;
        Complex oldf = PLUS_INF;        

        while (std::abs(f - oldf) > (100*nct::EPS*std::abs(f))) {
            double alpha = (n - 1) + (j / 2); 
            auto a = am1 + alpha * am2;
            auto b = bm1 + alpha * bm2;

            am2 = am1 / b;
            bm2 = bm1 / b;
            am1 = a / b;
            bm1 = 1;

            f = am1;
            j = j + 1;

            alpha = (j - 1) / 2;
            auto beta = z;
            a = beta*am1 + alpha * am2;
            b = beta*bm1 + alpha * bm2;
            am2 = am1/b;
            bm2 = bm1/b;
            am1 = a/b;
            bm1 = 1;
            oldf = f;
            f = am1;
            j = j + 1;
        }    
        
        y = std::exp(-z)*f - (nct::I1*PI)* (double)( (z.real()<0) && (z.imag() == 0) );
    }    

    return y;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::halton(unsigned int i, unsigned int j)
{
    // The first 100 prime numbers.
    static constinit const std::array primes
    {
        2,      3,      5,      7,     11,     13,     17,     19,     23,     29,
        31,     37,     41,     43,     47,     53,     59,     61,     67,     71,
        73,     79,     83,     89,     97,    101,    103,    107,    109,    113,
        127,    131,    137,    139,    149,    151,    157,    163,    167,    173,
        179,    181,    191,    193,    197,    199,    211,    223,    227,    229,
        233,    239,    241,    251,    257,    263,    269,    271,    277,    281,
        283,    293,    307,    311,    313,    317,    331,    337,    347,    349,
        353,    359,    367,    373,    379,    383,    389,    397,    401,    409,
        419,    421,    431,    433,    439,    443,    449,    457,    461,    463,
        467,    479,    487,    491,    499,    503,    509,    521,    523,    541
    };

    if (j >= primes.size())
        throw ArgumentException("j", exc_bad_halton_arguments, SOURCE_INFO);

    unsigned int p1 = primes[j];
    unsigned int p2 = p1;
    double x;
    double sum = 0;

    do {
        x = i % p1;
        sum = sum + x / p2;
        i = i / p1;
        p2 = p2 * p1;
    } while (i > 0);

    return sum;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::continuedFraction(const std::function<double(unsigned int)>& a,
    const std::function<double(unsigned int)>& b, double tiny)
{
    static constinit const unsigned int maxIt {500000};

    double f = b(0);
    if (f == 0)
        f = tiny;

    double c = f;
    double d = 0;
    double delta = PLUS_INF;

    unsigned int j = 0;
    while ((std::abs(delta - 1) >= EPS) && (j < maxIt)) {
        j++;
        d = b(j) + a(j)*d;
        if (d == 0)
            d = tiny;

        c = b(j) + a(j) / c;
        if (c == 0)
            c = tiny;

        d = 1.0 / d;
        delta = c * d;
        f = f * delta;
    }

    return f;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Complex nct::math::continuedFraction(const std::function<Complex(unsigned int)>& a,
    const std::function<Complex(unsigned int)>& b, double tiny)
{
    static constinit const unsigned int maxIt {500000};

    Complex f = b(0);
    if (f == 0.0)
        f = tiny;

    Complex c = f;
    Complex d = 0;
    Complex delta = PLUS_INF;

    unsigned int j = 0;
    while ((std::abs(delta - 1.0) >= EPS) && (j < maxIt)) {
        j++;
        d = b(j) + a(j)*d;
        if (d == 0.0)
            d = tiny;

        c = b(j) + a(j) / c;
        if (c == 0.0)
            c = tiny;

        d = 1.0 / d;
        delta = c * d;
        f = f * delta;
    }

    return f;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::ellirf(double x, double y, double z) 
{
    static constinit const double ERRTOL {0.0025};
    static constinit const double THIRD {1.0 / 3.0};
    static constinit const double C1 {1.0 / 24.0};
    static constinit const double C2 {0.1};
    static constinit const double C3 {3.0 / 44.0};
    static constinit const double C4 {1.0 / 14.0};
    static constinit const double TINY {5.0 * std::numeric_limits<double>::min()};
    static constinit const double BIG {0.2 * std::numeric_limits<double>::max()};

    if (x < 0)
        throw ArgumentException("x", x, 0.0, RelationalOperator::GreaterThan, SOURCE_INFO);

    if (y < 0)
        throw ArgumentException("y", y, 0.0, RelationalOperator::GreaterThan, SOURCE_INFO);

    if (z < 0)
        throw ArgumentException("z", z, 0.0, RelationalOperator::GreaterThan, SOURCE_INFO);

    if ((math::min(math::min(x + y, x + z), y + z) < TINY) || (math::max(math::max(x, y), z) > BIG))
        throw ArgumentException("x, y, z", exc_values_outside_bounds, SOURCE_INFO);

    auto xt = x;
    auto yt = y;
    auto zt = z;

    double ave = 0;
    double delx = PLUS_INF;
    double dely = PLUS_INF;
    double delz = PLUS_INF;
    while (math::max(math::max(std::abs(delx), std::abs(dely)), std::abs(delz)) > ERRTOL) {
        auto sqrtx = std::sqrt(xt);
        auto sqrty = std::sqrt(yt);
        auto sqrtz = std::sqrt(zt);
        auto alamb = sqrtx*(sqrty + sqrtz) + sqrty*sqrtz;
        xt = 0.25*(xt + alamb);
        yt = 0.25*(yt + alamb);
        zt = 0.25*(zt + alamb);
        ave = THIRD*(xt + yt + zt);
        delx = (ave - xt) / ave;
        dely = (ave - yt) / ave;
        delz = (ave - zt) / ave;
    }

    auto e2 = delx*dely - delz*delz;
    auto e3 = delx*dely*delz;
    return (1.0 + (C1*e2 - C2 - C3*e3)*e2 + C4*e3) / std::sqrt(ave);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::ellird(double x, double y, double z)
{
    static constinit const double ERRTOL {0.0015};
    static constinit const double C1 {3.0 / 14.0};
    static constinit const double C2 {1.0 / 6.0};
    static constinit const double C3 {9.0 / 22.0};
    static constinit const double C4 {3.0 / 26.0};
    static constinit const double C5 {0.25 * 9.0 / 22.0};
    static constinit const double C6 {1.5 * 3.0 / 26.0};
    static const double TINY {2.0 * std::pow(std::numeric_limits<double>::max(), -2. / 3.)};
    static const double BIG {0.1 * ERRTOL * std::pow(std::numeric_limits<double>::min(), -2. / 3.)};

    if (x < 0)
        throw ArgumentException("x", x, 0.0, RelationalOperator::GreaterThan, SOURCE_INFO);

    if (y < 0)
        throw ArgumentException("y", y, 0.0, RelationalOperator::GreaterThan, SOURCE_INFO);

    if ((math::min(x + y, z) < TINY) || (math::max(math::max(x, y), z) > BIG))
        throw ArgumentException("x, y, z", exc_values_outside_bounds, SOURCE_INFO);

    auto xt = x;
    auto yt = y;
    auto zt = z;
    double sum = 0.0;
    double fac = 1.0;
    
    double ave = 0;
    double delx = PLUS_INF;
    double dely = PLUS_INF;
    double delz = PLUS_INF;
    while (math::max(math::max(std::abs(delx), std::abs(dely)), std::abs(delz)) > ERRTOL) {
        auto sqrtx = std::sqrt(xt);
        auto sqrty = std::sqrt(yt);
        auto sqrtz = std::sqrt(zt);
        auto alamb = sqrtx*(sqrty + sqrtz) + sqrty*sqrtz;
        sum += fac / (sqrtz*(zt + alamb));
        fac = 0.25*fac;
        xt = 0.25*(xt + alamb);
        yt = 0.25*(yt + alamb);
        zt = 0.25*(zt + alamb);
        ave = 0.2*(xt + yt + 3.0*zt);
        delx = (ave - xt) / ave;
        dely = (ave - yt) / ave;
        delz = (ave - zt) / ave;
    } 

    auto ea = delx*dely;
    auto eb = delz*delz;
    auto ec = ea - eb;
    auto ed = ea - 6.0*eb;
    auto ee = ed + ec + ec;
    return 3.0*sum + fac*(1.0 + ed*(-C1 + C5*ed - C6*delz*ee)
        + delz*(C2*ee + delz*(-C3*ec + delz*C4*ea))) / (ave*std::sqrt(ave));
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::ellirj(double x, double y, double z, double p)
{
    static constinit const double ERRTOL {0.0015};
    static constinit const double C1 {3.0 / 14.0};
    static constinit const double C2 {1.0 / 3.0};
    static constinit const double C3 {3.0 / 22.0};
    static constinit const double C4 {3.0 / 26.0};
    static constinit const double C5 {0.75 * 3.0 / 22.0};
    static constinit const double C6 {1.5 * 3.0 / 26.0};
    static constinit const double C7 {0.5 / 3.0};
    static constinit const double C8 {3.0 / 11.0};
    static const double TINY {std::pow(5.0 * std::numeric_limits<double>::min(), 1. / 3.)};
    static const double BIG {0.3 * std::pow(0.2 * std::numeric_limits<double>::max(), 1. / 3.)};

    if (x < 0)
        throw ArgumentException("x", x, 0.0, RelationalOperator::GreaterThan, SOURCE_INFO);

    if (y < 0)
        throw ArgumentException("y", y, 0.0, RelationalOperator::GreaterThan, SOURCE_INFO);

    if (z < 0)
        throw ArgumentException("z", z, 0.0, RelationalOperator::GreaterThan, SOURCE_INFO);

    if ((math::min(math::min(x + y, x + z), math::min(y + z, std::abs(p))) < TINY) || 
        (math::max(math::max(x, y), math::max(z, std::abs(p))) > BIG))
        throw ArgumentException("x, y, z, p", exc_values_outside_bounds, SOURCE_INFO);

    double xt = 0;
    double yt = 0;
    double zt = 0;
    double pt = 0;
    double a = 0;
    double b = 0;
    double rho = 0;
    double tau = 0;
    double rcx = 0;
    double sum = 0.0;
    double fac = 1.0;
    if (p > 0.0) {
        xt = x;
        yt = y;
        zt = z;
        pt = p;
    }
    else  {
        xt = math::min(math::min(x, y), z);
        zt = math::max(math::max(x, y), z);
        yt = x + y + z - xt - zt;
        a = 1.0 / (yt - p);
        b = a*(zt - yt)*(yt - xt);
        pt = yt + b;
        rho = xt*zt / yt;
        tau = p*pt / yt;
        rcx = ellirc(rho, tau);
    }

    double ave = 0;
    double delx = PLUS_INF;
    double dely = PLUS_INF;
    double delz = PLUS_INF;
    double delp = PLUS_INF;
    while (math::max(math::max(std::abs(delx), std::abs(dely)),
        math::max(std::abs(delz), std::abs(delp))) > ERRTOL)
    {
        auto sqrtx = std::sqrt(xt);
        auto sqrty = std::sqrt(yt);
        auto sqrtz = std::sqrt(zt);
        auto alamb = sqrtx*(sqrty + sqrtz) + sqrty*sqrtz;
        auto alpha = math::sqr(pt*(sqrtx + sqrty + sqrtz) + sqrtx*sqrty*sqrtz);
        auto beta = pt*math::sqr(pt + alamb);
        sum += fac*ellirc(alpha, beta);
        fac = 0.25*fac;
        xt = 0.25*(xt + alamb);
        yt = 0.25*(yt + alamb);
        zt = 0.25*(zt + alamb);
        pt = 0.25*(pt + alamb);
        ave = 0.2*(xt + yt + zt + pt + pt);
        delx = (ave - xt) / ave;
        dely = (ave - yt) / ave;
        delz = (ave - zt) / ave;
        delp = (ave - pt) / ave;
    } 

    auto ea = delx*(dely + delz) + dely*delz;
    auto eb = delx*dely*delz;
    auto ec = delp*delp;
    auto ed = ea - 3.0*ec;
    auto ee = eb + 2.0*delp*(ea - ec);
    auto ans = 3.0*sum + fac*(1.0 + ed*(-C1 + C5*ed - C6*ee) + eb*(C7 + delp*(-C8 + delp*C4))
        + delp*ea*(C2 - delp*C3) - C2*delp*ec) / (ave*std::sqrt(ave));
    if (p <= 0.0) 
        ans = a*(b*ans + 3.0*(rcx - ellirf(xt, yt, zt)));
    return ans;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::ellirc(double x, double y)
{
    static constinit const double ERRTOL {0.0012};
    static constinit const double THIRD {1.0 / 3.0};
    static constinit const double C1 {0.3};
    static constinit const double C2 {1.0 / 7.0};
    static constinit const double C3 {0.375};
    static constinit const double C4 {9.0 / 22.0};
    static constinit const double TINY {5.0 * std::numeric_limits<double>::min()};
    static constinit const double BIG {0.2 * std::numeric_limits<double>::max()};
    static const double COMP1 {2.236 / std::sqrt(TINY)};
    static const double COMP2 {math::sqr(TINY * BIG) / 25.0};

    if (x < 0)
        throw ArgumentException("x", x, 0.0, RelationalOperator::GreaterThan, SOURCE_INFO);

    if (y == 0)
        throw ArgumentException("y", y, 0.0, RelationalOperator::NotEqual, SOURCE_INFO);

    if (((x + std::abs(y)) < TINY) || ((x + std::abs(y)) > BIG) ||
        (((y<-COMP1) && (x > 0.0) && (x < COMP2))))
        throw ArgumentException("x, y", exc_values_outside_bounds, SOURCE_INFO);

    double xt = 0;
    double yt = 0;
    double w = 0;

    if (y > 0.0) {
        xt = x;
        yt = y;
        w = 1.0;
    }
    else {
        xt = x - y;
        yt = -y;
        w = std::sqrt(x) / std::sqrt(xt);
    }

    double ave = 0;
    double s = PLUS_INF;

    while (std::abs(s) > ERRTOL) {
        auto alamb = 2.0*std::sqrt(xt)*std::sqrt(yt) + yt;
        xt = 0.25*(xt + alamb);
        yt = 0.25*(yt + alamb);
        ave = THIRD*(xt + yt + yt);
        s = (yt - ave) / ave;
    }

    return w*(1.0 + s*s*(C1 + s*(C2 + s*(C3 + s*C4)))) / std::sqrt(ave);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::ellif(double phi, double k)
{
    double s = std::sin(phi);
    return s*ellirf(math::sqr(std::cos(phi)), (1.0 - s*k)*(1.0 + s*k), 1.0);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::ellie(double phi, double k)
{
    auto s = std::sin(phi);
    auto cc = math::sqr(cos(phi));
    auto q = (1.0 - s*k)*(1.0 + s*k);
    return s*(ellirf(cc, q, 1.0) - (math::sqr(s*k))*ellird(cc, q, 1.0) / 3.0);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::ellipi(double phi, double n, double k)
{
    auto s = std::sin(phi);
    auto enss = n*s*s;
    auto cc = math::sqr(std::cos(phi));
    auto q = (1.0 - s*k)*(1.0 + s*k);
    return s*(ellirf(cc, q, 1.0) - enss*ellirj(cc, q, 1.0, 1.0 + enss) / 3.0);
}

//-----------------------------------------------------------------------------------------------------------------
nct::math::JacobianEllipticFunction nct::math::sncndn(double u, double m)
{
    static constinit const double CA {1.0e-8};

    JacobianEllipticFunction feval;

    std::array<double, 13> em;
    std::array<double, 13> en;
    
    if (m != 0.0) {
        double a = 0;
        double b = 0;
        double c = 0;
        double d = 0;

        bool bo = (m < 0.0);
        if (bo) {
            d = 1.0 - m;
            m /= -1.0 / d;
            u *= (d = sqrt(d));
        }
        a = 1.0;
        feval.dn = 1.0;

        int l = 0;
        for (int i = 0; i<13; i++) {
            l = i;
            em[i] = a;
            en[i] = (m = sqrt(m));
            c = 0.5*(a + m);
            if (std::abs(a - m) <= CA*a) break;
            m *= a;
            a = c;
        }
        u *= c;
        feval.sn = sin(u);
        feval.cn = cos(u);
        if (feval.sn != 0.0) {
            a = feval.cn / feval.sn;
            c *= a;
            for (int ii = l; ii >= 0; ii--) {
                b = em[ii];
                a *= c;
                c *= feval.dn;
                feval.dn = (en[ii] + a) / (b + a);
                a = c / b;
            }
            a = 1.0 / sqrt(c*c + 1.0);
            feval.sn = (feval.sn >= 0.0 ? a : -a);
            feval.cn = c* feval.sn;
        }
        if (bo) {
            a = feval.dn;
            feval.dn = feval.cn;
            feval.cn = a;
            feval.sn /= d;
        }
    }
    else  {
        feval.cn = 1.0 / cosh(u);
        feval.dn = feval.cn;
        feval.sn = tanh(u);
    }

    return feval;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::besselj0(double x) 
{
    // Coefficents to calculate the bessel function.

    static constinit const std::array j0r {1.682397144220462e-4,2.058861258868952e-5,
            5.288947320067750e-7,5.557173907680151e-9,2.865540042042604e-11,
            7.398972674152181e-14,7.925088479679688e-17};

    static constinit const std::array j0s {1.0,1.019685405805929e-2,5.130296867064666e-5,
        1.659702063950243e-7,3.728997574317067e-10,
        5.709292619977798e-13,4.932979170744996e-16};

    static constinit const std::array j0pn {9.999999999999999e-1,1.039698629715637,
        2.576910172633398e-1,1.504152485749669e-2,1.052598413585270e-4};

    static constinit const std::array j0pd {1.0,1.040797262528109,2.588070904043728e-1,
        1.529954477721284e-2,1.168931211650012e-4};

    static constinit const std::array j0qn {-1.562499999999992e-2,-1.920039317065641e-2,
        -5.827951791963418e-3,-4.372674978482726e-4,-3.895839560412374e-6};

    static constinit const std::array j0qd {1.0,1.237980436358390,3.838793938147116e-1,
        3.100323481550864e-2,4.165515825072393e-4};

    static constinit const double xj00 {5.783185962946785};

    static constinit const double xj10 {3.047126234366209e1};

    auto ax = std::abs(x);
    if (ax < 8.0) {
        auto rational = rat(x,j0r.data(), j0s.data(), 6);
        return rational.nump*(rational.y-xj00)*(rational.y-xj10)/ rational.denp;
    }
    
    auto asintotic = asp(j0pn.data(), j0pd.data(), j0qn.data(), j0qd.data(), 1., ax);
    return std::sqrt(TWO_DIV_PI/ax)*(std::cos(asintotic.xx)* asintotic.nump /
        asintotic.denp - asintotic.z*std::sin(asintotic.xx)* asintotic.numq/asintotic.denq);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::besselj1(const double x) 
{
    static constinit const std::array j1r { 7.309637831891357e-5,3.551248884746503e-6,
        5.820673901730427e-8,4.500650342170622e-10,1.831596352149641e-12,
        3.891583573305035e-15,3.524978592527982e-18 };

    static constinit const std::array j1s { 1.0,9.398354768446072e-3,4.328946737100230e-5,
        1.271526296341915e-7,2.566305357932989e-10,
        3.477378203574266e-13,2.593535427519985e-16 };

    static constinit const std::array j1pn { 1.0,1.014039111045313,2.426762348629863e-1,
        1.350308200342000e-2,9.516522033988099e-5 };

    static constinit const std::array j1pd { 1.0,1.012208056357845,2.408580305488938e-1,
        1.309511056184273e-2,7.746422941504713e-5 };

    static constinit const std::array j1qn { 4.687499999999991e-2,5.652407388406023e-2,
        1.676531273460512e-2,1.231216817715814e-3,1.178364381441801e-5 };

    static constinit const std::array j1qd { 1.0,1.210119370463693,3.626494789275638e-1,
        2.761695824829316e-2,3.240517192670181e-4 };

    static constinit const double xj01 {1.468197064212389e1};

    static constinit const double xj11 {4.921845632169460e1};

    auto ax = std::abs(x);
    if (ax < 8.0) {
        auto rational = rat(x,j1r.data(), j1s.data(), 6);
        return x* rational.nump*(rational.y-xj01)*(rational.y-xj11)/ rational.denp;
    } 
    
    auto asintotic = asp(j1pn.data(), j1pd.data(), j1qn.data(), j1qd.data(), 3., ax);
    double ans=std::sqrt(TWO_DIV_PI/ax)*(std::cos(asintotic.xx)* asintotic.nump /
        asintotic.denp-asintotic.z*std::sin(asintotic.xx)*asintotic.numq/asintotic.denq);
    return x > 0.0 ? ans : -ans;
}
    
//-----------------------------------------------------------------------------------------------------------------
double nct::math::besseljn(int n, double x)
{
    static constinit const double acc {160.0};
    static constinit const int iexp {std::numeric_limits<double>::max_exponent / 2};

    if (n==0) 
        return besselj0(x);
    if (n==1) 
        return besselj1(x);

    auto ax=std::abs(x);
    double ans = 0;

    if (ax*ax <= 8.0*std::numeric_limits<double>::min())
        return 0.0;
    else if (ax > double(n)) {
        auto tox=2.0/ax;
        auto bjm=besselj0(ax);
        auto bj=besselj1(ax);
        for (int j=1; j<n; j++) {
            auto bjp=j*tox*bj-bjm;
            bjm=bj;
            bj=bjp;
        }
        ans=bj;
    } 
    else  {
        auto tox=2.0/ax;
        auto m=2*((n+int(std::sqrt(acc*n)))/2);
        auto jsum=false;

        double bjp = 0;
        double sum = 0;        
        auto bj=1.0;
        for (int j=m; j>0; j--) {
            auto bjm=j*tox*bj-bjp;
            bjp=bj;
            bj=bjm;

            int k = 0;
            frexp(bj, &k);
            if (k > iexp) {
                bj=ldexp(bj,-iexp);
                bjp=ldexp(bjp,-iexp);
                ans=ldexp(ans,-iexp);
                sum=ldexp(sum,-iexp);
            }
            if (jsum) 
                sum += bj;
            jsum=!jsum;
            if (j == n) 
                ans=bjp;
        }
        sum=2.0*sum-bj;
        ans /= sum;
    }

    return x < 0.0 && (n & 1) ? -ans : ans;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::bessely0(double x) 
{
    static constinit const std::array y0r { -7.653778457189104e-3,-5.854760129990403e-2,
        3.720671300654721e-4,3.313722284628089e-5,4.247761237036536e-8,
        -4.134562661019613e-9,-3.382190331837473e-11,
        -1.017764126587862e-13,-1.107646382675456e-16 };

    static constinit const std::array y0s { 1.0,1.125494540257841e-2,6.427210537081400e-5,
        2.462520624294959e-7,7.029372432344291e-10,1.560784108184928e-12,
        2.702374957564761e-15,3.468496737915257e-18,2.716600180811817e-21 };

    static constinit const std::array y0pn { 9.999999999999999e-1,1.039698629715637,
        2.576910172633398e-1,1.504152485749669e-2,1.052598413585270e-4 };

    static constinit const std::array y0pd { 1.0,1.040797262528109,2.588070904043728e-1,
        1.529954477721284e-2,1.168931211650012e-4 };

    static constinit const std::array y0qn { -1.562499999999992e-2,-1.920039317065641e-2,
        -5.827951791963418e-3,-4.372674978482726e-4,-3.895839560412374e-6 };

    static constinit const std::array y0qd { 1.0,1.237980436358390,3.838793938147116e-1,
        3.100323481550864e-2,4.165515825072393e-4 };

    if (x <= 0.0) 
        throw ArgumentException("x", x, 0.0,
        RelationalOperator::GreaterThan, SOURCE_INFO);

    if (x < 8.0) {
        double j0x = besselj0(x);
        auto rational = rat(x, y0r.data(), y0s.data(), 8);
        return rational.nump/rational.denp+TWO_DIV_PI*j0x*log(x);
    } 
    
    auto ax=x;
    auto asintotic = asp(y0pn.data(), y0pd.data(), y0qn.data(), y0qd.data() ,1., ax);
    return std::sqrt(TWO_DIV_PI/x)*(std::sin(asintotic.xx)*asintotic.nump/
        asintotic.denp + asintotic.z*std::cos(asintotic.xx)*asintotic.numq/ asintotic.denq);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::bessely1(double x) 
{
    static constinit const std::array y1r { -1.041835425863234e-1,-1.135093963908952e-5,
        2.212118520638132e-4,1.270981874287763e-6,
        -3.982892100836748e-8,-4.820712110115943e-10,
        -1.929392690596969e-12,-2.725259514545605e-15 };

    static constinit const std::array y1s { 1.0,1.186694184425838e-2,7.121205411175519e-5,
        2.847142454085055e-7,8.364240962784899e-10,1.858128283833724e-12,
        3.018846060781846e-15,3.015798735815980e-18 };

    static constinit const std::array y1pn { 1.0,1.014039111045313,2.426762348629863e-1,
        1.350308200342000e-2,9.516522033988099e-5 };

    static constinit const std::array y1pd { 1.0,1.012208056357845,2.408580305488938e-1,
        1.309511056184273e-2,7.746422941504713e-5 };

    static constinit const std::array y1qn { 4.687499999999991e-2,5.652407388406023e-2,
        1.676531273460512e-2,1.231216817715814e-3,1.178364381441801e-5 };

    static constinit const std::array y1qd { 1.0,1.210119370463693,3.626494789275638e-1,
        2.761695824829316e-2,3.240517192670181e-4 };

    if (x <= 0.0) 
        throw ArgumentException("x", x, 0.0,
        RelationalOperator::GreaterThan, SOURCE_INFO);

    if (x < 8.0) {
        double j1x = besselj1(x);
        auto rational = rat(x ,y1r.data(), y1s.data(), 7);
        return x* rational.nump/rational.denp+TWO_DIV_PI*(j1x*log(x)-1.0/x);
    } 
    
    auto ax=x;
    auto asintotic = asp(y1pn.data(), y1pd.data(), y1qn.data(), y1qd.data(),3., ax);
    return std::sqrt(TWO_DIV_PI/x)*(std::sin(asintotic.xx)*asintotic.nump / 
        asintotic.denp+asintotic.z*std::cos(asintotic.xx)*asintotic.numq/asintotic.denq);
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::besselyn(int n, double x)
{
     if (x <= 0.0) 
        throw ArgumentException("x", x, 0.0,
        RelationalOperator::GreaterThan, SOURCE_INFO);

    if (n==0) 
        return bessely0(x);
    if (n==1) 
        return bessely1(x);

    auto tox=2.0/x;
    auto by=bessely1(x);
    auto bym=bessely0(x);
    for (int j=1; j<n; j++) {
        auto byp=j*tox*by-bym;
        bym=by;
        by=byp;
    }

    return by;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::besseli0(double x) 
{
    static constinit const std::array i0p { 9.999999999999997e-1,2.466405579426905e-1,
        1.478980363444585e-2,3.826993559940360e-4,5.395676869878828e-6,
        4.700912200921704e-8,2.733894920915608e-10,1.115830108455192e-12,
        3.301093025084127e-15,7.209167098020555e-18,1.166898488777214e-20,
        1.378948246502109e-23,1.124884061857506e-26,5.498556929587117e-30 };

    static constinit const std::array i0q { 4.463598170691436e-1,1.702205745042606e-3,
        2.792125684538934e-6,2.369902034785866e-9,8.965900179621208e-13 };

    static constinit const std::array i0pp { 1.192273748120670e-1,1.947452015979746e-1,
        7.629241821600588e-2,8.474903580801549e-3,2.023821945835647e-4 };

    static constinit const std::array i0qq { 2.962898424533095e-1,4.866115913196384e-1,
        1.938352806477617e-1,2.261671093400046e-2,6.450448095075585e-4,
        1.529835782400450e-6 };
    
    auto ax=std::abs(x);
    if (ax < 15.0) {
        auto y = x*x;
        return poly(i0p.data(), 13, y)/poly(i0q.data(), 4, 225. -y);
    } 
    
    auto z=1.0-15.0/ax;
    return exp(ax)*poly(i0pp.data(), 4, z)/(poly(i0qq.data(), 5, z)*std::sqrt(ax));
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::besseli1(double x) 
{
    static constinit const std::array i1p { 5.000000000000000e-1,6.090824836578078e-2,
        2.407288574545340e-3,4.622311145544158e-5,5.161743818147913e-7,
        3.712362374847555e-9,1.833983433811517e-11,6.493125133990706e-14,
        1.693074927497696e-16,3.299609473102338e-19,4.813071975603122e-22,
        5.164275442089090e-25,3.846870021788629e-28,1.712948291408736e-31 };

    static constinit const std::array i1q { 4.665973211630446e-1,1.677754477613006e-3,
        2.583049634689725e-6,2.045930934253556e-9,7.166133240195285e-13 };

    static constinit const std::array i1pp { 1.286515211317124e-1,1.930915272916783e-1,
        6.965689298161343e-2,7.345978783504595e-3,1.963602129240502e-4 };

    static constinit const std::array i1qq { 3.309385098860755e-1,4.878218424097628e-1,
        1.663088501568696e-1,1.473541892809522e-2,1.964131438571051e-4,
        -1.034524660214173e-6 };

    auto ax=std::abs(x);
    if (ax < 15.0) {
        auto y=x*x;
        return x*poly(i1p.data(), 13, y)/poly(i1q.data(), 4, 225.-y);
    } 
    
    auto z=1.0-15.0/ax;
    auto ans = exp(ax)*poly(i1pp.data(), 4, z)/(poly(i1qq.data(), 5, z)*std::sqrt(ax));
    return x > 0.0 ? ans : -ans;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::besselin(int n, double x)
{
    static constinit const double acc {200.0};
    static constinit const int iExp {std::numeric_limits<double>::max_exponent / 2};

    if (n==0) 
        return besseli0(x);
    if (n==1) 
        return besseli1(x);
    if (x*x <= 8.0*std::numeric_limits<double>::min())
        return 0.0;
    
    auto tox=2.0/std::abs(x);    
    auto bi=1.0;
    double bip = 0.0;
    double ans = 0.0;

    for (int j= 2*(n+int(std::sqrt(acc*n))); j>0; j--) {
        auto bim=bip+j*tox*bi;
        bip=bi;
        bi=bim;

        int k = 0;
        frexp(bi,&k);
        if (k > iExp) {
            ans=ldexp(ans,-iExp);
            bi=ldexp(bi,-iExp);
            bip=ldexp(bip,-iExp);
        }

        if (j == n) 
            ans=bip;
    }

    ans *= besseli0(x)/bi;
    return x < 0.0 && (n & 1) ? -ans : ans;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::besselk0(double x) 
{
    static constinit const std::array k0pi { 1.0,2.346487949187396e-1,1.187082088663404e-2,
        2.150707366040937e-4,1.425433617130587e-6 };

    
    static constinit const std::array k0qi { 9.847324170755358e-1,1.518396076767770e-2,
        8.362215678646257e-5 };

    static constinit const std::array k0p { 1.159315156584126e-1,2.770731240515333e-1,
        2.066458134619875e-2,4.574734709978264e-4,3.454715527986737e-6 };

    static constinit const std::array k0q { 9.836249671709183e-1,1.627693622304549e-2,
        9.809660603621949e-5 };

    static constinit const std::array k0pp { 1.253314137315499,1.475731032429900e1,
        6.123767403223466e1,1.121012633939949e2,9.285288485892228e1,
        3.198289277679660e1,3.595376024148513,6.160228690102976e-2 };

    static constinit const std::array k0qq { 1.0,1.189963006673403e1,5.027773590829784e1,
        9.496513373427093e1,8.318077493230258e1,3.181399777449301e1,
        4.443672926432041,1.408295601966600e-1 };

    if (x <= 0.0) 
        throw ArgumentException("x", x, 0.0,
        RelationalOperator::GreaterThan, SOURCE_INFO);

    if (x <= 1.0) {
        auto z=x*x;
        auto term = poly(k0pi.data(), 4, z)*log(x)/poly(k0qi.data(), 2, 1.-z);
        return poly(k0p.data(), 4, z)/poly(k0q.data(), 2, 1.-z) - term;
    } 
    
    auto z=1.0/x;
    return exp(-x)*poly(k0pp.data(), 7, z)/(poly(k0qq.data(), 7, z)*std::sqrt(x));
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::besselk1(double x) 
{
    static constinit const std::array k1pi { 0.5,5.598072040178741e-2,1.818666382168295e-3,
        2.397509908859959e-5,1.239567816344855e-7 };

    static constinit const std::array k1qi { 9.870202601341150e-1,1.292092053534579e-2,
        5.881933053917096e-5 };

    static constinit const std::array k1p { -3.079657578292062e-1,-8.109417631822442e-2,
        -3.477550948593604e-3,-5.385594871975406e-5,-3.110372465429008e-7 };

    static constinit const std::array k1q { 9.861813171751389e-1,1.375094061153160e-2,
        6.774221332947002e-5 };

    static constinit const std::array k1pp { 1.253314137315502,1.457171340220454e1,
        6.063161173098803e1,1.147386690867892e2,1.040442011439181e2,
        4.356596656837691e1,7.265230396353690,3.144418558991021e-1 };

    static constinit const std::array k1qq { 1.0,1.125154514806458e1,4.427488496597630e1,
        7.616113213117645e1,5.863377227890893e1,1.850303673841586e1,
        1.857244676566022,2.538540887654872e-2 };

    if (x <= 0.0) 
        throw ArgumentException("x", x, 0.0,
        RelationalOperator::GreaterThan, SOURCE_INFO);

    if (x <= 1.0) {
        auto z=x*x;
        auto term = poly(k1pi.data(), 4, z)*log(x)/poly(k1qi.data(), 2, 1.-z);
        return x*(poly(k1p.data(), 4, z)/poly(k1q.data(), 2, 1.-z)+term)+1./x;
    }

    auto z=1.0/x;
    return exp(-x)*poly(k1pp.data(), 7, z)/(poly(k1qq.data(), 7, z)*std::sqrt(x));
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::besselkn(int n, double x)
{
    if (x <= 0.0) 
        throw ArgumentException("x", x, 0.0,
        RelationalOperator::GreaterThan, SOURCE_INFO);

    if (n==0) 
        return besselk0(x);
    if (n==1) 
        return besselk1(x);

    auto tox=2.0/x;
    auto bkm=besselk0(x);
    auto bk=besselk1(x);

    for (int j=1; j<n; j++) {
        auto bkp=bkm+j*tox*bk;
        bkm=bk;
        bk=bkp;
    }
    return bk;
}

//-----------------------------------------------------------------------------------------------------------------
nct::math::BesseljyFunction nct::math::besseljy(double n, double x)
{
    static constinit const int maxIt {10000};
    static constinit const double xMin {2.0};

    static constinit const std::array c1 { -1.142022680371168e0,6.5165112670737e-3,
        3.087090173086e-4,-3.4706269649e-6,6.9437664e-9,3.67795e-11,
        -1.356e-13 };

    static constinit const std::array c2 { 1.843740587300905e0,-7.68528408447867e-2,
        1.2719271366546e-3,-4.9717367042e-6,-3.31261198e-8,2.423096e-10, -1.702e-13,-1.49e-15 };

    if (x <= 0.0) 
        throw ArgumentException("x", x, 0.0,
        RelationalOperator::GreaterThan, SOURCE_INFO);

    if (n < 0.0) 
        throw ArgumentException("n", n, 0.0,
        RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    int nl=(x < xMin ? int(n+0.5) : math::max(0,int(n-x+1.5)));
    int isign = 1;

    auto xmu=n-nl;
    auto xmu2=xmu*xmu;
    auto xi=1.0/x;
    auto xi2=2.0*xi;
    auto w=xi2/PI;    
    
    auto h=n*xi;
    if (h < SMALL_FP) 
        h=SMALL_FP;

    auto b=xi2*n;
    auto d=0.0;
    auto c=h;

    int i = 0;
    for (; i<maxIt; i++) {
        b += xi2;
        d=b-d;
        if (std::abs(d) < SMALL_FP) 
            d=SMALL_FP;
        c=b-1.0/c;
        if (std::abs(c) < SMALL_FP) 
            c=SMALL_FP;
        d=1.0/d;

        auto del=c*d;
        h=del*h;
        if (d < 0.0) 
            isign = -isign;
        if (std::abs(del-1.0) <= EPS_100) 
            break;
    }

    if (i >= maxIt)
        throw ArgumentException(exc_value_too_large, SOURCE_INFO);

    auto rjl=isign*SMALL_FP;
    auto rjpl=h*rjl;
    auto rjl1=rjl;
    auto rjp1=rjpl;
    auto fact=n*xi;

    for (int l=nl-1;l>=0;l--) {
        auto rjtemp=fact*rjl+rjpl;
        fact -= xi;
        rjpl=fact*rjtemp-rjl;
        rjl=rjtemp;
    }

    if (rjl == 0.0) 
        rjl=EPS_100;
    auto f=rjpl/rjl;

    double rjmu = 0;
    double rymup = 0;
    double ry1 = 0;
    double rymu = 0;
    if (x < xMin) {
        auto x2=0.5*x;
        auto pimu=PI*xmu;
        fact = (std::abs(pimu) < EPS_100 ? 1.0 : pimu/std::sin(pimu));
        d = -log(x2);
        
        auto e = xmu*d;
        auto fact2 = (std::abs(e) < EPS_100 ? 1.0 : sinh(e)/e);
        auto xx=8.0*math::sqr(xmu)-1.0;
        auto gam1=chebev(c1.data(), static_cast<int>(c1.size()),xx);
        auto gam2=chebev(c2.data(), static_cast<int>(c2.size()),xx);
        auto gampl= gam2-xmu*gam1;
        auto gammi= gam2+xmu*gam1;
        auto ff=2.0/PI*fact*(gam1*cosh(e)+gam2*fact2*d);
        e=exp(e);
        
        auto p=e/(gampl*PI);
        auto q=1.0/(e*PI*gammi);
        auto pimu2=0.5*pimu;
        auto fact3 = (std::abs(pimu2) < EPS_100 ? 1.0 : std::sin(pimu2)/pimu2);
        auto r=PI*pimu2*fact3*fact3;
        c=1.0;
        d = -x2*x2;
        auto sum=ff+r*q;
        auto sum1=p;

        for (i=1;i<=maxIt;i++) {
            ff=(i*ff+p+q)/(static_cast<long long>(i)*i-xmu2);
            c *= (d/i);
            p /= (i-xmu);
            q /= (i+xmu);

            auto del=c*(ff+r*q);
            sum += del;

            auto del1=c*p-i*del;
            sum1 += del1;

            if (std::abs(del) < (1.0+std::abs(sum))*EPS_100) 
                break;
        }

        if (i > maxIt) 
            throw OperationException(exc_error_evaluating_bessy_series, SOURCE_INFO); 

        rymu = -sum;
        ry1 = -sum1*xi2;
        rymup=xmu*xi*rymu-ry1;
        rjmu=w/(rymup-f*rymu);
    } 
    else  {
        auto a=0.25-xmu2;
        auto p = -0.5*xi;
        auto q=1.0;
        auto br=2.0*x;
        auto bi=2.0;
        fact=a*xi/(p*p+q*q);

        auto cr=br+q*fact;
        auto ci=bi+p*fact;
        auto den=br*br+bi*bi;
        auto dr=br/den;
        auto di = -bi/den;
        auto dlr=cr*dr-ci*di;
        auto dli=cr*di+ci*dr;
        auto temp=p*dlr-q*dli;

        q=p*dli+q*dlr;
        p=temp;

        for (i=1;i<maxIt;i++) {
            a += 2* static_cast<long long>(i);
            bi += 2.0;
            dr=a*dr+br;
            di=a*di+bi;
            if (std::abs(dr)+std::abs(di) < SMALL_FP) 
                dr=SMALL_FP;
            fact=a/(cr*cr+ci*ci);
            cr=br+cr*fact;
            ci=bi-ci*fact;
            if (std::abs(cr)+std::abs(ci) < SMALL_FP) 
                cr=SMALL_FP;
            den=dr*dr+di*di;
            dr /= den;
            di /= -den;
            dlr=cr*dr-ci*di;
            dli=cr*di+ci*dr;
            temp=p*dlr-q*dli;
            q=p*dli+q*dlr;
            p=temp;
            if (std::abs(dlr-1.0)+std::abs(dli) <= EPS_100) break;
        }

        if (i >= maxIt) 
            throw OperationException(exc_maximum_number_of_iterations_exceeded, SOURCE_INFO);

        auto gam=(p-f)/q;

        rjmu=std::sqrt(w/((p-f)*gam+q));
        rjmu=math::sign(rjmu,rjl);
        rymu=rjmu*gam;
        rymup=rymu*(p+q/gam);
        ry1=xmu*xi*rymu-rymup;
    }

    BesseljyFunction feval;
    fact=rjmu/rjl;
    feval.j=rjl1*fact;
    feval.jp=rjp1*fact;

    for (i=1;i<=nl;i++) {
        auto rytemp=(xmu+i)*xi2*ry1-rymu;
        rymu=ry1;
        ry1=rytemp;
    }
    feval.y=rymu;
    feval.yp=n*xi*rymu-ry1;

    return feval;
}

//-----------------------------------------------------------------------------------------------------------------
nct::math::BesselikFunction nct::math::besselik(double n, double x)
{
    static constinit const int maxIt {10000};
    static constinit const double xMin {2.0};

    static constinit const std::array c1 { -1.142022680371168e0,6.5165112670737e-3,
        3.087090173086e-4,-3.4706269649e-6,6.9437664e-9,3.67795e-11,
        -1.356e-13 };

    static constinit const std::array c2 { 1.843740587300905e0,-7.68528408447867e-2,
        1.2719271366546e-3,-4.9717367042e-6,-3.31261198e-8,2.423096e-10, -1.702e-13,-1.49e-15 };
        
    if (x <= 0.0) 
        throw ArgumentException("x", x, 0.0,
        RelationalOperator::GreaterThan, SOURCE_INFO);

    if (n < 0.0) 
        throw ArgumentException("n", n, 0.0,
        RelationalOperator::GreaterThanOrEqualTo, 
        SOURCE_INFO);
    
    int nl=int(n+0.5);
    auto xmu=n-nl;
    auto xmu2=xmu*xmu;
    auto xi=1.0/x;
    auto xi2=2.0*xi;
    
    auto h=n*xi;
    if (h < SMALL_FP)
        h=SMALL_FP;
    
    auto b=xi2*n;
    auto d=0.0;
    auto c=h;

    int it = 0;
    for (;it<maxIt;it++) {
        b += xi2;
        d=1.0/(b+d);
        c=b+1.0/c;

        auto del=c*d;
        h=del*h;

        if (std::abs(del-1.0) <= EPS_100)
            break;
    }

    if (it >= maxIt)
        throw OperationException(exc_value_too_large, SOURCE_INFO);

    auto ril=SMALL_FP;
    auto ripl=h*ril;
    auto ril1=ril;
    auto rip1=ripl;

    auto fact=n*xi;
    for (int l=nl-1;l >= 0;l--) {
        auto ritemp=fact*ril+ripl;
        fact -= xi;
        ripl=fact*ritemp+ril;
        ril=ritemp;
    }

    auto f=ripl/ril;
    double rkmu = 0;
    double rk1 = 0;
    if (x < xMin) {
        auto x2=0.5*x;
        auto pimu=PI*xmu;

        fact = (std::abs(pimu) < EPS_100 ? 1.0 : pimu/std::sin(pimu));
        d = -log(x2);

        auto e=xmu*d;
        auto fact2 = (std::abs(e) < EPS_100 ? 1.0 : sinh(e)/e);
        auto xx=8.0*math::sqr(xmu)-1.0;
        auto gam1 = chebev(c1.data(), static_cast<int>(c1.size()), xx);
        auto gam2 = chebev(c2.data(), static_cast<int>(c2.size()), xx);
        auto gampl= gam2-xmu*gam1;
        auto gammi= gam2+xmu*gam1;
        auto ff=fact*(gam1*cosh(e)+gam2*fact2*d);
        auto sum=ff;

        e=exp(e);
        auto p=0.5*e/gampl;
        auto q=0.5/(e*gammi);
        c=1.0;
        d=x2*x2;

        auto sum1=p;
        for (it=1;it<=maxIt;it++) {
            ff=(it*ff+p+q)/(static_cast<long long>(it)*it-xmu2);
            c *= (d/it);
            p /= (it-xmu);
            q /= (it+xmu);

            auto del=c*ff;
            sum += del;

            auto del1=c*(p-it*ff);
            sum1 += del1;
            if (std::abs(del) < std::abs(sum)*EPS_100)
                break;
        }

        if (it > maxIt) 
            throw OperationException(exc_error_evaluating_bessk_series, SOURCE_INFO); 
        
        rkmu=sum;
        rk1=sum1*xi2;
    } 
    else {
        b=2.0*(1.0+x);
        d=1.0/b;
        h = d;
        auto delh = d;
        auto q1=0.0;
        auto q2=1.0;
        auto a1=0.25-xmu2;
        auto q=c=a1;
        auto a = -a1;
        auto s=1.0+q*delh;

        for (it=1;it<maxIt;it++) {
            a -= 2* static_cast<long long>(it);
            c = -a*c/(it+1.0);
            auto qnew=(q1-b*q2)/a;
            q1=q2;
            q2=qnew;
            q += c*qnew;
            b += 2.0;
            d=1.0/(b+a*d);
            delh=(b*d-1.0)*delh;
            h += delh;
            auto dels=q*delh;
            s += dels;

            if (std::abs(dels/s) <= EPS_100)
                break;
        }
        if (it >= maxIt) 
            throw OperationException(exc_maximum_number_of_iterations_exceeded, SOURCE_INFO);
        h=a1*h;
        rkmu=std::sqrt(PI/(2.0*x))*exp(-x)/s;
        rk1=rkmu*(xmu+x+0.5-h)*xi;
    }

    auto rkmup=xmu*xi*rkmu-rk1;
    auto rimu=xi/(f*rkmu-rkmup);

    BesselikFunction feval;
    feval.i=(rimu*ril1)/ril;
    feval.ip=(rimu*rip1)/ril;
    for (it=1;it <= nl;it++) {
        auto rktemp=(xmu+it)*xi2*rk1+rkmu;
        rkmu=rk1;
        rk1=rktemp;
    }
    feval.k=rkmu;
    feval.kp=n*xi*rkmu-rk1;

    return feval;
}

//-----------------------------------------------------------------------------------------------------------------
nct::math::AiryFunction nct::math::airy(double x)
{
    static constinit const double onovrt {0.577350269189626};
    static constinit const double thr {1. / 3.};
    static constinit const double twothr {2. / 3.};
    
    auto absx=std::abs(x);
    auto rootx=std::sqrt(absx);
    auto z=twothr*absx*rootx;
    AiryFunction feval;

    if (x > 0.0) {        
        auto bessel = besselik(thr,z);
        feval.ai = rootx*onovrt* bessel.k/PI;
        feval.bi = rootx*(bessel.k/PI+2.0*onovrt* bessel.i);
        bessel = besselik(twothr,z);
        feval.aip = -x*onovrt* bessel.k/PI;
        feval.bip = x*(bessel.k/PI+2.0*onovrt* bessel.i);
    } 
    else if (x < 0.0) {
        auto bessel = besseljy(thr, z);
        feval.ai = 0.5*rootx*(bessel.j-onovrt* bessel.y);
        feval.bi = -0.5*rootx*(bessel.y+onovrt* bessel.j);
        bessel = besseljy(twothr,z);
        feval.aip = 0.5*absx*(onovrt* bessel.y+ bessel.j);
        feval.bip = 0.5*absx*(onovrt* bessel.j- bessel.y);
    } 
    else  {
        feval.ai=0.355028053887817;
        feval.bi= feval.ai/onovrt;
        feval.aip = -0.258819403792807;
        feval.bip = -feval.aip/onovrt;
    }

    return feval;
}

//-----------------------------------------------------------------------------------------------------------------
nct::math::BesseljyFunction nct::math::sphericalBessel(double n, double x)
{
    static constinit const double rtpio2 {1.253314137315500251};
    
    if (x <= 0.0) 
        throw ArgumentException("x", x, 0.0,
        RelationalOperator::GreaterThan, SOURCE_INFO);

    if (n < 0.0) 
        throw ArgumentException("n", n, 0.0,
        RelationalOperator::GreaterThanOrEqualTo, 
        SOURCE_INFO);

    auto order=n+0.5;
    auto bessel = besseljy(order,x);
    auto factor=rtpio2/std::sqrt(x);

    bessel.j*=factor;
    bessel.y*=factor;
    bessel.jp=factor* bessel.jp- bessel.j/(2.*x);
    bessel.yp=factor* bessel.yp- bessel.y/(2.*x);

    return bessel;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::chebyshevPolFirst(int n, double x)
{
    if (n < 0)
        throw ArgumentException("n", n, 0, 
        RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    if (n == 0)
        return 1.0;

    if (n == 1)
        return x;

    double ttmp = 0;
    double tant = 1.0;
    double t = x;

    for (int i = 2; i<=n; i++) {
        ttmp = t;
        t = 2.0*x*t - tant;
        tant = ttmp;
    }

    return t;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Complex nct::math::chebyshevPolFirst(int n, Complex z)
{
    if (n < 0)
        throw ArgumentException("n", n, 0, 
        RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    if (n == 0)
        return 1.0;

    if (n == 1)
        return z;

    Complex ttmp = 0;
    Complex tant = 1.0;
    Complex t = z;

    for (int i = 2; i<=n; i++) {
        ttmp = t;
        t = 2.0*z*t - tant;
        tant = ttmp;
    }

    return t;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::chebyshevPolSecond(int n, double x)
{
    if (n < 0)
        throw ArgumentException("n", n, 0, 
        RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    if (n == 0)
        return 1.0;

    if (n == 1)
        return 2.0*x;

    double ttmp = 0;
    double tant = 1.0;
    double t = 2.0*x;

    for (int i = 2; i<=n; i++) {
        ttmp = t;
        t = 2.0*x*t - tant;
        tant = ttmp;
    }

    return t;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Complex nct::math::chebyshevPolSecond(int n, Complex z)
{
    if (n < 0)
        throw ArgumentException("n", n, 0, 
        RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    if (n == 0)
        return 1.0;

    if (n == 1)
        return 2.0*z;

    Complex ttmp = 0;
    Complex tant = 1.0;
    Complex t = 2.0*z;

    for (int i = 2; i<=n; i++) {
        ttmp = t;
        t = 2.0*z*t - tant;
        tant = ttmp;
    }

    return t;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::spLegendre(int l, int m, double x)
{
    if (m < 0)
        throw ArgumentException("m", m, 0,
        RelationalOperator::GreaterThanOrEqualTo, 
        SOURCE_INFO);

    if (m > l)
        throw ArgumentException("m, l", exc_bad_legendre_arguments, SOURCE_INFO);

    if ( (x<-1.0) || (x>1.0) )
        throw ArgumentException("x", x, -1.0, 1.0, 
        RelationalOperator::GreaterThanOrEqualTo, 
        RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);
    
    double fact = 0, oldfact = 0, pll = 0, pmm = 1.0, pmmp1 = 0, omx2 = 0;

    if (m > 0) {
        omx2=(1.0-x)*(1.0+x);
        fact=1.0;
        for (int i=0; i<m; i++) {
            pmm *= omx2*fact/(fact+1.0);
            fact += 2.0;
        }
    }

    pmm=std::sqrt((2*static_cast<long long>(m)+1)*pmm/(4.0*PI));

    if (m & 1)
        pmm=-pmm;

    if (l == m) {
        return pmm;
    }
    else  {
        pmmp1=x*std::sqrt(2.0*m+3.0)*pmm;
        if (l == (m+1)) {
            return pmmp1;
        }
        else  {
            oldfact=std::sqrt(2.0*m+3.0);

            for (int ll=m+2; ll<=l; ll++) {
                fact=std::sqrt((4.0*static_cast<long long>(ll)*ll-1.0)/
                    (static_cast<long long>(ll)*ll- static_cast<long long>(m)*m));
                pll=(x*pmmp1-pmm/oldfact)*fact;
                oldfact=fact;
                pmm=pmmp1;
                pmmp1=pll;
            }

            return pll;
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::legendre(int l, int m, double x)
{
    if (m < 0)
        throw ArgumentException("m", m, 0,RelationalOperator::GreaterThanOrEqualTo, 
        SOURCE_INFO);

    if (m > l)
        throw ArgumentException("m, l", exc_bad_legendre_arguments, SOURCE_INFO);

    if ( (x<-1.0) || (x>1.0) )
        throw ArgumentException("x", x, -1.0, 1.0, 
        RelationalOperator::GreaterThanOrEqualTo, 
        RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    double prod=1.0;

    for (int j=l-m+1;j<=l+m;j++)
        prod *= j;

    return std::sqrt(4.0*PI*prod/(2.0*l+1.0))*spLegendre(l,m,x);
}

//-----------------------------------------------------------------------------------------------------------------
nct::Complex nct::math::sphericalHarmonic(int l, int m, double theta, double phi)
{
    if (l < 0)
        throw ArgumentException("l", l, 0,
        RelationalOperator::GreaterThanOrEqualTo, 
        SOURCE_INFO);

    if ( (m < -l) || (m > l) )
        throw ArgumentException("m, l", exc_bad_legendre_arguments, SOURCE_INFO);

    // Real part and imaginary part of the harmonic.
    double r = std::cos(m*theta);
    double i = std::sin(m*theta);

    // Sign of the harmonic.
    double s = 1;
    double c = 1;
    if (m<0) {
        m = -m;
        c = -1;
        for (int j=0; j<m; j++)
            s*=-1;
    }

    // Result.
    double mag = s*spLegendre(l, m, std::cos(phi));

    return Complex(r*mag, c*i*mag);
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
