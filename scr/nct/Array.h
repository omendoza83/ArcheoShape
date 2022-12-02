//=================================================================================================================
/**
 *  @file       Array.h
 *  @brief      nct::Array class template.
 *  @details    Declaration of the nct::Array class template.
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

#ifndef NCT_ARRAY_H_INCLUDE
#define NCT_ARRAY_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/array_iterator.h>

#include <initializer_list>
#include <iostream>
#include <functional>

//=================================================================================================================
namespace nct {

////////// Type definitions //////////

template<typename T, typename Alloc = std::allocator<T>>
class Array;

/** Real vector. */
using RealVector = nct::Array<double, std::allocator<double>>;

/** Complex vector. */
using ComplexVector = nct::Array<nct::Complex, std::allocator<nct::Complex>>;

/** Column vector. */
using ColumnVector = nct::Array<double, std::allocator<double>>;

/** Complex column vector. */
using ComplexColumnVector = nct::Array<nct::Complex, std::allocator<nct::Complex>>;

/** Row vector. */
using RowVector = nct::Array<double, std::allocator<double>>;

/** Complex row vector. */
using ComplexRowVector = nct::Array<nct::Complex, std::allocator<nct::Complex>>;

////////// Classes ////////// 

/**
 *  @brief      Class template for 1-dimensional arrays of objects. 
 *  @details    This class template is used to manipulate 1D arrays of objects.
 *  @note       It is possible to disable index checking in the [] operator by defining
 *              NCT_ARRAY_DISABLE_INDEX_CHECKING.
 *  @tparam     T  The data type to be stored in the array.
 *  @tparam     Alloc  The type of allocator to be used to build the array.
 */
template<typename T, typename Alloc>
class Array {

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
    using iterator = nct::array_iterator<Array<T, Alloc>, value_type,
        difference_type, pointer, reference>;

    /** Const iterator. */
    using const_iterator = nct::array_iterator<Array<T, Alloc>, const value_type,
        difference_type, const_pointer, const_reference>;

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
    explicit Array(const allocator_type& allocator = allocator_type()) noexcept;

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes an array of size s.
     *  @param[in] s  Array size.
     *  @param[in]  allocator  Allocator object. The container keeps and uses an internal copy of this
     *              allocator.
     */
    explicit Array(size_type s, const allocator_type& allocator = allocator_type());

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes an array of size s and sets each element to val.
     *  @param[in]  s  Array size.
     *  @param[in]  val  Value that is taken by all the new elements inside the array.
     *  @param[in]  allocator  Allocator object. The container keeps and uses an internal copy of this
     *              allocator.
     */
    Array(size_type s, const_reference val,
        const allocator_type& allocator = allocator_type());

    /**
     *  @brief      Class constructor from range.
     *  @details    This constructor initializes an array by copying the elements of the specified range.
     *  @tparam     InputIt  The iterator type to be used to traverse the input data.
     *  @param[in]  first  Beginning of the range of elements to be copied.
     *  @param[in]  last  end of the range of elements to be copied.
     *  @param[in]  allocator  Allocator object. The container keeps and uses an internal copy of this
     *              allocator.
     */
    template<class InputIt>
    Array(InputIt first, InputIt last, const allocator_type& allocator = allocator_type());

    /**
     *  @brief      Class constructor from initializer list.
     *  @details    This constructor initializes an array by copying the elements of the specified
     *              initializer list.
     *  @param[in]  il  Initializer list.
     *  @param[in]  allocator  Allocator object. The container keeps and uses an internal copy of this
     *  allocator.
     */
    Array(std::initializer_list<value_type> il,
        const allocator_type& allocator = allocator_type());

    /**
     *  @brief      Copy constructor.
     *  @details    This constructor copies the contents of an object of the same type.
     *  @param[in]  other  Another object of the same type whose contents are copied.
     */
    Array(const Array<T, Alloc>& other);

    /**
     *  @brief      Copy constructor.
     *  @details    This constructor copies the contents of an object of the same type.
     *  @param[in]  other  Another object of the same type whose contents are copied.
     *  @param[in]  allocator  Allocator object. The container keeps and uses an internal copy of this
     *              allocator.
     */
    Array(const Array<T, Alloc>& other, const allocator_type& allocator);

