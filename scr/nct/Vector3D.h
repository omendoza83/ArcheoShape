//=================================================================================================================
/**
 *  @file       Vector3D.h
 *  @brief      nct::Vector3D class template.
 *  @details    Declaration of the nct::Vector3D class template.
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

#ifndef NCT_VECTOR3D_H_INCLUDE
#define NCT_VECTOR3D_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>

#include <iostream>

//=================================================================================================================
namespace nct {

////////// Type definitions //////////

template<nct::Numeric T>
class Vector3D;

using Point3D = Vector3D<double>;   /**< 3-Dimensional point. */

using Point3DF = Vector3D<float>;   /**< 3-Dimensional point in single precision. */

////////// Classes ////////// 

/**
 *  @brief      Class template for 3-dimensional vectors.
 *  @details    This class is used to manipulate 3-dimensional vectors.
 *  @note       It is possible to disable index checking in the [] operator by defining
 *              NCT_VECTOR_3D_DISABLE_INDEX_CHECKING.
 *  @tparam     T  The data type of the vector elements.
 */
template<nct::Numeric T>
class Vector3D final {

public:

    ////////// Type definitions //////////

    /** Base data type. */
    using value_type = T;

    /** Pointer. */
    using pointer = T*;

    /** Const pointer. */
    using const_pointer = const T*;

    /** Reference. */
    using reference = T&;

    /** const Reference. */
    using const_reference = const T&;

    /** Size type. */
    using size_type = size_t;

    /** Base numeric data type. */
    using numeric_type = T;

    ////////// Constructors //////////
    
    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes a null vector.
     */
    constexpr Vector3D() noexcept = default;
    
    /**
     *  @brief      Initialize vector.
     *  @details    This constructor initializes a vector with the specified components.
     *  @param[in]  v1  The first component of the new vector.
     *  @param[in]  v2  The second component of the new vector.
     *  @param[in]  v3  The third component of the new vector.
     */
    constexpr Vector3D(const_reference v1, const_reference v2, const_reference v3) noexcept;

    ////////// Operators //////////        

    /**
     *  @brief      Equality operator.
     *  @details    Two vectors are equal if both have the same components.
     *  @param[in]  other  Vector on the right side of the operation.
     *  @returns    True if both vectors are equal.
     */
    constexpr bool operator==(const Vector3D<T>& right) const noexcept;

    /**
     *  @brief      Inequality operator.
     *  @details    Two vectors are not equal if one of their components differs.
     *  @param[in]  right  Vector on the right side of the operation.
     *  @returns    True if both vectors are not equal.
     */
    constexpr bool operator!=(const Vector3D<T>& right) const noexcept;

    /**
     *  @brief      Vector subscript.
     *  @details    This operator returns a reference to the selected component.
     *  @param[in]  i  Index of the component to be returned.
     *  @returns    A reference to the selected component.
     */
    reference operator[](size_type i);

    /**
     *  @brief      Vector subscript.
     *  @details    This operator returns a reference to the selected component.
     *  @param[in]  i  Index of the component to be returned.
     *  @returns    A reference to the selected component.
     */
    constexpr const_reference operator[](size_type i) const;

    /**
     *  @brief      Unary plus.
     *  @details    This operator multiplies by one the vector.
     *  @returns    The result of the operation.
     */
    constexpr Vector3D<T> operator+() const noexcept;

    /**
     *  @brief      Sum.
     *  @details    Addition of two vectors.
     *  @param[in]  right  Vector on the right side of the operation.
     *  @returns    The result of the operation.
     */
    constexpr Vector3D<T> operator+(const Vector3D<T>& right) const noexcept;

    /**
     *  @brief      Sum.
     *  @details    Addition of two vectors. The result is stored in the current instance.
     *  @param[in]  right  Vector on the right side of the operation.
     *  @returns    A reference to the object.
     */
    const Vector3D<T>& operator+=(const Vector3D<T>& right) noexcept;

