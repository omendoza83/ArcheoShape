//=================================================================================================================
/**
 *  @file       SpectralClustering.h
 *  @brief      nct::clustering::SpectralClustering class.
 *  @details    Declaration of the nct::clustering::SpectralClustering class.
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

#ifndef NCT_SPECTRAL_CLUSTERING_H_INCLUDE
#define NCT_SPECTRAL_CLUSTERING_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/Array.h>
#include <nct/Array2D.h>
#include <nct/statistics/distance_metrics.h>
#include <nct/random/RandomNumber.h>

//=================================================================================================================
namespace nct {
namespace clustering {

/**
 *  @brief      Class for spectral clustering algorithm.
 *  @details    This class is used to find clusters in data using the spectral clustering algorihtm.
 */
class NCT_EXPIMP SpectralClustering final {

public:

    ////////// Constructors //////////
    
    /**
     *  @brief      Class constructor.
     *  @details    This constructor builds a clustering object according to an input array of data and
     *              the given number of clusters. Each column of the input data is a variable or feature
     *              of the data and each row is an observation.
     *  @param[in]  data  N-by-D array of observations to group.  
     *  @param[in]  nClusters  Number of clusters to group the data.
     *  @param[in, out] rnd  Pseudo-random number generator.
     *  @param[in]  distanceFunction  Distance function between observations.
     *  @param[in]  sigma  Value of sigma in the similarity function.
     *  @param[in]  maxIt  The maximum number of iterations for the K-means algorithm.
     *  @param[in]  tol  Tolerance value used to calculate the SVD decomposition of the laplacian matrix.
     */
    SpectralClustering(const Matrix& data, unsigned int nClusters, random::RandomNumber& rnd,
        statistics::distance_metrics::DistanceFunction distanceFunction,
        double sigma = -1, unsigned int maxIt = 1000, double tol = VERY_SMALL_TOL);

    /**
     *  @brief      Class constructor.
     *  @details    This constructor builds a clustering object according to an input array of data and
     *              the given number of clusters. The object takes ownership of the input array. Each
     *              column of the input data is a variable or feature of the data and each row is an
     *              observation.
     *  @param[in]  data  N-by-D array of observations to group.  
     *  @param[in]  nClusters  Number of clusters to group the data.
     *  @param[in, out] rnd  Pseudo-random number generator.
     *  @param[in]  distanceFunction  Distance function between observations.
     *  @param[in]  sigma  Value of sigma in the similarity function.
     *  @param[in]  maxIt  The maximum number of iterations for the K-means algorithm.
     *  @param[in]  tol  Tolerance value used to calculate the SVD decomposition of the laplacian matrix.
     */
    SpectralClustering(Matrix&& data, unsigned int nClusters, random::RandomNumber& rnd,
        statistics::distance_metrics::DistanceFunction distanceFunction,
        double sigma = -1, unsigned int maxIt = 1000, double tol = VERY_SMALL_TOL);

    /**
     *  @brief      Class constructor.
     *  @details    This constructor builds a clustering object according to an input array with the
     *              distances between observations.
     *  @param[in]  dist  N-by-N array of distances between elements.
     *  @param[in]  nClusters  Number of clusters to group the data.
     *  @param[in, out] rnd  Pseudo-random number generator.
     *  @param[in]  sigma  Value of sigma in the similarity function.
     *  @param[in]  maxIt  The maximum number of iterations for the K-means algorithm.
     *  @param[in]  tol  Tolerance value used to calculate the SVD decomposition of the laplacian matrix.
     */
    SpectralClustering(const Matrix& dist, unsigned int nClusters, random::RandomNumber& rnd,
        double sigma = -1, unsigned int maxIt = 1000, double tol = VERY_SMALL_TOL);

    /**
     *  @brief      Class constructor.
     *  @details    This constructor builds a clustering object according to an input array with the
     *              distances between observations. This constructor takes ownership of the data stored
     *              in the distance array.
     *  @param[in]  dist  N-by-N array of distances between elements.
     *  @param[in]  nClusters  Number of clusters to group the data.
     *  @param[in, out] rnd  Pseudo-random number generator.
     *  @param[in]  sigma  Value of sigma in the similarity function.
     *  @param[in]  maxIt  The maximum number of iterations for the K-means algorithm.
     *  @param[in]  tol  Tolerance value used to calculate the SVD decomposition of the laplacian matrix.
     */
    SpectralClustering(Matrix&& dist, unsigned int nClusters, random::RandomNumber& rnd,
        double sigma = -1, unsigned int maxIt = 1000, double tol = VERY_SMALL_TOL);
    
