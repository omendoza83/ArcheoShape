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
 *  @brief      QR decomposition.
 *  @details    Structure that contains the elements of a QR decomposition.
 */
struct NCT_EXPIMP QR final {

    Matrix q;   /**< Orthogonal matrix Q. */

    Matrix r;   /**< Upper triangular matrix R. */
};

/**
 *  @brief      Complex QR decomposition.
 *  @details    Structure that contains the elements of a QR decomposition.
 */
struct NCT_EXPIMP ComplexQR final {

    ComplexMatrix q;    /**< Unitary matrix Q. */

    ComplexMatrix r;    /**< Upper triangular matrix R. */
};

/**
 *  @brief      SVD decomposition.
 *  @details    Structure that contains the elements of a SVD decomposition (A=UWV').
 *              The factorization is always expressed in the thin form of the SVD.
 */
struct NCT_EXPIMP SVD final {

    Matrix u;           /**< Orthogonal matrix U (array of size m*n). */

    Matrix v;           /**< Orthogonal matrix V (array of size n*n). */

    ColumnVector w;     /**< Singular values (Vector of size n). */
};

/**
 *  @brief      Complex SVD decomposition.
 *  @details    Structure that contains the elements of a complex SVD decomposition (A=UWV').
 *              The factorization is always expressed in the thin form of the SVD.
 */
struct NCT_EXPIMP ComplexSVD final {

    ComplexMatrix u;    /**< Unitary matrix U (array of size m*n). */

    ComplexMatrix v;    /**< Unitary matrix V (array of size n*n). */

    ColumnVector w;     /**< Singular values (Vector of size n). */
};

/**
 *  @brief      Jacobi decomposition.
 *  @details    Structure that contains the elements of a jacobi decomposition (A=VDV').
 */
struct NCT_EXPIMP Jacobi final {

    Matrix v;           /**< Orthogonal matrix V (or eigenvectors). */

    ColumnVector d;     /**< Singular values (or eigenvalues). */
};

/**
 *  @brief      Complex jacobi decomposition.
 *  @details    Structure that contains the elements of a complex jacobi decomposition (A=VDV').
 */
struct NCT_EXPIMP ComplexJacobi final {

    ComplexMatrix v;    /**< Unitary matrix V (or eigenvectors). */

    ColumnVector d;     /**< Singular values (or eigenvalues). */
};

/**
 *  @brief      Eigenvalues and eigenvectors.
 *  @details    Structure that contains the eigenvalues and eigenvectors of a matrix.
 */
struct NCT_EXPIMP Eigen final {

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

/**
 *  @brief      Range and null space of a matrix.
 *  @details    Structure that contains the range and null space of a matrix.
 */
struct NCT_EXPIMP RangeAndNullity final {

    int rank {0};           /**< Rank. */

    int nullity {0};        /**< Nullity. */

    Matrix range;           /**< Range. */

    Matrix nullSpace;       /**< Null space. */
};

/**
 *  @brief      Range and null space of a complex matrix.
 *  @details    Structure that contains the range and null space of a complex matrix.
 */
struct NCT_EXPIMP ComplexRangeAndNullity final {

    int rank {0};               /**< Rank. */

    int nullity {0};            /**< Nullity. */

    ComplexMatrix range;        /**< Range. */

