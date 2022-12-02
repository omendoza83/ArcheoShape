//=================================================================================================================
/**
 *  @file       AffineTransformation.h
 *  @brief      nct::geometry::AffineTransformation class.
 *  @details    Declaration of the nct::geometry::AffineTransformation class.
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

#ifndef NCT_AFFINE_TRANSFORMATION_H_INCLUDE
#define NCT_AFFINE_TRANSFORMATION_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/Array.h>
#include <nct/Vector2D.h>
#include <nct/math/math.h>

#include <iostream>

//=================================================================================================================
namespace nct {
/**
 *  @brief      Geometry namespace.
 *  @details    This namespace contains functions and classes to manipulate geometrical objects.
 *              The namespace includes affine transformations, rasterization functions, basic and
 *              parametric shapes, etc.
 */
namespace geometry {

/**
 *  @brief      2D affine transformaiton class.
 *  @details    The AffineTransform class represents a 2D affine transform that performs a linear
 *              mapping from 2D coordinates to other 2D coordinates that preserves the "straightness"
 *              and "parallelness" of lines. Affine transformations can be constructed using
 *              sequences of translations, scales, flips, rotations, and shears.
 *              Such transformations can be represented using a matrix-vector product of a
 *              transformation array M(m00, m01, m02; m10, m11, m12, 0, 0, 1) and a
 *              point P(x, y).
 *              This class also includes direct methods to transform points.
 */
class NCT_EXPIMP AffineTransformation final {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the default configuration. 
     *              The affine transformation is initialized as an identity matrix.
     */
    AffineTransformation() noexcept = default;

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes the affine transformation using the specified components.
     *  @param[in]  ma00  Value of the coefficient M(0,0).
     *  @param[in]  ma01  Value of the coefficient M(0,1).
     *  @param[in]  ma02  Value of the coefficient M(0,2).
     *  @param[in]  ma10  Value of the coefficient M(1,0).
     *  @param[in]  ma11  Value of the coefficient M(1,1).
     *  @param[in]  ma12  Value of the coefficient M(1,2).
     */
    AffineTransformation(double ma00, double ma01, double ma02,
        double ma10, double ma11, double ma12) noexcept;
    
    ////////// Operators ////////// 
    
    /**
     *  @brief      Equality operator.
     *  @details    Two matrices are equal if each element 
     *              of one array is equal to the element with the same index in the other array.
     *  @param[in]  right  Array to compare.
     *  @returns    True if both arrays are equal.
     */
    bool operator==(const AffineTransformation& right) const noexcept;
    
    /**
     *  @brief      Inequality operator.
     *  @details    Two arrays are not equal if have different same size or element 
     *              of one array is not equal to the element with the same index in the other array.
     *  @param[in]  right  Array to compare.
     *  @returns    True if both arrays are not equal.
     */
    bool operator!=(const AffineTransformation& right) const noexcept;

    /**
     *  @brief      Array subscript.
     *  @details    This function returns the specified element of the transformation matrix.
     *  @param[in]  i  Row index of the selected element.
     *  @param[in]  j  Column index of the selected element.
     *  @returns    The selected element.
     */
    double& operator()(size_t i, size_t j);

    /**
     *  @brief      Array subscript.
     *  @details    This function returns the specified element of the transformation matrix.
     *  @param[in]  i  Row index of the selected element.
     *  @param[in]  j  Column index of the selected element.
     *  @returns    The selected element.
     */
    const double& operator()(size_t i, size_t j) const;

    /**
     *  @brief      Unary plus.
     *  @details    This operator multiplies by one each element inside the transformation matrix.
     *  @returns    The result of the operation.
     */
    AffineTransformation operator+() const noexcept;

    /**
     *  @brief      Matrix addition.
     *  @details    This operator calculates the sum of two transformation matrices.
     *  @param[in]  right  Matrix on the right side of the operation.
     *  @returns    The result of the operation.
     */
    AffineTransformation operator+(const AffineTransformation& right) const noexcept;

    /**
     *  @brief      Matrix addition.
     *  @details    This operator calculates the sum of two transformation matrices.
     *  @param[in]  right  Matrix on the right side of the operation.
     *  @returns    A reference to the object.
     */
    const AffineTransformation& operator+=(const AffineTransformation& right) noexcept;

