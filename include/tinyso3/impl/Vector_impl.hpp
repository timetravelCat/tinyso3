/**
 * @file Vector_impl.hpp
 * 
 * A template based minimal vector.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

template<size_t M, typename Type>
Vector<M, Type>::Vector(const Type data_[M]) {
    for(size_t i = 0; i < M; i++) {
        data[i][0] = data_[i];
    }
}

template<size_t M, typename Type>
Vector<M, Type>::Vector(const Matrix<M, 1, Type>& v) :
Matrix<M, 1, Type>(v) {}

template<size_t M, typename Type>
const Type& Vector<M, Type>::operator()(size_t i) const {
    assert(i < M);
    return data[i][0];
}

template<size_t M, typename Type>
Type& Vector<M, Type>::operator()(size_t i) {
    assert(i < M);
    return data[i][0];
}

template<size_t M, typename Type>
Type Vector<M, Type>::dot(const Matrix<M, 1, Type>& v) const {
    Type result = Type(0);
    for(size_t i = 0; i < M; i++) {
        result += data[i][0] * v.data[i][0];
    }
    return result;
}

template<size_t M, typename Type>
Type Vector<M, Type>::norm() const {
    return sqrt(dot(*this));
}

template<size_t M, typename Type>
Type Vector<M, Type>::squaredNorm() const {
    return dot(*this);
}

template<size_t M, typename Type>
inline void Vector<M, Type>::normalize() {
    (*this) /= norm();
}

template<size_t M, typename Type>
Vector<M, Type> Vector<M, Type>::unit() const {
    return (*this) / norm();
}