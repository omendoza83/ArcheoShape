//=================================================================================================================
/**
 *  @file       Array3D.h
 *  @brief      nct::Array3D class template.
 *  @details    Declaration of the nct::Array3D class template.
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

#ifndef NCT_ARRAY_3D_H_INCLUDE
#define NCT_ARRAY_3D_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/array_iterator.h>
#include <nct/Array.h>
#include <nct/Array2D.h>

#include <initializer_list>
#include <iostream>
#include <functional>

//=================================================================================================================
namespace nct {

////////// Classes ////////// 

/**
 *  @brief      Class template for 3D arrays of objects.
 *  @details    This class template is used to manipulate 3D arrays of objects.
 *  @note       It is possible to disable index checking in the [] and () operators by defining
 *              NCT_ARRAY_3D_DISABLE_INDEX_CHECKING.
 *  @tparam     T  The data type to be stored in the array.
 *  @tparam     Alloc  The type of allocator to be used to build the array.
 */
template<typename T, typename Alloc = std::allocator<T>>
class Array3D {

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
    using iterator = nct::array_iterator < Array3D<T, Alloc>, value_type,
        difference_type, pointer, reference >;

    /** Const iterator. */
    using const_iterator = nct::array_iterator < Array3D<T, Alloc>, const value_type,
        difference_type, const_pointer, const_reference >;

    /** Reverse iterator. */
    using reverse_iterator = std::reverse_iterator<iterator>;

    /** Const reverse iterator. */
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;


    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an empty array.
     *  @param[in]  allocator  Allocator object. The container keeps and uses an internal copy of this 
     *              allocator.
     */
    explicit Array3D(const allocator_type& allocator = allocator_type()) noexcept;

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes a three-dimensional array.
     *  @param[in]  dim1  The size of the array in the dimension 1.
     *  @param[in]  dim2  The size of the array in the dimension 2.
     *  @param[in]  dim3  The size of the array in the dimension 3.
     *  @param[in]  allocator  Allocator object. The container keeps and uses an internal copy of this
     *              allocator.
     */
    Array3D(size_type dim1, size_type dim2, size_type dim3, 
        const allocator_type& allocator = allocator_type());

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes a three-dimensional array.
     *  @param[in]  dim1  The size of the array in the dimension 1.
     *  @param[in]  dim2  The size of the array in the dimension 2.
     *  @param[in]  dim3  The size of the array in the dimension 3.
     *  @param[in]  val  Value that is taken by all the new elements inside the array.
     *  @param[in]  allocator  Allocator object. The container keeps and uses an internal copy of this 
     *              allocator.
     */
    Array3D(size_type dim1, size_type dim2, size_type dim3,
        const_reference val, const allocator_type& allocator = allocator_type());

    /**
     *  @brief      Copy constructor.
     *  @details    This constructor copies the contents of an object of the same type.
     *  @param[in]  other  Another object of the same type whose contents are copied.
     */
    Array3D(const Array3D<T, Alloc>& other);

    /**
     *  @brief      Copy constructor.
     *  @details    This constructor copies the contents of an object of the same type.
     *  @param[in]  other  Another object of the same type whose contents are copied.
     *  @param[in]  allocator  Allocator object. The container keeps and uses an internal copy of this 
     *              allocator.
     */
    Array3D(const Array3D<T, Alloc>& other, const allocator_type& allocator);

    /**
     *  @brief      Move constructor.
     *  @details    This constructor moves the contents of an object to the new class instance.
     *  @param[in]  other  Another object of the same type whose contents are acquired.
     */
    Array3D(Array3D<T, Alloc>&& other) noexcept;

    /**
     *  @brief      Move constructor.
     *  @details    This constructor moves the contents of an object to the new class instance.
     *  @param[in]  other  Another object of the same type whose contents are acquired.
     *  @param[in]  allocator  Allocator object. The container keeps and uses an internal copy of this 
     *              allocator.
     */
    Array3D(Array3D<T, Alloc>&& other, const allocator_type& allocator);

    ////////// Destructor //////////

    /**
     *  @brief      Destructor.
     *  @details    Class destructor. 
     */
    ~Array3D() noexcept;

    ////////// Operators //////////        

    /**
     *  @brief      Assignment operator.
     *  @details    This operator copies the contents of an object of the same type.
     *  @param[in]  other  Another object of the same type whose contents are copied.
     *  @returns    A reference to the object.
     */
    Array3D<T, Alloc>& operator=(const Array3D<T, Alloc>& other);

    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator acquires the contents of another object.
     *  @param[in]  other  Another object of the same type whose contents are acquired.
     *  @returns    A reference to the object.
     */
    Array3D<T, Alloc>& operator=(Array3D<T, Alloc>&& other) noexcept;

    /**
     *  @brief      Array subscript.
     *  @details    This operator returns the specified element.
     *  @param[in]  i  The index in the dimension 1.
     *  @param[in]  j  The index in the dimension 2.
     *  @param[in]  k  The index in the dimension 3.
     *  @returns    The selected element.
     */
    reference operator()(size_type i, size_type j, size_type k);

    /**
     *  @brief      Array subscript.
     *  @details    This operator returns the specified element.
     *  @param[in]  i  The index in the dimension 1.
     *  @param[in]  j  The index in the dimension 2.
     *  @param[in]  k  The index in the dimension 3.
     *  @returns    The selected element.
     */
    const_reference operator()(size_type i, size_type j, size_type k) const;

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
    bool operator==(const Array3D<T, Alloc>& right) const;

    /**
     *  @brief      Inequality operator.
     *  @details    Two arrays are not equal if have different same size or element
     *              of one array is not equal to the element with the same index in the other array.
     *  @param[in]  right  Array to compare.
     *  @returns    True if both arrays are not equal.
     */
    bool operator!=(const Array3D<T, Alloc>& right) const;

