#include <tinyso3/tiny_utility.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace tinyso3;

TEST_CASE("tiny_utility") {
    SECTION("pair") {
        pair<int, float> p1;
        REQUIRE(p1.first == 0);
        REQUIRE(p1.second == 0.0f);

        pair<int, float> p2{1, 2.0f};
        REQUIRE(p2.first == 1);
        REQUIRE(p2.second == 2.0f);

        pair<int, float> p3 = p2;
        REQUIRE(p3.first == 1);
        REQUIRE(p3.second == 2.0f);

        p3 = p1;
        REQUIRE(p3.first == 0);
        REQUIRE(p3.second == 0.0f);

        p3 = make_pair(3, 4.0f);
        REQUIRE(p3.first == 3);
        REQUIRE(p3.second == 4.0f);
    }

    SECTION("array") {
        array<int, 3> a1;
        REQUIRE(a1.size() == 3);

        REQUIRE(a1.data[0] == 0);
        REQUIRE(a1.data[1] == 0);
        REQUIRE(a1.data[2] == 0);

        array<int, 3> a2{1, 2, 3};
        REQUIRE(a2.data[0] == 1);
        REQUIRE(a2.data[1] == 2);
        REQUIRE(a2.data[2] == 3);

        REQUIRE(a2.data[0] == a2[0]);
        REQUIRE(a2.data[1] == a2[1]);
        REQUIRE(a2.data[2] == a2[2]);

        array<int, 3> a3 = a2;
        REQUIRE(a3.data[0] == 1);
        REQUIRE(a3.data[1] == 2);
        REQUIRE(a3.data[2] == 3);

        a3 = a1;
        REQUIRE(a3.data[0] == 0);
        REQUIRE(a3.data[1] == 0);
        REQUIRE(a3.data[2] == 0);
    }
}
