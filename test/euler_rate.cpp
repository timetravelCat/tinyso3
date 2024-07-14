#include <tinyso3/AngularVelocity.hpp>
#include <tinyso3/EulerRate.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace tinyso3;

TEST_CASE("EulerRate") {
    AngularVelocity<float> angular_velocity{0.4f, 0.5f, 0.6f};
    Euler<INTRINSIC, XYZ, float> euler{0.1f, 0.2f, 0.3f};
    EulerRate<INTRINSIC, XYZ, float> euler_rate{RotationMatrix<PASSIVE, float>{euler}, angular_velocity};

    SquareMatrix<3, float> AngularVelocityToEulerRate{
      cos(euler(2)) / cos(euler(1)),
      -sin(euler(2)) / cos(euler(1)),
      float(0),
      sin(euler(2)),
      cos(euler(2)),
      float(0),
      -tan(euler(1)) * cos(euler(2)),
      tan(euler(1)) * sin(euler(2)),
      float(1)};
    Vector3<float> euler_rate_comp = AngularVelocityToEulerRate * angular_velocity;

    REQUIRE(fabs(euler_rate(0U) - euler_rate_comp(0U)) < 1e-4f);
    REQUIRE(fabs(euler_rate(1U) - euler_rate_comp(1U)) < 1e-4f);
    REQUIRE(fabs(euler_rate(2U) - euler_rate_comp(2U)) < 1e-4f);
}