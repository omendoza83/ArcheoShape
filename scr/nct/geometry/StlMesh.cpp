//=================================================================================================================
/**
 *  @file       StlMesh.cpp
 *  @brief      nct::geometry::mesh::StlMesh class implementation file.
 *  @details    This file contains the implementation of the nct::geometry::mesh::StlMesh class.
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
#include <nct/geometry/StlMesh.h>
#include <nct/nct_utils.h>

#include <iomanip>
#include <fstream>
#include <cstring>
#include <list>
#include <algorithm>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::mesh::StlMesh::StlMesh(const std::string& fileName) 
{
    try {
        *this = load(fileName);
    }
    catch (const nct_exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw InitializationException(SOURCE_INFO);
    }
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::mesh::StlMesh::allocateModel(unsigned int nTriangles) 
{
    clear();    
    faces_.resize(nTriangles);
    normals_.resize(nTriangles);
    for (unsigned int i=0; i<nTriangles; i++) {
        faces_[i].setVertex1(0,0,0);
        faces_[i].setVertex2(0,0,0);
        faces_[i].setVertex3(0,0,0);
        normals_[i].setCoefficients(0, 0, 0);
    }

    name_ = "STL model";
    data_ = "STL model";
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::mesh::StlMesh::clear() 
{
    faces_.clear();
    normals_.clear();
    name_ = "Empty model";
    data_ = "Empty model";
}

//-----------------------------------------------------------------------------------------------------------------
std::string& nct::geometry::mesh::StlMesh::modelName() noexcept 
{
    return name_;
}
    
//-----------------------------------------------------------------------------------------------------------------
const std::string& nct::geometry::mesh::StlMesh::modelName() const noexcept 
{
    return name_;
}

//-----------------------------------------------------------------------------------------------------------------
std::string& nct::geometry::mesh::StlMesh::modelData() noexcept
{
    return data_;
}

//-----------------------------------------------------------------------------------------------------------------
const std::string& nct::geometry::mesh::StlMesh::modelData() const noexcept 
{
    return data_;
}

//-----------------------------------------------------------------------------------------------------------------
unsigned int nct::geometry::mesh::StlMesh::numberOfTriangles() const noexcept
{
    return static_cast<unsigned int>(faces_.size());
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::Triangle3D& nct::geometry::mesh::StlMesh::triangle(unsigned int triangleIndex)
{
    if (triangleIndex >= numberOfTriangles())
        throw nct::IndexOutOfRangeException("triangleIndex", SOURCE_INFO);
    return faces_[triangleIndex];
}

//-----------------------------------------------------------------------------------------------------------------
const nct::geometry::Triangle3D& nct::geometry::mesh::StlMesh::triangle(unsigned int triangleIndex) const 
{
    if (triangleIndex >= numberOfTriangles())
        throw nct::IndexOutOfRangeException("triangleIndex", SOURCE_INFO);
    return faces_[triangleIndex];
}

//-----------------------------------------------------------------------------------------------------------------
nct::Vector3D<double>& nct::geometry::mesh::StlMesh::triangleNormal(unsigned int triangleIndex)
{
    if (triangleIndex >= numberOfTriangles())
        throw nct::IndexOutOfRangeException("triangleIndex", SOURCE_INFO);
    return normals_[triangleIndex];
}

//-----------------------------------------------------------------------------------------------------------------
const nct::Vector3D<double>& nct::geometry::mesh::StlMesh::triangleNormal(
    unsigned int triangleIndex) const
{
    if (triangleIndex >= numberOfTriangles())
        throw nct::IndexOutOfRangeException("triangleIndex", SOURCE_INFO);
    return normals_[triangleIndex];
}


//-----------------------------------------------------------------------------------------------------------------
std::tuple<nct::Array<nct::Point3D>, nct::Array<nct::Vector3D<double>>,
    nct::Array<nct::Vector3D<unsigned int>>>
nct::geometry::mesh::StlMesh::triangularMesh(bool joinVertices) const 
{
    auto nFaces = numberOfTriangles();
    Array<Vector3D<unsigned int>> triangles(nFaces, Vector3D<unsigned int>());
    Array<Vector3D<double>> vertexNormals;
    Array<Point3D> vertices;

    if (joinVertices) {
        unsigned int nVertices = 0;
        Array<Vector3D<double>> ver((size_t)3*nFaces);
        for (unsigned int i=0; i<nFaces; i++) {
            // Vertex 1.
            unsigned int j = 0;
            for (j=0; j<nVertices; j++) {
                if (faces_[i][0] == ver[j])
                    break;
            }

            if (j == nVertices) {
                ver[nVertices] = faces_[i][0];
                triangles[i][0] = nVertices;
                nVertices++;
            }
            else {
                triangles[i][0] = j;
            }

            // Vertex 2.    
            for (j=0; j<nVertices; j++) {
                if (faces_[i][1] == ver[j])
                    break;
            }

            if (j == nVertices) {
                ver[nVertices] = faces_[i][1];
                triangles[i][1] = nVertices;
                nVertices++;
            }
            else {
                triangles[i][1] = j;
            }

            // Vertex 3.
            for (j=0; j<nVertices; j++) {
                if (faces_[i][2] == ver[j])
                    break;
            }

            if (j == nVertices) {
                ver[nVertices] = faces_[i][2];
                triangles[i][2] = nVertices;
                nVertices++;
            }
            else {
                triangles[i][2] = j;
            }
        }

        // Store vertices.
        vertices.assign(nVertices, Point3D());
        for (unsigned int i=0; i<nVertices; i++)
            vertices[i] = ver[i];

        // Calculate vertexNormals.
        vertexNormals.assign(nVertices, Vector3D<double>(0, 0, 0));
        nct::RealVector nN(nVertices, 0);

        auto nTr = triangles.size();
        for (index_t i=0; i<nTr; i++) {
            for (unsigned int j=0; j<3; j++) {
                vertexNormals[triangles[i][j]] += normals_[i];
                nN[triangles[i][j]]++;
            }
        }
        
        for (unsigned int i=0; i<nVertices; i++) {
            if (nN[i]>0) {
                vertexNormals[i] *= 1.f/nN[i];
                vertexNormals[i].normalize();
            }
        }
    }
    else {
        vertices.assign((size_t)3*nFaces, Point3D());
        vertexNormals.assign((size_t)3*nFaces, Vector3D<double>());
        for (unsigned int i=0; i<nFaces; i++) {
            vertices[(size_t)3*i]     = faces_[i][0];
            vertices[(size_t)3*i + 1] = faces_[i][1];
            vertices[(size_t)3*i + 2] = faces_[i][2];

            vertexNormals[(size_t)3*i] = normals_[i];
            vertexNormals[(size_t)3*i].normalize();
            vertexNormals[(size_t)3*i + 1] = vertexNormals[(size_t)3*i];
            vertexNormals[(size_t)3*i + 2] = vertexNormals[(size_t)3*i];

            triangles[i] = Vector3D<unsigned int>(3 * i, 3 * i + 1, 3 * i + 2);
        }
    }

    return std::make_tuple(vertices, vertexNormals, triangles);
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::mesh::StlMesh::save(const std::string& fileName, bool binary)
{
    std::ofstream file;            
    if (binary) {
        // Open file.
        file.open(fileName.c_str(), std::ios_base::binary);
        if (file.fail())
            throw nct::IOException(fileName, exc_error_opening_ouput_file, SOURCE_INFO);

        // Write header.
        char header[80];        
        memset(header, 0, 80);
        unsigned int nchar = static_cast<unsigned int>(data_.length());
        if (nchar > 79)
            nchar = 79;
        std::strcpy(header, data_.substr(0, nchar).c_str());
        file.write(header, 80);

        // Write number of faces_.
        unsigned int nFaces =  static_cast<unsigned int>(faces_.size());
        file.write(reinterpret_cast<char*> (&nFaces), sizeof(nFaces));

        // Write faces_.
        float outF[12];            
        unsigned short endFile =  0;        
        for (unsigned int i=0; i<nFaces; i++) {
            // Normal vector.
            outF[0] = static_cast<float>(normals_[i][0]);
            outF[1] = static_cast<float>(normals_[i][1]);
            outF[2] = static_cast<float>(normals_[i][2]);

            // Vertex 1.
            outF[3] = static_cast<float>(faces_[i][0][0]);
            outF[4] = static_cast<float>(faces_[i][0][1]);
            outF[5] = static_cast<float>(faces_[i][0][2]);

            // Vertex 2.
            outF[6] = static_cast<float>(faces_[i][1][0]);
            outF[7] = static_cast<float>(faces_[i][1][1]);
            outF[8] = static_cast<float>(faces_[i][1][2]);

            // Vertex 3.
            outF[9] = static_cast<float>(faces_[i][2][0]);
            outF[10]= static_cast<float>(faces_[i][2][1]);
            outF[11]= static_cast<float>(faces_[i][2][2]);

            // Write data.
            file.write(reinterpret_cast<char*> (outF), 12*sizeof(float));
            file.write(reinterpret_cast<char*> (&endFile), sizeof(endFile));
        }
    }
    else {
        // Open the file.
        file.open (fileName.c_str());    
        if (file.fail())
            throw nct::IOException(fileName, exc_error_opening_ouput_file, SOURCE_INFO);
        file << std::showpos << std::showpoint << std::fixed << std::scientific << std::setprecision(6);

        // Write solid name.
        file << "solid " << name_ << std::endl;
            
        // Write faces_.
        auto nFaces =  faces_.size();
        for (index_t i=0; i<nFaces; i++) {
            // Write facet normal.
            file << "    facet normal " << normals_[i][0] << " " 
                << normals_[i][1] << " " << normals_[i][2] << std::endl;

            // Write outer loop.
            file << "        outer loop" << std::endl;

            // Write faces_.
            file << "            vertex " << faces_[i][0][0] << " " 
                << faces_[i][0][1] << " " << faces_[i][0][2] << std::endl;
            file << "            vertex " << faces_[i][1][0] << " " 
                << faces_[i][1][1] << " " << faces_[i][1][2] << std::endl;
            file << "            vertex " << faces_[i][2][0] << " " 
                << faces_[i][2][1] << " " << faces_[i][2][2] << std::endl;

            // Write endloop.
            file << "        endloop" << std::endl;

            // Write endfacet.
            file << "    endfacet" << std::endl;
        }            

        // Write endsolid.
        file << "endsolid " << name_ << std::endl;
    }

    // Close the file.
    file.close();
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::mesh::StlMesh nct::geometry::mesh::StlMesh::load(const std::string& fileName) 
{
    StlMesh meshObj;

    // Open the file to test if the file is binary or ASCII.
    std::ifstream file;    
    file.open (fileName.c_str(), std::ios_base::binary);    
    if (file.fail())
        throw IOException(fileName, exc_error_opening_input_file, SOURCE_INFO);

    char solid[6];
    file.read(solid, 5);
    solid[5] = 0;

    file.close();
    std::transform(solid, solid + 6, solid, [](const char c)->char
    {
        return static_cast<char>(::tolower(c));
    });
    bool binary = strcmp(solid, "solid")!=0;
    
    // Read data from the file.
    if (binary) {
        // Open the file.
        file.open(fileName.c_str(), std::ios_base::binary);
        if (file.fail())
            throw nct::IOException(fileName, exc_error_reading_data, SOURCE_INFO);

        // Load header.
        char header[80];    
        std::memset(header, 0, 80);
        unsigned int nchar = static_cast<unsigned int>(meshObj.data_.length());
        if (nchar > 79)
            nchar = 79;
        std::strcpy(header, meshObj.data_.substr(0, nchar).c_str());
        file.read(header, 80);
        meshObj.name_ = "Unknwon";
        meshObj.data_ = header;

        // Load number of faces_.
        unsigned int nFaces =  0;
        file.read(reinterpret_cast<char*> (&nFaces), sizeof(nFaces));
        meshObj.faces_.resize(nFaces);
        meshObj.normals_.resize(nFaces);

        // Load faces_ and normals.
        float inF[12];            
        unsigned short endFile =  0;        
        for (unsigned int i=0; i<nFaces; i++) {
            // Read data.
            file.read(reinterpret_cast<char*> (inF), 12*sizeof(float));
            file.read(reinterpret_cast<char*> (&endFile), sizeof(endFile));

            // Normal vector.
            meshObj.normals_[i].setCoefficients(inF[0], inF[1], inF[2]);

            // Vertex 1.
            meshObj.faces_[i].setVertex1(inF[3], inF[4], inF[5]);

            // Vertex 2.
            meshObj.faces_[i].setVertex2(inF[6], inF[7], inF[8]);
            
            // Vertex 3.
            meshObj.faces_[i].setVertex3(inF[9], inF[10], inF[11]);
        }        
    }
    else {
        // Open the file.
        file.open (fileName.c_str());    
        if (file.fail())
            throw nct::IOException(fileName, exc_error_reading_data, SOURCE_INFO);

        // Load model name.
        std::string inS, inS2;
        std::getline(file, inS);
        meshObj.name_ = inS.substr(6, inS.length()-1);
        meshObj.data_ = std::string("Model name: ") + meshObj.name_;

        // Load model data.
        std::list<std::pair<geometry::Triangle3D, Vector3D<double>>> tr;

        bool endFile = false;
        bool error = false;
        while (!endFile && !error) {
            file >> inS;
            std::transform(inS.begin(), inS.end(), inS.begin(), [](const char c)->char
            {
                return static_cast<char>(::tolower(c));
            });

            error = file.eof();

            if (inS == "facet" && !error) {
                geometry::Triangle3D trian;
                Vector3D<double> norm;

                file >> inS;
                std::transform(inS.begin(), inS.end(), inS.begin(), [](const char c)->char
                {
                    return static_cast<char>(::tolower(c));
                });

                if (inS == "normal") {
                    file >> norm[0] >> norm[1] >> norm[2];
                    file >> inS >> inS2;
                    std::transform(inS.begin(), inS.end(), inS.begin(), [](const char c)->char
                    {
                        return static_cast<char>(::tolower(c));
                    });
                    std::transform(inS2.begin(), inS2.end(), inS2.begin(), [](const char c)->char
                    {
                        return static_cast<char>(::tolower(c));
                    });

                    if (inS == "outer" && inS2 == "loop") {
                        file >> inS;
                        std::transform(inS.begin(), inS.end(), inS.begin(), [](const char c)->char
                        {
                            return static_cast<char>(::tolower(c));
                        });

                        if (inS == "vertex")
                            file >> trian[0][0] >> trian[0][1] >> trian[0][2];
                        else
                            error = true;

                        file >> inS;
                        std::transform(inS.begin(), inS.end(), inS.begin(), [](const char c)->char
                        {
                            return static_cast<char>(::tolower(c));
                        });

                        if (inS == "vertex")
                            file >> trian[1][0] >> trian[1][1] >> trian[1][2];
                        else
                            error = true;

                        file >> inS;
                        std::transform(inS.begin(), inS.end(), inS.begin(), [](const char c)->char
                        {
                            return static_cast<char>(::tolower(c));
                        });

                        if (inS == "vertex")
                            file >> trian[2][0] >> trian[2][1] >> trian[2][2];
                        else
                            error = true;

                        tr.push_back(std::make_pair(trian, norm));
                    }
                    else
                        error = true;

                    file >> inS;
                    std::transform(inS.begin(), inS.end(), inS.begin(), [](const char c)->char
                    {
                        return static_cast<char>(::tolower(c));
                    });

                    if (inS != "endloop")
                        error = true;
                }
                else
                    error = true;

                file >> inS;
                std::transform(inS.begin(), inS.end(), inS.begin(), [](const char c)->char
                {
                    return static_cast<char>(::tolower(c));
                });

                if (inS != "endfacet")
                    error = true;
            }
            else if (inS == "endsolid")
                endFile = true;    
        }

        if (error)
            throw nct::IOException(fileName, exc_error_decoding_file, SOURCE_INFO);

        // Store triangles.
        auto nFaces = tr.size();
        meshObj.faces_.resize(nFaces);
        meshObj.normals_.resize(nFaces);

        auto faceIndex = 0;
        for (const auto& item : tr) {
            meshObj.faces_[faceIndex] = item.first;
            meshObj.normals_[faceIndex] = item.second;
            faceIndex++;
        }
    }

    file.close();

    return meshObj;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
