/**
 * @file Vector.hpp
 * 
 * A template based minimal 3D vector.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

#include "Vector.hpp"

namespace tinyso3 {
template<size_t M, typename Type>
class SquareMatrix;

template<typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
class Vector3 : public Vector<3, Type> {
protected:
    using Vector<3, Type>::data;

public:
    /**
     * Constructors
     */
    using Vector<3, Type>::Vector;

    Vector3(const Vector<3, Type>& other);

    /**
     * Vector3 Group Operations
     */
    using Vector<3, Type>::operator+;
    inline Vector3 operator+(Type scalar) const { return Vector<3, Type>::operator+(scalar); };
    using Vector<3, Type>::operator-;
    inline Vector3 operator-(Type scalar) const { return Vector<3, Type>::operator-(scalar); };
    using Vector<3, Type>::operator*;
    inline Vector3 operator*(Type scalar) const { return Vector<3, Type>::operator*(scalar); };
    using Vector<3, Type>::operator/;
    inline Vector3 operator/(Type scalar) const { return Vector<3, Type>::operator/(scalar); };
    inline Vector3 operator-() const { return Vector<3, Type>::operator-(); };

    inline friend Vector3 operator+(Type lhs, const Vector3& rhs) { return rhs + lhs; }
    inline friend Vector3 operator-(Type lhs, const Vector3& rhs) { return -rhs + lhs; };
    inline friend Vector3 operator*(Type lhs, const Vector3& rhs) { return rhs * lhs; };
    inline Vector3 operator+(const Vector3& other) const { return Vector<3, Type>::operator+(other); };
    inline Vector3 operator-(const Vector3& other) const { return Vector<3, Type>::operator-(other); };
    inline Vector3 operator*(const Vector3& other) const { return Vector<3, Type>::operator*(other); };

    inline Vector3 unit() const { return Vector<3, Type>::unit(); }

    /**
     * Accessors
     */
    using Vector<3, Type>::operator();

    /**
     * Cross product
     */
    Vector3 cross(const Vector3& v) const;
    inline Vector3 operator%(const Vector3& v) const;

    /**
     * Hat operator
     */
    SquareMatrix<3, Type> hat() const;

    inline Type& x() { return data[0][0]; }
    inline Type& y() { return data[1][0]; }
    inline Type& z() { return data[2][0]; }
    inline const Type& x() const { return data[0][0]; }
    inline const Type& y() const { return data[1][0]; }
    inline const Type& z() const { return data[2][0]; }
};

using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;
using Vector3ld = Vector3<long double>;

#include "impl/Vector3_impl.hpp"
}; // namespace tinyso3