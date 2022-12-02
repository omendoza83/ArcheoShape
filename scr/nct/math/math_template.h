#include "math.h"
//=================================================================================================================
/**
 *  @file       math_template.h
 *  @brief      Implementation of the template functions defined in the nct::math namespace.
 *  @details    This file contains the implementation of the template functions declared in the 
 *              nct::math namespace.    
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
//       FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<nct::Signed T>
constexpr T nct::math::absolute(const T& v) noexcept
{
    return v >= 0 ? v : -v;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr T nct::math::sqr(const T& v) noexcept
{
    return v * v;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr T nct::math::cube(const T& v) noexcept
{
    return v * v* v;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr T nct::math::fourth_pwr(const T& v) noexcept
{
    return v * v* v* v;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr T nct::math::fifth_pwr(const T& v) noexcept
{
    return v * v* v* v* v;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::totally_ordered T>
constexpr const T& nct::math::max(const T& v1, const T& v2) noexcept
{
    return v2 > v1 ? (v2) : (v1);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::totally_ordered T>
constexpr const T& nct::math::max(const T& v1, const T& v2, const T& v3) noexcept
{
    if (v1 > v2)
        return v3 > v1 ? (v3) : (v1);
    else
        return v3 > v2 ? (v3) : (v2);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::totally_ordered T>
constexpr const T& nct::math::max(const T& v1, const T& v2, const T& v3, const T& v4) noexcept
{
    return math::max(math::max(v1, v2), math::max(v3, v4));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::totally_ordered T>
constexpr const T& nct::math::min(const T& v1, const T& v2) noexcept
{
    return v2 < v1 ? (v2) : (v1);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::totally_ordered T>
constexpr const T& nct::math::min(const T& v1, const T& v2, const T& v3) noexcept
{
    if (v1 < v2)
        return v3 < v1 ? (v3) : (v1);
    else
        return v3 < v2 ? (v3) : (v2);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::totally_ordered T>
constexpr const T& nct::math::min(const T& v1, const T& v2, const T& v3, const T& v4) noexcept
{
    return min(min(v1, v2), min(v3, v4));
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Signed T>
constexpr T nct::math::sign(const T& v) noexcept
{
    if (v == 0)
        return 0;
    return v > 0 ? 1 : -1;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Signed T>
constexpr T nct::math::sign(const T & a, const T & b) noexcept
{
    return b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Signed T>
constexpr T nct::math::positivePart(const T & v) noexcept
{
    return v < 0 ? (0) : (v);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Signed T>
constexpr T nct::math::negativePart(const T & v) noexcept
{
    return v > 0 ? (0) : (-v);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr T nct::math::lerp(double t, double t0, const T& x0, double t1, const T& x1)
{
    auto tt = (t - t0) / (t1 - t0);
    return static_cast<T>(x0 + x1 * tt - x0 * tt);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr T nct::math::linear(double t, const T& m, const T& a)
{
    return static_cast<T>(m * t + a);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr T nct::math::quadratic(double t, const T& a, const T& b, const T& c)
{
    return static_cast<T>(a * t * t + b * t + c);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr T nct::math::cubic(double t, const T& a, const T& b, const T& c, const T& d)
{
    return static_cast<T>(a * t * t * t + b * t * t + c * t + d);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
T nct::math::exponential(double t, const T& x0, const T& xt, const T& tau)
{
    return static_cast<T>(xt + (x0 - xt) * std::exp(-t / tau));
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
double nct::math::pythag(const T& a, const T& b)  noexcept
{
    auto absa = static_cast<double>(std::abs(a));
    auto absb = static_cast<double>(std::abs(b));
    return (absa > absb ? absa * std::sqrt(1.0 + math::sqr(absb / absa)) :
        (absb == 0 ? 0 : absb * std::sqrt(1.0 + math::sqr(absa / absb))));
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
constexpr T nct::math::absDifference(const T & v1, const T & v2) noexcept
{
    if (v1 > v2)
        return v1 - v2;
    return v2 - v1;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
constexpr double nct::math::absRealDifference(const T & v1, const T & v2) noexcept
{
    if (v1 > v2)
        return static_cast<double>(v1) - static_cast<double>(v2);
    return static_cast<double>(v2) - static_cast<double>(v1);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr double nct::math::absRelativeDifference(const T& v1, const T& v2) noexcept
{
    auto diff = absDifference(v1, v2);    
    
    double den = 0.5*(static_cast<double>(std::abs(v1)) + static_cast<double>(std::abs(v2)));
    if (den == 0)
        den = 1;

    return diff / den;
}

//-----------------------------------------------------------------------------------------------------------------
template<>
inline double nct::math::absRelativeDifference(const Complex& v1, const Complex& v2) noexcept
{
    auto diff = std::abs(v1 - v2);

    double den = 0.5*(static_cast<double>(std::abs(v1)) + static_cast<double>(std::abs(v2)));
    if (den == 0)
        den = 1;

    return diff / den;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr double nct::math::absRelativeDifferenceMod(const T& v1, const T& v2) noexcept
{
    auto diff = absDifference(v1, v2);
    if (diff <= 1)
        return diff;

    double den = 0.5 * (static_cast<double>(std::abs(v1)) + static_cast<double>(std::abs(v2)));
    return diff / den;
}

//-----------------------------------------------------------------------------------------------------------------
template<>
inline double nct::math::absRelativeDifferenceMod(const Complex& v1, const Complex& v2) noexcept
{
    auto diff = std::abs(v1 - v2);
    if (diff <= 1)
        return diff;

    double den = 0.5 * (static_cast<double>(std::abs(v1)) + static_cast<double>(std::abs(v2)));
    return diff / den;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type>  &&
    nct::Numeric<typename InputIt::value_type>
void nct::math::diff(InputIt first, InputIt last, OutIt out, unsigned int n)
{
    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    if (n == 0)
        throw ArgumentException("n", n, 0UL, RelationalOperator::GreaterThan, SOURCE_INFO);

    auto nx = last - first;
    if (nx <= static_cast<diff_t>(n))
        return;

    double sign = 1.;
    std::vector<double> coeff(n + static_cast<size_t>(1));
    for (unsigned int i = 0; i <= n; i++) {
        coeff[i] = sign * binCoefficient(n, i);
        sign *= -1.;
    }

    last = first + (nx - n);
    for (auto x = first; x != last; ++x) {
        *out = 0;
        for (unsigned int i = 0; i <= n; i++)
            *out += coeff[i] * (*(x + (n - i)));
        ++out;
    }

}

//-----------------------------------------------------------------------------------------------------------------
template<std::totally_ordered T>
constexpr T nct::math::threshold(const T & v, const T & tr, ThresholdType thresholdType)
{
    switch (thresholdType) {
        case ThresholdType::UpperThreshold:
            return upperThreshold(v, tr);
            //break;
        case ThresholdType::AbsUpperThreshold:
            return absUpperThreshold(v, tr);
            //break;
        case ThresholdType::LowerThreshold:
            return lowerThreshold(v, tr);
            //break;
        case ThresholdType::AbsLowerThreshold:
            return absLowerThreshold(v, tr);
            //break;
    }
    throw ArgumentException("thresholdType", exc_bad_threshold_type, SOURCE_INFO);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt> 
requires std::output_iterator<OutIt, typename InputIt::value_type> &&
    std::totally_ordered<typename InputIt::value_type>
void nct::math::threshold(InputIt first, InputIt last, OutIt out,
    const typename InputIt::value_type& tr, ThresholdType thresholdType)
{
    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    switch (thresholdType) {
        case ThresholdType::UpperThreshold:
            return upperThreshold(first, last, out, tr);
            //break;
        case ThresholdType::AbsUpperThreshold:
            return absUpperThreshold(first, last, out, tr);
            //break;
        case ThresholdType::LowerThreshold:
            return lowerThreshold(first, last, out, tr);
            //break;
        case ThresholdType::AbsLowerThreshold:
            return absLowerThreshold(first, last, out, tr);
            //break;
        default:
            throw ArgumentException("thresholdType", exc_bad_threshold_type, SOURCE_INFO);
            //break;
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<std::totally_ordered T>
constexpr T nct::math::upperThreshold(const T & v, const T & tr) noexcept
{
    return v > tr;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt> 
requires std::output_iterator<OutIt, typename InputIt::value_type> &&
    std::totally_ordered<typename InputIt::value_type>
void nct::math::upperThreshold(InputIt first, InputIt last, OutIt out, 
    const typename InputIt::value_type& tr)
{
    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    for (auto x = first; x != last; ++x) {
        *out = upperThreshold(*x, tr);
        ++out;
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Signed T>
constexpr T nct::math::absUpperThreshold(const T & v, const T & tr) noexcept
{
    return (v > 0 ? v : -v) > tr;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt> 
requires std::output_iterator<OutIt, typename InputIt::value_type> &&
    std::totally_ordered<typename InputIt::value_type>
void nct::math::absUpperThreshold(InputIt first, InputIt last, OutIt out,
    const typename InputIt::value_type& tr)
{
    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    for (auto x = first; x != last; ++x) {
        *out = absUpperThreshold(*x, tr);
        ++out;
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<std::totally_ordered T>
constexpr T nct::math::lowerThreshold(const T & v, const T & tr) noexcept
{
    return v < tr;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt> 
requires std::output_iterator<OutIt, typename InputIt::value_type> &&
    std::totally_ordered<typename InputIt::value_type>
void nct::math::lowerThreshold(InputIt first, InputIt last,
    OutIt out, const typename InputIt::value_type& tr)
{
    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    for (auto x = first; x != last; ++x) {
        *out = lowerThreshold(*x, tr);
        ++out;
    }

}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Signed T>
constexpr T nct::math::absLowerThreshold(const T & v, const T & tr) noexcept
{
    return (v > 0 ? v : -v) < tr;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires nct::Signed<typename InputIt::value_type> &&
    std::output_iterator<OutIt, typename InputIt::value_type>
void nct::math::absLowerThreshold(InputIt first, InputIt last,
    OutIt out, const typename InputIt::value_type& tr)
{
    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    for (auto x = first; x != last; ++x) {
        *out = absLowerThreshold(*x, tr);
        ++out;
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, std::input_or_output_iterator BidirectionalIterator>
bool nct::math::nextCombination(InputIt nbegin, InputIt nend,
    BidirectionalIterator rbegin, BidirectionalIterator rend)
{
    if ((nend - nbegin) < (rend - rbegin))
        throw ArgumentException("nbegin, nend, rbegin, rend", exc_bad_sizes_of_ranges, SOURCE_INFO);

    bool boolmarked = false;

    auto tmpREnd = rend;
    auto rMarked = rbegin;
    --tmpREnd;

    auto nIt1 = nend;
    --nIt1;

    for (auto rIt1 = tmpREnd; (rIt1 != rbegin || rIt1 == rbegin); --rIt1, --nIt1) {
        if (*rIt1 == *nIt1) {
            if (rIt1 != rbegin) {
                boolmarked = true;
                rMarked = (--rIt1);
                ++rIt1;
                continue;
            }
            else {
                return false;    // No more combinations.
            }
        }
        else {
            if (boolmarked == true) {
                auto nMarked = nbegin;
                for (auto nIt2 = nbegin; nIt2 != nend; ++nIt2) {
                    if (*rMarked == *nIt2) {
                        nMarked = nIt2;
                        break;
                    }
                }

                auto nIt3 = ++nMarked;
                for (auto rIt2 = rMarked; rIt2 != rend; ++rIt2, ++nIt3)
                    *rIt2 = *nIt3;
                return true;
            }
            for (auto nIt4 = nbegin; nIt4 != nend; ++nIt4) {
                if (*rIt1 == *nIt4) {
                    *rIt1 = *(++nIt4);
                    return true;
                }
            }
        }
    }

    return false; // If this point is reached, an error ocurred in the algorithm.
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, std::input_or_output_iterator BidirectionalIterator>
bool nct::math::previousCombination(InputIt nbegin, InputIt nend,
    BidirectionalIterator rbegin, BidirectionalIterator rend)
{
    if ((nend - nbegin) < (rend - rbegin))
        throw ArgumentException("nbegin, nend, rbegin, rend", exc_bad_sizes_of_ranges, SOURCE_INFO);

    auto rIt1 = rend;
    auto tmpREnd = rend;
    auto marked = rbegin;
    auto rMarked = rbegin;
    --rIt1;
    --tmpREnd;

    auto tmpNEnd = nend;
    auto nMarked = nbegin;
    --tmpNEnd;


    for (auto nIt1 = tmpNEnd; nIt1 != nbegin || nIt1 == nbegin; --nIt1) {
        if (*rIt1 == *nIt1) {
            rMarked = rIt1;
            nMarked = nIt1;
            break;
        }
    }

    auto nIt2 = nMarked;

    for (auto rIt2 = rMarked; rIt2 != rbegin || rIt2 == rbegin; --rIt2, --nIt2) {
        if (*rIt2 == *nIt2) {
            if (rIt2 == rbegin && !(*rIt2 == *nbegin)) {
                for (auto nIt3 = nbegin; nIt3 != nend; ++nIt3) {
                    if (*rIt2 == *nIt3) {
                        marked = rIt2;
                        *rIt2 = *(--nIt3);

                        auto nIt4 = nend;
                        --nIt4;
                        for (auto rIt3 = tmpREnd; (rIt3 != rbegin || rIt3 == rbegin) &&
                            rIt3 != marked; --rIt3, --nIt4)
                            *rIt3 = *nIt4;
                        return true;
                    }
                }
            }
            else if (rIt2 == rbegin && *rIt2 == *nbegin) {
                return false; // No more combinations.
            }
        }
        else {
            ++rIt2;
            marked = rIt2;
            for (auto nIt5 = nbegin; nIt5 != nend; ++nIt5) {
                if (*rIt2 == *nIt5) {
                    *rIt2 = *(--nIt5);

                    auto nIt6 = nend;
                    --nIt6;

                    for (auto rIt4 = tmpREnd; (rIt4 != rbegin || rIt4 == rbegin) &&
                        rIt4 != marked; --rIt4, --nIt6)
                        *rIt4 = *nIt6;

                    return true;
                }
            }
        }
    }

    return false; // If this point is reached, an error ocurred.
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
requires nct::Numeric<typename InputIt::value_type>
auto nct::math::squaredNorm(InputIt first, InputIt last)  -> decltype(std::norm(*first))
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    decltype(std::norm(*first)) r = 0;
    for (InputIt x = first; x != last; ++x)
        r += std::norm(*x);

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
requires nct::Numeric<typename InputIt::value_type>
double nct::math::euclidianNorm(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 0;
    for (InputIt x = first; x != last; ++x)
        r += static_cast<double>(std::norm(*x));

    return std::sqrt(r);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
requires nct::Numeric<typename InputIt::value_type>
double nct::math::lpNorm(InputIt first, InputIt last, double p)
{
    if (p < 1)
        throw ArgumentException("p", p, 1.,
            RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 0;
    if (p == 1) {
        // L1
        for (InputIt x = first; x != last; ++x)
            r += static_cast<double>(std::abs(*x));

        return r;
    }

    // LP
    for (InputIt x = first; x != last; ++x)
        r += std::pow(static_cast<double>(std::abs(*x)), p);

    return std::pow(r, 1. / p);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
requires nct::Numeric<typename InputIt::value_type>
auto nct::math::infinityNorm(InputIt first, InputIt last) -> decltype(std::abs(*first))
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    decltype(std::abs(*first)) r = 0;
    for (InputIt x = first; x != last; ++x)
        r = math::max(std::abs(*x), r);

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
requires nct::Numeric<typename InputIt::value_type>
auto nct::math::squaredNormOfDifference(InputIt first1, InputIt last1, 
    InputIt first2, InputIt last2) -> decltype(std::norm(*first1))
{
    if (first1 >= last1)
        throw RangeException("first1, last1", SOURCE_INFO);

    if (first2 >= last2)
        throw RangeException("first2, last2", SOURCE_INFO);

    if ((last1 - first1) != (last2 - first2))
        throw ArgumentException("first1, last1, first2, last2",
            exc_two_ranges_of_different_sizes, SOURCE_INFO);

    decltype(std::norm(*first1)) r = 0;
    for (InputIt x1 = first1, x2 = first2; x1 != last1 && x2 != last2; ++x1, ++x2)
        r += std::norm(*x1 - *x2);

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
requires nct::SignedNumeric<typename InputIt::value_type>
double nct::math::euclidianNormOfDifference(InputIt first1, InputIt last1, 
    InputIt first2, InputIt last2)
{
    if (first1 >= last1)
        throw RangeException("first1, last1", SOURCE_INFO);

    if (first2 >= last2)
        throw RangeException("first2, last2", SOURCE_INFO);

    if ((last1 - first1) != (last2 - first2))
        throw ArgumentException("first1, last1, first2, last2",
            exc_two_ranges_of_different_sizes, SOURCE_INFO);

    double r = 0;
    for (InputIt x1 = first1, x2 = first2; x1 != last1 && x2 != last2; ++x1, ++x2)
        r += static_cast<double>(std::norm(*x1 - *x2));

    return std::sqrt(r);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
requires nct::SignedNumeric<typename InputIt::value_type>
double nct::math::lpNormOfDifference(InputIt first1, InputIt last1, 
    InputIt first2, InputIt last2, double p)
{
    if (p < 1)
        throw ArgumentException("p", p, 1.,
            RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    if (first1 >= last1)
        throw RangeException("first1, last1", SOURCE_INFO);

    if (first2 >= last2)
        throw RangeException("first2, last2", SOURCE_INFO);

    if ((last1 - first1) != (last2 - first2))
        throw ArgumentException("first1, last1, first2, last2",
            exc_two_ranges_of_different_sizes, SOURCE_INFO);

    double r = 0;
    if (p == 1) {
        // L1
        for (InputIt x1 = first1, x2 = first2; x1 != last1 && x2 != last2; ++x1, ++x2)
            r += static_cast<double>(std::abs(*x1 - *x2));

        return r;
    }

    // LP
    for (InputIt x1 = first1, x2 = first2; x1 != last1 && x2 != last2; ++x1, ++x2)
        r += std::pow(static_cast<double>(std::abs(*x1 - *x2)), p);

    return std::pow(r, 1. / p);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
requires nct::SignedNumeric<typename InputIt::value_type>
auto nct::math::infinityNormOfDifference(InputIt first1, InputIt last1, 
    InputIt first2, InputIt last2) -> decltype(std::abs(*first1))
{
    if (first1 >= last1)
        throw RangeException("first1, last1", SOURCE_INFO);

    if (first2 >= last2)
        throw RangeException("first2, last2", SOURCE_INFO);

    if ((last1 - first1) != (last2 - first2))
        throw ArgumentException("first1, last1, first2, last2",
            exc_two_ranges_of_different_sizes, SOURCE_INFO);

    decltype(std::abs(*first1)) r = 0;
    for (InputIt x1 = first1, x2 = first2; x1 != last1 && x2 != last2; ++x1, ++x2)
        r = math::max(std::abs(*x1 - *x2), r);

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> &&
    std::totally_ordered<typename InputIt::value_type>
void nct::math::normalizeByMax(InputIt first, InputIt last, OutIt out)
{
    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    auto max = maximumAbs(first, last);
    if (max == 0)
        max = 1;

    for (auto x = first; x != last; ++x) {
        *out = (*x) / max;
        ++out;
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> &&
    nct::Numeric<typename InputIt::value_type>
void nct::math::normalizeBySum(InputIt first, InputIt last, OutIt out)
{
    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    auto norm = sum(first, last);
    if (norm == 0)
        norm = 1;

    for (auto x = first; x != last; ++x) {
        *out = (*x) / norm;
        ++out;
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Numeric<typename InputIt1::value_type> && 
    nct::Numeric<typename InputIt2::value_type>
auto nct::math::dotProduct(InputIt1 first1, InputIt1 last1,
    InputIt2 first2, InputIt2 last2) -> decltype((*first1) * (*first2))
{
    if (first1 >= last1)
        throw RangeException("first1, last1", SOURCE_INFO);

    if (first2 >= last2)
        throw RangeException("first2, last2", SOURCE_INFO);

    if ((last1 - first1) != (last2 - first2))
        throw ArgumentException("first1, last1, first2, last2", 
            exc_two_ranges_of_different_sizes, SOURCE_INFO);


    auto x1 = first1;
    auto x2 = first2;
    auto res = (*x1) * (*x2);
    ++x1;
    ++x2;
    for (; (x1 != last1) && (x2 != last2); ++x1, ++x2)
        res += (*x1) * (*x2);

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Numeric<typename InputIt::value_type>
auto nct::math::sum(InputIt first, InputIt last) -> typename std::remove_cvref_t<decltype(*first)>
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    typename std::remove_cvref_t<decltype(*first)> r = 0;
    for (InputIt x = first; x != last; ++x)
        r += *x;

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
requires std::convertible_to<typename InputIt::value_type, double>
double nct::math::castSum(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 0;
    for (InputIt x = first; x != last; ++x)
        r += static_cast<double>(*x);

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> 
requires std::totally_ordered<typename InputIt::value_type>
auto nct::math::minimum(InputIt first, InputIt last) -> typename std::remove_cvref_t<decltype(*first)>
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    auto r = *first;
    for (InputIt x = first; x != last; ++x)
        r = math::min(*x, r);

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
requires std::totally_ordered<typename InputIt::value_type>
auto nct::math::minimumValueIndex(InputIt first, InputIt last) -> decltype(last - first)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    auto n = last - first;
    decltype(last - first) index = 0;
    auto r = *first;

    InputIt x = first;
    for (decltype(last - first) i = 1; i < n; i++) {
        ++x;
        if (*x < r) {
            index = i;
            r = *x;
        }
    }

    return index;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
auto nct::math::minimumAbs(InputIt first, InputIt last) -> decltype(std::abs(*first))
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    auto r = std::abs(*first);
    for (InputIt x = first; x != last; ++x)
        r = math::min(std::abs(*x), r);

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
auto nct::math::minimumAbsValueIndex(InputIt first, InputIt last) -> decltype(last - first)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    auto n = last - first;
    decltype(last - first) index = 0;
    auto r = std::abs(*first);

    InputIt x = first;
    for (decltype(last - first) i = 1; i < n; i++) {
        ++x;
        if (std::abs(*x) < r) {
            index = i;
            r = std::abs(*x);
        }
    }

    return index;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
requires std::totally_ordered<typename InputIt::value_type>
auto nct::math::maximum(InputIt first, InputIt last) -> typename std::remove_cvref_t<decltype(*first)>
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    auto r = *first;
    for (InputIt x = first; x != last; ++x)
        r = math::max(*x, r);

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
requires std::totally_ordered<typename InputIt::value_type>
auto nct::math::maximumValueIndex(InputIt first, InputIt last) -> decltype(last - first)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    auto n = last - first;
    decltype(last - first) index = 0;
    auto r = *first;

    InputIt x = first;
    for (decltype(last - first) i = 1; i < n; i++) {
        ++x;
        if (*x > r) {
            index = i;
            r = *x;
        }
    }

    return index;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
requires nct::SignedNumeric<typename InputIt::value_type>
auto nct::math::maximumAbs(InputIt first, InputIt last) -> decltype(std::abs(*first))
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    auto r = std::abs(*first);
    for (InputIt x = first; x != last; ++x)
        r = math::max(std::abs(*x), r);

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
requires nct::SignedNumeric<typename InputIt::value_type>
auto nct::math::maximumAbsValueIndex(InputIt first, InputIt last) -> decltype(last - first)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    auto n = last - first;
    decltype(last - first) index = 0;
    auto r = std::abs(*first);

    InputIt x = first;
    for (decltype(last - first) i = 1; i < n; i++) {
        ++x;
        if (std::abs(*x) > r) {
            index = i;
            r = std::abs(*x);
        }
    }

    return index;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
requires nct::SignedNumeric<typename InputIt::value_type>
auto nct::math::maximumAbsDifference(InputIt first1, InputIt last1,
    InputIt first2, InputIt last2) -> typename std::remove_cvref_t<decltype(*first1)>
{
    if (first1 >= last1)
        throw RangeException("first1, last1", SOURCE_INFO);

    if (first2 >= last2)
        throw RangeException("first2, last2", SOURCE_INFO);

    if ((last1 - first1) != (last2 - first2))
        throw ArgumentException("first1, last1, first2, last2", 
            exc_two_ranges_of_different_sizes, SOURCE_INFO);

    auto r = absDifference(*first1, *first2);
    for (InputIt x1 = first1, x2 = first2; (x1 != last1) && (x2 != last2); ++x1, ++x2)
        r = math::max(absDifference(*x1, *x2), r);

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
requires nct::SignedNumeric<typename InputIt::value_type>
double nct::math::maximumAbsRelativeDifference(InputIt first1, InputIt last1,
    InputIt first2, InputIt last2)
{
    if (first1 >= last1)
        throw RangeException("first1, last1", SOURCE_INFO);

    if (first2 >= last2)
        throw RangeException("first2, last2", SOURCE_INFO);

    if ((last1 - first1) != (last2 - first2))
        throw ArgumentException("first1, last1, first2, last2", 
            exc_two_ranges_of_different_sizes, SOURCE_INFO);
    
    auto r = absRelativeDifference(*first1, *first2);
    
    for (InputIt x1 = first1, x2 = first2; (x1 != last1) && (x2 != last2); ++x1, ++x2)
        r = math::max(absRelativeDifference(*x1, *x2), r);        

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt>
requires nct::SignedNumeric<typename InputIt::value_type>
double nct::math::maximumAbsRelativeDifferenceMod(InputIt first1, InputIt last1,
    InputIt first2, InputIt last2)
{
    if (first1 >= last1)
        throw RangeException("first1, last1", SOURCE_INFO);

    if (first2 >= last2)
        throw RangeException("first2, last2", SOURCE_INFO);

    if ((last1 - first1) != (last2 - first2))
        throw ArgumentException("first1, last1, first2, last2",
            exc_two_ranges_of_different_sizes, SOURCE_INFO);

    auto r = absRelativeDifferenceMod(*first1, *first2);

    for (InputIt x1 = first1, x2 = first2; (x1 != last1) && (x2 != last2); ++x1, ++x2)
        r = math::max(absRelativeDifferenceMod(*x1, *x2), r);

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires std::integral<typename InputIt::value_type>
auto nct::math::logicalAnd(InputIt first, InputIt last) ->
typename std::remove_cvref_t<decltype(*first)>
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    auto r = *first;
    for (InputIt x = first; x != last; ++x)
        r &= *x;

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires std::integral<typename InputIt::value_type>
auto nct::math::logicalOr(InputIt first, InputIt last) ->
typename std::remove_cvref_t<decltype(*first)>
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    auto r = *first;
    for (InputIt x = first; x != last; ++x)
        r |= *x;

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::floating_point T>
inline T nct::math::halfRoundUp(const T & v) noexcept
{
    return static_cast<T>(std::floor(v + 0.5));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::floating_point T>
inline T nct::math::halfRoundDown(const T & v) noexcept
{
    return static_cast<T>(std::ceil(v - 0.5));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::floating_point T>
inline T nct::math::roundHalfAwayFromZero(const T & v) noexcept
{
    auto r = std::floor(std::abs(v) + 0.5);
    return (v < 0.0) ? -r : r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::floating_point T>
inline T nct::math::roundHalfTowardsZero(const T & v) noexcept
{
    auto r = std::ceil(std::abs(v) - 0.5);
    return (v < 0.0) ? -r : r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::floating_point T>
inline T nct::math::roundAwayFromZero(const T & v) noexcept
{
    auto r = std::ceil(std::fabs(v));
    return (v < 0.0) ? -r : r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::floating_point T>
inline T nct::math::roundTowardsZero(const T & v) noexcept
{
    auto r = std::floor(std::fabs(v));
    return (v < 0.0) ? -r : r;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
constexpr T nct::math::wrap(const T & v, const T & l, const T & u)
{
    if (l >= u)
        throw ArgumentException("l, u", exc_bad_bounds, SOURCE_INFO);

    auto diff = u - l;
    auto val = v;

    while (val < l)
        val += diff;

    while (val >= u)
        val -= diff;

    return val;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
constexpr double nct::math::wrapToPi(const T& angle) noexcept
{
    double val = static_cast<double>(angle);

    while (val < -PI)
        val += TWO_PI;

    while (val >= PI)
        val -= TWO_PI;

    return val;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
constexpr double nct::math::wrapTo2Pi(const T& angle) noexcept
{
    T val = static_cast<double>(angle);

    while (val < 0)
        val += TWO_PI;

    while (val >= TWO_PI)
        val -= TWO_PI;

    return val;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
constexpr T nct::math::wrapTo180(const T& angle) noexcept
{
    T val = angle;

    while (val < -180)
        val += 360;

    while (val >= 180)
        val -= 360;

    return val;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
constexpr T nct::math::wrapTo360(const T& angle) noexcept
{
    T val = angle;

    while (val < 0)
        val += 360;

    while (val >= 360)
        val -= 360;

    return val;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> &&
    nct::Arithmetic<typename InputIt::value_type>
void nct::math::unwrap(InputIt first, InputIt last,
    OutIt out, double cutoff)
{
    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    if (cutoff <= 0)
        throw ArgumentException("cutoff", cutoff, 0.0, RelationalOperator::GreaterThan, SOURCE_INFO);

    if ((last - first) < 2)
        return;

    double acc = 0;
    auto cutoff2 = 2 * cutoff;
    auto xm = *first;
    ++first;
    
    *out = xm;    
    ++out;
    for (auto x = first; x != last; ++x, ++out) {
        auto d = (*x) - xm;
        xm = (*x);

        auto dc = 0.0; 
        if (std::abs(d) >= cutoff)
            dc = roundHalfTowardsZero(d / cutoff2);

        acc += dc;        
        *out = (*x) - cutoff2 * acc;
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> &&
    nct::Arithmetic<typename InputIt::value_type>
void nct::math::unwrapPhaseAngles(InputIt first, InputIt last,
    OutIt out)
{
    unwrap(first, last, out, PI);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
constexpr double nct::math::radToDeg(const T& angle) noexcept
{
    return static_cast<double>(angle * 180. / PI);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
constexpr double nct::math::degToRad(const T& angle) noexcept
{
    return static_cast<double>(PI * angle / 180.);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
double nct::math::angularDistance(const T& angle1, const T& angle2) noexcept
{
    return static_cast<double>(std::atan2(std::sin(angle1 - angle2),
        std::cos(angle1 - angle2)));
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr T nct::math::calculateDelta(const T& x, const T& h) noexcept
{
    T xh = x + h;
    return xh - x;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================