    /**
     *  @brief      Move constructor.
     *  @details    This constructor moves the contents of an object to the new class instance.
     *  @param[in]  other  Another object of the same type whose contents are acquired.
     */
    Array(Array<T, Alloc>&& other) noexcept;

    /**
     *  @brief      Move constructor.
     *  @details    This constructor moves the contents of an object to the new class instance.
     *  @param[in]  other  Another object of the same type whose contents are acquired.
     *  @param[in]  allocator  Allocator object. The container keeps and uses an internal copy of this
     *              allocator.
     */
    Array(Array<T, Alloc>&& other, const allocator_type& allocator);

    ////////// Constructors //////////

    /**
     *  @brief      Destructor.
     *  @details    Class destructor.
     */
    ~Array() noexcept;

    ////////// Operators //////////        

    /**
     *  @brief      Assignment operator.
     *  @details    This operator copies the contents of an object of the same type.
     *  @param[in]  other  Another object of the same type whose contents are copied.
     *  @returns    A reference to the object.
     */
    Array<T, Alloc>& operator=(const Array<T, Alloc>& other);

    /**
     *  @brief      Move-assignment operator.
     *  @details    This operator acquires the contents of another object.
     *  @param[in]  other  Another object of the same type whose contents are acquired.
     *  @returns    A reference to the object.
     */
    Array<T, Alloc>& operator=(Array<T, Alloc>&& other) noexcept;    

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
    bool operator==(const Array<T, Alloc>& right) const;

    /**
     *  @brief      Inequality operator.
     *  @details    Two arrays are not equal if have different same size or element
     *              of one array is not equal to the element with the same index in the other array.
     *  @param[in]  right  Array to compare.
     *  @returns    True if both arrays are not equal.
     */
    template<typename = void> requires std::equality_comparable<T>
    bool operator!=(const Array<T, Alloc>& right) const;

    /**
     *  @brief      Bitwise AND.
     *  @details    This operator performs the bitwise "and" operation for each index of the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires std::integral<T>
    Array<T, Alloc> operator&(const Array<T, Alloc>& right) const;

    /**
     *  @brief      Bitwise AND.
     *  @details    This operator performs the bitwise "and" operation for each index of the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires std::integral<T>
    const Array<T, Alloc>& operator&=(const Array<T, Alloc>& right);

    /**
     *  @brief      Bitwise OR.
     *  @details    This operator performs the bitwise "or" operation for each index of the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires std::integral<T>
    Array<T, Alloc> operator|(const Array<T, Alloc>& right) const;

    /**
     *  @brief      Bitwise OR.
     *  @details    This operator performs the bitwise "or" operation for each index of the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires std::integral<T>
    const Array<T, Alloc>& operator|=(const Array<T, Alloc>& right);

    /**
     *  @brief      Bitwise XOR.
     *  @details    This operator performs the bitwise "xor" operation for each index of the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires std::integral<T>
    Array<T, Alloc> operator^(const Array<T, Alloc>& right) const;

    /**
     *  @brief      Bitwise XOR.
     *  @details    This operator performs the bitwise "xor" operation for each index of the arrays.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires std::integral<T>
    const Array<T, Alloc>& operator^=(const Array<T, Alloc>& right);

    /**
     *  @brief      Unary plus.
     *  @details    This operator multiplies by one each element inside the array.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires nct::Numeric<T>
    Array<T, Alloc> operator+() const;

    /**
     *  @brief      Array addition.
     *  @details    This operator calculates the sum of two matrices.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires nct::Addable<T>
    Array<T, Alloc> operator+(const Array<T, Alloc>& right) const;

    /**
     *  @brief      Array addition.
     *  @details    This operator calculates the sum of two matrices and stores the result in the same
     *              instance.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    A reference to the object.
     */    
    template<typename = void> requires nct::Addable<T>
    const Array<T, Alloc>& operator+=(const Array<T, Alloc>& right);

    /**
     *  @brief      Unary minus.
     *  @details    This operator multiplies by minus one each element inside the array.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires nct::SignedNumeric<T>
    Array<T, Alloc> operator-() const;

    /**
     *  @brief      Array substraction.
     *  @details    This operator calculates the substraction of two matrices.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    The array with the result of the operation.
     */    
    template<typename = void> requires nct::Substractable<T>
    Array<T, Alloc> operator-(const Array<T, Alloc>& right) const;

