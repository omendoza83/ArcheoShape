//=================================================================================================================
/**
 *  @file       distance_metrics_template.h
 *  @brief      Implementation of distance functions.
 *  @details    This file contains the implementation of the template functions defined in 
 *              the nct::statistics::distance_metrics namespace.            
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
//        GENERIC FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::distance_metrics::distance(InputIt xFirst, InputIt xLast,
    InputIt yFirst, InputIt yLast, DistanceFunction distanceFunction, double param)
{
    double d = 0;
    switch (distanceFunction) {
        case DistanceFunction::SquaredEuclideanDistance:
            d = squaredEuclideanDistance(xFirst, xLast, yFirst, yLast);
            break;
        case DistanceFunction::EuclideanDistance:
            d = euclideanDistance(xFirst, xLast, yFirst, yLast);
            break;
        case DistanceFunction::MinkowskiDistance:
            d = minkowskiDistance(xFirst, xLast, yFirst, yLast, param);
            break;
        case DistanceFunction::CityBlockDistance:
            d = cityBlockDistance(xFirst, xLast, yFirst, yLast);
            break;
        case DistanceFunction::ChebychevDistance:
            d = chebychevDistance(xFirst, xLast, yFirst, yLast);
            break;    
        case DistanceFunction::MinDistance:
            d = minDistance(xFirst, xLast, yFirst, yLast);
            break;    
        case DistanceFunction::BhattacharyyaDistance:
            d = bhattacharrayDistance(xFirst, xLast, yFirst, yLast);
            break;    
        case DistanceFunction::CosineDistance:
            d = cosineDistance(xFirst, xLast, yFirst, yLast);
            break;
        case DistanceFunction::CorrelationDistance:
            d = correlationDistance(xFirst, xLast, yFirst, yLast);
            break;
        case DistanceFunction::SpearmanDistance:
            d = spearmanDistance(xFirst, xLast, yFirst, yLast);
            break;
        case DistanceFunction::JaccardDistance:
            d = jaccardDistance(xFirst, xLast, yFirst, yLast);
            break;
        case DistanceFunction::HammingDistance:
            d = hammingDistance(xFirst, xLast, yFirst, yLast);
            break;        
        default:
            throw ConfigurationException(exc_bad_distance_function, SOURCE_INFO);
    }

    return d;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::RealVector nct::statistics::distance_metrics::distance(const Array<T>& xt, 
    const Array2D<T>& x, DistanceFunction distanceFunction, double param)
{
    RealVector dist;
    switch (distanceFunction) {
        case DistanceFunction::SquaredEuclideanDistance:
            dist = squaredEuclideanDistance(xt, x);
            break;
        case DistanceFunction::EuclideanDistance:
            dist = euclideanDistance(xt, x);
            break;
        case DistanceFunction::MinkowskiDistance:
            dist = minkowskiDistance(xt, x, param);
            break;
        case DistanceFunction::CityBlockDistance:
            dist = cityBlockDistance(xt, x);
            break;
        case DistanceFunction::ChebychevDistance:
            dist = chebychevDistance(xt, x);
            break;    
        case DistanceFunction::MinDistance:
            dist = minDistance(xt, x);
            break;    
        case DistanceFunction::CosineDistance:
            dist = cosineDistance(xt, x);
            break;
        case DistanceFunction::CorrelationDistance:
            dist = correlationDistance(xt, x);
            break;
        case DistanceFunction::SpearmanDistance:
            dist = spearmanDistance(xt, x);
            break;
        case DistanceFunction::JaccardDistance:
            dist = jaccardDistance(xt, x);
            break;
        case DistanceFunction::HammingDistance:
            dist = hammingDistance(xt, x);
            break;        
        default:
            throw ConfigurationException(exc_bad_distance_function, SOURCE_INFO);
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::pairwiseDistance(const Array2D<T>& x,
    DistanceFunction distanceFunction, double param)
{
    Matrix dist;
    switch (distanceFunction) {
        case DistanceFunction::SquaredEuclideanDistance:
            dist = pairwiseSquaredEuclideanDistance(x);
            break;
        case DistanceFunction::EuclideanDistance:
            dist = pairwiseEuclideanDistance(x);
            break;
        case DistanceFunction::MinkowskiDistance:
            dist = pairwiseMinkowskiDistance(x, param);
            break;
        case DistanceFunction::CityBlockDistance:
            dist = pairwiseCityBlockDistance(x);
            break;
        case DistanceFunction::ChebychevDistance:
            dist = pairwiseChebychevDistance(x);
            break;    
        case DistanceFunction::MinDistance:
            dist = pairwiseMinDistance(x);
            break;    
        case DistanceFunction::CosineDistance:
            dist = pairwiseCosineDistance(x);
            break;
        case DistanceFunction::CorrelationDistance:
            dist = pairwiseCorrelationDistance(x);
            break;
        case DistanceFunction::SpearmanDistance:
            dist = pairwiseSpearmanDistance(x);
            break;
        case DistanceFunction::JaccardDistance:
            dist = pairwiseJaccardDistance(x);
            break;
        case DistanceFunction::HammingDistance:
            dist = pairwiseHammingDistance(x);
            break;        
        default:
            throw ConfigurationException(exc_bad_distance_function, SOURCE_INFO);
    }

    return dist;
}

//=================================================================================================================
//        DISTANCE TRANSFORMS FOR 2D ARRAYS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::distanceTransform(const Array2D<T>& x, 
    DistanceFunction distanceFunction, double param)
{
    auto nr = x.rows();
    auto nc = x.columns();
    auto nt = nr*nc;

    // Find non-null elements in x.
    size_t c = 0;
    for (index_t i=0; i<nt; i++)
        c += (x[i]!=0);
    
    Matrix ind(c, 2);
    c = 0;
    for (index_t i=0; i<nr; i++) {
        for (index_t j=0; j<nc; j++) {
            if (x(i,j) != 0) {
                ind(c,0) = static_cast<double>(i);
                ind(c,1) = static_cast<double>(j);
                c++;
            }
        }
    }

    // Calculate transform.
    Matrix xd(nr, nc, PLUS_INF);
    double d = 0;

    switch (distanceFunction) {
        case DistanceFunction::SquaredEuclideanDistance:
            for (index_t i=0; i<nr; i++) {
                for (index_t j=0; j<nc; j++) {
                    for (index_t k=0; k<c; k++) {
                        d = math::sqr(i - ind(k,0)) + math::sqr(j - ind(k,1));
                        xd(i,j) = math::min(d, xd(i,j));
                    }
                }
            }
            break;

        case DistanceFunction::EuclideanDistance:
            for (index_t i=0; i<nr; i++) {
                for (index_t j=0; j<nc; j++) {
                    for (index_t k=0; k<c; k++) {
                        d = math::sqr(i - ind(k,0)) + math::sqr(j - ind(k,1));
                        xd(i,j) = math::min(d, xd(i,j));
                    }
                    xd(i,j) = std::sqrt(xd(i,j));
                }
            }
            break;

        case DistanceFunction::MinkowskiDistance:
            for (index_t i=0; i<nr; i++) {
                for (index_t j=0; j<nc; j++) {
                    for (index_t k=0; k<c; k++) {
                        d = std::pow(std::abs(static_cast<double>(i)-static_cast<double>(ind(k, 0))), param) +
                            std::pow(std::abs(static_cast<double>(j)-static_cast<double>(ind(k, 1))), param);
                        xd(i,j) = math::min(d, xd(i,j));
                    }
                    xd(i,j) = std::pow(xd(i,j), 1./param);
                }
            }
            break;

        case DistanceFunction::CityBlockDistance:
            for (index_t i=0; i<nr; i++) {
                for (index_t j=0; j<nc; j++) {
                    for (index_t k=0; k<c; k++) {
                        d = std::abs(i - ind(k,0)) + std::abs(j - ind(k,1));
                        xd(i,j) = math::min(d, xd(i,j));
                    }                    
                }
            }
            break;

        case DistanceFunction::ChebychevDistance:
            for (index_t i=0; i<nr; i++) {
                for (index_t j=0; j<nc; j++) {
                    for (index_t k=0; k<c; k++) {
                        d = math::max(std::abs(i - ind(k, 0)), std::abs(j - ind(k, 1)));
                        xd(i,j) = math::min(d, xd(i,j));
                    }                    
                }
            }
            break;    

        case DistanceFunction::MinDistance:
            for (index_t i=0; i<nr; i++) {
                for (index_t j=0; j<nc; j++) {
                    for (index_t k=0; k<c; k++) {
                        d = math::min(std::abs(i - ind(k, 0)), std::abs(j - ind(k, 1)));
                        xd(i,j) = math::min(d, xd(i,j));
                    }                    
                }
            }
            break;    

        default:
            throw ConfigurationException(exc_bad_distance_function, SOURCE_INFO);
    }

    return xd;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::sampledFunctionDT(const Array2D<T>& x,
    DistanceFunction distanceFunction, double param)
{
    auto nr = x.rows();
    auto nc = x.columns();

    // Calculate transform.
    Matrix xd(nr, nc, PLUS_INF);
    double d = 0;

    switch (distanceFunction) {
        case DistanceFunction::SquaredEuclideanDistance:
            for (index_t i=0; i<nr; i++) {
                for (index_t j=0; j<nc; j++) {
                    for (index_t i2=0; i2<nr; i2++) {
                        for (index_t j2=0; j2<nc; j2++) {
                            d = math::sqr(static_cast<double>(i) - static_cast<double>(i2)) + 
                                math::sqr(static_cast<double>(j) - static_cast<double>(j2)) + 
                                x(i2,j2);
                            xd(i,j) = math::min(d, xd(i,j));
                        }
                    }                    
                }
            }
            break;

        case DistanceFunction::EuclideanDistance:
            for (index_t i=0; i<nr; i++) {
                for (index_t j=0; j<nc; j++) {
                    for (index_t i2=0; i2<nr; i2++) {
                        for (index_t j2=0; j2<nc; j2++) {
                            d = std::sqrt( math::sqr(static_cast<double>(i) - static_cast<double>(i2))
                                    + math::sqr(static_cast<double>(j) - static_cast<double>(j2)) ) +
                                x(i2,j2);
                            xd(i,j) = math::min(d, xd(i,j));
                        }
                    }                    
                }
            }
            break;

        case DistanceFunction::MinkowskiDistance:
            for (index_t i=0; i<nr; i++) {
                for (index_t j=0; j<nc; j++) {
                    for (index_t i2=0; i2<nr; i2++) {
                        for (index_t j2=0; j2<nc; j2++) {
                            d = std::pow(std::pow(std::abs(
                                static_cast<double>(i)-static_cast<double>(i2)), param) +
                                std::pow(std::abs(static_cast<double>(j)-static_cast<double>(j2)), param),
                                    1./param) +
                                x(i2,j2);
                            xd(i,j) = math::min(d, xd(i,j));
                        }
                    }
                }
            }
            break;

        case DistanceFunction::CityBlockDistance:
            for (index_t i=0; i<nr; i++) {
                for (index_t j=0; j<nc; j++) {
                    for (index_t i2=0; i2<nr; i2++) {
                        for (index_t j2=0; j2<nc; j2++) {
                            d = std::abs(static_cast<double>(i)-static_cast<double>(i2)) +
                                std::abs(static_cast<double>(j)-static_cast<double>(j2)) +
                                x(i2,j2);
                            xd(i,j) = math::min(d, xd(i,j));
                        }
                    }    
                }
            }
            break;

        case DistanceFunction::ChebychevDistance:
            for (index_t i=0; i<nr; i++) {
                for (index_t j=0; j<nc; j++) {
                    for (index_t i2=0; i2<nr; i2++) {
                        for (index_t j2=0; j2<nc; j2++) {
                            d = math::max(std::abs(static_cast<double>(i)-static_cast<double>(i2)),
                                std::abs(static_cast<double>(j)-static_cast<double>(j2))) +
                                x(i2,j2);
                            xd(i,j) = math::min(d, xd(i,j));
                        }
                    }    
                }
            }            
            break;    

        case DistanceFunction::MinDistance:
            for (index_t i=0; i<nr; i++) {
                for (index_t j=0; j<nc; j++) {
                    for (index_t i2=0; i2<nr; i2++) {
                        for (index_t j2=0; j2<nc; j2++) {
                            d = math::min(std::abs(static_cast<double>(i)-static_cast<double>(i2)),
                                std::abs(static_cast<double>(j)-static_cast<double>(j2))) +
                                x(i2,j2);
                            xd(i,j) = math::min(d, xd(i,j));
                        }
                    }    
                }
            }                    
            break;    

        default:
            throw ConfigurationException(exc_bad_distance_function, SOURCE_INFO);
    }

    return xd;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::fastSquaredEuclideanDT(const Array2D<T>& x)
{
    auto nr = x.rows();
    auto nc = x.columns();
    auto nt = nr*nc;

    if ( (nr<2) || (nc<2) )
        throw ArgumentException("x", exc_array_with_less_than_two_rows_and_two_columns,    SOURCE_INFO);
    
    // Transform input array in a sampled-function representation.
    Matrix sampFunc(nr, nc);

    for (index_t i=0; i<nt; i++) {
        if (!x[i])
            sampFunc[i] = PLUS_INF;
        else
            sampFunc[i] = 0;
    }

    return fastSquaredEuclideanSFDT(sampFunc);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::fastSquaredEuclideanSFDT(const Array2D<T>& x)
{
    auto nr = x.rows();
    auto nc = x.columns();

    if ( (nr<2) || (nc<2) )
        throw ArgumentException("x", exc_array_with_less_than_two_rows_and_two_columns,    
        SOURCE_INFO);
    
    // 1-D transform of each row.
    RealVector z(nc + 1);
    Array<size_t> v(nc);    
    Matrix xr(nr, nc, PLUS_INF);

    for (index_t r = 0; r<nr; r++) {
        double s = 0;
        size_t k = 0; 
        z[0] = MINUS_INF;
        z[1] = PLUS_INF;
        v[0] = 0;

        // Compute lower envelope.
        for (index_t q = 1; q<nc; q++) {        
            s = ((static_cast<double>(x(r, q)) + q*q) - 
                 (static_cast<double>(x(r, v[k])) + v[k]*v[k])) / (2.*q - 2.*v[k]);
            
            while (s <= z[k]) {
                k--;
                s = ((static_cast<double>(x(r, q)) + q*q) - 
                     (static_cast<double>(x(r, v[k])) + v[k]*v[k])) / (2.*q - 2.*v[k]);
            }                

            k++;
            v[k] = q;
            z[k] = s;
            z[k+1] = PLUS_INF;

        }

        // Fill in values of distance transform.
        k = 0; 
        for (index_t q = 0; q<nc; q++) {
            while (z[k+1] < q)
                k++;
            xr(r, q) = math::sqr(static_cast<double>(q) - static_cast<double>(v[k])) + x(r, v[k]);
        }
    }
    

    // 1-D transform of each column.
    Matrix xd(nr, nc, PLUS_INF);

    v.assign(nr, 0);
    z.assign(nr+1, 0);
    
    for (index_t c = 0; c<nc; c++) {
        double s = 0;
        size_t k = 0;
        z[0] = MINUS_INF;
        z[1] = PLUS_INF;
        v[0] = 0;

        // Compute lower envelope.
        for (index_t q = 1; q<nr; q++) {
            s = ((xr(q, c) + q*q) - (xr(v[k], c) + v[k]*v[k])) / (2.*q - 2.*v[k]);
            
            while (s <= z[k]) {
                k--;
                s = ((xr(q, c) + q*q) - (xr(v[k], c) + v[k]*v[k])) / (2.*q - 2.*v[k]);
            }        

            k++;
            v[k] = q;
            z[k] = s;
            z[k+1] = PLUS_INF;
        }

        // Fill in values of distance transform.
        k = 0; 
        for (index_t q = 0; q<nr; q++) {
            while (z[k+1] < q)
                k++;
            xd(q, c) = math::sqr(static_cast<double>(q) - static_cast<double>(v[k])) + xr(v[k], c);
        }
    }

    return xd;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::fastCityBlockDT(const Array2D<T>& x)
{
    auto nr = x.rows();
    auto nc = x.columns();
    auto nt = nr*nc;

    if ( (nr<2) || (nc<2) )
        throw ArgumentException("x", exc_array_with_less_than_two_rows_and_two_columns, 
        SOURCE_INFO);
    
    // Transform input array in a sampled-function representation.
    Matrix sampFunc(nr, nc);

    for (index_t i=0; i<nt; i++) {
        if (!x[i])
            sampFunc[i] = PLUS_INF;
        else
            sampFunc[i] = 0;
    }

    return fastCityBlockSFDT(sampFunc);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::fastCityBlockSFDT(const Array2D<T>& x)
{
    auto nr = x.rows();
    auto nc = x.columns();
    auto nt = nr*nc;

    if ( (nr<2) || (nc<2) )
        throw ArgumentException("x", exc_array_with_less_than_two_rows_and_two_columns,    
        SOURCE_INFO);
    
    Matrix xd(nr, nc);
    for (index_t i=0; i<nt; i++)
        xd[i] = static_cast<double>(x[i]);

    // 1-D transform of each row.
    for (index_t r = 0; r<nr; r++) {
        for (int q = 1; q < static_cast<int>(nc); q++)
            xd(r, q) = math::min(xd(r, q), xd(r, q-1) + 1);

        for (int q = (static_cast<int>(nc) - 2); q >= 0; q--)
            xd(r, q) = math::min(xd(r, q), xd(r, q+1) + 1);
    }
    
    // 1-D transform of each column.
    for (index_t c = 0; c<nc; c++) {
        for (int q = 1; q < static_cast<int>(nr); q++)
            xd(q, c) = math::min(xd(q, c), xd(q-1, c) + 1);

        for (int q = (static_cast<int>(nr) - 2); q >= 0; q--)
            xd(q, c) = math::min(xd(q, c), xd(q+1, c) + 1);
    }

    return xd;
}

//=================================================================================================================
//        DISTANCE TRANSFORMS FOR 3D ARRAYS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Array3D<double> nct::statistics::distance_metrics::distanceTransform(const Array3D<T>& x,
    DistanceFunction distanceFunction, double param)
{
    auto nd1 = x.dimension1();
    auto nd2 = x.dimension2();
    auto nd3 = x.dimension3();
    auto nt = nd1*nd2*nd3;

    // Find non-null elements in x.
    size_t c = 0;
    for (index_t i=0; i<nt; i++)
        c += (x[i]!=0);
    
    Matrix ind(c, 3);
    c = 0;
    for (index_t i=0; i<nd1; i++) {
        for (index_t j=0; j<nd2; j++) {
            for (index_t k=0; k<nd3; k++) {
                if (x(i,j,k) != 0) {
                    ind(c,0) = static_cast<double>(i);
                    ind(c,1) = static_cast<double>(j);
                    ind(c,2) = static_cast<double>(k);
                    c++;
                }
            }
        }
    }

    // Calculate transform.
    Array3D<double> xd(nd1, nd2, nd3, PLUS_INF);
    double d = 0;

    switch (distanceFunction) {
        case DistanceFunction::SquaredEuclideanDistance:
            for (index_t i=0; i<nd1; i++) {
                for (index_t j=0; j<nd2; j++) {
                    for (index_t k=0; k<nd3; k++) {
                        for (index_t l=0; l<c; l++) {
                            d = math::sqr(i - ind(l,0)) + math::sqr(j - ind(l,1)) + math::sqr(k - ind(l,2));
                            xd(i,j,k) = math::min(d, xd(i,j,k));
                        }
                    }
                }
            }
            break;

        case DistanceFunction::EuclideanDistance:
            for (index_t i=0; i<nd1; i++) {
                for (index_t j=0; j<nd2; j++) {
                    for (index_t k=0; k<nd3; k++) {
                        for (index_t l=0; l<c; l++) {
                            d = math::sqr(i - ind(l,0)) + math::sqr(j - ind(l,1)) + math::sqr(k - ind(l,2));
                            xd(i,j,k) = math::min(d, xd(i,j,k));
                        }
                        xd(i,j,k) = std::sqrt(xd(i,j,k));
                    }
                }
            }
            break;

        case DistanceFunction::MinkowskiDistance:
            for (index_t i=0; i<nd1; i++) {
                for (index_t j=0; j<nd2; j++) {
                    for (index_t k=0; k<nd3; k++) {
                        for (index_t l=0; l<c; l++) {
                            d = std::pow(std::abs(static_cast<double>(i)-static_cast<double>(ind(l, 0))),
                                param) +
                                std::pow(std::abs(static_cast<double>(j)-static_cast<double>(ind(l, 1))),
                                param) +
                                std::pow(std::abs(static_cast<double>(k)-static_cast<double>(ind(l, 2))), 
                                param);
                            xd(i,j,k) = math::min(d, xd(i,j,k));
                        }
                        xd(i,j,k) = std::pow(xd(i,j,k), 1./param);
                    }
                }
            }
            break;

        case DistanceFunction::CityBlockDistance:
            for (index_t i=0; i<nd1; i++) {
                for (index_t j=0; j<nd2; j++) {
                    for (index_t k=0; k<nd3; k++) {
                        for (index_t l=0; l<c; l++) {
                            d = std::abs(i - ind(l,0)) + std::abs(j - ind(l,1)) + std::abs(k - ind(l,2));
                            xd(i,j,k) = math::min(d, xd(i,j,k));
                        }
                    }                    
                }
            }
            break;

        case DistanceFunction::ChebychevDistance:
            for (index_t i=0; i<nd1; i++) {
                for (index_t j=0; j<nd2; j++) {
                    for (index_t k=0; k<nd3; k++) {
                        for (index_t l=0; l<c; l++) {
                            d = math::max(std::abs(i - ind(l, 0)), std::abs(j - ind(l, 1)), 
                                std::abs(k - ind(l, 2)));
                            xd(i,j,k) = math::min(d, xd(i,j,k));
                        }
                    }                    
                }
            }
            break;    

        case DistanceFunction::MinDistance:
            for (index_t i=0; i<nd1; i++) {
                for (index_t j=0; j<nd2; j++) {
                    for (index_t k=0; k<nd3; k++) {
                        for (index_t l=0; l<c; l++) {
                            d = math::min(std::abs(i - ind(l, 0)), std::abs(j - ind(l, 1)),
                                std::abs(k - ind(l, 2)));
                            xd(i,j,k) = math::min(d, xd(i,j,k));
                        }
                    }                    
                }
            }
            break;    

        default:
            throw ConfigurationException(exc_bad_distance_function, SOURCE_INFO);
    }

    return xd;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Array3D<double> nct::statistics::distance_metrics::sampledFunctionDT(
    const Array3D<T>& x, DistanceFunction distanceFunction, double param)
{
    auto nd1 = x.dimension1();
    auto nd2 = x.dimension2();
    auto nd3 = x.dimension3();

    // Calculate transform.
    Array3D<double> xd(nd1, nd2, nd3, PLUS_INF);
    double d = 0;

    switch (distanceFunction) {
        case DistanceFunction::SquaredEuclideanDistance:
            for (index_t i=0; i<nd1; i++) {
                for (index_t j=0; j<nd2; j++) {
                    for (index_t k=0; k<nd3; k++) {
                        for (index_t i2=0; i2<nd1; i2++) {
                            for (index_t j2=0; j2<nd2; j2++) {
                                for (index_t k2=0; k2<nd3; k2++) {
                                    d = math::sqr(static_cast<double>(i) - static_cast<double>(i2)) + 
                                        math::sqr(static_cast<double>(j) - static_cast<double>(j2)) + 
                                        math::sqr(static_cast<double>(k) - static_cast<double>(k2)) +
                                        x(i2,j2,k2);
                                    xd(i,j,k) = math::min(d, xd(i,j,k));
                                }
                            }
                        }        
                    }
                }
            }
            break;

        case DistanceFunction::EuclideanDistance:
            for (index_t i=0; i<nd1; i++) {
                for (index_t j=0; j<nd2; j++) {
                    for (index_t k=0; k<nd3; k++) {
                        for (index_t i2=0; i2<nd1; i2++) {
                            for (index_t j2=0; j2<nd2; j2++) {
                                for (index_t k2=0; k2<nd3; k2++) {
                                    d = std::sqrt( math::sqr(static_cast<double>(i) - static_cast<double>(i2)) + 
                                              math::sqr(static_cast<double>(j) - static_cast<double>(j2)) +
                                              math::sqr(static_cast<double>(k) - static_cast<double>(k2)) ) +
                                        x(i2,j2,k2);
                                    xd(i,j,k) = math::min(d, xd(i,j,k));
                                }
                            }
                        }
                    }                    
                }
            }
            break;

        case DistanceFunction::MinkowskiDistance:
            for (index_t i=0; i<nd1; i++) {
                for (index_t j=0; j<nd2; j++) {
                    for (index_t k=0; k<nd3; k++) {
                        for (index_t i2=0; i2<nd1; i2++) {
                            for (index_t j2=0; j2<nd2; j2++) {
                                for (index_t k2=0; k2<nd3; k2++) {
                                    d = std::pow(std::pow(std::abs(static_cast<double>(i)-
                                        static_cast<double>(i2)), param) +
                                        std::pow(std::abs(static_cast<double>(j)-
                                        static_cast<double>(j2)), param) +
                                        std::pow(std::abs(static_cast<double>(k)-
                                        static_cast<double>(k2)), param), 1./param) +
                                        x(i2,j2,k2);
                                    xd(i,j,k) = math::min(d, xd(i,j,k));
                                }
                            }
                        }
                    }
                }
            }
            break;

        case DistanceFunction::CityBlockDistance:
            for (index_t i=0; i<nd1; i++) {
                for (index_t j=0; j<nd2; j++) {
                    for (index_t k=0; k<nd3; k++) {
                        for (index_t i2=0; i2<nd1; i2++) {
                            for (index_t j2=0; j2<nd2; j2++) {
                                for (index_t k2=0; k2<nd3; k2++) {
                                    d = std::abs(static_cast<double>(i)-static_cast<double>(i2)) +
                                        std::abs(static_cast<double>(j)-static_cast<double>(j2)) +
                                        std::abs(static_cast<double>(k)-static_cast<double>(k2)) +
                                        x(i2,j2,k2);
                                    xd(i,j,k) = math::min(d, xd(i,j,k));
                                }
                            }
                        }
                    }    
                }
            }
            break;

        case DistanceFunction::ChebychevDistance:
            for (index_t i=0; i<nd1; i++) {
                for (index_t j=0; j<nd2; j++) {
                    for (index_t k=0; k<nd3; k++) {
                        for (index_t i2=0; i2<nd1; i2++) {
                            for (index_t j2=0; j2<nd2; j2++) {
                                for (index_t k2=0; k2<nd3; k2++) {
                                    d = math::max(std::abs(static_cast<double>(i)-static_cast<double>(i2)),
                                        std::abs(static_cast<double>(j)-static_cast<double>(j2)),
                                        std::abs(static_cast<double>(k)-static_cast<double>(k2))) +
                                        x(i2,j2,k2);
                                    xd(i,j,k) = math::min(d, xd(i,j,k));
                                }
                            }
                        }
                    }    
                }
            }            
            break;    

        case DistanceFunction::MinDistance:
            for (index_t i=0; i<nd1; i++) {
                for (index_t j=0; j<nd2; j++) {
                    for (index_t k=0; k<nd3; k++) {
                        for (index_t i2=0; i2<nd1; i2++) {
                            for (index_t j2=0; j2<nd2; j2++) {
                                for (index_t k2=0; k2<nd3; k2++) {
                                    d = math::min(std::abs(static_cast<double>(i)-static_cast<double>(i2)),
                                        std::abs(static_cast<double>(j)-static_cast<double>(j2)),
                                        std::abs(static_cast<double>(k)-static_cast<double>(k2))) +
                                        x(i2,j2,k2);
                                    xd(i,j,k) = math::min(d, xd(i,j,k));
                                }
                            }
                        }
                    }    
                }
            }                    
            break;    

        default:
            throw ConfigurationException(exc_bad_distance_function, SOURCE_INFO);
    }

    return xd;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Array3D<double> nct::statistics::distance_metrics::fastSquaredEuclideanDT(const Array3D<T>& x)
{
    auto nd1 = x.dimension1();
    auto nd2 = x.dimension2();
    auto nd3 = x.dimension3();
    auto nt = nd1*nd2*nd3;

    if ( (nd1<2) || (nd2<2) || (nd3<2) )
        throw ArgumentException("x", exc_array_dimensions_are_lower_than_two, SOURCE_INFO);
    
    // Transform input array in a sampled-function representation.
    Array3D<double> sampFunc(nd1, nd2, nd3);

    for (index_t i=0; i<nt; i++) {
        if (!x[i])
            sampFunc[i] = PLUS_INF;
        else
            sampFunc[i] = 0;
    }

    return fastSquaredEuclideanSFDT(sampFunc);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Array3D<double> nct::statistics::distance_metrics::fastSquaredEuclideanSFDT(const Array3D<T>& x)
{
    auto nd1 = x.dimension1();
    auto nd2 = x.dimension2();
    auto nd3 = x.dimension3();

    if ( (nd1<2) || (nd2<2) || (nd3<2) )
        throw ArgumentException("x", exc_array_dimensions_are_lower_than_two, SOURCE_INFO);
    
    // 1-D transform of each row.
    RealVector z(nd3 + 1);
    Array<size_t> v(nd3);
    Array3D<double> xr(nd1, nd2, nd3, PLUS_INF);

    for (index_t d = 0; d<nd1; d++) {
        for (index_t r = 0; r<nd2; r++) {
            double s = 0;
            size_t k = 0;
            z[0] = MINUS_INF;
            z[1] = PLUS_INF;
            v[0] = 0;

            // Compute lower envelope.
            for (index_t q = 1; q<nd3; q++) {        
                s = ((static_cast<double>(x(d, r, q)) + q*q) - 
                     (static_cast<double>(x(d, r, v[k])) + v[k]*v[k])) / (2.*q - 2.*v[k]);
            
                while (s <= z[k]) {
                    k--;
                    s = ((static_cast<double>(x(d, r, q)) + q*q) - 
                         (static_cast<double>(x(d, r, v[k])) + v[k]*v[k])) / (2.*q - 2.*v[k]);
                }                

                k++;
                v[k] = q;
                z[k] = s;
                z[k+1] = PLUS_INF;

            }

            // Fill in values of distance transform.
            k = 0; 
            for (index_t q = 0; q<nd3; q++) {
                while (z[k+1] < q)
                    k++;
                xr(d, r, q) = math::sqr(static_cast<double>(q) - static_cast<double>(v[k])) + x(d, r, v[k]);
            }
        }
    }

    // 1-D transform of each column.
    Array3D<double> xc(nd1, nd2, nd3, PLUS_INF);

    v.assign(nd2, 0);
    z.assign(nd2+1, 0);
    
    for (index_t d = 0; d<nd1; d++) {
        for (index_t c = 0; c<nd3; c++) {
            double s = 0;
            size_t k = 0;
            z[0] = MINUS_INF;
            z[1] = PLUS_INF;
            v[0] = 0;

            // Compute lower envelope.
            for (index_t q = 1; q<nd2; q++) {
                s = ((xr(d, q, c) + q*q) - (xr(d, v[k], c) + v[k]*v[k])) / (2.*q - 2.*v[k]);
            
                while (s <= z[k]) {
                    k--;
                    s = ((xr(d, q, c) + q*q) - (xr(d, v[k], c) + v[k]*v[k])) / (2.*q - 2.*v[k]);
                }        

                k++;
                v[k] = q;
                z[k] = s;
                z[k+1] = PLUS_INF;
            }

            // Fill in values of distance transform.
            k = 0; 
            for (index_t q = 0; q<nd2; q++) {
                while (z[k+1] < q)
                    k++;
                xc(d, q, c) = math::sqr(static_cast<double>(q) - static_cast<double>(v[k])) + xr(d, v[k], c);
            }
        }
    }

    // 1-D transform of each sub-array.
    Array3D<double> xd(nd1, nd2, nd3, PLUS_INF);

    v.assign(nd1, 0);
    z.assign(nd1+1, 0);
    
    for (index_t r = 0; r<nd1; r++) {
        for (index_t c = 0; c<nd3; c++) {
            double s = 0;
            size_t k = 0;
            z[0] = MINUS_INF;
            z[1] = PLUS_INF;
            v[0] = 0;

            // Compute lower envelope.
            for (index_t q = 1; q<nd1; q++) {
                s = ((xc(q, r, c) + q*q) - (xc(v[k], r, c) + v[k]*v[k])) / (2.*q - 2.*v[k]);
            
                while (s <= z[k]) {
                    k--;
                    s = ((xc(q, r, c) + q*q) - (xc(v[k], r, c) + v[k]*v[k])) / (2.*q - 2.*v[k]);
                }        

                k++;
                v[k] = q;
                z[k] = s;
                z[k+1] = PLUS_INF;
            }

            // Fill in values of distance transform.
            k = 0; 
            for (index_t q = 0; q<nd1; q++) {
                while (z[k+1] < q)
                    k++;
                xd(q, r, c) = math::sqr(static_cast<double>(q) - static_cast<double>(v[k])) + xc(v[k], r, c);
            }
        }
    }

    return xd;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Array3D<double> nct::statistics::distance_metrics::fastCityBlockDT(const Array3D<T>& x)
{
    auto nd1 = x.dimension1();
    auto nd2 = x.dimension2();
    auto nd3 = x.dimension3();
    auto nt = nd1*nd2*nd3;

    if ( (nd1<2) || (nd2<2) || (nd3<2) )
        throw ArgumentException("x", exc_array_dimensions_are_lower_than_two, SOURCE_INFO);
    
    // Transform input array in a sampled-function representation.
    Array3D<double> sampFunc(nd1, nd2, nd3);

    for (index_t i=0; i<nt; i++) {
        if (!x[i])
            sampFunc[i] = PLUS_INF;
        else
            sampFunc[i] = 0;
    }

    return fastCityBlockSFDT(sampFunc);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Array3D<double> nct::statistics::distance_metrics::fastCityBlockSFDT(const Array3D<T>& x)
{
    auto nd1 = x.dimension1();
    auto nd2 = x.dimension2();
    auto nd3 = x.dimension3();
    auto nt = nd1*nd2*nd3;

    if ( (nd1<2) || (nd2<2) || (nd3<2) )
        throw ArgumentException("x", exc_array_dimensions_are_lower_than_two, SOURCE_INFO);
    
    Array3D<double> xd(nd1, nd2, nd3);
    for (index_t i=0; i<nt; i++)
        xd[i] = static_cast<double>(x[i]);

    // 1-D transform of each row.
    for (index_t d = 0; d<nd1; d++) {
        for (index_t r = 0; r<nd2; r++) {
            for (int q = 1; q < static_cast<int>(nd3); q++)
                xd(d, r, q) = math::min(xd(d, r, q), xd(d, r, q-1) + 1);

            for (int q = (static_cast<int>(nd3) - 2); q >= 0; q--)
                xd(d, r, q) = math::min(xd(d, r, q), xd(d, r, q+1) + 1);
        }
    }

    // 1-D transform of each column.
    for (index_t d = 0; d<nd1; d++) {
        for (index_t c = 0; c<nd3; c++) {
            for (int q = 1; q < static_cast<int>(nd2); q++)
                xd(d, q, c) = math::min(xd(d, q, c), xd(d, q-1, c) + 1);

            for (int q = (static_cast<int>(nd2) - 2); q >= 0; q--)
                xd(d, q, c) = math::min(xd(d, q, c), xd(d, q+1, c) + 1);
        }
    }

    // 1-D transform of each sub-array.
    for (index_t r = 0; r<nd2; r++) {
        for (index_t c = 0; c<nd3; c++) {
            for (int q = 1; q < static_cast<int>(nd1); q++)
                xd(q, r, c) = math::min(xd(q, r, c), xd(q-1, r, c) + 1);

            for (int q = (static_cast<int>(nd1) - 2); q >= 0; q--)
                xd(q, r, c) = math::min(xd(q, r, c), xd(q+1, r, c) + 1);
        }
    }

    return xd;
}

//=================================================================================================================
//        DISTANCE FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::distance_metrics::squaredEuclideanDistance(InputIt xFirst, InputIt xLast,
    InputIt yFirst, InputIt yLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    

    if ((yLast - yFirst)!=(xLast - xFirst))
        throw ArgumentException("xLast, xFirst, yFirst, yLast", exc_two_ranges_of_different_sizes, SOURCE_INFO);
        
    double r = 0;
    for (InputIt x=xFirst, y=yFirst; x!=xLast && y!=yLast; ++x, ++y)
        r += math::sqr(*x - *y);

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::RealVector nct::statistics::distance_metrics::squaredEuclideanDistance(
    const Array<T>& xt, const Array2D<T>& x)
{
    auto d = xt.size();
    auto n = x.rows();

    if (d == 0)
        throw EmptyArrayException("xt", SOURCE_INFO);

    if (x.rows() < 1)
        throw ArgumentException("x", exc_data_with_less_than_one_observation, SOURCE_INFO);

    if (x.columns() != d)
        throw ArgumentException("x, xt", exc_objects_with_different_number_of_variables, SOURCE_INFO);

    RealVector dist(n, 0);
    for (index_t i = 0; i<n; i++) {
        for (index_t k = 0; k<d; k++)
            dist[i] += math::sqr(xt[k] - x(i,k));    
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::pairwiseSquaredEuclideanDistance(const Array2D<T>& x)
{
    if (x.columns() < 1 || x.rows() < 2)
        throw ArgumentException("x", exc_bad_array_dimensions, SOURCE_INFO);

    auto n = x.rows();
    auto d = x.columns();
    Matrix dist(n, n);
    
    for (index_t i = 0; i<n; i++) {
        dist(i,i) = 0;
        for (auto j = (i+1); j<n; j++) {
            dist(i,j) = 0;
            for (index_t k = 0; k<d; k++)
                dist(i,j) += math::sqr(x(i,k) - x(j,k));        
            dist(j,i) = dist(i,j);
        }
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::distance_metrics::euclideanDistance(InputIt xFirst, InputIt xLast,
    InputIt yFirst, InputIt yLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range,  SOURCE_INFO);    

    if ((yLast - yFirst)!=(xLast - xFirst))
        throw ArgumentException("xLast, xFirst, yFirst, yLast", exc_two_ranges_of_different_sizes, SOURCE_INFO);
        
    double r = 0;
    for (InputIt x=xFirst, y=yFirst; x!=xLast && y!=yLast; ++x, ++y)
        r += math::sqr(*x - *y);

    return std::sqrt(r);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::RealVector nct::statistics::distance_metrics::euclideanDistance(const Array<T>& xt, const Array2D<T>& x)
{
    auto d = xt.size();
    auto n = x.rows();

    if (d == 0)
        throw EmptyArrayException("xt", SOURCE_INFO);

    if (x.rows() < 1)
        throw ArgumentException("x", exc_data_with_less_than_one_observation, SOURCE_INFO);

    if (x.columns() != d)
        throw ArgumentException("x, xt", exc_objects_with_different_number_of_variables, SOURCE_INFO);

    RealVector dist(n, 0);
    for (index_t i = 0; i<n; i++) {
        for (index_t k = 0; k<d; k++)
            dist[i] += (xt[k] - x(i,k))*(xt[k] - x(i,k));    
        dist[i] = std::sqrt(dist[i]);
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::pairwiseEuclideanDistance(const Array2D<T>& x)
{
    if (x.columns() < 1 || x.rows() < 2)
        throw ArgumentException("x", exc_bad_array_dimensions, SOURCE_INFO);

    auto n = x.rows();
    auto d = x.columns();
    Matrix dist(n, n);
    
    for (index_t i = 0; i<n; i++) {
        dist(i,i) = 0;
        for (auto j = (i+1); j<n; j++) {
            dist(i,j) = 0;
            for (index_t k = 0; k<d; k++)
                dist(i,j) += math::sqr(x(i,k) - x(j,k));        
            dist(i,j)=std::sqrt(dist(i,j));
            dist(j,i) = dist(i,j);
        }
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::distance_metrics::minkowskiDistance(InputIt xFirst, InputIt xLast,
    InputIt yFirst, InputIt yLast, double p)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    

    if (yFirst >= yLast)
        throw ArgumentException("yLast, yFirst", exc_empty_range, SOURCE_INFO);

    if ((yLast - yFirst)!=(xLast - xFirst))
        throw ArgumentException("xLast, xFirst, yFirst, yLast", exc_two_ranges_of_different_sizes, SOURCE_INFO);

    if (p<=0)
        throw ArgumentException("p", p, 0.0,RelationalOperator::GreaterThan, SOURCE_INFO);

    double r = 0;
    for (InputIt x=xFirst, y=yFirst; x!=xLast && y!=yLast; ++x, ++y)
        r += std::pow(std::abs(*x - *y), p);

    return std::pow(r,1./p);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::RealVector nct::statistics::distance_metrics::minkowskiDistance(
    const Array<T>& xt, const Array2D<T>& x, double p)
{
    auto d = xt.size();
    auto n = x.rows();

    if (d == 0)
        throw EmptyArrayException("xt", SOURCE_INFO);

    if (x.rows() < 1)
        throw ArgumentException("x", exc_data_with_less_than_one_observation, SOURCE_INFO);

    if (x.columns() != d)
        throw ArgumentException("x, xt", exc_objects_with_different_number_of_variables, SOURCE_INFO);

    if (p<=0)
        throw ArgumentException("p", p, 0.0,RelationalOperator::GreaterThan, SOURCE_INFO);

    RealVector dist(n, 0);
    for (index_t i = 0; i<n; i++) {
        for (index_t k = 0; k<d; k++)                    
            dist[i] += std::pow(std::abs(xt[k] - x(i, k)), p);
        dist[i] = std::pow(dist[i], 1.0/p);
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::pairwiseMinkowskiDistance(const Array2D<T>& x, double p)
{
    if (x.columns() < 1 || x.rows() < 2)
        throw ArgumentException("x", exc_bad_array_dimensions, SOURCE_INFO);

    if (p<=0)
        throw ArgumentException("p", p, 0.0,RelationalOperator::GreaterThan, SOURCE_INFO);

    auto n = x.rows();
    auto d = x.columns();
    Matrix dist(n, n);
    
    for (index_t i = 0; i<n; i++) {
        dist(i,i) = 0;
        for (auto j = (i+1); j<n; j++) {
            dist(i,j) = 0;
            for (index_t k = 0; k<d; k++)                    
                dist(i, j) += std::pow(std::abs(x(i, k) - x(j, k)), p);
            dist(i,j)=std::pow(dist(i,j), 1.0/p);
            dist(j,i) = dist(i,j);
        }
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::distance_metrics::cityBlockDistance(InputIt xFirst, InputIt xLast,
    InputIt yFirst, InputIt yLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    

    if (yFirst >= yLast)
        throw ArgumentException("yLast, yFirst", exc_empty_range, SOURCE_INFO);    

    if ((yLast - yFirst)!=(xLast - xFirst))
        throw ArgumentException("xLast, xFirst, yFirst, yLast", exc_two_ranges_of_different_sizes, SOURCE_INFO);
        
    double r = 0;
    for (InputIt x=xFirst, y=yFirst; x!=xLast && y!=yLast; ++x, ++y)
        r += std::abs(*x - *y);

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::RealVector nct::statistics::distance_metrics::cityBlockDistance(
    const Array<T>& xt, const Array2D<T>& x)
{
    auto d = xt.size();
    auto n = x.rows();

    if (d == 0)
        throw EmptyArrayException("xt", SOURCE_INFO);

    if (x.rows() < 1)
        throw ArgumentException("x", exc_data_with_less_than_one_observation, SOURCE_INFO);

    if (x.columns() != d)
        throw ArgumentException("x, xt", exc_objects_with_different_number_of_variables, SOURCE_INFO);

    RealVector dist(n, 0);
    for (index_t i = 0; i<n; i++) {
        for (index_t k = 0; k<d; k++)                    
            dist[i] += std::abs(xt[k] - x(i, k));
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::pairwiseCityBlockDistance(const Array2D<T>& x)
{
    if (x.columns() < 1 || x.rows() < 2)
        throw ArgumentException("x", exc_bad_array_dimensions, SOURCE_INFO);

    auto n = x.rows();
    auto d = x.columns();
    Matrix dist(n, n);
    
    for (index_t i = 0; i<n; i++) {
        dist(i,i) = 0;
        for (auto j = (i+1); j<n; j++) {
            dist(i,j) = 0;
            for (index_t k = 0; k<d; k++)                    
                dist(i, j) += std::abs(x(i, k) - x(j, k));
            dist(j,i) = dist(i,j);
        }
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::distance_metrics::chebychevDistance(InputIt xFirst, InputIt xLast, 
    InputIt yFirst, InputIt yLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    

    if (yFirst >= yLast)
        throw ArgumentException("yLast, yFirst", exc_empty_range, SOURCE_INFO);        

    if ((yLast - yFirst)!=(xLast - xFirst))
        throw ArgumentException("xLast, xFirst, yFirst, yLast", exc_two_ranges_of_different_sizes, SOURCE_INFO);
        
    double diff = 0;
    double r = std::abs(*xFirst - *yFirst);
    for (InputIt x=xFirst, y=yFirst; x!=xLast && y!=yLast; ++x, ++y) {
        diff = std::abs(*x - *y);
        if (diff > r)
            r = diff;
    }

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::RealVector nct::statistics::distance_metrics::chebychevDistance(const Array<T>& xt, 
    const Array2D<T>& x)
{
    auto d = xt.size();
    auto n = x.rows();

    if (d == 0)
        throw EmptyArrayException("xt", SOURCE_INFO);

    if (x.rows() < 1)
        throw ArgumentException("x", exc_data_with_less_than_one_observation, SOURCE_INFO);

    if (x.columns() != d)
        throw ArgumentException("x, xt", exc_objects_with_different_number_of_variables, SOURCE_INFO);

    RealVector dist(n, 0);
    for (index_t i = 0; i<n; i++) {
        double diff = 0;
        double maxDiff = std::abs(xt[0] - x(i, 0));
        for (index_t k = 1; k<d; k++) {
            diff = std::abs(xt[k] - x(i, k));
            if (diff>maxDiff)
                maxDiff = diff;
        }
        dist[i] = maxDiff;
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::pairwiseChebychevDistance(const Array2D<T>& x)
{
    if (x.columns() < 1 || x.rows() < 2)
        throw ArgumentException("x", exc_bad_array_dimensions, SOURCE_INFO);

    auto n = x.rows();
    auto d = x.columns();
    Matrix dist(n, n);
    
    for (index_t i = 0; i<n; i++) {
        dist(i,i) = 0;
        for (auto j = (i+1); j<n; j++) {
            double diff = 0;
            double maxDiff = std::abs(x(i, 0) - x(j, 0));
            for (index_t k = 1; k<d; k++) {
                diff = std::abs(x(i, k) - x(j, k));
                if (diff>maxDiff)
                    maxDiff = diff;
            }
            dist(i,j) = maxDiff;
            dist(j,i) = dist(i,j);
        }
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::distance_metrics::minDistance(InputIt xFirst, InputIt xLast, 
    InputIt yFirst, InputIt yLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    

    if (yFirst >= yLast)
        throw ArgumentException("yLast, yFirst", exc_empty_range, SOURCE_INFO);        

    if ((yLast - yFirst)!=(xLast - xFirst))
        throw ArgumentException("xLast, xFirst, yFirst, yLast", exc_two_ranges_of_different_sizes, SOURCE_INFO);
        
    double diff = 0;
    double r = std::abs(*xFirst - *yFirst);
    for (InputIt x=xFirst, y=yFirst; x!=xLast && y!=yLast; ++x, ++y) {
        diff = std::abs(*x - *y);
        if (diff < r)
            r = diff;
    }

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::RealVector nct::statistics::distance_metrics::minDistance(const Array<T>& xt, const Array2D<T>& x)
{
    auto d = xt.size();
    auto n = x.rows();

    if (d == 0)
        throw EmptyArrayException("xt", SOURCE_INFO);

    if (x.rows() < 1)
        throw ArgumentException("x", exc_data_with_less_than_one_observation, SOURCE_INFO);

    if (x.columns() != d)
        throw ArgumentException("x, xt", exc_objects_with_different_number_of_variables, SOURCE_INFO);

    RealVector dist(n, 0);
    for (index_t i = 0; i<n; i++) {
        double diff = 0;
        double minDiff = std::abs(xt[0] - x(i, 0));
        for (index_t k = 1; k<d; k++) {
            diff = std::abs(xt[k] - x(i, k));
            if (diff<minDiff)
                minDiff = diff;
        }
        dist[i] = minDiff;
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::pairwiseMinDistance(const Array2D<T>& x)
{
    if (x.columns() < 1 || x.rows() < 2)
        throw ArgumentException("x", exc_bad_array_dimensions, SOURCE_INFO);

    auto n = x.rows();
    auto d = x.columns();
    Matrix dist(n, n);
    
    for (index_t i = 0; i<n; i++) {
        dist(i,i) = 0;
        for (auto j = (i+1); j<n; j++) {
            double diff = 0;
            double minDiff = std::abs(x(i, 0) - x(j, 0));
            for (index_t k = 1; k<d; k++) {
                diff = std::abs(x(i, k) - x(j, k));
                if (diff<minDiff)
                    minDiff = diff;
            }
            dist(i,j) = minDiff;
            dist(j,i) = dist(i,j);
        }
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::distance_metrics::bhattacharrayDistance(InputIt f1First, InputIt f1Last, 
    InputIt f2First, InputIt f2Last)
{
    if (f1First >= f1Last)
        throw ArgumentException("f1Last, f1First", exc_empty_range, SOURCE_INFO);    
    
    if (f2First >= f2Last)
        throw ArgumentException("f2First, f2Last", exc_empty_range, SOURCE_INFO);    

    double d = 0;
    for (InputIt f1=f1First, f2=f2First; f1!=f1Last && f2!=f2Last; ++f1, ++f2) {
        if ( ((*f1) < 0) || ((*f1) > 1) )
            throw ArgumentException("f1Last, f1First",exc_values_outside_bounds, SOURCE_INFO);    

        if ( ((*f2) < 0) || ((*f2) > 1) )
            throw ArgumentException("f2Last, f2First",exc_values_outside_bounds, SOURCE_INFO);    

        d += std::sqrt((*f1)*(*f2));
    }
    
    return -log(d);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::distance_metrics::cosineDistance(InputIt xFirst, InputIt xLast, 
    InputIt yFirst, InputIt yLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    

    if (yFirst >= yLast)
        throw ArgumentException("yLast, yFirst", exc_empty_range, SOURCE_INFO);    

    if ((yLast - yFirst)!=(xLast - xFirst))
        throw ArgumentException("xLast, xFirst, yFirst, yLast", exc_two_ranges_of_different_sizes, SOURCE_INFO);
        
    double xy = 0;
    double xx = 0;
    double yy = 0;
    for (InputIt x=xFirst, y=yFirst; x!=xLast && y!=yLast; ++x, ++y) {
        xx += math::sqr(*x);
        yy += math::sqr(*y);
        xy += *x * *y;
    }

    return 1 - xy/(std::sqrt(xx) * std::sqrt(yy));
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::RealVector nct::statistics::distance_metrics::cosineDistance(const Array<T>& xt, const Array2D<T>& x)
{
    auto d = xt.size();
    auto n = x.rows();

    if (d == 0)
        throw EmptyArrayException("xt", SOURCE_INFO);

    if (x.rows() < 1)
        throw ArgumentException("x", exc_data_with_less_than_one_observation, SOURCE_INFO);

    if (x.columns() != d)
        throw ArgumentException("x, xt", exc_objects_with_different_number_of_variables, SOURCE_INFO);

    RealVector dist(n, 0);
    double xx = 0;
    for (index_t k = 0; k<d; k++)                    
        xx += xt[k]*xt[k];
    xx = std::sqrt(xx);

    for (index_t i = 0; i<n; i++) {
        double xy = 0;
        double yy = 0;
        for (index_t k = 0; k<d; k++) {
            xy += xt[k]*x(i,k);    
            yy += x(i,k)*x(i,k);    
        }
        dist[i] = 1 - xy/(xx * std::sqrt(yy));
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::pairwiseCosineDistance(const Array2D<T>& x)
{
    if (x.columns() < 1 || x.rows() < 2)
        throw ArgumentException("x", exc_bad_array_dimensions, SOURCE_INFO);

    auto n = x.rows();
    auto d = x.columns();
    Matrix dist(n, n);
    
    RealVector xx(n, 0);
    for (index_t i = 0; i<n; i++) {
        for (index_t k = 0; k<d; k++)                    
            xx[i] += math::sqr(x(i,k));
        xx[i] = std::sqrt(xx[i]);
    }

    for (index_t i = 0; i<n; i++) {
        dist(i,i) = 0;
        for (auto j = (i+1); j<n; j++) {
            double xy = 0;
            for (index_t k = 0; k<d; k++)                    
                xy += x(i,k) * x(j,k);
            dist(i,j) = 1 - xy/(xx[i] * xx[j]);
            dist(j,i) = dist(i,j);
        }
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::distance_metrics::correlationDistance(InputIt xFirst, InputIt xLast, 
    InputIt yFirst, InputIt yLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    

    if (yFirst >= yLast)
        throw ArgumentException("yLast, yFirst", exc_empty_range, SOURCE_INFO);    

    if ((yLast - yFirst)!=(xLast - xFirst))
        throw ArgumentException("xLast, xFirst, yFirst, yLast", exc_two_ranges_of_different_sizes,
            SOURCE_INFO);
        
    double xx = statistics::variance(xFirst, xLast);
    double yy = statistics::variance(yFirst, yLast);
    double xy = statistics::covariance(xFirst, xLast, yFirst, yLast);    
    return 1 - xy/(std::sqrt(xx)*std::sqrt(yy));
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::RealVector nct::statistics::distance_metrics::correlationDistance(
    const Array<T>& xt, const Array2D<T>& x)
{
    auto d = xt.size();
    auto n = x.rows();

    if (d == 0)
        throw EmptyArrayException("xt", SOURCE_INFO);

    if (x.rows() < 1)
        throw ArgumentException("x", exc_data_with_less_than_one_observation, SOURCE_INFO);

    if (x.columns() != d)
        throw ArgumentException("x, xt", exc_objects_with_different_number_of_variables, SOURCE_INFO);

    double xx = statistics::variance(xt.begin(), xt.end());

    RealVector dist(n, 0);
    for (index_t i = 0; i<n; i++) {
        double yy = statistics::variance(x.beginRow(i), x.endRow(i));
        double xy = statistics::covariance(xt.begin(), xt.end(), x.beginRow(i), x.endRow(i));        
        dist[i] = 1 - xy/(std::sqrt(xx)*std::sqrt(yy));
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::pairwiseCorrelationDistance(const Array2D<T>& x)
{
    if (x.columns() < 1 || x.rows() < 2)
        throw ArgumentException("x", exc_bad_array_dimensions, SOURCE_INFO);

    auto n = x.rows();    
    Matrix dist(n, n);
    
    RealVector xx(n);
    for (index_t i=0; i<n; i++)
        xx[i] = statistics::variance(x.beginRow(i), x.endRow(i));
    
    for (index_t i = 0; i<n; i++) {
        dist(i,i) = 0;
        for (auto j = (i+1); j<n; j++) {
            double xy = statistics::covariance(x.beginRow(i), x.endRow(i), 
                x.beginRow(j), x.endRow(j));    
            dist(i,j) = 1 - xy/(std::sqrt(xx[i])*std::sqrt(xx[j]));
            dist(j,i) = dist(i,j);
        }
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::distance_metrics::spearmanDistance(InputIt xFirst, InputIt xLast, 
    InputIt yFirst, InputIt yLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    

    if (yFirst >= yLast)
        throw ArgumentException("yLast, yFirst", exc_empty_range, SOURCE_INFO);    

    if ((yLast - yFirst)!=(xLast - xFirst))
        throw ArgumentException("xLast, xFirst, yFirst, yLast", exc_two_ranges_of_different_sizes, SOURCE_INFO);
        
    int n = static_cast<int>(xLast - xFirst);
    RealVector x(n);
    RealVector y(n);
    
    for (int k=0; k<n; k++) {
        x[k] = xFirst[k];
        y[k] = yFirst[k];        
    }

    RealVector rx(n);
    statistics::ranks(begin(x), end(x), begin(rx));

    RealVector ry(n);
    statistics::ranks(begin(y), end(y), begin(ry));

    return correlationDistance(rx.begin(), rx.end(), ry.begin(), ry.end());
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::RealVector nct::statistics::distance_metrics::spearmanDistance(const Array<T>& xt, const Array2D<T>& x)
{
    auto d = xt.size();
    auto n = x.rows();

    if (d == 0)
        throw EmptyArrayException("xt", SOURCE_INFO);

    if (x.rows() < 1)
        throw ArgumentException("x", exc_data_with_less_than_one_observation, SOURCE_INFO);

    if (x.columns() != d)
        throw ArgumentException("x, xt", exc_objects_with_different_number_of_variables, SOURCE_INFO);

    RealVector dist(n, 0);
    RealVector xTmp(d);
    RealVector yTmp(d);    
    for (index_t k=0; k<d; k++)
        xTmp[k] = xt[k];
        
    for (index_t i = 0; i<n; i++) {
        for (index_t k=0; k<d; k++)
            yTmp[k] = x(i,k);

        dist[i] = spearmanDistance(xTmp.begin(), xTmp.end(), 
            yTmp.begin(), yTmp.end());
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::pairwiseSpearmanDistance(const Array2D<T>& x)
{
    if (x.columns() < 1 || x.rows() < 2)
        throw ArgumentException("x", exc_bad_array_dimensions, SOURCE_INFO);

    auto n = x.rows();
    auto d = x.columns();
    Matrix dist(n, n);
    
    RealVector xTmp(d);
    RealVector yTmp(d);        
    
    for (index_t i = 0; i<n; i++) {
        dist(i,i) = 0;
        for (index_t j = (i+1); j<n; j++) {
            
            for (index_t k=0; k<d; k++) {
                xTmp[k] = x(i,k);
                yTmp[k] = x(j,k);
            }            
            dist(i,j) = spearmanDistance(xTmp.begin(), xTmp.end(), 
                yTmp.begin(), yTmp.end());
            dist(j,i) = dist(i,j);
        }
    }

    return dist;
}


//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::distance_metrics::hammingDistance(InputIt xFirst, InputIt xLast, 
    InputIt yFirst, InputIt yLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    

    if (yFirst >= yLast)
        throw ArgumentException("yLast, yFirst", exc_empty_range, SOURCE_INFO);    

    if ((yLast - yFirst)!=(xLast - xFirst))
        throw ArgumentException("xLast, xFirst, yFirst, yLast", exc_two_ranges_of_different_sizes, 
            SOURCE_INFO);
        
    double r = 0;
    for (InputIt x=xFirst, y=yFirst; x!=xLast && y!=yLast; ++x, ++y)
        r += (*x != *y);

    auto n = static_cast<double>(xLast - xFirst);
    return r/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::RealVector nct::statistics::distance_metrics::hammingDistance(const Array<T>& xt, const Array2D<T>& x)
{
    auto d = xt.size();
    auto n = x.rows();

    if (d == 0)
        throw EmptyArrayException("xt", SOURCE_INFO);

    if (x.rows() < 1)
        throw ArgumentException("x", exc_data_with_less_than_one_observation, 
        SOURCE_INFO);

    if (x.columns() != d)
        throw ArgumentException("x, xt", exc_objects_with_different_number_of_variables, SOURCE_INFO);

    RealVector dist(n, 0);
    for (index_t i = 0; i<n; i++) {
        for (index_t k = 0; k<d; k++)                    
            dist[i] += (xt[k] != x(i,k));            
        dist[i]/=d;
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::pairwiseHammingDistance(const Array2D<T>& x)
{
    if (x.columns() < 1 || x.rows() < 2)
        throw ArgumentException("x", exc_bad_array_dimensions, SOURCE_INFO);

    auto n = x.rows();
    auto d = x.columns();
    Matrix dist(n, n);
    
    for (index_t i = 0; i<n; i++) {
        dist(i,i) = 0;
        for (auto j = (i+1); j<n; j++) {
            dist(i,j) = 0;
            for (index_t k = 0; k<d; k++)                    
                dist(i,j) += (x(i,k) != x(j,k));                    
            dist(i,j) /= d;
            dist(j,i) = dist(i,j);
        }
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::distance_metrics::jaccardDistance(InputIt xFirst, InputIt xLast,
    InputIt yFirst, InputIt yLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst",
        exc_empty_range, SOURCE_INFO);    

    if (yFirst >= yLast)
        throw ArgumentException("yLast, yFirst", 
        exc_empty_range, SOURCE_INFO);    

    if ((yLast - yFirst)!=(xLast - xFirst))
        throw ArgumentException("xLast, xFirst, yFirst, yLast", exc_two_ranges_of_different_sizes, 
            SOURCE_INFO);
        
    double r = 0;
    double norm = 0;
    for (InputIt x=xFirst, y=yFirst; x!=xLast && y!=yLast; ++x, ++y) {
        if ((*x != 0) || (*y != 0)) {
            r += (*x != *y);
            norm++;
        }
        
    }
    if (norm == 0)
        return 1.0;

    return r/norm;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::RealVector nct::statistics::distance_metrics::jaccardDistance(const Array<T>& xt, const Array2D<T>& x)
{
    auto d = xt.size();
    auto n = x.rows();

    if (d == 0)
        throw EmptyArrayException("xt", SOURCE_INFO);

    if (x.rows() < 1)
        throw ArgumentException("x", exc_data_with_less_than_one_observation, SOURCE_INFO);

    if (x.columns() != d)
        throw ArgumentException("x, xt", exc_objects_with_different_number_of_variables, SOURCE_INFO);

    RealVector dist(n, 0);
    for (index_t i = 0; i<n; i++) {
        double norm = 0;
        for (index_t k = 0; k<d; k++) {
            if ((xt[k] != 0) || (x(i,k) != 0)) {
                dist[i] += (xt[k] != x(i,k));            
                norm ++;
            }
        }
        if (norm == 0)
            dist[i] = 1.0;
        else
            dist[i]/=norm;
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::pairwiseJaccardDistance(const Array2D<T>& x)
{
    if (x.columns() < 1 || x.rows() < 2)
        throw ArgumentException("x", exc_bad_array_dimensions, SOURCE_INFO);

    auto n = x.rows();
    auto d = x.columns();
    Matrix dist(n, n);
    
    for (index_t i = 0; i<n; i++) {
        dist(i,i) = 0;
        for (auto j = (i+1); j<n; j++) {
            dist(i,j) = 0;
            double norm = 0;
            for (index_t k = 0; k<d; k++) {
                if ((x(i,k) != 0) || (x(j,k) != 0)) {
                    dist(i,j) += (x(i,k) != x(j,k));    
                    norm++;
                }
            }
            if (norm == 0)
                dist(i,j) = 1.0;
            else
                dist(i,j)/= norm;            
            dist(j,i) = dist(i,j);
        }
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::RealVector nct::statistics::distance_metrics::stdEuclideanDistance(const Array<T>& xt, const Array2D<T>& x)
{
    auto d = xt.size();
    auto n = x.rows();

    if (d == 0)
        throw EmptyArrayException("xt", SOURCE_INFO);

    if (x.rows() < 2)
        throw ArgumentException("x", exc_data_with_less_than_one_observation, SOURCE_INFO);

    if (x.columns() != d)
        throw ArgumentException("x, xt", exc_objects_with_different_number_of_variables, SOURCE_INFO);

    auto var = x.varCol();
    RealVector dist(n, 0);
    for (index_t i = 0; i<n; i++) {
        for (index_t k = 0; k<d; k++)                    
            dist[i] += ((xt[k] - x(i,k))*(xt[k] - x(i,k)))/var[k];    
        dist[i] = std::sqrt(dist[i]);
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::RealVector nct::statistics::distance_metrics::refStdEuclideanDistance(
    const Array2D<T>& xt, const Array2D<T>& x)
{
    if (xt.columns() < 1 || xt.rows() < 1)
        throw EmptyArrayException("xt", SOURCE_INFO);

    if (x.columns() < 1 || x.rows() < 2)
        throw ArgumentException("x", exc_bad_array_dimensions, SOURCE_INFO);

    if (xt.columns() != x.columns())
        throw ArgumentException("x, xt", exc_arrays_with_different_number_of_colums, SOURCE_INFO);

    auto n = xt.rows();    
    auto d = xt.columns();

    auto m = x.meanCol();
    auto var = x.varCol();

    RealVector dist(n, 0);
    for (index_t i = 0; i<n; i++) {
        for (index_t k = 0; k<d; k++)                    
            dist[i] += math::sqr(xt(i,k) - m[k])/var[k];    
        dist[i] = std::sqrt(dist[i]);
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::pairwiseStdEuclideanDistance(const Array2D<T>& x)
{
    if (x.columns() < 1 || x.rows() < 2)
        throw ArgumentException("x", exc_bad_array_dimensions, SOURCE_INFO);

    auto n = x.rows();
    auto d = x.columns();
    Matrix dist(n, n);
    
    auto var = x.varCol();

    for (index_t i = 0; i<n; i++) {
        dist(i,i) = 0;
        for (auto j = (i+1); j<n; j++) {
            dist(i,j) = 0;
            for (index_t k = 0; k<d; k++)
                dist(i,j) += math::sqr(x(i,k) - x(j,k))/var[k];
            dist(i,j)=std::sqrt(dist(i,j));
            dist(j,i) = dist(i,j);
        }
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::RealVector nct::statistics::distance_metrics::mahalanobisDistance(
    const Array<T>& xt, const Array2D<T>& x, double tol)
{
    auto d = xt.size();
    auto n = x.rows();

    if (d == 0)
        throw EmptyArrayException("xt", SOURCE_INFO);

    if (x.rows() < 2)
        throw ArgumentException("x", exc_data_with_less_than_one_observation, SOURCE_INFO);

    if (x.columns() != d)
        throw ArgumentException("x, xt", exc_objects_with_different_number_of_variables, SOURCE_INFO);

    auto cov = x.covariance();
    decltype(cov) invCov;
    try {        
        invCov = math::linear_algebra::inverse(cov, tol);
    }
    catch (const nct_exception& ex) {
        throw OperationException(exc_error_computing_inverse_of_cov_matrix,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw OperationException(exc_error_computing_inverse_of_cov_matrix,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_unknown, SOURCE_INFO);
    }

    RealVector dist(n, 0);
    for (index_t i = 0; i<n; i++) {
        for (index_t k1 = 0; k1<d; k1++) {
            double tmp = 0;
            for (index_t k2 = 0; k2<d; k2++)
                tmp += invCov(k1,k2)*(xt[k2] - x(i,k2));

            dist[i] += (xt[k1] - x(i,k1))*tmp;
        }
        dist[i] = std::sqrt(dist[i]);
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::RealVector nct::statistics::distance_metrics::refMahalanobisDistance(
    const Array2D<T>& xt, const Array2D<T>& x, double tol)
{
    if (xt.columns() < 1 || xt.rows() < 1)
        throw EmptyArrayException("xt", SOURCE_INFO);

    if (x.columns() < 1 || x.rows() < 2)
        throw ArgumentException("x", exc_bad_array_dimensions, SOURCE_INFO);

    if (xt.columns() != x.columns())
        throw ArgumentException("x, xt", exc_arrays_with_different_number_of_colums, SOURCE_INFO);

    auto n = xt.rows();    
    auto d = xt.columns();

    auto m = x.meanCol();
    auto cov = x.covariance();
    decltype(cov) invCov;
    try {
        invCov = math::linear_algebra::inverse(cov, tol);
    }
    catch (const nct_exception& ex) {
        throw OperationException(exc_error_computing_inverse_of_cov_matrix,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw OperationException(exc_error_computing_inverse_of_cov_matrix,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_unknown, SOURCE_INFO);
    }

    RealVector dist(n, 0);
    for (index_t i = 0; i<n; i++) {
        for (index_t k1 = 0; k1<d; k1++) {
            double tmp = 0;
            for (index_t k2 = 0; k2<d; k2++)
                tmp += invCov(k1,k2)*(xt(i,k2) - m[k2]);

            dist[i] += (xt(i,k1) - m[k1])*tmp;
        }
        dist[i] = std::sqrt(dist[i]);
    }

    return dist;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Arithmetic T>
nct::Matrix nct::statistics::distance_metrics::pairwiseMahalanobisDistance(
    const Array2D<T>& x, double tol) 
{
    if (x.columns() < 1 || x.rows() < 2)
        throw ArgumentException("x", exc_bad_array_dimensions, SOURCE_INFO);

    auto n = x.rows();
    auto d = x.columns();
    Matrix dist(n, n);
    
    auto cov = x.covariance();
    decltype(cov) invCov;
    try {
        invCov = math::linear_algebra::inverse(cov, tol);
    }
    catch (const nct_exception& ex) {
        throw OperationException(exc_error_computing_inverse_of_cov_matrix,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw OperationException(exc_error_computing_inverse_of_cov_matrix,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_unknown, SOURCE_INFO);
    }

    for (index_t i = 0; i<n; i++) {
        dist(i,i) = 0;
        for (auto j = (i+1); j<n; j++) {
            dist(i,j) = 0;
            for (index_t k1 = 0; k1<d; k1++) {
                double tmp = 0;
                for (index_t k2 = 0; k2<d; k2++)
                    tmp += invCov(k1,k2)*(x(i,k2) - x(j,k2));
                dist(i,j) += (x(i,k1) - x(j,k1))*tmp;
            }

            dist(i,j)=std::sqrt(dist(i,j));
            dist(j,i) = dist(i,j);
        }
    }

    return dist;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
