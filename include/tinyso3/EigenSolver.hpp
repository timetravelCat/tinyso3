/**
 * @file EigenSolver.hpp
 * 
 * A template based minimal eigen solver, for 3x3 real symmetric matrices.
 * 
 * @author timetravelCat <timetraveler930@gmail.com>
 */

#pragma once

#include "tiny_utility.hpp"
#include "tiny_math.hpp"
#include "SquareMatrix.hpp"
#include "Vector3.hpp"

namespace tinyso3 {
/**
 * @class EigenSolver
 * 
 * Computes eigenvalue and eigenvectors for 3x3 real symmetric matrices.
 * Based on https://www.geometrictools.com/Documentation/RobustEigenSymmetric3x3.pdf
 * Implements only non-iterative version.
 */
template<typename Type>
using EigenPair = pair<Type, Vector3<Type>>;

template<typename Type = TINYSO3_DEFAULT_FLOATING_POINT_TYPE>
class EigenSolver {
public:
    /**
     * @brief Computes eigenvalues and eigenvectors for 3x3 real symmetric matrices.
     */
    array<EigenPair<Type>, 3> operator()(SquareMatrix<3, Type> A) const {
        array<EigenPair<Type>, 3> eigenpairs;

        const Type max0 = fmax(fabs(A(0, 0)), fabs(A(0, 1)));
        const Type max1 = fmax(fabs(A(0, 2)), fabs(A(1, 1)));
        const Type max2 = fmax(fabs(A(1, 2)), fabs(A(2, 2)));
        const Type maxAbsElement = fmax(fmax(max0, max1), max2);

        if(maxAbsElement == Type(0)) {
            // A is the zero matrix.
            eigenpairs[0] = EigenPair<Type>{Type(0), Vector3<Type>{Type(1), Type(0), Type(0)}};
            eigenpairs[1] = EigenPair<Type>{Type(0), Vector3<Type>{Type(0), Type(1), Type(0)}};
            eigenpairs[2] = EigenPair<Type>{Type(0), Vector3<Type>{Type(0), Type(0), Type(1)}};
            return eigenpairs;
        }

        const Type invMaxAbsElement = Type(1) / maxAbsElement;
        A(0, 0) *= invMaxAbsElement;
        A(0, 1) *= invMaxAbsElement;
        A(0, 2) *= invMaxAbsElement;
        A(1, 1) *= invMaxAbsElement;
        A(1, 2) *= invMaxAbsElement;
        A(2, 2) *= invMaxAbsElement;

        const Type norm = A(0, 1) * A(0, 1) + A(0, 2) * A(0, 2) + A(1, 2) * A(1, 2);
        if(norm > Type(0)) {
            const Type q = (A(0, 0) + A(1, 1) + A(2, 2)) / Type(3);
            const Type b00 = A(0, 0) - q;
            const Type b11 = A(1, 1) - q;
            const Type b22 = A(2, 2) - q;
            Type p = sqrt((b00 * b00 + b11 * b11 + b22 * b22 + norm * Type(2)) / Type(6));
            const Type c00 = b11 * b22 - A(1, 2) * A(1, 2);
            const Type c01 = A(0, 1) * b22 - A(1, 2) * A(0, 2);
            const Type c02 = A(0, 1) * A(1, 2) - b11 * A(0, 2);
            const Type det = (b00 * c00 - A(0, 1) * c01 + A(0, 2) * c02) / (p * p * p);
            const Type halfDet = fmin(fmax(det * Type(0.5), Type(-1)), Type(1));

            const Type angle = acos(halfDet) / Type(3);
            const Type twoThirdsPi = Type(2.09439510239319549);
            const Type beta2 = cos(angle) * Type(2);
            const Type beta0 = cos(angle + twoThirdsPi) * Type(2);
            const Type beta1 = -(beta0 + beta2);

            eigenpairs[0].first = q + p * beta0;
            eigenpairs[1].first = q + p * beta1;
            eigenpairs[2].first = q + p * beta2;

            if(halfDet >= Type(0)) {
                eigenpairs[2].second = computeEigenVector0(A, eigenpairs[2].first);
                eigenpairs[1].second = computeEigenVector1(A, EigenPair<Type>{eigenpairs[1].first, eigenpairs[2].second});
                eigenpairs[0].second = eigenpairs[1].second.cross(eigenpairs[2].second);
            } else {
                eigenpairs[0].second = computeEigenVector0(A, eigenpairs[0].first);
                eigenpairs[1].second = computeEigenVector1(A, EigenPair<Type>{eigenpairs[1].first, eigenpairs[0].second});
                eigenpairs[2].second = eigenpairs[0].second.cross(eigenpairs[1].second);
            }
        } else {
            // The matrix is diagonal.
            eigenpairs[0] = EigenPair<Type>{A(0, 0), Vector3<Type>{Type(1), Type(0), Type(0)}};
            eigenpairs[1] = EigenPair<Type>{A(1, 1), Vector3<Type>{Type(0), Type(1), Type(0)}};
            eigenpairs[2] = EigenPair<Type>{A(2, 2), Vector3<Type>{Type(0), Type(0), Type(1)}};
        }
        eigenpairs[0].first *= maxAbsElement;
        eigenpairs[1].first *= maxAbsElement;
        eigenpairs[2].first *= maxAbsElement;

        return eigenpairs;
    }

private:
    static pair<Vector3<Type>, Vector3<Type>> computeOrthogonalComplement(const Vector3<Type>& W) {
        Vector3<Type> U;
        if(fabs(W(0)) > fabs(W(1))) {
            Type invLength = Type(1) / sqrt(W(0) * W(0) + W(2) * W(2));
            U = {-W(2) * invLength, Type(0), +W(0) * invLength};
        } else {
            Type invLength = Type(1) / sqrt(W(1) * W(1) + W(2) * W(2));
            U = {Type(0), +W(2) * invLength, -W(1) * invLength};
        }

        return make_pair(U, W.cross(U));
    }
    static Vector3<Type> computeEigenVector0(const SquareMatrix<3, Type>& A, const Type& eigenvalue) {
        const Vector3<Type> row0{A(0, 0) - eigenvalue, A(0, 1), A(0, 2)};
        const Vector3<Type> row1{A(0, 1), A(1, 1) - eigenvalue, A(1, 2)};
        const Vector3<Type> row2{A(0, 2), A(1, 2), A(2, 2) - eigenvalue};
        const Vector3<Type> r0xr1 = row0.cross(row1);
        const Vector3<Type> r0xr2 = row0.cross(row2);
        const Vector3<Type> r1xr2 = row1.cross(row2);

        const Type d0 = r0xr1.dot(r0xr1);
        const Type d1 = r0xr2.dot(r0xr2);
        const Type d2 = r1xr2.dot(r1xr2);

        if(d0 > d1 && d0 > d2) {
            return r0xr1 / sqrt(d0);
        } else if(d1 > d2) {
            return r0xr2 / sqrt(d1);
        } else {
            return r1xr2 / sqrt(d2);
        }
    }
    static Vector3<Type> computeEigenVector1(const SquareMatrix<3, Type>& A, const EigenPair<Type>& eigenpair) {
        const pair<Vector3<Type>, Vector3<Type>> UV = computeOrthogonalComplement(eigenpair.second);
        const Vector3<Type>& U = UV.first;
        const Vector3<Type>& V = UV.second;

        const Vector3<Type> AU{
          A(0, 0) * U(0) + A(0, 1) * U(1) + A(0, 2) * U(2),
          A(0, 1) * U(0) + A(1, 1) * U(1) + A(1, 2) * U(2),
          A(0, 2) * U(0) + A(1, 2) * U(1) + A(2, 2) * U(2)};

        const Vector3<Type> AV{
          A(0, 0) * V(0) + A(0, 1) * V(1) + A(0, 2) * V(2),
          A(0, 1) * V(0) + A(1, 1) * V(1) + A(1, 2) * V(2),
          A(0, 2) * V(0) + A(1, 2) * V(1) + A(2, 2) * V(2)};

        Type m00 = U(0) * AU(0) + U(1) * AU(1) + U(2) * AU(2) - eigenpair.first;
        Type m01 = U(0) * AV(0) + U(1) * AV(1) + U(2) * AV(2);
        Type m11 = V(0) * AV(0) + V(1) * AV(1) + V(2) * AV(2) - eigenpair.first;

        const Type absM00 = fabs(m00);
        const Type absM01 = fabs(m01);
        const Type absM11 = fabs(m11);
        Type maxAbsComp;
        if(absM00 >= absM11) {
            maxAbsComp = fmax(absM00, absM01);
            if(maxAbsComp > Type(0)) {
                if(absM00 >= absM01) {
                    m01 /= m00;
                    m00 = Type(1) / sqrt(Type(1) + m01 * m01);
                    m01 *= m00;
                } else {
                    m00 /= m01;
                    m01 = Type(1) / sqrt(Type(1) + m00 * m00);
                    m00 *= m01;
                }

                return m01 * U - m00 * V;
            } else {
                return U;
            }
        } else {
            maxAbsComp = fmax(absM11, absM01);
            if(maxAbsComp > Type(0)) {
                if(absM11 >= absM01) {
                    m01 /= m11;
                    m11 = Type(1) / sqrt(Type(1) + m01 * m01);
                    m01 *= m11;
                } else {
                    m11 /= m01;
                    m01 = Type(1) / sqrt(Type(1) + m11 * m11);
                    m11 *= m01;
                }

                return m11 * U - m01 * V;
            } else {
                return U;
            }
        }
    };
};
}; // namespace tinyso3