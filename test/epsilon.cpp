#include <tinyso3/epsilon.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <math.h>

using namespace tinyso3;

TEST_CASE("Epsilon") {
    constexpr float flt_eps = epsilon<float>();
    constexpr double dbl_eps = epsilon<double>();
    constexpr long double ldbl_eps = epsilon<long double>();

    for(int i = 0; i <= 20; i++) {
        if(i == CONFIG_DEFAULT_FLOATING_POINT_PRECISION_32_EPSILON) {
            REQUIRE_THAT(flt_eps, Catch::Matchers::WithinRel(::pow(static_cast<float>(10), static_cast<float>(-i)), 1e-6f));
        }

        if(i == CONFIG_DEFAULT_FLOATING_POINT_PRECISION_64_EPSILON) {
            REQUIRE_THAT(dbl_eps, Catch::Matchers::WithinRel(::pow(static_cast<double>(10), static_cast<double>(-i)), 1e-12));
        }

        if(i == CONFIG_DEFAULT_FLOATING_POINT_PRECISION_128_EPSILON) {
            REQUIRE_THAT(ldbl_eps, Catch::Matchers::WithinRel(::pow(static_cast<long double>(10), static_cast<long double>(-i)), 1e-12));
        }
    }
};