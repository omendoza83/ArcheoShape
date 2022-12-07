//=================================================================================================================
/**
 *  @file       linear_algebra.cpp
 *  @brief      Implementation file of functions of the nct::math::linear_algebra namespace.
 *  @details    This file contains the implementation of the functions defined in the 
 *              nct::math::linear_algebra namespace.          
 *  @author     Omar Mendoza Montoya (email: omendoz@live.com.mx).
 *  @copyright  Copyright (c) 2010 Omar Mendoza Montoya \n \n
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

#define NCT_ARRAY_DISABLE_INDEX_CHECKING  
#define NCT_ARRAY_2D_DISABLE_INDEX_CHECKING  

//=================================================================================================================
//        HEADERS AND NAMESPACES
//=================================================================================================================
#include <nct/math/linear_algebra.h>
#include <nct/math/math.h>
#include <nct/nct_utils.h>

#include <algorithm>

#include "Eigen/Core"
#include "Eigen/Eigenvalues"

//=================================================================================================================
//        GENERAL PURPOSE FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
bool nct::math::linear_algebra::isUpperTriangular(const Matrix& a, double tol)
{
    if (a.size() == 0)
        return false;

    size_t nRows = a.rows();
    size_t nColumns = a.columns();
    
    if (nRows != nColumns)
        return false;
    
    tol = (tol >= 0 ? tol : SMALL_TOL) * max(nRows, nColumns) * maximumAbs(a.begin(), a.end());

    for (index_t i=1; i<nRows; i++) {            
        for (index_t j=0; j<i; j++) {
            if (std::abs(a(i,j))>tol)
                return false;
        }
    }
    return true;
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::math::linear_algebra::isLowerTriangular(const Matrix& a, double tol)
{
    if (a.size() == 0)
        return false;

    size_t nRows = a.rows();
    size_t nColumns = a.columns();
    
    if (nRows != nColumns)
        return false;

    tol = (tol >= 0 ? tol : SMALL_TOL) * max(nRows, nColumns) * maximumAbs(a.begin(), a.end());

    auto rf = math::max(nRows, size_t(1)) - 1;
    for (index_t i = 0; i<rf; i++) {
        for (index_t j=i+1; j<nColumns; j++) {
            if (std::abs(a(i,j))>tol)
                return false;
        }
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::math::linear_algebra::isSymmetric(const Matrix& a, double tol)
{
    if (a.size() == 0)
        return false;

    size_t nRows = a.rows();
    size_t nColumns = a.columns();
    
    if (nRows != nColumns)
        return false;

    tol = (tol >= 0 ? tol : SMALL_TOL) * max(nRows, nColumns) * maximumAbs(a.begin(), a.end());

    for (index_t i=0; i<nRows; i++) {
        for (index_t j=0; j<i; j++) {
            if (std::abs(a(i, j) - a(j, i)) > tol)
                return false;                
        }
    }
    
    return true;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::math::linear_algebra::makeSymmetric(Matrix& a)
{
    if (a.size() == 0)
        return;

    if (a.rows() != a.columns())
        throw ArgumentException("a", exc_non_square_matrix, SOURCE_INFO);

    size_t n = a.rows();
    for (index_t i=0; i<n; i++) {
        for (index_t j=(i+1); j<n; j++) {
            a(i,j) = (a(i,j) + a(j,i))/2;
            a(j,i) = a(i,j);
        }
    }
}

//=================================================================================================================
//        PIVOTING FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
/**
 *  @brief      Pivoting.
 *  @details    This function finds the next pivot in the Gauss reduction.
 *  @param[in]  a  Matrix to be checked.
 *  @param[in,out] pivInd    Array with the pivoting information.
 *  @param[in]  i  Row index where is needed to find the pivot.
 *  @param[in]  j  Column index where is needed to find the pivot.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    A pair that indicates wheter the pivot is valid and whether two rows were exchanged.
 */
