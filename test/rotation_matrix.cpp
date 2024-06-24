#include <tinyso3/RotationMatrix.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace tinyso3;

TEST_CASE("RotationMatrix") {
    SECTION("Constructors") {
        RotationMatrix<float> m1{1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
    }

    SECTION("SO3 Group Operations") {
        RotationMatrix<float> m1{1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
        RotationMatrix<float> m2{1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};

        REQUIRE(is_same<RotationMatrix<float>, decltype(m1 * m2)>::value);
        REQUIRE(is_same<RotationMatrix<float>, decltype(m1.transpose())>::value);
        REQUIRE(is_same<RotationMatrix<float>, decltype(m1.T())>::value);
        REQUIRE(is_same<RotationMatrix<float>, decltype(m1.inverse())>::value);

        REQUIRE(is_same<RotationMatrix<float>, decltype(RotationMatrix<float>::Identity())>::value);
        REQUIRE_FALSE(is_same<RotationMatrix<float>, decltype(RotationMatrix<float>::Null())>::value);
        REQUIRE_FALSE(is_same<RotationMatrix<float>, decltype(RotationMatrix<float>::NaN())>::value);
    }

    SECTION("Principal Rotations") {
        const RotationMatrix<float> x_active = RotationMatrix<float>::RotatePrincipalAxis<X, ACTIVE>(M_PIf / 6.0f);
        const RotationMatrix<float> y_active = RotationMatrix<float>::RotatePrincipalAxis<Y, ACTIVE>(M_PIf / 6.0f);
        const RotationMatrix<float> z_active = RotationMatrix<float>::RotatePrincipalAxis<Z, ACTIVE>(M_PIf / 6.0f);

        const RotationMatrix<float> x_passive = RotationMatrix<float>::RotatePrincipalAxis<X, PASSIVE>(M_PIf / 6.0f);
        const RotationMatrix<float> y_passive = RotationMatrix<float>::RotatePrincipalAxis<Y, PASSIVE>(M_PIf / 6.0f);
        const RotationMatrix<float> z_passive = RotationMatrix<float>::RotatePrincipalAxis<Z, PASSIVE>(M_PIf / 6.0f);

        const RotationMatrix<float> x_passive_transpose = x_passive.T();
        const RotationMatrix<float> y_passive_transpose = y_passive.T();
        const RotationMatrix<float> z_passive_transpose = z_passive.T();

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 3; j++) {
                REQUIRE_THAT(x_active(i, j), Catch::Matchers::WithinRel(x_passive_transpose(i, j), 1e-6f));
                REQUIRE_THAT(y_active(i, j), Catch::Matchers::WithinRel(y_passive_transpose(i, j), 1e-6f));
                REQUIRE_THAT(z_active(i, j), Catch::Matchers::WithinRel(z_passive_transpose(i, j), 1e-6f));
            }
        }

        REQUIRE_THAT(x_active(0, 0), Catch::Matchers::WithinRel(1.0f, 1e-6f));
        REQUIRE_THAT(x_active(0, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(x_active(0, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(x_active(1, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(x_active(1, 1), Catch::Matchers::WithinRel(cosf(M_PIf / 6.0f), 1e-6f));
        REQUIRE_THAT(x_active(1, 2), Catch::Matchers::WithinRel(-sinf(M_PIf / 6.0f), 1e-6f));
        REQUIRE_THAT(x_active(2, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(x_active(2, 1), Catch::Matchers::WithinRel(sinf(M_PIf / 6.0f), 1e-6f));
        REQUIRE_THAT(x_active(2, 2), Catch::Matchers::WithinRel(cosf(M_PIf / 6.0f), 1e-6f));

        REQUIRE_THAT(y_active(0, 0), Catch::Matchers::WithinRel(cosf(M_PIf / 6.0f), 1e-6f));
        REQUIRE_THAT(y_active(0, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(y_active(0, 2), Catch::Matchers::WithinRel(sinf(M_PIf / 6.0f), 1e-6f));
        REQUIRE_THAT(y_active(1, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(y_active(1, 1), Catch::Matchers::WithinRel(1.0f, 1e-6f));
        REQUIRE_THAT(y_active(1, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(y_active(2, 0), Catch::Matchers::WithinRel(-sinf(M_PIf / 6.0f), 1e-6f));
        REQUIRE_THAT(y_active(2, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(y_active(2, 2), Catch::Matchers::WithinRel(cosf(M_PIf / 6.0f), 1e-6f));

        REQUIRE_THAT(z_active(0, 0), Catch::Matchers::WithinRel(cosf(M_PIf / 6.0f), 1e-6f));
        REQUIRE_THAT(z_active(0, 1), Catch::Matchers::WithinRel(-sinf(M_PIf / 6.0f), 1e-6f));
        REQUIRE_THAT(z_active(0, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(z_active(1, 0), Catch::Matchers::WithinRel(sinf(M_PIf / 6.0f), 1e-6f));
        REQUIRE_THAT(z_active(1, 1), Catch::Matchers::WithinRel(cosf(M_PIf / 6.0f), 1e-6f));
        REQUIRE_THAT(z_active(1, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(z_active(2, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(z_active(2, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(z_active(2, 2), Catch::Matchers::WithinRel(1.0f, 1e-6f));
    }

    SECTION("Normalize") {
        /**
         * Assume we have a matrix, with row 
         * {1.0f, 1.0f, 0.0f}
         * {0.0f, 1.0f, 0.0f}
         * {0.0f, 0.0f, 1.0f}
         * 
         * After normalization, the matrix should be orthonomal.
         * 
         * {0.894427 0.447214 0.000000}
         * {-0.447213 0.894427 0.000000}
         * {0.000000 0.000000 1.000000}
         * 
         * Which is the closest to the original matrix.
         */
        RotationMatrix<float> m{1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
        m.normalize();

        Vector3<float> col0 = m.col<0>();
        Vector3<float> col1 = m.col<1>();
        Vector3<float> col2 = m.col<2>();

        REQUIRE_THAT(col0.squaredNorm(), Catch::Matchers::WithinRel(1.0, 1e-4));
        REQUIRE_THAT(col1.squaredNorm(), Catch::Matchers::WithinRel(1.0, 1e-4));
        REQUIRE_THAT(col2.squaredNorm(), Catch::Matchers::WithinRel(1.0, 1e-4));
        REQUIRE(::fabs(col0.dot(col1)) < 1e-4f);
        REQUIRE(::fabs(col0.dot(col2)) < 1e-4f);
        REQUIRE(::fabs(col1.dot(col2)) < 1e-4f);
        REQUIRE_THAT(m.determinant(), Catch::Matchers::WithinRel(1.0, 1e-4));
    }

    SECTION("log and pow") {
        RotationMatrix<float> m1 = RotationMatrix<float>::Identity();
        SquareMatrix<3, float> m1_log = m1.log();

        // log of identity matrix should be zero matrix.
        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 3; j++) {
                REQUIRE_THAT(m1_log(i, j), Catch::Matchers::WithinRel(0.0f, 1e-6f));
            }
        }

        // pow of identity matrix should be identity matrix.
        RotationMatrix<float> m2 = m1.pow(0.5f);
        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 3; j++) {
                if(i == j) {
                    REQUIRE_THAT(m2(i, j), Catch::Matchers::WithinRel(1.0f, 1e-6f));
                } else {
                    REQUIRE_THAT(m2(i, j), Catch::Matchers::WithinRel(0.0f, 1e-6f));
                }
            }
        }

        const RotationMatrix<float> x_active = RotationMatrix<float>::RotatePrincipalAxis<X, ACTIVE>(M_PIf / 6.0f);
        SquareMatrix<3, float> x_active_log = x_active.log();
        REQUIRE_THAT(x_active_log(0, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(x_active_log(0, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(x_active_log(0, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(x_active_log(1, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(x_active_log(1, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(x_active_log(1, 2), Catch::Matchers::WithinRel(-M_PIf / 6.0f, 1e-6f));
        REQUIRE_THAT(x_active_log(2, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(x_active_log(2, 1), Catch::Matchers::WithinRel(M_PIf / 6.0f, 1e-6f));
        REQUIRE_THAT(x_active_log(2, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));

        const RotationMatrix<float> y_active = RotationMatrix<float>::RotatePrincipalAxis<Y, ACTIVE>(M_PIf / 6.0f);
        SquareMatrix<3, float> y_active_log = y_active.log();
        REQUIRE_THAT(y_active_log(0, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(y_active_log(0, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(y_active_log(0, 2), Catch::Matchers::WithinRel(M_PIf / 6.0f, 1e-6f));
        REQUIRE_THAT(y_active_log(1, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(y_active_log(1, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(y_active_log(1, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(y_active_log(2, 0), Catch::Matchers::WithinRel(-M_PIf / 6.0f, 1e-6f));
        REQUIRE_THAT(y_active_log(2, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(y_active_log(2, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));

        const RotationMatrix<float> z_active = RotationMatrix<float>::RotatePrincipalAxis<Z, ACTIVE>(M_PIf / 6.0f);
        SquareMatrix<3, float> z_active_log = z_active.log();
        REQUIRE_THAT(z_active_log(0, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(z_active_log(0, 1), Catch::Matchers::WithinRel(-M_PIf / 6.0f, 1e-6f));
        REQUIRE_THAT(z_active_log(0, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(z_active_log(1, 0), Catch::Matchers::WithinRel(M_PIf / 6.0f, 1e-6f));
        REQUIRE_THAT(z_active_log(1, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(z_active_log(1, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(z_active_log(2, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(z_active_log(2, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(z_active_log(2, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));

        const RotationMatrix<float> x_active_pow_log = x_active.pow(0.5f).log();
        REQUIRE_THAT(x_active_pow_log(0, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(x_active_pow_log(0, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(x_active_pow_log(0, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(x_active_pow_log(1, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(x_active_pow_log(1, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(x_active_pow_log(1, 2), Catch::Matchers::WithinRel(-M_PIf / 12.0f, 1e-6f));
        REQUIRE_THAT(x_active_pow_log(2, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(x_active_pow_log(2, 1), Catch::Matchers::WithinRel(M_PIf / 12.0f, 1e-6f));
        REQUIRE_THAT(x_active_pow_log(2, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));

        const RotationMatrix<float> y_active_pow_log = y_active.pow(0.5f).log();
        REQUIRE_THAT(y_active_pow_log(0, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(y_active_pow_log(0, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(y_active_pow_log(0, 2), Catch::Matchers::WithinRel(M_PIf / 12.0f, 1e-6f));
        REQUIRE_THAT(y_active_pow_log(1, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(y_active_pow_log(1, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(y_active_pow_log(1, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(y_active_pow_log(2, 0), Catch::Matchers::WithinRel(-M_PIf / 12.0f, 1e-6f));
        REQUIRE_THAT(y_active_pow_log(2, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(y_active_pow_log(2, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));

        const RotationMatrix<float> z_active_pow_log = z_active.pow(0.5f).log();
        REQUIRE_THAT(z_active_pow_log(0, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(z_active_pow_log(0, 1), Catch::Matchers::WithinRel(-M_PIf / 12.0f, 1e-6f));
        REQUIRE_THAT(z_active_pow_log(0, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(z_active_pow_log(1, 0), Catch::Matchers::WithinRel(M_PIf / 12.0f, 1e-6f));
        REQUIRE_THAT(z_active_pow_log(1, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(z_active_pow_log(1, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(z_active_pow_log(2, 0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(z_active_pow_log(2, 1), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(z_active_pow_log(2, 2), Catch::Matchers::WithinRel(0.0f, 1e-6f));
    }

    SECTION("Interpolation") {
        const RotationMatrix<float> x_active_from = RotationMatrix<float>::RotatePrincipalAxis<X, ACTIVE>(M_PIf / 6.0f);
        const RotationMatrix<float> x_active_to = RotationMatrix<float>::RotatePrincipalAxis<X, ACTIVE>(M_PIf / 2.0f);
        const RotationMatrix<float> x_active = RotationMatrix<float>::RotatePrincipalAxis<X, ACTIVE>(M_PIf / 3.0f);
        const RotationMatrix<float> x_active_interpolated = x_active_from.interpolate<ACTIVE>(x_active_to, 0.5f);

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 3; j++) {
                REQUIRE_THAT(x_active(i, j), Catch::Matchers::WithinRel(x_active_interpolated(i, j), 1e-6f));
            }
        }

        const RotationMatrix<float> x_passive_from = RotationMatrix<float>::RotatePrincipalAxis<X, PASSIVE>(M_PIf / 6.0f);
        const RotationMatrix<float> x_passive_to = RotationMatrix<float>::RotatePrincipalAxis<X, PASSIVE>(M_PIf / 2.0f);
        const RotationMatrix<float> x_passive = RotationMatrix<float>::RotatePrincipalAxis<X, PASSIVE>(M_PIf / 3.0f);
        const RotationMatrix<float> x_passive_interpolated = x_passive_from.interpolate<PASSIVE>(x_passive_to, 0.5f);

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 3; j++) {
                REQUIRE_THAT(x_passive(i, j), Catch::Matchers::WithinRel(x_passive_interpolated(i, j), 1e-6f));
            }
        }
    };
}