    /**
     *  @brief      Unary minus.
     *  @details    This operator multiplies by minus one each element inside the transformation matrix.
     *  @returns    The result of the operation.
     */
    AffineTransformation operator-() const noexcept;

    /**
     *  @brief      Matrix substraction.
     *  @details    This operator calculates the substraction of two transformation matrices.
     *  @param[in]  right  Matrix on the right side of the operation.
     *  @returns    The result of the operation.
     */
    AffineTransformation operator-(const AffineTransformation& right) const noexcept;

    /**
     *  @brief      Matrix substraction.
     *  @details    This operator calculates the substraction of two transformation matrices.
     *  @param[in]  right  Matrix on the right side of the operation.
     *  @returns    A reference to the object.
     */
    const AffineTransformation& operator-=(const AffineTransformation& right) noexcept;

    /**
     *  @brief      Matrix multiplication.
     *  @details    This operator calculates the product of two transformation matrices.
     *  @param[in]  right  Matrix on the right side of the operation.
     *  @returns    The result of the operation.
     */
    AffineTransformation operator*(const AffineTransformation& right) const noexcept;

    /**
     *  @brief      Matrix multiplication.
     *  @details    This operator calculates the product of two transformation matrices.
     *  @param[in]  right  Matrix on the right side of the operation.
     *  @returns    A reference to the object.
     */
    const AffineTransformation& operator*=(const AffineTransformation& right) noexcept;

    /**
     *  @brief      Scalar product.
     *  @details    This operator calculates the product of the transformation matrix with a scalar.
     *  @param[in]  right  Scalar value.
     *  @returns    The result of the operation.
     */
    AffineTransformation operator*(double right) const noexcept;
    
    /**
     *  @brief      Scalar product.
     *  @details    This operator calculates the product of the transformation matrix with a scalar.
     *  @param[in]  right  Scalar value.
     *  @returns    A reference to the object.
     */
    const AffineTransformation& operator*=(double right) noexcept;

    /**
     *  @brief      Scalar division.
     *  @details    This operator calculates the division of the matrix with a scalar.
     *  @param[in]  right  Scalar value.
     *  @returns    The result of the operation.
     */
    AffineTransformation operator/(double right) const noexcept;
    
    /**
     *  @brief      Scalar division.
     *  @details    This operator calculates the division of the matrix with a scalar and stores the 
     *              result in the same instance.
     *  @param[in]  right  Scalar value.
     *  @returns    A reference to the object.
     */    
    const AffineTransformation& operator/=(double right) noexcept;

    ////////// Member functions //////////     

    /**
     *  @brief      Coefficient M(0, 0).
     *  @details    This function returns the coefficient M(0, 0) of the affine transformation.
     *  @returns    The transformaiton coefficient M(0, 0).
     */
    double& m00() noexcept;

    /**
     *  @brief      Coefficient M(0, 0).
     *  @details    This function returns the coefficient M(0, 0) of the affine transformation.
     *  @returns    The transformaiton coefficient M(0,0).
     */
    const double& m00() const noexcept;

    /**
     *  @brief      Coefficient M(0, 1).
     *  @details    This function returns the coefficient M(0, 1) of the affine transformation.
     *  @returns    The transformaiton coefficient M(0, 1).
     */
    double& m01() noexcept;

    /**
     *  @brief      Coefficient M(0, 1).
     *  @details    This function returns the coefficient M(0, 1) of the affine transformation.
     *  @returns    The transformaiton coefficient M(0, 1).
     */
    const double& m01() const noexcept;

    /**
     *  @brief      Coefficient M(0, 2).
     *  @details    This function returns the coefficient M(0, 2) of the affine transformation.
     *  @returns    The transformaiton coefficient M(0, 2).
     */
    double& m02() noexcept;

    /**
     *  @brief      Coefficient M(0, 2).
     *  @details    This function returns the coefficient M(0, 2) of the affine transformation.
     *  @returns    The transformaiton coefficient M(0, 2).
     */
    const double& m02() const noexcept;

    /**
     *  @brief      Coefficient M(1, 0).
     *  @details    This function returns the coefficient M(1, 0) of the affine transformation.
     *  @returns    The transformaiton coefficient M(1, 0).
     */
    double& m10() noexcept;

