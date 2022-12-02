//=================================================================================================================
/**
 *  @file       Array_template.h
 *  @brief      nct::Array class template implementation file.
 *  @details    This file contains the implementation of the nct::Array class template.
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
nct::Array<T, Alloc>::Array(const allocator_type& allocator) noexcept : alloc_{allocator},
n_{0}, data_{nullptr}
{
    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array<T, Alloc>::Array(size_type s, const allocator_type& allocator) : alloc_{allocator},
n_{0}, data_{nullptr}
{

    try {
        resize(s);
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
nct::Array<T, Alloc>::Array(size_type s, const_reference val,
    const allocator_type& allocator) : alloc_{allocator}, n_{0}, data_{nullptr}
{
    try {
        resize(s, val);
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
template<typename T, typename Alloc> template<class InputIt>
nct::Array<T, Alloc>::Array(InputIt first, InputIt last,
    const allocator_type& allocator) : alloc_{allocator}, n_{0}, data_{nullptr}
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    try {
        size_type i = 0;
        resize(static_cast<size_type>(last-first));
        for (auto x = first; x != last; ++x, i++)
            data_[i] = *x;
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
nct::Array<T, Alloc>::Array(std::initializer_list<value_type> il,
    const allocator_type& allocator) : Array{std::begin(il), std::end(il), allocator}
{
    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array<T, Alloc>::Array(const Array<T, Alloc>& other)
{
    n_ = 0;
    data_ = nullptr;
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
nct::Array<T, Alloc>::Array(const Array<T, Alloc>& other,
    const allocator_type& allocator) : alloc_{allocator}
{
    n_ = 0;
    data_ = nullptr;
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
nct::Array<T, Alloc>::Array(Array<T, Alloc>&& other) noexcept
{
    n_ = other.n_;
    data_ = other.data_;

    other.n_ = 0;
    other.data_ = nullptr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array<T, Alloc>::Array(Array<T, Alloc>&& other,
    const allocator_type& allocator) : alloc_{allocator}
{
    n_ = other.n_;
    data_ = other.data_;

    other.n_ = 0;
    other.data_ = nullptr;
}

//=================================================================================================================
//        DESTRUCTOR
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline nct::Array<T, Alloc>::~Array() noexcept
{        
    clear();
}

//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array<T, Alloc>& nct::Array<T, Alloc>::operator=(const Array<T, Alloc>& other)
{
    if (data_ == other.data_)
        return *this;

    try {
        copy(other);
    }
    catch (const nct_exception & ex) {
        throw OperationException(exc_error_copying_array, SOURCE_INFO,
            std::make_exception_ptr(ex));
    }
    catch (const std::exception & ex) {
        throw OperationException(exc_error_copying_array, SOURCE_INFO,
            std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_unknown, SOURCE_INFO);
    }

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array<T, Alloc>& nct::Array<T, Alloc>::operator=(Array<T, Alloc>&& other) noexcept
{
    if (data_ == other.data_)
        return *this;

    clear();
    n_ = other.n_;
    data_ = other.data_;

    other.n_ = 0;
    other.data_ = nullptr;

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::reference
nct::Array<T, Alloc>::operator[](size_type i)
{
#ifndef NCT_ARRAY_DISABLE_INDEX_CHECKING
    if (i >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
#endif
    return data_[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::const_reference
nct::Array<T, Alloc>::operator[](size_type i) const
{
#ifndef NCT_ARRAY_DISABLE_INDEX_CHECKING
    if (i >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
#endif
    return data_[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::reference
nct::Array<T, Alloc>::operator()(size_type i)
{
#ifndef NCT_ARRAY_DISABLE_INDEX_CHECKING
    if (i >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
#endif
    return data_[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::const_reference
nct::Array<T, Alloc>::operator()(size_type i) const
{
#ifndef NCT_ARRAY_DISABLE_INDEX_CHECKING
    if (i >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
#endif
    return data_[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::equality_comparable<T>
bool nct::Array<T, Alloc>::operator==(const Array<T, Alloc>& right) const
{
    if (data_ == right.data_)
        return true;

    if (n_ != right.n_)
        return false;

    for (size_type i = 0; i < n_; i++) {
        if (data_[i] != right.data_[i])
            return false;
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::equality_comparable<T>
bool nct::Array<T, Alloc>::operator!=(const Array<T, Alloc>& right) const
{
    return !(*this == right);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
nct::Array<T, Alloc> nct::Array<T, Alloc>::operator&( const Array<T, Alloc> & right) const
{
    if (right.n_ != n_)
        throw ArgumentException("right", exc_bad_array_dimensions,
            SOURCE_INFO);

    Array<T, Alloc> res(n_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = (data_[i] & right.data_[i]);

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::integral T, typename Alloc>
nct::Array<T, Alloc> nct::operator&(Array<T, Alloc> && left, const Array<T, Alloc> & right)
{
    if (left.size() != right.size())
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array<T, Alloc> resArr;
    std::swap(resArr, left);

    for (typename Array<T, Alloc>::size_type i = 0; i < resArr.size(); i++)
        resArr[i] = (resArr[i] & right[i]);

    return resArr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
const nct::Array<T, Alloc> & nct::Array<T, Alloc>::operator&=(
    const Array<T, Alloc> & right)
{
    if (right.n_ != n_)
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] &= right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
nct::Array<T, Alloc> nct::Array<T, Alloc>::operator|(
    const Array<T, Alloc> & right) const
{
    if (right.n_ != n_)
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array<T, Alloc> res(n_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = (data_[i] | right.data_[i]);

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::integral T, typename Alloc>
nct::Array<T, Alloc> nct::operator|(Array<T, Alloc> && left, const Array<T, Alloc> & right)
{
    if (left.size() != right.size())
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array<T, Alloc> resArr;
    std::swap(resArr, left);

    for (typename Array<T, Alloc>::size_type i = 0; i < resArr.size(); i++)
        resArr[i] = (resArr[i] | right[i]);

    return resArr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
const nct::Array<T, Alloc> & nct::Array<T, Alloc>::operator|=(
    const Array<T, Alloc> & right)
{
    if (right.n_ != n_)
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] |= right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
nct::Array<T, Alloc> nct::Array<T, Alloc>::operator^(const Array<T, Alloc> & right) const
{
    if (right.n_ != n_)
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array<T, Alloc> res(n_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = (data_[i] ^ right.data_[i]);

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<std::integral T, typename Alloc>
nct::Array<T, Alloc> nct::operator^(Array<T, Alloc> && left, const Array<T, Alloc> & right)
{
    if (left.size() != right.size())
        throw ArgumentException("right, left", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array<T, Alloc> resArr;
    std::swap(resArr, left);

    for (typename Array<T, Alloc>::size_type i = 0; i < resArr.size(); i++)
        resArr[i] = (resArr[i] ^ right[i]);

    return resArr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::integral<T>
const nct::Array<T, Alloc> & nct::Array<T, Alloc>::operator^=(
    const Array<T, Alloc> & right)
{
    if (right.n_ != n_)
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] ^= right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array<T, Alloc> nct::Array<T, Alloc>::operator+() const
{
    Array<T, Alloc> res(n_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Addable<T>
nct::Array<T, Alloc> nct::Array<T, Alloc>::operator+(const Array<T, Alloc>& right) const
{
    if (right.n_ != n_)
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array<T, Alloc> res(n_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i] + right.data_[i];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Addable T, typename Alloc>
nct::Array<T, Alloc> nct::operator+(Array<T, Alloc>&& left, const Array<T, Alloc>& right)
{
    if (left.size() != right.size())
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array<T, Alloc> resArr;
    std::swap(resArr, left);

    for (typename Array<T, Alloc>::size_type i = 0; i < resArr.size(); i++)
        resArr[i] += right[i];

    return resArr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Addable<T>
const nct::Array<T, Alloc> & nct::Array<T, Alloc>::operator+=(const Array<T, Alloc> & right)
{
    if (right.n_ != n_)
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] += right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::SignedNumeric<T>
nct::Array<T, Alloc> nct::Array<T, Alloc>::operator-() const
{
    Array<T, Alloc> res(n_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = -data_[i];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Substractable<T>
nct::Array<T, Alloc> nct::Array<T, Alloc>::operator-(const Array & right) const
{
    if (right.n_ != n_)
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    Array<T, Alloc> res(n_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i] - right.data_[i];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Substractable T, typename Alloc>
nct::Array<T, Alloc> nct::operator-(Array<T, Alloc> && left, const Array<T, Alloc> & right)
{
    if (left.size() != right.size())
        throw ArgumentException("left, right", exc_bad_dimensions_of_arrays, SOURCE_INFO);

    Array<T, Alloc> resArr;
    std::swap(resArr, left);

    for (typename Array<T, Alloc>::size_type i = 0; i < resArr.size(); i++)
        resArr[i] -= right[i];

    return resArr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Substractable<T>
const nct::Array<T, Alloc> & nct::Array<T, Alloc>::operator-=(
    const Array<T, Alloc> & right)
{
    if (right.n_ != n_)
        throw ArgumentException("right", exc_bad_array_dimensions, SOURCE_INFO);

    for (size_type i = 0; i < n_; i++)
        data_[i] -= right.data_[i];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array<T, Alloc> nct::Array<T, Alloc>::operator*(const_reference right) const
{
    Array<T, Alloc> res(n_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i] * right;

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T, typename Alloc>
nct::Array<T, Alloc> nct::operator*(const T & left, const Array<T, Alloc> & right)
{
    Array<T, Alloc> res(right.size());
    for (typename Array<T, Alloc>::size_type i = 0; i < right.size(); i++)
        res[i] = right[i] * left;

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
const nct::Array<T, Alloc>& nct::Array<T, Alloc>::operator*=(const_reference right)
{
    for (size_type i = 0; i < n_; i++)
        data_[i] *= right;

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array<T, Alloc> nct::Array<T, Alloc>::operator/(const_reference right) const
{
    Array<T, Alloc> res(n_);
    for (size_type i = 0; i < n_; i++)
        res.data_[i] = data_[i] / right;

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
const nct::Array<T, Alloc>& nct::Array<T, Alloc>::operator/=(const_reference right)
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
void nct::Array<T, Alloc>::clear() noexcept
{
    if (n_) {
        for (size_type i = 0; i<n_; i++)
            allocator_traits::destroy(alloc_, data_ + i);
        alloc_.deallocate(data_, n_);        
    }
    n_ = 0;
    data_ = nullptr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array<T, Alloc>::assign(size_type s, const_reference val)
{    
    if (n_ == s) {
        for (size_type i=0; i<n_; i++)
            data_[i] = val;
    }
    else {
        try {    
            // Release old data.
            clear();

            // Allocate new array.
            n_ = s; 
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
inline void nct::Array<T, Alloc>::resize(size_type s)
{
    if (n_ == s)
        return;

    // Previous array size.
    auto pn = n_;

    // New array size.
    n_ = s;

    // Block segment that will be preserved.
    auto iMin = pn < n_ ? (pn) : (n_);

    // Allocate memory and copy previous data.
    if (n_ > 0) {
        try {
            // Allocate new array.
            auto dd = data_;
            data_ = alloc_.allocate(n_);

            // Initialize data.
            for (size_type i = 0; i < n_; i++) {
                if (i < iMin)
                    allocator_traits::construct(alloc_, data_ + i, std::move(dd[i]));
                else
                    allocator_traits::construct(alloc_, data_ + i, T());
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
void nct::Array<T, Alloc>::resize(size_type s, const_reference val)
{    
    if (n_ == s)
        return;

    // Previous array size.
    auto pn = n_;

    // New array size.
    n_ = s;

    // Block segment that will be preserved.
    auto iMin = pn < n_? (pn) : (n_);

    // Allocate memory and copy previous data.
    if (n_>0) {
        try {    
            // Allocate new array.
            auto dd = data_;        
            data_ = alloc_.allocate(n_);

            // Initialize data.
            for (size_type i=0; i<n_; i++) {
                if (i < iMin)
                    allocator_traits::construct(alloc_, data_ + i, std::move(dd[i]));
                else
                    allocator_traits::construct(alloc_, data_ + i, val);                
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
inline typename nct::Array<T, Alloc>::allocator_type 
nct::Array<T, Alloc>::get_allocator() const
{
    return allocator_type(alloc_);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline void nct::Array<T, Alloc>::fill(const_reference val)
{
    for (size_type i=0; i<n_; i++)
        data_[i] = val;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array<T, Alloc>::copy(const Array& other)
{
    // Check whether a different instance is being copied.
    if ((data_ == other.data_) && (n_ == other.n_))
        return;

    if (other.n_ == 0) {
        // Release object.
        clear();
    }
    else if (n_ == other.n_) {
        // Copy new contents.
        for (size_type i=0; i<n_; i++)
            data_[i] = other.data_[i];
    }
    else {
        // Allocate new array and copy data.
        try {                
            clear();
            n_ = other.n_;
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
bool nct::Array<T, Alloc>::empty() const noexcept
{
    return (n_ == 0);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::size_type nct::Array<T, Alloc>::size() const noexcept
{
    return n_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::pointer nct::Array<T, Alloc>::data() noexcept
{
    return data_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::const_pointer
nct::Array<T, Alloc>::data() const noexcept
{
    return data_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::pointer
nct::Array<T, Alloc>::data(size_type index)
{
    if (index >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
    return &data_[index];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::const_pointer 
nct::Array<T, Alloc>::data(size_type index) const
{
    if (index >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
    return &data_[index];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::reference
nct::Array<T, Alloc>::at(size_type index) 
{
    if (index >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
    return data_[index];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::const_reference
nct::Array<T, Alloc>::at(size_type index) const
{
    if (index >= n_)
        throw IndexOutOfRangeException(SOURCE_INFO);
    return data_[index];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::reference nct::Array<T, Alloc>::front()
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);
    return data_[0];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::const_reference
nct::Array<T, Alloc>::front() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);
    return data_[0];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::reference nct::Array<T, Alloc>::back()
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);
    return data_[n_ - 1];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::const_reference 
nct::Array<T, Alloc>::back() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);
    return data_[n_ - 1];
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename Container>
Container nct::Array<T, Alloc>::find(const_reference t) const
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
nct::Array<U, AllocU> nct::Array<T, Alloc>::toArray() const
{
    Array<U, AllocU> outputArray(n_);        
    for (size_type k = 0; k<n_; k++)
        outputArray[k] = static_cast<U>(data_[k]);
    return outputArray;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename C>
nct::Array<T, Alloc> nct::Array<T, Alloc>::fromContainer(const C& container)
{
    return Array<T, Alloc>(std::begin(container), std::end(container));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename C>
nct::Array<T, Alloc> nct::Array<T, Alloc>::fromSubscript(const C& container, size_type i)
{
    auto n = container.size();
    if (n == 0)
        return Array<T, Alloc>(0);

    Array<T, Alloc> items(n);
    try {
        for (size_type ni = 0; ni < n; ni++)
            items[ni] = container[ni](i);
    }
    catch (const nct_exception& ex) {
        throw OperationException(exc_bad_array_of_arrays_subscript,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw OperationException(exc_bad_array_of_arrays_subscript,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_bad_array_of_arrays_subscript, 
            SOURCE_INFO);
    }

    return items;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename C>
nct::Array<T, Alloc> nct::Array<T, Alloc>::fromSubscript(const C& container,
    size_type i, size_type j)
{
    auto n = container.size();
    if (n == 0)
        return Array<T, Alloc>(0);

    Array<T, Alloc> items(n);
    try {
        for (size_type ni = 0; ni < n; ni++)
            items[ni] = container[ni](i, j);
    }
    catch (const nct_exception& ex) {
        throw OperationException(exc_bad_array_of_arrays_subscript,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw OperationException(exc_bad_array_of_arrays_subscript,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_bad_array_of_arrays_subscript, 
            SOURCE_INFO);
    }

    return items;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename C>
nct::Array<T, Alloc> nct::Array<T, Alloc>::fromSubscript(const C& container,
    size_type i, size_type j, size_type k)
{
    auto n = container.size();
    if (n == 0)
        return Array<T, Alloc>(0);

    Array<T, Alloc> items(n);
    try {
        for (size_type ni = 0; ni < n; ni++)
            items[ni] = container[ni](i, j, k);
    }
    catch (const nct_exception& ex) {
        throw OperationException(exc_bad_array_of_arrays_subscript,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw OperationException(exc_bad_array_of_arrays_subscript,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_bad_array_of_arrays_subscript, 
            SOURCE_INFO);
    }

    return items;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename C>
nct::Array<T, Alloc> nct::Array<T, Alloc>::fromSubscript(const C& container,
    size_type i, size_type j, size_type k, size_type l)
{
    auto n = container.size();
    if (n == 0)
        return Array<T, Alloc>(0);

    Array<T, Alloc> items(n);
    try {
        for (size_type ni = 0; ni < n; ni++)
            items[ni] = container[ni](i, j, k, l);
    }
    catch (const nct_exception& ex) {
        throw OperationException(exc_bad_array_of_arrays_subscript,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw OperationException(exc_bad_array_of_arrays_subscript,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_bad_array_of_arrays_subscript, 
            SOURCE_INFO);
    }

    return items;
}

//=================================================================================================================
//        DATA INSERTIONS AND DELETIONS 
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array<T, Alloc>::push_back(const_reference val)
{
    resize(n_ + 1, val);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array<T, Alloc>::push_back(rvalue_reference val)
{
    resize(n_ + 1);
    data_[n_-1] = std::move(val);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array<T, Alloc>::pop_back()
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    if (n_ == 1)
        clear();
    else 
        resize(n_ - 1);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
typename nct::Array<T, Alloc>::iterator
    nct::Array<T, Alloc>::insert(size_type position, const_reference val)
{
    if (position > n_)
        throw IndexOutOfRangeException("position", SOURCE_INFO);

    // Old data.
    nct::Array<T, Alloc> old(std::move(*this));

    // Resize array.
    resize(old.n_ + 1);
    
    // Fill array.
    for (size_type i = 0; i<position; i++)
        data_[i] = std::move(old.data_[i]);

    data_[position] = val;

    for (size_type i = (position+1); i<n_; i++)
        data_[i] = std::move(old.data_[i-1]);

    return begin() + position;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
typename nct::Array<T, Alloc>::iterator
    nct::Array<T, Alloc>::insert(size_type position, rvalue_reference val)
{
    if (position > n_)
        throw IndexOutOfRangeException("position", SOURCE_INFO);

    // Old data.
    nct::Array<T, Alloc> old(std::move(*this));

    // Resize array.
    resize(old.n_ + 1);
    
    // Fill array.
    for (size_type i = 0; i<position; i++)
        data_[i] = std::move(old.data_[i]);

    data_[position] = std::move(val);

    for (size_type i = (position+1); i<n_; i++)
        data_[i] = std::move(old.data_[i-1]);

    return begin() + position;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
typename nct::Array<T, Alloc>::iterator
    nct::Array<T, Alloc>::insert(const_iterator position, const_reference val)
{
    if (!position.validForComparison(begin()))
        throw IteratorException("position", SOURCE_INFO);
    return insert(static_cast<size_type>(position.currentIndex()), val);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
typename nct::Array<T, Alloc>::iterator
    nct::Array<T, Alloc>::insert(const_iterator position, rvalue_reference val)
{
    if (!position.validForComparison(begin()))
        throw IteratorException("position", SOURCE_INFO);
    return insert(static_cast<size_type>(position.currentIndex()), std::move(val));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator InputIt>
typename nct::Array<T, Alloc>::iterator
    nct::Array<T, Alloc>::insert(size_type position, InputIt first, InputIt last)
{
    if (position > n_)
        throw IndexOutOfRangeException("position", SOURCE_INFO);

    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    size_type nn = static_cast<size_type>(last - first);
    if (nn == 0)
        return begin() + position;

    // Old data.
    nct::Array<T, Alloc> old(std::move(*this));

    // Resize array.
    resize(old.n_ + nn);
    
    // Fill array.
    for (size_type i = 0; i<position; i++)
        data_[i] = std::move(old.data_[i]);

    auto c = position;
    for (auto x = first; x != last; ++x)
        data_[c++] = *x;

    for (size_type i = (position + nn); i<n_; i++)
        data_[i] = std::move(old.data_[i-nn]);

    return begin() + position;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator InputIt>
typename nct::Array<T, Alloc>::iterator nct::Array<T, Alloc>::insert(
    const_iterator position, InputIt first, InputIt last)
{
    if (!position.validForComparison(begin()))
        throw IteratorException("position", SOURCE_INFO);
    return insert(static_cast<size_type>(position.currentIndex()), first, last);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
typename nct::Array<T, Alloc>::iterator
nct::Array<T, Alloc>::insert(size_type position, std::initializer_list<value_type> il)
{
    return insert(position, std::begin(il), std::end(il));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
typename nct::Array<T, Alloc>::iterator
nct::Array<T, Alloc>::insert(const_iterator position, std::initializer_list<value_type> il)
{
    return insert(position, std::begin(il), std::end(il));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
typename nct::Array<T, Alloc>::iterator
nct::Array<T, Alloc>::insert(size_type position, const Array<T, Alloc>& data)
{
    return insert(position, std::begin(data), std::end(data));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
typename nct::Array<T, Alloc>::iterator
nct::Array<T, Alloc>::insert(const_iterator position, const Array<T, Alloc>& data)
{
    return insert(position, std::begin(data), std::end(data));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
typename nct::Array<T, Alloc>::iterator
    nct::Array<T, Alloc>::erase(size_type position)
{
    if (position >= n_)
        throw IndexOutOfRangeException("position", SOURCE_INFO);

    if (n_ == 1) {
        clear();
        return begin();
    }

    // Old data.
    nct::Array<T, Alloc> old(std::move(*this));

    // Resize array.
    resize(old.n_ - 1);
    
    // Fill array.
    for (size_type i = 0; i<position; i++)
        data_[i] = std::move(old.data_[i]);

    for (size_type i = position; i<n_; i++)
        data_[i] = std::move(old.data_[i+1]);

    return begin() + position;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
typename nct::Array<T, Alloc>::iterator
    nct::Array<T, Alloc>::erase(const_iterator position)
{
    if (!position.validForComparison(begin()))
        throw IteratorException("position", SOURCE_INFO);
    return erase(static_cast<size_type>(position.currentIndex()));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
typename nct::Array<T, Alloc>::iterator
    nct::Array<T, Alloc>::erase(size_type first, size_type last)
{
    if (first >= n_)
        throw IndexOutOfRangeException("first", SOURCE_INFO);

    if (last >= n_)
        throw IndexOutOfRangeException("last", SOURCE_INFO);

    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    auto nn = last - first + 1;
    if (nn == n_) {
        clear();
        return begin();
    }

    // Old data.
    nct::Array<T, Alloc> old(std::move(*this));

    // Resize array.
    resize(old.n_ - nn);
    
    // Fill array.
    for (size_type i = 0; i<first; i++)
        data_[i] = std::move(old.data_[i]);

    for (size_type i = first; i<n_; i++)
        data_[i] = std::move(old.data_[i+nn]);

    return begin() + first;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> 
typename nct::Array<T, Alloc>::iterator
    nct::Array<T, Alloc>::erase(const_iterator first, const_iterator last)
{
    if (!first.validForComparison(begin()))
        throw IteratorException("first", SOURCE_INFO);

    if (!last.validForComparison(begin()))
        throw IteratorException("last", SOURCE_INFO);

    if ((first == cend()) && (last == cend()))
        return end();

    --last;
    return erase(static_cast<size_type>(first.currentIndex()),
        static_cast<size_type>(last.currentIndex()));
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<std::random_access_iterator IndexIt>
void nct::Array<T, Alloc>::eraseElements(IndexIt first, IndexIt last)
{
    if (last < first)
        throw RangeException("first, last", SOURCE_INFO);

    size_type nn = 0;    
    for (auto p1 = first; p1 != last; ++p1) {
        if (static_cast<size_type>(*p1) >= n_)
            throw ArgumentException("first, last", exc_indices_out_of_range, SOURCE_INFO);

        auto p2 = first;
        for (; p2!=p1; ++p2) {
            if (static_cast<size_type>(*p1) == static_cast<size_type>(*p2))
                break;
        }
            
        nn += (p2 == p1);
    }

    if (nn == n_) {
        clear();
        return;
    }

    // Old data.
    nct::Array<T, Alloc> old(std::move(*this));

    // Resize array.
    resize(old.n_ - nn);
    
    // Fill array.
    size_type c = 0;
    for (size_type i = 0; i<old.n_; i++) {
        auto p = first;
        for (; p != last; ++p) {
            if (i == static_cast<size_type>(*p))
                break;
        }

        if (p == last)
            data_[c++] = std::move(old.data_[i]);
    }
}

//=================================================================================================================
//        DATA SELECTION
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array<T, Alloc> nct::Array<T, Alloc>::selectRange(
    size_type first, size_type last) const
{
    if (last<first)
        throw RangeException("first, last", SOURCE_INFO);

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
inline nct::Array<T, Alloc> nct::Array<T, Alloc>::selectRange(
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
nct::Array<T, Alloc> nct::Array<T, Alloc>::selectData(
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
nct::Array<T, Alloc> nct::Array<T, Alloc>::selectData(
    const Array<size_type, AllocU>& indices) const
{
    return selectData(std::begin(indices), std::end(indices));
}

//=================================================================================================================
//        CIRCULAR SHIFTS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array<T, Alloc> nct::Array<T, Alloc>::circularShift(difference_type s0) const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array<T, Alloc> res(n_);                
    for (difference_type i=0; i<static_cast<difference_type>(n_); i++) {
        difference_type off = i+s0;            
        while (off<0)
            off+=n_;
        off %= n_;
        res[i] = (*this)[off];
    }

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array<T, Alloc> nct::Array<T, Alloc>::circularShift() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array<T, Alloc> res(n_);
    size_type c = (n_ + 1) / 2;    
    for (difference_type i=0; i<static_cast<difference_type>(n_); i++)
        res[i] = (*this)[(i + c) % n_];

    return res;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array<T, Alloc> nct::Array<T, Alloc>::circularInvShift() const
{
    if (n_ == 0)
        throw EmptyArrayException(SOURCE_INFO);

    Array<T, Alloc> res(n_);
    size_type c = (n_ + 1) / 2;
    for (size_type i=0; i<n_; i++) {    
        auto iPos = (i < c) ? (n_ + i - c) : (i - c);
        res[i] = (*this)[iPos];
    }

    return res;
}

//=================================================================================================================
//        NUMERICAL AND LOGICAL OPERATIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Addable<T>
typename nct::Array<T, Alloc>::value_type nct::Array<T, Alloc>::sum() const
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
double nct::Array<T, Alloc>::castSum() const
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
typename nct::Array<T, Alloc>::value_type nct::Array<T, Alloc>::squaredNorm() const
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
double nct::Array<T, Alloc>::euclideanNorm() const
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
double nct::Array<T, Alloc>::lpNorm(double p) const
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
double nct::Array<T, Alloc>::infinityNorm() const
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
double nct::Array<T, Alloc>::mean() const
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
double nct::Array<T, Alloc>::variance() const
{
    if (n_<2)
        throw ConfigurationException(exc_array_with_less_than_two_elements,
        SOURCE_INFO);    

    double res = 0; 
    double meanVal = mean(); 

    for (size_type i=0; i<n_; i++)
        res += (data_[i] - meanVal)*(data_[i] - meanVal);        
    
    return res/(n_-1);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires std::totally_ordered<T>
typename nct::Array<T, Alloc>::value_type nct::Array<T, Alloc>::max() const
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
typename nct::Array<T, Alloc>::value_type nct::Array<T, Alloc>::min() const
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
T nct::dotProduct(const Array<T, Alloc>& a, const Array<T, Alloc>& b)
{
    if (a.size() != b.size())
        throw ArgumentException("a, b", exc_arrays_of_different_dimensions, SOURCE_INFO);

    auto n = a.size();
    T temp = 0;        
    for (index_t i=0; i<n; i++)
        temp += a[i]*b[i];
    return temp;
}

//=================================================================================================================
//        SPECIAL ARRAYS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array<T, Alloc> nct::Array<T, Alloc>::constant(size_type arraySize, const_reference t)
{
    return nct::Array<T, Alloc>(arraySize, t);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array<T, Alloc> nct::Array<T, Alloc>::zeros(size_type arraySize)
{
    return nct::Array<T, Alloc>(arraySize, 0);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array<T, Alloc> nct::Array<T, Alloc>::ones(size_type arraySize)
{
    return nct::Array<T, Alloc>(arraySize, 1);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename> requires nct::Numeric<T>
nct::Array<T, Alloc> nct::Array<T, Alloc>::numericalSequence(
    size_type arraySize, const_reference ini, const_reference inc)
{
    if (arraySize == 0)
        return Array<T, Alloc>(0);

    Array<T, Alloc> newArray(arraySize);
    newArray[0] = ini;
    
    for (size_type i = 1; i<arraySize; i++)
        newArray[i] = newArray[i-1] + inc;

    return newArray;
}

//=================================================================================================================
//        ITERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::iterator nct::Array<T, Alloc>::begin()
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, 0);    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::const_iterator
nct::Array<T, Alloc>::begin() const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, 0);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::const_iterator 
nct::Array<T, Alloc>::cbegin() const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, 0);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::iterator nct::Array<T, Alloc>::end()
{
    if (n_ == 0)
        return iterator();
    return iterator(*this, n_);    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::const_iterator 
nct::Array<T, Alloc>::end() const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, n_);    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::const_iterator
nct::Array<T, Alloc>::cend() const
{
    if (n_ == 0)
        return const_iterator();
    return const_iterator(*this, n_);    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::reverse_iterator 
nct::Array<T, Alloc>::rbegin()
{
    return reverse_iterator(end());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::const_reverse_iterator
nct::Array<T, Alloc>::rbegin() const
{
    return const_reverse_iterator(end());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::const_reverse_iterator 
nct::Array<T, Alloc>::crbegin() const
{
    return const_reverse_iterator(end());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::reverse_iterator nct::Array<T, Alloc>::rend()
{
    return reverse_iterator(begin());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::const_reverse_iterator 
nct::Array<T, Alloc>::rend() const
{
    return const_reverse_iterator(begin());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
inline typename nct::Array<T, Alloc>::const_reverse_iterator 
nct::Array<T, Alloc>::crend() const
{
    return const_reverse_iterator(begin());
}

//=================================================================================================================
//        TRANSFORMATIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc> template<typename U, typename AllocU>
nct::Array<U, AllocU> nct::Array<T, Alloc>::transformData(
    const std::function<U(const_reference)>& f) const
{
    Array<U, AllocU> outputArray(n_);        
    for (size_type k = 0; k<n_; k++)
        outputArray[k] = f(data_[k]);
    return outputArray;    
}

//=================================================================================================================
//        I/O OPERATIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
nct::Array<T, Alloc> nct::Array<T, Alloc>::read(std::istream& i)
{
    // Check for errors.
    if (i.fail())
        throw IOException(exc_bad_input_stream, SOURCE_INFO);

    // Read number of rows and number of columns.
    size_type n_ = 0;
    i.read(reinterpret_cast<char*> (&n_), sizeof(size_type));
    if (i.fail())
        throw IOException(exc_error_reading_array_size, SOURCE_INFO);

    // Read data.
    Array<T, Alloc> arr(n_);
    i.read(reinterpret_cast<char*> (arr.data()), sizeof(T)*arr.size());
    if (i.fail())
        throw IOException(exc_error_reading_data, SOURCE_INFO);
    
    return arr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
void nct::Array<T, Alloc>::write(std::ostream& o) const
{
    // Check for errors.
    if (o.fail())
        throw IOException(exc_bad_output_stream, SOURCE_INFO);
    
    // Write number of rows and number of columns.
    o.write(reinterpret_cast<const char*>(&n_), sizeof(size_type));
    if (o.fail())
        throw IOException(exc_error_writing_array_size, SOURCE_INFO);
    
    // Write data.
    if (n_>0) {
        o.write(reinterpret_cast<const char*> (data()), sizeof(T)*n_);
        if (o.fail())
            throw IOException(exc_error_writing_data, SOURCE_INFO);

    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
std::istream& nct::operator>>(std::istream& i, Array<T, Alloc>& arr)
{
    arr = Array<T, Alloc>::read(i);
    return i;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename Alloc>
std::ostream& nct::operator<<(std::ostream& o, const Array<T, Alloc>& arr)
{
    auto n = arr.size();
    o << std::endl;
    o << "(";
    for (index_t i = 0; i<n; i++) {
        o << arr[i];
        if (i < (n-1))
            o << ", ";
    }
    o << ")" << std::endl;

    return o;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
