#include <tinyso3/AngularVelocity.hpp>
#include <tinyso3/EulerRate.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace tinyso3;

TEST_CASE("AngularVelocity") {
    Euler<INTRINSIC, XYZ, float> euler{0.1f, 0.2f, 0.3f};
    EulerRate<INTRINSIC, XYZ, float> euler_rate{0.4f, 0.5f, 0.6f};
    AngularVelocity<float> angular_velocity{euler, euler_rate};

    SquareMatrix<3, float> EulerRateToAngularVelocity{
      cos(euler(1U)) * cos(euler(2U)),
      sin(euler(2U)),
      float(0),
      -cos(euler(1U)) * sin(euler(2U)),
      cos(euler(2U)),
      float(0),
      sin(euler(1U)),
      float(0),
      float(1)};
    Vector3<float> angular_velocity_comp = EulerRateToAngularVelocity * euler_rate;

    REQUIRE(fabs(angular_velocity(0U) - angular_velocity_comp(0U)) < 1e-4f);
    REQUIRE(fabs(angular_velocity(1U) - angular_velocity_comp(1U)) < 1e-4f);
    REQUIRE(fabs(angular_velocity(2U) - angular_velocity_comp(2U)) < 1e-4f);
}