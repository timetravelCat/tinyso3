#include <tinyso3/SquareMatrix.hpp>
#include <tinyso3/Vector3.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace tinyso3;

TEST_CASE("SquareMatrix") {
    SECTION("Constructors") {
        Matrix<3, 3, float> m1{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
        SquareMatrix<3, float> m2(m1);

        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 3; j++) {
                REQUIRE(m1(i, j) == m2(i, j));
            }
        }
    }

    SECTION("Group Operations") {
        Matrix<3, 3, float> m{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
        SquareMatrix<3, float> sm{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
        REQUIRE_FALSE(is_same<decltype(sm), decltype(m)>::value);
        REQUIRE(is_same<decltype(sm), decltype(sm + 1.0f)>::value);
        REQUIRE(is_same<decltype(sm), decltype(sm - 1.0f)>::value);
        REQUIRE(is_same<decltype(sm), decltype(sm * 1.0f)>::value);
        REQUIRE(is_same<decltype(sm), decltype(-sm)>::value);
        REQUIRE(is_same<decltype(sm), decltype(1.0f + sm)>::value);
        REQUIRE(is_same<decltype(sm), decltype(1.0f - sm)>::value);
        REQUIRE(is_same<decltype(sm), decltype(1.0f * sm)>::value);
        REQUIRE(is_same<decltype(sm), decltype(sm + sm)>::value);
        REQUIRE(is_same<SquareMatrix<3, float>, decltype(sm - sm)>::value);
        REQUIRE(is_same<SquareMatrix<3, float>, decltype(sm * sm)>::value);

        REQUIRE(is_same<SquareMatrix<3, float>, decltype(SquareMatrix<3, float>::Identity())>::value);
        REQUIRE(is_same<SquareMatrix<3, float>, decltype(SquareMatrix<3, float>::Null())>::value);
        REQUIRE(is_same<SquareMatrix<3, float>, decltype(SquareMatrix<3, float>::NaN())>::value);
    }

    SECTION("Diagonal vector") {
        SquareMatrix<3, float> m1{1.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 3.0f};
        Vector<3, float> v = m1.diag();

        REQUIRE(v(0) == 1.0f);
        REQUIRE(v(1) == 2.0f);
        REQUIRE(v(2) == 3.0f);
    }

    SECTION("Trace") {
        SquareMatrix<3, int> m1{1, 0, 0, 0, 2, 0, 0, 0, 3};
        REQUIRE(m1.trace() == 6);
    }

    SECTION("Determinant and Inverse") {
        SquareMatrix<1, float> m1{2.0f};
        REQUIRE(m1.determinant() == 2.0f);
        REQUIRE(m1.inverse()(0, 0) == (1.0f / 2.0f));

        SquareMatrix<2, float> m2{1.0f, 2.0f, 3.0f, 4.0f};
        SquareMatrix<2, float> m2_inv = m2.inverse();
        REQUIRE_THAT(m2.determinant(), Catch::Matchers::WithinRel(-2.0f, 1e-6f));
        REQUIRE_THAT(m2_inv.determinant(), Catch::Matchers::WithinRel(-0.5f, 1e-6f));
        REQUIRE_THAT(m2_inv(0, 0), Catch::Matchers::WithinRel(-2.0f, 1e-6f));
        REQUIRE_THAT(m2_inv(0, 1), Catch::Matchers::WithinRel(1.0f, 1e-6f));
        REQUIRE_THAT(m2_inv(1, 0), Catch::Matchers::WithinRel(1.5f, 1e-6f));
        REQUIRE_THAT(m2_inv(1, 1), Catch::Matchers::WithinRel(-0.5f, 1e-6f));

        SquareMatrix<3, float> m3{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 9.0f};
        SquareMatrix<3, float> m3_inv = m3.inverse();
        SquareMatrix<3, float> m3_inv_compare{-0.3333333f, -1.6666666f, 1.0f, -1.0f, 4.0f, -2.0f, 1.0f, -2.0f, 1.0f};

        REQUIRE_THAT(m3.determinant(), Catch::Matchers::WithinRel(-3.0f, 1e-6f));
        for(size_t i = 0; i < 3; i++) {
            for(size_t j = 0; j < 3; j++) {
                REQUIRE_THAT(m3_inv(i, j), Catch::Matchers::WithinRel(m3_inv(i, j), 1e-6f));
            }
        }

        // TODO test inverse of 4x4 matrix or larger
    }

    SECTION("Vee") {
        //  0 -3  2
        //  3  0 -1
        // -2  1  0
        SquareMatrix<3, float> m1{0.0f, -3.0f, 2.0f, 3.0f, 0.0f, -1.0f, -2.0f, 1.0f, 0.0f};
        Vector<3, float> v = m1.vee();

        REQUIRE(v(0) == 1.0f);
        REQUIRE(v(1) == 2.0f);
        REQUIRE(v(2) == 3.0f);
    }
}
