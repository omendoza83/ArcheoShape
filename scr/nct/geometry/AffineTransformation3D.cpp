//=================================================================================================================
/**
 *  @file       AffineTransformation3D.cpp
 *  @brief      nct::geometry::AffineTransformation3D class implementation file.
 *  @details    This file contains the implementation of the nct::geometry::AffineTransformation3D class.
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
#include <nct/geometry/AffineTransformation3D.h>


//=================================================================================================================
//        CONSTRUCTORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D::AffineTransformation3D(
    double ma00, double ma01, double ma02, double ma03,
    double ma10, double ma11, double ma12, double ma13,
    double ma20, double ma21, double ma22, double ma23) noexcept
{
    m_[0][0] = ma00;
    m_[0][1] = ma01;
    m_[0][2] = ma02;
    m_[0][3] = ma03;

    m_[1][0] = ma10;
    m_[1][1] = ma11;
    m_[1][2] = ma12;
    m_[1][3] = ma13;

    m_[2][0] = ma20;
    m_[2][1] = ma21;
    m_[2][2]= ma22;
    m_[2][3]= ma23;
}

//=================================================================================================================
//        OPERATORS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::AffineTransformation3D::operator==(const AffineTransformation3D& right) const noexcept 
{
    return 
        (m_[0][0] == right.m_[0][0]) && (m_[0][1] == right.m_[0][1]) &&
        (m_[0][2] == right.m_[0][2]) && (m_[0][3] == right.m_[0][3]) &&
        (m_[1][0] == right.m_[1][0]) && (m_[1][1] == right.m_[1][1]) && 
        (m_[1][2] == right.m_[1][2]) && (m_[1][3] == right.m_[1][3]) &&
        (m_[2][0] == right.m_[2][0]) && (m_[2][1] == right.m_[2][1]) &&
        (m_[2][2] == right.m_[2][2]) && (m_[2][3] == right.m_[2][3]);
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::AffineTransformation3D::operator!=(const AffineTransformation3D& right) const noexcept 
{
    return !(*this == right);
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation3D::operator()(size_t i, size_t j) 
{
    if (i >= 3)
        throw IndexOutOfRangeException("i", SOURCE_INFO);

    if (j >= 4)
        throw IndexOutOfRangeException("j", SOURCE_INFO);

    return m_[i][j];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation3D::operator()(size_t i, size_t j) const 
{
    if (i >= 3)
        throw IndexOutOfRangeException("i", SOURCE_INFO);

    if (j >= 4)
        throw IndexOutOfRangeException("j", SOURCE_INFO);

    return m_[i][j];
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::operator+() const noexcept 
{
    return (*this);
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::operator+(
    const AffineTransformation3D& right) const noexcept
{
    AffineTransformation3D tt;
    for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 4; j++)
            tt.m_[i][j] = m_[i][j] + right.m_[i][j];

    return tt;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::geometry::AffineTransformation3D& nct::geometry::AffineTransformation3D::operator+=(
    const AffineTransformation3D& right) noexcept
{
    for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 4; j++)
            m_[i][j] += right.m_[i][j];
    
    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::operator-() const noexcept 
{
    AffineTransformation3D tt;
    for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 4; j++)
            tt.m_[i][j] = -m_[i][j];

    return tt;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::operator-(
    const AffineTransformation3D& right) const noexcept
{
    AffineTransformation3D tt;
    for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 4; j++)
            tt.m_[i][j] = m_[i][j] - right.m_[i][j];

    return tt;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::geometry::AffineTransformation3D& nct::geometry::AffineTransformation3D::operator-=(
    const AffineTransformation3D& right) noexcept
{
    for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 4; j++)
            m_[i][j] -= right.m_[i][j];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::operator*(
    const AffineTransformation3D& right) const noexcept
{
    AffineTransformation3D tt;
    tt.m_[0][0] = m_[0][0]*right.m_[0][0] + m_[0][1]*right.m_[1][0] + m_[0][2]*right.m_[2][0];
    tt.m_[0][1] = m_[0][0]*right.m_[0][1] + m_[0][1]*right.m_[1][1] + m_[0][2]*right.m_[2][1];
    tt.m_[0][2] = m_[0][0]*right.m_[0][2] + m_[0][1]*right.m_[1][2] + m_[0][2]*right.m_[2][2];
    tt.m_[0][3] = m_[0][0]*right.m_[0][3] + m_[0][1]*right.m_[1][3] + m_[0][2]*right.m_[2][3] + m_[0][3];

    tt.m_[1][0] = m_[1][0]*right.m_[0][0] + m_[1][1]*right.m_[1][0] + m_[1][2]*right.m_[2][0];
    tt.m_[1][1] = m_[1][0]*right.m_[0][1] + m_[1][1]*right.m_[1][1] + m_[1][2]*right.m_[2][1];
    tt.m_[1][2] = m_[1][0]*right.m_[0][2] + m_[1][1]*right.m_[1][2] + m_[1][2]*right.m_[2][2];
    tt.m_[1][3] = m_[1][0]*right.m_[0][3] + m_[1][1]*right.m_[1][3] + m_[1][2]*right.m_[2][3] + m_[1][3];

    tt.m_[2][0] = m_[2][0]*right.m_[0][0] + m_[2][1]*right.m_[1][0] + m_[2][2]*right.m_[2][0];
    tt.m_[2][1] = m_[2][0]*right.m_[0][1] + m_[2][1]*right.m_[1][1] + m_[2][2]*right.m_[2][1];
    tt.m_[2][2] = m_[2][0]*right.m_[0][2] + m_[2][1]*right.m_[1][2] + m_[2][2]*right.m_[2][2];
    tt.m_[2][3] = m_[2][0]*right.m_[0][3] + m_[2][1]*right.m_[1][3] + m_[2][2]*right.m_[2][3] + m_[2][3];

    return tt;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::geometry::AffineTransformation3D& nct::geometry::AffineTransformation3D::operator*=(
    const AffineTransformation3D& right) noexcept
{
    auto tt = (*this)*right;
    (*this) = tt;
    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::operator*(
    double right) const noexcept 
{
    AffineTransformation3D tt;
    for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 4; j++)
            tt.m_[i][j] = m_[i][j] * right;

    return tt;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::operator*(double left,
    const nct::geometry::AffineTransformation3D& right) noexcept
{
    AffineTransformation3D tt;
    for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 4; j++)
            tt(i, j) = left*right(i, j);

    return tt;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::geometry::AffineTransformation3D& nct::geometry::AffineTransformation3D::operator*=(
    double right) noexcept
{
    for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 4; j++)
            m_[i][j] *= right;

    return *this;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::operator/(
    double right) const noexcept 
{
    AffineTransformation3D tt;
    for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 4; j++)
            tt.m_[i][j] = m_[i][j] / right;

    return tt;
}

//-----------------------------------------------------------------------------------------------------------------
const nct::geometry::AffineTransformation3D& nct::geometry::AffineTransformation3D::operator/=(
    double right) noexcept 
{
    for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 4; j++)
            m_[i][j] /= right;

    return *this;
}

//=================================================================================================================
//        MEMBER FUNCTIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation3D::m00() noexcept 
{
    return m_[0][0];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation3D::m00() const noexcept 
{
    return m_[0][0];
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation3D::m01() noexcept 
{
    return m_[0][1];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation3D::m01() const noexcept 
{
    return m_[0][1];
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation3D::m02() noexcept
{
    return m_[0][2];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation3D::m02() const noexcept
{
    return m_[0][2];
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation3D::m03() noexcept
{
    return m_[0][3];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation3D::m03() const noexcept 
{
    return m_[0][3];
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation3D::m10() noexcept
{
    return m_[1][0];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation3D::m10() const noexcept
{
    return m_[1][0];
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation3D::m11() noexcept 
{
    return m_[1][1];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation3D::m11() const noexcept
{
    return m_[1][1];
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation3D::m12() noexcept 
{
    return m_[1][2];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation3D::m12() const noexcept
{
    return m_[1][2];
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation3D::m13() noexcept
{
    return m_[1][3];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation3D::m13() const noexcept 
{
    return m_[1][3];
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation3D::m20() noexcept 
{
    return m_[2][0];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation3D::m20() const noexcept
{
    return m_[2][0];
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation3D::m21() noexcept 
{
    return m_[2][1];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation3D::m21() const noexcept
{
    return m_[2][1];
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation3D::m22() noexcept
{
    return m_[2][2];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation3D::m22() const noexcept 
{
    return m_[2][2];
}

//-----------------------------------------------------------------------------------------------------------------
double& nct::geometry::AffineTransformation3D::m23() noexcept
{
    return m_[2][3];
}

//-----------------------------------------------------------------------------------------------------------------
const double& nct::geometry::AffineTransformation3D::m23() const noexcept 
{
    return m_[2][3];
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::reset() noexcept 
{
    m_[0][0] = 1;
    m_[0][1] = 0;
    m_[0][2] = 0;
    m_[0][3] = 0;

    m_[1][0] = 0;
    m_[1][1] = 1;
    m_[1][2] = 0;
    m_[1][3] = 0;

    m_[2][0] = 0;
    m_[2][1] = 0;
    m_[2][2] = 1;
    m_[2][3] = 0;
}

//-----------------------------------------------------------------------------------------------------------------
bool nct::geometry::AffineTransformation3D::isUnitary() const noexcept 
{
    if ((m_[0][0] == 1) && (m_[0][1] == 0) && (m_[0][2] == 0) && (m_[0][3] == 0) &&
        (m_[1][0] == 0) && (m_[1][1] == 1) && (m_[1][2] == 0) && (m_[1][3] == 0) &&
        (m_[2][0] == 0) && (m_[2][1] == 0) && (m_[2][2] == 1) && (m_[2][3] == 0))
        return true;

    return false;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addTransformation(const AffineTransformation3D& tm) noexcept 
{
    (*this) = tm * (*this);
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addRotation(const Vector3D<double>& w, double theta)
{
    addTransformation(rotationMatrix(w, theta));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addRotationX(double theta) noexcept
{
    addTransformation(rotationMatrixX(theta));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addRotationY(double theta) noexcept 
{
    addTransformation(rotationMatrixY(theta));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addRotationZ(double theta) noexcept
{
    addTransformation(rotationMatrixZ(theta));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addRotationXYZ(double thetaX, double thetaY, double thetaZ) noexcept 
{
    addTransformation(rotationMatrixXYZ(thetaX, thetaY, thetaZ));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addRotationXZY(double thetaX, double thetaY, double thetaZ) noexcept
{
    addTransformation(rotationMatrixXZY(thetaX, thetaY, thetaZ));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addRotationYXZ(double thetaX, double thetaY, double thetaZ) noexcept 
{
    addTransformation(rotationMatrixYXZ(thetaX, thetaY, thetaZ));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addRotationYZX(double thetaX, double thetaY, double thetaZ) noexcept 
{
    addTransformation(rotationMatrixYZX(thetaX, thetaY, thetaZ));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addRotationZXY(double thetaX, double thetaY, double thetaZ) noexcept
{
    addTransformation(rotationMatrixZXY(thetaX, thetaY, thetaZ));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addRotationZYX(double thetaX, double thetaY, double thetaZ) noexcept 
{
    addTransformation(rotationMatrixZYX(thetaX, thetaY, thetaZ));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addTranslation(double dx, double dy, double dz) noexcept
{
    m_[0][3] += dx;
    m_[1][3] += dy;
    m_[2][3] += dz;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addTranslationX(double d) noexcept 
{
    m_[0][3] += d;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addTranslationY(double d) noexcept
{
    m_[1][3] += d;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addTranslationZ(double d) noexcept 
{
    m_[2][3] += d;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addScaling(double sx, double sy, double sz) noexcept 
{
    m_[0][0] *= sx;
    m_[1][1] *= sy;
    m_[2][2] *= sz;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addScalingX(double s) noexcept
{
    m_[0][0] *= s;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addScalingY(double s) noexcept
{
    m_[1][1] *= s;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addScalingZ(double s) noexcept 
{
    m_[2][2] *= s;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addSkewXY(double alpha) noexcept 
{
    addTransformation(skewMatrixXY(alpha));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addSkewYX(double alpha) noexcept
{
    addTransformation(skewMatrixYX(alpha));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addSkewXZ(double alpha) noexcept
{
    addTransformation(skewMatrixXZ(alpha));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addSkewZX(double alpha) noexcept
{
    addTransformation(skewMatrixZX(alpha));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addSkewYZ(double alpha) noexcept
{
    addTransformation(skewMatrixYZ(alpha));
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::addSkewZY(double alpha) noexcept
{
    addTransformation(skewMatrixZY(alpha));
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::rotationMatrix(
    const Vector3D<double>& w, double theta)
{
    if (w.magnitude() == 0)
        throw ArgumentException("w", exc_bad_rotation_axis, SOURCE_INFO);

    auto ww = w;
    ww.normalize();

    double kx[3][3];
    for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 3; j++)
            kx[i][j] = 0.0;
    kx[0][1] = -ww[2];
    kx[0][2] = ww[1];

    kx[1][0] = ww[2];
    kx[1][2] = -ww[0];

    kx[2][0] = -ww[1];
    kx[2][1] = ww[0];

    double kkx[3][3];
    for (unsigned int i = 0; i < 3; i++) {
        for (unsigned int j = 0; j < 3; j++) {
            kkx[i][j] = 0.0;
            for (unsigned int k = 0; k < 3; k++)
                kkx[i][j] += kx[i][k] * kx[k][j];
        }
    }

    auto st = std::sin(theta);
    auto sc = 1. - std::cos(theta);
    double R[3][3];
    for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 3; j++)
            R[i][j] = st*kx[i][j] + sc*kkx[i][j];

    R[0][0] += 1;
    R[1][1] += 1;
    R[2][2] += 1;

    AffineTransformation3D R2;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            R2.m_[i][j] = R[i][j];
    R2.m_[0][3] = 0.0;
    R2.m_[1][3] = 0.0;

    return R2;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::rotationMatrixX(
    double theta) noexcept
{
    AffineTransformation3D r;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<4; j++)
            r.m_[i][j] = 0.0;

    double c = (std::cos(theta));
    double s = (std::sin(theta));
    r.m_[0][0] = 1;
    r.m_[1][1] = c;
    r.m_[1][2] =-s;
    r.m_[2][1] = s;
    r.m_[2][2] = c;

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::rotationMatrixY(
    double theta) noexcept
{
    AffineTransformation3D r;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<4; j++)
            r.m_[i][j] = 0.0;

    double c = (std::cos(theta));
    double s = (std::sin(theta));
    r.m_[0][0] = c;
    r.m_[0][2] = s;
    r.m_[1][1] = 1;
    r.m_[2][0] =-s;
    r.m_[2][2] = c;

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::rotationMatrixZ(
    double theta) noexcept
{
    AffineTransformation3D r;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<4; j++)
            r.m_[i][j] = 0.0;

    double c = (std::cos(theta));
    double s = (std::sin(theta));
    r.m_[0][0] = c;
    r.m_[0][1] =-s;
    r.m_[1][0] = s;
    r.m_[1][1] = c;
    r.m_[2][2] = 1;

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::rotationMatrixXYZ(
    double thetaX, double thetaY, double thetaZ) noexcept
{
    double cx = std::cos(thetaX);
    double sx = std::sin(thetaX);
    double cy = std::cos(thetaY);
    double sy = std::sin(thetaY);
    double cz = std::cos(thetaZ);
    double sz = std::sin(thetaZ);

    AffineTransformation3D r;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<4; j++)
            r.m_[i][j] = 0.0;

    r.m_[0][0] = cy*cz;
    r.m_[0][1] = -cy*sz;
    r.m_[0][2] = sy;

    r.m_[1][0] = cx*sz + sx*sy*cz;
    r.m_[1][1] = cx*cz - sx*sy*sz;
    r.m_[1][2] = -sx*cy;

    r.m_[2][0] = sx*sz - cx*sy*cz;
    r.m_[2][1] = sx*cz + cx*sy*sz;
    r.m_[2][2] = cx*cy;

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::rotationMatrixXZY(
    double thetaX, double thetaY, double thetaZ) noexcept
{
    double cx = std::cos(thetaX);
    double sx = std::sin(thetaX);
    double cy = std::cos(thetaY);
    double sy = std::sin(thetaY);
    double cz = std::cos(thetaZ);
    double sz = std::sin(thetaZ);

    AffineTransformation3D r;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<4; j++)
            r.m_[i][j] = 0.0;

    r.m_[0][0] = cy*cz;
    r.m_[0][1] = -sz;
    r.m_[0][2] = sy*cz;

    r.m_[1][0] = cx*cy*sz + sx*sy;
    r.m_[1][1] = cx*cz;
    r.m_[1][2] = cx*sy*sz - sx*cy;

    r.m_[2][0] = sx*cy*sz - cx*sy;
    r.m_[2][1] = sx*cz;
    r.m_[2][2] = sx*sy*sz + cx*cy;

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::rotationMatrixYXZ(
    double thetaX, double thetaY, double thetaZ) noexcept
{
    double cx = std::cos(thetaX);
    double sx = std::sin(thetaX);
    double cy = std::cos(thetaY);
    double sy = std::sin(thetaY);
    double cz = std::cos(thetaZ);
    double sz = std::sin(thetaZ);

    AffineTransformation3D r;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<4; j++)
            r.m_[i][j] = 0.0;

    r.m_[0][0] = cy*cz + sx*sy*sz;
    r.m_[0][1] = -cy*sz + sx*sy*cz;
    r.m_[0][2] = cx*sy;

    r.m_[1][0] = cx*sz;
    r.m_[1][1] = cx*cz;
    r.m_[1][2] = -sx;

    r.m_[2][0] = -sy*cz + sx*cy*sz;
    r.m_[2][1] = sy*sz + sx*cy*cz;
    r.m_[2][2] = cx*cy;

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::rotationMatrixYZX(
    double thetaX, double thetaY, double thetaZ) noexcept
{
    double cx = std::cos(thetaX);
    double sx = std::sin(thetaX);
    double cy = std::cos(thetaY);
    double sy = std::sin(thetaY);
    double cz = std::cos(thetaZ);
    double sz = std::sin(thetaZ);

    AffineTransformation3D r;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<4; j++)
            r.m_[i][j] = 0.0;

    r.m_[0][0] = cy*cz;
    r.m_[0][1] = -cx*cy*sz + sx*sy;
    r.m_[0][2] = sx*cy*sz + cx*sy;

    r.m_[1][0] = sz;
    r.m_[1][1] = cx*cz;
    r.m_[1][2] = -sx*cz;

    r.m_[2][0] = -sy*cz;
    r.m_[2][1] = cx*sy*sz + sx*cy;
    r.m_[2][2] = -sx*sy*sz + cx*cy;

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::rotationMatrixZXY(
    double thetaX, double thetaY, double thetaZ) noexcept
{
    double cx = std::cos(thetaX);
    double sx = std::sin(thetaX);
    double cy = std::cos(thetaY);
    double sy = std::sin(thetaY);
    double cz = std::cos(thetaZ);
    double sz = std::sin(thetaZ);

    AffineTransformation3D r;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<4; j++)
            r.m_[i][j] = 0.0;

    r.m_[0][0] = cy*cz - sx*sy*sz;
    r.m_[0][1] = -cx*sz;
    r.m_[0][2] = sy*cz + sx*cy*sz;

    r.m_[1][0] = cy*sz + sx*sy*cz;
    r.m_[1][1] = cx*cz;
    r.m_[1][2] = sy*sz - sx*cy*cz;

    r.m_[2][0] = -cx*sy;
    r.m_[2][1] = sx;
    r.m_[2][2] = cx*cy;

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::rotationMatrixZYX(
    double thetaX, double thetaY, double thetaZ) noexcept
{
    double cx = std::cos(thetaX);
    double sx = std::sin(thetaX);
    double cy = std::cos(thetaY);
    double sy = std::sin(thetaY);
    double cz = std::cos(thetaZ);
    double sz = std::sin(thetaZ);

    AffineTransformation3D r;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<4; j++)
            r.m_[i][j] = 0.0;

    r.m_[0][0] = cy*cz;
    r.m_[0][1] = sx*sy*cz - cx*sz;
    r.m_[0][2] = cx*sy*cz + sx*sz;

    r.m_[1][0] = cy*sz;
    r.m_[1][1] = sx*sy*sz + cx*cz;
    r.m_[1][2] = cx*sy*sz - sx*cz;

    r.m_[2][0] = -sy;
    r.m_[2][1] = sx*cy;
    r.m_[2][2] = cx*cy;

    return r;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::translationMatrix(
    double dx, double dy, double dz) noexcept
{
    AffineTransformation3D tm;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<4; j++)
            tm.m_[i][j] = 0.0;
    
    tm.m_[0][0] = 1;
    tm.m_[0][3] = dx;
    tm.m_[1][1] = 1;
    tm.m_[1][3] = dy;
    tm.m_[2][2] = 1;
    tm.m_[2][3] = dz;
    return tm;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::scalingMatrix(
    double sx, double sy, double sz) noexcept
{
    AffineTransformation3D tm;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<4; j++)
            tm.m_[i][j] = 0.0;
    
    tm.m_[0][0] = sx;
    tm.m_[1][1] = sy;
    tm.m_[2][2] = sz;
    return tm;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::skewMatrixXY(
    double alpha) noexcept
{
    AffineTransformation3D tm;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<4; j++)
            tm.m_[i][j] = 0.0;

    tm.m_[0][0] = 1;
    tm.m_[1][1] = 1;
    tm.m_[2][2] = 1;
    tm.m_[0][1] = std::tan(alpha);
    return tm;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::skewMatrixYX(
    double alpha) noexcept
{
    AffineTransformation3D tm;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<4; j++)
            tm.m_[i][j] = 0.0;

    tm.m_[0][0] = 1;
    tm.m_[1][1] = 1;
    tm.m_[2][2] = 1;
    tm.m_[1][0] = std::tan(alpha);
    return tm;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::skewMatrixXZ(
    double alpha) noexcept
{
    AffineTransformation3D tm;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<4; j++)
            tm.m_[i][j] = 0.0;

    tm.m_[0][0] = 1;
    tm.m_[1][1] = 1;
    tm.m_[2][2] = 1;
    tm.m_[0][2] = std::tan(alpha);
    return tm;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::skewMatrixZX(
    double alpha) noexcept
{
    AffineTransformation3D tm;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<4; j++)
            tm.m_[i][j] = 0.0;

    tm.m_[0][0] = 1;
    tm.m_[1][1] = 1;
    tm.m_[2][2] = 1;
    tm.m_[2][0] = std::tan(alpha);
    return tm;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::skewMatrixYZ(
    double alpha) noexcept
{
    AffineTransformation3D tm;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<4; j++)
            tm.m_[i][j] = 0.0;

    tm.m_[0][0] = 1;
    tm.m_[1][1] = 1;
    tm.m_[2][2] = 1;
    tm.m_[1][2] = std::tan(alpha);
    return tm;
}

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::skewMatrixZY(
    double alpha) noexcept
{
    AffineTransformation3D tm;
    for (int i = 0; i<3; i++)
        for (int j = 0; j<4; j++)
            tm.m_[i][j] = 0.0;

    tm.m_[0][0] = 1;
    tm.m_[1][1] = 1;
    tm.m_[2][2] = 1;
    tm.m_[2][1] = std::tan(alpha);
    return tm;
}

//=================================================================================================================
//        I/O OPERATIONS
//=================================================================================================================

//-----------------------------------------------------------------------------------------------------------------
nct::geometry::AffineTransformation3D nct::geometry::AffineTransformation3D::read(std::istream& i)
{
    AffineTransformation3D tm;

    // Check for errors.
    if (i.fail())
        throw IOException(exc_bad_input_stream, SOURCE_INFO);

    i.read(reinterpret_cast<char*> (tm.m_), sizeof(double) * 12);
    if (i.fail())
        throw IOException(exc_error_reading_data, SOURCE_INFO);

    return tm;
}

//-----------------------------------------------------------------------------------------------------------------
void nct::geometry::AffineTransformation3D::write(std::ostream& o) const
{
    // Check for errors.
    if (o.fail())
        throw IOException(exc_bad_output_stream, SOURCE_INFO);
    
    // Write data.
    o.write(reinterpret_cast<const char*>(m_), sizeof(double)*12);    
    if (o.fail())
        throw IOException(exc_error_writing_data, SOURCE_INFO);    
}

//-----------------------------------------------------------------------------------------------------------------
std::istream& nct::geometry::operator>>(std::istream& i, geometry::AffineTransformation3D& tm) 
{    
    tm = AffineTransformation3D::read(i);
    return i;
}

//-----------------------------------------------------------------------------------------------------------------
std::ostream& nct::geometry::operator<<(std::ostream& o, const geometry::AffineTransformation3D& tm)
{
    o << "\n"
      << tm.m00() << " " << tm.m01() << " " << tm.m02() << " " << tm.m03() << "\n"
      << tm.m10() << " " << tm.m11() << " " << tm.m12() << " " << tm.m13() << "\n"
      << tm.m20() << " " << tm.m21() << " " << tm.m22() << " " << tm.m23() << "\n"
      << (double)(0) << " "<< (double)(0)<< " " << (double)(0)<< " " << (double)(1) << std::endl;
    return o;
}
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
