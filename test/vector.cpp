#include <tinyso3/Vector.hpp>
#include <tinyso3/tiny_type_traits.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace tinyso3;

TEST_CASE("Vector") {
    SECTION("Constructors") {
        const float data[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        Vector<5, float> v1{1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        Vector<5, float> v2(data);

        for(size_t i = 0; i < 5; i++) {
            REQUIRE(v1(i, 0) == v2(i, 0));
        }

        Matrix<5, 1, float> v3{-1.0f, -2.0f, -3.0f, -4.0f, -5.0f};
        v2 = v3;
        for(size_t i = 0; i < 5; i++) {
            REQUIRE(v2(i, 0) == v3(i, 0));
        }
    }

    SECTION("Group Operations") {
        Vector<3, float> v1{1.0f, 2.0f, 3.0f};
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

    SECTION("Accessors") {
        const float data[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
        Vector<5, float> v{data};

        for(size_t i = 0; i < 5; i++) {
            REQUIRE(data[i] == v(i));
            v(i) = data[i];
            REQUIRE(data[i] == v(i));
        }
    }

    SECTION("Dot product") {
        const int data1[5] = {1, 2, 3, 4, 5};
        const int data2[5] = {2, 3, 4, 5, 6};
        Vector<5, int> v1{data1};
        Matrix<5, 1, int> v2{data2};

        REQUIRE(v1.dot(v2) == 70);
    }

    SECTION("Norm") {
        const float data[3] = {0.0f, 1.0f, 2.0f};
        Vector<3, float> v{data};

        REQUIRE_THAT(v.norm(), Catch::Matchers::WithinRel(2.23606797749979f, 1e-6f));
        REQUIRE_THAT(v.squaredNorm(), Catch::Matchers::WithinRel(5.0f, 1e-6f));

        Vector<3, float> v2 = v.unit();
        REQUIRE_THAT(v2(0), Catch::Matchers::WithinRel(0.0f, 1e-6f));
        REQUIRE_THAT(v2(1), Catch::Matchers::WithinRel(0.4472135954999579f, 1e-6f));
        REQUIRE_THAT(v2(2), Catch::Matchers::WithinRel(0.8944271909999159f, 1e-6f));

        v.normalize();

        for(size_t i = 0; i < 3; i++) {
            REQUIRE(v(i) == v2(i));
        }
    }
}