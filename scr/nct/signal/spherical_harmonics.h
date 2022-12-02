//=================================================================================================================
/**
 *  @file       spherical_harmonics.h
 *  @brief      nct::signal::spherical_harmonics namespace.
 *  @details    Declaration of the nct::signal::spherical_harmonics namespace.
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

#ifndef NCT_SPHERICAL_HARMONICS_H_INCLUDE
#define NCT_SPHERICAL_HARMONICS_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/nct_constants.h>
#include <nct/Array.h>
#include <nct/Array2D.h>

//=================================================================================================================
namespace nct {
namespace signal {

/**
 *  @brief      Spherical harmonic transform.
 *  @details    This namespace contains methods to compute the harmonic transform of spherical
 *              data.
 */
namespace spherical_harmonics
{
////////// Structures //////////

/**
 *  @brief      Spherical harmonic order.
 *  @details    This structure describes the order of one spherical harmonic.
 */
struct NCT_EXPIMP SphericalHarmonic {

    int l {0};  /**< Parameter l of the harmonic (l>=0). */

    int m {0};  /**< Parameter h of the harmonic (-l<=m<=l). */
};

/**
 *  @brief      Spherical harmonic matrix system.
 *  @details    This structure contains the matrix system calculated to obtaine the
 *              spherical harmonic transform.
 */
struct NCT_EXPIMP SphericalMatrix {

    Matrix mat;     /**< The matrix system needed to obtain the spherical transform. */

    Array<SphericalHarmonic> harmonics;     /**< Array with the order of each calculated harmonic. */
};

/**
 *  @brief      Spherical harmonic decomposition.
 *  @details    This structure contains the results obtained by applying the spherical harmonic transform.
 */
struct NCT_EXPIMP SphericalTransform {

    ComplexVector c;                         /**< The coefficients of the decomposition. */

    Array<SphericalHarmonic> harmonics;      /**< Array with the order of each calculated harmonic. */
};

////////////// Function /////////////

/**
 *  @brief      Spherical Harmonic matrix system.
 *  @details    This function computes the matrix system that is needed to perform the spherical
 *              transform. Each row of the matrix corresponds to one point (defined by one pair <theta,
 *              phi>) and each column corresponds to one harmonic. The order of each harmonic is returned
 *              in one array.
 *  @param[in]  maxl  Maximum l order of the harmonics. The function calculates harmonics in the range
 *              0<=l and -l<=m<=l.
 *  @param[in]  theta  Array of theta values where the harmonics will be evaluated.
 *  @param[in]  phi  Array of phi values where the harmonics will be evaluated.
 *  @returns    An struct with the spherical harmonic matrix system. 
 */
NCT_EXPIMP SphericalMatrix sphericalMatrix(unsigned int maxl, const RealVector& theta,
    const RealVector& phi);

/**
 *  @brief      Orthogonal spherical Harmonic matrix system.
 *  @details    This function computes the matrix system that is needed to perform the spherical
 *              transform. Each row of the matrix corresponds to one point (defined by one pair <theta,
 *              phi>) and each column corresponds to one harmonic. The order of each harmonic is returned
 *              in one array. The matrix is built in such a way to guarantee the columns are orthogonal.
 *  @param[in]  maxl  Maximum l order of the harmonics. The function calculates harmonics in the range
 *              0<=l and -l<=m<=l.
 *  @param[in]  theta  Array of theta values where the harmonics will be evaluated.
 *  @param[in]  phi  Array of phi values where the harmonics will be evaluated.
 *  @param[in]  tol  Tolerance to consider a vector is not orthogonal in the Gram-Schmidt
 *              orthogonalization procedure.
 *  @returns    An struct with the spherical harmonic matrix system. 
 */
NCT_EXPIMP SphericalMatrix orthogonalHarmonicMatrix(unsigned int maxl, const RealVector& theta,
    const RealVector& phi, double tol = MEDIUM_TOL);

/**
 *  @brief      Decomposition in spherical harmonic functions.
 *  @details    This function computes decomposition in spherical harmonics of one sub-sampled function.
 *  @param[in]  maxl  Maximum l order of the harmonics. The function calculates harmonics in the range
 *              0<=l and -l<=m<=l.
 *  @param[in]  f  Array with the evaluations of the function to be transformed.
 *  @param[in]  theta  Array of theta values where the function f was evalauted.
 *  @param[in]  phi  Array of phi values where the function f was evalauted.
 *  @param[in]  tol  Tolerance to consider a number too small.
 */
NCT_EXPIMP SphericalTransform sphericalTransform(unsigned int maxl, const RealVector& f,
    const RealVector& theta, const RealVector& phi, double tol = VERY_SMALL_TOL);

/**
 *  @brief      Decomposition in spherical harmonic functions.
 *  @details    This function computes decomposition in spherical harmonics of one sub-sampled function.
 *              The method explores only orthogonal spherical functions.
 *  @param[in]  maxl  Maximum l order of the harmonics. The function calculates harmonics in the range
 *              0<=l and -l<=m<=l.
 *  @param[in]  f  Array with the evaluations of the function to be transformed.
 *  @param[in]  theta  Array of theta values where the function f was evalauted.
 *  @param[in]  phi  Array of phi values where the function f was evalauted.
 *  @param[in]  tol  Tolerance to consider a number too small.
 */
NCT_EXPIMP SphericalTransform orthogonalSphericalTransform(unsigned int maxl, const RealVector& f,
    const RealVector& theta, const RealVector& phi, double tol = VERY_SMALL_TOL);

}}}

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
