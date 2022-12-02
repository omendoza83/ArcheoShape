//=================================================================================================================
/**
 *  @file       PlyMesh.h
 *  @brief      nct::geometry::PlyMesh class.
 *  @details    Declaration of the nct::geometry::PlyMesh class. 
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

#ifndef NCT_PLY_MESH_H_INCLUDE
#define NCT_PLY_MESH_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/Array.h>
#include <nct/Array2D.h>
#include <nct/Vector3D.h>

#include <string>
#include <vector>
#include <tuple>
#include <iostream>

//=================================================================================================================
namespace nct {
namespace geometry {
namespace mesh {

/**
 *  @brief      PLY mesh class.
 *  @details    This class is used to manipulate 3D meshes that are loaded and saved thru PLY files.
 */
class NCT_EXPIMP PlyMesh final {

public:

    /**
     *  @brief      Data types.
     *  @details    Data types to store information of the model.
     */
    enum class DataType : unsigned short {

        NotValid = 0x0000,  /**< Not valid data type. */

        Char = 0x0001,      /**< Signed integer (1 byte). */

        Short = 0x0002,     /**< Signed integer (2 bytes). */

        Int = 0x0004,       /**< Signed integer (4 bytes). */

        UChar = 0x0101,     /**< Unsigned integer (1 byte). */

        UShort = 0x0102,    /**< Unsigned integer (2 bytes). */

        UInt = 0x0104,      /**< Unsigned integer (4 bytes). */

        Float = 0x0204,     /**< Real number (4 bytes, single precision). */

        Double = 0x0208,    /**< Real number (8 bytes, double precision). */
    };

    /**
     *  @brief      File types.
     *  @details    File types that are supported by this class.
     */
    enum class FileType : unsigned char {

        NotValid,               /**< Not valid file. */

        Ascii,                  /**< ASCII file. */

        BinaryLittleEndian,     /**< Binary file with data in little endian format. */

        BinaryBigEndian,        /**< Binary file with data in big endian format. */
    };

    /**
     *  @brief      Property types.
     *  @details    Property types that are supported by this class.
     */
    enum class PropertyType : unsigned char {

        Ordinary,   /**< Ordinary property (one scalar). */

        List,       /**< List of scalar values. */
    };

    /**
     *  @brief      Single element.
     *  @details    This tuple defines an alias representing an element in the model.
     *              <Name, number of elements, start index, size in bytes,
     *               max number of entries for each item>
     */
    using Element = std::tuple<std::string, unsigned int, unsigned int,
        unsigned int, unsigned int>;

    /**
     *  @brief      Property object.
     *  @details    This tuple defines an alias representing a property in the model.
     *              <Element index, property type(ordinary, list), data type,
     *              second data type (only for lists), name>
     */
    using Property = std::tuple<unsigned int, PropertyType, DataType, DataType, std::string>;

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the default configuration.
     */
    PlyMesh() = default;

    /**
     *  @brief      Class constructor.
     *  @details    Class constructor that loads one model from a file.
     *  @param[in]  fileName  File to load.
     */
    explicit PlyMesh(const std::string& fileName);
    
    ////////// Member functions //////////        

    /**
     *  @brief      Clear object.
     *  @details    This function releases the allocated memory.
     */
    void clear();

    /**
     *  @brief      Initialize model.
     *  @details    This function initializes a new model according to a triangular mesh.
     *  @param[in]  vertices  Array with the vertices of the model.
     *  @param[in]  triangles  Array with the triangles of the model.
     */
    void initializeModel(const Array<Point3D>& vertices,
        const Array<Vector3D<unsigned int>>& triangles);

    /**
     *  @brief      Number of comments.
     *  @details    This function returns the number of comments in the object.
     *  @returns    The number of comments.
     */
    unsigned int numberOfComments() const noexcept;

    /**
     *  @brief      Comment.
     *  @details    This function returns the specified comment.
     *  @param[in]  commentIndex  Index of the comment to be returned.
     *  @returns    The selected comment.
     */
    const std::string& comment(unsigned int commentIndex) const;

    /**
     *  @brief      Comments.
     *  @details    This function returns an array with the comments of the object.
     *  @returns    An array with the comments.
     */
    Array<std::string> comments() const;

    /**
     *  @brief      Number of elements.
     *  @details    This function returns the number of elements in the object.
     *  @returns    The number of elements.
     */
    unsigned int numberOfElements() const noexcept;

    /**
     *  @brief      Get an element.
     *  @details    This function returns the specified element.
     *  @param[in]  elemIndex  Index of the element to be returned.
     *  @returns    The selected element.
     */
    const Element& element(unsigned int elemIndex) const;

    /**
     *  @brief      Get elements.
     *  @details    This function returns an array with the elements of the object.
     *  @returns    An array with the elements of the object.
     */
    Array<Element> elements() const;

    /**
     *  @brief      Number of properties.
     *  @details    This function returns the number of properties in the object.
     *  @returns    The number of properties.
     */
    unsigned int numberOfProperties() const noexcept;

    /**
     *  @brief      Number of properties of the selected element.
     *  @details    This function returns the number of proeprties of the selected element.
     *  @param[in]  elemIndex  Index of the elemenet whose number of properties will be returned.
     *  @returns    The number of properties.
     */
    unsigned int numberOfProperties(unsigned int elemIndex) const;

    /**
     *  @brief      Get a property.
     *  @details    This function returns the specified property.
     *  @param[in]  propIndex  Index of the property to be returned.
     *  @returns    The selected property.
     */
    const Property& property(unsigned int propIndex) const;

