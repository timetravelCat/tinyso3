/**
 * @file tiny_math.hpp
 * 
 * A template based minimal math library.
 */

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace tinyso3 {
template<typename T>
inline T sqrt(const T& value) {
    return ::sqrt(value);
}
template<>
inline float sqrt(const float& value) {
    return ::sqrtf(value);
}
template<>
inline long double sqrt(const long double& value) {
    return ::sqrtl(value);
}

template<typename T>
inline T sin(const T& value) {
    return ::sin(value);
}
template<>
inline float sin(const float& value) {
    return ::sinf(value);
}
template<>
inline long double sin(const long double& value) {
    return ::sinl(value);
}

template<typename T>
inline T cos(const T& value) {
    return ::cos(value);
}
template<>
inline float cos(const float& value) {
    return ::cosf(value);
}
template<>
inline long double cos(const long double& value) {
    return ::cosl(value);
}

template<typename T>
inline T tan(const T& value) {
    return ::tan(value);
}
template<>
inline float tan(const float& value) {
    return ::tanf(value);
}
template<>
inline long double tan(const long double& value) {
    return ::tanl(value);
}

template<typename T>
inline T atan(const T& value) {
    return ::atan(value);
}
template<>
inline float atan(const float& value) {
    return ::atanf(value);
}
template<>
inline long double atan(const long double& value) {
    return ::atanl(value);
}

template<typename T>
inline T atan2(const T& y, const T& x) {
    return ::atan2(y, x);
}
template<>
inline float atan2(const float& y, const float& x) {
    return ::atan2f(y, x);
}
template<>
inline long double atan2(const long double& y, const long double& x) {
    return ::atan2l(y, x);
}

template<typename T>
inline T asin(const T& value) {
    return ::asin(value);
}
template<>
inline float asin(const float& value) {
    return ::asinf(value);
}
template<>
inline long double asin(const long double& value) {
    return ::asinl(value);
}

template<typename T>
inline T acos(const T& value) {
    return ::acos(value);
}
template<>
inline float acos(const float& value) {
    return ::acosf(value);
}
template<>
inline long double acos(const long double& value) {
    return ::acosl(value);
}

template<typename T>
inline T fmin(const T& a, const T& b) {
    return ::fmin(a, b);
}
template<>
inline float fmin(const float& a, const float& b) {
    return ::fminf(a, b);
}
template<>
inline long double fmin(const long double& a, const long double& b) {
    return ::fminl(a, b);
}

template<typename T>
inline T fmax(const T& a, const T& b) {
    return ::fmax(a, b);
}
template<>
inline float fmax(const float& a, const float& b) {
    return ::fmaxf(a, b);
}
template<>
inline long double fmax(const long double& a, const long double& b) {
    return ::fmaxl(a, b);
}

template<typename T>
inline T fabs(const T& value) {
    return ::fabs(value);
}
template<>
inline float fabs(const float& value) {
    return ::fabsf(value);
}
template<>
inline long double fabs(const long double& value) {
    return ::fabsl(value);
}

template<typename T>
inline T pow(const T& base, const T& exponent) {
    return ::pow(base, exponent);
}
template<>
inline float pow(const float& base, const float& exponent) {
    return ::powf(base, exponent);
}
template<>
inline long double pow(const long double& base, const long double& exponent) {
    return ::powl(base, exponent);
}

template<typename T>
inline T exp(const T& value) {
    return ::exp(value);
}
template<>
inline float exp(const float& value) {
    return ::expf(value);
}
template<>
inline long double exp(const long double& value) {
    return ::expl(value);
}

template<typename T>
inline T log(const T& value) {
    return ::log(value);
}
template<>
inline float log(const float& value) {
    return ::logf(value);
}
template<>
inline long double log(const long double& value) {
    return ::logl(value);
}

template<typename T>
inline T log10(const T& value) {
    return ::log10(value);
}
template<>
inline float log10(const float& value) {
    return ::log10f(value);
}
template<>
inline long double log10(const long double& value) {
    return ::log10l(value);
}

template<typename T>
inline T log2(const T& value) {
    return ::log2(value);
}
template<>
inline float log2(const float& value) {
    return ::log2f(value);
}
template<>
inline long double log2(const long double& value) {
    return ::log2l(value);
}

template<typename T>
inline T ceil(const T& value) {
    return ::ceil(value);
}
template<>
inline float ceil(const float& value) {
    return ::ceilf(value);
}
template<>
inline long double ceil(const long double& value) {
    return ::ceill(value);
}

template<typename T>
inline T floor(const T& value) {
    return ::floor(value);
}
template<>
inline float floor(const float& value) {
    return ::floorf(value);
}
template<>
inline long double floor(const long double& value) {
    return ::floorl(value);
}

template<typename T>
inline T round(const T& value) {
    return ::round(value);
}
template<>
inline float round(const float& value) {
    return ::roundf(value);
}
template<>
inline long double round(const long double& value) {
    return ::roundl(value);
}

template<typename T>
inline T trunc(const T& value) {
    return ::trunc(value);
}
template<>
inline float trunc(const float& value) {
    return ::truncf(value);
}
template<>
inline long double trunc(const long double& value) {
    return ::truncl(value);
}

template<typename T>
inline T clamp(const T& value, const T& min, const T& max) {
    return fmin(fmax(value, min), max);
}

} // namespace tinyso3