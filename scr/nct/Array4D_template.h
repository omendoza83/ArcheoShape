//=================================================================================================================
/**
 *  @file       Array4D_template.h
 *  @brief      nct::Array4D class template implementation file.
 *  @details    This file contains the implementation of the nct::Array4D class template.
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
template<typename T, typename Alloc> 
nct::Array4D<T, Alloc>::Array4D(const allocator_type& allocator)  noexcept : alloc_{allocator},
n_{0}, nd1_{0}, nd2_{0}, nd3_{0}, nd4_{0}, data_{nullptr}
{

}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array4D<T, Alloc>::Array4D(
    size_type dim1, size_type dim2, size_type dim3, size_type dim4,
    const allocator_type& allocator) : alloc_(allocator), n_{0}, nd1_{0}, nd2_{0}, nd3_{0}, nd4_{0}, data_{nullptr}
{
    try {
        resize(dim1, dim2, dim3, dim4);
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

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array4D<T, Alloc>::Array4D(
    size_type dim1, size_type dim2, size_type dim3, size_type dim4,
    const_reference val, const allocator_type& allocator) : alloc_{allocator},
    n_{0}, nd1_{0}, nd2_{0}, nd3_{0}, nd4_{0}, data_{nullptr}
{
    try {
        assign(dim1, dim2, dim3, dim4, val);
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

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array4D<T, Alloc>::Array4D(const Array4D<T, Alloc>& other) :
n_{0}, nd1_{0}, nd2_{0}, nd3_{0}, nd4_{0}, data_{nullptr}
{
    try {
        copy(other);
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

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array4D<T, Alloc>::Array4D(const Array4D<T, Alloc>& other, 
    const allocator_type& allocator) : alloc_{allocator},
    n_{0}, nd1_{0}, nd2_{0}, nd3_{0}, nd4_{0}, data_{nullptr}
{
    try {
        copy(other);
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

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array4D<T, Alloc>::Array4D(Array4D<T, Alloc>&& other) noexcept
{
    n_ = other.n_;
    nd1_ = other.nd1_;
    nd2_ = other.nd2_;
    nd4_ = other.nd4_;
    nd3_ = other.nd3_;    
    data_ = other.data_;

    other.n_ = 0;
    other.nd1_ = 0;
    other.nd2_ = 0;    
    other.nd3_ = 0;
    other.nd4_ = 0;
    other.data_ = nullptr;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array4D<T, Alloc>::Array4D(Array4D<T, Alloc>&& other,
    const allocator_type& allocator) : alloc_{allocator}
{
    n_ = other.n_;
    nd1_ = other.nd1_;
    nd2_ = other.nd2_;
    nd4_ = other.nd4_;
    nd3_ = other.nd3_;    
    data_ = other.data_;

    other.n_ = 0;
    other.nd1_ = 0;
    other.nd2_ = 0;    
    other.nd3_ = 0;
    other.nd4_ = 0;
    other.data_ = nullptr;    
}

//=================================================================================================================
//        DESTRUCTOR
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline nct::Array4D<T, Alloc>::~Array4D() noexcept
{        
    clear();
}

//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array4D<T, Alloc>& nct::Array4D<T, Alloc>::operator=(
    const Array4D<T, Alloc>& other)
{
    if (data_ == other.data_)
        return *this;

    try {
        copy(other);
    }
    catch (const nct_exception & ex) {
        throw OperationException(exc_error_copying_array, SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception & ex) {
        throw OperationException(exc_error_copying_array, SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_unknown, SOURCE_INFO);
    }

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array4D<T, Alloc>& nct::Array4D<T, Alloc>::operator=(Array4D<T, Alloc>&& other) noexcept
{
    if (data_ == other.data_)
        return *this;

    clear();
    nd1_ = other.nd1_;
    nd2_ = other.nd2_;
    nd3_ = other.nd3_;
    nd4_ = other.nd4_;
    n_ = other.n_;
    data_ = other.data_;

    other.n_ = 0;
    other.nd1_ = 0;
    other.nd2_ = 0;
    other.nd3_ = 0;
    other.nd4_ = 0;
    other.data_ = nullptr;

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
bool nct::Array4D<T, Alloc>::operator==(const Array4D<T, Alloc>& right) const
{
    if (data_ == right.data_)
        return true;

    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) || (right.nd3_ != nd3_) || (right.nd4_ != nd4_))
        return false;

    for (size_type i = 0; i < n_; i++) {
        if (data_[i] != right.data_[i])
            return false;
    }

    return true;
}

template<typename T, typename Alloc>
bool nct::Array4D<T, Alloc>::operator!=(const Array4D<T, Alloc> & right) const
{
    return !(*this == right);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::reference
nct::Array4D<T, Alloc>::operator()(size_type i, size_type j, size_type k, size_type l)
{
#ifndef NCT_ARRAY_4D_DISABLE_INDEX_CHECKING
    if (i >= nd1_)
        throw IndexOutOfRangeException("i", SOURCE_INFO);
    if (j >= nd2_)
        throw IndexOutOfRangeException("j", SOURCE_INFO);
    if (k >= nd3_)
        throw IndexOutOfRangeException("k", SOURCE_INFO);
    if (l >= nd4_)
        throw IndexOutOfRangeException("l", SOURCE_INFO);
#endif
    return data_[nd4_ * (nd3_ * (nd2_ * i + j) + k) + l];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reference
nct::Array4D<T, Alloc>::operator()(
    size_type i, size_type j, size_type k, size_type l) const
{
#ifndef NCT_ARRAY_4D_DISABLE_INDEX_CHECKING
    if (i >= nd1_)
        throw IndexOutOfRangeException("i", SOURCE_INFO);
    if (j >= nd2_)
        throw IndexOutOfRangeException("j", SOURCE_INFO);
    if (k >= nd3_)
        throw IndexOutOfRangeException("k", SOURCE_INFO);
    if (l >= nd4_)
        throw IndexOutOfRangeException("l", SOURCE_INFO);
#endif
    return data_[nd4_ * (nd3_ * (nd2_ * i + j) + k) + l];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::reference
nct::Array4D<T, Alloc>::operator[](size_type i)
{
#ifndef NCT_ARRAY_4D_DISABLE_INDEX_CHECKING
    if (i >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
#endif
    return data_[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reference
nct::Array4D<T, Alloc>::operator[](
    size_type i) const
{
#ifndef NCT_ARRAY_4D_DISABLE_INDEX_CHECKING
    if (i >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
#endif
    return data_[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::reference
nct::Array4D<T, Alloc>::operator()(size_type i)
{
#ifndef NCT_ARRAY_4D_DISABLE_INDEX_CHECKING
    if (i >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
#endif
    return data_[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reference
nct::Array4D<T, Alloc>::operator()(
    size_type i) const
{
#ifndef NCT_ARRAY_4D_DISABLE_INDEX_CHECKING
    if (i >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
#endif
    return data_[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::operator&(const Array4D<T, Alloc> & right) const
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) ||
        (right.nd3_ != nd3_) || (right.nd4_ != nd4_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array4D<T, Alloc> res(nd1_, nd2_, nd3_, nd4_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = (data_[i] & right.data_[i]);

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::integral T, typename Alloc>
nct::Array4D<T, Alloc> nct::operator&(
    Array4D<T, Alloc> && left, const Array4D<T, Alloc> & right)
{
    if ((left.dimension1() != right.dimension1()) ||
        (left.dimension2() != right.dimension2()) ||
        (left.dimension3() != right.dimension3()) ||
        (left.dimension4() != right.dimension4()))
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array4D<T, Alloc> resMat;
    std::swap(resMat, left);

    for (typename Array4D<T, Alloc>::size_type i = 0; i < resMat.size(); i++)
        resMat[i] = (resMat[i] & right[i]);

    return resMat;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>  template<typename> requires std::integral<T>
const nct::Array4D<T, Alloc>& nct::Array4D<T, Alloc>::operator&=(const Array4D<T, Alloc> & right)
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) ||
        (right.nd3_ != nd3_) || (right.nd4_ != nd4_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] &= right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>  template<typename> requires std::integral<T>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::operator|(const Array4D<T, Alloc> & right) const
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) ||
        (right.nd3_ != nd3_) || (right.nd4_ != nd4_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array4D<T, Alloc> res(nd1_, nd2_, nd3_, nd4_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = (data_[i] | right.data_[i]);

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::integral T, typename Alloc>
nct::Array4D<T, Alloc> nct::operator|(
    Array4D<T, Alloc> && left, const Array4D<T, Alloc> & right)
{
    if ((left.dimension1() != right.dimension1()) ||
        (left.dimension2() != right.dimension2()) ||
        (left.dimension3() != right.dimension3()) ||
        (left.dimension4() != right.dimension4()))
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array4D<T, Alloc> resMat;
    std::swap(resMat, left);

    for (typename Array4D<T, Alloc>::size_type i = 0; i < resMat.size(); i++)
        resMat[i] = (resMat[i] | right[i]);

    return resMat;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>  template<typename> requires std::integral<T>
const nct::Array4D<T, Alloc>& nct::Array4D<T, Alloc>::operator|=(const Array4D<T, Alloc> & right)
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) ||
        (right.nd3_ != nd3_) || (right.nd4_ != nd4_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] |= right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>  template<typename> requires std::integral<T>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::operator^(
    const Array4D<T, Alloc> & right) const
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) ||
        (right.nd3_ != nd3_) || (right.nd4_ != nd4_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array4D<T, Alloc> res(nd1_, nd2_, nd3_, nd4_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = (data_[i] ^ right.data_[i]);

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::integral T, typename Alloc>
nct::Array4D<T, Alloc> nct::operator^(Array4D<T, Alloc> && left, const Array4D<T, Alloc> & right)
{
    if ((left.dimension1() != right.dimension1()) ||
        (left.dimension2() != right.dimension2()) ||
        (left.dimension3() != right.dimension3()) ||
        (left.dimension4() != right.dimension4()))
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array4D<T, Alloc> resMat;
    std::swap(resMat, left);

    for (typename Array4D<T, Alloc>::size_type i = 0; i < resMat.size(); i++)
        resMat[i] = (resMat[i] ^ right[i]);

    return resMat;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
const nct::Array4D<T, Alloc> & nct::Array4D<T, Alloc>::operator^=(
    const Array4D<T, Alloc> & right)
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) ||
        (right.nd3_ != nd3_) || (right.nd4_ != nd4_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] ^= right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::operator+() const
{
    Array4D<T, Alloc> res(nd1_, nd2_, nd3_, nd4_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Addable<T>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::operator+(
    const Array4D<T, Alloc> & right) const
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) ||
        (right.nd3_ != nd3_) || (right.nd4_ != nd4_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array4D<T, Alloc> res(nd1_, nd2_, nd3_, nd4_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i] + right.data_[i];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Addable T, typename Alloc> 
nct::Array4D<T, Alloc> nct::operator+
(Array4D<T, Alloc> && left, const Array4D<T, Alloc> & right)
{
    if ((left.dimension1() != right.dimension1()) ||
        (left.dimension2() != right.dimension2()) ||
        (left.dimension3() != right.dimension3()) ||
        (left.dimension4() != right.dimension4()))
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array4D<T, Alloc> resMat;
    std::swap(resMat, left);

    for (typename Array4D<T, Alloc>::size_type i = 0; i < resMat.size(); i++)
        resMat[i] += right[i];

    return resMat;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Addable<T>
const nct::Array4D<T, Alloc> & nct::Array4D<T, Alloc>::operator+=(
    const Array4D<T, Alloc> & right)
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) ||
        (right.nd3_ != nd3_) || (right.nd4_ != nd4_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] += right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::SignedNumeric<T>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::operator-() const
{
    Array4D<T, Alloc> res(nd1_, nd2_, nd3_, nd4_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = -data_[i];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Substractable<T>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::operator-(
    const Array4D<T, Alloc> & right) const
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) ||
        (right.nd3_ != nd3_) || (right.nd4_ != nd4_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array4D<T, Alloc> res(nd1_, nd2_, nd3_, nd4_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i] - right.data_[i];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Substractable T, typename Alloc>
nct::Array4D<T, Alloc> nct::operator-(
    Array4D<T, Alloc> && left, const Array4D<T, Alloc> & right)
{
    if ((left.dimension1() != right.dimension1()) ||
        (left.dimension2() != right.dimension2()) ||
        (left.dimension3() != right.dimension3()) ||
        (left.dimension4() != right.dimension4()))
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array4D<T, Alloc> resMat;
    std::swap(resMat, left);

    for (typename Array4D<T, Alloc>::size_type i = 0; i < resMat.size(); i++)
        resMat[i] -= right[i];

    return resMat;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Substractable<T>
const nct::Array4D<T, Alloc> & nct::Array4D<T, Alloc>::operator-=(
    const Array4D<T, Alloc> & right)
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) ||
        (right.nd3_ != nd3_) || (right.nd4_ != nd4_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] -= right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::operator*(
    const_reference right) const
{
    Array4D<T, Alloc> res(nd1_, nd2_, nd3_, nd4_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i] * right;

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T, typename Alloc> 
nct::Array4D<T, Alloc> nct::operator*(const T & left,
    const Array4D<T, Alloc> & right)
{
    Array4D<T, Alloc> res(right.dimension1(), right.dimension2(),
        right.dimension3(), right.dimension4());

    for (typename Array4D<T, Alloc>::size_type i = 0; i < right.size(); i++)
        res[i] = right[i] * left;

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
const nct::Array4D<T, Alloc>& nct::Array4D<T, Alloc>::operator*=(
    const_reference right)
{
    for (size_type i = 0; i < n_; i++)
        data_[i] *= right;

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::operator/(
    const_reference right) const
{
    Array4D<T, Alloc> res(nd1_, nd2_, nd3_, nd4_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i] / right;

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
const nct::Array4D<T, Alloc>& nct::Array4D<T, Alloc>::operator/=(
    const_reference right)
{
    for (size_type i = 0; i < n_; i++)
        data_[i] /= right;

    return *this;
}

//=================================================================================================================
//        BASIC MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array4D<T, Alloc>::clear() noexcept
{
    if (n_) {
        for (size_type i = 0; i<n_; i++)
            allocator_traits::destroy(alloc_, data_ + i);
        alloc_.deallocate(data_, n_);        
    }
    n_ = 0;
    nd1_ = 0;
    nd2_ = 0;    
    nd3_ = 0;
    nd4_ = 0;    
    data_ = nullptr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array4D<T, Alloc>::assign(size_type dim1, size_type dim2, 
    size_type dim3, size_type dim4, const_reference val)
{    
    if ( n_ == (dim1*dim2*dim3*dim4) ) {
        nd1_ = dim1;
        nd2_ = dim2;
        nd3_ = dim3;
        nd4_ = dim4;
        for (size_type i=0; i<n_; i++)
            data_[i] = val;
    }
    else {
        try {    
            // Release old data.
            clear();

            // Allocate new array.
            nd1_ = dim1;
            nd2_ = dim2;
            nd3_ = dim3;
            nd4_ = dim4;
            n_ = nd4_*nd3_*nd2_*nd1_;
            data_ = alloc_.allocate(n_);

            // Initialize data.
            for (size_type i=0; i<n_; i++)
                allocator_traits::construct(alloc_, data_ + i, val);
        }
        catch (const std::bad_alloc& ex) {
            throw MemoryException(SOURCE_INFO, std::make_exception_ptr(ex));
        }
        catch (...) {
            throw InitializationException(SOURCE_INFO);
        }
    }    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline void nct::Array4D<T, Alloc>::resize(size_type dim1, size_type dim2, size_type dim3,
    size_type dim4)
{    
    if ((nd1_ == dim1) && (nd2_ == dim2) && (nd4_ == dim4) && (nd3_ == dim3))
        return;

    // Previous array.
    auto pnd2 = nd1_;
    auto pnd = nd2_;
    auto pnr = nd3_;
    auto pnc = nd4_;
    auto pn = n_;

    // New array size.
    nd1_ = dim1;
    nd2_ = dim2;
    nd3_ = dim3;
    nd4_ = dim4;
    n_ = nd4_ * nd3_ * nd2_ * nd1_;

    // Block segment that will be preserved.
    auto d2Min = pnd2 < nd1_ ? (pnd2) : (nd1_);
    auto d1Min = pnd < nd2_ ? (pnd) : (nd2_);
    auto rMin = pnr < nd3_ ? (pnr) : (nd3_);
    auto cMin = pnc < nd4_ ? (pnc) : (nd4_);

    // Allocate memory and copy previous data.
    if (n_ > 0) {
        try {
            // Allocate new array.
            auto dd = data_;
            data_ = alloc_.allocate(n_);

            // Initialize data.
            for (size_type i = 0; i < nd1_; i++) {
                for (size_type j = 0; j < nd2_; j++) {
                    for (size_type k = 0; k < nd3_; k++) {
                        for (size_type l = 0; l < nd4_; l++) {
                            if ((i < d2Min) && (j < d1Min) && (k < rMin) && (l < cMin))
                                allocator_traits::construct(alloc_,
                                    data_ + (nd4_ * (nd3_ * (nd2_ * i + j) + k) + l),
                                    std::move(dd[pnc * (pnr * (pnd * i + j) + k) + l]));
                            else
                                allocator_traits::construct(alloc_,
                                    data_ + (nd4_ * (nd3_ * (nd2_ * i + j) + k) + l), T());
                        }
                    }
                }
            }

            // Release old data.
            if (pn > 0) {
                for (size_type i = 0; i < pn; i++)
                    allocator_traits::destroy(alloc_, dd + i);
                alloc_.deallocate(dd, pn);
            }
        }
        catch (const std::bad_alloc & ex) {
            throw MemoryException(SOURCE_INFO, std::make_exception_ptr(ex));
        }
        catch (...) {
            throw InitializationException(SOURCE_INFO);
        }
    }
    else if (pn > 0) {
        // Release old data.
        for (size_type i = 0; i < pn; i++)
            allocator_traits::destroy(alloc_, data_ + i);
        alloc_.deallocate(data_, pn);
        data_ = nullptr;
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array4D<T, Alloc>::resize(size_type dim1, size_type dim2, size_type dim3,
    size_type dim4, const_reference val)
{    
    if ( (nd1_ == dim1) && (nd2_ == dim2) && (nd4_ == dim4) && (nd3_ == dim3) )
        return;

    // Previous array.
    auto pnd2 = nd1_;
    auto pnd = nd2_;    
    auto pnr = nd3_;
    auto pnc = nd4_;    
    auto pn = n_;

    // New array size.
    nd1_ = dim1;
    nd2_ = dim2;
    nd3_ = dim3;
    nd4_ = dim4;    
    n_ = nd4_*nd3_*nd2_*nd1_;
    
    // Block segment that will be preserved.
    auto d2Min = pnd2 < nd1_? (pnd2) : (nd1_);
    auto d1Min = pnd < nd2_? (pnd) : (nd2_);
    auto rMin = pnr < nd3_? (pnr) : (nd3_);
    auto cMin = pnc < nd4_? (pnc) : (nd4_);

    // Allocate memory and copy previous data.
    if (n_>0) {
        try {    
            // Allocate new array.
            auto dd = data_;
            data_ = alloc_.allocate(n_);
            
            // Initialize data.
            for (size_type i=0; i<nd1_; i++) {
                for (size_type j=0; j<nd2_; j++) {
                    for (size_type k=0; k<nd3_; k++) {
                        for (size_type l=0; l<nd4_; l++) {
                            if ((i < d2Min) && (j < d1Min) && (k < rMin) && (l < cMin))
                                allocator_traits::construct(alloc_, 
                                    data_ + (nd4_ * (nd3_ * (nd2_ * i + j) + k) + l), 
                                std::move(dd[pnc * (pnr * (pnd * i + j) + k) + l]));
                            else
                                allocator_traits::construct(alloc_,
                                    data_ + (nd4_ * (nd3_ * (nd2_ * i + j) + k) + l), val);
                        }
                    }
                }
            }    

            // Release old data.
            if (pn>0) {
                for (size_type i = 0; i<pn; i++)
                    allocator_traits::destroy(alloc_, dd + i);
                alloc_.deallocate(dd, pn);
            }
        }
        catch (const std::bad_alloc& ex) {
            throw MemoryException(SOURCE_INFO, std::make_exception_ptr(ex));
        }
        catch (...) {
            throw InitializationException(SOURCE_INFO);
        }        
    }        
    else if (pn>0) {
        // Release old data.
        for (size_type i = 0; i<pn; i++)
            allocator_traits::destroy(alloc_, data_ + i);
        alloc_.deallocate(data_, pn);
        data_ = nullptr;
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::allocator_type
nct::Array4D<T, Alloc>::get_allocator() const
{
    return allocator_type(alloc_);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline void nct::Array4D<T, Alloc>::fill(const_reference val)
{
    for (size_type i=0; i<n_; i++)
        data_[i] = val;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array4D<T, Alloc>::reshape(size_type dim1, 
    size_type dim2, size_type dim3, size_type dim4)
{
    if (n_ != dim1*dim2*dim3*dim4)
        throw ArgumentException("dim1, dim2, dim3, dim4.", exc_bad_reshape_dimensions, SOURCE_INFO);
    nd1_ = dim1;
    nd2_ = dim2;
    nd3_ = dim3;
    nd4_ = dim4;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array4D<T, Alloc>::copy(const Array4D& other)
{
    if ( (data_ == other.data_) && (nd4_ == other.nd4_) && (nd3_ == other.nd3_) && 
        (nd2_ == other.nd2_) &&  (nd1_ == other.nd1_))
        return;

    if (other.n_ == 0) {
        // Release object.
        clear();
        nd1_ = other.nd1_;
        nd2_ = other.nd2_;
        nd3_ = other.nd3_;
        nd4_ = other.nd4_;
    }
    else if (n_ == other.n_) {
        // Copy new contents.
        nd1_ = other.nd1_;
        nd2_ = other.nd2_;
        nd3_ = other.nd3_;
        nd4_ = other.nd4_;
        for (size_type i=0; i<n_; i++)
            data_[i] = other.data_[i];
    }
    else {
        // Allocate new array and copy data.
        try {                
            clear();
            n_ = other.n_;
            nd1_ = other.nd1_;
            nd2_ = other.nd2_;
            nd3_ = other.nd3_;
            nd4_ = other.nd4_;
            data_ = alloc_.allocate(n_);

            for (size_type i=0; i<n_; i++)
                allocator_traits::construct(alloc_, data_ + i, other.data_[i]);            
        }
        catch (const std::bad_alloc& ex) {
            throw MemoryException(SOURCE_INFO, std::make_exception_ptr(ex));
        }
        catch (...) {
            throw InitializationException(SOURCE_INFO);
        }            
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
bool nct::Array4D<T, Alloc>::empty() const noexcept
{
    return (n_ == 0);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::size_type 
nct::Array4D<T, Alloc>::dimension1() const noexcept
{
    return nd1_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::size_type 
nct::Array4D<T, Alloc>::dimension2() const noexcept
{
    return nd2_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::size_type 
nct::Array4D<T, Alloc>::dimension3() const noexcept
{
    return nd3_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::size_type 
nct::Array4D<T, Alloc>::dimension4() const noexcept
{
    return nd4_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::size_type
nct::Array4D<T, Alloc>::size() const noexcept
{
    return n_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::pointer 
nct::Array4D<T, Alloc>::data() noexcept
{
    return data_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::const_pointer
nct::Array4D<T, Alloc>::data() const noexcept
{
    return data_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::pointer
nct::Array4D<T, Alloc>::data(size_type index)
{
    if (index >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
    return &data_[index];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::const_pointer 
nct::Array4D<T, Alloc>::data(size_type index) const
{
    if (index >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
    return &data_[index];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::pointer nct::Array4D<T, Alloc>::data(
    size_type dim1, size_type dim2, size_type dim3, size_type dim4)
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);
    if (dim4 >= nd4_)
        throw IndexOutOfRangeException("dim4", SOURCE_INFO);
    return &data_[nd4_ * (nd3_ * (nd2_ * dim1 + dim2) + dim3) + dim4];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::const_pointer
nct::Array4D<T, Alloc>::data(size_type dim1, size_type dim2,
size_type dim3, size_type dim4) const
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);
    if (dim4 >= nd4_)
        throw IndexOutOfRangeException("dim4", SOURCE_INFO);
    return &data_[nd4_ * (nd3_ * (nd2_ * dim1 + dim2) + dim3) + dim4];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::reference nct::Array4D<T, Alloc>::at(
    size_type index) 
{
    if (index >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
    return data_[index];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::const_reference nct::Array4D<T, Alloc>::at(
    size_type index) const
{
    if (index >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
    return data_[index];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::reference nct::Array4D<T, Alloc>::at(
    size_type dim1, size_type dim2, size_type dim3, size_type dim4)
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);
    if (dim4 >= nd4_)
        throw IndexOutOfRangeException("dim4", SOURCE_INFO);
    return data_[nd4_ * (nd3_ * (nd2_ * dim1 + dim2) + dim3) + dim4];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::const_reference nct::Array4D<T, Alloc>::at(
    size_type dim1, size_type dim2, size_type dim3, size_type dim4) const
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);
    if (dim4 >= nd4_)
        throw IndexOutOfRangeException("dim4", SOURCE_INFO);
    return data_[nd4_ * (nd3_ * (nd2_ * dim1 + dim2) + dim3) + dim4];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::size_type nct::Array4D<T, Alloc>::offset(
    size_type dim1) const noexcept
{
    return nd4_ * nd3_ * nd2_ * dim1;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::size_type nct::Array4D<T, Alloc>::offset(
    size_type dim1, size_type dim2) const noexcept
{
    return nd4_ * (nd3_ * (nd2_ * dim1 + dim2));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::size_type nct::Array4D<T, Alloc>::offset(
    size_type dim1, size_type dim2, size_type dim3) const noexcept
{
    return nd4_ * (nd3_ * (nd2_ * dim1 + dim2) + dim3);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::size_type nct::Array4D<T, Alloc>::offset(
    size_type dim1, size_type dim2, size_type dim3, size_type dim4) const noexcept
{
    return nd4_ * (nd3_ * (nd2_ * dim1 + dim2) + dim3) + dim4;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::reference nct::Array4D<T, Alloc>::front()
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);
    return data_[0];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::const_reference
nct::Array4D<T, Alloc>::front() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);
    return data_[0];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::reference nct::Array4D<T, Alloc>::back()
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);
    return data_[n_ - 1];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array4D<T, Alloc>::const_reference 
nct::Array4D<T, Alloc>::back() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);
    return data_[n_ - 1];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename Container> 
Container nct::Array4D<T, Alloc>::find(
    const_reference t) const
{
    size_type nIndices = 0;

    for (size_type i=0; i<n_; i++)
        nIndices += (data_[i] == t);
        
    Container obtTmp(nIndices);
    size_type c = 0;
    for (size_type i=0; i<n_; i++) {
        if (data_[i] == t)
            obtTmp[c++] = static_cast<typename Container::value_type>(i);
    }

    return obtTmp;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array4D<U, AllocU> nct::Array4D<T, Alloc>::toArray() const
{
    Array4D<U, AllocU> outputArray(nd1_, nd2_, nd3_, nd4_);        
    for (size_type k = 0; k<n_; k++)
        outputArray[k] = static_cast<U>(data_[k]);
    return outputArray;    
}

//=================================================================================================================
//        DATA INSERTIONS AND DELETIONS 
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array4D<T, Alloc>::insertDim1(size_type dim1, const Array3D<T, Alloc>& data)
{
    if (dim1 > nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);

    if ((data.dimension1() != nd2_) || (data.dimension2() != nd3_) || (data.dimension3() != nd4_))
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    // Move old data and resize array.
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_ + 1, old.nd2_, old.nd3_, old.nd4_);

    // Fill array.
    for (size_type i = 0; i<dim1; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);

    for (size_type j = 0; j<nd2_; j++)
        for (size_type k = 0; k<nd3_; k++)
            for (size_type l = 0; l<nd4_; l++)
                data_[offset(dim1, j, k, l)] = data(j, k, l);

    for (size_type i = dim1+1; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i - 1, j, k, l)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array4D<T, Alloc>::insertDim1(size_type dim1, const Array4D<T, Alloc>& data)
{
    if (dim1 > nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);

    if ((data.nd2_ != nd2_) || (data.nd3_ != nd3_) || (data.nd4_ != nd4_))
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    // Move old data and resize array.
    auto nnd2 = data.dimension1();
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_ + nnd2, old.nd2_, old.nd3_, old.nd4_);
    
    // Fill array.
    for (size_type i = 0; i<dim1; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);
    
    for (size_type i = dim1; i<(dim1 + nnd2); i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = data.data_[data.offset(i - dim1, j, k, l)];
    
    for (size_type i = (dim1 + nnd2); i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i - nnd2, j, k, l)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array4D<T, Alloc>::eraseDim1(size_type dim1)
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);

    // Move old data and resize array.
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_ - 1, old.nd2_, old.nd3_, old.nd4_);

    // Fill array.
    for (size_type i = 0; i<dim1; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);

    for (size_type i = dim1; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i + 1, j, k, l)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array4D<T, Alloc>::eraseDim1(size_type first, size_type last)
{
    if (first >= nd1_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nd1_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    // Move old data and resize array.
    auto nnd2 = last - first + 1;
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_ - nnd2, old.nd2_, old.nd3_, old.nd4_);
    
    // Fill array.
    for (size_type i = 0; i<first; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);
        
    for (size_type i = first; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i + nnd2, j, k, l)]);

}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
void nct::Array4D<T, Alloc>::eraseDim1(IndexIt first, IndexIt last)
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    size_type nnd2 = 0;
    for (auto ind1 = first; ind1 != last; ++ind1) {
        if (static_cast<size_type>(*ind1) >= nd1_)
            throw ArgumentException("first, last", exc_indices_out_of_range, SOURCE_INFO);

        auto ind2 = first;
        for (; ind2 != ind1; ++ind2) {
            if (static_cast<size_type>(*ind1) == static_cast<size_type>(*ind2))
                break;
        }        
        nnd2 += (ind2 == ind1);
    }

    // Move old data and resize array.
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_ - nnd2, old.nd2_, old.nd3_, old.nd4_);
    
    // Fill array.
    size_type c = 0;
    
    for (size_type i = 0; i < old.nd1_; i++) {
        auto ind = first;
        for (; ind != last; ++ind) {
            if (i == static_cast<size_type>(*ind))
                break;
        }

        if (ind == last) {
            for (size_type j = 0; j<nd2_; j++)
                for (size_type k = 0; k<nd3_; k++)
                    for (size_type l = 0; l<nd4_; l++)
                        data_[offset(c, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);
            c++;
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array4D<T, Alloc>::insertDim2(size_type dim2, const Array3D<T, Alloc>& data)
{
    if (dim2 > nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);

    if ((data.dimension1() != nd1_) || (data.dimension2() != nd3_) || (data.dimension3() != nd4_))
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    // Move old data and resize array.
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_ + 1, old.nd3_, old.nd4_);

    // Fill array.
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<dim2; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);

    for (size_type i = 0; i<nd1_; i++)
        for (size_type k = 0; k<nd3_; k++)
            for (size_type l = 0; l<nd4_; l++)
                data_[offset(i, dim2, k, l)] = data(i, k, l);

    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = (dim2 + 1); j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j - 1, k, l)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array4D<T, Alloc>::insertDim2(size_type dim2, const Array4D<T, Alloc>& data)
{
    if (dim2 > nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);

    if ((data.nd1_ != nd1_) || (data.nd3_ != nd3_) || (data.nd4_ != nd4_))
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    // Move old data and resize array.
    auto nnd = data.dimension2();
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_ + nnd, old.nd3_, old.nd4_);
    
    // Fill array.
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<dim2; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);
    
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = dim2; j<(dim2 + nnd); j++)
            for (size_type k=0; k<nd3_; k++)
                for (size_type l=0; l<nd4_; l++)        
                    data_[offset(i, j, k, l)] = data.data_[data.offset(i, j - dim2, k, l)];
    
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = (dim2 + nnd); j<nd2_; j++)
            for (size_type k=0; k<nd3_; k++)
                for (size_type l=0; l<nd4_; l++)        
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j - nnd, k, l)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array4D<T, Alloc>::eraseDim2(size_type dim2)
{
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);

    // Move old data and resize array.
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_ - 1, old.nd3_, old.nd4_);
    
    // Fill array.
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<dim2; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);
    
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = dim2; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j + 1, k, l)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array4D<T, Alloc>::eraseDim2(size_type first, size_type last)
{
    if (first >= nd2_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nd2_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    // Move old data and resize array.
    auto nnd = last - first + 1;
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_ - nnd, old.nd3_, old.nd4_);
    
    // Fill array.
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<first; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);
        
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = first; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j + nnd, k, l)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
void nct::Array4D<T, Alloc>::eraseDim2(IndexIt first, IndexIt last)
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    size_type nnd = 0;
    for (auto ind1 = first; ind1 != last; ++ind1) {
        if (static_cast<size_type>(*ind1) >= nd2_)
            throw ArgumentException("first, last", exc_indices_out_of_range, SOURCE_INFO);

        auto ind2 = first;
        for (; ind2 != ind1; ++ind2) {
            if (static_cast<size_type>(*ind1) == static_cast<size_type>(*ind2))
                break;
        }        
        nnd += (ind2 == ind1);
    }

    // Move old data and resize array.
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_ - nnd, old.nd3_, old.nd4_);
    
    // Fill array.
    size_type c = 0;
    
    for (size_type j = 0; j < old.nd2_; j++) {
        auto ind = first;
        for (; ind != last; ++ind) {
            if (j == static_cast<size_type>(*ind))
                break;
        }

        if (ind == last) {
            for (size_type i = 0; i<nd1_; i++)
                for (size_type k = 0; k < nd3_; k++)
                    for (size_type l = 0; l < nd4_; l++)
                        data_[offset(i, c, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);
            c++;
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array4D<T, Alloc>::insertDim3(size_type dim3, const Array3D<T, Alloc>& data)
{
    if (dim3 > nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);

    if ((data.dimension1() != nd1_) || (data.dimension2() != nd2_) || (data.dimension3() != nd4_))
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    // Move old data and resize array.
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_, old.nd3_ + 1, old.nd4_);

    // Fill array.
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<dim3; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);

    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type l = 0; l<nd4_; l++)
                data_[offset(i, j, dim3, l)] = data(i, j, l);

    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = (dim3 + 1); k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k - 1, l)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array4D<T, Alloc>::insertDim3(size_type dim3, const Array4D<T, Alloc>& data)
{
    if (dim3 > nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);

    if ((data.nd1_ != nd1_) || (data.nd2_ != nd2_) || (data.nd4_ != nd4_))
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    // Move old data and resize array.
    auto nnr = data.dimension3();
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_, old.nd3_ + nnr, old.nd4_);
    
    // Fill array.
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<dim3; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);
    
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k=dim3; k<(dim3+nnr); k++)
                for (size_type l=0; l<nd4_; l++)        
                    data_[offset(i, j, k, l)] = data.data_[data.offset(i, j, k - dim3, l)];
    
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k=(dim3+nnr); k<nd3_; k++)
                for (size_type l=0; l<nd4_; l++)        
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k - nnr, l)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array4D<T, Alloc>::eraseDim3(size_type dim3)
{
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);

    // Move old data and resize array.
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_, old.nd3_ - 1, old.nd4_);
    
    // Fill array.
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<dim3; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);
    
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = dim3; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k + 1, l)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array4D<T, Alloc>::eraseDim3(size_type first, size_type last)
{
    if (first >= nd3_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nd3_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    // Move old data and resize array.
    auto nnr = last - first + 1;
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_, old.nd3_ - nnr, old.nd4_);
    
    // Fill array.
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<first; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);
        
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = first; k<nd3_; k++)
                for (size_type l = 0; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k + nnr, l)]);

}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
void nct::Array4D<T, Alloc>::eraseDim3(IndexIt first, IndexIt last)
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    size_type nnr = 0;
    for (auto ind1 = first; ind1 != last; ++ind1) {
        if (static_cast<size_type>(*ind1) >= nd3_)
            throw ArgumentException("first, last", exc_indices_out_of_range, SOURCE_INFO);

        auto ind2 = first;
        for (; ind2 != ind1; ++ind2) {
            if (static_cast<size_type>(*ind1) == static_cast<size_type>(*ind2))
                break;
        }        
        nnr += (ind2 == ind1);
    }

    // Move old data and resize array.
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_, old.nd3_ - nnr, old.nd4_);
    
    // Fill array.
    size_type c = 0;
    
    for (size_type k = 0; k < old.nd3_; k++) {
        auto ind = first;
        for (; ind != last; ++ind) {
            if (k == static_cast<size_type>(*ind))
                break;
        }

        if (ind == last) {
            for (size_type i = 0; i<nd1_; i++)
                for (size_type j = 0; j < nd2_; j++)
                    for (size_type l = 0; l < nd4_; l++)
                        data_[offset(i, j, c, l)] = std::move(old.data_[old.offset(i, j, k, l)]);
            c++;
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array4D<T, Alloc>::insertDim4(size_type dim4, const Array3D<T, Alloc>& data)
{
    if (dim4 > nd4_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);

    if ((data.dimension1() != nd1_) || (data.dimension2() != nd2_) || (data.dimension3() != nd3_))
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    // Move old data and resize array.
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_, old.nd3_, old.nd4_ + 1);

    // Fill array.
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<dim4; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);

    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                data_[offset(i, j, k, dim4)] = data(i, j, k);

    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = (dim4 + 1); l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l - 1)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array4D<T, Alloc>::insertDim4(size_type dim4, const Array4D<T, Alloc>& data)
{
    if (dim4 > nd4_)
        throw IndexOutOfRangeException("dim4", SOURCE_INFO);

    if ((data.nd1_ != nd1_) || (data.nd2_ != nd2_) || (data.nd3_ != nd3_))
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    // Move old data and resize array.
    auto nnc = data.dimension4();
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_, old.nd3_, old.nd4_ + nnc);
    
    // Fill array.
    for (size_type i = 0; i < nd1_; i++) {
        for (size_type j = 0; j < nd2_; j++) {
            for (size_type k = 0; k < nd3_; k++) {
                for (size_type l = 0; l < dim4; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);

                for (size_type l = dim4; l < (dim4 + nnc); l++)
                    data_[offset(i, j, k, l)] = data.data_[data.offset(i, j, k, l - dim4)];

                for (size_type l = (dim4 + nnc); l < nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l - nnc)]);
            }
        }
    }
}        

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array4D<T, Alloc>::eraseDim4(size_type dim4)
{
    if (dim4 >= nd4_)
        throw IndexOutOfRangeException("dim4", SOURCE_INFO);

    // Move old data and resize array.
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_, old.nd3_, old.nd4_ - 1);

    // Fill array.
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = 0; l<dim4; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);

    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                for (size_type l = dim4; l<nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l + 1)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array4D<T, Alloc>::eraseDim4(size_type first, size_type last)
{
    if (first >= nd4_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nd4_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    // Move old data and resize array.
    auto nnc = last - first + 1;
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_, old.nd3_, old.nd4_ - nnc);
    
    // Fill array.
    for (size_type i = 0; i < nd1_; i++) {
        for (size_type j = 0; j < nd2_; j++) {
            for (size_type k = 0; k < nd3_; k++) {
                for (size_type l = 0; l < first; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l)]);

                for (size_type l = first; l < nd4_; l++)
                    data_[offset(i, j, k, l)] = std::move(old.data_[old.offset(i, j, k, l + nnc)]);
            }
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
void nct::Array4D<T, Alloc>::eraseDim4(IndexIt first, IndexIt last)
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    size_type nnc = 0;
    for (auto ind1 = first; ind1 != last; ++ind1) {
        if (static_cast<size_type>(*ind1) >= nd4_)
            throw ArgumentException("first, last", exc_indices_out_of_range, SOURCE_INFO);

        auto ind2 = first;
        for (; ind2 != ind1; ++ind2) {
            if (static_cast<size_type>(*ind1) == static_cast<size_type>(*ind2))
                break;
        }
        
        nnc += (ind2 == ind1);
    }

    // Move old data and resize array.
    nct::Array4D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_, old.nd3_, old.nd4_ - nnc);
    
    // Fill array.
    size_type c = 0;
    for (size_type l=0; l<old.nd4_; l++) {
        auto ind = first;
        for (; ind != last; ++ind) {
            if (l == static_cast<size_type>(*ind))
                break;
        }

        if (ind == last) {
            for (size_type i = 0; i < nd1_; i++)
                for (size_type j = 0; j < nd2_; j++)
                    for (size_type k=0; k<nd3_; k++)
                        data_[offset(i, j, k, c)] = std::move(old.data_[old.offset(i, j, k, l)]);
            c++;
        }        
    }
}


//=================================================================================================================
//        DATA SELECTION
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array3D<T, Alloc> nct::Array4D<T, Alloc>::subArray(size_type dim1) const
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);
        
    size_type nItems = nd2_*nd3_*nd4_;
    Array3D<T, Alloc> newArray(nd2_, nd3_, nd4_);    
    size_type start = nd4_ * (nd3_ * (nd2_ * dim1));
    for (size_type i=0; i<nItems; i++)
        newArray[i] = data_[i+start]; 

    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array<T, Alloc> nct::Array4D<T, Alloc>::elementsOfDim1(
    size_type dim2, size_type dim3, size_type dim4) const
{
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);
    if (dim4 >= nd4_)
        throw IndexOutOfRangeException("dim4", SOURCE_INFO);

    size_type nItems = nd1_;
    Array<T, Alloc> newArray(nItems);        
    size_type inc = nd2_*nd3_*nd4_;
    size_type start = nd4_ * (nd3_ * (dim2) + dim3) + dim4;
    for (size_type i=0; i<nItems; i++)
        newArray[i] = data_[i*inc+start]; 

    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array<T, Alloc> nct::Array4D<T, Alloc>::elementsOfDim2(
    size_type dim1, size_type dim3, size_type dim4) const
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);
    if (dim4 >= nd4_)
        throw IndexOutOfRangeException("dim4", SOURCE_INFO);

    size_type nItems = nd2_;
    Array<T, Alloc> newArray(nItems);    
    size_type inc = nd3_*nd4_;
    size_type start = nd4_ * (nd3_ * (nd2_ * dim1) + dim3) + dim4;
    for (size_type i=0; i<nItems; i++)
        newArray[i] = data_[i*inc+start]; 

    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array<T, Alloc> nct::Array4D<T, Alloc>::elementsOfDim3(
    size_type dim1, size_type dim2, size_type dim4) const
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);
    if (dim4 >= nd4_)
        throw IndexOutOfRangeException("dim4", SOURCE_INFO);

    size_type nItems = nd3_;
    Array<T, Alloc> newArray(nItems);    
    size_type inc = nd4_;
    size_type start = nd4_ * (nd3_ * (nd2_ * dim1 + dim2)) + dim4;
    for (size_type i=0; i<nItems; i++)
        newArray[i] = data_[i*inc+start]; 

    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array<T, Alloc> nct::Array4D<T, Alloc>::elementsOfDim4(
    size_type dim1, size_type dim2, size_type dim3) const
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);

    size_type nItems = nd4_;
    Array<T, Alloc> newArray(nItems);
    size_type start = nd4_ * (nd3_ * (nd2_ * dim1 + dim2) + dim3);
    for (size_type i=0; i<nItems; i++)
        newArray[i] = data_[i+start]; 

    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array<T, Alloc> nct::Array4D<T, Alloc>::selectRange(
    size_type first, size_type last) const
{
    if (last<first)
        throw RangeException("first, last", SOURCE_INFO);
    if (last >= n_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    auto nItems = last - first + 1;
    Array<T, Alloc> selData(nItems);

    for (size_type i = 0; i<nItems; i++)
        selData[i] = data_[i + first];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline nct::Array<T, Alloc> nct::Array4D<T, Alloc>::selectRange(
    const_iterator first, const_iterator last) const
{
    if (!first.validForComparison(begin()))
        throw IteratorException("first", SOURCE_INFO);

    if (!last.validForComparison(begin()))
        throw IteratorException("last", SOURCE_INFO);

    --last;
    return selectRange(first.currentIndex(), last.currentIndex());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
nct::Array<T, Alloc> nct::Array4D<T, Alloc>::selectData(IndexIt first, IndexIt last) const
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    auto nt = last - first;
    for (auto it = first; it != last; ++it) {
        if (static_cast<size_type>(*it) >= n_)
            throw IndexOutOfRangeException("first, last", SOURCE_INFO);
    }

    Array<T, Alloc> selData(nt);
    size_type i = 0;
    for (auto it = first; it != last; ++it, ++i)
        selData[i] = data_[static_cast<size_type>(*it)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU>
nct::Array<T, Alloc> nct::Array4D<T, Alloc>::selectData(
    const Array<size_type, AllocU>& indices) const
{
    return selectData(std::begin(indices), std::end(indices));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectSubArray(
    size_type firstDim1, size_type lastDim1,
    size_type firstDim2, size_type lastDim2, size_type firstDim3, size_type lastDim3, 
    size_type firstDim4, size_type lastDim4) const
{
    if (lastDim1<firstDim1)
        throw RangeException("firstDim1, lastDim1", SOURCE_INFO);

    if (lastDim2<firstDim2)
        throw RangeException("firstDim2, lastDim2", SOURCE_INFO);

    if (lastDim3<firstDim3)
        throw RangeException("firstDim3, lastDim3", SOURCE_INFO);

    if (lastDim4<firstDim4)
        throw RangeException("firstDim4, lastDim4", SOURCE_INFO);

    if (lastDim1 >= nd1_)
        throw IndexOutOfRangeException("lastDim1", SOURCE_INFO);

    if (lastDim2 >= nd2_)
        throw IndexOutOfRangeException("lastDim2", SOURCE_INFO);

    if (lastDim3 >= nd3_)
        throw IndexOutOfRangeException("lastDim3", SOURCE_INFO);
    
    if (lastDim4 >= nd4_)
        throw IndexOutOfRangeException("lastDim4", SOURCE_INFO);

    auto nNewDim22 = lastDim1-firstDim1+1;
    auto nNewDim21 = lastDim2-firstDim2+1;
    auto nNewDim3s = lastDim3-firstDim3+1;
    auto nNewCols = lastDim4-firstDim4+1;

    Array4D<T, Alloc> selData(nNewDim22, nNewDim21, nNewDim3s, nNewCols);
    for (size_type i=0; i<nNewDim22; i++)
        for (size_type j=0; j<nNewDim21; j++)
            for (size_type k=0; k<nNewDim3s; k++)
                for (size_type l=0; l<nNewCols; l++)
                    selData.data_[selData.offset(i, j, k, l)] = 
                    data_[offset(i + firstDim1, j + firstDim2, k + firstDim3, l + firstDim4)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
template<std::random_access_iterator IndexIt1, std::random_access_iterator IndexIt2,
    std::random_access_iterator IndexIt3, std::random_access_iterator IndexIt4>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectIndices(
    IndexIt1 firstDim1, IndexIt1 lastDim1,
    IndexIt2 firstDim2, IndexIt2 lastDim2,
    IndexIt3 firstDim3, IndexIt3 lastDim3,
    IndexIt4 firstDim4, IndexIt4 lastDim4) const
{
    if (lastDim1 < firstDim1)
        throw RangeException("firstDim1, lastDim1", SOURCE_INFO);

    if (lastDim2 < firstDim2)
        throw RangeException("firstDim2, lastDim2", SOURCE_INFO);

    if (lastDim3 < firstDim3)
        throw RangeException("firstDim3, lastDim3", SOURCE_INFO);

    if (lastDim4 < firstDim4)
        throw RangeException("firstDim4, lastDim4", SOURCE_INFO);

    auto nnd2 = lastDim1 - firstDim1;
    auto nnd1 = lastDim2 - firstDim2;
    auto nnr = lastDim3 - firstDim3;
    auto nnc = lastDim4 - firstDim4;

    for (auto dp2 = firstDim1; dp2!=lastDim1; ++dp2) {
        if (static_cast<size_type>(*dp2) >= nd1_)
            throw IndexOutOfRangeException("firstDim1, lastDim1", SOURCE_INFO);
    }

    for (auto dp1 = firstDim2; dp1!=lastDim2; ++dp1) {
        if (static_cast<size_type>(*dp1) >= nd2_)
            throw IndexOutOfRangeException("firstDim2, lastDim2", SOURCE_INFO);
    }

    for (auto r = firstDim3; r!=lastDim3; ++r) {
        if (static_cast<size_type>(*r) >= nd3_)
            throw IndexOutOfRangeException("firstDim3, lastDim3", SOURCE_INFO);
    }

    for (auto c = firstDim4; c!=lastDim4; ++c) {
        if (static_cast<size_type>(*c) >= nd4_)
            throw IndexOutOfRangeException("firstDim4, lastDim4", SOURCE_INFO);
    }
        
    Array4D<T, Alloc> selData(nnd2, nnd1, nnr, nnc);
    size_type i = 0;
    for (auto dp2 = firstDim1; dp2!=lastDim1; ++dp2, ++i) {
        size_type j = 0;
        for (auto dp1 = firstDim2; dp1!=lastDim2; ++dp1, ++j) {
            size_type k = 0;
            for (auto r = firstDim3; r!=lastDim3; ++r, ++k) {
                size_type l = 0;
                for (auto c = firstDim4; c!=lastDim4; ++c, ++l)
                    selData.data_[selData.offset(i, j, k, l)] = data_[offset(*dp2, *dp1, *r, *c)];
            }
        }
    }

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectIndices(
    const Array<size_type, AllocU>& dim1,
    const Array<size_type, AllocU>& dim2,
    const Array<size_type, AllocU>& dim3,
    const Array<size_type, AllocU>& dim4) const
{
    return selectIndices(std::begin(dim1), std::end(dim1),
        std::begin(dim2), std::end(dim2),
        std::begin(dim3), std::end(dim3),
        std::begin(dim4), std::end(dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectDim1(size_type dim1) const
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);

    Array4D<T, Alloc> selData(1, nd2_, nd3_, nd4_);
    for (size_type j=0; j<nd2_; j++)
        for (size_type k=0; k<nd3_; k++)
            for (size_type l=0; l<nd4_; l++)
                selData.data_[selData.offset(0, j, k, l)] = data_[offset(dim1, j, k, l)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectDim1(
    size_type first, size_type last) const
{
    if (first >= nd1_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nd1_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    auto nnd2 = last - first + 1;
    Array4D<T, Alloc> selData(nnd2, nd2_, nd3_, nd4_);
    for (size_type i=0; i<nnd2; i++)
        for (size_type j=0; j<nd2_; j++)
            for (size_type k=0; k<nd3_; k++)
                for (size_type l=0; l<nd4_; l++)
                    selData.data_[selData.offset(i, j, k, l)] = data_[offset(i + first, j, k, l)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectDim1(
    IndexIt first, IndexIt last) const
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    auto nnd2 = last - first;    
    for (auto dp2 = first; dp2 != last; ++dp2) {
        if (static_cast<size_type>(*dp2) >= nd1_)
            throw IndexOutOfRangeException("first, last", SOURCE_INFO);
    }

    Array4D<T, Alloc> selData(nnd2, nd2_, nd3_, nd4_);

    size_type i = 0;
    for (auto dp2 = first; dp2 != last; ++dp2, ++i)
        for (size_type j=0; j<nd2_; j++)
            for (size_type k=0; k<nd3_; k++)
                for (size_type l=0; l<nd4_; l++)
                    selData.data_[selData.offset(i, j, k, l)] = data_[offset(*dp2, j, k, l)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectDim1(
    const Array<size_type, AllocU>& dim1) const
{
    return selectDim1(std::begin(dim1), std::end(dim1));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectDim2(size_type dim2) const
{
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);

    Array4D<T, Alloc> selData(nd1_, 1, nd3_, nd4_);
    for (size_type i=0; i<nd1_; i++)
        for (size_type k=0; k<nd3_; k++)
            for (size_type l=0; l<nd4_; l++)
                selData.data_[selData.offset(i, 0, k, l)] = data_[offset(i, dim2, k, l)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectDim2(
    size_type first, size_type last) const
{
    if (first >= nd2_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nd2_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    size_type nnd1 = last - first + 1;
    Array4D<T, Alloc> selData(nd1_, nnd1, nd3_, nd4_);
    for (size_type i=0; i<nd1_; i++)
        for (size_type j=0; j<nnd1; j++)
            for (size_type k=0; k<nd3_; k++)
                for (size_type l=0; l<nd4_; l++)
                    selData.data_[selData.offset(i, j, k, l)] = data_[offset(i, j + first, k, l)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectDim2(
    IndexIt first, IndexIt last) const
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    auto nnd1 = last - first;
    for (auto dp1 = first; dp1 != last; ++dp1) {
        if (static_cast<size_type>(*dp1) >= nd2_)
            throw IndexOutOfRangeException("first, last", SOURCE_INFO);
    }

    Array4D<T, Alloc> selData(nd1_, nnd1, nd3_, nd4_);
    for (size_type i=0; i<nd1_; i++) {
        size_type j = 0;
        for (auto dp1 = first; dp1 != last; ++dp1, ++j)
            for (size_type k=0; k<nd3_; k++)
                for (size_type l=0; l<nd4_; l++)    
                    selData.data_[selData.offset(i, j, k, l)] = data_[offset(i, *dp1, k, l)];
    }

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectDim2(
    const Array<size_type, AllocU>& dim2) const
{
    return selectDim2(std::begin(dim2), std::end(dim2));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectDim3(size_type dim3) const
{
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);

    Array4D<T, Alloc> selData(nd1_, nd2_, 1, nd4_);
    for (size_type i=0; i<nd1_; i++)
        for (size_type j=0; j<nd2_; j++)
            for (size_type l=0; l<nd4_; l++)
                selData.data_[selData.offset(i, j, 0, l)] = data_[offset(i, j, dim3, l)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectDim3(
    size_type first, size_type last) const
{
    if (first >= nd3_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nd3_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    auto nnr = last - first + 1;
    Array4D<T, Alloc> selData(nd1_, nd2_, nnr, nd4_);
    for (size_type i=0; i<nd1_; i++)
        for (size_type j=0; j<nd2_; j++)
            for (size_type k=0; k<nnr; k++)
                for (size_type l=0; l<nd4_; l++)
                    selData.data_[selData.offset(i, j, k, l)] = data_[offset(i, j, k + first, l)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectDim3(
    IndexIt first, IndexIt last) const
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    auto nnr = last - first;
    for (auto r = first; r != last; ++r) {
        if (static_cast<size_type>(*r) >= nd3_)
            throw IndexOutOfRangeException("first, last", SOURCE_INFO);
    }

    Array4D<T, Alloc> selData(nd1_, nd2_, nnr, nd4_);
    for (size_type i=0; i<nd1_; i++) {
        for (size_type j=0; j<nd2_; j++) {
            size_type k = 0;
            for (auto r = first; r != last; ++r, ++k) {
                for (size_type l=0; l<nd4_; l++)
                    selData.data_[selData.offset(i, j, k, l)] = data_[offset(i, j, *r, l)];
            }
        }
    }

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectDim3(
    const Array<size_type, AllocU>& dim3) const
{
    return selectDim3(std::begin(dim3), std::end(dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectDim4(size_type dim4) const
{
    if (dim4 >= nd4_)
        throw IndexOutOfRangeException("dim4", SOURCE_INFO);

    Array4D<T, Alloc> selData(nd1_, nd2_, nd3_, 1);
    for (size_type i=0; i<nd1_; i++)
        for (size_type j=0; j<nd2_; j++)
            for (size_type k=0; k<nd3_; k++)
                selData.data_[selData.offset(i, j, k, 0)] = data_[offset(i, j, k, dim4)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectDim4(
    size_type first, size_type last) const
{
    if (first >= nd4_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nd4_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    auto nnc = last - first + 1;
    Array4D<T, Alloc> selData(nd1_, nd2_, nd3_, nnc);
    for (size_type i=0; i<nd1_; i++)
        for (size_type j=0; j<nd2_; j++)
            for (size_type k=0; k<nd3_; k++)
                for (size_type l=0; l<nnc; l++)
                    selData.data_[selData.offset(i, j, k, l)] = data_[offset(i, j, k, l + first)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectDim4(
    IndexIt first, IndexIt last) const
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    auto nnc = last - first;
    for (auto c = first; c!=last; ++c) {
        if (static_cast<size_type>(*c) >= nd4_)
            throw IndexOutOfRangeException("first, last", SOURCE_INFO);
    }
        
    Array4D<T, Alloc> selData(nd1_, nd2_, nd3_, nnc);
    for (size_type i=0; i<nd1_; i++) {
        for (size_type j=0; j<nd2_; j++) {
            for (size_type k=0; k<nd3_; k++) {
                size_type l = 0;
                for (auto c = first; c!=last; ++c, ++l)
                    selData.data_[selData.offset(i, j, k, l)] = data_[offset(i, j, k, *c)];
            }
        }
    }

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::selectDim4(
    const Array<size_type, AllocU>& dim4) const
{
    return selectDim4(std::begin(dim4), std::end(dim4));
}

//=================================================================================================================
//        CIRCULAR SHIFTS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::circularDim1Shift(
    difference_type i0) const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array4D<T, Alloc> res(nd1_, nd2_, nd3_, nd4_);
    for (difference_type i = 0; i < static_cast<difference_type>(nd1_); i++) {
        difference_type off = i + i0;
        while (off < 0)
            off += nd1_;
        off %= nd1_;

        for (difference_type j = 0; j < static_cast<difference_type>(nd2_); j++)
            for (difference_type k = 0; k < static_cast<difference_type>(nd3_); k++)
                for (difference_type l = 0; l < static_cast<difference_type>(nd4_); l++)
                    res.data_[res.offset(i, j, k, l)] = data_[offset(off, j, k, l)];
    }

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::circularDim2Shift(
    difference_type j0) const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array4D<T, Alloc> res(nd1_, nd2_, nd3_, nd4_);
    for (difference_type j = 0; j < static_cast<difference_type>(nd2_); j++) {
        difference_type off = j + j0;
        while (off < 0)
            off += nd2_;
        off %= nd2_;

        for (difference_type i = 0; i < static_cast<difference_type>(nd1_); i++)
            for (difference_type k = 0; k < static_cast<difference_type>(nd3_); k++)
                for (difference_type l = 0; l < static_cast<difference_type>(nd4_); l++)
                    res.data_[res.offset(i, j, k, l)] = data_[offset(i, off, k, l)];
    }

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::circularDim3Shift(
    difference_type k0) const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array4D<T, Alloc> res(nd1_, nd2_, nd3_, nd4_);
    for (difference_type k = 0; k < static_cast<difference_type>(nd3_); k++) {
        difference_type off = k + k0;
        while (off < 0)
            off += nd3_;
        off %= nd3_;

        for (difference_type i = 0; i < static_cast<difference_type>(nd1_); i++)
            for (difference_type j = 0; j < static_cast<difference_type>(nd2_); j++)
                for (difference_type l = 0; l < static_cast<difference_type>(nd4_); l++)
                    res.data_[res.offset(i, j, k, l)] = data_[offset(i, j, off, l)];
    }

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::circularDim4Shift(
    difference_type l0) const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array4D<T, Alloc> res(nd1_, nd2_, nd3_, nd4_);
    for (difference_type l=0; l<static_cast<difference_type>(nd4_); l++) {
        difference_type off = l+l0;
        while (off<0)
            off+=nd4_;
        off %= nd4_;

        for (difference_type i=0; i<static_cast<difference_type>(nd1_); i++)    
            for (difference_type j = 0; j<static_cast<difference_type>(nd2_); j++)
                for (difference_type k = 0; k < static_cast<difference_type>(nd3_); k++)
                    res.data_[res.offset(i, j, k, l)] = data_[offset(i, j, k, off)];
    }

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::circularShift(difference_type i0, 
    difference_type j0, difference_type k0, difference_type l0) const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array4D<T, Alloc> res(nd1_, nd2_, nd3_, nd4_);
    for (difference_type i = 0; i < static_cast<difference_type>(nd1_); i++) {
        difference_type off1 = i + i0;
        while (off1 < 0)
            off1 += nd1_;
        off1 %= nd1_;

        for (difference_type j = 0; j < static_cast<difference_type>(nd2_); j++) {
            difference_type off2 = j + j0;
            while (off2 < 0)
                off2 += nd2_;
            off2 %= nd2_;

            for (difference_type k = 0; k < static_cast<difference_type>(nd3_); k++) {
                difference_type off3 = k + k0;
                while (off3 < 0)
                    off3 += nd3_;
                off3 %= nd3_;

                for (difference_type l = 0; l < static_cast<difference_type>(nd4_); l++) {
                    difference_type off4 = l + l0;
                    while (off4 < 0)
                        off4 += nd4_;
                    off4 %= nd4_;

                    res.data_[res.offset(i, j, k, l)] = data_[offset(off1, off2, off3, off4)];
                }
            }
        }
    }

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::circularShift() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array4D<T, Alloc> res(nd1_, nd2_, nd3_, nd4_);
    size_type depthC2 = (nd1_ + 1) / 2;
    size_type depthC1 = (nd2_ + 1) / 2;
    size_type rowsC = (nd3_ + 1) / 2; 
    size_type columnsC = (nd4_ + 1) / 2;

    for (difference_type i = 0; i<static_cast<difference_type>(nd1_); i++)
        for (difference_type j = 0; j<static_cast<difference_type>(nd2_); j++)
            for (difference_type k=0; k<static_cast<difference_type>(nd3_); k++)
                for (difference_type l=0; l<static_cast<difference_type>(nd4_); l++)
                    res.data_[res.offset(i, j, k, l)] = 
                    data_[offset((i + depthC2) % nd1_, (j + depthC1) % nd2_,
                    (k + rowsC) % nd3_, (l + columnsC) % nd4_)];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::circularInvShift() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array4D<T, Alloc> res(nd1_, nd2_, nd3_, nd4_);
    size_type depthC2 = (nd1_ + 1) / 2;
    size_type depthC1 = (nd2_ + 1) / 2;
    size_type rowsC = (nd3_ + 1) / 2;
    size_type columnsC = (nd4_ + 1) / 2;
    
    for (size_type i = 0; i < nd1_; i++) {
        auto iPos = (i < depthC2) ? (nd1_ + i - depthC2) : (i - depthC2);
        for (size_type j = 0; j < nd2_; j++) {
            auto jPos = (j < depthC1) ? (nd2_ + j - depthC1) : (j - depthC1);
            for (size_type k = 0; k < nd3_; k++) {
                auto kPos = (k < rowsC) ? (nd3_ + k - rowsC) : (k - rowsC);
                for (size_type l = 0; l < nd4_; l++) {
                    auto lPos = (l < columnsC) ? (nd4_ + l - columnsC) : (l - columnsC);
                    res.data_[res.offset(i, j, k, l)] = data_[offset(iPos, jPos, kPos, lPos)];
                }
            }
        }
    }

    return res;
}

//=================================================================================================================
//        NUMERICAL OPERATIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Addable<T>
typename nct::Array4D<T, Alloc>::value_type nct::Array4D<T, Alloc>::sum() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    T r = 0;

    for (size_type i=0; i<n_; i++)
        r += data_[i];

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Arithmetic<T>
double nct::Array4D<T, Alloc>::castSum() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    double r = 0;

    for (size_type i=0; i<n_; i++)
        r += static_cast<double>(data_[i]);

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
typename nct::Array4D<T, Alloc>::value_type 
nct::Array4D<T, Alloc>::squaredNorm() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    T r = 0;

    for (size_type i=0; i<n_; i++)
        r += std::norm(data_[i]);

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
double nct::Array4D<T, Alloc>::euclideanNorm() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    double r = 0;

    for (size_type i=0; i<n_; i++)
        r += static_cast<double>(std::norm(data_[i]));

    return std::sqrt(r);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
double nct::Array4D<T, Alloc>::lpNorm(double p) const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    if (p<1)
        throw ArgumentException("p", p, 1.,
        RelationalOperator::GreaterThanOrEqualTo, SOURCE_INFO);

    double res = 0;    
    if (p==1) {
        // L1
        for (size_type i=0; i<n_; i++)
            res += static_cast<double>(std::abs(data_[i]));
        return res;
    }

    // LP
    for (size_type i=0; i<n_; i++)
        res += std::pow(static_cast<double>(std::abs(data_[i])), static_cast<double>(p));
    
    return std::pow(res, 1/p);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
double nct::Array4D<T, Alloc>::infinityNorm() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    double res = 0;    
    for (size_type i=0; i<n_; i++) {
        double tmp = static_cast<double>(std::abs(data_[i]));
        if (tmp > res)
            res = tmp;
    }
    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Arithmetic<T>
double nct::Array4D<T, Alloc>::mean() const
{
    if (n_<1)
        throw EmptyArrayException(SOURCE_INFO);    

    double res = 0; 

    for (size_type i=0; i<n_; i++)
        res += data_[i];
    
    return res/n_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Arithmetic<T>
double nct::Array4D<T, Alloc>::variance() const
{
    if (n_<2)
        throw ConfigurationException(exc_array_with_less_than_two_elements, SOURCE_INFO);    

    double res = 0; 
    double meanVal = mean(); 

    for (size_type i=0; i<n_; i++)
        res += (data_[i] - meanVal)*(data_[i] - meanVal);        
    
    return res/(n_-1);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::totally_ordered<T>
typename nct::Array4D<T, Alloc>::value_type nct::Array4D<T, Alloc>::max() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    T r = data_[0];

    for (size_type i=1; i<n_; i++) {
        if (data_[i] > r)
            r = data_[i];
    }

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::totally_ordered<T>
typename nct::Array4D<T, Alloc>::value_type nct::Array4D<T, Alloc>::min() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    T r = data_[0];

    for (size_type i=1; i<n_; i++) {
        if (data_[i] < r)
            r = data_[i];
    }

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T, typename Alloc>
T nct::dotProduct(const Array4D<T, Alloc>& a, const Array4D<T, Alloc>& b)
{
    if ((a.dimension1() != b.dimension1()) || (a.dimension2() != b.dimension2()) ||
         (a.dimension3() != b.dimension3()) || (a.dimension4() != b.dimension4()) )
        throw ArgumentException("a, b", exc_arrays_of_different_dimensions, SOURCE_INFO);    

    auto n = a.size();
    T temp = 0;        
    for (index_t i = 0; i<n; i++)
        temp += a[i]*b[i];
    return temp;
}

//=================================================================================================================
//        SPECIAL ARRAYS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::constant(
    size_type dim1, size_type dim2, size_type dim3, size_type dim4, const_reference t)
{
    return nct::Array4D<T, Alloc>(dim1, dim2, dim3, dim4, t);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::zeros(
    size_type dim1, size_type dim2, size_type dim3, size_type dim4)
{
    return nct::Array4D<T, Alloc>(dim1, dim2, dim3, dim4, 0);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::ones(
    size_type dim1, size_type dim2, size_type dim3, size_type dim4)
{
    return nct::Array4D<T, Alloc>(dim1, dim2, dim3, dim4, 1);
}



//=================================================================================================================
//        ITERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::iterator 
nct::Array4D<T, Alloc>::begin()
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, 0);    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator
nct::Array4D<T, Alloc>::begin() const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, 0);    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator 
nct::Array4D<T, Alloc>::cbegin() const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, 0);    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::iterator
nct::Array4D<T, Alloc>::end()
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, n_);    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator 
nct::Array4D<T, Alloc>::end() const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, n_);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator
nct::Array4D<T, Alloc>::cend() const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, n_);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::reverse_iterator 
nct::Array4D<T, Alloc>::rbegin()
{
    return reverse_iterator(end());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator
nct::Array4D<T, Alloc>::rbegin() const
{
    return const_reverse_iterator(end());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator 
nct::Array4D<T, Alloc>::crbegin() const
{
    return const_reverse_iterator(end());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::reverse_iterator
nct::Array4D<T, Alloc>::rend()
{
    return reverse_iterator(begin());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator 
nct::Array4D<T, Alloc>::rend() const
{
    return const_reverse_iterator(begin());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator 
nct::Array4D<T, Alloc>::crend() const
{
    return const_reverse_iterator(begin());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::iterator 
nct::Array4D<T, Alloc>::beginDim1(
    size_type dim2, size_type dim3, size_type dim4)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, 0, dim2, dim3, dim4, IteratorShiftMode4D::Dim1Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator 
nct::Array4D<T, Alloc>::beginDim1(
    size_type dim2, size_type dim3, size_type dim4) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, 0, dim2, dim3, dim4, IteratorShiftMode4D::Dim1Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator
nct::Array4D<T, Alloc>::cbeginDim1(
    size_type dim2, size_type dim3, size_type dim4) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, 0, dim2, dim3, dim4, IteratorShiftMode4D::Dim1Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::iterator 
nct::Array4D<T, Alloc>::endDim1(
    size_type dim2, size_type dim3, size_type dim4)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, nd1_, dim2, dim3, dim4, IteratorShiftMode4D::Dim1Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator
nct::Array4D<T, Alloc>::endDim1(
    size_type dim2, size_type dim3, size_type dim4) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, nd1_, dim2, dim3, dim4, IteratorShiftMode4D::Dim1Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator
nct::Array4D<T, Alloc>::cendDim1(
    size_type dim2, size_type dim3, size_type dim4) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, nd1_, dim2, dim3, dim4, IteratorShiftMode4D::Dim1Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::reverse_iterator
nct::Array4D<T, Alloc>::rbeginDim1(
    size_type dim2, size_type dim3, size_type dim4)
{
    return reverse_iterator(endDim1(dim2, dim3, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator
nct::Array4D<T, Alloc>::rbeginDim1(
    size_type dim2, size_type dim3, size_type dim4) const
{
    return const_reverse_iterator(endDim1(dim2, dim3, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator 
nct::Array4D<T, Alloc>::crbeginDim1(
    size_type dim2, size_type dim3, size_type dim4) const
{
    return const_reverse_iterator(endDim1(dim2, dim3, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::reverse_iterator 
nct::Array4D<T, Alloc>::rendDim1(
    size_type dim2, size_type dim3, size_type dim4)
{
    return reverse_iterator(beginDim1(dim2, dim3, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator 
nct::Array4D<T, Alloc>::rendDim1(
    size_type dim2, size_type dim3, size_type dim4) const
{
    return const_reverse_iterator(beginDim1(dim2, dim3, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator 
nct::Array4D<T, Alloc>::crendDim1(
    size_type dim2, size_type dim3, size_type dim4) const
{
    return const_reverse_iterator(beginDim1(dim2, dim3, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::iterator
nct::Array4D<T, Alloc>::beginDim2(
    size_type dim1, size_type dim3, size_type dim4)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, dim1, 0, dim3, dim4, IteratorShiftMode4D::Dim2Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator
nct::Array4D<T, Alloc>::beginDim2(
    size_type dim1, size_type dim3, size_type dim4) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, 0, dim3, dim4, IteratorShiftMode4D::Dim2Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator
nct::Array4D<T, Alloc>::cbeginDim2(
    size_type dim1, size_type dim3, size_type dim4) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, 0, dim3, dim4, IteratorShiftMode4D::Dim2Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::iterator 
nct::Array4D<T, Alloc>::endDim2(
    size_type dim1, size_type dim3, size_type dim4)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, dim1, nd2_, dim3, dim4, IteratorShiftMode4D::Dim2Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator
nct::Array4D<T, Alloc>::endDim2(
    size_type dim1, size_type dim3, size_type dim4) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, nd2_, dim3, dim4, IteratorShiftMode4D::Dim2Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator 
nct::Array4D<T, Alloc>::cendDim2(
    size_type dim1, size_type dim3, size_type dim4) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, nd2_, dim3, dim4, IteratorShiftMode4D::Dim2Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::reverse_iterator
nct::Array4D<T, Alloc>::rbeginDim2(
    size_type dim1, size_type dim3, size_type dim4)
{
    return reverse_iterator(endDim2(dim1, dim3, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator 
nct::Array4D<T, Alloc>::rbeginDim2(
    size_type dim1, size_type dim3, size_type dim4) const
{
    return const_reverse_iterator(endDim2(dim1, dim3, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator
nct::Array4D<T, Alloc>::crbeginDim2(
    size_type dim1, size_type dim3, size_type dim4) const
{
    return const_reverse_iterator(endDim2(dim1, dim3, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::reverse_iterator 
nct::Array4D<T, Alloc>::rendDim2(
    size_type dim1, size_type dim3, size_type dim4)
{
    return reverse_iterator(beginDim2(dim1, dim3, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator
nct::Array4D<T, Alloc>::rendDim2(
    size_type dim1, size_type dim3, size_type dim4) const
{
    return const_reverse_iterator(beginDim2(dim1, dim3, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator
nct::Array4D<T, Alloc>::crendDim2(
    size_type dim1, size_type dim3, size_type dim4) const
{
    return const_reverse_iterator(beginDim2(dim1, dim3, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::iterator 
nct::Array4D<T, Alloc>::beginDim3(size_type dim1, 
    size_type dim2, size_type dim4)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, dim1, dim2, 0, dim4, IteratorShiftMode4D::Dim3Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator
nct::Array4D<T, Alloc>::beginDim3(size_type dim1, 
    size_type dim2, size_type dim4) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, dim2, 0, dim4, IteratorShiftMode4D::Dim3Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator 
nct::Array4D<T, Alloc>::cbeginDim3(size_type dim1, 
    size_type dim2, size_type dim4) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, dim2, 0, dim4, IteratorShiftMode4D::Dim3Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::iterator 
nct::Array4D<T, Alloc>::endDim3(size_type dim1, 
    size_type dim2, size_type dim4)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, dim1, dim2, nd3_, dim4, IteratorShiftMode4D::Dim3Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator 
nct::Array4D<T, Alloc>::endDim3(size_type dim1, 
    size_type dim2, size_type dim4) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, dim2, nd3_, dim4, IteratorShiftMode4D::Dim3Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator 
nct::Array4D<T, Alloc>::cendDim3(size_type dim1, 
    size_type dim2, size_type dim4) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, dim2, nd3_, dim4, IteratorShiftMode4D::Dim3Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::reverse_iterator 
nct::Array4D<T, Alloc>::rbeginDim3(
    size_type dim1, size_type dim2, size_type dim4)
{
    return reverse_iterator(endDim3(dim1, dim2, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator
nct::Array4D<T, Alloc>::rbeginDim3(
    size_type dim1, size_type dim2, size_type dim4) const
{
    return const_reverse_iterator(endDim3(dim1, dim2, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator
nct::Array4D<T, Alloc>::crbeginDim3(
    size_type dim1, size_type dim2, size_type dim4) const
{
    return const_reverse_iterator(endDim3(dim1, dim2, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::reverse_iterator
nct::Array4D<T, Alloc>::rendDim3(size_type dim1, 
    size_type dim2, size_type dim4)
{
    return reverse_iterator(beginDim3(dim1, dim2, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator 
nct::Array4D<T, Alloc>::rendDim3(
    size_type dim1, size_type dim2, size_type dim4) const
{
    return const_reverse_iterator(beginDim3(dim1, dim2, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator
nct::Array4D<T, Alloc>::crendDim3(
    size_type dim1, size_type dim2, size_type dim4) const
{
    return const_reverse_iterator(beginDim3(dim1, dim2, dim4));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::iterator 
nct::Array4D<T, Alloc>::beginDim4(
    size_type dim1, size_type dim2, size_type dim3)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, dim1, dim2, dim3, 0, IteratorShiftMode4D::Dim4Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator 
nct::Array4D<T, Alloc>::beginDim4(
    size_type dim1, size_type dim2, size_type dim3) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, dim2, dim3, 0, IteratorShiftMode4D::Dim4Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator 
nct::Array4D<T, Alloc>::cbeginDim4(
    size_type dim1, size_type dim2, size_type dim3) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, dim2, dim3, 0, IteratorShiftMode4D::Dim4Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::iterator
nct::Array4D<T, Alloc>::endDim4(
    size_type dim1, size_type dim2, size_type dim3)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, dim1, dim2, dim3, nd4_, IteratorShiftMode4D::Dim4Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator
nct::Array4D<T, Alloc>::endDim4(
    size_type dim1, size_type dim2, size_type dim3) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, dim2, dim3, nd4_, IteratorShiftMode4D::Dim4Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_iterator 
nct::Array4D<T, Alloc>::cendDim4(
    size_type dim1, size_type dim2, size_type dim3) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, dim2, dim3, nd4_, IteratorShiftMode4D::Dim4Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::reverse_iterator 
nct::Array4D<T, Alloc>::rbeginDim4(
    size_type dim1, size_type dim2, size_type dim3)
{
    return reverse_iterator(endDim4(dim1, dim2, dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator
nct::Array4D<T, Alloc>::rbeginDim4(
    size_type dim1, size_type dim2, size_type dim3) const
{
    return const_reverse_iterator(endDim4(dim1, dim2, dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator
nct::Array4D<T, Alloc>::crbeginDim4(
    size_type dim1, size_type dim2, size_type dim3) const
{
    return const_reverse_iterator(endDim4(dim1, dim2, dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::reverse_iterator
nct::Array4D<T, Alloc>::rendDim4(
    size_type dim1, size_type dim2, size_type dim3)
{
    return reverse_iterator(beginDim4(dim1, dim2, dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator 
nct::Array4D<T, Alloc>::rendDim4(
    size_type dim1, size_type dim2, size_type dim3) const
{
    return const_reverse_iterator(beginDim4(dim1, dim2, dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array4D<T, Alloc>::const_reverse_iterator 
nct::Array4D<T, Alloc>::crendDim4(
    size_type dim1, size_type dim2, size_type dim3) const
{
    return const_reverse_iterator(beginDim4(dim1, dim2, dim3));
}


//=================================================================================================================
//        TRANSFORMATIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array4D<U, AllocU> nct::Array4D<T, Alloc>::transformData(
    const std::function<U(const_reference)>& f) const
{
    Array4D<U, AllocU> outputArray(nd1_, nd2_, nd3_, nd4_);        
    for (size_type k = 0; k<n_; k++)
        outputArray[k] = f(data_[k]);
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array4D<U, AllocU> nct::Array4D<T, Alloc>::collapseDim1(
    const std::function<U(const Array<T, Alloc>&)>& f) const
{
    Array4D<U, AllocU> outputArray(1, nd2_, nd3_, nd4_);
    for (size_type j = 0; j<nd2_; j++)
        for (size_type k = 0; k<nd3_; k++)
            for (size_type l = 0; l<nd4_; l++)
                outputArray(0, j, k, l) = f(elementsOfDim1(j, k, l));
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array4D<U, AllocU> nct::Array4D<T, Alloc>::collapseDim1(
    const std::function<U(const_iterator, const_iterator)>& f) const
{
    Array4D<U, AllocU> outputArray(1, nd2_, nd3_, nd4_);
    for (size_type j = 0; j<nd2_; j++)
        for (size_type k = 0; k<nd3_; k++)
            for (size_type l = 0; l<nd4_; l++)
                outputArray(0, j, k, l) = f(beginDim1(j, k, l), endDim1(j, k, l));
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array4D<U, AllocU> nct::Array4D<T, Alloc>::collapseDim2(
    const std::function<U(const Array<T, Alloc>&)>& f) const
{
    Array4D<U, AllocU> outputArray(nd1_, 1, nd3_, nd4_);
    for (size_type i = 0; i<nd1_; i++)
        for (size_type k = 0; k<nd3_; k++)
            for (size_type l = 0; l<nd4_; l++)
                outputArray(i, 0, k, l) = f(elementsOfDim2(i, k, l));
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array4D<U, AllocU> nct::Array4D<T, Alloc>::collapseDim2(
    const std::function<U(const_iterator, const_iterator)>& f) const
{
    Array4D<U, AllocU> outputArray(nd1_, 1, nd3_, nd4_);
    for (size_type i = 0; i<nd1_; i++)
        for (size_type k = 0; k<nd3_; k++)
            for (size_type l = 0; l<nd4_; l++)
                outputArray(i, 0, k, l) = f(beginDim2(i, k, l), endDim2(i, k, l));
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array4D<U, AllocU> nct::Array4D<T, Alloc>::collapseDim3(
    const std::function<U(const Array<T, Alloc>&)>& f) const
{
    Array4D<U, AllocU> outputArray(nd1_, nd2_, 1, nd4_);        
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type l = 0; l<nd4_; l++)
                outputArray(i, j, 0, l) = f(elementsOfDim3(i,j,l));
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array4D<U, AllocU> nct::Array4D<T, Alloc>::collapseDim3(
    const std::function<U(const_iterator, const_iterator)>& f) const
{
    Array4D<U, AllocU> outputArray(nd1_, nd2_, 1, nd4_);        
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type l = 0; l<nd4_; l++)
                outputArray(i, j, 0, l) = f(beginDim3(i, j, l), endDim3(i, j, l));
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array4D<U, AllocU> nct::Array4D<T, Alloc>::collapseDim4(
    const std::function<U(const Array<T, Alloc>&)>& f) const
{
    Array4D<U, AllocU> outputArray(nd1_, nd2_, nd3_, 1);        
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                outputArray(i, j, k, 0) = f(elementsOfDim4(i,j,k));
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array4D<U, AllocU> nct::Array4D<T, Alloc>::collapseDim4(
    const std::function<U(const_iterator, const_iterator)>& f) const
{
    Array4D<U, AllocU> outputArray(nd1_, nd2_, nd3_, 1);
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                outputArray(i, j, k, 0) = f(beginDim4(i, j, k), endDim4(i, j, k));
    return outputArray;    
}

//=================================================================================================================
//        I/O OPERATIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array4D<T, Alloc> nct::Array4D<T, Alloc>::read(std::istream& i)
{
    // Check for errors.
    if (i.fail())
        throw IOException(exc_bad_input_stream, SOURCE_INFO);

    // Read dimensions.
    size_type d1 = 0;
    size_type d2 = 0;
    size_type r = 0;
    size_type c = 0;

    i.read(reinterpret_cast<char*> (&d1), sizeof(size_type));
    if (i.fail())
        throw IOException(exc_error_reading_dimension1, SOURCE_INFO);

    i.read(reinterpret_cast<char*> (&d2), sizeof(size_type));
    if (i.fail())
        throw IOException(exc_error_reading_dimension2, SOURCE_INFO);

    i.read(reinterpret_cast<char*> (&r), sizeof(size_type));
    if (i.fail())
        throw IOException(exc_error_reading_dimension3, SOURCE_INFO);

    i.read(reinterpret_cast<char*> (&c), sizeof(size_type));
    if (i.fail())
        throw IOException(exc_error_reading_dimension4, SOURCE_INFO);

    // Read data.
    Array4D<T, Alloc> arr(d1, d2, r, c);
    i.read(reinterpret_cast<char*> (arr.data()), sizeof(T)*arr.size());
    if (i.fail())
        throw IOException(exc_error_reading_data, SOURCE_INFO);
    
    return arr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array4D<T, Alloc>::write(std::ostream& o) const
{
    // Check for errors.
    if (o.fail())
        throw IOException(exc_bad_output_stream, SOURCE_INFO);
    
    // Write number of dim3 and number of dim4.

    o.write(reinterpret_cast<const char*>(&nd1_), sizeof(size_type));
    if (o.fail())
        throw IOException(exc_error_writing_dimension1, SOURCE_INFO);

    o.write(reinterpret_cast<const char*>(&nd2_), sizeof(size_type));
    if (o.fail())
        throw IOException(exc_error_writing_dimension2, SOURCE_INFO);

    o.write(reinterpret_cast<const char*>(&nd3_), sizeof(size_type));
    if (o.fail())
        throw IOException(exc_error_writing_dimension3, SOURCE_INFO);

    o.write(reinterpret_cast<const char*>(&nd4_), sizeof(size_type));
    if (o.fail())
        throw IOException(exc_error_writing_dimension4, SOURCE_INFO);

    // Write data.
    if (n_>0) {
        o.write(reinterpret_cast<const char*> (data()), sizeof(T)*n_);
        if (o.fail())
            throw IOException(exc_error_writing_data, SOURCE_INFO);

    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
std::istream& nct::operator>>(std::istream& i, Array4D<T, Alloc>& arr)
{
    arr = Array4D<T, Alloc>::read(i);
    return i;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
std::ostream& nct::operator<<(std::ostream& o, const Array4D<T, Alloc>& arr)
{
    auto nd1 = arr.dimension1();
    auto nd2 = arr.dimension2();
    auto nd3 = arr.dimension3();
    auto nd4 = arr.dimension4();        

    o << std::endl;
    for (index_t i=0; i<nd1; i++) {
        o << "---"<< std::endl;
        for (index_t j=0; j<nd2; j++) {
            for (index_t k = 0; k<nd3; k++) {
                for (index_t l = 0; l<nd4; l++)
                    o << arr(i, j, k, l) << " ";
                o << std::endl;
            }
            o << std::endl;
        }
    }

    return o;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