    /**
     *  @brief      Bitwise AND.
     *  @details    This operator performs the bitwise "and" operation for each index in the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires std::integral<T>
    Array3D<T, Alloc> operator&(const Array3D<T, Alloc>& right) const;

    /**
     *  @brief      Bitwise AND.
     *  @details    This operator performs the bitwise "and" operation for each index of the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires std::integral<T>
    const Array3D<T, Alloc>& operator&=(const Array3D<T, Alloc>& right);

    /**
     *  @brief      Bitwise OR.
     *  @details    This operator performs the bitwise "or" operation for each index in the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires std::integral<T>
    Array3D<T, Alloc> operator|(const Array3D<T, Alloc>& right) const;

    /**
     *  @brief      Bitwise OR.
     *  @details    This operator performs the bitwise "or" operation for each index of the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires std::integral<T>
    const Array3D<T, Alloc>& operator|=(const Array3D<T, Alloc>& right);

    /**
     *  @brief      Bitwise XOR.
     *  @details    This operator performs the bitwise "xor" operation for each index in the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires std::integral<T>
    Array3D<T, Alloc> operator^(const Array3D<T, Alloc>& right) const;

    /**
     *  @brief      Bitwise XOR.
     *  @details    This operator performs the bitwise "xor" operation for each index of the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires std::integral<T>
    const Array3D<T, Alloc>& operator^=(const Array3D<T, Alloc>& right);

    /**
     *  @brief      Unary plus.
     *  @details    This operator multiplies by one all the elements of the array.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires nct::Numeric<T>
    Array3D<T, Alloc> operator+() const;

    /**
     *  @brief      Array addition.
     *  @details    This operator calculates the sum of two arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires nct::Addable<T>
    Array3D<T, Alloc> operator+(const Array3D<T, Alloc>& right) const;

    /**
     *  @brief      Array addition.
     *  @details    This operator calculates the sum of two arrays and stores the result in the current
     *              instance.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires nct::Addable<T>
    const Array3D<T, Alloc>& operator+=(const Array3D<T, Alloc>& right);

    /**
     *  @brief      Unary minus.
     *  @details    This operator multiplies by minus one all the elements of the array.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires nct::SignedNumeric<T>
    Array3D<T, Alloc> operator-() const;

    /**
     *  @brief      Array substraction.
     *  @details    This operator calculates the substraction of two arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires nct::Substractable<T>
    Array3D<T, Alloc> operator-(const Array3D<T, Alloc>& right) const;

    /**
     *  @brief      Array substraction.
     *  @details    This operator calculates the substraction of two arrays and stores the result in the 
     *              current instance.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires nct::Substractable<T>
    const Array3D<T, Alloc>& operator-=(const Array3D<T, Alloc>& right);

    /**
     *  @brief      Scalar product.
     *  @details    This operator calculates the multiplication of the array by a scalar.
     *  @param[in]  right  Scalar value.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires nct::Numeric<T>
    Array3D<T, Alloc> operator*(const_reference right) const;

    /**
     *  @brief      Scalar product.
     *  @details    This operator calculates the multiplication of the array by a scalar and stores 
     *              the result in this instance.
     *  @param[in]  right  Scalar value.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires nct::Numeric<T>
    const Array3D<T, Alloc>& operator*=(const_reference right);

    /**
     *  @brief      Scalar division.
     *  @details    This operator calculates the division of the array by a scalar.
     *  @param[in]  right  Scalar value.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires nct::Numeric<T>
    Array3D<T, Alloc> operator/(const_reference right) const;

    /**
     *  @brief      Scalar division.
     *  @details    This operator calculates the division of the array by a scalar and stores the 
     *              result in this instance.
     *  @param[in]  right  Scalar value.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires nct::Numeric<T>
    const Array3D<T, Alloc>& operator/=(const_reference right);

    ////////// Basic member functions //////////        

    /**
     *  @brief      CLear array.
     *  @details    This function releases the allocated memory.
     */
    void clear() noexcept;

    /**
     *  @brief      Assigns contents to the array.
     *  @details    This function Assigns new contents to the array, replacing its current
     *              contents, and modifying its size accordingly.
     *  @param[in]  dim1  The size of the array in the dimension 1.      
     *  @param[in]  dim2  The size of the array in the dimension 2.
     *  @param[in]  dim3  The size of the array in the dimension 3.
     *  @param[in]  val  Value that is taken by all the elements inside the array.
     */
    void assign(size_type dim1, size_type dim2, size_type dim3,
        const_reference val);

    /**
     *  @brief      Resizes the array.
     *  @details    This function modifies the size of the array. The original data contained in
     *              the array keep their original positions and elements beyond the boundaries are
     *              erased. If new positions are added to the array, the new elements are set according
     *              to the default constructor.
     *  @param[in]  dim1  The size of the array in the dimension 1.      
     *  @param[in]  dim2  The size of the array in the dimension 2.
     *  @param[in]  dim3  The size of the array in the dimension 3.
     */
    void resize(size_type dim1, size_type dim2, size_type dim3);

    /**
     *  @brief      Resizes the array.
     *  @details    This function modifies the size of the array. The original data contained in
     *              the array keep their original positions and elements beyond the boundaries are
     *              erased. If new positions are added to the array, the new elements are set to val.
     *  @param[in]  dim1  The size of the array in the dimension 1.      
     *  @param[in]  dim2  The size of the array in the dimension 2.
     *  @param[in]  dim3  The size of the array in the dimension 3.
     *  @param[in]  val  New value of all the array elements.
     */
    void resize(size_type dim1, size_type dim2, size_type dim3,
        const_reference val);

    /**
     *  @brief      Gets the array allocator.
     *  @details    This function returns a copy of the allocator object that is used by the
     *              container.
     *  @returns    An allocator object.
     */
    allocator_type get_allocator() const;

    /**
     *  @brief      Fills the array with a constant value.
     *  @details    This function fills the array with a value.
     *  @param[in]  val  New value of all the array elements.
     */
    void fill(const_reference val);

    /**
     *  @brief      Change the shape of the array.
     *  @details    This function modifies the shape of the array. The size of the array must not
     *              change. 
     *  @param[in]  dim1  The new size of the array in dimension 1.
     *  @param[in]  dim2  The new size of the array in dimension 2.
     *  @param[in]  dim3  The new size of the array in dimension 3.
     */
    void reshape(size_type dim1, size_type dim2, size_type dim3);

    /**
     *  @brief      Copies another array.
     *  @details    This function copies the contents of other array.
     *  @param[in]  other  Array to copy.
     */
    void copy(const Array3D<T, Alloc>& other);

    /**
     *  @brief      Is the array empty?
     *  @details    This function tests whether the array is empty.
     *  @returns    True, if the array is empty.
     */
    bool empty() const noexcept;

    /**
     *  @brief      Size of the array in the dimension 1.
     *  @details    This function returns the size of the array in the dimension 1.
     *  @returns    The size of the array in the dimension 1.
     */
    size_type dimension1() const noexcept;

    /**
     *  @brief      Size of the array in the dimension 2.
     *  @details    This function returns the size of the array in the dimension 2.
     *  @returns    The size of the array in the dimension 2.
     */
    size_type dimension2() const noexcept;

    /**
     *  @brief      Size of the array in the dimension 3.
     *  @details    This function returns the size of the array in the dimension 3.
     *  @returns    The size of the array in the dimension 3.
     */
    size_type dimension3() const noexcept;

    /**
     *  @brief      Returns the array size.
     *  @details    This function returns the number of elements in the array. 
     *  @returns    Number of elements.
     */
    size_type size() const noexcept;

    /**
     *  @brief      Pointer to data.
     *  @details    This function returns the pointer that is used to allocate the data in the
     *              array.
     *  @note       Don't use this function unless it's extremely necessary to access the data directly.
     *              Also, the returned pointer must never be released.            
     *  @returns    The pointer to the selected item.
     */
    pointer data() noexcept;

    /**
     *  @brief      Const pointer to data.
     *  @details    This function returns the pointer that is used to allocate the data in the
     *              array.
     *  @note       Don't use this function unless it's extremely necessary to access the data directly.
     *              Also, the returned pointer must never be released.            
     *  @returns    The pointer to the selected item.
     */
    const_pointer data() const noexcept;

    /**
     *  @brief      Pointer to one element.
     *  @details    This function returns the pointer to the address of one element in the array.
     *  @note       Don't use this function unless is extremely necessary to access the data directly.
     *              Also, the returned pointer must never be released.        
     *  @param[in]  index  The index of the object to be returned.    
     *  @returns    The pointer to the data.
     */
    pointer data(size_type index);

