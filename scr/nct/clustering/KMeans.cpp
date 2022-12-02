//=================================================================================================================
/**
 *  @file       KMeans.cpp
 *  @brief      nct::clustering::KMeans class implementation file.
 *  @details    This file contains the implementation of the nct::clustering::KMeans class.
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
#include <algorithm>

#include <nct/clustering/KMeans.h>
#include <nct/math/math.h>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::clustering::KMeans::KMeans(const Matrix& data, unsigned int nClusters, random::RandomNumber& rnd,
    InitializationMethod method, unsigned int maxIt, double tol)
{
    if (data.size() == 0)
        throw EmptyArrayException("data", SOURCE_INFO);

    if (nClusters == 0)
        throw ArgumentException("nClusters", nClusters, 1U,
            RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    if (nClusters > data.rows())
        throw ArgumentException("nClusters", exc_number_of_clusters_less_than_observations, SOURCE_INFO);

    try {

        k_ = nClusters;
        x_ = data;
        l_.assign(x_.rows(), 0);
        initializationMethod_ = method;
        centers_.assign(k_, data.columns(), 0);

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
nct::clustering::KMeans::KMeans(Matrix&& data, unsigned int nClusters, random::RandomNumber& rnd,
    InitializationMethod method, unsigned int maxIt, double tol)
{
    if (data.size() == 0)
        throw EmptyArrayException("data", SOURCE_INFO);

    if (nClusters == 0)
        throw ArgumentException("nClusters", nClusters, 1U,
            RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    if (nClusters > data.rows())
        throw ArgumentException("nClusters", exc_number_of_clusters_less_than_observations, SOURCE_INFO);

    try {
        k_ = nClusters;
        x_ = std::move(data);
        l_.assign(x_.rows(), 0);
        initializationMethod_ = method;
        centers_.assign(k_, x_.columns(), 0);

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
nct::clustering::KMeans::InitializationMethod nct::clustering::KMeans::initializationMethod() const noexcept
{
    return initializationMethod_;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Matrix& nct::clustering::KMeans::centers() const noexcept
{
    return centers_;
}

//-----------------------------------------------------------------------------------------------------------------
std::tuple<double, int> nct::clustering::KMeans::findClosestCenter(const RealVector& p) const
{
    auto d = x_.columns();

    if (d != p.size())
        throw ArgumentException("p", exc_bad_array_size, SOURCE_INFO);
    
    int center = 0;            
    double dAcc = 0;
    for (index_t j=0; j<d; j++)
        dAcc += math::sqr(p[j] - centers_(0,j));

    double dMin = dAcc;
    for (unsigned int ki=1; ki<k_; ki++) {
        dAcc = 0;
        for (index_t j=0; j<d; j++)
            dAcc += math::sqr(p[j] - centers_(ki,j));
        if (dAcc < dMin) {
            center = ki;
            dMin = dAcc;
        }
    }
    
    return std::make_tuple(dMin, center);
}

//-----------------------------------------------------------------------------------------------------------------
std::tuple<double, int> nct::clustering::KMeans::findClosestCenter( const Matrix& data, size_t row) const
{    
    if (row >= data.rows())
        throw IndexOutOfRangeException("row", SOURCE_INFO);

    if (data.columns() != x_.columns())
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);
    
    int center = 0;
    auto d = x_.columns();
    double dAcc = 0;
    for (index_t j=0; j<d; j++)
        dAcc += math::sqr(data(row,j) - centers_(0,j));

    double dMin = dAcc;
    for (unsigned int ki=1; ki<k_; ki++) {
        dAcc = 0;
        for (index_t j=0; j<d; j++)
            dAcc += math::sqr(data(row,j) - centers_(ki,j));
        if (dAcc < dMin) {
            center = ki;
            dMin = dAcc;
        }
    }
    
    return std::make_tuple(dMin, center);
}

//-----------------------------------------------------------------------------------------------------------------
void nct::clustering::KMeans::config(random::RandomNumber& rnd,
    unsigned int maxIt, double tol)
{
    auto d = x_.columns();
    auto n = x_.rows();
    
    ////////// Find limits of the space //////////    
    auto minD = x_.minCol();
    auto maxD = x_.maxCol();

    ////////// Calculate clusters //////////
    try {
        // Initialize centers.
        initializeCenters(rnd);

        // Find closest center to each point and its distance.
        RealVector p(n);
        for (index_t i = 0; i < n; i++) {
            auto pc = findClosestCenter(x_, i);
            p[i] = std::get<0>(pc);
            l_[i] = std::get<1>(pc);
        }

        // Iterate until it converges.
        unsigned int it = 0;
        double qNew = PLUS_INF;
        double qOld = 0;
        Array<unsigned int> items(k_);

        tol = tol >= 0 ? tol : VERY_SMALL_TOL;

        while ((it < maxIt) && (math::absRelativeDifferenceMod(qNew, qOld) > tol)) {
            qOld = qNew;        
            
            // Sum up data points within each center.
            centers_.fill(0);
            items.fill(0);
            for (index_t i=0; i<n; i++) {
                for (index_t j=0; j<d; j++)
                    centers_(l_[i], j) += x_(i,j);
                items[l_[i]]++;
            }            

            // Initialize randomly empty centers.
            for (unsigned int ki = 0; ki<k_; ki++) {
                if (items[ki] == 0) {
                    for (index_t j=0; j<d; j++)
                        centers_(ki,j)=minD[j] + (maxD[j] - minD[j])*rnd.random();
                    items[ki] = 1;
                }
            }

            // Update centers.
            for (unsigned int ki = 0; ki<k_; ki++) {
                for (index_t j=0; j<d; j++)
                    centers_(ki, j) /= items[ki];
            }

            // Update labels and distances.
            for (index_t i = 0; i < n; i++) {
                auto pc = findClosestCenter(x_, i);
                p[i] = std::get<0>(pc);
                l_[i] = std::get<1>(pc);
            }

            // Calculate objective function.
            qNew = 0;
            for (index_t i=0; i<n; i++)
                qNew += p[i];
            qNew/=n;

            // Update iterations.
            it++;            
        }    

        if (it >= maxIt)
            throw OperationException(exc_maximum_number_of_iterations_exceeded, SOURCE_INFO);

        for (index_t i=0; i<n; i++)        
            l_[i] ++;
    }
    catch (const nct_exception& ex) {
        throw OperationException(exc_clustering_error, SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw OperationException(exc_clustering_error, SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_unknown, SOURCE_INFO);
    }        
}

//-----------------------------------------------------------------------------------------------------------------
void nct::clustering::KMeans::initializeCenters(random::RandomNumber& rnd)
{
    auto d = x_.columns();
    auto n = x_.rows();

    // Minimum and maximun values of each column.
    auto minD = x_.minCol();
    auto maxD = x_.maxCol();

    ////////// Calculate initial centers //////////
    if (initializationMethod_ == InitializationMethod::RandomCenters) {
        // Random centers.
        for (index_t j=0; j<d; j++) {
            for (unsigned int i=0; i<k_; i++)
                centers_(i,j) = minD[j] + (maxD[j] - minD[j])*rnd.random();
        }
    }
    else if (initializationMethod_ == InitializationMethod::OrthogonalCenters) {
        // Orthogonal centers.    
        auto xTmp = x_;
        RealVector acc(n-1, 0);
        RealVector prevC(d);        

        // Select one center.
        auto c = static_cast<size_t>(n*rnd.random());
        if (c == n)
            c--;

        for (index_t j=0; j<d; j++)
            centers_(0, j) = xTmp (c, j);
        xTmp.eraseRow(c);        

        // Choose the most orthogonal centers.
        for (unsigned int ki = 1; ki<k_; ki++) {
            // Previous center.
            for (index_t j=0; j<d; j++)
                prevC[j] = centers_(ki-1, j);

            // Accumalated orthogonal values to existing centers for non-centers.
            auto ctmp = matrixVectorProduct(xTmp, prevC);
            std::transform(ctmp.begin(), ctmp.end(), ctmp.begin(), math::absolute<double>);
            acc+=ctmp;

            // Find the lowest element in acc.
            c = math::minimumValueIndex(acc.begin(), acc.end());

            // Store new center.
            for (index_t j=0; j<d; j++)
                centers_(ki, j) = xTmp (c, j);

            // Remove added center.
            xTmp.eraseRow(c);
            acc.erase(c);
        }
    }
    else if (initializationMethod_ == InitializationMethod::RandomPoints) {
        Array<size_t> points(k_);
        for (unsigned int ki=0; ki<k_; ki++) {
            bool exit = false;
            while (!exit) {
                exit = true;
                points[ki] = static_cast<size_t>(n*rnd.random());
                if (points[ki] == n)
                    points[ki]--;

                for (unsigned int j=0; j<ki; j++) {
                    if (points[ki] == points[j])
                        exit = false;
                }
            }            
        }

        for (unsigned int ki=0; ki<k_; ki++)
            for (index_t j=0; j<d; j++)
                centers_(ki,j) = x_(points[ki], j);
    }
    else if (initializationMethod_ == InitializationMethod::RandomPartition) {
        Array<unsigned int> part(n);
        Array<size_t> items(k_);

        // Assign to each point to a center.
        for (index_t i=0; i<n; i++) {
            part[i] = static_cast<unsigned int>(k_*rnd.random());
            if (part[i]==k_)
                part[i]--;
        }
                
        // Sum up points within centers.
        items.fill(0);
        centers_.fill(0);
        for (index_t i=0; i<n; i++) {
            for (index_t j=0; j<d; j++)
                centers_(part[i], j) += x_(i,j);
            items[part[i]]++;            
        }            

        // Initialize randomly empty centers.
        for (unsigned int ki = 0; ki<k_; ki++) {
            if (items[ki] == 0) {
                for (index_t j=0; j<d; j++)
                    centers_(ki,j)=minD[j] + (maxD[j] - minD[j])*rnd.random();
                items[ki] = 1;
            }
        }

        // Update centers.        
        for (unsigned int ki = 0; ki<k_; ki++) {
            for (index_t j=0; j<d; j++)
                centers_(ki, j) /= items[ki];
        }
    }
    else {
        throw ArgumentException("method", exc_bad_init_method, SOURCE_INFO);
    }

    // Verify that all the centers are different.
    for (unsigned int i=1; i<k_; i++) {
        index_t j = 0;
        for (j=0; j<d; j++) {    
            if (centers_(i,j) != centers_(i-1,j))
                break;        
        }

        if (j == d) {
            for (index_t ii=0; ii<d; ii++)                
                centers_(i, ii)=minD[ii] + (maxD[ii] - minD[ii])*rnd.random();
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Array<int>& nct::clustering::KMeans::labels() const noexcept
{
    return l_;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Matrix& nct::clustering::KMeans::observations() const noexcept
{
    return x_;
}

//-----------------------------------------------------------------------------------------------------------------
unsigned int nct::clustering::KMeans::numberOfClusters() const noexcept
{
    return k_;
}
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
