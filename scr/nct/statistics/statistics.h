//=================================================================================================================
/**
 *  @file       statistics.h
 *  @brief      nct::statistics namespace.
 *  @details    Declaration of the nct::statistics namespace.
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

#ifndef NCT_STATISTICS_H_INCLUDE
#define NCT_STATISTICS_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/math/math.h>

#include <algorithm>
#include <vector>

//=================================================================================================================
namespace nct {
/**
 *  @brief      Statistics namespace.
 *  @details    This namespace contains functions related to statistics methods and inference.
 */
namespace statistics {

////////// Enumerations //////////

/**
 *  @brief      Types of results for inference tests.
 *  @details    Types of results that inference tests can calculate.
 */
enum class ResultType : unsigned char {

    LeftTailedPValue,   /**< Left tailed P-value. */

    RightTailedPValue,  /**< Right tailed P-value. */

    TwoTailedPValue,    /**< Two tailed P-value. */

    SignificanceIndex,  /**< Significant index. */

    TestStatistic,      /**< Value of the test statistic. */
};

////////// Linear data //////////

// Descriptive statistics.        

/**
 *  @brief      Mean.
 *  @details    This function calculates the mean of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The mean of the observations. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double mean(InputIt first, InputIt last);

/**
 *  @brief      Weighted arithemetic mean.
 *  @details    This function calculates the weighted arithmetic mean of a set of observations. The function computes:
 *              sum(wi xi)/sum(wi).
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The mean of the observations. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double mean(InputIt1 first, InputIt1 last, InputIt2 wFirst);

/**
 *  @brief      Quadratic mean.
 *  @details    This function calculates the quadratic mean of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The quadratic mean of the observations. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double quadraticMean(InputIt first, InputIt last);

/**
 *  @brief      Weighted quadratic mean.
 *  @details    This function calculates the weighted quadratic mean of a set of observations. The function computes:
 *              (sum(wi * xi^2) / sum(wi))^(1/2) .
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The mean of the observations. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double quadraticMean(InputIt1 first, InputIt1 last, InputIt2 wFirst);

/**
 *  @brief      Harmonic mean.
 *  @details    This function calculates the harmonic mean of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The harmonic mean of the observations. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double harmonicMean(InputIt first, InputIt last);

/**
 *  @brief      Weighted harmonic mean.
 *  @details    This function calculates the weighted harmonic mean of a set of observations. The function computes:
 *              sum(wi)/sum(wi/xi).
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The mean of the observations. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double harmonicMean(InputIt1 first, InputIt1 last, InputIt2 wFirst);

/**
 *  @brief      Geometric mean.
 *  @details    This function calculates the geometric mean of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The geometric mean of the observations. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double geometricMean(InputIt first, InputIt last);

/**
 *  @brief      Weighted geometric mean.
 *  @details    This function calculates the weighted geometric mean of a set of observations. The function computes:
 *              mult(xi^wi)^sum(wi).
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The mean of the observations. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double geometricMean(InputIt1 first, InputIt1 last, InputIt2 wFirst);

/**
 *  @brief      Power mean.
 *  @details    This function calculates the generilized power mean of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  p  Power of the mean.
 *  @returns    The mean of the observations. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double powerMean(InputIt first, InputIt last, double p);

/**
 *  @brief      Weighted power mean.
 *  @details    This function calculates the weighted power mean of a set of observations. The function computes:
 *              (sum(wi * xi^p) / sum(wi))^(1/p) .
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @param[in]  p  Power of the mean.
 *  @returns    The mean of the observations. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double powerMean(InputIt1 first, InputIt1 last, InputIt2 wFirst, double p);

/**
 *  @brief      Median.
 *  @details    This function calculates the median of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The median of the observations. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double median(InputIt first, InputIt last);

/**
 *  @brief      Weighted meadian.
 *  @details    This function calculates the weighted median of a set of observations. 
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The weighted median of the observations. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double median(InputIt1 first, InputIt1 last, InputIt2 wFirst);

/**
 *  @brief      Variance.
 *  @details    This function calculates the variance of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The variance of the observations. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double variance(InputIt first, InputIt last);

/**
 *  @brief      Weighted variance.
 *  @details    This function calculates the weighted variance of a set of observations.
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The variance of the observations. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double variance(InputIt1 first, InputIt1 last, InputIt2 wFirst);

/**
 *  @brief      Weighted variance.
 *  @details    This function calculates a weighted version of the variance of a set of observations.
 *              Use this function when each given observation represents the mean values of other sub-sets, 
 *              and only these mean values and the sum of the squares of each sub-set are available. 
 *              The final result may be represented in the following way: 
 *              (sum(wi*sqr) - sum(wi*xi)*sum(wi*xi)/sum(wi)) / sum(wi).
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of mean values.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of sums of squares.
 *  @tparam     InputIt3  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the initial position of a container with the mean values.
 *  @param[in]  last  Iterator defining the final position of a container with the mean values.
 *  @param[in]  sqrFirst  Iterator defining the initial position of a container with the sum of squares.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The variance of the observations. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2, 
    std::random_access_iterator InputIt3>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type> &&
    nct::Arithmetic<typename InputIt3::value_type>
double variance(InputIt1 first, InputIt1 last, InputIt2 sqrFirst, InputIt3 wFirst);

/**
 *  @brief      Sample variance.
 *  @details    This function calculates the sample variance (unbiased estimator of the variance) of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The variance of the observations. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double sampleVariance(InputIt first, InputIt last);

/**
 *  @brief      Weighted sample variance.
 *  @details    This function calculates the weighted sample variance of a set of observations.
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The variance of the observations. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double sampleVariance(InputIt1 first, InputIt1 last, InputIt2 wFirst);

/**
 *  @brief      Weighted sample variance.
 *  @details    This function calculates a weighted version of the sample variance of a set of
 *              observations. use this function when each given observation represents the mean values of
 *              other sub-sets, and only these mean values and the sum of the squares of each sub-set are
 *              available. The final result may be represented in the following way: (sum(wi*sqr) -
 *              sum(wi*xi)*sum(wi*xi)/sum(wi)) / (sum(wi) - 1).
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of mean values.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of sums of squares.
 *  @tparam     InputIt3  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the initial position of a container with the mean values.
 *  @param[in]  last  Iterator defining the final position of a container with the mean values.
 *  @param[in]  sqrFirst  Iterator defining the initial position of a container with the sum of squares.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The variance of the observations. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2, 
    std::random_access_iterator InputIt3>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type> &&
    nct::Arithmetic<typename InputIt3::value_type>
double sampleVariance(InputIt1 first, InputIt1 last, InputIt2 sqrFirst, InputIt3 wFirst);

/**
 *  @brief      Standard deviation.
 *  @details    This function calculates the standard deviation of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The standard deviation of the observations. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double standardDeviation(InputIt first, InputIt last);

/**
 *  @brief      Weighted standard deviation.
 *  @details    This function calculates the weighted standard deviation of a set of observations.
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The standard deviation of the observations. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double standardDeviation(InputIt1 first, InputIt1 last, InputIt2 wFirst);

/**
 *  @brief      Weighted standard deviation.
 *  @details    This function calculates a weighted version of the standard deviation of a set of
 *              observations. use this function when each given observation represents the mean values of
 *              other sub-sets, and only these mean values and the sum of the squares of each sub-set are
 *              available. The final result may be represented in the following way:
 *              std::sqrt((sum(wi*sqr) - sum(wi*xi)*sum(wi*xi)/sum(wi)) / sum(wi)).
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of mean values.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of sums of squares.
 *  @tparam     InputIt3  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the initial position of a container with the mean values.
 *  @param[in]  last  Iterator defining the final position of a container with the mean values.
 *  @param[in]  sqrFirst  Iterator defining the initial position of a container with the sum of squares.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The standard deviation of the observations. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2, 
    std::random_access_iterator InputIt3>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type> &&
    nct::Arithmetic<typename InputIt3::value_type>
double standardDeviation(InputIt1 first, InputIt1 last, InputIt2 sqrFirst, InputIt3 wFirst);

/**
 *  @brief      Sample standard deviation.
 *  @details    This function calculates the sample standard deviation (unbiased estimator of the standard deviation)
 *              of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The standard deviation of the observations.  
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double sampleStandardDeviation(InputIt first, InputIt last);

/**
 *  @brief      Weighted sample standard deviation.
 *  @details    This function calculates the weighted sample standard deviation of a set of observations.
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The standard deviation of the observations.  
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double sampleStandardDeviation(InputIt1 first, InputIt1 last, InputIt2 wFirst);

/**
 *  @brief      Weighted sample standard deviation.
 *  @details    This function calculates a weighted version of the sample standard deviation of a
 *              set of observations. use this function when each given observation represents the mean
 *              values of other sub-sets,  and only these mean values and the sum of the squares of each
 *              sub-set are available. The final result may be represented in the following way:
 *              std::sqrt((sum(wi*sqr) - sum(wi*xi)*sum(wi*xi)/sum(wi)) / (sum(wi) - 1)).
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of mean values.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of sums of squares.
 *  @tparam     InputIt3  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the initial position of a container with the mean values.
 *  @param[in]  last  Iterator defining the final position of a container with the mean values.
 *  @param[in]  sqrFirst  Iterator defining the initial position of a container with the sum of squares.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The standard deviation of the observations. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2, 
    std::random_access_iterator InputIt3>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type> &&
    nct::Arithmetic<typename InputIt3::value_type>
double sampleStandardDeviation(InputIt1 first, InputIt1 last, InputIt2 sqrFirst, InputIt3 wFirst);

/**
 *  @brief      Median absolute deviation (MAD).
 *  @details    This function calculates the median absolute deviation of a set of numerical observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The MAD estimator of the observations.   
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double medianAbsoluteDeviation(InputIt first, InputIt last);

/**
 *  @brief      Robust standard deviation.
 *  @details    This function calculates a robust version of the standard deviation of a set of observations. This 
 *              estimator works well in the presence of outliers.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The standard deviation of the observations.   
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double robustStandardDeviation(InputIt first, InputIt last);

/**
 *  @brief      Interquartile range.
 *  @details    This function calculates the interquartile-range of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The interquartile range.
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double interquartileRange(InputIt first, InputIt last);

/**
 *  @brief      Skewness.
 *  @details    This function calculates the skewness of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The skewness of the observations. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double skewness(InputIt first, InputIt last);

/**
 *  @brief      Sample skewness.
 *  @details    This function calculates the sample skewness of a set of observations. (unbiased estimator of the 
 *              skewness).
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The sample skewness of the observations. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double sampleSkewness(InputIt first, InputIt last);

/**
 *  @brief      Medcouple estimate.
 *  @details    This function calculates the medcouple estimate which represents the skewness of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The medcouple of the observations. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double medcouple(InputIt first, InputIt last);

/**
 *  @brief      Kurtosis.
 *  @details    This function calculates the kurtosis of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The kurtosis of the observations. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double kurtosis(InputIt first, InputIt last);

/**
 *  @brief      Sample kurtosis.
 *  @details    This function calculates the sample kurtosis of a set of observations (unbiased estimator of the 
 *              kurtosis).
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The sample kurtosis of the observations.  
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double sampleKurtosis(InputIt first, InputIt last);

/**
 *  @brief      Second moment.
 *  @details    This function calculates the second moment of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the moment. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double secondMoment(InputIt first, InputIt last);

/**
 *  @brief      Third moment.
 *  @details    This function calculates the third moment of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the moment. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double thirdMoment(InputIt first, InputIt last);

/**
 *  @brief      Third centered moment.
 *  @details    This function calculates the third centered moment of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the moment. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double thirdCentralMoment(InputIt first, InputIt last);

/**
 *  @brief      Fourth moment.
 *  @details    This function calculates the fourth moment of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the moment. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double fourthMoment(InputIt first, InputIt last);

/**
 *  @brief      Fourth centered moment.
 *  @details    This function calculates the fourth centered moment of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the moment. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double fourthCentralMoment(InputIt first, InputIt last);

/**
 *  @brief      K moment.
 *  @details    This function calculates the K-moment of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  k  Moment to calculate.
 *  @returns    The value of the moment. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double kMoment(InputIt first, InputIt last, unsigned int k);

/**
 *  @brief      K-centered moment.
 *  @details    This function calculates the K centered moment of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  k  Moment to calculate.
 *  @returns    The value of the moment. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double kCentralMoment(InputIt first, InputIt last, unsigned int k);

/**
 *  @brief      Covariance.
 *  @details    This function calculates the covariance of two sets of observations. Both sets must be of 
 *              the same size.
 *  @tparam     InputIt1  The iterator type to be used to traverse the observations of group 1.
 *  @tparam     InputIt2  The iterator type to be used to traverse the observations of group 2.
 *  @param[in]  xFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  xLast  Iiterator to the final position of one of the sequences.
 *  @param[in]  yFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  yLast  Iiterator to the final position of one of the sequences.
 *  @returns    The covariance.   
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double covariance(InputIt1 xFirst, InputIt1 xLast, InputIt2 yFirst, InputIt2 yLast);

/**
 *  @brief      Weighted covariance.
 *  @details    This function calculates the weighted covariance of two sets of observations. Both sets must be 
 *              of the same size.
 *  @tparam     InputIt1  The iterator type to be used to traverse the observations of group 1.
 *  @tparam     InputIt2  The iterator type to be used to traverse the observations of group 2.
 *  @tparam     InputIt3  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  xFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  xLast  Iiterator to the final position of one of the sequences.
 *  @param[in]  yFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  yLast  Iiterator to the final position of one of the sequences.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The covariance.   
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2, 
    std::random_access_iterator InputIt3>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type> &&
    nct::Arithmetic<typename InputIt3::value_type>
double covariance(InputIt1 xFirst, InputIt1 xLast, InputIt2 yFirst, InputIt2 yLast, InputIt3 wFirst);

/**
 *  @brief      Sample covariance.
 *  @details    This function calculates the sample covariance of two sets of observations (unbiased estimator of the 
 *              covariance). Both sets must be of the same size.
 *  @tparam     InputIt1  The iterator type to be used to traverse the observations of group 1.
 *  @tparam     InputIt2  The iterator type to be used to traverse the observations of group 2.
 *  @param[in]  xFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  xLast  Iiterator to the final position of one of the sequences.
 *  @param[in]  yFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  yLast  Iiterator to the final position of one of the sequences.
 *  @returns    The covariance.   
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type>&& nct::Arithmetic<typename InputIt2::value_type>
double sampleCovariance(InputIt1 xFirst, InputIt1 xLast, InputIt2 yFirst, InputIt2 yLast);

/**
 *  @brief      Weighted sample covariance.
 *  @details    This function calculates the weighted sample covariance of two sets of observations. Both sets must be 
 *              of the same size.
 *  @tparam     InputIt1  The iterator type to be used to traverse the observations of group 1.
 *  @tparam     InputIt2  The iterator type to be used to traverse the observations of group 2.
 *  @tparam     InputIt3  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  xFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  xLast  Iiterator to the final position of one of the sequences.
 *  @param[in]  yFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  yLast  Iiterator to the final position of one of the sequences.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The covariance.   
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2, 
    std::random_access_iterator InputIt3>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type> &&
    nct::Arithmetic<typename InputIt3::value_type>
double sampleCovariance(InputIt1 xFirst, InputIt1 xLast, InputIt2 yFirst, InputIt2 yLast, InputIt3 wFirst);

/**
 *  @brief      Pearson correlation.
 *  @details    This function calculates the person correlation of two paired samples.
 *  @tparam     InputIt1  The iterator type to be used to traverse the observations of group 1.
 *  @tparam     InputIt2  The iterator type to be used to traverse the observations of group 2.
 *  @param[in]  xFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  xLast  Iiterator to the final position of one of the sequences.
 *  @param[in]  yFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  yLast  Iiterator to the final position of one of the sequences.
 *  @returns    The correlation coefficient.   
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double pearsonCorrelation(InputIt1 xFirst, InputIt1 xLast, InputIt2 yFirst, InputIt2 yLast);

/**
 *  @brief      Spearman's Rho correlation.
 *  @details    This function calculates the Spearman's rho correlation of two paired samples.
 *  @tparam     InputIt1  The iterator type to be used to traverse the observations of group 1.
 *  @tparam     InputIt2  The iterator type to be used to traverse the observations of group 2.
 *  @param[in]  xFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  xLast  Iiterator to the final position of one of the sequences.
 *  @param[in]  yFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  yLast  Iiterator to the final position of one of the sequences.
 *  @returns    The correlation coefficient.   
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double spearmanRhoCorrelation(InputIt1 xFirst, InputIt1 xLast, InputIt2 yFirst, InputIt2 yLast);

/**
 *  @brief      Kendal's Tau correlation.
 *  @details    This function calculates the Kendal's Tau correlation of two paired samples.
 *  @tparam     InputIt1  The iterator type to be used to traverse the observations of group 1.
 *  @tparam     InputIt2  The iterator type to be used to traverse the observations of group 2.
 *  @param[in]  xFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  xLast  Iiterator to the final position of one of the sequences.
 *  @param[in]  yFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  yLast  Iiterator to the final position of one of the sequences.
 *  @returns    The correlation coefficient.   
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double kendallTauCorrelation(InputIt1 xFirst, InputIt1 xLast, InputIt2 yFirst, InputIt2 yLast);

/**
 *  @brief      Difference of two means.
 *  @details    This function calculates the difference of the sample means.
 *  @tparam     InputIt1  The iterator type to be used to traverse the observations of group 1.
 *  @tparam     InputIt2  The iterator type to be used to traverse the observations of group 2.
 *  @param[in]  xFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  xLast  Iiterator to the final position of one of the sequences.
 *  @param[in]  yFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  yLast  Iiterator to the final position of one of the sequences.
 *  @returns    The difference of the sample means.   
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double differenceOfTwoMeans(InputIt1 xFirst, InputIt1 xLast, InputIt2 yFirst, InputIt2 yLast);

/**
 *  @brief      Normalized difference of two means.
 *  @details    This function calculates the normalized (studenized) difference of the sample means.
 *  @tparam     InputIt1  The iterator type to be used to traverse the observations of group 1.
 *  @tparam     InputIt2  The iterator type to be used to traverse the observations of group 2.
 *  @param[in]  xFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  xLast  Iiterator to the final position of one of the sequences.
 *  @param[in]  yFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  yLast  Iiterator to the final position of one of the sequences.
 *  @returns    The normalized difference of the sample means.   
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double normDifferenceOfTwoMeans(InputIt1 xFirst, InputIt1 xLast, InputIt2 yFirst, InputIt2 yLast);

/**
 *  @brief      Normalized difference of two means.
 *  @details    This function calculates the normalized (studenized) difference of the sample means.
 *  @tparam     InputIt1  The iterator type to be used to traverse the observations of group 1.
 *  @tparam     InputIt2  The iterator type to be used to traverse the observations of group 2.
 *  @param[in]  xFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  xLast  Iiterator to the final position of one of the sequences.
 *  @param[in]  yFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  yLast  Iiterator to the final position of one of the sequences.
 *  @returns    The calculated normalized difference and the degress of freedom of the calculated
 *              difference.
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
std::pair<double, double> normDifferenceOfTwoMeansDf(InputIt1 xFirst, InputIt1 xLast,
    InputIt2 yFirst, InputIt2 yLast);

// Performance metrics.

/**
 *  @brief      Tanimoto index.
 *  @details    This function calculates the tanimoto index of two containers: |(X AND Y)|/|X OR Y|.
 *  @tparam     InputIt1  The iterator type to be used to traverse the container 1.
 *  @tparam     InputIt2  The iterator type to be used to traverse the container 2.
 *  @param[in]  xFirst  Iterator defining the initial position of a container.
 *  @param[in]  xLast  Iterator defining the final position of a container.
 *  @param[in]  yFirst  Iterator defining the initial position of a container.
 *  @param[in]  yLast  Iterator defining the final position of a container.
 *  @returns    The tanimoto index of x and y. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double tanimotoIndex(InputIt1 xFirst, InputIt1 xLast, InputIt2 yFirst, InputIt2 yLast);

/**
 *  @brief      True positives.
 *  @details    This function calculates the number of positives which are correctly identified as such.
 *              The container x indicates the test results that will be evaluated, while the container 
 *              t indicates the set true positives and negatives.
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of test results.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of positives and negatives.
 *  @param[in]  xFirst  Iterator defining the initial position of a container.
 *  @param[in]  xLast  Iterator defining the final position of a container.
 *  @param[in]  tFirst  Iterator defining the initial position of a container.
 *  @param[in]  tLast  Iterator defining the final position of a container.
 *  @returns    The number of true positives in container x.
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
size_t truePositives(InputIt1 xFirst, InputIt1 xLast, InputIt2 tFirst, InputIt2 tLast);

/**
 *  @brief      True positive rate.
 *  @details    This function calculates the proportion of actual positives which are correctly identified as such.
 *              The container x indicates the test results that will be evaluated, while the container 
 *              t indicates the set true positives and negatives.
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of test results.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of positives and negatives.
 *  @param[in]  xFirst  Iterator defining the initial position of a container.
 *  @param[in]  xLast  Iterator defining the final position of a container.
 *  @param[in]  tFirst  Iterator defining the initial position of a container.
 *  @param[in]  tLast  Iterator defining the final position of a container.
 *  @returns    The true positive rate of the tests in container x.
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double truePositiveRate(InputIt1 xFirst, InputIt1 xLast, InputIt2 tFirst, InputIt2 tLast);

/**
 *  @brief      True negatives.
 *  @details    This function calculates the number actual negatives which are correctly identified as such.
 *              The container x indicates the test results that will be evaluated, while the container 
 *              t indicates the set true positives and negatives.
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of test results.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of positives and negatives.
 *  @param[in]  xFirst  Iterator defining the initial position of a container.
 *  @param[in]  xLast  Iterator defining the final position of a container.
 *  @param[in]  yFirst  Iterator defining the initial position of a container.
 *  @param[in]  yLast  Iterator defining the final position of a container.
 *  @returns    The number of true negatives in container x.
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
size_t trueNegatives(InputIt1 xFirst, InputIt1 xLast, InputIt2 tFirst, InputIt2 tLast);

/**
 *  @brief      True negative rate.
 *  @details    This function calculates the proportion of actual negatives which are correctly identified as such.
 *              The container x indicates the test results that will be evaluated, while the container 
 *              t indicates the set true positives and negatives.
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of test results.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of positives and negatives.
 *  @param[in]  xFirst  Iterator defining the initial position of a container.
 *  @param[in]  xLast  Iterator defining the final position of a container.
 *  @param[in]  yFirst  Iterator defining the initial position of a container.
 *  @param[in]  yLast  Iterator defining the final position of a container.
 *  @returns    The true negative rate of the tests in container x.
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double trueNegativeRate(InputIt1 xFirst, InputIt1 xLast, InputIt2 tFirst, InputIt2 tLast);

/**
 *  @brief      False positived.
 *  @details    This function calculates the number of actual positives which are incorrectly identified as such.
 *              The container x indicates the test results that will be evaluated, while the container 
 *              t indicates the set true positives and negatives.
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of test results.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of positives and negatives.
 *  @param[in]  xFirst  Iterator defining the initial position of a container.
 *  @param[in]  xLast  Iterator defining the final position of a container.
 *  @param[in]  yFirst  Iterator defining the initial position of a container.
 *  @param[in]  yLast  Iterator defining the final position of a container.
 *  @returns    The number of false positives in container x.
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
size_t falsePositives(InputIt1 xFirst, InputIt1 xLast, InputIt2 tFirst, InputIt2 tLast);

/**
 *  @brief      False positive rate.
 *  @details    This function calculates the proportion of actual positives which are incorrectly identified as such.
 *              The container x indicates the test results that will be evaluated, while the container 
 *              t indicates the set true positives and negatives.
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of test results.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of positives and negatives.
 *  @param[in]  xFirst  Iterator defining the initial position of a container.
 *  @param[in]  xLast  Iterator defining the final position of a container.
 *  @param[in]  yFirst  Iterator defining the initial position of a container.
 *  @param[in]  yLast  Iterator defining the final position of a container.
 *  @returns    The false positive rate of the tests in container x.
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double falsePositiveRate(InputIt1 xFirst, InputIt1 xLast, InputIt2 tFirst, InputIt2 tLast);

/**
 *  @brief      False negatives.
 *  @details    This function calculates the number of actual negatives which are incorrectly identified as such.
 *              The container x indicates the test results that will be evaluated, while the container 
 *              t indicates the set true positives and negatives.
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of test results.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of positives and negatives.
 *  @param[in]  xFirst  Iterator defining the initial position of a container.
 *  @param[in]  xLast  Iterator defining the final position of a container.
 *  @param[in]  yFirst  Iterator defining the initial position of a container.
 *  @param[in]  yLast  Iterator defining the final position of a container.
 *  @returns    The number of false negatives in container x.
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
size_t falseNegatives(InputIt1 xFirst, InputIt1 xLast, InputIt2 tFirst, InputIt2 tLast);

/**
 *  @brief      False negative rate.
 *  @details    This function calculates the proportion of actual negatives which are incorrectly identified as such.
 *              The container x indicates the test results that will be evaluated, while the container 
 *              t indicates the set true positives and negatives.
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of test results.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of positives and negatives.
 *  @param[in]  xFirst  Iterator defining the initial position of a container.
 *  @param[in]  xLast  Iterator defining the final position of a container.
 *  @param[in]  yFirst  Iterator defining the initial position of a container.
 *  @param[in]  yLast  Iterator defining the final position of a container.
 *  @returns    The false negative rate of the tests in container x.
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double falseNegativeRate(InputIt1 xFirst, InputIt1 xLast, InputIt2 tFirst, InputIt2 tLast);

/**
 *  @brief      Positive predictive value.
 *  @details    This function calculates the rate of true positives among the positive calls.
 *              The container x indicates the test results that will be evaluated, while the container 
 *              t indicates the set true positives and negatives.
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of test results.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of positives and negatives.
 *  @param[in]  xFirst  Iterator defining the initial position of a container.
 *  @param[in]  xLast  Iterator defining the final position of a container.
 *  @param[in]  tFirst  Iterator defining the initial position of a container.
 *  @param[in]  tLast  Iterator defining the final position of a container.
 *  @returns    The positive predictive value.
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double positivePredictiveValue(InputIt1 xFirst, InputIt1 xLast, InputIt2 tFirst, InputIt2 tLast);

/**
 *  @brief      Negative predictive value.
 *  @details    This function calculates the rate of true negatives among the negative calls.
 *              The container x indicates the test results that will be evaluated, while the container 
 *              t indicates the set true positives and negatives.
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of test results.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of positives and negatives.
 *  @param[in]  xFirst  Iterator defining the initial position of a container.
 *  @param[in]  xLast  Iterator defining the final position of a container.
 *  @param[in]  tFirst  Iterator defining the initial position of a container.
 *  @param[in]  tLast  Iterator defining the final position of a container.
 *  @returns    The positive predictive value.
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double negativePredictiveValue(InputIt1 xFirst, InputIt1 xLast, InputIt2 tFirst, InputIt2 tLast);

/**
 *  @brief      False discovery rate.
 *  @details    This function calculates the rate of false positives among the positive calls.
 *              The container x indicates the test results that will be evaluated, while the container 
 *              t indicates the set true positives and negatives.
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of test results.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of positives and negatives.
 *  @param[in]  xFirst  Iterator defining the initial position of a container.
 *  @param[in]  xLast  Iterator defining the final position of a container.
 *  @param[in]  tFirst  Iterator defining the initial position of a container.
 *  @param[in]  tLast  Iterator defining the final position of a container.
 *  @returns    The positive predictive value.
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double falseDiscoveryRate(InputIt1 xFirst, InputIt1 xLast, InputIt2 tFirst, InputIt2 tLast);

/**
 *  @brief      Accuracy.
 *  @details    This function calculates the proportion of actual positives and negatives which are correctly
 *              identified as such. The container x indicates the test results that will be evaluated,
 *              while the container t indicates the set true positives and negatives.
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of test results.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of positives and negatives.
 *  @param[in]  xFirst  Iterator defining the initial position of a container.
 *  @param[in]  xLast  Iterator defining the final position of a container.
 *  @param[in]  tFirst  Iterator defining the initial position of a container.
 *  @param[in]  tLast  Iterator defining the final position of a container.
 *  @returns    The true positive rate of the tests in container x.
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double accuracy(InputIt1 xFirst, InputIt1 xLast, InputIt2 tFirst, InputIt2 tLast);

// Ranks.

/**
 *  @brief      Ranks.
 *  @details    This function computes the ranks of the elements inside a container. No correction
 *              for ties are done by this function.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  xFirst  Iterator defining the initial position of a container with observations.
 *  @param[in]  xLast  Iterator defining the final position of a container with observations.
 *  @param[out] rFirst  Iterator defining the initial position where the result is returned.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void ranks(InputIt xFirst, InputIt xLast, OutIt rFirst);

/**
 *  @brief      Corrected ranks.
 *  @details    This function computes the ranks of the elements inside a container. This function
 *              makes a correction for tied items, by computing the average range of elements with the
 *              same value.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  xFirst  Iterator defining the initial position of a container with observations.
 *  @param[in]  xLast  Iterator defining the final position of a container with observations.
 *  @param[out] rFirst  Iterator defining the initial position where the result is returned.
 *  @returns    The number of groups of tied items that have more than one element.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
size_t correctedRanks(InputIt xFirst, InputIt xLast, OutIt rFirst);

/**
 *  @brief      Count ties.
 *  @details    This function counts the number of elements that have the same value in a sorted
 *              range. For each element in the range, it's value is compared with the rest. If the number
 *              of ocurrencies is greater than one, a new entry in the output iterator is returned. If
 *              all the elements are not equal, the output range is not modified. The function sorts the
 *              given range before making the comparisson.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  xFirst  Iterator defining the initial position of a container with observations.
 *  @param[in]  xLast  Iterator defining the final position of a container with observations.
 *  @param[out] tFirst  Iterator defining the initial position where the result is returned.
 *  @returns    The number of groups of tied items that have more than one element.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
size_t countTies(InputIt xFirst, InputIt xLast, OutIt tFirst);

// Empirical distribution.

/**
 *  @brief      Quantile.
 *  @details    This function calculates the quantile that corresponds to a proability value in a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  p  Cumulative probability value for which the quantile is computed.
 *  @returns    The quantile value.
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double quantile(InputIt first, InputIt last, double p);

/**
 *  @brief      Quantiles.
 *  @details    This function calculates the quantiles that correspond to a array of probabilities 
 *              in a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the observations and probability values.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  pFirst  Iterator defining the initial position of the sequence of probabilities.
 *  @param[in]  pLast  Iterator defining the final position of the sequence of probabilities.
 *  @param[out] qOut  Output iterator to the initial position of a container.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void quantile(InputIt first, InputIt last, InputIt pFirst, InputIt pLast, OutIt qOut);

/**
 *  @brief      Cumulative data.
 *  @details    This function accumulates the values in a container.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[out] out  Output iterator defining the beginning of the destination container.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void cumulativeData(InputIt first, InputIt last, OutIt out);

/**
 *  @brief      Cumulative probability using the empirical distribution.
 *  @details    This function calculates P(X<=x) by using the empirical distribution of a set of
 *              observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  x  Value for which the probability is computed.
 *  @returns    The probability value.
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double empiricalCDF(InputIt first, InputIt last, double x);

/**
 *  @brief      Cumulative probabilities using the empirical distribution.
 *  @details    This function calculates P(X<=x) of each element inside a range by using the empirical 
 *              distribution of that range of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the initial position of a container with the observations.
 *  @param[in]  last  Iterator defining the final position of a container with the observations.
 *  @param[out] pOut  Output iterator to the initial position of a container.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void empiricalCDF(InputIt first, InputIt last, OutIt pOut);

/**
 *  @brief      Cumulative probabilities using the empirical distribution.
 *  @details    This function calculates P(X<=x) for each element of one sequence 
 *              by using the empirical distribution of another set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequences of observations.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  testFirst  Iterator defining the initial position of a container with the points for
 *              which the CDF is calculated.
 *  @param[in]  testLast  Iterator defining the final position of a container with the points for which
 *              the CDF is calculated.
 *  @param[out] pOut  Output iterator to the initial position of a container.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void empiricalCDF(InputIt first, InputIt last, InputIt testFirst, InputIt testLast, OutIt pOut);

/**
 *  @brief      Cumulative probability using the empirical distribution and mid-values.
 *  @details    This function calculates P(X<=x) by using the empirical distribution of a set of
 *              observations. The value of P(X=x) is replaced by P(X=x)/2.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  x  Value for which the probability is computed.
 *  @returns    The probability value.
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double empiricalMidCDF(InputIt first, InputIt last, double x);

/**
 *  @brief      Cumulative probabilities using the empirical distribution and mid-values.
 *  @details    This function calculates P(X<=x) of each element inside a range by using the empirical 
 *              distribution of that range of observations. Values of P(X=x) is replaced by P(X=x)/2.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the initial position of a container with the observations.
 *  @param[in]  last  Iterator defining the final position of a container with the observations.
 *  @param[out] pOut  Output iterator to the initial position of a container.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void empiricalMidCDF(InputIt first, InputIt last, OutIt pOut);

/**
 *  @brief      Cumulative probabilities using the empirical distribution and the mid-value.
 *  @details    This function calculates P(X<=x) for each element of one sequence 
 *              by using the empirical distribution of another set of observations.
 *              The value of P(X=x) is replaced by P(X=x)/2.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequences of observations.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  testFirst  Iterator defining the initial position of a container with the points for
 *              which the CDF is calculated.
 *  @param[in]  testLast  Iterator defining the final position of a container with the points for which
 *              the CDF is calculated.
 *  @param[out] pOut  Output iterator to the initial position of a container.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void empiricalMidCDF(InputIt first, InputIt last, InputIt testFirst, InputIt testLast, OutIt pOut);

/**
 *  @brief      Complement of the cumulative probability using the empirical distribution.
 *  @details    This function calculates P(X>=x) by using the empirical distribution of a set of
 *              observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  x  Value for which the probability is computed.
 *  @returns    The probability value.
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double empiricalCompCDF(InputIt first, InputIt last, double x);

/**
 *  @brief      Complement of the cumulative probabilities using the empirical distribution.
 *  @details    This function calculates P(X>=x) of each element inside a range by using the empirical
 *              distribution of that range of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the initial position of a container with the observations.
 *  @param[in]  last  Iterator defining the final position of a container with the observations.
 *  @param[out] pOut  Output iterator to the initial position of a container.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void empiricalCompCDF(InputIt first, InputIt last, OutIt pOut);

/**
 *  @brief      Complement of cumulative probabilities using the empirical distribution.
 *  @details    This function calculates P(X>=x) for each element of one sequence 
 *              by using the empirical distribution of another set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequences of observations.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  testFirst  Iterator defining the initial position of a container with the points for
 *              which the CDF is calculated.
 *  @param[in]  testLast  Iterator defining the final position of a container with the points for which
 *              the CDF is calculated.
 *  @param[out] pOut  Output iterator to the initial position of a container.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void empiricalCompCDF(InputIt first, InputIt last, InputIt testFirst, InputIt testLast, OutIt pOut);

/**
 *  @brief      Complement of cumulative probability using the empirical distribution and mid-values.
 *  @details    This function calculates P(X>=x) by using the empirical distribution of a set of
 *              observations. The value of P(X=x) is replaced by P(X=x)/2.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  x  Value for which the probability is computed.
 *  @returns    The probability value.
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double empiricalCompMidCDF(InputIt first, InputIt last, double x);

/**
 *  @brief      Complement of cumulative probabilities using the empirical distribution and mid-values.
 *  @details    This function calculates P(X>=x) of each element inside a range by using the empirical
 *              distribution of that range of observations. Values of P(X=x) is replaced by P(X=x)/2.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequences of observations.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the initial position of a container with the observations.
 *  @param[in]  last  Iterator defining the final position of a container with the observations.
 *  @param[out] pOut  Output iterator to the initial position of a container.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void empiricalCompMidCDF(InputIt first, InputIt last, OutIt pOut);

/**
 *  @brief      Complement of cumulative probabilities using the empirical distribution and the
 *              mid-value.
 *  @details    This function calculates P(X>=x) for each element of one sequence 
 *              by using the empirical distribution of another set of observations.
 *              The value of P(X=x) is replaced by P(X=x)/2.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequences of observations.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  testFirst  Iterator defining the initial position of a container with the points for
 *              which the CDF is calculated.
 *  @param[in]  testLast  Iterator defining the final position of a container with the points for which
 *              the CDF is calculated.
 *  @param[out] pOut  Output iterator to the initial position of a container.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void empiricalCompMidCDF(InputIt first, InputIt last, InputIt testFirst, InputIt testLast, OutIt pOut);

/**
 *  @brief      Cumulative probability to p-value.
 *  @details    This function tranform the cumulative probability values (P(X<=x)) to p-values.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  pFirst  Iterator defining the beginning of the source container.
 *  @param[in]  pLast Iterator defining the end of the source container.
 *  @param[out] pOut  Output iterator to the initial position of a container.
 *  @param[in]  pvalType  Type of p-value to calculate.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void cdfToPval(InputIt first, InputIt last, OutIt pOut, ResultType pvalType);

/**
 *  @brief      Cumulative probability using the empirical distribution.
 *  @details    This function calculates P(X<=x) by using the empirical distribution of a set of
 *              observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  pFirst  Iterator defining the beginning of the source container.
 *  @param[in]  pLast Iterator defining the end of the source container.
 *  @param[out] pOut  Output iterator to the initial position of a container.
 *  @param[in]  pvalType  Type of p-value to calculate.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void pvalToCDF(InputIt pFirst, InputIt pLast, OutIt pOut, ResultType pvalType);

/**
 *  @brief      Histogram.
 *  @details    This function gets the histogram of a set of observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     OutIt  The iterator type to be used to store the results.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[out] hOut  Outout iterator to the initial position of a container where the histogram is 
 *              stored.
 *  @param[out] bins  Outout iterator to the initial position of a container where the histogram are 
 *              stored.
 *  @param[in]  nBins  Number of bins in the histogram.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void histogram(InputIt first, InputIt last, OutIt hOut, OutIt bins, size_t nBins);

/**
 *  @brief      Histogram.
 *  @details    This function gets the histogram of a set of observations. Thi histogram is
 *              limited by the minimin and maximum values specified in the parameters.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[out] hOut  Output iterator to the initial position of a container where the histogram will be
 *              stored.
 *  @param[out] bins  Output iterator to the initial position of a container where the bins will be
 *              stored.
 *  @param[in]  nBins  Number of bins in the histogram.
 *  @param[in]  xMin  Lower limit of the first bin in the histogram.
 *  @param[in]  xMax  Upper limit of the last bin in the histogram.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void histogram(InputIt first, InputIt last, OutIt hOut, OutIt bins, size_t nBins, double xMin, double xMax);

////////// Circular data //////////

// Descriptive statistics.

/**
 *  @brief      P-axial data correction.
 *  @details    This function transforms p-axial data to a common scale.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[out] out  Output iterator defining the beginning of the destination container.
 *  @param[in]  p  Number of modes of the data. 
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void pAxial(InputIt first, InputIt last, OutIt out, unsigned int p);

/**
 *  @brief      Mean direction.
 *  @details    This function calculates the mean direction a set of circular observations. The data must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the mean direction in radians. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double meanDirection(InputIt first, InputIt last);

/**
 *  @brief      Weighted mean direction.
 *  @details    This function calculates the weighted mean direction of a set of observations. 
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The value of the mean direction in radians. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double meanDirection(InputIt1 first, InputIt1 last, InputIt2 wFirst);

/**
 *  @brief      Median direction.
 *  @details    This function calculates the median direction a set of circular observations. The data must be in
 *              radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the median direction in radians. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double medianDirection(InputIt first, InputIt last);

/**
 *  @brief      Resultant length.
 *  @details    This function calculates the resultant length a set of circular observations. The data must be in
 *              radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the resultant length. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double resultantLength(InputIt first, InputIt last);

/**
 *  @brief      Mean resultant length.
 *  @details    This function calculates the mean resultant length a set of circular observations. The data must be 
 *              in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the mean resultant length. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double meanResultantLength(InputIt first, InputIt last);

/**
 *  @brief      Weighted mean resultant length.
 *  @details    This function calculates the weighted mean resultant length of a set of observations. 
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The value of the mean resultant length. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double meanResultantLength(InputIt1 first, InputIt1 last, InputIt2 wFirst);

/**
 *  @brief      Circular variance.
 *  @details    This function calculates the variance of a set of circular observations. The data must be 
 *              in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the circular variance. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double sampleCircularVariance(InputIt first, InputIt last);

/**
 *  @brief      Weighted circular variance.
 *  @details    This function calculates the weighted circular variance of a set of observations. 
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The value of the circular variance. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double sampleCircularVariance(InputIt1 first, InputIt1 last, InputIt2 wFirst);

/**
 *  @brief      Angular variance.
 *  @details    This function calculates the angular variance of a set of observations. The data must be 
 *              in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the angular variance. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double sampleAngularVariance(InputIt first, InputIt last);

/**
 *  @brief      Weighted angular variance.
 *  @details    This function calculates the weighted angular variance of a set of observations. 
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The value of the angular variance. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double sampleAngularVariance(InputIt1 first, InputIt1 last, InputIt2 wFirst);

/**
 *  @brief      Circular standard deviation.
 *  @details    This function calculates the standard deviation of a set of circular observations. The data
 *              must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the circular standard deviation. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double sampleCircularStandardDeviation(InputIt first, InputIt last);

/**
 *  @brief      Weighted circular standard deviation.
 *  @details    This function calculates the weighted circular standard deviation of a set of observations. 
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The value of the circular standard deviation. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double sampleCircularStandardDeviation(InputIt1 first, InputIt1 last, InputIt2 wFirst);

/**
 *  @brief      Angular standard deviation.
 *  @details    This function calculates the angular standard deviation of a set of observations. The data
 *              must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the circular standard deviation. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double sampleAngularStandardDeviation(InputIt first, InputIt last);

/**
 *  @brief      Weighted angular standard deviation.
 *  @details    This function calculates the weighted angular standard deviation of a set of observations. 
 *  @tparam     InputIt1  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     InputIt2  The iterator type to be used to traverse the sequence of weights.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  wFirst  Iterator defining the initial position of a container with the weights.
 *  @returns    The value of the angular standard deviation. 
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type>&& nct::Arithmetic<typename InputIt2::value_type>
double sampleAngularStandardDeviation(InputIt1 first, InputIt1 last, InputIt2 wFirst);

/**
 *  @brief      Circular dispersion.
 *  @details    This function calculates the dispersion of a set of circular observations. The data
 *              must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the circular dispersion. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double sampleCircularDispersion(InputIt first, InputIt last);

/**
 *  @brief      Circular kappa.
 *  @details    This function calculates the dispersion parameter of the Von Mises distribution of a set of circular 
 *              observations. The data must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the dispersion parameter. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double sampleCircularKappa(InputIt first, InputIt last);

/**
 *  @brief      Circular skewness.
 *  @details    This function calculates the skewness of a set of circular observations. The data
 *              must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the circular skewness. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double sampleCircularSkewness(InputIt first, InputIt last);

/**
 *  @brief      Circular skewness (Pewsey version).
 *  @details    This function calculates the skewness of a set of circular observations (Pewsey version). The data
 *              must be in radians. 
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the circular skewness. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double sampleCircularSkewnessP(InputIt first, InputIt last);

/**
 *  @brief      Circular kurtosis.
 *  @details    This function calculates the kurtosis of a set of circular observations. The data
 *              must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the circular skewness. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double sampleCircularKurtosis(InputIt first, InputIt last);

/**
 *  @brief      Circular kurtosis (Pewsey version).
 *  @details    This function calculates the kurtosis of a set of circular observations. The data
 *              must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the circular skewness. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double sampleCircularKurtosisP(InputIt first, InputIt last);

/**
 *  @brief      First trigonometric moment.
 *  @details    This function calculates the first trigonometric moment of a set of circular observations. The data
 *              must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the moment. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
Complex firstTrigonometricMoment(InputIt first, InputIt last);

/**
 *  @brief      First trigonometric centered moment.
 *  @details    This function calculates the first trigonometric centered moment of a set of circular observations. 
 *              The data must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the moment. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
Complex firstCentralTrigonometricMoment(InputIt first, InputIt last);

/**
 *  @brief      Second trigonometric moment.
 *  @details    This function calculates the second trigonometric moment of a set of circular observations. The data
 *              must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the moment. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
Complex secondTrigonometricMoment(InputIt first, InputIt last);

/**
 *  @brief      Second trigonometric centered moment.
 *  @details    This function calculates the second trigonometric centered moment of a set of circular observations. 
 *              The data must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the moment. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
Complex secondCentralTrigonometricMoment(InputIt first, InputIt last);

/**
 *  @brief      Third trigonometric moment.
 *  @details    This function calculates the third trigonometric moment of a set of circular observations. The data
 *              must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the moment. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
Complex thirdTrigonometricMoment(InputIt first, InputIt last);

/**
 *  @brief      Third trigonometric centered moment.
 *  @details    This function calculates the third trigonometric centered moment of a set of circular observations. 
 *              The data must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the moment. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
Complex thirdCentralTrigonometricMoment(InputIt first, InputIt last);

/**
 *  @brief      Fourth trigonometric moment.
 *  @details    This function calculates the fourth trigonometric moment of a set of circular observations. The data
 *              must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the moment. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
Complex fourthTrigonometricMoment(InputIt first, InputIt last);

/**
 *  @brief      Fourth trigonometric centered moment.
 *  @details    This function calculates the fourth trigonometric centered moment of a set of circular observations. 
 *              The data must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @returns    The value of the moment. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
Complex fourthCentralTrigonometricMoment(InputIt first, InputIt last);

/**
 *  @brief      K trigonometric moment.
 *  @details    This function calculates the K-trigonometric moment of a set of circular observations.
 *              The data must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  k  Moment to calculate.
 *  @returns    The value of the moment. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
Complex kTrigonometricMoment(InputIt first, InputIt last, unsigned int k);

/**
 *  @brief      K trigonometric centered moment.
 *  @details    This function calculates the K-trigonometric centered moment of a set of circular observations.
 *              The data must be in radians.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[in]  k  Moment to calculate.
 *  @returns    The value of the moment. 
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
Complex kCentralTrigonometricMoment(InputIt first, InputIt last, unsigned int k);

/**
 *  @brief      Circular-linear association.
 *  @details    Correlation coefficient between one circular variable x and one linear 
 *              variable y.
 *  @tparam     InputIt1  The iterator type to be used to traverse the observations of group 1.
 *  @tparam     InputIt2  The iterator type to be used to traverse the observations of group 2.
 *  @param[in]  xFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  xLast  Iiterator to the final position of one of the sequences.
 *  @param[in]  yFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  yLast  Iiterator to the final position of one of the sequences.
 *  @returns    The circular-linear association of x and y.   
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double CircularLinearAssociation(InputIt1 xFirst, InputIt1 xLast, InputIt2 yFirst, InputIt2 yLast);

/**
 *  @brief      Circular-circular association.
 *  @details    Correlation coefficient between two circular random variables.
 *  @tparam     InputIt1  The iterator type to be used to traverse the observations of group 1.
 *  @tparam     InputIt2  The iterator type to be used to traverse the observations of group 2.
 *  @param[in]  xFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  xLast  Iiterator to the final position of one of the sequences.
 *  @param[in]  yFirst  Iiterator to the initial position of one of the sequences.
 *  @param[in]  yLast  Iiterator to the final position of one of the sequences.
 *  @returns    The circular-circular association of x and y.   
 */
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double CircularCircularAssociation(InputIt1 xFirst, InputIt1 xLast, InputIt2 yFirst, InputIt2 yLast);

/**
 *  @brief      Circular Ranks.
 *  @details    This function returns the circular ranks of the elements in one array. No
 *              correction for ties are performed in this function.
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     OutIt  The iterator type to be used to store the result.
 *  @param[in]  xFirst  Iterator defining the initial position of a container with observations.
 *  @param[in]  xLast  Iterator defining the final position of a container with observations.
 *  @param[out] rFirst  Iterator defining the initial position where the result is returned.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void circularRanks(InputIt xFirst, InputIt xLast, OutIt rFirst);

// Histograms.

/**
 *  @brief      Circular histogram.
 *  @details    This function gets the circular histogram of a set of observations. The
 *              observations must be in radians. 
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     OutIt  The iterator type to be used to store the results.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[out] hOut  Output iterator to the initial position of a container.
 *  @param[out] bins  Output iterator to the initial position of a container.
 *  @param[in]  nBins  Number of bins in the histogram.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void circularHistogram(InputIt first, InputIt last, OutIt hOut, OutIt bins, size_t nBins);

/**
 *  @brief      Circular histogram.
 *  @details    This function gets the circular histogram of a set of observations. The observations must
 *              ne in radians. 
 *  @tparam     InputIt  The iterator type to be used to traverse the sequence of observations.
 *  @tparam     OutIt  The iterator type to be used to store the results.
 *  @param[in]  first  Iterator defining the beginning of the source container.
 *  @param[in]  last Iterator defining the end of the source container.
 *  @param[out] hOut  Output iterator to the initial position of a container.
 *  @param[out] bins  Output iterator to the initial position of a container.
 *  @param[in]  nBins  Number of bins in the histogram.
 *  @param[in]  hIni  Beginnig of the first bin in the histogram.
 */
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void circularHistogram(InputIt first, InputIt last, OutIt hOut, OutIt bins, size_t nBins, double hIni);

}}

////////// Implementation of function templates //////////
#include <nct/statistics/statistics_template.h> 

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
