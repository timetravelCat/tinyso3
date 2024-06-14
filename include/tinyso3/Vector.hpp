/**
 * @file Vector.hpp
 * 
 * A template based minimal vector.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

#include "Matrix.hpp"

namespace tinyso3 {
template<size_t M, typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
class Vector : public Matrix<M, 1, Type> {
protected:
    using Matrix<M, 1, Type>::data;

public:
    /**
     * Constructors
     */
    using Matrix<M, 1, Type>::Matrix;

    Vector(const Type data_[M]);
    Vector(const Matrix<M, 1, Type>& v);

    /**
     * Accessors
     */
    using Matrix<M, 1, Type>::operator();

    inline const Type& operator()(size_t i) const;
    inline Type& operator()(size_t i);

    /**
     * Dot product
     */
    Type dot(const Matrix<M, 1, Type>& v) const;

    /**
     * Norms
     */
    inline Type norm() const;
    inline Type squaredNorm() const;
    inline void normalize();
    inline Vector<M, Type> unit() const;
};

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
    return ::sqrt(dot(*this));
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

} // namespace tinyso3