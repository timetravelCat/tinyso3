/**
 * @file Matrix.hpp
 * 
 * A template based minimal matrix library.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

#include "version.hpp"

#include <stddef.h>
#include <assert.h>
#define _USE_MATH_DEFINES
#include <math.h>

namespace tinyso3 {
template<size_t M, size_t N, typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
class Matrix {
private:
    Type data[M][N]{};

public:
    /**
     * Constructors
     */
    Matrix() = default;
    Matrix(const Type data_[M * N]);
    Matrix(const Type data_[M][N]);
    Matrix(const Matrix& other);
    Matrix(const Type& value); // Fill with a value
    template<typename U, typename V, typename... Args>
    Matrix(const U&, const V&, const Args&... args); // replacement of initializer_list

    /**
     * Assignment
     */
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(const Type& value); // Fill with a value
    template<size_t O, size_t P, size_t Q, size_t R>
    Matrix& setBlock(const Matrix<Q, R, Type>& block);
    template<size_t Q, size_t R>
    Matrix& setBlock(size_t i, size_t j, const Matrix<Q, R, Type>& block);
    template<size_t C>
    Matrix& setCol(const Matrix<M, 1, Type>& col);
    Matrix& setCol(size_t i, const Matrix<M, 1, Type>& col);
    template<size_t R>
    Matrix& setRow(const Matrix<1, N, Type>& row);
    Matrix& setRow(size_t i, const Matrix<1, N, Type>& row);

    /**
     * Constants(Static Methods)
     */
    static Matrix O();   // Zero matrix
    static Matrix I();   // Identity matrix
    static Matrix NaN(); // Not a number matrix

    /**
     * Cast to other type
     */
    template<typename U>
    operator Matrix<M, N, U>() const;
    template<typename U>
    Matrix<M, N, U> cast() const;

    /**
     * Accessors
     */
    inline const Type& operator()(size_t i, size_t j) const;
    inline Type& operator()(size_t i, size_t j);
    template<size_t C>
    inline Matrix<M, 1, Type> col() const;
    inline Matrix<M, 1, Type> col(size_t i) const;
    template<size_t R>
    inline Matrix<1, N, Type> row() const;
    inline Matrix<1, N, Type> row(size_t i) const;

    /**
     * Arithmetic operators by scalar
     */
    Matrix operator+(Type scalar) const;
    void operator+=(Type scalar);
    inline Matrix operator-(Type scalar) const;
    inline void operator-=(Type scalar);
    Matrix operator*(Type scalar) const;
    void operator*=(Type scalar);
    inline Matrix operator/(Type scalar) const;
    inline void operator/=(Type scalar);

    /**
     * Arithmetic operators by matrix
     */
    Matrix operator+(const Matrix& other) const;
    void operator+=(const Matrix& other);
    inline Matrix operator-(const Matrix& other) const;
    inline void operator-=(const Matrix& other);
    template<size_t P>
    Matrix<M, P, Type> operator*(const Matrix<N, P, Type>& other) const;

    /**
     * Transpose
     */
    Matrix<N, M, Type> transpose() const;
    inline Matrix<N, M, Type> T() const;

    /**
     * Slice
     */
    template<size_t O, size_t P, size_t Q, size_t R>
    Matrix<Q, R, Type> slice() const;
    template<size_t Q, size_t R>
    Matrix<Q, R, Type> slice(size_t i, size_t j) const;

    /**
     * Utility functions
     */
    bool isfinite() const; // Check if all elements are finite
    bool isnan() const;    // Check if all elements are NaN
    Type min() const;
    Type max() const;
    Matrix abs() const;
    template<size_t O, size_t P>
    void swapRows();
    void swapRows(size_t i, size_t j);
    template<size_t O, size_t P>
    void swapCols();
    void swapCols(size_t i, size_t j);

