/**
 * @file Euler_impl.hpp
 * 
 * A template based minimal euler angle representations.
 * 
 * Euler angles are a way to describe the orientation of a rigid body in three-dimensional space. 
 * They are defined by three successive rotations around different axes. 
 * There are two main types of Euler angles: extrinsic and intrinsic.
 * 
 * Extrinsic Euler angles describe rotations about the axes of a fixed coordinate system (global frame).
 * Intrinsic Euler angles describe rotations about the axes of a moving coordinate system (body frame).
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
 * 
 * ACTIVE(ALIBI) rotation, Intrinsic euler, ZYX Sequence rotation matrix is, Rz*Ry*Rx.
 * PASSIVE(ALIAS) rotation, Intrinsic euler, ZYX Sequence rotation matrix is, Rx*Ry*Rz.
 * ACTIVE(ALIBI) rotation, Extrinsic euler, ZYX Sequence rotation matrix is, Rx*Ry*Rz.
 * PASSIVE(ALIAS) rotation, Extrinsic euler, ZYX Sequence rotation matrix is, Rz*Ry*Rx.
 * 
 * Be careful about PASSIVE / ACTIVE rotation. 
 * PASSIVE principal rotation matrix is transpose of ACTIVE principal rotation matrix.
 * 
 * Euler class contains 3 angles, in order of rotation.
 * In case of gimbal lock, there are infinite solutions.
 * Here, we set first rotation angle to 0.
 * 
 * @author timetravelCat<timetraveler930@gmail.com>
 */

#pragma once

template<typename EulerConvention, typename EulerSequence, typename Type>
Euler<EulerConvention, EulerSequence, Type>::Euler(const Euler& other) :
Vector3<Type>(other){};

template<typename EulerConvention, typename EulerSequence, typename Type>
template<typename RotationMatrixConvention>
Euler<EulerConvention, EulerSequence, Type>::Euler(const RotationMatrix<RotationMatrixConvention, Type>& dcm) {
    constexpr int AXIS_FIRST = static_cast<int>(EulerSequence::Axis1);
    constexpr int AXIS_SECOND = static_cast<int>(EulerSequence::Axis2);
    constexpr int AXIS_THIRD = static_cast<int>(EulerSequence::Axis3);
    constexpr int AXIS_LEFT = 3 - AXIS_FIRST - AXIS_SECOND;
    constexpr Type SIGN = (((AXIS_SECOND - AXIS_FIRST) == 1) || ((AXIS_SECOND - AXIS_FIRST) == -2)) ? Type(1) : Type(-1);

    constexpr bool IS_DEFAULT_SEQUENCE = (is_same<EulerConvention, INTRINSIC>::value && is_same<RotationMatrixConvention, ACTIVE>::value) ||
                                         (is_same<EulerConvention, EXTRINSIC>::value && is_same<RotationMatrixConvention, PASSIVE>::value);

    if(IS_DEFAULT_SEQUENCE) {
        if(AXIS_FIRST == AXIS_THIRD) { // Proper Euler angles
            data[2][0] = atan2(dcm(AXIS_FIRST, AXIS_SECOND), SIGN * dcm(AXIS_FIRST, AXIS_LEFT));
            data[1][0] = acos(dcm(AXIS_FIRST, AXIS_FIRST));
            data[0][0] = atan2(dcm(AXIS_SECOND, AXIS_FIRST), -SIGN * dcm(AXIS_LEFT, AXIS_FIRST));
        } else { // Tait-Bryan angles
            data[2][0] = atan2(-SIGN * dcm(AXIS_FIRST, AXIS_SECOND), dcm(AXIS_FIRST, AXIS_FIRST));
            data[1][0] = SIGN * asin(dcm(AXIS_FIRST, AXIS_THIRD));
            data[0][0] = atan2(-SIGN * dcm(AXIS_SECOND, AXIS_THIRD), dcm(AXIS_THIRD, AXIS_THIRD));
        }
    } else {
        if(AXIS_FIRST == AXIS_THIRD) { // Proper Euler angles
            data[2][0] = atan2(dcm(AXIS_SECOND, AXIS_FIRST), SIGN * dcm(AXIS_LEFT, AXIS_FIRST));
            data[1][0] = acos(dcm(AXIS_FIRST, AXIS_FIRST));
            data[0][0] = atan2(dcm(AXIS_FIRST, AXIS_SECOND), -SIGN * dcm(AXIS_FIRST, AXIS_LEFT));
        } else { // Tait-Bryan angles
            data[2][0] = atan2(-SIGN * dcm(AXIS_SECOND, AXIS_FIRST), dcm(AXIS_FIRST, AXIS_FIRST));
            data[1][0] = SIGN * asin(dcm(AXIS_THIRD, AXIS_FIRST));
            data[0][0] = atan2(-SIGN * dcm(AXIS_THIRD, AXIS_SECOND), dcm(AXIS_THIRD, AXIS_THIRD));
        }
    }

    /**
     * In case of gimbal lock.
     */
    if(AXIS_FIRST == AXIS_THIRD) { // Proper Euler angles
        if(fabs(data[1][0]) < epsilon<Type>()) {
            data[0][0] = Type(0);
            data[2][0] = IS_DEFAULT_SEQUENCE ?
                           atan2(-SIGN * dcm(AXIS_SECOND, AXIS_LEFT), dcm(AXIS_SECOND, AXIS_SECOND)) :
                           atan2(-SIGN * dcm(AXIS_LEFT, AXIS_SECOND), dcm(AXIS_SECOND, AXIS_SECOND));

        } else if(fabs(data[1][0] - Type(M_PI)) < epsilon<Type>()) {
            data[0][0] = Type(0);
            data[2][0] = IS_DEFAULT_SEQUENCE ?
                           atan2(-SIGN * dcm(AXIS_SECOND, AXIS_LEFT), dcm(AXIS_SECOND, AXIS_SECOND)) :
                           atan2(-SIGN * dcm(AXIS_LEFT, AXIS_SECOND), dcm(AXIS_SECOND, AXIS_SECOND));
        }
    } else { // Tait-Bryan angles
        if(fabs(data[1][0] - Type(M_PI_2)) < epsilon<Type>()) {
            data[0][0] = Type(0);
            data[2][0] = IS_DEFAULT_SEQUENCE ?
                           atan2(dcm(AXIS_THIRD, AXIS_SECOND), -SIGN * dcm(AXIS_THIRD, AXIS_FIRST)) :
                           atan2(dcm(AXIS_SECOND, AXIS_THIRD), -SIGN * dcm(AXIS_FIRST, AXIS_THIRD));
        } else if(fabs(data[1][0] + Type(M_PI_2)) < epsilon<Type>()) {
            data[0][0] = Type(0);
            data[2][0] = IS_DEFAULT_SEQUENCE ?
                           atan2(-dcm(AXIS_THIRD, AXIS_SECOND), SIGN * dcm(AXIS_THIRD, AXIS_FIRST)) :
                           atan2(-dcm(AXIS_SECOND, AXIS_THIRD), SIGN * dcm(AXIS_FIRST, AXIS_THIRD));
        }
    }
};

template<typename EulerConvention, typename EulerSequence, typename Type>
Euler<EulerConvention, EulerSequence, Type>::Euler(const AxisAngle<Type>& axis_angle) :
Euler(RotationMatrix<ACTIVE, Type>{axis_angle}){};
