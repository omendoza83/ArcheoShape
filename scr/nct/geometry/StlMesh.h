//=================================================================================================================
/**
 *  @file       StlMesh.h
 *  @brief      nct::geometry::mesh::StlMesh class.
 *  @details    Declaration of the nct::geometry::mesh::StlMesh class. 
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

#ifndef NCT_STL_MESH_H_INCLUDE
#define NCT_STL_MESH_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/Array.h>
#include <nct/Vector3D.h>
#include <nct/geometry/Triangle3D.h>
#include <nct/geometry/mesh.h>

#include <string>
#include <iostream>

//=================================================================================================================
namespace nct {
namespace geometry {
namespace mesh {

/**
 *  @brief      STL mesh class.
 *  @details    This class is used to manipulate 3D meshes that are loaded and saved thru STL files.
 */
class NCT_EXPIMP StlMesh final {

public:

    ////////// Constructors //////////
    
    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the default configuration.
     */
    StlMesh() = default;

    /**
     *  @brief      Class constructor.
     *  @details    Class constructor that loads one model from a file.
     *  @param[in]  fileName  File to load.
     */
    explicit StlMesh(const std::string& fileName);
    
    ////////// Member functions //////////        

    /**
     *  @brief      Allocate model.
     *  @details    This function allocates the memory needed by the object to manipulate a model.
     *  @param[in]  nTriangles  Number of triangles in the model.
     */
    void allocateModel(unsigned int nTriangles);

    /**
     *  @brief      Clear object.
     *  @details    This function releases the allocated memory.
     */
    void clear();
    
    /**
     *  @brief      Name of the model.
     *  @details    This function returns the name of the model that is used when the data are stored in an ASCII file.
     *  @returns    The name of the model.
     */
    std::string& modelName() noexcept;

    /**
     *  @brief      Name of the model.
     *  @details    This function returns the name of the model that is used when the data are stored in an ASCII file.
     *  @returns    The name of the model.
     */
    const std::string& modelName() const noexcept;

    /**
     *  @brief      Data of the model.
     *  @details    This function returns the header data of the model that is used when it is stored in a binary file.
     *  @returns    The data of the model.
     */
    std::string& modelData() noexcept;

    /**
     *  @brief      Data of the model.
     *  @details    This function returns the header data of the model that is used when it is stored in a binary file.
     *  @returns    The data of the model.
     */
    const std::string& modelData() const noexcept;

    /**
     *  @brief      Number of triangles in the model.
     *  @details    This function returns the number of triangles of the current model.
     *  @returns    The number of triangles.
     */
    unsigned int numberOfTriangles() const noexcept;

    /**
     *  @brief      Triangle.
     *  @details    This function returns the selected triangle.
     *  @param[in]  triangleIndex  Triangle index.
     *  @returns    The selected triangle.
     */
    geometry::Triangle3D& triangle(unsigned int triangleIndex);

    /**
     *  @brief      Triangle.
     *  @details    This function returns the selected triangle.
     *  @param[in]  triangleIndex  Triangle index.
     *  @returns    The selected triangle.
     */
    const geometry::Triangle3D& triangle(unsigned int triangleIndex) const;

    /**
     *  @brief      Triangle normal.
     *  @details    This function returns the normal vector of the selected triangle.
     *  @param[in]  triangleIndex  Triangle index.
     *  @returns    The selected normal vector.
     */
    Vector3D<double>& triangleNormal(unsigned int triangleIndex);

    /**
     *  @brief      Triangle normal.
     *  @details    This function returns the normal vector of the selected triangle.
     *  @param[in]  triangleIndex  Triangle index.
     *  @returns    The selected normal vector.
     */
    const Vector3D<double>& triangleNormal(unsigned int triangleIndex) const;

    /**
     *  @brief      Triangular mesh.
     *  @details    This function returns the mesh of the model. The mesh is defined by one array of vertices
     *              and one array of the indices that defines the triangle elements.
     *  @param[in]  joinVertices  True to join repeated vertices.
     *  @returns    A tuple with the following components: \n
     *              * The vertices of the mesh. \n
     *              * The vertex normals of the mesh. \n
     *              * The indices that define the triangles of the mesh.
     */
    std::tuple<Array<Point3D>, Array<Vector3D<double>>, Array<Vector3D<unsigned int>>> triangularMesh(
        bool joinVertices = false) const;

    /**
     *  @brief      Save STL file.
     *  @details    This function saves the model in a STL file. 
     *  @param[in]  fileName  Name of the file to save.
     *  @param[in]  binary  True, if the new file will be saved in binary format, false if the new file
     *              will be saved in ASCII format.
     */
    void save(const std::string& fileName, bool binary = true);

    /**
     *  @brief      Load STL file.
     *  @details    This function loads a model from a STL file.
     *  @param[in]  fileName  Name of the file to load.
     *  @return     An object with the loaded mesh.
     */
    static StlMesh load(const std::string& fileName);
    

private:

    ////////// Data members //////////    

    std::string name_{ "Empty object" };        /**< Name of the solid represented by the object
                                                     (only ascii files). */
    std::string data_{ "Empty object" };        /**< Data added to the header (for binary files). */

    nct::Array<geometry::Triangle3D> faces_;    /**< Array of triangular faces. */

    nct::Array<Vector3D<double>> normals_;      /**< Normal vectors to the faces. */

};

}}}

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