    /**
     *  @brief      Array substraction.
     *  @details    This operator calculates the substraction of two matrices and stores the result in 
     *              the same instance.
     *  @param[in]  right  Array on the right side of the operation.
     *  @returns    A reference to the object.
     */    
    template<typename = void> requires nct::Substractable<T>
    const Array<T, Alloc>& operator-=(const Array<T, Alloc>& right);

    /**
     *  @brief      Scalar product.
     *  @details    This operator calculates the multiplication of the array by a scalar.
     *  @param[in]  right  Scalar value.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires nct::Numeric<T>
    Array<T, Alloc> operator*(const_reference right) const;

    /**
     *  @brief      Scalar product.
     *  @details    This operator calculates the multiplication of the array by a scalar and stores the 
     *              result in the same instance.
     *  @param[in]  right  Scalar value.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires nct::Numeric<T>
    const Array<T, Alloc>& operator*=(const_reference right);

    /**
     *  @brief      Scalar division.
     *  @details    This operator calculates the division of the array by a scalar.
     *  @param[in]  right  Scalar value.
     *  @returns    The array with the result of the operation.
     */
    template<typename = void> requires nct::Numeric<T>
    Array<T, Alloc> operator/(const_reference right) const;

    /**
     *  @brief      Scalar division.
     *  @details    This operator calculates the division of the array by a scalar and stores the 
     *              result in the same instance.
     *  @param[in]  right  Scalar value.
     *  @returns    A reference to the object.
     */
    template<typename = void> requires nct::Numeric<T>
    const Array<T, Alloc>& operator/=(const_reference right);

    ////////// Basic member functions //////////        

    /**
     *  @brief      Clears array contents.
     *  @details    This function releases the allocated memory.
     */
    void clear() noexcept;

    /**
     *  @brief      Assigns contents to the array.
     *  @details    This function assigns new contents to the array, replacing its current
     *              contents, and modifying its size accordingly.
     *  @param[in]  s  Array size.
     *  @param[in]  val  Value that is taken by all the elements inside the array.
     */
    void assign(size_type s, const_reference val);

    /**
     *  @brief      Resizes the array.
     *  @details    This function modifies the size of the array. The original data contained in
     *              the array keep their original positions and elements beyond the boundaries are
     *              erased. If new positions are added to the array, the new elements are set according
     *              to the default constructor.
     *  @param[in]  s  Array size.
     */
    void resize(size_type s);

    /**
     *  @brief      Resizes the array.
     *  @details    This function modifies the size of the array. The original data contained in
     *              the array
     *              keep their original positions and elements beyond the boundaries are erased. If new
     *              positions are added to the array, the new elements are set to val.
     *  @param[in]  s  Array size.
     *  @param[in]  val  Value that is taken by all the new elements inside the array.
     */
    void resize(size_type s, const_reference val);

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
     *  @brief      Copies another array.
     *  @details    This function copies the contents of other array.
     *  @param[in]  other  Array to copy.
     */
    void copy(const Array<T, Alloc>& other);

    /**
     *  @brief      Is the array empty?
     *  @details    This function tests whether the array is empty.
     *  @returns    True, if the array is empty.
     */
    bool empty() const noexcept;

    /**
     *  @brief      Returns the array size.
     *  @details    This function returns the number of elements in the array.
     *  @returns    The number of elements.
     */
    size_type size() const noexcept;

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
     *  @brief      Reference to one element.
     *  @details    This function returns a reference to the specified object. The function
     *              verifies whether the index is out of range.
     *  @param[in]  index  The index of the object to be returned.
     *  @returns    The chosen object.
     */
    reference at(size_type index);

    /**
     *  @brief      Reference to one element.
     *  @details    This function returns a reference to the specified object. The function
     *              verifies whether the index is out of range.
     *  @param[in]  index  The index of the object to be returned.
     *  @returns    The chosen object.
     */
    const_reference at(size_type index) const;

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
    Array<U, AllocU> toArray() const;

    /**
     *  @brief      From container.
     *  @details    This function creates a new array by copying the contents of a
     *              sequential container.
     *  @tparam     C  The type of container of the input data.
     *  @param[in]  container  Input container.
     *  @returns    The new array.
     */
    template<typename C>
    static Array<T, Alloc> fromContainer(const C& container);