    /**
     *  @brief      const pointer to one element.
     *  @details    This function returns the pointer to the address of one element in the array.
     *  @note       Don't use this function unless is extremely necessary to access the data directly.
     *              Also, the returned pointer must never be released.        
     *  @param[in]  index  The index of the object to be returned.    
     *  @returns    The pointer to the data.
     */
    const_pointer data(size_type index) const;

    /**
     *  @brief      Pointer to one element.
     *  @details    This function returns the pointer to the address of one element in the array.
     *  @note       Don't use this function unless is extremely necessary to access the data directly.
     *              Also, the returned pointer must never be released.        
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The pointer to the selected item.
     */
    pointer data(size_type dim1, size_type dim2, size_type dim3);

    /**
     *  @brief      Const pointer to one element.
     *  @details    This function returns the pointer to the address of one element in the array.
     *  @note       Don't use this function unless is extremely necessary to access the data directly.
     *              Also, the returned pointer must never be released.        
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The pointer to the selected item.
     */
    const_pointer data(size_type dim1, size_type dim2, size_type dim3) const;

    /**
     *  @brief      Reference to one element.
     *  @details    This function returns a reference to the specified object. The function
     *              verifies whether the specified element is out of range.
     *  @param[in]  index  The index of the object to be returned.
     *  @returns    The desired object.
     */
    reference at(size_type index);

    /**
     *  @brief      Reference to one element.
     *  @details    This function returns a reference to the specified object. The function
     *              verifies whether the specified element is out of range.
     *  @param[in]  index  The index of the object to be returned.
     *  @returns    The desired object.
     */
    const_reference at(size_type index) const;

    /**
     *  @brief      Reference to one element.
     *  @details    This function returns a reference to the specified object. The function
     *              verifies whether the specified element is out of range.
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The desired object.
     */
    reference at(size_type dim1, size_type dim2, size_type dim3);

    /**
     *  @brief      Reference to one element.
     *  @details    This function returns a reference to the specified object. The function
     *              verifies whether the specified element is out of range.
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The desired object.
     */
    const_reference at(size_type dim1, size_type dim2, size_type dim3) const;

    /**
     *  @brief      Memory offset.
     *  @details    This function returns the offset inside the memory block that corresponds
     *              to the specified dim1. This function doesn't verify whether the specified
     *              index is valid for the current instance.
     *  @param[in]  dim1  The index in the dimension 1.
     *  @returns    The offset of the specified index.
     */
    size_type offset(size_type dim1) const noexcept;

    /**
     *  @brief      Memory offset.
     *  @details    This function returns the offset inside the memory block that corresponds
     *              to the specified dim1 and dim2. This function doesn't verify whether the specified
     *              indices are valid for the current instance.
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @returns    The offset of the specified indices.
     */
    size_type offset(size_type dim1, size_type dim2) const noexcept;

    /**
     *  @brief      Memory offset.
     *  @details    This function returns the offset inside the memory block that corresponds to
     *              the specified dim1, dim2 and dim3. This function doesn't verify whether the specified
     *              indices are valid for the current instance.
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The offset of the specified indices.
     */
    size_type offset(size_type dim1, size_type dim2, size_type dim3) const noexcept;

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
    Array3D<U, AllocU> toArray() const;

    ////////// Data insertions and deletions //////////    

    /**
     *  @brief      Insert index in the dimension 1.
     *  @details    This function inserts new items in the specified index in the dimension 1.
     *  @param[in]  dim1  Index where the new items will be inserted.
     *  @param[in]  data  Array that contains the elements the new items. 
     *              The element of index (j, k) is copied to the position (dim1, j, k).
     */
    void insertDim1(size_type dim1, const Array2D<T, Alloc>& data);

    /**
     *  @brief      Insert multiple indices in the dimension 1.
     *  @details    This function inserts multiple items in the dimension 1.
     *  @param[in]  dim1  Index where the new items will be inserted.
     *  @param[in]  data  Data of the new dimension 1.
     */
    void insertDim1(size_type dim1, const Array3D<T, Alloc>& data);

    /**
     *  @brief      Erase index in the dimension 1.
     *  @details    This function removes the items at the specified index in the dimension 1. 
     *  @param[in]  dim1  Index of the items to eliminate.
     */
    void eraseDim1(size_type dim1);

    /**
     *  @brief      Erase indices in the dimension 1.
     *  @details    This function removes a range of items with the specified index in the
     *              dimension 1.
     *  @param[in]  first  Initial index of the range to remove.
     *  @param[in]  last  Last index of the range to remove.
     */
    void eraseDim1(size_type first, size_type last);

    /**
     *  @brief      Erase indices in the dimension 1.
     *  @details    This function removes the items that are specified in the range [first, last).
     *              The range indicates the indices in the dimension 1 to erase from the container.
     *  @tparam     IndexIt  The iterator type to be used to indicate the indices. 
     *  @param[in]  first  Beginning of the range with the indices to remove.
     *  @param[in]  last  End of the range that with the indices to remove.
     */
    template<std::random_access_iterator IndexIt>
    void eraseDim1(IndexIt first, IndexIt last);

    /**
     *  @brief      Insert index in the dimension 2.
     *  @details    This function inserts new items in the specified index in the dimension 2.
     *  @param[in]  dim2  Index where the new items will be inserted.
     *  @param[in]  data  Array that contains the elements the new items.
     *              The element of index (i, k) is copied to the position (i, dim2, k).
     */
    void insertDim2(size_type dim2, const Array2D<T, Alloc>& data);

    /**
     *  @brief      Insert multiple indices in the dimension 2.
     *  @details    This function inserts multiple items in the dimension 2.
     *  @param[in]  dim2  Index where the new items will be inserted.
     *  @param[in]  data  Data of the new dimension 2.
     */
    void insertDim2(size_type dim2, const Array3D<T, Alloc>& data);

    /**
     *  @brief      Erase index in the dimension 2.
     *  @details    This function removes the items at the specified index in the dimension 2. 
     *  @param[in]  dim2  Index of the items to eliminate.
     */
    void eraseDim2(size_type dim2);

    /**
     *  @brief      Erase items in the dimension 2.
     *  @details    This function removes a range of items with the specified index in the
     *              dimension 2.
     *  @param[in]  first  Initial index of the range to remove.
     *  @param[in]  last  Last index of the range to remove.
     */
    void eraseDim2(size_type first, size_type last);

    /**
     *  @brief      Erase indices in the dimension 2.
     *  @details    This function removes the items that are specified in the range [first, last).
     *              The range indicates the indices in the dimension 2 to erase from the container.
     *  @tparam     IndexIt  The iterator type to be used to indicate the indices.
     *  @param[in]  first  Beginning of the range with the indices to remove.
     *  @param[in]  last  End of the range that with the indices to remove.
     */
    template<std::random_access_iterator IndexIt>
    void eraseDim2(IndexIt first, IndexIt last);

    /**
     *  @brief      Insert index in the dimension 3.
     *  @details    This function inserts new items in the specified index in the dimension 3.
     *  @param[in]  dim3  Index where the new items will be inserted.
     *  @param[in]  data  Array that contains the elements the new items.
     *              The element of index (i, j) is copied to the position (i, j, dim3).
     */
    void insertDim3(size_type dim3, const Array2D<T, Alloc>& data);

