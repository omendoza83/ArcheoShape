//=================================================================================================================
/**
 *  @file       array_iterator.h
 *  @brief      nct::iterator class template.
 *  @details    Declaration of the nct::iterator class template.
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

#ifndef NCT_ARRAY_ITERATOR_H_INCLUDE
#define NCT_ARRAY_ITERATOR_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <iterator>

//=================================================================================================================
namespace nct {

////////// Enumerators //////////

/**
 *  @brief      Iterator shift mode for 2D Arrays.
 *  @details    This enumeration is used to define how an iterator visits the elements
 *              of a 2-D array.
 */
enum class IteratorShiftMode2D : unsigned char {

    ItemMode,       /**< The iterator is used to visit each element of the array. */

    RowMode,        /**< The iterator is used to visit the elements of one row of the array. */

    ColumnMode,     /**< The iterator is used to visit the elements of one column of the array. */
};

/**
 *  @brief      Iterator shift mode for 3D Arrays.
 *  @details    This enumeration is used to define how an iterator visits the elements
 *              of a 3-D array.
 */
enum class IteratorShiftMode3D : unsigned char {

    ItemMode,       /**< The iterator is used to visit each element of the array. */

    Dim1Mode,       /**< The iterator is used to visit the elements across the dimension 1. */

    Dim2Mode,       /**< The iterator is used to visit the elements across the dimension 2. */

    Dim3Mode,       /**< The iterator is used to visit the elements across the dimension 3. */

};

/**
 *  @brief      Iterator shift mode for 4D Arrays.
 *  @details    This enumeration is used to define how an iterator visits the elements
 *              of a 4-D array.
 */
enum class IteratorShiftMode4D : unsigned char {

    ItemMode,       /**< The iterator is used to visit each element of the array. */

    Dim1Mode,       /**< The iterator is used to visit the elements across the dimension 1. */

    Dim2Mode,       /**< The iterator is used to visit the elements across the dimension 2. */

    Dim3Mode,       /**< The iterator is used to visit the elements across the dimension 3. */

    Dim4Mode,       /**< The iterator is used to visit the elements across the dimension 4. */
};

////////// Classes //////////

/**
 *  @brief      Array iterator class template.
 *  @details    This class defines an iterator that is used to read the contents of 2D, 3D
 *              and 4D arrays whose elements are in one contiguous block of memory.
 *              This iterator can be used to access elements at an arbitrary offset position
 *              relative to the element they point to.
 *  @note       This class represents a safe iterator. That is to say, bounds checking
 *              is always performed before any operation that may modify the state of the iterator, 
 *              and index checking occurs before accessing any element relative to the 
 *              element pointed to.
 *              To disable this feature, define NCT_ARRAY_ITERATOR_DISABLE_BOUNDS_CHECKING.
 *  @tparam     Container  The type of array that the iterator will traverse.
 *  @tparam     T  The data type to be pointed to by the iterator.
 *  @tparam     Distance  The type of variable to be used to calculate distances between pointers.
 *  @tparam     Pointer  The type of pointer to be handled by the iterator.
 *  @tparam     Reference  The type of reference to be handled by the iterator.
 */
