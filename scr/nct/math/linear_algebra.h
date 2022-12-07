//=================================================================================================================
/**
 *  @file       linear_algebra.h
 *  @brief      nct::math::linear_algebra namespace.
 *  @details    Declaration of the nct::math::linear_algebra namespace.
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

#ifndef NCT_LINEAR_ALGEBRA_H_INCLUDE
#define NCT_LINEAR_ALGEBRA_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_constants.h>
#include <nct/Array.h>
#include <nct/Array2D.h>

//=================================================================================================================
namespace nct {
namespace math {
/**
 *  @brief      Linear algebra namespace.
 *  @details    This namespace contains functions related to matrix factorizations and
 *              linear systems.
 */
namespace linear_algebra {

////////// Structures //////////

/**
 *  @brief      LDL' decomposition.
 *  @details    Structure that contains the elements of a LDL' decomposition.
 */
struct NCT_EXPIMP LDLt final {

    Matrix l;           /**< Lower triangular matrix L. */

    ColumnVector d;     /**< Diagonal elements of matrix D. */
};

/**
 *  @brief      Complex LDL' decomposition.
 *  @details    Structure that contains the elements of a LDL' decomposition.
 */
struct NCT_EXPIMP ComplexLDLt final {

    ComplexMatrix l;        /**< Lower triangular matrix L. */

    ComplexColumnVector d;  /**< Diagonal elements of matrix D. */

};

/**
 *  @brief      LU decomposition.
 *  @details    Structure that contains the elements of an LU decomposition.
 */
struct NCT_EXPIMP LU final {

    Matrix l;   /**< Lower triangular matrix L. */

    Matrix u;   /**< Upper triangular matrix U. */
};

/**
 *  @brief      Complex LU decomposition.
 *  @details    Structure that contains the elements of an LU decomposition.
 */
struct NCT_EXPIMP ComplexLU final {

    ComplexMatrix l;    /**< Lower triangular matrix L. */

    ComplexMatrix u;    /**< Upper triangular matrix U. */
};

/**
 *  @brief      PA = LU decomposition.
 *  @details    Structure that contains the elements of a PA = LU decomposition.
 */
struct NCT_EXPIMP PLU final {

    Matrix lu;          /**< LU decomposition. */

    Array<size_t> p;    /**< Array of permutations. The i-th element of this array indicates the row in the 
                             original matrix A that is represented by the i-th row of the LU product.*/
    size_t np {0};      /**< The number of permutations performed over the original matrix. */
};

/**
 *  @brief      Complex PA = LU decomposition.
 *  @details    Structure that contains the elements of a PA = LU decomposition.
 */
struct NCT_EXPIMP ComplexPLU final {

    ComplexMatrix lu;   /**< LU decomposition. */

    Array<size_t> p;    /**< Array of permutations. The i-th element of this array indicates the row in the 
                             original matrix A that is represented by the i-th row of the LU product.*/
    size_t np {0};      /**< The number of permutations performed over the original matrix. */
};


/**
 *  @brief      (P^-1)LU decomposition of a banded matrix.
 *  @details    Structure that contains the elements of a (P^-1)LU decomposition of
 *              a banded matrix.
 */
struct NCT_EXPIMP PLUBanded final {

    Matrix l;           /**< Lower triangular matrix L. */

    Matrix u;           /**< Upper triangular matrix U. */

    Array<size_t> p;    /**< Array of permutations. The i-th element of this array indicates the row in the 
                             original matrix A that is represented by the i-th row of the LU product.*/
    size_t np {0};      /**< The number of permutations performed over the original matrix. */
};

/**
 *  @brief      Complex (P^-1)LU decomposition of a banded matrix.
 *  @details    Structure that contains the elements of a (P^-1)LU decomposition of
 *              a banded matrix.
 */
struct NCT_EXPIMP ComplexPLUBanded final {

    ComplexMatrix l;    /**< Lower triangular matrix L (n*diagColumn). */

    ComplexMatrix u;    /**< Upper triangular matrix U (n*columns of a). */

