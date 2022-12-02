//=================================================================================================================
/**
 *  @file       Array3D_template.h
 *  @brief      nct::Array3D class template implementation file.
 *  @details    This file contains the implementation of the nct::Array3D class template.
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
nct::Array3D<T, Alloc>::Array3D(const allocator_type& allocator)  noexcept : alloc_{allocator},
n_(0), nd1_(0), nd2_(0), nd3_(0), data_(nullptr)
{
    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array3D<T, Alloc>::Array3D(size_type dim1, size_type dim2, size_type dim3,
    const allocator_type& allocator) : alloc_{allocator}, n_{0}, nd1_{0}, nd2_{0}, nd3_{0}, data_{nullptr}
{
    try {
        resize(dim1, dim2, dim3);
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
nct::Array3D<T, Alloc>::Array3D(size_type dim1, size_type dim2, size_type dim3,
    const_reference val, const allocator_type& allocator) : alloc_{allocator},
    n_{0}, nd1_{0}, nd2_{0}, nd3_{0}, data_{nullptr}
{
    try {
        assign(dim1, dim2, dim3, val);
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
nct::Array3D<T, Alloc>::Array3D(const Array3D<T, Alloc>& other) :
n_{0}, nd1_{0}, nd2_{0}, nd3_{0}, data_{nullptr}
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
nct::Array3D<T, Alloc>::Array3D(const Array3D<T, Alloc>& other,
    const allocator_type& allocator) : alloc_{allocator}, n_{0}, nd1_{0}, nd2_{0}, nd3_{0}, data_{nullptr}
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
nct::Array3D<T, Alloc>::Array3D(Array3D<T, Alloc>&& other)  noexcept
{
    n_ = other.n_;
    nd1_ = other.nd1_;
    nd2_ = other.nd2_;
    nd3_ = other.nd3_;        
    data_ = other.data_;

    other.n_ = 0;
    other.nd1_ = 0;
    other.nd2_ = 0;
    other.nd3_ = 0;    
    other.data_ = nullptr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array3D<T, Alloc>::Array3D(Array3D<T, Alloc>&& other,
    const allocator_type& allocator) : alloc_{allocator}
{
    n_ = other.n_;
    nd1_ = other.nd1_;
    nd2_ = other.nd2_;
    nd3_ = other.nd3_;        
    data_ = other.data_;

    other.n_ = 0;
    other.nd1_ = 0;
    other.nd2_ = 0;
    other.nd3_ = 0;    
    other.data_ = nullptr;
}

//=================================================================================================================
//        DESTRUCTOR
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline nct::Array3D<T, Alloc>::~Array3D() noexcept
{        
    clear();
}

//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array3D<T, Alloc>& nct::Array3D<T, Alloc>::operator=(const Array3D<T, Alloc>& other)
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
nct::Array3D<T, Alloc>& nct::Array3D<T, Alloc>::operator=(Array3D<T, Alloc>&& other) noexcept
{
    if (data_ == other.data_)
        return *this;

    clear();
    n_ = other.n_;
    nd1_ = other.nd1_;
    nd2_ = other.nd2_;
    nd3_ = other.nd3_;
    data_ = other.data_;

    other.n_ = 0;
    other.nd1_ = 0;
    other.nd2_ = 0;
    other.nd3_ = 0;
    other.data_ = nullptr;

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::reference nct::Array3D<T, Alloc>::operator()(
    size_type i, size_type j, size_type k)
{
#ifndef NCT_ARRAY_3D_DISABLE_INDEX_CHECKING
    if (i >= nd1_)
        throw IndexOutOfRangeException("i", SOURCE_INFO);
    if (j >= nd2_)
        throw IndexOutOfRangeException("j", SOURCE_INFO);
    if (k >= nd3_)
        throw IndexOutOfRangeException("k", SOURCE_INFO);
#endif
    return data_[nd3_ * (nd2_ * i + j) + k];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reference nct::Array3D<T, Alloc>::operator()(
    size_type i, size_type j, size_type k) const
{
#ifndef NCT_ARRAY_3D_DISABLE_INDEX_CHECKING
    if (i >= nd1_)
        throw IndexOutOfRangeException("i", SOURCE_INFO);
    if (j >= nd2_)
        throw IndexOutOfRangeException("j", SOURCE_INFO);
    if (k >= nd3_)
        throw IndexOutOfRangeException("k", SOURCE_INFO);
#endif
    return data_[nd3_ * (nd2_ * i + j) + k];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::reference nct::Array3D<T, Alloc>::operator[](size_type i)
{
#ifndef NCT_ARRAY_3D_DISABLE_INDEX_CHECKING
    if (i >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
#endif
    return data_[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reference nct::Array3D<T, Alloc>::operator[](size_type i) const
{
#ifndef NCT_ARRAY_3D_DISABLE_INDEX_CHECKING
    if (i >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
#endif
    return data_[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::reference nct::Array3D<T, Alloc>::operator()(size_type i)
{
#ifndef NCT_ARRAY_3D_DISABLE_INDEX_CHECKING
    if (i >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
#endif
    return data_[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reference nct::Array3D<T, Alloc>::operator()(size_type i) const
{
#ifndef NCT_ARRAY_3D_DISABLE_INDEX_CHECKING
    if (i >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
#endif
    return data_[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
bool nct::Array3D<T, Alloc>::operator==(const Array3D<T, Alloc>& right) const
{
    if (data_ == right.data_)
        return true;

    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) || (right.nd3_ != nd3_))
        return false;

    for (size_type i = 0; i < n_; i++) {
        if (data_[i] != right.data_[i])
            return false;
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
bool nct::Array3D<T, Alloc>::operator!=(const Array3D<T, Alloc>& right) const
{
    return !(*this == right);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::operator&(const Array3D<T, Alloc> & right) const
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) || (right.nd3_ != nd3_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array3D<T, Alloc> res(nd1_, nd2_, nd3_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = (data_[i] & right.data_[i]);

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::integral T, typename Alloc>
nct::Array3D<T, Alloc> nct::operator&(
    Array3D<T, Alloc> && left, const Array3D<T, Alloc> & right)
{
    if ((left.dimension1() != right.dimension1()) ||
        (left.dimension2() != right.dimension2()) ||
        (left.dimension3() != right.dimension3()))
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array3D<T, Alloc> resArr;
    std::swap(resArr, left);

    for (typename Array3D<T, Alloc>::size_type i = 0; i < resArr.size(); i++)
        resArr[i] = (resArr[i] & right[i]);

    return resArr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
const nct::Array3D<T, Alloc> & nct::Array3D<T, Alloc>::operator&=(const Array3D<T, Alloc> & right)
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) || (right.nd3_ != nd3_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] &= right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::operator|(const Array3D<T, Alloc> & right) const
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) || (right.nd3_ != nd3_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array3D<T, Alloc> res(nd1_, nd2_, nd3_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = (data_[i] | right.data_[i]);

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::integral T, typename Alloc>
nct::Array3D<T, Alloc> nct::operator|(
    Array3D<T, Alloc> && left, const Array3D<T, Alloc> & right)
{
    if ((left.dimension1() != right.dimension1()) ||
        (left.dimension2() != right.dimension2()) ||
        (left.dimension3() != right.dimension3()))
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array3D<T, Alloc> resArr;
    std::swap(resArr, left);

    for (typename Array3D<T, Alloc>::size_type i = 0; i < resArr.size(); i++)
        resArr[i] = (resArr[i] | right[i]);

    return resArr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
const nct::Array3D<T, Alloc> & nct::Array3D<T, Alloc>::operator|=(
    const Array3D<T, Alloc> & right)
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) || (right.nd3_ != nd3_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] |= right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::operator^(const Array3D<T, Alloc>& right) const
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) || (right.nd3_ != nd3_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array3D<T, Alloc> res(nd1_, nd2_, nd3_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = (data_[i] ^ right.data_[i]);

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::integral T, typename Alloc>
nct::Array3D<T, Alloc> nct::operator^(
    Array3D<T, Alloc> && left, const Array3D<T, Alloc> & right)
{
    if ((left.dimension1() != right.dimension1()) ||
        (left.dimension2() != right.dimension2()) ||
        (left.dimension3() != right.dimension3()))
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array3D<T, Alloc> resArr;
    std::swap(resArr, left);

    for (typename Array3D<T, Alloc>::size_type i = 0; i < resArr.size(); i++)
        resArr[i] = (resArr[i] ^ right[i]);

    return resArr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
const nct::Array3D<T, Alloc> & nct::Array3D<T, Alloc>::operator^=(const Array3D<T, Alloc> & right)
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) || (right.nd3_ != nd3_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] ^= right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::operator+() const
{
    Array3D<T, Alloc> res(nd1_, nd2_, nd3_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Addable<T>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::operator+(const Array3D<T, Alloc> & right) const
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) || (right.nd3_ != nd3_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array3D<T, Alloc> res(nd1_, nd2_, nd3_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i] + right.data_[i];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Addable T, typename Alloc>
nct::Array3D<T, Alloc> nct::operator+(
    Array3D<T, Alloc> && left, const Array3D<T, Alloc> & right)
{
    if ((left.dimension1() != right.dimension1()) ||
        (left.dimension2() != right.dimension2()) ||
        (left.dimension3() != right.dimension3()))
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array3D<T, Alloc> resArr;
    std::swap(resArr, left);

    for (typename Array3D<T, Alloc>::size_type i = 0; i < resArr.size(); i++)
        resArr[i] += right[i];

    return resArr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Addable<T>
const nct::Array3D<T, Alloc> & nct::Array3D<T, Alloc>::operator+=(
    const Array3D<T, Alloc> & right)
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) || (right.nd3_ != nd3_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] += right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::SignedNumeric<T>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::operator-() const
{
    Array3D<T, Alloc> res(nd1_, nd2_, nd3_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = -data_[i];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Substractable<T>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::operator-(const Array3D<T, Alloc> & right) const
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) || (right.nd3_ != nd3_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array3D<T, Alloc> res(nd1_, nd2_, nd3_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i] - right.data_[i];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Substractable T, typename Alloc>
nct::Array3D<T, Alloc> nct::operator-(
    Array3D<T, Alloc> && left, const Array3D<T, Alloc> & right)
{
    if ((left.dimension1() != right.dimension1()) ||
        (left.dimension2() != right.dimension2()) ||
        (left.dimension3() != right.dimension3()))
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array3D<T, Alloc> resArr;
    std::swap(resArr, left);

    for (typename Array3D<T, Alloc>::size_type i = 0; i < resArr.size(); i++)
        resArr[i] -= right[i];

    return resArr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Substractable<T>
const nct::Array3D<T, Alloc> & nct::Array3D<T, Alloc>::operator-=(
    const Array3D<T, Alloc> & right)
{
    if ((right.nd1_ != nd1_) || (right.nd2_ != nd2_) || (right.nd3_ != nd3_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] -= right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::operator*(const_reference right) const
{
    Array3D<T, Alloc> res(nd1_, nd2_, nd3_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i] * right;

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T, typename Alloc>
nct::Array3D<T, Alloc> nct::operator*(
    const T & left, const Array3D<T, Alloc> & right)
{
    Array3D<T, Alloc> res(right.dimension1(), right.dimension2(), right.dimension3());

    for (typename Array3D<T, Alloc>::size_type i = 0; i < right.size(); i++)
        res[i] = right[i] * left;

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
const nct::Array3D<T, Alloc>& nct::Array3D<T, Alloc>::operator*=(const_reference right)
{
    for (size_type i = 0; i < n_; i++)
        data_[i] *= right;

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::operator/(const_reference right) const
{
    Array3D<T, Alloc> res(nd1_, nd2_, nd3_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i] / right;

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
const nct::Array3D<T, Alloc>& nct::Array3D<T, Alloc>::operator/=(const_reference right)
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
void nct::Array3D<T, Alloc>::clear() noexcept
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
    data_ = nullptr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array3D<T, Alloc>::assign(size_type dim1, size_type dim2, size_type dim3, 
    const_reference val)
{    
    if ( n_ == (dim1*dim2*dim3) ) {
        nd1_ = dim1;
        nd2_ = dim2;
        nd3_ = dim3;    
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
            n_ = nd3_*nd2_*nd1_;
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
inline void nct::Array3D<T, Alloc>::resize(size_type dim1, size_type dim2, size_type dim3)
{    
    if ((nd3_ == dim3) && (nd2_ == dim2) && (nd1_ == dim1))
        return;

    // Previous array size.
    auto pnd = nd1_;
    auto pnr = nd2_;
    auto pnc = nd3_;
    auto pn = n_;

    // New array size.
    nd3_ = dim3;
    nd2_ = dim2;
    nd1_ = dim1;
    n_ = nd3_ * nd2_ * nd1_;

    // Block segment that will be preserved.
    auto dMin = pnd < nd1_ ? (pnd) : (nd1_);
    auto rMin = pnr < nd2_ ? (pnr) : (nd2_);
    auto cMin = pnc < nd3_ ? (pnc) : (nd3_);

    // Allocate memory pnd copy previous data.
    if (n_ > 0) {
        try {
            // Allocate new array.
            auto dd = data_;
            data_ = alloc_.allocate(n_);

            // Initialize data.
            for (size_type i = 0; i < nd1_; i++) {
                for (size_type j = 0; j < nd2_; j++) {
                    for (size_type k = 0; k < nd3_; k++) {
                        if ((i < dMin) && (j < rMin) && (k < cMin))
                            allocator_traits::construct(alloc_, data_ + (nd3_ * (nd2_ * i + j) + k), 
                                std::move(dd[pnc * (pnr * i + j) + k]));
                        else
                            allocator_traits::construct(alloc_, data_ + (nd3_ * (nd2_ * i + j) + k), T());
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
void nct::Array3D<T, Alloc>::resize(size_type dim1, size_type dim2, size_type dim3, const_reference val)
{    
    if ( (nd3_ == dim3) && (nd2_ == dim2) && (nd1_ == dim1) )
        return;

    // Previous array size.
    auto pnd = nd1_;
    auto pnr = nd2_;
    auto pnc = nd3_;    
    auto pn = n_;

    // New array size.
    nd3_ = dim3;
    nd2_ = dim2;
    nd1_ = dim1;
    n_ = nd3_*nd2_*nd1_;
    
    // Block segment that will be preserved.
    auto dMin = pnd < nd1_? (pnd) : (nd1_);
    auto rMin = pnr < nd2_? (pnr) : (nd2_);
    auto cMin = pnc < nd3_? (pnc) : (nd3_);

    // Allocate memory pnd copy previous data.
    if (n_>0) {
        try {    
            // Allocate new array.
            auto dd = data_;        
            data_ = alloc_.allocate(n_);

            // Initialize data.
            for (size_type i=0; i<nd1_; i++) {
                for (size_type j=0; j<nd2_; j++) {
                    for (size_type k=0; k<nd3_; k++) {
                        if ((i < dMin) && (j < rMin) && (k < cMin))
                            allocator_traits::construct(alloc_, data_ +(nd3_*(nd2_*i + j) + k), 
                                std::move(dd[pnc*(pnr*i + j) + k]));
                        else
                            allocator_traits::construct(alloc_, data_ + (nd3_*(nd2_*i + j) + k), val);
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
inline typename nct::Array3D<T, Alloc>::allocator_type nct::Array3D<T, Alloc>::get_allocator() const
{
    return allocator_type(alloc_);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline void nct::Array3D<T, Alloc>::fill(const_reference val)
{
    for (size_type i=0; i<n_; i++)
        data_[i] = val;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array3D<T, Alloc>::reshape(size_type dim1, size_type dim2, size_type dim3)
{
    if (n_ != dim1*dim2*dim3)
        throw ArgumentException("dim1, dim2, dim3.", exc_bad_reshape_dimensions, SOURCE_INFO);
    nd1_ = dim1;
    nd2_ = dim2;
    nd3_ = dim3;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array3D<T, Alloc>::copy(const Array3D<T, Alloc>& other)
{
    if ( (data_ == other.data_) && (nd3_ == other.nd3_) && (nd2_ == other.nd2_) && (nd1_ == other.nd1_))
        return;

    if (other.n_ == 0) {
        // Release object.
        clear();
        nd1_ = other.nd1_;
        nd2_ = other.nd2_;
        nd3_ = other.nd3_;
    }
    else if (n_ == other.n_) {
        // Copy new contents.
        nd1_ = other.nd1_;
        nd2_ = other.nd2_;
        nd3_ = other.nd3_;
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
bool nct::Array3D<T, Alloc>::empty() const noexcept
{
    return (n_ == 0);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::size_type
nct::Array3D<T, Alloc>::dimension1() const noexcept
{
    return nd1_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::size_type
nct::Array3D<T, Alloc>::dimension2() const noexcept
{
    return nd2_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::size_type
nct::Array3D<T, Alloc>::dimension3() const noexcept
{
    return nd3_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::size_type
nct::Array3D<T, Alloc>::size() const noexcept
{
    return n_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::pointer nct::Array3D<T, Alloc>::data() noexcept
{
    return data_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::const_pointer
nct::Array3D<T, Alloc>::data() const noexcept
{
    return data_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::pointer
nct::Array3D<T, Alloc>::data(size_type index)
{
    if (index >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
    return &data_[index];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::const_pointer
nct::Array3D<T, Alloc>::data(size_type index) const
{
    if (index >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
    return &data_[index];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::pointer nct::Array3D<T, Alloc>::data(
    size_type dim1, size_type dim2, size_type dim3)
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);
    return &data_[nd3_*(nd2_*dim1 + dim2) + dim3];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::const_pointer 
nct::Array3D<T, Alloc>::data(size_type dim1, size_type dim2, size_type dim3) const
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);
    return &data_[nd3_*(nd2_*dim1 + dim2) + dim3];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::reference
nct::Array3D<T, Alloc>::at(size_type index) 
{
    if (index >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
    return data_[index];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::const_reference
nct::Array3D<T, Alloc>::at(size_type index) const
{
    if (index >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
    return data_[index];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::const_reference nct::Array3D<T, Alloc>::at(
    size_type dim1, size_type dim2, size_type dim3) const
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);
    return data_[nd3_*(nd2_*dim1 + dim2) + dim3];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::reference nct::Array3D<T, Alloc>::at(
    size_type dim1, size_type dim2, size_type dim3)
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);
    return data_[nd3_*(nd2_*dim1 + dim2) + dim3];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::size_type nct::Array3D<T, Alloc>::offset(
    size_type dim1) const noexcept
{
    return nd3_*nd2_*dim1;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::size_type nct::Array3D<T, Alloc>::offset(
    size_type dim1, size_type dim2) const noexcept
{
    return nd3_*(nd2_*dim1 + dim2);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::size_type nct::Array3D<T, Alloc>::offset(
    size_type dim1, size_type dim2, size_type dim3) const noexcept
{
    return nd3_*(nd2_*dim1 + dim2) + dim3;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::reference nct::Array3D<T, Alloc>::front()
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);
    return data_[0];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::const_reference nct::Array3D<T, Alloc>::front() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);
    return data_[0];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::reference nct::Array3D<T, Alloc>::back()
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);
    return data_[n_ - 1];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
inline typename nct::Array3D<T, Alloc>::const_reference 
nct::Array3D<T, Alloc>::back() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);
    return data_[n_ - 1];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename Container>
Container nct::Array3D<T, Alloc>::find(
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
nct::Array3D<U, AllocU> nct::Array3D<T, Alloc>::toArray() const
{
    Array3D<U, AllocU> outputArray(nd1_, nd2_, nd3_);        
    for (size_type k = 0; k<n_; k++)
        outputArray[k] = static_cast<U>(data_[k]);
    return outputArray;    
}

//=================================================================================================================
//        DATA INSERTIONS AND DELETIONS 
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array3D<T, Alloc>::insertDim1(size_type dim1, const Array2D<T, Alloc>& data)
{
    if (dim1 > nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);

    if ((data.rows() != nd2_) || (data.columns() != nd3_))
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    // Move old data and resize array.
    nct::Array3D<T, Alloc> old(std::move(*this));
    resize(old.nd1_ + 1, old.nd2_, old.nd3_);

    // Fill array.
    for (size_type i = 0; i<dim1; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j, k)]);

    for (size_type j = 0; j<nd2_; j++)
        for (size_type k = 0; k<nd3_; k++)
            data_[offset(dim1, j, k)] = data(j, k);

    for (size_type i = (dim1 + 1); i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i - 1, j, k)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array3D<T, Alloc>::insertDim1(size_type dim1, const Array3D<T, Alloc>& data)
{
    if (dim1 > nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);

    if ((data.nd2_ != nd2_) || (data.nd3_ != nd3_))
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    // Move old data and resize array.
    auto nnd1 = data.dimension1();
    nct::Array3D<T, Alloc> old(std::move(*this));
    resize(old.nd1_ + nnd1, old.nd2_, old.nd3_);
    
    // Fill array.
    for (size_type i = 0; i<dim1; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j, k)]);
    
    for (size_type i = dim1; i<(dim1 + nnd1); i++)
        for (size_type j=0; j<nd2_; j++)
            for (size_type k=0; k<nd3_; k++)        
                data_[offset(i, j, k)] = data.data_[data.offset(i - dim1, j, k)];
    
    for (size_type i = (dim1 + nnd1); i<nd1_; i++)
        for (size_type j=0; j<nd2_; j++)
            for (size_type k=0; k<nd3_; k++)        
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i - nnd1, j, k)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array3D<T, Alloc>::eraseDim1(size_type dim1)
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);

    // Move old data and resize array.
    nct::Array3D<T, Alloc> old(std::move(*this));
    resize(old.nd1_ - 1, old.nd2_, old.nd3_);
    
    // Fill array.
    for (size_type i = 0; i<dim1; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j, k)]);
    
    for (size_type i = dim1; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i + 1, j, k)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array3D<T, Alloc>::eraseDim1(size_type first, size_type last)
{
    if (first >= nd1_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nd1_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    // Move old data and resize array.
    auto nnd1 = last - first + 1;
    nct::Array3D<T, Alloc> old(std::move(*this));
    resize(old.nd1_ - nnd1, old.nd2_, old.nd3_);
    
    // Fill array.
    for (size_type i = 0; i<first; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j, k)]);
        
    for (size_type i = first; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i + nnd1, j, k)]);

}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
void nct::Array3D<T, Alloc>::eraseDim1(IndexIt first, IndexIt last)
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    size_type nnd1 = 0;
    for (auto ind1 = first; ind1 != last; ++ind1) {
        if (static_cast<size_type>(*ind1) >= nd1_)
            throw ArgumentException("first, last", exc_indices_out_of_range, SOURCE_INFO);

        auto ind2 = first;
        for (; ind2 != ind1; ++ind2) {
            if (static_cast<size_type>(*ind1) == static_cast<size_type>(*ind2))
                break;
        }        
        nnd1 += (ind2 == ind1);
    }

    // Move old data and resize array.
    nct::Array3D<T, Alloc> old(std::move(*this));
    resize(old.nd1_ - nnd1, old.nd2_, old.nd3_);
    
    // Fill array.
    size_type c = 0;
    
    for (size_type i = 0; i < old.nd1_; i++) {
        auto ind = first;
        for (; ind != last; ++ind) {
            if (i == static_cast<size_type>(*ind))
                break;
        }

        if (ind == last) {
            for (size_type j = 0; j < nd2_; j++)
                for (size_type k = 0; k < nd3_; k++)
                    data_[offset(c, j, k)] = std::move(old.data_[old.offset(i, j, k)]);
            c++;
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array3D<T, Alloc>::insertDim2(size_type dim2, const Array2D<T, Alloc>& data)
{
    if (dim2 > nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);

    if ((data.rows() != nd1_) || (data.columns() != nd3_))
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    // Move old data and resize array.
    nct::Array3D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_ + 1, old.nd3_);

    // Fill array.
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<dim2; j++)
            for (size_type k = 0; k<nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j, k)]);

    for (size_type i = 0; i<nd1_; i++)
        for (size_type k = 0; k<nd3_; k++)
            data_[offset(i, dim2, k)] = data(i, k);

    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = (dim2 + 1); j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j - 1, k)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array3D<T, Alloc>::insertDim2(size_type dim2, const Array3D<T, Alloc>& data)
{
    if (dim2 > nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);

    if ((data.nd1_ != nd1_) || (data.nd3_ != nd3_))
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    // Move old data and resize array.
    auto nnd2 = data.dimension2();
    nct::Array3D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_ + nnd2, old.nd3_);
    
    // Fill array.
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<dim2; j++)
            for (size_type k = 0; k<nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j, k)]);
    
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j=dim2; j<(dim2+nnd2); j++)
            for (size_type k=0; k<nd3_; k++)        
                data_[offset(i, j, k)] = data.data_[data.offset(i, j - dim2, + k)];
    
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j=(dim2+nnd2); j<nd2_; j++)
            for (size_type k=0; k<nd3_; k++)        
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j - nnd2, k)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array3D<T, Alloc>::eraseDim2(size_type dim2)
{
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);

    // Move old data and resize array.
    nct::Array3D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_ - 1, old.nd3_);
    
    // Fill array.
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<dim2; j++)
            for (size_type k = 0; k<nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j, k)]);
    
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = dim2; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j + 1, k)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array3D<T, Alloc>::eraseDim2(size_type first, size_type last)
{
    if (first >= nd2_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nd2_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    // Move old data and resize array.
    auto nnd2 = last - first + 1;
    nct::Array3D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_ - nnd2, old.nd3_);
    
    // Fill array.
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<first; j++)
            for (size_type k = 0; k<nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j, k)]);
        
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = first; j<nd2_; j++)
            for (size_type k = 0; k<nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j + nnd2, k)]);

}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
void nct::Array3D<T, Alloc>::eraseDim2(IndexIt first, IndexIt last)
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    size_type nnd2 = 0;
    for (auto ind1 = first; ind1 != last; ++ind1) {
        if (static_cast<size_type>(*ind1) >= nd2_)
            throw ArgumentException("first, last", exc_indices_out_of_range, SOURCE_INFO);

        auto ind2 = first;
        for (; ind2 != ind1; ++ind2) {
            if (static_cast<size_type>(*ind1) == static_cast<size_type>(*ind2))
                break;
        }        
        nnd2 += (ind2 == ind1);
    }

    // Move old data and resize array.
    nct::Array3D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_ - nnd2, old.nd3_);
    
    // Fill array.
    size_type c = 0;
    
    for (size_type j = 0; j < old.nd2_; j++) {
        auto ind = first;
        for (; ind != last; ++ind) {
            if (j == static_cast<size_type>(*ind))
                break;
        }

        if (ind == last) {
            for (size_type i = 0; i < nd1_; i++)
                for (size_type k = 0; k < nd3_; k++)
                    data_[offset(i, c, k)] = std::move(old.data_[old.offset(i, j, k)]);
            c++;
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array3D<T, Alloc>::insertDim3(size_type dim3, const Array2D<T, Alloc>& data)
{
    if (dim3 > nd3_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);

    if ((data.rows() != nd1_) || (data.columns() != nd2_))
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    // Move old data and resize array.
    nct::Array3D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_, old.nd3_ + 1);

    // Fill array.
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<dim3; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j, k)]);

    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            data_[offset(i, j, dim3)] = data(i, j);

    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = (dim3 + 1); k<nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j, k - 1)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array3D<T, Alloc>::insertDim3(size_type dim3, const Array3D<T, Alloc>& data)
{
    if (dim3 > nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);

    if ((data.nd1_ != nd1_) || (data.nd2_ != nd2_))
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    // Move old data and resize array.
    auto nnd3 = data.dimension3();
    nct::Array3D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_, old.nd3_ + nnd3);
    
    // Fill array.
    for (size_type i = 0; i < nd1_; i++) {
        for (size_type j = 0; j < nd2_; j++) {
            for (size_type k = 0; k < dim3; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j, k)]);

            for (size_type k = dim3; k < (dim3 + nnd3); k++)
                data_[offset(i, j, k)] = data.data_[data.offset(i, j, k - dim3)];

            for (size_type k = (dim3 + nnd3); k < nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j, k - nnd3)]);
        }
    }
}        

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array3D<T, Alloc>::eraseDim3(size_type dim3)
{
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);

    // Move old data and resize array.
    nct::Array3D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_, old.nd3_ - 1);

    // Fill array.
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = 0; k<dim3; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j, k)]);

    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            for (size_type k = dim3; k<nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j, k + 1)]);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
void nct::Array3D<T, Alloc>::eraseDim3(size_type first, size_type last)
{
    if (first >= nd3_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nd3_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    // Move old data and resize array.
    auto nnd3 = last - first + 1;
    nct::Array3D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_, old.nd3_ - nnd3);
    
    // Fill array.
    for (size_type i = 0; i < nd1_; i++) {
        for (size_type j = 0; j < nd2_; j++) {
            for (size_type k = 0; k < first; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j, k)]);

            for (size_type k = first; k < nd3_; k++)
                data_[offset(i, j, k)] = std::move(old.data_[old.offset(i, j, k + nnd3)]);
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
void nct::Array3D<T, Alloc>::eraseDim3(IndexIt first, IndexIt last)
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    size_type nnd3 = 0;
    for (auto ind1 = first; ind1 != last; ++ind1) {
        if (static_cast<size_type>(*ind1) >= nd3_)
            throw ArgumentException("first, last", exc_indices_out_of_range, SOURCE_INFO);

        auto ind2 = first;
        for (; ind2 != ind1; ++ind2) {
            if (static_cast<size_type>(*ind1) == static_cast<size_type>(*ind2))
                break;
        }
        
        nnd3 += (ind2 == ind1);
    }

    // Move old data and resize array.
    nct::Array3D<T, Alloc> old(std::move(*this));
    resize(old.nd1_, old.nd2_, old.nd3_ - nnd3);
    
    // Fill array.
    size_type c = 0;
    for (size_type k=0; k<old.nd3_; k++) {
        auto ind = first;
        for (; ind != last; ++ind) {
            if (k == static_cast<size_type>(*ind))
                break;
        }

        if (ind == last) {
            for (size_type i = 0; i < nd1_; i++)
                for (size_type j=0; j<nd2_; j++)
                    data_[offset(i, j, c)] = std::move(old.data_[old.offset(i, j, k)]);
            c++;
        }        
    }
}

//=================================================================================================================
//        DATA SELECTION
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array3D<T, Alloc>::subArray(size_type dim1) const
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);

    size_type nItems = nd2_*nd3_;
    Array2D<T, Alloc> newArray(nd2_, nd3_);
    size_type start = nd3_*(nd2_*dim1);
    for (size_type i = 0; i<nItems; i++)
        newArray[i] = data_[i + start];

    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array<T, Alloc> nct::Array3D<T, Alloc>::elementsOfDim1(
    size_type dim2, size_type dim3) const
{
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);

    size_type nItems = nd1_;
    Array<T, Alloc> newArray(nItems);    
    size_type inc = nd2_*nd3_;
    size_type start = nd3_*(dim2) + dim3;
    for (size_type i=0; i<nItems; i++)
        newArray[i] = data_[i*inc+start]; 

    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array<T, Alloc> nct::Array3D<T, Alloc>::elementsOfDim2(
    size_type dim1, size_type dim3) const
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);

    size_type nItems = nd2_;
    Array<T, Alloc> newArray(nItems);    
    size_type inc = nd3_;
    size_type start = nd3_*(nd2_*dim1) + dim3;
    for (size_type i=0; i<nItems; i++)
        newArray[i] = data_[i*inc+start]; 

    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array<T, Alloc> nct::Array3D<T, Alloc>::elementsOfDim3(
    size_type dim1, size_type dim2) const
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);

    size_type nItems = nd3_;
    Array<T, Alloc> newArray(nItems);
    size_type start = nd3_*(nd2_*dim1 + dim2);
    for (size_type i=0; i<nItems; i++)
        newArray[i] = data_[i+start]; 

    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array<T, Alloc> nct::Array3D<T, Alloc>::selectRange(
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
inline nct::Array<T, Alloc> nct::Array3D<T, Alloc>::selectRange(
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
nct::Array<T, Alloc> nct::Array3D<T, Alloc>::selectData(
    IndexIt first, IndexIt last) const
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
nct::Array<T, Alloc> nct::Array3D<T, Alloc>::selectData(
    const Array<size_type, AllocU>& indices) const
{
    return selectData(std::begin(indices), std::end(indices));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::selectSubArray(
    size_type firstDim1, size_type lastDim1,
    size_type firstDim2, size_type lastDim2, 
    size_type firstDim3, size_type lastDim3) const
{
    if (lastDim1<firstDim1)
        throw RangeException("firstDim1, lastDim1", SOURCE_INFO);

    if (lastDim2<firstDim2)
        throw RangeException("firstDim2, lastDim2", SOURCE_INFO);

    if (lastDim3<firstDim3)
        throw RangeException("firstDim3, lastDim3", SOURCE_INFO);

    if (lastDim1 >= nd1_)
        throw IndexOutOfRangeException("lastDim1", SOURCE_INFO);

    if (lastDim2 >= nd2_)
        throw IndexOutOfRangeException("lastDim2", SOURCE_INFO);
    
    if (lastDim3 >= nd3_)
        throw IndexOutOfRangeException("lastDim3", SOURCE_INFO);

    auto nNewDepth = lastDim1-firstDim1+1;
    auto nNewRows = lastDim2-firstDim2+1;
    auto nNewCols = lastDim3-firstDim3+1;

    Array3D<T, Alloc> selData(nNewDepth, nNewRows, nNewCols);
    for (size_type i=0; i<nNewDepth; i++)
        for (size_type j=0; j<nNewRows; j++)
            for (size_type k=0; k<nNewCols; k++)
                selData.data_[selData.offset(i, j, k)] =
                data_[offset(i+firstDim1, j+firstDim2, k+firstDim3)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
template<std::random_access_iterator IndexIt1, std::random_access_iterator IndexIt2,
    std::random_access_iterator IndexIt3>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::selectIndices(
    IndexIt1 firstDim1, IndexIt1 lastDim1,
    IndexIt2 firstDim2, IndexIt2 lastDim2,
    IndexIt3 firstDim3, IndexIt3 lastDim3) const
{
    if (lastDim1 < firstDim1)
        throw RangeException("firstDim1, lastDim1", SOURCE_INFO);

    if (lastDim2 < firstDim2)
        throw RangeException("firstDim2, lastDim2", SOURCE_INFO);

    if (lastDim3 < firstDim3)
        throw RangeException("firstDim3, lastDim3", SOURCE_INFO);

    auto nnd1 = lastDim1 - firstDim1;
    auto nnd2 = lastDim2 - firstDim2;
    auto nnd3 = lastDim3 - firstDim3;

    for (auto dp = firstDim1; dp!=lastDim1; ++dp) {
        if (static_cast<size_type>(*dp) >= nd1_)
            throw IndexOutOfRangeException("firstDim1, lastDim1", SOURCE_INFO);
    }

    for (auto r = firstDim2; r!=lastDim2; ++r) {
        if (static_cast<size_type>(*r) >= nd2_)
            throw IndexOutOfRangeException("firstDim2, lastDim2", SOURCE_INFO);
    }

    for (auto c = firstDim3; c!=lastDim3; ++c) {
        if (static_cast<size_type>(*c) >= nd3_)
            throw IndexOutOfRangeException("firstDim3, lastDim3", SOURCE_INFO);
    }
        
    Array3D<T, Alloc> selData(nnd1, nnd2, nnd3);
    size_type i = 0;
    for (auto dp = firstDim1; dp!=lastDim1; ++dp, ++i) {
        size_type j = 0;
        for (auto r = firstDim2; r!=lastDim2; ++r, ++j) {
            size_type k = 0;
            for (auto c = firstDim3; c!=lastDim3; ++c, ++k)
                selData.data_[selData.offset(i, j, k)] = data_[offset(*dp, *r, *c)];
        }
    }

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::selectIndices(
    const Array<size_type, AllocU>& dim1,
    const Array<size_type, AllocU>& dim2,
    const Array<size_type, AllocU>& dim3) const
{
    return selectIndices(std::begin(dim1), std::end(dim1),
        std::begin(dim2), std::end(dim2),
        std::begin(dim3), std::end(dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::selectDim1(size_type dim1) const
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);

    Array3D<T, Alloc> selData(1, nd2_, nd3_);
    for (size_type j=0; j<nd2_; j++)
        for (size_type k=0; k<nd3_; k++)
            selData.data_[selData.offset(0, j, k)] = data_[offset(dim1, j, k)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::selectDim1(
    size_type first, size_type last) const
{
    if (first >= nd1_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nd1_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    auto nnd1 = last - first + 1;
    Array3D<T, Alloc> selData(nnd1, nd2_, nd3_);
    for (size_type i=0; i<nnd1; i++)
        for (size_type j=0; j<nd2_; j++)
            for (size_type k=0; k<nd3_; k++)
                selData.data_[selData.offset(i, j, k)] = data_[offset(i + first, j, k)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::selectDim1(
    IndexIt first, IndexIt last) const
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    auto nnd1 = last - first;
    for (auto dp = first; dp != last; ++dp) {
        if (static_cast<size_type>(*dp) >= nd1_)
            throw IndexOutOfRangeException("first, last", SOURCE_INFO);
    }

    Array3D<T, Alloc> selData(nnd1, nd2_, nd3_);
    size_type i = 0;
    for (auto dp = first; dp != last; ++dp, ++i)
        for (size_type j=0; j<nd2_; j++)
            for (size_type k=0; k<nd3_; k++)
                selData.data_[selData.offset(i, j, k)] = data_[offset(*dp, j, k)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::selectDim1(
    const Array<size_type, AllocU>& dim1) const
{
    return selectDim1(std::begin(dim1), std::end(dim1));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::selectDim2(size_type dim2) const
{
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);

    Array3D<T, Alloc> selData(nd1_, 1, nd3_);
    for (size_type i=0; i<nd1_; i++)
            for (size_type k=0; k<nd3_; k++)
                selData.data_[selData.offset(i, 0, k)] = data_[offset(i, dim2, k)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::selectDim2(
    size_type first, size_type last) const
{
    if (first >= nd2_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nd2_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    auto nnd2 = last - first + 1;
    Array3D<T, Alloc> selData(nd1_, nnd2, nd3_);
    for (size_type i=0; i<nd1_; i++)
        for (size_type j=0; j<nnd2; j++)
            for (size_type k=0; k<nd3_; k++)
                selData.data_[selData.offset(i, j, k)] = data_[offset(i, j + first, k)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::selectDim2(
    IndexIt first, IndexIt last) const
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    auto nnd2 = last - first;
    for (auto r = first; r != last; ++r) {
        if (static_cast<size_type>(*r) >= nd2_)
            throw IndexOutOfRangeException("first, last", SOURCE_INFO);
    }

    Array3D<T, Alloc> selData(nd1_, nnd2, nd3_);
    for (size_type i=0; i<nd1_; i++) {
        size_type j = 0;
        for (auto r = first; r != last; ++r, ++j) {
            for (size_type k=0; k<nd3_; k++)
                selData.data_[selData.offset(i, j, k)] = data_[offset(i, *r, k)];
        }
    }

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::selectDim2(
    const Array<size_type, AllocU>& dim2) const
{
    return selectDim2(std::begin(dim2), std::end(dim2));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::selectDim3(size_type dim3) const
{
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);

    Array3D<T, Alloc> selData(nd1_, nd2_, 1);
    for (size_type i=0; i<nd1_; i++)
        for (size_type j=0; j<nd2_; j++)
            selData.data_[selData.offset(i, j, 0)] = data_[offset(i, j, dim3)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::selectDim3(
    size_type first, size_type last) const
{
    if (first >= nd3_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nd3_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    auto nnd3 = last - first + 1;
    Array3D<T, Alloc> selData(nd1_, nd2_, nnd3);
    for (size_type i=0; i<nd1_; i++)
        for (size_type j=0; j<nd2_; j++)
            for (size_type k=0; k<nnd3; k++)
                selData.data_[selData.offset(i, j, k)] = data_[offset(i, j, k + first)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::selectDim3(
    IndexIt first, IndexIt last) const
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    auto nnd3 = last - first;
    for (auto c = first; c!=last; ++c) {
        if (static_cast<size_type>(*c) >= nd3_)
            throw IndexOutOfRangeException("first, last", SOURCE_INFO);
    }
        
    Array3D<T, Alloc> selData(nd1_, nd2_, nnd3);
    for (size_type i=0; i<nd1_; i++) {
        for (size_type j=0; j<nd2_; j++) {
            size_type k = 0;
            for (auto c = first; c!=last; ++c, ++k)
                selData.data_[selData.offset(i, j, k)] = data_[offset(i, j, *c)];
        }
    }

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::selectDim3(
    const Array<size_type, AllocU>& dim3) const
{
    return selectDim3(std::begin(dim3), std::end(dim3));
}

//=================================================================================================================
//        CIRCULAR SHIFTS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::circularDim1Shift(
    difference_type i0) const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array3D<T, Alloc> res(nd1_, nd2_, nd3_);
    for (difference_type i = 0; i < static_cast<difference_type>(nd1_); i++) {
        difference_type off = i + i0;
        while (off < 0)
            off += nd1_;
        off %= nd1_;

        for (difference_type j = 0; j < static_cast<difference_type>(nd2_); j++)
            for (difference_type k = 0; k < static_cast<difference_type>(nd3_); k++)
                res.data_[res.offset(i, j, k)] = data_[offset(off, j, k)];
    }

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::circularDim2Shift(
    difference_type j0) const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array3D<T, Alloc> res(nd1_, nd2_, nd3_);
    for (difference_type j = 0; j < static_cast<difference_type>(nd2_); j++) {
        difference_type off = j + j0;
        while (off < 0)
            off += nd2_;
        off %= nd2_;

        for (difference_type i = 0; i < static_cast<difference_type>(nd1_); i++)
            for (difference_type k = 0; k < static_cast<difference_type>(nd3_); k++)
                res.data_[res.offset(i, j, k)] = data_[offset(i, off, k)];
    }

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::circularDim3Shift(
    difference_type k0) const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array3D<T, Alloc> res(nd1_, nd2_, nd3_);
    for (difference_type k=0; k<static_cast<difference_type>(nd3_); k++) {
        difference_type off = k+k0;
        while (off<0)
            off+=nd3_;
        off %= nd3_;

        for (difference_type i=0; i<static_cast<difference_type>(nd1_); i++)    
            for (difference_type j = 0; j < static_cast<difference_type>(nd2_); j++)
                res.data_[res.offset(i, j, k)] = data_[offset(i, j, off)];
    }

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::circularShift(difference_type i0, 
    difference_type j0, difference_type k0) const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array3D<T, Alloc> res(nd1_, nd2_, nd3_);
    for (difference_type i=0; i<static_cast<difference_type>(nd1_); i++) {
        difference_type off1 = i+i0;            
        while (off1<0)
            off1+=nd1_;
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

                res.data_[res.offset(i, j, k)] = data_[offset(off1, off2, off3)];
            }        
        }
    }
    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::circularShift() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array3D<T, Alloc> res(nd1_, nd2_, nd3_);
    size_type depthC = (nd1_ + 1) / 2;
    size_type rowsC = (nd2_ + 1) / 2; 
    size_type columnsC = (nd3_ + 1) / 2;

    for (difference_type i = 0; i<static_cast<difference_type>(nd1_); i++)
        for (difference_type j=0; j<static_cast<difference_type>(nd2_); j++)
            for (difference_type k=0; k<static_cast<difference_type>(nd3_); k++)
                res.data_[res.offset(i, j, k)] = data_[offset((i + depthC) % nd1_, (j + rowsC) % nd2_, 
                (k + columnsC) % nd3_)];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::circularInvShift() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array3D<T, Alloc> res(nd1_, nd2_, nd3_);
    size_type depthC = (nd1_ + 1) / 2;
    size_type rowsC = (nd2_ + 1) / 2;
    size_type columnsC = (nd3_ + 1) / 2;
    
    for (size_type i = 0; i < nd1_; i++) {
        auto iPos = (i < depthC) ? (nd1_ + i - depthC) : (i - depthC);
        for (size_type j = 0; j < nd2_; j++) {
            auto jPos = (j < rowsC) ? (nd2_ + j - rowsC) : (j - rowsC);
            for (size_type k = 0; k < nd3_; k++) {
                auto kPos = (k < columnsC) ? (nd3_ + k - columnsC) : (k - columnsC);
                res.data_[res.offset(i, j, k)] = data_[offset(iPos, jPos, kPos)];
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
typename nct::Array3D<T, Alloc>::value_type nct::Array3D<T, Alloc>::sum() const
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
double nct::Array3D<T, Alloc>::castSum() const
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
typename nct::Array3D<T, Alloc>::value_type nct::Array3D<T, Alloc>::squaredNorm() const
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
double nct::Array3D<T, Alloc>::euclideanNorm() const
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
double nct::Array3D<T, Alloc>::lpNorm(double p) const
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
double nct::Array3D<T, Alloc>::infinityNorm() const
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
double nct::Array3D<T, Alloc>::mean() const
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
double nct::Array3D<T, Alloc>::variance() const
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
typename nct::Array3D<T, Alloc>::value_type nct::Array3D<T, Alloc>::max() const
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
typename nct::Array3D<T, Alloc>::value_type nct::Array3D<T, Alloc>::min() const
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
T nct::dotProduct(const Array3D<T, Alloc>& a, const Array3D<T, Alloc>& b)
{
    if ((a.dimension1() != b.dimension1()) || (a.dimension2() != b.dimension2()) || 
        (a.dimension3() != b.dimension3()))
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
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::constant(
    size_type dim1, size_type dim2, size_type dim3, const_reference t)
{
    return nct::Array3D<T, Alloc>(dim1, dim2, dim3, t);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::zeros(
    size_type dim1, size_type dim2, size_type dim3)
{
    return nct::Array3D<T, Alloc>(dim1, dim2, dim3, 0);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::ones(
    size_type dim1, size_type dim2, size_type dim3)
{
    return nct::Array3D<T, Alloc>(dim1, dim2, dim3, 1);    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::filledCube(
    size_type dim1, size_type dim2, size_type dim3,
    size_type c1, size_type c2, size_type c3, size_type l, const_reference val)
{
    Array3D<T, Alloc> arr(dim1, dim2, dim3, T());

    auto ii = c1 + l;
    auto jj = c2 + l;
    auto kk = c3 + l;

    for (size_type i = c1; (i <= ii) && (i < dim1); i++)
        for (size_type j = c2; (j <= jj) && (j < dim2); j++)
            for (size_type k = c3; (k <= kk) && (k < dim3); k++)
                arr(i, j, k) = val;


    return arr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::filledPrism(
    size_type dim1, size_type dim2, size_type dim3,
    size_type c1, size_type c2, size_type c3,
    size_type w1, size_type w2, size_type w3, const_reference val)
{
    Array3D<T, Alloc> arr(dim1, dim2, dim3, T());

    auto ii = c1 + w1;
    auto jj = c2 + w2;
    auto kk = c3 + w3;

    for (size_type i = c1; (i <= ii) && (i < dim1); i++)
        for (size_type j = c2; (j <= jj) && (j < dim2); j++)
            for (size_type k = c3; (k <= kk) && (k < dim3); k++)
                arr(i, j, k) = val;

    return arr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::filledSphere(
    size_type dim1, size_type dim2, size_type dim3,
    size_type c1, size_type c2, size_type c3, size_type r, const_reference val)
{
    Array3D<T, Alloc> arr(dim1, dim2, dim3, T());
    auto r2 = r*r;

    for (size_type i = 0; i < dim1; i++) {
        auto dd = (i > c1) ? (i - c1) : (c1 - i);
        for (size_type j = 0; j < dim2; j++) {
            auto dr = (j > c2) ? (j - c2) : (c2 - j);
            for (size_type k = 0; k < dim3; k++) {
                auto dc = (k > c3) ? (k - c3) : (c3 - k);

                auto d2 = dd*dd + dr*dr + dc*dc;
                if (d2 <= r2)
                    arr(i, j, k) = val;
            }
        }
    }

    return arr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::filledEllipsoid(
    size_type dim1, size_type dim2, size_type dim3,
    size_type c1, size_type c2, size_type c3,
    size_type w1, size_type w2, size_type w3, const_reference val)
{
    Array3D<T, Alloc> arr(dim1, dim2, dim3, T());
    auto w12 = static_cast<double>(w1*w1);
    auto w22 = static_cast<double>(w2*w2);
    auto w32 = static_cast<double>(w3*w3);

    for (size_type i = 0; i < dim1; i++) {
        auto dd = static_cast<double>(i)-static_cast<double>(c1);
        for (size_type j = 0; j < dim2; j++) {
            auto dr = static_cast<double>(j)-static_cast<double>(c2);
            for (size_type k = 0; k < dim3; k++) {
                auto dc = static_cast<double>(k)-static_cast<double>(c3);
                auto d2 = dd*dd + dr*dr + dc*dc;

                auto r = std::sqrt(d2);
                auto t = r > 0? std::acos(dc / r) : 0.0;
                auto p = std::atan2(dr, dd);
                
                auto ct = std::cos(t);
                auto st = std::sin(t);
                auto cp = std::cos(p);
                auto sp = std::sin(p);

                auto r2 = 1.0 / ((st*st*cp*cp / w12) + (st*st*sp*sp / w22) + (ct*ct / w32));
                if (d2 <= r2)
                    arr(i, j, k) = val;
            }
        }
    }

    return arr;
}

//=================================================================================================================
//        ITERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::iterator nct::Array3D<T, Alloc>::begin()
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, 0);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_iterator 
nct::Array3D<T, Alloc>::begin() const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, 0);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_iterator 
nct::Array3D<T, Alloc>::cbegin() const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, 0);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::iterator nct::Array3D<T, Alloc>::end()
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, n_);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_iterator
nct::Array3D<T, Alloc>::end() const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, n_);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_iterator
nct::Array3D<T, Alloc>::cend() const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, n_);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::reverse_iterator 
nct::Array3D<T, Alloc>::rbegin()
{
    return reverse_iterator(end());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reverse_iterator
nct::Array3D<T, Alloc>::rbegin() const
{
    return const_reverse_iterator(end());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reverse_iterator 
nct::Array3D<T, Alloc>::crbegin() const
{
    return const_reverse_iterator(end());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::reverse_iterator 
nct::Array3D<T, Alloc>::rend()
{
    return reverse_iterator(begin());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reverse_iterator 
nct::Array3D<T, Alloc>::rend() const
{
    return const_reverse_iterator(begin());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reverse_iterator
nct::Array3D<T, Alloc>::crend() const
{
    return const_reverse_iterator(begin());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::iterator 
nct::Array3D<T, Alloc>::beginDim1(size_type dim2, size_type dim3)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, 0, dim2, dim3, IteratorShiftMode3D::Dim1Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_iterator
nct::Array3D<T, Alloc>::beginDim1(size_type dim2, size_type dim3) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, 0, dim2, dim3, IteratorShiftMode3D::Dim1Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_iterator 
nct::Array3D<T, Alloc>::cbeginDim1(size_type dim2, size_type dim3) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, 0, dim2, dim3, IteratorShiftMode3D::Dim1Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::iterator
nct::Array3D<T, Alloc>::endDim1(size_type dim2, size_type dim3)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, nd1_, dim2, dim3, IteratorShiftMode3D::Dim1Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_iterator 
nct::Array3D<T, Alloc>::endDim1(size_type dim2, size_type dim3) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, nd1_, dim2, dim3, IteratorShiftMode3D::Dim1Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_iterator
nct::Array3D<T, Alloc>::cendDim1(size_type dim2, size_type dim3) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, nd1_, dim2, dim3, IteratorShiftMode3D::Dim1Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::reverse_iterator 
nct::Array3D<T, Alloc>::rbeginDim1(size_type dim2, size_type dim3)
{
    return reverse_iterator(endDim1(dim2, dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reverse_iterator 
nct::Array3D<T, Alloc>::rbeginDim1(size_type dim2, size_type dim3) const
{
    return const_reverse_iterator(endDim1(dim2, dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reverse_iterator 
nct::Array3D<T, Alloc>::crbeginDim1(size_type dim2, size_type dim3) const
{
    return const_reverse_iterator(endDim1(dim2, dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::reverse_iterator
nct::Array3D<T, Alloc>::rendDim1(size_type dim2, size_type dim3)
{
    return reverse_iterator(beginDim1(dim2, dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reverse_iterator 
nct::Array3D<T, Alloc>::rendDim1(size_type dim2, size_type dim3) const
{
    return const_reverse_iterator(beginDim1(dim2, dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reverse_iterator 
nct::Array3D<T, Alloc>::crendDim1( size_type dim2, size_type dim3) const
{
    return const_reverse_iterator(beginDim1(dim2, dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::iterator
nct::Array3D<T, Alloc>::beginDim2(size_type dim1, size_type dim3)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, dim1, 0, dim3, IteratorShiftMode3D::Dim2Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_iterator 
nct::Array3D<T, Alloc>::beginDim2(size_type dim1, size_type dim3) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, 0, dim3, IteratorShiftMode3D::Dim2Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_iterator
nct::Array3D<T, Alloc>::cbeginDim2(size_type dim1, size_type dim3) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, 0, dim3, IteratorShiftMode3D::Dim2Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::iterator
nct::Array3D<T, Alloc>::endDim2(size_type dim1, size_type dim3)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, dim1, nd2_, dim3, IteratorShiftMode3D::Dim2Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_iterator
nct::Array3D<T, Alloc>::endDim2(size_type dim1, size_type dim3) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, nd2_, dim3, IteratorShiftMode3D::Dim2Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_iterator
nct::Array3D<T, Alloc>::cendDim2(size_type dim1, size_type dim3) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, nd2_, dim3, IteratorShiftMode3D::Dim2Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::reverse_iterator 
nct::Array3D<T, Alloc>::rbeginDim2(size_type dim1, size_type dim3)
{
    return reverse_iterator(endDim2(dim1, dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reverse_iterator 
nct::Array3D<T, Alloc>::rbeginDim2(size_type dim1, size_type dim3) const
{
    return const_reverse_iterator(endDim2(dim1, dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reverse_iterator 
nct::Array3D<T, Alloc>::crbeginDim2(size_type dim1, size_type dim3) const
{
    return const_reverse_iterator(endDim2(dim1, dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::reverse_iterator
nct::Array3D<T, Alloc>::rendDim2(size_type dim1, size_type dim3)
{
    return reverse_iterator(beginDim2(dim1, dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reverse_iterator 
nct::Array3D<T, Alloc>::rendDim2(size_type dim1, size_type dim3) const
{
    return const_reverse_iterator(beginDim2(dim1, dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reverse_iterator 
nct::Array3D<T, Alloc>::crendDim2(size_type dim1, size_type dim3) const
{
    return const_reverse_iterator(beginDim2(dim1, dim3));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::iterator 
nct::Array3D<T, Alloc>::beginDim3(size_type dim1, size_type dim2)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, dim1, dim2, 0, IteratorShiftMode3D::Dim3Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_iterator
nct::Array3D<T, Alloc>::beginDim3(size_type dim1, size_type dim2) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, dim2, 0, IteratorShiftMode3D::Dim3Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_iterator 
nct::Array3D<T, Alloc>::cbeginDim3(size_type dim1, size_type dim2) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, dim2, 0, IteratorShiftMode3D::Dim3Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::iterator 
nct::Array3D<T, Alloc>::endDim3(size_type dim1, size_type dim2)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, dim1, dim2, nd3_, IteratorShiftMode3D::Dim3Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_iterator 
nct::Array3D<T, Alloc>::endDim3(size_type dim1, size_type dim2) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, dim2, nd3_, IteratorShiftMode3D::Dim3Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_iterator 
nct::Array3D<T, Alloc>::cendDim3(size_type dim1, size_type dim2) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, dim1, dim2, nd3_, IteratorShiftMode3D::Dim3Mode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::reverse_iterator
nct::Array3D<T, Alloc>::rbeginDim3(size_type dim1, size_type dim2)
{
    return reverse_iterator(endDim3(dim1, dim2));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reverse_iterator 
nct::Array3D<T, Alloc>::rbeginDim3(size_type dim1, size_type dim2) const
{
    return const_reverse_iterator(endDim3(dim1, dim2));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reverse_iterator
nct::Array3D<T, Alloc>::crbeginDim3(size_type dim1, size_type dim2) const
{
    return const_reverse_iterator(endDim3(dim1, dim2));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::reverse_iterator
nct::Array3D<T, Alloc>::rendDim3(size_type dim1, size_type dim2)
{
    return reverse_iterator(beginDim3(dim1, dim2));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reverse_iterator
nct::Array3D<T, Alloc>::rendDim3(size_type dim1, size_type dim2) const
{
    return const_reverse_iterator(beginDim3(dim1, dim2));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array3D<T, Alloc>::const_reverse_iterator 
nct::Array3D<T, Alloc>::crendDim3(size_type dim1, size_type dim2) const
{
    return const_reverse_iterator(beginDim3(dim1, dim2));
}

//=================================================================================================================
//        TRANSFORMATIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array3D<U, AllocU> nct::Array3D<T, Alloc>::transformData(
    const std::function<U(const_reference)>& f) const
{
    Array3D<U, AllocU> outputArray(nd1_, nd2_, nd3_);        
    for (size_type k = 0; k<n_; k++)
        outputArray[k] = f(data_[k]);
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array3D<U, AllocU> nct::Array3D<T, Alloc>::collapseDim1(
    const std::function<U(const Array<T, Alloc>&)>& f) const
{
    Array3D<U, AllocU> outputArray(1, nd2_, nd3_);        
    for (size_type j = 0; j<nd2_; j++)
        for (size_type k = 0; k<nd3_; k++)
            outputArray(0, j, k) = f(elementsOfDim1(j, k));
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array3D<U, AllocU> nct::Array3D<T, Alloc>::collapseDim1(
    const std::function<U(const_iterator, const_iterator)>& f) const
{
    Array3D<U, AllocU> outputArray(1, nd2_, nd3_);        
    for (size_type j = 0; j<nd2_; j++)
        for (size_type k = 0; k<nd3_; k++)
            outputArray(0, j, k) = f(beginDim1(j, k), endDim1(j, k));
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array3D<U, AllocU> nct::Array3D<T, Alloc>::collapseDim2(
    const std::function<U(const Array<T, Alloc>&)>& f) const
{
    Array3D<U, AllocU> outputArray(nd1_, 1, nd3_);        
    for (size_type i = 0; i<nd1_; i++)
        for (size_type k = 0; k<nd3_; k++)
            outputArray(i, 0, k) = f(elementsOfDim2(i,k));
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array3D<U, AllocU> nct::Array3D<T, Alloc>::collapseDim2(
    const std::function<U(const_iterator, const_iterator)>& f) const
{
    Array3D<U, AllocU> outputArray(nd1_, 1, nd3_);        
    for (size_type i = 0; i<nd1_; i++)
        for (size_type k = 0; k<nd3_; k++)
            outputArray(i, 0, k) = f(beginDim2(i, k), endDim2(i, k));
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array3D<U, AllocU> nct::Array3D<T, Alloc>::collapseDim3(
    const std::function<U(const Array<T, Alloc>&)>& f) const
{
    Array3D<U, AllocU> outputArray(nd1_, nd2_, 1);        
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            outputArray(i, j, 0) = f(elementsOfDim3(i,j));
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array3D<U, AllocU> nct::Array3D<T, Alloc>::collapseDim3(
    const std::function<U(const_iterator, const_iterator)>& f) const
{
    Array3D<U, AllocU> outputArray(nd1_, nd2_, 1);        
    for (size_type i = 0; i<nd1_; i++)
        for (size_type j = 0; j<nd2_; j++)
            outputArray(i, j, 0) = f(beginDim3(i, j), endDim3(i, j));
    return outputArray;    
}

//=================================================================================================================
//        I/O OPERATIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array3D<T, Alloc> nct::Array3D<T, Alloc>::read(std::istream& i)
{
    // Check for errors
    if (i.fail())
        throw IOException(exc_bad_input_stream, SOURCE_INFO);

    // Read dimensions
    size_type data_ = 0;
    size_type r = 0;
    size_type c = 0;

    i.read(reinterpret_cast<char*> (&data_), sizeof(size_type));
    if (i.fail())
        throw IOException(exc_error_reading_dimension1, SOURCE_INFO);

    i.read(reinterpret_cast<char*> (&r), sizeof(size_type));
    if (i.fail())
        throw IOException(exc_error_reading_dimension2, SOURCE_INFO);

    i.read(reinterpret_cast<char*> (&c), sizeof(size_type));
    if (i.fail())
        throw IOException(exc_error_reading_dimension3, SOURCE_INFO);

    // Read data
    Array3D<T, Alloc> arr(data_, r, c);
    i.read(reinterpret_cast<char*> (arr.data()), sizeof(T)*arr.size());
    if (i.fail())
        throw IOException(exc_error_reading_data, SOURCE_INFO);
    
    return arr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array3D<T, Alloc>::write(std::ostream& o) const
{
    // Check for errors
    if (o.fail())
        throw IOException(exc_bad_output_stream, SOURCE_INFO);
    
    // Write number of dim2 and number of dim3
    o.write(reinterpret_cast<const char*>(&nd1_), sizeof(size_type));
    if (o.fail())
        throw IOException(exc_error_writing_dimension1, SOURCE_INFO);

    o.write(reinterpret_cast<const char*>(&nd2_), sizeof(size_type));
    if (o.fail())
        throw IOException(exc_error_writing_dimension2, SOURCE_INFO);

    o.write(reinterpret_cast<const char*>(&nd3_), sizeof(size_type));
    if (o.fail())
        throw IOException(exc_error_writing_dimension3, SOURCE_INFO);

    // Write data
    if (n_>0) {
        o.write(reinterpret_cast<const char*> (data()), sizeof(T)*n_);
        if (o.fail())
            throw IOException(exc_error_writing_data, SOURCE_INFO);

    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
std::istream& nct::operator>>(std::istream& i, Array3D<T, Alloc>& arr)
{
    arr = Array3D<T, Alloc>::read(i);
    return i;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
std::ostream& nct::operator<<(std::ostream& o, const Array3D<T, Alloc>& arr)
{
    auto nd1 = arr.dimension1();
    auto nd2 = arr.dimension2();
    auto nd3 = arr.dimension3();        

    o << std::endl;
    for (index_t i=0; i<nd1; i++) {
        for (index_t j = 0; j<nd2; j++) {
            for (index_t k = 0; k<nd3; k++)
                o << arr(i, j, k) << " ";
            o << std::endl;
        }
        o << std::endl;
    }

    return o;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
