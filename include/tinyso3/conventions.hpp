/**
 * @file Conventions.hpp
 * 
 * @brief This file contains the common conventions used in the library.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

#include <assert.h>
#include "tiny_type_traits.hpp"

namespace tinyso3 {
enum class PrincipalAxis { // Do not change the order and values.
    X,
    Y,
    Z
};

static_assert(static_cast<int>(PrincipalAxis::X) == 0, "PrincipalAxis::X must be 0.");
static_assert(static_cast<int>(PrincipalAxis::Y) == 1, "PrincipalAxis::Y must be 1.");
static_assert(static_cast<int>(PrincipalAxis::Z) == 2, "PrincipalAxis::Z must be 2.");

using X = integral_constant<PrincipalAxis, PrincipalAxis::X>;
using Y = integral_constant<PrincipalAxis, PrincipalAxis::Y>;
using Z = integral_constant<PrincipalAxis, PrincipalAxis::Z>;

template<typename T>
struct is_principal_axis;

enum class RotationMatrixConvention {
    ACTIVE,
    PASSIVE
};

using ACTIVE = integral_constant<RotationMatrixConvention, RotationMatrixConvention::ACTIVE>;
using PASSIVE = integral_constant<RotationMatrixConvention, RotationMatrixConvention::PASSIVE>;

template<typename T>
struct is_rotation_matrix_convention;

enum class EulerConvention {
    INTRINSIC,
    EXTRINSIC
};

using INTRINSIC = integral_constant<EulerConvention, EulerConvention::INTRINSIC>;
using EXTRINSIC = integral_constant<EulerConvention, EulerConvention::EXTRINSIC>;

template<typename T>
struct is_euler_convention;

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

template<typename T>
struct is_principal_axis : false_type {};
template<>
struct is_principal_axis<X> : true_type {};
template<>
struct is_principal_axis<Y> : true_type {};
template<>
struct is_principal_axis<Z> : true_type {};

template<typename T>
struct is_rotation_matrix_convention : false_type {};
template<>
struct is_rotation_matrix_convention<ACTIVE> : true_type {};
template<>
struct is_rotation_matrix_convention<PASSIVE> : true_type {};

using ALIBI = ACTIVE;
using ALIAS = PASSIVE;

template<typename T>
struct is_euler_convention : false_type {};
template<>
struct is_euler_convention<INTRINSIC> : true_type {};
template<>
struct is_euler_convention<EXTRINSIC> : true_type {};

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

enum class QuaternionConvention {
    HAMILTON,
    JPL,
};

using HAMILTON = integral_constant<QuaternionConvention, QuaternionConvention::HAMILTON>;
using JPL = integral_constant<QuaternionConvention, QuaternionConvention::JPL>;

template<typename T>
struct is_quaternion_convention;
template<typename T>
struct is_quaternion_convention : false_type {};
template<>
struct is_quaternion_convention<HAMILTON> : true_type {};
template<>
struct is_quaternion_convention<JPL> : true_type {};

}; // namespace tinyso3