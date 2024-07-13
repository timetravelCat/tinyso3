#include <tinyso3/Angle.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace tinyso3;

TEST_CASE("Angle") {
    SECTION("Constructors, Cast and Wrap") {
        Angle<WrapMode::NEG_PI_TO_PI, float> a1{M_PI_2f + 14.0f * M_PIf};
        Angle<WrapMode::NEG_PI_TO_PI, float> a2{a1};
        Angle<WrapMode::NEG_PI_TO_PI, float> a3{-M_PI_2f + 14.0f * M_PIf};
        Angle<WrapMode::NEG_PI_TO_PI, float> a4{M_PI_2f - 14.0f * M_PIf};
        Angle<WrapMode::NEG_PI_TO_PI, float> a5{-M_PI_2f - 14.0f * M_PIf};
        Angle<WrapMode::ZERO_TO_TWO_PI, float> a6{M_PI_2f + 14.0f * M_PIf};
        Angle<WrapMode::ZERO_TO_TWO_PI, float> a7{-M_PI_2f + 14.0f * M_PIf};
        Angle<WrapMode::ZERO_TO_TWO_PI, float> a8{M_PI_2f - 14.0f * M_PIf};
        Angle<WrapMode::ZERO_TO_TWO_PI, float> a9{-M_PI_2f - 14.0f * M_PIf};

        REQUIRE(float(a1) == float(a2));
        REQUIRE_THAT(float(a1), Catch::Matchers::WithinRel(M_PI_2f, 1e-6f));
        REQUIRE_THAT(float(a3), Catch::Matchers::WithinRel(-M_PI_2f, 1e-6f));
        REQUIRE_THAT(float(a4), Catch::Matchers::WithinRel(M_PI_2f, 1e-6f));
        REQUIRE_THAT(float(a5), Catch::Matchers::WithinRel(-M_PI_2f, 1e-6f));
        REQUIRE_THAT(float(a6), Catch::Matchers::WithinRel(M_PI_2f, 1e-6f));
        REQUIRE_THAT(float(a7), Catch::Matchers::WithinRel(2.0f * M_PIf - M_PI_2f, 1e-6f));
        REQUIRE_THAT(float(a8), Catch::Matchers::WithinRel(M_PI_2f, 1e-6f));
        REQUIRE_THAT(float(a9), Catch::Matchers::WithinRel(2.0f * M_PIf - M_PI_2f, 1e-6f));
    }

    SECTION("Deg") {
        Angle<WrapMode::NEG_PI_TO_PI, float> a{M_PI_2f};
        REQUIRE_THAT(a.deg(), Catch::Matchers::WithinRel(90.0f, 1e-6f));
    }

    SECTION("Arithmetic operators") {
        Angle<WrapMode::NEG_PI_TO_PI, float> a{M_PI_2f};
        Angle<WrapMode::NEG_PI_TO_PI, float> b{M_PI_2f};
        REQUIRE(a == M_PI_2f);
        REQUIRE(b == M_PI_2f);
        REQUIRE(a == b);

        REQUIRE_THAT(float(a + 14.0f * M_PIf), Catch::Matchers::WithinRel(M_PI_2f, 1e-6f));
        REQUIRE_THAT(float(a + Angle<WrapMode::NEG_PI_TO_PI, float>{14.0f * M_PIf}), Catch::Matchers::WithinRel(M_PI_2f, 1e-6f));
        a += 14.0f * M_PIf;
        REQUIRE_THAT(float(a), Catch::Matchers::WithinRel(M_PI_2f, 1e-6f));
        REQUIRE_THAT(float(a - 14.0f * M_PIf), Catch::Matchers::WithinRel(M_PI_2f, 1e-6f));
        REQUIRE_THAT(float(a - Angle<WrapMode::NEG_PI_TO_PI, float>{14.0f * M_PIf}), Catch::Matchers::WithinRel(M_PI_2f, 1e-6f));
        a -= 14.0f * M_PIf;
        REQUIRE_THAT(float(a), Catch::Matchers::WithinRel(M_PI_2f, 1e-6f));
        REQUIRE_THAT(float(a * 1.5f), Catch::Matchers::WithinRel(1.5f * M_PI_2f, 1e-6f));
        a *= 1.5f;
        REQUIRE_THAT(float(a), Catch::Matchers::WithinRel(1.5f * M_PI_2f, 1e-6f));
        REQUIRE_THAT(float(a / 1.5f), Catch::Matchers::WithinRel(M_PI_2f, 1e-6f));
        a /= 1.5f;
        REQUIRE_THAT(float(a), Catch::Matchers::WithinRel(M_PI_2f, 1e-6f));
    }
}