    /**
     *  @brief      Insert indices in the dimension 3.
     *  @details    This function inserts multiple items in the dimension 3.
     *  @param[in]  dim3  Index where the new items will be inserted.
     *  @param[in]  data  Data of the new dimension 3.
     */
    void insertDim3(size_type dim3, const Array3D<T, Alloc>& data);

    /**
     *  @brief      Erase index in the dimension 3.
     *  @details    This function removes the items at the specified index in the dimension 3. 
     *  @param[in]  dim3  Index of the items to eliminate.
     */
    void eraseDim3(size_type dim3);

    /**
     *  @brief      Erase indices in the dimension 3.
     *  @details    This function removes a range of items with the specified index in the
     *              dimension 3.
     *  @param[in]  first  Initial index of the range to remove.
     *  @param[in]  last  Last index of the range to remove.
     */
    void eraseDim3(size_type first, size_type last);

    /**
     *  @brief      Erase indices in the dimension 3.
     *  @details    This function removes the items that are specified in the range [first, last).
     *              The range indicates the indices in the dimension 3 to erase from the container.
     *  @tparam     IndexIt  The iterator type to be used to indicate the indices.
     *  @param[in]  first  Beginning of the range with the indices to remove.
     *  @param[in]  last  End of the range that with the indices to remove.
     */
    template<std::random_access_iterator IndexIt>
    void eraseDim3(IndexIt first, IndexIt last);

    ////////// Data selection //////////

    /**
     *  @brief      Sub-array.
     *  @details    This function returns the selected 2D array. The array corresponds to the set
     *              of items with the specified index in the dimension 1.
     *  @param[in]  dim1  Index of the 2D array to be returned.
     *  @returns    The new array with the selected data.
     */
    Array2D<T, Alloc> subArray(size_type dim1) const;

    /**
     *  @brief      Elements of dimension 1.
     *  @details    This function returns a new array with the elements at the especified dim2 and dim3.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The new array with the selected data.
     */
    Array<T, Alloc> elementsOfDim1(size_type dim2, size_type dim3) const;

    /**
     *  @brief      Elements of dimension 2.
     *  @details    This function returns a new array with the elements at the especified dim1 and dim3.
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The new array with the selected data.
     */
    Array<T, Alloc> elementsOfDim2(size_type dim1, size_type dim3) const;

    /**
     *  @brief      Elements of dimension 3.
     *  @details    This function returns a new array with the elements at the especified dim1 and dim2.
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @returns    The new array with the selected data.
     */
    Array<T, Alloc> elementsOfDim3(size_type dim1, size_type dim2) const;

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
     *  @brief      Select data.
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
     *              ranges of indices.
     *  @param[in]  firstDim1  First index in the dimension 1 to be copied.
     *  @param[in]  lastDim1  Last index in the dimension 1 to be copied.
     *  @param[in]  firstDim2  First index in the dimension 2 to be copied.
     *  @param[in]  lastDim2  Last index in the dimension 2 to be copied.
     *  @param[in]  firstDim3  First index in the dimension 3 to be copied.
     *  @param[in]  lastDim3  Last index in the dimension 3 to be copied.
     *  @returns    The new array with the selected data.
     */
    Array3D<T, Alloc> selectSubArray(
        size_type firstDim1, size_type lastDim1,
        size_type firstDim2, size_type lastDim2,
        size_type firstDim3, size_type lastDim3) const;

    /**
     *  @brief      Select indices.
     *  @details    This function returns an array with the elements that are into the specified
     *              ranges of indices.
     *  @tparam     IndexIt1  The type of iterator used to traverse the dimension 1.
     *  @tparam     IndexIt2  The type of iterator used to traverse the dimension 2.
     *  @tparam     IndexIt3  The type of iterator used to traverse the dimension 3.
     *  @param[in]  firstDim1  Beginning of the range of indices in the dimension 1.
     *  @param[in]  lastDim1  End of the range of indices in the dimension 1.
     *  @param[in]  firstDim2  Beginning of the range of indices in the dimension 2.
     *  @param[in]  lastDim2  End of the range of indices in the dimension 2.
     *  @param[in]  firstDim3  Beginning of the range of indices in the dimension 3.
     *  @param[in]  lastDim3  End of the range of indices in the dimension 3.
     *  @returns    The new array with the selected data.
     */
    template<std::random_access_iterator IndexIt1,
        std::random_access_iterator IndexIt2, std::random_access_iterator IndexIt3>
    Array3D<T, Alloc> selectIndices(IndexIt1 firstDim1, IndexIt1 lastDim1,
        IndexIt2 firstDim2, IndexIt2 lastDim2,
        IndexIt3 firstDim3, IndexIt3 lastDim3) const;

    /**
     *  @brief      Select indices.
     *  @details    This function returns an array with the selected indices.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  dim1  Indices of the selected dim1.
     *  @param[in]  dim2  Indices of the selected dim2.
     *  @param[in]  dim3  Indices of the selected dim3.
     *  @returns    The new array with the selected data.
     */
    template<typename AllocU>
    Array3D<T, Alloc> selectIndices(const Array<size_type, AllocU>& dim1,
        const Array<size_type, AllocU>& dim2,
        const Array<size_type, AllocU>& dim3) const;

    /**
     *  @brief      Select index in the dimension 1.
     *  @details    This function returns a new array that only contains the selected index in the
     *              dimension 1.
     *  @param[in]  dim1  The index in the dimension 1.
     *  @returns    The new array with the selected data.
     */
    Array3D<T, Alloc> selectDim1(size_type dim1) const;

    /**
     *  @brief      Select range of indices in the dimension 1.
     *  @details    This function returns the selected range of indices in the dimension 1.
     *  @param[in]  first  First index of the selected range.
     *  @param[in]  last  Last index of the selected range.
     *  @returns    The new array with the selected data.
     */
    Array3D<T, Alloc> selectDim1(size_type first, size_type last) const;

    /**
     *  @brief      Select indices in the dimension 1.
     *  @details    This function returns the items with indices in the dimension 1 that are
     *              specified in the range [first, last).
     *  @tparam     IndexIt  The iterator type to be used to indicate the indices.
     *  @param[in]  first  Beginning of the range of indices.
     *  @param[in]  last  End of the range of indices.
     *  @returns    The new array with the selected data.
     */
    template<std::random_access_iterator IndexIt>
    Array3D<T, Alloc> selectDim1(IndexIt first, IndexIt last) const;

    /**
     *  @brief      Select indices in the dimension 1.
     *  @details    This function returns the elements in the dimension 1 that are specified in
     *              the input parameters.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  dim1  The array with the selected indices.
     *  @returns    The new array with the selected data.
     */
    template<typename AllocU>
    Array3D<T, Alloc> selectDim1(const Array<size_type, AllocU>& dim1) const;

    /**
     *  @brief      Select index in the dimension 2.
     *  @details    This function returns a new array that only contains the selected index in the
     *  dimension 2.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @returns    The new array with the selected data.
     */
    Array3D<T, Alloc> selectDim2(size_type dim2) const;

    /**
     *  @brief      Select range of indices in the dimension 2.
     *  @details    This function returns the selected range of indices in the dimension 2.
     *  @param[in]  first  First index of the selected range.
     *  @param[in]  last  Last index of the selected range.
     *  @returns    The new array with the selected data.
     */
    Array3D<T, Alloc> selectDim2(size_type first, size_type last) const;

