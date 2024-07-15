/**
 * @file Angle.hpp
 * 
 * An angle class for 1D angles.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

#include "version.hpp"
#include "tiny_math.hpp"

#include <stddef.h>

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

template<WrapMode Mode = WrapMode::NEG_PI_TO_PI>
using Anglef = Angle<Mode, float>;
template<WrapMode Mode = WrapMode::NEG_PI_TO_PI>
using Angled = Angle<Mode, double>;
template<WrapMode Mode = WrapMode::NEG_PI_TO_PI>
using Angleld = Angle<Mode, long double>;

#include "impl/Angle_impl.hpp"
}; // namespace tinyso3