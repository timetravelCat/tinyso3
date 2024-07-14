#include <tinyso3/tinyso3.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace tinyso3;

TEST_CASE("Quaternion") {
    SECTION("Constructors") {
        Quaternion<HAMILTON, float> q1;
        REQUIRE(q1.w() == 1);
        REQUIRE(q1.x() == 0);
        REQUIRE(q1.y() == 0);
        REQUIRE(q1.z() == 0);

        Quaternion<HAMILTON, float> q2(1.f, 2.f, 3.f, 4.f);
        REQUIRE(q2.w() == 1);
        REQUIRE(q2.x() == 2);
        REQUIRE(q2.y() == 3);
        REQUIRE(q2.z() == 4);

        Quaternion<HAMILTON, float> q3{q1};
        REQUIRE(q3.w() == 1);
        REQUIRE(q3.x() == 0);
        REQUIRE(q3.y() == 0);
        REQUIRE(q3.z() == 0);

        Vector3<float> re{2.f, 3.f, 4.f};
        float Im{1.f};

        Quaternion<HAMILTON, float> q4{Im, re};
        REQUIRE(q4.w() == 1);
        REQUIRE(q4.x() == 2);
        REQUIRE(q4.y() == 3);
        REQUIRE(q4.z() == 4);
    }

    SECTION("Accessors") {
        const Quaternion<HAMILTON, float> q1{1.f, 2.f, 3.f, 4.f};
        REQUIRE(q1.w() == 1);
        REQUIRE(q1.x() == 2);
        REQUIRE(q1.y() == 3);
        REQUIRE(q1.z() == 4);
        REQUIRE(q1(0) == 1);
        REQUIRE(q1(1) == 2);
        REQUIRE(q1(2) == 3);
        REQUIRE(q1(3) == 4);

        const Quaternion<JPL, float> q2{2.f, 3.f, 4.f, 1.f};
        REQUIRE(q2.w() == 1);
        REQUIRE(q2.x() == 2);
        REQUIRE(q2.y() == 3);
        REQUIRE(q2.z() == 4);
        REQUIRE(q2(0, 0) == 2);
        REQUIRE(q2(1, 0) == 3);
        REQUIRE(q2(2, 0) == 4);
        REQUIRE(q2(3, 0) == 1);

        Quaternion<HAMILTON, float> q3;
        Quaternion<JPL, float> q4;

        q3.w() = 1.f;
        q3.x() = 2.f;
        q3.y() = 3.f;
        q3.z() = 4.f;

        q4.w() = 1.f;
        q4.x() = 2.f;
        q4.y() = 3.f;
        q4.z() = 4.f;

        REQUIRE(q3.w() == 1);
        REQUIRE(q3.x() == 2);
        REQUIRE(q3.y() == 3);
        REQUIRE(q3.z() == 4);
        REQUIRE(q3(0, 0) == 1);
        REQUIRE(q3(1, 0) == 2);
        REQUIRE(q3(2, 0) == 3);
        REQUIRE(q3(3, 0) == 4);

        REQUIRE(q4.w() == 1);
        REQUIRE(q4.x() == 2);
        REQUIRE(q4.y() == 3);
        REQUIRE(q4.z() == 4);
        REQUIRE(q4(0, 0) == 2);
        REQUIRE(q4(1, 0) == 3);
        REQUIRE(q4(2, 0) == 4);
        REQUIRE(q4(3, 0) == 1);

        Quaternion<HAMILTON, float> q5{1.f, 2.f, 3.f, 4.f};
        // Quaternion<HAMILTON, float> q5_unit = q5.unit();
    }

    SECTION("HAMILTON - Euler Conversion") {
        Euler<INTRINSIC, XYZ, float> euler_xyz(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, XZY, float> euler_xzy(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, YXZ, float> euler_yxz(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, YZX, float> euler_yzx(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, ZXY, float> euler_zxy(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, ZYX, float> euler_zyx(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, XYX, float> euler_xyx(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, XZX, float> euler_xzx(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, YXY, float> euler_yxy(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, YZY, float> euler_yzy(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, ZXZ, float> euler_zxz(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, ZYZ, float> euler_zyz(0.1f, 0.2f, 0.3f);

        RotationMatrix<ACTIVE, float> R_xyz{euler_xyz};
        RotationMatrix<ACTIVE, float> R_xzy{euler_xzy};
        RotationMatrix<ACTIVE, float> R_yxz{euler_yxz};
        RotationMatrix<ACTIVE, float> R_yzx{euler_yzx};
        RotationMatrix<ACTIVE, float> R_zxy{euler_zxy};
        RotationMatrix<ACTIVE, float> R_zyx{euler_zyx};
        RotationMatrix<ACTIVE, float> R_xyx{euler_xyx};
        RotationMatrix<ACTIVE, float> R_xzx{euler_xzx};
        RotationMatrix<ACTIVE, float> R_yxy{euler_yxy};
        RotationMatrix<ACTIVE, float> R_yzy{euler_yzy};
        RotationMatrix<ACTIVE, float> R_zxz{euler_zxz};
        RotationMatrix<ACTIVE, float> R_zyz{euler_zyz};

        Quaternion<HAMILTON, float> q_xyz{R_xyz};
        Quaternion<HAMILTON, float> q_xzy{R_xzy};
        Quaternion<HAMILTON, float> q_yxz{R_yxz};
        Quaternion<HAMILTON, float> q_yzx{R_yzx};
        Quaternion<HAMILTON, float> q_zxy{R_zxy};
        Quaternion<HAMILTON, float> q_zyx{R_zyx};
        Quaternion<HAMILTON, float> q_xyx{R_xyx};
        Quaternion<HAMILTON, float> q_xzx{R_xzx};
        Quaternion<HAMILTON, float> q_yxy{R_yxy};
        Quaternion<HAMILTON, float> q_yzy{R_yzy};
        Quaternion<HAMILTON, float> q_zxz{R_zxz};
        Quaternion<HAMILTON, float> q_zyz{R_zyz};

        Quaternion<HAMILTON, float> q_xyz_expected{euler_xyz};
        Quaternion<HAMILTON, float> q_xzy_expected{euler_xzy};
        Quaternion<HAMILTON, float> q_yxz_expected{euler_yxz};
        Quaternion<HAMILTON, float> q_yzx_expected{euler_yzx};
        Quaternion<HAMILTON, float> q_zxy_expected{euler_zxy};
        Quaternion<HAMILTON, float> q_zyx_expected{euler_zyx};
        Quaternion<HAMILTON, float> q_xyx_expected{euler_xyx};
        Quaternion<HAMILTON, float> q_xzx_expected{euler_xzx};
        Quaternion<HAMILTON, float> q_yxy_expected{euler_yxy};
        Quaternion<HAMILTON, float> q_yzy_expected{euler_yzy};
        Quaternion<HAMILTON, float> q_zxz_expected{euler_zxz};
        Quaternion<HAMILTON, float> q_zyz_expected{euler_zyz};

        REQUIRE_THAT(q_xyx(0), Catch::Matchers::WithinAbs(double(q_xyx_expected(0)), 1e-6));
        REQUIRE_THAT(q_xyx(1), Catch::Matchers::WithinAbs(double(q_xyx_expected(1)), 1e-6));
        REQUIRE_THAT(q_xyx(2), Catch::Matchers::WithinAbs(double(q_xyx_expected(2)), 1e-6));
        REQUIRE_THAT(q_xyx(3), Catch::Matchers::WithinAbs(double(q_xyx_expected(3)), 1e-6));

        REQUIRE_THAT(q_xzx(0), Catch::Matchers::WithinAbs(double(q_xzx_expected(0)), 1e-6));
        REQUIRE_THAT(q_xzx(1), Catch::Matchers::WithinAbs(double(q_xzx_expected(1)), 1e-6));
        REQUIRE_THAT(q_xzx(2), Catch::Matchers::WithinAbs(double(q_xzx_expected(2)), 1e-6));
        REQUIRE_THAT(q_xzx(3), Catch::Matchers::WithinAbs(double(q_xzx_expected(3)), 1e-6));

        REQUIRE_THAT(q_yxy(0), Catch::Matchers::WithinAbs(double(q_yxy_expected(0)), 1e-6));
        REQUIRE_THAT(q_yxy(1), Catch::Matchers::WithinAbs(double(q_yxy_expected(1)), 1e-6));
        REQUIRE_THAT(q_yxy(2), Catch::Matchers::WithinAbs(double(q_yxy_expected(2)), 1e-6));
        REQUIRE_THAT(q_yxy(3), Catch::Matchers::WithinAbs(double(q_yxy_expected(3)), 1e-6));

        REQUIRE_THAT(q_yzy(0), Catch::Matchers::WithinAbs(double(q_yzy_expected(0)), 1e-6));
        REQUIRE_THAT(q_yzy(1), Catch::Matchers::WithinAbs(double(q_yzy_expected(1)), 1e-6));
        REQUIRE_THAT(q_yzy(2), Catch::Matchers::WithinAbs(double(q_yzy_expected(2)), 1e-6));
        REQUIRE_THAT(q_yzy(3), Catch::Matchers::WithinAbs(double(q_yzy_expected(3)), 1e-6));

        REQUIRE_THAT(q_zxz(0), Catch::Matchers::WithinAbs(double(q_zxz_expected(0)), 1e-6));
        REQUIRE_THAT(q_zxz(1), Catch::Matchers::WithinAbs(double(q_zxz_expected(1)), 1e-6));
        REQUIRE_THAT(q_zxz(2), Catch::Matchers::WithinAbs(double(q_zxz_expected(2)), 1e-6));
        REQUIRE_THAT(q_zxz(3), Catch::Matchers::WithinAbs(double(q_zxz_expected(3)), 1e-6));

        REQUIRE_THAT(q_zyz(0), Catch::Matchers::WithinAbs(double(q_zyz_expected(0)), 1e-6));
        REQUIRE_THAT(q_zyz(1), Catch::Matchers::WithinAbs(double(q_zyz_expected(1)), 1e-6));
        REQUIRE_THAT(q_zyz(2), Catch::Matchers::WithinAbs(double(q_zyz_expected(2)), 1e-6));
        REQUIRE_THAT(q_zyz(3), Catch::Matchers::WithinAbs(double(q_zyz_expected(3)), 1e-6));

        REQUIRE_THAT(q_xyz(0), Catch::Matchers::WithinAbs(double(q_xyz_expected(0)), 1e-6));
        REQUIRE_THAT(q_xyz(1), Catch::Matchers::WithinAbs(double(q_xyz_expected(1)), 1e-6));
        REQUIRE_THAT(q_xyz(2), Catch::Matchers::WithinAbs(double(q_xyz_expected(2)), 1e-6));
        REQUIRE_THAT(q_xyz(3), Catch::Matchers::WithinAbs(double(q_xyz_expected(3)), 1e-6));

        REQUIRE_THAT(q_xzy(0), Catch::Matchers::WithinAbs(double(q_xzy_expected(0)), 1e-6));
        REQUIRE_THAT(q_xzy(1), Catch::Matchers::WithinAbs(double(q_xzy_expected(1)), 1e-6));
        REQUIRE_THAT(q_xzy(2), Catch::Matchers::WithinAbs(double(q_xzy_expected(2)), 1e-6));
        REQUIRE_THAT(q_xzy(3), Catch::Matchers::WithinAbs(double(q_xzy_expected(3)), 1e-6));

        REQUIRE_THAT(q_yxz(0), Catch::Matchers::WithinAbs(double(q_yxz_expected(0)), 1e-6));
        REQUIRE_THAT(q_yxz(1), Catch::Matchers::WithinAbs(double(q_yxz_expected(1)), 1e-6));
        REQUIRE_THAT(q_yxz(2), Catch::Matchers::WithinAbs(double(q_yxz_expected(2)), 1e-6));
        REQUIRE_THAT(q_yxz(3), Catch::Matchers::WithinAbs(double(q_yxz_expected(3)), 1e-6));

        REQUIRE_THAT(q_yzx(0), Catch::Matchers::WithinAbs(double(q_yzx_expected(0)), 1e-6));
        REQUIRE_THAT(q_yzx(1), Catch::Matchers::WithinAbs(double(q_yzx_expected(1)), 1e-6));
        REQUIRE_THAT(q_yzx(2), Catch::Matchers::WithinAbs(double(q_yzx_expected(2)), 1e-6));
        REQUIRE_THAT(q_yzx(3), Catch::Matchers::WithinAbs(double(q_yzx_expected(3)), 1e-6));

        REQUIRE_THAT(q_zxy(0), Catch::Matchers::WithinAbs(double(q_zxy_expected(0)), 1e-6));
        REQUIRE_THAT(q_zxy(1), Catch::Matchers::WithinAbs(double(q_zxy_expected(1)), 1e-6));
        REQUIRE_THAT(q_zxy(2), Catch::Matchers::WithinAbs(double(q_zxy_expected(2)), 1e-6));
        REQUIRE_THAT(q_zxy(3), Catch::Matchers::WithinAbs(double(q_zxy_expected(3)), 1e-6));

        REQUIRE_THAT(q_zyx(0), Catch::Matchers::WithinAbs(double(q_zyx_expected(0)), 1e-6));
        REQUIRE_THAT(q_zyx(1), Catch::Matchers::WithinAbs(double(q_zyx_expected(1)), 1e-6));
        REQUIRE_THAT(q_zyx(2), Catch::Matchers::WithinAbs(double(q_zyx_expected(2)), 1e-6));
        REQUIRE_THAT(q_zyx(3), Catch::Matchers::WithinAbs(double(q_zyx_expected(3)), 1e-6));
    }
    SECTION("JPL - Euler Conversion") {
        Euler<INTRINSIC, XYZ, float> euler_xyz(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, XZY, float> euler_xzy(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, YXZ, float> euler_yxz(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, YZX, float> euler_yzx(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, ZXY, float> euler_zxy(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, ZYX, float> euler_zyx(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, XYX, float> euler_xyx(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, XZX, float> euler_xzx(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, YXY, float> euler_yxy(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, YZY, float> euler_yzy(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, ZXZ, float> euler_zxz(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, ZYZ, float> euler_zyz(0.1f, 0.2f, 0.3f);

        RotationMatrix<PASSIVE, float> R_xyz{euler_xyz};
        RotationMatrix<PASSIVE, float> R_xzy{euler_xzy};
        RotationMatrix<PASSIVE, float> R_yxz{euler_yxz};
        RotationMatrix<PASSIVE, float> R_yzx{euler_yzx};
        RotationMatrix<PASSIVE, float> R_zxy{euler_zxy};
        RotationMatrix<PASSIVE, float> R_zyx{euler_zyx};
        RotationMatrix<PASSIVE, float> R_xyx{euler_xyx};
        RotationMatrix<PASSIVE, float> R_xzx{euler_xzx};
        RotationMatrix<PASSIVE, float> R_yxy{euler_yxy};
        RotationMatrix<PASSIVE, float> R_yzy{euler_yzy};
        RotationMatrix<PASSIVE, float> R_zxz{euler_zxz};
        RotationMatrix<PASSIVE, float> R_zyz{euler_zyz};

        Quaternion<JPL, float> q_xyz{R_xyz};
        Quaternion<JPL, float> q_xzy{R_xzy};
        Quaternion<JPL, float> q_yxz{R_yxz};
        Quaternion<JPL, float> q_yzx{R_yzx};
        Quaternion<JPL, float> q_zxy{R_zxy};
        Quaternion<JPL, float> q_zyx{R_zyx};
        Quaternion<JPL, float> q_xyx{R_xyx};
        Quaternion<JPL, float> q_xzx{R_xzx};
        Quaternion<JPL, float> q_yxy{R_yxy};
        Quaternion<JPL, float> q_yzy{R_yzy};
        Quaternion<JPL, float> q_zxz{R_zxz};
        Quaternion<JPL, float> q_zyz{R_zyz};

        Quaternion<JPL, float> q_xyz_expected{euler_xyz};
        Quaternion<JPL, float> q_xzy_expected{euler_xzy};
        Quaternion<JPL, float> q_yxz_expected{euler_yxz};
        Quaternion<JPL, float> q_yzx_expected{euler_yzx};
        Quaternion<JPL, float> q_zxy_expected{euler_zxy};
        Quaternion<JPL, float> q_zyx_expected{euler_zyx};
        Quaternion<JPL, float> q_xyx_expected{euler_xyx};
        Quaternion<JPL, float> q_xzx_expected{euler_xzx};
        Quaternion<JPL, float> q_yxy_expected{euler_yxy};
        Quaternion<JPL, float> q_yzy_expected{euler_yzy};
        Quaternion<JPL, float> q_zxz_expected{euler_zxz};
        Quaternion<JPL, float> q_zyz_expected{euler_zyz};

        REQUIRE_THAT(q_xyx(0), Catch::Matchers::WithinAbs(double(q_xyx_expected(0)), 1e-6));
        REQUIRE_THAT(q_xyx(1), Catch::Matchers::WithinAbs(double(q_xyx_expected(1)), 1e-6));
        REQUIRE_THAT(q_xyx(2), Catch::Matchers::WithinAbs(double(q_xyx_expected(2)), 1e-6));
        REQUIRE_THAT(q_xyx(3), Catch::Matchers::WithinAbs(double(q_xyx_expected(3)), 1e-6));

        REQUIRE_THAT(q_xzx(0), Catch::Matchers::WithinAbs(double(q_xzx_expected(0)), 1e-6));
        REQUIRE_THAT(q_xzx(1), Catch::Matchers::WithinAbs(double(q_xzx_expected(1)), 1e-6));
        REQUIRE_THAT(q_xzx(2), Catch::Matchers::WithinAbs(double(q_xzx_expected(2)), 1e-6));
        REQUIRE_THAT(q_xzx(3), Catch::Matchers::WithinAbs(double(q_xzx_expected(3)), 1e-6));

        REQUIRE_THAT(q_yxy(0), Catch::Matchers::WithinAbs(double(q_yxy_expected(0)), 1e-6));
        REQUIRE_THAT(q_yxy(1), Catch::Matchers::WithinAbs(double(q_yxy_expected(1)), 1e-6));
        REQUIRE_THAT(q_yxy(2), Catch::Matchers::WithinAbs(double(q_yxy_expected(2)), 1e-6));
        REQUIRE_THAT(q_yxy(3), Catch::Matchers::WithinAbs(double(q_yxy_expected(3)), 1e-6));

        REQUIRE_THAT(q_yzy(0), Catch::Matchers::WithinAbs(double(q_yzy_expected(0)), 1e-6));
        REQUIRE_THAT(q_yzy(1), Catch::Matchers::WithinAbs(double(q_yzy_expected(1)), 1e-6));
        REQUIRE_THAT(q_yzy(2), Catch::Matchers::WithinAbs(double(q_yzy_expected(2)), 1e-6));
        REQUIRE_THAT(q_yzy(3), Catch::Matchers::WithinAbs(double(q_yzy_expected(3)), 1e-6));

        REQUIRE_THAT(q_zxz(0), Catch::Matchers::WithinAbs(double(q_zxz_expected(0)), 1e-6));
        REQUIRE_THAT(q_zxz(1), Catch::Matchers::WithinAbs(double(q_zxz_expected(1)), 1e-6));
        REQUIRE_THAT(q_zxz(2), Catch::Matchers::WithinAbs(double(q_zxz_expected(2)), 1e-6));
        REQUIRE_THAT(q_zxz(3), Catch::Matchers::WithinAbs(double(q_zxz_expected(3)), 1e-6));

        REQUIRE_THAT(q_zyz(0), Catch::Matchers::WithinAbs(double(q_zyz_expected(0)), 1e-6));
        REQUIRE_THAT(q_zyz(1), Catch::Matchers::WithinAbs(double(q_zyz_expected(1)), 1e-6));
        REQUIRE_THAT(q_zyz(2), Catch::Matchers::WithinAbs(double(q_zyz_expected(2)), 1e-6));
        REQUIRE_THAT(q_zyz(3), Catch::Matchers::WithinAbs(double(q_zyz_expected(3)), 1e-6));

        REQUIRE_THAT(q_xyz(0), Catch::Matchers::WithinAbs(double(q_xyz_expected(0)), 1e-6));
        REQUIRE_THAT(q_xyz(1), Catch::Matchers::WithinAbs(double(q_xyz_expected(1)), 1e-6));
        REQUIRE_THAT(q_xyz(2), Catch::Matchers::WithinAbs(double(q_xyz_expected(2)), 1e-6));
        REQUIRE_THAT(q_xyz(3), Catch::Matchers::WithinAbs(double(q_xyz_expected(3)), 1e-6));

        REQUIRE_THAT(q_xzy(0), Catch::Matchers::WithinAbs(double(q_xzy_expected(0)), 1e-6));
        REQUIRE_THAT(q_xzy(1), Catch::Matchers::WithinAbs(double(q_xzy_expected(1)), 1e-6));
        REQUIRE_THAT(q_xzy(2), Catch::Matchers::WithinAbs(double(q_xzy_expected(2)), 1e-6));
        REQUIRE_THAT(q_xzy(3), Catch::Matchers::WithinAbs(double(q_xzy_expected(3)), 1e-6));

        REQUIRE_THAT(q_yxz(0), Catch::Matchers::WithinAbs(double(q_yxz_expected(0)), 1e-6));
        REQUIRE_THAT(q_yxz(1), Catch::Matchers::WithinAbs(double(q_yxz_expected(1)), 1e-6));
        REQUIRE_THAT(q_yxz(2), Catch::Matchers::WithinAbs(double(q_yxz_expected(2)), 1e-6));
        REQUIRE_THAT(q_yxz(3), Catch::Matchers::WithinAbs(double(q_yxz_expected(3)), 1e-6));

        REQUIRE_THAT(q_yzx(0), Catch::Matchers::WithinAbs(double(q_yzx_expected(0)), 1e-6));
        REQUIRE_THAT(q_yzx(1), Catch::Matchers::WithinAbs(double(q_yzx_expected(1)), 1e-6));
        REQUIRE_THAT(q_yzx(2), Catch::Matchers::WithinAbs(double(q_yzx_expected(2)), 1e-6));
        REQUIRE_THAT(q_yzx(3), Catch::Matchers::WithinAbs(double(q_yzx_expected(3)), 1e-6));

        REQUIRE_THAT(q_zxy(0), Catch::Matchers::WithinAbs(double(q_zxy_expected(0)), 1e-6));
        REQUIRE_THAT(q_zxy(1), Catch::Matchers::WithinAbs(double(q_zxy_expected(1)), 1e-6));
        REQUIRE_THAT(q_zxy(2), Catch::Matchers::WithinAbs(double(q_zxy_expected(2)), 1e-6));
        REQUIRE_THAT(q_zxy(3), Catch::Matchers::WithinAbs(double(q_zxy_expected(3)), 1e-6));

        REQUIRE_THAT(q_zyx(0), Catch::Matchers::WithinAbs(double(q_zyx_expected(0)), 1e-6));
        REQUIRE_THAT(q_zyx(1), Catch::Matchers::WithinAbs(double(q_zyx_expected(1)), 1e-6));
        REQUIRE_THAT(q_zyx(2), Catch::Matchers::WithinAbs(double(q_zyx_expected(2)), 1e-6));
        REQUIRE_THAT(q_zyx(3), Catch::Matchers::WithinAbs(double(q_zyx_expected(3)), 1e-6));
    }

    SECTION("axis angle") {
        AxisAngle<float> axis_angle{Vector3<float>{1.f, 0.f, 0.f}, 0.1f};
        Quaternion<HAMILTON, float> q{axis_angle};
        REQUIRE_THAT(q.w(), Catch::Matchers::WithinAbs(cos(0.5 * 0.1), 1e-4));
        REQUIRE_THAT(q.x(), Catch::Matchers::WithinAbs(sin(0.5 * 0.1), 1e-4));
        REQUIRE_THAT(q.y(), Catch::Matchers::WithinAbs(0.0, 1e-4));
        REQUIRE_THAT(q.z(), Catch::Matchers::WithinAbs(0.0, 1e-4));

        RotationMatrix<ACTIVE, float> R{axis_angle};
        Vector3<float> vec;
        auto vec2 = q * vec;
        auto vec3 = Vector3<float>{R * vec};

        REQUIRE_THAT(vec2(0), Catch::Matchers::WithinAbs(double(vec3(0)), 1e-4));
        REQUIRE_THAT(vec2(1), Catch::Matchers::WithinAbs(double(vec3(1)), 1e-4));
        REQUIRE_THAT(vec2(2), Catch::Matchers::WithinAbs(double(vec3(2)), 1e-4));

        Quaternion<JPL, float> q2{axis_angle};
        REQUIRE_THAT(q2.w(), Catch::Matchers::WithinAbs(cos(0.5 * 0.1), 1e-4));
        REQUIRE_THAT(q2.x(), Catch::Matchers::WithinAbs(-sin(0.5 * 0.1), 1e-4));
        REQUIRE_THAT(q2.y(), Catch::Matchers::WithinAbs(-0.0, 1e-4));
        REQUIRE_THAT(q2.z(), Catch::Matchers::WithinAbs(-0.0, 1e-4));

        RotationMatrix<PASSIVE, float> R2{axis_angle};
        Vector3<float> vec4 = q2 * vec;
        auto vec5 = Vector3<float>{R2 * vec};

        REQUIRE_THAT(vec4(0), Catch::Matchers::WithinAbs(double(vec5(0)), 1e-4));
        REQUIRE_THAT(vec4(1), Catch::Matchers::WithinAbs(double(vec5(1)), 1e-4));
        REQUIRE_THAT(vec4(2), Catch::Matchers::WithinAbs(double(vec5(2)), 1e-4));
    }

    SECTION("quaternion operator overloads") {
        Euler<INTRINSIC, XYZ, float> euler1(0.1f, 0.0f, 0.0f);
        Euler<INTRINSIC, ZYX, float> euler2(0.1f, 0.2f, 0.3f);

        RotationMatrix<ACTIVE, float> R1{euler1};
        RotationMatrix<ACTIVE, float> R2{euler2};

        Quaternion<HAMILTON, float> q1{euler1};
        Quaternion<HAMILTON, float> q2{euler2};

        Quaternion<HAMILTON, float> q_12 = q1 * q2;
        Quaternion<HAMILTON, float> q_21 = q2 * q1;

        Vector3<float> vec{1.f, 2.f, 3.f};

        Vector3<float> vec_q1 = q1 * vec;
        Vector3<float> vec_r1 = Vector3<float>{R1 * vec};
        REQUIRE_THAT(vec_q1(0), Catch::Matchers::WithinAbs(double(vec_r1(0)), 1e-4));
        REQUIRE_THAT(vec_q1(1), Catch::Matchers::WithinAbs(double(vec_r1(1)), 1e-4));
        REQUIRE_THAT(vec_q1(2), Catch::Matchers::WithinAbs(double(vec_r1(2)), 1e-4));

        Vector3<float> vec_q_12 = q_12 * vec;
        Vector3<float> vec_q_21 = q_21 * vec;
        Vector3<float> vec_R_12 = Vector3<float>{R1 * R2 * vec};
        Vector3<float> vec_R_21 = Vector3<float>{R2 * R1 * vec};

        REQUIRE_THAT(vec_q_12(0), Catch::Matchers::WithinAbs(double(vec_R_12(0)), 1e-4));
        REQUIRE_THAT(vec_q_12(1), Catch::Matchers::WithinAbs(double(vec_R_12(1)), 1e-4));
        REQUIRE_THAT(vec_q_12(2), Catch::Matchers::WithinAbs(double(vec_R_12(2)), 1e-4));

        REQUIRE_THAT(vec_q_21(0), Catch::Matchers::WithinAbs(double(vec_R_21(0)), 1e-4));
        REQUIRE_THAT(vec_q_21(1), Catch::Matchers::WithinAbs(double(vec_R_21(1)), 1e-4));
        REQUIRE_THAT(vec_q_21(2), Catch::Matchers::WithinAbs(double(vec_R_21(2)), 1e-4));
    }

    SECTION("slerp") {
        Euler<INTRINSIC, XYZ, float> euler1(0.1f, 0.2f, 0.3f);
        Euler<INTRINSIC, XYZ, float> euler2(0.2f, 0.3f, 0.4f);

        RotationMatrix<ACTIVE, float> R1{euler1};
        RotationMatrix<ACTIVE, float> R2{euler2};
        RotationMatrix<ACTIVE, float> R_slerp = R1.interpolate(R2, 0.33333f);

        Quaternion<HAMILTON, float> q1{euler1};
        Quaternion<HAMILTON, float> q2{euler2};
        Quaternion<HAMILTON, float> q_slerp = q1.slerp(q2, 0.33333f);

        Vector3<float> vec{1.1f, 2.2f, 3.3f};

        Vector3<float> vec_r_slerp = Vector3<float>{R_slerp * vec};
        Vector3<float> vec_q_slerp = q_slerp * vec;

        REQUIRE_THAT(vec_r_slerp.x(), Catch::Matchers::WithinAbs(double(vec_q_slerp.x()), 1e-4));
        REQUIRE_THAT(vec_r_slerp.y(), Catch::Matchers::WithinAbs(double(vec_q_slerp.y()), 1e-4));
        REQUIRE_THAT(vec_r_slerp.z(), Catch::Matchers::WithinAbs(double(vec_q_slerp.z()), 1e-4));
    }

    SECTION("Exponential, logarithm") {
        // exp 0 = 1
        Quaternion<HAMILTON, float> q2{1.f, 0.f, 0.f, 0.f};
        Quaternion<HAMILTON, float> q2_exp = Quaternion<HAMILTON, float>::Exp(Vector3<float>{0.f, 0.f, 0.f});
        REQUIRE_THAT(q2_exp.w(), Catch::Matchers::WithinAbs(1.f, 1e-4));
        REQUIRE_THAT(q2_exp.x(), Catch::Matchers::WithinAbs(0.f, 1e-4));
        REQUIRE_THAT(q2_exp.y(), Catch::Matchers::WithinAbs(0.f, 1e-4));
        REQUIRE_THAT(q2_exp.z(), Catch::Matchers::WithinAbs(0.f, 1e-4));

        // log 1 = 0
        Quaternion<HAMILTON, float> q3{1.f, 0.f, 0.f, 0.f};
        Vector3<float> q3_log = q3.log();
        REQUIRE_THAT(q3_log.x(), Catch::Matchers::WithinAbs(0.0, 1e-4));
        REQUIRE_THAT(q3_log.y(), Catch::Matchers::WithinAbs(0.0, 1e-4));
        REQUIRE_THAT(q3_log.z(), Catch::Matchers::WithinAbs(0.0, 1e-4));

        // exp(w + tu)) = e^w (cos(t) + u sin(t))
        Vector3<float> u = {1.f, 2.f, 3.f};
        u.normalize();
        float t = 0.123f;
        Quaternion<HAMILTON, float> q5_exp = Quaternion<HAMILTON, float>::Exp(t * u);
        REQUIRE_THAT(q5_exp.w(), Catch::Matchers::WithinAbs(cos(t), 1e-4));
        REQUIRE_THAT(q5_exp.x(), Catch::Matchers::WithinAbs(sin(t) * u.x(), 1e-4));
        REQUIRE_THAT(q5_exp.y(), Catch::Matchers::WithinAbs(sin(t) * u.y(), 1e-4));
        REQUIRE_THAT(q5_exp.z(), Catch::Matchers::WithinAbs(sin(t) * u.z(), 1e-4));

        // log(e^w (cos(t) + u sin(t))) = w + tu
        Quaternion<HAMILTON, float> q6{cos(t), sin(t) * u};
        Vector3<float> q6_log = q6.log();
        REQUIRE_THAT(q6_log.x(), Catch::Matchers::WithinAbs(t * u.x(), 1e-4));
        REQUIRE_THAT(q6_log.y(), Catch::Matchers::WithinAbs(t * u.y(), 1e-4));
        REQUIRE_THAT(q6_log.z(), Catch::Matchers::WithinAbs(t * u.z(), 1e-4));

        // exp(log(q)) = q
        Quaternion<HAMILTON, float> q7{1.f, 0.1f, 0.2f, 0.3f};
        q7.normalize();
        Vector3<float> q7_log = q7.log();
        Quaternion<HAMILTON, float> q7_exp = Quaternion<HAMILTON, float>::Exp(q7_log);
        REQUIRE_THAT(q7_exp.w(), Catch::Matchers::WithinAbs(q7.w(), 1e-4));
        REQUIRE_THAT(q7_exp.x(), Catch::Matchers::WithinAbs(q7.x(), 1e-4));
        REQUIRE_THAT(q7_exp.y(), Catch::Matchers::WithinAbs(q7.y(), 1e-4));
        REQUIRE_THAT(q7_exp.z(), Catch::Matchers::WithinAbs(q7.z(), 1e-4));

        // log(exp(q)) = q
        Vector3<float> q8_vec{0.1f, 0.2f, 0.3f};
        Quaternion<HAMILTON, float> q8_exp = Quaternion<HAMILTON, float>::Exp(q8_vec);
        Vector3<float> q8_log = q8_exp.log();
        REQUIRE_THAT(q8_log.x(), Catch::Matchers::WithinAbs(q8_vec.x(), 1e-4));
        REQUIRE_THAT(q8_log.y(), Catch::Matchers::WithinAbs(q8_vec.y(), 1e-4));
        REQUIRE_THAT(q8_log.z(), Catch::Matchers::WithinAbs(q8_vec.z(), 1e-4));
    }
}