    /**
     *  @brief      Select indices in the dimension 2.
     *  @details    This function returns the items with indices in the dimension 2 that are
     *              specified in the range [first, last).
     *  @tparam     IndexIt  The iterator type to be used to indicate the indices.
     *  @param[in]  first  Beginning of the range of indices.
     *  @param[in]  last  End of the range of indices.
     *  @returns    The new array with the selected data.
     */
    template<std::random_access_iterator IndexIt>
    Array3D<T, Alloc> selectDim2(IndexIt first, IndexIt last) const;

    /**
     *  @brief      Select indices in the dimension 2.
     *  @details    This function returns the elements in the dimension 2 that are specified in
     *              the input parameters.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  dim2  The array with the selected indices.
     *  @returns    The new array with the selected data.
     */
    template<typename AllocU>
    Array3D<T, Alloc> selectDim2(const Array<size_type, AllocU>& dim2) const;

    /**
     *  @brief      Select index in the dimension 3.
     *  @details    This function returns a new array that only contains the selected index in the 
     *              dimension 3.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The new array with the selected data.
     */
    Array3D<T, Alloc> selectDim3(size_type dim3) const;

    /**
     *  @brief      Select range of indices in the dimension 3.
     *  @details    This function returns the selected range of indices in the dimension 3.
     *  @param[in]  first  First index of the selected range.
     *  @param[in]  last  Last index of the selected range.
     *  @returns    The new array with the selected data.
     */
    Array3D<T, Alloc> selectDim3(size_type first, size_type last) const;

    /**
     *  @brief      Select indices in the dimension 3.
     *  @details    This function returns the items with indices in the dimension 3 that are
     *              specified in the range [first, last).
     *  @tparam     IndexIt  The iterator type to be used to indicate the indices.
     *  @param[in]  first  Beginning of the range of indices.
     *  @param[in]  last  End of the range of indices.
     *  @returns    The new array with the selected data.
     */
    template<std::random_access_iterator IndexIt>
    Array3D<T, Alloc> selectDim3(IndexIt first, IndexIt last) const;

    /**
     *  @brief      Select indices in the dimension 3.
     *  @details    This function returns the elements in the dimension 3 that are specified in
     *              the input parameters.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  dim3  The array with the selected indices.
     *  @returns    The new array with the selected data.
     */
    template<typename AllocU>
    Array3D<T, Alloc> selectDim3(const Array<size_type, AllocU>& dim3) const;

    ////////// Circular shifts //////////

    /**
     *  @brief      Circular shift in the dimension 1.
     *  @details    This function circularly shifts the dimension 1 of the array. 
     *  @param[in]  i0  Index of the new first element in dimension 1.
     *  @returns    The new circular-shifted array.
     */
    Array3D<T, Alloc> circularDim1Shift(difference_type i0) const;

    /**
     *  @brief      Circular shift in the dimension 2.
     *  @details    This function circularly shifts the dimension 2 of the array. 
     *  @param[in]  j0  Index of the new first element in dimension 2.
     *  @returns    The new circular-shifted array.
     */
    Array3D<T, Alloc> circularDim2Shift(difference_type j0) const;

    /**
     *  @brief      Circular shift in the dimension 3.
     *  @details    This function circularly shifts the dimension 3 of the array. 
     *  @param[in]  k0  Index of the new first element in dimension 3.
     *  @returns    The new circular-shifted array.
     */
    Array3D<T, Alloc> circularDim3Shift(difference_type k0) const;

    /**
     *  @brief      Circular shift.
     *  @details    This function circularly shifts the values in the array. The new element of index (0, 0, 0)
     *              is specified in the arguments.
     *  @param[in]  i0  The index in dim1 of the new first element.
     *  @param[in]  j0  The index in dim2 of the new first element.
     *  @param[in]  k0  The index in dim3 of the new first element.
     *  @returns    The new circular-shifted array.
     */
    Array3D<T, Alloc> circularShift(difference_type i0, difference_type j0,
        difference_type k0) const;

    /**
     *  @brief      Circular shift.
     *  @details    This function circularly shifts the values of the array by (nd1/2, nd2/2, nd3/2) (the element
     *              indexed by (0, 0, 0) is moved to (nd1/2, nd2/2, nd3/2)).
     *  @returns    The new circular-shifted array.
     */
    Array3D<T, Alloc> circularShift() const;

    /**
     *  @brief      Inverse circular shift.
     *  @details    This function undo the circular shift performed by circularShift().
     *  @returns    The new circular-shifted array.
     */
    Array3D<T, Alloc> circularInvShift() const;

    ////////// Numerical operations //////////

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
     *  @brief      Euclidian norm.
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

    ////////// Special arrays //////////

    /**
     *  @brief      Constant.
     *  @details    This function creates an array and fills it with a constant value.
     *  @param[in]  dim1  Size in the dimension 1.
     *  @param[in]  dim2  Size in the dimension 2.
     *  @param[in]  dim3  Size in the dimension 3.
     *  @param[in]  t  Constant value.
     *  @returns    The new array.
     */
    static Array3D<T, Alloc> constant(size_type dim1, size_type dim2,
        size_type dim3, const_reference t);

    /**
     *  @brief      Zeros.
     *  @details    This function creates an array of zeros.
     *  @param[in]  dim1  Size in the dimension 1.
     *  @param[in]  dim2  Size in the dimension 2.
     *  @param[in]  dim3  Size in the dimension 3.
     *  @returns    The new array.
     */
    template<typename = void> requires nct::Numeric<T>
    static Array3D<T, Alloc> zeros(size_type dim1, size_type dim2, size_type dim3);

    /**
     *  @brief      Ones.
     *  @details    This function creates an array of ones.
     *  @param[in]  dim1  Size in the dimension 1.
     *  @param[in]  dim2  Size in the dimension 2.
     *  @param[in]  dim3  Size in the dimension 3.
     *  @returns    The new array.
     */
    template<typename = void> requires nct::Numeric<T>
    static Array3D<T, Alloc> ones(size_type dim1, size_type dim2, size_type dim3);    

    /**
     *  @brief      Filled cube.
     *  @details    This function returns an array whose elements inside the specified cube are set to val.
     *              The rest of the elements are set to T().
     *  @param[in]  dim1  Size in the dimension 1.
     *  @param[in]  dim2  Size in the dimension 2.
     *  @param[in]  dim3  Size in the dimension 3.
     *  @param[in]  c1  The index in dim 1 where the bounded area begins.
     *  @param[in]  c2  The index in dim 2 where the bounded area begins.
     *  @param[in]  c3  The index in dim 3 where the bounded area begins.
     *  @param[in]  l  Cube size.
     *  @param[in]  val  Value that is used to fill the bounded area.
     *  @returns    The new array.
     */
    static Array3D<T, Alloc> filledCube(size_type dim1, size_type dim2, size_type dim3,
        size_type c1, size_type c2, size_type c3, size_type l, const_reference val);

