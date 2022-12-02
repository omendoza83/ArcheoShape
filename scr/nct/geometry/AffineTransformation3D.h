//=================================================================================================================
/**
 *  @file       AffineTransformation3D.h
 *  @brief      nct::geometry::AffineTransformation3D class.
 *  @details    Declaration of the nct::geometry::AffineTransformation3D class.
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

#ifndef NCT_AFFINE_TRANSFORMATION_3D_H_INCLUDE
#define NCT_AFFINE_TRANSFORMATION_3D_H_INCLUDE

//=================================================================================================================
//        HEADERS
//=================================================================================================================
#include <nct/nct.h>
#include <nct/nct_exception.h>
#include <nct/Array.h>
#include <nct/Vector3D.h>
#include <nct/math/math.h>

#include <iostream>

//=================================================================================================================
namespace nct {
namespace geometry {

/**
 *  @brief      3D affine transformaiton class.
 *  @details    The AffineTransform3D class represents a 3D affine transform that performs a linear
 *              mapping from 3D coordinates to other 3D coordinates that preserves the "straightness"
 *              and "parallelness" of lines and planes. Affine transformations can be constructed
 *              using sequences of translations, scales, flips, rotations, and shears.
 *              Such transformations can be represented using a matrix-vector product of a
 *              transformation array M(m00, m01, m02, m03; m10, m11, m12, m13, m20, m21, m22, m23,
 *              0, 0, 0, 1) and a point P(x, y, z).
 *              This class also includes direct methods to transform points.
 */
class NCT_EXPIMP AffineTransformation3D final {

public:

    ////////// Constructors //////////

    /**
     *  @brief      Default constructor.
     *  @details    This constructor initializes an instance of this class using the default configuration. 
     *              The affine transformation is initialized as an identity matrix.
     */
    AffineTransformation3D() noexcept = default;

    /**
     *  @brief      Class constructor.
     *  @details    This constructor initializes the affine transformation using the specified components.
     *  @param[in]  ma00  Value of the coefficient M(0,0).
     *  @param[in]  ma01  Value of the coefficient M(0,1).
     *  @param[in]  ma02  Value of the coefficient M(0,2).
     *  @param[in]  ma03  Value of the coefficient M(0,3).
     *  @param[in]  ma10  Value of the coefficient M(1,0).
     *  @param[in]  ma11  Value of the coefficient M(1,1).
     *  @param[in]  ma12  Value of the coefficient M(1,2).
     *  @param[in]  ma13  Value of the coefficient M(1,3).
     *  @param[in]  ma20  Value of the coefficient M(2,0).
     *  @param[in]  ma21  Value of the coefficient M(2,1).
     *  @param[in]  ma22  Value of the coefficient M(2,2).
     *  @param[in]  ma23  Value of the coefficient M(2,3).
     */
    AffineTransformation3D(double ma00, double ma01, double ma02, double ma03,
        double ma10, double ma11, double ma12, double ma13,
        double ma20, double ma21, double ma22, double ma23) noexcept;
    
    ////////// Operators ////////// 
    
    /**
     *  @brief      Equality operator.
     *  @details    Two matrices are equal if each element 
     *              of one array is equal to the element with the same index in the other array.
     *  @param[in]  right  Array to compare.
     *  @returns    True if both arrays are equal.
     */
    bool operator==(const AffineTransformation3D& right) const noexcept;

    /**
     *  @brief      Inequality operator.
     *  @details    Two arrays are not equal if have different same size or element 
     *              of one array is not equal to the element with the same index in the other array.
     *  @param[in]  right  Array to compare.
     *  @returns    True if both arrays are not equal.
     */
    bool operator!=(const AffineTransformation3D& right) const noexcept;

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
    AffineTransformation3D operator+() const noexcept;

    /**
     *  @brief      Matrix addition.
     *  @details    This operator calculates the sum of two transformation matrices.
     *  @param[in]  right  Matrix on the right side of the operation.
     *  @returns    The result of the operation.
     */
    AffineTransformation3D operator+(const AffineTransformation3D& right) const noexcept;

    /**
     *  @brief      Matrix addition.
     *  @details    This operator calculates the sum of two transformation matrices.
     *  @param[in]  right  Matrix on the right side of the operation.
     *  @returns    A reference to the object.
     */
    const AffineTransformation3D& operator+=(const AffineTransformation3D& right) noexcept;

    /**
     *  @brief      Unary minus.
     *  @details    This operator multiplies by minus one each element inside the transformation matrix.
     *  @returns    The result of the operation.
     */
    AffineTransformation3D operator-() const noexcept;

    /**
     *  @brief      Matrix substraction.
     *  @details    This operator calculates the substraction of two transformation matrices.
     *  @param[in]  right  Matrix on the right side of the operation.
     *  @returns    The result of the operation.
     */
    AffineTransformation3D operator-(const AffineTransformation3D& right) const noexcept;

    /**
     *  @brief      Matrix substraction.
     *  @details    This operator calculates the substraction of two transformation matrices.
     *  @param[in]  right  Matrix on the right side of the operation.
     *  @returns    A reference to the object.
     */
    const AffineTransformation3D& operator-=(const AffineTransformation3D& right) noexcept;

