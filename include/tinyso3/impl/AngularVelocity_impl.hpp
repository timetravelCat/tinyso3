/**
 * @file AngularVelocity_impl.hpp
 * 
 * An AngularVelocity class for 3D euler rates.
 * Angular Velocity represents the rate of change of the orientation, 
 * measuring from the reference frame, but expressed in the body frame.
 * Supports conversion between euler rates and angular velocities.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */
#pragma once

template<typename Type>
template<typename EulerConvention, typename EulerSequence>
AngularVelocity<Type>::AngularVelocity(const Euler<EulerConvention, EulerSequence, Type>& euler, const EulerRate<EulerConvention, EulerSequence, Type>& euler_rate) {
    if(is_same<EulerConvention, INTRINSIC>::value) {
        const RotationMatrix<PASSIVE, Type> principal_3 =
          RotationMatrix<PASSIVE, Type>::template RotatePrincipalAxis<integral_constant<PrincipalAxis, EulerSequence::Axis3>>(euler(2));
        const RotationMatrix<PASSIVE, Type> principal_2 =
          RotationMatrix<PASSIVE, Type>::template RotatePrincipalAxis<integral_constant<PrincipalAxis, EulerSequence::Axis2>>(euler(1));

        SquareMatrix<3, Type> temp{};
        temp.template setCol<0>((principal_3 * principal_2).template col<0>());
        temp.template setCol<1>(principal_3.template col<1>());
        temp.template setCol<2>(Matrix<3, 1, Type>{Type(0), Type(0), Type(1)});
        (*this) = temp * euler_rate;
    } else if(is_same<EulerConvention, EXTRINSIC>::value) {
        const RotationMatrix<PASSIVE, Type> principal_1 =
          RotationMatrix<PASSIVE, Type>::template RotatePrincipalAxis<integral_constant<PrincipalAxis, EulerSequence::Axis1>>(euler(0));
        const RotationMatrix<PASSIVE, Type> principal_2 =
          RotationMatrix<PASSIVE, Type>::template RotatePrincipalAxis<integral_constant<PrincipalAxis, EulerSequence::Axis2>>(euler(1));

        SquareMatrix<3, Type> temp{};
        temp.template setCol<0>(Matrix<3, 1, Type>{Type(1), Type(0), Type(0)});
        temp.template setCol<1>(principal_1.template col<1>());
        temp.template setCol<2>((principal_1 * principal_2).template col<2>());
        (*this) = temp * euler_rate;
    }
}