    /**
     *  @brief      Filled prism.
     *  @details    This function returns an array whose elements inside the specified prism are set to val.
     *              The rest of the elements are set to T().
     *  @param[in]  dim1  Size in the dimension 1.
     *  @param[in]  dim2  Size in the dimension 2.
     *  @param[in]  dim3  Size in the dimension 3.
     *  @param[in]  d0  The index in dim 1 where the bounded area begins.
     *  @param[in]  r0  The index in dim 2 where the bounded area begins.
     *  @param[in]  c0  The index in dim 3 where the bounded area begins.
     *  @param[in]  w1  Size of the shape in the dimension 1.
     *  @param[in]  w2  Size of the shape in the dimension 2.
     *  @param[in]  w3  Size of the shape in the dimension 3.
     *  @param[in]  val  Value that is used to fill the bounded area.
     *  @returns    The new array.
     */
    static Array3D<T, Alloc> filledPrism(size_type dim1, size_type dim2, size_type dim3,
        size_type c1, size_type c2, size_type c3,
        size_type w1, size_type w2, size_type w3, const_reference val);

    /**
     *  @brief      Filled sphere.
     *  @details    This function returns an array whose elements inside the specified sphere are set to val.
     *              The rest of the elements are set to T().
     *  @param[in]  dim1  Size in the dimension 1.
     *  @param[in]  dim2  Size in the dimension 2.
     *  @param[in]  dim3  Size in the dimension 3.
     *  @param[in]  d0  The index in dim 1 where the bounded area begins.
     *  @param[in]  r0  The index in dim 2 where the bounded area begins.
     *  @param[in]  c0  The index in dim 3 where the bounded area begins.
     *  @param[in]  r  The radius of the circle.
     *  @param[in]  val  Value that is used to fill the bounded area.
     *  @returns    The new array.
     */
    static Array3D<T, Alloc> filledSphere(size_type dim1, size_type dim2, size_type dim3,
        size_type c1, size_type c2, size_type c3, size_type r, const_reference val);

    /**
     *  @brief      Filled ellipsoid.
     *  @details    This function returns an array whose elements inside the specified ellipsoid are set to val.
     *              The rest of the elements are set to T().
     *  @param[in]  dim1  Size in the dimension 1.
     *  @param[in]  dim2  Size in the dimension 2.
     *  @param[in]  dim3  Size in the dimension 3.
     *  @param[in]  d0  The index in dim 1 where the bounded area begins.
     *  @param[in]  r0  The index in dim 2 where the bounded area begins.
     *  @param[in]  c0  The index in dim 3 where the bounded area begins.
     *  @param[in]  w1  The radius of the ellipse in the direction of the dimension 1.
     *  @param[in]  w2  The radius of the ellipse in the direction of the dimension 2.
     *  @param[in]  w3  The radius of the ellipse in the direction of the dimension 3.
     *  @param[in]  val  Value that is used to fill the bounded area.
     *  @returns    The new array.
     */
    static Array3D<T, Alloc> filledEllipsoid(size_type dim1, size_type dim2, size_type dim3,
        size_type c1, size_type c2, size_type c3,
        size_type w1, size_type w2, size_type w3, const_reference val);

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
     *  @brief      Beginning of the elements with the specified dim2 and dim3.
     *  @details    This function returns an iterator that points to the beginning of the elements with
     *              the specified dim2 and dim3. This iterator visits linearly the elements in the range
     *              ([0 ... nd1-1], dim2, dim3).
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    iterator beginDim1(size_type dim2, size_type dim3);