private:
    template<size_t _M, size_t _N, typename _Type>
    friend class Matrix;

    template<size_t D, typename U, typename... Args>
    inline void initializer(const U& value, const Args&... args);
    template<size_t D, typename U>
    inline void initializer(const U& value);
};

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type>::Matrix(const Type data_[M * N]) {
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            data[i][j] = data_[N * i + j];
}

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type>::Matrix(const Type data_[M][N]) {
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            data[i][j] = data_[i][j];
}

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type>::Matrix(const Matrix& other) {
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            data[i][j] = other.data[i][j];
}

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type>::Matrix(const Type& value) {
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            data[i][j] = value;
}

template<size_t M, size_t N, typename Type>
template<typename U, typename V, typename... Args>
Matrix<M, N, Type>::Matrix(const U& u, const V& v, const Args&... args) {
    static_assert(sizeof...(args) == M * N - 2, "Invalid number of arguments");

    data[0][0] = u;
    initializer<1, V, Args...>(v, args...);
}

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type>& Matrix<M, N, Type>::operator=(const Matrix& other) {
    if(this != &other) {
        for(size_t i = 0; i < M; i++)
            for(size_t j = 0; j < N; j++)
                data[i][j] = other.data[i][j];
    }

    return *this;
}

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type>& Matrix<M, N, Type>::operator=(const Type& value) {
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            data[i][j] = value;

    return *this;
}

template<size_t M, size_t N, typename Type>
template<size_t O, size_t P, size_t Q, size_t R>
Matrix<M, N, Type>& Matrix<M, N, Type>::setBlock(const Matrix<Q, R, Type>& block) {
    static_assert(O + Q <= M, "Invalid block size");
    static_assert(P + R <= N, "Invalid block size");

    for(size_t i = 0; i < Q; i++)
        for(size_t j = 0; j < R; j++)
            data[O + i][P + j] = block.data[i][j];

    return *this;
}

template<size_t M, size_t N, typename Type>
template<size_t Q, size_t R>
Matrix<M, N, Type>& Matrix<M, N, Type>::setBlock(size_t i, size_t j, const Matrix<Q, R, Type>& block) {
    assert(i + Q <= M);
    assert(j + R <= N);

    for(size_t k = 0; k < Q; k++)
        for(size_t l = 0; l < R; l++)
            data[i + k][j + l] = block.data[k][l];

    return *this;
}

template<size_t M, size_t N, typename Type>
template<size_t C>
Matrix<M, N, Type>& Matrix<M, N, Type>::setCol(const Matrix<M, 1, Type>& col) {
    static_assert(C < N, "Invalid column size");

    for(size_t i = 0; i < M; i++)
        data[i][C] = col.data[i][0];

    return *this;
}

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type>& Matrix<M, N, Type>::setCol(size_t i, const Matrix<M, 1, Type>& col) {
    assert(i < N);

    for(size_t j = 0; j < M; j++)
        data[j][i] = col.data[j][0];

    return *this;
}

template<size_t M, size_t N, typename Type>
template<size_t R>
Matrix<M, N, Type>& Matrix<M, N, Type>::setRow(const Matrix<1, N, Type>& row) {
    static_assert(R < M, "Invalid row size");

    for(size_t i = 0; i < N; i++)
        data[R][i] = row.data[0][i];

    return *this;
}

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type>& Matrix<M, N, Type>::setRow(size_t i, const Matrix<1, N, Type>& row) {
    assert(i < M);

    for(size_t j = 0; j < N; j++)
        data[i][j] = row.data[0][j];

    return *this;
}

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type> Matrix<M, N, Type>::O() {
    return Matrix(Type(0));
}

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type> Matrix<M, N, Type>::NaN() {
    return Matrix(Type(NAN));
}

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type> Matrix<M, N, Type>::I() {
    constexpr size_t MIN = (M < N) ? M : N;
    Matrix result{Type(0)};
    for(size_t i = 0; i < MIN; i++)
        result.data[i][i] = Type(1);
    return result;
}

template<size_t M, size_t N, typename Type>
template<typename U>
Matrix<M, N, Type>::operator Matrix<M, N, U>() const {
    Matrix<M, N, U> result;
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            result.data[i][j] = static_cast<U>(data[i][j]);

    return result;
}

