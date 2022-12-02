//=================================================================================================================
/**
 *  @file       Array2D.h
 *  @brief      nct::Array2D class template.
 *  @details    Declaration of the nct::Array2D class template.
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

#ifndef NCT_ARRAY_2D_H_INCLUDE
#define NCT_ARRAY_2D_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/array_iterator.h>
#include <nct/Array.h>

#include <initializer_list>
#include <iostream>
#include <functional>

//=================================================================================================================
namespace nct {

////////// Type definitions //////////

template<typename T, typename Alloc = std::allocator<T>>
class Array2D;

/** Real matrix. */
using Matrix = nct::Array2D<double, std::allocator<double>>;

/** Complex matrix. */
using ComplexMatrix = nct::Array2D<nct::Complex, std::allocator<nct::Complex>>;

/**
 *  @brief      Real matrix function.
 *  @details    This function takes one real matrix and returns a real matrix.
 */
using MatrixFunction = std::function<Matrix(const Matrix&)>;

/**
 *  @brief      Complex matrix function.
 *  @details    This function takes one complex matrix and returns a complex matrix.
 */
using ComplexMatrixFunction = std::function<ComplexMatrix(const ComplexMatrix&)>;

/**
 *  @brief      Real vector-matrix function.
 *  @details    This function takes one real vector and returns a real matrix.
 */
using VectorMatrixFunction = std::function<Matrix(const RealVector&)>;

/**
 *  @brief      Complex vector-matrix function.
 *  @details    This function takes one complex vector and returns a complex matrix.
 */
using ComplexVectorMatrixFunction = std::function<ComplexMatrix(const ComplexVector&)>;

/**
 *  @brief      Real matrix-vector function.
 *  @details    This function takes one real matrix and returns a real vector.
 */
using MatrixVectorFunction = std::function<RealVector(const Matrix&)>;

/**
 *  @brief      Complex matrix-vector function.
 *  @details    This function takes one complex matrix and returns a complex vector.
 */
using ComplexMatrixVectorFunction = std::function<ComplexVector(const ComplexMatrix&)>;

////////// Classes ////////// 

/**
 *  @brief      Class template for 2-dimensional arrays of objects.
 *  @details    This class template is used to manipulate 2D arrays of objects. There are also
 *              matrix operations implemented in this class.
 *  @note       It is possible to disable index checking in the [] and () operators by defining
 *              NCT_ARRAY_2D_DISABLE_INDEX_CHECKING.
 *  @tparam     T  The data type to be stored in the array.
 *  @tparam     Alloc  The type of allocator to be used to build the array.
 */
template<typename T, typename Alloc>
class Array2D {

public:

    ////////// Type definitions //////////

    /** Base data type. */
    using value_type = T;

    /** Pointer. */
    using pointer = T*;

    /** Const pointer. */
    using const_pointer = const T*;

    /** Reference. */
    using reference = T&;

    /** Const reference. */
    using const_reference = const T&;

    /** R-value reference. */
    using rvalue_reference = T&&;

    /** Size type. */
    using size_type = size_t;

    /** Difference type. */
    using difference_type = diff_t;

    /** Allocator type. */
    using allocator_type = Alloc;

    /** Allocator traits. */
    using allocator_traits = std::allocator_traits<Alloc>;

    ////////// Iterators //////////

    /** Iterator. */
    using iterator = nct::array_iterator<Array2D<T, Alloc>, value_type,
        difference_type, pointer, reference>;

    /** Const iterator. */
    using const_iterator = nct::array_iterator < Array2D<T, Alloc>, const value_type,
        difference_type, const_pointer,
        const_reference >;

    /** Reverse iterator. */
    using reverse_iterator = std::reverse_iterator<iterator>;

    /** Const reverse iterator. */
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;


    ////////// Constructors //////////

    /**
     * @brief      Default constructor.
     * @details    This constructor initializes an empty array.
     * @param[in]  allocator  Allocator object. The container keeps and uses an internal copy of this
     *             allocator.                
     */
    explicit Array2D(const allocator_type& allocator = allocator_type())  noexcept;

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes a two-dimensional array.
     *  @param[in]  rows  Number of rows.
     *  @param[in]  columns  Number of columns.
     *  @param[in]  allocator  Allocator object. The container keeps and uses an internal copy of this
     *              allocator.
     */
    Array2D(size_type rows, size_type columns, const allocator_type& allocator = allocator_type());

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes an array and assigns to all the elements the specified value.
     *  @param[in]  rows  Number of rows.
     *  @param[in]  columns  Number of columns.
     *  @param[in]  val  Value that is taken by all the new elements inside the array.
     *  @param[in]  allocator  Allocator object. The container keeps and uses an internal copy of this
     *              allocator.
     */
    Array2D(size_type rows, size_type columns, const_reference val,
        const allocator_type& allocator = allocator_type());

    /**
     *  @brief      Copy constructor.
     *  @details    This constructor copies the contents of an object of the same type.
     *  @param[in]  other  Another object of the same type whose contents are copied.
     */
    Array2D(const Array2D<T, Alloc>& other);

    /**
     *  @brief      Copy constructor.
     *  @details    This constructor copies the contents of an object of the same type.
     *  @param[in]  other  Another object of the same type whose contents are copied.
     *  @param[in]  allocator  Allocator object. The container keeps and uses an internal copy of this
     *              allocator.
     */
    Array2D(const Array2D<T, Alloc>& other, const allocator_type& allocator);

    /**
     *  @brief      Move constructor.
     *  @details    This constructor moves the contents of an object to the new class instance.
     *  @param[in]  other  Another object of the same type whose contents are acquired.
     */
    Array2D(Array2D<T, Alloc>&& other) noexcept;

    /**
     *  @brief      Move constructor.
     *  @details    This constructor moves the contents of an object to the new class instance.
     *  @param[in]  other  Another object of the same type whose contents are acquired.
     *  @param[in]  allocator  Allocator object. The container keeps and uses an internal copy of this
     *              allocator.
     */
    Array2D(Array2D<T, Alloc>&& other, const allocator_type& allocator);

    ////////// Destructor //////////

    /**
     *  @brief      Destructor.
     *  @details    Class destructor.
     */
    ~Array2D() noexcept;

    ////////// Operators //////////        

    /**
     *  @brief      Assignment operator.
     *  @details    This operator copies the contents of an object of the same type.
     *  @param[in]  other  Another object of the same type whose contents are copied.
     *  @returns    A reference to the object.
     */
    Array2D<T, Alloc>& operator=(const Array2D<T, Alloc>& other);

    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator acquires the contents of another object.
     *  @param[in]  other  Another object of the same type whose contents are acquired.
     *  @returns    A reference to the object.
     */
    Array2D<T, Alloc>& operator=(Array2D<T, Alloc>&& other) noexcept;

    /**
     *  @brief      Array subscript.
     *  @details    This operator returns the specified element.
     *  @param[in]  i  Row index of the selected element.
     *  @param[in]  j  Column index of the selected element.
     *  @returns    The selected element.
     */
    reference operator()(size_type i, size_type j);

    /**
     *  @brief      Array subscript.
     *  @details    This operator returns the specified element.
     *  @param[in]  i  Row index of the selected element.
     *  @param[in]  j  Column index of the selected element.
     *  @returns    The selected element.
     */
    const_reference operator()(size_type i, size_type j) const;

    /**
     *  @brief      Array subscript.
     *  @details    This operator returns the specified element.
     *  @param[in]  i  Index of the selected element.
     *  @returns    The selected element.
     */
    reference operator[](size_type i);

    /**
     *  @brief      Array subscript.
     *  @details    This operator returns the specified element.
     *  @param[in]  i  Index of the selected element.
     *  @returns    The selected element.
     */
    const_reference operator[](size_type i) const;

    /**
     *  @brief      Array subscript.
     *  @details    This operator returns the specified element.
     *  @param[in]  i  Index of the selected element.
     *  @returns    The selected element.
     */
    reference operator()(size_type i);

    /**
     *  @brief      Array subscript.
     *  @details    This operator returns the specified element.
     *  @param[in]  i  Index of the selected element.
     *  @returns    The selected element.
     */
    const_reference operator()(size_type i) const;

    /**
     *  @brief      Equality operator.
     *  @details    Two arrays are equal if both have the same size and each element
     *              of one array is equal to the element with the same index in the other array.
     *  @param[in]  right  Array to compare.
     *  @returns    True if both arrays are equal.
     */
    template<typename = void> requires std::equality_comparable<T>
    bool operator==(const Array2D<T, Alloc>& right) const;

    /**
     *  @brief      Inequality operator.
     *  @details    Two arrays are not equal if have different same size or element
     *              of one array is not equal to the element with the same index in the other array.
     *  @param[in]  right  Array to compare.
     *  @returns    True if both arrays are not equal.
     */
    template<typename = void> requires std::equality_comparable<T>
    bool operator!=(const Array2D<T, Alloc>& right) const;

