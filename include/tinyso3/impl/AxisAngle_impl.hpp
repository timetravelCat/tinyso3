/**
 * @file AxisAngle_impl.hpp
 * 
 * An AxisAngle class for 3D rotations.
 * Represents a 3D rotation with an axis and an angle.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

template<typename Type>
template<typename Convention>
AxisAngle<Type>::AxisAngle(const RotationMatrix<Convention, Type>& dcm) {
    const Type theta = acos(clamp((dcm.trace() - Type(1)) / Type(2), Type(-1), Type(1)));
    if(theta < epsilon<Type>()) {
        (*this) = Vector3<Type>{Type(0), Type(0), Type(0)};
        return;
    }

    if(is_same<Convention, ACTIVE>::value) {
        (*this) = (theta / (Type(2) * sin(theta)) * (dcm - dcm.T())).vee();
    } else {
        (*this) = (theta / (Type(2) * sin(theta)) * (dcm.T() - dcm)).vee();
    }
};

template<typename Type>
template<typename EulerConvention, typename EulerSequence>
AxisAngle<Type>::AxisAngle(const Euler<EulerConvention, EulerSequence, Type>& euler) :
AxisAngle(RotationMatrix<ACTIVE, Type>{euler}){};

template<typename Type>
template<typename QuaternionConvention>
AxisAngle<Type>::AxisAngle(const Quaternion<QuaternionConvention, Type>& quaternion) {
    const Type angle = Type(2) * acos(quaternion.w());

    if(fabs(Type(1) - quaternion.w() * quaternion.w()) < epsilon<Type>()) {
        (*this) = Vector3<Type>{Type(0), Type(0), Type(0)};
    } else {
        const Type acos2 = sqrt(Type(1) - quaternion.w() * quaternion.w());
        if(is_same<QuaternionConvention, HAMILTON>::value) {
            (*this) = Vector3<Type>{quaternion.x(), quaternion.y(), quaternion.z()} / acos2 * angle;
        } else if(is_same<QuaternionConvention, JPL>::value) {
            (*this) = Vector3<Type>{-quaternion.x(), -quaternion.y(), -quaternion.z()} / acos2 * angle;
        }
    }
}

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