    /**
     *  @brief      Get a property.
     *  @details    This function returns the specified property.
     *  @param[in]  elemIndex  Index of the element which property will be returned.
     *  @param[in]  propIndex  Index of the property to be returned.
     *  @returns    The selected property.
     */
    const Property& property(unsigned int elemIndex, unsigned int propIndex) const;

    /**
     *  @brief      Get properties.
     *  @details    This function returns an array with the properties of the object.
     *  @returns    An array with the properties of the object.
     */
    Array<Property> properties() const;

    /**
     *  @brief      Get properties.
     *  @details    This function returns an array with the properties of the selected element.
     *  @param[in]  elemIndex  Index of the element which properties will be returned.
     *  @returns    An array with the properties of the selected element.
     */
    Array<Property> properties(unsigned int elemIndex) const;

    /**
     *  @brief      Element index.
     *  @details    This function returns the index of the element with name "elementName".
     *  @param[in]  elementName  The name of the element which index will be returned.
     *  @returns    The index of the specified element. -1 indicates that the element doesn't exist.
     */
    int elementIndex(const std::string& elementName) const;
    
    /**
     *  @brief      Property index.
     *  @details    This function returns the index of the property with name "propertyName" into the list of
     *              properties of the element "elementName".
     *  @param[in]  elementName  The name of the element that contains the specified property.
     *  @param[in]  propertyName  The name of the property which index will be returned.
     *  @returns    The index of the specified property. -1 indicates that the element doesn't exist.
     */
    int propertyIndex(const std::string& elementName, const std::string& propertyName) const;

    /**
     *  @brief      Element data.
     *  @details    This function returns an array with the data that correspond to one element.
     *  @param[in]  elemIndex  Index of the element which data will be returned.
     *  @returns    Array with the element data. Each row in the array corresponds
     *              to one item and each column corresponds to one properties.
     */
    Matrix elementData(unsigned int elemIndex) const;

    /**
     *  @brief      Element data array.
     *  @details    This function returns an array with the data that correspond to one element.
     *  @param[in]  elemIndex  Index of the element which data will be returned.
     *  @returns    Array with the data of the element. Each element in the array corresponds
     *              to one item of the element. Each item is represented by one array.
     */
    Array<RealVector> elementDataArray(unsigned int elemIndex) const;
    
    /**
     *  @brief      Triangular mesh.
     *  @details    This function returns the model mesh. The mesh is specified by one array with the vertices of the
     *              solid figure and another array with the indices of the vertices of each triangle. 
     *  @returns    A tuple with the following components: \n
     *              * The vertices of the mesh. \n
     *              * The indices that define the triangles of the mesh.
     */
    std::tuple<Array<Point3D>, Array<Vector3D<unsigned int>>> triangularMesh() const;

    /**
     *  @brief      Save PLY file.
     *  @details    This function saves the model in a STL file. 
     *  @param[in]  fileName  Name of the file to save.
     *  @param[in]  binary  True, if the new file will be saved in binary format, false if the new file will 
     *              be saved in ASCII format.
     */
    void save(const std::string& fileName, bool binary = true) const;

    /**
     *  @brief      Load PLY file.
     *  @details    This function loads a model from a PLY file.
     *  @param[in]  fileName  Name of the file to read from.
     *  @return     An object with the loaded mesh.
     */
    static PlyMesh load(const std::string& fileName);
    
private:

    ////////// Member functions //////////    

    /**
     *  @brief      Read a datum.
     *  @details    This function reads one datum from the data container.
     *  @param[in]  position  Position in the data container.
     *  @param[in]  dataType  Data type of the element to be read.
     *  @returns    The datum that was read.
     */
    double readDatum(unsigned int position, DataType dataType) const;

    /**
     *  @brief      Write a datum.
     *  @details    This function writes a new datum to one output stream.
     *  @param[in, out] file  File stream where the datum will be written.
     *  @param[in]  position  Position in the data container.
     *  @param[in]  dataType  Data type of the datum to be added.
     *  @returns    The datum that was written.
     */
    double writeDatum(std::ostream& file, unsigned int position, DataType dataType) const;

    /**
     *  @brief      Add a datum.
     *  @details    This function adds a new datum to the object.
     *  @param[in, out] file  File stream from where the datum will be read.
     *  @param[in]  dataType  Data type of the datum to be added.
     *  @returns    The value of the datum that was added to the container.
     */
    double addDatum(std::istream& file, DataType dataType);

    /**
     *  @brief      Swap endian.
     *  @details    Swapps the endianness of one variable.
     *  @param[in]  position  Index of the datum to be swapped by this function.
     *  @param[in]  dataType  Data type to be added.
     */
    void swapEndian(unsigned int position, DataType dataType);

    /**
     *  @brief      Data type.
     *  @details    This function returns the data type represented by the specified string.
     *  @param[in]  dataStr  String with the data type.
     *  @returns    The data type represented by the input string.
     */
    static DataType dataType(const std::string& dataStr);

    /**
     *  @brief      String of one data type.
     *  @details    This function returns the string that represent one data type.
     *  @param[in]  dataType  Data type which string is required.
     *  @returns    The string of the specified data type.
     */
    static std::string stringDataType(DataType dataType);

    ////////// Data members //////////    

    std::vector<std::string> comments_;     /**< Model comments. */

    std::vector<Element> elements_;         /**< Model elements. */

    std::vector<Property> properties_;      /**< Element properties. */

    std::vector<char> data_;                /**< Data. */

};

}}}

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
