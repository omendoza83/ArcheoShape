//=================================================================================================================
/**
 *  @file       Vector2D_template.h
 *  @brief      nct::Vector2D class template implementation file.
 *  @details    This file contains the implementation of the nct::Vector2D class template.
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
template<nct::Numeric T>
constexpr nct::Vector2D<T>::Vector2D(const_reference v1, const_reference v2) noexcept
{
    vc[0] = v1;
    vc[1] = v2;
}

//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr bool nct::Vector2D<T>::operator==(const Vector2D<T>& right) const noexcept
{
    return ((vc[0] == right.vc[0]) && (vc[1] == right.vc[1]));
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr bool nct::Vector2D<T>::operator!=(const Vector2D<T> & right) const noexcept
{
    return ((vc[0] != right.vc[0]) || (vc[1] != right.vc[1]));
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
inline typename nct::Vector2D<T>::reference nct::Vector2D<T>::operator[](size_type i)
{
#ifndef NCT_VECTOR_2D_DISABLE_INDEX_CHECKING
    if (i > 1)
        throw IndexOutOfRangeException("i", i, (size_type)0, (size_type)1,
            RelationalOperator::GreaterThanOrEqualTo,
            RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);
#endif
    return vc[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr typename nct::Vector2D<T>::const_reference nct::Vector2D<T>::operator[](size_type i) const
{
#ifndef NCT_VECTOR_2D_DISABLE_INDEX_CHECKING
    if (i > 1)
        throw IndexOutOfRangeException("i", i, (size_type)0, (size_type)1,
            RelationalOperator::GreaterThanOrEqualTo,
            RelationalOperator::LowerThanOrEqualTo, SOURCE_INFO);
#endif
    return vc[i];
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr nct::Vector2D<T> nct::Vector2D<T>::operator+() const noexcept
{
    return Vector2D<T>(vc[0], vc[1]);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr nct::Vector2D<T> nct::Vector2D<T>::operator+(const Vector2D<T> & right) const noexcept
{
    return Vector2D<T>(vc[0] + right.vc[0], vc[1] + right.vc[1]);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
inline const nct::Vector2D<T>& nct::Vector2D<T>::operator+=(const Vector2D<T> & right) noexcept
{
    vc[0] += right.vc[0];
    vc[1] += right.vc[1];
    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T> template<typename> requires nct::SignedNumeric<T>
constexpr nct::Vector2D<T> nct::Vector2D<T>::operator-() const
{
    return Vector2D<T>(-vc[0], -vc[1]);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr nct::Vector2D<T> nct::Vector2D<T>::operator-(const Vector2D<T> & right) const noexcept
{
    return Vector2D<T>(vc[0] - right.vc[0], vc[1] - right.vc[1]);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
inline const nct::Vector2D<T>& nct::Vector2D<T>::operator-=(const Vector2D<T> & right) noexcept
{
    vc[0] -= right.vc[0];
    vc[1] -= right.vc[1];
    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr nct::Vector2D<T> nct::Vector2D<T>::operator*(const_reference right) const noexcept
{
    return Vector2D<T>(right * vc[0], right * vc[1]);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr nct::Vector2D<T> nct::operator*(const T & left, const Vector2D<T> & right) noexcept
{
    return Vector2D<T>(left * right.v1(), left * right.v2());
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
inline const nct::Vector2D<T>& nct::Vector2D<T>::operator*=(const_reference right) noexcept
{
    vc[0] *= right;
    vc[1] *= right;
    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr nct::Vector2D<T> nct::Vector2D<T>::operator/(const_reference right) const
{
    if (right == 0)
        throw ArithmeticException(exc_div_by_zero, SOURCE_INFO);
    return Vector2D<T>(vc[0] / right, vc[1] / right);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
inline const nct::Vector2D<T> & nct::Vector2D<T>::operator/=(const_reference right)
{
    if (right == 0)
        throw ArithmeticException(exc_div_by_zero, SOURCE_INFO);
    vc[0] /= right;
    vc[1] /= right;
    return *this;
}


//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
inline void nct::Vector2D<T>::setCoefficients(const_reference v1, const_reference v2) noexcept
{
    vc[0] = v1;
    vc[1] = v2;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
inline void nct::Vector2D<T>::normalize() noexcept
{
    double mag = magnitude();
    if (mag == 0)
        mag = 1;
    vc[0]=static_cast<T>(vc[0]/mag);
    vc[1]=static_cast<T>(vc[1]/mag);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
inline typename nct::Vector2D<T>::reference nct::Vector2D<T>::v1() noexcept
{
    return vc[0];
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr typename nct::Vector2D<T>::const_reference nct::Vector2D<T>::v1() const noexcept
{
    return vc[0];
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
inline typename nct::Vector2D<T>::reference nct::Vector2D<T>::v2() noexcept
{
    return vc[1];
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr typename nct::Vector2D<T>::const_reference nct::Vector2D<T>::v2() const noexcept
{
    return vc[1];
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
inline double nct::Vector2D<T>::magnitude() const noexcept
{
    return std::sqrt(static_cast<double>(std::norm(vc[0]))+ 
        static_cast<double>(std::norm(vc[1])));
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr double nct::Vector2D<T>::sqrMagnitude() const noexcept
{
    return static_cast<double>(std::norm(vc[0])) +
        static_cast<double>(std::norm(vc[1]));
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
inline nct::Vector2D<double> nct::Vector2D<T>::unitaryVector() const noexcept
{
    double mag = magnitude();
    if (mag == 0)
        mag = 1;
    return Vector2D<double>(vc[0]/mag, vc[1]/mag);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
inline nct::Vector2D<double> nct::Vector2D<T>::directionalCosines() const noexcept
{
    return unitaryVector();
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
nct::Vector2D<double> nct::Vector2D<T>::directionalAngles() const noexcept
{
    Vector2D<double> dir = unitaryVector();
    dir.v1() = std::acos(static_cast<double>(dir.v1()));
    dir.v2() = std::acos(static_cast<double>(dir.v2()));
    return dir;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
nct::Vector2D<double> nct::Vector2D<T>::cartesianToPolar() const noexcept
{
    double r = magnitude();
    double theta = 0;

    if (r>0)
        theta = std::atan2(static_cast<double>(vc[1]), static_cast<double>(vc[0]));

    return Vector2D<double>(r, theta); 
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
inline nct::Vector2D<double> nct::Vector2D<T>::polarToCartesian() const noexcept
{
    return Vector2D<double>(vc[0]*std::cos(static_cast<double>(vc[1])), 
        vc[0]*std::sin(static_cast<double>(vc[1]))); 
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
inline nct::Vector2D<T> nct::Vector2D<T>::rotate(double theta) const noexcept
{
    T c = static_cast<T>(std::cos(theta));
    T s = static_cast<T>(std::sin(theta));
    return Vector2D<T>(vc[0]*c - vc[1]*s, vc[0]*s + vc[1]*c); 
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr nct::Vector2D<T> nct::Vector2D<T>::translate(const_reference s1, const_reference s2) const noexcept
{
    return Vector2D<T>(vc[0] + s1, vc[1] + s2); 
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr T nct::dotProduct(const Vector2D<T>& u, const Vector2D<T>& v) noexcept
{
    return u.v1()*v.v1() + u.v2()*v.v2();
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
constexpr T nct::crossProduct(const Vector2D<T>& u, const Vector2D<T>& v) noexcept
{
    return u.v1()*v.v2() - u.v2()*v.v1();
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
double nct::angleBetweenVectors(const Vector2D<T>& u, const Vector2D<T>& v) noexcept
{
    double dProd = static_cast<double>(u.v1()*v.v1() + u.v2()*v.v2());
    double mag1 = u.magnitude();
    double mag2 = v.magnitude();
    if (mag1 == 0 || mag2 == 0)
        return 0;
    return std::acos(dProd/(mag1*mag2));
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
nct::Vector2D<double> nct::projection(const Vector2D<T>& u, const Vector2D<T>& v) noexcept
{
    double dProd = static_cast<double>(u.v1()*v.v1() + u.v2()*v.v2());
    double magv = v.sqrMagnitude();
    if (magv==0)
        magv = 1;
    double f = dProd/magv;
    return Vector2D<double>(f*v.v1(), f*v.v2());
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
double nct::triangleArea(const Vector2D<T>& v1, const Vector2D<T>& v2, 
    const Vector2D<T>& v3) noexcept
{
    return std::abs( crossProduct(v2 - v1, v3 - v1) / 2.0);
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
double nct::parallelogramArea(const Vector2D<T>& v1, const Vector2D<T>& v2, 
    const Vector2D<T>& v3) noexcept
{
    return std::abs(static_cast<double>(crossProduct(v2 - v1, v3 - v1)));
}

//=================================================================================================================
//        I/O OPERATIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
nct::Vector2D<T> nct::Vector2D<T>::read(std::istream& i)
{
    // Check for errors.
    if (i.fail())
        throw IOException(exc_bad_input_stream, SOURCE_INFO);

    // Read data.
    Vector2D<T> v;

    i.read(reinterpret_cast<char*> (&v.vc[0]), sizeof(T));
    if (i.fail())
        throw IOException(exc_error_reading_first_component, SOURCE_INFO);

    i.read(reinterpret_cast<char*> (&v.vc[1]), sizeof(T));
    if (i.fail())
        throw IOException(exc_error_reading_second_component, SOURCE_INFO);
    
    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
void nct::Vector2D<T>::write(std::ostream& o) const
{
    // Check for errors.
    if (o.fail())
        throw IOException(exc_bad_output_stream, SOURCE_INFO);
    
    // Write data.
    o.write(reinterpret_cast<const char*>(&vc[0]), sizeof(T));
    if (o.fail())
        throw IOException(exc_error_writing_first_component, SOURCE_INFO);

    o.write(reinterpret_cast<const char*>(&vc[1]), sizeof(T));
    if (o.fail())
        throw IOException(exc_error_writing_second_component, SOURCE_INFO);
    
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
std::istream& nct::operator>>(std::istream& i, Vector2D<T>& v)
{
    char elem = 0;
    T v1 = 0, v2 = 0;

    if (i >> elem && elem != '(') {
        // No leading '(', treat as bad field.
        i.putback(elem);
        i.setstate(std::ios_base::failbit);
    }
    else if (i >> v1 >> elem && elem != ',') {
        // No ',' after item, treat as bad field.
        i.putback(elem);
        i.setstate(std::ios_base::failbit);
    }
    else if (i >> v2 >> elem && elem != ')') {    // No trailing ')' after item, treat as bad field.
        i.putback(elem);
        i.setstate(std::ios_base::failbit);
    }

    // Store valid result.
    if (!i.fail()) {
        v.v1() = v1;
        v.v2() = v2;
    }    
    return i;
}

//-----------------------------------------------------------------------------------------------------------------
template<nct::Numeric T>
std::ostream& nct::operator<<(std::ostream& o, const Vector2D<T>& v)
{
    o << "(" << v.v1() << "," << v.v2() << ")";
    return o;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