    /**
     *  @brief      Matrix multiplication.
     *  @details    This operator calculates the product of two transformation matrices.
     *  @param[in]  right  Matrix on the right side of the operation.
     *  @returns    The result of the operation.
     */
    AffineTransformation3D operator*(const AffineTransformation3D& right) const noexcept;

    /**
     *  @brief      Matrix multiplication.
     *  @details    This operator calculates the product of two transformation matrices.
     *  @param[in]  right  Matrix on the right side of the operation.
     *  @returns    A reference to the object.
     */
    const AffineTransformation3D& operator*=(const AffineTransformation3D& right) noexcept;

    /**
     *  @brief      Scalar product.
     *  @details    This operator calculates the product of the transformation matrix with a scalar.
     *  @param[in]  right  Scalar value.
     *  @returns    The result of the operation.
     */
    AffineTransformation3D operator*(double right) const noexcept;

    /**
     *  @brief      Scalar product.
     *  @details    This operator calculates the product of the transformation matrix with a scalar.
     *  @param[in]  right  Scalar value.
     *  @returns    A reference to the object.
     */
    const AffineTransformation3D& operator*=(double right) noexcept;

    /**
     *  @brief      Scalar division.
     *  @details    This operator calculates the division of the matrix with a scalar.
     *  @param[in]  right  Scalar value.
     *  @returns    The result of the operation.
     */
    AffineTransformation3D operator/(double right) const noexcept;

    /**
     *  @brief      Scalar division.
     *  @details    This operator calculates the division of the matrix with a scalar and stores the 
     *              result in the same instance.
     *  @param[in]  right  Scalar value.
     *  @returns    A reference to the object.
     */
    const AffineTransformation3D& operator/=(double right) noexcept;

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
     *  @brief      Coefficient M(0, 3).
     *  @details    This function returns the coefficient M(0, 3) of the affine transformation.
     *  @returns    The transformaiton coefficient M(0, 3).
     */
    double& m03() noexcept;

    /**
     *  @brief      Coefficient M(0, 3).
     *  @details    This function returns the coefficient M(0, 3) of the affine transformation.
     *  @returns    The transformaiton coefficient M(0, 3).
     */
    const double& m03() const noexcept;

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
     *  @brief      Coefficient M(1, 3).
     *  @details    This function returns the coefficient M(1, 3) of the affine transformation.
     *  @returns    The transformaiton coefficient M(1, 3).
     */
    double& m13() noexcept;

    /**
     *  @brief      Coefficient M(1, 3).
     *  @details    This function returns the coefficient M(1, 3) of the affine transformation.
     *  @returns    The transformaiton coefficient M(1, 3).
     */
    const double& m13() const noexcept;

    /**
     *  @brief      Coefficient M(2, 0).
     *  @details    This function returns the coefficient M(2, 0) of the affine transformation.
     *  @returns    The transformaiton coefficient M(2, 0).
     */
    double& m20() noexcept;

    /**
     *  @brief      Coefficient M(2, 0).
     *  @details    This function returns the coefficient M(2, 0) of the affine transformation.
     *  @returns    The transformaiton coefficient M(2, 0).
     */
    const double& m20() const noexcept;

    /**
     *  @brief      Coefficient M(2, 1).
     *  @details    This function returns the coefficient M(2, 1) of the affine transformation.
     *  @returns    The transformaiton coefficient M(2, 1).
     */
    double& m21() noexcept;

    /**
     *  @brief      Coefficient M(2, 1).
     *  @details    This function returns the coefficient M(2, 1) of the affine transformation.
     *  @returns    The transformaiton coefficient M(2, 1).
     */
    const double& m21() const noexcept;

    /**
     *  @brief      Coefficient M(2, 2).
     *  @details    This function returns the coefficient M(2, 2) of the affine transformation.
     *  @returns    The transformaiton coefficient M(2, 2).
     */
    double& m22() noexcept;

    /**
     *  @brief      Coefficient M(2, 2).
     *  @details    This function returns the coefficient M(2, 2) of the affine transformation.
     *  @returns    The transformaiton coefficient M(2, 2).
     */
    const double& m22() const noexcept;

    /**
     *  @brief      Coefficient M(2, 3).
     *  @details    This function returns the coefficient M(2, 3) of the affine transformation.
     *  @returns    The transformaiton coefficient M(2, 3).
     */
    double& m23() noexcept;

    /**
     *  @brief      Coefficient M(2, 3).
     *  @details    This function returns the coefficient M(2, 3) of the affine transformation.
     *  @returns    The transformaiton coefficient M(2, 3).
     */
    const double& m23() const noexcept;

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
    void addTransformation(const AffineTransformation3D& tm) noexcept;

    /**
     *  @brief      Add rotation.
     *  @details    This function adds a rotation to the transformation matrix.
     *  @param[in]  w  Rotation axis.
     *  @param[in]  theta  Rotation angle.
     */
    void addRotation(const Vector3D<double>& w, double theta);

    /**
     *  @brief      Add rotation around x.
     *  @details    This function adds a rotation around the x-axis to the transformation matrix.
     *  @param[in]  theta  Rotation angle.
     */
    void addRotationX(double theta) noexcept;