    /**
     *  @brief      From sub-script.
     *  @details    This function creates a new array by copying the items indexed by (i)
     *              into a container of containers. That means, "container" contains functors
     *              or objects that have implemented the operator (i), and this function
     *              copies the value returned by calling the operator (i) for each object.
     *  @tparam     C  The type of container of the input data.
     *  @param[in]  container  Input container.
     *  @param[in]  i  Index value.
     *  @returns    The new array.
     */
    template<typename C>
    static Array<T, Alloc> fromSubscript(const C& container, size_type i);

    /**
     *  @brief      From sub-script.
     *  @details    This function creates a new array by copying the items indexed by (i, j)
     *              into a container of containers. That means, "container" contains functors
     *              or objects that have implemented the operator (i, j), and this function
     *              copies the value returned by calling the operator (i, j) for each object.
     *  @tparam     C  The type of container of the input data.
     *  @param[in]  container  Input container.
     *  @param[in]  i  Index value.
     *  @param[in]  j  Index value.
     *  @returns    The new array.
     */
    template<typename C>
    static Array<T, Alloc> fromSubscript(const C& container, size_type i, size_type j);

    /**
     *  @brief      From sub-script.
     *  @details    This function creates a new array by copying the items indexed by (i, j, k)
     *              into a container of containers. That means, "container" contains functors
     *              or objects that have implemented the operator (i, j, k), and this function
     *              copies the value returned by calling the operator (i, j, k) for each object.
     *  @tparam     C  The type of container of the input data.
     *  @param[in]  container  Input container.
     *  @param[in]  i  Index value.
     *  @param[in]  j  Index value.
     *  @param[in]  k  Index value.
     *  @returns    The new array.
     */
    template<typename C>
    static Array<T, Alloc> fromSubscript(const C& container, size_type i, size_type j, size_type k);

    /**
     *  @brief      From sub-script.
     *  @details    This function creates a new array by copying the items indexed by (i, j, k, l)
     *              into a container of containers. That means, "container" contains functors
     *              or objects that have implemented the operator (i, j, k, l), and this function
     *              copies the value returned by calling the operator (i, j, k, l) for each object.
     *  @tparam     C  The type of container of the input data.
     *  @param[in]  container  Input container.
     *  @param[in]  i  Index value.
     *  @param[in]  j  Index value.
     *  @param[in]  k  Index value.
     *  @param[in]  l  Index value.
     *  @returns    The new array.
     */
    template<typename C>
    static Array<T, Alloc> fromSubscript(const C& container,
        size_type i, size_type j, size_type k, size_type l);

    ////////// Data insertions and deletions //////////

    /**
     *  @brief      Add one element at the end.
     *  @details    This function adds a new element at the end of the container.
     *  @param[in]  val  Object that is used to initialize the new element.
     */
    void push_back(const_reference val);

    /**
     *  @brief      Add one element at the end.
     *  @details    This function adds a new element at the end of the container.
     *  @param[in]  val  Temporal object that is used to initialize the new element.
     */
    void push_back(rvalue_reference val);

    /**
     *  @brief      Remove element at the end of the container.
     *  @details    This function removes the last element of the container.
     */
    void pop_back();

    /**
     *  @brief      Insert element.
     *  @details    This function inserts one new item at the specified position.
     *  @param[in]  position  Index where the new item will be inserted.
     *  @param[in]  val  Object that is used to initialize the new element.
     *  @returns    An interator pointing to the new location where the
     *              inserted item is stored inside the container.
     */
    iterator insert(size_type position, const_reference val);

    /**
     *  @brief      Insert element.
     *  @details    This function inserts one new item at the specified position.
     *  @param[in]  position  Index where the new item will be inserted.
     *  @param[in]  val  Temporal object that is used to initialize the new element.
     *  @returns    An interator pointing to the new location where the
     *              inserted item is stored inside the container.
     */
    iterator insert(size_type position, rvalue_reference val);

    /**
     *  @brief      Insert element.
     *  @details    This function inserts one new item at the specified position.
     *  @param[in]  position  Iterator that indicates the position where the new
     *              item will be inserted.
     *  @param[in]  val  Object that is used to initialize the new element.
     *  @returns    An interator pointing to the new location where the
     *              inserted item is stored inside the container.
     */
    iterator insert(const_iterator position, const_reference val);

