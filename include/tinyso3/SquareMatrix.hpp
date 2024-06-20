/**
 * @file SquareMatrix.hpp
 * 
 * A template based minimal square matrix.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

#include "tiny_type_traits.hpp"
#include "Vector3.hpp"

namespace tinyso3 {
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
    inline Type Det() const;
    SquareMatrix<M, Type> inverse() const;
    inline SquareMatrix<M, Type> Inv() const;

    /**
     * vee operation, enabled only for 3x3 matrix.
     */
    template<typename _Type = Type, typename R = enable_if_t<M == 3, Vector3<_Type>>>
    inline R vee() const {
        return R{-data[1][2], data[0][2], -data[0][1]};
    }

private:
    template<typename _Type>
    friend class RotationMatrix;
};

template<size_t M, typename Type>
SquareMatrix<M, Type>::SquareMatrix(const Matrix<M, M, Type>& other) :
Matrix<M, M, Type>(other) {}

template<size_t M, typename Type>
Vector<M, Type> SquareMatrix<M, Type>::diag() const {
    Vector<M, Type> result;
    for(size_t i = 0; i < M; i++) {
        result(i) = data[i][i];
    }
    return result;
}

template<size_t M, typename Type>
Vector<M, Type> SquareMatrix<M, Type>::D() const {
    return diag();
}

template<size_t M, typename Type>
Type SquareMatrix<M, Type>::trace() const {
    Type result = Type(0);
    for(size_t i = 0; i < M; i++) {
        result += data[i][i];
    }
    return result;
}

template<size_t M, typename Type>
Type SquareMatrix<M, Type>::Tr() const {
    return trace();
}

template<size_t M, typename Type>
Type SquareMatrix<M, Type>::determinant() const {
    Type result = NAN;
    if(M == 1) {
        result = data[0][0];
    } else if(M == 2) {
        result = data[0][0] * data[1][1] - data[0][1] * data[1][0];
    } else if(M == 3) {
        result = data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) -
                 data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
                 data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
    } else {
        assert(false); // Not implemented yet.
    }

    return result;
}

template<size_t M, typename Type>
Type SquareMatrix<M, Type>::Det() const {
    return determinant();
}

template<size_t M, typename Type>
SquareMatrix<M, Type> SquareMatrix<M, Type>::inverse() const {
    SquareMatrix<M, Type> result;
    const Type det = determinant();
    if(M == 1) {
        result(0, 0) = Type(1);
    } else if(M == 2) {
        result(0, 0) = data[1][1];
        result(0, 1) = -data[0][1];
        result(1, 0) = -data[1][0];
        result(1, 1) = data[0][0];
    } else if(M == 3) {
        result(0, 0) = (data[1][1] * data[2][2] - data[1][2] * data[2][1]);
        result(0, 1) = (data[0][2] * data[2][1] - data[0][1] * data[2][2]);
        result(0, 2) = (data[0][1] * data[1][2] - data[0][2] * data[1][1]);
        result(1, 0) = (data[1][2] * data[2][0] - data[1][0] * data[2][2]);
        result(1, 1) = (data[0][0] * data[2][2] - data[0][2] * data[2][0]);
        result(1, 2) = (data[0][2] * data[1][0] - data[0][0] * data[1][2]);
        result(2, 0) = (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
        result(2, 1) = (data[0][1] * data[2][0] - data[0][0] * data[2][1]);
        result(2, 2) = (data[0][0] * data[1][1] - data[0][1] * data[1][0]);
    } else {
        assert(false); // Not implemented yet.
    }

    if(!::isfinite(det)) {
        return SquareMatrix<M, Type>::NaN();
    }

    return result / det;
}

template<size_t M, typename Type>
SquareMatrix<M, Type> SquareMatrix<M, Type>::Inv() const {
    return inverse();
}

} // namespace tinyso3