    /**
     *  @brief      Add rotation around y.
     *  @details    This function adds a rotation around the y-axis to the transformation matrix.
     *  @param[in]  theta  Rotation angle.
     */
    void addRotationY(double theta) noexcept;

    /**
     *  @brief      Add rotation around z.
     *  @details    This function adds a rotation around the z-axis to the transformation matrix.
     *  @param[in]  theta  Rotation angle.
     */
    void addRotationZ(double theta) noexcept;

    /**
     *  @brief      Add rotation around x, y and z.
     *  @details    This function adds a rotation around the axes x, y and z (in this order).
     *  @param[in]  thetaX  Rotation angle about x axis.
     *  @param[in]  thetaY  Rotation angle about y axis.
     *  @param[in]  thetaZ  Rotation angle about z axis.
     */
    void addRotationXYZ(double thetaX, double thetaY, double thetaZ) noexcept;

    /**
     *  @brief      Add rotation around x, z and y.
     *  @details    This function adds a rotation around the axes x, z and y (in this order).
     *  @param[in]  thetaX  Rotation angle about x axis.
     *  @param[in]  thetaY  Rotation angle about y axis.
     *  @param[in]  thetaZ  Rotation angle about z axis.
     */
    void addRotationXZY(double thetaX, double thetaY, double thetaZ) noexcept;

    /**
     *  @brief      Add rotation around y, x and z.
     *  @details    This function adds a rotation around the axes y, x and z (in this order).
     *  @param[in]  thetaX  Rotation angle about x axis.
     *  @param[in]  thetaY  Rotation angle about y axis.
     *  @param[in]  thetaZ  Rotation angle about z axis.
     */
    void addRotationYXZ(double thetaX, double thetaY, double thetaZ) noexcept;

    /**
     *  @brief      Add rotation around y, z and x.
     *  @details    This function adds a rotation around the axes y, z and x (in this order).
     *  @param[in]  thetaX  Rotation angle about x axis.
     *  @param[in]  thetaY  Rotation angle about y axis.
     *  @param[in]  thetaZ  Rotation angle about z axis.
     */
    void addRotationYZX(double thetaX, double thetaY, double thetaZ) noexcept;

    /**
     *  @brief      Add rotation around z, x and y.
     *  @details    This function adds a rotation around the axes z, x and y (in this order).
     *  @param[in]  thetaX  Rotation angle about x axis.
     *  @param[in]  thetaY  Rotation angle about y axis.
     *  @param[in]  thetaZ  Rotation angle about z axis.
     */
    void addRotationZXY(double thetaX, double thetaY, double thetaZ) noexcept;

    /**
     *  @brief      Add rotation around z, y and x.
     *  @details    This function adds a rotation around the axes z, y and x (in this order).
     *  @param[in]  thetaX  Rotation angle about x axis.
     *  @param[in]  thetaY  Rotation angle about y axis.
     *  @param[in]  thetaZ  Rotation angle about z axis.
     */
    void addRotationZYX(double thetaX, double thetaY, double thetaZ) noexcept;

    /**
     *  @brief      Add translation.
     *  @details    This function adds a translation to the transformation matrix.
     *  @param[in]  dx  Translation of the first coordinate.
     *  @param[in]  dy  Translation of the second coordinate.
     *  @param[in]  dz  Translation of the third coordinate.
     */
    void addTranslation(double dx, double dy, double dz) noexcept;

    /**
     *  @brief      Add translation along the x-axis.
     *  @details    This function adds a translation along the x-axis to the transformation matrix.
     *  @param[in]  d  Translation.
     */
    void addTranslationX(double d) noexcept;

    /**
     *  @brief      Add translation along the y-axis.
     *  @details    This function adds a translation along the y-axis to the transformation matrix.
     *  @param[in]  d  Translation.
     */
    void addTranslationY(double d) noexcept;

    /**
     *  @brief      Add translation along the z-axis.
     *  @details    This function adds a translation along the z-axis to the transformation matrix.
     *  @param[in]  d  Translation.
     */
    void addTranslationZ(double d) noexcept;

    /**
     *  @brief      Add scaling.
     *  @details    This function adds a scaling to the transformation matrix.
     *  @param[in]  sx  Scale of the first coordinate.
     *  @param[in]  sy  Scale of the second coordinate.
     *  @param[in]  sz  Scale of the third coordinate.
     */
    void addScaling(double sx, double sy, double sz) noexcept;

    /**
     *  @brief      Add scaling along the x-axis.
     *  @details    This function adds a scaling along the x-axis to the transformation matrix.
     *  @param[in]  s  Scale factor.
     */
    void addScalingX(double s) noexcept;

    /**
     *  @brief      Add scaling along the y-axis.
     *  @details    This function adds a scaling along the y-axis to the transformation matrix.
     *  @param[in]  s  Scale factor.
     */
    void addScalingY(double s) noexcept;

    /**
     *  @brief      Add scaling along the z-axis.
     *  @details    This function adds a scaling along the z-axis to the transformation matrix.
     *  @param[in]  s  Scale factor.
     */
    void addScalingZ(double s) noexcept;

