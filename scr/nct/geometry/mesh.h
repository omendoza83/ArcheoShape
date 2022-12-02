//=================================================================================================================
/**
 *  @file       mesh.H
 *  @brief      nct::geometry::mesh namespace.
 *  @details    Declaration of the nct::geometry::mesh namespace. 
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

#ifndef NCT_mesh_H_INCLUDE
#define NCT_mesh_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/Array.h>
#include <nct/Array2D.h>
#include <nct/Vector3D.h>
#include <nct/SparseArray3D.h>
#include <nct/random/RandomNumber.h>
#include <nct/geometry/Triangle3D.h>

//=================================================================================================================
namespace nct {
namespace geometry {
/**
 *  @brief      Mesh namespace.
 *  @details    This namespace contains clases and functions for representing and analyzing meshes.
 */
namespace mesh {

////////// Enumerations //////////

/**
 *  @brief      Shape distributions.
 *  @details    Different shape distributions that characterize triangular meshes.
 */
enum class ShapeDistribution : unsigned char {

    TwoVectorsAngle,    /**< Angle between two vectors. */

    CentroidDistance,   /**< Distance between the centroid and one random point. */

    TwoPointDistance,   /**< Distance between two random points. */

    ThreePointArea,     /**< Square root of the area of the triangle defined by three points. */

    FourPointVolume,    /**< Cube root of the volumen of the tetrahedron defined by four points. */
};

/**
 *  @brief      Distance functions.
 *  @details    Distance functions to compare shape distributions.
 */
enum class DistanceFunction : unsigned char {

    EuclideanDistance,  /**< Euclidian distance. */

    CityBlockDistance,  /**< Sum of absolute differences. */

    ChebychevDistance,  /**< Coordinade with maximun absolute difference. */

    MinDistance,        /**< Coordinade with minimum absolute difference. */

