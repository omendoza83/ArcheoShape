//=================================================================================================================
/**
 *  @file       AffineTransformation.cpp
 *  @brief      nct::geometry::AffineTransformation class implementation file.
 *  @details    This file contains the implementation of the nct::geometry::AffineTransformation class.
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
//        HEADERS AND NAMESPACES
//=================================================================================================================
#include <nct/geometry/AffineTransformation.h>

//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation::AffineTransformation(double ma00, double ma01, double ma02,
    double ma10, double ma11, double ma12) noexcept
{
    m_[0][0] = ma00;
    m_[0][1] = ma01;
    m_[0][2] = ma02;

    m_[1][0] = ma10;
    m_[1][1] = ma11;
    m_[1][2] = ma12;
}

//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::AffineTransformation::operator==(const AffineTransformation& right) const noexcept 
{
    return 
        (m_[0][0] == right.m_[0][0]) && (m_[0][1] == right.m_[0][1]) && (m_[0][2] == right.m_[0][2]) &&
        (m_[1][0] == right.m_[1][0]) && (m_[1][1] == right.m_[1][1]) && (m_[1][2] == right.m_[1][2]);
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::AffineTransformation::operator!=(const AffineTransformation& right) const noexcept
{
    return !(*this == right);
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation::operator()(size_t i, size_t j)
{
    if (i >= 2)
        throw IndexOutOfRangeException("i", SOURCE_INFO);

    if (j >= 3)
        throw IndexOutOfRangeException("j", SOURCE_INFO);

    return m_[i][j];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation::operator()(size_t i, size_t j) const
{
    if (i >= 2)
        throw IndexOutOfRangeException("i", SOURCE_INFO);

    if (j >= 3)
        throw IndexOutOfRangeException("j", SOURCE_INFO);

    return m_[i][j];
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation nct::geometry::AffineTransformation::operator+() const noexcept 
{
    return (*this);
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation nct::geometry::AffineTransformation::operator+(
    const AffineTransformation& right) const noexcept
{
    return AffineTransformation(
        m_[0][0] + right.m_[0][0], m_[0][1] + right.m_[0][1], m_[0][2] + right.m_[0][2],
        m_[1][0] + right.m_[1][0], m_[1][1] + right.m_[1][1], m_[1][2] + right.m_[1][2]);
}

//-----------------------------------------------------------------------------------------------------------------
const nct::geometry::AffineTransformation& nct::geometry::AffineTransformation::operator+=(
    const AffineTransformation& right) noexcept
{
    m_[0][0] += right.m_[0][0];
    m_[0][1] += right.m_[0][1];
    m_[0][2] += right.m_[0][2];

    m_[1][0] += right.m_[1][0];
    m_[1][1] += right.m_[1][1];
    m_[1][2] += right.m_[1][2];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation nct::geometry::AffineTransformation::operator-() const noexcept
{
    return AffineTransformation(
        -m_[0][0], -m_[0][1], -m_[0][2],
        -m_[1][0], -m_[1][1], -m_[1][2]);
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation nct::geometry::AffineTransformation::operator-(
    const AffineTransformation& right) const noexcept
{
    return AffineTransformation(
        m_[0][0] - right.m_[0][0], m_[0][1] - right.m_[0][1], m_[0][2] - right.m_[0][2],
        m_[1][0] - right.m_[1][0], m_[1][1] - right.m_[1][1], m_[1][2] - right.m_[1][2]);
}

//-----------------------------------------------------------------------------------------------------------------
const nct::geometry::AffineTransformation& nct::geometry::AffineTransformation::operator-=(
    const AffineTransformation& right) noexcept
{
    m_[0][0] -= right.m_[0][0];
    m_[0][1] -= right.m_[0][1];
    m_[0][2] -= right.m_[0][2];

    m_[1][0] -= right.m_[1][0];
    m_[1][1] -= right.m_[1][1];
    m_[1][2] -= right.m_[1][2];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation nct::geometry::AffineTransformation::operator*(
    const AffineTransformation& right) const noexcept
{
    AffineTransformation tt;

    tt.m_[0][0] = m_[0][0]*right.m_[0][0] + m_[0][1]*right.m_[1][0];
    tt.m_[0][1] = m_[0][0]*right.m_[0][1] + m_[0][1]*right.m_[1][1];
    tt.m_[0][2] = m_[0][0]*right.m_[0][2] + m_[0][1]*right.m_[1][2] + m_[0][2];

    tt.m_[1][0] = m_[1][0]*right.m_[0][0] + m_[1][1]*right.m_[1][0];
    tt.m_[1][1] = m_[1][0]*right.m_[0][1] + m_[1][1]*right.m_[1][1];
    tt.m_[1][2] = m_[1][0]*right.m_[0][2] + m_[1][1]*right.m_[1][2] + m_[1][2];

    return tt;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::geometry::AffineTransformation& nct::geometry::AffineTransformation::operator*=(
    const AffineTransformation& right) noexcept
{
    auto tt = (*this)*right;
    (*this) = tt;
    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation nct::geometry::AffineTransformation::operator*(
    double right) const noexcept
{
    return AffineTransformation(
        m_[0][0] * right, m_[0][1] * right, m_[0][2] * right,
        m_[1][0] * right, m_[1][1] * right, m_[1][2] * right);
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation nct::geometry::operator*(double left,
    const nct::geometry::AffineTransformation& right) noexcept 
{
    return nct::geometry::AffineTransformation(
        right.m00() * left, right.m01() * left, right.m02() * left,
        right.m10() * left, right.m11() * left, right.m12() * left);
}

//-----------------------------------------------------------------------------------------------------------------
const nct::geometry::AffineTransformation& nct::geometry::AffineTransformation::operator*=(
    double right) noexcept 
{
    m_[0][0] *= right;
    m_[0][1] *= right;
    m_[0][2] *= right;

    m_[1][0] *= right;
    m_[1][1] *= right;
    m_[1][2] *= right;

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation nct::geometry::AffineTransformation::operator/(double right) const noexcept
{
    return AffineTransformation(
        m_[0][0] / right, m_[0][1] / right, m_[0][2] / right,
        m_[1][0] / right, m_[1][1] / right, m_[1][2] / right);
}

//-----------------------------------------------------------------------------------------------------------------
const nct::geometry::AffineTransformation& nct::geometry::AffineTransformation::operator/=(double right) noexcept 
{
    m_[0][0] /= right;
    m_[0][1] /= right;
    m_[0][2] /= right;

    m_[1][0] /= right;
    m_[1][1] /= right;
    m_[1][2] /= right;

    return *this;
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation::m00() noexcept
{
    return m_[0][0];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation::m00() const noexcept
{
    return m_[0][0];
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation::m01() noexcept
{
    return m_[0][1];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation::m01() const noexcept
{
    return m_[0][1];
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation::m02() noexcept 
{
    return m_[0][2];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation::m02() const noexcept 
{
    return m_[0][2];
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation::m10() noexcept
{
    return m_[1][0];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation::m10() const noexcept 
{
    return m_[1][0];
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation::m11() noexcept
{
    return m_[1][1];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation::m11() const noexcept
{
    return m_[1][1];
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation::m12() noexcept
{
    return m_[1][2];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation::m12() const noexcept
{
    return m_[1][2];
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation::reset() noexcept 
{
    m_[0][0] = 1;
    m_[0][1] = 0;
    m_[0][2] = 0;

    m_[1][0] = 0;
    m_[1][1] = 1;
    m_[1][2] = 0;
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::AffineTransformation::isUnitary() const noexcept 
{
    if ((m_[0][0] == 1) && (m_[0][1] == 0) && (m_[0][2] == 0) &&
        (m_[1][0] == 0) && (m_[1][1] == 1) && (m_[1][2] == 0))
        return true;

    return false;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation::addTransformation(const AffineTransformation& tm) noexcept 
{
    (*this) = tm * (*this);
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation::addRotation(double theta) noexcept
{
    addTransformation(rotationMatrix(theta));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation::addRotationAround(const Point2D& p, double theta) noexcept
{
    addTransformation(rotationAroundMatrix(p, theta));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation::addTranslation(double dx, double dy) noexcept
{
    m_[0][2] += dx;
    m_[1][2] += dy;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation::addTranslationX(double d) noexcept 
{
    m_[0][2] += d;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation::addTranslationY(double d) noexcept 
{
    m_[1][2] += d;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation::addScaling(double sx, double sy) noexcept
{
    m_[0][0] *= sx;
    m_[1][1] *= sy;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation::addScalingX(double s) noexcept
{
    m_[0][0] *= s;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation::addScalingY(double s) noexcept 
{
    m_[1][1] *= s;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation::addSkew(double alpha1, double alpha2) noexcept 
{
    addTransformation(skewMatrix(alpha1, alpha2));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation::addSkewX(double alpha) noexcept 
{
    addTransformation(skewMatrix(alpha, 0.0));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation::addSkewY(double alpha) noexcept
{
    addTransformation(skewMatrix(0.0, alpha));
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation nct::geometry::AffineTransformation::rotationMatrix(double theta) noexcept 
{
    double c = (std::cos(theta));
    double s = (std::sin(theta));
    return AffineTransformation(c, -s, 0, s, c, 0);
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation nct::geometry::AffineTransformation::rotationAroundMatrix(
    const Point2D& p, double theta) noexcept
{
    double c = (std::cos(theta));
    double s = (std::sin(theta));
    return AffineTransformation(c, -s, -c*p[0] + s*p[1] + p[0], s, c, -s*p[0] - c*p[1] + p[1]);
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation nct::geometry::AffineTransformation::translationMatrix(
    double dx, double dy) noexcept
{
    return AffineTransformation(1, 0, dx, 0, 1, dy);
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation nct::geometry::AffineTransformation::scalingMatrix(
    double sx, double sy) noexcept
{
    return AffineTransformation(sx, 0, 0, 0, sy, 0);
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation nct::geometry::AffineTransformation::skewMatrix(
    double alpha1, double alpha2) noexcept
{
    double a1 = std::tan(alpha1);
    double a2 = std::tan(alpha2);
    return AffineTransformation(1, a1, 0, a2, 1, 0);
}

//=================================================================================================================
//        I/O OPERATIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation nct::geometry::AffineTransformation::read(std::istream& i) 
{
    AffineTransformation tm;

    // Check for errors.
    if (i.fail())
        throw IOException(exc_bad_input_stream, SOURCE_INFO);

    i.read(reinterpret_cast<char*> (tm.m_), sizeof(double) * 6);
    if (i.fail())
        throw IOException(exc_error_reading_data, SOURCE_INFO);

    return tm;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation::write(std::ostream& o) const
{
    // Check for errors.
    if (o.fail())
        throw IOException(exc_bad_output_stream, SOURCE_INFO);
    
    // Write data.
    o.write(reinterpret_cast<const char*> (m_), sizeof(double)*6);    
    if (o.fail())
        throw IOException(exc_error_writing_data, SOURCE_INFO);    
}

//-----------------------------------------------------------------------------------------------------------------
std::istream& nct::geometry::operator>>(std::istream& i, geometry::AffineTransformation& tm)
{    
    tm = AffineTransformation::read(i);
    return i;
}

//-----------------------------------------------------------------------------------------------------------------
std::ostream& nct::geometry::operator<<(std::ostream& o, const geometry::AffineTransformation& tm) 
{
    o << "\n"
      << tm.m00() << " " << tm.m01() << " " << tm.m02() << "\n"
      << tm.m10() << " " << tm.m11() << " " << tm.m12() << "\n"
      << (double)(0) << " " << (double)(0) << " " << (double)(1) << std::endl;
    return o;
}
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
