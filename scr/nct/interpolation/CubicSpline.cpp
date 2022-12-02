//=================================================================================================================
/**
 *  @file       CubicSpline.cpp
 *  @brief      nct::interpolation::CubicSpline class implementation file.
 *  @details    This file contains the implementation of the nct::interpolation::CubicSpline class.          
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

//=================================================================================================================
//        HEADERS AND NAMESPACES
//=================================================================================================================
#include <nct/interpolation/CubicSpline.h>
#include <nct/math/linear_algebra.h>
#include <vector>
#include <algorithm>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::interpolation::CubicSpline::CubicSpline(const RealVector& xData, const RealVector& yData,
    double tol)
{
    if (xData.size() < 2)
        throw ArgumentException("xData", exc_data_with_less_than_two_observations,
            SOURCE_INFO);

    if (xData.size() != yData.size())
        throw ArgumentException("xData, yData", exc_objects_with_different_number_of_observations, SOURCE_INFO);

    try {
        natural_ = true;
        d1_ = 0;
        dN_ = 0;
        xData_ = xData;
        yData_ = yData;
        build(tol);
    }
    catch (const nct_exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }    
    catch (...) {
        throw InitializationException(SOURCE_INFO);
    }
}

//-----------------------------------------------------------------------------------------------------------------
nct::interpolation::CubicSpline::CubicSpline(RealVector&& xData, RealVector&& yData,
    double tol)
{
    if (xData.size() < 2)
        throw ArgumentException("xData", exc_data_with_less_than_two_observations,
            SOURCE_INFO);

    if (xData.size() != yData.size())
        throw ArgumentException("xData, yData", exc_objects_with_different_number_of_observations, SOURCE_INFO);

    try {
        natural_ = true;
        d1_ = 0;
        dN_ = 0;
        xData_ = std::move(xData);
        yData_ = std::move(yData);
        build(tol);
    }
    catch (const nct_exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }    
    catch (...) {
        throw InitializationException(SOURCE_INFO);
    }
}

//-----------------------------------------------------------------------------------------------------------------
nct::interpolation::CubicSpline::CubicSpline(const RealVector& xData, const RealVector& yData,
    double der1, double derN, double tol)
{
    if (xData.size() < 2)
        throw ArgumentException("xData", exc_data_with_less_than_two_observations,
            SOURCE_INFO);

    if (xData.size() != yData.size())
        throw ArgumentException("xData, yData", exc_objects_with_different_number_of_observations, SOURCE_INFO);
    try {
        natural_ = false;
        d1_ = der1;
        dN_ = derN;
        xData_ = xData;
        yData_ = yData;
        build(tol);
    }
    catch (const nct_exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }    
    catch (...) {
        throw InitializationException(SOURCE_INFO);
    }    
}

//-----------------------------------------------------------------------------------------------------------------
nct::interpolation::CubicSpline::CubicSpline(RealVector&& xData, RealVector&& yData,
    double der1, double derN, double tol)
{
    if (xData.size() < 2)
        throw ArgumentException("xData", exc_data_with_less_than_two_observations,
            SOURCE_INFO);

    if (xData.size() != yData.size())
        throw ArgumentException("xData, yData", exc_objects_with_different_number_of_observations, SOURCE_INFO);
    
    try {
        natural_ = false;
        d1_ = der1;
        dN_ = derN;
        xData_ = std::move(xData);
        yData_ = std::move(yData);
        build(tol);
    }
    catch (const nct_exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }    
    catch (...) {
        throw InitializationException(SOURCE_INFO);
    }    
}

//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
double nct::interpolation::CubicSpline::operator()(double x) const
{
    return eval(x);
}

//-----------------------------------------------------------------------------------------------------------------
nct::RealVector nct::interpolation::CubicSpline::operator()(const RealVector& x) const
{
    return eval(x);    
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
const nct::RealVector& nct::interpolation::CubicSpline::xValues() const noexcept
{
    return xData_;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::RealVector& nct::interpolation::CubicSpline::yValues() const noexcept
{
    return yData_;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::interpolation::CubicSpline::derivL() const noexcept
{
    return d1_;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::interpolation::CubicSpline::derivR() const noexcept
{
    return dN_;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::RealVector& nct::interpolation::CubicSpline::deriv2() const noexcept
{
    return d2_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::interpolation::CubicSpline::build(double tol)
{
    // Sort input.
    auto n = xData_.size();            
    std::vector<std::pair<double, double>> vecXPair(n);
    
    for (index_t i=0; i<n; i++)
        vecXPair[i] = std::make_pair(static_cast<double>(xData_[i]), static_cast<double>(yData_[i]));

    sort(vecXPair.begin(), vecXPair.end(), 
        [](const std::pair<double, double>& x, 
            const std::pair<double, double>& y) -> bool {return y.first>x.first; });

    for (index_t i=0; i<n; i++) {
        xData_[i] = vecXPair[i].first;
        yData_[i] = vecXPair[i].second;
    }

    // Build the linear system to be solved.
    n = xData_.size();        
    Matrix a(n,3);            
    RealVector b(n);            
    for (index_t i=1; i<n; i++) {
        a(i,0) = xData_[i]-xData_[i-1];
        if (i<n-1)
            a(i,1) = 2*(xData_[i+1]-xData_[i-1]);        
        a(i-1,2) = a(i,0);
        b[i] = (yData_[i]-yData_[i-1])/a(i,0);
        b[i-1] = 6*(b[i] - b[i-1]);
    }
    if (natural_) {
        a(0,0) = 0;
        a(0,1) = 1;
        a(0,2) = 0;
        b[0] = 0;

        a(n-1,0) = 0;
        a(n-1,1) = 1;
        a(n-1,2) = 0;
        b[n-1] = 0;
    }
    else {
        a(0,0) = 0;
        a(0,1) = 4*(xData_[1]-xData_[0]);
        a(0,2) = xData_[1]-xData_[0];
        b[0] = 6*((yData_[1]-yData_[0])/a(0,2) -d1_);

        a(n-1,0) = xData_[n-1]-xData_[n-2];
        a(n-1,1) = 4*(xData_[n-1]-xData_[n-2]);
        a(n-1,2) = 0;
        b[n-1] = 6*(dN_ - (yData_[n-1]-yData_[n-2])/a(n-1,0));
    }

    // Solve system by using LU fctorization.
    auto plu = math::linear_algebra::pluFactorizationOfBandedMatrix(a, 1, tol);
    d2_ = math::linear_algebra::solveSystemPLUBanded(plu, b, tol);

    // Calculate the first num_differentiation if the spline is natural
    if (natural_) {
        d1_ = (yData_[1]-yData_[0])/(xData_[1]-xData_[0]) - (xData_[1]-xData_[0])*(2*d2_[0]/3 +d2_[1]/6);
        dN_ = (yData_[n-1]-yData_[n-2])/(xData_[n-1]-xData_[n-2]) + 
            (xData_[n-1]-xData_[n-2])*(2*d2_[n-1]/3 +d2_[n-2]/6);
    }
}

//-----------------------------------------------------------------------------------------------------------------
double nct::interpolation::CubicSpline::eval(double x) const
{
    if ((xData_.size() == 0) || (yData_.size() == 0) || (d2_.size() == 0))
        throw ConfigurationException(exc_bad_interpolation_model, SOURCE_INFO);

    auto n = xData_.size();        
    size_t i = 0;                        
        
    if (x <= xData_[0])
        i = 0;
    else if (x >= xData_[n-1])
        i = n-2;
    else {
        // Find the index of the interval where is located the point to interpolate.
        for (i=0; i<n-1; i++) {
            if ((x >= xData_[i]) && (x < xData_[i+1]))
                 break;
        }        
    }

    // Intepolation.
    double temp = (xData_[i+1] - xData_[i]);
    double a = (xData_[i+1] - x) / temp;
    double b = 1-a;
    temp*=temp/6;        
    double c = (a*a-1)*a*temp;
    double d = (b*b-1)*b*temp;

    return a*yData_[i] + b*yData_[i+1] + c*d2_[i] + d*d2_[i+1];
}

//-----------------------------------------------------------------------------------------------------------------
nct::RealVector nct::interpolation::CubicSpline::eval(const RealVector& x) const
{
    if ((xData_.size() == 0) || (yData_.size() == 0) || (d2_.size() == 0))
        throw ConfigurationException(exc_bad_interpolation_model, SOURCE_INFO);

    auto n = xData_.size();     // Observations in the object.
    auto m = x.size();          // Points to interpolate.
    size_t i = 0;               // Interval of the point to interpolate.

    double temp, a, b, c, d;    // Variables for calculations.
    RealVector y(m);

    // Sort array.
    Array<std::pair<double, size_t>> xTmp(m);
    for (index_t j=0; j<m; j++)
        xTmp[j] = std::make_pair(x[j], j);
    sort(xTmp.begin(), xTmp.end(), 
        [](const std::pair<double, size_t>& p1, const std::pair<double, size_t>& p2)->bool
    {return p1.first<p2.first;});

    for (index_t j=0; j<m; j++) {
        // Interval where the point to interpolate is located.
        if (i == 0 && (xTmp[j].first < xData_[0]))
            i = 0;    
        else {
            for (; i<n-1; i++) {
                if ((xTmp[j].first >= xData_[i]) && (xTmp[j].first < xData_[i+1]))
                     break;
            }    
            if (i == n-1)
                i--;
        }

        // Interpolation.
        temp = (xData_[i+1] - xData_[i]);
        a = (xData_[i+1] - xTmp[j].first) / temp;
        b = 1-a;
        temp*=temp/6;        
        c = (a*a-1)*a*temp;
        d = (b*b-1)*b*temp;
        y[xTmp[j].second] = a*yData_[i] + b*yData_[i+1] + c*d2_[i] + d*d2_[i+1];    
    }    

    return y;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
