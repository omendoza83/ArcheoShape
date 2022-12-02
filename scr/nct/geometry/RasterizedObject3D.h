//=================================================================================================================
/**
 *  @file       RasterizedObject3D.h
 *  @brief      nct::geometry::RasterizedObject3D class.
 *  @details    Declaration of the nct::geometry::RasterizedObject3D class. 
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

#ifndef NCT_RASTERIZED_OBJECT_H_INCLUDE
#define NCT_RASTERIZED_OBJECT_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/Array.h>
#include <nct/SparseArray3D.h>
#include <nct/signal/spherical_harmonics.h>
#include <nct/geometry/rasterization.h>

//=================================================================================================================
namespace nct {
namespace geometry {

/**
 *  @brief      Rasterized object.
 *  @details    This class is used to represent rasterized 3D objects. 
 */
class NCT_EXPIMP RasterizedObject3D final {    
public:

    ////////// Structures //////////

    /**
     *  @brief      Model surface.
     *  @details    This structure defines the elements of a surface evaluation.
     */
    struct Surface final {

        double r {0};           /**< The radix used to evaluate the model. */

        Array<bool> f;          /**< The result of the model evaluation. */

        Array<Point3D> points;  /**< The centers used to evaluate the model. */
    };

    /**
     *  @brief      Model surfaces.
     *  @details    This structure defines the elements of multiple surface evaluations.
     */
    struct Surfaces final {

        Array2D<bool> f;        /**< The results of the model evaluation. */

        RealVector r;           /**< The array with the evaluated radices. */

        RealVector theta;       /**< The array with the evaluated theta angles. */

        RealVector phi;         /**< The array with the evaluated phi angles. */
    };

    /**
     *  @brief      Harmonic decomposition.
     *  @details    This structure defines the elements of an harmonic decomposition.
     */
    struct HarmonicDecomposition final {

        ComplexMatrix c;    /**< The array with coefficients of the decomposition. */

        /** The array with the characteristics of the computer harmonics. */
        Array<signal::spherical_harmonics::SphericalHarmonic> h;    
    };

    /**
     *  @brief      Harmonic matrices.
     *  @details    This structure defines the matrices used to calculate the harmonic decomposition.
     */
    struct HarmonicMatrices final {

        unsigned int maxl {0};  /**< The maximum degree of the harmonics. */

        Matrix BtBI;            /**< The inverse of BtB. */

        Matrix Bt;              /**< The transponse of B, where B defines the linear system Bx=f. */

        /** Array where the degree of the harmonics are specified. */
        Array<signal::spherical_harmonics::SphericalHarmonic> hB;   

        RealVector theta;       /**< Theta angles where the funcions are evaluated. */

        RealVector phi;         /**< Phi angles where the funcions are evaluated. */
    };

    /**
     *  @brief      Symmetry descriptor.
     *  @details    This structure defines the symmetry reflective descriptor of an object.
     */
    struct SymmetryDescriptor final {

        Matrix sd;              /**< The coeficients of the symmetry descriptor. */
        
        Matrix rsd;             /**< The coeficients of the reflexive symmetry descriptor. */
        
        /** The normal vectors to the planes obtained in the calculation of the descriptor. */
        Array<Point3D> norms;   
    };

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the specified argument.
     *  @param[in]  div  Number of divisions of each variable in the mesh.
     */
    explicit RasterizedObject3D(unsigned int div = 64);

    /**
     *  @brief      Class constructor.
     *  @details    This constructor creates a new instance of this class with the rasterized set of
     *              points that are specified in the arguments.
     *  @param[in]  points  Set of points to rasterize.
     *  @param[in]  min  Lower limit of each variable to rasterize.
     *  @param[in]  max  Upper limit of each variable to rasterize.
     *  @param[in]  div  Number of divisions of each variable in the mesh.
     */
    RasterizedObject3D(const Array<Point3D>& points,
        double min, double max, unsigned int div = 64);