    /**
     *  @brief      Unary minus.
     *  @details    This operator multiplies by minus one the vector.
     *  @returns    The result of the operation.
     */
    template<typename = void> requires nct::SignedNumeric<T>
    constexpr Vector3D<T> operator-() const;

    /**
     *  @brief      Substraction.
     *  @details    Substraction of two vectors.
     *  @param[in]  right  Vector on the right side of the operation.
     *  @returns    The result of the operation.
     */
    constexpr Vector3D<T> operator-(const Vector3D<T>& right) const noexcept;

    /**
     *  @brief      Substraction.
     *  @details    Substraction of two vectors. The result is stored in the current instance.
     *  @param[in]  right  Vector on the right side of the operation.
     *  @returns    A reference to the object.
     */
    const Vector3D<T>& operator-=(const Vector3D<T>& right) noexcept;

    /**
     *  @brief      Scalar product.
     *  @details    Multiplication of a vector by a scalar value.
     *  @param[in]  right  Value on the right side of the operation.
     *  @returns    The result of the operation.
     */
    constexpr Vector3D<T> operator*(const_reference right) const noexcept;

    /**
     *  @brief      Scalar product.
     *  @details    Multiplication of a vector by a scalar value. The result is stored in the current instance.
     *  @param[in]  right  Value on the right side of the operation.
     *  @returns    A reference to the object.
     */
    const Vector3D<T>& operator*=(const_reference right) noexcept;

    /**
     *  @brief      Scalar division.
     *  @details    Division of a vector by a scalar value.
     *  @param[in]  right  Value on the right side of the operation.
     *  @returns    The result of the operation.
     */
    constexpr Vector3D<T> operator/(const_reference right) const;

    /**
     *  @brief      Scalar division.
     *  @details    Division of a vector by a scalar value. The result is stored in the current instance.
     *  @param[in]  right  Value on the right side of the operation.
     *  @returns    A reference to the object.
     */
    const Vector3D<T>& operator/=(const_reference right);

    ////////// Member functions //////////        
    
    /**
     *  @brief      Set the vector coefficients.
     *  @details    This function sets the coefficients of the vector.
     *  @param[in]  v1  The first component of the vector.
     *  @param[in]  v2  The second component of the vector.
     *  @param[in]  v3  The third component of the vector.
     */
    void setCoefficients(const_reference v1, const_reference v2, const_reference v3) noexcept;
    
    /**
     *  @brief      Normalize vector.
     *  @details    This function normalizes the vector so that its magnitude is 1.
     */
    void normalize() noexcept;
    
    /**
     *  @brief      First component.
     *  @details    This function returns a reference to the first component of the vector.
     *  @returns    A reference to the vector component.
     */
    reference v1() noexcept;
    
    /**
     *  @brief      First component.
     *  @details    This function returns a reference to the first component of the vector.
     *  @returns    A reference to the vector component.
     */
    constexpr const_reference v1() const noexcept;
            
    /**
     *  @brief      Second component.
     *  @details    This function returns a reference to the second component of the vector.
     *  @returns    A reference to the vector component.
     */
    reference v2() noexcept;
    
    /**
     *  @brief      Second component.
     *  @details    This function returns a reference to the second component of the vector.
     *  @returns    A reference to the vector component.
     */
    constexpr const_reference v2() const noexcept;
    
    /**
     *  @brief      Third component.
     *  @details    This function returns a reference to the third component of the vector.
     *  @returns    A reference to the third component.
     */
    reference v3() noexcept;
    
    /**
     *  @brief      Third component.
     *  @details    This function returns a reference to the third component of the vector.
     *  @returns    A reference to the vector component.
     */
    constexpr const_reference v3() const noexcept;
    
    /**
     *  @brief      Magnitude.
     *  @details    This function returns the magnitude of the vector.
     *  @returns    The magnitude.
     */
    double magnitude() const noexcept;
    
