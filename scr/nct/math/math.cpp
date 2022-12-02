//=================================================================================================================
/**
 *  @file       math.cpp
 *  @brief      Implementation of the functions defined in the nct::math namespace.
 *  @details    This file contains the implementation of the functions declared in the nct::math namespace.    
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
#include <nct/math/math.h>

#include <array>
#include <numeric>
#include <thread>
#include <future>

//=================================================================================================================
//       CONSTANTS
//=================================================================================================================

/** List of known prime numbers. */
constexpr std::array knownPrimes
{
      2u,     3u,     5u,     7u,    11u,    13u,    17u,    19u,
     23u,    29u,    31u,    37u,    41u,    43u,    47u,    53u,
     59u,    61u,    67u,    71u,    73u,    79u,    83u,    89u,
     97u,   101u,   103u,   107u,   109u,   113u,   127u,   131u,
    137u,   139u,   149u,   151u,   157u,   163u,   167u,   173u,
    179u,   181u,   191u,   193u,   197u,   199u,   211u,   223u,
    227u,   229u,   233u,   239u,   241u,   251u,   257u,   263u,
    269u,   271u,   277u,   281u,   283u,   293u,   307u,   311u,
    313u,   317u,   331u,   337u,   347u,   349u,   353u,   359u,
    367u,   373u,   379u,   383u,   389u,   397u,   401u,   409u,
    419u,   421u,   431u,   433u,   439u,   443u,   449u,   457u,
    461u,   463u,   467u,   479u,   487u,   491u,   499u,   503u,
    509u,   521u,   523u,   541u,   547u,   557u,   563u,   569u,
    571u,   577u,   587u,   593u,   599u,   601u,   607u,   613u,
    617u,   619u,   631u,   641u,   643u,   647u,   653u,   659u,
    661u,   673u,   677u,   683u,   691u,   701u,   709u,   719u,
    727u,   733u,   739u,   743u,   751u,   757u,   761u,   769u,
    773u,   787u,   797u,   809u,   811u,   821u,   823u,   827u,
    829u,   839u,   853u,   857u,   859u,   863u,   877u,   881u,
    883u,   887u,   907u,   911u,   919u,   929u,   937u,   941u,
    947u,   953u,   967u,   971u,   977u,   983u,   991u,   997u
};

/** Maximum known prime. */
constexpr unsigned int maxKnownPrime {997};