    /**
     *  @brief      Class constructor.
     *  @details    This constructor creates a new instance of this class with the rasterized set of
     *              lines that are specified in the arguments.
     *  @param[in]  lines  Set of lines to rasterize.
     *  @param[in]  min  Lower limit of each variable to rasterize.
     *  @param[in]  max  Upper limit of each variable to rasterize.
     *  @param[in]  div  Number of divisions of each variable in the mesh.
     *  @param[in]  connectivity  N-Connectivity.
     */
    RasterizedObject3D(const Array<geometry::Line3D>& lines, double min, double max,
        unsigned int div = 64,
        rasterization::NConnectivity3D connectivity =
        rasterization::NConnectivity3D::TwentySixConnected);

    /**
     *  @brief      Class constructor.
     *  @details    This constructor creates a new instance of this class with the rasterized set of
     *              triangles that are specified in the arguments.
     *  @param[in]  triangles  Set of triangles to rasterize.
     *  @param[in]  min  Lower limit of each variable to rasterize.
     *  @param[in]  max  Upper limit of each variable to rasterize.
     *  @param[in]  div  Number of divisions of each variable in the mesh.
     *  @param[in]  connectivity  N-Connectivity.
     */
    RasterizedObject3D(const Array<geometry::Triangle3D>& triangles,
        double min, double max, unsigned int div = 64,
        rasterization::NConnectivity3D connectivity =
        rasterization::NConnectivity3D::TwentySixConnected);
    
    ////////// Operators //////////
    
    /**
     *  @brief      Operator ().
     *  @details    This operator returns the value at the specified point.
     *  @param[in]  x  x coordinate of the selected element.
     *  @param[in]  y  y coordinate of the selected element.
     *  @param[in]  z  y coordinate of the selected element.
     *  @returns    A reference to the object.
     */
    bool operator()(double x, double y, double z) const;

    /**
     *  @brief      Operator ().
     *  @details    This operator returns the value of the specified element.
     *  @param[in]  i  First index of the selected element.
     *  @param[in]  j  Second index of the selected element.
     *  @param[in]  k  Third index of the selected element.
     *  @returns    A reference to the object.
     */
    bool operator()(unsigned int i, unsigned int j, unsigned int k) const;

    ////////// Member functions //////////    

    /**
     *  @brief      Number of divisions.
     *  @details    This function gets the number of divisions of each variable in the mesh.
     *  @returns    The total number of divisions of each variable.
     */
    unsigned int numberOfDivisions() const noexcept;

    /**
     *  @brief      Array of voxels.
     *  @details    This function returns the sparse array of voxels.
     *  @return     The array of voxels.
     */
    const SparseArray3D<bool>& voxelArray() const noexcept;

    /**
     *  @brief      Center of a voxel.
     *  @details    This function gets the coordinates of the center of the specified voxel.
     *  @param[in]  i  First index of the selected voxel.
     *  @param[in]  j  Second index of the selected voxel.
     *  @param[in]  k  Third index of the selected voxel.
     *  @returns    The coordinates of the indicated voxel.
     */
    Point3D voxelCenter(unsigned int i, unsigned int j, unsigned int k) const;

    /**
     *  @brief      Mean distance.
     *  @details    This function calculates the mean distance to the center of the object.
     *  @returns    The mean distance.
     */
    double meanDistance() const;

    /**
     *  @brief      Evaluate model at multiple points.
     *  @details    This function evaluates the model at multiple points expressed in cartesian
     *              coordinates.
     *  @param[in]  points  The points to be evaluated.
     *  @returns    An array with the evaluation of the model at the specified points.
     */
    Array<bool> evalXYZ(const Array<Point3D>& points) const;

