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
#include "RotationMatrix.hpp"
#include "Euler.hpp"
#include "epsilon.hpp"

namespace tinyso3 {
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
    template<typename EulerSequence>
    AxisAngle(const Euler<EulerSequence, Type>& euler);
    AxisAngle(const Vector3<Type>& axis_angle);
    AxisAngle(const Vector3<Type>& axis, const Type& angle);

    /**
     * AxisAngle Group Operations
     */
    using Vector3<Type>::operator*;
    inline AxisAngle operator*(Type scalar) const { return Vector3<Type>::operator*(scalar); };
    using Vector3<Type>::operator/;
    inline Vector3<Type> operator/(Type scalar) const { return Vector3<Type>::operator/(scalar); };
    inline AxisAngle operator-() const { return Vector3<Type>::operator-(); };
    inline friend AxisAngle operator*(Type lhs, const AxisAngle& rhs) { return rhs * lhs; };

    /**
     * Axis(Unit) and Angle
     */
    inline const Vector3<Type> axis() const;
    inline const Type angle() const;
};

template<typename Type>
template<typename Convention>
AxisAngle<Type>::AxisAngle(const RotationMatrix<Convention, Type>& dcm) {
    const Type theta = ::acos(constrain((dcm.trace() - Type(1)) / Type(2), Type(-1), Type(1)));
    if(theta < epsilon<Type>()) {
        (*this) = Vector3<Type>{Type(0), Type(0), Type(0)};
        return;
    }

    if(is_same<Convention, ACTIVE>::value) {
        (*this) = (theta / (Type(2) * ::sin(theta)) * (dcm - dcm.T())).vee();
    } else {
        (*this) = (theta / (Type(2) * ::sin(theta)) * (dcm.T() - dcm)).vee();
    }
};

template<typename Type>
template<typename EulerSequence>
AxisAngle<Type>::AxisAngle(const Euler<EulerSequence, Type>& euler) :
AxisAngle(RotationMatrix<ACTIVE, Type>{euler}){};

template<typename Type>
AxisAngle<Type>::AxisAngle(const Vector3<Type>& axis_angle) :
Vector3<Type>(axis_angle){};

template<typename Type>
AxisAngle<Type>::AxisAngle(const Vector3<Type>& axis, const Type& angle) :
Vector3<Type>(angle * axis) {}

template<typename Type>
const Vector3<Type> AxisAngle<Type>::axis() const {
    if(angle() < epsilon<Type>()) {
        return Vector3<Type>{Type(0), Type(0), Type(0)};
    }

    return Vector3<Type>::unit();
};

template<typename Type>
const Type AxisAngle<Type>::angle() const {
    return Vector3<Type>::norm();
};

}; // namespace tinyso3