    /**
     *  @brief      Bitwise AND.
     *  @details    This operator performs the bitwise "and" operation for each index of the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires std::integral<T>
    Array2D<T, Alloc> operator&(const Array2D<T, Alloc>& right) const;

    /**
     *  @brief      Bitwise AND.
     *  @details    This operator performs the bitwise "and" operation for each index of the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires std::integral<T>
    const Array2D<T, Alloc>& operator&=(const Array2D<T, Alloc>& right);

    /**
     *  @brief      Bitwise OR.
     *  @details    This operator performs the bitwise "or" operation for each index of the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires std::integral<T>
    Array2D<T, Alloc> operator|(const Array2D<T, Alloc>& right) const;

    /**
     *  @brief      Bitwise OR.
     *  @details    This operator performs the bitwise "or" operation for each index of the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires std::integral<T>
    const Array2D<T, Alloc>& operator|=(const Array2D<T, Alloc>& right);

    /**
     *  @brief      Bitwise XOR.
     *  @details    This operator performs the bitwise "xor" operation for each index of the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires std::integral<T>
    Array2D<T, Alloc> operator^(const Array2D<T, Alloc>& right) const;

    /**
     *  @brief      Bitwise XOR.
     *  @details    This operator performs the bitwise "xor" operation for each index of the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires std::integral<T>
    const Array2D<T, Alloc>& operator^=(const Array2D<T, Alloc>& right);

    /**
     *  @brief      Unary plus.
     *  @details    This operator multiplies by one each element inside the array.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires nct::Numeric<T>
    Array2D<T, Alloc> operator+() const;

    /**
     *  @brief      Matrix sum.
     *  @details    This operator calculates the sum of two matrices.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires nct::Addable<T>
    Array2D<T, Alloc> operator+(const Array2D<T, Alloc>& right) const;

    /**
     *  @brief      Matrix sum.
     *  @details    This operator calculates the sum of two matrices and stores the result in the same 
     *              instance.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires nct::Addable<T>
    const Array2D<T, Alloc>& operator+=(const Array2D<T, Alloc>& right);

    /**
     *  @brief      Unary minus.
     *  @details    This operator multiplies by minus one each element inside the array.
     *  @returns    The array with the result of the operation.
     */    
    template<typename = void> requires nct::SignedNumeric<T>
    Array2D<T, Alloc> operator-() const;

    /**
     *  @brief      Matrix substraction.
     *  @details    This operator calculates the substraction of two matrices.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires nct::Substractable<T>
    Array2D<T, Alloc> operator-(const Array2D<T, Alloc>& right) const;

    /**
     *  @brief      Matrix substraction.
     *  @details    This operator calculates the substraction of two matrices and stores the result 
     *              in the same instance.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires nct::Substractable<T>
    const Array2D<T, Alloc>& operator-=(const Array2D<T, Alloc>& right);

    /**
     *  @brief      Matrix multiplication.
     *  @details    This operator calculates the product of two matrices.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires nct::Numeric<T>
    Array2D<T, Alloc> operator*(const Array2D<T, Alloc>& right) const;

    /**
     *  @brief      Matrix multiplication.
     *  @details    This operator calculates the multiplication of two matrices and stores the result in 
     *              the same instance.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires nct::Numeric<T>
    const Array2D<T, Alloc>& operator*=(const Array2D<T, Alloc>& right);

    /**
     *  @brief      Scalar product.
     *  @details    This operator calculates the product of the matrix with a scalar.
     *  @param[in]  right  Scalar value.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires nct::Numeric<T>
    Array2D<T, Alloc> operator*(const_reference right) const;

    /**
     *  @brief      Scalar product.
     *  @details    This operator calculates the multiplication of the matrix with a scalar and stores 
     *              the result in the same instance.
     *  @param[in]  right  Scalar value.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires nct::Numeric<T>
    const Array2D<T, Alloc>& operator*=(const_reference right);

    /**
     *  @brief      Scalar division.
     *  @details    This operator calculates the division of the matrix with a scalar.
     *  @param[in]  right  Scalar value.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires nct::Numeric<T>
    Array2D<T, Alloc> operator/(const_reference right) const;

    /**
     *  @brief      Scalar division.
     *  @details    This operator calculates the division of the matrix with a scalar and stores the 
     *              result in the same instance.
     *  @param[in]  right  Scalar value.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires nct::Numeric<T>
    const Array2D<T, Alloc>& operator/=(const_reference right);

    ////////// Basic member functions //////////        

    /**
     *  @brief      Clear array.
     *  @details    This function releases the allocated memory.
     */
    void clear() noexcept;

    /**
     *  @brief      Assigns contents to the array.
     *  @details    This function assigns new contents to the array, replacing its current
     *              contents, and modifying its size accordingly.
     *  @param[in]  rows  Number of rows.
     *  @param[in]  columns  Number of columns.
     *  @param[in]  val  Value that is taken by all the elements inside the array.
     */
    void assign(size_type rows, size_type columns, const_reference val);

    /**
     *  @brief      Resizes the array.
     *  @details    This function modifies the size of the array. The original data contained in
     *              the array keep their original positions and elements beyond the boundaries are
     *              erased. If new positions are added to the array, the new elements are set according
     *              to the default constructor.
     *  @param[in]  rows  Number of rows.
     *  @param[in]  columns  Number of columns.
     */
    void resize(size_type rows, size_type columns);

    /**
     *  @brief      Resizes the array.
     *  @details    This function modifies the size of the array. The original data contained in the array
     *              keep their original positions and elements beyond the boundaries are erased. If new
     *              positions are added to the array, the new elements are set to val.
     *  @param[in]  rows  Number of rows.
     *  @param[in]  columns  Number of columns.
     *  @param[in]  val  Value that is taken by all the new elements inside the array.
     */
    void resize(size_type rows, size_type columns, const_reference val);

    /**
     *  @brief      Gets the array allocator.
     *  @details    This function returns a copy of the allocator object that is used by the
     *              container.
     *  @returns    An allocator object.
     */
    allocator_type get_allocator() const;

    /**
     *  @brief      Fills the array with a constant value.
     *  @details    This function fills the array with the specified value.
     *  @param[in]  val  New value of all the array elements.
     */
    void fill(const_reference val);

    /**
     *  @brief      Change the shape of the array.
     *  @details    This function modifies the shape of the array. The size of the array must not
     *              change.
     *  @param[in]  rows  The new number of rows.
     *  @param[in]  columns  The new number of columns.
     */
    void reshape(size_type rows, size_type columns);

    /**
     *  @brief      Copies another array.
     *  @details    This function copies the contents of other array.
     *  @param[in]  other  Array to copy.
     */
    void copy(const Array2D<T, Alloc>& other);

    /**
     *  @brief      Is the array empty?
     *  @details    This function tests whether the array is empty.
     *  @returns    True, if the array is empty.
     */
    bool empty() const noexcept;

    /**
     *  @brief      Number of rows.
     *  @details    This function returns the number of rows of the array.
     *  @returns    The number of rows.
     */
    size_type rows() const noexcept;

    /**
     *  @brief      Number of columns.
     *  @details    This function returns the number of columns of the array.
     *  @returns    The number of columns.
     */
    size_type columns() const noexcept;

    /**
     *  @brief      Returns the array size.
     *  @details    This function returns the number of elements in the array.
     *  @returns    The number of elements.
     */
    size_type size() const noexcept;

    /**
     *  @brief      Transpose.
     *  @details    This function returns the transpose of the array.
     *  @returns    The transpose.
     */
    Array2D<T, Alloc> transpose() const;

    /**
     *  @brief      Pointer to the data.
     *  @details    This function returns the pointer that is used to allocate the data in the
     *              array.
     *  @note       Don't use this function unless is extremely necessary to access the data directly.
     *              Also, the returned pointer must never be released.
     *  @returns    The pointer to the data.
     */
    pointer data() noexcept;

    /**
     *  @brief      Const pointer to the data.
     *  @details    This function returns the pointer that is used to allocate the data in the
     *              array.
     *  @note       Don't use this function unless is extremely necessary to access the data directly.
     *              Also, the returned pointer must never be released.
     *  @returns    The pointer to the data.
     */
    const_pointer data() const noexcept;

    /**
     *  @brief      Pointer to one element.
     *  @details    This function returns the pointer to the address of one element in the array.
     *  @note       Don't use this function unless it's extremely necessary to access the data directly.
     *              Also, the returned pointer must never be released.
     *  @param[in]  index  The index of the object to be returned.
     *  @returns    The pointer to the selected item.
     */
    pointer data(size_type index);

    /**
     *  @brief      Const pointer to one element.
     *  @details    This function returns the pointer to the address of one element in the array.
     *  @note       Don't use this function unless it's extremely necessary to access the data directly.
     *              Also, the returned pointer must never be released.
     *  @param[in]  index  The index of the object to be returned.
     *  @returns    The pointer to the selected item.
     */
    const_pointer data(size_type index) const;

    /**
     *  @brief      Pointer to one element.
     *  @details    This function returns the pointer to the address of one element in the array.
     *  @note       Don't use this function unless is extremely necessary to access the data directly.
     *              Also, the returned pointer must never be released.
     *  @param[in]  row  The row of the element to be returned.
     *  @param[in]  column  The column of the element to be returned.
     *  @returns    The pointer to the selected item.
     */
    pointer data(size_type row, size_type column);

    /**
     *  @brief      Const pointer to one element.
     *  @details    This function returns the pointer to the address of one element in the array.
     *  @note       Don't use this function unless is extremely necessary to access the data directly.
     *              Also, the returned pointer must never be released.
     *  @param[in]  row  The row of the element to be returned.
     *  @param[in]  column  The column of the element to be returned.
     *  @returns    The pointer to the selected item.
     */
    const_pointer data(size_type row, size_type column) const;

    /**
     *  @brief      Reference to one element.
     *  @details    This function returns a reference to the specified object. The function
     *              verifies whether the index is out of range.
     *  @param[in]  index  The index of the object to be returned.
     *  @returns    The chosen object.
     */
    reference at(size_type index);

    /**
     *  @brief      const reference to one element.
     *  @details    This function returns a reference to the specified object. The function
     *              verifies whether the index is out of range.
     *  @param[in]  index  The index of the object to be returned.
     *  @returns    The chosen object.
     */
    const_reference at(size_type index) const;

    /**
     *  @brief      Reference to one element.
     *  @details    This function returns a reference to the specified object. The function
     *              verifies whether the specified element is out of range.
     *  @param[in]  row  The row of the element to be returned.
     *  @param[in]  column  The column of the element to be returned.
     *  @returns    The chosen object.
     */
    reference at(size_type row, size_type column);