    /**
     *  @brief      Coefficient M(1, 0).
     *  @details    This function returns the coefficient M(1, 0) of the affine transformation.
     *  @returns    The transformaiton coefficient M(1, 0).
     */
    const double& m10() const noexcept;

    /**
     *  @brief      Coefficient M(1, 1).
     *  @details    This function returns the coefficient M(1, 1) of the affine transformation.
     *  @returns    The transformaiton coefficient M(1, 1).
     */
    double& m11() noexcept;

    /**
     *  @brief      Coefficient M(1, 1).
     *  @details    This function returns the coefficient M(1, 1) of the affine transformation.
     *  @returns    The transformaiton coefficient M(1, 1).
     */
    const double& m11() const noexcept;

    /**
     *  @brief      Coefficient M(1, 2).
     *  @details    This function returns the coefficient M(1, 2) of the affine transformation.
     *  @returns    The transformaiton coefficient M(1, 2).
     */
    double& m12() noexcept;

    /**
     *  @brief      Coefficient M(1, 2).
     *  @details    This function returns the coefficient M(1, 2) of the affine transformation.
     *  @returns    The transformaiton coefficient M(1, 2).
     */
    const double& m12() const noexcept;

    /**
     *  @brief      Reset transformation.
     *  @details    This function resets the matrix transformation.
     */
    void reset() noexcept;

    /**
     *  @brief      Is unitary?
     *  @details    This function returns whether the transformation is unitary.
     *  @returns    True, if the transformation is unitary, otherwise, false.
     */
    bool isUnitary() const noexcept;

    /**
     *  @brief      Add transformation.
     *  @details    This function adds a transformation to the current matrix.
     *  @param[in]  tm  Transformation to be added.
     */
    void addTransformation(const AffineTransformation& tm) noexcept;

    /**
     *  @brief      Add rotation.
     *  @details    This function adds a rotation to the transformation matrix.
     *  @param[in]  theta  Rotation angle in radians.
     */
    void addRotation(double theta) noexcept;

    /**
     *  @brief      Add rotation around one point.
     *  @details    This function adds a rotation around one point to the transformation matrix.
     *  @param[in]  p  Pivot point.
     *  @param[in]  theta  Rotation angle in radians.
     */
    void addRotationAround(const Point2D& p, double theta) noexcept;

    /**
     *  @brief      Add translation.
     *  @details    This function adds a translation to the transformation matrix.
     *  @param[in]  dx  Horizontal translation.
     *  @param[in]  dy  Vertical translation.
     */
    void addTranslation(double dx, double dy) noexcept;

    /**
     *  @brief      Add horizontal translation.
     *  @details    This function adds a horizontal translation to the transformation matrix.
     *  @param[in]  d  Translation.
     */
    void addTranslationX(double d) noexcept;

    /**
     *  @brief      Add vertical translation.
     *  @details    This function adds a vertical translation to the transformation matrix.
     *  @param[in]  d  Translation.
     */
    void addTranslationY(double d) noexcept;

    /**
     *  @brief      Add scaling.
     *  @details    This function adds a scaling to the transformation matrix.
     *  @param[in]  sx  Horizontal scaling.
     *  @param[in]  sy  Vertical scaling.
     */
    void addScaling(double sx, double sy) noexcept;

    /**
     *  @brief      Add horizontal scaling.
     *  @details    This function adds an horizontal scaling to the transformation matrix.
     *  @param[in]  s  Scaling.
     */
    void addScalingX(double s) noexcept;

    /**
     *  @brief      Add vertical scaling.
     *  @details    This function adds a vertical scaling to the transformation matrix.
     *  @param[in]  s  Scaling.
     */
    void addScalingY(double s) noexcept;

    /**
     *  @brief      Add skew.
     *  @details    This function adds a skew to the transformation matrix.
     *  @param[in]  alpha1  Angle in radians by which vectors are skewed along the x-axis.
     *  @param[in]  alpha2  Angle in radians by which vectors are skewed along the y-axis.
     */
    void addSkew(double alpha1, double alpha2) noexcept;

    /**
     *  @brief      Add skew along the x-axis.
     *  @details    This function adds a skew along to the x axis to the transformation matrix.
     *  @param[in]  alpha  Angle in radians by which vectors are skewed along the x-axis.
     */
    void addSkewX(double alpha1) noexcept;