    /**
     *  @brief      Squared magnitude.
     *  @details    This function returns the square of the vector magnitude.
     *  @returns    The squared magnitude.
     */
    constexpr double sqrMagnitude() const noexcept;
    
    /**
     *  @brief      Unitary vector.
     *  @details    This function returns the unitary vector in the direction of the vector.
     *  @returns    The unitary vector.
     */
    Vector3D<double> unitaryVector() const noexcept;
    
    /**
     *  @brief      Directional cosines.
     *  @details    This function returns a vector with the directional cosines of the vector.
     *  @returns    A vector with the directional cosines.
     */
    Vector3D<double> directionalCosines() const noexcept;
    
    /**
     *  @brief      Directional angles.
     *  @details    This function returns a vector with the directional angles of the vector.
     *  @returns    A vector with the directional angles.
     */
    Vector3D<double> directionalAngles() const noexcept;
    
    /**
     *  @brief      Cartesian coordinates (x, y, z) to cylindrical coordinates (r, theta, z).
     *  @details    This function returns a vector with the cylindrical coordinates that correspond to the vector. The
     *              relationship between coordinate systems is: 
     *              std::tan(theta) = x/y, r^2 = x^2 + y^2, z = z.
     *  @returns    A vector with the cylindrical coordinates.
     */
    Vector3D<double> cartesianToCylindrical() const noexcept;
    
    /**
     *  @brief      Cylindrical coordinates (r, theta, z) to cartesian coordinates (x, y, z).
     *  @details    This function returns a vector with the cylindrical coordinates that correspond to the vector. The 
     *              relationship between coordinate systems is: 
     *              x = r*std::cos(theta), y=r*std::sin(theta), z = z.
     *  @returns    A vector with the cartesian coordinates.
     */
    Vector3D<double> cylindricalToCartesian() const noexcept;
    
    /**
     *  @brief      Cartesian coordinates (x, y, z) to spherical coordinates (rho, theta, phi).
     *  @details    This function returns a vector with the spherical coordinates that correspond to the vector. The 
     *              relationship between coordinate systems is: 
     *              std::tan(theta) = y/x, rho^2 = x^2 + y^2 + z^2, 
     *              std::cos(phi) = z/rho.
     *  @returns    A vector with the spherical coordinates.
     */
    Vector3D<double> cartesianToSpherical() const noexcept;
    
    /**
     *  @brief      Spherical coordinates (rho, theta, phi) to cartesian coordinates (x, y, z).
     *  @details    This function returns a vector with the spherical coordinates that correspond to the vector. The 
     *              relationship between coordinate systems is: x=rho*std::cos(theta)*std::sin(phi),
     *              y=rho*std::sin(theta)*std::sin(phi), z=rho*std::cos(phi).
     *  @returns    A vector with the cartesian coordinates.
     */
    Vector3D<double> sphericalToCartesian() const noexcept;
    
    /**
     *  @brief      Cylindrical coordinates (r, theta, z) to spherical coordinates (rho, theta, phi).
     *  @details    This function returns a vector with the spherical coordinates that correspond to the vector. The 
     *              relationship between coordinate systems is: r = rho*std::sin(theta), theta = theta,
     *              z=rho*std::cos(phi).
     *  @returns    A vector with the spherical coordinates.
     */
    Vector3D<double> cylindricalToSpherical() const noexcept;
    
    /**
     *  @brief      Spherical coordinates (rho, theta, phi) to cylindrical coordinates (r, theta, z).
     *  @details    This function returns a vector with the spherical coordinates that correspond to the vector. The 
     *              relationship between coordinate systems is: 
     *              std::tan(theta) = x/y, rho^2 = x^2 + y^2 + z^2, 
     *              std::cos(phi) = z/rho.
     *  @returns    A vector with the cylindrical coordinates.
     */
    Vector3D<double> sphericalToCylindrical() const noexcept;
    
    /**
     *  @brief      Rotate vector
     *  @details    This function rotates vector given a rotation axis and an angle of rotation.
     *  @param[in]  w  Rotation axis.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    The new rotated vector.
     */
    Vector3D<T> rotate(const Vector3D<T>& w, double theta) const;
    
