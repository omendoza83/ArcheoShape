//=================================================================================================================
/**
 *  @file       Array2D_template.h
 *  @brief      nct::Array2D class template implementation file.
 *  @details    This file contains the implementation of the nct::Array2D class template.
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
nct::Array2D<T, Alloc>::Array2D(const allocator_type& allocator)  noexcept : alloc_{allocator},
n_{0}, nr_{0}, nc_{0}, data_{nullptr}
{

}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc>::Array2D(size_type rows, size_type columns, 
    const allocator_type& allocator) : alloc_{allocator}, n_{0}, nr_{0}, nc_{0}, data_{nullptr}
{
    try {
        resize(rows, columns);
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
nct::Array2D<T, Alloc>::Array2D(size_type rows, size_type columns, const_reference val,
    const allocator_type& allocator) : alloc_{allocator}, n_{0}, nr_{0}, nc_{0}, data_{nullptr}
{
    try {
        assign(rows, columns, val);
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
nct::Array2D<T, Alloc>::Array2D(const Array2D<T, Alloc>& other) :
n_{0}, nr_{0}, nc_{0}, data_{nullptr}
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
nct::Array2D<T, Alloc>::Array2D(const Array2D<T, Alloc>& other,
    const allocator_type& allocator) : alloc_{allocator}, n_{0}, nr_{0}, nc_{0}, data_{nullptr}
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
nct::Array2D<T, Alloc>::Array2D(Array2D<T, Alloc>&& other) noexcept
{
    n_ = other.n_;
    nr_ = other.nr_;
    nc_ = other.nc_;    
    data_ = other.data_;

    other.n_ = 0;
    other.nr_ = 0;
    other.nc_ = 0;    
    other.data_ = nullptr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc>::Array2D(Array2D<T, Alloc>&& other,
    const allocator_type& allocator) : alloc_{allocator}
{
    n_ = other.n_;
    nr_ = other.nr_;
    nc_ = other.nc_;    
    data_ = other.data_;

    other.n_ = 0;
    other.nr_ = 0;
    other.nc_ = 0;    
    other.data_ = nullptr;
}

//=================================================================================================================
//        DESTRUCTOR
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline nct::Array2D<T, Alloc>::~Array2D() noexcept
{        
    clear();
}

//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc>& nct::Array2D<T, Alloc>::operator=(const Array2D<T, Alloc>& other)
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
nct::Array2D<T, Alloc>& nct::Array2D<T, Alloc>::operator=(Array2D<T, Alloc>&& other) noexcept
{
    if (data_ == other.data_)
        return *this;

    clear();
    n_ = other.n_;
    nr_ = other.nr_;
    nc_ = other.nc_;
    data_ = other.data_;

    other.n_ = 0;
    other.nr_ = 0;
    other.nc_ = 0;
    other.data_ = nullptr;

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::reference nct::Array2D<T, Alloc>::operator()(
    size_type i, size_type j)
{
#ifndef NCT_ARRAY_2D_DISABLE_INDEX_CHECKING
    if (i >= nr_)
        throw IndexOutOfRangeException("i", SOURCE_INFO);
    if (j >= nc_)
        throw IndexOutOfRangeException("j", SOURCE_INFO);
#endif
    return data_[i * nc_ + j];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reference
nct::Array2D<T, Alloc>::operator()(size_type i, size_type j) const
{
#ifndef NCT_ARRAY_2D_DISABLE_INDEX_CHECKING
    if (i >= nr_)
        throw IndexOutOfRangeException("i", SOURCE_INFO);
    if (j >= nc_)
        throw IndexOutOfRangeException("j", SOURCE_INFO);
#endif
    return data_[i * nc_ + j];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::reference
nct::Array2D<T, Alloc>::operator[](size_type i)
{
#ifndef NCT_ARRAY_2D_DISABLE_INDEX_CHECKING
    if (i >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
#endif
    return data_[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reference
nct::Array2D<T, Alloc>::operator[](size_type i) const
{
#ifndef NCT_ARRAY_2D_DISABLE_INDEX_CHECKING
    if (i >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
#endif
    return data_[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::reference
nct::Array2D<T, Alloc>::operator()(size_type i)
{
#ifndef NCT_ARRAY_2D_DISABLE_INDEX_CHECKING
    if (i >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
#endif
    return data_[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reference
nct::Array2D<T, Alloc>::operator()(size_type i) const
{
#ifndef NCT_ARRAY_2D_DISABLE_INDEX_CHECKING
    if (i >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
#endif
    return data_[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::equality_comparable<T>
bool nct::Array2D<T, Alloc>::operator==(const Array2D<T, Alloc>& right) const
{
    if (data_ == right.data_)
        return true;

    if ((nr_ != right.nr_) || (nc_ != right.nc_))
        return false;

    for (size_type i = 0; i < n_; i++) {
        if (data_[i] != right.data_[i])
            return false;
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::equality_comparable<T>
bool nct::Array2D<T, Alloc>::operator!=(const Array2D<T, Alloc>& right) const
{
    return !(*this == right);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::operator&(const Array2D<T, Alloc> & right) const
{
    if ((right.nr_ != nr_) || (right.nc_ != nc_))
        throw ArgumentException("right", exc_bad_array_dimensions,
            SOURCE_INFO);

    Array2D<T, Alloc> res(nr_, nc_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = (data_[i] & right.data_[i]);

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::integral T, typename Alloc>
nct::Array2D<T, Alloc> nct::operator&(Array2D<T, Alloc> && left, const Array2D<T, Alloc> & right)
{
    if ((left.rows() != right.rows()) || (left.columns() != right.columns()))
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array2D<T, Alloc> resArr;
    std::swap(resArr, left);

    for (typename Array2D<T, Alloc>::size_type i = 0; i < resArr.size(); i++)
        resArr[i] = (resArr[i] & right[i]);

    return resArr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
const nct::Array2D<T, Alloc> & nct::Array2D<T, Alloc>::operator&=(
    const Array2D<T, Alloc> & right)
{
    if ((right.nr_ != nr_) || (right.nc_ != nc_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] &= right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::operator|(
    const Array2D<T, Alloc> & right) const
{
    if ((right.nr_ != nr_) || (right.nc_ != nc_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array2D<T, Alloc> res(nr_, nc_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = (data_[i] | right.data_[i]);

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::integral T, typename Alloc>
nct::Array2D<T, Alloc> nct::operator|(Array2D<T, Alloc> && left, const Array2D<T, Alloc> & right)
{
    if ((left.rows() != right.rows()) || (left.columns() != right.columns()))
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array2D<T, Alloc> resArr;
    std::swap(resArr, left);

    for (typename Array2D<T, Alloc>::size_type i = 0; i < resArr.size(); i++)
        resArr[i] = (resArr[i] | right[i]);

    return resArr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
const nct::Array2D<T, Alloc> & nct::Array2D<T, Alloc>::operator|=(
    const Array2D<T, Alloc> & right)
{
    if ((right.nr_ != nr_) || (right.nc_ != nc_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] |= right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::operator^(
    const Array2D<T, Alloc> & right) const
{
    if ((right.nr_ != nr_) || (right.nc_ != nc_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array2D<T, Alloc> res(nr_, nc_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = (data_[i] ^ right.data_[i]);

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::integral T, typename Alloc>
nct::Array2D<T, Alloc> nct::operator^(Array2D<T, Alloc> && left, const Array2D<T, Alloc> & right)
{
    if ((left.rows() != right.rows()) || (left.columns() != right.columns()))
        throw ArgumentException("right, left", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array2D<T, Alloc> resArr;
    std::swap(resArr, left);

    for (typename Array2D<T, Alloc>::size_type i = 0; i < resArr.size(); i++)
        resArr[i] = (resArr[i] ^ right[i]);

    return resArr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
const nct::Array2D<T, Alloc> & nct::Array2D<T, Alloc>::operator^=(
    const Array2D<T, Alloc> & right)
{
    if ((right.nr_ != nr_) || (right.nc_ != nc_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] ^= right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::operator+() const
{
    Array2D<T, Alloc> res(nr_, nc_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Addable<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::operator+(
    const Array2D<T, Alloc> & right) const
{
    if ((right.nr_ != nr_) || (right.nc_ != nc_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array2D<T, Alloc> res(nr_, nc_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i] + right.data_[i];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Addable T, typename Alloc>
nct::Array2D<T, Alloc> nct::operator+(Array2D<T, Alloc> && left, const Array2D<T, Alloc> & right)
{
    if ((left.rows() != right.rows()) || (left.columns() != right.columns()))
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array2D<T, Alloc> resArr;
    std::swap(resArr, left);

    for (typename Array2D<T, Alloc>::size_type i = 0; i < resArr.size(); i++)
        resArr[i] += right[i];

    return resArr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Addable<T>
const nct::Array2D<T, Alloc> & nct::Array2D<T, Alloc>::operator+=(
    const Array2D<T, Alloc> & right)
{
    if ((right.nr_ != nr_) || (right.nc_ != nc_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] += right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::SignedNumeric<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::operator-() const
{
    Array2D<T, Alloc> res(nr_, nc_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = -data_[i];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Substractable<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::operator-(const Array2D & right) const
{
    if ((right.nr_ != nr_) || (right.nc_ != nc_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array2D<T, Alloc> res(nr_, nc_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i] - right.data_[i];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Substractable T, typename Alloc>
nct::Array2D<T, Alloc> nct::operator-(Array2D<T, Alloc> && left, const Array2D<T, Alloc> & right)
{
    if (left.rows() != right.rows() || left.columns() != left.columns())
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array2D<T, Alloc> resArr;
    std::swap(resArr, left);

    for (typename Array2D<T, Alloc>::size_type i = 0; i < resArr.size(); i++)
        resArr[i] -= right[i];

    return resArr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Substractable<T>
const nct::Array2D<T, Alloc> & nct::Array2D<T, Alloc>::operator-=(
    const Array2D<T, Alloc> & right)
{
    if ((right.nr_ != nr_) || (right.nc_ != nc_))
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] -= right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::operator*(const Array2D<T, Alloc> & right) const
{
    if (right.nr_ != nc_)
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array2D<T, Alloc> res(nr_, right.nc_);
    for (size_type i = 0; i < nr_; i++) {
        auto offsetRes = res.offset(i);
        auto offsetM1 = offset(i);

        for (size_type j = 0; j < right.nc_; j++) {
            res.data_[offsetRes + j] = 0;
            for (size_type k = 0; k < nc_; k++)
                res.data_[offsetRes + j] += data_[offsetM1 + k] * right.data_[right.offset(k, j)];
        }
    }

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
const nct::Array2D<T, Alloc>& nct::Array2D<T, Alloc>::operator*=(
    const Array2D<T, Alloc> & right)
{
    if (right.nr_ != nc_)
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    nct::Array2D<T, Alloc> tmp(std::move(*this));
    resize(tmp.nr_, right.nc_);
    for (size_type i = 0; i < nr_; i++) {
        auto offsetRes = offset(i);
        auto offsetM1 = tmp.offset(i);

        for (size_type j = 0; j < nc_; j++) {
            data_[offsetRes + j] = 0;
            for (size_type k = 0; k < tmp.nc_; k++)
                data_[offsetRes + j] += tmp.data_[offsetM1 + k] * right.data_[right.offset(k, j)];
        }
    }

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::operator*(const_reference right) const
{
    Array2D<T, Alloc> res(nr_, nc_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i] * right;

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T, typename Alloc>
nct::Array2D<T, Alloc> nct::operator*(const T & left, const Array2D<T, Alloc> & right)
{
    Array2D<T, Alloc> res(right.rows(), right.columns());

    for (typename Array2D<T, Alloc>::size_type i = 0; i < right.size(); i++)
        res[i] = right[i] * left;

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
const nct::Array2D<T, Alloc>& nct::Array2D<T, Alloc>::operator*=(const_reference right)
{
    for (size_type i = 0; i < n_; i++)
        data_[i] *= right;

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::operator/(const_reference right) const
{
    Array2D<T, Alloc> res(nr_, nc_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i] / right;

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
const nct::Array2D<T, Alloc>& nct::Array2D<T, Alloc>::operator/=(const_reference right)
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
void nct::Array2D<T, Alloc>::clear() noexcept
{
    if (n_) {
        for (size_type i = 0; i<n_; i++)
            allocator_traits::destroy(alloc_, data_ + i);
        alloc_.deallocate(data_, n_);        
    }
    n_ = 0;
    nr_ = 0;
    nc_ = 0;    
    data_ = nullptr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array2D<T, Alloc>::assign(size_type rows, size_type columns, const_reference val)
{    
    if ( n_ == (rows*columns) ) {
        nr_ = rows;
        nc_ = columns;
        for (size_type i=0; i<n_; i++)
            data_[i] = val;
    }
    else {
        try {    
            // Release old data.
            clear();

            // Allocate new array.
            nr_ = rows;
            nc_ = columns;    
            n_ = nc_*nr_; 
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
inline void nct::Array2D<T, Alloc>::resize(size_type rows, size_type columns)
{    
    if ((nc_ == columns) && (nr_ == rows))
        return;

    // Previous array size.
    auto pnr = nr_;
    auto pnc = nc_;
    auto pn = n_;

    // New array size.
    nr_ = rows;
    nc_ = columns;
    n_ = nc_ * nr_;

    // Block segment that will be preserved.
    auto rMin = pnr < nr_ ? (pnr) : (nr_);
    auto cMin = pnc < nc_ ? (pnc) : (nc_);

    // Allocate memory and copy previous data.
    if ((n_ > 0) && (pn != n_)) {
        try {
            // Allocate new array.
            auto dd = data_;
            data_ = alloc_.allocate(n_);

            // Initialize data.
            for (size_type i = 0; i < nr_; i++) {
                for (size_type j = 0; j < nc_; j++) {
                    if ((i < rMin) && (j < cMin))
                        allocator_traits::construct(alloc_, data_ + (i * nc_ + j), std::move(dd[i * pnc + j]));
                    else
                        allocator_traits::construct(alloc_, data_ + (i * nc_ + j), T());
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
    else if (n_ > 0) {
        // Re-arrange data.
        difference_type i0 = 0, j0 = 0, ii = 1, ij = 1;
        if (nc_ > pnc) {
            i0 = nr_ - 1;
            ii = -1;
            j0 = nc_ - 1;
            ij = -1;
        }

        auto i = i0;
        for (size_type ic = 0; ic < nr_; ic++) {
            auto j = j0;
            for (size_type jc = 0; jc < nc_; jc++) {
                if ((i < static_cast<difference_type>(rMin)) &&
                    (j < static_cast<difference_type>(cMin)))
                    std::swap(data_[offset(i, j)], data_[i * pnc + j]);
                else
                    data_[offset(i, j)] = T();
                j += ij;
            }
            i += ii;
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
void nct::Array2D<T, Alloc>::resize(size_type rows, size_type columns, const_reference val)
{    
    if ( (nc_ == columns) && (nr_ == rows) )
        return;

    // Previous array size.
    auto pnr = nr_;
    auto pnc = nc_;
    auto pn = n_;

    // New array size.
    nr_ = rows;
    nc_ = columns;    
    n_ = nc_*nr_;

    // Block segment that will be preserved.
    auto rMin = pnr < nr_? (pnr) : (nr_);
    auto cMin = pnc < nc_? (pnc) : (nc_);

    // Allocate memory and copy previous data.
    if ((n_>0) && (pn != n_)) {
        try {    
            // Allocate new array.
            auto dd = data_;        
            data_ = alloc_.allocate(n_);

            // Initialize data.
            for (size_type i=0; i<nr_; i++) {
                for (size_type j=0; j<nc_; j++) {
                    if ((i < rMin) && (j < cMin))
                        allocator_traits::construct(alloc_, data_ + (i*nc_ + j), std::move(dd[i*pnc + j]));
                    else
                        allocator_traits::construct(alloc_, data_ + (i*nc_ + j), val);
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
    else if (n_>0) {
        // Re-arrange data.
        difference_type i0 = 0, j0 = 0, ii = 1, ij = 1;
        if (nc_ > pnc) {
            i0 = nr_ - 1;
            ii = -1;
            j0 = nc_ - 1;
            ij = -1;
        }
        
        auto i = i0;
        for (size_type ic=0; ic<nr_; ic++) {
            auto j = j0;
            for (size_type jc=0; jc<nc_; jc++) {
                if ((i < static_cast<difference_type>(rMin)) && 
                    (j < static_cast<difference_type>(cMin)))
                    std::swap(data_[offset(i, j)], data_[i*pnc + j]);
                else
                    data_[offset(i, j)] = val;
                j += ij;
            }
            i += ii;
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
inline typename nct::Array2D<T, Alloc>::allocator_type 
nct::Array2D<T, Alloc>::get_allocator() const
{
    return allocator_type(alloc_);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline void nct::Array2D<T, Alloc>::fill(const_reference val)
{
    for (size_type i=0; i<n_; i++)
        data_[i] = val;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array2D<T, Alloc>::reshape(size_type rows, size_type columns)
{
    if (n_ != rows*columns)
        throw ArgumentException("rows, columns.", exc_bad_reshape_dimensions, 
            SOURCE_INFO);
    nr_ = rows;
    nc_ = columns;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array2D<T, Alloc>::copy(const Array2D& other)
{
    // Check whether a different instance is being copied.
    if ( (data_ == other.data_) && (nc_ == other.nc_) && (nr_ == other.nr_))
        return;

    if (other.n_ == 0) {
        // Release object.
        clear();
        nr_ = other.nr_;
        nc_ = other.nc_;
    }
    else if (n_ == other.n_) {
        // Copy new contents.
        nr_ = other.nr_;
        nc_ = other.nc_;
        for (size_type i=0; i<n_; i++)
            data_[i] = other.data_[i];
    }
    else {
        // Allocate new array and copy data.
        try {                
            clear();
            n_ = other.n_;
            nr_ = other.nr_;
            nc_ = other.nc_;
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
bool nct::Array2D<T, Alloc>::empty() const noexcept
{
    return (n_ == 0);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::size_type
nct::Array2D<T, Alloc>::rows() const noexcept
{
    return nr_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::size_type 
nct::Array2D<T, Alloc>::columns() const noexcept
{
    return nc_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::size_type
nct::Array2D<T, Alloc>::size() const noexcept
{
    return n_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::transpose() const
{
    Array2D<T, Alloc>res (nc_, nr_);
    for (size_type i = 0; i < nr_; i++)
        for (size_type j = 0; j < nc_; j++)
            res.data_[res.offset(j, i)] = data_[offset(i, j)];
    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::pointer nct::Array2D<T, Alloc>::data() noexcept
{
    return data_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_pointer
nct::Array2D<T, Alloc>::data() const noexcept
{
    return data_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::pointer 
nct::Array2D<T, Alloc>::data(size_type index)
{
    if (index >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
    return &data_[index];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_pointer
nct::Array2D<T, Alloc>::data(size_type index) const
{
    if (index >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
    return &data_[index];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::pointer
nct::Array2D<T, Alloc>::data(size_type row, size_type column)
{
    if (row >= nr_)
        throw IndexOutOfRangeException("row", SOURCE_INFO);
    if (column >= nc_)
        throw IndexOutOfRangeException("column", SOURCE_INFO);
    return &data_[row*nc_ + column];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_pointer 
nct::Array2D<T, Alloc>::data(size_type row, size_type column) const
{
    if (row >= nr_)
        throw IndexOutOfRangeException("row", SOURCE_INFO);
    if (column >= nc_)
        throw IndexOutOfRangeException("column", SOURCE_INFO);
    return &data_[row*nc_ + column];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::reference 
nct::Array2D<T, Alloc>::at(size_type index) 
{
    if (index >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
    return data_[index];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reference 
nct::Array2D<T, Alloc>::at(size_type index) const
{
    if (index >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
    return data_[index];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::reference nct::Array2D<T, Alloc>::at(
    size_type row, size_type column)
{
    if (row >= nr_)
        throw IndexOutOfRangeException("row", SOURCE_INFO);
    if (column >= nc_)
        throw IndexOutOfRangeException("column", SOURCE_INFO);
    return data_[row*nc_ + column];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reference nct::Array2D<T, Alloc>::at(
    size_type row, size_type column) const
{
    if (row >= nr_)
        throw IndexOutOfRangeException("row", SOURCE_INFO);
    if (column >= nc_)
        throw IndexOutOfRangeException("column", SOURCE_INFO);
    return data_[row*nc_ + column];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::size_type nct::Array2D<T, Alloc>::offset(
    size_type row) const noexcept
{
    return row*nc_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::size_type nct::Array2D<T, Alloc>::offset(
    size_type row, size_type column) const noexcept
{
    return row*nc_ + column;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::reference nct::Array2D<T, Alloc>::front()
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);
    return data_[0];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reference
nct::Array2D<T, Alloc>::front() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);
    return data_[0];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::reference 
nct::Array2D<T, Alloc>::back()
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);
    return data_[n_ - 1];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reference 
nct::Array2D<T, Alloc>::back() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);
    return data_[n_ - 1];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename Container>
Container nct::Array2D<T, Alloc>::find(const_reference t) const
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
template<typename T, typename Alloc>template<typename U, typename AllocU>
nct::Array2D<U, AllocU> nct::Array2D<T, Alloc>::toArray() const
{
    Array2D<U, AllocU> outputArray(nr_, nc_);        
    for (size_type k = 0; k<n_; k++)
        outputArray[k] = static_cast<U>(data_[k]);
    return outputArray;    
}

//=================================================================================================================
//        DATA INSERTIONS AND DELETIONS 
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator InputIt>
typename nct::Array2D<T, Alloc>::iterator
    nct::Array2D<T, Alloc>::insertRow(size_type row, InputIt first, InputIt last)
{
    if (row > nr_)
        throw IndexOutOfRangeException("row", SOURCE_INFO);

    if (static_cast<size_type>(last-first) != nc_)
        throw RangeException("first, last", SOURCE_INFO);

    // Move old data and resize array.
    nct::Array2D<T, Alloc> old(std::move(*this));
    resize(old.nr_ + 1, old.nc_);
    
    // Fill array.
    for (size_type i=0; i<row; i++)
        for (size_type j=0; j<nc_; j++)        
            data_[offset(i, j)] = std::move(old.data_[old.offset(i, j)]);
    
    auto x = first;
    for (size_type j=0; j<nc_; j++, ++x)        
        data_[offset(row, j)] = *x;
    
    for (size_type i=(row+1); i<nr_; i++)
        for (size_type j=0; j<nc_; j++)        
            data_[offset(i, j)] = std::move(old.data_[old.offset(i - 1, j)]);

    return beginRow(row);
}    

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
typename nct::Array2D<T, Alloc>::iterator
    nct::Array2D<T, Alloc>::insertRow(size_type row, std::initializer_list<value_type> il)
{
    if (row > nr_)
        throw IndexOutOfRangeException("row", SOURCE_INFO);

    if (il.size() != nc_)
        throw ArgumentException("il", exc_bad_initializer_list_size, SOURCE_INFO);

    return insertRow(row, std::begin(il), std::end(il));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
typename nct::Array2D<T, Alloc>::iterator
nct::Array2D<T, Alloc>::insertRow(size_type row, const Array<T, Alloc>& data)
{
    if (row > nr_)
        throw IndexOutOfRangeException("row", SOURCE_INFO);

    if (data.size() != nc_)
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    return insertRow(row, std::begin(data), std::end(data));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
typename nct::Array2D<T, Alloc>::iterator
    nct::Array2D<T, Alloc>::eraseRow(size_type row)
{
    if (row >= nr_)
        throw IndexOutOfRangeException("row", SOURCE_INFO);

    // Move old data and resize array.
    nct::Array2D<T, Alloc> old(std::move(*this));
    resize(old.nr_ - 1, old.nc_);
    
    // Fill array.
    for (size_type i=0; i<row; i++)
        for (size_type j=0; j<nc_; j++)        
            data_[offset(i, j)] = std::move(old.data_[old.offset(i, j)]);
    
    for (size_type i=row; i<nr_; i++)
        for (size_type j=0; j<nc_; j++)        
            data_[offset(i, j)] = std::move(old.data_[old.offset(i + 1, j)]);

    if (row == nr_)
        return iterator();
    return beginRow(row);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
typename nct::Array2D<T, Alloc>::iterator
nct::Array2D<T, Alloc>::insertRows(size_type row, const Array2D<T, Alloc>& data)
{
    if (row > nr_)
        throw IndexOutOfRangeException("row", SOURCE_INFO);

    if (data.nc_ != nc_)
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    // Move old data and resize array.
    auto nnr = data.rows();
    nct::Array2D<T, Alloc> old(std::move(*this));
    resize(old.nr_ + nnr, old.nc_);
    
    // Fill array.
    for (size_type i=0; i<row; i++)
        for (size_type j=0; j<nc_; j++)        
            data_[offset(i, j)] = std::move(old.data_[old.offset(i, j)]);
    
    for (size_type i=row; i<(row+nnr); i++)
        for (size_type j=0; j<nc_; j++)        
            data_[offset(i, j)] = data.data_[data.offset(i - row, j)];
    
    for (size_type i=(row+nnr); i<nr_; i++)
        for (size_type j=0; j<nc_; j++)        
            data_[offset(i, j)] = std::move(old.data_[old.offset(i - nnr, j)]);

    return beginRow(row);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
typename nct::Array2D<T, Alloc>::iterator
nct::Array2D<T, Alloc>::eraseRows(size_type first, size_type last)
{
    if (first >= nr_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nr_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    // Move old data and resize array.
    auto nnr = last - first + 1;
    nct::Array2D<T, Alloc> old(std::move(*this));
    resize(old.nr_ - nnr, old.nc_);
    
    // Fill array.
    for (size_type i=0; i<first; i++)
        for (size_type j=0; j<nc_; j++)        
            data_[offset(i, j)] = std::move(old.data_[old.offset(i, j)]);
        
    for (size_type i=first; i<nr_; i++)
        for (size_type j=0; j<nc_; j++)        
            data_[offset(i, j)] = std::move(old.data_[old.offset(i + nnr, j)]);

    if (first == nr_)
        return iterator();
    return beginRow(first);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
void nct::Array2D<T, Alloc>::eraseRows(IndexIt first, IndexIt last)
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    size_type nnr = 0;
    for (auto ind1 = first; ind1 != last; ++ind1) {
        if (static_cast<size_type>(*ind1) >= nr_)
            throw ArgumentException("first, last", exc_indices_out_of_range, SOURCE_INFO);

        auto ind2 = first;
        for (; ind2 != ind1; ++ind2) {
            if (static_cast<size_type>(*ind1) == static_cast<size_type>(*ind2))
                break;
        }        
        nnr += (ind2 == ind1);
    }

    // Move old data and resize array.
    nct::Array2D<T, Alloc> old(std::move(*this));
    resize(old.nr_ - nnr, old.nc_);
    
    // Fill array.
    size_type c = 0;
    for (size_type i=0; i<old.nr_; i++) {
        auto ind = first;
        for (; ind != last; ++ind) {
            if (i == static_cast<size_type>(*ind))
                break;
        }

        if (ind == last) {
            for (size_type j=0; j<nc_; j++)        
                data_[offset(c, j)] = std::move(old.data_[old.offset(i, j)]);
            c++;
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator InputIt>
typename nct::Array2D<T, Alloc>::iterator
    nct::Array2D<T, Alloc>::insertColumn(size_type column, InputIt first, InputIt last)
{
    if (column > nc_)
        throw IndexOutOfRangeException("row", SOURCE_INFO);

    if (static_cast<size_type>(last-first) != nr_)
        throw RangeException("first, last", SOURCE_INFO);

    // Move old data and resize array.
    nct::Array2D<T, Alloc> old(std::move(*this));
    resize(old.nr_, old.nc_ + 1);
    
    // Fill array.
    auto x = first;
    for (size_type i=0; i<nr_; i++, ++x) {
        for (size_type j=0; j<column; j++)    
            data_[offset(i, j)] = std::move(old.data_[old.offset(i, j)]);
        
        data_[offset(i, column)] = *x;
    
        for (size_type j=(column+1); j<nc_; j++)        
            data_[offset(i, j)] = std::move(old.data_[old.offset(i, j - 1)]);
    }

    return beginColumn(column);
}    

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
typename nct::Array2D<T, Alloc>::iterator
    nct::Array2D<T, Alloc>::insertColumn(size_type column, std::initializer_list<value_type> il)
{
    if (column > nc_)
        throw IndexOutOfRangeException("row", SOURCE_INFO);

    if (il.size() != nr_)
        throw ArgumentException("il", exc_bad_initializer_list_size, SOURCE_INFO);

    return insertColumn(column, std::begin(il), std::end(il));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
typename nct::Array2D<T, Alloc>::iterator
nct::Array2D<T, Alloc>::insertColumn(size_type column, const Array<T, Alloc>& data)
{
    if (column > nc_)
        throw IndexOutOfRangeException("row", SOURCE_INFO);

    if (data.size() != nr_)
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    return insertColumn(column, std::begin(data), std::end(data));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
typename nct::Array2D<T, Alloc>::iterator
    nct::Array2D<T, Alloc>::eraseColumn(size_type column)
{
    if (column >= nc_)
        throw IndexOutOfRangeException("column", SOURCE_INFO);

    // Move old data and resize array.
    nct::Array2D<T, Alloc> old(std::move(*this));
    resize(old.nr_, old.nc_ - 1);
    
    // Fill array.
    for (size_type i=0; i<nr_; i++) {
        for (size_type j=0; j<column; j++)        
            data_[offset(i, j)] = std::move(old.data_[old.offset(i, j)]);
    
        for (size_type j=column; j<nc_; j++)        
            data_[offset(i, j)] = std::move(old.data_[old.offset(i, j + 1)]);
    }

    if (column == nc_)
        return iterator();
    return beginColumn(column);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
typename nct::Array2D<T, Alloc>::iterator
nct::Array2D<T, Alloc>::insertColumns(size_type column, const Array2D<T, Alloc>& data)
{
    if (column > nc_)
        throw IndexOutOfRangeException("column", SOURCE_INFO);

    if (data.nr_ != nr_)
        throw ArgumentException("data", exc_bad_array_size, SOURCE_INFO);

    // Move old data and resize array.
    auto nnc = data.columns();
    nct::Array2D<T, Alloc> old(std::move(*this));
    resize(old.nr_, old.nc_ + nnc);
    
    // Fill array.
    for (size_type i=0; i<nr_; i++) {
        for (size_type j=0; j<column; j++)        
            data_[offset(i, j)] = std::move(old.data_[old.offset(i, j)]);
    
        for (size_type j=column; j<(column+nnc); j++)        
            data_[offset(i, j)] = data.data_[data.offset(i, j - column)];
    
        for (size_type j=(column+nnc); j<nc_; j++)        
            data_[offset(i, j)] = std::move(old.data_[old.offset(i, j - nnc)]);
    }

    return beginColumn(column);
}        

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
typename nct::Array2D<T, Alloc>::iterator
nct::Array2D<T, Alloc>::eraseColumns(size_type first, size_type last)
{
    if (first >= nc_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nc_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    // Move old data and resize array.
    auto nnc = last - first + 1;
    nct::Array2D<T, Alloc> old(std::move(*this));
    resize(old.nr_, old.nc_ - nnc);
    
    // Fill array.
    for (size_type i=0; i<nr_; i++) {
        for (size_type j=0; j<first; j++)        
            data_[offset(i, j)] = std::move(old.data_[old.offset(i, j)]);
        
        for (size_type j=first; j<nc_; j++)        
            data_[offset(i, j)] = std::move(old.data_[old.offset(i, j + nnc)]);
    }

    if (first == nc_)
        return iterator();
    return beginColumn(first);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
void nct::Array2D<T, Alloc>::eraseColumns(IndexIt first, IndexIt last)
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    size_type nnc = 0;
    for (auto ind1 = first; ind1 != last; ++ind1) {
        if (static_cast<size_type>(*ind1) >= nc_)
            throw ArgumentException("first, last", exc_indices_out_of_range, SOURCE_INFO);

        auto ind2 = first;
        for (; ind2 != ind1; ++ind2) {
            if (static_cast<size_type>(*ind1) == static_cast<size_type>(*ind2))
                break;
        }
        
        nnc += (ind2 == ind1);
    }

    // Move old data and resize array.
    nct::Array2D<T, Alloc> old(std::move(*this));
    resize(old.nr_, old.nc_ - nnc);
    
    // Fill array.
    size_type c = 0;
    for (size_type j=0; j<old.nc_; j++) {
        auto ind = first;
        for (; ind != last; ++ind) {
            if (j == static_cast<size_type>(*ind))
                break;
        }

        if (ind == last) {
            for (size_type i=0; i<nr_; i++)
                data_[offset(i, c)] = std::move(old.data_[old.offset(i, j)]);
            c++;
        }        
    }
}

//=================================================================================================================
//        DATA SELECTION
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array<T, Alloc> nct::Array2D<T, Alloc>::rowElements(size_type row) const
{
    if (row >= nr_)
        throw IndexOutOfRangeException("row", SOURCE_INFO);

    Array<T, Alloc> selData(nc_);
    for (size_type j = 0; j<nc_; j++)
        selData[j] = data_[offset(row, j)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array<T, Alloc> nct::Array2D<T, Alloc>::columnElements(size_type column) const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    if (column >= nc_)
        throw IndexOutOfRangeException("column", SOURCE_INFO);

    Array<T, Alloc> selData(nr_);
    for (size_type i = 0; i<nr_; i++)
        selData[i] = data_[offset(i, column)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array<T, Alloc> nct::Array2D<T, Alloc>::selectRange(
    size_type first, size_type last) const
{
    if (last<first)
        throw RangeException("first, last", SOURCE_INFO);

    if (first >= n_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= n_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);
    
    auto nItems = last-first+1;
    Array<T, Alloc> selData(nItems);
    for (size_type i=0; i<nItems; i++)
        selData[i] = data_[i+first]; 

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline nct::Array<T, Alloc> nct::Array2D<T, Alloc>::selectRange(
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
nct::Array<T, Alloc> nct::Array2D<T, Alloc>::selectData(
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
nct::Array<T, Alloc> nct::Array2D<T, Alloc>::selectData(
    const Array<size_type, AllocU>& indices) const
{
    return selectData(std::begin(indices), std::end(indices));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::selectSubArray(
    size_type firstRow, size_type lastRow,
    size_type firstCol, size_type lastCol) const
{
    if (lastRow<firstRow)
        throw RangeException("firstRow, lastRow", SOURCE_INFO);

    if (lastCol<firstCol)
        throw RangeException("firstCol, lastCol", SOURCE_INFO);

    if (lastRow >= nr_)
        throw IndexOutOfRangeException("lastRow", SOURCE_INFO);

    if (lastCol >= nc_)
        throw IndexOutOfRangeException("lastCol", SOURCE_INFO);

    size_type nNewRows = lastRow - firstRow + 1;
    size_type nNewCols = lastCol - firstCol + 1;
    Array2D<T, Alloc> selData(nNewRows, nNewCols);
    for (size_type i = 0; i<nNewRows; i++)
        for (size_type j = 0; j<nNewCols; j++)
            selData.data_[selData.offset(i, j)] = data_[offset(i + firstRow, j + firstCol)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
template<std::random_access_iterator RowIndexIt, std::random_access_iterator ColumnIndexIt>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::selectIndices(
    RowIndexIt firstRow, RowIndexIt lastRow,
    ColumnIndexIt firstCol, ColumnIndexIt lastCol) const
{
    if (lastRow < firstRow)
        throw RangeException("firstRow, lastRow", SOURCE_INFO);

    if (lastCol < firstCol)
        throw RangeException("firstCol, lastCol", SOURCE_INFO);

    auto nnr = lastRow - firstRow;
    auto nnc = lastCol - firstCol;

    for (auto r = firstRow; r!=lastRow; ++r) {
        if (static_cast<size_type>(*r) >= nr_)
            throw IndexOutOfRangeException("firstRow, lastRow", SOURCE_INFO);
    }

    for (auto c = firstCol; c!=lastCol; ++c) {
        if (static_cast<size_type>(*c) >= nc_)
            throw IndexOutOfRangeException("firstCol, lastCol", SOURCE_INFO);
    }
        
    Array2D<T, Alloc> selData(nnr, nnc);
    size_type i = 0;
    for (auto r = firstRow; r!=lastRow; ++r, ++i) {
        size_type j = 0;
        for (auto c = firstCol; c!=lastCol; ++c, ++j)
            selData.data_[selData.offset(i, j)] = data_[offset(static_cast<size_type>(*r),
            static_cast<size_type>(*c))];
    }

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::selectIndices(
    const Array<size_type, AllocU>& rows,
    const Array<size_type, AllocU>& columns) const
{
    return selectIndices(std::begin(rows), std::end(rows), 
        std::begin(columns), std::end(columns));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::selectRow(size_type row) const
{
    if (row >= nr_)
        throw IndexOutOfRangeException("row", SOURCE_INFO);

    Array2D<T, Alloc> selData(1, nc_);
    for (size_type j=0; j<nc_; j++)
        selData[j] = data_[offset(row, j)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::selectRangeOfRows(
    size_type first, size_type last) const
{
    if (first >= nr_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nr_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    auto nnr = last - first + 1;
    Array2D<T, Alloc> selData(nnr, nc_);
    for (size_type i=0; i<nnr; i++)
        for (size_type j=0; j<nc_; j++)
            selData.data_[selData.offset(i, j)] = data_[offset(i + first, j)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::selectRows(
    IndexIt first, IndexIt last) const
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    auto nnr = last - first;
    for (auto r = first; r != last; ++r) {
        if (static_cast<size_type>(*r) >= nr_)
            throw IndexOutOfRangeException("first, last", SOURCE_INFO);
    }
                
    Array2D<T, Alloc> selData(nnr, nc_);
    size_type i = 0;
    for (auto r = first; r != last; ++r, ++i)
        for (size_type j = 0; j < nc_; j++)
            selData.data_[selData.offset(i, j)] = data_[offset(static_cast<size_type>(*r), j)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::selectRows(
    const Array<size_type, AllocU>& rows) const
{
    return selectRows(std::begin(rows), std::end(rows));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::selectColumn(size_type column) const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    if (column >= nc_)
        throw IndexOutOfRangeException("column", SOURCE_INFO);

    Array2D<T, Alloc> selData(nr_, 1);
    for (size_type i=0; i<nr_; i++)
        selData[i] = data_[offset(i, column)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::selectRangeOfColumns(
    size_type first, size_type last) const
{
    if (first >= nc_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= nc_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (first > last)
        throw RangeException("first, last", SOURCE_INFO);

    auto nnc = last - first + 1;
    Array2D<T, Alloc> selData(nr_, nnc);
    for (size_type i=0; i<nr_; i++)
        for (size_type j=0; j<nnc; j++)
            selData.data_[selData.offset(i, j)] = data_[offset(i, j + first)];

    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::selectColumns(
    IndexIt first, IndexIt last) const
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    auto nnc = last - first;
    for (auto c = first; c!=last; ++c) {
        if (static_cast<size_type>(*c) >= nc_)
            throw IndexOutOfRangeException("first, last", SOURCE_INFO);
    }
        
    Array2D<T, Alloc> selData(nr_, nnc);
    for (size_type i=0; i<nr_; i++) {
        size_type j = 0;
        for (auto c = first; c!=last; ++c, ++j)
            selData.data_[selData.offset(i, j)] = data_[offset(i, static_cast<size_type>(*c))];
    }


    return selData;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::selectColumns(
    const Array<size_type, AllocU>& columns) const
{
    return selectColumns(std::begin(columns), std::end(columns));
}

//=================================================================================================================
//        CIRCULAR SHIFTS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::circularRowShift(
    difference_type i0) const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array2D<T, Alloc> res(nr_, nc_);
    for (difference_type i=0; i<static_cast<difference_type>(nr_); i++) {
        difference_type off = i+i0;            
        while (off<0)
            off+=nr_;
        off %= nr_;
        for (difference_type j=0; j<static_cast<difference_type>(nc_); j++)        
            res.data_[offset(i, j)] = data_[offset(off, j)];
    }

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::circularColumnShift(difference_type j0) const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array2D<T, Alloc> res(nr_, nc_);
    for (difference_type j=0; j<static_cast<difference_type>(nc_); j++) {
        difference_type off = j + j0;
        while (off<0)
            off += nc_;
        off %= nc_;

        for (difference_type i=0; i<static_cast<difference_type>(nr_); i++)                    
            res.data_[res.offset(i, j)] = data_[offset(i, off)];
    }

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::circularShift(
    difference_type i0, difference_type j0) const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array2D<T, Alloc> res(nr_, nc_);
    for (difference_type i=0; i<static_cast<difference_type>(nr_); i++) {
        difference_type off1 = i+i0;            
        while (off1<0)
            off1+=nr_;
        off1 %= nr_;

        for (difference_type j=0; j<static_cast<difference_type>(nc_); j++) {            
            difference_type off2 = j+j0;
            while (off2<0)
                off2+=nc_;
            off2 %= nc_;

            res.data_[res.offset(i, j)] = data_[offset(off1, off2)];
        }
    }
    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::circularShift() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array2D<T, Alloc> res(nr_, nc_);
    size_type rowsC = (nr_ + 1) / 2;        
    size_type columnsC = (nc_ + 1) / 2;    

    for (difference_type i=0; i<static_cast<difference_type>(nr_); i++)
        for (difference_type j=0; j<static_cast<difference_type>(nc_); j++)
            res.data_[res.offset(i, j)] = data_[offset((i + rowsC) % nr_, (j + columnsC) % nc_)];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::circularInvShift() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array2D<T, Alloc> res(nr_, nc_);
    size_type rowsC = (nr_ + 1) / 2;            
    size_type columnsC = (nc_ + 1) / 2;        
    
    for (size_type i=0; i<nr_; i++) {    
        auto iPos = (i < rowsC) ? (nr_ + i - rowsC) : (i - rowsC);
        for (size_type j=0; j<nc_; j++) {
            auto jPos = (j < columnsC) ? (nc_ + j - columnsC) : (j - columnsC);
            res.data_[res.offset(i, j)] = data_[offset(iPos, jPos)];
        }
    }

    return res;
}

//=================================================================================================================
//        NUMERICAL OPERATIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Addable<T>
typename nct::Array2D<T, Alloc>::value_type nct::Array2D<T, Alloc>::trace() const
{
    if (nr_ != nc_)
        throw ConfigurationException(exc_non_square_matrix, SOURCE_INFO);
    T tmp = data_[offset(0, 0)];
    for (size_type i = 1; i < nr_; i++)
        tmp += data_[offset(i, i)];
    return tmp;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Addable<T>
typename nct::Array2D<T, Alloc>::value_type nct::Array2D<T, Alloc>::sum() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    T r = data_[0];

    for (size_type i=1; i<n_; i++)
        r += data_[i];

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Arithmetic<T>
double nct::Array2D<T, Alloc>::castSum() const
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
typename nct::Array2D<T, Alloc>::value_type nct::Array2D<T, Alloc>::squaredNorm() const
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
double nct::Array2D<T, Alloc>::euclideanNorm() const
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
double nct::Array2D<T, Alloc>::lpNorm(double p) const
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
double nct::Array2D<T, Alloc>::infinityNorm() const
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
double nct::Array2D<T, Alloc>::mean() const
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
double nct::Array2D<T, Alloc>::variance() const
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
typename nct::Array2D<T, Alloc>::value_type nct::Array2D<T, Alloc>::max() const
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
typename nct::Array2D<T, Alloc>::value_type nct::Array2D<T, Alloc>::min() const
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
template<typename T, typename Alloc> template<typename> requires std::totally_ordered<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::minCol() const
{
    if (nr_ < 1)
        throw ConfigurationException(exc_bad_number_of_rows, SOURCE_INFO);

    Array2D<T, Alloc> newArray(1, nc_);
    for (size_type j = 0; j<nc_; j++) {
        newArray[j] = data_[offset(0,j)];
        for (size_type i = 1; i<nr_; i++) {
            if (newArray[j] > data_[offset(i,j)])
                newArray[j] = data_[offset(i,j)];        
        }
    }
    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::totally_ordered<T>
typename nct::Array2D<T, Alloc>::value_type
nct::Array2D<T, Alloc>::minCol(size_type column) const
{
    if (column >= nc_)
        throw IndexOutOfRangeException(SOURCE_INFO);

    if (nr_<1)
        throw EmptyArrayException(SOURCE_INFO);        

    T res = data_[offset(0, column)]; 
    for (size_type i=1; i<nr_; i++) {
        if (res > data_[offset(i, column)])
            res = data_[offset(i, column)];
    }
    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::totally_ordered<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::minRow() const
{
    if (nc_ < 1)
        throw ConfigurationException(exc_bad_number_of_columns, SOURCE_INFO);

    Array2D<T, Alloc> newArray(nr_, 1);
    for (size_type i = 0; i<nr_; i++) {
        newArray[i] = data_[offset(i,0)];
        for (size_type j = 1; j<nc_; j++) {
            if (newArray[i] > data_[offset(i,j)])
                newArray[i] = data_[offset(i,j)];        
        }
    }
    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::totally_ordered<T>
typename nct::Array2D<T, Alloc>::value_type 
nct::Array2D<T, Alloc>::minRow(size_type row) const
{
    if (row >= nr_)
        throw IndexOutOfRangeException(SOURCE_INFO);

    if (nc_<1)
        throw EmptyArrayException(SOURCE_INFO);        

    T res = data_[offset(row, 0)]; 
    for (size_type i=1; i<nc_; i++) {
        if (res > data_[offset(row, i)])
            res = data_[offset(row, i)];
    }
    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::totally_ordered<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::maxCol() const
{
    if (nr_ < 1)
        throw ConfigurationException(exc_non_square_matrix, SOURCE_INFO);    

    Array2D<T, Alloc> newArray(1, nc_);
    for (size_type j = 0; j<nc_; j++) {
        newArray[j] = data_[offset(0,j)];
        for (size_type i = 1; i<nr_; i++) {
            if (newArray[j] < data_[offset(i,j)])
                newArray[j] = data_[offset(i,j)];        
        }
    }
    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::totally_ordered<T>
typename nct::Array2D<T, Alloc>::value_type nct::Array2D<T, Alloc>::maxCol(
    size_type column) const
{
    if (column >= nc_)
        throw IndexOutOfRangeException(SOURCE_INFO);

    if (nr_<1)
        throw EmptyArrayException(SOURCE_INFO);        

    T res = data_[offset(0, column)]; 
    for (size_type i=1; i<nr_; i++) {
        if (res < data_[offset(i, column)])
            res = data_[offset(i, column)];
    }
    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::totally_ordered<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::maxRow() const
{
    if (nc_ < 1)
        throw ConfigurationException(exc_bad_number_of_columns, SOURCE_INFO);

    Array2D<T, Alloc> newArray(nr_, 1);
    for (size_type i = 0; i<nr_; i++) {
        newArray[i] = data_[offset(i,0)];
        for (size_type j = 1; j<nc_; j++) {
            if (newArray[i] < data_[offset(i,j)])
                newArray[i] = data_[offset(i,j)];        
        }
    }
    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::totally_ordered<T>
typename nct::Array2D<T, Alloc>::value_type nct::Array2D<T, Alloc>::maxRow(
    size_type row) const
{
    if (row >= nr_)
        throw IndexOutOfRangeException(SOURCE_INFO);

    if (nc_<1)
        throw EmptyArrayException(SOURCE_INFO);        

    T res = data_[offset(row, 0)]; 
    for (size_type i=1; i<nc_; i++) {
        if (res < data_[offset(row, i)])
            res = data_[offset(row, i)];
    }
    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::sumCol() const
{
    if (nr_ < 1)
        throw ConfigurationException(exc_non_square_matrix, SOURCE_INFO);    

    Array2D<T, Alloc> newArray(1, nc_);
    for (size_type j = 0; j<nc_; j++) {
        newArray[j] = 0;
        for (size_type i = 0; i<nr_; i++)        
            newArray[j]+=data_[offset(i,j)];
    }
    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
typename nct::Array2D<T, Alloc>::value_type nct::Array2D<T, Alloc>::sumCol(
    size_type column) const
{
    if (column >= nc_)
        throw IndexOutOfRangeException(SOURCE_INFO);

    if (nr_<1)
        throw EmptyArrayException(SOURCE_INFO);        

    T res = 0; 
    for (size_type i=0; i<nr_; i++)
        res+=data_[offset(i, column)];
    
    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::sumRow() const
{
    if (nc_ < 1)
        throw ConfigurationException(exc_bad_number_of_columns, SOURCE_INFO);

    Array2D<T, Alloc> newArray(nr_, 1);
    for (size_type i = 0; i<nr_; i++) {
        newArray[i] = 0;
        for (size_type j = 0; j<nc_; j++)    
            newArray[i]+=data_[offset(i,j)];        
    }
    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
typename nct::Array2D<T, Alloc>::value_type nct::Array2D<T, Alloc>::sumRow(
    size_type row) const
{
    if (row >= nr_)
        throw IndexOutOfRangeException(SOURCE_INFO);

    if (nc_<1)
        throw EmptyArrayException(SOURCE_INFO);        

    T res = 0; 
    for (size_type i=0; i<nc_; i++)
        res += data_[offset(row, i)];
    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU> requires nct::Arithmetic<T>
nct::Array2D<double, AllocU> nct::Array2D<T, Alloc>::meanCol() const
{
    if (nr_ < 1)
        throw ConfigurationException(exc_non_square_matrix, SOURCE_INFO);    

    Array2D<double, AllocU> newArray(1, nc_);
    for (size_type j = 0; j<nc_; j++) {
        newArray[j] = 0;
        for (size_type i = 0; i<nr_; i++)        
            newArray[j]+=data_[offset(i,j)];
        newArray[j]/=nr_;
    }
    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Arithmetic<T>
double nct::Array2D<T, Alloc>::meanCol(size_type column) const
{
    if (column >= nc_)
        throw IndexOutOfRangeException(SOURCE_INFO);

    if (nr_<1)
        throw EmptyArrayException(SOURCE_INFO);        

    T res = 0; 
    for (size_type i=0; i<nr_; i++)
        res+=data_[offset(i, column)];    
    return static_cast<double>(res) / static_cast<double>(nr_);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU> requires nct::Arithmetic<T>
nct::Array2D<double, AllocU> nct::Array2D<T, Alloc>::meanRow() const
{
    if (nc_ < 1)
        throw ConfigurationException(exc_bad_number_of_columns, SOURCE_INFO);

    Array2D<double, AllocU> newArray(nr_, 1);
    for (size_type i = 0; i<nr_; i++) {
        newArray[i] = 0;
        for (size_type j = 0; j<nc_; j++)    
            newArray[i]+=data_[offset(i,j)];
        newArray[i]/=nc_;
    }
    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Arithmetic<T>
double nct::Array2D<T, Alloc>::meanRow(size_type row) const
{
    if (row >= nr_)
        throw IndexOutOfRangeException(SOURCE_INFO);

    if (nc_<1)
        throw EmptyArrayException(SOURCE_INFO);        

    T res = 0; 
    for (size_type i=0; i<nc_; i++)
        res += data_[offset(row, i)];
    return static_cast<double>(res) / static_cast<double>(nc_);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU> requires nct::Arithmetic<T>
nct::Array2D<double, AllocU> nct::Array2D<T, Alloc>::varCol() const
{
    if (nc_ < 1 || nr_ < 2)
        throw ConfigurationException(exc_bad_array_dimensions, SOURCE_INFO);

    Array2D<double, AllocU> newArray(1, nc_);
    Array2D<double, AllocU> vMean = meanCol();

    for (size_type j = 0; j<nc_; j++) {
        newArray[j] = 0;
        for (size_type i = 0; i<nr_; i++)        
            newArray[j]+=(data_[offset(i,j)] - vMean[j])*(data_[offset(i,j)] - vMean[j]);
        newArray[j]/=(nr_-1);                
    }

    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Arithmetic<T>
double nct::Array2D<T, Alloc>::varCol(size_type column) const
{
    if (column >= nc_)
        throw IndexOutOfRangeException(SOURCE_INFO);

    if (nr_<2)
        throw ConfigurationException(exc_bad_number_of_rows, SOURCE_INFO);        

    double res = 0; 
    double meanVal = meanCol(column); 
    for (size_type i=0; i<nr_; i++)
        res += (data_[offset(i, column)] - meanVal)*(data_[offset(i, column)] - meanVal);        
    return res/(nr_-1.0);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU> requires nct::Arithmetic<T>
nct::Array2D<double, AllocU> nct::Array2D<T, Alloc>::varRow() const
{
    if (nc_ < 2 || nr_ < 1)
        throw ConfigurationException(exc_bad_array_dimensions, SOURCE_INFO);

    Array2D<double, AllocU> newArray(nr_, 1);
    Array2D<double, AllocU> vMean = meanRow();

    for (size_type i = 0; i<nr_; i++) {
        newArray[i] = 0;
        for (size_type j = 0; j<nc_; j++)        
            newArray[i]+=(data_[offset(i,j)] - vMean[i])*(data_[offset(i,j)] - vMean[i]);
        newArray[i]/=(nc_-1);                
    }
    return newArray;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Arithmetic<T>
double nct::Array2D<T, Alloc>::varRow(size_type row) const
{
    if (row >= nr_)
        throw IndexOutOfRangeException(SOURCE_INFO);

    if (nc_<2)
        throw ConfigurationException(exc_bad_number_of_columns, SOURCE_INFO);        

    double res = 0; 
    double meanVal = meanRow(row); 
    for (size_type i=0; i<nc_; i++)
        res += (data_[offset(row, i)] - meanVal)*(data_[offset(row, i)] - meanVal);        
    return res/(nc_-1.0);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU> requires nct::Arithmetic<T>
nct::Array2D<double, AllocU> nct::Array2D<T, Alloc>::covariance() const
{
    if (nc_ < 1 || nr_ < 2)
        throw ConfigurationException(exc_bad_array_dimensions, SOURCE_INFO);

    // Means.
    Array2D<double, AllocU> vMean(nc_, 1, 0);
    for (size_type i = 0; i<nr_; i++)
        for (size_type j = 0; j<nc_; j++)
            vMean[j]+=data_[offset(i,j)];
    vMean/=static_cast<double>(nr_);
    
    // Covariances.
    Array2D<double, AllocU> cov(nc_, nc_);
    for (size_type v1 = 0; v1<nc_; v1++) {
        for (size_type v2 = v1; v2<nc_; v2++) {
            cov(v1,v2) = 0;
            for (size_type i = 0; i<nr_; i++)        
                cov(v1,v2)+=(data_[offset(i,v1)] - vMean[v1])*(data_[offset(i,v2)] - vMean[v2]);
            cov(v1,v2)/=(nr_-1);
            cov(v2,v1) = cov(v1,v2);
        }
    }

    return cov;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename AllocU> requires nct::Arithmetic<T>
nct::Array2D<double, AllocU> nct::Array2D<T, Alloc>::regularizedCovariance() const
{
    if (nc_ < 1 || nr_ < 2)
        throw ConfigurationException(exc_bad_array_dimensions, SOURCE_INFO);

    //  Estimate sample covariance matrix.
    auto mx = meanCol();
    auto s = covariance();

    //  Estimate structured covariance matrix.
    Array2D<double, AllocU> sst(nc_, nc_);

    for (size_type i = 0; i < nc_; i++)
        sst(i, i) = s(i, i);

    double r = 0;
    for (size_type i = 0; i < (nc_ - 1); i++) {
        for (size_type j = i + 1; j < nc_; j++) {
            auto tmp = std::sqrt(s(i, i) * s(j, j));
            r += s(i, j) / tmp;
            sst(i, j) = tmp;
        }
    }
    r /= (static_cast<double>(nc_) - 1.)*static_cast<double>(nc_) / 2.0;

    for (size_type i = 0; i < (nc_ - 1); i++) {
        for (size_type j = i + 1; j < nc_; j++) {
            sst(i, j) *= r;
            sst(j, i) = sst(i, j);
        }
    }

    // Estimate regularization parameter.
    Array2D<double, AllocU> pp(nc_, nc_, 0.0);
    for (size_type i = 0; i < nc_; i++) {
        for (size_type j = 0; j < nc_; j++) {
            double acc = 0;
            for (size_type k = 0; k < nr_; k++) {
                auto tmp = (at(k, i) - mx[i])*(at(k, j) - mx[j]) - s(i, j);
                acc += tmp*tmp;
            }
            acc /= static_cast<double>(nr_);
            pp(i, j) = acc;
        }
    }

    double pi = pp.sum();

    Array2D<double, AllocU> di(nc_, nc_, 0.0);
    Array2D<double, AllocU> dj(nc_, nc_, 0.0);
    for (size_type i = 0; i < nc_; i++) {
        for (size_type j = 0; j < nc_; j++) {
            double acci = 0;
            double accj = 0;
            for (size_type k = 0; k < nr_; k++) {
                auto tmpi = at(k, i) - mx[i];
                auto tmpj = at(k, j) - mx[j];
                acci += (tmpi*tmpi - s(i, i)) * ((at(k, i) - mx[i])*(at(k, j) - mx[j]) - s(i, j));
                accj += (tmpj*tmpj - s(j, j)) * ((at(k, i) - mx[i])*(at(k, j) - mx[j]) - s(i, j));
            }

            acci /= static_cast<double>(nr_);
            di(i, j) = acci;

            accj /= static_cast<double>(nr_);
            dj(i, j) = accj;
        }
    }

    double rr = 0;
    for (size_type i = 0; i < nc_; i++)
        rr += pp[i];

    for (size_type i = 0; i < nc_; i++) {
        for (size_type j = 0; j < nc_; j++) {
            if (i == j)
                continue;

            rr += (r / 2.)*(di(i, j)*std::sqrt(s(j, j) / s(i, i)) +
                dj(i, j)*std::sqrt(s(i, i) / s(j, j)));
        }
    }

    double g = 0;
    for (size_type i = 0; i < nc_; i++) {
        for (size_type j = 0; j < nc_; j++) {
            auto tmp = s(i, j) - sst(i, j);
            g += tmp*tmp;
        }
    }

    auto kappa = (pi - rr) / g;

    double delta = kappa / static_cast<double>(nr_);
    if (delta > 1.0)
        delta = 1.0;
    if (delta < 0.0)
        delta = 0.0;
    
    // Return final matrix.
    return (1.0 - delta)*s + delta*sst;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T, typename Alloc>
 T nct::dotProduct(const Array2D<T, Alloc>& a, const Array2D<T, Alloc>& b)
{
    if ( (a.rows() != b.rows()) || (a.columns() != b.columns()) )
        throw ArgumentException("a, b", exc_arrays_of_different_dimensions, SOURCE_INFO);

    auto n = a.size();
    T temp = 0;        
    for (index_t i=0; i<n; i++)
        temp += a[i]*b[i];
    return temp;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T, typename Alloc>
nct::Array<T, Alloc> nct::matrixVectorProduct(const Array2D<T, Alloc>& m, 
    const Array<T, Alloc>& v)
{
    auto n = m.rows();
    auto p = m.columns();
    if (v.size() != p)
        throw ArgumentException("m, v", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array<T, Alloc> r(n, T(0));
    for (index_t i = 0; i < n; i++)
        for (index_t j = 0; j < p; j++)
            r[i] += m(i, j)*v[j];

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T, typename Alloc>
nct::Array2D<T, Alloc> nct::colVectorRowVectorProduct(
    const Array<T, Alloc>& c, const Array<T, Alloc>& r)
{
    auto n = c.size();
    auto m = r.size();
    
    Array2D<T, Alloc> mm(n, m);
    for (index_t i = 0; i < n; i++)
        for (index_t j = 0; j < m; j++)
            mm(i, j) = c[i]*r[j];

    return mm;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T, typename Alloc>
nct::Array2D<T, Alloc> nct::directSum(const Array2D<T, Alloc>& m, unsigned int times)
{
    auto nr = m.rows();
    auto nc = m.columns();

    Array2D<T, Alloc> res(times*nr, times*nc, T(0));

    for (unsigned int p = 0; p < times; p++)
        for (index_t i = 0; i < nr; i++)
            for (index_t j = 0; j < nc; j++)
                res(p*nr + i, p*nc + j) = m(i, j);

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T, typename Alloc>
nct::Array2D<T, Alloc> nct::directSum(const Array2D<T, Alloc>& left, const Array2D<T, Alloc>& right)
{
    auto nr1 = left.rows();
    auto nc1 = left.columns();
    
    auto nr2 = right.rows();
    auto nc2 = right.columns();

    Array2D<T, Alloc> res(nr1+nr2, nc1+nc2, T(0));

    for (index_t i = 0; i < nr1; i++)
        for (index_t j = 0; j < nc1; j++)
            res(i, j) = left(i, j);

    for (index_t i = 0; i < nr2; i++)
        for (index_t j = 0; j < nc2; j++)
            res(i + nr1, j + nc1) = right(i, j);

    return res;

}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T, typename Alloc>
nct::Array2D<T, Alloc> nct::kroneckerSum(const Array2D<T, Alloc>& left, const Array2D<T, Alloc>& right)
{
    if (left.rows() != left.columns())
        throw ArgumentException("left", exc_non_square_matrix, SOURCE_INFO);

    if (right.rows() != right.columns())
        throw ArgumentException("right", exc_non_square_matrix, SOURCE_INFO);

    auto n = left.rows();
    auto m = right.rows();

    Array2D<T, Alloc> res(n * m, n * m, T(0));
    for (index_t i = 0; i < n; i++)
        for (index_t j = 0; j < n; j++)
            for (index_t k = 0; k < m; k++)
                res(i*m + k, j*m + k) = left(i, j);


    for (index_t p = 0; p < n; p++)
        for (index_t i = 0; i < m; i++)
            for (index_t j = 0; j < m; j++)
                res(p*m + i, p*m + j) += right(i, j);


    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T, typename Alloc>
nct::Array2D<T, Alloc> nct::kroneckerProduct(const Array2D<T, Alloc>& left, const Array2D<T, Alloc>& right)
{
    auto nr1 = left.rows();
    auto nc1 = left.columns();

    auto nr2 = right.rows();
    auto nc2 = right.columns();

    Array2D<T, Alloc> res(nr1 * nr2, nc1 * nc2, T(0));

    for (index_t i = 0; i < nr1; i++)
        for (index_t j = 0; j < nc1; j++)
            for (index_t k = 0; k < nr2; k++)
                for (index_t l = 0; l < nc2; l++)
                    res(i*nr2 + k , j*nc2 + l) = left(i, j)*right(k, l);

    return res;
}

//=================================================================================================================
//        SPECIAL ARRAYS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::equality_comparable<T>
bool nct::Array2D<T, Alloc>::isUpperTriangular() const
{
    if (nr_ != nc_)
        return false;
    
    if (n_ == 0)
        return false;

    for (size_type i=1; i<nr_; i++) {            
        for (size_type j=0; j<i; j++) {
            if (data_[offset(i,j)] != T(0))
                return false;
        }
    }
    return true;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::equality_comparable<T>
bool nct::Array2D<T, Alloc>::isLowerTriangular() const
{
    if (nr_ != nc_)
        return false;
    
    if (n_ == 0)
        return false;

    for (size_type i=0; i<nr_-1; i++) {
        for (size_type j=i+1; j<nc_; j++) {
            if (data_[offset(i,j)] != T(0))
                return false;
        }
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::equality_comparable<T>
bool nct::Array2D<T, Alloc>::isSymmetric() const
{
    if (nr_ != nc_)
        return false;

    if (n_ == 0)
        return false;

    for (size_type i=0; i<nr_; i++) {
        for (size_type j=0; j<i; j++) {
            if (data_[offset(i,j)] != data_[offset(j,i)])
                return false;                    
        }
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::equality_comparable<T>
bool nct::Array2D<T, Alloc>::isDiagonal() const
{
    if (nr_ != nc_)
        return false;

    if (n_ == 0)
        return false;

    for (size_type i=0; i<nr_; i++) {
        for (size_type j=0; j<nc_; j++) {
            if ( (data_[offset(i,j)] != T(0)) && (i!=j) )
                return false;
        }
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::equality_comparable<T>
bool nct::Array2D<T, Alloc>::isScalar() const
{
    if (nr_ != nc_)
        return false;

    if (n_ == 0)
        return false;

    if (isDiagonal() == false)
        return false;
        
    for (size_type i=1; i<nr_; i++)
        if (data_[offset(i,i)] != data_[offset(i-1,i-1)])
            return false;

    return true;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::equality_comparable<T>
bool nct::Array2D<T, Alloc>::isToeplitz() const
{
    if (nr_ != nc_)
        return false;

    if (n_ == 0)
        return false;

    for (size_type i=1; i<nr_; i++)
        for (size_type j=1; j<nc_; j++)
            if ( data_[offset(i,j)] != data_[offset(i-1,j-1)] )
                return false;

    return true;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::equality_comparable<T>
bool nct::Array2D<T, Alloc>::isHankel() const
{
    if (nr_ != nc_)
        return false;

    if (n_ == 0)
        return false;

    for (size_type i=1; i<nr_; i++)
        for (size_type j=0; j<(nc_-1); j++)
            if ( data_[offset(i,j)] != data_[offset(i-1,j+1)] )
                return false;

    return true;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::equality_comparable<T>
bool nct::Array2D<T, Alloc>::isCirculant() const
{
    if (nr_ != nc_)
        return false;

    if (n_ == 0)
        return false;

    difference_type t=0;
    for (size_type i=0; i<nr_; i++) {
        for (size_type j=1; j<nc_; j++) {
            t = static_cast<difference_type>(i)-static_cast<difference_type>(j);
            if (t<0)
                t+=nr_;
            if ( data_[offset(i,j)] != data_[offset(t,0)] )
                return false;
        }
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::constant(
    size_type rows, size_type columns, const_reference t)
{
    return nct::Array2D<T, Alloc>(rows, columns, t);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::zeros(
    size_type rows, size_type columns)
{
    return nct::Array2D<T, Alloc>(rows, columns, 0);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::ones(
    size_type rows, size_type columns)
{
    return nct::Array2D<T, Alloc>(rows, columns, 1);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::eye(size_type n)
{
    nct::Array2D<T, Alloc> identity(n, n, 0);
    for (size_type j=0; j<n; j++)
        identity(j,j) = static_cast<T>(1);            
    return identity;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::eye(size_type rows, size_type columns)
{
    nct::Array2D<T, Alloc> identity(rows, columns, 0);
    auto n_ = rows<columns? rows:columns;

    for (size_type j=0; j<n_; j++)
        identity(j,j) = static_cast<T>(1);            
    return identity;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU> requires std::convertible_to<U, T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::diag(const Array<U, AllocU>& w)
{
    size_type n_ = w.size();        
    Array2D<T, Alloc>data_(n_, n_, 0);
    for (size_type j=0; j<n_; j++)
        data_(j,j) = w[j];        
    return data_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU> requires std::convertible_to<U, T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::diag(
    size_type rows, size_type columns, const Array<U, AllocU>& w)
{
    Array2D<T, Alloc>data_(rows, columns, 0);

    size_type n_ = w.size();        
    if (n_ > rows)
        n_ = rows;

    if (n_ > columns)
        n_ = columns;

    for (size_type j=0; j<n_; j++)
        data_(j,j) = w[j];    

    return data_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU> requires std::convertible_to<U, T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::toeplitz(
    const Array<U, AllocU>& r)
{
    size_type n_ = r.size();
    Array2D<T, Alloc> t(n_, n_, 0);
    
    for (size_type j = 0; j<n_; j++)
        t(0, j) = r[j];

    for (size_type i = 1; i<n_; i++)
        t(i, 0) = r[i];

    for (size_type i = 1; i<n_; i++)
        for (size_type j = 1; j<n_; j++)
            t(i, j) = t(i-1, j-1);

    return t;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU> requires std::convertible_to<U, T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::toeplitz(
    const Array<U, AllocU>& c, const Array<U, AllocU>& r)
{
    size_type nr_ = c.size();
    size_type nc_ = r.size();

    Array2D<T, Alloc> t(nr_, nc_, 0);
    if ((nr_ == 0) && (nc_ == 0))
        return t;

    if (c[0] != r[0])
        throw ArgumentException("r, c", exc_first_element_of_arrays_different, SOURCE_INFO);

    for (size_type j = 0; j<nc_; j++)
        t(0, j) = r[j];

    for (size_type i = 1; i<nr_; i++)
        t(i, 0) = c[i];

    for (size_type i = 1; i<nr_; i++)
        for (size_type j = 1; j<nc_; j++)
            t(i, j) = t(i-1, j-1);

    return t;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU> requires std::convertible_to<U, T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::hankel(const Array<U, AllocU>& c)
{
    size_type n_ = c.size();
    Array2D<T, Alloc> h(n_, n_, 0);

    for (size_type i = 0; i<n_; i++)
        h(i, 0) = c[i];

    for (size_type j = 1; j<n_; j++)
        h(0, j) = c[j];

    for (size_type i = 1; i<n_; i++)
        for (size_type j = 1; j<(n_-i); j++)
            h(i, j) = h(i - 1, j + 1);

    return h;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU> requires std::convertible_to<U, T>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::hankel(const Array<U, AllocU>& c, 
    const Array<U, AllocU>& r)
{
    size_type nr_ = c.size();
    size_type nc_ = r.size();

    Array2D<T, Alloc> h(nr_, nc_, 0);
    if ((nr_ == 0) && (nc_ == 0))
        return h;

    if (c[nr_-1] != r[0])
        throw ArgumentException("r, c", exc_bad_hankel_arguments, SOURCE_INFO);

    for (size_type i = 0; i<nr_; i++)
        h(i, 0) = c[i];

    for (size_type j = 1; j<nc_; j++)
        h(nr_-1, j) = r[j];
    
    for (difference_type i = static_cast<difference_type>(nr_-2); i>=0; i--)
        for (size_type j = 1; j<nc_; j++)
            h(i, j) = h(i + 1, j - 1);

    return h;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::filledSquare(
    size_type rows, size_type columns,
    size_type r0, size_type c0, size_type l, const_reference val)
{
    Array2D<T, Alloc> arr(rows, columns, T());
    
    auto r1 = r0 + l;
    auto c1 = c0 + l;

    for (size_type i = r0; (i <= r1) && (i < rows); i++)
        for (size_type j = c0; (j <= c1) && (j < columns); j++)
            arr(i, j) = val;

    return arr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::filledRectangle(
    size_type rows, size_type columns,
    size_type r0, size_type c0, size_type wr, size_type wc, const_reference val)
{
    Array2D<T, Alloc> arr(rows, columns, T());

    auto r1 = r0 + wr;
    auto c1 = c0 + wc;

    for (size_type i = r0; (i <= r1) && (i < rows); i++)
        for (size_type j = c0; (j <= c1) && (j < columns); j++)
            arr(i, j) = val;

    return arr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::filledCircle(
    size_type rows, size_type columns,
    size_type r0, size_type c0, size_type r, const_reference val)
{
    Array2D<T, Alloc> arr(rows, columns, T());
    auto r2 = r*r;

    for (size_type i = 0; i < rows; i++) {
        auto dr = (i > r0) ? (i - r0) : (r0 - i);
        for (size_type j = 0; j < columns; j++) {
            auto dc = (j > c0) ? (j - c0) : (c0 - j);

            auto d2 = dr*dr + dc*dc;
            if (d2 <= r2)
                arr(i, j) = val;
        }
    }

    return arr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::filledEllipse(
    size_type rows, size_type columns,
    size_type r0, size_type c0, size_type wr, size_type wc, const_reference val)
{
    Array2D<T, Alloc> arr(rows, columns, T());
    auto wr2 = static_cast<double>(wr*wr);
    auto wc2 = static_cast<double>(wc*wc);

    for (size_type i = 0; i < rows; i++) {
        auto dr = static_cast<double>(i)-static_cast<double>(r0);
        for (size_type j = 0; j < columns; j++) {
            auto dc = static_cast<double>(j)-static_cast<double>(c0);
            auto ang = std::atan2(dc, dr);
            auto cc = std::cos(ang);
            auto ss = std::sin(ang);
            double r2 = (wr2 * wc2) / (wc2*cc*cc + wr2*ss*ss);
            auto d2 = dr*dr + dc*dc;
            if (d2 <= r2)
                arr(i, j) = val;
        }
    }

    return arr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::chessPattern(
    size_type rows, size_type columns, size_type nRowDiv, size_type nColumnDiv)
{
    Array2D<T, Alloc> arr(rows, columns, T());

    if ((nRowDiv == 0) || (nColumnDiv == 0))
        return arr;

    double xs = static_cast<double>(rows) / static_cast<double>(nRowDiv);
    double ys = static_cast<double>(columns) / static_cast<double>(nColumnDiv);
    for (size_type i = 0; i<rows; i++) {
        auto x = static_cast<size_type> (i / xs);
        for (size_type j = 0; j<columns; j++) {
            auto y = static_cast<size_type> (j / ys);
            arr(i, j) = static_cast<T>( ((x + y) % 2) == 1 );
        }
    }

    return arr;
}

//=================================================================================================================
//        ITERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::iterator nct::Array2D<T, Alloc>::begin()
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, 0);    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_iterator 
nct::Array2D<T, Alloc>::begin() const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, 0);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_iterator
nct::Array2D<T, Alloc>::cbegin() const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, 0);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::iterator nct::Array2D<T, Alloc>::end()
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, n_);    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_iterator 
nct::Array2D<T, Alloc>::end() const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, n_);    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_iterator
nct::Array2D<T, Alloc>::cend() const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, n_);    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::reverse_iterator 
nct::Array2D<T, Alloc>::rbegin()
{
    return reverse_iterator(end());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reverse_iterator
nct::Array2D<T, Alloc>::rbegin() const
{
    return const_reverse_iterator(end());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reverse_iterator 
nct::Array2D<T, Alloc>::crbegin() const
{
    return const_reverse_iterator(end());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::reverse_iterator
nct::Array2D<T, Alloc>::rend()
{
    return reverse_iterator(begin());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reverse_iterator
nct::Array2D<T, Alloc>::rend() const
{
    return const_reverse_iterator(begin());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reverse_iterator
nct::Array2D<T, Alloc>::crend() const
{
    return const_reverse_iterator(begin());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::iterator 
nct::Array2D<T, Alloc>::beginRow(size_type row)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, row, 0, IteratorShiftMode2D::RowMode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_iterator
nct::Array2D<T, Alloc>::beginRow(
    size_type row) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, row, 0, IteratorShiftMode2D::RowMode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_iterator
nct::Array2D<T, Alloc>::cbeginRow(
    size_type row) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, row, 0, IteratorShiftMode2D::RowMode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::iterator 
nct::Array2D<T, Alloc>::endRow(size_type row)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, row, nc_, IteratorShiftMode2D::RowMode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_iterator 
nct::Array2D<T, Alloc>::endRow(size_type row) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, row, nc_, IteratorShiftMode2D::RowMode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_iterator
nct::Array2D<T, Alloc>::cendRow(size_type row) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, row, nc_, IteratorShiftMode2D::RowMode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::reverse_iterator
nct::Array2D<T, Alloc>::rbeginRow(size_type row)
{
    return reverse_iterator(endRow(row));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reverse_iterator
nct::Array2D<T, Alloc>::rbeginRow(
    size_type row) const
{
    return const_reverse_iterator(endRow(row));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reverse_iterator
nct::Array2D<T, Alloc>::crbeginRow(
    size_type row) const
{
    return const_reverse_iterator(endRow(row));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::reverse_iterator
nct::Array2D<T, Alloc>::rendRow(size_type row)
{
    return reverse_iterator(beginRow(row));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reverse_iterator
nct::Array2D<T, Alloc>::rendRow(
    size_type row) const
{
    return const_reverse_iterator(beginRow(row));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reverse_iterator
nct::Array2D<T, Alloc>::crendRow(
    size_type row) const
{
    return const_reverse_iterator(beginRow(row));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::iterator
nct::Array2D<T, Alloc>::beginColumn(size_type column)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, 0, column, IteratorShiftMode2D::ColumnMode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_iterator 
nct::Array2D<T, Alloc>::beginColumn(
    size_type column) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, 0, column, IteratorShiftMode2D::ColumnMode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_iterator 
nct::Array2D<T, Alloc>::cbeginColumn(
    size_type column) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, 0, column, IteratorShiftMode2D::ColumnMode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::iterator
nct::Array2D<T, Alloc>::endColumn(size_type column)
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, nr_, column, IteratorShiftMode2D::ColumnMode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_iterator
nct::Array2D<T, Alloc>::endColumn(
    size_type column) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, nr_, column, IteratorShiftMode2D::ColumnMode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_iterator
nct::Array2D<T, Alloc>::cendColumn(
    size_type column) const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, nr_, column, IteratorShiftMode2D::ColumnMode);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::reverse_iterator
nct::Array2D<T, Alloc>::rbeginColumn(
    size_type column)
{
    return reverse_iterator(endColumn(column));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reverse_iterator
nct::Array2D<T, Alloc>::rbeginColumn(
    size_type column) const
{
    return const_reverse_iterator(endColumn(column));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reverse_iterator
nct::Array2D<T, Alloc>::crbeginColumn(
    size_type column) const
{
    return const_reverse_iterator(endColumn(column));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::reverse_iterator 
nct::Array2D<T, Alloc>::rendColumn(
    size_type column)
{
    return reverse_iterator(beginColumn(column));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reverse_iterator 
nct::Array2D<T, Alloc>::rendColumn(
    size_type column) const
{
    return const_reverse_iterator(beginColumn(column));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array2D<T, Alloc>::const_reverse_iterator
nct::Array2D<T, Alloc>::crendColumn(
    size_type column) const
{
    return const_reverse_iterator(beginColumn(column));
}

//=================================================================================================================
//        TRANSFORMATIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array2D<U, AllocU> nct::Array2D<T, Alloc>::transformData(
    const std::function<U(const_reference)>& f) const
{
    Array2D<U, AllocU> outputArray(nr_, nc_);        
    for (size_type k = 0; k<n_; k++)
        outputArray[k] = f(data_[k]);
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array2D<U, AllocU> nct::Array2D<T, Alloc>::collapseRows(
    const std::function<U(const Array<T, Alloc>&)>& f) const
{
    Array2D<U, AllocU> outputArray(nr_, 1);        
    for (size_type i = 0; i<nr_; i++)
        outputArray[i] = f(rowElements(i));
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array2D<U, AllocU> nct::Array2D<T, Alloc>::collapseRows(
    const std::function<U(const_iterator, const_iterator)>& f) const
{
    Array2D<U, AllocU> outputArray(nr_, 1);        
    for (size_type i = 0; i<nr_; i++)
        outputArray[i] = f(beginRow(i), endRow(i));
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array2D<U, AllocU> nct::Array2D<T, Alloc>::collapseColumns(
    const std::function<U(const Array<T, Alloc>&)>& f) const
{
    Array2D<U, AllocU> outputArray(1, nc_);        
    for (size_type j = 0; j<nc_; j++)
        outputArray[j] = f(columnElements(j));
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array2D<U, AllocU> nct::Array2D<T, Alloc>::collapseColumns(
    const std::function<U(const_iterator, const_iterator)>& f) const
{
    Array2D<U, AllocU> outputArray(1, nc_);        
    for (size_type j = 0; j<nc_; j++)
        outputArray[j] = f(beginColumn(j), endColumn(j));
    return outputArray;    
}

//=================================================================================================================
//        I/O OPERATIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array2D<T, Alloc> nct::Array2D<T, Alloc>::read(std::istream& i)
{
    // Check for errors.
    if (i.fail())
        throw IOException(exc_bad_input_stream, SOURCE_INFO);

    // Read number of rows and number of columns.
    size_type r = 0;
    size_type c = 0;
    i.read(reinterpret_cast<char*> (&r), sizeof(size_type));
    if (i.fail())
        throw IOException(exc_error_reading_number_of_rows, SOURCE_INFO);

    i.read(reinterpret_cast<char*> (&c), sizeof(size_type));
    if (i.fail())
        throw IOException(exc_error_reading_number_of_columns, SOURCE_INFO);

    // Read data.
    Array2D<T, Alloc> arr(r, c);
    i.read(reinterpret_cast<char*> (arr.data()), sizeof(T)*arr.size());
    if (i.fail())
        throw IOException(exc_error_reading_data, SOURCE_INFO);
    
    return arr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array2D<T, Alloc>::write(std::ostream& o) const
{
    // Check for errors.
    if (o.fail())
        throw IOException(exc_bad_output_stream, SOURCE_INFO);
    
    // Write number of rows and number of columns.
    o.write(reinterpret_cast<const char*>(&nr_), sizeof(size_type));
    if (o.fail())
        throw IOException(exc_error_writing_number_of_rows, SOURCE_INFO);

    o.write(reinterpret_cast<const char*>(&nc_), sizeof(size_type));
    if (o.fail())
        throw IOException(exc_error_writing_number_of_columns, SOURCE_INFO);

    // Write data.
    if (n_>0) {
        o.write(reinterpret_cast<const char*> (data()), sizeof(T)*n_);
        if (o.fail())
            throw IOException(exc_error_writing_data, SOURCE_INFO);

    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
std::istream& nct::operator>>(std::istream& i, Array2D<T, Alloc>& arr)
{
    arr = Array2D<T, Alloc>::read(i);
    return i;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
std::ostream& nct::operator<<(std::ostream& o, const Array2D<T, Alloc>& arr)
{
    auto r = arr.rows();
    auto c = arr.columns();        

    o << std::endl;
    for (index_t i = 0; i<r; i++) {
        for (index_t j = 0; j<c; j++)
            o << arr(i, j) << " ";
        o << std::endl;
    }

    return o;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
