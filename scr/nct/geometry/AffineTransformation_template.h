//=================================================================================================================
/**
 *  @file       AffineTransformation_template.h
 *  @brief      Function templates of the nct::geometry namespace.
 *  @details    Implementation of function templates of the nct::geometry namespace.
 *  @author     Omar Mendoza Montoya (email: omendoz@live.com.mx).
 *  @copyright  Copyright (c) 2012 Omar Mendoza Montoya \n \n
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
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Vector2D<T> nct::geometry::AffineTransformation::transform(const Vector2D<T>& u) const noexcept 
{
    Vector2D<T> v;
    v[0] = static_cast<T>(m_[0][0]*u[0] + m_[0][1]*u[1] + m_[0][2]);
    v[1] = static_cast<T>(m_[1][0]*u[0] + m_[1][1]*u[1] + m_[1][2]);
    
    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Array<nct::Vector2D<T>> nct::geometry::AffineTransformation::transform(
    const Array<Vector2D<T>>& u) const
{
    auto nv = u.size();
    Array<Vector2D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = static_cast<T>(m_[0][0]*u[i][0] + m_[0][1]*u[i][1] + m_[0][2]);
        v[i][1] = static_cast<T>(m_[1][0]*u[i][0] + m_[1][1]*u[i][1] + m_[1][2]);
    }    

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
double nct::geometry::AffineTransformation::rotationAngle(const Vector2D<T>& u, const Vector2D<T>& v) noexcept 
{
    double a =  std::atan2(static_cast<double>(u[0]), static_cast<double>(u[1]));
    double b =  std::atan2(static_cast<double>(v[0]), static_cast<double>(v[1]));
    double rotAng = a - b;
    return math::wrapTo2Pi(rotAng);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Vector2D<T> nct::geometry::AffineTransformation::rotate(const Vector2D<T>& u, const U& theta) noexcept 
{
    double c = std::cos(static_cast<double>(theta));
    double s = std::sin(static_cast<double>(theta));

    Vector2D<T> v; 
    v[0] = static_cast<T>(u[0]*c - u[1]*s);
    v[1] = static_cast<T>(u[0]*s + u[1]*c);

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Array<nct::Vector2D<T>> nct::geometry::AffineTransformation::rotate(
    const Array<Vector2D<T>>& u, const U& theta)
{
    double c = (std::cos(theta));
    double s = (std::sin(theta));

    auto nv = u.size();
    Array<Vector2D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = static_cast<T>(u[i][0]*c - u[i][1]*s);
        v[i][1] = static_cast<T>(u[i][0]*s + u[i][1]*c);
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Vector2D<T> nct::geometry::AffineTransformation::rotateAround(
    const Vector2D<T>& u, const Vector2D<T>& p, const U& theta) noexcept
{
    double c = std::cos(static_cast<double>(theta));
    double s = std::sin(static_cast<double>(theta));

    Vector2D<T> v; 
    v[0] = static_cast<T>((u[0] - p[0])*c - (u[1] - p[1])*s + p[0]);
    v[1] = static_cast<T>((u[0] - p[0])*s + (u[1] - p[1])*c + p[1]);

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Array<nct::Vector2D<T>> nct::geometry::AffineTransformation::rotateAround(
    const Array<Vector2D<T>>& u, const Vector2D<T>& p, const U& theta)
{
    double c = (std::cos(theta));
    double s = (std::sin(theta));

    auto nv = u.size();
    Array<Vector2D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = static_cast<T>((u[i][0] - p[0])*c - (u[i][1] - p[1])*s + p[0]);
        v[i][1] = static_cast<T>((u[i][0] - p[0])*s + (u[i][1] - p[1])*c + p[1]);
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Vector2D<T> nct::geometry::AffineTransformation::translate(
    const Vector2D<T>& u, const T& dx, const T& dy) noexcept
{
    Vector2D<T> v; 
    v[0] = u[0] + dx;
    v[1] = u[1] + dy;

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Array<nct::Vector2D<T>> nct::geometry::AffineTransformation::translate(
    const Array<Vector2D<T>>& u, const T& dx, const T& dy)
{
    auto nv = u.size();
    Array<Vector2D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = u[i][0] + dx;
        v[i][1] = u[i][1] + dy;
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Vector2D<T> nct::geometry::AffineTransformation::translateX(const Vector2D<T>& u, const T& d) noexcept 
{
    Vector2D<T> v; 
    v[0] = u[0] + d;
    v[1] = u[1];

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Array<nct::Vector2D<T>> nct::geometry::AffineTransformation::translateX(
    const Array<Vector2D<T>>& u, const T& d)
{
    auto nv = u.size();
    Array<Vector2D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = u[i][0] + d;
        v[i][1] = u[i][1];
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Vector2D<T> nct::geometry::AffineTransformation::translateY(const Vector2D<T>& u, const T& d) noexcept 
{
    Vector2D<T> v; 
    v[0] = u[0];
    v[1] = u[1] + d;

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Array<nct::Vector2D<T>> nct::geometry::AffineTransformation::translateY(
    const Array<Vector2D<T>>& u, const T& d)
{
    auto nv = u.size();
    Array<Vector2D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = u[i][0];
        v[i][1] = u[i][1] + d;
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Vector2D<T> nct::geometry::AffineTransformation::scale(
    const Vector2D<T>& u, const T& sx, const T& sy) noexcept
{
    Vector2D<T> v; 
    v[0] = u[0] * sx;
    v[1] = u[1] * sy;
    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Array<nct::Vector2D<T>> nct::geometry::AffineTransformation::scale(
    const Array<Vector2D<T>>& u, const T& sx, const T& sy)
{
    auto nv = u.size();
    Array<Vector2D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = u[i][0] * sx;
        v[i][1] = u[i][1] * sy;
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Vector2D<T> nct::geometry::AffineTransformation::scaleX(const Vector2D<T>& u, const T& s) noexcept 
{
    Vector2D<T> v; 
    v[0] = u[0] * s;
    v[1] = u[1];
    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Array<nct::Vector2D<T>> nct::geometry::AffineTransformation::scaleX(
    const Array<Vector2D<T>>& u, const T& s)
{
    auto nv = u.size();
    Array<Vector2D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = u[i][0] * s;
        v[i][1] = u[i][1];
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Vector2D<T> nct::geometry::AffineTransformation::scaleY(const Vector2D<T>& u, const T& s) noexcept 
{
    Vector2D<T> v; 
    v[0] = u[0];
    v[1] = u[1] * s;
    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Array<nct::Vector2D<T>> nct::geometry::AffineTransformation::scaleY(
    const Array<Vector2D<T>>& u, const T& s)
{
    auto nv = u.size();
    Array<Vector2D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = u[i][0];
        v[i][1] = u[i][1] * s;
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Vector2D<T> nct::geometry::AffineTransformation::skew(
    const Vector2D<T>& u, const U& alphax, const U& alphay) noexcept
{
    double a1 = std::tan(static_cast<double>(alphax));
    double a2 = std::tan(static_cast<double>(alphay));

    Vector2D<T> v; 
    v[0] = static_cast<T>(u[0] + u[1]*a1);
    v[1] = static_cast<T>(u[0]*a2 + u[1]);

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Array<nct::Vector2D<T>> nct::geometry::AffineTransformation::skew(
    const Array<Vector2D<T>>& u,
    const U& alphax, const U& alphay)
{
    double a1 = std::tan(static_cast<double>(alphax));
    double a2 = std::tan(static_cast<double>(alphay));

    auto nv = u.size();
    Array<Vector2D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = static_cast<T>(u[i][0] + u[i][1] * a1);
        v[i][1] = static_cast<T>(u[i][0] * a2 + u[i][1]);
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Vector2D<T> nct::geometry::AffineTransformation::skewX(const Vector2D<T>& u, const U& alpha) noexcept 
{
    double a = std::tan(static_cast<double>(alpha));

    Vector2D<T> v; 
    v[0] = static_cast<T>(u[0] + u[1]*a);
    v[1] = static_cast<T>(u[1]);

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Array<nct::Vector2D<T>> nct::geometry::AffineTransformation::skewX(const Array<Vector2D<T>>& u,
    const U& alpha)
{
    double a = std::tan(static_cast<double>(alpha));

    auto nv = u.size();
    Array<Vector2D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = static_cast<T>(u[i][0] + u[i][1] * a);
        v[i][1] = static_cast<T>(u[i][1]);
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Vector2D<T> nct::geometry::AffineTransformation::skewY(const Vector2D<T>& u, const U& alpha) noexcept 
{
    double a = std::tan(static_cast<double>(alpha));

    Vector2D<T> v; 
    v[0] = static_cast<T>(u[0]);
    v[1] = static_cast<T>(u[0]*a + u[1]);

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Array<nct::Vector2D<T>> nct::geometry::AffineTransformation::skewY(const Array<Vector2D<T>>& u,
    const U& alpha)
{
    double a = std::tan(static_cast<double>(alpha));

    auto nv = u.size();
    Array<Vector2D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = static_cast<T>(u[i][0]);
        v[i][1] = static_cast<T>(u[i][0]*a + u[i][1]);
    }

    return v;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