    /**
     *  @brief      Reference to one element.
     *  @details    This function returns a reference to the specified object. The function
     *              verifies whether the specified element is out of range.
     *  @param[in]  row  The row of the element to be returned.
     *  @param[in]  column  The column of the element to be returned.
     *  @returns    The chosen object.
     */
    const_reference at(size_type row, size_type column) const;

    /**
     *  @brief      Memory offset.
     *  @details    This function returns the offset inside the memory block that corresponds
     *              to the specified row. This function doesn't verify whether the specified
     *              index is valid for the current instance.
     *  @param[in]  row  Row index.
     *  @returns    The offset of the specified index.
     */
    size_type offset(size_type row) const noexcept;

    /**
     *  @brief      Memory offset.
     *  @details    This function returns the offset inside the memory block that corresponds
     *              to the specified row and column. This function doesn't verify whether the specified
     *              indices are valid for the current instance.
     *  @param[in]  row  Row index.
     *  @param[in]  column  Column index.
     *  @returns    The offset of the specified indices.
     */
    size_type offset(size_type row, size_type column) const noexcept;

    /**
     *  @brief      First element of the container.
     *  @details    This function returns a reference to the first element in the array.
     *  @returns    The first element.
     */
    reference front();

    /**
     *  @brief      First element of the container.
     *  @details    This function returns a reference to the first element in the array.
     *  @returns    The first element.
     */
    const_reference front() const;

    /**
     *  @brief      Last element of the container.
     *  @details    This function returns a reference to the last element in the array.
     *  @returns    The last element.
     */
    reference back();

    /**
     *  @brief      Last element of the container.
     *  @details    This function returns a reference to the last element in the array.
     *  @returns    The last element.
     */
    const_reference back() const;

    /**
     *  @brief      Find indices.
     *  @details    This function returns an array with the positions that are equal to "t".
     *  @tparam     Container  The type of output container.
     *  @param[in]  t  The value to be found.
     *  @returns    A container with the indices of the found items.
     */
    template<typename Container = Array<size_type>>
    Container find(const_reference t) const;

    /**
     *  @brief      To array.
     *  @details    This function creates a new array of different data type. The new array
     *              is a copy of the original, but the data are casted to other data type if it's
     *              possible.
     *  @tparam     U  The data type to be used to store the result.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @returns    The new array.
     */
    template<typename U, typename AllocU = std::allocator<U>>
    Array2D<U, AllocU> toArray() const;

    ////////// Data insertions and deletions //////////    

    /**
     *  @brief      Insert row.
     *  @details    This function inserts one new row.
     *  @tparam     InputIt  The type of iterator of the input data.
     *  @param[in]  row  Index where the new row will be inserted.
     *  @param[in]  first  Beginning of the range with the elements of the new row.
     *  @param[in]  last  End of the range with the elements of the new row.
     *  @returns    An interator pointing to the first element of the new row
     *              that visits only this row.
     */
    template<std::random_access_iterator InputIt>
    iterator insertRow(size_type row, InputIt first, InputIt last);

    /**
     *  @brief      Insert row.
     *  @details    This function inserts one new row.
     *  @param[in]  row  Index where the new row will be inserted.
     *  @param[in]  il  Initializer list with the elements of the new row.
     *  @returns    An interator pointing to the first element of the new row
     *              that visits only this row.
     */
    iterator insertRow(size_type row, std::initializer_list<value_type> il);

    /**
     *  @brief      Insert row.
     *  @details    This function inserts one new row.
     *  @param[in]  row  Index where the new row will be inserted.
     *  @param[in]  data  Elements of the new row.
     *  @returns    An interator pointing to the first element of the new row
     *              that visits only this row.
     */
    iterator insertRow(size_type row, const Array<T, Alloc>& data);

    /**
     *  @brief      Erase row.
     *  @details    This function removes one row.
     *  @param[in]  row  Index of the row to eliminate.
     *  @returns    An interator pointing to the first element of the next row
     *              after the erased one.
     */
    iterator eraseRow(size_type row);

    /**
     *  @brief      Insert rows.
     *  @details    This function inserts multiple rows.
     *  @param[in]  row  Index where the new rows will be inserted.
     *  @param[in]  data  Data of the new rows.
     *  @returns    An interator pointing to the first element of the first new
     *              inserted row.
     */
    iterator insertRows(size_type row, const Array2D<T, Alloc>& data);

    /**
     *  @brief      Erase rows.
     *  @details    This function removes a range of rows.
     *  @param[in]  first  Index of the first row to remove.
     *  @param[in]  last  Index of the last row to remove.
     *  @returns    An interator pointing to the first element of the next row
     *              after the erased ones.
     */
    iterator eraseRows(size_type first, size_type last);

    /**
     *  @brief      Erase rows.
     *  @details    This function removes the rows that are specified in the range [first, last).
     *              The range indicates the indices of the rows to erase from the container.
     *  @tparam     IndexIt  The iterator type to be used to indicate the indices.
     *  @param[in]  first  Beginning of the range that indicates the rows to be removed.
     *  @param[in]  last  End of the range that indicates the rows to be removed.
     */
    template<std::random_access_iterator IndexIt>
    void eraseRows(IndexIt first, IndexIt last);

    /**
     *  @brief      Insert column.
     *  @details    This function inserts one new column.
     *  @tparam     InputIt  The type of iterator of the input data.
     *  @param[in]  column  Index where the new column will be inserted.
     *  @param[in]  first  Beginning of the range with the elements of the new column.
     *  @param[in]  last  End of the range with the elements of the new column.
     *  @returns    An interator pointing to the first element of the new column
     *              that visits only this row.
     */
    template<std::random_access_iterator InputIt>
    iterator insertColumn(size_type column, InputIt first, InputIt last);

    /**
     *  @brief      Insert column.
     *  @details    This function inserts one new column.
     *  @param[in]  column  Index where the new column will be inserted.
     *  @param[in]  il  Initializer list with the elements of the new column.
     *  @returns    An interator pointing to the first element of the new column
     *              that visits only this row.
     */
    iterator insertColumn(size_type column, std::initializer_list<value_type> il);

    /**
     *  @brief      Insert column.
     *  @details    This function inserts one new column.
     *  @param[in]  column  Index where the new column will be inserted.
     *  @param[in]  data  Elements of the new column.
     *  @returns    An interator pointing to the first element of the new column
     *              that visits only this row.
     */
    iterator insertColumn(size_type column, const Array<T, Alloc>& data);

    /**
     *  @brief      Erase column.
     *  @details    This function removes one column.
     *  @param[in]  column  Index of the column to eliminate.
     *  @returns    An interator pointing to the first element of the next column
     *              after the erased one.
     */
    iterator eraseColumn(size_type column);

    /**
     *  @brief      Insert columns.
     *  @details    This function inserts multiple columns.
     *  @param[in]  row  Index where the new columns will be inserted.
     *  @param[in]  data  Data of the new columns.
     *  @returns    An interator pointing to the first element of the first
     *              new inserted column.
     */
    iterator insertColumns(size_type column, const Array2D<T, Alloc>& data);

    /**
     *  @brief      Erase columns.
     *  @details    This function removes a range of columns.
     *  @param[in]  first  Index of the first column to remove.
     *  @param[in]  last  Index of the last column to remove.
     *  @returns    An interator pointing to the first element of the next column
     *              after the erased ones.
     */
    iterator eraseColumns(size_type first, size_type last);

    /**
     *  @brief      Erase columns.
     *  @details    This function removes the columns that are specified in the range [first,
     *              last). The range indicates the indices of the columns to erase from the container.
     *  @tparam     IndexIt  The iterator type to be used to indicate the indices.
     *  @param[in]  first  Beginning of the range that indicates the columns to be removed.
     *  @param[in]  last  End of the range that indicates the columns to be removed.
     */
    template<std::random_access_iterator IndexIt>
    void eraseColumns(IndexIt first, IndexIt last);

    ////////// Data selection //////////

    /**
     *  @brief      Row. elements.
     *  @details    This function returns a new array with the elements of the specified row.
     *  @param[in]  row  Row index.
     *  @returns    The new array with the selected data.
     */
    Array<T, Alloc> rowElements(size_type row) const;

    /**
     *  @brief      Column elements.
     *  @details    This function returns a new array with the elements of the specified column.
     *  @param[in]  column  Column index.
     *  @returns    The new array with the selected data.
     */
    Array<T, Alloc> columnElements(size_type column) const;

    /**
     *  @brief      Select range.
     *  @details    This function returns an array with the elements that are into the specified 
     *              range of indices.
     *  @param[in]  first  Index of the first element to be copied.
     *  @param[in]  last  Index of the last element to be copied.
     *  @returns    The new array with the selected data.
     */
    Array<T, Alloc> selectRange(size_type first, size_type last) const;

    /**
     *  @brief      Select range.
     *  @details    This function returns an array with the elements that are into the specified
     *              range [first, last).
     *  @param[in]  first  Beginning of the range of elements to be copied.
     *  @param[in]  last  End of the range of elements to be copied.
     *  @returns    The new array with the selected data.
     */
    Array<T, Alloc> selectRange(const_iterator first, const_iterator last) const;

    /**
     *  @brief      Select items.
     *  @details    This function returns the elements that are specified in the range [first,
     *              last). The range indicates the indices of the elements to be copied.
     *  @tparam     IndexIt  The iterator type to be used to indicate the indices.
     *  @param[in]  first  Beginning of the range of indices.
     *  @param[in]  last  End of the range of indices.
     *  @returns    The new array with the selected data.
     */
    template<std::random_access_iterator IndexIt>
    Array<T, Alloc> selectData(IndexIt first, IndexIt last) const;

    /**
     *  @brief      Select items.
     *  @details    This function returns the elements that are specified in the input parameters.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  indices  Indices of the elements to be returned by this function.
     *  @returns    The new array with the selected data.
     */
    template<typename AllocU>
    Array<T, Alloc> selectData(const Array<size_type, AllocU>& indices) const;