    /**
     *  @brief      Add skew along the y-axis.
     *  @details    This function adds a skew along to the y axis to the transformation matrix.
     *  @param[in]  alpha  Angle in radians by which vectors are skewed along the y-axis.
     */
    void addSkewY(double alpha1) noexcept;

    /**
     *  @brief      Transform vector.
     *  @details    This function applies the current affine transformation to a 2D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @param[in]  u  Vector to be transformed.
     *  @returns    The transformed vector.
     */
    template<typename T>
    Vector2D<T> transform(const Vector2D<T>& u) const noexcept;

    /**
     *  @brief      Transform vectors.
     *  @details    This function applies the current affine transformation to a set of 2D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @param[in]  u  Vectors to be transformed.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T>
    Array<Vector2D<T>> transform(const Array<Vector2D<T>>& u) const;

    /**
     *  @brief      Rotation angle.
     *  @details    This operator calculates the angle that is needed to rotate a vector u to the direction 
     *              of a vector v.
     *  @tparam     T  The data type of the input vectors.
     *  @param[in]  u  Vector u.
     *  @param[in]  v  Vector v.
     *  @returns    The rotation angle in radians.
     */
    template<typename T>
    static double rotationAngle(const Vector2D<T>& u, const Vector2D<T>& v) noexcept;

    /**
     *  @brief      Rotation matrix.
     *  @details    This function calculates the rotation matrix that corresponds to the specified 
     *              rotation angle.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    The calculated transformation matrix.
     */
    static AffineTransformation rotationMatrix(double theta) noexcept;

    /**
     *  @brief      Rotation matrix around one point.
     *  @details    This function calculates the rotation matrix that corresponds to the specified 
     *              rotation angle and pivot point.
     *  @param[in]  p  Pivot point.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    The calculated transformation matrix.
     */
    static AffineTransformation rotationAroundMatrix(const Point2D& p, double theta) noexcept;

    /**
     *  @brief      Translation matrix.
     *  @details    This function calculates the translation matrix that corresponds to the specified 
     *              offset.
     *  @param[in]  dx  Translation of the first coordinate.
     *  @param[in]  dy  Translation of the second coordinate.
     *  @returns    The calculated transformation matrix.
     */    
    static AffineTransformation translationMatrix(double dx, double dy) noexcept;

    /**
     *  @brief      Scaling matrix.
     *  @details    This function calculates the scaling matrix that corresponds to the specified scale 
     *              factors.
     *  @param[in]  sx  Scale of the first coordinate.
     *  @param[in]  sy  Scale of the second coordinate.
     *  @returns    The calculated transformation matrix.
     */    
    static AffineTransformation scalingMatrix(double sx, double sy) noexcept;

    /**
     *  @brief      Skew matrix.
     *  @details    This function calculates the skew matrix that corresponds to the specified angles.
     *  @param[in]  alpha1  Angle in radians by which vectors are skewed along the x-axis.
     *  @param[in]  alpha2  Angle in radians by which vectors are skewed along the y-axis.
     *  @returns    The calculated transformation matrix.
     */    
    static AffineTransformation skewMatrix(double alpha1, double alpha2) noexcept;

    // IO Operations.

    /**
     *  @brief      Write an affine transformation to an output stream.
     *  @details    This function writes a transformation matrix to an output stream in binary format.
     *  @param[in, out] o  The output stream where the data will be written.
     */
    void write(std::ostream& o) const;

    /**
     *  @brief      Read an affine transformation from an input stream.
     *  @details    This function reads a transformation matrix from an input stream in binary format.
     *  @param[in, out] i  The input stream from where the data will be read.
     *  @returns    The object that was read from the input stream.
     */
    static AffineTransformation read(std::istream& i);

    ////////// Direct trasnformation functions //////////

    /**
     *  @brief      Vector rotation.
     *  @details    This function applies the specified rotation to a 2D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @tparam     U  The data type of the rotation angle.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    The transformed vector.
     */
    template<typename T, nct::Arithmetic U>
    static Vector2D<T> rotate(const Vector2D<T>& u, const U& theta) noexcept;

