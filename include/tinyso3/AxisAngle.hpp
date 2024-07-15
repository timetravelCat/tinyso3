/**
 * @file AxisAngle.hpp
 * 
 * An AxisAngle class for 3D rotations.
 * Represents a 3D rotation with an axis and an angle.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

#include "Vector3.hpp"
#include "tiny_epsilon.hpp"

namespace tinyso3 {
template<typename RotationMatrixConvention, typename Type>
class RotationMatrix;
template<typename EulerConvention, typename EulerSequence, typename Type>
class Euler;
template<typename QuaternionConvention, typename Type>
class Quaternion;

/**
 * AxisAngle class
 * 
 * The body(local) frame is rotated by an angle about the axis from the world(global) frame.
 * Stores zero vector if the angle is zero.
 * 
 * Is case of passive rotation matrix, AxisAngle is not the log of the rotation matrix.
 */
template<typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
class AxisAngle : public Vector3<Type> {
protected:
    using Vector3<Type>::data;

public:
    /**
     * Constructors
     */
    using Vector3<Type>::Vector3;

    template<typename Convention>
    AxisAngle(const RotationMatrix<Convention, Type>& dcm);
    template<typename EulerConvention, typename EulerSequence>
    AxisAngle(const Euler<EulerConvention, EulerSequence, Type>& euler);
    template<typename QuaternionConvention>
    AxisAngle(const Quaternion<QuaternionConvention, Type>& quaternion);
    AxisAngle(const Vector3<Type>& axis_angle);
    AxisAngle(const Vector3<Type>& axis, const Type& angle);

    /**
     * AxisAngle Group Operations
     */
    inline AxisAngle operator*(Type scalar) const { return Vector3<Type>::operator*(scalar); };
    inline Vector3<Type> operator/(Type scalar) const { return Vector3<Type>::operator/(scalar); };
    inline AxisAngle operator-() const { return Vector3<Type>::operator-(); };
    inline friend AxisAngle operator*(Type lhs, const AxisAngle& rhs) { return rhs * lhs; };

    /**
     * Axis(Unit) and Angle
     */
    inline const Vector3<Type> axis() const;
    inline const Type angle() const;
};

using AxisAnglef = AxisAngle<float>;
using AxisAngled = AxisAngle<double>;
using AxisAngleld = AxisAngle<long double>;

#include "impl/AxisAngle_impl.hpp"
}; // namespace tinyso3