template<size_t M, size_t N, typename Type>
template<typename U>
Matrix<M, N, U> Matrix<M, N, Type>::cast() const {
    return static_cast<Matrix<M, N, U>>(*this);
}

template<size_t M, size_t N, typename Type>
const Type& Matrix<M, N, Type>::operator()(size_t i, size_t j) const {
    assert(i < M);
    assert(j < N);
    return data[i][j];
}

template<size_t M, size_t N, typename Type>
Type& Matrix<M, N, Type>::operator()(size_t i, size_t j) {
    assert(i < M);
    assert(j < N);
    return data[i][j];
}

template<size_t M, size_t N, typename Type>
template<size_t C>
Matrix<M, 1, Type> Matrix<M, N, Type>::col() const {
    return slice<0, C, M, 1>();
}

template<size_t M, size_t N, typename Type>
Matrix<M, 1, Type> Matrix<M, N, Type>::col(size_t i) const {
    return slice<M, 1>(0, i);
}

template<size_t M, size_t N, typename Type>
template<size_t R>
Matrix<1, N, Type> Matrix<M, N, Type>::row() const {
    return slice<R, 0, 1, N>();
}

template<size_t M, size_t N, typename Type>
Matrix<1, N, Type> Matrix<M, N, Type>::row(size_t i) const {
    return slice<1, N>(i, 0);
}

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type> Matrix<M, N, Type>::operator+(Type scalar) const {
    Matrix result;
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            result.data[i][j] = data[i][j] + scalar;
    return result;
}

template<size_t M, size_t N, typename Type>
void Matrix<M, N, Type>::operator+=(Type scalar) {
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            data[i][j] += scalar;
}

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type> Matrix<M, N, Type>::operator-(Type scalar) const {
    return *this + (-scalar);
}

template<size_t M, size_t N, typename Type>
void Matrix<M, N, Type>::operator-=(Type scalar) {
    *this += (-scalar);
}

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type> Matrix<M, N, Type>::operator*(Type scalar) const {
    Matrix result;
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            result.data[i][j] = data[i][j] * scalar;
    return result;
}

template<size_t M, size_t N, typename Type>
void Matrix<M, N, Type>::operator*=(Type scalar) {
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            data[i][j] *= scalar;
}

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type> Matrix<M, N, Type>::operator/(Type scalar) const {
    Matrix result;
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            result.data[i][j] = data[i][j] / scalar;
    return result;
}

template<size_t M, size_t N, typename Type>
void Matrix<M, N, Type>::operator/=(Type scalar) {
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            data[i][j] /= scalar;
}

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type> Matrix<M, N, Type>::operator+(const Matrix& other) const {
    Matrix result;
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            result.data[i][j] = data[i][j] + other.data[i][j];
    return result;
}

template<size_t M, size_t N, typename Type>
void Matrix<M, N, Type>::operator+=(const Matrix& other) {
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            data[i][j] += other.data[i][j];
}

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type> Matrix<M, N, Type>::operator-(const Matrix& other) const {
    Matrix result;
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            result.data[i][j] = data[i][j] - other.data[i][j];
    return result;
}

template<size_t M, size_t N, typename Type>
void Matrix<M, N, Type>::operator-=(const Matrix& other) {
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            data[i][j] -= other.data[i][j];
}

template<size_t M, size_t N, typename Type>
template<size_t P>
Matrix<M, P, Type> Matrix<M, N, Type>::operator*(const Matrix<N, P, Type>& other) const {
    Matrix<M, P, Type> result;
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < P; j++)
            for(size_t k = 0; k < N; k++)
                result.data[i][j] += data[i][k] * other(k, j);
    return result;
}

template<size_t M, size_t N, typename Type>
Matrix<N, M, Type> Matrix<M, N, Type>::transpose() const {
    Matrix<N, M, Type> result;
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            result.data[j][i] = data[i][j];
    return result;
}

template<size_t M, size_t N, typename Type>
Matrix<N, M, Type> Matrix<M, N, Type>::T() const {
    return transpose();
}

