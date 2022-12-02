//=================================================================================================================
/**
 *  @file       SparseArray2D_template.h
 *  @brief      nct::SparseArray2D class implementation file.
 *  @details    This file contains the implementation of the nct::SparseArray2D class template.
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
nct::SparseArray2D<T, MapAlloc>::SparseArray2D(const_reference nullValue) : 
nr_{0}, nc_{0}, n_{0}, nullValue_{nullValue}
{

}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
nct::SparseArray2D<T, MapAlloc>::SparseArray2D(size_type rows, size_type columns, 
    const_reference nullValue) : nr_{0}, nc_{0}, n_{0}, nullValue_{nullValue}
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
template<typename T, typename MapAlloc>
nct::SparseArray2D<T, MapAlloc>::SparseArray2D(const SparseArray2D<T, MapAlloc>& other)
{
    try {
        nr_ = other.nr_;
        nc_ = other.nc_;
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
nct::SparseArray2D<T, MapAlloc>::SparseArray2D(SparseArray2D<T, MapAlloc>&& other) noexcept
{
    nr_ = other.nr_;
    nc_ = other.nc_;
    n_ = other.n_;
    nullValue_ = other.nullValue_;
    data_ = std::move(other.data_);

    other.nr_ = 0;
    other.nc_ = 0;
    other.n_ = 0;
}

//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc>
nct::SparseArray2D<T, MapAlloc>&
nct::SparseArray2D<T, MapAlloc>::operator=(const SparseArray2D<T, MapAlloc>& other)
{
    if (&data_ == &other.data_)
        return *this;

    nr_ = other.nr_;
    nc_ = other.nc_;
    n_ = other.n_;
    nullValue_ = other.nullValue_;
    data_ = other.data_;

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc>
nct::SparseArray2D<T, MapAlloc>&
nct::SparseArray2D<T, MapAlloc>::operator=(SparseArray2D<T, MapAlloc>&& other) noexcept
{
    if (&data_ == &other.data_)
        return *this;

    nr_ = other.nr_;
    nc_ = other.nc_;
    n_ = other.n_;
    nullValue_ = other.nullValue_;
    data_ = std::move(other.data_);

    other.nr_ = 0;
    other.nc_ = 0;
    other.n_ = 0;

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc>
bool nct::SparseArray2D<T, MapAlloc>::operator==(const SparseArray2D<T, MapAlloc>& right)
{
    if (&data_ == &right.data_)
        return true;

    if ((nr_ != right.nr_) || (nc_ != right.nc_))
        return false;

    for (auto it = data_.begin(); it != data_.end(); it++) {
        const auto& ind = (*it).first;
        if (((*it).second) != (right(ind[0], ind[1])))
            return false;
    }

    for (auto it = right.data_.begin(); it != right.data_.end(); it++) {
        const auto& ind = (*it).first;
        if (((*it).second) != ((*this)(ind[0], ind[1])))
            return false;
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc>
bool nct::SparseArray2D<T, MapAlloc>::operator!=(const SparseArray2D<T, MapAlloc> & right)
{
    return !(*this == right);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc>
inline typename nct::SparseArray2D<T, MapAlloc>::
const_reference nct::SparseArray2D<T, MapAlloc>::operator()(
    size_type i, size_type j) const
{
#ifndef NCT_SPARSE_ARRAY_2D_DISABLE_INDEX_CHECKING
    if (i >= nr_)
        throw IndexOutOfRangeException("i", SOURCE_INFO);
    if (j >= nc_)
        throw IndexOutOfRangeException("j", SOURCE_INFO);
#endif
    auto it = data_.find(index_type(i, j));
    if (it == data_.end())
        return nullValue_;
    return (*it).second;
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
void nct::SparseArray2D<T, MapAlloc>::resize(size_type rows, size_type columns)
{    
    if ( (nc_ != columns) || (nr_ != rows) ) {
        clear();
        nc_ = columns;
        nr_ = rows;
        n_ = columns*rows;        
    }
    data_.clear();
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
void nct::SparseArray2D<T, MapAlloc>::clear() noexcept
{
    nr_ = 0;
    nc_ = 0;
    n_ = 0;
    data_.clear();
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
void nct::SparseArray2D<T, MapAlloc>::copy(const SparseArray2D& other)
{
    if (data_ == other.data_)
        return;
    
    clear();
    nc_ = other.nc_;
    nr_ = other.nr_;
    n_ = other.n_;
    nullValue_ = other.nullValue_;
    data_ = other.data_;    
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
inline typename nct::SparseArray2D<T, MapAlloc>::size_type
nct::SparseArray2D<T, MapAlloc>::rows() const noexcept
{
    return nr_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
inline typename nct::SparseArray2D<T, MapAlloc>::size_type
nct::SparseArray2D<T, MapAlloc>::columns() const noexcept
{
    return nc_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
inline typename nct::SparseArray2D<T, MapAlloc>::size_type 
nct::SparseArray2D<T, MapAlloc>::size() const noexcept
{
    return n_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
inline typename nct::SparseArray2D<T, MapAlloc>::size_type
 nct::SparseArray2D<T, MapAlloc>::numberOfNonNullElements() const noexcept
{
    return static_cast<size_type>(data_.size());
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
inline typename nct::SparseArray2D<T, MapAlloc>::const_reference
 nct::SparseArray2D<T, MapAlloc>::nullValue() const noexcept
{
    return nullValue_;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
inline typename nct::SparseArray2D<T, MapAlloc>::const_reference
nct::SparseArray2D<T, MapAlloc>::at(
    size_type row, size_type column) const
{
    if (row >= nr_)
        throw IndexOutOfRangeException("row", SOURCE_INFO);
    if (column >= nc_)
        throw IndexOutOfRangeException("column", SOURCE_INFO);
    
    auto it = data_.find(index_type(row, column));
    if (it == data_.end())
        return nullValue_;
    return (*it).second;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
void nct::SparseArray2D<T, MapAlloc>::modify(
    size_type row, size_type column, const_reference val)
{
    if (row >= nr_)
        throw IndexOutOfRangeException("row", SOURCE_INFO);
    if (column >= nc_)
        throw IndexOutOfRangeException("column", SOURCE_INFO);
    index_type ind(row, column);
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
nct::Array2D<T> nct::SparseArray2D<T, MapAlloc>::toArray() const
{
    Array2D<T> r(nr_, nc_, nullValue_);
    for (auto it=data_.begin() ; it != data_.end(); it++)
        r((*it).first[0], (*it).first[1]) = (*it).second;    

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
nct::Array<T> nct::SparseArray2D<T, MapAlloc>::row(size_type row) const
{
    if (row >= nr_)
        throw IndexOutOfRangeException("row", SOURCE_INFO);
    

    Array<T> r(nc_, nullValue_);
    for (auto it=data_.begin() ; it != data_.end(); it++) {
        const auto& ind = (*it).first;
        if (ind[0] == row)
            r[ind[1]] = (*it).second;
    }

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
nct::Array<T> nct::SparseArray2D<T, MapAlloc>::column(size_type column) const
{
    if (column >= nc_)
        throw IndexOutOfRangeException("column", SOURCE_INFO);

    Array<T> c(nr_, nullValue_);
    for (auto it=data_.begin() ; it != data_.end(); it++) {
        const auto& ind = (*it).first;
        if (ind[1] == column)
            c[ind[0]] = (*it).second;
    }

    return c;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc> 
nct::Array<typename nct::SparseArray2D<T, MapAlloc>::index_type>
nct::SparseArray2D<T, MapAlloc>::find(const_reference t) const
{
    Array<index_type> ind;
    if (t == nullValue_) {
        size_type ni = static_cast<size_type>(n_-data_.size());
        ind.resize(ni);

        Array2D<bool> matRel(nr_, nc_, false);
        for (auto it=data_.begin() ; it != data_.end(); it++) {
            const auto& index = (*it).first;
            matRel(index[0], index[1]) = true;
        }

        size_type c = 0;
        for (size_type i=0; i<nr_; i++) {
            for (size_type j=0; j<nc_; j++) {
                if (!matRel(i,j)) {
                    ind[c] = index_type(i, j);
                    c++;
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
nct::Array<std::pair<typename nct::SparseArray2D<T, MapAlloc>::index_type, T>> 
nct::SparseArray2D<T, MapAlloc>::nonNullElements() const
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
nct::SparseArray2D<T, MapAlloc> 
nct::SparseArray2D<T, MapAlloc>::read(std::istream& i)
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

    // Read null value.
    T nvalue;
    i.read(reinterpret_cast<char*> (&nvalue), sizeof(T));
    if (i.fail())
        throw IOException(exc_error_reading_null_value, SOURCE_INFO);

    // Read non-null values.
    SparseArray2D<T, MapAlloc> arr;
    try {
        auto values = Array<std::pair<index_type, T>>::read(i);

        arr = SparseArray2D<T, MapAlloc>(r, c, nvalue);
        size_type nn = values.size();
        for (size_type j = 0; j<nn; j++)
            arr.modify(values[j].first[0], values[j].first[1], values[j].second); 
        
    }
    catch (const nct_exception& ex) {
        throw OperationException(exc_error_reading_data,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw OperationException(exc_error_reading_data, 
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_unknown, SOURCE_INFO);
    }

    return arr;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc>
void nct::SparseArray2D<T, MapAlloc>::write(std::ostream& o) const
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
        throw OperationException(exc_error_writing_data,
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (const std::exception& ex) {
        throw OperationException(exc_error_writing_data, 
            SOURCE_INFO, std::make_exception_ptr(ex));
    }
    catch (...) {
        throw OperationException(exc_unknown, SOURCE_INFO);
    }
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc>
std::istream& nct::operator>>(std::istream& i, SparseArray2D<T, MapAlloc>& arr)
{
    arr = SparseArray2D<T, MapAlloc>::read(i);
    return i;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, typename MapAlloc>
std::ostream& nct::operator<<(std::ostream& o, const SparseArray2D<T, MapAlloc>& other)
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
inline bool nct::SparseArray2D<T, MapAlloc>::IndexComparator::operator()(const index_type& ind1,
    const index_type& ind2) const
{
    return ( (ind1[0]<ind2[0]) || 
           ( (ind1[0]==ind2[0]) && (ind1[1]<ind2[1]) ) );
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
