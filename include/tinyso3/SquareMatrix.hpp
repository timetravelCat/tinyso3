/**
 * @file SquareMatrix.hpp
 * 
 * A template based minimal square matrix.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

#include "Vector.hpp"
#include "tiny_type_traits.hpp"

namespace tinyso3 {
template<typename Type>
class Vector3;

template<size_t M, typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
class SquareMatrix : public Matrix<M, M, Type> {
protected:
    using Matrix<M, M, Type>::data;

public:
    /**
     * Constructors
     */
    using Matrix<M, M, Type>::Matrix;

    SquareMatrix(const Matrix<M, M, Type>& other);

    /**
     * SquareMatrix Group Operations
     */
    using Matrix<M, M, Type>::operator+;
    inline SquareMatrix operator+(Type scalar) const { return Matrix<M, M, Type>::operator+(scalar); };
    using Matrix<M, M, Type>::operator-;
    inline SquareMatrix operator-(Type scalar) const { return Matrix<M, M, Type>::operator-(scalar); };
    using Matrix<M, M, Type>::operator*;
    inline SquareMatrix operator*(Type scalar) const { return Matrix<M, M, Type>::operator*(scalar); };
    using Matrix<M, M, Type>::operator/;
    inline SquareMatrix operator/(Type scalar) const { return Matrix<M, M, Type>::operator/(scalar); };
    inline SquareMatrix operator-() const { return Matrix<M, M, Type>::operator-(); };

    inline friend SquareMatrix operator+(Type lhs, const SquareMatrix& rhs) { return rhs + lhs; }
    inline friend SquareMatrix operator-(Type lhs, const SquareMatrix& rhs) { return -rhs + lhs; };
    inline friend SquareMatrix operator*(Type lhs, const SquareMatrix& rhs) { return rhs * lhs; };
    inline SquareMatrix operator+(const SquareMatrix& other) const { return Matrix<M, M, Type>::operator+(other); };
    inline SquareMatrix operator-(const SquareMatrix& other) const { return Matrix<M, M, Type>::operator-(other); };
    inline SquareMatrix operator*(const SquareMatrix& other) const { return Matrix<M, M, Type>::operator*(other); };

    static inline SquareMatrix Null() { return Matrix<M, M, Type>::Null(); }
    static inline SquareMatrix Identity() { return Matrix<M, M, Type>::Identity(); }
    static inline SquareMatrix NaN() { return Matrix<M, M, Type>::NaN(); }

    /**
     * Accessors
     */
    using Matrix<M, M, Type>::operator();

    /**
     * Diagonal vector
     */
    Vector<M, Type> diag() const;
    inline Vector<M, Type> D() const;

    /**
     * trace
     */
    Type trace() const;
    inline Type Tr() const;

    /**
     * Determinant and Inverse
     */
    Type determinant() const;
    SquareMatrix<M, Type> inverse() const;

    /**
     * vee operation, enabled only for 3x3 matrix.
     */
    template<typename _Type = Type, typename R = enable_if_t<M == 3, Vector3<_Type>>>
    inline R vee() const { return R{-data[1][2], data[0][2], -data[0][1]}; }

private:
    template<typename _Convention, typename _Type>
    friend class RotationMatrix;
};

#include "impl/SquareMatrix_impl.hpp"
} // namespace tinyso3