/**
 * @file RotationMatrix.hpp
 * 
 * A template based minimal 3x3 rotation matrix.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

#include "tiny_type_traits.hpp"
#include "SquareMatrix.hpp"
#include "Vector3.hpp"

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
struct is_integral_constant_of_principal_rotation_axis : false_type {};
template<>
struct is_integral_constant_of_principal_rotation_axis<X> : true_type {};
template<>
struct is_integral_constant_of_principal_rotation_axis<Y> : true_type {};
template<>
struct is_integral_constant_of_principal_rotation_axis<Z> : true_type {};

enum class RotationMatrixTransformConvention {
    ACTIVE,
    PASSIVE
};

using ACTIVE = integral_constant<RotationMatrixTransformConvention, RotationMatrixTransformConvention::ACTIVE>;
using PASSIVE = integral_constant<RotationMatrixTransformConvention, RotationMatrixTransformConvention::PASSIVE>;
using ALIBI = ACTIVE;
using ALIAS = PASSIVE;

template<typename T>
struct is_integral_constant_of_rotation_matrix_transform_convention : false_type {};
template<>
struct is_integral_constant_of_rotation_matrix_transform_convention<ACTIVE> : true_type {};
template<>
struct is_integral_constant_of_rotation_matrix_transform_convention<PASSIVE> : true_type {};

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
     * Principal Rotations
     */
    template<typename Axis,
             typename T = TINYSO3_DEFAULT_ROTATION_MATRIX_TRANSFORMATION_CONVENTION,
             enable_if_t<(is_integral_constant_of_principal_rotation_axis<Axis>::value &&
                          is_integral_constant_of_rotation_matrix_transform_convention<T>::value),
                         int> = 0>
    static RotationMatrix<Type> RotatePrincipalAxis(const Type& angle);

    /**
     * (R*R^T)^(-1/2)*R
     * State Estimation For Robotics 257page
     * https://www.quora.com/How-can-you-find-the-square-root-of-3-3-matrix
     * https://github.com/rounakdatta/mat-ops/blob/master/eigenvector.cpp
     * https://stackoverflow.com/questions/13328676/c-solving-cubic-equations
     * https://cplusplus.com/forum/beginner/234717/
     * 
     * 1/sqrt(r1) * e e^T + 1/sqrt(r2) * f f^T + 1/sqrt(r3) * g g^T
     */
    void normalize();
};

template<typename Type>
RotationMatrix<Type>::RotationMatrix(const SquareMatrix<3, Type>& other) :
SquareMatrix<3, Type>(other) {}

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
void RotationMatrix<Type>::normalize() {
    // WIP
}

}; // namespace tinyso3