    /**
     *  @brief      Insert element.
     *  @details    This function inserts one new item at the specified position.
     *  @param[in]  position  Iterator that indicates the position where the new
     *              item will be inserted.
     *  @param[in]  val  Temporal object that is used to initialize the new element.
     *  @returns    An interator pointing to the new location where the
     *              inserted item is stored inside the container.
     */
    iterator insert(const_iterator position, rvalue_reference val);

    /**
     *  @brief      Insert range.
     *  @details    This function inserts a range of new items starting at the specified position.
     *  @tparam     InputIt  The type of iterator of the input data.
     *  @param[in]  position  Index where the first new item will be inserted.
     *  @param[in]  first  Beginning of the range with the elements to insert.
     *  @param[in]  last  End of the range with the elements to insert.
     *  @returns    An interator pointing to the new location of the
     *              first inserted item.
     */
    template<std::random_access_iterator InputIt>
    iterator insert(size_type position, InputIt first, InputIt last);

    /**
     *  @brief      Insert range.
     *  @details    This function inserts a range of new items starting at the specified position.
     *  @tparam     InputIt  The type of iterator of the input data.
     *  @param[in]  position  Iterator that indicates the position where the new
     *              items will be inserted.
     *  @param[in]  first  Beginning of the range with the elements to insert.
     *  @param[in]  last  End of the range with the elements to insert.
     *  @returns    An interator pointing to the new location of the
     *              first inserted item.
     */
    template<std::random_access_iterator InputIt>
    iterator insert(const_iterator position, InputIt first, InputIt last);

    /**
     *  @brief      Insert initializer list.
     *  @details    This function inserts an initializer list starting at the specified position.
     *  @param[in]  position  Index where the first new item will be inserted.
     *  @param[in]  il  Initializer list.
     *  @returns    An interator pointing to the new location of the
     *              first inserted item.
     */
    iterator insert(size_type position, std::initializer_list<value_type> il);

    /**
     *  @brief      Insert initializer list.
     *  @details    This function inserts a initializer list starting at the specified position.
     *  @param[in]  position  Iterator that indicates the position where the new
     *              items will be inserted.
     *  @param[in]  il  Initializer list.
     *  @returns    An interator pointing to the new location of the
     *              first inserted item.
     */
    iterator insert(const_iterator position, std::initializer_list<value_type> il);

    /**
     *  @brief      Insert array.
     *  @details    This function inserts an array starting at the specified position.
     *  @param[in]  position  Index where the first new item will be inserted.
     *  @param[in]  data  Array that contains the elements that will be inserted.
     *  @returns    An interator pointing to the new location of the
     *              first inserted item.
     */
    iterator insert(size_type position, const Array<T, Alloc>& data);

    /**
     *  @brief      Insert array.
     *  @details    This function inserts an array starting at the specified position.
     *  @param[in]  position  Iterator that indicates the position where the new
     *              items will be inserted.
     *  @param[in]  data  Array that contains the elements that will be inserted.
     *  @returns    An interator pointing to the new location of the
     *              first inserted item.
     */
    iterator insert(const_iterator position, const Array<T, Alloc>& data);

    /**
     *  @brief      Erase element.
     *  @details    This function removes one element of the container.
     *  @param[in]  position  Index of the element to remove.
     *  @returns    An interator pointing to the new location of the element that followed the last
     *              element erased by the function call.
     */
    iterator erase(size_type position);

    /**
     *  @brief      Erase element.
     *  @details    This function removes one element of the container.
     *  @param[in]  position  Iterator that is pointing to the element to be removed by
     *              the function call.
     *  @returns    An interator pointing to the new location of the element that followed the last
     *              element erased by the function call.
     */
    iterator erase(const_iterator position);

    /**
     *  @brief      Erase range.
     *  @details    This function removes the items between the specified indices.
     *  @param[in]  first  Index of the first element to remove.
     *  @param[in]  last  Index of the last element to remove.
     *  @returns    An interator pointing to the new location of the element that followed the last
     *              element erased by the function call.
     */
    iterator erase(size_type first, size_type last);