static std::pair<bool, bool> pivoting(const nct::Matrix& a, nct::Array<nct::size_t>& pivInd,
    nct::size_t i, nct::size_t j, double tol)
{
    nct::size_t nRows = a.rows();        // Rows.
    nct::size_t nColumns = a.columns();  // Columns.
    bool bPivot = false;                 // Flag that indicates whether a pivot was found.
    double maxDiv = 0;                   // Maximun value of one row.
    double minMaxDiv = 0;                // Minimum value of the maximum values in one row.
    double temp = 0;                     // Variable for calculations.
    nct::size_t pivot = i;               // Initial pivot.

    if (pivInd.size() != nRows)
        throw nct::ArgumentException("pivInd", nct::exc_bad_pivot, SOURCE_INFO);
    if (i >= nRows)
        throw nct::IndexOutOfRangeException("i", SOURCE_INFO);
    if (j >= nColumns)
        throw nct::IndexOutOfRangeException("j", SOURCE_INFO);
    bool changed = false;

    for (nct::index_t l = i; l < nRows; l++) {
        if (std::abs(a(pivInd[l], j)) > tol) {
            maxDiv = 0;
            for (nct::index_t k = j + 1; k < nColumns; k++) {
                temp = std::abs(a(pivInd[l], k) / a(pivInd[l], j));
                if (temp > maxDiv)
                    maxDiv = temp;
            }
            if (!bPivot) {
                minMaxDiv = maxDiv;
                bPivot = true;
                pivot = l;
            }
            else if (minMaxDiv > maxDiv) {
                minMaxDiv = maxDiv;
                pivot = l;
            }
        }
    }

    // Swap rows.
    if (pivot != i) {
        std::swap(pivInd[i], pivInd[pivot]);
        changed = true;
    }

    return std::make_pair(bPivot, changed);
}