    /**
     *  @brief      Select sub-array.
     *  @details    This function returns an array with the elements that are into the specified
     *              range of rows and columns.
     *  @param[in]  firstRow  Index of the first row to be copied.
     *  @param[in]  lastRow  Index of the last row to be copied.
     *  @param[in]  firstCol  Index of the first column to be copied.
     *  @param[in]  lastCol  Index of the last column to be copied.
     *  @returns    The new array with the selected data.
     */
    Array2D<T, Alloc> selectSubArray(
        size_type firstRow, size_type lastRow,
        size_type firstCol, size_type lastCol) const;

    /**
     *  @brief      Select indices.
     *  @details    This function returns an array with the selected rows and columns specified by
     *              the ranges [firstRow, lastRow) and [firstCol, lastCol). The ranges indicate the
     *              indices of the rows and columns to be copied.
     *  @tparam     RowIndexIt  The type of iterator used to traverse the row indices.
     *  @tparam     ColumnIndexIt  The type of iterator used to traverse the column indices.
     *  @param[in]  firstRow  Beginning of the range of row indices.
     *  @param[in]  lastRow  End of the range of row indices.
     *  @param[in]  firstCol  Beginning of the range of column indices.
     *  @param[in]  lastCol  End of the range of column indices.
     *  @returns    The new array with the selected data.
     */
    template<std::random_access_iterator RowIndexIt, std::random_access_iterator ColumnIndexIt>
    Array2D<T, Alloc> selectIndices(RowIndexIt firstRow, RowIndexIt lastRow,
        ColumnIndexIt firstCol, ColumnIndexIt lastCol) const;

    /**
     *  @brief      Select indices.
     *  @details    This function returns an array with the selected rows and columns specified
     *              in the input parameters.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  rows  Indices of the selected rows.
     *  @param[in]  columns  Indices of the selected columns.
     *  @returns    The new array with the selected data.
     */
    template<typename AllocU>
    Array2D<T, Alloc> selectIndices(const Array<size_type, AllocU>& rows,
        const Array<size_type, AllocU>& columns) const;

    /**
     *  @brief      Select row.
     *  @details    This function returns a new array with the elements of the specified row.
     *  @param[in]  row  Row index.
     *  @returns    The new array with the selected data.
     */
    Array2D<T, Alloc> selectRow(size_type row) const;

    /**
     *  @brief      Select range of rows.
     *  @details    This function returns a range of rows.
     *  @param[in]  first  First row of the selected range.
     *  @param[in]  last  Last row of the selected range.
     *  @returns    The new array with the selected data.
     */
    Array2D<T, Alloc> selectRangeOfRows(size_type first, size_type last) const;

    /**
     *  @brief      Select rows.
     *  @details    This function returns the rows that are specified in the range [first, last).
     *              The range indicates the indices of the rows to be copied.
     *  @tparam     IndexIt  The iterator type to be used to indicate the indices.
     *  @param[in]  first  Beginning of the range of indices.
     *  @param[in]  last  End of the range of indices.
     *  @returns    The new array with the selected data.
     */
    template<std::random_access_iterator IndexIt>
    Array2D<T, Alloc> selectRows(IndexIt first, IndexIt last) const;

    /**
     *  @brief      Select rows.
     *  @details    This function returns the rows that are specified in the input parameters.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  rows  Indices of the selected rows.
     *  @returns    The new array with the selected data.
     */
    template<typename AllocU>
    Array2D<T, Alloc> selectRows(const Array<size_type, AllocU>& rows) const;

    /**
     *  @brief      Select column.
     *  @details    This function returns a new array with the elements of the specified column.
     *  @param[in]  column  Column index.
     *  @returns    The new array with the selected data.
     */
    Array2D<T, Alloc> selectColumn(size_type column) const;

    /**
     *  @brief      Select range of columns.
     *  @details    This function returns a range of columns.
     *  @param[in]  first  First column of the selected range.
     *  @param[in]  last  Last column of the selected range.
     *  @returns    The new array with the selected data.
     */
    Array2D<T, Alloc> selectRangeOfColumns(size_type first, size_type last) const;

    /**
     *  @brief      Select columns.
     *  @details    This function returns the columns that are specified in the range [first,
     *              last). The range indicates the indices of the columns to be copied.
     *  @tparam     IndexIt  The iterator type to be used to indicate the indices.
     *  @param[in]  first  Beginning of the range of indices.
     *  @param[in]  last  End of the range of indices.
     *  @returns    The new array with the selected data.
     */    
    template <std::random_access_iterator IndexIt>
    Array2D<T, Alloc> selectColumns(IndexIt first, IndexIt last) const;

    /**
     *  @brief      Select columns.
     *  @details    This function returns the columns that are specified in the input parameters.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  columns  Indices of the selected columns.
     *  @returns    The new array with the selected data.
     */
    template<typename AllocU>
    Array2D<T, Alloc> selectColumns(const Array<size_type, AllocU>& columns) const;

    ////////// Circular shifts //////////

    /**
     *  @brief      Circular row shift.
     *  @details    This function circularly shifts the rows of the array. The new first row of the array
     *              is specified in the arguments.
     *  @param[in]  i0  Index of the new first row.
     */
    Array2D<T, Alloc> circularRowShift(difference_type i0) const;

    /**
     *  @brief      Circular column shift.
     *  @details    This function circularly shifts the columns of the array.  The new first column of
     *              the array is specified in the arguments.
     *  @param[in]  j0  Index of the new first column.
     */
    Array2D<T, Alloc> circularColumnShift(difference_type j0) const;

    /**
     *  @brief      Circular shift.
     *  @details    This function circularly shifts the values in the array (rows and columns). The new
     *              element of index (0, 0) is specified in the arguments.
     *  @param[in]  i0  The row of the new first element.
     *  @param[in]  j0  The column of the new first element.
     */
    Array2D<T, Alloc> circularShift(difference_type i0, difference_type j0) const;

    /**
     *  @brief      Circular shift.
     *  @details    This function circularly shifts the values of the array by (nr/2, nc/2) (the element
     *              indexed by (0, 0) is moved to (nr/2, nc/2)).
     */
    Array2D<T, Alloc> circularShift() const;

    /**
     *  @brief      Inverse circular shift.
     *  @details    This function undo the circular shift performed by circularShift().
     */
    Array2D<T, Alloc> circularInvShift() const;

    ////////// Numerical operations //////////

    /**
     *  @brief      Trace.
     *  @details    This function computes the matrix trace, if the array is square.
     *  @returns    The matrix trace.
     */
    template<typename = void> requires nct::Addable<T>
    value_type trace() const;

    /**
     *  @brief      Sum.
     *  @details    This function computes the total sum of the elements of the array.
     *  @returns    The total sum.
     */
    template<typename = void> requires nct::Addable<T>
    value_type sum() const;

    /**
     *  @brief      Casted sum.
     *  @details    This function transforms each element to a double and then computes the total sum of the
     *              transformed elements.
     *  @returns    The total sum.
     */
    template<typename = void> requires nct::Arithmetic<T>
    double castSum() const;

    /**
     *  @brief      Squared norm.
     *  @details    This function computes the squared norm of the elements of the array.
     *  @returns    The squared norm.
     */
    template<typename = void> requires nct::Numeric<T>
    value_type squaredNorm() const;

    /**
     *  @brief      Euclidean norm.
     *  @details    This function computes the euclidian norm of the elements of the array.
     *  @returns    The euclidian norm.
     */
    template<typename = void> requires nct::Numeric<T>
    double euclideanNorm() const;

    /**
     *  @brief      Vectorial LP-norm.
     *  @details    This function computes the vectorial LP-norm of the array.
     *  @param[in]  p  Norm to be calculated.
     *  @returns    The norm of the array.
     */
    template<typename = void> requires nct::Numeric<T>
    double lpNorm(double p) const;

    /**
     *  @brief      Infinity norm.
     *  @details    This function computes the Infinity norm of the array.
     *  @returns    The infinity norm of the array.
     */
    template<typename = void> requires nct::Numeric<T>
    double infinityNorm() const;

    /**
     *  @brief      Mean.
     *  @details    This function returns the mean value of the elements into the array.
     *  @returns    The mean.
     */
    template<typename = void> requires nct::Arithmetic<T>
    double mean() const;

    /**
     *  @brief      Variance.
     *  @details    This function returns the sample variance of the elements into the array.
     *  @returns    The sample variance.
     */
    template<typename = void> requires nct::Arithmetic<T>
    double variance() const;

    /**
     *  @brief      Maximum.
     *  @details    This function computes the maximum element of the array.
     *  @returns    The maximum element.
     */
    template<typename = void> requires std::totally_ordered<T>
    value_type max() const;

    /**
     *  @brief      Minimum.
     *  @details    This function computes the minimum element of the array.
     *  @returns    The minimum element.
     */
    template<typename = void> requires std::totally_ordered<T>
    value_type min() const;

    /**
     *  @brief      Minimum of each column.
     *  @details    This function calculates the minimum value of each column of the array.
     *  @returns    The new array with the values of the operation.
     */
    template<typename = void> requires std::totally_ordered<T>
    Array2D<T, Alloc> minCol() const;

    /**
     *  @brief      Minimum of one column.
     *  @details    This function returns the minimum value of the selected column.
     *  @param[in]  column  Column index.
     *  @returns    The minimum value.
     */
    template<typename = void> requires std::totally_ordered<T>
    value_type minCol(size_type column) const;

    /**
     *  @brief      Minimum of each row.
     *  @details    This function calculates the minimum values of each row of the array.
     *  @returns    The new array with the values of the operation.
     */
    template<typename = void> requires std::totally_ordered<T>
    Array2D<T, Alloc> minRow() const;

