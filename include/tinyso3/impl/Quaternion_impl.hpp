/**
 * @file Quaternion_impl.hpp
 * 
 * A template based quaternion
 * 
 * @author lightaxis <jisuk500@gmail.com>
 */

#pragma once

template<typename QuaternionConvention, typename Type>
template<typename Axis>
constexpr inline int Quaternion<QuaternionConvention, Type>::IDX() {
    static_assert(is_principal_axis<Axis>::value, "Axis must be one of the PrincipalAxis types.");
    return is_same<QuaternionConvention, HAMILTON>::value ? static_cast<int>(Axis::value) + 1 : static_cast<int>(Axis::value);
}

template<typename QuaternionConvention, typename Type>
Quaternion<QuaternionConvention, Type> Quaternion<QuaternionConvention, Type>::conjugate() const {
    return is_same<QuaternionConvention, HAMILTON>::value ?
             Quaternion{w(), -x(), -y(), -z()} :
             Quaternion{-x(), -y(), -z(), w()};
}

template<typename QuaternionConvention, typename Type>
Quaternion<QuaternionConvention, Type> Quaternion<QuaternionConvention, Type>::operator*(const Quaternion& other) const {
    return is_same<QuaternionConvention, HAMILTON>::value ?
             Quaternion<QuaternionConvention, Type>{
               other.w() * w() - other.x() * x() - other.y() * y() - other.z() * z(),
               other.w() * x() + other.x() * w() - other.y() * z() + other.z() * y(),
               other.w() * y() + other.x() * z() + other.y() * w() - other.z() * x(),
               other.w() * z() - other.x() * y() + other.y() * x() + other.z() * w()} :
             Quaternion<QuaternionConvention, Type>{
               other.w() * x() + other.x() * w() - other.y() * z() + other.z() * y(),
               other.w() * y() + other.x() * z() + other.y() * w() - other.z() * x(),
               other.w() * z() - other.x() * y() + other.y() * x() + other.z() * w(),
               other.w() * w() - other.x() * x() - other.y() * y() - other.z() * z()};
}

template<typename QuaternionConvention, typename Type>
Quaternion<QuaternionConvention, Type> Quaternion<QuaternionConvention, Type>::canonicalize() const {
    if(w() < Type(0)) {
        return is_same<QuaternionConvention, HAMILTON>::value ?
                 Quaternion{-w(), -x(), -y(), -z()} :
                 Quaternion{-x(), -y(), -z(), -w()};
    }

    return *this;
}

template<typename QuaternionConvention, typename Type>
Quaternion<QuaternionConvention, Type> Quaternion<QuaternionConvention, Type>::slerp(const Quaternion<QuaternionConvention, Type>& to, Type t) {
    if(is_same<QuaternionConvention, HAMILTON>::value) {
        return (to * this->conjugate()).pow(t) * (*this);
    } else if(is_same<QuaternionConvention, JPL>::value) {
        return (*this) * (this->conjugate() * to).pow(t);
    }

    return Quaternion<QuaternionConvention, Type>{}; // Cannot reach here, but to avoid warning
}

template<typename QuaternionConvention, typename Type>
template<typename Axis, enable_if_t<(is_principal_axis<Axis>::value), int>>
Quaternion<QuaternionConvention, Type> Quaternion<QuaternionConvention, Type>::RotatePrincipalAxis(const Type& angle) {
    Quaternion<QuaternionConvention, Type> q{};
    q.w() = cos(angle / Type(2));
    q.data[IDX<Axis>()][0] =
      is_same<QuaternionConvention, HAMILTON>::value ?
        sin(angle / Type(2)) :
        -sin(angle / Type(2));

    return q;
}

// ln(q) = ln|q| + v/|v| acos(w/|q|)
template<typename QuaternionConvention, typename Type>
Vector3<Type> Quaternion<QuaternionConvention, Type>::log() const {
    // assume unit quaternion

    const Type n = sqrt(x() * x() + y() * y() + z() * z());
    if(n < tinyso3::epsilon<Type>()) { // log(w+0) = ln(w)
        return Vector3<Type>{Type(0), Type(0), Type(0)};
    } else {
        Type scale = acos(w()) / n;
        return Vector3<Type>{x() * scale, y() * scale, z() * scale};
    }
}

