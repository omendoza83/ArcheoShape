//=================================================================================================================
/**
 *  @file       spherical_harmonics.cpp
 *  @brief      Implementation file of functions of the nct::signal::spherical_harmonics namespace.
 *  @details    This file contains the implementation of the functions defined in 
 *              the nct::signal::spherical_harmonics namespace.          
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
#include <nct/signal/spherical_harmonics.h>
#include <nct/math/math_functions.h>
#include <nct/math/linear_algebra.h>

//=================================================================================================================
//        FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::signal::spherical_harmonics::SphericalMatrix nct::signal::spherical_harmonics::sphericalMatrix(
    unsigned int maxl, const RealVector& theta, const RealVector& phi) 
{
    auto nr = theta.size();

    if (nr == 0)
        throw EmptyArrayException("theta", SOURCE_INFO);

    if (nr != phi.size())
        throw ArgumentException("phi", exc_bad_array_size, 
        SOURCE_INFO);

    auto nc = (maxl+1)*(maxl+1);

    SphericalMatrix sphericalMatrix;
    sphericalMatrix.mat.assign(nr, nc, 0.0);

    sphericalMatrix.harmonics.resize(nc);

    unsigned int c = 0;
    Complex h;
    for (unsigned int l=0; l<=maxl; l++) {
        for (unsigned int m=0; m<=l; m++) {
            sphericalMatrix.harmonics[c].l = l;
            sphericalMatrix.harmonics[c].m = m;
                                
            if (m==0) {
                for (index_t s=0; s<nr; s++) {
                    h = math::sphericalHarmonic(l, m, theta[s], phi[s]);
                    sphericalMatrix.mat(s, c) = h.real();
                }
            }
            else {
                sphericalMatrix.harmonics[c+(size_t)1].l = l;
                sphericalMatrix.harmonics[c+(size_t)1].m = m;
                for (index_t s=0; s<nr; s++) {
                    h = math::sphericalHarmonic(l, m, theta[s], phi[s]);
                    sphericalMatrix.mat(s, c) = 2*h.real();
                    sphericalMatrix.mat(s, c+(size_t)1) = -2*h.imag();
                }
            }
            
            c+= 1 + (m!=0);            
        }
    }

    return sphericalMatrix;
}

//-----------------------------------------------------------------------------------------------------------------
nct::signal::spherical_harmonics::SphericalMatrix 
nct::signal::spherical_harmonics::orthogonalHarmonicMatrix(
    unsigned int maxl, const RealVector& theta, const RealVector& phi, double tol) 
{
    auto nr = theta.size();

    if (nr == 0)
        throw EmptyArrayException("theta", SOURCE_INFO);

    if (nr != phi.size())
        throw ArgumentException("phi", exc_bad_array_size, 
        SOURCE_INFO);

    tol = tol >= 0 ? tol : MEDIUM_TOL;

    // Compute harmonics from l = 0 to l = maxl.
    auto nc = (maxl+1)*(maxl+1);
    Matrix v(nr, nc);
    Array<SphericalHarmonic> harTmp(nc);
    Array<bool> realPart(nc);

    Complex h;
    unsigned int c = 0;
    for (unsigned int l=0; l<=maxl; l++) {
        for (unsigned int m=0; m<=l; m++) {
            harTmp[c].l = l;
            harTmp[c].m = m;
                                
            if (m==0) {
                realPart[c] = true;
                for (index_t s=0; s<nr; s++) {
                    h = math::sphericalHarmonic(l, m, theta[s], phi[s]);
                    v(s, c) = h.real();
                }
            }
            else {
                harTmp[c+(size_t)1].l = l;
                harTmp[c+(size_t)1].m = m;
                realPart[c] = true;
                realPart[c+(size_t)1] = false;
                for (index_t s=0; s<nr; s++) {
                    h = math::sphericalHarmonic(l, m, theta[s], phi[s]);
                    v(s, c) = 2*h.real();
                    v(s, c+(size_t)1) = -2*h.imag();
                }
            }
            
            c+= 1 + (m!=0);            
        }
    }

    // Select orthogonal harmonics.
    Matrix w(nr, nc);
    RealVector wm(nc);
    Array<size_t> wflag(nc);
    for (unsigned int i=0; i<nc; i++) {
        // wi = vi
        for (index_t r=0; r<nr; r++)
            w(r, i) = v(r, i);            
        
        // wi -= sum( wj * <vi,wj>/<wj,wj> )
        for (unsigned int j = 0; j<i; j++) {
            if (wflag[j]) {
                double dtmp = 0;
                for (index_t r=0; r<nr; r++)
                    dtmp += w(r, j) * v(r, i);

                for (index_t r=0; r<nr; r++)
                    w(r, i) -= w(r, j) * dtmp/wm[j];
            }
        }

        // <wi, wi>
        wm[i] = 0;
        for (index_t r=0; r<nr; r++)
            wm[i] += w(r,i)*w(r,i);

        // Verify whether the element is included in the next iteration.
        wflag[i] = (std::sqrt(wm[i]) > tol);
    }
    
    c = 0;
    for (unsigned int l=0; l<=maxl; l++) {
        for (unsigned int m=0; m<=l; m++) {
            if (m!=0) {
                if (!wflag[c] || !wflag[c+(size_t)1]) {
                    wflag[c] = 0;
                    wflag[c+(size_t)1] = 0;
                }
            }

            c+= 1 + (m!=0);    
        }
    }

    // Fill output arrays of the selected elements.
    auto nOrt = wflag.sum();

    SphericalMatrix sphericalMatrix;
    sphericalMatrix.mat.assign(nr, nOrt, 0.0);

    sphericalMatrix.harmonics.resize(nOrt);

    c = 0;
    for (unsigned int i=0; i<nc; i++) {
        if (wflag[i]) {
            for (index_t r=0; r<nr; r++)
                sphericalMatrix.mat(r, c) = v(r, i);
            sphericalMatrix.harmonics[c] = harTmp[i];
            c++;
        }
    }

    return sphericalMatrix;
}

//-----------------------------------------------------------------------------------------------------------------
nct::signal::spherical_harmonics::SphericalTransform nct::signal::spherical_harmonics::sphericalTransform(
    unsigned int maxl, const RealVector& f, const RealVector& theta,
    const RealVector& phi, double tol) 
{
    static constinit const double BIG_CONDITION_NUMBER {1E12};

    auto nr = f.size();

    if (nr == 0)
        throw EmptyArrayException("f", SOURCE_INFO);

    if (nr != phi.size())
        throw ArgumentException("phi", exc_bad_array_size, 
        SOURCE_INFO);

    if (nr != theta.size())
        throw ArgumentException("theta", exc_bad_array_size, 
        SOURCE_INFO);

    // Compute matrix of harmonics.
    auto spMatrix = sphericalMatrix(maxl, theta, phi);

    // Compute coefficients.
    auto Bt = spMatrix.mat.transpose();
    auto BtB = Bt* spMatrix.mat;
    //double nCond = math::linear_algebra::cond(BtB);
    //if (nCond>BIG_CONDITION_NUMBER)
    //    throw OperationException(exc_bad_condition_number, SOURCE_INFO);

    auto Btf = matrixVectorProduct(Bt, f);
    auto cc = math::linear_algebra::solveSystem(BtB, Btf, tol);

    // Compute coefficients for negative m.
    auto nhs = spMatrix.harmonics.size();
    auto nhT = (maxl + 1)* (maxl + 1);

    SphericalTransform transform;
    transform.c.assign(nhT, 0.0);
    transform.harmonics.resize(nhT);

    unsigned int cont = 0;
    for (int l = 0; l<=static_cast<int>(maxl); l++) {
        for (int m = -l; m<=l; m++) {
            // Find harmonic in the solution.
            size_t i = 0;
            for (i = 0; i<nhs; i++) {
                if ((spMatrix.harmonics[i].l) == l && (spMatrix.harmonics[i].m) == std::abs(m))
                    break;
            }
            if (i == nhs)
                continue;

            if (m<0) {
                double sign = std::abs(m)%2 ? (-1): 1; 
                transform.c[cont] = Complex(sign*cc[i], -sign*cc[i+1]);
            }
            else if (m == 0) {
                transform.c[cont] = Complex(cc[i], 0);
            }
            else {
                transform.c[cont] = Complex(cc[i], cc[i+1]);
            }
            transform.harmonics[cont].l = l;
            transform.harmonics[cont].m = m;
            cont++;
        }
    }

    return transform;
}

//-----------------------------------------------------------------------------------------------------------------
nct::signal::spherical_harmonics::SphericalTransform 
nct::signal::spherical_harmonics::orthogonalSphericalTransform(
    unsigned int maxl, const RealVector& f, const RealVector& theta,
    const RealVector& phi, double tol)
{
    static constinit const double BIG_CONDITION_NUMBER {1E12};

    auto nr = f.size();

    if (nr == 0)
        throw EmptyArrayException("f", SOURCE_INFO);

    if (nr != phi.size())
        throw ArgumentException("phi", exc_bad_array_size, 
        SOURCE_INFO);

    if (nr != theta.size())
        throw ArgumentException("theta", exc_bad_array_size, 
        SOURCE_INFO);

    // Compute matrix of harmonics.
    auto spMatrix = orthogonalHarmonicMatrix(maxl, theta, phi);

    // Compute coefficients.
    auto Bt = spMatrix.mat.transpose();
    auto BtB = Bt* spMatrix.mat;
    //double nCond = math::linear_algebra::cond(BtB);
    //if (nCond>BIG_CONDITION_NUMBER)
    //    throw OperationException(exc_bad_condition_number, SOURCE_INFO);

    auto Btf = matrixVectorProduct(Bt,f);
    auto cc = math::linear_algebra::solveSystem(BtB, Btf, tol);

    // Compute coefficients for negative m.
    auto nhs = spMatrix.harmonics.size();
    auto nhT = (maxl + 1)* (maxl + 1);

    SphericalTransform transform;
    transform.c.assign(nhT, 0.0);
    transform.harmonics.clear();
    transform.harmonics.resize(nhT);

    unsigned int cont = 0;
    for (int l = 0; l<=static_cast<int>(maxl); l++) {
        for (int m = -l; m<=l; m++) {
            // Find harmonic in the solution.
            transform.harmonics[cont].l = l;
            transform.harmonics[cont].m = m;

            size_t i = 0;
            for (i = 0; i<nhs; i++) {
                if ((spMatrix.harmonics[i].l) == l && (spMatrix.harmonics[i].m) == std::abs(m))
                    break;
            }
            if (i == nhs) {
                cont++;
                continue;
            }

            if (m<0) {
                double sign = std::abs(m)%2 ? (-1): 1; 
                transform.c[cont] = Complex(sign*cc[i], -sign*cc[i+1]);
            }
            else if (m == 0) {
                transform.c[cont] = Complex(cc[i], 0);
            }
            else {
                transform.c[cont] = Complex(cc[i], cc[i+1]);
            }
            
            cont++;
        }
    }        
    return transform;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
