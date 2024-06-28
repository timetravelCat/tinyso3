/**
 * @file EulerRate.hpp
 * 
 * An EulerRate class for 3D euler rates.
 * Supports conversion between euler rates and angular velocities.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

#include "Vector3.hpp"
#include "RotationMatrix.hpp"
#include "Euler.hpp"

namespace tinyso3 {
template<typename Type>
class AngularVelocity;

template<typename EulerSequence = TINYSO3_DEFAULT_EULER_ANGLE_SEQUENCE, typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
class EulerRate : public Vector3<Type> {
    static_assert(is_euler_sequence<EulerSequence>::value, "EulerSequence must be one of the EulerSequence types.");

protected:
    using Vector3<Type>::data;

public:
    /**
     * Constructors
     */
    using Vector3<Type>::Vector3;

    template<typename Convention>
    EulerRate(const RotationMatrix<Convention, Type> dcm, const AngularVelocity<Type>& angular_velocity);
};

template<typename EulerSequence, typename Type>
template<typename Convention>
EulerRate<EulerSequence, Type>::EulerRate(const RotationMatrix<Convention, Type> dcm, const AngularVelocity<Type>& angular_velocity) {
    const Euler<EulerSequence, Type> euler{dcm};

    const RotationMatrix<PASSIVE, Type> principal_3 =
      RotationMatrix<PASSIVE, Type>::template RotatePrincipalAxis<integral_constant<PrincipalAxis, EulerSequence::Axis3>>(euler(2));
    const RotationMatrix<PASSIVE, Type> principal_2 =
      RotationMatrix<PASSIVE, Type>::template RotatePrincipalAxis<integral_constant<PrincipalAxis, EulerSequence::Axis2>>(euler(1));

    SquareMatrix<3, Type> temp{};
    temp.template setCol<0>((principal_3 * principal_2).template col<0>());
    temp.template setCol<1>(principal_3.template col<1>());
    temp.template setCol<2>(Matrix<3, 1, Type>{Type(0), Type(0), Type(1)});

    // Implement slightly optimized inverse,
    // [a b 0] ^ (-1)  [d/(ad-bc)       b/(bc-ad)       0 ]
    // [c d 0]       = [c/(bc-ad)       a/(ad-bc)       0 ]
    // [e f 1]         [(de-cf)/(bc-ad) (be-af)/(ad-bc) 1 ]
    [](SquareMatrix<3, Type>& matrix) {
        const Type a = matrix(0, 0);
        const Type b = matrix(0, 1);
        const Type c = matrix(1, 0);
        const Type d = matrix(1, 1);
        const Type e = matrix(2, 0);
        const Type f = matrix(2, 1);

        const Type ad_bc = a * d - b * c;
        const Type bc_ad = b * c - a * d;
        matrix(0, 0) = d / ad_bc;
        matrix(0, 1) = b / bc_ad;
        matrix(1, 0) = c / bc_ad;
        matrix(1, 1) = a / ad_bc;
        matrix(2, 0) = (d * e - c * f) / bc_ad;
        matrix(2, 1) = (b * e - a * f) / ad_bc;
    }(temp);

    (*this) = temp * angular_velocity;
}
} // namespace tinyso3