    /**
     *  @brief      Minimum of one row.
     *  @details    This function returns the minimum value of the selected row.
     *  @param[in]  row  Row index.
     *  @returns    The minimum value.
     */
    template<typename = void> requires std::totally_ordered<T>
    value_type minRow(size_type row) const;

    /**
     *  @brief      Maximum of each column.
     *  @details    This function calculates the maximum values of each column of the array.
     *  @returns    The new array with the values of the operation.
     */
    template<typename = void> requires std::totally_ordered<T>
    Array2D<T, Alloc> maxCol() const;

    /**
     *  @brief      Maximum of one column.
     *  @details    This function returns the maximum value of the selected column.
     *  @param[in]  column  Column index.
     *  @returns    The maximum value.
     */
    template<typename = void> requires std::totally_ordered<T>
    value_type maxCol(size_type column) const;

    /**
     *  @brief      Maximun of each row.
     *  @details    This function calculates the maximum values of each row of the array.
     *  @returns    The new array with the values of the operation.
     */
    template<typename = void> requires std::totally_ordered<T>
    Array2D<T, Alloc> maxRow() const;

    /**
     *  @brief      Maximum of one row.
     *  @details    This function returns the maximum value of the selected row.
     *  @param[in]  row  Row index.
     *  @returns    The maximum value.
     */
    template<typename = void> requires std::totally_ordered<T>
    value_type maxRow(size_type row) const;

    /**
     *  @brief      Sum of each column.
     *  @details    This function calculates the sum of the elements of each column of the array.
     *  @returns    The new array with the values of the operation.
     */
    template<typename = void> requires nct::Numeric<T>
    Array2D<T, Alloc> sumCol() const;

    /**
     *  @brief      Sum of one column.
     *  @details    This function returns the sum of the selected column.
     *  @param[in]  column  Column index.
     *  @returns    The sum.
     */
    template<typename = void> requires nct::Numeric<T>
    value_type sumCol(size_type column) const;

    /**
     *  @brief      Sum of each row.
     *  @details    This function calculates the sum of the element of each row of the array.
     *  @returns    The new array with the values of the operation.
     */
    template<typename = void> requires nct::Numeric<T>
    Array2D<T, Alloc> sumRow() const;

    /**
     *  @brief      Sum of one row.
     *  @details    This function returns the sum of the selected row.
     *  @param[in]  row  Row index.
     *  @returns    The sum.
     */
    template<typename = void> requires nct::Numeric<T>
    value_type sumRow(size_type row) const;

    /**
     *  @brief      Mean of each column.
     *  @details    This function calculates the mean of the elements of each column of the array.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @returns    The new array with the values of the operation.
     */
    template<typename AllocU = std::allocator<double>> requires nct::Arithmetic<T>
    Array2D<double, AllocU> meanCol() const;

    /**
     *  @brief      Mean of one column.
     *  @details    This function returns the mean of the selected column.
     *  @param[in]  column  Column index.
     *  @returns    The mean value.
     */
    template<typename = void> requires nct::Arithmetic<T>
    double meanCol(size_type column) const;

    /**
     *  @brief      Mean of each row.
     *  @details    This function calculates the mean of the elements of each row of the array.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @returns    The new array with the values of the operation.
     */
    template<typename AllocU = std::allocator<double>> requires nct::Arithmetic<T>
    Array2D<double, AllocU> meanRow() const;

    /**
     *  @brief      Mean of one row.
     *  @details    This function returns the mean of the selected row.
     *  @param[in]  row  Row index.
     *  @returns    The mean value.
     */
    template<typename = void> requires nct::Arithmetic<T>
    double meanRow(size_type row) const;

    /**
     *  @brief      Sample variance of each column.
     *  @details    This function calculates the sample variance of the elements of each
     *              column of the array.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @returns    The new array with the values of the operation.
     */
    template<typename AllocU = std::allocator<double>> requires nct::Arithmetic<T>
    Array2D<double, AllocU> varCol() const;

    /**
     *  @brief      Variance of one column.
     *  @details    This function returns the sample variance of the selected column.
     *  @param[in]  column  Column index.
     *  @returns    The variance.
     */
    template<typename = void> requires nct::Arithmetic<T>
    double varCol(size_type column) const;

    /**
     *  @brief      Sample variance of each row.
     *  @details    This function calculates the sample variance of the elements of each row of
     *              the array.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @returns    The new array with the values of the operation.
     */
    template<typename AllocU = std::allocator<double>> requires nct::Arithmetic<T>
    Array2D<double, AllocU> varRow() const;

    /**
     *  @brief      Variance of one row.
     *  @details    This function returns the sample variance of the selected row.
     *  @param[in]  row  Row index.
     *  @returns    The mean value.
     */
    template<typename = void> requires nct::Arithmetic<T>
    double varRow(size_type row) const;

    /**
     *  @brief      Covariance matrix.
     *  @details    This function calculates the sample covariance matrix of the array. Each row 
     *              corresponds to one observation and each column corresponds to one variable.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @returns    The covariance matrix.
     */
    template<typename AllocU = std::allocator<double>> requires nct::Arithmetic<T>
    Array2D<double, AllocU> covariance() const;

    /**
     *  @brief      Regularized covariance matrix.
     *  @details    This function returns a regularized version of the sample covariance matrix
     *              using the algorithm proposed by Olivier Ledoit and Michael Wolf. Each row corresponds
     *              to one observation and each column corresponds to one variable.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @returns    The covariance matrix.
     */
    template<typename AllocU = std::allocator<double>> requires nct::Arithmetic<T>
    Array2D<double, AllocU> regularizedCovariance() const;

    ////////// Special arrays //////////

    /**
     *  @brief      Is upper triangular?
     *  @details    This function indicates whether the array is an upper triangular matrix.
     *  @returns    True, if the array is an upper triangular matrix.
     */
    template<typename = void> requires std::equality_comparable<T>
    bool isUpperTriangular() const;

    /**
     *  @brief      Is lower triangular?
     *  @details    This function indicates whether the array is a lower triangular matrix.
     *  @returns    True, if the array is a lower triangular matrix.
     */
    template<typename = void> requires std::equality_comparable<T>
    bool isLowerTriangular() const;

    /**
     *  @brief      Is symmetric?
     *  @details    This function indicates whether the array is a symmetric matrix.
     *  @returns    True, if the array is symmetric matrix.
     */
    template<typename = void> requires std::equality_comparable<T>
    bool isSymmetric() const;

    /**
     *  @brief      Is diagonal?
     *  @details    This function indicates whether the array is diagonal matrix.
     *  @returns    True, if the array is a diagonal matrix.
     */
    template<typename = void> requires std::equality_comparable<T>
    bool isDiagonal() const;

    /**
     *  @brief      Is scalar?
     *  @details    This function indicates whether the array is a scalar matrix.
     *  @returns    True, if the array is a scalar matrix.
     */
    template<typename = void> requires std::equality_comparable<T>
    bool isScalar() const;

    /**
     *  @brief      Is Toeplitz?
     *  @details    This function indicates whether the array is a Toeplitz matrix.
     *  @returns    True, if the array is a Toeplitz matrix.
     */
    template<typename = void> requires std::equality_comparable<T>
    bool isToeplitz() const;

    /**
     *  @brief      Is Hankel?
     *  @details    This function indicates whether the array is a Hankel matrix.
     *  @returns    True, if the array is a Hankel matrix.
     */
    template<typename = void> requires std::equality_comparable<T>
    bool isHankel() const;

    /**
     *  @brief      Is Circulant?
     *  @details    This function indicates whether the array is a circulant matrix.
     *  @returns    True, if the array is a circulant matrix.
     */
    template<typename = void> requires std::equality_comparable<T>
    bool isCirculant() const;

    /**
     *  @brief      Constant.
     *  @details    This function creates an array and fills it with a constant value.
     *  @param[in]  rows  Rows of the array.
     *  @param[in]  columns  Columns of the array.
     *  @param[in]  t  Constant value.
     *  @returns    The new array.
     */
    static Array2D<T, Alloc> constant(size_type rows, size_type columns, const_reference t);

    /**
     *  @brief      Zeros.
     *  @details    This function creates an array of zeros.
     *  @param[in]  rows  Rows of the array.
     *  @param[in]  columns  Columns of the array.
     *  @returns    The new array.
     */
    template<typename = void> requires nct::Numeric<T>
    static Array2D<T, Alloc> zeros(size_type rows, size_type columns);

    /**
     *  @brief      Ones.
     *  @details    This function creates an array of ones.
     *  @param[in]  rows  Rows of the array.
     *  @param[in]  columns  Columns of the array.
     *  @returns    The new array.
     */
    template<typename = void> requires nct::Numeric<T>
    static Array2D<T, Alloc> ones(size_type rows, size_type columns);    

    /**
     *  @brief      Identity matrix.
     *  @details    This function creates an identity matrix of size n*n.
     *  @param[in]  n  Size of the identity matrix.
     *  @returns    The identity matrix.
     */
    template<typename = void> requires nct::Numeric<T>
    static Array2D<T, Alloc> eye(size_type n);

    /**
     *  @brief      Identity matrix.
     *  @details    This function creates an identity matrix of size rows*columns. All the elements on the
     *              main diagonal are set to one and the rest are set to zero.
     *  @param[in]  rows  Number of rows of the matrix.
     *  @param[in]  columns  Number of columns of the matrix.
     *  @returns    The identity matrix.
     */
    template<typename = void> requires nct::Numeric<T>
    static Array2D<T, Alloc> eye(size_type rows, size_type columns);

