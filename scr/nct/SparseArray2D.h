//=================================================================================================================
/**
 *  @file       SparseArray2D.h
 *  @brief      nct::SparseArray2D class template.
 *  @details    Declaration of the nct::SparseArray2D class template.
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

#ifndef NCT_SPARSE_ARRAY_2D_H_INCLUDE
#define NCT_SPARSE_ARRAY_2D_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/Array.h>
#include <nct/Array2D.h>
#include <nct/Vector2D.h>

#include <map>
#include <iostream>

//=================================================================================================================
namespace nct {

/**
 *  @brief      Class template for sparse arrays of objects.
 *  @details    This class template is used to manipulate sparse arrays of objects.
 *  @note       It is possible to disable index checking in the () operator by defining
 *              NCT_SPARSE_ARRAY_2D_DISABLE_INDEX_CHECKING.
 *  @tparam     T  The data type to be stored in the array.
 *  @tparam     MapAlloc  The type of allocator to be used to build the array.
 */
template<typename T, typename MapAlloc =
    std::allocator<std::pair<const Vector2D<size_t>, T>>>
    class SparseArray2D {

public:

    ////////// Type definitions //////////

    /** Base data type. */
    using value_type = T;

    /** Pointer. */
    using pointer = T* ;

    /** Const pointer. */
    using const_pointer = const T*;

    /** Reference. */
    using reference = T&;

    /** const Reference. */
    using const_reference = const T&;

    /** Size type. */
    using size_type = size_t;

    /** Difference type. */
    using difference_type = diff_t;

    /** Map allocator type. */
    using map_allocator_type = MapAlloc;

    /** Element index type. */
    using index_type = Vector2D<size_type>;

    ////////// Auxiliar classes //////////

    /**
     *  @brief      Index comparator.
     *  @details    Helper class for index comparisons.
     */
    class IndexComparator final {
    public:

        /**
         *  @brief      Compare two indices.
         *  @details    This function compares two indices according to the order of the 
         *              coordinates. If the first coordinate of index 1 is lower than 
         *              the first coordinate of index 2, this function returns true. 
         *              If the coordinate of index 2 is greater, this function returns false.
         *              If both coordinates are the same, then the second coordinate is compared
         *              in the same way.
         *  @param[in]  ind1  Index object.
         *  @param[in]  ind2  Index object.
         *  @returns    The result of the comparison.
         */
        bool operator()(const index_type& ind1, const index_type& ind2) const;
    };

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an empty array.
     *  @param[in]  nullValue  Null value (value that is added to the array).
     */
    explicit SparseArray2D(const_reference nullValue = value_type(0));

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes a sparse array.
     *  @param[in]  rows  Number of rows.
     *  @param[in]  columns  Number of columns.
     *  @param[in]  nullValue  Null value (value that is added to the array).
     */
    SparseArray2D(size_type rows, size_type columns, const_reference nullValue = value_type(0));

    /**
     *  @brief      Copy constructor.
     *  @details    This constructor copies the contents of an object of the same type.
     *  @param[in]  other  Another object of the same type whose contents are copied.
     */
    SparseArray2D(const SparseArray2D<T, MapAlloc>& other);

    /**
     *  @brief      Move constructor.
     *  @details    This constructor moves the contents of an object to the new class instance.
     *  @param[in]  other  Another object of the same type whose contents are acquired.
     */
    SparseArray2D(SparseArray2D<T, MapAlloc>&& other) noexcept;
    
    ////////// Destructor //////////

    /**
     *  @brief      Destructor.
     *  @details    Class destructor. 
     */
    ~SparseArray2D() noexcept = default;

    ////////// Operators //////////        

    /**
     *  @brief      Assignment operator.
     *  @details    This operator copies the contents of an object of the same type.
     *  @param[in]  other  Another object of the same type whose contents are copied.
     *  @returns    A reference to the object.
     */
    SparseArray2D<T, MapAlloc>& operator=(const SparseArray2D<T, MapAlloc>& other);

    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator acquires the contents of another object.
     *  @param[in]  other  Another object of the same type whose contents are acquired.
     *  @returns    A reference to the object.
     */
    SparseArray2D<T, MapAlloc>& operator=(SparseArray2D<T, MapAlloc>&& other)  noexcept;

    /**
     *  @brief      Equality operator.
     *  @details    Two arrays are equal if both have the same size and each element
     *              of one array is equal to the element with the same index in the other array.
     *  @param[in]  right  Array to compare.
     *  @returns    True if both arrays are equal.
     */
    bool operator==(const SparseArray2D<T, MapAlloc>& right) noexcept(false);

    /**
     *  @brief      Inequality operator.
     *  @details    Two arrays are not equal if they have different sizes or the elements
     *              corresponding to one position are not equal.
     *  @param[in]  right  Array to compare.
     *  @returns    True if both arrays are not equal.
     */
    bool operator!=(const SparseArray2D<T, MapAlloc>& right);

    /**
     *  @brief      Array subscript.
     *  @details    This operator returns the specified element.
     *  @param[in]  i  Row index of the selected element.
     *  @param[in]  j  Column index of the selected element.
     *  @returns    The selected element.
     */
    const_reference operator()(size_type i, size_type j) const;

    ////////// Member functions //////////        

    /**
     *  @brief      Resizes the array.
     *  @details    This function modifies the size of the array. The original data contained in
     *              the array is released so that they can be used after calling this function.
     *  @param[in]  rows  Number of rows.
     *  @param[in]  columns  Number of columns.
     */
    void resize(size_type rows, size_type columns);
    
    /**
     *  @brief      Clear array.
     *  @details    This function releases the allocated memory.
     */
    void clear() noexcept;

    /**
     *  @brief      Copies another array.
     *  @details    This function copies the contents of other array.
     *  @param[in]  other  Array to copy.
     */
    void copy(const SparseArray2D<T, MapAlloc>& other);

    /**
     *  @brief      Number of rows.
     *  @details    This function returns the number of rows of the array. 
     *  @returns    Number of rows.
     */
    size_type rows() const noexcept;

    /**
     *  @brief      Number of columns.
     *  @details    This function returns the number of columns of the array. 
     *  @returns    Number of columns.
     */
    size_type columns() const noexcept;

    /**
     *  @brief      Returns the array size.
     *  @details    This function returns the number of elements in the array. 
     *  @returns    Number of elements.
     */
    size_type size() const noexcept;

    /**
     *  @brief      Number of non-null elements.
     *  @details    This function returns the number of non-null elements.
     *  @returns    Number of non-null elements.
     */
    size_type numberOfNonNullElements() const noexcept;

    /**
     *  @brief      Null value.
     *  @details    This function returns the value that is not added to the array.
     *  @returns    The null value.
     */
    const_reference nullValue() const noexcept;

    /**
     *  @brief      Object into the array.
     *  @details    This function returns a reference to the specified object. The function
     *              verifies whether the specified element is out of range.
     *  @param[in]  row  The row of the element to be returned.
     *  @param[in]  column  The column of the element to be returned.
     *  @returns    The selected object.
     */
    const_reference at(size_type row, size_type column) const;

    /**
     *  @brief      Modify object into the array.
     *  @details    This function modifies the value of one of the objects into the array.
     *  @param[in]  row  The row of the element to be modified.
     *  @param[in]  column  The column of the element to be modified.
     *  @param[in]  val  New value of the selected element.
     */
    void modify(size_type row, size_type column, const_reference val);

    /**
     *  @brief      To array.
     *  @details    This function transform the array into a non-sparse array.
     *  @returns    The array with the elements of the sparse array
     */
    Array2D<T> toArray() const;

    /**
     *  @brief      Get the elements of one row.
     *  @details    This function returns the elements of one row.
     *  @param[in]  row  The row of the elements to be returned.
     *  @returns    The array with the elements of the selected row.
     */
    Array<T> row(size_type row) const;

    /**
     *  @brief      Get the elements of one column.
     *  @details    This function returns the elements of one column.
     *  @param[in]  column  The column of the elements to be returned.
     *  @returns    The array with the elements of the selected column.
     */
    Array<T> column(size_type column) const;

    /**
     *  @brief      Find elements.
     *  @details    This function finds the indices of the indicated value.
     *  @param[in]  t  Value to be found.
     *  @returns    The array with the indices of the indicated value.
     */
    Array<index_type> find(const_reference t) const;

    /**
     *  @brief      Non-null elements.
     *  @details    This function returns the non-null elements of the array. 
     *  @returns    The array with the elements.
     */
    Array<std::pair<index_type, T>> nonNullElements() const;    

    ////////// I/O operations //////////

    /**
     *  @brief      Write array to an output stream.
     *  @details    This function writes an array to an output stream in binary format.
     *  @param[in, out] o  The output stream where the data will be written.
     */
    void write(std::ostream& o) const;

    /**
     *  @brief      Read array from an input stream.
     *  @details    This function reads an array from an input stream in binary format.
     *  @param[in, out] i  The input stream from where the data will be read.
     *  @returns    The object that was read from the input stream.
     */
    static SparseArray2D<T, MapAlloc> read(std::istream& i);

protected:

    ////////// Data members //////////        

    size_type nr_ {0};  /**< Number of rows. */

    size_type nc_ {0};  /**< Number of columns. */

    size_type n_ {0};   /**< Number of elements into the array. */

    std::map <index_type, value_type,
        IndexComparator, map_allocator_type > data_;    /**< The data stored in the container. */

    value_type nullValue_;  /**< Null value. */

private:
};

////////// Global operators //////////    

/**
 *  @brief      Input stream to array.
 *  @details    This operators reads the contents of an array from an input stream. 
 *              The data are read in binary format.
 *  @tparam     T  The data type to be stored in the array.
 *  @tparam     MapAlloc  The type of allocator to be used to build the array.
 *  @param[in, out] i  Input stream.
 *  @param[out] arr  Object where the data are stored.
 *  @returns    A reference to the stream.
 */
template<typename T, typename MapAlloc>
std::istream& operator>>(std::istream& i, SparseArray2D<T, MapAlloc>& arr);

/**
 *  @brief      Array to output stream.
 *  @details    This operators writes the contents of the array in an output stream.
 *  @tparam     T  The data type to be stored in the array.
 *  @tparam     MapAlloc  The type of allocator to be used to build the array.
 *  @param[in, out] o  Output stream.
 *  @param[in]  other  The object to be written.
 *  @returns    A reference to the stream.
 */
template<typename T, typename MapAlloc>
std::ostream& operator<<(std::ostream& o, const SparseArray2D<T, MapAlloc>& arr);

}

////////// Implementation of class template //////////
#include <nct/SparseArray2D_template.h> 

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
