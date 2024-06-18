#include <tinyso3/RotationMatrix.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace tinyso3;

TEST_CASE("RotationMatrix") {
    SECTION("Constructors") {
        RotationMatrix<float> m1{1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
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

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                REQUIRE_THAT(x_active(i, j), Catch::Matchers::WithinRel(x_passive_transpose(i, j), 1e-6f));
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
    }
}