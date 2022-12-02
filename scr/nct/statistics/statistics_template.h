//=================================================================================================================
/**
 *  @file       statistics_template.h
 *  @brief      Implementation of statistical function templates.
 *  @details    This file contains the implementation of the statistical function templates defined in 
 *              the nct::statistics namespace.            
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
//        LINEAR DATA
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::mean(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 0;
    for (auto x=first; x!=last; ++x)
        r+=*x;
    
    double n = static_cast<double>(last - first);
    return r/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type>&& nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::mean(InputIt1 first, InputIt1 last, InputIt2 wFirst)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 0.0;
    double n = 0.0;
    auto w = wFirst;
    for (auto x=first; x!=last; ++x, ++w) {
        r += (*w)*(*x);
        n += (*w);
    }
    
    return r/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::quadraticMean(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 0;
    for (auto x=first; x!=last; ++x)
        r+=(*x) * (*x);
    
    double n = static_cast<double>(last - first);
    return std::sqrt(r/n);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type>&& nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::quadraticMean(InputIt1 first, InputIt1 last, InputIt2 wFirst)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 0.0;
    double n = 0.0;
    auto w = wFirst;
    for (auto x=first; x!=last; ++x, ++w) {
        r += (*w)*(*x)*(*x);
        n += (*w);
    }
    
    return std::sqrt(r/n);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::harmonicMean(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 0;
    for (auto x=first; x!=last; ++x) {
        if (*x == 0)
            throw ArithmeticException(exc_div_by_zero, SOURCE_INFO);
        r+= 1./(*x);
    }
    
    double n = static_cast<double>(last - first);
    return (n/r);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type>&& nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::harmonicMean(InputIt1 first, InputIt1 last, InputIt2 wFirst)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 0.0;
    double n = 0.0;
    auto w = wFirst;
    for (auto x=first; x!=last; ++x, ++w) {
        r += (*w)/(*x);
        n += (*w);
    }
    
    return n/r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::geometricMean(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 1.0;
    for (auto x=first; x!=last; ++x)
        r*=(*x);
    
    double n = static_cast<double>(last - first);
    return std::pow(r,1.0/n);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type>&& nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::geometricMean(InputIt1 first, InputIt1 last, InputIt2 wFirst)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 1.0;
    double n = 0.0;
    auto w = wFirst;
    for (auto x=first; x!=last; ++x, ++w) {
        r *= std::pow(*x, (*w));
        n += (*w);
    }
    
    return std::pow(r,1.0/n);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::powerMean(InputIt first, InputIt last, double p)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 0;
    for (auto x=first; x!=last; ++x)
        r+= std::pow(*x, p);
    
    double n = static_cast<double>(last - first);
    return std::pow(r/n, 1.0/p);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type>&& nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::powerMean(InputIt1 first, InputIt1 last, 
    InputIt2 wFirst, double p)
{
    if (first >= last)
        throw RangeException("first, last",    SOURCE_INFO);

    double r = 0.0;
    double n = 0.0;
    auto w = wFirst;
    for (auto x=first; x!=last; ++x, ++w) {
        r += (*w)*std::pow(*x, p);
        n += (*w);
    }
    
    return std::pow(r/n, 1.0/p);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::median(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    auto n = last - first;
    std::vector<double> xSort(n);
    diff_t c=0;
    for (auto x=first; x!=last; ++x)
        xSort[c++] = *x;
    std::sort(xSort.begin(), xSort.end());
    
    if (n%2 == 0)
        return (xSort[n/2-1] + xSort[n/2])/2.;
    return (xSort[(n-1)/2]);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type>&& nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::median(InputIt1 first, InputIt1 last, InputIt2 wFirst)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    auto n = last - first;

    std::vector<std::pair<double, double>> xw(n);
    
    size_t i = 0;
    double wtot = 0;
    auto w = wFirst;
    for (auto x = first; x != last; ++x, ++w, ++i) {
        xw[i] = std::make_pair(*x, *w);
        wtot += *w;
    }

    size_t beg = 0;
    size_t end = n - 1;

    double trial = 0;
    bool ok = false;
    while (!ok) {
        size_t mid = (beg + end) / 2;
        std::nth_element(xw.begin(), xw.begin() + mid, xw.end(),
            [](const std::pair<double, double>& l, const std::pair<double, double>& r) 
        {
            return l.first > r.first; 
        });
        
        trial = xw[mid].first;
        double wleft = 0;
        double    wright = 0;

        for (auto& xwi : xw) {
            double xi;
            double wi;
            std::tie(xi, wi) = xwi;
            if (xi > trial)
                wleft += wi;
            else
                wright += wi;
        }

        if (2 * wleft > wtot)
            end = mid;
        else if (2 * wright < wtot)
            beg = mid;
        else
            ok = true;
    }

    return trial;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::variance(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);    

    double m = mean(first, last);
    double r = 0;
    for (auto x=first; x!=last; ++x)
        r += (*x - m)*(*x - m);

    double n = static_cast<double>(last - first);
    return r/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type>&& nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::variance(InputIt1 first, InputIt1 last, InputIt2 wFirst)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);    

    double m = mean(first, last, wFirst);
    double r = 0;
    double n = 0.0;
    auto w = wFirst;
    for (auto x = first; x != last; ++x, ++w) {
        r += (*w)*(*x - m)*(*x - m);
        n += (*w);
    }

    return r/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2, 
    std::random_access_iterator InputIt3>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type> &&
    nct::Arithmetic<typename InputIt3::value_type>
double nct::statistics::variance(InputIt1 first, InputIt1 last, InputIt2 sqrFirst, InputIt3 wFirst)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);    

    double r = 0.0;
    double r2 = 0.0;
    double n = 0.0;
    auto w = wFirst;
    auto s = sqrFirst;
    for (auto m=first; m!=last; ++m, ++w, ++s) {
        r += (*w)*(*m);
        r2 += (*w)*(*s);
        n += (*w);
    }

    return (r2 - r*r/n) / n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::sampleVariance(InputIt first, InputIt last)
{
    if (first >= (last-1))
        throw RangeException("first, last", SOURCE_INFO);    

    double m = mean(first, last);
    double r = 0;
    for (auto x=first; x!=last; ++x)
        r += (*x - m)*(*x - m);

    double n = static_cast<double>(last - first);
    return r/(n-1);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type>&& nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::sampleVariance(InputIt1 first, InputIt1 last, InputIt2 wFirst)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);    

    double m = mean(first, last, wFirst);
    double r = 0;
    double n = 0.0;
    double n2 = 0.0;
    auto w = wFirst;
    for (auto x = first; x != last; ++x, ++w) {
        r += (*w)*(*x - m)*(*x - m);
        n += (*w);
        n2 += (*w)*(*w);
    }

    return r / (n - n2 / n);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2, 
    std::random_access_iterator InputIt3>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type> &&
    nct::Arithmetic<typename InputIt3::value_type>
double nct::statistics::sampleVariance(InputIt1 first, InputIt1 last,
    InputIt2 sqrFirst, InputIt3 wFirst)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);    

    double r = 0.0;
    double r2 = 0.0;
    double n = 0.0;
    auto w = wFirst;
    auto s = sqrFirst;
    for (auto m=first; m!=last; ++m, ++w, ++s) {
        r += (*w)*(*m);
        r2 += (*w)*(*s);
        n += (*w);
    }

    return (r2 - r*r/n) / (n - 1.0);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::standardDeviation(InputIt first, InputIt last)
{
    return std::sqrt(variance(first, last));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::standardDeviation(InputIt1 first, InputIt1 last, InputIt2 wFirst)
{
    return std::sqrt(variance(first, last, wFirst));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2, 
    std::random_access_iterator InputIt3>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type> &&
    nct::Arithmetic<typename InputIt3::value_type>
double nct::statistics::standardDeviation(InputIt1 first, InputIt1 last,
    InputIt2 sqrFirst, InputIt3 wFirst)
{
    return std::sqrt(variance(first, last, sqrFirst, wFirst));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::sampleStandardDeviation(InputIt first, InputIt last)
{
    return std::sqrt(sampleVariance(first, last));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type>&& nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::sampleStandardDeviation(InputIt1 first, InputIt1 last, InputIt2 wFirst)
{
    return std::sqrt(sampleVariance(first, last, wFirst));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2, 
    std::random_access_iterator InputIt3>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type> &&
    nct::Arithmetic<typename InputIt3::value_type>
double nct::statistics::sampleStandardDeviation(InputIt1 first, InputIt1 last, InputIt2 sqrFirst, InputIt3 wFirst)
{
    return std::sqrt(sampleVariance(first, last, sqrFirst, wFirst));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::medianAbsoluteDeviation(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);    

    auto size = last - first;
    double m = 0;                            
    double sigma;                            
    std::vector<double> tmpArray(size);            
    
    for (diff_t i=0; i<size; i++)
        tmpArray[i] = first[i];
    m = median(first, last);

    for (diff_t i=0; i<size; i++)
        tmpArray[i] = std::abs(tmpArray[i] - m);

    sigma = median(tmpArray.begin(), tmpArray.end());
    
    return sigma;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::robustStandardDeviation(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);    

    auto size = last - first;
    double m = 0;                            
    double sigma;                            
    std::vector<double> tmpArray(size);            
    
    for (diff_t i=0; i<size; i++)
        tmpArray[i] = first[i];
    m = median(first, last);

    for (diff_t i=0; i<size; i++)
        tmpArray[i] = std::abs(tmpArray[i] - m);

    sigma = median(tmpArray.begin(), tmpArray.end())/0.6745;
    
    return sigma;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::interquartileRange(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);            
    return quantile(first, last, 0.75) - quantile(first, last, 0.25);    
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::skewness(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);    

    double m = mean(first, last);
    double v = variance(first, last);
    double r = 0;
    for (auto x=first; x!=last; ++x)
        r += math::cube(*x - m);

    auto n = (last - first);
    return r/(n*math::cube(std::sqrt(v)));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::sampleSkewness(InputIt first, InputIt last)
{
    if (first >= (last-2))
        throw RangeException("first, last", SOURCE_INFO);    

    double m = mean(first, last);
    double v = sampleVariance(first, last);
    double r = 0;
    for (auto x=first; x!=last; ++x)
        r += math::cube(*x - m);

    auto n = (last - first);
    return n*r/((n-1.0)*(n-2.0)*math::cube(std::sqrt(v)));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::medcouple(InputIt first, InputIt last)
{
    static constinit const auto eps1 {std::numeric_limits<double>::epsilon()};
    static constinit const auto eps2 {std::numeric_limits<double>::min()};

    if (first >= (last - 3))
        throw RangeException("first, last", SOURCE_INFO);

    auto n = last - first;
    auto n2 = (n - 1) / 2;    

    std::vector<double> sortedX(n);
    std::copy(first, last, std::begin(sortedX));
    sort(sortedX.begin(), sortedX.end(), std::greater<double>());
    
    double xmed;
    if (n % 2 == 1)
        xmed = sortedX[n2];
    else
        xmed = (sortedX[n2] + sortedX[n2 + 1]) / 2;
    
    // Check if the median is at the edges up to relative epsilon.
    if (std::abs(sortedX[0] - xmed) < eps1*(eps1 + std::abs(xmed)))
         return -1.0;
    if (std::abs(sortedX[n - 1] - xmed) < eps1*(eps1 + std::abs(xmed)))
        return 1.0;
    
    // Centre xsorted with median, so that median(xsorted) = 0.
    std::for_each(sortedX.begin(), sortedX.end(), [&](double& xi) { xi -= xmed; });
    
    // Scale inside [-0.5, 0.5], for greater numerical stability.
    double xden = 2 * std::max(sortedX[0], -sortedX[n - 1]);
    std::for_each(sortedX.begin(), sortedX.end(), [&](double& xi) {xi /= xden; });
    xmed /= xden;
    
    double xeps = eps1*(eps1 + std::abs(xmed));
    
    // These overlap on the entries that are tied with the median.
    std::vector<double> xplus;
    std::vector<double> xminus;
    
    std::copy_if(sortedX.begin(), sortedX.end(), std::back_inserter(xplus),
        [=](double xi) {return xi >= -xeps; });
    
    std::copy_if(sortedX.begin(), sortedX.end(), std::back_inserter(xminus),
        [=](double xi) {return xeps >= xi; });
    
    diff_t nPlus = static_cast<diff_t>(xplus.size());
    diff_t nMinus = static_cast<diff_t>(xminus.size());
    
    /* Kernel function h for the medcouple, closing over the values of
    xplus and xminus just defined above.*/
    auto hkern = [&](diff_t i, diff_t j)
    {
        double a = xplus[i];
        double b = xminus[j];
        double h = 0;
        if (std::abs(a - b) <= 2 * eps2)
            h = static_cast<double>(nct::math::sign(nPlus - 1 - i - j));
        else
            h = (a + b) / (a - b);
        return h;
    };
    
    // Init left and right borders.
    std::vector<diff_t> l(nPlus, 0);
    std::vector<diff_t> r(nPlus, nMinus - 1);
    
    diff_t ltot = 0;
    diff_t rtot = nMinus*nPlus;
    diff_t medcIndex = rtot / 2;
    
    // kth pair algorithm (Johnson & Mizoguchi).
    double mc = 0;
    bool ok = false;
    while ((rtot - ltot > nPlus) && (!ok)) {
        // First, compute the median inside the given bounds.
        std::vector<double> a;
        std::vector<double> w;
        
        for (diff_t i = 0; i < nPlus; i++) {
            if (l[i] <= r[i]) {
                a.push_back(hkern(i, (l[i] + r[i]) / 2));
                w.push_back(static_cast<double>(r[i] - l[i] + 1));
            }
        }
        
        double am = median(a.begin(), a.end(), w.begin());
        double ameps = eps1*(eps1 + std::abs(am));
        
        // Compute new left and right boundaries, based on the weighted median.
        std::vector<diff_t> p(nPlus);
        std::vector<diff_t> q(nPlus);
        
        {    
            diff_t j = 0;
            for (diff_t i = nPlus - 1; i >= 0; i--) {
                while ((j < nMinus) && ((hkern(i, j) - am) > ameps))
                    j++;
                p[i] = j - 1;
            }
        }
        
        {
            diff_t j = nMinus - 1;
            for (diff_t i = 0; i < nPlus; i++) {
                while ((j >= 0) && ((hkern(i, j) - am) < -ameps))
                    j--;
                q[i] = j + 1;
            }
        }
        
        diff_t sumP = math::sum(p.begin(), p.end()) + nPlus;
        diff_t sumQ = math::sum(q.begin(), q.end());
        
        if (medcIndex <= sumP - 1) {
            r = p;
            rtot = sumP;
        }
        else {
            if (medcIndex > sumQ - 1) {
                l = q;
                ltot = sumQ;                
            }
            else {
                mc = am;
                ok = true;
            }
        }        
    }
    
    if (!ok) {
        /* Didn't find the median, but now we have a very small search space
           to find it in, just between the left and right boundaries. This
           space is of size Rtot - Ltot which is <= nPlus.*/
        std::vector<double> a;
        for (diff_t i = 0; i < nPlus; i++) {
            for (diff_t j = l[i]; j <= r[i]; j++)
                a.push_back(hkern(i, j));
        }

        std::nth_element(a.begin(), a.begin() + (medcIndex - ltot), a.end(),
            [](double x, double y) {return x > y; });

        mc = a[medcIndex - ltot];
    }
    
    return mc;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::kurtosis(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);    

    double m = mean(first, last);
    double v = variance(first, last);
    double r = 0;
    for (auto x=first; x!=last; ++x)
        r += math::fourth_pwr(*x - m);

    double n = static_cast<double>(last - first);
    return r/(n*math::sqr(v)) - 3;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::sampleKurtosis(InputIt first, InputIt last)
{
    if (first >= (last-3))
        throw RangeException("first, last", SOURCE_INFO);    

    double m = mean(first, last);
    double v = sampleVariance(first, last);
    double r = 0;
    for (auto x=first; x!=last; ++x)
        r += math::fourth_pwr(*x - m);

    auto n = (last - first);
    return r*(n+1.0)*n/((n-1.0)*(n-2.0)*(n-3.0)*math::sqr(v)) - 3*math::sqr(n-1.0)/((n-2.0)*(n-3.0));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::secondMoment(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 0;
    for (auto x=first; x!=last; ++x)
        r+=math::sqr(*x);
    
    auto n = (last - first);
    return r/n;
}
        
//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::thirdMoment(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 0;
    for (auto x=first; x!=last; ++x)
        r+=math::cube(*x);
    
    auto n = (last - first);
    return r/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::thirdCentralMoment(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 0;
    double m = mean(first, last);
    for (auto x=first; x!=last; ++x)
        r+=math::cube(*x - m);
    
    auto n = (last - first);
    return r/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::fourthMoment(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 0;
    for (auto x=first; x!=last; ++x)
        r+=math::fourth_pwr(*x);
    
    auto n = (last - first);
    return r/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::fourthCentralMoment(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 0;
    double m = mean(first, last);
    for (auto x=first; x!=last; ++x)
        r+=math::fourth_pwr(*x - m);
    
    auto n = (last - first);
    return r/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::kMoment(InputIt first, InputIt last, unsigned int k)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 0;
    double p = 0;
    for (auto x=first; x!=last; ++x) {
        p = 1;
        for (unsigned int i=0; i<k;i++)
            p*=*x;
        r+=p;
    }
    
    auto n = (last - first);
    return r/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::kCentralMoment(InputIt first, InputIt last, unsigned int k)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double r = 0;
    double p = 0;
    double m = mean(first, last);
    for (auto x=first; x!=last; ++x) {
        p = 1;
        for (unsigned int i=0; i<k;i++)
            p*=(*x-m);
        r+=p;
    }
    
    auto n = (last - first);
    return r/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::covariance(InputIt1 xFirst, InputIt1 xLast, InputIt2 yFirst, 
    InputIt2 yLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    
    if ((yLast - yFirst)!=(xLast - xFirst))
        throw ArgumentException("xLast, xFirst, yFirst, yLast", exc_two_ranges_of_different_sizes, 
            SOURCE_INFO);

    double mx = mean(xFirst, xLast);
    double my = mean(yFirst, yLast);
    double r = 0;
    auto x = xFirst;
    auto y = yFirst;
    for (; x!=xLast && y!=yLast; ++x, ++y)
        r += (*x - mx)*(*y - my);

    auto n = static_cast<double>(xLast - xFirst);
    return r/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2, 
    std::random_access_iterator InputIt3>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type> &&
    nct::Arithmetic<typename InputIt3::value_type>
double nct::statistics::covariance(InputIt1 xFirst, InputIt1 xLast, InputIt2 yFirst, 
    InputIt2 yLast, InputIt3 wFirst)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, 
            SOURCE_INFO);    
    if ((yLast - yFirst)!=(xLast - xFirst))
        throw ArgumentException("xLast, xFirst, yFirst, yLast", exc_two_ranges_of_different_sizes,
            SOURCE_INFO);

    double mx = mean(xFirst, xLast, wFirst);
    double my = mean(yFirst, yLast, wFirst);
    double r = 0;
    double n = 0.0;
    auto x = xFirst;
    auto y = yFirst;
    auto w = wFirst;
    for (; x != xLast && y != yLast; ++x, ++y, ++w) {
        r += (*w)*(*x - mx)*(*y - my);
        n += (*w);
    }

    return r/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type>&& nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::sampleCovariance(InputIt1 xFirst, InputIt1 xLast, InputIt2 yFirst, 
    InputIt2 yLast)
{
    if (xFirst >= (xLast-1))
        throw ArgumentException("xLast, xFirst", exc_data_with_less_than_two_observations,  
            SOURCE_INFO);    
    if ((xLast - xFirst)!=(xLast - xFirst))
        throw ArgumentException("xLast, xFirst, yFirst, yLast", exc_two_ranges_of_different_sizes, 
            SOURCE_INFO);

    double mx = mean(xFirst, xLast);
    double my = mean(yFirst, yLast);
    double r = 0;
    auto x = xFirst;
    auto y = yFirst;
    for (; x!=xLast && y!=yLast; ++x, ++y)
        r += (*x - mx)*(*y - my);

    auto n = static_cast<double>(xLast - xFirst);
    return r/(n-1);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2, 
    std::random_access_iterator InputIt3>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type> &&
    nct::Arithmetic<typename InputIt3::value_type>
double nct::statistics::sampleCovariance(InputIt1 xFirst, InputIt1 xLast, InputIt2 yFirst, 
    InputIt2 yLast, InputIt3 wFirst)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, 
            SOURCE_INFO);    
    if ((yLast - yFirst)!=(xLast - xFirst))
        throw ArgumentException("xLast, xFirst, yFirst, yLast", exc_two_ranges_of_different_sizes, 
            SOURCE_INFO);

    double mx = mean(xFirst, xLast, wFirst);
    double my = mean(yFirst, yLast, wFirst);
    double r = 0;
    double n = 0.0;
    double n2 = 0.0;
    auto x = xFirst;
    auto y = yFirst;
    auto w = wFirst;
    for (; x != xLast && y != yLast; ++x, ++y, ++w) {
        r += (*w)*(*x - mx)*(*y - my);
        n += (*w);
        n2 += (*w)*(*w);
    }

    return (n/(n*n - n2))*r;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::pearsonCorrelation(InputIt1 xFirst, InputIt1 xLast, 
    InputIt2 yFirst, InputIt2 yLast)
{
    auto n = xLast - xFirst;        
    
    if (n<1)
        throw ArgumentException("xFirst, xLast", exc_empty_range, SOURCE_INFO);
    
    if ((yLast - yFirst) != n)
        throw ArgumentException("xFirst, xLast, yFirst, yLast", exc_two_ranges_of_different_sizes,
            SOURCE_INFO);

    double x = 0, y = 0, xy = 0, xx = 0, yy = 0;
    auto xi=xFirst; 
    auto yi=yFirst;
    for (; (xi!=xLast) && (yi!=yLast); ++xi, ++yi) {
        x  += static_cast<double>(*xi);
        y  += static_cast<double>(*yi);
        xx += static_cast<double>(*xi)*static_cast<double>(*xi);
        yy += static_cast<double>(*yi) * static_cast<double>(*yi);
        xy += static_cast<double>(*xi)*static_cast<double>(*yi);
    }

    double d1 = static_cast<double>(n)*xx-x*x;
    double d2 = static_cast<double>(n)*yy-y*y;

    if (d1==0 || d2==0)
        throw ArithmeticException(exc_div_by_zero, SOURCE_INFO);

    return (static_cast<double>(n)*xy - x*y)/std::sqrt(d1*d2);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::spearmanRhoCorrelation(InputIt1 xFirst, InputIt1 xLast, 
    InputIt2 yFirst, InputIt2 yLast)
{
    auto n = xLast - xFirst;        
    
    if (n<1)
        throw ArgumentException("xFirst, xLast", exc_empty_range, SOURCE_INFO);
    
    if ((yLast - yFirst) != n)
        throw ArgumentException("xFirst, xLast, yFirst, yLast", exc_two_ranges_of_different_sizes,
            SOURCE_INFO);

    // Ranks.
    std::vector<double> r1(n);
    auto nTies1 = correctedRanks(xFirst, xLast, begin(r1));
    
    std::vector<double> r2(n);
    auto nTies2 = correctedRanks(yFirst, yLast, begin(r2));

    // Coefficient.
    double r = 0;
    if (nTies1==0 && nTies2==0) {
        double d = 0;
        for (diff_t i=0; i<n; i++)
            d+=math::sqr((r1[i]-r2[i]));
        r = 1-6*d/(static_cast<double>(n)*(static_cast<double>(n)*static_cast<double>(n)-1.));
    }
    else {
        double x = 0, y = 0, xy = 0, xx = 0, yy = 0;
        for (diff_t i=0; i<n; i++) {
            x+=r1[i];
            y+=r2[i];
            xx+=r1[i]*r1[i];
            yy+=r2[i]*r2[i];
            xy+=r1[i]*r2[i];
        }

        double d1 = static_cast<double>(n)*xx-x*x;
        double d2 = static_cast<double>(n)*yy-y*y;

        if (d1==0 || d2==0)
            throw ArithmeticException(exc_div_by_zero, SOURCE_INFO);
        r = (static_cast<double>(n)*xy - x*y)/std::sqrt(d1*d2);
    }

    return r;
}    

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::kendallTauCorrelation(InputIt1 xFirst, InputIt1 xLast, 
    InputIt2 yFirst, InputIt2 yLast)
{    
    auto n = xLast - xFirst;        
    
    if (n < 1)
        throw ArgumentException("xFirst, xLast", exc_empty_range, SOURCE_INFO);

    if ((yLast - yFirst) != n)
        throw ArgumentException("xFirst, xLast, yFirst, yLast", exc_two_ranges_of_different_sizes,
            SOURCE_INFO);
    
    // Ranks.
    std::vector<double> r1(n);
    auto nTies1 = correctedRanks(xFirst, xLast, begin(r1));
    std::vector<double> t1(nTies1);
    if (nTies1)
        countTies(xFirst, xLast, begin(t1));

    std::vector<double> r2(n);
    auto nTies2 = correctedRanks(yFirst, yLast, begin(r2));
    std::vector<double> t2(nTies2);
    if (nTies2)
        countTies(yFirst, yLast, begin(t2));

    // Coefficient.
    double t = 0;
    double s = 0;    
    for (diff_t i=0; i<n; i++)
        for (diff_t j=(i+1); j<n; j++)
            s+=nct::math::sign(r1[i]-r1[j])*nct::math::sign(r2[i]-r2[j]);

    double ti=0;
    for (diff_t i=0; i<static_cast<diff_t>(t1.size()); i++)
        ti+=t1[i]*(t1[i]-1);

    double ui=0;
    for (diff_t i=0; i<static_cast<diff_t>(t2.size()); i++)
        ui+=t2[i]*(t2[i]-1);

    t = s/(std::sqrt(n*(n-1.)/2. -ti/2.)*std::sqrt(n*(n-1.)/2. - ui/2.));

    return t;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::differenceOfTwoMeans(InputIt1 xFirst, InputIt1 xLast, 
    InputIt2 yFirst, InputIt2 yLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    
    
    if (yFirst >= yLast)
        throw ArgumentException("yFirst, yLast", exc_empty_range, SOURCE_INFO);    

    double mx = mean(xFirst, xLast);
    double my = mean(yFirst, yLast);    
    
    return mx - my;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::normDifferenceOfTwoMeans(InputIt1 xFirst, InputIt1 xLast, 
    InputIt2 yFirst, InputIt2 yLast)
{
    if (xFirst >= (xLast-1))
        throw ArgumentException("xLast, xFirst", exc_data_with_less_than_two_observations, SOURCE_INFO);
    
    if (yFirst >= (yLast-1))
        throw ArgumentException("yFirst, yLast", exc_data_with_less_than_two_observations, SOURCE_INFO);

    auto n1 = (xLast - xFirst);
    double m1 = mean(xFirst, xLast);
    double r1 = 0;
    for (auto x=xFirst; x!=xLast; ++x)
        r1 += (*x - m1)*(*x - m1);
    r1 /= n1-1.;
    
    auto n2 = (yLast - yFirst);
    double m2 = mean(yFirst, yLast);
    double r2 = 0;
    for (auto y=yFirst; y!=yLast; ++y)
        r2 += (*y - m2)*(*y - m2);
    r2 /= n2-1.;
    
    return (m1 - m2)/std::sqrt(r1/n1 + r2/n2);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
std::pair<double, double> nct::statistics::normDifferenceOfTwoMeansDf(InputIt1 xFirst,
    InputIt1 xLast, InputIt2 yFirst, InputIt2 yLast)
{
    if (xFirst >= (xLast-1))
        throw ArgumentException("xLast, xFirst", exc_data_with_less_than_two_observations, SOURCE_INFO);    
    
    if (yFirst >= (yLast-1))
        throw ArgumentException("yFirst, yLast", exc_data_with_less_than_two_observations, SOURCE_INFO);    

    auto n1 = (xLast - xFirst);
    double m1 = mean(xFirst, xLast);
    double r1 = 0;
    for (auto x=xFirst; x!=xLast; ++x)
        r1 += (*x - m1)*(*x - m1);
    r1 /= n1-1.;
    
    auto n2 = (yLast - yFirst);
    double m2 = mean(yFirst, yLast);
    double r2 = 0;
    for (auto y=yFirst; y!=yLast; ++y)
        r2 += (*y - m2)*(*y - m2);
    r2 /= n2-1.;
    
    double a = r1/n1;
    double b = r2/n2;
    double df = (a+b)*(a+b)/((a*a)/(n1-1.0) + (b*b)/(n2-1.0));    
    double d = (m1 - m2)/std::sqrt(a + b);

    return std::make_pair(d, df);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::tanimotoIndex(InputIt1 xFirst, InputIt1 xLast, 
    InputIt2 yFirst, InputIt2 yLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);
    if ((yLast - yFirst)!=(xLast - xFirst))
        throw ArgumentException("xLast, xFirst, yFirst, yLast", exc_two_ranges_of_different_sizes, 
            SOURCE_INFO);
    
    double xANDy = 0;
    double xORy = 0;
    auto x=xFirst;
    auto y=yFirst;
    for (x=xFirst, y=yFirst; (x!=xLast) && (y!=yLast); ++x, ++y) {
        xANDy += ((*x != 0) && (*y != 0));
        xORy  += ((*x != 0) || (*y != 0));
    }

    if (xORy == 0)
        return 0.0;

    return xANDy / xORy;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
nct::size_t nct::statistics::truePositives(InputIt1 xFirst, InputIt1 xLast,
    InputIt2 tFirst, InputIt2 tLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    
    if ((tLast - tFirst) != (xLast - xFirst))
        throw ArgumentException("xLast, xFirst, tFirst, tLast", exc_two_ranges_of_different_sizes, 
            SOURCE_INFO);
    
    size_t tp = 0;
    auto x=xFirst;
    auto t=tFirst;
    for (x=xFirst, t=tFirst; (x!=xLast) && (t!=tLast); ++x, ++t)
        tp += ((*x != 0) && (*t != 0));
    
    return tp;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::truePositiveRate(InputIt1 xFirst, InputIt1 xLast,
    InputIt2 tFirst, InputIt2 tLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    
    if ((tLast - tFirst) != (xLast - xFirst))
        throw ArgumentException("xLast, xFirst, tFirst, tLast", exc_two_ranges_of_different_sizes, 
            SOURCE_INFO);
    
    double tp = 0.0;
    double xp = 0.0;
    double np = 0.0;

    auto x=xFirst;
    auto t=tFirst;
    for (x=xFirst, t=tFirst; (x!=xLast) && (t!=tLast); ++x, ++t) {
        tp += ((*x != 0) && (*t != 0));
        xp += (*x != 0);
        np += (*t != 0);
    }

    if (np == 0) {
        if (xp == 0)
            return 1.0;
        else
            return 0.0;
    }
    return tp / np;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
nct::size_t nct::statistics::trueNegatives(InputIt1 xFirst, InputIt1 xLast,
    InputIt2 tFirst, InputIt2 tLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    
    if ((tLast - tFirst) != (xLast - xFirst))
        throw ArgumentException("xLast, xFirst, tFirst, tLast", exc_two_ranges_of_different_sizes, 
            SOURCE_INFO);
    
    size_t tn = 0;
    auto x=xFirst;
    auto t=tFirst;
    for (x=xFirst, t=tFirst; (x!=xLast) && (t!=tLast); ++x, ++t)
        tn += ((*x == 0) && (*t == 0));
        
    return tn;
}
//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::trueNegativeRate(InputIt1 xFirst, InputIt1 xLast,
    InputIt2 tFirst, InputIt2 tLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    
    if ((tLast - tFirst) != (xLast - xFirst))
        throw ArgumentException("xLast, xFirst, tFirst, tLast", exc_two_ranges_of_different_sizes, 
            SOURCE_INFO);
    
    double tn = 0.0;
    double xn = 0.0;    
    double nn = 0.0;

    auto x=xFirst;
    auto t=tFirst;
    for (x=xFirst, t=tFirst; (x!=xLast) && (t!=tLast); ++x, ++t) {
        tn += ((*x == 0) && (*t == 0));
        xn += (*x == 0);
        nn += (*t == 0);
    }

    if (nn == 0) {
        if (xn == 0)
            return 1.0;
        else
            return 0.0;
    }
    return tn / nn;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
nct::size_t nct::statistics::falsePositives(InputIt1 xFirst, InputIt1 xLast,
    InputIt2 tFirst, InputIt2 tLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    
    if ((tLast - tFirst) != (xLast - xFirst))
        throw ArgumentException("xLast, xFirst, tFirst, tLast", exc_two_ranges_of_different_sizes, 
            SOURCE_INFO);
    
    size_t fp = 0;
    auto x=xFirst;
    auto t=tFirst;
    for (x=xFirst, t=tFirst; (x!=xLast) && (t!=tLast); ++x, ++t)
        fp += ((*x != 0) && (*t == 0));
        
    return fp;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::falsePositiveRate(InputIt1 xFirst, InputIt1 xLast,
    InputIt2 tFirst, InputIt2 tLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    
    if ((tLast - tFirst) != (xLast - xFirst))
        throw ArgumentException("xLast, xFirst, tFirst, tLast", exc_two_ranges_of_different_sizes, 
            SOURCE_INFO);
    
    double fp = 0.0;
    double xn = 0.0;
    double nn = 0.0;

    auto x=xFirst;
    auto t=tFirst;
    for (x=xFirst, t=tFirst; (x!=xLast) && (t!=tLast); ++x, ++t) {
        fp += ((*x != 0) && (*t == 0));
        xn += (*x == 0);
        nn += (*t == 0);
    }

    if (nn == 0) {
        if (xn == 0)
            return 0.0;
        else
            return 1.0;
    }
    return fp / nn;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
nct::size_t nct::statistics::falseNegatives(InputIt1 xFirst, InputIt1 xLast,
    InputIt2 tFirst, InputIt2 tLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    
    if ((tLast - tFirst) != (xLast - xFirst))
        throw ArgumentException("xLast, xFirst, tFirst, tLast", exc_two_ranges_of_different_sizes, 
            SOURCE_INFO);
    
    size_t fn = 0;
    auto x=xFirst;
    auto t=tFirst;
    for (x=xFirst, t=tFirst; (x!=xLast) && (t!=tLast); ++x, ++t)
        fn += ((*x == 0) && (*t != 0));
    
    return fn;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::falseNegativeRate(InputIt1 xFirst, InputIt1 xLast,
    InputIt2 tFirst, InputIt2 tLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    
    if ((tLast - tFirst) != (xLast - xFirst))
        throw ArgumentException("xLast, xFirst, tFirst, tLast", exc_two_ranges_of_different_sizes, 
            SOURCE_INFO);
    
    double fn = 0.0;
    double xp = 0.0;
    double np = 0.0;

    auto x=xFirst;
    auto t=tFirst;
    for (x=xFirst, t=tFirst; (x!=xLast) && (t!=tLast); ++x, ++t) {
        fn += ((*x == 0) && (*t != 0));
        xp += (*x != 0);
        np += (*t != 0);
    }

    if (np == 0) {
        if (xp == 0)
            return 0.0;
        else
            return 1.0;
    }
    return fn / np;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::positivePredictiveValue(InputIt1 xFirst, InputIt1 xLast,
    InputIt2 tFirst, InputIt2 tLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    
    if ((tLast - tFirst) != (xLast - xFirst))
        throw ArgumentException("xLast, xFirst, tFirst, tLast", exc_two_ranges_of_different_sizes,
            SOURCE_INFO);
    
    double tp = 0.0;
    double xp = 0.0;    
    double np = 0.0;

    auto x=xFirst;
    auto t=tFirst;
    for (x=xFirst, t=tFirst; (x!=xLast) && (t!=tLast); ++x, ++t) {
        tp += ((*x != 0) && (*t != 0));
        xp += (*x != 0);
        np += (*t != 0);
    }

    if (xp == 0) {
        if (np == 0)
            return 1.0;
        else
            return 0.0;
    }
    return tp / xp;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::negativePredictiveValue(InputIt1 xFirst, InputIt1 xLast,
    InputIt2 tFirst, InputIt2 tLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    
    if ((tLast - tFirst) != (xLast - xFirst))
        throw ArgumentException("xLast, xFirst, tFirst, tLast", exc_two_ranges_of_different_sizes, 
            SOURCE_INFO);
    
    double tn = 0.0;
    double xn = 0.0;    
    double nn = 0.0;

    auto x=xFirst;
    auto t=tFirst;
    for (x=xFirst, t=tFirst; (x!=xLast) && (t!=tLast); ++x, ++t) {
        tn += ((*x == 0) && (*t == 0));
        xn += (*x == 0);
        nn += (*t == 0);
    }

    if (xn == 0) {
        if (nn == 0)
            return 1.0;
        else
            return 0.0;
    }
    return tn / xn;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::falseDiscoveryRate(InputIt1 xFirst, InputIt1 xLast,
    InputIt2 tFirst, InputIt2 tLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    
    if ((tLast - tFirst) != (xLast - xFirst))
        throw ArgumentException("xLast, xFirst, tFirst, tLast", exc_two_ranges_of_different_sizes,
            SOURCE_INFO);
    
    double fp = 0.0;
    double xp = 0.0;    
    double np = 0.0;

    auto x=xFirst;
    auto t=tFirst;
    for (x=xFirst, t=tFirst; (x!=xLast) && (t!=tLast); ++x, ++t) {
        fp += ((*x != 0) && (*t == 0));
        xp += (*x != 0);
        np += (*t != 0);
    }

    if (xp == 0) {
        if (np == 0)
            return 0.0;
        else
            return 1.0;
    }
    return fp / xp;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::accuracy(InputIt1 xFirst, InputIt1 xLast, InputIt2 tFirst, InputIt2 tLast)
{
    if (xFirst >= xLast)
        throw ArgumentException("xLast, xFirst", exc_empty_range, SOURCE_INFO);    
    if ((tLast - tFirst) != (xLast - xFirst))
        throw ArgumentException("xLast, xFirst, tFirst, tLast", exc_two_ranges_of_different_sizes,
            SOURCE_INFO);
    
    double tp = 0.0;
    double tn = 0.0;
    double n = 0.0;

    auto x=xFirst;
    auto t=tFirst;
    for (x=xFirst, t=tFirst; (x!=xLast) && (t!=tLast); ++x, ++t) {
        tp += ((*x != 0) && (*t != 0));
        tn += ((*x == 0) && (*t == 0));
        n ++;
    }

    return (tp + tn) / n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::ranks(InputIt xFirst, InputIt xLast, OutIt rFirst)
{
    auto n = xLast - xFirst;

    // Sort observations.
    std::vector<std::pair<diff_t, typename std::remove_cvref_t<decltype(*xFirst)>>> sortedData(n);
    
    auto x = xFirst;
    for (diff_t k = 0; k<n; k++, ++x)
        sortedData[k] = std::make_pair(k, *x);

    std::sort(begin(sortedData), end(sortedData), [](
        typename std::remove_cvref_t <decltype(sortedData[0])> const& v1,
        typename std::remove_cvref_t <decltype(sortedData[0])> const& v2)
        {return v1.second<v2.second;});

    // Ranks.
    std::vector<typename std::remove_cvref_t<decltype(*rFirst)>> rt(n);
    for (diff_t k = 0; k<n; k++)
        rt[sortedData[k].first] =
        static_cast<typename std::remove_cvref_t<decltype(*rFirst)>>(k+1);

    std::copy(begin(rt), end(rt), rFirst);    
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
nct::size_t nct::statistics::correctedRanks(InputIt xFirst, InputIt xLast, 
    OutIt rFirst)    
{
    auto n = xLast - xFirst;
    
    // Sort observations.
    std::vector<std::pair<diff_t, typename std::remove_cvref_t<decltype(*xFirst)>>> sortedData(n);
    
    auto x = xFirst;
    for (diff_t k = 0; k<n; k++, ++x)
        sortedData[k] = std::make_pair(k, *x);

    std::sort(begin(sortedData), end(sortedData), [] (
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v1,
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v2)
        {return v1.second<v2.second;});

    // Ranks.
    std::vector<typename std::remove_cvref_t<decltype(*rFirst)>> rt(n);
    for (diff_t k = 0; k<n; k++)
        rt[sortedData[k].first] =
        static_cast<typename std::remove_cvref_t<decltype(*rFirst)>>(k+1);

    // Correction for tied data.
    diff_t nTies = 0;
    for (diff_t i = 0; i<n;) {
        diff_t j = 0;
        for (j = i+1; j<n; j++) {
            if (sortedData[i].second != sortedData[j].second)
                break;
        }
        if (j>(i+1)) {    
            nTies++;
            typename std::remove_cvref_t<decltype(rt[0])> acc = 0;
            for (diff_t k = i; k<j; k++)
                acc += rt[sortedData[k].first];
            
            acc /= static_cast<decltype(acc)>(j-i);
            
            for (diff_t k = i; k<j; k++)
                rt[sortedData[k].first] = acc;
        }
        i+=j-i;
    }

    // Copy final result.
    std::copy(begin(rt), end(rt), rFirst);    
    return nTies;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
nct::size_t nct::statistics::countTies(InputIt xFirst, InputIt xLast, 
    OutIt tFirst)
{
    // Sort elements.
    auto n = xLast - xFirst;
    typename std::vector<typename std::remove_cvref_t<decltype(*xFirst)>> sortedData(n);

    std::copy(xFirst, xLast, begin(sortedData));
    std::sort(begin(sortedData), end(sortedData));

    // Count ties.
    diff_t nTies = 0;
    for (diff_t i = 0; i<n;) {
        auto j = i + 1;
        for (; j<n; j++) {
            if (sortedData[i] != sortedData[j])
                break;
        }
        if (j>(i+1)) {
            *tFirst = static_cast<typename std::remove_cvref_t<decltype(*tFirst)>>(j - i);
            ++tFirst;
            nTies++;
        }
        i+=j-i;
    }    

    return nTies;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::quantile(InputIt first, InputIt last, double p)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    if (p < 0 || p > 1) 
        throw ArgumentException("p", p , 0., 1.,RelationalOperator::GreaterThanOrEqualTo, 
            RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);

    double q = 0;
    double tmp = 0;
    double tmp2 = 0;

    // Sort data.
    auto size = (last - first);    
    diff_t c=0;
    std::vector<double> xSort(size);
    for (InputIt x=first; x!=last; ++x)
        xSort[c++] = *x;
    
    std::sort(xSort.begin(), xSort.end());
    
    // Calculates the quantile.
    for (diff_t i=0; i<=size; i++) {
        tmp2 = tmp;
        tmp = (0.5+i)/size;
        if (p<tmp) {
            if (i == 0)
                q = xSort[0];
            else if (i == (size))
                q = xSort[size-1];    
            else
                q = xSort[i-1] + (p - tmp2)*(xSort[i] - xSort[i-1])/(tmp - tmp2);
            break;
        }
    }    

    return q;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::quantile(InputIt first, InputIt last, InputIt pFirst, 
    InputIt pLast, OutIt qOut)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);    
    if (pFirst >= pLast)
        throw ArgumentException("pLast, pFirst", exc_empty_range, SOURCE_INFO);

    for (InputIt p=pFirst; p!=pLast; ++p) {
        if (*p <0  || *p > 1) 
            throw ArgumentException("pFirst, pLast", exc_values_are_not_probabilities, SOURCE_INFO);
    }

    // Sort data.
    auto size = last - first;    
    diff_t c=0;
    std::vector<double> xSort(size);
    for (InputIt x=first; x!=last; ++x)
        xSort[c++] = *x;
    std::sort(xSort.begin(), xSort.end());

    // Quantiles.
    double tmp = 0;
    double tmp2 = 0;
    for (InputIt p=pFirst; p!=pLast; ++p) {
        tmp = 0;
        for (diff_t i=0; i<=size; i++) {
            tmp2 = tmp;
            tmp = (0.5+i)/size;
            if (*p<tmp) {
                if (i == 0)
                    *qOut = xSort[0];
                else if (i == (size))
                    *qOut = xSort[size-1];    
                else
                    *qOut = xSort[i-1] + (*p - tmp2)*(xSort[i] - xSort[i-1])/(tmp - tmp2);
                break;
            }
        }    
        qOut++;
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::cumulativeData(InputIt first, InputIt last, OutIt out)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    *out = *first;
    OutIt tmpOut = out;
    ++out;
    ++first;
    for (InputIt x=first; x!=last; ++x) {
        *out = *tmpOut + *x;
        ++out;
        ++tmpOut;
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::empiricalCDF(InputIt first, InputIt last, double x)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);    
    
    double p = 0;        
    for (InputIt xIt=first; xIt!=last; ++xIt)
        p += (*xIt <= x);        
    
    auto n = (last - first);
    return p/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::empiricalCDF(InputIt first, InputIt last, OutIt pOut)
{
    auto n = (last - first);
    if (n < 1)
        throw RangeException("first, last", SOURCE_INFO);    
    
    // Sort observations.
    std::vector<std::pair<diff_t, typename std::remove_cvref_t<decltype(*first)>>> sortedData(n);
    
    auto x = first;
    for (diff_t k = 0; k<n; k++, ++x)
        sortedData[k] = std::make_pair(k, *x);
    
    std::sort(begin(sortedData), end(sortedData), [] (
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v1,
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v2)
        {return v1.second<v2.second;});

    // Calculate probabilities.
    std::vector<typename std::remove_cvref_t<decltype(*first)>> acc(n);
    
    diff_t current = 0;
    for (diff_t j = 0; j<n; j++) {
        if (j == 0)
            acc[j] = 0;
        else
            acc[j] = acc[j-1];

        for (; current<n; current++) {
            if (sortedData[current].second <= sortedData[j].second)
                acc[j]++;
            else
                break;
        }        
    }

    // Rearange data and copy results.
    for (diff_t k = 0; k<n; k++)
        sortedData[sortedData[k].first].second = acc[k];

    for (diff_t k = 0; k<n; k++, ++pOut)
        *pOut = sortedData[k].second / n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::empiricalCDF(InputIt first, InputIt last, InputIt testFirst, 
    InputIt testLast, OutIt pOut)
{
    auto n = (last - first);
    auto nt = (testLast - testFirst);
    if (n < 1)
        throw RangeException("first, last", SOURCE_INFO);    
    if (nt < 1)
        throw ArgumentException("testLast, testFirst", exc_empty_range,
            SOURCE_INFO);

    // Sort observations.
    std::vector<std::pair<diff_t, typename std::remove_cvref_t<decltype(*first)>>> sortedData(n);
    
    auto x = first;
    for (diff_t k = 0; k<n; k++, ++x)
        sortedData[k] = std::make_pair(k, *x);
    
    std::sort(std::begin(sortedData), std::end(sortedData), [] (
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v1,
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v2)
        {return v1.second<v2.second;});

    std::vector<std::pair<diff_t, typename std::remove_cvref_t<decltype(*first)>>> sortedTestData(nt);
    
    auto xt = testFirst;
    for (diff_t k = 0; k<nt; k++, ++xt)
        sortedTestData[k] = std::make_pair(k, *xt);
    
    std::sort(std::begin(sortedTestData), std::end(sortedTestData), [] (
        typename std::remove_cvref_t<decltype(sortedTestData[0])> const& v1,
        typename std::remove_cvref_t<decltype(sortedTestData[0])> const& v2)
        {return v1.second<v2.second;});

    // Calculate probabilities.
    std::vector<typename std::remove_cvref_t<decltype(*testFirst)>> acc(nt);
    
    diff_t current = 0;
    for (diff_t j = 0; j<nt; j++) {
        if (j == 0)
            acc[j] = 0;
        else
            acc[j] = acc[j-1];

        for (; current<n; current++) {
            if (sortedData[current].second <= sortedTestData[j].second)
                acc[j]++;
            else
                break;
        }        
    }

    // Rearange data and copy results.
    for (diff_t k = 0; k<nt; k++)
        sortedTestData[sortedTestData[k].first].second = acc[k];

    for (diff_t k = 0; k<nt; k++, ++pOut)
        *pOut = sortedTestData[k].second / n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::empiricalMidCDF(InputIt first, InputIt last, double x)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);    
    
    double p = 0;                            
    for (InputIt xIt=first; xIt!=last; ++xIt) {
        if (*xIt == x)
            p += 0.5;        
        else
            p += (*xIt < x);                
    }

    auto n = (last - first);
    return p/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::empiricalMidCDF(InputIt first, InputIt last, OutIt pOut)
{
    auto n = (last - first);
    if (n < 1)
        throw RangeException("first, last", SOURCE_INFO);    
    
    // Sort observations.
    std::vector<std::pair<diff_t, typename std::remove_cvref_t<decltype(*first)>>> sortedData(n);
    
    auto x = first;
    for (diff_t k = 0; k<n; k++, ++x)
        sortedData[k] = std::make_pair(k, *x);
    
    std::sort(begin(sortedData), end(sortedData), [] (
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v1,
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v2)
        {return v1.second<v2.second;});

    // Calculate probabilities.
    std::vector<typename std::remove_cvref_t<decltype(*first)>> acc(n);    
    std::vector<typename std::remove_cvref_t<decltype(*first)>> adj(n);
    
    diff_t current = 0;
    for (diff_t j = 0; j<n; j++) {
        adj[j] = 0;
        if (j == 0)
            acc[j] = 0;
        else
            acc[j] = acc[j-1];

        if (current < n) {
            for (auto k = current; k>=0; k--) {
                if (sortedData[k].second == sortedData[j].second)            
                    adj[j]++;
                else
                    break;
            }
        }

        for (auto k = (current+1); k<n; k++) {
            if (sortedData[k].second == sortedData[j].second)
                adj[j]++;
            else
                break;
        }

        for (; current<n; current++) {
            if (sortedData[current].second < sortedData[j].second)
                acc[j]++;
            else
                break;
        }        
    }

    // Rearange data and copy results.
    for (diff_t k = 0; k<n; k++)
        sortedData[sortedData[k].first].second = acc[k] + 0.5*adj[k];

    for (diff_t k = 0; k<n; k++, ++pOut)
        *pOut = sortedData[k].second / n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::empiricalMidCDF(InputIt first, InputIt last, InputIt testFirst, 
    InputIt testLast, OutIt pOut)
{
    auto n = (last - first);
    auto nt = (testLast - testFirst);
    if (n < 1)
        throw RangeException("first, last", SOURCE_INFO);    
    if (nt < 1)
        throw ArgumentException("testLast, testFirst", exc_empty_range,
            SOURCE_INFO);

    // Sort observations.
    std::vector<std::pair<diff_t, typename std::remove_cvref_t<decltype(*first)>>> sortedData(n);
    
    auto x = first;
    for (diff_t k = 0; k<n; k++, ++x)
        sortedData[k] = std::make_pair(k, *x);
    
    std::sort(std::begin(sortedData), std::end(sortedData), [] (
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v1,
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v2)
        {return v1.second<v2.second;});

    std::vector<std::pair<diff_t, typename std::remove_cvref_t<decltype(*first)>>> sortedTestData(nt);
    
    auto xt = testFirst;
    for (diff_t k = 0; k<nt; k++, ++xt)
        sortedTestData[k] = std::make_pair(k, *xt);
    
    std::sort(std::begin(sortedTestData), std::end(sortedTestData), [] (
        typename std::remove_cvref_t<decltype(sortedTestData[0])> const& v1,
        typename std::remove_cvref_t<decltype(sortedTestData[0])> const& v2)
        {return v1.second<v2.second;});

    // Calculate probabilities.
    std::vector<typename std::remove_cvref_t<decltype(*testFirst)>> acc(nt);    
    std::vector<typename std::remove_cvref_t<decltype(*first)>> adj(nt);
    
    diff_t current = 0;
    for (diff_t j = 0; j<nt; j++) {
        adj[j] = 0;
        if (j == 0)
            acc[j] = 0;
        else
            acc[j] = acc[j-1];
        
        if (current < n) {
            for (auto k = current; k>=0; k--) {
                if (sortedData[k].second == sortedTestData[j].second)
                    adj[j]++;
                else
                    break;
            }
        }
        
        for (auto k = (current+1); k<n; k++) {
            if (sortedData[k].second == sortedTestData[j].second)
                adj[j]++;
            else
                break;
        }
        
        for (; current<n; current++) {
            if (sortedData[current].second < sortedTestData[j].second)
                acc[j]++;
            else
                break;
        }        
    }

    // Rearange data and copy results.
    for (diff_t k = 0; k<nt; k++)
        sortedTestData[sortedTestData[k].first].second = acc[k] + 0.5*adj[k];

    for (diff_t k = 0; k<nt; k++, ++pOut)
        *pOut = sortedTestData[k].second / n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::empiricalCompCDF(InputIt first, InputIt last, double x)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double p = 0;
    for (InputIt xIt = first; xIt != last; ++xIt)
        p += (*xIt >= x);

    auto n = (last - first);
    return p / n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::empiricalCompCDF(InputIt first, InputIt last, OutIt pOut)
{
    auto n = (last - first);
    if (n < 1)
        throw RangeException("first, last", SOURCE_INFO);

    // Sort observations.
    std::vector<std::pair<diff_t, typename std::remove_cvref_t<decltype(*first)>>> sortedData(n);
    
    auto x = first;
    for (diff_t k = 0; k<n; k++, ++x)
        sortedData[k] = std::make_pair(k, *x);

    std::sort(std::begin(sortedData), std::end(sortedData), [](
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v1,
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v2)
        {return v1.second>v2.second; });

    // Calculate probabilities.
    std::vector<typename std::remove_cvref_t<decltype(*first)>> acc(n);
    
    diff_t current = 0;
    for (diff_t j = 0; j<n; j++) {
        if (j == 0)
            acc[j] = 0;
        else
            acc[j] = acc[j - 1];

        for (; current<n; current++) {
            if (sortedData[current].second >= sortedData[j].second)
                acc[j]++;
            else
                break;
        }
    }

    // Rearange data and copy results.
    for (diff_t k = 0; k<n; k++)
        sortedData[sortedData[k].first].second = acc[k];

    for (diff_t k = 0; k<n; k++, ++pOut)
        *pOut = sortedData[k].second / n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::empiricalCompCDF(InputIt first, InputIt last, InputIt testFirst,
    InputIt testLast, OutIt pOut)
{
    auto n = (last - first);
    auto nt = (testLast - testFirst);
    if (n < 1)
        throw RangeException("first, last", SOURCE_INFO);
    if (nt < 1)
        throw ArgumentException("testLast, testFirst", exc_empty_range,
        SOURCE_INFO);

    // Sort observations.
    std::vector<std::pair<diff_t, typename std::remove_cvref_t<decltype(*first)>>> sortedData(n);
    
    auto x = first;
    for (diff_t k = 0; k<n; k++, ++x)
        sortedData[k] = std::make_pair(k, *x);

    std::sort(begin(sortedData), end(sortedData), [](
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v1,
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v2)
        {return v1.second>v2.second; });

    std::vector<std::pair<diff_t, typename std::remove_cvref_t<decltype(*first)>>> sortedTestData(nt);
    
    auto xt = testFirst;
    for (diff_t k = 0; k<nt; k++, ++xt)
        sortedTestData[k] = std::make_pair(k, *xt);

    std::sort(std::begin(sortedTestData), std::end(sortedTestData), [](
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v1,
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v2)
        {return v1.second>v2.second; });

    // Calculate probabilities.
    std::vector<typename std::remove_cvref_t<decltype(*testFirst)>> acc(nt);
    
    diff_t current = 0;
    for (diff_t j = 0; j<nt; j++) {
        if (j == 0)
            acc[j] = 0;
        else
            acc[j] = acc[j - 1];

        for (; current<n; current++) {
            if (sortedData[current].second >= sortedTestData[j].second)
                acc[j]++;
            else
                break;
        }
    }

    // Rearange data and copy results.
    for (diff_t k = 0; k<nt; k++)
        sortedTestData[sortedTestData[k].first].second = acc[k];

    for (diff_t k = 0; k<nt; k++, ++pOut)
        *pOut = sortedTestData[k].second / n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::empiricalCompMidCDF(InputIt first, InputIt last, double x)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    double p = 0;
    for (InputIt xIt = first; xIt != last; ++xIt) {
        if (*xIt == x)
            p += 0.5;
        else
            p += (*xIt > x);
    }

    auto n = (last - first);
    return p / n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::empiricalCompMidCDF(InputIt first, InputIt last, OutIt pOut)
{
    auto n = (last - first);
    if (n < 1)
        throw RangeException("first, last", SOURCE_INFO);

    // Sort observations.
    std::vector<std::pair<diff_t, typename std::remove_cvref_t<decltype(*first)>>> sortedData(n);
    
    auto x = first;
    for (diff_t k = 0; k<n; k++, ++x)
        sortedData[k] = std::make_pair(k, *x);

    std::sort(begin(sortedData), end(sortedData), [](
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v1,
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v2)
        {return v1.second>v2.second; });

    // Calculate probabilities.
    std::vector<typename std::remove_cvref_t<decltype(*first)>> acc(n);    
    std::vector<typename std::remove_cvref_t<decltype(*first)>> adj(n);
    
    diff_t current = 0;
    for (diff_t j = 0; j<n; j++) {
        adj[j] = 0;
        if (j == 0)
            acc[j] = 0;
        else
            acc[j] = acc[j - 1];

        if (current < n) {
            for (auto k = current; k >= 0; k--) {
                if (sortedData[k].second == sortedData[j].second)
                    adj[j]++;
                else
                    break;
            }
        }

        for (auto k = (current + 1); k<n; k++) {
            if (sortedData[k].second == sortedData[j].second)
                adj[j]++;
            else
                break;
        }

        for (; current<n; current++) {
            if (sortedData[current].second > sortedData[j].second)
                acc[j]++;
            else
                break;
        }
    }

    // Rearange data and copy results.
    for (diff_t k = 0; k<n; k++)
        sortedData[sortedData[k].first].second = acc[k] + 0.5*adj[k];

    for (diff_t k = 0; k<n; k++, ++pOut)
        *pOut = sortedData[k].second / n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::empiricalCompMidCDF(InputIt first, InputIt last, InputIt testFirst,
    InputIt testLast, OutIt pOut)
{
    auto n = (last - first);
    auto nt = (testLast - testFirst);
    if (n < 1)
        throw RangeException("first, last", SOURCE_INFO);
    if (nt < 1)
        throw ArgumentException("testLast, testFirst", exc_empty_range,
        SOURCE_INFO);

    // Sort observations.
    std::vector<std::pair<diff_t, typename std::remove_cvref_t<decltype(*first)>>> sortedData(n);
    
    auto x = first;
    for (diff_t k = 0; k<n; k++, ++x)
        sortedData[k] = std::make_pair(k, *x);

    std::sort(std::begin(sortedData), std::end(sortedData), [](
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v1,
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v2)
        {return v1.second>v2.second; });

    std::vector<std::pair<diff_t, typename std::remove_cvref_t<decltype(*first)>>> sortedTestData(nt);
    
    auto xt = testFirst;
    for (diff_t k = 0; k<nt; k++, ++xt)
        sortedTestData[k] = std::make_pair(k, *xt);

    std::sort(std::begin(sortedTestData), std::end(sortedTestData), [](
        typename std::remove_cvref_t<decltype(sortedTestData[0])> const& v1,
        typename std::remove_cvref_t<decltype(sortedTestData[0])> const& v2)
        {return v1.second>v2.second; });

    // Calculate probabilities.
    std::vector<typename std::remove_cvref_t<decltype(*testFirst)>> acc(nt);    
    std::vector<typename std::remove_cvref_t<decltype(*first)>> adj(nt);
    
    diff_t current = 0;
    for (diff_t j = 0; j<nt; j++) {
        adj[j] = 0;
        if (j == 0)
            acc[j] = 0;
        else
            acc[j] = acc[j - 1];

        if (current < n) {
            for (auto k = current; k >= 0; k--) {
                if (sortedData[k].second == sortedTestData[j].second)
                    adj[j]++;
                else
                    break;
            }
        }

        for (auto k = (current + 1); k<n; k++) {
            if (sortedData[k].second == sortedTestData[j].second)
                adj[j]++;
            else
                break;
        }

        for (; current<n; current++) {
            if (sortedData[current].second > sortedTestData[j].second)
                acc[j]++;
            else
                break;
        }
    }

    // Rearange data and copy results.
    for (diff_t k = 0; k<nt; k++)
        sortedTestData[sortedTestData[k].first].second = acc[k] + 0.5*adj[k];

    for (diff_t k = 0; k<nt; k++, ++pOut)
        *pOut = sortedTestData[k].second / n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::cdfToPval(InputIt pFirst, InputIt pLast, OutIt pOut, 
    ResultType pvalType)
{
    if (pFirst >= pLast)
        throw ArgumentException("pLast, pFirst",
            exc_empty_range, SOURCE_INFO);
    
    for (InputIt xT=pFirst; xT!=pLast; ++xT) {
        if ( (*xT<0) || (*xT>1) )
            throw ArgumentException("pLast, pFirst", exc_values_are_not_pvalues,
            SOURCE_INFO);
    }

    switch (pvalType) {
        case ResultType::LeftTailedPValue:            
            for (InputIt xT=pFirst; xT!=pLast; ++xT) {
                *pOut = *xT;    
                ++pOut;
            }
            break;

        case ResultType::RightTailedPValue:
            for (InputIt xT=pFirst; xT!=pLast; ++xT) {
                *pOut = 1-(*xT);    
                ++pOut;
            }
            break;

        case ResultType::TwoTailedPValue:
            for (InputIt xT=pFirst; xT!=pLast; ++xT) {
                if (*xT < 0.5)
                    *pOut = 2*(*xT);    
                else
                    *pOut = 2*(1-(*xT));    
                ++pOut;
            }
            break;
        
        default:
            throw ArgumentException("pvalType", exc_bad_pval_type, SOURCE_INFO);
            //break;
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::pvalToCDF(InputIt pFirst, InputIt pLast, OutIt pOut, 
    ResultType pvalType)
{
    if (pFirst >= pLast)
        throw ArgumentException("pLast, pFirst", exc_empty_range, SOURCE_INFO);
    
    for (InputIt xT=pFirst; xT!=pLast; ++xT) {
        if ( (*xT<0) || (*xT>1) )
            throw ArgumentException("pLast, pFirst", exc_values_are_not_pvalues,
            SOURCE_INFO);
    }

    switch (pvalType) {
        case ResultType::LeftTailedPValue:            
            for (InputIt xT=pFirst; xT!=pLast; ++xT) {
                *pOut = *xT;    
                ++pOut;
            }
            break;

        case ResultType::RightTailedPValue:
            for (InputIt xT=pFirst; xT!=pLast; ++xT) {
                *pOut = 1-(*xT);    
                ++pOut;
            }
            break;

        default:
            throw ArgumentException("pvalType", 
                exc_bad_pval_type, SOURCE_INFO);
            //break;
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::histogram(InputIt first, InputIt last, OutIt hOut, 
    OutIt bins, size_t nBins)
{
    double xMin = *first;
    double xMax = *first;    
    for (InputIt x=first; x!=last; ++x) {
        if (xMin>(*x))
            xMin = *x;
        if (xMax<(*x))
            xMax = *x;
    }
    histogram(first, last, hOut, bins, nBins, xMin, xMax);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::histogram(InputIt first, InputIt last, OutIt hOut, 
    OutIt bins, size_t nBins, double xMin, double xMax)
{
    if (nBins < 2) 
        throw ArgumentException("nBins", nBins, (size_t)2,
        RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    if (xMax <= xMin) 
        throw ArgumentException("xMin, xMax", exc_bad_bounds, SOURCE_INFO);
        
    // Sort data.
    auto size = (last - first);
    diff_t c=0;
    std::vector<double> xSort(size);
    for (InputIt x=first; x!=last; ++x)
        xSort[c++] = static_cast<double>(*x);
    std::sort(xSort.begin(), xSort.end());

    // Histogram.
    double lowerLimit = xMin;
    double upperLimit = xMin;
    diff_t lastIndex = 0;
    for (index_t i=0; i<nBins; i++) {
        // Bin value.
        *bins = xMin + (xMax-xMin)*((i+0.5)/static_cast<double>(nBins));
        lowerLimit = upperLimit;
        upperLimit = xMin + (xMax-xMin)*((i+1.0)/static_cast<double>(nBins));

        // Acumulated data.
        *hOut = 0;
        for (diff_t j=lastIndex; j<size; j++) {
            if (xSort[j]>upperLimit) {
                lastIndex = j;
                break;
            }
            else if (xSort[j]>=lowerLimit)
                (*hOut)++;
        }        
        
        // Increase iterators.
        ++hOut;
        ++bins;
    }
}

//=================================================================================================================
//        CIRCULAR DATA
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::pAxial(InputIt first, InputIt last, OutIt out,
    unsigned int p)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    if (p < 1) 
        throw ArgumentException("p", p, 0U, RelationalOperator::GreaterThan, SOURCE_INFO);

    for (auto x=first; x!=last; ++x) {
        *out = math::wrapTo2Pi(p*(*x));
        ++out;
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::meanDirection(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    for (auto x=first; x!=last; ++x)
        c+=Complex(std::cos(*x), std::sin(*x));
    
    return math::wrapTo2Pi(arg(c));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::meanDirection(InputIt1 first, InputIt1 last,
    InputIt2 wFirst)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    auto w = wFirst;
    for (auto x=first; x!=last; ++x, ++w)
        c+=(*w)*Complex(std::cos(*x), std::sin(*x));
    
    return math::wrapTo2Pi(arg(c));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::medianDirection(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    auto n = last - first;
    std::vector<double> t(n);
    for (int i=0; i<n; i++)
        t[i] = math::wrapTo2Pi(first[i]);

    // Differences.
    auto m1 = std::vector<diff_t>(n, 0);
    auto m2 = std::vector<diff_t>(n, 0);
    for (diff_t i=0; i<n; i++) {
        for (diff_t j=0; j<n; j++) {
            auto diff = math::angularDistance(t[i], t[j]);
            if (diff>=0)
                m1[j]++;
            else
                m2[j]++;
        }
    }
    std::vector<diff_t> dm(n);
    for (diff_t i=0; i<n; i++)
        dm[i] = std::abs(m1[i]-m2[i]);    

    // Minimum difference.
    auto minDif = math::minimum(std::begin(dm), std::end(dm));
    
    // Sub-array with the points that contains the median direction.
    int c = 0;
    for (diff_t i=0; i<n; i++)
        c += (dm[i] == minDif);        
    
    std::vector<double> ang(c);
    c = 0;
    for (diff_t i=0; i<n; i++) {
        if (dm[i] == minDif)
            ang[c++] = t[i];
    }

    // Median direction.
    double median = meanDirection(ang.begin(), ang.end());
    double mean = meanDirection(first, last);

    if (std::abs(median - mean) > std::abs(PI + median - mean))
        median = math::wrapTo2Pi(median + PI);
    
    return median;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::resultantLength(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    for (auto x=first; x!=last; ++x)
        c+=Complex(std::cos(*x), std::sin(*x));
            
    return std::abs(c);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::meanResultantLength(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    for (auto x=first; x!=last; ++x)
        c+=Complex(std::cos(*x), std::sin(*x));
        
    double n = static_cast<double>(last - first);
    return std::abs(c) / n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::meanResultantLength(InputIt1 first, InputIt1 last,
    InputIt2 wFirst)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    double n = 0.0;
    auto w = wFirst;    
    for (auto x=first; x!=last; ++x, ++w) {
        c += (*w)*Complex(std::cos(*x), std::sin(*x));
        n += (*w);
    }    
    
    return std::abs(c) / n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::sampleCircularVariance(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    for (auto x=first; x!=last; ++x)
        c+=Complex(std::cos(*x), std::sin(*x));
    
    double n = static_cast<double>(last - first);
    return  1. - std::abs(c) / n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type>&& nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::sampleCircularVariance(InputIt1 first, InputIt1 last,
    InputIt2 wFirst)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    double n = 0.0;
    auto w = wFirst;    
    for (auto x=first; x!=last; ++x, ++w) {
        c += (*w)*Complex(std::cos(*x), std::sin(*x));
        n += (*w);
    }    
    
    return 1. - std::abs(c) / n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::sampleAngularVariance(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    for (auto x=first; x!=last; ++x)
        c+=Complex(std::cos(*x), std::sin(*x));
    
    double n = static_cast<double>(last - first);
    return  2.0*(1. - std::abs(c) / n);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type>&& nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::sampleAngularVariance(InputIt1 first, InputIt1 last,
    InputIt2 wFirst)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    double n = 0.0;
    auto w = wFirst;    
    for (auto x=first; x!=last; ++x, ++w) {
        c += (*w)*Complex(std::cos(*x), std::sin(*x));
        n += (*w);
    }    
    
    return 2.0*(1. - std::abs(c) / n);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::sampleCircularStandardDeviation(InputIt first, 
    InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    for (auto x=first; x!=last; ++x)
        c += Complex(std::cos(*x), std::sin(*x));
    
    double n = static_cast<double>(last - first);
    return  std::sqrt(-2.*log(std::abs(c) / n));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::sampleCircularStandardDeviation(InputIt1 first, InputIt1 last,
    InputIt2 wFirst)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    double n = 0.0;
    auto w = wFirst;    
    for (auto x=first; x!=last; ++x, ++w) {
        c += (*w)*Complex(std::cos(*x), std::sin(*x));
        n += (*w);
    }    
    
    return std::sqrt(-2.*log(std::abs(c) / n));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::sampleAngularStandardDeviation(InputIt first, 
    InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    for (auto x=first; x!=last; ++x)
        c += Complex(std::cos(*x), std::sin(*x));
    
    double n = static_cast<double>(last - first);
    return  std::sqrt(2.*(1.-std::abs(c) / n));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type>&& nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::sampleAngularStandardDeviation(InputIt1 first, InputIt1 last,
    InputIt2 wFirst)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    double n = 0.0;
    auto w = wFirst;    
    for (auto x=first; x!=last; ++x, ++w) {
        c += (*w)*Complex(std::cos(*x), std::sin(*x));
        n += (*w);
    }    
    
    return std::sqrt(2.*(1.-std::abs(c) / n));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::sampleCircularDispersion(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex m1 = firstTrigonometricMoment(first, last);
    Complex m2 = secondCentralTrigonometricMoment(first, last);
    
    return (1.-std::abs(m2))/(2.*math::sqr(std::abs(m1)));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::sampleCircularKappa(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    double n = static_cast<double>(last - first);
    double k = 0;
    double r = meanResultantLength(first, last);

    if (r<0.53)
        k = 2*r + math::cube(r) + 5*std::pow(r, 5)/6;
    else if (r<0.85)
        k = -0.4 + 1.39*r +0.43/(1-r);
    else
        k = 1/(math::cube(r) -4*math::sqr(r) +3*r);

    if (n<15) {
        if (k<2)
            k = math::max(k-2/(n*k),0.0);
        else
            k = math::cube(n-1)*k/(math::cube(n)+n);
    }

    return k;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::sampleCircularSkewness(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    Complex m1 = firstTrigonometricMoment(first, last);
    Complex m2 = secondCentralTrigonometricMoment(first, last);

    return std::abs(m2)*std::sin(arg(m2) - 2*arg(m1))/std::pow(1.-std::abs(m1),3.0/2.0);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::sampleCircularSkewnessP(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    double b = 0;    
    double t = meanDirection(first, last);
    for (auto x=first; x!=last; ++x)
        b+=std::sin(2*(*x - t));
    
    double n = static_cast<double>(last - first);    
    return b/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::sampleCircularKurtosis(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);

    Complex m1 = firstTrigonometricMoment(first, last);
    Complex m2 = secondCentralTrigonometricMoment(first, last);
    Complex m2p = secondTrigonometricMoment(first, last);
    double r = std::abs(m1);

    return (std::abs(m2)*std::cos(math::wrapTo2Pi(arg(m2p)) - 2.*math::wrapTo2Pi(arg(m1))) -
        math::fourth_pwr(r))/math::sqr(1.-r);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
double nct::statistics::sampleCircularKurtosisP(InputIt first, InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    double k = 0;    
    double t = meanDirection(first, last);
    for (auto x=first; x!=last; ++x)
        k+=std::cos(2*(*x - t));

    double n = static_cast<double>(last - first);    
    return k/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
nct::Complex nct::statistics::firstTrigonometricMoment(InputIt first, 
    InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    for (auto x=first; x!=last; ++x)
        c+=Complex(std::cos(*x), std::sin(*x));
    
    double n = static_cast<double>(last - first);
    return c/n;
}    

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
nct::Complex nct::statistics::firstCentralTrigonometricMoment(InputIt first, 
    InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    double t = meanDirection(first, last);
    for (auto x=first; x!=last; ++x)
        c+=std::cos(*x - t);
    
    double n = static_cast<double>(last - first);
    return c/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
nct::Complex nct::statistics::secondTrigonometricMoment(InputIt first, 
    InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    for (auto x=first; x!=last; ++x)
        c += Complex(std::cos(2*(*x)), std::sin(2*(*x)));
    
    double n = static_cast<double>(last - first);
    return c/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
nct::Complex nct::statistics::secondCentralTrigonometricMoment(InputIt first,
    InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    double t = meanDirection(first, last);
    for (auto x=first; x!=last; ++x)
        c+=Complex(std::cos(2*(*x - t)), std::sin(2*(*x - t)));
        
    double n = static_cast<double>(last - first);
    return c/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
nct::Complex nct::statistics::thirdTrigonometricMoment(InputIt first, 
    InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    for (auto x=first; x!=last; ++x)
        c += Complex(std::cos(3*(*x)), std::sin(3*(*x)));

    double n = static_cast<double>(last - first);
    return c/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
nct::Complex nct::statistics::thirdCentralTrigonometricMoment(InputIt first, 
    InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    double t = meanDirection(first, last);
    for (auto x=first; x!=last; ++x)
        c += Complex(std::cos(3* (*x - t)), std::sin(3*(*x - t)));

    double n = static_cast<double>(last - first);
    return c/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
nct::Complex nct::statistics::fourthTrigonometricMoment(InputIt first, 
    InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    for (auto x=first; x!=last; ++x)
        c += Complex(std::cos(4*(*x)), std::sin(4*(*x)));

    double n = static_cast<double>(last - first);
    return c/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
nct::Complex nct::statistics::fourthCentralTrigonometricMoment(InputIt first,
    InputIt last)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    double t = meanDirection(first, last);
    for (auto x=first; x!=last; ++x)
        c += Complex(std::cos(4*(*x - t)), std::sin(4*(*x - t)));

    double n = static_cast<double>(last - first);
    return c/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
nct::Complex nct::statistics::kTrigonometricMoment(InputIt first, InputIt last,
    unsigned int k)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    for (auto x=first; x!=last; ++x)
        c += Complex(std::cos(k*(*x)), std::sin(k*(*x)));

    double n = static_cast<double>(last - first);
    return c/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt> requires nct::Arithmetic<typename InputIt::value_type>
nct::Complex nct::statistics::kCentralTrigonometricMoment(InputIt first, 
    InputIt last, unsigned int k)
{
    if (first >= last)
        throw RangeException("first, last", SOURCE_INFO);
    
    Complex c(0,0);    
    double t = meanDirection(first, last);
    for (auto x=first; x!=last; ++x)
         c += Complex(std::cos(k*(*x - t)), std::sin(k*(*x - t)));
    
    double n = static_cast<double>(last - first);
    return c/n;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::CircularLinearAssociation(InputIt1 xFirst, InputIt1 xLast, 
    InputIt2 yFirst, InputIt2 yLast)
{
    auto n = xLast - xFirst;    
    if (n<1)
        throw ArgumentException("x, y", exc_empty_range, SOURCE_INFO);
    
    if ((yLast - yFirst) != n)
        throw ArgumentException("x, y", exc_two_ranges_of_different_sizes, SOURCE_INFO);

    // Correlations.
    std::vector<double> s(n);
    std::vector<double> c(n);
    auto x = xFirst;
    for (diff_t i=0; i<n; i++, ++x) {
        s[i] = std::sin(*x);
        c[i] = std::cos(*x);
    }
    double rls = pearsonCorrelation(yFirst, yLast, s.cbegin(), s.cend());
    double rlc = pearsonCorrelation(yFirst, yLast, c.cbegin(), c.cend());
    double rcs = pearsonCorrelation(s.cbegin(), s.cend(), c.cbegin(), c.cend());

    // Angular-linear correlation.
    return std::sqrt((rlc*rlc + rls*rls - 2*rlc*rls*rcs)/(1.0 - rcs*rcs));
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt1, std::random_access_iterator InputIt2>
requires nct::Arithmetic<typename InputIt1::value_type> && nct::Arithmetic<typename InputIt2::value_type>
double nct::statistics::CircularCircularAssociation(InputIt1 xFirst, InputIt1 xLast, 
    InputIt2 yFirst, InputIt2 yLast)
{
    auto n = xLast - xFirst;    
    if (n<1)
        throw ArgumentException("x, y", exc_empty_range, SOURCE_INFO);
    
    if ((yLast - yFirst) != n)
        throw ArgumentException("x, y", exc_two_ranges_of_different_sizes, SOURCE_INFO);

    // Mean directions.
    double m1 = meanDirection(xFirst, xLast);
    double m2 = meanDirection(yFirst, yLast);

    // Coefficient.
    double num = 0;
    double den1 = 0;
    double den2 = 0;
    auto x = xFirst;
    auto y = yFirst;
    for (diff_t i=0; i<n; i++, ++x, ++y) {
        double t1 = std::sin(*x - m1);
        double t2 = std::sin(*y - m2);
        num += t1*t2;
        den1 += t1*t1;
        den2 += t2*t2;
    }
    
    return num / std::sqrt(den1*den2);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::circularRanks(InputIt xFirst, InputIt xLast, OutIt rFirst)
{
    auto n = xLast - xFirst;

    // Sort observations.
    std::vector<std::pair<diff_t, typename std::remove_cvref_t<decltype(*xFirst)>>> sortedData(n);
    
    auto x = xFirst;
    for (diff_t k = 0; k<n; k++, ++x)
        sortedData[k] = std::make_pair(k, math::wrapTo2Pi(*x));

    std::sort(begin(sortedData), end(sortedData), [](
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v1,
        typename std::remove_cvref_t<decltype(sortedData[0])> const& v2)
        {return v1.second<v2.second;});

    // Ranks.
    std::vector<typename std::remove_cvref_t<decltype(*rFirst)>> rt(n);
    for (diff_t k = 0; k<n; k++)
        rt[sortedData[k].first] = 
        static_cast<typename std::remove_cvref_t<decltype(*rFirst)>>(TWO_PI*(k+1.0)/n);

    std::copy(begin(rt), end(rt), rFirst);    

}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::circularHistogram(InputIt first, InputIt last,
    OutIt hOut, OutIt bins, size_t nBins)
{
    circularHistogram(first, last, hOut, bins, nBins, 0);
}

//-----------------------------------------------------------------------------------------------------------------
template<std::random_access_iterator InputIt, typename OutIt>
requires std::output_iterator<OutIt, typename InputIt::value_type> && 
    nct::Numeric<typename InputIt::value_type>
void nct::statistics::circularHistogram(InputIt first, InputIt last,
    OutIt hOut, OutIt bins, size_t nBins, double hIni)
{
    
    if (nBins < 2) 
        throw ArgumentException("nBins", nBins, (size_t)2, RelationalOperator::GreaterThanOrEqualTo,
            SOURCE_INFO);
    if (last <= first) 
        throw RangeException("first, last", SOURCE_INFO);
    
    hIni = math::wrapTo2Pi(hIni);
    
    // Sort data.
    auto n = last - first;
    diff_t c=0;
    std::vector<double> xSort(n);
    for (auto x=first; x!=last; ++x)
        xSort[c++] = math::wrapTo2Pi(*x - hIni);
    std::sort(xSort.begin(), xSort.end());

    // Histogram.
    double lowerLimit = 0;
    double upperLimit = 0;
    diff_t lastIndex = 0;
    for (index_t i=0; i<nBins; i++) {
        *bins = math::wrapTo2Pi(hIni + TWO_PI*(static_cast<double>(i+0.5)/static_cast<double>(nBins)));
        lowerLimit = upperLimit;
        upperLimit = TWO_PI*((i+1.0)/static_cast<double>(nBins));

        *hOut = 0;
        for (auto j=lastIndex; j<n; j++) {
            if (xSort[j]>(upperLimit)) {
                lastIndex = j;
                break;
            }
            else if (xSort[j]>=(lowerLimit))
                (*hOut)++;
        }        

        ++hOut;
        ++bins;
    }
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
