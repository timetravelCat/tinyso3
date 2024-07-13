/**
 * @file Euler.hpp
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

#include "Vector3.hpp"
#include "tiny_type_traits.hpp"
#include "tiny_epsilon.hpp"

namespace tinyso3 {
template<typename RotationMatrixConvention, typename Type>
class RotationMatrix;
template<typename Type>
class AxisAngle;
template<typename QuaternionConvention, typename Type>
class Quaternion;

template<typename EulerConvention = TINYSO3_DEFAULT_EULER_ANGLE_CONVENTION, typename EulerSequence = TINYSO3_DEFAULT_EULER_ANGLE_SEQUENCE, typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
class Euler : public Vector3<Type> {
    static_assert(is_euler_convention<EulerConvention>::value, "EulerConvention must be one of the EulerConvention types.");
    static_assert(is_euler_sequence<EulerSequence>::value, "EulerSequence must be one of the EulerSequence types.");

protected:
    using Vector3<Type>::data;

public:
    using Convention = EulerConvention;
    using Sequence = EulerSequence;

    /**
     * Constructors
     */
    using Vector3<Type>::Vector3;

    Euler(const Euler& other);
    template<typename RotationMatrixConvention>
    Euler(const RotationMatrix<RotationMatrixConvention, Type>& dcm);
    Euler(const AxisAngle<Type>& axis_angle);
    template<typename QuaternionConvention>
    Euler(const Quaternion<QuaternionConvention, Type>& quaternion);
};

#include "impl/Euler_impl.hpp"
} // namespace tinyso3