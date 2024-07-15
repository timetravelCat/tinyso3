/**
 * @file Matrix.hpp
 * 
 * A template based minimal matrix library.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

#include "version.hpp"
#include "tiny_math.hpp"

#include <stddef.h>
#include <assert.h>

namespace tinyso3 {
template<size_t M, size_t N, typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
class Matrix {
protected:
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
    static Matrix Null();     // Zero matrix
    static Matrix Identity(); // Identity matrix
    static Matrix NaN();      // Not a number matrix

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
    Matrix operator-() const;

    inline friend Matrix operator+(Type lhs, const Matrix& rhs) { return rhs + lhs; }
    inline friend Matrix operator-(Type lhs, const Matrix& rhs) { return -rhs + lhs; }
    inline friend Matrix operator*(Type lhs, const Matrix& rhs) { return rhs * lhs; }

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

    /**
     * ElementWise operations
     */
    template<typename UnaryOp>
    Matrix<M, N, Type> elementWise(UnaryOp) const;
    template<typename BinaryOp>
    Matrix<M, N, Type> elementWise(const Matrix<M, N, Type>&, BinaryOp) const;

private:
    template<size_t _M, size_t _N, typename _Type>
    friend class Matrix;
    template<size_t _M, typename _Type>
    friend class Vector;

    template<size_t D, typename U, typename... Args>
    inline void initializer(const U& value, const Args&... args);
    template<size_t D, typename U>
    inline void initializer(const U& value);
};

template<size_t M, size_t N>
using Matrixf = Matrix<M, N, float>;
template<size_t M, size_t N>
using Matrixd = Matrix<M, N, double>;
template<size_t M, size_t N>
using Matrixld = Matrix<M, N, long double>;

#include "impl/Matrix_impl.hpp"
}; // namespace tinyso3