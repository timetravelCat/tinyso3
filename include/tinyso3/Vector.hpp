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
     * Vector Group Operations
     */
    using Matrix<M, 1, Type>::operator+;
    inline Vector operator+(Type scalar) const { return Matrix<M, 1, Type>::operator+(scalar); };
    using Matrix<M, 1, Type>::operator-;
    inline Vector operator-(Type scalar) const { return Matrix<M, 1, Type>::operator-(scalar); };
    using Matrix<M, 1, Type>::operator*;
    inline Vector operator*(Type scalar) const { return Matrix<M, 1, Type>::operator*(scalar); };
    using Matrix<M, 1, Type>::operator/;
    inline Vector operator/(Type scalar) const { return Matrix<M, 1, Type>::operator/(scalar); };
    inline Vector operator-() const { return Matrix<M, 1, Type>::operator-(); };

    inline friend Vector operator+(Type lhs, const Vector& rhs) { return rhs + lhs; }
    inline friend Vector operator-(Type lhs, const Vector& rhs) { return -rhs + lhs; };
    inline friend Vector operator*(Type lhs, const Vector& rhs) { return rhs * lhs; };
    inline Vector operator+(const Vector& other) const { return Matrix<M, 1, Type>::operator+(other); };
    inline Vector operator-(const Vector& other) const { return Matrix<M, 1, Type>::operator-(other); };
    inline Vector operator*(const Vector& other) const { return Matrix<M, 1, Type>::operator*(other); };

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

#include "impl/Vector_impl.hpp"
} // namespace tinyso3