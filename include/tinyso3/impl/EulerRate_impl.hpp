/**
 * @file EulerRate_impl.hpp
 * 
 * An EulerRate class for 3D euler rates.
 * Supports conversion between euler rates and angular velocities.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

template<typename EulerConvention, typename EulerSequence, typename Type>
template<typename RotationMatrixConvention>
EulerRate<EulerConvention, EulerSequence, Type>::EulerRate(const RotationMatrix<RotationMatrixConvention, Type>& dcm, const AngularVelocity<Type>& angular_velocity) {
    const Euler<EulerConvention, EulerSequence, Type> euler{dcm};

    if(is_same<EulerConvention, INTRINSIC>::value) {
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
    } else if(is_same<EulerConvention, EXTRINSIC>::value) {
        const RotationMatrix<PASSIVE, Type> principal_1 =
          RotationMatrix<PASSIVE, Type>::template RotatePrincipalAxis<integral_constant<PrincipalAxis, EulerSequence::Axis1>>(euler(0));
        const RotationMatrix<PASSIVE, Type> principal_2 =
          RotationMatrix<PASSIVE, Type>::template RotatePrincipalAxis<integral_constant<PrincipalAxis, EulerSequence::Axis2>>(euler(1));

        SquareMatrix<3, Type> temp{};
        temp.template setCol<0>(Matrix<3, 1, Type>{Type(1), Type(0), Type(0)});
        temp.template setCol<1>(principal_1.template col<1>());
        temp.template setCol<2>((principal_1 * principal_2).template col<2>());

        // Implement slightly optimized inverse,
        // [1 a b] ^ (-1)  [1 (be-af)/(cf-de) (bc-ad)/(de-cf)]
        // [0 c d]       = [0       f/(cf-de)       d/(de-cf)]
        // [0 e f]         [0       e/(de-cf)       c/(cf-de)]
        [](SquareMatrix<3, Type>& matrix) {
            const Type a = matrix(0, 1);
            const Type b = matrix(0, 2);
            const Type c = matrix(1, 1);
            const Type d = matrix(1, 2);
            const Type e = matrix(2, 1);
            const Type f = matrix(2, 2);

            const Type cf_de = c * f - d * e;
            const Type de_cf = d * e - c * f;
            matrix(0, 1) = (b * e - a * f) / cf_de;
            matrix(0, 2) = (b * c - a * d) / de_cf;
            matrix(1, 1) = f / cf_de;
            matrix(1, 2) = d / de_cf;
            matrix(2, 1) = e / de_cf;
            matrix(2, 2) = c / cf_de;
        }(temp);

        (*this) = temp * angular_velocity;
    }
}