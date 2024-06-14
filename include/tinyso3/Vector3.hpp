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
    Matrix<3, 3, Type> hat() const;
};

template<typename Type>
Vector3<Type>::Vector3(const Vector<3, Type>& other) :
Vector<3, Type>(other) {}

template<typename Type>
Vector3<Type> Vector3<Type>::cross(const Vector3& v) const {
    return Vector3(
      data[1][0] * v(2) - data[2][0] * v(1),
      data[2][0] * v(0) - data[0][0] * v(2),
      data[0][0] * v(1) - data[1][0] * v(0));
}

template<typename Type>
Vector3<Type> Vector3<Type>::operator%(const Vector3& v) const {
    return cross(v);
}

template<typename Type>
Matrix<3, 3, Type> Vector3<Type>::hat() const {
    return Matrix<3, 3, Type>{Type(0), -data[2][0], data[1][0], data[2][0], Type(0), -data[0][0], -data[1][0], data[0][0], Type(0)};
}
}; // namespace tinyso3