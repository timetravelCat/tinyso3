/**
 * @file AngularVelocity.hpp
 * 
 * An AngularVelocity class for 3D euler rates.
 * Angular Velocity represents the rate of change of the orientation, 
 * measuring from the reference frame, but expressed in the body frame.
 * Supports conversion between euler rates and angular velocities.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

#include "Vector3.hpp"
#include "RotationMatrix.hpp"
#include "Euler.hpp"

namespace tinyso3 {

template<typename EulerSequence, typename Type>
class EulerRate;

template<typename Type>
class AngularVelocity : public Vector3<Type> {
protected:
    using Vector3<Type>::data;

public:
    /**
     * Constructors
     */
    using Vector3<Type>::Vector3;

    template<typename EulerSequence>
    AngularVelocity(const Euler<EulerSequence, Type> euler, const EulerRate<EulerSequence, Type>& euler_rate);
};

template<typename Type>
template<typename EulerSequence>
AngularVelocity<Type>::AngularVelocity(const Euler<EulerSequence, Type> euler, const EulerRate<EulerSequence, Type>& euler_rate) {
    const RotationMatrix<PASSIVE, Type> principal_3 =
      RotationMatrix<PASSIVE, Type>::template RotatePrincipalAxis<integral_constant<PrincipalAxis, EulerSequence::Axis3>>(euler(2));
    const RotationMatrix<PASSIVE, Type> principal_2 =
      RotationMatrix<PASSIVE, Type>::template RotatePrincipalAxis<integral_constant<PrincipalAxis, EulerSequence::Axis2>>(euler(1));

    SquareMatrix<3, Type> temp{};
    temp.template setCol<0>((principal_3 * principal_2).template col<0>());
    temp.template setCol<1>(principal_3.template col<1>());
    temp.template setCol<2>(Matrix<3, 1, Type>{Type(0), Type(0), Type(1)});
    (*this) = temp * euler_rate;
}
} // namespace tinyso3