    /**
     *  @brief      Add x-y skew.
     *  @details    This function adds a x-y skew to the transformation matrix.
     *  @param[in]  alpha  Skew angle in radians.
     */
    void addSkewXY(double alpha) noexcept;

    /**
     *  @brief      Add y-x skew.
     *  @details    This function adds a y-x skew to the transformation matrix.
     *  @param[in]  alpha  Skew angle in radians.
     */
    void addSkewYX(double alpha) noexcept;

    /**
     *  @brief      Add x-z skew.
     *  @details    This function adds a x-z skew to the transformation matrix.
     *  @param[in]  alpha  Skew angle in radians.
     */
    void addSkewXZ(double alpha) noexcept;

    /**
     *  @brief      Add z-x skew.
     *  @details    This function adds a z-x skew to the transformation matrix.
     *  @param[in]  alpha  Skew angle in radians.
     */
    void addSkewZX(double alpha) noexcept;

    /**
     *  @brief      Add y-z skew.
     *  @details    This function adds a y-z skew to the transformation matrix.
     *  @param[in]  alpha  Skew angle in radians.
     */
    void addSkewYZ(double alpha) noexcept;

    /**
     *  @brief      Add z-y skew.
     *  @details    This function adds a z-y skew to the transformation matrix.
     *  @param[in]  alpha  Skew angle in radians.
     */
    void addSkewZY(double alpha) noexcept;

    /**
     *  @brief      Transform vector.
     *  @details    This function applies the current affine transformation to a 3D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @param[in]  u  Vector to be transformed.
     *  @returns    The transformed vector.
     */
    template<typename T>
    Vector3D<T> transform(const Vector3D<T>& u) const noexcept;

    /**
     *  @brief      Transform vectors.
     *  @details    This function applies the current affine transformation to a set of 3D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @param[in]  u  Vectors to be transformed.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T>
    Array<Vector3D<T>> transform(const Array<Vector3D<T>>& u) const;

    /**
     *  @brief      Rotation system.
     *  @details    This operator calculates the rotation that is needed to align a vector u to the direction of a vector v.
     *              The result is expressed in the axis-angle representation.
     *  @tparam     T  The data type of the input vector.
     *  @param[in]  u  Vector u.
     *  @param[in]  v  Vector v.
     *  @returns    A tuple that containts the folloging elements of the rotation system:\n
     *              * The rotation axis.
     *              * The rotation angle.
     */
    template<typename T>
    static std::tuple<Vector3D<double>, double> rotationSystem(const Vector3D<T>& u, const Vector3D<T>& v);

    /**
     *  @brief      Rotation matrix.
     *  @details    This function calculates the rotation matrix that corresponds to the specified
     *              rotation axis and rotation angle.
     *  @param[in]  w  Rotation axis.
     *  @param[in]  theta  Rotation angle.
     *  @returns    The calculated transformation matrix.
     */
    static AffineTransformation3D rotationMatrix(
        const Vector3D<double>& w, double theta);

    /**
     *  @brief      Rotation matrix X.
     *  @details    This function calculates the rotation matrix about X axis that corresponds to the 
     *              specified rotation angle.
     *  @param[in]  theta  Rotation angle about x axis.
     *  @returns    The calculated transformation matrix.
     */
    static AffineTransformation3D rotationMatrixX(double theta) noexcept;

    /**
     *  @brief      Rotation matrix Y.
     *  @details    This function calculates the rotation matrix about Y axis that corresponds to the 
     *              specified rotation angle.
     *  @param[in]  theta  Rotation angle about y axis.
     *  @returns    The calculated transformation matrix.
     */
    static AffineTransformation3D rotationMatrixY(double theta) noexcept;

    /**
     *  @brief      Rotation matrix Z.
     *  @details    This function calculates the rotation matrix about Z axis that corresponds to the 
     *              specified rotation angle.
     *  @param[in]  theta  Rotation angle about z axis.
     *  @returns    The calculated transformation matrix.
     */
    static AffineTransformation3D rotationMatrixZ(double theta) noexcept;

    /**
     *  @brief      Rotation matrix RxRyRz.
     *  @details    This function calculates the rotation matrix about x, y and z that corresponds to the 
     *              specified angles.
     *  @param[in]  thetaX  Rotation angle about x axis.
     *  @param[in]  thetaY  Rotation angle about y axis.
     *  @param[in]  thetaZ  Rotation angle about z axis.
     *  @returns    The calculated transformation matrix.
     */
    static AffineTransformation3D rotationMatrixXYZ(
        double thetaX, double thetaY, double thetaZ) noexcept;

    /**
     *  @brief      Rotation matrix RxRzRy.
     *  @details    This function calculates the rotation matrix about x, z and y that corresponds to the 
     *              specified angles.
     *  @param[in]  thetaX  Rotation angle about x axis.
     *  @param[in]  thetaY  Rotation angle about y axis.
     *  @param[in]  thetaZ  Rotation angle about z axis.
     *  @returns    The calculated transformation matrix.
     */
    static AffineTransformation3D rotationMatrixXZY(
        double thetaX, double thetaY, double thetaZ) noexcept;