    /**
     *  @brief      Diagonal matrix.
     *  @details    This function creates a diagonal matrix taking the elements of an array that
     *              contains the elements of the main diagonal.
     *  @tparam     U  The type used to define the input array.
     *  @tparam     AllocU  The type of allocator used to build the input array.
     *  @param[in]  w  Array with the elements to write on the matrix diagonal.
     *  @returns    The diagonal matrix.
     */
    template<typename U, typename AllocU> requires std::convertible_to<U, T>
    static Array2D<T, Alloc> diag(const Array<U, AllocU>& w);

    /**
     *  @brief      Diagonal matrix.
     *  @details    This function creates a diagonal matrix taking the elements of an array that
     *              contains the elements of the main diagonal.
     *  @tparam     U  The data type used to define the input array.
     *  @tparam     AllocU  The type of allocator used to build the input array.
     *  @param[in]  rows  Number of rows of the matrix.
     *  @param[in]  columns  Number of columns of the matrix.
     *  @param[in]  w  Array with the elements to write on the matrix diagonal.
     *  @returns    The diagonal matrix.
     */
    template<typename U, typename AllocU> requires std::convertible_to<U, T>
    static Array2D<T, Alloc> diag(size_type rows, size_type columns, const Array<U, AllocU>& w);

    /**
     *  @brief      Toeplitz matrix.
     *  @details    This function creates a symmetric Toeplitz matrix using the elements of an array that contains
     *              the elements of the first row of the matrix.
     *  @tparam     U  The data type used to define the input array.
     *  @tparam     AllocU  The type of allocator used to build the input array.
     *  @param[in]  r  The first row of the matrix.
     *  @returns    The new Toeplitz matrix.
     */
    template<typename U, typename AllocU> requires std::convertible_to<U, T>
    static Array2D<T, Alloc> toeplitz(const Array<U, AllocU>& r);

    /**
     *  @brief      Toeplitz matrix.
     *  @details    This function creates a Toeplitz matrix.
     *  @tparam     U  The data type used to define the input arrays.
     *  @tparam     AllocU  The type of allocator used to build the input arrays.
     *  @param[in]  c  The first column of the matrix.
     *  @param[in]  r  The first row of the matrix.
     *  @returns    The new Toeplitz matrix.
     */
    template<typename U, typename AllocU> requires std::convertible_to<U, T>
    static Array2D<T, Alloc> toeplitz(const Array<U, AllocU>& c, const Array<U, AllocU>& r);

    /**
     *  @brief      Hankel matrix.
     *  @details    This function creates a symmetric Hankel matrix taking the elements of an array that
     *              contains the elements of the first column of the matrix.
     *  @tparam     U  The data type used to define the input array.
     *  @tparam     AllocU  The type of allocator used to build the input array.
     *  @param[in]  c  The first columm of the matrix.
     *  @returns    The new Hankel matrix.
     */
    template<typename U, typename AllocU> requires std::convertible_to<U, T>
    static Array2D<T, Alloc> hankel(const Array<U, AllocU>& c);

    /**
     *  @brief      Hankel matrix.
     *  @details    This function creates a symmetric Hankel matrix taking the elements of an array that
     *              contains the elements of the first column of the matrix.
     *  @tparam     U  The data type used to define the input array.
     *  @tparam     AllocU  The type of allocator used to build the input array.
     *  @param[in]  c  The first columm of the matrix.
     *  @param[in]  r  The last row of the matrix.
     *  @returns    The new Hankel matrix.
     */
    template<typename U, typename AllocU> requires std::convertible_to<U, T>
    static Array2D<T, Alloc> hankel(const Array<U, AllocU>& c, const Array<U, AllocU>& r);

    /**
     *  @brief      Filled square.
     *  @details    This function returns an array whose elements inside the specified square are set to val.
     *              The rest of the elements are set to T().
     *  @param[in]  rows  Rows of the array.
     *  @param[in]  columns  Columns of the array.
     *  @param[in]  r0  Row index where the bounded area begins.
     *  @param[in]  c0  Column index where the bounded area begins.
     *  @param[in]  l  Square size.
     *  @param[in]  val  Value that is used to fill the bounded area.
     *  @returns    The new array.
     */
    static Array2D<T, Alloc> filledSquare(size_type rows, size_type columns,
        size_type r0, size_type c0, size_type l, const_reference val);

    /**
     *  @brief      Filled rectangle.
     *  @details    This function returns an array whose elements inside the specified rectangle are set to val.
     *              The rest of the elements are set to T().
     *  @param[in]  rows  Rows of the array.
     *  @param[in]  columns  Columns of the array.
     *  @param[in]  r0  Row index where the bounded area begins.
     *  @param[in]  c0  Column index where the bounded area begins.
     *  @param[in]  wr  Size in the dimension of the rows.
     *  @param[in]  wc  Size in the dimension of the columns.
     *  @param[in]  val  Value that is used to fill the bounded area.
     *  @returns    The new array.
     */
    static Array2D<T, Alloc> filledRectangle(size_type rows, size_type columns,
        size_type r0, size_type c0, size_type wr, size_type wc, const_reference val);

    /**
     *  @brief      Filled circle.
     *  @details    This function returns an array whose elements inside the specified circle are set to val.
     *              The rest of the elements are set to T().
     *  @param[in]  rows  Rows of the array.
     *  @param[in]  columns  Columns of the array.
     *  @param[in]  r0  Row index where the circle is centered.
     *  @param[in]  c0  Column index where the circle is centered.
     *  @param[in]  r  The radius of the circle.
     *  @param[in]  val  Value that is used to fill the bounded area.
     *  @returns    The new array.
     */
    static Array2D<T, Alloc> filledCircle(size_type rows, size_type columns,
        size_type r0, size_type c0, size_type r, const_reference val);

    /**
     *  @brief      Filled ellipse.
     *  @details    This function returns an array whose elements inside the specified ellipse are set to val.
     *              The rest of the elements are set to T().
     *  @param[in]  rows  Rows of the array.
     *  @param[in]  columns  Columns of the array.
     *  @param[in]  r0  Row index where the ellipse is centered.
     *  @param[in]  c0  Column index where the ellipse is centered.
     *  @param[in]  wr  The radius of the ellipse in the direction of the rows.
     *  @param[in]  wc  The radius of the ellipse in the direction of the columns.
     *  @param[in]  val  Value that is used to fill the bounded area.
     *  @returns    The new array.
     */
    static Array2D<T, Alloc> filledEllipse(size_type rows, size_type columns,
        size_type r0, size_type c0, size_type wr, size_type wc, const_reference val);

    /**
     *  @brief      Chess pattern.
     *  @details    This function creates an array that represents a chess pattern.
     *  @param[in]  rows  Rows of the array.
     *  @param[in]  columns  Columns of the array.
     *  @param[in]  horizontalDiv  Number of horizontal divisions.
     *  @param[in]  verticalDiv  Number of vertical divisions.
     */
    static Array2D<T, Alloc> chessPattern(size_type rows, size_type columns,
        size_type nRowDiv = 8, size_type nColumnDiv = 8);

    ////////// Member functions for iterators //////////

    /**
     *  @brief      Beginning of the array.
     *  @details    This function returns an iterator that points to the beginning of the array.
     *  @returns    The iterator.
     */
    iterator begin();

    /**
     *  @brief      Beginning of the array.
     *  @details    This function returns a const iterator that points to the beginning of the array.
     *  @returns    The iterator.
     */
    const_iterator begin() const;

    /**
     *  @brief      Beginning of the array.
     *  @details    This function returns a const iterator that points to the beginning of the array.
     *  @returns    The iterator.
     */
    const_iterator cbegin() const;

    /**
     *  @brief      End of the array.
     *  @details    This function returns an iterator that points to the end of the array.
     *  @returns    The iterator.
     */
    iterator end();

    /**
     *  @brief      End of the array.
     *  @details    This function returns an iterator that points to the end of the array.
     *  @returns    The iterator.
     */
    const_iterator end() const;

    /**
     *  @brief      End of the array.
     *  @details    This function returns an iterator that points to the end of the array.
     *  @returns    The iterator.
     */
    const_iterator cend() const;

    /**
     *  @brief      Beginning of the reversed array.
     *  @details    This function returns an iterator that points to the beginning of the reversed array.
     *  @returns    The iterator.
     */
    reverse_iterator rbegin();

    /**
     *  @brief      Beginning of the reversed array.
     *  @details    This function returns a const iterator that points to the beginning of the reversed array.
     *  @returns    The iterator.
     */
    const_reverse_iterator rbegin() const;

    /**
     *  @brief      Beginning of the reversed array.
     *  @details    This function returns a const iterator that points to the beginning of the reversed array.
     *  @returns    The iterator.
     */
    const_reverse_iterator crbegin() const;

    /**
     *  @brief      End of the reversed array.
     *  @details    This function returns an iterator that points to the end of the reversed array.
     *  @returns    The iterator.
     */
    reverse_iterator rend();

    /**
     *  @brief      End of the reversed array.
     *  @details    This function returns an iterator that points to the end of the reversed array.
     *  @returns    The iterator.
     */
    const_reverse_iterator rend() const;

    /**
     *  @brief      End of the reversed array.
     *  @details    This function returns an iterator that points to the end of the reversed array.
     *  @returns    The iterator.
     */
    const_reverse_iterator crend() const;

    /**
     *  @brief      Beginning of a row.
     *  @details    This function returns an iterator that points to the beginning of a row. The iterator
     *              steps the elements of the selected row and it's limited by these elements.
     *  @param[in]  row  Row index.
     *  @returns    The iterator.
     */
    iterator beginRow(size_type row);

    /**
     *  @brief      Beginning of a row.
     *  @details    This function returns a const iterator that points to the beginning of a row. The
     *              iterator steps the elements of the selected row and it's limited by these elements.
     *  @param[in]  row  Row index.
     *  @returns    The iterator.
     */
    const_iterator beginRow(size_type row) const;