    Array<size_t> p;    /**< Array of permutations. The i-th element of this array indicates the row in the 
                             original matrix A that is represented by the i-th row of the LU product.*/
    size_t np {0};      /**< The number of permutations performed over the original matrix. */
};

/**
 *  @brief      Eigenvalues and eigenvectors.
 *  @details    Structure that contains the eigenvalues and eigenvectors of a matrix.
 */
struct NCT_EXPIMP Eigensol final {

    Matrix v;           /**< Eigenvectors. */

    ColumnVector d;     /**< Eigenvalues. */
};

/**
*  @brief      Eigenvalues and eigenvectors.
*  @details    Structure that contains the eigenvalues and eigenvectors of a matrix.
*/
struct NCT_EXPIMP ComplexEigen final {

    ComplexMatrix v;        /**< Eigenvectors. */

    ComplexColumnVector d;  /**< Eigenvalues. */
};


////////// General purpose functions //////////

/**
 *  @brief      Is upper triangular?
 *  @details    This function indicates whether a matrix is upper triangular.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is upper triangular.
 */
NCT_EXPIMP bool isUpperTriangular(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is lower triangular?
 *  @details    This function indicates whether a matrix is lower triangular.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is lower triangular.
 */
NCT_EXPIMP bool isLowerTriangular(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is symmetric?
 *  @details    This function indicates whether a matrix is symmetric.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is symmetric.
 */
NCT_EXPIMP bool isSymmetric(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Make symmetric.
 *  @details    This function forces a matrix to be symmetric.
 *  @param[in, out] a  The matrix to modify.
 */
NCT_EXPIMP void makeSymmetric(Matrix& a);

////////// Inverse and square root //////////

/**
 *  @brief      Inverse of a matrix.
 *  @details    This function calculates the inverse of a matrix.
 *  @param[in]  a  The input matrix.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @param[in]  improvementSteps  The number of times that the result is improved by estimating the
 *              error of the solution.
 *  @returns    The inverse of the input matrix.
 */
NCT_EXPIMP Matrix inverse(const Matrix& a, 
    double tol = SMALL_TOL, unsigned int improvementSteps = 0);

/**
 *  @brief      Inverse of a lower triangular matrix.
 *  @details    This function calculates the inverse of a lower triangular matrix.
 *  @param[in]  a  The input matrix.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The inverse of the input matrix.
 */
NCT_EXPIMP Matrix inverseL(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Inverse of an upper triangular matrix.
 *  @details    This function calculates the inverse of an upper triangular matrix.
 *  @param[in]  a  The input matrix.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The inverse of the input matrix.
 */
NCT_EXPIMP Matrix inverseU(const Matrix& a, double tol = SMALL_TOL);

////////// Linear systems  //////////

/**
 *  @brief      Solve linear system.
 *  @details    This function solves the linear system Ax=b.
 *  @param[in]  a  The n x m matrix A.
 *  @param[in]  b  The n-length vector b. 
 *  @param[in]  improvementSteps  The number of times that the system Ae = b - A(x+e) is
 *              solved to improve the final solution.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ColumnVector solveSystem(const Matrix& a, const ColumnVector& b, 
    double tol = SMALL_TOL, unsigned int improvementSteps = 0);

/**
 *  @brief      Solve linear system.
 *  @details    This function solves the linear system AX=B.
 *  @param[in]  a  The n x m matrix A.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @param[in]  improvementSteps  The number of times that the system AE = B - A(X+E) is
 *              solved to improve the final solution.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP Matrix solveSystem(const Matrix& a, const Matrix& b,
    double tol = SMALL_TOL, unsigned int improvementSteps = 0);

/**
 *  @brief      Solve linear system Lx=b.
 *  @details    This function solves the linear system Lx = b where L is a lower triangular matrix. 
 *  @param[in]  l  The n x n matrix L.
 *  @param[in]  b  The n-length vector b. 
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ColumnVector solveSystemL(const Matrix& l,
    const ColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system LX=B.
 *  @details    This function solves the linear system LX = B where L is a lower triangular matrix. 
 *  @param[in]  l  The n x n matrix L.
 *  @param[in]  b  The n x p matrix B.     
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP Matrix solveSystemL(const Matrix& l, const Matrix& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system Ux=b.
 *  @details    This function solves the linear system Ux = b where L is an upper triangular matrix. 
 *  @param[in]  u  The n x n matrix U.
 *  @param[in]  b  The n-length vector b.  
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ColumnVector solveSystemU(const Matrix& u,
    const ColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system UX=B.
 *  @details    This function solves the linear system UX = B where L is an upper triangular matrix. 
 *  @param[in]  u  The n x n matrix U.
 *  @param[in]  b  The n x p matrix B. 
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP Matrix solveSystemU(const Matrix& u, const Matrix& b, double tol = SMALL_TOL);

////////// PA = LU factorization //////////

/**
 *  @brief      PA = LU factorization.
 *  @details    This function calculates the PA = LU factorization. The result is reported in one matrix
 *              and one vector that contains the permutations of A. The entries on the matrix below the
 *              diagonal correspond to the L matrix, and the elements on and above the diagonal
 *              correspond to the U matrix. The diagonal on the L matrix are 1's. 
 *  @param[in]  a  The matrix to factorize.  
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero. 
 *  @returns    The factorization of the input matrix.
 */
NCT_EXPIMP PLU pluFactorization(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the PA = LU factorization.
 *  @details    This function solves the linear system P^-1LU x = b where LU is the result of the
 *              PA=LU factorization and P is the permutation matrix. 
 *  @param[in]  plu  PA=LA factorization of the system matrix of size n x n.
 *  @param[in]  b  The n-length vector b.         
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ColumnVector solveSystemPLU(const PLU& plu, const ColumnVector& b, 
    double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the PA = LU factorization.
 *  @details    This function solves the linear system P^-1LU X = B where LU is the result of the
 *              PA=LU factorization and P is the permutation matrix. 
 *  @param[in]  plu  PA=LA factorization of the system matrix of size n x n.
 *  @param[in]  b  The n x p matrix B. 
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP Matrix solveSystemPLU(const PLU& plu, const Matrix& b, double tol = SMALL_TOL);

////////// PA = LU factorization of banded matrices //////////

/**
 *  @brief      PA=LU factorization of banded matrix.
 *  @details    This function calculates the PA=LU factorization for banded matrices that are represented
 *              in compact form (n rows and m columns, m<n). 
 *  @param[in]  a  The matrix to factorize.  
 *  @param[in]  diagColumn  Column in the input matrix that corresponds to the main diagonal.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero. 
 *  @returns    The factorization of the input matrix.
 */
NCT_EXPIMP PLUBanded pluFactorizationOfBandedMatrix(
    const Matrix& a, size_t diagColumn, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the PA=LU factorization of a banded matrix.
 *  @details    This function solves the linear system P^-1LU x = b where LU is the result of the
 *              PA=LU banded factorization and P is the permutation matrix. 
 *  @param[in]  plu  PA=LU factorization of the system matrix.
 *  @param[in]  b  The n-length vector b.    
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ColumnVector solveSystemPLUBanded(const PLUBanded& plu,
    const ColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the PA=LU factorization of a banded matrix.
 *  @details    This function solves the linear system P^-1LU X = B where LU is the result of the
 *              PA=LU banded factorization and P is the permutation matrix. 
 *  @param[in]  plu  PA=LU factorization of the system matrix.
 *  @param[in]  b  The n x p matrix B.    
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP Matrix solveSystemPLUBanded(const PLUBanded& plu,
    const Matrix& b, double tol = SMALL_TOL);

////////// Eigenvalues and eigenvectors //////////            

/**
 *  @brief      Eigenvalues and eigenvectors of a symmetric matrix.
 *  @details    This function calculates the eigenvalues and eigenvectors of a symmetric 
 *              real matrix. The eigenvectors are returned in one array v, and the eigenvalues
 *              are returned in one array d.
 *  @param[in]  a  The input matrix.  
 *  @returns    The eigenvalues and eigenvectors of the input matrix.
 */
NCT_EXPIMP Eigensol symmEigenvectors(const Matrix& a);

}}}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