    ComplexMatrix nullSpace;    /**< Null space. */
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
 *  @brief      Is upper triangular?
 *  @details    This function indicates whether a complex matrix is upper triangular.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is upper triangular.
 */
NCT_EXPIMP bool isUpperTriangular(const ComplexMatrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is lower triangular?
 *  @details    This function indicates whether a matrix is lower triangular.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is lower triangular.
 */
NCT_EXPIMP bool isLowerTriangular(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is lower triangular?
 *  @details    This function indicates whether a matrix is lower triangular.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is lower triangular.
 */
NCT_EXPIMP bool isLowerTriangular(const ComplexMatrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is upper Hessenberg?
 *  @details    This function indicates whether a matrix is upper Hessenberg.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is upper Hessenberg.
 */
NCT_EXPIMP bool isUpperHessenberg(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is upper Hessenberg?
 *  @details    This function indicates whether a complex matrix is upper Hessenberg.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is upper Hessenberg.
 */
NCT_EXPIMP bool isUpperHessenberg(const ComplexMatrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is lower Hessenberg?
 *  @details    This function indicates whether a matrix is lower Hessenberg.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is lower Hessenberg.
 */
NCT_EXPIMP bool isLowerHessenberg(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is lower Hessenberg?
 *  @details    This function indicates whether a matrix is lower Hessenberg.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is lower Hessenberg.
 */
NCT_EXPIMP bool isLowerHessenberg(const ComplexMatrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is symmetric?
 *  @details    This function indicates whether a matrix is symmetric.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is symmetric.
 */
NCT_EXPIMP bool isSymmetric(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is symmetric?
 *  @details    This function indicates whether a matrix is symmetric.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is symmetric.
 */
NCT_EXPIMP bool isSymmetric(const ComplexMatrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is Hermitian?
 *  @details    This function indicates whether a matrix is Hermitian.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is Hermitian.
 */
NCT_EXPIMP bool isHermitian(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is Hermitian?
 *  @details    This function indicates whether a matrix is Hermitian.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is Hermitian.
 */
NCT_EXPIMP bool isHermitian(const ComplexMatrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is diagonal?
 *  @details    This function indicates whether a matrix is diagonal.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is diagonal.
 */
NCT_EXPIMP bool isDiagonal(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is diagonal?
 *  @details    This function indicates whether a matrix is diagonal.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is diagonal.
 */
NCT_EXPIMP bool isDiagonal(const ComplexMatrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is scalar?
 *  @details    This function indicates whether a matrix is scalar.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is scalar.
 */
NCT_EXPIMP bool isScalar(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is scalar?
 *  @details    This function indicates whether a matrix is scalar.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is scalar.
 */
NCT_EXPIMP bool isScalar(const ComplexMatrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is symmetric positive definite?
 *  @details    This function indicates whether a matrix is symmetric positive definite by using the
 *              Cholesky factorization. If the factorization fails, the matrix is not symmetric positive
 *              definite.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is symmetric positive definite.
 */
NCT_EXPIMP bool isPosDef(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Is symmetric positive definite?
 *  @details    This function indicates whether a complex matrix is symmetric positive definite by using
 *              the Cholesky factorization. If the factorization fails, the matrix is not symmetric
 *              positive definite.
 *  @param[in]  a  The matrix to be checked.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    True, if the matrix is symmetric positive definite.
 */
NCT_EXPIMP bool isPosDef(const ComplexMatrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Make symmetric.
 *  @details    This function forces a matrix to be symmetric.
 *  @param[in, out] a  The matrix to modify.
 */
NCT_EXPIMP void makeSymmetric(Matrix& a);

/**
 *  @brief      Make symmetric.
 *  @details    This function forces a matrix to be symmetric.
 *  @param[in, out] a  The matrix to modify.
 */
NCT_EXPIMP void makeSymmetric(ComplexMatrix& a);

/**
 *  @brief      Conjugate transpose.
 *  @details    This function computes the conjugate transpose of a matrix.
 *  @param[in]  a  The input matrix.
 *  @returns    The conjugate transpose of the input matrix.
 */
NCT_EXPIMP ComplexMatrix conjugateTranspose(const ComplexMatrix& a);

/**
 *  @brief      L1 induced norm.
 *  @details    This function computes the L1 induced matrix norm. 
 *  @param[in]  a  The input matrix.
 *  @returns    The matrix norm.
 */
NCT_EXPIMP double matrixNormL1(const Matrix& a);

/**
 *  @brief      L1 induced norm.
 *  @details    This function computes the L1 induced matrix norm. 
 *  @param[in]  a  The input matrix.
 *  @returns    The matrix norm.
 */
NCT_EXPIMP double matrixNormL1(const ComplexMatrix& a);

/**
 *  @brief      Infinity induced norm.
 *  @details    This function computes the infinity induced matrix norm. 
 *  @param[in]  a  The input matrix.
 *  @returns    The matrix norm.
 */
NCT_EXPIMP double matrixNormLI(const Matrix& a);

/**
 *  @brief      Infinity induced norm.
 *  @details    This function computes the infinity induced matrix norm. 
 *  @param[in]  a  The input matrix.
 *  @returns    The matrix norm.
 */
NCT_EXPIMP double matrixNormLI(const ComplexMatrix& a);

/**
 *  @brief      Range, null space, rank and nullity of a matrix.
 *  @details    This function gets the range, null space, rank and nullity of a matrix using the SVD
 *              decomposition.
 *  @param[in]  a  The matrix to analyze. 
 *  @param[in]  maxIt  The maximum number of allowed iterations in the SVD algorithm.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The matrix range and nullity.
 */
NCT_EXPIMP RangeAndNullity matrixRangeAndNullity(const Matrix& a,
    unsigned int maxIt = 1000, double tol = SMALL_TOL);

/**
 *  @brief      Range, null space, rank and nullity of a complex matrix.
 *  @details    This function gets the range, null space, rank and nullity of a complex matrix using 
 *              the SVD decomposition.
 *  @param[in]  a  The matrix to analyze. 
 *  @param[in]  maxIt  The maximum number of allowed iterations in the SVD algorithm.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The matrix range and nullity.
 */
NCT_EXPIMP ComplexRangeAndNullity matrixRangeAndNullity(const ComplexMatrix& a,
    unsigned int maxIt = 1000, double tol = SMALL_TOL);

////////// Condition number and pre-conditioners //////////

/**
 *  @brief      Condition number.
 *  @details    This function calculates the condition number of a square matrix. The condition
 *              number is calculated by using the SVD decomposition and the following expresion: k(A) =
 *              smax/smin, where smax and smin are the maximal and minimal singular values of the matrix
 *              A.
 *  @param[in]  a  The n x m matrix A.
 *  @returns    The condition number of A.
 */
NCT_EXPIMP double cond(const Matrix& a);

/**
 *  @brief      Condition number.
 *  @details    This function calculates the condition number of a square matrix. The condition
 *              number is calculated by using the following expresion: k(A) = ||A|| * ||A^-1||, where
 *              ||*|| is the L1 induced matrix norm.
 *  @param[in]  a  The n x m matrix A.
 *  @returns    The condition number of A.
 */
NCT_EXPIMP double condL1(const Matrix& a);

/**
 *  @brief      Condition number.
 *  @details    This function calculates the condition number of a square matrix. The condition
 *              number is calculated by using the following expresion: k(A) = ||A|| * ||A^-1||, where
 *              ||*|| is the L1 induced matrix norm.
 *  @param[in]  a  The n x m matrix A.
 *  @returns    The condition number of A.
 */
NCT_EXPIMP double condL1(const ComplexMatrix& a);

/**
 *  @brief      Condition number.
 *  @details    This function calculates the condition number of a square matrix. The condition
 *              number is calculated by using the following expresion: k(A) = ||A|| * ||A^-1||, where
 *              ||*|| is the infinite induced matrix norm.
 *  @param[in]  a  The n x m matrix A.
 *  @returns    The condition number of A.
 */
NCT_EXPIMP double condLI(const Matrix& a);

/**
 *  @brief      Condition number.
 *  @details    This function calculates the condition number of a square matrix. The condition
 *              number is calculated by using the following expresion: k(A) = ||A|| * ||A^-1||, where
 *              ||*|| is the infinite induced matrix norm.
 *  @param[in]  a  The n x m matrix A.
 *  @returns    The condition number of A.
 */
NCT_EXPIMP double condLI(const ComplexMatrix& a);

/**
 *  @brief      Condition number.
 *  @details    This function calculates the condition number of a square matrix. The condition
 *              number is calculated by using the following expresion: k(A) = ||A|| * ||A^-1||, where
 *              ||*|| is the frobenius norm.
 *  @param[in]  a  The n x m matrix A.
 *  @returns    The condition number of A.
 */
NCT_EXPIMP double condF(const Matrix& a);

/**
 *  @brief      Condition number.
 *  @details    This function calculates the condition number of a square matrix. The condition
 *              number is calculated by using the following expresion: k(A) = ||A|| * ||A^-1||, where
 *              ||*|| is the frobenius norm.
 *  @param[in]  a  The n x m matrix A.
 *  @returns    The condition number of A.
 */
NCT_EXPIMP double condF(const ComplexMatrix& a);

/**
 *  @brief      Jacobi preconditioner.
 *  @details    This function calculates the Jacobi preconditioner (P^-1) that is used to improve
 *              the condition number of a square matrix.
 *  @param[in]  a  The n x m matrix A.
 *  @returns    The preconditioner of A.
 */
NCT_EXPIMP Matrix jacobiPreconditioner(const Matrix& a);

////////// Determinant //////////

/**
 *  @brief      Determinant.
 *  @details    This function calculates the determinant of a square matrix.
 *  @param[in]  a  The input matrix.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The determinant of the input matrix.
 */
NCT_EXPIMP double deteminant(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Determinant.
 *  @details    This function calculates the determinant of a square matrix.
 *  @param[in]  a  The input matrix.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The determinant of the input matrix.
 */
NCT_EXPIMP Complex deteminant(const ComplexMatrix& a, double tol = SMALL_TOL);

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
 *  @brief      Inverse of a complex matrix.
 *  @details    This function calculates the inverse of a complex matrix.
 *  @param[in]  a  The input matrix.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @param[in]  improvementSteps  The number of times that the result is improved by estimating the
 *              error of the solution.
 *  @returns    The inverse of the input matrix.
 */
NCT_EXPIMP ComplexMatrix inverse(const ComplexMatrix& a, 
    double tol = SMALL_TOL, unsigned int improvementSteps = 0);

/**
 *  @brief      Pseudoinverse of a matrix.
 *  @details    This function calculates the pseudoinverse of a matrix.
 *  @note       This function uses the SVD factorization to obtain the pseudoinverse.
 *  @param[in]  a  The input matrix.
 *  @param[in]  tol  The tolerance that is used to determine whether one singular value is zero.
 *  @returns    The pseudoinverse of the input matrix.
 */
NCT_EXPIMP Matrix pseudoinverse(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Pseudoinverse of a complex matrix.
 *  @details    This function calculates the pseudoinverse of a complex matrix.
 *  @note       This function uses the SVD factorization to obtain the pseudoinverse.
 *  @param[in]  a  The input matrix.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The pseudoinverse of the input matrix.
 */
NCT_EXPIMP ComplexMatrix pseudoinverse(const ComplexMatrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Inverse of a lower triangular matrix.
 *  @details    This function calculates the inverse of a lower triangular matrix.
 *  @param[in]  a  The input matrix.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The inverse of the input matrix.
 */
NCT_EXPIMP Matrix inverseL(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Inverse of a lower triangular matrix.
 *  @details    This function calculates the inverse of a lower triangular matrix.
 *  @param[in]  a  The input matrix.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The inverse of the input matrix.
 */
NCT_EXPIMP ComplexMatrix inverseL(const ComplexMatrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Inverse of an upper triangular matrix.
 *  @details    This function calculates the inverse of an upper triangular matrix.
 *  @param[in]  a  The input matrix.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The inverse of the input matrix.
 */
NCT_EXPIMP Matrix inverseU(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Inverse of an upper triangular matrix.
 *  @details    This function calculates the inverse of an upper triangular matrix.
 *  @param[in]  a  The input matrix.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The inverse of the input matrix.
 */
NCT_EXPIMP ComplexMatrix inverseU(const ComplexMatrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Square root of a symmetric matrix.
 *  @details    This function calculates the square root of a symmetric matrix.
 *  @param[in]  a  The input matrix.
 *  @returns    The square root of the input matrix.
 */
NCT_EXPIMP Matrix symmSquareRoot(const Matrix& a);

/**
 *  @brief      Inverse of the square root of a symmetric matrix.
 *  @details    This function calculates the inverse of the square root of a symmetric matrix.
 *  @param[in]  a  The matrix to factorize.
 *  @returns    The inverse of the square root of the input matrix.
 */
NCT_EXPIMP Matrix symmInverseSquareRoot(const Matrix& a);

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
 *  @brief      Solve complex linear system.
 *  @details    This function solves the complex linear system Ax=b.
 *  @param[in]  a  The n x m matrix A. 
 *  @param[in]  b  The n-length vector b.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @param[in]  improvementSteps  The number of times that the system Ae = b - A(x+e) is
 *              solved to improve the final solution.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexColumnVector solveSystem(const ComplexMatrix& a,
    const ComplexColumnVector& b, double tol = SMALL_TOL, unsigned int improvementSteps = 0);

/**
 *  @brief      Solve complex linear system.
 *  @details    This function solves the complex linear system AX=B.
 *  @param[in]  a  The n x m matrix A.
 *  @param[in]  b  The n x p matrix B.    
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @param[in]  improvementSteps  The number of times that the system AE = B - A(X+E) is
 *              solved to improve the final solution.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexMatrix solveSystem(const ComplexMatrix& a,
    const ComplexMatrix& b, double tol = SMALL_TOL, unsigned int improvementSteps = 0);

/**
 *  @brief      Least square solution of linear system.
 *  @details    This function solves the linear system (AtA)x = (At)b. If A is invertible,
 *              the result is equivalent to that obtained by the solveSystem function.
 *  @param[in]  a  The n x m matrix A.
 *  @param[in]  b  The n-length vector b.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @param[in]  improvementSteps  The number of times that the system (AtA)e = (At)b - (AtA)(x+e) is
 *              solved to improve the final solution.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ColumnVector solveLeastSquareSystem(const Matrix& a,
    const ColumnVector& b, double tol = SMALL_TOL, unsigned int improvementSteps = 0);

/**
 *  @brief      Least square solution of linear system.
 *  @details    This function solves the linear system (AtA)X = (At)B. If A is invertible,
 *              the result is equivalent to that obtained by the solveSystem function.
 *  @param[in]  a  The n x m matrix A.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @param[in]  improvementSteps  The number of times that the system (AtA)E = (At)B - (AtA)(X+E) is
 *              solved to improve the final solution.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP Matrix solveLeastSquareSystem(const Matrix& a,
    const Matrix& b, double tol = SMALL_TOL, unsigned int improvementSteps = 0);

/**
 *  @brief      Least square solution of complex linear system.
 *  @details    This function solves the complex linear system (AtA)x = (At)b. If A is invertible,
 *              the result is equivalent to that obtained by the solveSystem function.
 *  @param[in]  a  The n x m matrix A.
 *  @param[in]  b  The n-length vector b.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @param[in]  improvementSteps  The number of times that the system (AtA)e = (At)b - (AtA)(x+e) is
 *              solved to improve the final solution.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexColumnVector solveLeastSquareSystem(const ComplexMatrix& a,
    const ComplexColumnVector& b, double tol = SMALL_TOL, unsigned int improvementSteps = 0);

/**
 *  @brief      Least square solution of complex linear system.
 *  @details    This function solves the complex linear system (AtA)X = (At)B. If A is invertible,
 *              the result is equivalent to that obtained by the solveSystem function.
 *  @param[in]  a  The n x m matrix A.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @param[in]  improvementSteps  The number of times that the system (AtA)E = (At)B - (AtA)(X+E) is
 *              solved to improve the final solution.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexMatrix solveLeastSquareSystem(const ComplexMatrix& a,
    const ComplexMatrix& b, double tol = SMALL_TOL, unsigned int improvementSteps = 0);

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
 *  @brief      Solve linear system Lx=b.
 *  @details    This function solves the linear system Lx = b where L is a lower triangular matrix. 
 *  @param[in]  l  The n x n matrix L.
 *  @param[in]  b  The n-length vector b.  
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexColumnVector solveSystemL(const ComplexMatrix& l,
    const ComplexColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system LX=B.
 *  @details    This function solves the linear system Lx = b where L is a lower triangular matrix. 
 *  @param[in]  l  The n x n matrix L.
 *  @param[in]  b  The n x p matrix B.    
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexMatrix solveSystemL(const ComplexMatrix& l,
    const ComplexMatrix& b, double tol = SMALL_TOL);

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

/**
 *  @brief      Solve linear system Ux=b.
 *  @details    This function solves the linear system Ux = b where L is an upper triangular matrix. 
 *  @param[in]  u  The n x n matrix U.
 *  @param[in]  b  The n-length vector b.  
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexColumnVector solveSystemU(const ComplexMatrix& u,
    const ComplexColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system UX=B.
 *  @details    This function solves the linear system UX = B where L is an upper triangular matrix. 
 *  @param[in]  u  The n x n matrix U.
 *  @param[in]  b  The n x p matrix B.    
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexMatrix solveSystemU(const ComplexMatrix& u,
    const ComplexMatrix& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the Gaussian elimination method.
 *  @details    This function solves the linear system Ax = b by using the Gaussian elimination of A.
 *  @param[in]  a  The n x m matrix A.
 *  @param[in]  b  The n-length vector b.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ColumnVector solveSystemGaussianReduction(const Matrix& a,
    const ColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the Gaussian elimination method.
 *  @details    This function solves the linear system AX = B by using the Gaussian elimination of A.
 *  @param[in]  a  The n x m matrix A.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP Matrix solveSystemGaussianReduction(const Matrix& a,
    const Matrix& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the Gaussian elimination method.
 *  @details    This function solves the complex linear system Ax = b by using the Gaussian 
 *              elimination of A.
 *  @param[in]  a  The n x m matrix A.
 *  @param[in]  b  The n-length vector b.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexColumnVector solveSystemGaussianReduction(const ComplexMatrix& a,
    const ComplexColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the Gaussian elimination method.
 *  @details    This function solves the complex linear system AX = B  by using the Gaussian 
 *              elimination of A.
 *  @param[in]  a  The n x m matrix A.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexMatrix solveSystemGaussianReduction(const ComplexMatrix& a,
    const ComplexMatrix& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using Gauss-Seidel.
 *  @details    This function solves the linear system Ax=b by using the Gauss-Seidel method.
 *  @param[in]  xIni  The initial guess that is used to initialize the method.
 *  @param[in]  a  The n x n matrix A.
 *  @param[in]  b  The n-length vector b. 
 *  @param[in]  maxIter  The maximun number of iterations before the algorithm is stopped.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ColumnVector solveSystemGaussSeidel(const ColumnVector& xIni,
    const Matrix& a, const ColumnVector& b,
    unsigned int maxIter = 1000, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using Gauss-Seidel.
 *  @details    This function solves the linear system AX=B by using the Gauss-Seidel method.
 *  @param[in]  xIni  The initial guess that is used to initialize the method.
 *  @param[in]  a  The n x n matrix A.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  maxIter  The maximun number of iterations before the algorithm is stopped.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP Matrix solveSystemGaussSeidel(const Matrix& xIni,
    const Matrix& a, const Matrix& b,
    unsigned int maxIter = 1000, double tol = SMALL_TOL);

/**
 *  @brief      Solve complex linear system by using the Gauss-Seidel algorithm.
 *  @details    This function solves the complex linear system Ax=b by using the Gauss-Seidel method.
 *  @param[in]  xIni  The initial guess that is used to initialize the method.
 *  @param[in]  a  The n x n matrix A.
 *  @param[in]  b  The n-length vector b. 
 *  @param[in]  maxIter  The maximun number of iterations before the algorithm is stopped.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexColumnVector solveSystemGaussSeidel(const ComplexColumnVector& xIni,
    const ComplexMatrix& a, const ComplexColumnVector& b,
    unsigned int maxIter = 1000, double tol = SMALL_TOL);

/**
 *  @brief      Solve complex linear system by using the Gauss-Seidel algorithm.
 *  @details    This function solves the complex linear system AX=B by using the Gauss-Seidel method.
 *  @param[in]  xIni  The initial guess that is used to initialize the method.
 *  @param[in]  a  The n x n matrix A.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  maxIter  The maximun number of iterations before the algorithm is stopped.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexMatrix solveSystemGaussSeidel(const ComplexMatrix& xIni,
    const ComplexMatrix& a, const ComplexMatrix& b,
    unsigned int maxIter = 1000, double tol = SMALL_TOL);

/**
 *  @brief      Solve complex linear system by using the conjugate gradient algorithm.
 *  @details    This function solves the complex linear system Ax=b by using the conjugate gradient
 *              method.
 *  @param[in]  a  The n x n matrix A.
 *  @param[in]  b  The n-length vector b.
 *  @param[in]  maxIter  The maximun number of iterations before the algorithm is stopped.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ColumnVector solveSystemCG(const Matrix& a, const ColumnVector& b,
    double tol = SMALL_TOL);

/**
 *  @brief      Solve complex linear system by using the conjugate gradient algorithm.
 *  @details    This function solves the complex linear system AX=B by using the conjugate
 *              gradient method.
 *  @param[in]  a  The n x n matrix A.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  maxIter  The maximun number of iterations before the algorithm is stopped.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP Matrix solveSystemCG(const Matrix& a, const Matrix& b,
    double tol = SMALL_TOL);

/**
 *  @brief      Solve complex linear system by using conjugate gradient.
 *  @details    This function solves the complex linear system Ax=b by using conjugate gradient.
 *  @param[in]  a  The n x n matrix A.
 *  @param[in]  b  The n-length vector b.
 *  @param[in]  maxIter  The maximun number of iterations before the algorithm is stopped.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexColumnVector solveSystemCG(const ComplexMatrix& a,
    const ComplexColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve complex linear system by using conjugate gradient.
 *  @details    This function solves the complex linear system AX=B by using conjugate gradient.
 *  @param[in]  a  The n x n matrix A.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  maxIter  The maximun number of iterations before the algorithm is stopped.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexMatrix solveSystemCG(const ComplexMatrix& a, const ComplexMatrix& b,
    double tol = SMALL_TOL);

/**
 *  @brief      Solve tridiagonal linear system.
 *  @details    This function solves the tridiagonal linear system Ax=b. A is a tridiagonal matrix
 *              and it's expressed in a compact form (3 columns and n rows). The elements a(0, 0) and
 *              a(n-1,2) are ignored, but they should be zero. The column 0 contains the elements below
 *              the main diagonal, the column 1 contains the elements of the main diagonal, and the
 *              column 2 contains the elements above the main diagonal.
 *  @param[in]  a  The n x 3 matrix A.
 *  @param[in]  b  The n-length vector b.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ColumnVector solveTridiagonalSystem(const Matrix& a,
    const ColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve tridiagonal linear system.
 *  @details    This function solves the tridiagonal linear system AX=B. A is a tridiagonal matrix
 *              and it's expressed in a compact form (3 columns and n rows). The elements a(0, 0) and
 *              a(n-1,2) are ignored, but they should be zero. The column 0 contains the elements below
 *              the main diagonal, the column 1 contains the elements of the main diagonal, and the
 *              column 2 contains the elements above the main diagonal.
 *  @param[in]  a  The n x 3 matrix A.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP Matrix solveTridiagonalSystem(const Matrix& a,
    const Matrix& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve tridiagonal complex linear system.
 *  @details    This function solves the tridiagonal linear system Ax=b. A is a tridiagonal matrix
 *              and it's expressed in a compact form (3 columns and n rows). The elements a(0, 0) and
 *              a(n-1,2) are ignored, but they should be zero. The column 0 contains the elements below
 *              the main diagonal, the column 1 contains the elements of the main diagonal, and the
 *              column 2 contains the elements above the main diagonal.
 *  @param[in]  a  The n x 3 matrix A.
 *  @param[in]  b  The n-length vector b.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexColumnVector solveTridiagonalSystem(const ComplexMatrix& a,
    const ComplexColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve tridiagonal complex linear system.
 *  @details    This function solves the tridiagonal linear system AX=B. A is a tridiagonal matrix
 *              and it's expressed in a compact form (3 columns and n rows). The elements a(0, 0) and
 *              a(n-1,2) are ignored, but they should be zero. The column 0 contains the elements below
 *              the main diagonal, the column 1 contains the elements of the main diagonal, and the
 *              column 2 contains the elements above the main diagonal.
 *  @param[in]  a  The n x 3 matrix A.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexMatrix solveTridiagonalSystem(const ComplexMatrix& a,
    const ComplexMatrix& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve cyclic tridiagonal linear system.
 *  @details    This function solves the cyclic tridiagonal linear system Ax=b. A is a tridiagonal matrix
 *              and it's expressed in a compact form (3 columns and n rows). The column 0 contains the
 *              elements below the main diagonal, the column 1 contains the elements of the main
 *              diagonal, and the column 2 contains the elements above the main diagonal. The element
 *              a(0, 0) correspond to the element A(0, n-1), where n is the size of the system. In the
 *              same way, the entry a(n-1,n-1) corresponds to the element A(n-1,0).
 *  @param[in]  a  The n x 3 matrix A.
 *  @param[in]  b  The n-length vector b.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ColumnVector solveCyclicTridiagonalSystem(const Matrix& a,
    const ColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve cyclic tridiagonal linear system.
 *  @details    This function solves the cyclic tridiagonal linear system AX=B. A is a tridiagonal
 *              matrix and it's expressed in a compact form (3 columns and n rows). The column 0 contains the
 *              elements below the main diagonal, the column 1 contains the elements of the main diagonal,
 *              and the column 2 contains the elements above the main diagonal.
 *              The element a(0, 0) correspond to the element A(0, n-1), where n is the size of the system.
 *              In the same way, the entry a(n-1,n-1) corresponds to the element A(n-1,0).
 *  @param[in]  a  The n x 3 matrix A.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP Matrix solveCyclicTridiagonalSystem(const Matrix& a,
    const Matrix& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve cyclic tridiagonal complex linear system.
 *  @details    This function solves the cyclic tridiagonal linear system Ax=b. A is a tridiagonal
 *              matrix and it's expressed in a compact form (3 columns and n rows). The column 0 contains the
 *              elements below the main diagonal, the column 1 contains the elements of the main diagonal,
 *              and the column 2 contains the elements above the main diagonal.
 *              The element a(0, 0) correspond to the element A(0, n-1), where n is the size of the system.
 *              In the same way, the entry a(n-1,n-1) corresponds to the element A(n-1,0).
 *  @param[in]  a  The n x 3 matrix A.
 *  @param[in]  b  The n-length vector b.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexColumnVector solveCyclicTridiagonalSystem(const ComplexMatrix& a,
    const ComplexColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve cyclic tridiagonal complex linear system.
 *  @details    This function solves the cyclic tridiagonal linear system AX=B. A is a tridiagonal
 *              matrix and it's expressed in a compact form (3 columns and n rows). The column 0 contains the
 *              elements below the main diagonal, the column 1 contains the elements of the main diagonal,
 *              and the column 2 contains the elements above the main diagonal.
 *              The element a(0, 0) correspond to the element A(0, n-1), where n is the size of the system.
 *              In the same way, the entry a(n-1,n-1) corresponds to the element A(n-1,0).
 *  @param[in]  a  The n x 3 matrix A.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexMatrix solveCyclicTridiagonalSystem(const ComplexMatrix& a,
    const ComplexMatrix& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve Vandermonde linear system.
 *  @details    This function solves the Vandermonde linear system sum(xi^k) = qk.
 *  @param[in]  x  The n-length vector x.
 *  @param[in]  q  The n-length vector q.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP RealVector solveVandermondeSystem(const RealVector& x,
    const RealVector& q);

/**
 *  @brief      Solve Vandermonde complex linear system.
 *  @details    This function solves the Vandermonde complex linear system sum(wi*(xi^k)) = qk.
 *  @param[in]  x  The n-length vector x.
 *  @param[in]  q  The n-length vector q.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexVector solveVandermondeSystem(const ComplexVector& x,
    const ComplexVector& q);

/**
 *  @brief      Solve Vandermonde linear system.
 *  @details    This function solves the Vandermonde linear system sum(ci*(xk^i)) = yk.
 *  @param[in]  x  The n-length vector x.
 *  @param[in]  q  The n-length vector q.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP RealVector solveVandermondePoliSystem(const RealVector& x,
    const RealVector& y);

/**
 *  @brief      Solve Vandermonde linear system.
 *  @details    This function solves the Vandermonde complex linear system sum(ci*(xk^i)) = yk.
 *  @param[in]  x  The n-length vector x.
 *  @param[in]  q  The n-length vector q.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexVector solveVandermondePoliSystem(const ComplexVector& x,
    const ComplexVector& y);

/**
 *  @brief      Solve Toeplitz linear system by using the levinson algorithm.
 *  @details    This function solves the Toeplitz linear system Tx = b where T is the Toeplitz
 *              matrix that corresponds to the input array t.
 *  @param[in]  t  Input array. This array can contains the elements of a sequence of size 2l+1 and
 *              indices -l,-l+1, ..., -2, -1, 0, 1, 2, ..., l-1, l; or the sequence of size l+1 and
 *              indices 0, 1, 2, 3, ..., l-1, l.
 *  @param[in]  b  Array b of the system. If LENGTH(x) = LENGTH(b), then the vector x contains indices
 *              from 0 to l. If LENGTH(x) = 2*LENGTH(b) - 1, then array x contains elements of indices
 *              -l,-l+1, ..., -2, -1, 0, 1, 2, ..., l-1, l. Any other relation between the size of these
 *              arrays is not valid.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP RealVector levinson(const RealVector& t, const RealVector& b);

/**
 *  @brief      Solve Toeplitz linear system by using the levinson algorithm.
 *  @details    This function solves the Toeplitz linear system Tx = b where T is the Toeplitz
 *              matrix that corresponds to the input array t.
 *  @param[in]  t  Input array. This array can contains the elements of a sequence of size 2l+1 and
 *              indices -l,-l+1, ..., -2, -1, 0, 1, 2, ..., l-1, l; or the sequence of size l+1 and
 *              indices 0, 1, 2, 3, ..., l-1, l.
 *  @param[in]  b  True indicates that the input array contains a sequence of size 2l+1, false, indicates
 *              that "t" only conatains elements with indices 0, 1, 2, ..., l. In the second case, the
 *              Toeplitz matrix is build by considering that t(-i) = t*(i).
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexVector levinson(const ComplexVector& t, const ComplexVector& b);

////////// Cholesky factorization //////////

/**
 *  @brief      LLt factorization.
 *  @details    This function computes the cholesky factorization of a symmetric matrix. The result is 
 *              reported in one lower triangular matrix.
 *  @param[in]  a  The matrix to factorize.  
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The factorization of the input matrix.
 */
NCT_EXPIMP Matrix lltFactorization(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      LLt factorization.
 *  @details    This function computes the cholesky factorization of an Hermitian matrix. The result is 
 *              reported in one lower triangular matrix.
 *  @param[in]  a  The matrix to factorize.  
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The factorization of the input matrix.
 */
NCT_EXPIMP ComplexMatrix lltFactorization(const ComplexMatrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Incomplete LLt factorization.
 *  @details    This function computes the incomplete Cholesky factorization of a symmetric matrix. The result is 
 *              reported in one lower triangular matrix.
 *  @param[in]  a  The matrix to factorize.  
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The factorization of the input matrix.
 */
NCT_EXPIMP Matrix incompleteLLtFactorization(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Incomplete LLt factorization.
 *  @details    This function computes the incomplete Cholesky factorization of an Hermitian matrix. The result is 
 *              reported in one lower triangular matrix.
 *  @param[in]  a  The matrix to factorize.  
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The factorization of the input matrix.
 */
NCT_EXPIMP ComplexMatrix incompleteLLtFactorization(const ComplexMatrix& a,
    double tol = SMALL_TOL);

/**
 *  @brief      LDLt factorization.
 *  @details    This function computes the LDLt factorization of a symmetric matrix. The result is reported in one
 *              matrix, where the entries on the main diagonal correspond to D and the entries below
 *              the diagonal correspond to L.
 *  @param[in]  a  The matrix to factorize.  
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The factorization of the input matrix.
 */
NCT_EXPIMP Matrix ldltFactorization(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      LDLt factorization.
 *  @details    This function computes the LDLt factorization of an Hermitian matrix. The result is reported in one
 *              matrix, where the entries on the main diagonal correspond to D and the entries below
 *              the diagonal correspond to L.
 *  @param[in]  a  The matrix to factorize.  
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The factorization of the input matrix.
 */
NCT_EXPIMP ComplexMatrix ldltFactorization(const ComplexMatrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Modified LDLt factorization.
 *  @details    This function computes the modified LDLt factorization of a symmetric matrix. The result is reported 
 *              in one matrix, where the entries on the main diagonal correspond to D and the entries below
 *              the diagonal correspond to L.
 *  @param[in]  a  The matrix to factorize.  
 *  @param[in]  delta  The parameter delta of the Cholesky modified algorithm.
 *  @param[in]  beta  The parameter beta of the Cholesky modified algorithm.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero. 
 *  @returns    The factorization of the input matrix.
 */
NCT_EXPIMP Matrix ldltModFactorization(const Matrix& a,
    double delta = 0.10, double beta = 100, double tol = SMALL_TOL);

/**
 *  @brief      LDLt product.
 *  @details    This function inverts the result of any function that calculates 
 *              the LDLt factorization (i.e. LDL').
 *  @param[in]  ldlt  Matrix with the LDLt factorization. 
 *  @returns    The LDLt product.
 */
NCT_EXPIMP Matrix ldltProduct(const Matrix& ldlt);

/**
 *  @brief      LDL' product.
 *  @details    This function inverts the result of any function that calculates 
 *              the LDLt factorization (i.e. LDL').
 *  @param[in]  ldlt  Matrix with the LDLt factorization. 
 *  @returns    The LDLt product.
 */
NCT_EXPIMP ComplexMatrix ldltProduct(const ComplexMatrix& ldlt);

/**
 *  @brief      Result of the LDLt factorization.
 *  @details    This function separates the L and D matrices from the result computed by any function that
 *              calculates the LDLt factorization.
 *  @param[in]  ldlt  Matrix with the LDLt factorization. 
 *  @returns    An object with the elements of the factorization.
 */
NCT_EXPIMP LDLt ldltResult(const Matrix& ldlt);

/**
 *  @brief      Result of the LDLt factorization.
 *  @details    This function separates the L and D matrices from the result given by any function that
 *              calculates the LDLt factorization.
 *  @param[in]  ldlt  Matrix with the LDLt factorization. 
 *  @returns    An object with the elements of the factorization.
 */
NCT_EXPIMP ComplexLDLt ldltResult(const ComplexMatrix& ldlt);

/**
 *  @brief      Solve linear system by using the LDLt factorization.
 *  @details    This function solves the linear system LDLt x = b where LDLt is the result of the
 *              Cholesky factorization. 
 *  @param[in]  ldlt  The n x n matrix with the LDLt factorization.
 *  @param[in]  b  The n-length vector b.    
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ColumnVector solveSystemLDLt(const Matrix& ldlt,
    const ColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the LDLt factorization.
 *  @details    This function solves the linear system LDLt x = b where LDLt is the result of the
 *              Cholesky factorization. 
 *  @param[in]  ldlt  The n x n matrix with the LDLt factorization.
 *  @param[in]  b  The n-length vector b.    
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP Matrix solveSystemLDLt(const Matrix& ldlt,
    const Matrix& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the LDLt factorization.
 *  @details    This function solves the linear system LDLt x = b where LDLt is the result of the
 *              Cholesky factorization. 
 *  @param[in]  ldlt  The n x n matrix with the LDLt factorization.
 *  @param[in]  b  The n-length vector b.    
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexColumnVector solveSystemLDLt(const ComplexMatrix& ldlt,
    const ComplexColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the LDLt factorization.
 *  @details    This function solves the linear system LDLt X = B where LDLt is the result of the
 *              Cholesky factorization. 
 *  @param[in]  ldlt  The n x n matrix with the LDLt factorization.
 *  @param[in]  b  The n x p matrix B.    
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexMatrix solveSystemLDLt(const ComplexMatrix& ldlt,
    const ComplexMatrix& b, double tol = SMALL_TOL);

////////// LU factorization //////////

/**
 *  @brief      LU factorization.
 *  @details    This function calculates the LU factorization. The result is reported in one array. 
 *              The entries below the diagonal correspond to the L matrix, and the elements on and above 
 *              the diagonal correspond to the U matrix. The diagonal on the L matrix are 1's. 
 *  @param[in]  a  The matrix to factorize.  
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The factorization of the input matrix.
 */
NCT_EXPIMP Matrix luFactorization(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      LU factorization.
 *  @details    This function calculates the LU factorization. The result is reported in one array. The
 *              entries below the diagonal correspond to the L matrix, and the elements on and above the
 *              diagonal correspond to the U matrix. The diagonal on the L matrix are 1's. 
 *  @param[in]  a  The matrix to factorize.  
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The factorization of the input matrix.
 */
NCT_EXPIMP ComplexMatrix luFactorization(const ComplexMatrix& a, double tol = SMALL_TOL);

/**
 *  @brief      LU product.
 *  @details    This function inverts the result of any function that calculates
 *              the LU factorization (i.e., computes the LU product).
 *  @param[in]  lu  Matrix with the LU factorization (Doolittle factorization).
 *  @returns    The LU product.
 */
NCT_EXPIMP Matrix luProduct(const Matrix& lu);

/**
 *  @brief      LU product.
 *  @details    This function inverts the result of any function that calculates
 *              the LU factorization (i.e., computes the LU product).
 *  @param[in]  lu  Matrix with the LU factorization (Doolittle factorization).
 *  @returns    The LU product.
 */
NCT_EXPIMP ComplexMatrix luProduct(const ComplexMatrix& lu);

/**
 *  @brief      Result of the LU factorization.
 *  @details    This function separates the L and U matrices from the result given by any function that
 *              calculates the LU factorization.
 *  @param[in]  lu  Matrix with the LU factorization.
 *  @returns    An object with the elements of the factorization.
 */
NCT_EXPIMP LU luResult(const Matrix& lu);

/**
 *  @brief      Result of the LU factorization.
 *  @details    This function separates the L and U matrices from the result given by any function that
 *              calculates the LU factorization.
 *  @param[in]  lu  Matrix with the LU factorization.
 *  @returns    An object with the elements of the factorization.
 */
NCT_EXPIMP ComplexLU luResult(const ComplexMatrix& lu);

/**
 *  @brief      Solve linear system by using the LU factorization.
 *  @details    This function solves the linear system LU x = b where LU is the result of the LU 
 *              factorization of the system matrix.
 *  @param[in]  lu  The n x n matrix with the LU factorization.
 *  @param[in]  b  The n-length vector b.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ColumnVector solveSystemLU(const Matrix& lu, const ColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the LU factorization.
 *  @details    This function solves the linear system LU X = B where LU is the result of the LU 
 *              factorization of the system matrix.
 *  @param[in]  lu  The n x n matrix with the LU factorization.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP Matrix solveSystemLU(const Matrix& lu, const Matrix& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the LU factorization.
 *  @details    This function solves the linear system LU x = b where LU is the result of the LU 
 *              factorization of the system matrix.
 *  @param[in]  lu  The n x n matrix with the LU factorization.
 *  @param[in]  b  The n-length vector b.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexColumnVector solveSystemLU(const ComplexMatrix& lu,
    const ComplexColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the LU factorization.
 *  @details    This function solves the linear system LU X = B where LU is the result of the LU 
 *              factorization of the system matrix.
 *  @param[in]  lu  The n x n matrix with the LU factorization.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexMatrix solveSystemLU(const ComplexMatrix& lu,
    const ComplexMatrix& b, double tol = SMALL_TOL);

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
 *  @brief      PA = LU factorization.
 *  @details    This function calculates the PA = LU factorization. The result is reported in one matrix
 *              and one vector with the permutations. The entries on the matrix below the diagonal
 *              correspond to the L matrix, and the elements on and above the diagonal correspond to the
 *              U matrix. The diagonal on the L matrix are 1's. 
 *  @param[in]  a  The matrix to factorize.  
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero. 
 *  @returns    The factorization of the input matrix.
 */
NCT_EXPIMP ComplexPLU pluFactorization(const ComplexMatrix& a, double tol = SMALL_TOL);

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

/**
 *  @brief      Solve linear system by using the PA = LU factorization.
 *  @details    This function solves the linear system P^-1LU x = b where LU is the result of the
 *              PA=LU factorization and P is the permutation matrix. 
 *  @param[in]  plu  PA=LA factorization of the system matrix of size n x n.
 *  @param[in]  b  The n-length vector b.    
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexColumnVector solveSystemPLU(const ComplexPLU& plu,
    const ComplexColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the PA = LU factorization.
 *  @details    This function solves the linear system P^-1LU X = B where LU is the result of the
 *              PA=LU factorization and P is the permutation matrix. 
 *  @param[in]  plu  PA=LA factorization of the system matrix of size n x n.
 *  @param[in]  b  The n x p matrix B.    
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexMatrix solveSystemPLU(const ComplexPLU& plu,
    const ComplexMatrix& b, double tol = SMALL_TOL);

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
 *  @brief      PA=LU factorization of banded matrix.
 *  @details    This function calculates the PA=LU factorization for banded matrices that are represented
 *              in compact form (n rows and m columns, m<n). 
 *  @param[in]  a  The matrix to factorize.  
 *  @param[in]  diagColumn  Column in the input matrix that corresponds to the main diagonal.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero. 
 *  @returns    The factorization of the input matrix.
 */
NCT_EXPIMP ComplexPLUBanded pluFactorizationOfBandedMatrix(
    const ComplexMatrix& a, size_t diagColumn, double tol = SMALL_TOL);

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

/**
 *  @brief      Solve linear system by using the PA=LU factorization of a banded matrix.
 *  @details    This function solves the linear system P^-1LU x = b where LU is the result of the
 *              PA=LU banded factorization and P is the permutation matrix. 
 *  @param[in]  plu  PA=LU factorization of the system matrix.
 *  @param[in]  b  The n-length vector b.    
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexColumnVector solveSystemPLUBanded(const ComplexPLUBanded& plu,
    const ComplexColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the PA=LU factorization of a banded matrix.
 *  @details    This function solves the linear system P^-1LU X = B where LU is the result of the
 *              PA=LU banded factorization and P is the permutation matrix. 
 *  @param[in]  plu  PA=LU factorization of the system matrix.
 *  @param[in]  b  The n x p matrix B.    
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexMatrix solveSystemPLUBanded(const ComplexPLUBanded& plu,
    const ComplexMatrix& b, double tol = SMALL_TOL);

////////// QR factorization //////////

/**
 *  @brief      QR factorization.
 *  @details    This function calculates the QR factorization. 
 *  @param[in]  a  The matrix to factorize.  
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The QR factorization of the input matrix.
 */
NCT_EXPIMP QR qrFactorization(const Matrix& a, double tol = SMALL_TOL);

/**
 *  @brief      QR factorization.
 *  @details    This function calculates the QR factorization. 
 *  @param[in]  a  The matrix to factorize.  
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The QR factorization of the input matrix.
 */
NCT_EXPIMP ComplexQR qrFactorization(const ComplexMatrix& a, double tol = SMALL_TOL);

/**
 *  @brief      Update QR factorization.
 *  @details    Given the QR decomposition of a n*m matrix A, this function calcualtes the new
 *              decomposition of the matrix A + s*t, where s and t are vectors of size n and m
 *              respectively.
 *  @param[in, out] qr  QR decomposition of A.
 *  @param[in]  s  Vector s.
 *  @param[in]  t  Vector t.
 */
NCT_EXPIMP void updateQR(QR& qr, const ColumnVector& s, const ColumnVector& t);

/**
 *  @brief      Solve linear system by using the QR factorization.
 *  @details    This function solves the linear system QR x = b where QR is the result of the QR
 *              factorization. 
 *  @param[in]  qr  QR decomposition of the system matrix.
 *  @param[in]  b  The n-length vector b.     
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ColumnVector solveSystemQR(const QR& qr, const ColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the QR factorization.
 *  @details    This function solves the linear system QR X = B where QR is the result of the QR
 *              factorization. 
 *  @param[in]  qr  QR decomposition of the system matrix.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP Matrix solveSystemQR(const QR& qr, const Matrix& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the QR factorization.
 *  @details    This function solves the linear system QR x = b where QR is the result of the QR
 *              factorization. 
 *  @param[in]  qr  QR decomposition of the system matrix.
 *  @param[in]  b  TThe n-length vector b. 
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexColumnVector solveSystemQR(const ComplexQR& qr,
    const ComplexColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the QR factorization.
 *  @details    This function solves the linear system QR X = B where QR is the result of the QR
 *              factorization. 
 *  @param[in]  qr  QR decomposition of the system matrix.
 *  @param[in]  b  The n x p matrix B. 
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexMatrix solveSystemQR(const ComplexQR& qr,
    const ComplexMatrix& b, double tol = SMALL_TOL);

////////// SVD factorizacion //////////

/**
 *  @brief      SVD factorization.
 *  @details    This function calculates the SVD factorization (UWV') of a matrix.
 *  @param[in]  a  The matrix to factorize.  
 *  @param[in]  maxIt  The maximum number of allowed iterations.
 *  @returns    The SVD factorization of the input matrix.
 */
NCT_EXPIMP SVD svdFactorization(const Matrix& a, unsigned int maxIt = 1000);

/**
 *  @brief      Complex SVD factorization.
 *  @details    This function calculates the complex SVD factorization (UWV') of a matrix.
 *  @param[in]  a  The matrix to factorize.  
 *  @param[in]  maxIt  The maximum number of allowed iterations.
 *  @returns    The SVD factorization of the input matrix.
 */
NCT_EXPIMP ComplexSVD svdFactorization(const ComplexMatrix& a, unsigned int maxIt = 1000);

/**
 *  @brief      Solve linear system by using the SVD factorization.
 *  @details    This function solves the linear system UWV' x = b where UWV' is the result of the
 *              SVD factorization.
 *  @param[in]  svd  The SVD decomposition of the system matrix.
 *  @param[in]  b  The n-length vector b.  
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ColumnVector solveSystemSVD(const SVD& svd,
    const ColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the SVD factorization.
 *  @details    This function solves the linear system UWV' X = B where UWV' is the result of the
 *              SVD factorization.
 *  @param[in]  svd  The SVD decomposition of the system matrix.
 *  @param[in]  b  The n x p matrix B.  
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP Matrix solveSystemSVD(const SVD& svd, const Matrix& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve complex linear system by using the SVD factorization.
 *  @details    This function solves the linear linear system UWV' x = b where UWV' is the result
 *              of the SVD factorization.
 *  @param[in]  svd  The SVD decomposition of the system matrix.
 *  @param[in]  b  The n-length vector b.   
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexColumnVector solveSystemSVD(const ComplexSVD& svd,
    const ComplexColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve complex linear system by using the SVD factorization.
 *  @details    This function solves the linear system UWV' X = B where UWV' is the result of the
 *              SVD factorization.
 *  @param[in]  svd  The SVD decomposition of the system matrix.
 *  @param[in]  b  The n x p matrix B.    
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexMatrix solveSystemSVD(const ComplexSVD& svd, 
    const ComplexMatrix& b, double tol = SMALL_TOL);

////////// Jacobi factorizacion //////////

/**
 *  @brief      Jacobi factorization of a symmetric matrices.
 *  @details    This function calculates the jacobi decomposition of a symmetric real matrix
 *              The result is returned in one orthogonal matrix (v) and an array with the singular values.
 *  @param[in]  a  The input matrix.
 *  @returns    The Jacobi factorization of the input matrix.
 */
NCT_EXPIMP Jacobi jacobiFactorization(const Matrix& a);

/**
 *  @brief      Jacobi factorization of a complex hermitian matrix.
 *  @details    This function calculates the jacobi decomposition of a hermitian complex matrix
 *              The result is returned in one orthogonal matrix (v) and an array with the singular values.
 *  @param[in]  a  The input matrix.
 *  @returns    The Jacobi factorization of the input matrix.
 */
NCT_EXPIMP ComplexJacobi jacobiFactorization(const ComplexMatrix& a);

/**
 *  @brief      Solve linear system by using the Jacobi factorization.
 *  @details    This function solves the linear system VWV' x = b where VDV' is the result of the
 *              Jacobi factorization.
 *  @param[in]  jac  The jacobi decomposition of the system matrix.
 *  @param[in]  b  The n-length vector b.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ColumnVector solveSystemJacobi(const Jacobi& jac,
    const ColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve linear system by using the Jacobi factorization.
 *  @details    This function solves the linear system VWV' X = B where VDV' is the result of the
 *              Jacobi factorization.
 *  @param[in]  jac  The jacobi decomposition of the system matrix.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP Matrix solveSystemJacobi(const Jacobi& jac,
    const Matrix& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve complex linear system by using the Jacobi factorization.
 *  @details    This function solves the complex linear system VWV' x = b where VDV' is the result
 *              of the Jacobi factorization.
 *  @param[in]  jac  The jacobi decomposition of the system matrix.
 *  @param[in]  b  The n-length vector b.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexColumnVector solveSystemJacobi(const ComplexJacobi& jac,
    const ComplexColumnVector& b, double tol = SMALL_TOL);

/**
 *  @brief      Solve complex linear system by using the Jacobi factorization.
 *  @details    This function solves the complex linear system VWV' X = B where VDV' is the result
 *              of the Jacobi factorization.
 *  @param[in]  jac  The jacobi decomposition of the system matrix.
 *  @param[in]  b  The n x p matrix B.
 *  @param[in]  tol  The tolerance that is used to determine whether one number is zero.
 *  @returns    The solution of the linear system.
 */
NCT_EXPIMP ComplexMatrix solveSystemJacobi(const ComplexJacobi& jac,
    const ComplexMatrix& b, double tol = SMALL_TOL);

////////// Eigenvalues and eigenvectors //////////            

/**
 *  @brief      Eigenvalues of a symmetric matrix.
 *  @details    This function calculates the eigenvalues of a symmetric real matrix.
 *  @param[in]  a  The input matrix.  
 *  @returns    The eigenvalues of the input matrix.
 */
NCT_EXPIMP ColumnVector symmEigenvalues(const Matrix& a);

/**
 *  @brief      Eigenvalues and eigenvectors of a symmetric matrix.
 *  @details    This function calculates the eigenvalues and eigenvectors of a symmetric 
 *              real matrix. The eigenvectors are returned in one array v, and the eigenvalues
 *              are returned in one array d.
 *  @param[in]  a  The input matrix.  
 *  @returns    The eigenvalues and eigenvectors of the input matrix.
 */
NCT_EXPIMP Eigen symmEigenvectors(const Matrix& a);

/**
 *  @brief      Eigenvalues of a symmetric tridiagonal matrix.
 *  @details    This function calculates the eigenvalues of a symmetric tridiagonal real matrix.
 *              The tridiagonal matrix is represented by two arrays of size n and n-1,
 *              diag contains the diagonal elements and ee contains the subdiagonal
 *              entries. 
 *  @param[in]  diag  Diagonal elements. 
 *  @param[in]  ee  Subdiagonal elements. 
 *  @returns    The eigenvalues of the input matrix.
 */
NCT_EXPIMP ColumnVector symmTridiagEigenvalues(const ColumnVector& diag,
    const ColumnVector& ee);

/**
 *  @brief      m lowest eigenvalues of a symmetric tridiagonal matrix.
 *  @details    This function calculates the m lowest eigenvalues of a symmetric tridiagonal real matrix.
 *              The tridiagonal matrix is represented by two arrays of size n and n-1,
 *              diag contains the diagonal elements and ee contains the subdiagonal
 *              entries.
 *  @param[in]  diag  Diagonal elements.
 *  @param[in]  ee  Subdiagonal elements.
 *  @param[in]  m  The number of eigenvalues to be calculated.
 *  @returns    The first m lowest eigenvalues of the input matrix.
 */
NCT_EXPIMP ColumnVector symmTridiagMinEigenvalues(const ColumnVector& diag,
    const ColumnVector& ee, size_t m);

/**
 *  @brief      m largest eigenvalues of a symmetric tridiagonal matrix.
 *  @details    This function calculates the m largets eigenvalues of a symmetric tridiagonal real matrix.
 *              The tridiagonal matrix is represented by two arrays of size n and n-1,
 *              diag contains the diagonal elements and ee contains the subdiagonal
 *              entries.
 *  @param[in]  diag  Diagonal elements.
 *  @param[in]  ee  Subdiagonal elements.
 *  @param[in]  m  The number of eigenvalues to be calculated.
 *  @returns    The first m largest eigenvalues of the input matrix.
 */
NCT_EXPIMP ColumnVector symmTridiagMaxEigenvalues(const ColumnVector& diag,
    const ColumnVector& ee, size_t m);

/**
 *  @brief      Eigenvalues and eigenvectors of a symmetric tridiagonal matrix.
 *  @details    This function calculates the eigenvalues and eigenvectors of a symmetric 
 *              tridiagonal real matrix. The tridiagonal matrix is represented by two 
 *              arrays of size n and n-1, diag contains the diagonal elements and ee 
 *              contains the subdiagonal entries. 
 *  @param[in]  diag  Diagonal elements. 
 *  @param[in]  ee  Subdiagonal elements. 
 *  @returns    The eigenvalues and eigenvectors of the input matrix.
 */
NCT_EXPIMP Eigen symmTridiagEigenvectors(const ColumnVector& diag,
    const ColumnVector& ee);

/**
 *  @brief      Eigenvalues of a real matrix.
 *  @details    This function calculates the eigenvalues of a real matrix.
 *  @param[in]  a  The input matrix.  
 *  @returns    The eigenvalues of the input matrix.
 */
NCT_EXPIMP ComplexColumnVector eigenvalues(const Matrix& a);

/**
 *  @brief      Eigenvalues of a complex matrix.
 *  @details    This function calculates the eigenvalues of a complex matrix.
 *  @param[in]  a  The input matrix.  
 *  @returns    The eigenvalues of the input matrix.
 */
NCT_EXPIMP ComplexEigen eigenvectors(const ComplexMatrix& a);

/**
 *  @brief      Eigenvalues and eigenvectors of a real matrix.
 *  @details    This function calculates the eigenvalues and eigenvectors of a  
 *              real matrix. The eigenvectors are returned in one array v, and the eigenvalues
 *              are returned in one array d.
 *  @param[in]  a  The input matrix.  
 *  @returns    The eigenvalues and eigenvectors of the input matrix.
 */
NCT_EXPIMP ComplexEigen eigenvectors(const Matrix& a);

/**
 *  @brief      Eigenvalues and eigenvectors of a complex matrix.
 *  @details    This function calculates the eigenvalues and eigenvectors of a  
 *              complex matrix. The eigenvectors are returned in one array v, and the eigenvalues
 *              are returned in one array d.
 *  @param[in]  a  The input matrix.  
 *  @returns    The eigenvalues and eigenvectors of the input matrix.
 */
NCT_EXPIMP ComplexColumnVector eigenvalues(const ComplexMatrix& a);

////////// Algorithms for roots of polynomials //////////

/**
 *  @brief      Find roots of real polynomial function.
 *  @details    This function finds all the roots of a real polynomial function by finding the
 *              eigenvalues of the hessemberg matrix with eigenvalues equal to the roots of the given
 *              function. 
 *  @param[in]  pol  Coefficients of the polynomial. The element pol[i] correponds to the therm a[i]x^i.
 *  @returns    The array of roots.
 */
NCT_EXPIMP ComplexVector solvePolynomialRoots(const RealVector& pol);

/**
 *  @brief      Find roots of complex polynomial function.
 *  @details    This function finds all the roots of a complex polynomial function by finding the
 *              eigenvalues of the hessemberg matrix with eigenvalues equal to the roots of the given
 *              function. 
 *  @param[in]  pol  Coefficients of the polynomial. The element pol[i] correponds to the therm a[i]x^i.
 *  @returns    The array of roots.
 */
NCT_EXPIMP ComplexVector solvePolynomialRoots(const ComplexVector& pol);

/**
 *  @brief      Real polynomial from roots.
 *  @details    This function builds a polynomial function from its roots. 
 *  @param[in]  roots  The roots of the polynomial.
 *  @returns    The array that represents the polynomial function.
 */
NCT_EXPIMP RealVector realPoly(const RealVector& roots);

/**
 *  @brief      Real polynomial from roots.
 *  @details    This function builds a polynomial function from its roots. 
 *  @param[in]  roots  The roots of the polynomial.
 *  @returns    The array that represents the polynomial function.
 */
NCT_EXPIMP RealVector realPoly(const ComplexVector& roots);

/**
 *  @brief      Real polynomial from characteristic function.
 *  @details    This function builds a polynomial function from the coefficients of the
 *              characteristic function represented by the input matrix. 
 *  @param[in]  x  The characteristic function.
 *  @returns    The array that represents the polynomial function.
 */
NCT_EXPIMP RealVector realPoly(const Matrix& x);

/**
 *  @brief      Polynomial from roots.
 *  @details    This function builds a polynomial function from its roots. 
 *  @param[in]  roots  The roots of the polynomial.
 *  @returns    The array that represents the polynomial function.
 */
NCT_EXPIMP ComplexVector poly(const ComplexVector& roots);

/**
 *  @brief      Real polynomial from characteristic function.
 *  @details    This function builds a polynomial function from the coefficients of the
 *              characteristic function represented by the input matrix. 
 *  @param[in]  x  The characteristic function.
 *  @returns    The array that represents the polynomial function.
 */
NCT_EXPIMP ComplexVector poly(const ComplexMatrix& x);

}}}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
