//=================================================================================================================
/**
 *  @file       SpectralClustering.cpp
 *  @brief      nct::clustering::SpectralClustering class implementation file.
 *  @details    This file contains the implementation of the nct::clustering::SpectralClustering class.
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
#include <nct/clustering/SpectralClustering.h>
#include <nct/clustering/KMeans.h>
#include <nct/math/linear_algebra.h>
#include <nct/math/math.h>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::clustering::SpectralClustering::SpectralClustering(const Matrix& data, unsigned int nClusters,
    random::RandomNumber& rnd, statistics::distance_metrics::DistanceFunction distanceFunction, 
    double sigma, unsigned int maxIt, double tol)
{
    if (data.size() == 0)
        throw EmptyArrayException("data", SOURCE_INFO);

    if (nClusters == 0)
        throw ArgumentException("nClusters", nClusters, 1U,
            RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    if (nClusters > data.rows())
        throw ArgumentException("nClusters", exc_number_of_clusters_less_than_observations,
            SOURCE_INFO);
    
    if ((distanceFunction != statistics::distance_metrics::DistanceFunction::EuclideanDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::StadarizedEuclideanDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::MahalanobisDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::CityBlockDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::CosineDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::CorrelationDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::SpearmanDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::HammingDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::JaccardDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::ChebychevDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::MinDistance))
        throw ArgumentException("distanceFunction", exc_bad_distance_function,
            SOURCE_INFO);

    try {
        auto n = data.rows();

        ////////// Initialize data members //////////
        k_ = nClusters;
        x_ = data;
        l_.assign(n, 0);
        distanceFunction_ = distanceFunction;
        sigma_ = sigma;

        ////////// Calculate similarities //////////
        calculateDistances();
        calculateSimilarities();

        ////////// Compute clusters //////////
        config(rnd, maxIt, tol);
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
nct::clustering::SpectralClustering::SpectralClustering(Matrix&& data, unsigned int nClusters,
    random::RandomNumber& rnd, statistics::distance_metrics::DistanceFunction distanceFunction, 
    double sigma, unsigned int maxIt, double tol)
{
    if (data.size() == 0)
        throw EmptyArrayException("data", SOURCE_INFO);

    if (nClusters == 0)
        throw ArgumentException("nClusters", nClusters, 1U,
            RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    if (nClusters > data.rows())
        throw ArgumentException("nClusters", exc_number_of_clusters_less_than_observations,
            SOURCE_INFO);

    if ((distanceFunction != statistics::distance_metrics::DistanceFunction::EuclideanDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::StadarizedEuclideanDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::MahalanobisDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::CityBlockDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::CosineDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::CorrelationDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::SpearmanDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::HammingDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::JaccardDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::ChebychevDistance) &&
        (distanceFunction != statistics::distance_metrics::DistanceFunction::MinDistance))
        throw ArgumentException("distanceFunction", exc_bad_distance_function,
            SOURCE_INFO);

    try {
        auto n = data.rows();

        ////////// Initialize data members //////////
        k_ = nClusters;
        x_ = std::move(data);
        l_.assign(n, 0);
        distanceFunction_ = distanceFunction;
        sigma_ = sigma;

        ////////// Calculate similarities //////////
        calculateDistances();
        calculateSimilarities();

        ////////// Compute clusters //////////
        config(rnd, maxIt, tol);
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
nct::clustering::SpectralClustering::SpectralClustering(const Matrix& dist, unsigned int nClusters,
    random::RandomNumber& rnd, double sigma, unsigned int maxIt, double tol)
{
    if (dist.size() == 0)
        throw EmptyArrayException("data", SOURCE_INFO);

    if (!math::linear_algebra::isSymmetric(dist))
        throw ArgumentException("dist", exc_non_symmetric_matrix, 
            SOURCE_INFO);

    if (nClusters == 0)
        throw ArgumentException("nClusters", nClusters, 1U,
            RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    if (nClusters > dist.rows())
        throw ArgumentException("nClusters", exc_number_of_clusters_less_than_observations,
            SOURCE_INFO);

    try {
        auto n = dist.rows();

        ////////// Initialize data members //////////
        k_ = nClusters;
        x_ = Matrix(n, 1, 1);
        l_.assign(n, 0);
        distanceFunction_ = statistics::distance_metrics::DistanceFunction::NoDistance;
        sigma_ = sigma;

        ////////// Calculate similarities //////////
        distances_ = dist;
        calculateSimilarities();

        ////////// Compute clusters //////////
        config(rnd, maxIt, tol);
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
nct::clustering::SpectralClustering::SpectralClustering(Matrix&& dist, unsigned int nClusters,
    random::RandomNumber& rnd, double sigma, unsigned int maxIt, double tol)
{
    if (dist.size() == 0)
        throw EmptyArrayException("data", SOURCE_INFO);

    if (!math::linear_algebra::isSymmetric(dist))
        throw ArgumentException("dist", exc_non_symmetric_matrix,
            SOURCE_INFO);

    if (nClusters == 0)
        throw ArgumentException("nClusters", nClusters, 1U,
            RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    if (nClusters > dist.rows())
        throw ArgumentException("nClusters", exc_number_of_clusters_less_than_observations,
            SOURCE_INFO);

    try {
        auto n = dist.rows();

        ////////// Initialize data members //////////
        k_ = nClusters;
        x_ = Matrix(n, 1, 1);
        l_.assign(n, 0);
        distanceFunction_ = statistics::distance_metrics::DistanceFunction::NoDistance;
        sigma_ = sigma;

        ////////// Calculate similarities //////////
        distances_ = std::move(dist);
        calculateSimilarities();

        ////////// Compute clusters //////////
        config(rnd, maxIt, tol);
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
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
double nct::clustering::SpectralClustering::sigma() const noexcept
{
    return sigma_;
}

//-----------------------------------------------------------------------------------------------------------------
nct::statistics::distance_metrics::DistanceFunction
nct::clustering::SpectralClustering::distanceFunction() const noexcept
{
    return distanceFunction_;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Matrix& nct::clustering::SpectralClustering::distanceArray() const noexcept
{
    return distances_;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Matrix& nct::clustering::SpectralClustering::similarityArray() const noexcept
{
    return similarities_;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::RealVector& nct::clustering::SpectralClustering::eigenvalues() const noexcept
{
    return d_;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Matrix& nct::clustering::SpectralClustering::eigenvectors() const noexcept
{
    return v_;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::clustering::SpectralClustering::config(random::RandomNumber& rnd, 
    unsigned int maxIt, double tol)
{    
    ////////// Compute Laplacian matrix //////////
    auto n = distances_.rows();
    Matrix L(n, n, 0);
    RealVector D(n, 0);

    for (index_t i=0; i<n; i++) {
        for (index_t j=0; j<n; j++)
            D[i] += similarities_(i,j);
        D[i] = std::sqrt(1.0/(D[i] + SMALL_FP));
    }

    for (index_t i=0; i<n; i++) {
        for (index_t j=0; j<n; j++)        
            L(i,j) = - similarities_(i,j)*D[i]*D[j];

        L(i,i)++;
    }
    
    ////////// Compute eigenvalues //////////         
    try {
        math::linear_algebra::makeSymmetric(L);
        auto eig = math::linear_algebra::symmEigenvectors(L);
        v_ = std::move(eig.v);
        d_ = std::move(eig.d);
    }
    catch (const nct_exception& ex) {
        v_.clear();
        d_.clear();
        throw OperationException(exc_bad_eigenvalues_of_laplacian,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        v_.clear();
        d_.clear();
        throw OperationException(exc_bad_eigenvalues_of_laplacian, 
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        v_.clear();
        d_.clear();
        throw OperationException(exc_unknown, SOURCE_INFO);
    }
    
    ////////// Compute clusters //////////     
    try {
        recalculateClusters(k_, rnd, maxIt, tol);
    }
    catch (const std::exception& ex) {
        throw OperationException(exc_clustering_error, 
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_unknown, SOURCE_INFO);
    }
}

//-----------------------------------------------------------------------------------------------------------------
void nct::clustering::SpectralClustering::recalculateClusters(unsigned int nClusters, 
    random::RandomNumber& rnd, unsigned int maxIt, double tol)
{
    if (nClusters > x_.rows())
        throw ArgumentException("nClusters", exc_number_of_clusters_less_than_observations, 
        SOURCE_INFO);        

    if (v_.size() == 0 || d_.size() == 0) {
        throw ConfigurationException(exc_uninitialized_object, SOURCE_INFO);
    }

    auto n = x_.rows();
    k_ = nClusters;

    ////////// Compute normalized Array of K eigenvectors //////////
    Matrix U(n, k_);
    for (index_t i=0; i<n; i++) {
        for (unsigned int j=0; j<k_; j++) {
            U(i,j) = v_(i,n-j-1);
        }
    }
    
    for (index_t i=0; i<n; i++) {
        double norm =  0;
        for (unsigned int j=0; j<k_; j++)
            norm += math::sqr(U(i,j));
        norm = std::sqrt(norm) + 1E-20;

        for (unsigned int j=0; j<k_; j++)
            U(i,j) = U(i,j) / norm;
    }

    ////////// Do K-means in U //////////
    try {
        KMeans kmeans(U, nClusters, rnd, 
            KMeans::InitializationMethod::OrthogonalCenters, maxIt, tol);
        l_ = kmeans.labels();
    }
    catch (const nct_exception& ex) {
        throw OperationException(exc_clustering_error,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {        
        throw OperationException(exc_clustering_error, 
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {        
        throw OperationException(exc_unknown, SOURCE_INFO);
    }
}

//-----------------------------------------------------------------------------------------------------------------
void nct::clustering::SpectralClustering::calculateDistances()
{
    // Alocate arrays.
    auto n = x_.rows();
    distances_.assign(n, n, 0);
    
    // Compute distances.
    switch (distanceFunction_) {
        case statistics::distance_metrics::DistanceFunction::EuclideanDistance:
            distances_ = statistics::distance_metrics::pairwiseEuclideanDistance(x_);
            break;        
        case statistics::distance_metrics::DistanceFunction::StadarizedEuclideanDistance:
            distances_ = statistics::distance_metrics::pairwiseStdEuclideanDistance(x_);
            break;        
        case statistics::distance_metrics::DistanceFunction::MahalanobisDistance:
            distances_ = statistics::distance_metrics::pairwiseMahalanobisDistance(x_);
            break;        
        case statistics::distance_metrics::DistanceFunction::CityBlockDistance:
            distances_ = statistics::distance_metrics::pairwiseCityBlockDistance(x_);
            break;        
        case statistics::distance_metrics::DistanceFunction::CosineDistance:
            distances_ = statistics::distance_metrics::pairwiseCosineDistance(x_);
            break;        
        case statistics::distance_metrics::DistanceFunction::CorrelationDistance:
            distances_ = statistics::distance_metrics::pairwiseCorrelationDistance(x_);
            break;        
        case statistics::distance_metrics::DistanceFunction::SpearmanDistance:
            distances_ = statistics::distance_metrics::pairwiseSpearmanDistance(x_);
            break;        
        case statistics::distance_metrics::DistanceFunction::HammingDistance:
            distances_ = statistics::distance_metrics::pairwiseHammingDistance(x_);
            break;        
        case statistics::distance_metrics::DistanceFunction::JaccardDistance:
            distances_ = statistics::distance_metrics::pairwiseJaccardDistance(x_);
            break;        
        case statistics::distance_metrics::DistanceFunction::ChebychevDistance:
            distances_ = statistics::distance_metrics::pairwiseChebychevDistance(x_);
            break;        
        case statistics::distance_metrics::DistanceFunction::MinDistance:
            distances_ = statistics::distance_metrics::pairwiseMinDistance(x_);
            break;    
        default:
            throw ConfigurationException(exc_bad_distance_function, SOURCE_INFO);
    }
}

//-----------------------------------------------------------------------------------------------------------------
void nct::clustering::SpectralClustering::calculateSimilarities()
{
    // Alocate arrays.
    auto n = x_.rows();
    similarities_.assign(n, n, 0);

    // Compute similarity function (exp(-A*A/(2*sigma*sigma)).
    if (sigma_ > 0) {
        // Use selected sigma.
        double tmp = -1/(2*sigma_*sigma_);
        for (index_t i=0; i<n; i++) {
            similarities_(i,i) = exp(tmp * math::sqr(distances_(i,i)) );
            for (auto j=(i+1); j<n; j++) {    
                similarities_(i,j) = exp(tmp * math::sqr(distances_(i,j)) );
                similarities_(j,i) = similarities_(i,j);
            }
        }
    }
    else {
        // Self-tune sigma.
        RealVector colMeans(n, 0);
        RealVector colItems(n, 0);

        for (index_t i=0; i<n; i++) {
            for (index_t j=0; j<n; j++) {
                if (distances_(i,j) != 0) {
                    colMeans[i] += distances_(i,j);
                    colItems[i]++;
                }
            }        
            if (colItems[i]==0)
                colItems[i] = 1;
            colMeans[i] /= colItems[i];
        }
        
        for (index_t i=0; i<n; i++) {
            similarities_(i,i) = exp( -math::sqr(distances_(i,i))/(2*colMeans[i]*colMeans[i]) );
            for (auto j=(i+1); j<n; j++) {    
                similarities_(i,j) = exp( -math::sqr(distances_(i,j))/(2*colMeans[i]*colMeans[j]) );
                similarities_(j,i) = similarities_(i,j);
            }
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Array<int>& nct::clustering::SpectralClustering::labels() const noexcept
{
    return l_;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Matrix& nct::clustering::SpectralClustering::observations() const noexcept
{
    return x_;
}

//-----------------------------------------------------------------------------------------------------------------
unsigned int nct::clustering::SpectralClustering::numberOfClusters() const noexcept
{
    return k_;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
