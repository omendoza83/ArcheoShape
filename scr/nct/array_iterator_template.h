//=================================================================================================================
/**
 *  @file       array_iterator_template.h
 *  @brief      nct::array_iterator class implementation file.
 *  @details    This file contains the implementation of the nct::array_iterator class template.
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

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
template<typename Container2, typename T2, typename Distance2, typename Pointer2, typename Reference2>
nct::array_iterator<Container, T, Distance, Pointer, Reference>::array_iterator(
    const array_iterator<Container2, T2, Distance2, Pointer2, Reference2>& other) noexcept
{
    ini_ = other.memorySegmentBeginning();
    end_ = other.memorySegmentEnd();
    pos_ = other.currentPosition();
    inc_ = other.distance();
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
nct::array_iterator<Container, T, Distance, Pointer, Reference>::
    array_iterator(const container_type& father, difference_type index)
{
#ifndef NCT_ARRAY_ITERATOR_DISABLE_BOUND_CHECKING
    if ( (index < 0) || (index > static_cast<difference_type>(father.size()))  )
        throw IndexOutOfRangeException("index", SOURCE_INFO);
#endif

    ini_ = const_cast<pointer>(father.data());
    end_ = const_cast<pointer>(father.data()) + father.size();
    pos_ = const_cast<pointer>(father.data()) + index;
    inc_ = 1;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
nct::array_iterator<Container, T, Distance, Pointer, Reference>::
    array_iterator(const container_type& father, difference_type row, difference_type column,
    IteratorShiftMode2D mode)
{
    if ((mode!=IteratorShiftMode2D::RowMode) && 
        (mode!=IteratorShiftMode2D::ColumnMode))
        throw ArgumentException("mode", exc_bad_iterator_shift_mode, SOURCE_INFO);

#ifndef NCT_ARRAY_ITERATOR_DISABLE_BOUND_CHECKING
    if ( (row < 0) || (row >= (static_cast<difference_type>(father.rows()) + 
        (mode==IteratorShiftMode2D::ColumnMode))) )
        throw IndexOutOfRangeException("row", SOURCE_INFO);

    if ( (column < 0) || (column >= (static_cast<difference_type>(father.columns()) +
        (mode==IteratorShiftMode2D::RowMode))) )
        throw IndexOutOfRangeException("column", SOURCE_INFO);
#endif

    ini_ = nullptr;
    end_ = nullptr;
    pos_ = nullptr;
    inc_ = 0;
    switch (mode) {
        case IteratorShiftMode2D::RowMode:
            ini_ = const_cast<pointer>(father.data()) + row*father.columns();
            end_ = ini_ + father.columns();
            pos_ = const_cast<pointer>(father.data()) + row*father.columns() + column;
            inc_ = 1;
            break;
        case IteratorShiftMode2D::ColumnMode:
            ini_ = const_cast<pointer>(father.data()) + column;
            end_ = ini_ + father.rows()*father.columns();
            pos_ = const_cast<pointer>(father.data()) + row*father.columns() + column;
            inc_ = father.columns();
            break;
        default:
            // Do nothing.
            break;
    }        
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
nct::array_iterator<Container, T, Distance, Pointer, Reference>::
    array_iterator(const container_type& father, difference_type dim1, difference_type dim2, 
    difference_type dim3, IteratorShiftMode3D mode)
{
    if ((mode!=IteratorShiftMode3D::Dim1Mode) &&
        (mode!=IteratorShiftMode3D::Dim2Mode) && 
        (mode!=IteratorShiftMode3D::Dim3Mode))
        throw ArgumentException("mode", exc_bad_iterator_shift_mode, SOURCE_INFO);

#ifndef NCT_ARRAY_ITERATOR_DISABLE_BOUND_CHECKING
    if ( (dim1 < 0) || (dim1 >= (static_cast<difference_type>(father.dimension1()) + 
        (mode==IteratorShiftMode3D::Dim1Mode))) )
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);

    if ( (dim2 < 0) || (dim2 >= (static_cast<difference_type>(father.dimension2()) +
        (mode==IteratorShiftMode3D::Dim2Mode))) )
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);

    if ( (dim3 < 0) || (dim3 >= (static_cast<difference_type>(father.dimension3()) + 
        (mode==IteratorShiftMode3D::Dim3Mode))) )
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);
#endif

    ini_ = nullptr;
    end_ = nullptr;
    pos_ = nullptr;
    inc_ = 0;
    switch (mode) {
        case IteratorShiftMode3D::Dim1Mode:
            ini_ = const_cast<pointer>(father.data()) + father.dimension3()*(dim2) + dim3;
            end_ = ini_ + father.dimension2()*father.dimension3()*father.dimension1();
            pos_ = const_cast<pointer>(father.data()) + father.dimension3()*(father.dimension2()*dim1 + dim2) +
                dim3;
            inc_ = father.dimension2()*father.dimension3();
            break;   

        case IteratorShiftMode3D::Dim2Mode:
            ini_ = const_cast<pointer>(father.data()) + father.dimension3()*(father.dimension2()*dim1) + dim3;
            end_ = ini_ + father.dimension2()*father.dimension3();
            pos_ = const_cast<pointer>(father.data()) + father.dimension3()*(father.dimension2()*dim1 + dim2) +
                dim3;
            inc_ = father.dimension3();
            break;

        case IteratorShiftMode3D::Dim3Mode:
            ini_ = const_cast<pointer>(father.data()) + father.dimension3()*(father.dimension2()*dim1 + dim2);
            end_ = ini_ + father.dimension3();
            pos_ = const_cast<pointer>(father.data()) + father.dimension3()*(father.dimension2()*dim1 + dim2) +
                dim3;
            inc_ = 1;
            break;

        default:
            // Do nothing.
            break;
    }    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
nct::array_iterator<Container, T, Distance, Pointer, Reference>::
    array_iterator(const container_type& father, difference_type dim1, difference_type dim2, 
    difference_type dim3, difference_type dim4, IteratorShiftMode4D mode)
{
    if ((mode!=IteratorShiftMode4D::Dim1Mode) &&
        (mode!=IteratorShiftMode4D::Dim2Mode) &&
        (mode!=IteratorShiftMode4D::Dim3Mode) && 
        (mode!=IteratorShiftMode4D::Dim4Mode))
        throw ArgumentException("mode", exc_bad_iterator_shift_mode, SOURCE_INFO);

#ifndef NCT_ARRAY_ITERATOR_DISABLE_BOUND_CHECKING
    if ( (dim1 < 0) || (dim1 >= (static_cast<difference_type>(father.dimension1()) +
        (mode==IteratorShiftMode4D::Dim1Mode))) )
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);

    if ( (dim2 < 0) || (dim2 >= (static_cast<difference_type>(father.dimension2()) +
        (mode==IteratorShiftMode4D::Dim2Mode))) )
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);

    if ( (dim3 < 0) || (dim3 >= (static_cast<difference_type>(father.dimension3()) + 
        (mode==IteratorShiftMode4D::Dim3Mode))) )
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);

    if ( (dim4 < 0) || (dim4 >= (static_cast<difference_type>(father.dimension4()) +
        (mode==IteratorShiftMode4D::Dim4Mode))) )
        throw IndexOutOfRangeException("dim4", SOURCE_INFO);
#endif

    ini_ = nullptr;
    end_ = nullptr;
    pos_ = nullptr;
    inc_ = 0;
    switch (mode) {
        case IteratorShiftMode4D::Dim1Mode:
            ini_ = const_cast<pointer>(father.data()) + father.dimension4() * 
                (father.dimension3() *dim2 + dim3) + dim4;
            end_ = ini_ + father.dimension3()*father.dimension4()*father.dimension2()*father.dimension1();
            pos_ = const_cast<pointer>(father.data()) + father.dimension4() * 
                (father.dimension3() * (father.dimension2() * dim1 + dim2) + dim3) + dim4;
            inc_ = father.dimension2()*father.dimension3()*father.dimension4();
            break;

        case IteratorShiftMode4D::Dim2Mode:
            ini_ = const_cast<pointer>(father.data()) + father.dimension4() *
                (father.dimension3() * (father.dimension2() * dim1) + dim3) + dim4;
            end_ = ini_ + father.dimension3()*father.dimension4()*father.dimension2();
            pos_ = const_cast<pointer>(father.data()) + father.dimension4() *
                (father.dimension3() * (father.dimension2() * dim1 + dim2) + dim3) + dim4;
            inc_ = father.dimension3()*father.dimension4();
            break;

        case IteratorShiftMode4D::Dim3Mode:
            ini_ = const_cast<pointer>(father.data()) + father.dimension4() * 
                (father.dimension3() * (father.dimension2() * dim1 + dim2)) + dim4;
            end_ = ini_ + father.dimension3()*father.dimension4();
            pos_ = const_cast<pointer>(father.data()) + father.dimension4() * 
                (father.dimension3() * (father.dimension2() * dim1 + dim2) + dim3) + dim4;
            inc_ = father.dimension4();
            break;
        
        case IteratorShiftMode4D::Dim4Mode:
            ini_ = const_cast<pointer>(father.data()) + father.dimension4() * 
                (father.dimension3() * (father.dimension2() * dim1 + dim2) + dim3);
            end_ = ini_ + father.dimension4();
            pos_ = const_cast<pointer>(father.data()) + father.dimension4() * 
                (father.dimension3() * (father.dimension2() * dim1 + dim2) + dim3) + dim4;
            inc_ = 1;
            break;        

        default:
            break;
    }    
}

//=================================================================================================================
//        OPERATORS 
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
bool nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator==(
    const array_iterator<Container, T, Distance, Pointer, Reference>& right) const noexcept
{
    if (ini_!= right.ini_)
        return false;
    if (end_!= right.end_)
        return false;
    if (pos_!= right.pos_)
        return false;
    if (inc_!= right.inc_)
        return false;
    return true;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline bool nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator!=(
    const array_iterator<Container, T, Distance, Pointer, Reference>& right) const noexcept
{
    return !(*this== right);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline bool nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator>(
    const array_iterator<Container, T, Distance, Pointer, Reference>& right) const
{
    if ( (ini_!= right.ini_) || (end_!= right.end_) || (inc_!= right.inc_) )
        throw IteratorException("right", SOURCE_INFO);

    return pos_ > right.pos_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline bool nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator>=(
    const array_iterator<Container, T, Distance, Pointer, Reference>& right) const
{
    if ( (ini_!= right.ini_) || (end_!= right.end_) || (inc_!= right.inc_) )
        throw IteratorException("right", SOURCE_INFO);

    return pos_ >= right.pos_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline bool nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator<(
    const array_iterator<Container, T, Distance, Pointer, Reference>& right) const
{
    if ( (ini_!= right.ini_) || (end_!= right.end_) || (inc_!= right.inc_) )
        throw IteratorException("right", SOURCE_INFO);

    return pos_ < right.pos_;
}

template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline bool nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator<=(
    const array_iterator<Container, T, Distance, Pointer, Reference>& right) const
{
    if ( (ini_!= right.ini_) || (end_!= right.end_) || (inc_!= right.inc_) )
        throw IteratorException("right", SOURCE_INFO);

    return pos_ <= right.pos_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline typename nct::array_iterator<Container, T, Distance, Pointer, Reference>::reference 
    nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator*() const
{
#ifndef NCT_ARRAY_ITERATOR_DISABLE_BOUND_CHECKING
    if (nullIterator())
        throw NullIteratorException(SOURCE_INFO);
    if (pos_ >= end_)
        throw IteratorException(SOURCE_INFO);
#endif
    return *pos_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline typename nct::array_iterator<Container, T, Distance, Pointer, Reference>::pointer 
    nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator->() const
{
#ifndef NCT_ARRAY_ITERATOR_DISABLE_BOUND_CHECKING
    if (nullIterator())
        throw NullIteratorException(SOURCE_INFO);
    if (pos_ >= end_)
        throw IteratorException(SOURCE_INFO);
#endif
    return pos_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline typename nct::array_iterator<Container, T, Distance, Pointer, Reference>::reference 
    nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator[](
    difference_type i) const
{
    auto newPos = pos_+i*inc_;
#ifndef NCT_ARRAY_ITERATOR_DISABLE_BOUND_CHECKING
    if (nullIterator())
        throw NullIteratorException(SOURCE_INFO);    
    if ((newPos >= end_) || (newPos < ini_))
        throw IteratorException(SOURCE_INFO);
#endif
    return *newPos;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline nct::array_iterator<Container, T, Distance, Pointer, Reference>& 
    nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator++()
{
    auto newPos = pos_+inc_;
#ifndef NCT_ARRAY_ITERATOR_DISABLE_BOUND_CHECKING
    if (newPos > end_)
        throw IteratorException(SOURCE_INFO);
#endif
    pos_ = newPos;
    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline nct::array_iterator<Container, T, Distance, Pointer, Reference>
    nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator++(int)
{
    auto tmp = *this;
    ++(*this);
    return tmp;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline nct::array_iterator<Container, T, Distance, Pointer, Reference>& 
    nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator+=(
    difference_type i)
{
    auto newPos = pos_+i*inc_;
#ifndef NCT_ARRAY_ITERATOR_DISABLE_BOUND_CHECKING
    if ( (newPos > end_) || (newPos < ini_) )
        throw IteratorException(SOURCE_INFO);
#endif
    pos_ = newPos;
    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline nct::array_iterator<Container, T, Distance, Pointer, Reference>
    nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator+(
    difference_type i) const
{    
    auto newPos = pos_+i*inc_;
#ifndef NCT_ARRAY_ITERATOR_DISABLE_BOUND_CHECKING
    if ( (newPos > end_) || (newPos < ini_) )
        throw IteratorException(SOURCE_INFO);
#endif
    auto tmp = *this;
    tmp.pos_ = newPos;
    return tmp;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline nct::array_iterator<Container, T, Distance, Pointer, Reference> 
nct::operator+(typename array_iterator<Container, T, Distance, Pointer, Reference>::difference_type i,
    const array_iterator<Container, T, Distance, Pointer, Reference>& it)
{
    return it + i;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline nct::array_iterator<Container, T, Distance, Pointer, Reference>& 
    nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator--()
{
    auto newPos = pos_-inc_;
#ifndef NCT_ARRAY_ITERATOR_DISABLE_BOUND_CHECKING
    if (newPos < ini_)
        throw IteratorException(SOURCE_INFO);
#endif
    pos_ = newPos;
    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline nct::array_iterator<Container, T, Distance, Pointer, Reference>
    nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator--(int)
{
    auto tmp = *this;
    --(*this);
    return tmp;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline typename nct::array_iterator<Container, T, Distance, Pointer, Reference>&
    nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator-=(difference_type i)
{
    auto newPos = pos_-i*inc_;
#ifndef NCT_ARRAY_ITERATOR_DISABLE_BOUND_CHECKING
    if ( (newPos > end_) || (newPos < ini_) )
        throw IteratorException(SOURCE_INFO);
#endif
    pos_ = newPos;
    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline typename nct::array_iterator<Container, T, Distance, Pointer, Reference>
    nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator-(
    difference_type i) const
{
    auto newPos = pos_-i*inc_;
#ifndef NCT_ARRAY_ITERATOR_DISABLE_BOUND_CHECKING
    if ( (newPos > end_) || (newPos < ini_) )
        throw IteratorException(SOURCE_INFO);
#endif
    auto tmp = *this;
    tmp.pos_ = newPos;
    return tmp;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline typename nct::array_iterator<Container, T, Distance, Pointer, Reference>::difference_type 
    nct::array_iterator<Container, T, Distance, Pointer, Reference>::operator-(
    const array_iterator<Container, T, Distance, Pointer, Reference>& right) const
{
    if ( (ini_!= right.ini_) || (end_!= right.end_) || (inc_!= right.inc_) )
        throw IteratorException("right", SOURCE_INFO);

    if (inc_ == 0)
        return 0;

    return static_cast<nct::array_iterator<Container, T, Distance, Pointer, Reference>::
        difference_type>((pos_ - right.pos_)/inc_);
}

//=================================================================================================================
//        MEMBER FUNCTIONS 
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline bool nct::array_iterator<Container, T, Distance, Pointer, Reference>::nullIterator() const noexcept
{
    return ( (ini_ == nullptr) || (end_ == nullptr) || (pos_ == nullptr) );
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline bool nct::array_iterator<Container, T, Distance, Pointer, Reference>::validForComparison(
    const array_iterator<Container, T, Distance, Pointer, Reference>& other) const noexcept
{
    return ( (ini_ == other.ini_) && (end_ == other.end_) && (inc_ == other.inc_) );
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline typename nct::array_iterator<Container, T, Distance, Pointer, Reference>::difference_type 
    nct::array_iterator<Container, T, Distance, Pointer, Reference>::currentIndex() const noexcept
{
    if (nullIterator() || (inc_ == 0))
        return 0;
    return (pos_ - ini_) / inc_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline typename nct::array_iterator<Container, T, Distance, Pointer, Reference>::pointer 
    nct::array_iterator<Container, T, Distance, Pointer, Reference>::memorySegmentBeginning() const noexcept
{
    return ini_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline typename nct::array_iterator<Container, T, Distance, Pointer, Reference>::pointer 
    nct::array_iterator<Container, T, Distance, Pointer, Reference>::memorySegmentEnd() const noexcept
{
    return end_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline typename nct::array_iterator<Container, T, Distance, Pointer, Reference>::pointer 
    nct::array_iterator<Container, T, Distance, Pointer, Reference>::currentPosition() const noexcept
{
    return pos_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename Container, typename T, typename Distance, typename Pointer, typename Reference>
inline typename nct::array_iterator<Container, T, Distance, Pointer, Reference>::difference_type
    nct::array_iterator<Container, T, Distance, Pointer, Reference>::distance() const noexcept
{
    return inc_;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