template<typename Container,
    typename T,
    typename Distance = diff_t,
    typename Pointer = T*,
    typename Reference = T&>
    class array_iterator final  {

public:

    ////////// Type definitions //////////

    /** Difference type. */
    using difference_type = Distance;

    /** Value type. */
    using value_type = std::remove_cv_t<T>;

    /** Pointer type. */
    using pointer = Pointer;

    /** Reference type. */
    using reference = Reference;

    /** Iterator category. */
    using iterator_category = std::random_access_iterator_tag;

    /** Container type that uses this iterator. */
    using container_type = Container;

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an iterator that is not attached to any array.
     */
    array_iterator() noexcept = default;

    /**
     *  @brief      Copy constructor from other iterator.
     *  @details    This constructor copies the contents of other type of iterator.
     *  @tparam     Container2  The type of container of the other iterator.
     *  @tparam     T2  The data type pointed to by the other iterator.
     *  @tparam     Distance2  The type of variable used by the other iterator.
     *  @tparam     Pointer2  The type of pointer handled by the other iterator.
     *  @tparam     Reference2  The type of reference handled by the other iterator.
     *  @param[in]  other  The other iterator whose contents will be copied.
     */
    template<typename Container2, typename T2, typename Distance2, typename Pointer2,
        typename Reference2>
        array_iterator(const array_iterator<Container2, T2, Distance2,
            Pointer2, Reference2>& other) noexcept;

    /**
     *  @brief      Array iterator for 1D arrays.
     *  @details    This constructor initializes an iterator that visits the elements of a 1-D array.
     *  @param[in]  father  Father object that owns the iterator.
     *  @param[in]  index  Index of the element pointed to by the iterator.
     */
    array_iterator(const container_type& father, difference_type index);

    /**
     *  @brief      Array iterator for 2D arrays.
     *  @details    This constructor initializes an iterator that visits the elements of a 2-D array.
     *              The iterator can be configured to read all the array, one column or one row.
     *  @param[in]  father  Father object that owns the iterator.
     *  @param[in]  row  Row index of the element that is pointed to by the iterator.
     *  @param[in]  column  Column index of the element that is pointed to by the iterator.
     *  @param[in]  mode  Shift mode. It stablishes how the iterator is visiting the elements
     *              of the array and its limits.
     */
    array_iterator(const container_type& father,
        difference_type row, difference_type column, IteratorShiftMode2D mode);

    /**
     *  @brief      Array iterator for 3D arrays.
     *  @details    This constructor initializes an iterator that visits the elements of a 3-D array.
     *              The iterator can be configured to read all the array or elements across one dimension.
     *  @param[in]  father  Father object that owns the iterator.
     *  @param[in]  dim1  The index in the dimension 1 of the element that is pointed to by the iterator.
     *  @param[in]  dim2  The index in the dimension 2 of the element that is pointed to by the iterator.
     *  @param[in]  dim3  The index in the dimension 3 of the element that is pointed to by the iterator.
     *  @param[in]  mode  Shift mode. It stablishes how the iterator is visiting the elements
     *              of the array and its limits.
     */
    array_iterator(const container_type& father,
        difference_type dim1, difference_type dim2, difference_type dim3,
        IteratorShiftMode3D mode);

    /**
     *  @brief      Array iterator for 4D arrays.
     *  @details    This constructor initializes an iterator that visits the elements of a 4-D array.
     *              The iterator can be configured to read all the array or elements across one dimension.
     *  @param[in]  father  Father object that owns the iterator.
     *  @param[in]  dim1  The index in the dimension 1 of the element that is pointed to by the iterator.
     *  @param[in]  dim2  The index in the dimension 2 of the element that is pointed to by the iterator.
     *  @param[in]  dim3  The index in the dimension 3 of the element that is pointed to by the iterator.
     *  @param[in]  dim4  The index in the dimension 4 of the element that is pointed to by the iterator.
     *  @param[in]  mode  Shift mode. It stablishes how the iterator is visiting the elements
     *              of the array and its limits.
     */
    array_iterator(const container_type& father,
        difference_type dim1, difference_type dim2, difference_type dim3,
        difference_type dim4, IteratorShiftMode4D mode);    

    ////////// Operators //////////        

    /**
     *  @brief      Equality operator.
     *  @details    Two iterators are equal if both belongs to the same object and they are
     *              pointing to the same element.
     *  @param[in]  right  Iterator to compare.
     *  @returns    True if both iterators are equal. 
     */
    bool operator==(
        const array_iterator<Container, T, Distance, Pointer, Reference>& right) const noexcept;

    /**
     *  @brief      Inequality operator.
     *  @details    Two iterators are not equal if they belong to different objects or they are
     *              pointing to different elements.
     *  @param[in]  right  Iterator to compare.
     *  @returns    True if both iterators are inequal.
     */
    bool operator!=(
        const array_iterator<Container, T, Distance, Pointer, Reference>& right) const noexcept;

    /**
     *  @brief      Greater than operator. 
     *  @details    Greater than operator between iterators of the same type. 
     *  @param[in]  right  Iterator to compare. Both iterators must belong to the same container.
     *  @returns    True, if the object is pointing to an object with index greater than the index of the object 
     *              pointed by the input iterator.
     */
    bool operator>(
        const array_iterator<Container, T, Distance, Pointer, Reference>& right) const;

    /**
     *  @brief      Greater than or equal to operator.
     *  @details    Greater than or equal to operator between iterators of the same type. 
     *  @param[in]  right  Iterator to compare. Both iterators must belong to the same container.
     *  @returns    True, if the object is pointing to an object with index greater than or equal to the index 
     *              of the object pointed by the input iterator.
     */
    bool operator>=(
        const array_iterator<Container, T, Distance, Pointer, Reference>& right) const;

    /**
     *  @brief      Lower than operator. 
     *  @details    Lower than operator between iterators of the same type. 
     *  @param[in]  right  Iterator to compare. Both iterators must belong to the same container.
     *  @returns    True, if the object is pointing to an object with index lower than the index of the object 
     *              pointed by the input iterator.
     */
    bool operator<(
        const array_iterator<Container, T, Distance, Pointer, Reference>& right) const;

    /**
     *  @brief      Lower than or equal to operator. 
     *  @details    Lower than or equal to operator between iterators of the same type. 
     *  @param[in]  right  Iterator to compare. Both iterators must belong to the same container.
     *  @returns    True, if the object is pointing to an object with index lower than or equal to the index 
     *              of the object pointed by the input iterator.
     */
    bool operator<=(
        const array_iterator<Container, T, Distance, Pointer, Reference>& right) const;

    /**
     *  @brief      Indirection operator.
     *  @details    This operator returns a reference to the object pointed to by the iterator.
     *  @returns    A reference to the object pointed to by the iterator.
     */
    reference operator*() const;

    /**
     *  @brief      Reference operator. 
     *  @details    This operator returns the address of the object pointed to by the iterator.
     *  @returns    The address of the object pointed to by the iterator.
     */
    pointer operator->() const;
    
    /**
     *  @brief      Array subscript.
     *  @details    This operator returns the object with index i + current object. 
     *  @param[in]  i  Index of the object to be returned.
     *  @returns    The object with index i + actual object into de container.
     */
    reference operator[](difference_type i) const;

    /**
     *  @brief      Increment operator.
     *  @details    This operator increments the position of the iterator by 1.
     *  @returns    A const reference to the iterator.
     */
    array_iterator<Container, T, Distance, Pointer, Reference>& operator++();

    /**
     *  @brief      Increment operator.
     *  @details    This operator increments the position of the iterator by 1 and return the iterator
     *              before the increment.
     *  @returns    An iterator with the position of this object before the increment.
     */
    array_iterator<Container, T, Distance, Pointer, Reference> operator++(int);

    /**
     *  @brief      Increment operator.
     *  @details    This operator increments the position of the iterator by i.
     *  @param[in]  i  Increment value.
     *  @returns    A const reference to the iterator.
     */
    array_iterator<Container, T, Distance, Pointer, Reference>& operator+=(difference_type i);

    /**
     *  @brief      Addition.
     *  @details    This operator adds i to the index of the pointed object and creates a new iterator
     *              with this increment.
     *  @param[in]  i  Increment value.
     *  @returns    An iterator pointing to the object with index i + current object.
     */
    array_iterator<Container, T, Distance, Pointer, Reference> operator+(difference_type i) const;

    /**
     *  @brief      Decrement operator.
     *  @details    This operator decrements the position of the iterator by 1.
     *  @returns    A const reference to the iterator.
     */
    array_iterator<Container, T, Distance, Pointer, Reference>& operator--();

    /**
     *  @brief      Decrement operator.
     *  @details    This operator decrements the position of the iterator by 1 and return the iterator
     *              before the increment.
     *  @returns    An iterator with the position of this object before the decrement.
     */
    array_iterator<Container, T, Distance, Pointer, Reference> operator--(int);

    /**
     *  @brief      Decrement operator.
     *  @details    This operator decrements the position of the iterator by -i.
     *  @param[in]  i  Decrement value.
     *  @returns    A const reference to the iterator.
     */
    array_iterator<Container, T, Distance, Pointer, Reference>& operator-=(difference_type i);

    /**
     *  @brief      Substraction.
     *  @details    This operator substracts i to the index of the pointed object and creates a new
     *              iterator with this decrement.
     *  @param[in]  i  Decrement value.
     *  @returns    An iterator pointing to the object with index -i + current object.
     */
    array_iterator<Container, T, Distance, Pointer, Reference> operator-(difference_type i) const;

    /**
     *  @brief      Substraction.
     *  @details    This function calculates the distance between iterators.
     *  @param[in]  right  Iterator to be substracted.
     *  @returns    The distance between the iterators.
     */
    difference_type operator-(
        const array_iterator<Container, T, Distance, Pointer, Reference>& right) const;

    ////////// Member functions //////////    

    /**
     *  @brief      Is a null iterator?
     *  @details    This function returns whether the iterator is pointing to nothing.
     *  @returns    True, if the iterator is pointing to nothing.
     */
    bool nullIterator() const noexcept;

    /**
     *  @brief      Is valid for comparison?
     *  @details    This function tests whether an iterator is valid for comparisons. This means that 
     *              both iterators where initialized by using the same memory segment and dintance
     *              between contigouos items.
     *  @param[in]  other  Iterator to be testd.
     *  @returns    True, if the input iterator can be used in comparisons.
     */
    bool validForComparison(
        const array_iterator<Container, T, Distance, Pointer, Reference>& other) const noexcept;

    /**
     *  @brief      Current index.
     *  @details    This function returns the index of the current element pointed to by the iterator
     *              according to the initial position of the memory segement and the distance
     *              between contiguous elements.
     *  @returns    The index of the current element.
     */
    difference_type currentIndex() const noexcept;

    /**
     *  @brief      Beginning of memory segment.
     *  @details    This function returns pointer to the beginning of the memory segment that
     *              this iterator visits.
     *  @returns    The beginning of the memory segment.
     */
    pointer memorySegmentBeginning() const noexcept;

    /**
     *  @brief      End of memory segment.
     *  @details    This function returns pointer to the end of the memory segment that
     *              this iterator visits.
     *  @returns    The end of the memory segment.
     */
    pointer memorySegmentEnd() const noexcept;

    /**
     *  @brief      Current position.
     *  @details    This function returns the current position that the iterator is poining to.
     *  @returns    The current position.
     */
    pointer currentPosition() const noexcept;

    /**
     *  @brief      Distance between contiguous elements.
     *  @details    This function returns the distance between to contiguous elements.
     *  @returns    The distance between contiguous elements.
     */
    difference_type distance() const noexcept;

private:

    ////////// Data members //////////    

    pointer ini_ {nullptr};     /**< Beginning of the memory segment. */

    pointer end_ {nullptr};     /**< End of the memory segment. */

    pointer pos_ {nullptr};     /**< Object pointed to by the iterator. */

    difference_type inc_ {0};   /**< Distance between two contiguous objects. */

};

////////// Functions //////////  

/**
 *  @brief      Iterator addition.
 *  @details    This operator adds i to the index of the pointed object of one iterator and creates a new
 *              iterator with this increment. 
 *  @tparam     Container  The type of array that the iterator traverses.
 *  @tparam     T  The data type pointed to by the iterator.
 *  @tparam     Distance  The type of variable used to calculate distances between iterators.
 *  @tparam     Pointer  The type of pointer handled by the iterator.
 *  @tparam     Reference  The type of reference handled by the iterator.
 *  @param[in]  i  Increment value.
 *  @param[in]  it  The iterator to be incremented.
 *  @returns    An iterator pointing to the object with index i + current object of it.
 */
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
array_iterator<Container, T, Distance, Pointer, Reference> operator+(
    typename array_iterator<Container, T, Distance, Pointer, Reference>::difference_type i, 
    const array_iterator<Container, T, Distance, Pointer, Reference>& it);

}

////////// Implementation of class template //////////
#include <nct/array_iterator_template.h> 

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