template<typename QuaternionConvention, typename Type>
Quaternion<QuaternionConvention, Type> Quaternion<QuaternionConvention, Type>::Exp(const Vector3<Type>& vec3) {
    const Type angle = vec3.norm();
    if(angle < tinyso3::epsilon<Type>()) {
        return Quaternion<QuaternionConvention, Type>::Identity();
    }

    const Type scale = sin(angle) / angle;
    Quaternion<QuaternionConvention, Type> q;
    q.w() = cos(angle);
    q.x() = vec3.x() * scale;
    q.y() = vec3.y() * scale;
    q.z() = vec3.z() * scale;
    return q;
}

template<typename QuaternionConvention, typename Type>
Quaternion<QuaternionConvention, Type> Quaternion<QuaternionConvention, Type>::pow(Type t) const {
    return Quaternion<QuaternionConvention, Type>::Exp((log() * t));
}

template<typename QuaternionConvention, typename Type>
Vector3<Type> Quaternion<QuaternionConvention, Type>::operator*(const Vector3<Type>& other_vec) const {
    return ((*this) * Quaternion<QuaternionConvention, Type>{other_vec} * conjugate()).Im();
}

template<typename QuaternionConvention, typename Type>
Quaternion<QuaternionConvention, Type>::Quaternion() {
    w() = static_cast<Type>(1);
    x() = static_cast<Type>(0);
    y() = static_cast<Type>(0);
    z() = static_cast<Type>(0);
}

// w, x, y, z (Hamilton) or x y z w (JPL)
template<typename QuaternionConvention, typename Type>
Quaternion<QuaternionConvention, Type>::Quaternion(const Type arr[4]) {
    w() = arr[_W];
    x() = arr[_X];
    y() = arr[_Y];
    z() = arr[_Z];
}

template<typename QuaternionConvention, typename Type>
Quaternion<QuaternionConvention, Type>::Quaternion(const Vector<4, Type>& other) :
Quaternion<QuaternionConvention, Type>(other(0), other(1), other(2), other(3)) {}

template<typename QuaternionConvention, typename Type>
Quaternion<QuaternionConvention, Type>::Quaternion(Type q1, Type q2, Type q3, Type q4) {
    if(is_same<QuaternionConvention, HAMILTON>::value) {
        w() = q1;
        x() = q2;
        y() = q3;
        z() = q4;
    } else if(is_same<QuaternionConvention, JPL>::value) {
        x() = q1;
        y() = q2;
        z() = q3;
        w() = q4;
    }
}

template<typename QuaternionConvention, typename Type>
Quaternion<QuaternionConvention, Type>::Quaternion(Vector3<Type> xyz) {
    w() = static_cast<Type>(0);
    x() = xyz.x();
    y() = xyz.y();
    z() = xyz.z();
}

template<typename QuaternionConvention, typename Type>
template<typename Convention, enable_if_t<(is_same<Convention, HAMILTON>::value), int>>
Quaternion<QuaternionConvention, Type>::Quaternion(Type w, Vector3<Type> xyz) {
    this->w() = w;
    x() = xyz.x();
    y() = xyz.y();
    z() = xyz.z();
}

template<typename QuaternionConvention, typename Type>
template<typename Convention, enable_if_t<(is_same<Convention, JPL>::value), int>>
Quaternion<QuaternionConvention, Type>::Quaternion(Vector3<Type> xyz, Type w) {
    x() = xyz.x();
    y() = xyz.y();
    z() = xyz.z();
    this->w() = w;
}