//=================================================================================================================
//        INVERSE
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::Matrix nct::math::linear_algebra::inverse(const Matrix& a, 
    double tol, unsigned int improvementSteps)
{
    if (a.rows() != a.columns())
        throw ArgumentException("a", exc_non_square_matrix, SOURCE_INFO);

    if (a.size() == 0)
        return Matrix(0, 0);

    nct::Matrix inv;
    try {
        auto n = a.rows();
        if (isUpperTriangular(a, tol) && (improvementSteps == 0))
            inv = inverseU(a, tol);
        else if (isLowerTriangular(a, tol) && (improvementSteps == 0))
            inv = inverseL(a, tol);        
        else
            inv = solveSystem(a, Matrix::eye(n), tol, improvementSteps);
    }
    catch (const nct_exception& ex) {
        throw OperationException(exc_error_computing_inverse, SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw OperationException(exc_error_computing_inverse, SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_unknown, SOURCE_INFO);
    }

    return inv;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Matrix nct::math::linear_algebra::inverseL(const Matrix& a, double tol)
{
    if (a.rows() != a.columns())
        throw ArgumentException("a", exc_non_square_matrix, SOURCE_INFO);

    if (a.size() == 0)
        return Matrix(0, 0);

    if (!isLowerTriangular(a, tol))
        throw ArgumentException("a", exc_non_lower_triangular_matrix, SOURCE_INFO);
    
    size_t n = a.rows();
    tol = (tol >= 0 ? tol : SMALL_TOL) * n * maximumAbs(a.begin(), a.end());
    for (index_t i = 0; i<n; i++) {
        if (std::abs(a(i,i)) <= tol)
            throw ArgumentException("a", exc_singular_matrix, SOURCE_INFO);
    }
    
    Matrix inv(n, n, 0.0);
    for (diff_t i = 0; i<static_cast<diff_t>(n); i++) {
        for (diff_t j = 0; j<=i; j++) {
            for (diff_t k = j; k<=(i-1); k++)
                inv(i,j) -= a(i,k)*inv(k,j);
            inv(i,j) += (i==j);
            inv(i,j) /= a(i,i);
        }
    }

    return inv;
}


//-----------------------------------------------------------------------------------------------------------------
nct::Matrix nct::math::linear_algebra::inverseU(const Matrix& a, double tol)
{
    if (a.rows() != a.columns())
        throw ArgumentException("a", exc_non_square_matrix, SOURCE_INFO);

    if (a.size() == 0)
        return Matrix(0, 0);

    if (!isUpperTriangular(a, tol))
        throw ArgumentException("a", exc_non_lower_triangular_matrix, SOURCE_INFO);
    
    size_t n = a.rows();
    tol = (tol >= 0 ? tol : SMALL_TOL) * n * maximumAbs(a.begin(), a.end());
    for (index_t i = 0; i<n; i++) {
        if (std::abs(a(i,i)) <= tol)
            throw ArgumentException("a", exc_singular_matrix, SOURCE_INFO);
    }
    
    Matrix inv(n, n, 0.0);
    for (diff_t i = static_cast<diff_t>(n)-1; i>=0; i--) {
        for (diff_t j = static_cast<diff_t>(n)-1; j>=i; j--) {
            for (diff_t k = i; k<=j; k++)
                inv(i,j) -= a(i,k)*inv(k,j);
            inv(i,j) += (i==j);
            inv(i,j) /= a(i,i);
        }
    }

    return inv;    
}

//=================================================================================================================
//        LINEAR SYSTEMS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::Matrix nct::math::linear_algebra::solveSystem(const Matrix& a, const Matrix& b,
    double tol, unsigned int improvementSteps)
{
    if (a.size() == 0)
        throw EmptyArrayException("a", SOURCE_INFO);

    if (a.rows() != b.rows())
        throw ArgumentException("a, b", exc_bad_linear_system, SOURCE_INFO);
    
    Matrix x;

    try {
        
        if (isUpperTriangular(a, tol)) {
            x = solveSystemU(a, b, tol);
            for (unsigned int i = 0; i < improvementSteps; i++) {
                auto d = solveSystemU(a, b - a * x, tol);
                x -= d;
            }
        }
        else if (isLowerTriangular(a, tol)) {
            x = solveSystemL(a, b, tol);
            for (unsigned int i = 0; i < improvementSteps; i++) {
                auto d = solveSystemL(a, b - a * x, tol);
                x -= d;
            }
        }
        else {
            auto plu = pluFactorization(a, tol);
            x = solveSystemPLU(plu, b, tol);
            for (unsigned int i = 0; i < improvementSteps; i++) {
                auto d = solveSystemPLU(plu, b - a * x, tol);
                x -= d;
            }
        }
    }
    catch (const nct_exception & ex) {
        throw OperationException(exc_error_solving_linear_system, 
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception & ex) {
        throw OperationException(exc_error_solving_linear_system,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_unknown, SOURCE_INFO);
    }

    return x;
}

//-----------------------------------------------------------------------------------------------------------------
nct::ColumnVector nct::math::linear_algebra::solveSystem(const Matrix& a,
    const ColumnVector& b, double tol, unsigned int improvementSteps)
{
    if (a.size() == 0)
        throw EmptyArrayException("a", SOURCE_INFO);

    if (a.rows() != b.size())
        throw ArgumentException("a, b", exc_bad_linear_system, SOURCE_INFO);

    ColumnVector x;

    try {

        if (isUpperTriangular(a, tol)) {
            x = solveSystemU(a, b, tol);
            for (unsigned int i = 0; i < improvementSteps; i++) {
                auto d = solveSystemU(a, b - matrixVectorProduct(a, x), tol);
                x -= d;
            }
        }
        else if (isLowerTriangular(a, tol)) {
            x = solveSystemL(a, b, tol);
            for (unsigned int i = 0; i < improvementSteps; i++) {
                auto d = solveSystemL(a, b - matrixVectorProduct(a, x), tol);
                x -= d;
            }
            return x;
        }
        else {
            auto plu = pluFactorization(a, tol);
            x = solveSystemPLU(plu, b, tol);
            for (unsigned int i = 0; i < improvementSteps; i++) {
                auto d = solveSystemPLU(plu, b - matrixVectorProduct(a, x), tol);
                x -= d;
            }
        }
    }
    catch (const nct_exception & ex) {
        throw OperationException(exc_error_solving_linear_system,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception & ex) {
        throw OperationException(exc_error_solving_linear_system,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_unknown, SOURCE_INFO);
    }

    return x;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Matrix nct::math::linear_algebra::solveSystemL(const Matrix& l,
    const Matrix& b, double tol)
{
    size_t nRows = l.rows();                
    size_t nColumns = l.columns();        
    size_t nColumnsB = b.columns();

    if (l.size() == 0)
        throw EmptyArrayException("l", SOURCE_INFO);

    if (!isLowerTriangular(l, tol))
        throw ArgumentException("l", exc_non_lower_triangular_matrix, SOURCE_INFO);

    if (nRows != b.rows())
        throw ArgumentException("l, b", exc_bad_linear_system, SOURCE_INFO);
    
    tol = (tol >= 0 ? tol : SMALL_TOL) * nRows *  maximumAbs(l.begin(), l.end());
    for (index_t i=0; i<nRows; i++)
        if (std::abs(l(i,i)) <= tol)
            throw ArgumentException("l", exc_singular_matrix, SOURCE_INFO);

    // Solution (forward sustitution).
    Matrix x(nColumns, nColumnsB);
    for (index_t i=0; i<nRows; i++) {
        for (index_t j=0; j<nColumnsB; j++) {
            x(i,j) = b(i,j);
            for (index_t k=0; k<i; k++)
                x(i,j) -= x(k,j) * l(i,k);
            x(i,j) /= l(i, i);    
        }
    }    
    return x;
}

//-----------------------------------------------------------------------------------------------------------------
nct::ColumnVector nct::math::linear_algebra::solveSystemL(const Matrix& l,
    const ColumnVector& b, double tol)
{
    size_t nRows = l.rows();                
    size_t nColumns = l.columns();        

    if (l.size() == 0)
        throw EmptyArrayException("l", SOURCE_INFO);

    if (!isLowerTriangular(l, tol))
        throw ArgumentException("l", exc_non_lower_triangular_matrix, SOURCE_INFO);

    if (nRows != b.size())
        throw ArgumentException("l, b", exc_bad_linear_system, SOURCE_INFO);
    
    tol = (tol >= 0 ? tol : SMALL_TOL) * nRows * maximumAbs(l.begin(), l.end());
    for (index_t i=0; i<nRows; i++)
        if (std::abs(l(i,i)) <= tol)
            throw ArgumentException("l", exc_singular_matrix, SOURCE_INFO);

    // Solution (forward sustitution).
    ColumnVector x(nColumns);
    for (index_t i=0; i<nRows; i++) {
        x[i] = b[i];
        for (index_t k=0; k<i; k++)
            x[i] -= x[k] * l(i, k);
        x[i] /= l(i, i);            
    }    
    return x;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Matrix nct::math::linear_algebra::solveSystemU(const Matrix& u,
    const Matrix& b, double tol)
{
    size_t nRows = u.rows();            
    size_t nColumns = u.columns();    
    size_t nColumnsB = b.columns();    

    if (u.size() == 0)
        throw EmptyArrayException("u", SOURCE_INFO);

    if (!isUpperTriangular(u, tol))
        throw ArgumentException("u", exc_non_upper_triangular_matrix, SOURCE_INFO);

    if (nRows != b.rows())
        throw ArgumentException("u, b", exc_bad_linear_system, SOURCE_INFO);
    
    tol = (tol >= 0 ? tol : SMALL_TOL) * nRows * maximumAbs(u.begin(), u.end());
    for (index_t i=0; i<nRows; i++)
        if (std::abs(u(i,i)) <= tol)
            throw ArgumentException("u", exc_singular_matrix,SOURCE_INFO);

    // Solution (backward sustitution).
    Matrix x(nColumns, nColumnsB);
    for (index_t i=0; i<nRows; i++) {
        for (index_t j=0; j<nColumnsB; j++) {
            x(nRows-i-1,j) = b(nRows-i-1,j);
            for (index_t k=0; k<i; k++)
                x(nRows-i-1,j) -= x(nRows-k-1,j) * u(nRows-i-1, + nRows-k-1);
            x(nRows-i-1,j) /= u(nRows-i-1, nRows-i-1);    
        }
    }    

    return x;
}

//-----------------------------------------------------------------------------------------------------------------
nct::ColumnVector nct::math::linear_algebra::solveSystemU(const Matrix& u,
    const ColumnVector& b, double tol)
{
    size_t nRows = u.rows();            
    size_t nColumns = u.columns();    

    if (u.size() == 0)
        throw EmptyArrayException("u", SOURCE_INFO);

    if (!isUpperTriangular(u, tol))
        throw ArgumentException("u", exc_non_upper_triangular_matrix, SOURCE_INFO);

    if (nRows != b.size())
        throw ArgumentException("u, b", exc_bad_linear_system, SOURCE_INFO);
    
    tol = (tol >= 0 ? tol : SMALL_TOL) * nRows * maximumAbs(u.begin(), u.end());
    for (index_t i=0; i<nRows; i++)
        if (std::abs(u(i,i)) <= tol)
            throw ArgumentException("u", exc_singular_matrix, SOURCE_INFO);

    // Solution (backward sustitution).
    ColumnVector x(nColumns);
    for (index_t i=0; i<nRows; i++) {
        x[nRows-i-1] = b[nRows-i-1];
        for (index_t k=0; k<i; k++)
            x[nRows-i-1] -= x[nRows-k-1] * u(nRows-i-1, + nRows-k-1);
        x[nRows-i-1] /= u(nRows-i-1, nRows-i-1);    
    }    

    return x;
}

//=================================================================================================================
//        PA=LU FACTORIZATION
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::math::linear_algebra::PLU nct::math::linear_algebra::pluFactorization(const Matrix& a, double tol)
{
    size_t nRows = a.rows();
    size_t nColumns = a.columns();
    
    PLU plu;
    plu.p = Array<size_t>::numericalSequence(nRows, 0, 1);
    plu.lu = Matrix(nRows, nColumns, 0);
    Matrix tempA = a;    
    
    tol = (tol >= 0 ? tol : SMALL_TOL) * max(nRows, nColumns) * maximumAbs(a.begin(), a.end());
    
    for (index_t i = 0; i < nRows && i < nColumns; i++) {

        // Pivoting.
        auto pivres = pivoting(tempA, plu.p, i, i, tol);
        if (!pivres.first)
            throw OperationException(exc_error_computing_matrix_factorization, SOURCE_INFO);

        if (pivres.second)
            plu.np++;

        // Coefficients.
        for (index_t j = i + 1; j < nRows; j++) {
            tempA(plu.p[j], i) /= tempA(plu.p[i], i);
            for (index_t k = i + 1; k < nColumns; k++)
                tempA(plu.p[j], k) -= tempA(plu.p[j], i) * tempA(plu.p[i], k);
        }

        for (index_t j = 0; j < nColumns; j++)
            plu.lu(i, j) = tempA(plu.p[i], j);
    }

    return plu;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Matrix nct::math::linear_algebra::solveSystemPLU(const PLU& plu,
    const Matrix& b, double tol) 
{
    size_t nRows = plu.lu.rows();
    size_t nColumns = plu.lu.columns();
    size_t nColumnsB = b.columns();        

    if (plu.lu.size() == 0)
        throw EmptyArrayException("lu", SOURCE_INFO);

    if (nRows != nColumns)
        throw ArgumentException("plu", exc_non_square_matrix, SOURCE_INFO);

    if ((nRows != b.rows()) || (nRows != plu.p.size()))
        throw ArgumentException("lu, p, b", exc_bad_linear_system, SOURCE_INFO);
    
    tol = (tol >= 0 ? tol : SMALL_TOL) * nRows * maximumAbs(plu.lu.begin(), plu.lu.end());
    for (index_t i=0; i<nRows; i++)
        if (std::abs(plu.lu(i, i)) <= tol)
            throw ArgumentException("plu", exc_singular_matrix, SOURCE_INFO);

    // Backward sustitution (Lz = b).
    Matrix x(nColumns, nColumnsB);    
    for (index_t i=0; i<nRows; i++) {
        for (index_t j=0; j<nColumnsB; j++) {
            x(i, j) = b(plu.p[i], j);
            for (index_t k=0; k<i; k++)
                x(i, j) -= x(k, j) * plu.lu(i, k);
        }
    }
    // Forward sustitution (Ux = z).
    for (index_t i=0; i<nRows; i++) {
        for (index_t j=0; j<nColumnsB; j++) {
            for (index_t k=0; k<i; k++)
                x(nRows - i - 1, j) -= x(nRows - k - 1, j) * plu.lu(nRows - i - 1, +nRows - k - 1);
            x(nRows - i - 1, j) /= plu.lu(nRows - i - 1, nRows - i - 1);
        }
    }

    return x;
}

//-----------------------------------------------------------------------------------------------------------------
nct::ColumnVector nct::math::linear_algebra::solveSystemPLU(const PLU& plu,
    const ColumnVector& b, double tol)
{
    size_t nRows = plu.lu.rows();
    size_t nColumns = plu.lu.columns();

    if (plu.lu.size() == 0)
        throw EmptyArrayException("lu", SOURCE_INFO);

    if (nRows != nColumns)
        throw ArgumentException("plu", exc_non_square_matrix, SOURCE_INFO);

    if ((nRows != b.size()) || (nRows != plu.p.size()))
        throw ArgumentException("lu, p, b", exc_bad_linear_system, SOURCE_INFO);
    
    tol = (tol >= 0 ? tol : SMALL_TOL) * nRows * maximumAbs(plu.lu.begin(), plu.lu.end());
    for (index_t i=0; i<nRows; i++)
        if (std::abs(plu.lu(i, i)) <= tol)
            throw ArgumentException("plu", exc_singular_matrix, SOURCE_INFO);

    // Backward sustitution (Lz = b).
    ColumnVector x(nColumns);    
    for (index_t i=0; i<nRows; i++) {
        x[i] = b[plu.p[i]];
        for (index_t k=0; k<i; k++)
            x[i] -= x[k] * plu.lu(i, k);
    }

    // Forward sustitution (Ux = z).
    for (index_t i=0; i<nRows; i++) {
        for (index_t k=0; k<i; k++)
            x[nRows - i - 1] -= x[nRows - k - 1] * plu.lu(nRows - i - 1, +nRows - k - 1);
        x[nRows - i - 1] /= plu.lu(nRows - i - 1, nRows - i - 1);
    }

    return x;
}

//-----------------------------------------------------------------------------------------------------------------
nct::math::linear_algebra::PLUBanded nct::math::linear_algebra::pluFactorizationOfBandedMatrix(
    const Matrix& a, size_t diagColumn, double tol)
{
    size_t nRows = a.rows();
    size_t nColumns = a.columns();

    if (diagColumn >= nColumns)
        throw IndexOutOfRangeException("diagColumn", SOURCE_INFO);

    size_t m = 0;
    size_t pivot = 0;

    PLUBanded plu;
    plu.p.assign(nRows, 0);
    plu.l.assign(nRows, diagColumn, 0.0);
    plu.u = a;

    tol = (tol >= 0 ? tol : SMALL_TOL) * max(nRows, nColumns) * maximumAbs(a.begin(), a.end());

    // Rearrange the matrix.
    m = diagColumn;
    for (index_t i = 0; i < diagColumn; i++) {
        for (index_t j = diagColumn - i; j < nColumns; j++)
            plu.u(i, j - m) = plu.u(i, j);
        m--;
        for (index_t j = nColumns - m - 1; j < nColumns; j++)
            plu.u(i, j) = 0.0;
    }

    // Factorization.
    m = diagColumn;
    for (index_t k = 0; k < nRows; k++) {
        auto temp = plu.u(k, 0);
        pivot = k;
        if (m < nRows)
            m++;

        // Pivoting.
        for (index_t j = k + 1; j < m; j++) {
            if (std::abs(plu.u(j, 0)) > std::abs(temp)) {
                temp = plu.u(j, 0);
                pivot = j;
            }
        }
        if (std::abs(temp) <= tol)
            throw OperationException(exc_error_computing_matrix_factorization, SOURCE_INFO);

        // Swapt rows.
        plu.p[k] = pivot;
        if (pivot != k) {
            plu.np++;
            for (index_t j = 0; j < nColumns; j++)
                std::swap(plu.u(k, j), plu.u(pivot, j));
        }

        // Elimination.
        for (index_t i = k + 1; i < m; i++) {
            temp = plu.u(i, 0) / plu.u(k, 0);
            plu.l(k, i - k - 1) = temp;
            for (index_t j = 1; j < nColumns; j++)
                plu.u(i, j - 1) = plu.u(i, j) - temp * plu.u(k, j);
            plu.u(i, nColumns - 1) = 0.0;
        }
    }

    // Clean the elements above the main diagonal of U.
    m = nColumns;
    for (index_t i = nRows - nColumns; i < nRows; i++) {
        for (index_t j = m; j < nColumns; j++)
            plu.u(i, j) = 0.0;
        m--;
    }

    return plu;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Matrix nct::math::linear_algebra::solveSystemPLUBanded(const PLUBanded& plu,
    const Matrix& b, double tol)
{
    size_t nRows = plu.u.rows();
    size_t nColumns = plu.u.columns();
    size_t nColumnsB = b.columns();

    if (plu.l.size() == 0)
        throw EmptyArrayException("l", SOURCE_INFO);

    if (plu.u.size() == 0)
        throw EmptyArrayException("u", SOURCE_INFO);

    if (plu.l.rows() != nRows || plu.l.columns() >= nColumns || nRows < nColumns)
        throw ArgumentException("l, u", exc_bad_linear_system, SOURCE_INFO);

    if (nRows != b.rows())
        throw ArgumentException("l, u, b", exc_bad_linear_system, SOURCE_INFO);

    tol = (tol >= 0 ? tol : SMALL_TOL) * nRows * max(maximumAbs(plu.l.begin(), plu.l.end()),
        maximumAbs(plu.u.begin(), plu.u.end()));
    for (index_t i = 0; i < nRows; i++)
        if (std::abs(plu.u(i, 0)) <= tol)
            throw ArgumentException("plu", exc_singular_matrix, SOURCE_INFO);

    // Forward sustitution.
    auto p = plu.l.columns();
    Matrix x = b;
    for (index_t k = 0; k < nRows; k++) {
        if (p < nRows)
            p++;
        for (index_t m = 0; m < nColumnsB; m++) {
            if (plu.p[k] != k)
                std::swap(x(k, m), x(plu.p[k], m));
            for (index_t j = k + 1; j < p; j++)
                x(j, m) -= plu.l(k, j - k - 1) * x(k, m);
        }
    }

    // Backward sustitution.
    p = 1;
    for (diff_t i = nRows - 1; i >= 0; i--) {
        for (index_t m = 0; m < nColumnsB; m++) {
            auto temp = x(i, m);
            for (index_t k = 1; k < p; k++)
                temp -= plu.u(i, k) * x(k + i, m);
            x(i, m) = temp / plu.u(i, 0);
        }
        if (p < nColumns)
            p++;
    }

    return x;
}

//-----------------------------------------------------------------------------------------------------------------
nct::ColumnVector nct::math::linear_algebra::solveSystemPLUBanded(const PLUBanded& plu,
    const ColumnVector& b, double tol)
{
    size_t nRows = plu.u.rows();
    size_t nColumns = plu.u.columns();

    if (plu.l.size() == 0)
        throw EmptyArrayException("l", SOURCE_INFO);

    if (plu.u.size() == 0)
        throw EmptyArrayException("u", SOURCE_INFO);

    if (plu.l.rows() != nRows || plu.l.columns() >= nColumns || nRows < nColumns)
        throw ArgumentException("l, u", exc_bad_linear_system, SOURCE_INFO);

    if (nRows != b.size())
        throw ArgumentException("l, u, b", exc_bad_linear_system, SOURCE_INFO);

    tol = (tol >= 0 ? tol : SMALL_TOL) * nRows * max(maximumAbs(plu.l.begin(), plu.l.end()),
        maximumAbs(plu.u.begin(), plu.u.end()));
    for (index_t i = 0; i < nRows; i++)
        if (std::abs(plu.u(i, 0)) <= tol)
            throw ArgumentException("plu", exc_singular_matrix, SOURCE_INFO);

    // Forward sustitution.
    auto p = plu.l.columns();
    ColumnVector x = b;
    for (index_t k = 0; k < nRows; k++) {
        if (p < nRows)
            p++;

        if (plu.p[k] != k)
            std::swap(x[k], x[plu.p[k]]);

        for (index_t j = k + 1; j < p; j++)
            x[j] -= plu.l(k, j - k - 1) * x[k];
    }

    // Backward sustitution.
    p = 1;
    for (diff_t i = nRows - 1; i >= 0; i--) {
        auto temp = x[i];
        for (index_t k = 1; k < p; k++)
            temp -= plu.u(i, k) * x[k + i];
        x[i] = temp / plu.u(i, 0);

        if (p < nColumns)
            p++;
    }

    return x;
}


//-----------------------------------------------------------------------------------------------------------------
nct::math::linear_algebra::Eigensol nct::math::linear_algebra::symmEigenvectors(const Matrix& a)
{
    if ((a.rows() == 0) && (a.columns() == 0))
        return Eigensol();

    if (!isSymmetric(a))
        throw ArgumentException("a", exc_non_symmetric_matrix, SOURCE_INFO);

    Eigen::MatrixXd A = Eigen::MatrixXd::Zero(a.rows(), a.columns());    

    for (size_t i = 0; i < a.rows(); i++)
        for (size_t j = 0; j < a.rows(); j++)
            A(i, j) = a(i, j);

    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> es(A);

    Eigensol eig;

    eig.d.resize(es.eigenvalues().rows());
    for (size_t i = 0; i < static_cast<size_t>(es.eigenvalues().rows()); i++)
        eig.d[i] = es.eigenvalues()(i);

    eig.v.resize(es.eigenvectors().rows(), es.eigenvectors().cols());
    for (size_t i = 0; i < static_cast<size_t>(es.eigenvectors().rows()); i++)
        for (size_t j = 0; j < static_cast<size_t>(es.eigenvectors().rows()); j++)
            eig.v(i, j) = es.eigenvectors()(i, j);

    return eig;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
