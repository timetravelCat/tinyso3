#pragma once

#include "config.hpp"

#define TINYSO3_EPS_EXPONENT_0 1e-0
#define TINYSO3_EPS_EXPONENT_1 1e-1
#define TINYSO3_EPS_EXPONENT_2 1e-2
#define TINYSO3_EPS_EXPONENT_3 1e-3
#define TINYSO3_EPS_EXPONENT_4 1e-4
#define TINYSO3_EPS_EXPONENT_5 1e-5
#define TINYSO3_EPS_EXPONENT_6 1e-6
#define TINYSO3_EPS_EXPONENT_7 1e-7
#define TINYSO3_EPS_EXPONENT_8 1e-8
#define TINYSO3_EPS_EXPONENT_9 1e-9
#define TINYSO3_EPS_EXPONENT_10 1e-10
#define TINYSO3_EPS_EXPONENT_11 1e-11
#define TINYSO3_EPS_EXPONENT_12 1e-12
#define TINYSO3_EPS_EXPONENT_13 1e-13
#define TINYSO3_EPS_EXPONENT_14 1e-14
#define TINYSO3_EPS_EXPONENT_15 1e-15
#define TINYSO3_EPS_EXPONENT_16 1e-16
#define TINYSO3_EPS_EXPONENT_17 1e-17
#define TINYSO3_EPS_EXPONENT_18 1e-18
#define TINYSO3_EPS_EXPONENT_19 1e-19
#define TINYSO3_EPS_EXPONENT_20 1e-20

#define TINYSO3_EPS_EXPONENT_NAME(N) TINYSO3_EPS_EXPONENT_##N
#define TINYSO3_EPS_EXPONENT_VALUE(N) TINYSO3_EPS_EXPONENT_NAME(N)

#define TINYSO3_FLT_EPSILON TINYSO3_EPS_EXPONENT_VALUE(CONFIG_DEFAULT_FLOATING_POINT_PRECISION_32_EPSILON)
#define TINYSO3_DBL_EPSILON TINYSO3_EPS_EXPONENT_VALUE(CONFIG_DEFAULT_FLOATING_POINT_PRECISION_64_EPSILON)
#define TINYSO3_LDBL_EPSILON TINYSO3_EPS_EXPONENT_VALUE(CONFIG_DEFAULT_FLOATING_POINT_PRECISION_128_EPSILON)
namespace tinyso3 {
template<typename T>
constexpr T epsilon() {
    static_assert(true, "T must be a floating point type");
    return static_cast<T>(0); // Can not reach here, but to avoid compiler warning
}

template<>
constexpr float epsilon<>() {
    return static_cast<float>(TINYSO3_FLT_EPSILON);
}

template<>
constexpr double epsilon<>() {
    return TINYSO3_DBL_EPSILON;
}

template<>
constexpr long double epsilon<>() {
    return static_cast<long double>(TINYSO3_LDBL_EPSILON);
}
}; // namespace tinyso3
