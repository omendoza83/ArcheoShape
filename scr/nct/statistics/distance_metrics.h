//=================================================================================================================
/**
 *  @file       distance_metrics.h
 *  @brief      nct::statistics::distance_metrics namespace.
 *  @details    Declaration of the nct::statistics::distance_metrics namespace.
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

#ifndef NCT_DISTANCE_METRICS_H_INCLUDE
#define NCT_DISTANCE_METRICS_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/Array.h>
#include <nct/Array2D.h>
#include <nct/Array3D.h>
#include <nct/math/linear_algebra.h>
#include <nct/statistics/statistics.h>

//=================================================================================================================
namespace nct {
namespace statistics {
/**
 *  @brief      Distance metrics namespace.
 *  @details    This namespace contains functions for calculating distance metrics.
 */
namespace distance_metrics {

/**
 *  @brief      Distance functions.
 *  @details    Enumeration of supported distance functions.
 */
enum class DistanceFunction : unsigned char {

    SquaredEuclideanDistance,       /**< Squared euclidian distance. */

    EuclideanDistance,              /**< Euclidian distance. */

    MinkowskiDistance,              /**< Minkowski distance. */

    CityBlockDistance,              /**< Sum of absolute differences. */

    ChebychevDistance,              /**< Coordinade with maximun absolute difference. */

    MinDistance,                    /**< Coordinade with minimum absolute difference. */

    BhattacharyyaDistance,          /**< Bhattacharray distance (suitable only for
                                         probability distributions). */
    CosineDistance,                 /**< One minus the cosine of the included angle
                                         between points (treated as vectors). */
    CorrelationDistance,            /**< One minus the sample correlation between points
                                         (treated as sequences of values). */
    SpearmanDistance,               /**< One minus the spearman correlation between points
                                         (treated as sequences of values). */
    JaccardDistance,                /**< Percentage of non-zero coordinades that differ
                                         (suitable only for discrete data). */
    HammingDistance,                /**< Percentage of coordinades that differ
                                         (suitable only for discrete data). */
    StadarizedEuclideanDistance,    /**< Standarized euclidian distance. */

    MahalanobisDistance,            /**< Mahalanobis distance. */