    /**
     *  @brief      Translate vector
     *  @details    This function translates vector by the specified offset.
     *  @param[in]  s1  Offset of coordinate 1.
     *  @param[in]  s2  Offset of coordinate 2.
     *  @param[in]  s3  Offset of coordinate 3.
     *  @returns    The new translated vector.
     */
    constexpr Vector3D<T> translate(const_reference s1, const_reference s2, const_reference s3) const noexcept;

    ////////// I/O operations //////////
    
    /**
     *  @brief      Write vector to an output stream.
     *  @details    This function writes a vector to an output stream in binary format.
     *  @param[in, out] o  The output stream where the data will be written.
     */
    void write(std::ostream& o) const;
    
    /**
     *  @brief      Read vector from an input stream.
     *  @details    This function reads a vector from an input stream in binary format.
     *  @param[in, out] i  The input stream from where the data will be read.
     *  @returns    The object that was read from the input stream.
     */
    static Vector3D<T> read(std::istream& i);

private:

    ////////// Data members //////////        

    value_type vc[3] { value_type (0), value_type(0), value_type(0) };  /**< Vector components. */

};

////////// Friend methods and global operators //////////    

/**
 *  @brief      Dot product.
 *  @details    This function calculates the dot product of two vectors.
 *  @tparam     T  The data type of the vector elements.
 *  @param[in]  u  Vector u.
 *  @param[in]  v  Vector v.
 *  @returns    The dot product of vectors u and v (u*v).
 */
template<nct::Numeric T>
constexpr T dotProduct(const Vector3D<T>& u, const Vector3D<T>& v) noexcept;

/**
 *  @brief      Cross product.
 *  @details    This function calculates the cross product of two vectors. The result is reported as scalar, but it
 *              represents the third component of the 3-dimensional vector of the result.
 *  @tparam     T  The data type of the vector elements.
 *  @param[in]  u  Vector u.
 *  @param[in]  v  Vector v.
 *  @returns    The cross product of vectors u and v (u x v).
 */
template<nct::Numeric T>
constexpr Vector3D<T> crossProduct(const Vector3D<T>& u, const Vector3D<T>& v) noexcept;

/**
 *  @brief      Triple product.
 *  @details    This function calculates the triple product of three vectors.
 *  @tparam     T  The data type of the vector elements.
 *  @param[in]  u  Vector u.
 *  @param[in]  v  Vector v.
 *  @param[in]  w  Vector w.
 *  @returns    The triple product of vectors u, v and w   u*(v x w).
 */
template<nct::Numeric T>
constexpr T tripleProduct(const Vector3D<T>& u, const Vector3D<T>& v, const Vector3D<T>& w) noexcept;

/**
 *  @brief      Angle between vectors.
 *  @details    This function calculates the angle between two vectors.
 *  @tparam     T  The data type of the vector elements.
 *  @param[in]  u  Vector u.
 *  @param[in]  v  Vector v.
 *  @returns    The angle between u and v.
 */
template<nct::Numeric T>
double angleBetweenVectors(const Vector3D<T>& u, const Vector3D<T>& v) noexcept;

/**
 *  @brief      Projection of vector u in the direction of vector v.
 *  @details    This function calculates the projection of vector u in the direction of vector v.
 *  @tparam     T  The data type of the vector elements.
 *  @param[in]  u  Vector u.
 *  @param[in]  v  Vector v.
 *  @returns    The projection.
 */
template<nct::Numeric T>
Vector3D<double> projection(const Vector3D<T>& u, const Vector3D<T>& v) noexcept;

/**
 *  @brief      Area of a triangle.
 *  @details    This function calculates the area of the triangle of vertices v1, v2, v3.
 *  @tparam     T  The data type of the vector elements.
 *  @param[in]  v1  One vertex of the triangle.
 *  @param[in]  v2  One vertex of the triangle.
 *  @param[in]  v3  One vertex of the triangle.
 *  @returns    The are of the specified triangle.
 */