template<size_t M, size_t N, typename Type>
template<size_t O, size_t P, size_t Q, size_t R>
Matrix<Q, R, Type> Matrix<M, N, Type>::slice() const {
    static_assert(O + Q <= M, "Invalid slice size");
    static_assert(P + R <= N, "Invalid slice size");

    Matrix<Q, R, Type> result;
    for(size_t i = 0; i < Q; i++)
        for(size_t j = 0; j < R; j++)
            result.data[i][j] = data[O + i][P + j];
    return result;
}

template<size_t M, size_t N, typename Type>
template<size_t Q, size_t R>
Matrix<Q, R, Type> Matrix<M, N, Type>::slice(size_t i, size_t j) const {
    assert(i + Q <= M);
    assert(j + R <= N);

    Matrix<Q, R, Type> result;
    for(size_t k = 0; k < Q; k++)
        for(size_t l = 0; l < R; l++)
            result.data[k][l] = data[i + k][j + l];
    return result;
}

template<size_t M, size_t N, typename Type>
bool Matrix<M, N, Type>::isfinite() const {
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            if(!::isfinite(data[i][j]))
                return false;

    return true;
}

template<size_t M, size_t N, typename Type>
bool Matrix<M, N, Type>::isnan() const {
    bool result = true;

    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            result = result && ::isnan(data[i][j]);

    return result;
}

template<size_t M, size_t N, typename Type>
Type Matrix<M, N, Type>::min() const {
    Type result = data[0][0];
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            result = (data[i][j] < result) ? data[i][j] : result;
    return result;
}

template<size_t M, size_t N, typename Type>
Type Matrix<M, N, Type>::max() const {
    Type result = data[0][0];
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            result = (data[i][j] > result) ? data[i][j] : result;
    return result;
}

template<size_t M, size_t N, typename Type>
Matrix<M, N, Type> Matrix<M, N, Type>::abs() const {
    Matrix<M, N, Type> result;
    for(size_t i = 0; i < M; i++)
        for(size_t j = 0; j < N; j++)
            result.data[i][j] = ::abs(data[i][j]);
    return result;
}

template<size_t M, size_t N, typename Type>
template<size_t O, size_t P>
void Matrix<M, N, Type>::swapRows() {
    static_assert(O < M, "Invalid row size");
    static_assert(P < M, "Invalid row size");

    if(O == P)
        return;

    for(size_t i = 0; i < N; i++) {
        const Type temp = data[O][i];
        data[O][i] = data[P][i];
        data[P][i] = temp;
    }
}

template<size_t M, size_t N, typename Type>
void Matrix<M, N, Type>::swapRows(size_t i, size_t j) {
    assert(i < M);
    assert(j < M);

    if(i == j)
        return;

    for(size_t k = 0; k < N; k++) {
        const Type temp = data[i][k];
        data[i][k] = data[j][k];
        data[j][k] = temp;
    }
}

template<size_t M, size_t N, typename Type>
template<size_t O, size_t P>
void Matrix<M, N, Type>::swapCols() {
    static_assert(O < N, "Invalid column size");
    static_assert(P < N, "Invalid column size");

    if(O == P)
        return;

    for(size_t i = 0; i < M; i++) {
        const Type temp = data[i][O];
        data[i][O] = data[i][P];
        data[i][P] = temp;
    }
}

template<size_t M, size_t N, typename Type>
void Matrix<M, N, Type>::swapCols(size_t i, size_t j) {
    assert(i < N);
    assert(j < N);

    if(i == j)
        return;

    for(size_t k = 0; k < M; k++) {
        const Type temp = data[k][i];
        data[k][i] = data[k][j];
        data[k][j] = temp;
    }
}

template<size_t M, size_t N, typename Type>
template<size_t D, typename U, typename... Args>
void Matrix<M, N, Type>::initializer(const U& value, const Args&... args) {
    data[D / N][D % N] = value;
    initializer<D + 1, Args...>(args...);
}

template<size_t M, size_t N, typename Type>
template<size_t D, typename U>
void Matrix<M, N, Type>::initializer(const U& value) {
    data[M - 1][N - 1] = value;
}
}; // namespace tinyso3