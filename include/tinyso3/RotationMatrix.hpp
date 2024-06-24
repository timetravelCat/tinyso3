/**
 * @file RotationMatrix.hpp
 * 
 * A template based minimal 3x3 rotation matrix.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */
#pragma once

#include "version.hpp"
#include "tiny_type_traits.hpp"
#include "tiny_utility.hpp"
#include "epsilon.hpp"
#include "EigenSolver.hpp"

namespace tinyso3 {

enum class PrincipalAxis {
    X,
    Y,
    Z
};

using X = integral_constant<PrincipalAxis, PrincipalAxis::X>;
using Y = integral_constant<PrincipalAxis, PrincipalAxis::Y>;
using Z = integral_constant<PrincipalAxis, PrincipalAxis::Z>;

template<typename T>
struct is_integral_constant_of_principal_rotation_axis;

enum class RotationMatrixTransformConvention {
    ACTIVE,
    PASSIVE
};

using ACTIVE = integral_constant<RotationMatrixTransformConvention, RotationMatrixTransformConvention::ACTIVE>;
using PASSIVE = integral_constant<RotationMatrixTransformConvention, RotationMatrixTransformConvention::PASSIVE>;

template<typename T>
struct is_integral_constant_of_rotation_matrix_transform_convention;

template<typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
class RotationMatrix : public SquareMatrix<3, Type> {
protected:
    using SquareMatrix<3, Type>::data;

public:
    /**
     * Constructors
     */
    using SquareMatrix<3, Type>::SquareMatrix;

    RotationMatrix(const SquareMatrix<3, Type>& other);

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

    static inline RotationMatrix Identity() { return SquareMatrix<3, Type>::Identity(); }

    /**
     * Principal Rotations
     */
    template<typename Axis,
             typename T = TINYSO3_DEFAULT_ROTATION_MATRIX_TRANSFORMATION_CONVENTION,
             enable_if_t<(is_integral_constant_of_principal_rotation_axis<Axis>::value &&
                          is_integral_constant_of_rotation_matrix_transform_convention<T>::value),
                         int> = 0>
    static RotationMatrix<Type> RotatePrincipalAxis(const Type& angle);

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
    template<typename T = TINYSO3_DEFAULT_ROTATION_MATRIX_TRANSFORMATION_CONVENTION>
    RotationMatrix interpolate(const RotationMatrix& to, const Type& t) const;

    using SquareMatrix<3, Type>::Identity;
    using SquareMatrix<3, Type>::Null;
};

template<typename Type>
RotationMatrix<Type>::RotationMatrix(const SquareMatrix<3, Type>& other) :
SquareMatrix<3, Type>(other) {
}

template<typename Type>
template<typename Axis,
         typename T,
         enable_if_t<(is_integral_constant_of_principal_rotation_axis<Axis>::value &&
                      is_integral_constant_of_rotation_matrix_transform_convention<T>::value),
                     int>>
RotationMatrix<Type> RotationMatrix<Type>::RotatePrincipalAxis(const Type& angle) {
    if(is_same<T, ACTIVE>::value) {
        if(is_same<Axis, X>::value) {
            return RotationMatrix<Type>{Type(1), Type(0), Type(0), Type(0), ::cos(angle), -::sin(angle), Type(0), ::sin(angle), ::cos(angle)};
        } else if(is_same<Axis, Y>::value) {
            return RotationMatrix<Type>{::cos(angle), Type(0), ::sin(angle), Type(0), Type(1), Type(0), -::sin(angle), Type(0), ::cos(angle)};
        } else if(is_same<Axis, Z>::value) {
            return RotationMatrix<Type>{::cos(angle), -::sin(angle), Type(0), ::sin(angle), ::cos(angle), Type(0), Type(0), Type(0), Type(1)};
        }
    } else if(is_same<T, PASSIVE>::value) {
        if(is_same<Axis, X>::value) {
            return RotationMatrix<Type>{Type(1), Type(0), Type(0), Type(0), ::cos(angle), ::sin(angle), Type(0), -::sin(angle), ::cos(angle)};
        } else if(is_same<Axis, Y>::value) {
            return RotationMatrix<Type>{::cos(angle), Type(0), -::sin(angle), Type(0), Type(1), Type(0), ::sin(angle), Type(0), ::cos(angle)};
        } else if(is_same<Axis, Z>::value) {
            return RotationMatrix<Type>{::cos(angle), ::sin(angle), Type(0), -::sin(angle), ::cos(angle), Type(0), Type(0), Type(0), Type(1)};
        }
    }

    // Can not reach here, just for suppressing warning.
    return RotationMatrix<Type>{};
}

template<typename Type>
SquareMatrix<3, Type> RotationMatrix<Type>::log() const {
    const Type theta = ::acos(constrain((this->trace() - Type(1)) / Type(2), Type(-1), Type(1)));
    return theta < epsilon<Type>() ? Null() : theta / (Type(2) * ::sin(theta)) * (*this - this->T());
}

template<typename Type>
RotationMatrix<Type> RotationMatrix<Type>::pow(const Type& t) const {
    Vector3<Type> a = t * this->log().vee();
    const Type theta = a.norm();

    if(theta < epsilon<Type>()) {
        return Identity();
    }

    a /= theta;

    const Type c = ::cos(theta);
    const Type s = ::sin(theta);

    return c * Identity() + (Type(1) - c) * a * a.T() + s * a.hat();
}

template<typename Type>
template<typename T>
RotationMatrix<Type> RotationMatrix<Type>::interpolate(const RotationMatrix& to, const Type& t) const {
    const RotationMatrix<Type>& from = *this;

    if(is_same<T, ACTIVE>::value) {
        return from * (from.T() * to).pow(t);
    } else if(is_same<T, PASSIVE>::value) {
        return (to * from.T()).pow(t) * from;
    }

    // Can not reach here, just for suppressing warning.
    return RotationMatrix<Type>{};
}

template<typename Type>
void RotationMatrix<Type>::normalize() {
    // Get eigenvalues & eigenvectors of R*R^T
    const SquareMatrix<3, Type> RRt = (*this) * (this->T());
    const array<EigenPair<Type>, 3> eigenpairs = EigenSolver<Type>{}(RRt);

    (*this) = (Type(1) / ::sqrt(::fabs(eigenpairs[0].first)) * (eigenpairs[0].second * eigenpairs[0].second.transpose()) +
               Type(1) / ::sqrt(::fabs(eigenpairs[1].first)) * (eigenpairs[1].second * eigenpairs[1].second.transpose()) +
               Type(1) / ::sqrt(::fabs(eigenpairs[2].first)) * (eigenpairs[2].second * eigenpairs[2].second.transpose())) *
              (*this);
}

template<typename T>
struct is_integral_constant_of_principal_rotation_axis : false_type {
};
template<>
struct is_integral_constant_of_principal_rotation_axis<X> : true_type {
};
template<>
struct is_integral_constant_of_principal_rotation_axis<Y> : true_type {
};
template<>
struct is_integral_constant_of_principal_rotation_axis<Z> : true_type {
};

template<typename T>
struct is_integral_constant_of_rotation_matrix_transform_convention : false_type {
};
template<>
struct is_integral_constant_of_rotation_matrix_transform_convention<ACTIVE> : true_type {
};
template<>
struct is_integral_constant_of_rotation_matrix_transform_convention<PASSIVE> : true_type {
};

using ALIBI = ACTIVE;
using ALIAS = PASSIVE;

template<typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
using DirectionCosineMatrix = RotationMatrix<Type>;
template<typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
using DCM = DirectionCosineMatrix<Type>;

}; // namespace tinyso3