template<nct::Numeric T>
double triangleArea(const Vector3D<T>& v1, const Vector3D<T>& v2, const Vector3D<T>& v3) noexcept;

/**
 *  @brief      Area of a parallelogram.
 *  @details    This function calculates the area of the parallelogram defined by the vertices v1, v2, v3. The fourth
 *              vertex is calculated by: v4 = (v3 + (v2-v1)).
 *  @tparam     T  The data type of the vector elements.
 *  @param[in]  v1  One vertex of the parallelogram.
 *  @param[in]  v2  One vertex of the parallelogram.
 *  @param[in]  v3  One vertex of the parallelogram.
 *  @returns    The are of the specified parallelogram.
 */
template<nct::Numeric T>
double parallelogramArea(const Vector3D<T>& v1, const Vector3D<T>& v2, const Vector3D<T>& v3) noexcept;

/**
 *  @brief      Volume of a tetrahedron.
 *  @details    This function calculates the volumen of the parallelepiped of vertices v1, v2, v3 and v4.
 *  @tparam     T  The data type of the vector elements.
 *  @param[in]  v1  One vertex of the tetrahedron.
 *  @param[in]  v2  One vertex of the tetrahedron.
 *  @param[in]  v3  One vertex of the tetrahedron.
 *  @param[in]  v4  One vertex of the tetrahedron.
 *  @returns    The volumen of the specified tetrahedron.
 */
template<nct::Numeric T>
double tetrahedronVolume(const Vector3D<T>& v1, const Vector3D<T>& v2, const Vector3D<T>& v3,
    const Vector3D<T>& v4) noexcept;

/**
 *  @brief      Volume of a parallelepiped.
 *  @details    This function calculates the volumen of the parallelepiped of vertices v1, v2, v3 and v4. The
 *              vertices define the adjacent edges of the solid.
 *  @tparam     T  The data type of the vector elements.
 *  @param[in]  v1  One vertex of the parallelepiped.
 *  @param[in]  v2  One vertex of the parallelepiped.
 *  @param[in]  v3  One vertex of the parallelepiped.
 *  @param[in]  v4  One vertex of the parallelepiped.
 *  @returns    The volumen of the specified parallelepiped.
 */
template<nct::Numeric T>
double parallelepipedVolume(const Vector3D<T>& v1, const Vector3D<T>& v2, const Vector3D<T>& v3,
    const Vector3D<T>& v4) noexcept;

/**
 *  @brief      Scalar product.
 *  @details    Multiplication of a vector by a scalar value.
 *  @tparam     T  The data type of the vector elements.
 *  @param[in]  left  Value on the left side of the operation.
 *  @param[in]  right  Vector on the right side of the operation.
 *  @returns    The result of the operation.
 */
template<nct::Numeric T>
constexpr Vector3D<T> operator*(const T& scalar, const Vector3D<T>& v) noexcept;

/**
 *  @brief      Vector to output stream.
 *  @details    This operators writes a vector to an output stream.
 *  @tparam     T  The data type of the vector elements.
 *  @param[in, out] o  Output stream.
 *  @param[in]  v  The object to be written.
 *  @returns    A reference to the stream.
 */
template<nct::Numeric T>
std::ostream& operator<<(std::ostream& o, const Vector3D<T>& v);

/**
 *  @brief      Input stream to vector.
 *  @details    This operators reads a vector from an input stream.
 *  @tparam     T  The data type of the vector elements.
 *  @param[in, out] i  Input stream.
 *  @param[out] v  Object where the data are stored.
 *  @returns    A reference to the stream.
 */
template<nct::Numeric T>
std::istream& operator>>(std::istream& i, Vector3D<T>& v);

}

////////// Implementation of class template //////////
#include <nct/Vector3D_template.h>

#endif

//=================================================================================================================
//        END OF FILE
//=================================================================================================================
