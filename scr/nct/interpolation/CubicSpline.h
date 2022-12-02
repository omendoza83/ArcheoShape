//=================================================================================================================
/**
 *  @file       CubicSpline.h
 *  @brief      nct::interpolation::CubicSpline class.
 *  @details    Declaration of the nct::interpolation::CubicSpline class. 
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

#ifndef NCT_CUBIC_SPLINE_H_INCLUDE
#define NCT_CUBIC_SPLINE_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_constants.h>
#include <nct/nct_exception.h>
#include <nct/Array.h>
#include <nct/Array2D.h>

//=================================================================================================================
namespace nct {
namespace interpolation {

/**
 *  @brief      Class for cubic spline interpolation.
 *  @details    This class is used to interpolate data with cubic splines.
 */
class NCT_EXPIMP CubicSpline final {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the default configuration.
     */
    CubicSpline() = default;

    /**
     *  @brief      Constructor for natural splines.
     *  @details    This constructors creates an interpolation object according to the given observations.
     *              The constructor sets the array of observations and calculates the derivatives
     *              that are needed to define the cubic spline between observations.
     *              The first derivative at the beginning and at the end
     *              of the function are set to cero, then the spline is natural.
     *  @param[in]  xData  Observations of the independent variable.
     *  @param[in]  yData  Observations of the dependent variable.
     *  @param[in]  tol  Tolerance for small numbers.
     */
    CubicSpline(const RealVector& xData, const RealVector& yData, double tol = VERY_SMALL_TOL);

    /**
     *  @brief      Constructor for natural splines.
     *  @details    This constructors creates an interpolation object according to the given observations.
     *              The object takes ownership of the data that is stored in the input arrays.
     *              The constructor sets the array of observations and calculates the derivatives
     *              that are needed to define the cubic spline between observations.
     *              The first derivative at the beginning and at the end
     *              of the function are set to cero, then the spline is natural. 
     *  @param[in]  xData  Observations of the independent variable.
     *  @param[in]  yData  Observations of the dependent variable.
     *  @param[in]  tol  Tolerance for small numbers.
     */
    CubicSpline(RealVector&& xData, RealVector&& yData, double tol = VERY_SMALL_TOL);

    /**
     *  @brief      Constructor for non-natural splines.
     *  @details    This constructors creates an interpolation object according to the given observations.
     *              The constructor sets the array of observations and calculates the derivatives
     *              that are needed to define the cubic spline between observations.
     *  @param[in]  xData  Observations of the independent variable.
     *  @param[in]  yData  Observations of the dependent variable.
     *  @param[in]  der1  First derivative in the left side.
     *  @param[in]  derN  First derivative in the right side.
     *  @param[in]  tol  Tolerance for small numbers.
     */
    CubicSpline(const RealVector& xData, const RealVector& yData, double der1, double derN,
        double tol = VERY_SMALL_TOL);

    /**
     *  @brief      Constructor for non-natural splines.
     *  @details    This constructors creates an interpolation object according to the given observations.
     *              The object takes ownership of the data that is stored in the input arrays.
     *              The constructor sets the array of observations and calculates the derivatives
     *              that are needed to define the cubic spline between observations.
     *  @param[in]  yData  Observations of the dependent variable.
     *  @param[in]  der1  First derivative in the left side.
     *  @param[in]  derN  First derivative in the right side.
     *  @param[in]  tol  Tolerance for small numbers.
     */
    CubicSpline(RealVector&& xData, RealVector&& yData, double der1, double derN,
        double tol = VERY_SMALL_TOL);
    
    ////////// Operators //////////        
    
    /**
     *  @brief      Evaluate point.
     *  @details    This function evaluates the model at the specified point.
     *              This function is the same as eval(x).
     *  @param[in]  x  The point to be evaluated.
     *  @returns    The value of the evaluation.
     */
    double operator()(double x) const;

    /**
     *  @brief      Evaluate points.
     *  @details    This function evaluates the model at the specified points.
     *  @param[in]  x  The points to be evaluated.
     *  @returns    An array with the evaluations.
     */
    RealVector operator()(const RealVector& x) const;

    ////////// Member functions //////////        

    /**
     *  @brief      Independent variable.
     *  @details    This function returns the observations of the independent variables.
     *  @returns    A reference to the observations of the independent variables.
     */
    const RealVector& xValues() const noexcept;

    /**
     *  @brief      Dependent variable.
     *  @details    This function returns the observations of the dependent variables.
     *  @returns    A reference to the observations of the dependent variables.
     */
    const RealVector& yValues() const noexcept;

    /**
     *  @brief      First derivative in the left side.
     *  @details    This function returns the first derivative in the left side of the spline.
     *  @returns    The first derivative in the right side of the spline.
     */
    double derivL() const noexcept;

    /**
     *  @brief      First derivative in the right side.
     *  @details    This function returns the first derivative in the right side of the spline.
     *  @returns    The first derivative in the left side of the spline.
     */
    double derivR() const noexcept;

    /**
     *  @brief      Second derivative.
     *  @details    This function returns the array with the second derivatives in each point.
     *  @returns    A const reference to the array with the second derivatives.
     */
    const RealVector& deriv2() const noexcept;

    /**
     *  @brief      Evaluate point.
     *  @details    This function evaluates the model at the specified point.
     *  @param[in]  x  The point to be evaluated.
     *  @returns    The value of the evaluation.
     */
    double eval(double x) const;

    /**
     *  @brief      Evaluate points.
     *  @details    This function evaluates the model at the specified points.
     *  @param[in]  x  The points to be evaluated.
     *  @returns    An array with the evaluations.
     */
    RealVector eval(const RealVector& x) const;

private:

    ////////// Member functions //////////

    /**
     *  @brief      Build the spline.
     *  @details    This function builds the spline and calculates the second derivatives 
     *              in each observation.
     *  @param[in]  tol  Tolerance for small numbers.
     */
    void build(double tol);

    ////////// Data members //////////

    RealVector xData_;      /**< Observations of the independent variable. */

    RealVector yData_;      /**< Observations of the dependent variable. */

    bool natural_ {false};  /**< True, if the spline is natural. */

    double d1_ {0};         /**< First derivative at the left side. */

    double dN_ {0};         /**< First derivative at the right side. */

    RealVector d2_;         /**< Array of second derivatives. */

};

}}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
