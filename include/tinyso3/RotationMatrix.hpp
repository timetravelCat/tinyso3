/**
 * @file RotationMatrix.hpp
 * 
 * A template based minimal 3x3 rotation matrix.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

#include "version.hpp"
#include "tiny_epsilon.hpp"
#include "EigenSolver.hpp"

namespace tinyso3 {
template<typename EulerConvention, typename EulerSequence, typename Type>
class Euler;
template<typename Type>
class AxisAngle;
template<typename QuaternionConvention, typename Type>
class Quaternion;

template<typename RotationMatrixConvention = TINYSO3_DEFAULT_ROTATION_MATRIX_CONVENTION,
         typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
class RotationMatrix : public SquareMatrix<3, Type> {
protected:
    static_assert(is_rotation_matrix_convention<RotationMatrixConvention>::value,
                  "RotationMatrixConvention must be PASSIVE(ALIAS) or ACTIVE(ALIBI).");
    using SquareMatrix<3, Type>::data;

public:
    using Convention = RotationMatrixConvention;
    using QuaternionAlias = conditional_t<is_same<RotationMatrixConvention, ACTIVE>::value, Quaternion<HAMILTON, Type>, Quaternion<JPL, Type>>;

    /**
     * Constructors
     */
    using SquareMatrix<3, Type>::SquareMatrix;

    RotationMatrix();
    RotationMatrix(const SquareMatrix<3, Type>& other);
    template<typename EulerConvention, typename EulerSequence>
    RotationMatrix(const Euler<EulerConvention, EulerSequence, Type>& euler);
    RotationMatrix(const AxisAngle<Type>& axis_angle);
    RotationMatrix(const QuaternionAlias& quaternion);

    /**
     * SO3 Group Operations
     */
    using SquareMatrix<3, Type>::operator*;
    inline RotationMatrix operator*(const RotationMatrix& other) const { return SquareMatrix<3, Type>::operator*(other); }
    inline void operator*=(const RotationMatrix& other) { SquareMatrix<3, Type>::operator*=(other); }
    using SquareMatrix<3, Type>::transpose;
    inline RotationMatrix transpose() const { return SquareMatrix<3, Type>::transpose(); }
    using SquareMatrix<3, Type>::T;
    inline RotationMatrix T() const { return SquareMatrix<3, Type>::transpose(); }
    using SquareMatrix<3, Type>::inverse;
    inline RotationMatrix inverse() const { return SquareMatrix<3, Type>::transpose(); }

    /**
     * Static Methods
     */
    static inline RotationMatrix Identity() { return SquareMatrix<3, Type>::Identity(); }
    template<typename Axis, enable_if_t<(is_principal_axis<Axis>::value), int> = 0>
    static RotationMatrix RotatePrincipalAxis(const Type& angle);
    static RotationMatrix Exp(const SquareMatrix<3, Type>& exp);

    /**
     * Normalizes the rotation matrix.
     * 
     * Calculates (R*R^T)^(-1/2)*R
     * R*R^T is a symmetric matrix.
     * for symmetric matrix, A^(-1/2) is 1/sqrt(r1) * e e^T + 1/sqrt(r2) * f f^T + 1/sqrt(r3) * g g^T
     * https://www.quora.com/How-can-you-find-the-square-root-of-3-3-matrix
     * Fast analytic solution calculating eigen value and eigen vector implemented in EigenSolver.hpp
     * https://www.geometrictools.com/Documentation/RobustEigenSymmetric3x3.pdf
     * 
     * As a result, return matrix satisfy orthonormality and finds the closest to the original matrix.
     * See "State Estimation for Robotics - Timothy D. Barfoot - 2017 - p. 257"
     */
    void normalize();

    /**
     * Returns the logarithm of the rotation matrix.
     */
    SquareMatrix<3, Type> log() const;

    /**
     * Returns the power of the rotation matrix.
     */
    RotationMatrix pow(const Type& t) const;

    /**
     * Interpolates between two rotation matrices.
     * 
     * ACTIVE : R = R1 * (R1^(T) * R2)^t
     * PASSIVE : R = (R2 * R1^(T))^t * R1
     */
    RotationMatrix interpolate(const RotationMatrix& to, const Type& t) const;

    using SquareMatrix<3, Type>::Identity;
    using SquareMatrix<3, Type>::Null;
};

template<typename RotationMatrixConvention = TINYSO3_DEFAULT_ROTATION_MATRIX_CONVENTION, typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
using DirectionCosineMatrix = RotationMatrix<RotationMatrixConvention, Type>;
template<typename RotationMatrixConvention = TINYSO3_DEFAULT_ROTATION_MATRIX_CONVENTION, typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
using DCM = DirectionCosineMatrix<RotationMatrixConvention, Type>;

template<typename RotationMatrixConvention = TINYSO3_DEFAULT_ROTATION_MATRIX_CONVENTION>
using RotationMatrixf = RotationMatrix<RotationMatrixConvention, float>;
template<typename RotationMatrixConvention = TINYSO3_DEFAULT_ROTATION_MATRIX_CONVENTION>
using RotationMatrixd = RotationMatrix<RotationMatrixConvention, double>;
template<typename RotationMatrixConvention = TINYSO3_DEFAULT_ROTATION_MATRIX_CONVENTION>
using RotationMatrixld = RotationMatrix<RotationMatrixConvention, long double>;

template<typename RotationMatrixConvention = TINYSO3_DEFAULT_ROTATION_MATRIX_CONVENTION>
using DirectionCosineMatrixf = DirectionCosineMatrix<RotationMatrixConvention, float>;
template<typename RotationMatrixConvention = TINYSO3_DEFAULT_ROTATION_MATRIX_CONVENTION>
using DirectionCosineMatrixd = DirectionCosineMatrix<RotationMatrixConvention, double>;
template<typename RotationMatrixConvention = TINYSO3_DEFAULT_ROTATION_MATRIX_CONVENTION>
using DirectionCosineMatrixld = DirectionCosineMatrix<RotationMatrixConvention, long double>;

template<typename RotationMatrixConvention = TINYSO3_DEFAULT_ROTATION_MATRIX_CONVENTION>
using DCMf = DCM<RotationMatrixConvention, float>;
template<typename RotationMatrixConvention = TINYSO3_DEFAULT_ROTATION_MATRIX_CONVENTION>
using DCMd = DCM<RotationMatrixConvention, double>;
template<typename RotationMatrixConvention = TINYSO3_DEFAULT_ROTATION_MATRIX_CONVENTION>
using DCMld = DCM<RotationMatrixConvention, long double>;

#include "impl/RotationMatrix_impl.hpp"
}; // namespace tinyso3