    NoDistance,                     /**< No distance. */

};

// Generic functions.

/**
 *  @brief      Distance between x and y.
 *  @details    This function calculates the distance of two d-by-1 observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  xFirst  Iterator defining the beginning of the source container.
 *  @param[in]  xLast Iterator defining the end of the source container.
 *  @param[in]  yFirst  Iterator defining the beginning of the source container.
 *  @param[in]  yLast Iterator defining the end of the source container.
 *  @param[in]  distanceFunction  Distance metric to use in this function.
 *  @param[in]  param  Parameter of the distance metric (only if it's required).
 *              If distanceFunction = MinkowskiDistance, this parameter corresponds to the
 *              degree of the distance (p).
 *              The rest of the distance functions don't requiere this parameter.
 *  @returns    The distance value.   
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double distance(InputIt xFirst, InputIt xLast, InputIt yFirst, InputIt yLast, 
    DistanceFunction distanceFunction, double param = 0);

/**
 *  @brief      Distance between x and y.
 *  @details    This function calculates the distance between one observation and a set of 
 *              observations.
 *  @tparam     T  The data type of the input arrays.
 *  @param[in]  xt  d-by-1 (or 1-by-d) array with one observation. This is the observation
 *              for which the distances are calculated. 
 *  @param[in]  x  n-by-d array of observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d).
 *  @param[in]  distanceFunction  Distance metric to use in this function.
 *  @param[in]  param  Parameter of the distance metric (only if it's required).
 *              If distanceFunction = MinkowskiDistance, this parameter corresponds to the
 *              degree of the distance (p).
 *              The rest of the distance functions don't requiere this parameter.
 *  @returns    The array with the result of the operation.
 */        
template<nct::Arithmetic T>
RealVector distance(const Array<T>& xt, const Array2D<T>& x, DistanceFunction distanceFunction,
    double param = 0);

/**
 *  @brief      Pairwise distance.
 *  @details    This function calculates the distance between pairs of observations. 
 *  @param[in]  x  n-by-d array with the observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @tparam     T  The data type of the input array.
 *  @param[in]  distanceFunction  Distance metric to use in this function.
 *  @param[in]  param  Parameter of the distance metric (only if it's required).
 *              If distanceFunction = MinkowskiDistance, this parameter corresponds to the
 *              degree of the distance (p).
 *              The rest of the distance functions don't requiere this parameter.
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix pairwiseDistance(const Array2D<T>& x, DistanceFunction distanceFunction, double param = 0);

// Distance transforms for 2D arrays.

/**
 *  @brief      Distance transform.
 *  @details    This function calculates the distance transform of a 2-D binary array.
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  Input array to be transformed. 
 *  @param[in]  distanceFunction  Distance metric to use in this function.
 *  @param[in]  param  Parameter of the distance metric (only if it's required).
 *              If distanceFunction = MinkowskiDistance, this parameter corresponds to the
 *              degree of the distance (p).
 *              The rest of the distance functions don't requiere this parameter.
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix distanceTransform(const Array2D<T>& x, DistanceFunction distanceFunction, double param = 0);

/**
 *  @brief      Sample distance transform.
 *  @details    This function calculates the distance transform of a sampled 2-D function.
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  Input array to be transformed (sampled function). 
 *  @param[in]  distanceFunction  Distance metric to use in this function.
 *  @param[in]  param  Parameter of the distance metric (only if it's required).
 *              If distanceFunction = MinkowskiDistance, this parameter corresponds to the
 *              degree of the distance (p).
 *              The rest of the distance functions don't requiere this parameter.
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix sampledFunctionDT(const Array2D<T>& x, DistanceFunction distanceFunction, double param = 0);

/**
 *  @brief      Fast squared euclidean distance transform.
 *  @details    This function calculates the fast squared euclidean distance transform of a 2-D array.
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  Array to be transformed. 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix fastSquaredEuclideanDT(const Array2D<T>& x);

/**
 *  @brief      Fast squared euclidean distance transform of a sampled function.
 *  @details    This function calculates the fast squared euclidean distance transform of a sampled 2-D 
 *              function.
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  Input array to be transformed (sampled function). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix fastSquaredEuclideanSFDT(const Array2D<T>& x);

/**
 *  @brief      Fast city block distance transform.
 *  @details    This function calculates the fast city block distance transform of a 2-D array.
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  Array to be transformed. 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix fastCityBlockDT(const Array2D<T>& x);

/**
 *  @brief      Fast city block distance transform of a sampled function.
 *  @details    This function calculates the fast scity block distance transform of a sampled 2-D 
 *              function.
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  Input array to be transformed (sampled function). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix fastCityBlockSFDT(const Array2D<T>& x);

// Distance transforms for 3D arrays.

/**
 *  @brief      Distance transform.
 *  @details    This function calculates the distance transform of a 3-D binary array.
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  Input array to be transformed. 
 *  @param[in]  distanceFunction  Distance metric to use in this function.
 *  @param[in]  param  Parameter of the distance metric (only if it's required).
 *              If distanceFunction = MinkowskiDistance, this parameter corresponds to the
 *              degree of the distance (p).
 *              The rest of the distance functions don't requiere this parameter.
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Array3D<double> distanceTransform(const Array3D<T>& x, DistanceFunction distanceFunction, double param = 0);

/**
 *  @brief      Sample distance transform.
 *  @details    This function calculates the distance transform of a sampled 3-D function.
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  Input array to be transformed (sampled function). 
 *  @param[in]  distanceFunction  Distance metric to use in this function.
 *  @param[in]  param  Parameter of the distance metric (only if it's required).
 *              If distanceFunction = MinkowskiDistance, this parameter corresponds to the
 *              degree of the distance (p).
 *              The rest of the distance functions don't requiere this parameter.
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Array3D<double> sampledFunctionDT(const Array3D<T>& x, DistanceFunction distanceFunction, double param = 0);

/**
 *  @brief      Fast squared euclidean distance transform.
 *  @details    This function calculates the fast squared euclidean distance transform of a 3-D array.
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  Array to be transformed. 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Array3D<double> fastSquaredEuclideanDT(const Array3D<T>& x);

/**
 *  @brief      Fast squared euclidean distance transform of a sampled function.
 *  @details    This function calculates the fast squared euclidean distance transform of a sampled 3-D 
 *              function.
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  Input array to be transformed (sampled function). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Array3D<double> fastSquaredEuclideanSFDT(const Array3D<T>& x);

/**
 *  @brief      Fast city block distance transform.
 *  @details    This function calculates the fast city block distance transform of a 3-D array.
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  Array to be transformed. 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Array3D<double> fastCityBlockDT(const Array3D<T>& x);

/**
 *  @brief      Fast city block distance transform of a sampled function.
 *  @details    This function calculates the fast scity block distance transform of a sampled 3-D 
 *              function.
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  Input array to be transformed (sampled function). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Array3D<double> fastCityBlockSFDT(const Array3D<T>& x);

// Distance functions.

//______

/**
 *  @brief      Squared euclidean distance (sum( (xi-yi)^2 )).
 *  @details    This function calculates the squared euclidean distance of two d-by-1 observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  xFirst  Iterator defining the beginning of the source container.
 *  @param[in]  xLast Iterator defining the end of the source container.
 *  @param[in]  yFirst  Iterator defining the beginning of the source container.
 *  @param[in]  yLast Iterator defining the end of the source container.
 *  @returns    The distance value.   
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double squaredEuclideanDistance(InputIt xFirst, InputIt xLast, InputIt yFirst, InputIt yLast);

/**
 *  @brief      Squared euclidean distance sum( (xi-yi)^2 ).
 *  @details    This function calculates the squared euclidean distance between one observation 
 *              and a set of observations.
 *  @tparam     T  The data type of the input arrays.
 *  @param[in]  xt  d-by-1 (or 1-by-d) array with one observation. This is the observation
 *              for which the distances are calculated. 
 *  @param[in]  x  n-by-d array of observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d).
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
RealVector squaredEuclideanDistance(const Array<T>& xt, const Array2D<T>& x);

/**
 *  @brief      Pairwise squared euclidean distance std::sqrt(sum( (xi-yi)^2 )).
 *  @details    This function calculates the squared euclidean distance between pairs of observations. 
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  n-by-d array with the observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix pairwiseSquaredEuclideanDistance(const Array2D<T>& x);

//______

/**
 *  @brief      Euclidean distance std::sqrt(sum( (xi-yi)^2 )).
 *  @details    This function calculates the euclidean distance of two d-by-1 observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  xFirst  Iterator defining the beginning of the source container.
 *  @param[in]  xLast Iterator defining the end of the source container.
 *  @param[in]  yFirst  Iterator defining the beginning of the source container.
 *  @param[in]  yLast Iterator defining the end of the source container.
 *  @returns    The distance value.   
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double euclideanDistance(InputIt xFirst, InputIt xLast, InputIt yFirst, InputIt yLast);

/**
 *  @brief      Euclidean distance std::sqrt(sum( (xi-yi)^2 )).
 *  @details    This function calculates the euclidean distance between one observation and a set of 
 *              observations.
 *  @tparam     T  The data type of the input arrays.
 *  @param[in]  xt  d-by-1 (or 1-by-d) array with one observation. This is the observation
 *              for which the distances are calculated. 
 *  @param[in]  x  n-by-d array of observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d).
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
RealVector euclideanDistance(const Array<T>& xt, const Array2D<T>& x);

/**
 *  @brief      Pairwise euclidean distance std::sqrt(sum( (xi-yi)^2 )).
 *  @details    This function calculates the euclidean distance between pairs of observations. 
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  n-by-d array with the observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix pairwiseEuclideanDistance(const Array2D<T>& x);

//______

/**
 *  @brief      Minkowski distance ( (sum(|xi-yi|^p))^(1/p) ).
 *  @details    This function calculates the Minkowski distance of two d-by-1 observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  xFirst  Iterator defining the beginning of the source container.
 *  @param[in]  xLast Iterator defining the end of the source container.
 *  @param[in]  yFirst  Iterator defining the beginning of the source container.
 *  @param[in]  yLast Iterator defining the end of the source container.
 *  @param[in]  p  Power to use.
 *  @returns    The distance value.   
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double minkowskiDistance(InputIt xFirst, InputIt xLast, InputIt yFirst, InputIt yLast, double p);

/**
 *  @brief      Minkowski distance ( (sum(|xi-yi|^p))^(1/p) ).
 *  @details    This function calculates the Minkowski distance between one observation and a set o 
 *              observations.
 *  @tparam     T  The data type of the input arrays.
 *  @param[in]  xt  d-by-1 (or 1-by-d) array with one observation. This is the observation
 *              for which the distances are calculated. 
 *  @param[in]  x  n-by-d array of observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d).
 *  @param[in]  p  Power to use.
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
RealVector minkowskiDistance(const Array<T>& xt, const Array2D<T>& x, double p);

/**
 *  @brief      Minkowski euclidean distance ( (sum(|xi-yi|^p))^(1/p) ).
 *  @details    This function calculates the Minkowski distance between pairs of observations. 
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  n-by-d array with the observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @param[in]  p  Power to use.
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix pairwiseMinkowskiDistance(const Array2D<T>& x, double p);

//______

/**
 *  @brief      City-block distance (sum( |xi-yi| )).
 *  @details    This function calculates the city-block distance of two d-by-1 observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  xFirst  Iterator defining the beginning of the source container.
 *  @param[in]  xLast Iterator defining the end of the source container.
 *  @param[in]  yFirst  Iterator defining the beginning of the source container.
 *  @param[in]  yLast Iterator defining the end of the source container.
 *  @returns    The distance value.   
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double cityBlockDistance(InputIt xFirst, InputIt xLast, InputIt yFirst, InputIt yLast);

/**
 *  @brief      City-block distance (sum( |xi-yi| )).
 *  @details    This function calculates the City-block distance between one observation and a set o 
 *              observations.
 *  @tparam     T  The data type of the input arrays.
 *  @param[in]  xt  d-by-1 (or 1-by-d) array with one observation. This is the observation
 *              for which the distances are calculated. 
 *  @param[in]  x  n-by-d array of observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
RealVector cityBlockDistance(const Array<T>& xt, const Array2D<T>& x);

/**
 *  @brief      Pairwise city-block distance (sum( |xi-yi| )).
 *  @details    This function calculates the city-block distance between pairs of observations. 
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  n-by-d array with the observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix pairwiseCityBlockDistance(const Array2D<T>& x);

//______

/**
 *  @brief      Chebychev distance (max(|xi-yi|)).
 *  @details    This function calculates the Chebychev distance of two d-by-1 observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  xFirst  Iterator defining the beginning of the source container.
 *  @param[in]  xLast Iterator defining the end of the source container.
 *  @param[in]  yFirst  Iterator defining the beginning of the source container.
 *  @param[in]  yLast Iterator defining the end of the source container.
 *  @returns    The distance value.   
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double chebychevDistance(InputIt xFirst, InputIt xLast, InputIt yFirst, InputIt yLast);

/**
 *  @brief      Chebychev distance  (max(|xi-yi|)).
 *  @details    This function calculates the Chebychev distance between one observation and a set o 
 *              observations.
 *  @tparam     T  The data type of the input arrays.
 *  @param[in]  xt  d-by-1 (or 1-by-d) array with one observation. This is the observation
 *              for which the distances are calculated. 
 *  @param[in]  x  n-by-d array of observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.   
 */
template<nct::Arithmetic T>
RealVector chebychevDistance(const Array<T>& xt, const Array2D<T>& x);

/**
 *  @brief      Pairwise Chebychev distance (max(|xi-yi|)).
 *  @details    This function calculates the Chebychev distance between pairs of observations. 
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  n-by-d array with the observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix pairwiseChebychevDistance(const Array2D<T>& x);

//______

/**
 *  @brief      Min distance (min(|xi-yi|)).
 *  @details    This function calculates the Min distance of two d-by-1 observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  xFirst  Iterator defining the beginning of the source container.
 *  @param[in]  xLast Iterator defining the end of the source container.
 *  @param[in]  yFirst  Iterator defining the beginning of the source container.
 *  @param[in]  yLast Iterator defining the end of the source container.
 *  @returns    The distance value.   
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double minDistance(InputIt xFirst, InputIt xLast, InputIt yFirst, InputIt yLast);

/**
 *  @brief      Min distance  (min(|xi-yi|)).
 *  @details    This function calculates the Min distance between one observation and a set o 
 *              observations.
 *  @tparam     T  The data type of the input arrays.
 *  @param[in]  xt  d-by-1 (or 1-by-d) array with one observation. This is the observation
 *              for which the distances are calculated. 
 *  @param[in]  x  n-by-d array of observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.   
 */
template<nct::Arithmetic T>
RealVector minDistance(const Array<T>& xt, const Array2D<T>& x);

/**
 *  @brief      Pairwise Min distance (min(|xi-yi|)).
 *  @details    This function calculates the Min distance between pairs of observations. 
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  n-by-d array with the observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix pairwiseMinDistance(const Array2D<T>& x);

//______

/**
 *  @brief      Bhattacharray distance -log( sum( std::sqrt(f1i*f2i) ) ).
 *  @details    This function calculates the Bhattacharray distance between two probability density functions.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  f1First  Iterator defining the beginning of the source container.
 *  @param[in]  f1Last Iterator defining the end of the source container.
 *  @param[in]  f2First  Iterator defining the beginning of the source container.
 *  @param[in]  f2Last Iterator defining the end of the source container.
 *  @returns    The distance between the two density functions.
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double bhattacharrayDistance(InputIt f1First, InputIt f1Last, InputIt f2First, InputIt f2Last);

//______

/**
 *  @brief      Cosine distance ( 1 - std::cos(ang(x,y)) ).
 *  @details    This function calculates the cosine distance of two d-by-1 observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  xFirst  Iterator defining the beginning of the source container.
 *  @param[in]  xLast Iterator defining the end of the source container.
 *  @param[in]  yFirst  Iterator defining the beginning of the source container.
 *  @param[in]  yLast Iterator defining the end of the source container.
 *  @returns    The distance value.   
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double cosineDistance(InputIt xFirst, InputIt xLast, InputIt yFirst, InputIt yLast);

/**
 *  @brief      Cosine distance ( 1 - std::cos(ang(x,y)) ).
 *  @details    This function calculates the cosine distance between one observation and a set o 
 *              observations.
 *  @tparam     T  The data type of the input arrays.
 *  @param[in]  xt  d-by-1 (or 1-by-d) array with one observation. This is the observation
 *              for which the distances are calculated. 
 *  @param[in]  x  n-by-d array of observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.   
 */
template<nct::Arithmetic T>
RealVector cosineDistance(const Array<T>& xt, const Array2D<T>& x);

/**
 *  @brief      Pairwise cosine distance ( 1 - std::cos(ang(x,y)) ).
 *  @details    This function calculates the cosine distance between pairs of observations. 
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  n-by-d array with the observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix pairwiseCosineDistance(const Array2D<T>& x);

//______

/**
 *  @brief      Correlation distance ( 1 - corr(x,y) ).
 *  @details    This function calculates the correlation distance of two d-by-1 observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  xFirst  Iterator defining the beginning of the source container.
 *  @param[in]  xLast Iterator defining the end of the source container.
 *  @param[in]  yFirst  Iterator defining the beginning of the source container.
 *  @param[in]  yLast Iterator defining the end of the source container.
 *  @returns    The distance value.   
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double correlationDistance(InputIt xFirst, InputIt xLast, InputIt yFirst, InputIt yLast);

/**
 *  @brief      Correlation distance ( 1 - corr(x,y) ).
 *  @details    This function calculates the correlation distance between one observation and a set o 
 *              observations.
 *  @tparam     T  The data type of the input arrays.
 *  @param[in]  xt  d-by-1 (or 1-by-d) array with one observation. This is the observation
 *              for which the distances are calculated. 
 *  @param[in]  x  n-by-d array of observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.   
 */
template<nct::Arithmetic T>
RealVector correlationDistance(const Array<T>& xt, const Array2D<T>& x);

/**
 *  @brief      Pairwise correlation distance ( 1 - corr(x,y) ).
 *  @details    This function calculates the correlation distance between pairs of observations. 
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  n-by-d array with the observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix pairwiseCorrelationDistance(const Array2D<T>& x);

//______

/**
 *  @brief      Spearman distance ( 1 - spearman_corr(x,y) ).
 *  @details    This function calculates the Spearman distance of two d-by-1 observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  xFirst  Iterator defining the beginning of the source container.
 *  @param[in]  xLast Iterator defining the end of the source container.
 *  @param[in]  yFirst  Iterator defining the beginning of the source container.
 *  @param[in]  yLast Iterator defining the end of the source container.
 *  @returns    The distance value.   
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double spearmanDistance(InputIt xFirst, InputIt xLast, InputIt yFirst, InputIt yLast);

/**
 *  @brief      Spearman distance ( 1 - spearman_corr(x,y) ).
 *  @details    This function calculates the Spearman distance between one observation and a set o 
 *              observations.
 *  @tparam     T  The data type of the input arrays.
 *  @param[in]  xt  d-by-1 (or 1-by-d) array with one observation. This is the observation
 *              for which the distances are calculated. 
 *  @param[in]  x  n-by-d array of observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.   
 */
template<nct::Arithmetic T>
RealVector spearmanDistance(const Array<T>& xt, const Array2D<T>& x);

/**
 *  @brief      Pairwise Spearman distance ( 1 - spearman_corr(x,y) ).
 *  @details    This function calculates the Spearman distance between pairs of observations. 
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  n-by-d array with the observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix pairwiseSpearmanDistance(const Array2D<T>& x);

//______

/**
 *  @brief      Hamming distance ( sum( I(xi != yi) )/n ).
 *  @details    This function calculates the Hamming distance of two d-by-1 observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  xFirst  Iterator defining the beginning of the source container.
 *  @param[in]  xLast Iterator defining the end of the source container.
 *  @param[in]  yFirst  Iterator defining the beginning of the source container.
 *  @param[in]  yLast Iterator defining the end of the source container.
 *  @returns    The distance value.   
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double jaccardDistance(InputIt xFirst, InputIt xLast, InputIt yFirst, InputIt yLast);

/**
 *  @brief      Hamming distance ( sum( I(xi != yi) )/n ).
 *  @details    This function calculates the Hamming distance between one observation and a set o 
 *              observations.
 *  @tparam     T  The data type of the input arrays.
 *  @param[in]  xt  d-by-1 (or 1-by-d) array with one observation. This is the observation
 *              for which the distances are calculated. 
 *  @param[in]  x  n-by-d array of observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
RealVector jaccardDistance(const Array<T>& xt, const Array2D<T>& x);

/**
 *  @brief      Pairwise Hamming distance ( sum( I(xi != yi) )/n ).
 *  @details    This function calculates the Hamming distance between pairs of observations. 
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  n-by-d array with the observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix pairwiseJaccardDistance(const Array2D<T>& x);

//______

/**
 *  @brief      Jaccard distance ( sum( I(xi != yi) )/sum( I( (xi != 0) || (yi != 0) ) ) )
 *  @details    This function calculates the Jaccard distance of two d-by-1 observations.
 *  @tparam     InputIt  The iterator type to be used to traverse the input data.
 *  @param[in]  xFirst  Iterator defining the beginning of the source container.
 *  @param[in]  xLast Iterator defining the end of the source container.
 *  @param[in]  yFirst  Iterator defining the beginning of the source container.
 *  @param[in]  yLast Iterator defining the end of the source container.
 *  @returns    The distance value.   
 */
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double hammingDistance(InputIt xFirst, InputIt xLast, InputIt yFirst, InputIt yLast);

/**
 *  @brief      Jaccard distance ( sum( I(xi != yi) )/sum( I( (xi != 0) || (yi != 0) ) ) ).
 *  @details    This function calculates the Jaccard distance between one observation and a set o 
 *              observations.
 *  @tparam     T  The data type of the input arrays.
 *  @param[in]  xt  d-by-1 (or 1-by-d) array with one observation. This is the observation
 *              for which the distances are calculated. 
 *  @param[in]  x  n-by-d array of observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
RealVector hammingDistance(const Array<T>& xt, const Array2D<T>& x);

/**
 *  @brief      Pairwise Jaccard distance ( sum( I(xi != yi) )/sum( I( (xi != 0) || (yi != 0) ) ) ).
 *  @details    This function calculates the Jaccard distance between pairs of observations. 
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  n-by-d array with the observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix pairwiseHammingDistance(const Array2D<T>& x);

//______

/**
 *  @brief      Standarized euclidean distance (sum( (xi-yi)^2 / sigmai^2 )).
 *  @details    This function calculates the standarized euclidean distance between one observation and 
 *              a set of observations. The standarized euclidean distance uses the variances of the 
 *              data in order to weight each feature.
 *  @tparam     T  The data type of the input arrays.
 *  @param[in]  xt  d-by-1 (or 1-by-d) array with one observation. This is the observation
 *              for which the distances are calculated. 
 *  @param[in]  x  n-by-d array of observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
RealVector stdEuclideanDistance(const Array<T>& xt, const Array2D<T>& x);

/**
 *  @brief      Standarized euclidean distance (sum( (xi-yi)^2 / sigmai^2 )).
 *  @details    This function calculates the standarized euclidean distance between observations and 
 *              a reference sample x.
 *  @tparam     T  The data type of the input arrays.
 *  @param[in]  xt  n1-by-d array of observations. 
 *  @param[in]  x  n2-by-d array of observations (reference sample). Each row corresponds to an 
 *              observation (n) and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
RealVector refStdEuclideanDistance(const Array2D<T>& xt, const Array2D<T>& x);

/**
 *  @brief      Pairwise standarized euclidean distance (sum( (xi-yi)^2 / sigmai^2 )).
 *  @details    This function calculates the standarized euclidean distance between pairs of observations. 
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  n-by-d array with the observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix pairwiseStdEuclideanDistance(const Array2D<T>& x);

//______

/**
 *  @brief      Mahalanobis distance ( std::sqrt((x-mu)' S^-1 (x-mu)) ).
 *  @details    This function calculates the Mahalanobis distance between a observation and 
 *              a reference set. This distance uses the covariance matrix of the 
 *              data in order to weight and rotate the features.
 *  @tparam     T  The data type of the input arrays.
 *  @param[in]  xt  d-by-1 (or 1-by-d) array with one observation. This is the observation
 *              for which the distances are calculated. 
 *  @param[in]  x  n-by-d array of observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @param[in]  tol  Tolerance for small numbers. it's used to compute the inverse of the
 *              sample covariance matrix.
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
RealVector mahalanobisDistance(const Array<T>& xt, const Array2D<T>& x, double tol = VERY_SMALL_TOL);

/**
 *  @brief      Mahalanobis distance ( std::sqrt((x-mu)' S^-1 (x-mu)) ).
 *  @details    This function calculates the Mahalanobis distance between a set of observations and 
 *              a reference sample. 
 *  @tparam     T  The data type of the input arrays.
 *  @param[in]  xt  n1-by-d array of observations. 
 *  @param[in]  x  n2-by-d array of observations (reference sample). Each row corresponds to an 
 *              observation (n) and each column to a variable or feature (d). 
 *  @param[in]  tol  Tolerance for small numbers. it's used to compute the inverse of the
 *              sample covariance matrix.
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
RealVector refMahalanobisDistance(const Array2D<T>& xt, const Array2D<T>& x, 
    double tol = VERY_SMALL_TOL);

/**
 *  @brief      Pairwise Mahalanobis euclidean distance ( std::sqrt((x-mu)' S^-1 (x-mu)) ).
 *  @details    This function calculates the mahalanobis distance between pairs of observations.
 *  @tparam     T  The data type of the input array.
 *  @param[in]  x  n-by-d array with the observations. Each row corresponds to an observation (n)
 *              and each column to a variable or feature (d). 
 *  @param[in]  tol  Tolerance for small numbers. it's used to compute the inverse of the
 *              sample covariance matrix.
 *  @returns    The array with the result of the operation.
 */
template<nct::Arithmetic T>
Matrix pairwiseMahalanobisDistance(const Array2D<T>& x, double tol = VERY_SMALL_TOL);


}}}

////////// Implementation of function templates //////////
#include <nct/statistics/distance_metrics_template.h> 

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
