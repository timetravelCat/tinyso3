
/**
 * @file Angle.hpp
 * 
 * An angle class for 1D angles.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

#include "version.hpp"

#include <stddef.h>
#include <assert.h>
#define _USE_MATH_DEFINES
#include <math.h>

namespace tinyso3 {
enum class WrapMode {
    NEG_PI_TO_PI,
    ZERO_TO_TWO_PI,
    INFINITE
};

template<WrapMode Mode = WrapMode::NEG_PI_TO_PI, typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
class Angle {
private:
    Type rad{}; // stores the angle in radians

public:
    /**
     * Constructors
     */
    Angle() = default;
    Angle(const Type& rad_);

    /**
     * Cast to primitive type
     */
    inline operator Type() const;

    /**
     * Accessors
     */
    Type deg() const;

    /**
     * Arithmetic operators
     */
    Angle operator+(const Type& other) const;
    Angle operator-(const Type& other) const;
    Angle operator*(const Type& other) const;
    Angle operator/(const Type& other) const;
    void operator+=(const Type& other);
    void operator-=(const Type& other);
    void operator*=(const Type& other);
    void operator/=(const Type& other);
    bool operator==(const Type& other) const;
    bool operator!=(const Type& other) const;

    template<WrapMode _Mode, typename _Type>
    friend Angle<_Mode, _Type> operator+(const _Type& lhs, const Angle<_Mode, _Type>& rhs);
    template<WrapMode _Mode, typename _Type>
    friend Angle<_Mode, _Type> operator-(const _Type& lhs, const Angle<_Mode, _Type>& rhs);
    template<WrapMode _Mode, typename _Type>
    friend Angle<_Mode, _Type> operator*(const _Type& lhs, const Angle<_Mode, _Type>& rhs);
    template<WrapMode _Mode, typename _Type>
    friend Angle<_Mode, _Type> operator/(const _Type& lhs, const Angle<_Mode, _Type>& rhs);
    template<WrapMode _Mode, typename _Type>
    friend bool operator==(const _Type& lhs, const Angle<_Mode, _Type>& rhs);
    template<WrapMode _Mode, typename _Type>
    friend bool operator!=(const _Type& lhs, const Angle<_Mode, _Type>& rhs);

private:
    /**
     * wrap, depending on the mode
     */
    void wrap();
    void wrap(const Type& lowBound, const Type& highBound);

    template<WrapMode _Mode, typename _Type>
    friend class Angle;
};

template<WrapMode Mode, typename Type>
Angle<Mode, Type>::Angle(const Type& rad_) :
rad(rad_) {
    wrap();
}

template<WrapMode Mode, typename Type>
Angle<Mode, Type>::operator Type() const {
    return rad;
}

template<WrapMode Mode, typename Type>
Type Angle<Mode, Type>::deg() const {
    return rad * Type(180) / Type(M_PI);
}

template<WrapMode Mode, typename Type>
Angle<Mode, Type> Angle<Mode, Type>::operator+(const Type& other) const {
    return Angle<Mode, Type>{rad + other};
}

template<WrapMode Mode, typename Type>
Angle<Mode, Type> Angle<Mode, Type>::operator-(const Type& other) const {
    return Angle<Mode, Type>{rad - other};
}

template<WrapMode Mode, typename Type>
Angle<Mode, Type> Angle<Mode, Type>::operator*(const Type& other) const {
    return Angle<Mode, Type>{rad * other};
}

template<WrapMode Mode, typename Type>
Angle<Mode, Type> Angle<Mode, Type>::operator/(const Type& other) const {
    return Angle<Mode, Type>{rad / other};
}

template<WrapMode Mode, typename Type>
void Angle<Mode, Type>::operator+=(const Type& other) {
    rad += other;
    wrap();
}

template<WrapMode Mode, typename Type>
void Angle<Mode, Type>::operator-=(const Type& other) {
    rad -= other;
    wrap();
}

template<WrapMode Mode, typename Type>
void Angle<Mode, Type>::operator*=(const Type& other) {
    rad *= other;
    wrap();
}

template<WrapMode Mode, typename Type>
void Angle<Mode, Type>::operator/=(const Type& other) {
    rad /= other;
    wrap();
}

template<WrapMode Mode, typename Type>
bool Angle<Mode, Type>::operator==(const Type& other) const {
    return rad == other;
}

template<WrapMode Mode, typename Type>
bool Angle<Mode, Type>::operator!=(const Type& other) const {
    return rad != other;
}

template<WrapMode _Mode, typename _Type>
Angle<_Mode, _Type> operator+(const _Type& lhs, const Angle<_Mode, _Type>& rhs) {
    return Angle<_Mode, _Type>{lhs + rhs.rad};
}

template<WrapMode _Mode, typename _Type>
Angle<_Mode, _Type> operator-(const _Type& lhs, const Angle<_Mode, _Type>& rhs) {
    return Angle<_Mode, _Type>{lhs - rhs.rad};
}

template<WrapMode _Mode, typename _Type>
Angle<_Mode, _Type> operator*(const _Type& lhs, const Angle<_Mode, _Type>& rhs) {
    return Angle<_Mode, _Type>{lhs * rhs.rad};
}

template<WrapMode _Mode, typename _Type>
Angle<_Mode, _Type> operator/(const _Type& lhs, const Angle<_Mode, _Type>& rhs) {
    return Angle<_Mode, _Type>{lhs / rhs.rad};
}

template<WrapMode _Mode, typename _Type>
bool operator==(const _Type& lhs, const Angle<_Mode, _Type>& rhs) {
    return lhs == rhs.rad;
}

template<WrapMode _Mode, typename _Type>
bool operator!=(const _Type& lhs, const Angle<_Mode, _Type>& rhs) {
    return lhs != rhs.rad;
}

template<WrapMode Mode, typename Type>
void Angle<Mode, Type>::wrap() {
    if(Mode == WrapMode::NEG_PI_TO_PI) {
        wrap(-Type(M_PI), Type(M_PI));
    } else if(Mode == WrapMode::ZERO_TO_TWO_PI) {
        wrap(Type(0), Type(2) * Type(M_PI));
    }
}

template<WrapMode Mode, typename Type>
void Angle<Mode, Type>::wrap(const Type& lowBound, const Type& highBound) {
    if(lowBound <= rad && rad < highBound) {
        return;
    }

    const Type range = (highBound - lowBound);
    const Type num_wraps = ::floor((rad - lowBound) / range);
    rad -= num_wraps * range;
}

}; // namespace tinyso3