/**
 * @file SquareMatrix_impl.hpp
 * 
 * A template based minimal square matrix.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

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
