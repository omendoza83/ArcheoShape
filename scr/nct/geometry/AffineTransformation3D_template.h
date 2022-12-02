//=================================================================================================================
/**
 *  @file       AffineTransformation3D_template.h
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
nct::Vector3D<T> nct::geometry::AffineTransformation3D::transform(const Vector3D<T>& u) const noexcept 
{
    Vector3D<T> v;
    v[0] = static_cast<T>(m_[0][0]*u[0] + m_[0][1]*u[1] + m_[0][2]*u[2] + m_[0][3]);
    v[1] = static_cast<T>(m_[1][0]*u[0] + m_[1][1]*u[1] + m_[1][2]*u[2] + m_[1][3]);
    v[2] = static_cast<T>(m_[2][0]*u[0] + m_[2][1]*u[1] + m_[2][2]*u[2] + m_[2][3]);
    
    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::transform(
    const Array<Vector3D<T>>& u) const
{
    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = static_cast<T>(m_[0][0]*u[i][0] + m_[0][1]*u[i][1] + m_[0][2]*u[i][2] + m_[0][3]);
        v[i][1] = static_cast<T>(m_[1][0]*u[i][0] + m_[1][1]*u[i][1] + m_[1][2]*u[i][2] + m_[1][3]);
        v[i][2] = static_cast<T>(m_[2][0]*u[i][0] + m_[2][1]*u[i][1] + m_[2][2]*u[i][2] + m_[2][3]);
    }    

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
std::tuple<nct::Vector3D<double>, double> nct::geometry::AffineTransformation3D::rotationSystem(
    const Vector3D<T>& u, const Vector3D<T>& v)
{
    Vector3D<double> ud;
    ud[0] = static_cast<double>(u[0]);
    ud[1] = static_cast<double>(u[1]);
    ud[2] = static_cast<double>(u[2]);

    Vector3D<double> vd;
    vd[0] = static_cast<double>(v[0]);
    vd[1] = static_cast<double>(v[1]);
    vd[2] = static_cast<double>(v[2]);

    auto theta = angleBetweenVectors(v, u);
    auto w = crossProduct(ud, vd);
    if (w.magnitude() == 0)
        throw OperationException(exc_bad_rotation_axis, SOURCE_INFO);
    w.normalize();

    return std::make_tuple(w, theta);
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::rotate(const Vector3D<T>& u,
    const Vector3D<U>& w, U theta)
{
    if (w.magnitude() == 0)
        throw ArgumentException("w", exc_bad_rotation_axis, SOURCE_INFO);

    Vector3D<U> ww = w;
    ww.normalize();

    Vector3D<U> ud;
    ud[0] = static_cast<U>(u[0]);
    ud[1] = static_cast<U>(u[1]);
    ud[2] = static_cast<U>(u[2]);

    Vector3D<U> wv = crossProduct(ww, ud);

    double c = std::cos(static_cast<double>(theta));
    double s = std::sin(static_cast<double>(theta));
    double d = ((1-c))*dotProduct(ud, ww);
    
    Vector3D<T> v; 
    v[0] = static_cast<T>(c * ud[0] + s*wv[0] + d*ww[0]);
    v[1] = static_cast<T>(c * ud[1] + s*wv[1] + d*ww[1]);
    v[2] = static_cast<T>(c * ud[2] + s*wv[2] + d*ww[2]);

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::rotate(const Array<Vector3D<T>>& u,
    const Vector3D<U>& w, U theta)
{
    if (w.magnitude() == 0)
        throw ArgumentException("w", exc_bad_rotation_axis, SOURCE_INFO);

    double c = std::cos(static_cast<double>(theta));
    double s = std::sin(static_cast<double>(theta));
    double d = 0;

    Vector3D<U> ww = w;
    ww.normalize();
    
    Vector3D<U> ud;
    Vector3D<U> wv; 
    auto nv = u.size();
    Array<Vector3D<T>> v(nv); 
    for (index_t i = 0; i<nv; i++) {        
        ud[0] = static_cast<U>(u[i][0]);
        ud[1] = static_cast<U>(u[i][1]);
        ud[2] = static_cast<U>(u[i][2]);
        
        wv = crossProduct(ww, ud);
        d = ((1-c))*dotProduct(ud, ww);

        v[i][0] = static_cast<T>(c * u[i][0] + s*wv[0] + d*ww[0]);
        v[i][1] = static_cast<T>(c * u[i][1] + s*wv[1] + d*ww[1]);
        v[i][2] = static_cast<T>(c * u[i][2] + s*wv[2] + d*ww[2]);
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::rotateX(const nct::Vector3D<T>& u, U theta) noexcept 
{
    double c = std::cos(static_cast<double>(theta));
    double s = std::sin(static_cast<double>(theta));

    Vector3D<T> v; 
    v[0] = static_cast<T>(u[0]);
    v[1] = static_cast<T>(u[1]*c - u[2]*s);
    v[2] = static_cast<T>(u[1]*s + u[2]*c);

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::rotateX(
    const Array<Vector3D<T>>& u, U theta)
{
    double c = std::cos(static_cast<double>(theta));
    double s = std::sin(static_cast<double>(theta));

    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = static_cast<T>(u[i][0]);
        v[i][1] = static_cast<T>(u[i][1]*c - u[i][2]*s);
        v[i][2] = static_cast<T>(u[i][1]*s + u[i][2]*c);
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::rotateY(const Vector3D<T>& u, U theta) noexcept 
{
    double c = std::cos(static_cast<double>(theta));
    double s = std::sin(static_cast<double>(theta));

    Vector3D<T> v; 
    v[0] = static_cast<T>( u[0]*c + u[2]*s);
    v[1] = static_cast<T>( u[1]);
    v[2] = static_cast<T>(-u[0]*s + u[2]*c);
    
    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::rotateY(
    const Array<Vector3D<T>>& u, U theta)
{
    double c = std::cos(static_cast<double>(theta));
    double s = std::sin(static_cast<double>(theta));

    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = static_cast<T>( u[i][0]*c + u[i][2]*s);
        v[i][1] = static_cast<T>( u[i][1]);
        v[i][2] = static_cast<T>(-u[i][0]*s + u[i][2]*c);
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::rotateZ(const Vector3D<T>& u, U theta) noexcept 
{
    double c = std::cos(static_cast<double>(theta));
    double s = std::sin(static_cast<double>(theta));

    Vector3D<T> v; 
    v[0] = static_cast<T>(u[0]*c - u[1]*s);
    v[1] = static_cast<T>(u[0]*s + u[1]*c);
    v[2] = static_cast<T>(u[2]);

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::rotateZ(
    const Array<Vector3D<T>>& u, U theta)
{
    double c = std::cos(static_cast<double>(theta));
    double s = std::sin(static_cast<double>(theta));

    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = static_cast<T>(u[i][0]*c - u[i][1]*s);
        v[i][1] = static_cast<T>(u[i][0]*s + u[i][1]*c);
        v[i][2] = static_cast<T>(u[i][2]);

    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::translate(
    const Vector3D<T>& u, const T& dx, const T& dy, const T& dz) noexcept
{
    Vector3D<T> v; 
    v[0] = u[0] + dx;
    v[1] = u[1] + dy;
    v[2] = u[2] + dz;

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::translate(
    const Array<Vector3D<T>>& u, const T& dx, const T& dy, const T& dz)
{
    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = u[i][0] + dx;
        v[i][1] = u[i][1] + dy;
        v[i][2] = u[i][2] + dz;
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::translateX(
    const Vector3D<T>& u, const T& d) noexcept
{
    Vector3D<T> v; 
    v[0] = u[0] + d;
    v[1] = u[1];
    v[2] = u[2];

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::translateX(
    const Array<Vector3D<T>>& u, const T& d)
{
    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = u[i][0] + d;
        v[i][1] = u[i][1];
        v[i][2] = u[i][2];
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::translateY(
    const Vector3D<T>& u, const T& d) noexcept
{
    Vector3D<T> v; 
    v[0] = u[0];
    v[1] = u[1] + d;
    v[2] = u[2];

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::translateY(
    const Array<Vector3D<T>>& u, const T& d)
{
    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = u[i][0];
        v[i][1] = u[i][1] + d;
        v[i][2] = u[i][2];
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::translateZ(
    const Vector3D<T>& u, const T& d) noexcept
{
    Vector3D<T> v; 
    v[0] = u[0];
    v[1] = u[1];
    v[2] = u[2] + d;

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::translateZ(
    const Array<Vector3D<T>>& u, const T& d)
{
    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = u[i][0];
        v[i][1] = u[i][1];
        v[i][2] = u[i][2] + d;
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::scale(
    const Vector3D<T>& u, const T& sx, const T& sy, const T& sz) noexcept
{
    Vector3D<T> v; 
    v[0] = u[0] * sx;
    v[1] = u[1] * sy;
    v[2] = u[2] * sz;

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::scale(
    const Array<Vector3D<T>>& u, const T& sx, const T& sy, const T& sz)
{
    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = u[i][0] * sx;
        v[i][1] = u[i][1] * sy;
        v[i][2] = u[i][2] * sz;
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::scaleX(const Vector3D<T>& u, const T& s) noexcept 
{
    Vector3D<T> v; 
    v[0] = u[0] * s;
    v[1] = u[1];
    v[2] = u[2];

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::scaleX(
    const Array<Vector3D<T>>& u, const T& s)
{
    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = u[i][0] * s;
        v[i][1] = u[i][1];
        v[i][2] = u[i][2];
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::scaleY(
    const Vector3D<T>& u, const T& s) noexcept
{
    Vector3D<T> v; 
    v[0] = u[0];
    v[1] = u[1] * s;
    v[2] = u[2];

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::scaleY(
    const Array<Vector3D<T>>& u, const T& s)
{
    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = u[i][0];
        v[i][1] = u[i][1] * s;
        v[i][2] = u[i][2];
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::scaleZ(const Vector3D<T>& u, const T& s) noexcept 
{
    Vector3D<T> v; 
    v[0] = u[0];
    v[1] = u[1];
    v[2] = u[2] * s;

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::scaleZ(
    const Array<Vector3D<T>>& u, const T& s)
{
    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = u[i][0];
        v[i][1] = u[i][1];
        v[i][2] = u[i][2] * s;
    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::skewXY(const Vector3D<T>& u, const U& alpha) noexcept 
{
    double a = std::tan(static_cast<double>(alpha));

    Vector3D<T> v; 
    v[0] = static_cast<T>(u[0] + a*u[1]);
    v[1] = static_cast<T>(u[1]);
    v[2] = static_cast<T>(u[2]);

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::skewXY(
    const Array<Vector3D<T>>& u, const U& alpha)
{
    double a = std::tan(static_cast<double>(alpha));

    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = static_cast<T>(u[i][0] + a*u[i][1]);
        v[i][1] = static_cast<T>(u[i][1]);
        v[i][2] = static_cast<T>(u[i][2]);

    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::skewYX(const Vector3D<T>& u, const U& alpha) noexcept 
{
    double a = std::tan(static_cast<double>(alpha));

    Vector3D<T> v; 
    v[0] = static_cast<T>(u[0]);
    v[1] = static_cast<T>(u[1] + a*u[0]);
    v[2] = static_cast<T>(u[2]);

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::skewYX(
    const Array<Vector3D<T>>& u, const U& alpha)
{
    double a = std::tan(static_cast<double>(alpha));

    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = static_cast<T>(u[i][0]);
        v[i][1] = static_cast<T>(u[i][1] + a*u[i][0]);
        v[i][2] = static_cast<T>(u[i][2]);

    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::skewXZ(const Vector3D<T>& u, const U& alpha) noexcept 
{
    double a = std::tan(static_cast<double>(alpha));

    Vector3D<T> v; 
    v[0] = static_cast<T>(u[0] + a*u[2]);
    v[1] = static_cast<T>(u[1]);
    v[2] = static_cast<T>(u[2]);

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::skewXZ(
    const Array<Vector3D<T>>& u, const U& alpha)
{
    double a = std::tan(static_cast<double>(alpha));

    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = static_cast<T>(u[i][0] + a*u[i][2]);
        v[i][1] = static_cast<T>(u[i][1]);
        v[i][2] = static_cast<T>(u[i][2]);

    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::skewZX(const Vector3D<T>& u, const U& alpha) noexcept 
{
    double a = std::tan(static_cast<double>(alpha));

    Vector3D<T> v; 
    v[0] = static_cast<T>(u[0]);
    v[1] = static_cast<T>(u[1]);
    v[2] = static_cast<T>(u[2] + a*u[0]);

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::skewZX(
    const Array<Vector3D<T>>& u, const U& alpha)
{
    double a = std::tan(static_cast<double>(alpha));

    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = static_cast<T>(u[i][0]);
        v[i][1] = static_cast<T>(u[i][1]);
        v[i][2] = static_cast<T>(u[i][2] + a*u[i][0]);

    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::skewYZ(const Vector3D<T>& u, const U& alpha) noexcept 
{
    double a = std::tan(static_cast<double>(alpha));

    Vector3D<T> v; 
    v[0] = static_cast<T>(u[0]);
    v[1] = static_cast<T>(u[1] + a*u[2]);
    v[2] = static_cast<T>(u[2]);

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::skewYZ(
    const Array<Vector3D<T>>& u, const U& alpha)
{
    double a = std::tan(static_cast<double>(alpha));

    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = static_cast<T>(u[i][0]);
        v[i][1] = static_cast<T>(u[i][1] + a*u[i][2]);
        v[i][2] = static_cast<T>(u[i][2]);

    }

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Vector3D<T> nct::geometry::AffineTransformation3D::skewZY(const Vector3D<T>& u, const U& alpha) noexcept 
{
    double a = std::tan(static_cast<double>(alpha));

    Vector3D<T> v; 
    v[0] = static_cast<T>(u[0]);
    v[1] = static_cast<T>(u[1]);
    v[2] = static_cast<T>(u[2] + a*u[1]);

    return v;
}

//-----------------------------------------------------------------------------------------------------------------
template<typename T, nct::Arithmetic U>
nct::Array<nct::Vector3D<T>> nct::geometry::AffineTransformation3D::skewZY(
    const Array<Vector3D<T>>& u, const U& alpha)
{
    double a = std::tan(static_cast<double>(alpha));

    auto nv = u.size();
    Array<Vector3D<T>> v(nv);
    for (index_t i = 0; i<nv; i++) {
        v[i][0] = static_cast<T>(u[i][0]);
        v[i][1] = static_cast<T>(u[i][1]);
        v[i][2] = static_cast<T>(u[i][2] + a*u[i][1]);

    }

    return v;
}

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
