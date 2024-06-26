/**
 * @file Euler.hpp
 * 
 * A template based minimal euler angle representations.
 * 
 * There are 12 possible representations of Euler angles, which are divided into two groups:
 * - Tait-Bryan angles: The first and third angles are in the range [-pi, pi], and the second angle is in the range [-pi/2, pi/2].
 * - Proper Euler angles: The first and third angles are in the range [-pi, pi], and the second angle is in the range [0, pi].
 * 
 * Sequence of rotations(Tait-Bryan angles):
 * - XYZ: Rotate by Z, then Y, then X.
 * - XZY: Rotate by Y, then Z, then X.
 * - YXZ: Rotate by Z, then X, then Y.
 * - YZX: Rotate by X, then Z, then Y.
 * - ZXY: Rotate by Y, then X, then Z.
 * - ZYX: Rotate by X, then Y, then Z.
 * 
 * Sequence of rotations(Proper Euler angles):
 * - XYX: Rotate by X, then Y, then X.
 * - XZX: Rotate by Z, then X, then Z.
 * - YXY: Rotate by Y, then X, then Y.
 * - YZY: Rotate by Y, then Z, then Y.
 * - ZXZ: Rotate by Z, then X, then Z.
 * - ZYZ: Rotate by Y, then Z, then Y.
 * 
 * Sequence means the order of rotations.
 * For ACTIVE(ALIBI) rotation, ZYX Sequence rotation matrix is, Rz*Ry*Rx.
 * However, for PASSIVE(ALIAS), ZYX Sequence rotation matrix is, Rx*Ry*Rz.
 * Be careful about PASSIVE / ACTIVE rotation. 
 * PASSIVE principal rotation matrix is transpose of ACTIVE principal rotation matrix.
 * 
 * Euler class contains 3 angles, in order of rotation.
 * 
 * @author timetravelCat<timetraveler930@gmail.com>
 */

#pragma once

#include "Vector3.hpp"
#include "tiny_type_traits.hpp"
#include "epsilon.hpp"
#include "RotationMatrix.hpp"

namespace tinyso3 {
template<PrincipalAxis _Axis1, PrincipalAxis _Axis2, PrincipalAxis _Axis3>
struct EulerSequence {
    static constexpr PrincipalAxis Axis1 = _Axis1;
    static constexpr PrincipalAxis Axis2 = _Axis2;
    static constexpr PrincipalAxis Axis3 = _Axis3;
};

using XYZ = EulerSequence<X::value, Y::value, Z::value>;
using XZY = EulerSequence<X::value, Z::value, Y::value>;
using YXZ = EulerSequence<Y::value, X::value, Z::value>;
using YZX = EulerSequence<Y::value, Z::value, X::value>;
using ZXY = EulerSequence<Z::value, X::value, Y::value>;
using ZYX = EulerSequence<Z::value, Y::value, X::value>;
using XYX = EulerSequence<X::value, Y::value, X::value>;
using XZX = EulerSequence<X::value, Z::value, X::value>;
using YXY = EulerSequence<Y::value, X::value, Y::value>;
using YZY = EulerSequence<Y::value, Z::value, Y::value>;
using ZXZ = EulerSequence<Z::value, X::value, Z::value>;
using ZYZ = EulerSequence<Z::value, Y::value, Z::value>;

template<typename T>
struct is_euler_sequence;

template<typename EulerSequence = TINYSO3_DEFAULT_EULER_ANGLE_SEQUENCE, typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
class Euler : public Vector3<Type> {
    static_assert(is_euler_sequence<EulerSequence>::value, "EulerSequence must be one of the EulerSequence types.");

protected:
    using Vector3<Type>::data;

public:
    /**
     * Constructors
     */
    using Vector3<Type>::Vector3;

