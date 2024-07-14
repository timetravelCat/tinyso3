/**
 * @file EulerRate.hpp
 * 
 * An EulerRate class for 3D euler rates.
 * Supports conversion between euler rates and angular velocities.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

#include "RotationMatrix.hpp"
#include "Euler.hpp"

namespace tinyso3 {
template<typename Type>
class AngularVelocity;

template<typename EulerConvention = TINYSO3_DEFAULT_EULER_ANGLE_CONVENTION, typename EulerSequence = TINYSO3_DEFAULT_EULER_ANGLE_SEQUENCE, typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
class EulerRate : public Vector3<Type> {
    static_assert(is_euler_convention<EulerConvention>::value, "EulerConvention must be one of the EulerConvention types.");
    static_assert(is_euler_sequence<EulerSequence>::value, "EulerSequence must be one of the EulerSequence types.");

protected:
    using Vector3<Type>::data;

public:
    /**
     * Constructors
     */
    using Vector3<Type>::Vector3;

    template<typename RotationMatrixConvention>
    EulerRate(const RotationMatrix<RotationMatrixConvention, Type>& dcm, const AngularVelocity<Type>& angular_velocity);
};

#include "impl/EulerRate_impl.hpp"
} // namespace tinyso3