    /**
     *  @brief      Erase range.
     *  @details    This function removes the range of elements [first, last).
     *  @param[in]  first  Beginning of the range of elements to remove.
     *  @param[in]  last  End of the range of elements to remove.
     *  @returns    An interator pointing to the new location of the element that followed the last
     *              element erased by the function call.
     */
    iterator erase(const_iterator first, const_iterator last);

    /**
     *  @brief      Erase elements.
     *  @details    This function removes the elements that are specified in the range [first,
     *              last). The range indicates the indices of the items to erase from the container.
     *  @tparam     IndexIt  The iterator type to be used to indicate the indices.
     *  @param[in]  first  Beginning of the range that indicates the elements to be removed.
     *  @param[in]  last  End of the range that indicates the elements to be removed.
     */
    template<std::random_access_iterator IndexIt>
    void eraseElements(IndexIt first, IndexIt last);

    ////////// Data selection //////////

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

    ////////// Circular shifts //////////

    /**
     *  @brief      Circular shift.
     *  @details    This function circularly shifts the values in the array. The first element of the
     *              array is specified in the arguments.
     *  @param[in]  s0  Index of the element that will be moved to the position [0].
     *  @returns    The new array.
     */
    Array<T, Alloc> circularShift(difference_type s0) const;

    /**
     *  @brief      Circular shift.
     *  @details    This function circularly shifts the values of the array by [n_/2] (the element
     *              indexed by [0] is moved to the position [n_/2]).
     *  @returns    The new array.
     */
    Array<T, Alloc> circularShift() const;

    /**
     *  @brief      Inverse circular shift.
     *  @details    This function undo the circular shift performed by circularShift().
     */
    Array<T, Alloc> circularInvShift() const;

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

    ////////// Special arrays //////////

    /**
     *  @brief      Constant.
     *  @details    This function creates an array and fills it with a constant value.
     *  @param[in]  arraySize  Array size.
     *  @param[in]  t  The constant values to be used to fill the array.
     *  @returns    The new array.
     */
    static Array<T, Alloc> constant(size_type size, const_reference t);

    /**
     *  @brief      Zeros.
     *  @details    This function creates an array of zeros.
     *  @param[in]  arraySize  Array size.
     *  @returns    The new array.
     */
    template<typename = void> requires nct::Numeric<T>
    static Array<T, Alloc> zeros(size_type size);

    /**
     *  @brief      Ones.
     *  @details    This function creates an array of ones.
     *  @param[in]  arraySize  Array size.
     *  @returns    The new array.
     */
    template<typename = void> requires nct::Numeric<T>
    static Array<T, Alloc> ones(size_type size);    

    /**
     *  @brief      Numerical sequence.
     *  @details    This function creates a numerical sequence from ini to ini + (arraySize-1)*inc.
     *  @param[in]  arraySize  Size of the new array.
     *  @param[in]  ini  Value of the first element in the sequence.
     *  @param[in]  inc  Difference between elements.
     *  @returns    The new array.
     */
    template<typename = void> requires nct::Numeric<T>
    static Array<T, Alloc> numericalSequence(size_type size, const_reference ini,
        const_reference inc);

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
    Array<U, AllocU> transformData(const std::function<U(const_reference)>& f) const;

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
    static Array<T, Alloc> read(std::istream& i);

protected:

    ////////// Data members //////////        

    allocator_type alloc_;  /**< Allocator object. */

    size_type n_ {0};       /**< Number of elements into the array. */

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
T dotProduct(const Array<T, Alloc>& a, const Array<T, Alloc>& b);

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
Array<T, Alloc> operator&(Array<T, Alloc>&& left, const Array<T, Alloc>& right);

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
Array<T, Alloc> operator|(Array<T, Alloc>&& left, const Array<T, Alloc>& right);

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
Array<T, Alloc> operator^(Array<T, Alloc>&& left, const Array<T, Alloc>& right);

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
Array<T, Alloc> operator+(Array<T, Alloc>&& left, const Array<T, Alloc>& right);

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
Array<T, Alloc> operator-(Array<T, Alloc>&& left, const Array<T, Alloc>& right);

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
Array<T, Alloc> operator*(const T& left, const Array<T, Alloc>& right);

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
std::istream& operator>>(std::istream& i, Array<T, Alloc>& arr);

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
std::ostream& operator<<(std::ostream& o, const Array<T, Alloc>& arr);

}

////////// Implementation of class template //////////
#include <nct/Array_template.h> 

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================

