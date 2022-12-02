//=================================================================================================================
/**
 *  @file       SparseArray3D_template.h
 *  @brief      nct::SparseArray3D class implementation file.
 *  @details    This file contains the implementation of the nct::SparseArray3D class template.
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
template<typename T, typename MapAlloc> 
nct::SparseArray3D<T, MapAlloc>::SparseArray3D(const_reference nullValue) :
nd1_{0}, nd2_{0}, nd3_{0}, n_{0}, nullValue_{nullValue}
{

}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
nct::SparseArray3D<T, MapAlloc>::SparseArray3D(size_type dim1, size_type dim2, 
    size_type dim3, const_reference nullValue) :
    nd1_{0}, nd2_{0}, nd3_{0}, n_{0}, nullValue_{nullValue}
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
template<typename T, typename MapAlloc>
nct::SparseArray3D<T, MapAlloc>::SparseArray3D(const SparseArray3D<T, MapAlloc>& other)
{
    try {
        nd1_ = other.nd1_;
        nd2_ = other.nd2_;
        nd3_ = other.nd3_;
        n_ = other.n_;
        nullValue_ = other.nullValue_;
        data_ = other.data_;
    }
    catch (const nct_exception & ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception & ex) {
        throw InitializationException(SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw InitializationException(SOURCE_INFO);
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
 nct::SparseArray3D<T, MapAlloc>::SparseArray3D(SparseArray3D<T, MapAlloc>&& other) noexcept
{
    nd1_ = other.nd1_;
    nd2_ = other.nd2_;
    nd3_ = other.nd3_;
    n_ = other.n_;
    nullValue_ = other.nullValue_;
    data_ = std::move(other.data_);

    other.nd1_ = 0;
    other.nd2_ = 0;
    other.nd3_ = 0;
    other.n_ = 0;
}

//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
 template<typename T, typename MapAlloc>
 nct::SparseArray3D<T, MapAlloc>&
     nct::SparseArray3D<T, MapAlloc>::operator=(const SparseArray3D<T, MapAlloc>& other)
 {
     if (&data_ == &other.data_)
         return *this;

     nd1_ = other.nd1_;
     nd2_ = other.nd2_;
     nd3_ = other.nd3_;
     n_ = other.n_;
     nullValue_ = other.nullValue_;
     data_ = other.data_;

     return *this;
 }

//-----------------------------------------------------------------------------------------------------------------
 template<typename T, typename MapAlloc>
 nct::SparseArray3D<T, MapAlloc>&
     nct::SparseArray3D<T, MapAlloc>::operator=(SparseArray3D<T, MapAlloc>&& other) noexcept
 {
     if (&data_ == &other.data_)
         return *this;

     nd1_ = other.nd1_;
     nd2_ = other.nd2_;
     nd3_ = other.nd3_;
     n_ = other.n_;
     nullValue_ = other.nullValue_;
     data_ = std::move(other.data_);

     other.nd1_ = 0;
     other.nd2_ = 0;
     other.nd3_ = 0;
     other.n_ = 0;

     return *this;
 }

//-----------------------------------------------------------------------------------------------------------------
 template<typename T, typename MapAlloc>
 bool nct::SparseArray3D<T, MapAlloc>::operator==(const SparseArray3D<T, MapAlloc>& right)
 {
     if (&data_ == &right.data_)
         return true;

     if ((nd1_ != right.nd1_) || (nd2_ != right.nd2_) || (nd3_ != right.nd3_))
         return false;

     for (auto it = data_.begin(); it != data_.end(); it++) {
         const auto& ind = (*it).first;
         if (((*it).second) != (right(ind[0], ind[1], ind[2])))
             return false;
     }

     for (auto it = right.data_.begin(); it != right.data_.end(); it++) {
         const auto& ind = (*it).first;
         if (((*it).second) != ((*this)(ind[0], ind[1], ind[2])))
             return false;
     }

     return true;
 }

//-----------------------------------------------------------------------------------------------------------------
 template<typename T, typename MapAlloc>
 bool nct::SparseArray3D<T, MapAlloc>::operator!=(const SparseArray3D<T, MapAlloc> & right)
 {
     return !(*this == right);
 }

//-----------------------------------------------------------------------------------------------------------------
 template<typename T, typename MapAlloc>
 inline typename nct::SparseArray3D<T, MapAlloc>::const_reference
     nct::SparseArray3D<T, MapAlloc>::operator()(size_type i, size_type j, size_type k) const
 {
#ifndef NCT_SPARSE_ARRAY_3D_DISABLE_INDEX_CHECKING
     if (i >= nd1_)
         throw IndexOutOfRangeException("i", SOURCE_INFO);
     if (j >= nd2_)
         throw IndexOutOfRangeException("j", SOURCE_INFO);
     if (k >= nd3_)
         throw IndexOutOfRangeException("k", SOURCE_INFO);
#endif
     auto it = data_.find(index_type(i, j, k));
     if (it == data_.end())
         return nullValue_;
     return (*it).second;
 }

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
void nct::SparseArray3D<T, MapAlloc>::resize(size_type dim1, size_type dim2, size_type dim3)
{    
    if ( (nd1_ != dim1) || (nd3_ != dim3) || (nd2_ != dim2) ) {
        clear();
        nd1_ = dim1;
        nd2_ = dim2;
        nd3_ = dim3;        
        n_ = nd1_*dim3*dim2;
        data_.clear();
    }
    data_.clear();
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
void nct::SparseArray3D<T, MapAlloc>::clear() noexcept
{
    nd1_ = 0;
    nd2_ = 0;
    nd3_ = 0;
    n_ = 0;
    data_.clear();
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
void nct::SparseArray3D<T, MapAlloc>::copy(const SparseArray3D& other)
{
    if (data_ == other.data_)
        return;

    clear();
    nd1_ = other.nd1_;
    nd3_ = other.nd3_;
    nd2_ = other.nd2_;
    n_ = other.n_;
    nullValue_ = other.nullValue_;
    data_ = other.data_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
inline typename nct::SparseArray3D<T, MapAlloc>::size_type
nct::SparseArray3D<T, MapAlloc>::dimension1() const noexcept
{
    return nd1_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
inline typename nct::SparseArray3D<T, MapAlloc>::size_type 
nct::SparseArray3D<T, MapAlloc>::dimension2() const noexcept
{
    return nd2_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
inline typename nct::SparseArray3D<T, MapAlloc>::size_type 
nct::SparseArray3D<T, MapAlloc>::dimension3() const noexcept
{
    return nd3_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
inline typename nct::SparseArray3D<T, MapAlloc>::size_type
nct::SparseArray3D<T, MapAlloc>::size() const noexcept
{
    return n_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
inline typename nct::SparseArray3D<T, MapAlloc>::size_type
    nct::SparseArray3D<T, MapAlloc>::numberOfNonNullElements() const noexcept
{
    return static_cast<size_type>(data_.size());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
inline typename nct::SparseArray3D<T, MapAlloc>::const_reference
    nct::SparseArray3D<T, MapAlloc>::nullValue() const noexcept
{
    return nullValue_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
inline typename nct::SparseArray3D<T, MapAlloc>::
const_reference nct::SparseArray3D<T, MapAlloc>::at(
    size_type dim1, size_type dim2, size_type dim3) const
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);
    auto it = data_.find(index_type(dim1, dim2, dim3));
    if (it == data_.end())
        return nullValue_;
    return (*it).second;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
void nct::SparseArray3D<T, MapAlloc>::modify(size_type dim1, size_type dim2, size_type dim3, 
    const_reference val)
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);
    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);
    index_type ind(dim1, dim2, dim3);
    auto it = data_.find(ind);

    if (val != nullValue_) {
        if (it == data_.end())
            data_.operator[](ind) = val;
        else 
            (*it).second = val;        
    }
    else if (it != data_.end()) {
        data_.erase(it);
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
nct::Array3D<T> nct::SparseArray3D<T, MapAlloc>::toArray() const
{
    Array3D<T> r(nd1_, nd2_, nd3_, nullValue_);
    for (auto it=data_.begin() ; it != data_.end(); it++)
        r((*it).first[0], (*it).first[1], (*it).first[2]) = (*it).second;    

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
nct::Array2D<T> nct::SparseArray3D<T, MapAlloc>::subArray(size_type dim1) const
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);

    Array2D<T> arr(nd2_, nd3_, nullValue_);
    for (auto it=data_.begin() ; it != data_.end(); it++) {
        const auto& ind = (*it).first;
        if ( (ind[0] == dim1))
            arr(ind[1], ind[2]) = (*it).second;
    }

    return arr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
nct::Array<T> nct::SparseArray3D<T, MapAlloc>::elementsOfDim1(
    size_type dim2, size_type dim3) const
{
    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);

    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);

    Array<T> c(nd1_, nullValue_);
    for (auto it=data_.begin() ; it != data_.end(); it++) {
        const auto& ind = (*it).first;
        if ( (ind[1] == dim2) && (ind[2] == dim3) )
            c[ind[0]] = (*it).second;
    }

    return c;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
nct::Array<T> nct::SparseArray3D<T, MapAlloc>::elementsOfDim2(
    size_type dim1, size_type dim3) const
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);

    if (dim3 >= nd3_)
        throw IndexOutOfRangeException("dim3", SOURCE_INFO);

    Array<T> c(nd2_, nullValue_);
    for (auto it=data_.begin() ; it != data_.end(); it++) {
        const auto& ind = (*it).first;
        if ( (ind[0] == dim1) && (ind[2] == dim3) )
            c[ind[1]] = (*it).second;
    }

    return c;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
nct::Array<T> nct::SparseArray3D<T, MapAlloc>::elementsOfDim3(
    size_type dim1, size_type dim2) const
{
    if (dim1 >= nd1_)
        throw IndexOutOfRangeException("dim1", SOURCE_INFO);

    if (dim2 >= nd2_)
        throw IndexOutOfRangeException("dim2", SOURCE_INFO);

    Array<T> c(nd3_, nullValue_);
    for (auto it=data_.begin() ; it != data_.end(); it++) {
        const auto& ind = (*it).first;
        if ( (ind[0] == dim1) && (ind[1] == dim2) )
            c[ind[2]] = (*it).second;
    }

    return c;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
nct::Array<typename nct::SparseArray3D<T, MapAlloc>::index_type>
nct::SparseArray3D<T, MapAlloc>::find(const_reference t) const
{
    Array<index_type> ind;
    if (t == nullValue_) {
        size_type ni = static_cast<size_type>(n_-data_.size());
        ind.resize(ni);

        Array3D<bool> matRel(nd1_, nd2_, nd3_, false);
        for (auto it=data_.begin() ; it != data_.end(); it++) {
            const auto& index = (*it).first;
            matRel(index[0], index[1], index[2]) = true;
        }

        size_type c = 0;
        for (size_type i=0; i<nd1_; i++) {
            for (size_type j=0; j<nd2_; j++) {
                for (size_type k=0; k<nd3_; k++) {
                    if (!matRel(i,j,k)) {
                        ind[c] = index_type(i, j, k);
                        c++;
                    }
                }
            }
        }
    }
    else {
        size_type ni = 0;
        for (auto it=data_.begin() ; it != data_.end(); it++)
            if ( (*it).second == t )
                ni++;

        ind.resize(ni);
        ni = 0;
        for (auto it=data_.begin() ; it != data_.end(); it++) {
            if ( (*it).second == t ) {
                ind[ni] = (*it).first;
                ni++;
            }
        }
    }

    return ind;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
nct::Array<std::pair<typename nct::SparseArray3D<T, MapAlloc>::index_type, T>>
nct::SparseArray3D<T, MapAlloc>::nonNullElements() const
{
    size_type ni = static_cast<size_type>(data_.size());
    Array<std::pair<index_type, T>> el(ni);

    size_type c = 0;
    for (auto it=data_.begin() ; it != data_.end(); it++)
        el[c++] = *it;
        
    return el;
}

//=================================================================================================================
//        I/O OPERATIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc>
nct::SparseArray3D<T, MapAlloc> nct::SparseArray3D<T, MapAlloc>::read(std::istream& i)
{
    // Check for errors.
    if (i.fail())
        throw IOException(exc_bad_input_stream, SOURCE_INFO);

    // Read number of dim2 and number of dim3.
    size_type d = 0;
    size_type r = 0;
    size_type c = 0;
    
    i.read(reinterpret_cast<char*> (&d), sizeof(size_type));
    if (i.fail())
        throw IOException(exc_error_reading_dimension2, SOURCE_INFO);

    i.read(reinterpret_cast<char*> (&r), sizeof(size_type));
    if (i.fail())
        throw IOException(exc_error_reading_dimension2, SOURCE_INFO);

    i.read(reinterpret_cast<char*> (&c), sizeof(size_type));
    if (i.fail())
        throw IOException(exc_error_reading_dimension3, SOURCE_INFO);

    // Read null value.
    T nvalue;
    i.read(reinterpret_cast<char*> (&nvalue), sizeof(T));
    if (i.fail())
        throw IOException(exc_error_reading_null_value, SOURCE_INFO);

    // Read  non-null values.
    SparseArray3D<T, MapAlloc> arr;
    try {
        auto values = Array<std::pair<index_type, T>>::read(i);

        arr = SparseArray3D<T, MapAlloc>(d, r, c, nvalue);
        size_type nn = values.size();
        for (size_type j = 0; j<nn; j++)
            arr.modify(values[j].first[0], values[j].first[1], values[j].first[2], values[j].second); 
        
    }
    catch (const nct_exception& ex) {
        throw OperationException(exc_error_reading_data, SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw OperationException(exc_error_reading_data, SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_unknown, SOURCE_INFO);
    }
    
    return arr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc>
void nct::SparseArray3D<T, MapAlloc>::write(std::ostream& o) const
{
    // Check for errors.
    if (o.fail())
        throw IOException(exc_bad_output_stream, SOURCE_INFO);
    
    // Write number of dim2 and number of dim3.
    o.write(reinterpret_cast<const char*>(&nd1_), sizeof(size_type));
    if (o.fail())
        throw IOException(exc_error_writing_dimension2, SOURCE_INFO);

    o.write(reinterpret_cast<const char*>(&nd2_), sizeof(size_type));
    if (o.fail())
        throw IOException(exc_error_writing_dimension2, SOURCE_INFO);

    o.write(reinterpret_cast<const char*>(&nd3_), sizeof(size_type));
    if (o.fail())
        throw IOException(exc_error_writing_dimension3, SOURCE_INFO);

    // Write null value.
    o.write(reinterpret_cast<const char*>(&nullValue_), sizeof(T));
    if (o.fail())
        throw IOException(exc_error_writing_null_value, SOURCE_INFO);

    // Write non null values.
    try {
        auto values = nonNullElements();
        values.write(o);

    }
    catch (const nct_exception& ex) {
        throw OperationException(exc_error_writing_data, SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw OperationException(exc_error_writing_data, SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_unknown, SOURCE_INFO);
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc>
std::istream& nct::operator>>(std::istream& i, SparseArray3D<T, MapAlloc>& arr)
{
    arr = SparseArray3D<T, MapAlloc>::read(i);
    return i;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc>
std::ostream& nct::operator<<(std::ostream& o, const SparseArray3D<T, MapAlloc>& other)
{
    o << std::endl;
    o << "Null value: " << other.nullValue() << std::endl;
    
    auto nne = other.nonNullElements();
    for (auto it=nne.begin() ; it != nne.end(); it++)
        o << (*it).first << " - " << (*it).second << std::endl;     

    return o;
}

//=================================================================================================================
//        AUXILIAR CLASSES
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc>
inline bool nct::SparseArray3D<T, MapAlloc>::IndexComparator::operator()(
    const index_type& ind1, const index_type& ind2) const
{
    return ( (ind1[0]<ind2[0]) ||
           ( (ind1[0]==ind2[0]) && (ind1[1]<ind2[1]) ) || 
           ( (ind1[0]==ind2[0]) && (ind1[1]==ind2[1]) && (ind1[2]<ind2[2]) ) );
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