    /**
     *  @brief      Rotation matrix RyRxRz.
     *  @details    This function calculates the rotation matrix about y, x and z that corresponds to the 
     *              specified angles.
     *  @param[in]  thetaX  Rotation angle about x axis.
     *  @param[in]  thetaY  Rotation angle about y axis.
     *  @param[in]  thetaZ  Rotation angle about z axis.
     *  @returns    The calculated transformation matrix.
     */
    static AffineTransformation3D rotationMatrixYXZ(
        double thetaX, double thetaY, double thetaZ) noexcept;

    /**
     *  @brief      Rotation matrix RyRzRx.
     *  @details    This function calculates the rotation matrix about y, z and x that corresponds to the 
     *              specified angles.
     *  @param[in]  thetaX  Rotation angle about x axis.
     *  @param[in]  thetaY  Rotation angle about y axis.
     *  @param[in]  thetaZ  Rotation angle about z axis.
     *  @returns    The calculated transformation matrix.
     */
    static AffineTransformation3D rotationMatrixYZX(
        double thetaX, double thetaY, double thetaZ) noexcept;

    /**
     *  @brief      Rotation matrix RzRxRy.
     *  @details    This function calculates the rotation matrix about z, x and y that corresponds to the 
     *              specified angles.
     *  @param[in]  thetaX  Rotation angle about x axis.
     *  @param[in]  thetaY  Rotation angle about y axis.
     *  @param[in]  thetaZ  Rotation angle about z axis.
     *  @returns    The calculated transformation matrix.
     */
    static AffineTransformation3D rotationMatrixZXY(
        double thetaX, double thetaY, double thetaZ) noexcept;

    /**
     *  @brief      Rotation matrix RzRyRx.
     *  @details    This function calculates the rotation matrix about z, y and x that corresponds to the 
     *              specified angles.
     *  @param[in]  thetaX  Rotation angle about x axis.
     *  @param[in]  thetaY  Rotation angle about y axis.
     *  @param[in]  thetaZ  Rotation angle about z axis.
     *  @returns    The calculated transformation matrix.
     */
    static AffineTransformation3D rotationMatrixZYX(
        double thetaX, double thetaY, double thetaZ) noexcept;

    /**
     *  @brief      Translation matrix.
     *  @details    This function calculates the translation matrix that corresponds to the specified offset.
     *  @param[in]  dx  Translation of the first coordinate.
     *  @param[in]  dy  Translation of the second coordinate.
     *  @param[in]  dz  Translation of the third coordinate.
     *  @returns    The calculated transformation matrix.
     */    
    static AffineTransformation3D translationMatrix(
        double dx, double dy, double dz) noexcept;

    /**
     *  @brief      Scaling matrix.
     *  @details    This function calculates the scaling matrix that corresponds to the specified scales.
     *  @param[in]  sx  Scale of the first coordinate.
     *  @param[in]  sy  Scale of the second coordinate.
     *  @param[in]  sz  Scale of the third coordinate.
     *  @returns    The calculated transformation matrix.
     */    
    static AffineTransformation3D scalingMatrix(
        double sy, double sx, double sz) noexcept;

    /**
     *  @brief      Skew matrix X-Y.
     *  @details    This function calculates the skew matrix for the specified angle along the x-axis 
     *              as the y value increases.
     *  @param[in]  alpha  Skew angle in radians.
     *  @returns    The calculated transformation matrix.
     */    
    static AffineTransformation3D skewMatrixXY(double alpha) noexcept;

    /**
     *  @brief      Skew matrix Y-X.
     *  @details    This function calculates the skew matrix for the specified angle along the y-axis 
     *              as the x value increases.
     *  @param[in]  alpha  Skew angle in radians.
     *  @returns    The calculated transformation matrix.
     */    
    static AffineTransformation3D skewMatrixYX(double alpha) noexcept;

    /**
     *  @brief      Skew matrix X-Z.
     *  @details    This function calculates the skew matrix for the specified angle along the x-axis 
     *              as the z value increases.
     *  @param[in]  alpha  Skew angle in radians.
     *  @returns    The calculated transformation matrix.
     */    
    static AffineTransformation3D skewMatrixXZ(double alpha) noexcept;

    /**
     *  @brief      Skew matrix Z-X.
     *  @details    This function calculates the skew matrix for the specified angle along the z-axis 
     *              as the x value increases.
     *  @param[in]  alpha  Skew angle in radians.
     *  @returns    The calculated transformation matrix.
     */    
    static AffineTransformation3D skewMatrixZX(double alpha) noexcept;

    /**
     *  @brief      Skew matrix Y-Z.
     *  @details    This function calculates the skew matrix for the specified angle along the y-axis 
     *              as the z value increases.
     *  @param[in]  alpha  Skew angle in radians.
     *  @returns    The calculated transformation matrix.
     */    
    static AffineTransformation3D skewMatrixYZ(double alpha) noexcept;

    /**
     *  @brief      Skew matrix Z-Y.
     *  @details    This function calculates the skew matrix for the specified angle along the z-axis 
     *              as the y value increases.
     *  @param[in]  alpha  Skew angle in radians.
     *  @returns    The calculated transformation matrix.
     */    
    static AffineTransformation3D skewMatrixZY(double alpha) noexcept;

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
    static AffineTransformation3D read(std::istream& i);

