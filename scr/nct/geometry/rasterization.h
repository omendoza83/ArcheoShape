//=================================================================================================================
/**
 *  @file       rasterization.h
 *  @brief      nct::geometry::rasterization namespace.
 *  @details    Declaration of the nct::geometry::rasterization namespace.
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

#ifndef NCT_RASTERIZATION_H_INCLUDE
#define NCT_RASTERIZATION_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/Array.h>
#include <nct/SparseArray2D.h>
#include <nct/SparseArray3D.h>
#include <nct/geometry/Line.h>
#include <nct/geometry/Line3D.h>
#include <nct/geometry/Triangle3D.h>
#include <nct/Vector2D.h>
#include <nct/Vector3D.h>

//=================================================================================================================
namespace nct {
namespace geometry {

/**
 *  @brief      Rasterization namespace.
 *  @details    This namespace contains functions that rasterize points, lines and
 *              triangles.
 */
namespace rasterization
{
/**
 *  @brief      N-Connectivity for 2D spaces.
 *  @details    Types of connectivity in 2D grids.
 */
enum class NConnectivity2D : unsigned char {

    FourConnected,  /**< 4-Connected. Pixels are neighbors of all the elements that touch
                         their edges.*/
    EightConnected, /**< 8-Connected. Pixels are neighbors of all the elements that touch
                         their edges or corners.*/
};

/**
 *  @brief      N-Connectivity for 3D spaces.
 *  @details    Types of connectivity in 3D grids.
 */
enum class NConnectivity3D : unsigned char {

    SixConnected,       /**< 6-Connected. Voxels are neighbors of all the elements that touch
                             their faces.*/
    EighteenConnected,  /**< 18-Connected. Voxels are neighbors of all the elements that touch
                             their faces or edges.*/
    TwentySixConnected, /**< 26-Connected. Voxels are neighbors of all the elements that touch
                             their faces, edges or corners.*/
};

/**
 *  @brief      Rasterize points.
 *  @details    This function rasterizes points in a grid.
 *  @param[in]  min  Minimum value of each axis.
 *  @param[in]  max  Maximum value of each axis.
 *  @param[in]  div  Divisions of each axis.
 *  @param[in]  points  Coordinates of the points to be rasterized.
 *  @returns    The rasterized model.
 */
NCT_EXPIMP SparseArray2D<bool> rasterize(const Array<Point2D>& points,
    double min, double max, unsigned int div = 64);

/**
 *  @brief      Rasterize lines.
 *  @details    This function rasterizes lines in a grid.
 *  @param[in]  min  Minimum value of each axis.
 *  @param[in]  max  Maximum value of each axis.
 *  @param[in]  div  Divisions of each axis.
 *  @param[in]  lines  Lines to be rasterized.
 *  @param[in]  connectivity  Type of connectivity.
 *  @returns    The rasterized model.
 */
NCT_EXPIMP SparseArray2D<bool> rasterize(const Array<Line>& lines,
    double min, double max, unsigned int div = 64,
    NConnectivity2D connectivity = NConnectivity2D::FourConnected);

/**
 *  @brief      Rasterize points.
 *  @details    This function rasterizes points in a grid.
 *  @param[in]  min  Minimum value of each axis.
 *  @param[in]  max  Maximum value of each axis.
 *  @param[in]  div  Divisions of each axis.
 *  @param[in]  points  Coordinates of the points to be rasterized.
 *  @returns    The rasterized model.
 */
NCT_EXPIMP SparseArray3D<bool> rasterize(const Array<Point3D>& points,
    double min, double max, unsigned int div = 64);

/**
 *  @brief      Rasterize lines.
 *  @param[in]  min  Minimum value of each axis.
 *  @param[in]  max  Maximum value of each axis.
 *  @param[in]  div  Divisions of each axis.
 *  @param[in]  lines  Lines to be rasterized.
 *  @param[in]  connectivity  Type of connectivity.
 *  @returns    The rasterized model.
 */
NCT_EXPIMP SparseArray3D<bool> rasterize(const Array<Line3D>& lines,
    double min, double max, unsigned int div = 64,
    NConnectivity3D connectivity = NConnectivity3D::TwentySixConnected);

/**
 *  @brief      Rasterize triangles.
 *  @details    This function rasterizes triangles in a grid.
 *  @param[in]  min  Minimum value of each axis.
 *  @param[in]  max  Maximum value of each axis.
 *  @param[in]  div  Divisions of each axis.
 *  @param[in]  triangles  Triangles to be rasterized.
 *  @param[in]  connectivity  Type of connectivity.
 *  @returns    The rasterized model.
 */
NCT_EXPIMP SparseArray3D<bool> rasterize(const Array<Triangle3D>& triangles,
    double min, double max, unsigned int div = 64,
    NConnectivity3D connectivity = NConnectivity3D::TwentySixConnected);

}}}

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
