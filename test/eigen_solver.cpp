#include <tinyso3/EigenSolver.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace tinyso3;

TEST_CASE("EigenSolver") {
    // Test diagonal matrices
    for(size_t i = 0; i < 5; i++) {
        for(size_t j = 0; j < 3; j++) {
            for(size_t k = 0; k < 2; k++) {
                SquareMatrix<3, float> A;
                A(0, 0) = 1.0f + 0.1f * static_cast<float>(i);
                A(1, 1) = 1.0f - 0.1f * static_cast<float>(j);
                A(2, 2) = 1.0f + 0.1f * static_cast<float>(k);

                const array<EigenPair<float>, 3> R = EigenSolver<float>{}(A);
                REQUIRE_THAT(R[0].first, Catch::Matchers::WithinAbs(1.0 + 0.1 * static_cast<double>(i), 1e-6));
                REQUIRE_THAT(R[1].first, Catch::Matchers::WithinAbs(1.0 - 0.1 * static_cast<double>(j), 1e-6));
                REQUIRE_THAT(R[2].first, Catch::Matchers::WithinAbs(1.0 + 0.1 * static_cast<double>(k), 1e-6));

                REQUIRE_THAT(R[0].second(0), Catch::Matchers::WithinAbs(1.0, 1e-6));
                REQUIRE_THAT(R[0].second(1), Catch::Matchers::WithinAbs(0.0, 1e-6));
                REQUIRE_THAT(R[0].second(2), Catch::Matchers::WithinAbs(0.0, 1e-6));
                REQUIRE_THAT(R[1].second(0), Catch::Matchers::WithinAbs(0.0, 1e-6));
                REQUIRE_THAT(R[1].second(1), Catch::Matchers::WithinAbs(1.0, 1e-6));
                REQUIRE_THAT(R[1].second(2), Catch::Matchers::WithinAbs(0.0, 1e-6));
                REQUIRE_THAT(R[2].second(0), Catch::Matchers::WithinAbs(0.0, 1e-6));
                REQUIRE_THAT(R[2].second(1), Catch::Matchers::WithinAbs(0.0, 1e-6));
                REQUIRE_THAT(R[2].second(2), Catch::Matchers::WithinAbs(1.0, 1e-6));
            }
        }
    }

    SquareMatrix<3, float> A1{2.0f, 0.0f, 0.0f, 0.0f, 4.0f, -1.7f, 0.0f, -1.7f, 1.0f};
    const array<EigenPair<float>, 3> R1 = EigenSolver<float>{}(A1);

    // Check eigen results indirectly (A*v == lambda*v)
    for(size_t i = 0; i < 3; i++) {
        const Vector3<float> v = R1[i].second;
        const Vector3<float> Av = A1 * v;
        const Vector3<float> lambda_v = R1[i].first * v;
        for(size_t j = 0; j < 3; j++) {
            REQUIRE_THAT(Av(j), Catch::Matchers::WithinAbs(double(lambda_v(j)), 1e-6));
        }
    }

    SquareMatrix<3, float> A2{-2.0f, 1.8f, 0.0f, 1.8f, -4.0f, -1.7f, 0.0f, -1.7f, 1.0f};
    const array<EigenPair<float>, 3> R2 = EigenSolver<float>{}(A2);

    // Check eigen results indirectly (A*v == lambda*v)
    for(size_t i = 0; i < 3; i++) {
        const Vector3<float> v = R2[i].second;
        const Vector3<float> Av = A2 * v;
        const Vector3<float> lambda_v = R2[i].first * v;
        for(size_t j = 0; j < 3; j++) {
            REQUIRE_THAT(Av(j), Catch::Matchers::WithinAbs(double(lambda_v(j)), 1e-4));
        }
    }

    SquareMatrix<3, float> A3{-2.0f, 1.8f, 11.0f, 1.8f, -4.0f, -1.7f, 11.0f, -1.7f, 1.0f};
    const array<EigenPair<float>, 3> R3 = EigenSolver<float>{}(A3);

    // Check eigen results indirectly (A*v == lambda*v)
    for(size_t i = 0; i < 3; i++) {
        const Vector3<float> v = R3[i].second;
        const Vector3<float> Av = A3 * v;
        const Vector3<float> lambda_v = R3[i].first * v;
        for(size_t j = 0; j < 3; j++) {
            REQUIRE_THAT(Av(j), Catch::Matchers::WithinAbs(double(lambda_v(j)), 1e-4));
        }
    }
}