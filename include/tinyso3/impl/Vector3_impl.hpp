/**
 * @file Vector3_impl.hpp
 * 
 * A template based minimal 3D vector.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

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
SquareMatrix<3, Type> Vector3<Type>::hat() const {
    return SquareMatrix<3, Type>{Type(0), -data[2][0], data[1][0], data[2][0], Type(0), -data[0][0], -data[1][0], data[0][0], Type(0)};
}