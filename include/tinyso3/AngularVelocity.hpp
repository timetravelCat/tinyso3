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

#include "Euler.hpp"
#include "RotationMatrix.hpp"

namespace tinyso3 {

template<typename EulerConvention, typename EulerSequence, typename Type>
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

    template<typename EulerConvention, typename EulerSequence>
    AngularVelocity(const Euler<EulerConvention, EulerSequence, Type>& euler, const EulerRate<EulerConvention, EulerSequence, Type>& euler_rate);
};

using AngularVelocityf = AngularVelocity<float>;
using AngularVelocityd = AngularVelocity<double>;
using AngularVelocityld = AngularVelocity<long double>;

#include "impl/AngularVelocity_impl.hpp"
} // namespace tinyso3
