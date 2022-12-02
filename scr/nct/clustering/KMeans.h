//=================================================================================================================
/**
 *  @file       KMeans.h
 *  @brief      nct::clustering::KMeans class.
 *  @details    Declaration of the nct::clustering::KMeans class.
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

#ifndef NCT_KMEANS_H_INCLUDE
#define NCT_KMEANS_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_constants.h>
#include <nct/nct_exception.h>
#include <nct/Array.h>
#include <nct/Array2D.h>
#include <nct/random/RandomNumber.h>

//=================================================================================================================
namespace nct {
/**
 *  @brief      Clustering namespace.
 *  @details    This namespace contains classes and functions related to clustering algorithms.
 */
namespace clustering {

/**
 *  @brief      Class for K-means clustering algorithm.
 *  @details    This class is used to find clusters in data using the K-means algorihtm.
 */
class NCT_EXPIMP KMeans final {

public:

    ////////// Enumerations //////////

    /**
     *  @brief      Initialization methods.
     *  @details    Initialization methods for centers.
     */
    enum class InitializationMethod : unsigned char {

        RandomCenters,          /**< Random centers between min and max values of each variable. */

        OrthogonalCenters,      /**< Ortogonal centers. */

        RandomPoints,           /**< Choose random points. */

        RandomPartition,        /**< Choose a random partition. */
    };

    ////////// Constructors //////////
    
    /**
     *  @brief      Class constructor.
     *  @details    This constructor builds a clustering object according to an input array of data and the
     *              given number of clusters. Each column of the input data is a variable or feature of 
     *              the data and each row is an observation.
     *  @param[in]  data  N-by-D array of observations.  
     *  @param[in]  nClusters  Number of clusters to group the data.
     *  @param[in, out] rnd  Pseudo-random number generator.
     *  @param[in]  method  Method to use in the initialization of the cluster centers.
     *  @param[in]  maxIt  The maximum number of iterations in the optimization algorithm.
     *  @param[in]  tol  Minimum change in the objective function before stopping the algorithm.
     */
    KMeans(const Matrix& data, unsigned int nClusters, random::RandomNumber& rnd,
        InitializationMethod method = InitializationMethod::RandomCenters,
        unsigned int maxIt = 1000, double tol = VERY_SMALL_TOL);

    /**
     *  @brief      Class constructor.
     *  @details    This constructor builds a clustering object according to an input array of data and the
     *              given number of clusters. The object takes ownership of the input array.
     *              Each column of the input data is a variable or feature of 
     *              the data and each row is an observation.
     *  @param[in]  data  N-by-D array of observations.  
     *  @param[in]  nClusters  Number of clusters to group the data.
     *  @param[in, out] rnd  Pseudo-random number generator.
     *  @param[in]  method  Method to use in the initialization of the cluster centers.
     *  @param[in]  maxIt  The maximum number of iterations in the optimization algorithm.
     *  @param[in]  tol  Minimum change in the objective function before stopping the algorithm.
     */
    KMeans(Matrix&& data, unsigned int nClusters, random::RandomNumber& rnd,
        InitializationMethod method = InitializationMethod::RandomCenters,
        unsigned int maxIt = 1000, double tol = VERY_SMALL_TOL);
    
    ////////// Member functions //////////

    /**
     *  @brief      Method to calculate initial centers.
     *  @details    This function returns the method that was used to calculate the initial centers.
     *  @returns    The inicialization method.
     */
    InitializationMethod initializationMethod() const noexcept;

    /**
     *  @brief      Cluster centers.
     *  @details    This function returns the centers of the calculated clusters.
     *  @returns    A reference to the array with the centers.
     */
    const Matrix& centers() const noexcept;

    /**
     *  @brief      Find the closest center.
     *  @details    This function finds the closest center to the specified point and the
     *              calculated squared distance to this point.      
     *  @param[in]  p  Point to tbe tested.
     *  @returns    A tuple with wich contains the following elements: * The squared distance to the
     *              closest center. \n * The index of the closest center.
     */
    std::tuple<double, int> findClosestCenter(const RealVector& p) const;

    /**
     *  @brief      Find the closest center.
     *  @details    This function finds the closest center to the specified point and the
     *              calculated squared distance to this point. in this function, the point to be tested
     *              is one row of an 2D array.
     *  @param[in]  data  Array with the point to be tested.
     *  @param[in]  row  Row index of the point to be tested.
     *  @returns    A tuple with wich contains the following elements: * The squared distance to the
     *              closest center. \n * The index of the closest center.
     */
    std::tuple<double, int> findClosestCenter(const Matrix& data, size_t row) const;

    /**
     *  @brief      Label array.
     *  @details    This function returns the labels that correspond to each observation.
     *  @returns    A reference to the array with the observations.
     */
    const Array<int>& labels() const noexcept;

    /**
     *  @brief      Data array.
     *  @details    This function returns the obsevations.
     *  @returns    A reference to the array with the observations.
     */
    const Matrix& observations() const noexcept;

    /**
     *  @brief      Number of clusters.
     *  @details    This function returns the number of clusters to group the data.
     *  @returns    the number of clusters.
     */
    unsigned int numberOfClusters() const noexcept;

private:

    ////////// Member functions //////////

    /**
     *  @brief      Configure object.
     *  @details    This function configures object and calculates centers of clusters. 
     *  @param[in, out] rnd  Pseudo-random number generator.
     *  @param[in]  maxIt  The maximum number of iterations in the optimization algorithm.
     *  @param[in]  tol  Minimum change in the objective function before stopping the algorithm.
     */
    void config(random::RandomNumber& rnd,
        unsigned int maxIt = 1000, double tol = VERY_SMALL_TOL);
    
    /**
     *  @brief      Initialize centers.
     *  @details    This function initializes the cluster centers.
     *  @param[in, out] rnd  Pseudo-random number generator.
     */
    void initializeCenters(random::RandomNumber& rnd);

    ////////// Data members //////////            

    Matrix x_;              /**< N-by-D array of observations. Each row is an observation and
                                 each column is a feature or variable. */
    Array<int> l_;          /**< N-by-1 array of labels (between 1 and k for k clusters)
                                 of each observation. */
    unsigned int k_ {0};    /**< Number of clusters. */

    /** Initialization method. */
    InitializationMethod initializationMethod_ {InitializationMethod::RandomCenters};    

    Matrix centers_;        /**< K-by-D array of cluster centers. */

};

}}

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