    /**
     *  @brief      Beginning of the elements with the specified dim2 and dim3.
     *  @details    This function returns an iterator that points to the beginning of the elements with
     *              the specified dim2 and dim3. This iterator visits linearly the elements in the range
     *              ([0 ... nd1-1], dim2, dim3).
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    const_iterator beginDim1(size_type dim2, size_type dim3) const;

    /**
     *  @brief      Beginning of the elements with the specified dim2 and dim3.
     *  @details    This function returns an iterator that points to the beginning of the elements with
     *              the specified dim2 and dim3. This iterator visits linearly the elements in the range
     *              ([0 ... nd1-1], dim2, dim3).
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    const_iterator cbeginDim1(size_type dim2, size_type dim3) const;

    /**
     *  @brief      End of the elements with the specified dim2 and dim3.
     *  @details    This function returns an iterator that points to the end of the elements with the
     *              specified dim2 and dim3. This iterator visits linearly the elements in the range ([0
     *              ... nd1-1], dim2, dim3).
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    iterator endDim1(size_type dim2, size_type dim3);

    /**
     *  @brief      End of the elements with the specified dim2 and dim3.
     *  @details    This function returns an iterator that points to the end of the elements with the
     *              specified dim2 and dim3. This iterator visits linearly the elements in the range ([0
     *              ... nd1-1], dim2, dim3).
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    const_iterator endDim1(size_type dim2, size_type dim3) const;

    /**
     *  @brief      End of the elements with the specified dim2 and dim3.
     *  @details    This function returns an iterator that points to the end of the elements with the
     *              specified dim2 and dim3. This iterator visits linearly the elements in the range ([0
     *              ... nd1-1], dim2, dim3).
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    const_iterator cendDim1(size_type dim2, size_type dim3) const;

    /**
     *  @brief      Beginning of the reversed elements with the specified dim2 and dim3.
     *  @details    This function returns an iterator that points to the beginning of the reversed
     *              elements with the specified dim2 and dim3. This iterator visits linearly the elements
     *              in the range ([nd1-1 ... 0], dim2, dim3).
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    reverse_iterator rbeginDim1(size_type dim2, size_type dim3);

    /**
     *  @brief      Beginning of the reversed elements with the specified dim2 and dim3.
     *  @details    This function returns an iterator that points to the beginning of the reversed
     *              elements with the specified dim2 and dim3. This iterator visits linearly the elements
     *              in the range ([nd1-1 ... 0], dim2, dim3).
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    const_reverse_iterator rbeginDim1(size_type dim2, size_type dim3) const;

    /**
     *  @brief      Beginning of the reversed elements with the specified dim2 and dim3.
     *  @details    This function returns an iterator that points to the beginning of the reversed
     *              elements with the specified dim2 and dim3. This iterator visits linearly the elements
     *              in the range ([nd1-1 ... 0], dim2, dim3).
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    const_reverse_iterator crbeginDim1(size_type dim2, size_type dim3) const;

    /**
     *  @brief      End of the reversed elements with the specified dim2 and dim3.
     *  @details    This function returns an iterator that points to the end of the reversed elements
     *              with the specified dim2 and dim3. This iterator visits linearly the elements in the
     *              range ([nd1-1 ... 0], dim2, dim3).
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    reverse_iterator rendDim1(size_type dim2, size_type dim3);

    /**
     *  @brief      End of the reversed elements with the specified dim2 and dim3.
     *  @details    This function returns an iterator that points to the end of the reversed elements
     *              with the specified dim2 and dim3. This iterator visits linearly the elements in the
     *              range ([nd1-1 ... 0], dim2, dim3).
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    const_reverse_iterator rendDim1(size_type dim2, size_type dim3) const;

    /**
     *  @brief      End of the reversed elements with the specified dim2 and dim3.
     *  @details    This function returns an iterator that points to the end of the reversed elements
     *              with the specified dim2 and dim3. This iterator visits linearly the elements in the
     *              range ([nd1-1 ... 0], dim2, dim3).
     *  @param[in]  dim2  The index in the dimension 2.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    const_reverse_iterator crendDim1(size_type dim2, size_type dim3) const;

    /**
     *  @brief      Beginning of the elements with the specified dim1 and dim3.
     *  @details    This function returns an iterator that points to the beginning of the elements with
     *              the specified dim1 and dim3. This iterator visits linearly the elements in the range
     *              (dim1, [0 ... nd2-1], dim3).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    iterator beginDim2(size_type dim1, size_type dim3);

    /**
     *  @brief      Beginning of the elements with the specified dim1 and dim3.
     *  @details    This function returns an iterator that points to the beginning of the elements with
     *              the specified dim1 and dim3. This iterator visits linearly the elements in the range
     *              (dim1, [0 ... nd2-1], dim3).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    const_iterator beginDim2(size_type dim1, size_type dim3) const;

    /**
     *  @brief      Beginning of the elements with the specified dim1 and dim3.
     *  @details    This function returns an iterator that points to the beginning of the elements with
     *              the specified dim1 and dim3. This iterator visits linearly the elements in the range
     *              (dim1, [0 ... nd2-1], dim3).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    const_iterator cbeginDim2(size_type dim1, size_type dim3) const;

    /**
     *  @brief      End of the elements with the specified dim1 and dim3.
     *  @details    This function returns an iterator that points to the end of the elements with the
     *              specified dim1 and dim3. This iterator visits linearly the elements in the range
     *              (dim1, [0 ... nd2-1], dim3).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    iterator endDim2(size_type dim1, size_type dim3);

    /**
     *  @brief      End of the elements with the specified dim1 and dim3.
     *  @details    This function returns an iterator that points to the end of the elements with the
     *              specified dim1 and dim3. This iterator visits linearly the elements in the range
     *              (dim1, [0 ... nd2-1], dim3).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    const_iterator endDim2(size_type dim1, size_type dim3) const;
    
    /**
     *  @brief      End of the elements with the specified dim1 and dim3.
     *  @details    This function returns an iterator that points to the end of the elements with the specified dim1
     *              and dim3. This iterator visits linearly the elements in the range (dim1, [0 ...
     *              nd2-1], dim3).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    const_iterator cendDim2(size_type dim1, size_type dim3) const;

    /**
     *  @brief      Beginning of the reversed elements with the specified dim1 and dim3.
     *  @details    This function returns an iterator that points to the beginning of the reversed
     *              elements with the specified dim1 and dim3. This iterator visits linearly the elements
     *              in the range (dim1, [nd2-1 ... 0], dim3).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    reverse_iterator rbeginDim2(size_type dim1, size_type dim3);

    /**
     *  @brief      Beginning of the reversed elements with the specified dim1 and dim3.
     *  @details    This function returns an iterator that points to the beginning of the reversed
     *              elements with the specified dim1 and dim3. This iterator visits linearly the elements
     *              in the range (dim1, [nd2-1 ... 0], dim3).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    const_reverse_iterator rbeginDim2(size_type dim1, size_type dim3) const;

    /**
     *  @brief      Beginning of the reversed elements with the specified dim1 and dim3.
     *  @details    This function returns an iterator that points to the beginning of the reversed
     *              elements with the specified dim1 and dim3. This iterator visits linearly the elements
     *              in the range (dim1, [nd2-1 ... 0], dim3).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    const_reverse_iterator crbeginDim2(size_type dim1, size_type dim3) const;

    /**
     *  @brief      End of the reversed elements with the specified dim1 and dim3.
     *  @details    This function returns an iterator that points to the end of the reversed elements
     *              with the specified dim1 and dim3. This iterator visits linearly the elements in the
     *              range (dim1, [nd2-1 ... 0], dim3).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    reverse_iterator rendDim2(size_type dim1, size_type dim3);

    /**
     *  @brief      End of the reversed elements with the specified dim1 and dim3.
     *  @details    This function returns an iterator that points to the end of the reversed elements
     *              with the specified dim1 and dim3. This iterator visits linearly the elements in the
     *              range (dim1, [nd2-1 ... 0], dim3).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    const_reverse_iterator rendDim2(size_type dim1, size_type dim3) const;
    
    /**
     *  @brief      End of the reversed elements with the specified dim1 and dim3.
     *  @details    This function returns an iterator that points to the end of the reversed elements
     *              with the specified dim1 and dim3. This iterator visits linearly the elements in the
     *              range (dim1, [nd2-1 ... 0], dim3).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim3  The index in the dimension 3.
     *  @returns    The iterator.
     */
    const_reverse_iterator crendDim2(size_type dim1, size_type dim3) const;

    /**
     *  @brief      Beginning of the elements with the specified dim1 and dim2.
     *  @details    This function returns an iterator that points to the beginning of the elements with
     *              the specified dim1 and dim2. This iterator visits linearly the elements in the range
     *              (dim1, dim2, [0 ... nd3-1]).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @returns    The iterator.
     */
    iterator beginDim3(size_type dim1, size_type dim2);

    /**
     *  @brief      Beginning of the elements with the specified dim1 and dim2.
     *  @details    This function returns an iterator that points to the beginning of the elements with
     *              the specified dim1 and dim2. This iterator visits linearly the elements in the range
     *              (dim1, dim2, [0 ... nd3-1]).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @returns    The iterator.
     */
    const_iterator beginDim3(size_type dim1, size_type dim2) const;
    
    /**
     *  @brief      Beginning of the elements with the specified dim1 and dim2.
     *  @details    This function returns an iterator that points to the beginning of the elements with
     *              the specified dim1 and dim2. This iterator visits linearly the elements in the range
     *              (dim1, dim2, [0 ... nd3-1]).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @returns    The iterator.
     */
    const_iterator cbeginDim3(size_type dim1, size_type dim2) const;

    /**
     *  @brief      End of the elements with the specified dim1 and dim2.
     *  @details    This function returns an iterator that points to the end of the elements with the
     *              specified dim1 and dim2. This iterator visits linearly the elements in the range
     *              (dim1, dim2, [0 ... nd3-1]).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @returns    The iterator.
     */
    iterator endDim3(size_type dim1, size_type dim2);

    /**
     *  @brief      End of the elements with the specified dim1 and dim2.
     *  @details    This function returns an iterator that points to the end of the elements with the
     *              specified dim1 and dim2. This iterator visits linearly the elements in the range
     *              (dim1, dim2, [0 ... nd3-1]).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @returns    The iterator.
     */
    const_iterator endDim3(size_type dim1, size_type dim2) const;

    /**
     *  @brief      End of the elements with the specified dim1 and dim2.
     *  @details    This function returns an iterator that points to the end of the elements with the
     *              specified dim1 and dim2. This iterator visits linearly the elements in the range
     *              (dim1, dim2, [0 ... nd3-1]).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @returns    The iterator.
     */
    const_iterator cendDim3(size_type dim1, size_type dim2) const;

    /**
     *  @brief      Beginning of the reversed elements with the specified dim1 and dim2.
     *  @details    This function returns an iterator that points to the beginning of the reversed
     *              elements with the specified dim1 and dim2. This iterator visits linearly the elements
     *              in the range (dim1, dim2, [nd3-1 ... 0]).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @returns    The iterator.
     */
    reverse_iterator rbeginDim3(size_type dim1, size_type dim2);

    /**
     *  @brief      Beginning of the reversed elements with the specified dim1 and dim2.
     *  @details    This function returns an iterator that points to the beginning of the reversed
     *              elements with the specified dim1 and dim2. This iterator visits linearly the elements
     *              in the range (dim1, dim2, [nd3-1 ... 0]).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @returns    The iterator.
     */
    const_reverse_iterator rbeginDim3(size_type dim1, size_type dim2) const;

