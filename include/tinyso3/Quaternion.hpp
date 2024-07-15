/**
 * @file Quaternion.hpp
 * 
 * A template based quaternion
 * 
 * @author lightaxis <jisuk500@gmail.com>
 */

#pragma once

#include "Vector3.hpp"
#include "tiny_type_traits.hpp"
#include "tiny_epsilon.hpp"

namespace tinyso3 {
template<typename RotationMatrixConvention, typename Type>
class RotationMatrix;
template<typename EulerConvention, typename EulerSequence, typename Type>
class Euler;
template<typename Type>
class AxisAngle;

template<typename QuaternionConvention = TINYSO3_DEFAULT_QUATERNION_CONVENTION, typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
class Quaternion : public Vector<4, Type> {
    static_assert(is_quaternion_convention<QuaternionConvention>::value, "QuaternionConvention must be one of the QuaternionConvention types (HAMILTON, JPL).");

protected:
    using Vector<4, Type>::data;

    Quaternion(Type) = delete;
    Quaternion(Vector3<Type> xyz); // w = 0

public:
    using Convention = QuaternionConvention;
    using RotationMatrixAlias = conditional_t<is_same<QuaternionConvention, HAMILTON>::value, RotationMatrix<ACTIVE, Type>, RotationMatrix<PASSIVE, Type>>;
    using Vector<4, Type>::norm;

    /**
     * Constructors
     */
    Quaternion();

    // w, x, y, z (Hamilton) or x y z w (JPL)
    Quaternion(const Type arr[4]);
    Quaternion(Type q1, Type q2, Type q3, Type q4);
    Quaternion(const Vector<4, Type>& other);
    template<typename Convention = QuaternionConvention, enable_if_t<(is_same<Convention, HAMILTON>::value), int> = 0>
    Quaternion(Type w, Vector3<Type> xyz);
    template<typename Convention = QuaternionConvention, enable_if_t<(is_same<Convention, JPL>::value), int> = 0>
    Quaternion(Vector3<Type> xyz, Type w);
    Quaternion(const RotationMatrixAlias& dcm);
    template<typename EulerConvention, typename EulerSequence>
    Quaternion(const Euler<EulerConvention, EulerSequence, Type>& euler);
    Quaternion(const AxisAngle<Type>& axis_angle);

    /**
     * Static Methods
     */
    static inline Quaternion<QuaternionConvention, Type> Identity() { return Quaternion<QuaternionConvention, Type>{}; }
    template<typename Axis, enable_if_t<(is_principal_axis<Axis>::value), int> = 0>
    static Quaternion<QuaternionConvention, Type> RotatePrincipalAxis(const Type& angle);
    static Quaternion<QuaternionConvention, Type> Exp(const Vector3<Type>& vec3);

    /**
     * Accessors
     */
    inline Type& w() { return data[_W][0]; };
    inline Type& x() { return data[_X][0]; };
    inline Type& y() { return data[_Y][0]; };
    inline Type& z() { return data[_Z][0]; };
    inline const Type& w() const { return data[_W][0]; };
    inline const Type& x() const { return data[_X][0]; };
    inline const Type& y() const { return data[_Y][0]; };
    inline const Type& z() const { return data[_Z][0]; };

    /**
     * Real and Imaginary parts
     */
    inline Vector3<Type> Im() const { return Vector3<Type>(x(), y(), z()); }
    inline Type Re() const { return w(); }

    inline Quaternion<QuaternionConvention, Type> conjugate() const;
    inline Quaternion<QuaternionConvention, Type> canonicalize() const;

    /**
     * operator overloading
     */
    inline Quaternion<QuaternionConvention, Type> operator*(const Quaternion<QuaternionConvention, Type>& other) const;
    inline Vector3<Type> operator*(const Vector3<Type>& other_vec) const;

    inline void operator*=(const Quaternion<QuaternionConvention, Type>& other) { (*this) = (*this) * other; }
    inline Quaternion<QuaternionConvention, Type> operator/(const Quaternion<QuaternionConvention, Type>& other) const { return (*this) * other.conjugate(); }
    inline void operator/=(const Quaternion<QuaternionConvention, Type>& other) { (*this) = (*this) / other; }

    Quaternion<QuaternionConvention, Type> slerp(const Quaternion<QuaternionConvention, Type>& to, Type t);
    Vector3<Type> log() const;
    Quaternion<QuaternionConvention, Type> pow(Type t) const;

    inline Quaternion<QuaternionConvention, Type> unit() const { return Vector<4, Type>::unit(); }

private:
    template<typename Axis>
    constexpr static inline int IDX();
    constexpr static int _W = is_same<QuaternionConvention, HAMILTON>::value ? 0 : 3;
    constexpr static int _X = IDX<X>();
    constexpr static int _Y = IDX<Y>();
    constexpr static int _Z = IDX<Z>();
};

template<typename QuaternionConvention = HAMILTON>
using Quaternionf = Quaternion<QuaternionConvention, float>;
template<typename QuaternionConvention = HAMILTON>
using Quaterniond = Quaternion<QuaternionConvention, double>;
template<typename QuaternionConvention = HAMILTON>
using Quaternionld = Quaternion<QuaternionConvention, long double>;

#include "impl/Quaternion_impl.hpp"
} // namespace tinyso3