    template<typename Convention>
    Euler(const RotationMatrix<Convention, Type>& dcm);
};

template<typename EulerSequence, typename Type>
template<typename Convention>
Euler<EulerSequence, Type>::Euler(const RotationMatrix<Convention, Type>& dcm) {
    constexpr int AXIS_FIRST = static_cast<int>(EulerSequence::Axis1);
    constexpr int AXIS_SECOND = static_cast<int>(EulerSequence::Axis2);
    constexpr int AXIS_THIRD = static_cast<int>(EulerSequence::Axis3);
    constexpr int AXIS_LEFT = 3 - AXIS_FIRST - AXIS_SECOND;
    constexpr Type SIGN = (((AXIS_SECOND - AXIS_FIRST) == 1) || ((AXIS_SECOND - AXIS_FIRST) == -2)) ? Type(1) : Type(-1);

    if(is_same<Convention, ACTIVE>::value) {
        if(AXIS_FIRST == AXIS_THIRD) { // Proper Euler angles
            data[2][0] = ::atan2(dcm(AXIS_FIRST, AXIS_SECOND), SIGN * dcm(AXIS_FIRST, AXIS_LEFT));
            data[1][0] = ::acos(dcm(AXIS_FIRST, AXIS_FIRST));
            data[0][0] = ::atan2(dcm(AXIS_SECOND, AXIS_FIRST), -SIGN * dcm(AXIS_LEFT, AXIS_FIRST));
        } else { // Tait-Bryan angles
            data[2][0] = ::atan2(-SIGN * dcm(AXIS_FIRST, AXIS_SECOND), dcm(AXIS_FIRST, AXIS_FIRST));
            data[1][0] = SIGN * ::asin(dcm(AXIS_FIRST, AXIS_THIRD));
            data[0][0] = ::atan2(-SIGN * dcm(AXIS_SECOND, AXIS_THIRD), dcm(AXIS_THIRD, AXIS_THIRD));
        }
    } else if(is_same<Convention, PASSIVE>::value) {
        if(AXIS_FIRST == AXIS_THIRD) { // Proper Euler angles
            data[2][0] = ::atan2(dcm(AXIS_SECOND, AXIS_FIRST), SIGN * dcm(AXIS_LEFT, AXIS_FIRST));
            data[1][0] = ::acos(dcm(AXIS_FIRST, AXIS_FIRST));
            data[0][0] = ::atan2(dcm(AXIS_FIRST, AXIS_SECOND), -SIGN * dcm(AXIS_FIRST, AXIS_LEFT));
        } else { // Tait-Bryan angles
            data[2][0] = ::atan2(-SIGN * dcm(AXIS_SECOND, AXIS_FIRST), dcm(AXIS_FIRST, AXIS_FIRST));
            data[1][0] = SIGN * ::asin(dcm(AXIS_THIRD, AXIS_FIRST));
            data[0][0] = ::atan2(-SIGN * dcm(AXIS_THIRD, AXIS_SECOND), dcm(AXIS_THIRD, AXIS_THIRD));
        }
    }

    /**
     * In case of gimbal lock, there are infinite solutions.
     * 
     * Here, we set first rotation angle to 0.
     * ! WIP
     */
    if(AXIS_FIRST == AXIS_THIRD) { // Proper Euler angles
        if(::fabs(data[1][0]) < epsilon<Type>()) {
            data[0][0] = Type(0);
            // ! WIP
        } else if(::fabs(data[1][0] - Type(M_PI)) < epsilon<Type>()) {
            data[0][0] = Type(0);
            // ! WIP
        }
    } else { // Tait-Bryan angles
        if(::fabs(data[1][0] - Type(M_PI_2)) < epsilon<Type>()) {
            data[0][0] = Type(0);
            // ! WIP
        } else if(::fabs(data[1][0] + Type(M_PI_2)) < epsilon<Type>()) {
            data[0][0] = Type(0);
            // ! WIP
        }
    }
};

template<typename T>
struct is_euler_sequence : false_type {};
template<>
struct is_euler_sequence<EulerSequence<X::value, Y::value, Z::value>> : true_type {};
template<>
struct is_euler_sequence<EulerSequence<X::value, Z::value, Y::value>> : true_type {};
template<>
struct is_euler_sequence<EulerSequence<Y::value, X::value, Z::value>> : true_type {};
template<>
struct is_euler_sequence<EulerSequence<Y::value, Z::value, X::value>> : true_type {};
template<>
struct is_euler_sequence<EulerSequence<Z::value, X::value, Y::value>> : true_type {};
template<>
struct is_euler_sequence<EulerSequence<Z::value, Y::value, X::value>> : true_type {};
template<>
struct is_euler_sequence<EulerSequence<X::value, Y::value, X::value>> : true_type {};
template<>
struct is_euler_sequence<EulerSequence<X::value, Z::value, X::value>> : true_type {};
template<>
struct is_euler_sequence<EulerSequence<Y::value, X::value, Y::value>> : true_type {};
template<>
struct is_euler_sequence<EulerSequence<Y::value, Z::value, Y::value>> : true_type {};
template<>
struct is_euler_sequence<EulerSequence<Z::value, X::value, Z::value>> : true_type {};
template<>
struct is_euler_sequence<EulerSequence<Z::value, Y::value, Z::value>> : true_type {};
} // namespace tinyso3
