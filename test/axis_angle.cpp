#include <tinyso3/tinyso3.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace tinyso3;

TEST_CASE("AxisAngle") {
    SECTION("Constructors") {
        Euler<INTRINSIC, ZYX, float> euler{0.0f, 0.2f, 0.0f};
        RotationMatrix<ACTIVE, float> dcm_active{euler};
        RotationMatrix<PASSIVE, float> dcm_passive{euler};
        Quaternion<HAMILTON, float> q_hamilton{euler};
        Quaternion<JPL, float> q_jpl{euler};

        AxisAngle<float> axis_angle_euler{euler};
        AxisAngle<float> axis_angle_dcm_active{dcm_active};
        AxisAngle<float> axis_angle_dcm_passive{dcm_passive};
        AxisAngle<float> axis_angle_q_hamilton{q_hamilton};
        AxisAngle<float> axis_angle_q_jpl{q_jpl};

        AxisAngle<float> axis_angle_copy{axis_angle_euler};
        AxisAngle<float> axis_angle{Vector3<float>{0.0f, 1.0f, 0.0f}, 0.2f};

        REQUIRE(fabs(axis_angle_euler(0) - 0.0f) < 1e-4f);
        REQUIRE(fabs(axis_angle_euler(1) - 0.2f) < 1e-4f);
        REQUIRE(fabs(axis_angle_euler(2) - 0.0f) < 1e-4f);

        REQUIRE(fabs(axis_angle_dcm_active(0) - 0.0f) < 1e-4f);
        REQUIRE(fabs(axis_angle_dcm_active(1) - 0.2f) < 1e-4f);
        REQUIRE(fabs(axis_angle_dcm_active(2) - 0.0f) < 1e-4f);

        REQUIRE(fabs(axis_angle_dcm_passive(0) - 0.0f) < 1e-4f);
        REQUIRE(fabs(axis_angle_dcm_passive(1) - 0.2f) < 1e-4f);
        REQUIRE(fabs(axis_angle_dcm_passive(2) - 0.0f) < 1e-4f);

        REQUIRE_THAT(axis_angle_q_hamilton(0), Catch::Matchers::WithinAbs(0.0f, 1e-4f));
        REQUIRE_THAT(axis_angle_q_hamilton(1), Catch::Matchers::WithinAbs(0.2f, 1e-4f));
        REQUIRE_THAT(axis_angle_q_hamilton(2), Catch::Matchers::WithinAbs(0.0f, 1e-4f));

        REQUIRE_THAT(axis_angle_q_jpl(0), Catch::Matchers::WithinAbs(0.0f, 1e-4f));
        REQUIRE_THAT(axis_angle_q_jpl(1), Catch::Matchers::WithinAbs(0.2f, 1e-4f));
        REQUIRE_THAT(axis_angle_q_jpl(2), Catch::Matchers::WithinAbs(0.0f, 1e-4f));

        REQUIRE(fabs(axis_angle_copy(0) - 0.0f) < 1e-4f);
        REQUIRE(fabs(axis_angle_copy(1) - 0.2f) < 1e-4f);
        REQUIRE(fabs(axis_angle_copy(2) - 0.0f) < 1e-4f);

        REQUIRE(fabs(axis_angle(0) - 0.0f) < 1e-4f);
        REQUIRE(fabs(axis_angle(1) - 0.2f) < 1e-4f);
        REQUIRE(fabs(axis_angle(2) - 0.0f) < 1e-4f);
    }

    SECTION("Group Operations") {
        AxisAngle<float> axis_angle{0.0f, 0.2f, 0.0f};
        REQUIRE(is_same<AxisAngle<float>, decltype(axis_angle * 0.4f)>::value);
        REQUIRE(is_same<Vector3<float>, decltype(axis_angle / 0.4f)>::value);
        REQUIRE(is_same<AxisAngle<float>, decltype(-axis_angle)>::value);
        REQUIRE(is_same<AxisAngle<float>, decltype(0.4f * axis_angle)>::value);
    }

    SECTION("Axis and Angle") {
        AxisAngle<float> axis_angle{0.0f, 0.2f, 0.0f};
        Vector3<float> axis = axis_angle.axis();
        float angle = axis_angle.angle();
        REQUIRE(fabs(axis(0) - 0.0f) < 1e-4f);
        REQUIRE(fabs(axis(1) - 1.0f) < 1e-4f);
        REQUIRE(fabs(axis(2) - 0.0f) < 1e-4f);
        REQUIRE(fabs(angle - 0.2f) < 1e-4f);
    }
}