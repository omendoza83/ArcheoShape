//=================================================================================================================
/**
 *  @file       PlyMesh.cpp
 *  @brief      nct::geometry::PlyMesh class implementation file.
 *  @details    This file contains the implementation of the nct::geometry::PlyMesh class.
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
#include <nct/geometry/PlyMesh.h>
#include <nct/nct_utils.h>
#include <fstream>
#include <sstream>
#include <algorithm>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::mesh::PlyMesh::PlyMesh(const std::string& fileName) 
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
void nct::geometry::mesh::PlyMesh::clear() 
{
    comments_.clear();
    elements_.clear();
    properties_.clear();
    data_.clear();
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::mesh::PlyMesh::initializeModel(
    const Array<Point3D>& vertices,
    const Array<Vector3D<unsigned int>>& triangles)
{
    clear();

    // Add comments to the model.
    comments_.assign(2, "");
    comments_[0] = "NCT";
    comments_[1] = "Triangular mesh of one object";

    // Create header.
    unsigned int nv = static_cast<unsigned int>(vertices.size());
    unsigned int nt = static_cast<unsigned int>(triangles.size());

    elements_.resize(2);
    properties_.resize(4);

    elements_[0] = std::make_tuple("vertex", nv, 0, static_cast<unsigned int>(3 * nv*sizeof(double)), 3);
    properties_[0] = std::make_tuple(0, PropertyType::Ordinary, DataType::Double, DataType::NotValid, "x");
    properties_[1] = std::make_tuple(0, PropertyType::Ordinary, DataType::Double, DataType::NotValid, "y");
    properties_[2] = std::make_tuple(0, PropertyType::Ordinary, DataType::Double, DataType::NotValid, "z");

    elements_[1] = std::make_tuple("face", nt, static_cast<unsigned int>(3 * nv*sizeof(double)),
        static_cast<unsigned int>(nt + (size_t)3*nt*sizeof(int)), 4);
    properties_[3] = std::make_tuple(1, PropertyType::List, DataType::UChar, DataType::Int, "vertex_index");
    
    // Add data to the model.
    unsigned int totSize = std::get<3>(elements_[0]) + std::get<3>(elements_[1]);
    data_.assign(totSize, 0);
    unsigned int cc = 0;
    for (unsigned int i=0; i<nv; i++) {
        for (unsigned int j = 0; j < 3; j++) {
            auto c = reinterpret_cast<const char*>(&vertices[i][j]);
            data_[cc++] = c[0];
            data_[cc++] = c[1];
            data_[cc++] = c[2];
            data_[cc++] = c[3];
            data_[cc++] = c[4];
            data_[cc++] = c[5];
            data_[cc++] = c[6];
            data_[cc++] = c[7];
        }
    }

    for (unsigned int i=0; i<nt; i++) {
        data_[cc++] = 3;

        for (unsigned int j = 0; j < 3; j++) {
            unsigned int val = static_cast<unsigned int>(triangles[i][j]);
            auto c = reinterpret_cast<char*>(&val);
            data_[cc++] = c[0];
            data_[cc++] = c[1];
            data_[cc++] = c[2];
            data_[cc++] = c[3];
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
unsigned int nct::geometry::mesh::PlyMesh::numberOfComments() const noexcept 
{
    return static_cast<unsigned int>(comments_.size());
}

//-----------------------------------------------------------------------------------------------------------------
const std::string& nct::geometry::mesh::PlyMesh::comment(unsigned int commentIndex) const 
{
    if (commentIndex>= comments_.size())
        throw IndexOutOfRangeException("commentIndex", SOURCE_INFO);
    return comments_[commentIndex];
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<std::string> nct::geometry::mesh::PlyMesh::comments() const 
{
    unsigned int size = numberOfComments();
    Array<std::string> commArray (size, "");
    for (unsigned int i=0; i<size; i++)
        commArray[i] = comment(i);

    return commArray;
}

//-----------------------------------------------------------------------------------------------------------------
unsigned int nct::geometry::mesh::PlyMesh::numberOfElements() const noexcept 
{
    return static_cast<unsigned int>(elements_.size());
}

//-----------------------------------------------------------------------------------------------------------------
const nct::geometry::mesh::PlyMesh::Element& nct::geometry::mesh::PlyMesh::element(
    unsigned int elemIndex) const
{
    if (elemIndex>= elements_.size())
        throw IndexOutOfRangeException("elemIndex", SOURCE_INFO);
    return elements_[elemIndex];
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::geometry::mesh::PlyMesh::Element> nct::geometry::mesh::PlyMesh::elements() const 
{
    unsigned int size = numberOfElements();
    Array<Element> el(size);
    for (unsigned int i=0; i<size; i++)
        el[i] = element(i);
    return el;
}

//-----------------------------------------------------------------------------------------------------------------
unsigned int nct::geometry::mesh::PlyMesh::numberOfProperties() const noexcept 
{
    return static_cast<unsigned int>(properties_.size());
}

//-----------------------------------------------------------------------------------------------------------------
unsigned int nct::geometry::mesh::PlyMesh::numberOfProperties(unsigned int elemIndex) const 
{
    if (elemIndex>= elements_.size())
        throw IndexOutOfRangeException("elemIndex", SOURCE_INFO);

    unsigned int propN = static_cast<unsigned int>(properties_.size());
    unsigned int np = 0;
    for (unsigned int i=0; i<propN; i++)
        np += std::get<0>(properties_[i]) == elemIndex;
    return np;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::geometry::mesh::PlyMesh::Property& nct::geometry::mesh::PlyMesh::property(
    unsigned int propIndex) const
{
    if (propIndex>= properties_.size())
        throw IndexOutOfRangeException("propIndex", SOURCE_INFO);
    return properties_[propIndex];
}

//-----------------------------------------------------------------------------------------------------------------
const nct::geometry::mesh::PlyMesh::Property& nct::geometry::mesh::PlyMesh::property(
    unsigned int elemIndex, unsigned int propIndex) const
{
    unsigned int npt = numberOfProperties();
    unsigned int np = numberOfProperties(elemIndex);

    if (propIndex>= np)
        throw IndexOutOfRangeException("propIndex", SOURCE_INFO);
    
    unsigned int i = 0;
    unsigned int c = 0;
    for (i = 0; i<npt; i++) {
        if (std::get<0>(properties_[i]) == elemIndex) {
            if (c == propIndex)
                break;
            c++;            
        }
    }
    
    return properties_[i];
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::geometry::mesh::PlyMesh::Property> nct::geometry::mesh::PlyMesh::properties() const 
{
    unsigned int size = numberOfProperties();
    Array<Property> pr(size);
    for (unsigned int i=0; i<size; i++)
        pr[i] = property(i);

    return pr;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::geometry::mesh::PlyMesh::Property> nct::geometry::mesh::PlyMesh::properties(
    unsigned int elemIndex) const
{
    unsigned int size = numberOfProperties(elemIndex);
    Array<Property> pr(size);
    for (unsigned int i=0; i<size; i++)
        pr[i] = property(elemIndex, i);

    return pr;
}


//-----------------------------------------------------------------------------------------------------------------
int nct::geometry::mesh::PlyMesh::propertyIndex(const std::string& elementName, 
    const std::string& propertyName) const
{
    int elemIndex = elementIndex(elementName);
    if (elemIndex == -1)
        return -1;

    int index = -1;
    Array<Property> pr = properties(elemIndex);

    for (unsigned int i=0; i<pr.size(); i++) {
        if (std::get<4>(pr[i]) == propertyName) {
            index = i;
            break;
        }
    }

    return index;
}

//-----------------------------------------------------------------------------------------------------------------
std::tuple<nct::Array<nct::Point3D>, nct::Array<nct::Vector3D<unsigned int>>> 
nct::geometry::mesh::PlyMesh::triangularMesh() const 
{
    int vIndex = elementIndex("vertex");
    int fIndex = elementIndex("face");

    int xIndex = propertyIndex("vertex", "x");
    int yIndex = propertyIndex("vertex", "y");
    int zIndex = propertyIndex("vertex", "z");
    int vertexIndex = propertyIndex("face", "vertex_index");

    if (vertexIndex == -1)
        vertexIndex = propertyIndex("face", "vertex_indices");

    if ( (vIndex == -1) || (fIndex == -1) )
        throw ConfigurationException(exc_missing_elements_in_ply_object, SOURCE_INFO);

    if ( (xIndex == -1) || (yIndex == -1) || (zIndex == -1) || (vertexIndex == -1))
        throw ConfigurationException(exc_missing_properties_in_ply_object,
        SOURCE_INFO);

    auto vertexData = elementData(vIndex);
    auto faceData = elementData(fIndex);
    
    // Fill vertices.
    unsigned int nv = static_cast<unsigned int>(vertexData.rows());
    Array<nct::Point3D> vertices(nv, Point3D());
    for (unsigned int i=0; i<nv; i++)
        vertices[i] = Vector3D<double>(vertexData(i,xIndex),
            vertexData(i, yIndex), vertexData(i, zIndex));
    
    // Fill triangles.
    unsigned int nt = static_cast<unsigned int>(faceData.rows());
    unsigned int ntt = nt;
    for (unsigned int i=0; i<nt; i++) {
        if (faceData(i,vertexIndex)<3)
            throw ConfigurationException(exc_bad_face_in_ply_object, SOURCE_INFO);
        ntt += static_cast<unsigned int>(faceData(i,vertexIndex) + 0.1) - 3;
    }

    unsigned int c = 0;
    unsigned int tt = 0;
    Array<Vector3D<unsigned int>> triangles(ntt, Vector3D<unsigned int>());
    for (unsigned int i=0; i<nt; i++) {
        tt = static_cast<unsigned int>(faceData(i,vertexIndex) + 0.1) - 2;

        for (unsigned int j = 0; j<tt; j++) {
            triangles[c] = Vector3D<unsigned int>(
                static_cast<unsigned int>(faceData(i, (size_t)vertexIndex + 1) + 0.1),
                static_cast<unsigned int>(faceData(i, (size_t)vertexIndex + 2 + j) + 0.1),
                static_cast<unsigned int>(faceData(i, (size_t)vertexIndex + 3 + j) + 0.1));
            c++;
        }
    }

    return std::make_tuple(vertices, triangles);
}

//-----------------------------------------------------------------------------------------------------------------
nct::Matrix nct::geometry::mesh::PlyMesh::elementData(unsigned int elemIndex) const 
{
    if (elemIndex>= elements_.size())
        throw IndexOutOfRangeException("elemIndex", SOURCE_INFO);
    
    // Get properties of the element.
    unsigned int nProperties = static_cast<unsigned int>(properties_.size());
    std::vector<bool> plist;
    std::vector<unsigned char> psize;
    std::vector<DataType> pdataType;

    for (unsigned int j=0; j<nProperties; j++) {
        if (std::get<0>(properties_[j]) == elemIndex) {
            if (std::get<1>(properties_[j]) == PropertyType::Ordinary) {
                pdataType.push_back(std::get<2>(properties_[j]));
                psize.push_back(static_cast<unsigned char>(std::get<2>(properties_[j])) & 0x0F);
                plist.push_back(false);                
            }
            else {
                pdataType.push_back(std::get<2>(properties_[j]));
                pdataType.push_back(std::get<3>(properties_[j]));

                psize.push_back(static_cast<unsigned char>(std::get<2>(properties_[j])) & 0x0F);
                psize.push_back(static_cast<unsigned char>(std::get<3>(properties_[j])) & 0x0F);
                plist.push_back(true);
                plist.push_back(false);
            }
        }
    }

    // Get data of the element.
    unsigned int nItems = std::get<1>(elements_[elemIndex]);
    unsigned int currentPosition = std::get<2>(elements_[elemIndex]);
    unsigned int maxEntries = std::get<4>(elements_[elemIndex]);
    unsigned int nProp = static_cast<unsigned int>(psize.size());
    Matrix elemData(nItems, maxEntries, 0);
    std::vector<double> vecTmp(512);

    for (unsigned int k=0; k<nItems; k++) {
        vecTmp.clear();
        for (index_t p = 0; p<nProp; p++) {
            if (plist[p]) {
                unsigned int nl = static_cast<unsigned int>(
                    readDatum(currentPosition, pdataType[p]) + 0.1);
                vecTmp.push_back(nl);
                currentPosition += psize[p];
                for (unsigned int i=0; i<nl; i++) {
                    vecTmp.push_back(readDatum(currentPosition, pdataType[p+1]));
                    currentPosition+=psize[p+1];
                }
                p++;
            }
            else {                
                vecTmp.push_back(readDatum(currentPosition, pdataType[p]));
                currentPosition += psize[p];
            }
        }

        unsigned int nel = static_cast<unsigned int>(vecTmp.size());
        for (unsigned int i=0; i<nel; i++)
            elemData(k,i) = vecTmp[i];
    }

    return elemData;
}

//-----------------------------------------------------------------------------------------------------------------
nct::Array<nct::RealVector> nct::geometry::mesh::PlyMesh::elementDataArray(
    unsigned int elemIndex) const
{
    if (elemIndex>= elements_.size())
        throw IndexOutOfRangeException("elemIndex", SOURCE_INFO);
    
    // Get properties of the element.
    unsigned int nProperties = static_cast<unsigned int>(properties_.size());
    std::vector<bool> plist;
    std::vector<unsigned char> psize;
    std::vector<DataType> pdataType;

    for (unsigned int j=0; j<nProperties; j++) {
        if (std::get<0>(properties_[j]) == elemIndex) {
            if (std::get<1>(properties_[j]) == PropertyType::Ordinary) {
                pdataType.push_back(std::get<2>(properties_[j]));
                psize.push_back(static_cast<unsigned char>(std::get<2>(properties_[j])) & 0x0F);
                plist.push_back(false);                
            }
            else {
                pdataType.push_back(std::get<2>(properties_[j]));
                pdataType.push_back(std::get<3>(properties_[j]));

                psize.push_back(static_cast<unsigned char>(std::get<2>(properties_[j])) & 0x0F);
                psize.push_back(static_cast<unsigned char>(std::get<3>(properties_[j])) & 0x0F);
                plist.push_back(true);
                plist.push_back(false);
            }
        }
    }

    // Get data of the element.
    unsigned int nItems = std::get<1>(elements_[elemIndex]);
    unsigned int currentPosition = std::get<2>(elements_[elemIndex]);
    unsigned int nProp = static_cast<unsigned int>(psize.size());
    
    Array<RealVector> elemData(nItems);
    std::vector<double> vecTmp(512);

    for (unsigned int k=0; k<nItems; k++) {
        vecTmp.clear();
        for (index_t p = 0; p<nProp; p++) {
            if (plist[p]) {
                unsigned int nl = static_cast<unsigned int>(
                    readDatum(currentPosition, pdataType[p]) + 0.1);
                vecTmp.push_back(nl);
                currentPosition += psize[p];
                for (unsigned int i=0; i<nl; i++) {
                    vecTmp.push_back(readDatum(currentPosition, pdataType[p+1]));
                    currentPosition+=psize[p+1];
                }
                p++;
            }
            else {                
                vecTmp.push_back(readDatum(currentPosition, pdataType[p]));
                currentPosition += psize[p];
            }
        }

        unsigned int nel = static_cast<unsigned int>(vecTmp.size());
        elemData[k].assign(nel, 0.0);
        for (unsigned int i=0; i<nel; i++)
            elemData[k][i] = vecTmp[i];
    }    

    return elemData;
}

//-----------------------------------------------------------------------------------------------------------------
int nct::geometry::mesh::PlyMesh::elementIndex(const std::string& elementName) const 
{
    int index = -1;
    for (unsigned int i=0; i<elements_.size(); i++) {
        if (std::get<0>(elements_[i]) == elementName) {
            index = i;
            break;
        }
    }
    return index;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::mesh::PlyMesh::save(const std::string& fileName, bool binary) const 
{
    std::ofstream file;            

    // Open file.
    if (binary)
        file.open(fileName.c_str(), std::ios_base::binary);
    else
        file.open (fileName.c_str());

    if (file.fail())
        throw IOException(fileName, exc_error_opening_ouput_file, SOURCE_INFO);

    // Write magic key and format specification.
    file << "ply" << std::endl;

    if (binary)
        file << "format binary_little_endian 1.0" << std::endl;
    else
        file << "format ascii 1.0" << std::endl;

    // Write comments.
    for (unsigned int i=0; i<comments_.size(); i++)
        file << "comment " << comments_[i] << std::endl;

    // Write elements.
    for (unsigned int i=0; i<elements_.size(); i++) {
        file << "element " << std::get<0>(elements_[i]) << " " << std::get<1>(elements_[i]) << std::endl;

        auto pr = properties(i);
        for (unsigned int j=0; j<pr.size(); j++) {
            if (std::get<1>(pr[j]) == PropertyType::Ordinary)
                file << "property " << stringDataType(std::get<2>(pr[j])) 
                << " " << std::get<4>(pr[j]) << std::endl;
            else
                file << "property list " << stringDataType(std::get<2>(pr[j])) << " "
                << stringDataType(std::get<3>(pr[j])) << " " << std::get<4>(pr[j]) << std::endl;
        }
    }

    // Write end of header.
    file << "end_header" << std::endl;

    // Write data.
    if (binary) {
        file.write(&data_[0], data_.size());
    }
    else {        
        unsigned int nProperties = static_cast<unsigned int>(properties_.size());
        for (unsigned int i=0; i<elements_.size(); i++) {
            // Get properties of the element.    
            std::vector<bool> plist;
            std::vector<unsigned char> psize;
            std::vector<DataType> pdataType;

            for (unsigned int j=0; j<nProperties; j++) {
                if (std::get<0>(properties_[j]) == i) {
                    if (std::get<1>(properties_[j]) == PropertyType::Ordinary) {
                        pdataType.push_back(std::get<2>(properties_[j]));
                        psize.push_back(static_cast<unsigned char>(std::get<2>(properties_[j])) & 0x0F);
                        plist.push_back(false);                
                    }
                    else {
                        pdataType.push_back(std::get<2>(properties_[j]));
                        pdataType.push_back(std::get<3>(properties_[j]));

                        psize.push_back(static_cast<unsigned char>(std::get<2>(properties_[j])) & 0x0F);
                        psize.push_back(static_cast<unsigned char>(std::get<3>(properties_[j])) & 0x0F);
                        plist.push_back(true);
                        plist.push_back(false);
                    }
                }
            }

            // Write data of the element.
            unsigned int nItems = std::get<1>(elements_[i]);
            unsigned int currentPosition = std::get<2>(elements_[i]);
            unsigned int nProp = static_cast<unsigned int>(psize.size());

            for (unsigned int k=0; k<nItems; k++) {
                for (index_t p = 0; p<nProp; p++) {
                    if (plist[p]) {
                        unsigned int nl = static_cast<unsigned int>(writeDatum(file, 
                            currentPosition, pdataType[p]) + 0.1);
                        currentPosition += psize[p];
                        for (unsigned int l=0; l<nl; l++) {
                            writeDatum(file, currentPosition, pdataType[p+1]);
                            currentPosition+=psize[p+1];
                        }
                        p++;
                    }
                    else {                
                        writeDatum(file, currentPosition, pdataType[p]);
                        currentPosition += psize[p];
                    }
                }    
                file << std::endl;
            }    
        }

    }

    // Close file.
    file.close();
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::mesh::PlyMesh nct::geometry::mesh::PlyMesh::load(const std::string& fileName) 
{
    PlyMesh meshObj;

    std::ifstream file;    
    file.open (fileName.c_str(), std::ios_base::binary);    
    if (file.fail())
        throw IOException(fileName, exc_error_opening_input_file, SOURCE_INFO);

    file.seekg(0, std::ios_base::end);
    auto fileSize = static_cast<size_t>(file.tellg());
    file.seekg(0);

    ////////// Function for line reading //////////
    auto readNextLine = [&](std::ifstream& stream, std::string& line, bool toLowerCase) -> bool
    {
        line = "";
        while (line.length() == 0  && !stream.eof()) {
            std::getline(stream, line);
            line = trim(line);            
        }

        if (toLowerCase)
            std::transform(line.begin(), line.end(), line.begin(), [](const char c)->char
        {
            return static_cast<char>(::tolower(c));
        });

        return !stream.eof();        
    };
    
    ////////// Read "Magic Key" //////////
    std::string line;
    readNextLine(file, line, true);
    
    if (line != "ply")
        throw IOException(fileName, exc_bad_ply_file, SOURCE_INFO);

    ////////// Read data type //////////
    FileType fileType = FileType::NotValid;
    readNextLine(file, line, true);
    
    if (line == "format ascii 1.0")
        fileType = FileType::Ascii;
    else if (line == "format binary_little_endian 1.0")
        fileType = FileType::BinaryLittleEndian;
    else if (line == "format binary_big_endian 1.0")
        fileType = FileType::BinaryBigEndian;
    else
        throw IOException(fileName, exc_bad_file_format, SOURCE_INFO);

    ////////// Read elements and their properties //////////
    line = "";
    unsigned int nElements = 0;
    unsigned int nProperties = 0;
    
    bool endH = false;
    while (!endH && !file.eof()) {
        readNextLine(file, line, false);
        std::stringstream strStream;
        strStream << line;
        
        std::string entryName;
        strStream >> entryName;
        std::transform(entryName.begin(), entryName.end(), entryName.begin(), [](const char c)->char {
            return static_cast<char>(::tolower(c));
        });

        if (entryName == "comment") {
            std::streampos pos = strStream.tellg();
            std::string commentString = line.substr(static_cast<unsigned int>(pos));
            meshObj.comments_.push_back(trim(commentString));
        }
        else if (entryName == "element") {
            std::string elementName;
            unsigned int elementSize = 0;
            strStream >> elementName >> elementSize;            
            if (strStream.fail())
                throw IOException(fileName, exc_bad_file_format, SOURCE_INFO);

            meshObj.elements_.push_back(std::make_tuple(elementName, elementSize, 0, 0, 0));
            nElements++;
        }
        else if (entryName == "property") {
            if (nElements == 0)
                throw IOException(fileName, exc_bad_file_format, SOURCE_INFO);

            std::string entryData;
            strStream >> entryData;
            std::transform(entryData.begin(), entryData.end(), entryData.begin(), [](const char c)->char {
                return static_cast<char>(::tolower(c));
            });

            if (entryData == "list") {
                strStream >> entryData;
                DataType listType1 = dataType(entryData);
                if (listType1 == DataType::NotValid)
                    throw IOException(fileName, exc_bad_file_format, SOURCE_INFO);

                strStream >> entryData;
                DataType listType2 = dataType(entryData);
                if (listType2 == DataType::NotValid)
                    throw IOException(fileName, exc_bad_file_format, SOURCE_INFO);

                std::string propertyName;
                strStream >> propertyName;

                meshObj.properties_.push_back(
                    std::make_tuple(static_cast<unsigned int>(nElements - 1), PropertyType::List, listType1,
                    listType2, propertyName));

                nProperties++;
            }
            else {
                DataType dType = dataType(entryData);
                if (dType == DataType::NotValid)
                    throw IOException(fileName, exc_bad_file_format, SOURCE_INFO);

                std::string propertyName;
                strStream >> propertyName;

                meshObj.properties_.push_back(
                    std::make_tuple(
                    static_cast<unsigned int>(nElements-1), PropertyType::Ordinary, dType,
                    DataType::NotValid, propertyName));

                nProperties++;
            }

        }
        else if (entryName == "end_header") {
            endH = true;
        }
    }
    
    if (file.fail())
        throw IOException(fileName, exc_bad_file_format, SOURCE_INFO);

    if (file.eof())
        throw IOException(fileName, exc_error_reading_file_header, SOURCE_INFO);

    ////////// Read data from file //////////
    if (fileType == FileType::Ascii) {
        // ASCII file
        for (unsigned int i=0; i<nElements; i++) {
            // Get properties of the element.
            std::vector<bool> plist;
            std::vector<DataType> pdataType;

            for (unsigned int j=0; j<nProperties; j++) {
                if (std::get<0>(meshObj.properties_[j]) == i) {
                    if (std::get<1>(meshObj.properties_[j]) == PropertyType::Ordinary) {
                        pdataType.push_back(std::get<2>(meshObj.properties_[j]));
                        plist.push_back(false);                        
                    }
                    else {
                        pdataType.push_back(std::get<2>(meshObj.properties_[j]));
                        pdataType.push_back(std::get<3>(meshObj.properties_[j]));
                        plist.push_back(true);
                        plist.push_back(false);    
                    }
                }
            }

            // Read data of the element.
            unsigned int nItems = std::get<1>(meshObj.elements_[i]);
            unsigned int nProp = static_cast<unsigned int>(pdataType.size());
            for (unsigned int k=0; k<nItems; k++) {
                for (index_t p = 0; p<nProp; p++) {
                    if (plist[p]) {
                        unsigned int nElem = static_cast<int>(meshObj.addDatum(file, pdataType[p]) + 0.1);
                        for (unsigned int t = 0; t<nElem; t++)
                            meshObj.addDatum(file, pdataType[p+1]);
                        p++;
                    }
                    else {
                        meshObj.addDatum(file, pdataType[p]);
                    }
                }
            }            
        }
    }
    else  {
        // Binary file  with the same type of endianness.
        auto dataSize = fileSize - static_cast<size_t>(file.tellg());
        meshObj.data_.assign(dataSize, 0);
        file.read(&meshObj.data_[0], dataSize);
    }

    ////////// Close file //////////
    if (file.fail())
        throw IOException(fileName, exc_bad_file_format, SOURCE_INFO);
    
    file.close();    

    ////////// Find the beginning of each section into the data container //////////
    unsigned int currentPosition = 0;
    for (unsigned int i=0; i<nElements; i++) {
        // Get Properties of the element.
        std::vector<bool> plist;
        std::vector<unsigned char> psize;
        std::vector<DataType> pdataType;

        bool blist = 0;
        unsigned int tsun = 0;
        unsigned int maxEntries = 0;
        for (unsigned int j=0; j<nProperties; j++) {            
            if (std::get<0>(meshObj.properties_[j]) == i) {
                if (std::get<1>(meshObj.properties_[j]) == PropertyType::Ordinary) {
                    pdataType.push_back(std::get<2>(meshObj.properties_[j]));
                    psize.push_back(static_cast<unsigned char>(std::get<2>(meshObj.properties_[j])) & 0x0F);
                    plist.push_back(false);
                    tsun += static_cast<unsigned char>(std::get<2>(meshObj.properties_[j])) & 0x0F;
                    maxEntries++;
                }
                else {
                    pdataType.push_back(std::get<2>(meshObj.properties_[j]));
                    pdataType.push_back(std::get<3>(meshObj.properties_[j]));
                    psize.push_back(static_cast<unsigned char>(
                        std::get<2>(meshObj.properties_[j])) & 0x0F);
                    psize.push_back(static_cast<unsigned char>(
                        std::get<3>(meshObj.properties_[j])) & 0x0F);
                    plist.push_back(true);
                    plist.push_back(false);
                    blist = true;                    
                }
            }
        }
        
        // Calculate positions and size of each element.
        if (blist == false) {
            std::get<2>(meshObj.elements_[i]) = currentPosition;
            std::get<3>(meshObj.elements_[i]) = tsun*std::get<1>(meshObj.elements_[i]);
            currentPosition += std::get<3>(meshObj.elements_[i]);
            std::get<4>(meshObj.elements_[i]) = maxEntries;
        }
        else {
            std::get<2>(meshObj.elements_[i]) = currentPosition;

            tsun = 0;
            maxEntries = 0;
            unsigned int nItems = std::get<1>(meshObj.elements_[i]);
            unsigned int nProp = static_cast<unsigned int>(psize.size());
            for (unsigned int k=0; k<nItems; k++) {
                unsigned int nEntries = 0;
                for (index_t p = 0; p<nProp; p++) {
                    if (plist[p]) {
                        unsigned int totList = static_cast<unsigned int>(meshObj.readDatum(
                            currentPosition, pdataType[p]) + 0.1);
                        tsun +=  psize[p] +  psize[p+1]*totList;
                        currentPosition += psize[p] +  psize[p+1]*totList;
                        nEntries += 1 + totList;
                        p++;
                    }
                    else {
                        tsun += psize[p];
                        currentPosition += psize[p];
                        nEntries++;
                    }
                }
                                
                maxEntries = nEntries > maxEntries ? nEntries : maxEntries;
            }            
            std::get<3>(meshObj.elements_[i]) = tsun;
            std::get<4>(meshObj.elements_[i]) = maxEntries;
        }
    }

    ////////// Swap endianness if it's necessary //////////
    if ( (fileType == FileType::BinaryLittleEndian && isBigEndian()) || 
         (fileType == FileType::BinaryBigEndian && isLittleEndian()) )     
    {
        for (unsigned int i=0; i<nElements; i++) {
            // Get properties of the element.
            unsigned int nItemProperties = static_cast<unsigned int>(meshObj.properties_.size());
            std::vector<bool> plist;
            std::vector<unsigned char> psize;
            std::vector<DataType> pdataType;

            for (unsigned int j=0; j<nItemProperties; j++) {
                if (std::get<0>(meshObj.properties_[j]) == i) {
                    if (std::get<1>(meshObj.properties_[j]) == PropertyType::Ordinary) {
                        pdataType.push_back(std::get<2>(meshObj.properties_[j]));
                        psize.push_back(static_cast<unsigned char>(
                            std::get<2>(meshObj.properties_[j])) & 0x0F);
                        plist.push_back(false);                
                    }
                    else {
                        pdataType.push_back(std::get<2>(meshObj.properties_[j]));
                        pdataType.push_back(std::get<3>(meshObj.properties_[j]));
                        psize.push_back(static_cast<unsigned char>(std::get<2>(
                            meshObj.properties_[j])) & 0x0F);
                        psize.push_back(static_cast<unsigned char>(std::get<3>(
                            meshObj.properties_[j])) & 0x0F);
                        plist.push_back(true);
                        plist.push_back(false);
                    }
                }
            }

            // Get data of the element.
            currentPosition = std::get<2>(meshObj.elements_[i]);
            unsigned int nItems = std::get<1>(meshObj.elements_[i]);
            unsigned int nProp = static_cast<unsigned int>(psize.size());

            for (unsigned int k=0; k<nItems; k++) {
                for (index_t p = 0; p<nProp; p++) {
                    if (plist[p]) {
                        meshObj.swapEndian(currentPosition, pdataType[p]);
                        unsigned int nl = static_cast<unsigned int>(meshObj.readDatum(
                            currentPosition, pdataType[p]) + 0.1);
                        currentPosition += psize[p];
                        for (unsigned int l=0; l<nl; l++) {
                            meshObj.swapEndian(currentPosition, pdataType[p+1]);
                            currentPosition+=psize[p+1];
                        }
                        p++;
                    }
                    else {                
                        meshObj.swapEndian(currentPosition, pdataType[p]);
                        currentPosition += psize[p];
                    }
                }                
            }                    
        }
    }    

    return meshObj;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::mesh::PlyMesh::readDatum(unsigned int position, DataType dataType) const 
{
    unsigned int dataSize = static_cast<unsigned char>(dataType) & 0x0F;
    unsigned int totS = static_cast<unsigned int>(data_.size());
    if ( (position + dataSize) > totS)
        throw IndexOutOfRangeException("position", SOURCE_INFO);

    double r = 0;
    switch (dataType) {
        case DataType::Char:
                r = data_[position];
            break;
        case DataType::Short: {
                union dd
                {
                    short d;                    
                    char c[2];        
                }cd;
                cd.c[0] = data_[position];
                cd.c[1] = data_[position + (size_t)1];
                r = cd.d;
            }
            break;
        case DataType::Int: {
                union dd
                {
                    int d;                    
                    char c[4];        
                }cd;
                cd.c[0] = data_[position];
                cd.c[1] = data_[position + (size_t)1];
                cd.c[2] = data_[position + (size_t)2];
                cd.c[3] = data_[position + (size_t)3];
                r = cd.d;
            }
            break;
        case DataType::UChar:
            r = static_cast<unsigned char>(data_[position]);
            break;
        case DataType::UShort: {
                union dd
                {
                    unsigned short d;                    
                    char c[2];        
                }cd;
                cd.c[0] = data_[position];
                cd.c[1] = data_[position + (size_t)1];
                r = cd.d;
            }
            break;
        case DataType::UInt: {
                union dd
                {
                    unsigned int d;                    
                    char c[4];        
                }cd;
                cd.c[0] = data_[position];
                cd.c[1] = data_[position + (size_t)1];
                cd.c[2] = data_[position + (size_t)2];
                cd.c[3] = data_[position + (size_t)3];
                r = cd.d;
            }
            break;
        case DataType::Float: {
                union dd
                {
                    float d;                    
                    char c[4];        
                }cd;
                cd.c[0] = data_[position];
                cd.c[1] = data_[position + (size_t)1];
                cd.c[2] = data_[position + (size_t)2];
                cd.c[3] = data_[position + (size_t)3];
                r = cd.d;
            }
            break;
        case DataType::Double: {
                union dd
                {
                    double d;                    
                    char c[8];        
                }cd;
                cd.c[0] = data_[position];
                cd.c[1] = data_[position + (size_t)1];
                cd.c[2] = data_[position + (size_t)2];
                cd.c[3] = data_[position + (size_t)3];
                cd.c[4] = data_[position + (size_t)4];
                cd.c[5] = data_[position + (size_t)5];
                cd.c[6] = data_[position + (size_t)6];
                cd.c[7] = data_[position + (size_t)7];
                r = cd.d;
            }
            break;
        default:
            throw ArgumentException("dataType", exc_bad_data_type_in_file, SOURCE_INFO);
    }

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::mesh::PlyMesh::writeDatum(std::ostream& file,
    unsigned int position, DataType dataType) const
{
    unsigned int dataSize = static_cast<unsigned char>(dataType) & 0x0F;
    unsigned int totS = static_cast<unsigned int>(data_.size());
    if ( (position + dataSize) > totS)
        throw IndexOutOfRangeException("position", SOURCE_INFO);

    double r = 0;
    switch (dataType) {
        case DataType::Char: {
                r = data_[position];
                file << static_cast<short>(data_[position]) << " ";
            }
            break;
        case DataType::Short: {
                union dd
                {
                    short d;                    
                    char c[2];        
                }cd;
                cd.c[0] = data_[position];
                cd.c[1] = data_[position + (size_t)1];
                r = cd.d;
                file << cd.d << " ";
            }
            break;
        case DataType::Int: {
                union dd
                {
                    int d;                    
                    char c[4];        
                }cd;
                cd.c[0] = data_[position];
                cd.c[1] = data_[position + (size_t)1];
                cd.c[2] = data_[position + (size_t)2];
                cd.c[3] = data_[position + (size_t)3];
                r = cd.d;
                file << cd.d << " ";
            }
            break;
        case DataType::UChar:
            r = static_cast<unsigned char>(data_[position]);
            file << static_cast<unsigned short>(r + 0.1) << " ";
            break;
        case DataType::UShort: {
                union dd
                {
                    unsigned short d;                    
                    char c[2];        
                }cd;
                cd.c[0] = data_[position];
                cd.c[1] = data_[position + (size_t)1];
                r = cd.d;
                file << cd.d << " ";
            }
            break;
        case DataType::UInt: {
                union dd
                {
                    unsigned int d;                    
                    char c[4];        
                }cd;
                cd.c[0] = data_[position];
                cd.c[1] = data_[position + (size_t)1];
                cd.c[2] = data_[position + (size_t)2];
                cd.c[3] = data_[position + (size_t)3];
                r = cd.d;
                file << cd.d << " ";
            }
            break;
        case DataType::Float: {
                union dd
                {
                    float d;                    
                    char c[4];        
                }cd;
                cd.c[0] = data_[position];
                cd.c[1] = data_[position + (size_t)1];
                cd.c[2] = data_[position + (size_t)2];
                cd.c[3] = data_[position + (size_t)3];
                r = cd.d;
                file << cd.d << " ";
            }
            break;
        case DataType::Double: {
                union dd
                {
                    double d;                    
                    char c[8];        
                }cd;
                cd.c[0] = data_[position];
                cd.c[1] = data_[position + (size_t)1];
                cd.c[2] = data_[position + (size_t)2];
                cd.c[3] = data_[position + (size_t)3];
                cd.c[4] = data_[position + (size_t)4];
                cd.c[5] = data_[position + (size_t)5];
                cd.c[6] = data_[position + (size_t)6];
                cd.c[7] = data_[position + (size_t)7];
                r = cd.d;
                file << cd.d << " ";
            }
            break;
        default:
            throw ArgumentException("dataType", exc_bad_data_type_in_file, 
                SOURCE_INFO);
    }

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
double nct::geometry::mesh::PlyMesh::addDatum(std::istream& file, DataType dataType) 
{
    double r = 0;
    switch (dataType) {
        case DataType::Char: {
                short d;
                file >> d;
                data_.push_back(static_cast<char>(d));
                r = d;
            }
            break;
        case DataType::Short: {
                union dd
                {
                    short d;                    
                    char c[2];        
                }cd;
                file >> cd.d;
                data_.push_back(cd.c[0]);
                data_.push_back(cd.c[1]);
                r = cd.d;
            }
            break;
        case DataType::Int: {
                union dd
                {
                    int d;                    
                    char c[4];        
                }cd;
                file >> cd.d;
                data_.push_back(cd.c[0]);
                data_.push_back(cd.c[1]);
                data_.push_back(cd.c[2]);
                data_.push_back(cd.c[3]);
                r = cd.d;
            }
            break;
        case DataType::UChar: {
                short d;
                file >> d;
                data_.push_back(static_cast<unsigned char>(d));
                r = d;
            }
            break;
        case DataType::UShort: {
                union dd
                {
                    unsigned short d;                    
                    char c[2];        
                }cd;
                file >> cd.d;
                data_.push_back(cd.c[0]);
                data_.push_back(cd.c[1]);
                r = cd.d;
            }
            break;
        case DataType::UInt: {
                union dd
                {
                    unsigned int d;                    
                    char c[4];        
                }cd;
                file >> cd.d;
                data_.push_back(cd.c[0]);
                data_.push_back(cd.c[1]);
                data_.push_back(cd.c[2]);
                data_.push_back(cd.c[3]);
                r = cd.d;
            }
            break;
        case DataType::Float: {
                union dd
                {
                    float d;                    
                    char c[4];        
                }cd;
                file >> cd.d;
                data_.push_back(cd.c[0]);
                data_.push_back(cd.c[1]);
                data_.push_back(cd.c[2]);
                data_.push_back(cd.c[3]);
                r = cd.d;
            }
            break;
        case DataType::Double: {
                union dd
                {
                    double d;                    
                    char c[8];        
                }cd;
                file >> cd.d;
                data_.push_back(cd.c[0]);
                data_.push_back(cd.c[1]);
                data_.push_back(cd.c[2]);
                data_.push_back(cd.c[3]);
                data_.push_back(cd.c[4]);
                data_.push_back(cd.c[5]);
                data_.push_back(cd.c[6]);
                data_.push_back(cd.c[7]);
                r = cd.d;
            }
            break;
        default:
            throw ArgumentException("dataType", exc_bad_data_type_in_file, 
                SOURCE_INFO);
    }

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::mesh::PlyMesh::swapEndian(unsigned int position, DataType dataType) 
{
    unsigned int dataSize = static_cast<unsigned char>(dataType) & 0x0F;
    unsigned int totS = static_cast<unsigned int>(data_.size());
    if ( (position + dataSize) > totS)
        throw IndexOutOfRangeException("position", SOURCE_INFO);

    switch (dataType) {
        case DataType::Char:    
        case DataType::UChar:    
            break;
        case DataType::Short:
        case DataType::UShort: {
                char c[2];
                c[0] = data_[position];
                c[1] = data_[position + (size_t)1];
                data_[position]   = c[1];
                data_[position + (size_t)1] = c[0];
            }
            break;
        case DataType::Int:
        case DataType::UInt:
        case DataType::Float: {
                char c[4];    
                c[0] = data_[position];
                c[1] = data_[position + (size_t)1];
                c[2] = data_[position + (size_t)2];
                c[3] = data_[position + (size_t)3];
                data_[position]              = c[3];
                data_[position + (size_t)1]  = c[2];
                data_[position + (size_t)2]  = c[1];
                data_[position + (size_t)3]  = c[0];
            }
            break;
        case DataType::Double: {
                char c[8];    
                c[0] = data_[position];
                c[1] = data_[position + (size_t)1];
                c[2] = data_[position + (size_t)2];
                c[3] = data_[position + (size_t)3];
                c[4] = data_[position + (size_t)4];
                c[5] = data_[position + (size_t)5];
                c[6] = data_[position + (size_t)6];
                c[7] = data_[position + (size_t)7];
                data_[position]             = c[7];
                data_[position + (size_t)1] = c[6];
                data_[position + (size_t)2] = c[5];
                data_[position + (size_t)3] = c[4];
                data_[position + (size_t)4] = c[3];
                data_[position + (size_t)5] = c[2];
                data_[position + (size_t)6] = c[1];
                data_[position + (size_t)7] = c[0];
            }
            break;
        default:
            throw ArgumentException("dataType", exc_bad_data_type_in_file, 
                SOURCE_INFO);
    }

}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::mesh::PlyMesh::DataType nct::geometry::mesh::PlyMesh::dataType(
    const std::string& dataStr) {

    std::string dataString = trim(dataStr);
    std::transform(dataString.begin(), dataString.end(), dataString.begin(), [](const char c)->char
    {
        return static_cast<char>(::tolower(c));
    });

    if (dataString == "char" || dataString == "int8")
        return DataType::Char;
    else if (dataString == "short" || dataString == "int16")
        return DataType::Short;
    else if (dataString == "int" || dataString == "int32")
        return DataType::Int;
    else if (dataString == "uchar" || dataString == "uint8")
        return DataType::UChar;
    else if (dataString == "ushort" || dataString == "uint16")
        return DataType::UShort;
    else if (dataString == "uint" || dataString == "uint32")
        return DataType::UInt;
    else if (dataString == "float" || dataString == "float32")
        return DataType::Float;
    else if (dataString == "double" || dataString == "float64")
        return DataType::Double;

    return DataType::NotValid;    
}

//-----------------------------------------------------------------------------------------------------------------
std::string nct::geometry::mesh::PlyMesh::stringDataType(DataType dataType) 
{
    std::string str = "Not valid";
    switch (dataType) {
        case DataType::Char:
            str = "char";
            break;
        case DataType::Short:
            str = "short";
            break;
        case DataType::Int:
            str = "int";
            break;
        case DataType::UChar:
            str = "uchar";
            break;
        case DataType::UShort:
            str = "ushort";
            break;
        case DataType::UInt:
            str = "uint";
            break;
        case DataType::Float:
            str = "float";
            break;
        case DataType::Double:
            str = "double";
            break;        
        case DataType::NotValid:
            break;
    }

    return str;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