    /**
     *  @brief      Evaluate model at multiple points.
     *  @details    This function evaluates the model at multiple points expressed in spherical
     *              coordinates.
     *  @param[in]  points  The points to be evaluated.
     *  @returns    An array with the evaluation of the model at the specified points.
     */
    Array<bool> evalSph(const Array<Point3D>& points) const;

    /**
     *  @brief      Evaluate model at one radius.
     *  @details    This function evaluates the model for the specified radius. The result is
     *              returned in two arrays, one expresses the points that corresponds to the evaluated
     *              surface, and the other represents the model evaluations.
     *  @param[in]  r  The radius to be evaluated.
     *  @returns    The result of the model evaluation.
     */
    Surface surface(double r) const;

    /**
     *  @brief      Evaluate model at multiple radii.
     *  @details    This function evaluates the model at multiple radii. The points where the
     *              model is evaluated corresponds to the combination of the three arrays r, theta and
     *              phi.
     *  @returns    The result of the model evaluation.
     */
    Surfaces surfaces() const;

    /**
     *  @brief      Rasterized surface at one radius.
     *  @details    This function evaluates the model for the specified radius. The result is
     *              returned in a new rasterized model.
     *  @param[in]  r  The radius to be evaluated.
     *  @returns    An object with the selected surface.
     */
    RasterizedObject3D rasterizedSurface(double r) const;

    /**
     *  @brief      Harmonic decomposition.
     *  @details    This function calculates the harmonic decomposition of the rasterized model.
     *  @param[in]  tol  Tolerance used in the matrix invertion.
     *  @returns    The result of the model decomposition.
     */
    HarmonicDecomposition harmonicDecomposition(double tol = VERY_SMALL_TOL) const;

    /**
     *  @brief      Harmonic decomposition.
     *  @details    This function calculates the harmonic decomposition of the rasterized model.
     *  @param[in]  hm  The matrices needed to calculate the harmonic decomposition.
     *  @returns    The result of the model decomposition.
     */
    HarmonicDecomposition harmonicDecomposition(const HarmonicMatrices& hm) const;

    /**
     *  @brief      Harmonic descriptor.
     *  @brief      Calculates the harmonic descriptor of the model.
     *  @param[in]  tol  Tolerance to calculate BtB^-1.
     *  @returns    The descriptor of the model. Each row represents one radius of the model
     *              and each column represents the degree of an harmonic.
     */
    Matrix harmonicDescriptor(double tol = VERY_SMALL_TOL) const;

    /**
     *  @brief      Harmonic descriptor.
     *  @brief      Calculates the harmonic descriptor of the model.
     *  @param[in]  hm  The matrices needed to calculate the harmonic decomposition.
     *  @returns    The descriptor of the model. Each row represents one radius of the model
     *              and each column represents the degree of an harmonic.
     */
    Matrix harmonicDescriptor(const HarmonicMatrices& hm) const;

    /**
     *  @brief      Exponentially decaying distance transform.
     *  @details    This function calculates the exponentially decaying distance transform of the
     *              voxelized object.    
     *  @returns    An array that represents the transformed model.
     */
    Array3D<double> eddt() const;

    /**
     *  @brief      Symmetry descriptor.
     *  @details    This function calculates the symmetry reflective descriptor of the object.
     *  @returns    The symmetry descriptor of the object.
     */
    SymmetryDescriptor symmetryDescriptor() const;

    /**
     *  @brief      Harmonic matrix system.
     *  @details    This function returns the matrices that defines the linear system that is used to 
     *              calculate the harmonic transform for a model of div*div*div voxels.
     *  @param[in]  div  The number of divisions of the grid.
     *  @param[in]  tol  Tolerance that is used to calculate the inverse of BtB.
     *  @returns    An object with the decomposition matrices.
     */
    static HarmonicMatrices harmonicMatrices(unsigned int div, double tol = VERY_SMALL_TOL);

private:

    ////////// Data members //////////        

    SparseArray3D<bool> voxels_;    /**< Array of voxels_. */

};

}}

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