    /**
     *  @brief      Beginning of a row.
     *  @details    This function returns a const iterator that points to the beginning of a row. The
     *              iterator steps the elements of the selected row and it's limited by these elements.
     *  @param[in]  row  Row index.
     *  @returns    The iterator.
     */
    const_iterator cbeginRow(size_type row) const;

    /**
     *  @brief      End of a row.
     *  @details    This function returns an iterator that points to the end of a row. The iterator steps
     *              the elements of the selected row and it's limited by these elements.
     *  @param[in]  row  Row index.
     *  @returns    The iterator.
     */
    iterator endRow(size_type row);

    /**
     *  @brief      End of a row.
     *  @details    This function returns a const iterator that points to the end of a row. The iterator
     *              steps the elements of the selected row and it's limited by these elements.
     *  @param[in]  row  Row index.
     *  @returns    The iterator.
     */
    const_iterator endRow(size_type row) const;

    /**
     *  @brief      End of a row.
     *  @details    This function returns a const iterator that points to the end of a row. The iterator
     *              steps the elements of the selected row and it's limited by these elements.
     *  @param[in]  row  Row index.
     *  @returns    The iterator.
     */
    const_iterator cendRow(size_type row) const;

    /**
     *  @brief      Beginning of a reversed row.
     *  @details    This function returns an iterator that points to the beginning of a reversed row. The
     *              iterator steps the elements of the selected row and it's limited by these elements.
     *  @param[in]  row  Row index.
     *  @returns    The iterator.
     */
    reverse_iterator rbeginRow(size_type row);

    /**
     *  @brief      Beginning of a reversed row.
     *  @details    This function returns a const iterator that points to the beginning of a reversed
     *              row. The iterator steps the elements of the    selected row and it's limited by these
     *              elements.
     *  @param[in]  row  Row index.
     *  @returns    The iterator.
     */
    const_reverse_iterator rbeginRow(size_type row) const;

    /**
     *  @brief      Beginning of a reversed row.
     *  @details    This function returns a const iterator that points to the beginning of a reversed
     *              row. The iterator steps the elements of the    selected row and it's limited by these
     *              elements.
     *  @param[in]  row  Row index.
     *  @returns    The iterator.
     */
    const_reverse_iterator crbeginRow(size_type row) const;

    /**
     *  @brief      End of a reversed row.
     *  @details    This function returns an iterator that points to the end of a reversed row. The
     *              iterator steps the elements of the selected row and it's limited by these elements.
     *  @param[in]  row  Row index.
     *  @returns    The iterator.
     */
    reverse_iterator rendRow(size_type row);

    /**
     *  @brief      End of a reversed row.
     *  @details    This function returns a const iterator that points to the end of a reversed row. The
     *              iterator steps the elements of the selected row and it's limited by these elements.
     *  @param[in]  row  Row index.
     *  @returns    The iterator.
     */
    const_reverse_iterator rendRow(size_type row) const;

    /**
     *  @brief      End of a reversed row.
     *  @details    This function returns a const iterator that points to the end of a reversed row. The
     *              iterator steps the elements of the selected row and it's limited by these elements.
     *  @param[in]  row  Row index.
     *  @returns    The iterator.
     */
    const_reverse_iterator crendRow(size_type row) const;

    /**
     *  @brief      Beginning of a column.
     *  @details    This function returns an iterator that points to the beginning of a column. The
     *              iterator steps the elements of the selected column and it's limited by these
     *              elements.
     *  @param[in]  column  Column index.
     *  @returns    The iterator.
     */
    iterator beginColumn(size_type column);

    /**
     *  @brief      Beginning of a column.
     *  @details    This function returns an iterator that points to the beginning of a column. The
     *              iterator steps the elements of the selected column and it's limited by these
     *              elements.
     *  @param[in]  column  Column index.
     *  @returns    The iterator.
     */
    const_iterator beginColumn(size_type column) const;

    /**
     *  @brief      Beginning of a column.
     *  @details    This function returns an iterator that points to the beginning of a column. The
     *              iterator steps the elements of the selected column and it's limited by these
     *              elements.
     *  @param[in]  column  Column index.
     *  @returns    The iterator.
     */
    const_iterator cbeginColumn(size_type column) const;

    /**
     *  @brief      End of a column.
     *  @details    This function returns a const iterator that points to the end of a column. The
     *              iterator steps the elements of the selected column and it's limited by these
     *              elements.
     *  @param[in]  column  Column index.
     *  @returns    The iterator.
     */
    iterator endColumn(size_type column);

    /**
     *  @brief      End of a column.
     *  @details    This function returns a const iterator that points to the end of a column. The
     *              iterator steps the elements of the selected column and it's limited by these
     *              elements.
     *  @param[in]  column  Column index.
     *  @returns    The iterator.
     */
    const_iterator endColumn(size_type column) const;

    /**
     *  @brief      End of a column.
     *  @details    This function returns a const iterator that points to the end of a column. The
     *              iterator steps the elements of the selected column and it's limited by these
     *              elements.
     *  @param[in]  column  Column index.
     *  @returns    The iterator.
     */
    const_iterator cendColumn(size_type column) const;

    /**
     *  @brief      Beginning of a reversed column.
     *  @details    This function returns an iterator that points to the beginning of a reversed column.
     *              The iterator steps the elements of the selected column and it's limited by these
     *              elements.
     *  @param[in]  column  Column index.
     *  @returns    The iterator.
     */
    reverse_iterator rbeginColumn(size_type column);

    /**
     *  @brief      Beginning of a reversed column.
     *  @details    This function returns an iterator that points to the end of a reversed column. The
     *              iterator steps the elements of the selected column and it's limited by these
     *              elements.
     *  @param[in]  column  Column index.
     *  @returns    The iterator.
     */
    const_reverse_iterator rbeginColumn(size_type column) const;

    /**
     *  @brief      Beginning of a reversed column.
     *  @details    This function returns an iterator that points to the end of a reversed column. The
     *              iterator steps the elements of the selected column and it's limited by these
     *              elements.
     *  @param[in]  column  Column index.
     *  @returns    The iterator.
     */
    const_reverse_iterator crbeginColumn(size_type column) const;

    /**
     *  @brief      End of a reversed column.
     *  @details    This function returns a const iterator that points to the end of a reversed column.
     *              The iterator steps the elements of the selected column and it's limited by these
     *              elements.
     *  @param[in]  column  Column index.
     *  @returns    The iterator.
     */
    reverse_iterator rendColumn(size_type column);

    /**
     *  @brief      End of a reversed column.
     *  @details    This function returns a const iterator that points to the end of a reversed column.
     *              The iterator steps the elements of the selected column and it's limited by these
     *              elements.
     *  @param[in]  column  Column index.
     *  @returns    The iterator.
     */
    const_reverse_iterator rendColumn(size_type column) const;

    /**
     *  @brief      End of a reversed column.
     *  @details    This function returns a const iterator that points to the end of a reversed column.
     *              The iterator steps the elements of the selected column and it's limited by these
     *              elements.
     *  @param[in]  column  Column index.
     *  @returns    The iterator.
     */
    const_reverse_iterator crendColumn(size_type column) const;

    ////////// Transformations //////////

    /**
     *  @brief      Transform array.
     *  @details    This function transforms each element of the array into a new value 
     *              and stores the result in a new array of the same size. 
     *  @tparam     U  The data type of the output array.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  f  Function that will be used to transform the elements. The function only requires
     *              one argument, a const_reference to one element. Also, the function returns an escalar
     *              of type U.
     *  @returns    The new array.
     */
    template<typename U, typename AllocU = std::allocator<U>>
    Array2D<U, AllocU> transformData(const std::function<U(const_reference)>& f) const;

    /**
     *  @brief      Collapse rows.
     *  @details    This function transform each row into a scalar value.
     *              The result is returned in a new array with one column and
     *              the same number of rows of the original array.
     *  @tparam     U  The data type of the output array.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  f  Function that will be used to transform the elements. The function only
     *              requires one argument, a const_reference to an array. This argument
     *              represents a sub-array with the elements of one row. Also, the function
     *              returns an escalar of type U.
     *  @returns    The new array.
     */
    template<typename U, typename AllocU = std::allocator<U>>
    Array2D<U, AllocU> collapseRows(const std::function<U(const Array<T, Alloc>&)>& f) const;

    /**
     *  @brief      Collapse rows.
     *  @details    This function transform each row into a scalar value.
     *              The result is returned in a new array with one column and
     *              the same number of rows of the original array.
     *  @tparam     U  The data type of the output array.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  f  Function that will be used to transform the elements. The function
     *              requires two arguments, the iterators of the beginning and the end of a row.
     *              Also, the function returns an escalar of type U.
     *  @returns    The new array.
     */
    template<typename U, typename AllocU = std::allocator<U>>
    Array2D<U, AllocU> collapseRows(const std::function < U(const_iterator, const_iterator) >& f) const;

    /**
     *  @brief      Collapse columns.
     *  @details    This function transform each column into a scalar value.
     *              The result is returned in a new array with one row and
     *              the same number of columns of the original array.
     *  @tparam     U  The data type of the output array.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  f  Function that will be used to transform the elements. The function only requires
     *              one argument, a const_reference to an array. This argument represents a sub-array
     *              with the elements of one column. Also, the function returns an escalar of type U.
     *  @returns    The new array.
     */
    template<typename U, typename AllocU = std::allocator<U>>
    Array2D<U, AllocU> collapseColumns(const std::function<U(const Array<T, Alloc>&)>& f) const;

    /**
     *  @brief      Collapse columns.
     *  @details    This function transform each column into a scalar value.
     *              The result is returned in a new array with one row and
     *              the same number of columns of the original array.
     *  @tparam     U  The data type of the output array.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  f  Function that will be used to transform the elements. The function requires two
     *              arguments, the iterators of the beginning and the end of a column. Also, the function
     *              returns an escalar of type U.
     *  @returns    The new array.
     */
    template<typename U, typename AllocU = std::allocator<U>>
    Array2D<U, AllocU> collapseColumns(const std::function<U(const_iterator, const_iterator)>& f) const;