    ////////// Direct trasnformation functions //////////

    /**
     *  @brief      Vector rotation.
     *  @details    This function applies the specified rotation to a 3D vector. The rotation is about 
     *              the specified axis.
     *  @tparam     T  The data type of the input vector.
     *  @tparam     U  The data type of the rotation angle.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  w  Rotation axis.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    The transformed vector.
     */
    template<typename T, nct::Arithmetic U>
    static Vector3D<T> rotate(const Vector3D<T>& u, const Vector3D<U>& w, U theta);

    /**
     *  @brief      Rotation of vectors.
     *  @details    This function applies the specified rotation to a set of 3D vectors. The rotation is 
     *              about the specified axis.
     *  @tparam     T  The data type of the input vectors.
     *  @tparam     U  The data type of the rotation angle.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  w  Rotation axis.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T, nct::Arithmetic U>
    static Array<Vector3D<T>> rotate(const Array<Vector3D<T>>& u, const Vector3D<U>& w, U theta);

    /**
     *  @brief      Vector rotation about x.
     *  @details    This function applies the specified rotation about x axis to a 3D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @tparam     U  The data type of the rotation angle.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    The transformed vector.
     */
    template<typename T, nct::Arithmetic U>
    static Vector3D<T> rotateX(const Vector3D<T>& u, U theta) noexcept;

    /**
     *  @brief      Rotation of vectors about x.
     *  @details    This function applies the specified rotation about x axis to a set of 3D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @tparam     U  The data type of the rotation angle.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T, nct::Arithmetic U>
    static Array<Vector3D<T>> rotateX(const Array<Vector3D<T>>& u, U theta);

    /**
     *  @brief      Vector rotation about y.
     *  @details    This function applies the specified rotation about y axis to a 3D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @tparam     U  The data type of the rotation angle.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    The transformed vector.
     */
    template<typename T, nct::Arithmetic U>
    static Vector3D<T> rotateY(const Vector3D<T>& u, U theta) noexcept;

    /**
     *  @brief      Rotation of vectors about y.
     *  @details    This function applies the specified rotation about y axis to a set of 3D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @tparam     U  The data type of the rotation angle.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T, nct::Arithmetic U>
    static Array<Vector3D<T>> rotateY(const Array<Vector3D<T>>& u, U theta);

    /**
     *  @brief      Vector rotation about z.
     *  @details    This function applies the specified rotation about z axis to a 3D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @tparam     U  The data type of the rotation angle.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    The transformed vector.
     */
    template<typename T, nct::Arithmetic U>
    static Vector3D<T> rotateZ(const Vector3D<T>& u, U theta) noexcept;

    /**
     *  @brief      Rotation of vectors about z.
     *  @details    This function applies the specified rotation about z axis to a set of 3D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @tparam     U  The data type of the rotation angle.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  theta  Rotation angle in radians.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T, nct::Arithmetic U>
    static Array<Vector3D<T>> rotateZ(const Array<Vector3D<T>>& u, U theta);

    /**
     *  @brief      Vector translation.
     *  @details    This function applies the specified translation to a 3D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  dx  Translation of the first coordinate.
     *  @param[in]  dy  Translation of the second coordinate.
     *  @param[in]  dz  Translation of the third coordinate.
     *  @returns    The transformed vector.
     */
    template<typename T>
    static Vector3D<T> translate(const Vector3D<T>& u,
        const T& dx, const T& dy, const T& dz) noexcept;

    /**
     *  @brief      Translation of vectors.
     *  @details    This function applies the specified translation to a set of 2D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  dx  Translation of the first coordinate.
     *  @param[in]  dy  Translation of the second coordinate.
     *  @param[in]  dz  Translation of the third coordinate.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T>
    static Array<Vector3D<T>> translate(
        const Array<Vector3D<T>>& u, const T& dx, const T& dy, const T& dz);

    /**
     *  @brief      Vector translation on x.
     *  @details    This function applies the specified translation along the x-axis to a 3D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  d  Translation.
     *  @returns    The transformed vector.
     */
    template<typename T>
    static Vector3D<T> translateX(const Vector3D<T>& u, const T& d) noexcept;

    /**
     *  @brief      Translation of vectors on x.
     *  @details    This function applies the specified translation along the x-axis to a set of 2D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  d  Translation.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T>
    static Array<Vector3D<T>> translateX(const Array<Vector3D<T>>& u, const T& d);

    /**
     *  @brief      Vector translation on y.
     *  @details    This function applies the specified translation along the y-axis to a 3D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  d  Translation.
     *  @returns    The transformed vector.
     */
    template<typename T>
    static Vector3D<T> translateY(const Vector3D<T>& u, const T& d) noexcept;

    /**
     *  @brief      Translation of vectors on y.
     *  @details    This function applies the specified translation along the y-axis to a set of 2D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  d  Translation.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T>
    static Array<Vector3D<T>> translateY(const Array<Vector3D<T>>& u, const T& d);

    /**
     *  @brief      Vector translation on z.
     *  @details    This function applies the specified translation along the z-axis to a 3D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  d  Translation.
     *  @returns    The transformed vector.
     */
    template<typename T>
    static Vector3D<T> translateZ(const Vector3D<T>& u, const T& d) noexcept;