    /**
     *  @brief      Rotation of vectors.
     *  @details    This function applies the specified rotation to a set of 2D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @tparam     U  The data type of the rotation angle.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T, nct::Arithmetic U>
    static Array<Vector2D<T>> rotate(const Array<Vector2D<T>>& u, const U& theta);

    /**
     *  @brief      Vector rotation around one point.
     *  @details    This function applies the specified rotation around one point to a 2D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @tparam     U  The data type of the rotation angle.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  p  Pivot point.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    The transformed vector.
     */
    template<typename T, nct::Arithmetic U>
    static Vector2D<T> rotateAround(const Vector2D<T>& u,
        const Vector2D<T>&p, const U& theta) noexcept;

    /**
     *  @brief      Rotation of vectors around one point.
     *  @details    This function applies the specified rotation around one point to a set of 2D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @tparam     U  The data type of the rotation angle.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  p  Pivot point.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T, nct::Arithmetic U>
    static Array<Vector2D<T>> rotateAround(const Array<Vector2D<T>>& u,
        const Vector2D<T>&p, const U& theta);

    /**
     *  @brief      Vector translation.
     *  @details    This function applies the specified translation to a 2D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  dx  Translation of the first coordinate.
     *  @param[in]  dy  Translation of the second coordinate.
     *  @returns    The transformed vector.
     */
    template<typename T>
    static Vector2D<T> translate(const Vector2D<T>& u, const T& dx, const T& dy) noexcept;

    /**
     *  @brief      Translation of vectors.
     *  @details    This function applies the specified translation to a set of 2D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  dx  Translation of the first coordinate.
     *  @param[in]  dy  Translation of the second coordinate.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T>
    static Array<Vector2D<T>> translate(const Array<Vector2D<T>>& u, const T& dx, const T& dy);

    /**
     *  @brief      Vector translation on x.
     *  @details    This function applies the specified translation along the x-axis to a 2D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  d  Translation.
     *  @returns    The transformed vector.
     */
    template<typename T>
    static Vector2D<T> translateX(const Vector2D<T>& u, const T& d) noexcept;

    /**
     *  @brief      Translation of vectors on x.
     *  @details    This function applies the specified translations along the x-axis to a set of 2D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  d  Translation.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T>
    static Array<Vector2D<T>> translateX(const Array<Vector2D<T>>& u, const T& d);

    /**
     *  @brief      Vector translation on y.
     *  @details    This function applies the specified translation along the y-axis to a 2D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  d  Translation.
     *  @returns    The transformed vector.
     */
    template<typename T>
    static Vector2D<T> translateY(const Vector2D<T>& u, const T& d) noexcept;

    /**
     *  @brief      Translation of vectors on y.
     *  @details    This function applies the specified translations along the yx-axis to a set of 2D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  d  Translation.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T>
    static Array<Vector2D<T>> translateY(const Array<Vector2D<T>>& u, const T& d);

    /**
     *  @brief      Vector scaling.
     *  @details    This function applies the specified scaling to a 2D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  sx  Scale factor of the first coordinate.
     *  @param[in]  sy  Scale factor of the second coordinate.
     *  @returns    The transformed vector.
     */
    template<typename T>
    static Vector2D<T> scale(const Vector2D<T>& u, const T& sx, const T& sy) noexcept;

    /**
     *  @brief      Scaling of vectors.
     *  @details    This function applies the specified scaling to a set of 2D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  sx  Scale factor of the first coordinate.
     *  @param[in]  sy  Scale factor of the second coordinate.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T>
    static Array<Vector2D<T>> scale(const Array<Vector2D<T>>& u, const T& sx, const T& sy);

    /**
     *  @brief      Vector scaling on x.
     *  @details    This function applies the specified scaling along the x-axis to a 2D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  s  Scale factor.
     *  @returns    The transformed vector.
     */
    template<typename T>
    static Vector2D<T> scaleX(const Vector2D<T>& u, const T& s) noexcept;

    /**
     *  @brief      Scaling of vectors on x.
     *  @details    This function applies the specified scaling along the x-axis to a set of 2D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  s  Scale factor.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T>
    static Array<Vector2D<T>> scaleX(const Array<Vector2D<T>>& u, const T& s);

    /**
     *  @brief      Vector scaling on y.
     *  @details    This function applies the specified scaling along the y-axis to a 2D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  s  Scale factor.
     *  @returns    The transformed vector.
     */
    template<typename T>
    static Vector2D<T> scaleY(const Vector2D<T>& u, const T& s) noexcept;