    BhattacharyyaDistance,  /**< Bhattacharyya difference between distributions. */
};

////////// Auxiliar functions //////////

/**
 *  @brief      Find closest vertex.
 *  @details    This function searches for the first closest vertex to v in set of vertices.
 *  @param[in]  v   The vertex to be compared.
 *  @param[in]  vA  Array of vertices.  
 *  @returns    The index of the closest vertex to v.
 */
NCT_EXPIMP size_t findClosestVertex(const Point3D& v, const Array<Point3D>& vA);

/**
 *  @brief      Find closest vertex.
 *  @details    This function searches for the first closest vertex to one vertex in v1 in the set of
 *              vertices v2.
 *  @param[in]  v1  Array of vertices
 *  @param[in]  v2  Array of vertices.  
 *  @returns    An array with each of the closest vertex.
 */
NCT_EXPIMP Array<size_t> findClosestVertex(const Array<Point3D>& v1, const Array<Point3D>& v2);

/**
 *  @brief      Grid vertices.
 *  @details    This function calculates the vertices that are distributed in a grid.
 *  @param[in]  nx  Number of points in x.
 *  @param[in]  ny  Number of points in y.
 *  @returns    An array with the points of the grid.
 */
NCT_EXPIMP Array<Point3D> gridVertices(unsigned int nx = 16, unsigned int ny = 16);

/**
 *  @brief      Grid mesh.
 *  @details    This function calculates a mesh that represents a grid.
 *  @param[in]  nx  Number of points in x.
 *  @param[in]  ny  Number of points in y.
 *  @returns    A tuple with the following elements: \n
 *              * The vertices of the mesh. \n
 *              * The indices of the vertices of triangles.
 */
NCT_EXPIMP std::tuple<Array<Point3D>, Array<Vector3D<unsigned int>>> gridMesh(
    unsigned int nx = 16, unsigned int ny = 16);

/**
 *  @brief      Sphere vertices.
 *  @details    This function calculates the vertices that are distributed in the sphere surface.
 *  @param[in]  nTheta  Number of divisions of theta.
 *  @param[in]  nPhi  Number of circles of phi.
 *  @returns    An array with the calculated vertices.
 */
NCT_EXPIMP Array<Point3D> sphereVertices(
    unsigned int nTheta = 16, unsigned int nPhi = 8);

/**
 *  @brief      Sphere mesh.
 *  @details    This function calculates a mesh that represents a sphere of unitary radius.
 *  @param[in]  nTheta  Number of divisions of theta.
 *  @param[in]  nPhi  Number of circles of phi.
 *  @returns    A tuple with the following elements: \n
 *              * The vertices of the mesh. \n
 *              * The indices of the vertices of triangles.
 */
NCT_EXPIMP std::tuple<Array<Point3D>, Array<Vector3D<unsigned int>>> sphereMesh(
    unsigned int nTheta = 16, unsigned int nPhi = 8);

/**
 *  @brief      Calculate the face normals.
 *  @details    This function calculates the face normals to each face in a triangular mesh.
 *  @param[in]  vertices         The vertices of the triangular mesh.
 *  @param[in]  triangles  The indices of the vertices of each triangle in the triangular mesh.
 *  @returns    The calculated face normals.
 */
NCT_EXPIMP Array<Vector3D<double>> calculateFaceNormals(
    const Array<Point3D>& vertices,
    const Array<Vector3D<unsigned int>>& triangles);

/**
 *  @brief      Calculate the vertex normals.
 *  @details    This function calculates the normals to each vertex in a triangular mesh.
 *  @param[in]  vertices         The vertices of the triangular mesh.
 *  @param[in]  triangles  The indices of the vertices of each triangle in the triangular mesh.
 *  @returns    The calculated vertex normals.
 */
NCT_EXPIMP Array<Vector3D<double>> calculateVertexNormals(
    const Array<Point3D>& vertices,
    const Array<Vector3D<unsigned int>>& triangles);

/**
 *  @brief      Center and scale vertices.
 *  @details    This function centers and scales an array of vertices. 
 *  @param[in]  vertices  The vertices to center and scale.
 *  @returns    The scaled vertices.
 */
NCT_EXPIMP Array<Point3D> centerAndScaleVertices(
    const Array<Point3D>& vertices);

/**
 *  @brief      Center and scale vertices.
 *  @details    This function centers and scales an array of vertices. 
 *  @param[in]  vertices  The vertices to center and scale.
 *  @param[in]  triangles  The triangles of the mesh.
 *  @returns    The scaled vertices.
 */
NCT_EXPIMP Array<Point3D> centerAndScaleVertices(
    const Array<Point3D>& vertices,
    const Array<Vector3D<unsigned int>>& triangles);

/**
 *  @brief      Calculate the areas of the triangular mesh.
 *  @details    This function calculates the area of each triangle of the indicated mesh.
 *  @param[in]  vertices  Array with the vertices of the triangular mesh.
 *  @param[in]  triangles  Array that defines the triangles of the mesh.
 *  @returns    The calculated areas of each triangle.
 */
NCT_EXPIMP RealVector calculateAreas(
    const Array<Point3D>& vertices,
    const Array<Vector3D<unsigned int>>& triangles);

/**
 *  @brief      Calculate random points.
 *  @details    This function calculates random points of the specified mesh.
 *  @param[in]  vertices  Array with the vertices of the triangular mesh.
 *  @param[in]  triangles  Array that defines the triangles of the mesh.
 *  @param[in]  nSamples  Number of random points to calcualte.
 *  @param[in, out] rnd  Pseudo-random number generator.
 *  @returns    An array with the sampled points.
 */
NCT_EXPIMP Array<Point3D> samplePoints(
    const Array<Point3D>& vertices,
    const Array<Vector3D<unsigned int>>& triangles,
    unsigned int nSamples, random::RandomNumber& rnd);

/**
 *  @brief      Calculate the centroid of a set of points.
 *  @details    This function calculates the centroid of set of vertices. 
 *  @param[in]  vertices  Array with the vertices of the triangular mesh.
 *  @returns    The centroid of the figure.
 */
NCT_EXPIMP Point3D calculateCentroid(
    const Array<Point3D>& vertices);

/**
 *  @brief      Calculate the centroid of a mesh.
 *  @details    This function calculates the centroid of a mesh by averaging the centroids of each
 *              triangle. Each baricenter is weighted by the corresponding triangle area.
 *  @param[in]  vertices  Array with the vertices of the triangular mesh.
 *  @param[in]  triangles  Array that defines the triangles of the mesh.
 *  @returns    The centroid of the figure.
 */
NCT_EXPIMP Point3D calculateCentroid(
    const Array<Point3D>& vertices,
    const Array<Vector3D<unsigned int>>& triangles);

/**
 *  @brief      Calculate the centroid of a mesh.
 *  @details    This function calculates the centroid of a mesh by averaging random points.
 *  @param[in]  vertices  Array with the vertices of the triangular mesh.
 *  @param[in]  triangles  Array that defines the triangles of the mesh.
 *  @param[in]  nSamples  Number of random points to use in the centroid calculation. 
 *  @param[in, out] rnd  Pseudo-random number generator.
 *  @returns    The centroid of the figure.
 */
NCT_EXPIMP Point3D calculateCentroid(const Array<Point3D>& vertices,
    const Array<Vector3D<unsigned int>>& triangles, unsigned int nSamples,
    random::RandomNumber& rnd);

/**
 *  @brief      Calculate a shape distribution.
 *  @details    This function calculates a shape distribution of the triangular mesh specified in
 *              the input arguments.
 *  @param[in]  vertices  Array with the vertices of the triangular mesh.
 *  @param[in]  triangles  Array that defines the triangles of the mesh.
 *  @param[in, out] rnd  Pseudo-random number generator.
 *  @param[in]  dist  Type of distribution to be calculated.
 *  @param[in]  nSamples  Number of samples to use in the calculation of the shape distribution.
 *  @param[in]  nBins  Number of bins of the histogram that represents the shape distribution.
 *  @returns    A tuple with the following elements: \n * The values of the histogram for each bin. * The
 *              histogram bins.
 */
NCT_EXPIMP std::tuple<RealVector, RealVector> calculateShapeDistribution(
    const Array<Point3D>& vertices, const Array<Vector3D<unsigned int>>& triangles, 
    random::RandomNumber& rnd, ShapeDistribution dist, unsigned int nSamples = 65535,
    unsigned int nBins = 256);

/**
 *  @brief      Calculate the distance between two features.
 *  @details    This function calculates the distance between two feautres.
 *  @param[in]  h1  Feature 1.
 *  @param[in]  h2  Feature 2.
 *  @param[in]  distFunction  Distance function to use.
 *  @returns    The distance between the features.
 */
NCT_EXPIMP double compareFeatures(const RealVector& h1,
    const RealVector& h2, DistanceFunction distFunction);

/**
 *  @brief      Calculate the distance between shape distributions.
 *  @details    This function calculates the distance between two shape distributions.
 *  @param[in]  h1  Normalized histogram of shape distribution 1.
 *  @param[in]  h2  Normalized histogram of shape distribution 2.
 *  @param[in]  distFunction  Distance function to use.
 *  @param[in]  useCumulativeDistribution  True to use the cumulative distribution.
 *  @returns    The distance between the shape distributions.
 */
NCT_EXPIMP double calculateShapeDistributionDistance(const RealVector& h1,
    const RealVector& h2, DistanceFunction distFunction,
    bool useCumulativeDistribution);

/**
 *  @brief      Calculate the distance between shape distributions.
 *  @details    This function calculates the distance between two shape distributions. the
 *              distribution are scaled in order to find the optimal distance.
 *  @param[in]  h1  Normalized histogram of shape distribution 1.
 *  @param[in]  b1  Centers of the bins in shape distribution 1.
 *  @param[in]  h2  Normalized histogram of shape distribution 2.
 *  @param[in]  b2  Centers of the bins in shape distribution 2.
 *  @param[in]  distFunction  Distance function to use.
 *  @param[in]  useCumulativeDistribution  True to use the cumulative distribution.
 *  @param[in]  nPoints  Number of points to use in the evaluation of each distribution.
 *  @param[in]  nScales  Number of scales to test.
 *  @param[in]  minDbScale  Minimum scale (in DB) to test.
 *  @param[in]  maxDbScale  Maximum scale (in DB) to test.
 *  @returns    The distance between the shape distributions.
 */
NCT_EXPIMP double calculateShapeDistributionDistance(const RealVector& h1,
    const RealVector& b1, const RealVector& h2,
    const RealVector& b2, DistanceFunction distFunction,
    bool useCumulativeDistribution, unsigned int nPoints = 256,
    unsigned int nScales = 256, double minDbScale = -10.0, double maxDbScale = 10.0);

/**
 *  @brief      Find rotation indices.
 *  @details    This function finds the indices that are needed to match rotations. This indices
 *              are used to compare reflexive symmetry descriptors.
 *  @param[in]  dirVectors  Vectors that are rotated.
 *  @param[in]  nTestAngles  Number of test angles for each axis.
 *  @returns    An array with the indices that are used to match rotations. 
 *              Each element correspond to the indices of one rotation.
 */
NCT_EXPIMP Array<Array<size_t>> findRotationIndices(const Array<Vector3D<double>>& dirVectors,
    unsigned int nTestAngles = 8);

/**
 *  @brief      Compare reflexive symmetry descriptors.
 *  @details    This function calculates the distance between two shape reflexive symmetry
 *              descriptors. The minimum distance among rotation is returned by this function.
 *  @param[in]  rsd1  Symmetry descriptor 1.
 *  @param[in]  rsd2  Symmetry descriptor 2.
 *  @param[in]  dirVectors  Vectors that indicate the direction of each element of the descriptors.
 *  @param[in]  distFunction  Distance function to use in this function.
 *  @param[in]  nTestAngles  Number of test angles for each axis.
 *  @returns    The distance between the descriptors.
 */
NCT_EXPIMP double compareSymmetryDescriptors(const Matrix& rsd1,
    const Matrix& rsd2, const Array<Vector3D<double>>& dirVectors,
    DistanceFunction distFunction, unsigned int nTestAngles = 8);

/**
 *  @brief      Compare reflexive symmetry descriptors.
 *  @details    This function calculates the distance between two shape reflexive symmetry
 *              descriptors. The minimum distance among rotation is returned by this function.
 *  @param[in]  rsd1  Symmetry descriptor 1.
 *  @param[in]  rsd2  Symmetry descriptor 2.
 *  @param[in]  rotIndices  Indices that are used to match rotations. 
 *  @param[in]  distFunction  Distance function to use in this function.
 *  @returns    The distance between the descriptors.
 */
NCT_EXPIMP double compareSymmetryDescriptors(const Matrix& rsd1,
    const Matrix& rsd2, Array<Array<size_t>>& rotIndices,
    DistanceFunction distFunction);

/**
 *  @brief      Coordinates of triangles.
 *  @details    This function returns in one object the coordinates of a set of triangles.
 *  @param[in]  vertices  Array with the vertices of the triangular mesh.
 *  @param[in]  triangles  Array that defines the triangles of the mesh.
 *  @returns    An array with the coordinates of the triangles.
 */
NCT_EXPIMP Array<geometry::Triangle3D> triangleCoord(const Array<Point3D>& vertices,
    const Array<Vector3D<unsigned int>>& triangles);

/**
 *  @brief      Line coordinades.
 *  @details    This function returns in one object the coordinates of the lines of a set of
 *              triangles.
 *  @param[in]  vertices  Array with the vertices of the triangular mesh.
 *  @param[in]  triangles  Array that defines the triangles of the mesh.
 *  @returns    An array with the coordinates of the lines.
 */
NCT_EXPIMP Array<geometry::Line3D> lineCoord(const Array<Point3D>& vertices,
    const Array<Vector3D<unsigned int>>& triangles);

}}}

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