    /**
     *  @brief      Translation of vectors on z.
     *  @details    This function applies the specified translation along the z-axis to a set of 2D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  d  Translation.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T>
    static Array<Vector3D<T>> translateZ(const Array<Vector3D<T>>& u, const T& d);

    /**
     *  @brief      Vector scaling.
     *  @details    This function applies the specified scaling to a 3D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  sx  Scale factor of the first coordinate.
     *  @param[in]  sy  Scale factor of the second coordinate.
     *  @param[in]  sz  Scale factor of the third coordinate.
     *  @returns    The transformed vector.
     */
    template<typename T>
    static Vector3D<T> scale(const Vector3D<T>& u,
        const T& sx, const T& sy, const T& sz) noexcept;

    /**
     *  @brief      Scaling of vectors.
     *  @details    This function applies the specified scaling to a set of 3D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  sx  Scale factor of the first coordinate.
     *  @param[in]  sy  Scale factor of the second coordinate.
     *  @param[in]  sz  Scale factor of the third coordinate.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T>
    static Array<Vector3D<T>> scale(
        const Array<Vector3D<T>>& u, const T& sx, const T& sy, const T& sz);

    /**
     *  @brief      Vector scaling on x.
     *  @details    This function applies the specified scaling along the x-axis to a 3D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  s  Scale factor.
     *  @returns    The transformed vector.
     */
    template<typename T>
    static Vector3D<T> scaleX(const Vector3D<T>& u, const T& s) noexcept;

    /**
     *  @brief      Scaling of vectors on x.
     *  @details    This function applies the specified scaling along the x-axis to a set of 3D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  s  Scale factor.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T>
    static Array<Vector3D<T>> scaleX(const Array<Vector3D<T>>& u, const T& s);

    /**
     *  @brief      Vector scaling on y.
     *  @details    This function applies the specified scaling along the y-axis to a 3D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  s  Scale factor.
     *  @returns    The transformed vector.
     */
    template<typename T>
    static Vector3D<T> scaleY(const Vector3D<T>& u, const T& s) noexcept;

    /**
     *  @brief      Scaling of vectors on y.
     *  @details    This function applies the specified scaling along the y-axis to a set of 3D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  s  Scale factor.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T>
    static Array<Vector3D<T>> scaleY(const Array<Vector3D<T>>& u, const T& s);

    /**
     *  @brief      Vector scaling on z.
     *  @details    This function applies the specified scaling along the z-axis to a 3D vector. 
     *  @tparam     T  The data type of the input vector.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  s  Scale factor.
     *  @returns    The transformed vector.
     */
    template<typename T>
    static Vector3D<T> scaleZ(const Vector3D<T>& u, const T& s) noexcept;

    /**
     *  @brief      Scaling of vectors on z.
     *  @details    This function applies the specified scaling along the z-axis to a set of 3D vectors. 
     *  @tparam     T  The data type of the input vectors.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  s  Scale factor.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T>
    static Array<Vector3D<T>> scaleZ(const Array<Vector3D<T>>& u, const T& s);

    /**
     *  @brief      Vector skewing on X-Y.
     *  @details    This function applies the specified skewing along the x-axis that is obtained as 
     *              the y value increases.
     *  @tparam     T  The data type of the input vector.
     *  @tparam     U  The data type of the transformation angle.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  alpha  Skew angle in radians.
     *  @returns    The transformed vector.
     */
    template<typename T, nct::Arithmetic U>
    static Vector3D<T> skewXY(const Vector3D<T>& u, const U& alpha) noexcept;

    /**
     *  @brief      Skewing of vectors on X-Y.
     *  @details    This function applies the specified skewing along the x-axis that is obtained as 
     *              the y value increases.
     *  @tparam     T  The data type of the input vectors.
     *  @tparam     U  The data type of the transformation angle.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  alpha  Rotation angle in radians.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T, nct::Arithmetic U>
    static Array<Vector3D<T>> skewXY(const Array<Vector3D<T>>& u, const U& alpha);

    /**
     *  @brief      Vector skewing on Y-X.
     *  @details    This function applies the specified skewing along the y-axis that is obtained as 
     *              the x value increases.
     *  @tparam     T  The data type of the input vector.
     *  @tparam     U  The data type of the transformation angle.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  alpha  Skew angle in radians.
     *  @returns    The transformed vector.
     */
    template<typename T, nct::Arithmetic U>
    static Vector3D<T> skewYX(const Vector3D<T>& u, const U& alpha) noexcept;