template<typename QuaternionConvention, typename Type>
Quaternion<QuaternionConvention, Type>::Quaternion(const RotationMatrixAlias& dcm) {
    const Type tr = dcm.trace();
    if(tr > 0) {
        Type S = sqrt(tr + 1) * static_cast<Type>(2); // S=4*qw
        w() = static_cast<Type>(0.25) * S;
        x() = (dcm(2, 1) - dcm(1, 2)) / S;
        y() = (dcm(0, 2) - dcm(2, 0)) / S;
        z() = (dcm(1, 0) - dcm(0, 1)) / S;
    } else if((dcm(0, 0) > dcm(1, 1)) && (dcm(0, 0) > dcm(2, 2))) {
        Type S = sqrt(static_cast<Type>(1.0) + dcm(0, 0) - dcm(1, 1) - dcm(2, 2)) * static_cast<Type>(2); // S=4*qx
        w() = (dcm(2, 1) - dcm(1, 2)) / S;
        x() = static_cast<Type>(0.25) * S;
        y() = (dcm(0, 1) + dcm(1, 0)) / S;
        z() = (dcm(0, 2) + dcm(2, 0)) / S;
    } else if(dcm(1, 1) > dcm(2, 2)) {
        Type S = sqrt(static_cast<Type>(1.0) + dcm(1, 1) - dcm(0, 0) - dcm(2, 2)) * static_cast<Type>(2); // S=4*qy
        w() = (dcm(0, 2) - dcm(2, 0)) / S;
        x() = (dcm(0, 1) + dcm(1, 0)) / S;
        y() = static_cast<Type>(0.25) * S;
        z() = (dcm(1, 2) + dcm(2, 1)) / S;
    } else {
        Type S = sqrt(static_cast<Type>(1.0) + dcm(2, 2) - dcm(0, 0) - dcm(1, 1)) * static_cast<Type>(2); // S=4*qz
        w() = (dcm(1, 0) - dcm(0, 1)) / S;
        x() = (dcm(0, 2) + dcm(2, 0)) / S;
        y() = (dcm(1, 2) + dcm(2, 1)) / S;
        z() = static_cast<Type>(0.25) * S;
    }
}

template<typename QuaternionConvention, typename Type>
template<typename EulerConvention, typename EulerSequence>
Quaternion<QuaternionConvention, Type>::Quaternion(const Euler<EulerConvention, EulerSequence, Type>& euler) {
    const Quaternion<QuaternionConvention, Type> q1 = Quaternion<QuaternionConvention, Type>::RotatePrincipalAxis<integral_constant<PrincipalAxis, EulerSequence::Axis1>>(euler(0));
    const Quaternion<QuaternionConvention, Type> q2 = Quaternion<QuaternionConvention, Type>::RotatePrincipalAxis<integral_constant<PrincipalAxis, EulerSequence::Axis2>>(euler(1));
    const Quaternion<QuaternionConvention, Type> q3 = Quaternion<QuaternionConvention, Type>::RotatePrincipalAxis<integral_constant<PrincipalAxis, EulerSequence::Axis3>>(euler(2));

    if(is_same<EulerConvention, INTRINSIC>::value) {
        if(is_same<QuaternionConvention, HAMILTON>::value) {
            (*this) = q1 * q2 * q3;
        } else if(is_same<QuaternionConvention, JPL>::value) {
            (*this) = q3 * q2 * q1;
        }

    } else if(is_same<EulerConvention, EXTRINSIC>::value) {
        if(is_same<QuaternionConvention, HAMILTON>::value) {
            (*this) = q3 * q2 * q1;
        } else if(is_same<QuaternionConvention, JPL>::value) {
            (*this) = q1 * q2 * q3;
        }
    }
}

template<typename QuaternionConvention, typename Type>
Quaternion<QuaternionConvention, Type>::Quaternion(const AxisAngle<Type>& axis_angle) {
    if(is_same<QuaternionConvention, HAMILTON>::value) {
        const Type angle = axis_angle.angle();
        const Vector3<Type> axis = axis_angle.axis();

        const Type cos_angle = cos(angle / Type(2));
        const Type sin_angle = sin(angle / Type(2));

        w() = cos_angle;
        x() = sin_angle * axis.x();
        y() = sin_angle * axis.y();
        z() = sin_angle * axis.z();

    } else if(is_same<QuaternionConvention, JPL>::value) {
        const Type angle = axis_angle.angle();
        const Vector3<Type> axis = axis_angle.axis();

        const Type cos_angle = cos(angle / Type(2));
        const Type sin_angle = sin(angle / Type(2));

        w() = cos_angle;
        x() = -sin_angle * axis.x();
        y() = -sin_angle * axis.y();
        z() = -sin_angle * axis.z();
    }
}