    /**
     *  @brief      Scaling of vectors on y.
     *  @details    This function applies the specified scaling along the y-axis to a set of 2D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  s  Scale factor.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T>
    static Array<Vector2D<T>> scaleY(const Array<Vector2D<T>>& u, const T& s);

    /**
     *  @brief      Vector skewing.
     *  @details    This function applies the specified skewing to a 2D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @tparam     U  The data type of the transformation angles.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  alphax  Angle in radians by which the vector is skewed along the x-axis.
     *  @param[in]  alphay  Angle in radians by which the vector is skewed along the y-axis.
     *  @returns    The transformed vector.
     */
    template<typename T, nct::Arithmetic U>
    static Vector2D<T> skew(const Vector2D<T>& u, const U& alphax, const U& alphay) noexcept;

    /**
     *  @brief      Skewing of vectors.
     *  @details    This function applies the specified skewing to a set of 2D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @tparam     U  The data type of the transformation angles.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  alphax  Angle in radians by which the vector is skewed along the x-axis.
     *  @param[in]  alphay  Angle in radians by which the vector is skewed along the y-axis.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T, nct::Arithmetic U>
    static Array<Vector2D<T>> skew(const Array<Vector2D<T>>& u, const U& alphax, const U& alphay);

    /**
     *  @brief      Vector skewing on x.
     *  @details    This function applies the specified skewing along the x-axis to a 2D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @tparam     U  The data type of the transformation angle.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  alpha  Skew angle in radians.
     *  @returns    The transformed vector.
     */
    template<typename T, nct::Arithmetic U>
    static Vector2D<T> skewX(const Vector2D<T>& u, const U& alpha) noexcept;

    /**
     *  @brief      Skewing of vectors on x.
     *  @details    This function applies the specified skewing along the x-axis to a set of 2D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @tparam     U  The data type of the transformation angle.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  alpha  Skew angle in radians.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T, nct::Arithmetic U>
    static Array<Vector2D<T>> skewX(const Array<Vector2D<T>>& u, const U& alpha);

    /**
     *  @brief      Vector skewing on y.
     *  @details    This function applies the specified skewing along the y-axis to a 2D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @tparam     U  The data type of the transformation angle.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  alpha  Skew angle in radians.
     *  @returns    The transformed vector.
     */
    template<typename T, nct::Arithmetic U>
    static Vector2D<T> skewY(const Vector2D<T>& u, const U& alpha) noexcept;

    /**
     *  @brief      Skewing of vectors on y.
     *  @details    This function applies the specified skewing along the y-axis to a set of 2D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @tparam     U  The data type of the transformation angle.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  alpha  Skew angle in radians.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T, nct::Arithmetic U>
    static Array<Vector2D<T>> skewY(const Array<Vector2D<T>>& u, const U& alpha);

private:

    ////////// Data members //////////

    /** Transformation matrix M(m00, m01, m02; m10, m11, m12). */
    double m_[2][3] = { {1.0, 0.0, 0.0},{0.0, 1.0, 0.0} };    

};

////////// Global operators //////////

/**
 *  @brief      Input stream to affine transformation.
 *  @details    This operators reads the contents of a transformation matrix from an input stream. 
 *              The data are read in binary format.
 *  @param[in, out] i  Input stream.
 *  @param[out] tm  Object where the data are stored.
 *  @returns    A reference to the stream.
 */
NCT_EXPIMP std::istream& operator>>(std::istream& i, geometry::AffineTransformation& tm);

/**
 *  @brief      Affine transformation to output stream.
 *  @details    This operator writes the contents of the array in an output stream. The data
 *              is displayed in ASCII format. If a binary serialization is required, use 
 *              the "write" method instead. 
 *  @param[in, out] o  Output stream.
 *  @param[in]  arr  The object to be written.
 *  @returns    A reference to the stream.
 */
NCT_EXPIMP std::ostream& operator<<(std::ostream& o,
    const geometry::AffineTransformation& tm);

/**
 *  @brief      Scalar product.
 *  @details    This operator calculates the product of the transformation matrix with a scalar.
 *  @param[in]  left  Scalar value.
 *  @param[in]  right  Matrix to multiply.
 *  @returns    The result of the operation.
 */
NCT_EXPIMP geometry::AffineTransformation operator*(double val,
    const geometry::AffineTransformation& tm) noexcept;

}}

////////// Implementation of method templates //////////
#include <nct/geometry/AffineTransformation_template.h>

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