    /**
     *  @brief      Skewing of vectors on Y-X.
     *  @details    This function applies the specified skewing along the y-axis that is obtained as 
     *              the x value increases.
     *  @tparam     T  The data type of the input vectors.
     *  @tparam     U  The data type of the transformation angle.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  alpha  Rotation angle in radians.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T, nct::Arithmetic U>
    static Array<Vector3D<T>> skewYX(const Array<Vector3D<T>>& u, const U& alpha);

    /**
     *  @brief      Vector skewing on X-Z.
     *  @details    This function applies the specified skewing along the x-axis that is obtained as 
     *              the z value increases.
     *  @tparam     T  The data type of the input vector.
     *  @tparam     U  The data type of the transformation angle.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  alpha  Skew angle in radians.
     *  @returns    The transformed vector.
     */
    template<typename T, nct::Arithmetic U>
    static Vector3D<T> skewXZ(const Vector3D<T>& u, const U& alpha) noexcept;

    /**
     *  @brief      Skewing of vectors on X-Z.
     *  @details    This function applies the specified skewing along the x-axis that is obtained as 
     *              the z value increases.
     *  @tparam     T  The data type of the input vectors.
     *  @tparam     U  The data type of the transformation angle.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  alpha  Rotation angle in radians.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T, nct::Arithmetic U>
    static Array<Vector3D<T>> skewXZ(const Array<Vector3D<T>>& u, const U& alpha);

    /**
     *  @brief      Vector skewing on Z-X.
     *  @details    This function applies the specified skewing along the z-axis that is obtained as 
     *              the x value increases.
     *  @tparam     T  The data type of the input vector.
     *  @tparam     U  The data type of the transformation angle.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  alpha  Skew angle in radians.
     *  @returns    The transformed vector.
     */
    template<typename T, nct::Arithmetic U>
    static Vector3D<T> skewZX(const Vector3D<T>& u, const U& alpha) noexcept;

    /**
     *  @brief      Skewing of vectors on Z-X.
     *  @details    This function applies the specified skewing along the z-axis that is obtained as 
     *              the x value increases.
     *  @tparam     T  The data type of the input vectors.
     *  @tparam     U  The data type of the transformation angle.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  alpha  Rotation angle in radians.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T, nct::Arithmetic U>
    static Array<Vector3D<T>> skewZX(const Array<Vector3D<T>>& u, const U& alpha);

    /**
     *  @brief      Vector skewing on Y-Z.
     *  @details    This function applies the specified skewing along the y-axis that is obtained as the 
     *              z value increases.
     *  @tparam     T  The data type of the input vector.
     *  @tparam     U  The data type of the transformation angle.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  alpha  Skew angle in radians.
     *  @returns    The transformed vector.
     */
    template<typename T, nct::Arithmetic U>
    static Vector3D<T> skewYZ(const Vector3D<T>& u, const U& alpha) noexcept;

    /**
     *  @brief      Skewing of vectors on Y-Z.
     *  @details    This function applies the specified skewing along the y-axis that is obtained as the 
     *              z value increases.
     *  @tparam     T  The data type of the input vectors.
     *  @tparam     U  The data type of the transformation angle.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  alpha  Rotation angle in radians.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T, nct::Arithmetic U>
    static Array<Vector3D<T>> skewYZ(const Array<Vector3D<T>>& u, const U& alpha);

    /**
     *  @brief      Vector skewing on Z-Y.
     *  @details    This function applies the specified skewing along the z-axis that is obtained as the 
     *              y value increases.
     *  @tparam     T  The data type of the input vector.
     *  @tparam     U  The data type of the transformation angle.
     *  @param[in]  u  Vector to be transformed.
     *  @param[in]  alpha  Skew angle in radians.
     *  @returns    The transformed vector.
     */
    template<typename T, nct::Arithmetic U>
    static Vector3D<T> skewZY(const Vector3D<T>& u, const U& alpha) noexcept;

    /**
     *  @brief      Skewing of vectors on Z-Y.
     *  @details    This function applies the specified skewing along the z-axis that is obtained as the 
     *              y value increases.
     *  @tparam     T  The data type of the input vectors.
     *  @tparam     U  The data type of the transformation angle.
     *  @param[in]  u  Vectors to be transformed.
     *  @param[in]  alpha  Rotation angle in radians.
     *  @returns    An array with the transformed vectors.
     */
    template<typename T, nct::Arithmetic U>
    static Array<Vector3D<T>> skewZY(const Array<Vector3D<T>>& u, const U& alpha);

private:

    ////////// Data members //////////

    /** Transformation matrix M(m00, m01, m02, m03; m10, m11, m12, m13; m20, m21, m22, m23). */
    double m_[3][4] = { {1.0, 0.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}, {0.0, 0.0, 1.0, 0.0} };

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
NCT_EXPIMP std::istream& operator>>(std::istream& i, geometry::AffineTransformation3D& tm);

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
    const geometry::AffineTransformation3D& tm);

/**
 *  @brief      Scalar product.
 *  @details    This operator calculates the product of the transformation matrix with a scalar.
 *  @param[in]  left  Scalar value.
 *  @param[in]  right  Matrix to multiply.
 *  @returns    The result of the operation.
 */
NCT_EXPIMP geometry::AffineTransformation3D operator*(double val,
    const geometry::AffineTransformation3D& tm) noexcept;

}}

////////// Implementation of method templates //////////
#include <nct/geometry/AffineTransformation3D_template.h>

#endif
//=================================================================================================================
//        END OF FILE
//=================================================================================================================