//=================================================================================================================
//       FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
double nct::math::factorial(unsigned int n)
{
    static constinit const unsigned int nTop {171};
    static std::atomic<bool> calledBefore = false;
    static std::mutex dataMutex;    
    static double a[nTop];    

    if (!calledBefore) {
        std::lock_guard<std::mutex> lk(dataMutex);

        a[0] = 1.0;
        for (unsigned int i = 1; i < nTop; i++)
            a[i] = i * a[i - 1];

        calledBefore = true;
    }

    if (n >= nTop)
        throw ArgumentException("n", n, nTop, RelationalOperator::LowerThan, SOURCE_INFO);

    return a[n];
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::logFactorial(unsigned int n) noexcept
{
    static constinit const unsigned int nTop {1000};
    static std::atomic<bool> calledBefore = false;
    static std::mutex dataMutex;
    
    static double a[nTop];

    if (!calledBefore) {
        std::lock_guard<std::mutex> lk(dataMutex);

        a[0] = 0.0;
        for (unsigned int i = 1; i < nTop; i++)
            a[i] = a[i - 1] + std::log(static_cast<double>(i));

        calledBefore = true;
    }

    if (n < nTop)
        return a[n];

    double r = a[nTop - 1];
    for (unsigned int i = nTop; i <= n; i++)
        r += std::log(static_cast<double>(i));

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::binCoefficient(unsigned int n, unsigned int k)
{
    if (k > n)
        throw ArgumentException("k, n", exc_bad_binomial_coefficient, SOURCE_INFO);
    if (n < 171)
        return std::floor(0.5 + factorial(n) / (factorial(k) * factorial(n - k)));
    return std::floor(0.5 + exp(logFactorial(n) - logFactorial(k) - logFactorial(n - k)));
}

//-----------------------------------------------------------------------------------------------------------------
nct::Complex nct::math::rootOfComplex(const Complex& z, unsigned int n, unsigned int k) noexcept
{
    if (n == 0)
        return 1.0;
    else if (n == 1)
        return z;

    double r = std::pow(std::abs(z), 1. / n);
    double t = (std::arg(z) + TWO_PI * k) / static_cast<double>(n);
    return std::polar(r, t);
}

//-----------------------------------------------------------------------------------------------------------------
unsigned int nct::math::powerMod(unsigned int x, unsigned int n, unsigned int p) noexcept
{
    return static_cast<unsigned int>(powerMod(static_cast<unsigned long long>(x), 
        static_cast<unsigned long long>(n), static_cast<unsigned long long>(p)));
};

//-----------------------------------------------------------------------------------------------------------------
unsigned long long nct::math::powerMod(unsigned long long x, unsigned long long n,
    unsigned long long p) noexcept
{
    unsigned long long res = 1;
    x %= p;

    while (n > 0) {
        if (n & 1)
            res = ((res%p)*(x%p)) % p;

        n = n >> 1;
        x = ((x%p)*(x%p)) % p;
    }

    return res;
};

//-----------------------------------------------------------------------------------------------------------------
unsigned int nct::math::inverseMod(unsigned int x, unsigned int p)
{
    if (!areCoprimes(x, p))
        throw ArgumentException("x, p", exc_non_coprimes_numbers, SOURCE_INFO);

    if (p == 1)
        throw ArgumentException("p", p, (unsigned int)1, 
            RelationalOperator::GreaterThan, SOURCE_INFO);
    
    auto p0 = p;
    int k = 1;
    int l = 0;    

    while (x > 1) {
        auto quotient = x / p;
        auto temp = p;

        p = x % p;
        x = temp;
        temp = l;

        l = k - quotient * l;
        k = temp;
    }

    if (k < 0)
        k += p0;

    return static_cast<unsigned int>(k);
}

//-----------------------------------------------------------------------------------------------------------------
unsigned long long nct::math::inverseMod(unsigned long long x, unsigned long long p)
{
    if (!areCoprimes(x, p))
        throw ArgumentException("x, p", exc_non_coprimes_numbers, SOURCE_INFO);

    if (p == 1)
        throw ArgumentException("p", p, (unsigned long long)1, 
            RelationalOperator::GreaterThan, SOURCE_INFO);

    auto p0 = p;
    long long k = 1;
    long long l = 0;

    while (x > 1) {
        auto quotient = x / p;
        auto temp = p;

        p = x % p;
        x = temp;
        temp = l;

        l = k - quotient * l;
        k = temp;
    }

    if (k < 0)
        k += p0;

    return static_cast<unsigned long long>(k);
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::math::isPrime(unsigned int n) noexcept
{
    if ((n == 0) || (n == 1))
        return false;

    if ((n == 2) || (n == 3))
        return true;

    auto maxn = static_cast<unsigned int>(std::sqrt(n) + 0.5);
    
    for (auto testPrime : knownPrimes) {
        if ((n % testPrime) == 0)
            return false;

        if (testPrime > maxn)
            return true;
    }
    

    for (unsigned int i = 6 * ((maxKnownPrime / 6) + 1); i <= (maxn+1); i += 6) {
        if ((n % (i - 1)) == 0)
            return false;

        if ((n % (i + 1)) == 0)
            return false;
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::math::isPrime(unsigned long long n) noexcept
{
    if ((n == 0) || (n == 1))
        return false;

    if ((n == 2) || (n == 3))
        return true;

    auto maxn = static_cast<unsigned long long>(std::sqrt(n) + 0.5);

    for (auto testPrime : knownPrimes) {
        if ((n % testPrime) == 0)
            return false;

        if (testPrime > maxn)
            return true;
    }

    for (unsigned long long i = 6 * ((maxKnownPrime / 6) + 1); i <= (maxn + 1); i += 6) {
        if ((n % (i - 1)) == 0)
            return false;

        if ((n % (i + 1)) == 0)
            return false;
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------------
unsigned int nct::math::nextPrime(unsigned int n) noexcept
{
    if (n < maxKnownPrime) {
        auto it = std::upper_bound(knownPrimes.begin(), knownPrimes.end(), n);
        return *it;
    }

    unsigned int k = 6 * ((n / 6) + 1);

    bool primeOk = false;        
    while (!primeOk) {
        if (((k - 1) > n) && isPrime(k - 1)) {
            k--;
            primeOk = true;
        }
        else if (isPrime(k + 1)) {
            k++;
            primeOk = true;
        }
        else {
            k += 6;
        }        
    }

    return k;
}

//-----------------------------------------------------------------------------------------------------------------
unsigned long long nct::math::nextPrime(unsigned long long n) noexcept
{
    if (n < maxKnownPrime) {
        auto it = std::upper_bound(knownPrimes.begin(), knownPrimes.end(), static_cast<unsigned int>(n));
        return *it;
    }

    unsigned long long k = 6 * ((n / 6) + 1);

    bool primeOk = false;
    while (!primeOk) {
        if (((k - 1) > n) && isPrime(k - 1)) {
            k--;
            primeOk = true;
        }
        else if (isPrime(k + 1)) {
            k++;
            primeOk = true;
        }
        else {
            k += 6;
        }
    }

    return k;
}

//-----------------------------------------------------------------------------------------------------------------
std::vector<unsigned int> nct::math::primeNumbers(unsigned int n)
{
    if (n <= 1)
        return std::vector<unsigned int>();

    std::vector<bool> testIndices(n+(size_t)1, true);

    testIndices[0] = false;
    testIndices[1] = false;
    
    for (unsigned int i = 2; i <= n; i++) {
        if (!testIndices[i])
            continue;

        for (unsigned int j = 2*i; j <= n; j += i)
            testIndices[j] = false;
    }

    std::vector<unsigned int> pr;
    for (unsigned int i = 2; i <= n; i++) {
        if (testIndices[i])
            pr.push_back(i);
    }


    return pr;
}

//-----------------------------------------------------------------------------------------------------------------
std::vector<unsigned long long> nct::math::primeNumbers(unsigned long long n)
{
    if (n <= 1)
        return std::vector<unsigned long long>();

    std::vector<bool> testIndices(static_cast<size_t>(n + 1), true);

    testIndices[0] = false;
    testIndices[1] = false;

    for (unsigned long long i = 2; i <= n; i++) {
        if (!testIndices[static_cast<size_t>(i)])
            continue;

        for (unsigned long long j = 2*i; j <= n; j += i)
            testIndices[static_cast<size_t>(j)] = false;
    }

    std::vector<unsigned long long> pr;
    for (unsigned long long i = 2; i <= n; i++) {
        if (testIndices[static_cast<size_t>(i)])
            pr.push_back(i);
    }


    return pr;
}

//-----------------------------------------------------------------------------------------------------------------
std::vector<unsigned int> nct::math::primeFactors(unsigned int n)
{
    if (n <= 1)
        return std::vector<unsigned int>();

    std::vector<unsigned int> factors;

    for (auto testPrime : knownPrimes) {
        while ((n % testPrime) == 0) {
            n /= testPrime;
            factors.push_back(testPrime);
        }

        if (n == 1)
            break;
    }

    auto maxn = static_cast<unsigned int>(std::sqrt(n) + 0.5);

    unsigned int k = 6 * ((maxKnownPrime / 6) + 1);
    while ((n != 1) && (k < n)) {
        auto testFactor = k - 1;
        while (n % testFactor == 0) {
            n /= testFactor;
            factors.push_back(testFactor);
            maxn = static_cast<unsigned int>(std::sqrt(n) + 0.5);
        }

        testFactor = k + 1;
        while (n % testFactor == 0) {
            n /= testFactor;
            factors.push_back(testFactor);
            maxn = static_cast<unsigned int>(std::sqrt(n) + 0.5);
        }

        k += 6;

        if ((k - 1) > maxn)
            break;
    }

    if (n != 1)
        factors.push_back(n);

    return factors;
}

//-----------------------------------------------------------------------------------------------------------------
std::vector<unsigned long long> nct::math::primeFactors(unsigned long long n)
{
    if (n <= 1)
        return std::vector<unsigned long long>();

    std::vector<unsigned long long> factors;

    for (auto testPrime : knownPrimes) {
        while ((n % testPrime) == 0) {
            n /= testPrime;
            factors.push_back(testPrime);
        }

        if (n == 1)
            break;
    }

    auto maxn = static_cast<unsigned long long>(std::sqrt(n) + 0.5);

    unsigned long long k = 6 * ((maxKnownPrime / 6) + 1);
    while ((n != 1) && (k < n)) {
        auto testFactor = k - 1;
        while (n % testFactor == 0) {
            n /= testFactor;
            factors.push_back(testFactor);
            maxn = static_cast<unsigned long long>(std::sqrt(n) + 0.5);
        }

        testFactor = k + 1;
        while (n % testFactor == 0) {
            n /= testFactor;
            factors.push_back(testFactor);
            maxn = static_cast<unsigned long long>(std::sqrt(n) + 0.5);
        }

        k += 6;

        if ((k - 1) > maxn)
            break;
    }

    if (n != 1)
        factors.push_back(n);

    return factors;
}

//-----------------------------------------------------------------------------------------------------------------
unsigned int nct::math::primitiveRoot(unsigned int n)
{
    if (!isPrime(n))
        throw ArgumentException("n", exc_non_prime_number, SOURCE_INFO);

    auto relativePrimes = n - 1;
    auto factors = primeFactors(relativePrimes);

    unsigned int r = 2;
    bool valOk = true;

    while (r <= relativePrimes) {
        valOk = true;
        for (const auto& fi : factors) {
            if (powerMod(r, relativePrimes / fi, n) == 1) {
                valOk = false;
                break;
            }
        }

        if (valOk)
            break;

        r++;
    }

    if (!valOk)
        throw OperationException(exc_error_finding_primitive_root, SOURCE_INFO);

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
unsigned long long nct::math::primitiveRoot(unsigned long long n)
{
    if (!isPrime(n))
        throw ArgumentException("n", exc_non_prime_number, SOURCE_INFO);

    auto relativePrimes = n - 1;
    auto factors = primeFactors(relativePrimes);

    unsigned long long r = 2;
    bool valOk = true;

    while (r <= relativePrimes) {
        valOk = true;
        for (const auto& fi : factors) {
            if (powerMod(r, relativePrimes / fi, n) == 1) {
                valOk = false;
                break;
            }
        }

        if (valOk)
            break;        

        r++;
    }

    if (!valOk)
        throw ArgumentException("n", exc_error_finding_primitive_root, SOURCE_INFO);

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::math::areCoprimes(unsigned int a, unsigned int b) noexcept
{
    if ((a == 0) || (b == 0))
        return false;

    return std::gcd(a, b) == 1;
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::math::areCoprimes(unsigned long long a, unsigned long long b) noexcept
{
    if ((a == 0) || (b == 0))
        return false;

    return std::gcd(a, b) == 1;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::math::mostSignificantDigit(double num) noexcept
{
    if ((num == 0) || (std::isinf(num)) || (std::isnan(num)))
        return 0;

    num = std::abs(num);

    while (num < 1)
        num *= 10;

    while (num > 10)
        num /= 10;

    return static_cast<int>(num + 100 * EPS) % 10;
}

//-----------------------------------------------------------------------------------------------------------------
int nct::math::mostSignificantDigitPosition(double num) noexcept
{
    if ((num == 0) || (std::isinf(num)) || (std::isnan(num)))
        return 0;

    num = std::abs(num);

    int pos = 0;

    while (num < 1) {
        num *= 10;
        pos--;
    }

    while (num > 10) {
        num /= 10;
        pos++;
    }

    return pos;
}

//-----------------------------------------------------------------------------------------------------------------
std::pair<double, double> nct::math::solveQuadraticEq(double a, double b, double c)
{
    if (a == 0)
        throw ArgumentException("a", exc_null_quadratic_term, SOURCE_INFO);

    auto disc = b*b  - 4*a*c;        
    if (disc < 0)
        throw ArithmeticException(exc_negative_discriminant, SOURCE_INFO);

    auto q = -0.5*(b + sign(b)*std::sqrt(disc));
    auto r1 = q / a;
    auto r2 = c / q;
    return std::make_pair(r1, r2);
}

//-----------------------------------------------------------------------------------------------------------------
std::pair<nct::Complex, nct::Complex> nct::math::solveQuadraticEq(
    const Complex& a, const Complex& b, const Complex& c)
{
    if (a == 0.0)
        throw ArgumentException("a", exc_null_quadratic_term, SOURCE_INFO);

    auto srt = std::sqrt(b*b - 4.0*a*c);
    
    if (std::real(std::conj(b)*srt) <= 0)
        srt*=-1.0;
    
    auto q = -0.5*(b + srt);
    auto r1 = q / a;
    auto r2 = c / q;

    return std::make_pair(r1, r2);
}

//-----------------------------------------------------------------------------------------------------------------
std::pair<nct::Complex, nct::Complex> nct::math::solveQuadraticEqC(double a, double b, double c)
{
    if (a == 0)
        throw ArgumentException("a", exc_null_quadratic_term, SOURCE_INFO);

    Complex r1 = 0.;
    Complex r2 = 0.;
    auto disc = b * b - 4 * a * c;
    if (disc >= 0) {
        double q = -0.5 * (b + sign(b) * std::sqrt(disc));
        r1 = q / a;
        r2 = c / q;
        return std::make_pair(r1, r2);
    }

    auto q = -0.5 * (b + sign(b) * std::sqrt(Complex(disc, 0.0)));
    r1 = q / a;
    r2 = c / q;

    return std::make_pair(r1, r2);
}

//-----------------------------------------------------------------------------------------------------------------
std::tuple<double, double, double> nct::math::solveCubicEq(
    double a, double b, double c, double d)
{
    if (a == 0.0)
        throw ArgumentException("a", exc_null_cubic_term, SOURCE_INFO);

    auto disc = 18.*a*b*c*d - 4.*b*b*b*d + b*b*c*c - 4.*a*c*c*c - 27.*a*a*d*d;
    auto disc0 = b*b - 3.*a*c;
    
    if (disc < 0)
        throw OperationException(exc_complex_roots, SOURCE_INFO);
    
    double r1 = 0;
    double r2 = 0;
    double r3 = 0;

    if (disc == 0) {
        if (disc0 ==0) {
            r1 = -b / (3.0 *a);
            r2 = r1;
            r3 = r1;
        }
        else {
            r1 = (9.*a*d - b*c) / (2.*disc0);
            r2 = r1;
            r3 = (4.*a*b*c - 9.*a*a*d - b*b*b) / (a*disc0);
        }
    }
    else {
        auto disc1 = 2.*b*b*b - 9.*a*b*c + 27.*a*a*d;
        auto cc1 = std::pow((disc1 + std::sqrt(Complex(disc1*disc1 - 4.*disc0*disc0*disc0))) / 2.0, 
            1. / 3.);
        auto cc2 = std::pow((disc1 - std::sqrt(Complex(disc1*disc1 - 4.*disc0*disc0*disc0))) / 2.0, 
            1. / 3.);
        auto cc = (std::abs(cc1) > std::abs(cc2))? cc1 : cc2;
        if (cc != 0.) {
            auto u2 = Complex(-0.5, SQRT3 / 2.);
            auto u3 = Complex(-0.5, -SQRT3 / 2.);
            r1 = -(b + std::real(cc + disc0 / cc)) / (3.*a);
            r2 = -(b + std::real(cc*u2 + disc0 / (cc*u2))) / (3.*a);
            r3 = -(b + std::real(cc*u3 + disc0 / (cc*u3))) / (3.*a);
        }
        else {
            // Use an alternative method in this case.
            auto q = disc0 / (9.*a*a);
            auto r = disc1 / (54.*a*a*a);
            auto rr = r*r;
            auto qqq = q*q*q;

            if (rr >= qqq)
                throw OperationException(exc_complex_roots, SOURCE_INFO);

            auto theta = std::acos(r / std::sqrt(qqq));
            auto sr = std::sqrt(q);
            auto t1 = -b / (3 * a);
            r1 = t1 - 2.0*sr*std::cos(theta / 3.0);
            r2 = t1 - 2.0*sr*std::cos((theta + TWO_PI) / 3.0);
            r3 = t1 - 2.0*sr*std::cos((theta - TWO_PI) / 3.0);
        }
    }    

    return std::make_tuple(r1, r2, r3);
}

//-----------------------------------------------------------------------------------------------------------------
std::tuple<nct::Complex, nct::Complex, nct::Complex> nct::math::solveCubicEq(
    const Complex& a, const Complex& b, const Complex& c, const Complex& d)
{
    if (a == 0.0)
        throw ArgumentException("a", exc_null_cubic_term, SOURCE_INFO);

    Complex r1 = 0;
    Complex r2 = 0;
    Complex r3 = 0;

    auto disc = 18. * a * b * c * d - 4. * b * b * b * d + b * b * c * c - 
        4. * a * c * c * c - 27. * a * a * d * d;
    auto disc0 = b * b - 3. * a * c;
    if (disc == 0.0) {
        if (disc0 == 0.0) {
            r1 = -b / (3.0 * a);
            r2 = r1;
            r3 = r1;
        }
        else {
            r1 = (9. * a * d - b * c) / (2. * disc0);
            r2 = r1;
            r3 = (4. * a * b * c - 9. * a * a * d - b * b * b) / (a * disc0);
        }
    }
    else {
        auto disc1 = 2. * b * b * b - 9. * a * b * c + 27. * a * a * d;
        auto cc1 = pow((disc1 + sqrt(disc1 * disc1 - 4. * disc0 * disc0 * disc0)) / 2.0, 1. / 3.);
        auto cc2 = pow((disc1 - sqrt(disc1 * disc1 - 4. * disc0 * disc0 * disc0)) / 2.0, 1. / 3.);
        auto cc = (std::abs(cc1) > std::abs(cc2)) ? cc1 : cc2;

        if (cc != 0.) {
            auto u2 = Complex(-0.5, SQRT3 / 2.);
            auto u3 = Complex(-0.5, -SQRT3 / 2.);
            r1 = -(b + cc + disc0 / cc) / (3. * a);
            r2 = -(b + cc * u2 + disc0 / (cc * u2)) / (3. * a);
            r3 = -(b + cc * u3 + disc0 / (cc * u3)) / (3. * a);
        }
        else {
            // Use an alternative method in this case.
            auto q = disc0 / (9. * a * a);
            auto r = disc1 / (54. * a * a * a);
            auto rr = r * r;
            auto qqq = q * q * q;

            auto srt = std::sqrt(rr - qqq);
            if (std::real(std::conj(r) * srt) <= 0)
                srt *= -1.0;

            Complex A = -std::pow(r + srt, 1.0 / 3.0);
            Complex B = 0.0;
            if (A != 0.0)
                B = q / A;

            auto t1 = -b / (3. * a);
            auto t2 = -0.5 * (A + B);
            auto t3 = I1 * 0.5 * SQRT3 * (A - B);

            r1 = t1 + A + B;
            r2 = t1 + t2 + t3;
            r3 = t1 + t2 - t3;
        }
    }

    return std::make_tuple(r1, r2, r3);
}

//-----------------------------------------------------------------------------------------------------------------
std::tuple<nct::Complex, nct::Complex, nct::Complex> nct::math::solveCubicEqC(
    double a, double b, double c, double d)
{
    if (a == 0.0)
        throw ArgumentException("a", exc_null_cubic_term, SOURCE_INFO);

    Complex r1 = 0;
    Complex r2 = 0;
    Complex r3 = 0;

    auto disc = 18.*a*b*c*d - 4.*b*b*b*d + b*b*c*c - 4.*a*c*c*c - 27.*a*a*d*d;
    auto disc0 = b*b - 3.*a*c;
    if (disc == 0.0) {
        if (disc0 == 0.0) {
            r1 = -b / (3.0 *a);
            r2 = r1;
            r3 = r1;
        }
        else {
            r1 = (9.*a*d - b*c) / (2.*disc0);
            r2 = r1;
            r3 = (4.*a*b*c - 9.*a*a*d - b*b*b) / (a*disc0);
        }
    }
    else {
        auto disc1 = 2.*b*b*b - 9.*a*b*c + 27.*a*a*d;
        auto cc1 = std::pow((disc1 + std::sqrt(Complex(disc1*disc1 - 4.*disc0*disc0*disc0))) / 2.0, 
            1. / 3.);
        auto cc2 = std::pow((disc1 - std::sqrt(Complex(disc1*disc1 - 4.*disc0*disc0*disc0))) / 2.0, 
            1. / 3.);
        auto cc = (std::abs(cc1) > std::abs(cc2)) ? cc1 : cc2;

        if (cc != 0.) {
            auto u2 = Complex(-0.5, SQRT3 / 2.);
            auto u3 = Complex(-0.5, -SQRT3 / 2.);
            r1 = -(b + cc + disc0 / cc) / (3.*a);
            r2 = -(b + cc*u2 + disc0 / (cc*u2)) / (3.*a);
            r3 = -(b + cc*u3 + disc0 / (cc*u3)) / (3.*a);
        }
        else {
            // Use an alternative method in this case.
            auto q = disc0 / (9.*a*a);
            auto r = disc1 / (54.*a*a*a);
            auto rr = r*r;
            auto qqq = q*q*q;

            if (rr < qqq) {
                double theta = acos(r / std::sqrt(qqq));
                double sr = std::sqrt(q);
                auto t1 = -b / (3 * a);
                r1 = t1 - 2.0*sr*std::cos(theta / 3.0);
                r2 = t1 - 2.0*sr*std::cos((theta + TWO_PI) / 3.0);
                r3 = t1 - 2.0*sr*std::cos((theta - TWO_PI) / 3.0);
                return std::make_tuple(r1, r2, r3);
            }

            double A = -sign(r)*std::pow(std::abs(r) + std::sqrt(rr - qqq), 1.0 / 3.0);
            double B = 0.0;
            if (A != 0.0)
                B = q / A;

            auto t1 = -b / (3. * a);
            r1 = t1 + A + B;
            r2 = t1 + Complex(-0.5*(A + B), 0.5*SQRT3*(A - B));
            r3 = conj(r2);
        }
    }

    return std::make_tuple(r1, r2, r3);
}

//-----------------------------------------------------------------------------------------------------------------
std::tuple<double, double, double, double> nct::math::solveQuarticEq(
    double a, double b, double c, double d, double e)
{
    if (a == 0.0)
        throw ArgumentException("a", exc_null_quartic_term, SOURCE_INFO);

    auto disc = 256.*a*a*a*e*e*e - 192.*a*a*b*d*e*e - 128.*a*a*c*c*e*e + 144.*a*a*c*d*d*e - 27.*a*a*d*d*d*d +
        144.*a*b*b*c*e*e - 6.*a*b*b*d*d*e - 80.*a*b*c*c*d*e + 18.*a*b*c*d*d*d + 16.*a*c*c*c*c*e -
        4.*a*c*c*c*d*d - 27.*b*b*b*b*e*e + 18.*b*b*b*c*d*e - 4.*b*b*b*d*d*d - 4.*b*b*c*c*c*e + b*b*c*c*d*d;
    auto q = (8.*a*c - 3.*b*b) / (8.*a*a);
    auto r = (b*b*b - 4.*a*b*c + 8.*a*a*d) / (8.*a*a*a);
    auto s = (-3.*b*b*b*b + 256.*a*a*a*e - 64.*a*a*b*d + 16.*a*b*b*c) / (256.*a*a*a*a);

    auto uq = q*q / 4.;
    if (disc < 0)
        throw OperationException(exc_complex_roots, SOURCE_INFO);
    else if ( (disc > 0)  && (((q < 0) && (s > uq)) || (q >= 0)) )
        throw OperationException(exc_complex_roots, SOURCE_INFO);    
    else if ( (disc == 0) && (((q < 0) && (s > uq)) || (q > 0) || ((q == 0) && (s>0))) )
        throw OperationException(exc_complex_roots, SOURCE_INFO);

    double r1 = 0;
    double r2 = 0;
    double r3 = 0;
    double r4 = 0;

    auto t1 = -b / (4. * a);
    auto c1 = 5.*q / 2.;
    auto c2 = 2.*q*q - s;
    auto c3 = q*q*q / 2. - q*s / 2. - r*r / 8.;

    auto yr = solveCubicEqC(1., c1, c2, c3);
    auto yy1 = q + 2.*std::get<0>(yr);
    auto yy2 = q + 2.*std::get<1>(yr);
    auto yy3 = q + 2.*std::get<2>(yr);

    Complex y = 0;
    Complex sqrty = 0;
    if ((std::abs(yy1) >= std::abs(yy2)) && (std::abs(yy1) >= std::abs(yy3))) {
        y = std::get<0>(yr);
        sqrty = std::sqrt(yy1);
    }
    else if ((std::abs(yy2) >= std::abs(yy1)) && (std::abs(yy2) >= std::abs(yy3))) {
        y = std::get<1>(yr);
        sqrty = std::sqrt(yy2);
    }
    else {
        y = std::get<2>(yr);
        sqrty = std::sqrt(yy3);
    }
        
    if (sqrty == 0.0) {
        r1 = t1;
        r2 = t1;
        r3 = t1;
        r4 = t1;
    }
    else {
        auto t2 = -3.*q - 2.*y;
        auto t3 = -2.*r / sqrty;
        r1 = std::real(t1 + 0.5*(sqrty + std::sqrt(t2 + t3)));
        r2 = std::real(t1 + 0.5*(sqrty - std::sqrt(t2 + t3)));
        r3 = std::real(t1 + 0.5*(-sqrty + std::sqrt(t2 - t3)));
        r4 = std::real(t1 + 0.5*(-sqrty - std::sqrt(t2 - t3)));
    }

    return std::make_tuple(r1, r2, r3, r4);
}

//-----------------------------------------------------------------------------------------------------------------
std::tuple<nct::Complex, nct::Complex, nct::Complex, nct::Complex> nct::math::solveQuarticEq(
    const Complex& a, const Complex& b, const Complex& c, const Complex& d, const Complex& e)
{
    if (a == 0.0)
        throw ArgumentException("a", exc_null_cubic_term, SOURCE_INFO);

    Complex r1 = 0;
    Complex r2 = 0;
    Complex r3 = 0;
    Complex r4 = 0;

    auto q = (8. * a * c - 3. * b * b) / (8. * a * a);
    auto r = (b * b * b - 4. * a * b * c + 8. * a * a * d) / (8. * a * a * a);
    auto s = (-3. * b * b * b * b + 256. * a * a * a * e - 64. * a * a * b * d + 16. * a * b * b * c) / 
        (256. * a * a * a * a);
    auto t1 = -b / (4. * a);

    auto c1 = 5. * q / 2.;
    auto c2 = 2. * q * q - s;
    auto c3 = q * q * q / 2. - q * s / 2. - r * r / 8.;

    auto yr = solveCubicEq(1., c1, c2, c3);
    auto yy1 = q + 2. * std::get<0>(yr);
    auto yy2 = q + 2. * std::get<1>(yr);
    auto yy3 = q + 2. * std::get<2>(yr);

    Complex y = 0; 
    Complex sqrty = 0;
    if ((std::abs(yy1) >= std::abs(yy2)) && (std::abs(yy1) >= std::abs(yy3))) {
        y = std::get<0>(yr);
        sqrty = std::sqrt(yy1);
    }
    else if ((std::abs(yy2) >= std::abs(yy1)) && (std::abs(yy2) >= std::abs(yy3))) {
        y = std::get<1>(yr);
        sqrty = std::sqrt(yy2);
    }
    else {
        y = std::get<2>(yr);
        sqrty = std::sqrt(yy3);
    }

    if (sqrty == 0.0) {
        r1 = t1;
        r2 = t1;
        r3 = t1;
        r4 = t1;
    }
    else {
        auto t2 = -3. * q - 2. * y;
        auto t3 = -2. * r / sqrty;
        r1 = t1 + 0.5 * (sqrty + std::sqrt(t2 + t3));
        r2 = t1 + 0.5 * (sqrty - std::sqrt(t2 + t3));
        r3 = t1 + 0.5 * (-sqrty + std::sqrt(t2 - t3));
        r4 = t1 + 0.5 * (-sqrty - std::sqrt(t2 - t3));
    }

    return std::make_tuple(r1, r2, r3, r4);
}

//-----------------------------------------------------------------------------------------------------------------
std::tuple<nct::Complex, nct::Complex, nct::Complex, nct::Complex> nct::math::solveQuarticEqC(
    double a, double b, double c, double d, double e)
{
    if (a == 0.0)
        throw ArgumentException("a", exc_null_cubic_term, SOURCE_INFO);

    Complex r1 = 0;
    Complex r2 = 0;
    Complex r3 = 0;
    Complex r4 = 0;

    auto q = (8.*a*c - 3.*b*b) / (8.*a*a);
    auto r = (b*b*b - 4.*a*b*c + 8.*a*a*d) / (8.*a*a*a);
    auto s = (-3.*b*b*b*b + 256.*a*a*a*e - 64.*a*a*b*d + 16.*a*b*b*c) / (256.*a*a*a*a);
    auto t1 = -b / (4. * a);

    auto c1 = 5.*q / 2.;
    auto c2 = 2.*q*q - s;
    auto c3 = q*q*q / 2. - q*s / 2. - r*r / 8.;
    
    auto yr = solveCubicEqC(1., c1, c2, c3);
    auto yy1 = q + 2.*std::get<0>(yr);
    auto yy2 = q + 2.*std::get<1>(yr);
    auto yy3 = q + 2.*std::get<2>(yr);

    Complex y = 0;
    Complex sqrty = 0;
    if ((std::abs(yy1) >= std::abs(yy2)) && (std::abs(yy1) >= std::abs(yy3))) {
        y = std::get<0>(yr);
        sqrty = std::sqrt(yy1);
    }
    else if ((std::abs(yy2) >= std::abs(yy1)) && (std::abs(yy2) >= std::abs(yy3))) {
        y = std::get<1>(yr);
        sqrty = std::sqrt(yy2);
    }
    else {
        y = std::get<2>(yr);
        sqrty = std::sqrt(yy3);
    }

    if (sqrty == 0.0) {
        r1 = t1;
        r2 = t1;
        r3 = t1;
        r4 = t1;
    }
    else {
        auto t2 = -3.*q - 2.*y;
        auto t3 = -2. * r / sqrty;
        r1 = t1 + 0.5*(sqrty + std::sqrt(t2 + t3));
        r2 = t1 + 0.5*(sqrty - std::sqrt(t2 + t3));
        r3 = t1 + 0.5*(-sqrty + std::sqrt(t2 - t3));
        r4 = t1 + 0.5*(-sqrty - std::sqrt(t2 - t3));
    }

    return std::make_tuple(r1, r2, r3, r4);
}

//-----------------------------------------------------------------------------------------------------------------
unsigned int nct::math::numberOfRealDinstinctRoots(double a, double b, double c)
{
    if (a == 0)
        throw ArgumentException("a", exc_null_quadratic_term, SOURCE_INFO);

    double dsc = b*b - 4 * a*c;
    if (dsc < 0)
        return 0;
    else if (dsc == 0)
        return 1;
    return 2;
}

//-----------------------------------------------------------------------------------------------------------------
unsigned int nct::math::numberOfRealDinstinctRoots(double a, double b, double c, double d)
{
    if (a == 0.0)
        throw ArgumentException("a", exc_null_cubic_term, SOURCE_INFO);

    double disc = 18.*a*b*c*d - 4.*b*b*b*d + b*b*c*c - 4.*a*c*c*c - 27.*a*a*d*d;
    double disc0 = b*b - 3.*a*c;
    
    if (disc < 0)
        return 1;
    else if ((disc == 0) && (disc0 == 0))
        return 1;
    else if (disc == 0)
        return 2;
    return 3;

}

//-----------------------------------------------------------------------------------------------------------------
unsigned int nct::math::numberOfRealDinstinctRoots(double a, double b, double c, double d, double e)
{
    if (a == 0.0)
        throw ArgumentException("a", exc_null_quartic_term, SOURCE_INFO);

    auto disc = 256.*a*a*a*e*e*e - 192.*a*a*b*d*e*e - 128.*a*a*c*c*e*e + 144.*a*a*c*d*d*e - 27.*a*a*d*d*d*d + 
        144*a*b*b*c*e*e - 6.*a*b*b*d*d*e - 80.*a*b*c*c*d*e + 18.*a*b*c*d*d*d + 16.*a*c*c*c*c*e -
        4*a*c*c*c*d*d - 27.*b*b*b*b*e*e + 18.*b*b*b*c*d*e - 4.*b*b*b*d*d*d -4.*b*b*c*c*c*e + b*b*c*c*d*d;
    auto q = (8.*a*c - 3.*b*b) / (8.*a*a);
    auto r = (b*b*b - 4.*a*b*c + 8.*a*a*d) / (8.*a*a*a);
    auto s = (-3.*b*b*b*b + 256.*a*a*a*e - 64.*a*a*b*d + 16.*a*b*b*c) / (256.*a*a*a*a);
    
    auto uq = q*q / 4.;
    auto lq = -q*q / 12.;
    if (disc < 0) {
        return 2;
    }
    else if (disc > 0) {
        if ((q < 0) && (s < uq))
            return 4;
        else
            return 0;
    }

    if (q < 0) {
        if (s > uq)
            return 1;
        else if ((s>lq) && (s < uq))
            return 3;
        return 2;
    }
    else if (q > 0) {
        if ((s > 0) && (r != 0))
            return 1;
        else if ((s == uq) && (r == 0))
            return 0;
        return 1;
    }

    return 1;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