    ////////// I/O operations //////////

    /**
     *  @brief      Write an array to an output stream.
     *  @details    This function writes an array to an output stream in binary format.
     *  @param[in, out] o  The output stream where the data will be written.
     */
    void write(std::ostream& o) const;

    /**
     *  @brief      Read an array from an input stream.
     *  @details    This function reads an array from an input stream in binary format.
     *  @param[in, out] i  The input stream from where the data will be read.
     *  @returns    The object that was read from the input stream.
     */
    static Array2D<T, Alloc> read(std::istream& i);

protected:

    ////////// Data members //////////        

    allocator_type alloc_;  /**< Allocator object. */

    size_type n_{0};        /**< Number of elements into the array. */

    size_type nr_{0};       /**< Number of rows. */

    size_type nc_{0};       /**< Number of columns. */

    pointer data_{nullptr}; /**< Array of objects. */

};

////////// Global functions and global operators //////////    

/**
 *  @brief      Dot product.
 *  @details    This function calculates the dot product of two arrays of the same size.
 *  @tparam     T  The type of data of the input arrays.
 *  @tparam     Alloc  The type of allocator to build the arrays.
 *  @param[in]  a  Input array 1.
 *  @param[in]  b  Input array 2.
 *  @returns    The dot product of a and b.
 */
template<nct::Numeric T, typename Alloc> 
T dotProduct(const Array2D<T, Alloc>& a, const Array2D<T, Alloc>& b);

/**
 *  @brief      Matrix * Vector product.
 *  @details    This function calculates the product of one matrix and a column vector. The result
 *              is returned in one array of size = rows(m).
 *  @tparam     T  The type of data of the input and output arrays.
 *  @tparam     Alloc  The type of allocator to build the arrays.
 *  @param[in]  m  Input array of size n x p.
 *  @param[in]  v  Input array of size p.
 *  @returns    An array of size n_ with the result of the operation.
 */
template<nct::Numeric T, typename Alloc>
Array<T, Alloc> matrixVectorProduct(const Array2D<T, Alloc>& m, const Array<T, Alloc>& v);

/**
 *  @brief      ColVector * RowVector product.
 *  @details    This function calculates the product of one column vector and a row vector. The result
 *              is returned in one array.
 *  @tparam     T  The type of data of the input and output arrays.
 *  @tparam     Alloc  The type of allocator to build the arrays.
 *  @param[in]  c  Input array of size n.
 *  @param[in]  r  Input array of size m.
 *  @returns    An array of size n x m with the result of the operation.
 */
template<nct::Numeric T, typename Alloc>
Array2D<T, Alloc> colVectorRowVectorProduct(const Array<T, Alloc>& c,
    const Array<T, Alloc>& r);

/**
 *  @brief      Direct sum.
 *  @details    This function calculates the direct sum of one matrix of size m x n p times.
 *  @tparam     T  The type of data of the input and output arrays.
 *  @tparam     Alloc  The type of allocator to build the arrays.
 *  @param[in]  m  The matrix to add.
 *  @param[in]  times  The number of times that the matrix is added.
 *  @returns    An array of size mp x nq with the result of the operation.
 */
template<nct::Numeric T, typename Alloc>
Array2D<T, Alloc> directSum(const Array2D<T, Alloc>& m, unsigned int times);

/**
 *  @brief      Direct sum of two matrices.
 *  @details    This function calculates the direct sum of two matrices.
 *  @tparam     T  The type of data of the input and output arrays.
 *  @tparam     Alloc  The type of allocator to build the arrays.
 *  @param[in]  left  The matrix at the left side of the operation.
 *  @param[in]  right  The matrix at the right side of the operation.
 *  @returns    An array of size (m1+m2) x (n1+n2) with the result of the operation.
 */
template<nct::Numeric T, typename Alloc>
Array2D<T, Alloc> directSum(const Array2D<T, Alloc>& left, const Array2D<T, Alloc>& right);

/**
 *  @brief      Kronecker sum of two matrices.
 *  @details    This function calculates the Kronecker sum of two matrices.
 *  @tparam     T  The type of data of the input and output arrays.
 *  @tparam     Alloc  The type of allocator to build the arrays.
 *  @param[in]  left  The matrix at the left side of the operation.
 *  @param[in]  right  The matrix at the right side of the operation.
 *  @returns    An array of size (m1m2) x (n1n2) with the result of the operation.
 */
template<nct::Numeric T, typename Alloc>
Array2D<T, Alloc> kroneckerSum(const Array2D<T, Alloc>& left, const Array2D<T, Alloc>& right);

/**
 *  @brief      Kronecker product of two matrices.
 *  @details    This function calculates the Kronecker product of two matrices.
 *  @tparam     T  The type of data of the input and output arrays.
 *  @tparam     Alloc  The type of allocator to build the arrays.
 *  @param[in]  left  The matrix at the left side of the operation.
 *  @param[in]  right  The matrix at the right side of the operation.
 *  @returns    An array of size (m1m2) x (n1n2) with the result of the operation.
 */
template<nct::Numeric T, typename Alloc>
Array2D<T, Alloc> kroneckerProduct(const Array2D<T, Alloc>& left, const Array2D<T, Alloc>& right);

/**
 *  @brief      Bitwise AND.
 *  @details    This operator performs the bitwise "and" operation for each index of the arrays.
 *  @tparam     T  The type of data of the input and output arrays.
 *  @tparam     Alloc  The type of allocator to build the arrays.
 *  @param[in]  left  Array on the left side of the operation.
 *  @param[in]  right  Array on the right side of the operation.
 *  @returns    The array with the result of the operation.
 */
template<std::integral T, typename Alloc>
Array2D<T, Alloc> operator&(Array2D<T, Alloc>&& left, const Array2D<T, Alloc>& right);

/**
 *  @brief      Bitwise OR.
 *  @details    This operator performs the bitwise "or" operation for each index of the arrays.
 *  @tparam     T  The type of data of the input and output arrays.
 *  @tparam     Alloc  The type of allocator to build the arrays.
 *  @param[in]  left  Array on the left side of the operation.
 *  @param[in]  right  Array on the right side of the operation.
 *  @returns    The array with the result of the operation.
 */
template<std::integral T, typename Alloc>
Array2D<T, Alloc> operator|(Array2D<T, Alloc>&& left, const Array2D<T, Alloc>& right);

/**
 *  @brief      Bitwise XOR.
 *  @details    This operator performs the bitwise "xor" operation for each index of the arrays.
 *  @tparam     T  The type of data of the input and output arrays.
 *  @tparam     Alloc  The type of allocator to build the arrays.
 *  @param[in]  left  Array on the left side of the operation.
 *  @param[in]  right  Array on the right side of the operation.
 *  @returns    The array with the result of the operation.
 */
template<std::integral T, typename Alloc>
Array2D<T, Alloc> operator^(Array2D<T, Alloc>&& left, const Array2D<T, Alloc>& right);

/**
 *  @brief      Array addition.
 *  @details    This operator calculates the sum of two matrices.
 *  @tparam     T  The type of data of the input and output arrays.
 *  @tparam     Alloc  The type of allocator to build the arrays.
 *  @param[in]  left  Array on the left side of the operation.
 *  @param[in]  right  Array on the right side of the operation.
 *  @returns    The array with the result of the operation.
 */
template<nct::Addable T, typename Alloc>
Array2D<T, Alloc> operator+(Array2D<T, Alloc>&& left, const Array2D<T, Alloc>& right);

/**
 *  @brief      Array substraction.
 *  @details    This operator calculates the substraction of two matrices.
 *  @tparam     T  The type of data of the input and output arrays.
 *  @tparam     Alloc  The type of allocator to build the arrays.
 *  @param[in]  left  Array on the left side of the operation.
 *  @param[in]  right  Array on the right side of the operation.
 *  @returns    The array with the result of the operation.
 */
template<nct::Substractable T, typename Alloc>
Array2D<T, Alloc> operator-(Array2D<T, Alloc>&& left, const Array2D<T, Alloc>& right);

/**
 *  @brief      Scalar product.
 *  @details    This operator calculates the product of an array by a scalar.
 *  @tparam     T  The type of data of the input and output arrays.
 *  @tparam     Alloc  The type of allocator to build the arrays.
 *  @param[in]  left  Scalar value.
 *  @param[in]  right  Array to multiply.
 *  @returns    The array with the result of the operation.
 */
template<nct::Numeric T, typename Alloc>
Array2D<T, Alloc> operator*(const T& left, const Array2D<T, Alloc>& right);

/**
 *  @brief      Input stream to array.
 *  @details    This operators reads the contents of an array from an input stream.
 *              The data are read in binary format.
 *  @tparam     T  The type of data stored in the array.
 *  @tparam     Alloc  The type of allocator used to build the array.
 *  @param[in, out] i  Input stream.
 *  @param[out] arr  Object where the data are stored.
 *  @returns    A reference to the stream.
 */
template<typename T, typename Alloc>
std::istream& operator>>(std::istream& i, Array2D<T, Alloc>& right);

/**
 *  @brief      Array to output stream.
 *  @details    This operator writes the contents of the array in an output stream. The data
 *              is displayed in ASCII format. If a binary serialization is required, use
 *              the "write" method instead.
 *  @tparam     T  The type of data stored in the arrays.
 *  @tparam     Alloc  The type of allocator used to build the arrays.
 *  @param[in, out] o  Output stream.
 *  @param[in]  arr  The object to be written.
 *  @returns    A reference to the stream.
 */
template<typename T, typename Alloc>
std::ostream& operator<<(std::ostream& o, const Array2D<T, Alloc>& right);
}

////////// Implementation of class template //////////
#include <nct/Array2D_template.h> 

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
