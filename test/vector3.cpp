#include <tinyso3/Vector3.hpp>
#include <tinyso3/SquareMatrix.hpp>
#include <tinyso3/tiny_type_traits.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace tinyso3;

TEST_CASE("Vector") {
    SECTION("Constructors") {
        const float data[3] = {1.0f, 2.0f, 3.0f};
        Matrix<3, 1, float> v0{data};
        Vector<3, float> v1{data};
        Vector3<float> v2{v0};
        Vector3<float> v3{v1};

        for(size_t i = 0; i < 3; i++) {
            REQUIRE(v0(i, 0) == v1(i));
            REQUIRE(v0(i, 0) == v2(i));
            REQUIRE(v0(i, 0) == v3(i));
        }
    }

    SECTION("Group Operations") {
        Vector3<float> v1{1.0f, 2.0f, 3.0f};
        REQUIRE(is_same<decltype(v1), decltype(v1 + 1.0f)>::value);
        REQUIRE(is_same<decltype(v1), decltype(v1 - 1.0f)>::value);
        REQUIRE(is_same<decltype(v1), decltype(v1 * 1.0f)>::value);
        REQUIRE(is_same<decltype(v1), decltype(-v1)>::value);
        REQUIRE(is_same<decltype(v1), decltype(1.0f + v1)>::value);
        REQUIRE(is_same<decltype(v1), decltype(1.0f - v1)>::value);
        REQUIRE(is_same<decltype(v1), decltype(1.0f * v1)>::value);
        REQUIRE(is_same<decltype(v1), decltype(v1 + v1)>::value);
        REQUIRE(is_same<decltype(v1), decltype(v1 - v1)>::value);
        REQUIRE(is_same<decltype(v1), decltype(v1 * v1)>::value);
    }

    SECTION("Cross product") {
        Vector3<float> v1{1.0f, 2.0f, 3.0f};
        Matrix<3, 1, float> v2{4.0f, 5.0f, 6.0f};

        Vector3<float> v3 = v1.cross(v2);
        Vector3<float> v4 = v1 % v2;

        REQUIRE_THAT(v3(0), Catch::Matchers::WithinRel(-3.0f, 1e-6f));
        REQUIRE_THAT(v3(1), Catch::Matchers::WithinRel(6.0f, 1e-6f));
        REQUIRE_THAT(v3(2), Catch::Matchers::WithinRel(-3.0f, 1e-6f));
        REQUIRE_THAT(v4(0), Catch::Matchers::WithinRel(-3.0f, 1e-6f));
        REQUIRE_THAT(v4(1), Catch::Matchers::WithinRel(6.0f, 1e-6f));
        REQUIRE_THAT(v4(2), Catch::Matchers::WithinRel(-3.0f, 1e-6f));
    }

    SECTION("Hat operator") {
        Vector3<float> v{1.0f, 2.0f, 3.0f};
        Matrix<3, 3, float> m = v.hat();

        REQUIRE(m(0, 0) == 0.0f);
        REQUIRE(m(0, 1) == -3.0f);
        REQUIRE(m(0, 2) == 2.0f);
        REQUIRE(m(1, 0) == 3.0f);
        REQUIRE(m(1, 1) == 0.0f);
        REQUIRE(m(1, 2) == -1.0f);
        REQUIRE(m(2, 0) == -2.0f);
        REQUIRE(m(2, 1) == 1.0f);
        REQUIRE(m(2, 2) == 0.0f);
    }
}