    ////////// Member functions //////////

    /**
     *  @brief      Sigma.
     *  @details    This function returns the value of sigma that is used in the similarity function.
     *  @returns    The value of sigma.
     */
    double sigma() const noexcept;

    /**
     *  @brief      Distance function.
     *  @details    This function returns the distance function used in the algorithm.
     *  @returns    The distance function.
     */
    statistics::distance_metrics::DistanceFunction distanceFunction() const noexcept;

    /**
     *  @brief      Distances.
     *  @details    This function returns a reference to the array with the distances between
     *              observations.
     *  @returns    The distance array.
     */
    const Matrix& distanceArray() const noexcept;

    /**
     *  @brief      Similarities.
     *  @details    This function returns a reference to the array with the similarities between
     *              observations.
     *  @returns    The similarity array.
     */
    const Matrix& similarityArray() const noexcept;

    /**
     *  @brief      Eigenvalues of Laplacian matrix.
     *  @details    This function returns a reference to the array with the eigenvalues of the
     *              Laplacian Matrix.
     *  @returns    The eigenvalues array.
     */
    const RealVector& eigenvalues() const noexcept;

    /**
     *  @brief      Eigenvectors of Laplacian matrix.
     *  @details    This function returns a reference to the array with the eigenvectors of the
     *              Laplacian Matrix.
     *  @returns    The eigenvectors array.
     */
    const Matrix& eigenvectors() const noexcept;

    /**
     *  @brief      Recalculate clusters.
     *  @details    This function calculates clusters according to the current eigenvectors and eigenvalues of the 
     *              Laplacian matrix. 
     *  @param[in]  nClusters  Number of clusters to group the data. 
     *  @param[in, out] rnd  Pseudo-random number generator.
     *  @param[in]  maxIt  The maximum number of iterations for the K-means algorithm.
     *  @param[in]  tol  Tolerance value used in the K-means algorithm.
     */
    void recalculateClusters(unsigned int nClusters, random::RandomNumber& rnd,
        unsigned int maxIt = 1000, double tol = VERY_SMALL_TOL);

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
     *  @details    This function configures object and calculated centers of the clusters. 
     *  @param[in]  dist  N-by-N array of distances between elements.  
     *  @param[in]  nClusters  Number of clusters to group the data.
     *  @param[in, out] rnd  Pseudo-random number generator.
     *  @param[in]  sigma  Value of sigma in the similarity function. A negative value indicates
     *              the sigma must be self-tuned by the algorithm.
     *  @param[in]  maxIt  The maximum number of iterations for the K-means algorithm.
     *  @param[in]  tol  Tolerance value used to calculate the SVD decomposition of the 
     *              laplacian matrix.
     */
    void config(random::RandomNumber& rnd, unsigned int maxIt = 1000,
        double tol = VERY_SMALL_TOL);

    /**
     *  @brief      Calculate the distances.
     *  @details    This function calculates the distances between observations.
     */
    void calculateDistances();

    /**
     *  @brief      Calculate the similarities.
     *  @details    This function calculates the similarities between observations.
     */
    void calculateSimilarities();

    ////////// Data members //////////        

    Matrix x_;              /**< N-by-D array of observations. Each row is an observation and
                                 each column is a feature or variable. */
    Array<int> l_;          /**< N-by-1 array of labels (between 1 and k for k clusters)
                                 of each observation. */
    unsigned int k_ {0};    /**< Number of clusters. */

    double sigma_ {0};      /**< Value of sigma in the similarity function. */

    /** Distance function. */
    statistics::distance_metrics::DistanceFunction distanceFunction_ { 
        statistics::distance_metrics::DistanceFunction::EuclideanDistance};    

    Matrix distances_;      /**< Distance array. */

    Matrix similarities_;   /**< Similarity array. */

    RealVector d_;          /**< Eigenvalues of Laplacian matrix. */

    Matrix v_;              /**< Eigenvectors of Laplacian matrix. */
};

}}

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