    /**
     *  @brief      Beginning of the reversed elements with the specified dim1 and dim2.
     *  @details    This function returns an iterator that points to the beginning of the reversed
     *              elements with the specified dim1 and dim2. This iterator visits linearly the elements
     *              in the range (dim1, dim2, [nd3-1 ... 0]).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @returns    The iterator.
     */
    const_reverse_iterator crbeginDim3(size_type dim1, size_type dim2) const;

    /**
     *  @brief      End of the reversed elements with the specified dim1 and dim2.
     *  @details    This function returns an iterator that points to the end of the reversed elements
     *              with the specified dim1 and dim2. This iterator visits linearly the elements in the
     *              range (dim1, dim2, [nd3-1 ... 0]).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @returns    The iterator.
     */
    reverse_iterator rendDim3(size_type dim1, size_type dim2);
    
    /**
     *  @brief      End of the reversed elements with the specified dim1 and dim2.
     *  @details    This function returns an iterator that points to the end of the reversed elements
     *              with the specified dim1 and dim2. This iterator visits linearly the elements in the
     *              range (dim1, dim2, [nd3-1 ... 0]).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @returns    The iterator.
     */
    const_reverse_iterator rendDim3(size_type dim1, size_type dim2) const;
    
    /**
     *  @brief      End of the reversed elements with the specified dim1 and dim2.
     *  @details    This function returns an iterator that points to the end of the reversed elements
     *              with the specified dim1 and dim2. This iterator visits linearly the elements in the
     *              range (dim1, dim2, [nd3-1 ... 0]).
     *  @param[in]  dim1  The index in the dimension 1.
     *  @param[in]  dim2  The index in the dimension 2.
     *  @returns    The iterator.
     */
    const_reverse_iterator crendDim3(size_type dim1, size_type dim2) const;

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
    Array3D<U, AllocU> transformData(const std::function<U(const_reference)>& f) const;

    /**
     *  @brief      Collapse dimension 1.
     *  @details    This function transforms the elements of each dim2-dim3 pair into a scalar value.
     *  @tparam     U  The data type of the output array.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  f  Function that will be used to transform the elements. The function only requires
     *              one argument, a const_reference to an array. This argument represents a sub-array
     *              with the elements of fixed indices dim2 and dim3. Also, the function returns an
     *              escalar of type U.
     *  @returns    The new array.
     */
    template<typename U, typename AllocU = std::allocator<U>>
    Array3D<U, AllocU> collapseDim1(const std::function<U(const Array<T, Alloc>&)>& f) const;

    /**
     *  @brief      Collapse dimension 1.
     *  @details    This function transforms the elements of each dim2-dim3 pair into a scalar value.
     *  @tparam     U  The data type of the output array.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  f  Function that will be used to transform the elements. The function  
     *              requires two arguments, the iterators of the beginning and the end of a range among
     *              the dimension 1. Also, the function returns an escalar of type U.
     *  @returns    The new array.
     */
    template<typename U, typename AllocU = std::allocator<U>>
    Array3D<U, AllocU> collapseDim1(const std::function<U(const_iterator, const_iterator)>& f) const;

    /**
     *  @brief      Collapse dimension 2.
     *  @details    This function transforms the elements of each dim1-dim3 pair into a scalar value.
     *  @tparam     U  The data type of the output array.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  f  Function that will be used to transform the elements. The function only requires
     *              one argument, a const_reference to an array. This argument represents a sub-array
     *              with the elements of fixed indices dim1 and dim3. Also, the function returns an
     *              escalar of type U.
     *  @returns    The new array.
     */
    template<typename U, typename AllocU = std::allocator<U>>
    Array3D<U, AllocU> collapseDim2(const std::function<U(const Array<T, Alloc>&)>& f) const;

    /**
     *  @brief      Collapse dimension 2.
     *  @details    This function transforms the elements of each dim1-dim3 pair into a scalar value.
     *  @tparam     U  The data type of the output array.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  f  Function that will be used to transform the elements. The function requires two
     *              arguments, the iterators of the beginning and the end of a range among the dimension
     *              2. Also, the function returns an escalar of type U.
     *  @returns    The new array.
     */
    template<typename U, typename AllocU = std::allocator<U>>
    Array3D<U, AllocU> collapseDim2(const std::function<U(const_iterator, const_iterator)>& f) const;

    /**
     *  @brief      Collapse dimension 3.
     *  @details    This function transforms the elements of each dim1-dim2 pair into a scalar value.
     *  @tparam     U  The data type of the output array.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  f  Function that will be used to transform the elements. The function only requires
     *              one argument, a const_reference to an array. This argument represents a sub-array
     *              with the elements of fixed indices dim1 and dim2. Also, the function returns an
     *              escalar of type U.
     *  @returns    The new array.
     */
    template<typename U, typename AllocU = std::allocator<U>>
    Array3D<U, AllocU> collapseDim3(const std::function<U(const Array<T, Alloc>&)>& f) const;

    /**
     *  @brief      Collapse dimension 3.
     *  @details    This function transforms the elements of each dim1-dim2 pair into a scalar value.
     *  @tparam     U  The data type of the output array.
     *  @tparam     AllocU  The type of allocator to be used to build the output array.
     *  @param[in]  f  Function that will be used to transform the elements. The function  
     *              requires two arguments, the iterators of the beginning and the end of a range among
     *              the dimension 1. Also, the function returns an escalar of type U.
     *  @returns    The new array.
     */
    template<typename U, typename AllocU = std::allocator<U>> 
    Array3D<U, AllocU> collapseDim3(const std::function<U(const_iterator, const_iterator)>& f) const;

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
    static Array3D<T, Alloc> read(std::istream& i);

protected:

    ////////// Data members //////////        

    allocator_type alloc_;  /**< Allocator object. */

    size_type n_ {0};       /**< Number of elements into the array. */

    size_type nd1_ {0};     /**< Size of dimension 1. */

    size_type nd2_ {0};     /**< Size of dimension 2. */

    size_type nd3_ {0};     /**< Size of dimension 3. */

    pointer data_ {nullptr};/**< Array of objects. */

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
T dotProduct(const Array3D<T, Alloc>& a, const Array3D<T, Alloc>& b);

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
Array3D<T, Alloc> operator&(Array3D<T, Alloc>&& left, const Array3D<T, Alloc>& right);

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
Array3D<T, Alloc> operator|(Array3D<T, Alloc>&& left, const Array3D<T, Alloc>& right);

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
Array3D<T, Alloc> operator^(Array3D<T, Alloc>&& left, const Array3D<T, Alloc>& right);

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
Array3D<T, Alloc> operator+(Array3D<T, Alloc>&& left, const Array3D<T, Alloc>& right);

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
Array3D<T, Alloc> operator-(Array3D<T, Alloc>&& left, const Array3D<T, Alloc>& right);

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
Array3D<T, Alloc> operator*(const T& left, const Array3D<T, Alloc>& right);

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
std::istream& operator>>(std::istream& i, Array3D<T, Alloc>& arr);

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
std::ostream& operator<<(std::ostream& o, const Array3D<T, Alloc>& arr);

}

////////// Implementation of class template //////////
#include <nct/Array3D_template.h> 

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
