#include <tinyso3/tinyso3.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace tinyso3;

TEST_CASE("Euler") {
    // Create Euler Angle of All Sequences
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

    // Then Convert to Rotation Matrix
    RotationMatrix<ACTIVE, float> dcm_active_xyz(euler_xyz);
    RotationMatrix<ACTIVE, float> dcm_active_xzy(euler_xzy);
    RotationMatrix<ACTIVE, float> dcm_active_yxz(euler_yxz);
    RotationMatrix<ACTIVE, float> dcm_active_yzx(euler_yzx);
    RotationMatrix<ACTIVE, float> dcm_active_zxy(euler_zxy);
    RotationMatrix<ACTIVE, float> dcm_active_zyx(euler_zyx);
    RotationMatrix<ACTIVE, float> dcm_active_xyx(euler_xyx);
    RotationMatrix<ACTIVE, float> dcm_active_xzx(euler_xzx);
    RotationMatrix<ACTIVE, float> dcm_active_yxy(euler_yxy);
    RotationMatrix<ACTIVE, float> dcm_active_yzy(euler_yzy);
    RotationMatrix<ACTIVE, float> dcm_active_zxz(euler_zxz);
    RotationMatrix<ACTIVE, float> dcm_active_zyz(euler_zyz);

    RotationMatrix<PASSIVE, float> dcm_passive_xyz(euler_xyz);
    RotationMatrix<PASSIVE, float> dcm_passive_xzy(euler_xzy);
    RotationMatrix<PASSIVE, float> dcm_passive_yxz(euler_yxz);
    RotationMatrix<PASSIVE, float> dcm_passive_yzx(euler_yzx);
    RotationMatrix<PASSIVE, float> dcm_passive_zxy(euler_zxy);
    RotationMatrix<PASSIVE, float> dcm_passive_zyx(euler_zyx);
    RotationMatrix<PASSIVE, float> dcm_passive_xyx(euler_xyx);
    RotationMatrix<PASSIVE, float> dcm_passive_xzx(euler_xzx);
    RotationMatrix<PASSIVE, float> dcm_passive_yxy(euler_yxy);
    RotationMatrix<PASSIVE, float> dcm_passive_yzy(euler_yzy);
    RotationMatrix<PASSIVE, float> dcm_passive_zxz(euler_zxz);
    RotationMatrix<PASSIVE, float> dcm_passive_zyz(euler_zyz);

    // Then Convert to Euler Angle Again
    Euler<INTRINSIC, XYZ, float> euler_xyz_active(dcm_active_xyz);
    Euler<INTRINSIC, XZY, float> euler_xzy_active(dcm_active_xzy);
    Euler<INTRINSIC, YXZ, float> euler_yxz_active(dcm_active_yxz);
    Euler<INTRINSIC, YZX, float> euler_yzx_active(dcm_active_yzx);
    Euler<INTRINSIC, ZXY, float> euler_zxy_active(dcm_active_zxy);
    Euler<INTRINSIC, ZYX, float> euler_zyx_active(dcm_active_zyx);
    Euler<INTRINSIC, XYX, float> euler_xyx_active(dcm_active_xyx);
    Euler<INTRINSIC, XZX, float> euler_xzx_active(dcm_active_xzx);
    Euler<INTRINSIC, YXY, float> euler_yxy_active(dcm_active_yxy);
    Euler<INTRINSIC, YZY, float> euler_yzy_active(dcm_active_yzy);
    Euler<INTRINSIC, ZXZ, float> euler_zxz_active(dcm_active_zxz);
    Euler<INTRINSIC, ZYZ, float> euler_zyz_active(dcm_active_zyz);

    Euler<INTRINSIC, XYZ, float> euler_xyz_passive(dcm_passive_xyz);
    Euler<INTRINSIC, XZY, float> euler_xzy_passive(dcm_passive_xzy);
    Euler<INTRINSIC, YXZ, float> euler_yxz_passive(dcm_passive_yxz);
    Euler<INTRINSIC, YZX, float> euler_yzx_passive(dcm_passive_yzx);
    Euler<INTRINSIC, ZXY, float> euler_zxy_passive(dcm_passive_zxy);
    Euler<INTRINSIC, ZYX, float> euler_zyx_passive(dcm_passive_zyx);
    Euler<INTRINSIC, XYX, float> euler_xyx_passive(dcm_passive_xyx);
    Euler<INTRINSIC, XZX, float> euler_xzx_passive(dcm_passive_xzx);
    Euler<INTRINSIC, YXY, float> euler_yxy_passive(dcm_passive_yxy);
    Euler<INTRINSIC, YZY, float> euler_yzy_passive(dcm_passive_yzy);
    Euler<INTRINSIC, ZXZ, float> euler_zxz_passive(dcm_passive_zxz);
    Euler<INTRINSIC, ZYZ, float> euler_zyz_passive(dcm_passive_zyz);

    // Then Compare the Result
    for(size_t i = 0; i < 3; i++) {
        REQUIRE(fabs(euler_xyz(i) - euler_xyz_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_xzy(i) - euler_xzy_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_yxz(i) - euler_yxz_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_yzx(i) - euler_yzx_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_zxy(i) - euler_zxy_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_zyx(i) - euler_zyx_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_xyx(i) - euler_xyx_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_xzx(i) - euler_xzx_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_yxy(i) - euler_yxy_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_yzy(i) - euler_yzy_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_zxz(i) - euler_zxz_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_zyz(i) - euler_zyz_active(i)) < 1e-4f);

        REQUIRE(fabs(euler_xyz(i) - euler_xyz_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_xzy(i) - euler_xzy_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_yxz(i) - euler_yxz_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_yzx(i) - euler_yzx_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_zxy(i) - euler_zxy_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_zyx(i) - euler_zyx_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_xyx(i) - euler_xyx_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_xzx(i) - euler_xzx_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_yxy(i) - euler_yxy_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_yzy(i) - euler_yzy_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_zxz(i) - euler_zxz_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_zyz(i) - euler_zyz_passive(i)) < 1e-4f);
    }

    // Singular Cases
    Euler<INTRINSIC, XYZ, float> euler_xyz_singular_p_pi_2(0.0f, +M_PI_2f, M_PIf / 6.0f);
    Euler<INTRINSIC, XYZ, float> euler_xyz_singular_m_pi_2(0.0f, -M_PI_2f, M_PIf / 6.0f);
    Euler<INTRINSIC, XZY, float> euler_xzy_singular_p_pi_2(0.0f, +M_PI_2f, M_PIf / 6.0f);
    Euler<INTRINSIC, XZY, float> euler_xzy_singular_m_pi_2(0.0f, -M_PI_2f, M_PIf / 6.0f);
    Euler<INTRINSIC, YXZ, float> euler_yxz_singular_p_pi_2(0.0f, +M_PI_2f, M_PIf / 6.0f);
    Euler<INTRINSIC, YXZ, float> euler_yxz_singular_m_pi_2(0.0f, -M_PI_2f, M_PIf / 6.0f);
    Euler<INTRINSIC, YZX, float> euler_yzx_singular_p_pi_2(0.0f, +M_PI_2f, M_PIf / 6.0f);
    Euler<INTRINSIC, YZX, float> euler_yzx_singular_m_pi_2(0.0f, -M_PI_2f, M_PIf / 6.0f);
    Euler<INTRINSIC, ZXY, float> euler_zxy_singular_p_pi_2(0.0f, +M_PI_2f, M_PIf / 6.0f);
    Euler<INTRINSIC, ZXY, float> euler_zxy_singular_m_pi_2(0.0f, -M_PI_2f, M_PIf / 6.0f);
    Euler<INTRINSIC, ZYX, float> euler_zyx_singular_p_pi_2(0.0f, +M_PI_2f, M_PIf / 6.0f);
    Euler<INTRINSIC, ZYX, float> euler_zyx_singular_m_pi_2(0.0f, -M_PI_2f, M_PIf / 6.0f);
    Euler<INTRINSIC, XYX, float> euler_xyx_singular_p_pi_0(0.0f, +0.0f, M_PIf / 6.0f);
    Euler<INTRINSIC, XYX, float> euler_xyx_singular_p_pi_1(0.0f, M_PIf, M_PIf / 6.0f);
    Euler<INTRINSIC, XZX, float> euler_xzx_singular_p_pi_0(0.0f, +0.0f, M_PIf / 6.0f);
    Euler<INTRINSIC, XZX, float> euler_xzx_singular_p_pi_1(0.0f, M_PIf, M_PIf / 6.0f);
    Euler<INTRINSIC, YXY, float> euler_yxy_singular_p_pi_0(0.0f, +0.0f, M_PIf / 6.0f);
    Euler<INTRINSIC, YXY, float> euler_yxy_singular_p_pi_1(0.0f, M_PIf, M_PIf / 6.0f);
    Euler<INTRINSIC, YZY, float> euler_yzy_singular_p_pi_0(0.0f, +0.0f, M_PIf / 6.0f);
    Euler<INTRINSIC, YZY, float> euler_yzy_singular_p_pi_1(0.0f, M_PIf, M_PIf / 6.0f);
    Euler<INTRINSIC, ZXZ, float> euler_zxz_singular_p_pi_0(0.0f, +0.0f, M_PIf / 6.0f);
    Euler<INTRINSIC, ZXZ, float> euler_zxz_singular_p_pi_1(0.0f, M_PIf, M_PIf / 6.0f);
    Euler<INTRINSIC, ZYZ, float> euler_zyz_singular_p_pi_0(0.0f, +0.0f, M_PIf / 6.0f);
    Euler<INTRINSIC, ZYZ, float> euler_zyz_singular_p_pi_1(0.0f, M_PIf, M_PIf / 6.0f);

    RotationMatrix<ACTIVE, float> dcm_xyz_active_p_pi_2(euler_xyz_singular_p_pi_2);
    RotationMatrix<ACTIVE, float> dcm_xyz_active_m_pi_2(euler_xyz_singular_m_pi_2);
    RotationMatrix<ACTIVE, float> dcm_xzy_active_p_pi_2(euler_xzy_singular_p_pi_2);
    RotationMatrix<ACTIVE, float> dcm_xzy_active_m_pi_2(euler_xzy_singular_m_pi_2);
    RotationMatrix<ACTIVE, float> dcm_yxz_active_p_pi_2(euler_yxz_singular_p_pi_2);
    RotationMatrix<ACTIVE, float> dcm_yxz_active_m_pi_2(euler_yxz_singular_m_pi_2);
    RotationMatrix<ACTIVE, float> dcm_yzx_active_p_pi_2(euler_yzx_singular_p_pi_2);
    RotationMatrix<ACTIVE, float> dcm_yzx_active_m_pi_2(euler_yzx_singular_m_pi_2);
    RotationMatrix<ACTIVE, float> dcm_zxy_active_p_pi_2(euler_zxy_singular_p_pi_2);
    RotationMatrix<ACTIVE, float> dcm_zxy_active_m_pi_2(euler_zxy_singular_m_pi_2);
    RotationMatrix<ACTIVE, float> dcm_zyx_active_p_pi_2(euler_zyx_singular_p_pi_2);
    RotationMatrix<ACTIVE, float> dcm_zyx_active_m_pi_2(euler_zyx_singular_m_pi_2);
    RotationMatrix<ACTIVE, float> dcm_xyx_active_p_pi_0(euler_xyx_singular_p_pi_0);
    RotationMatrix<ACTIVE, float> dcm_xyx_active_p_pi_1(euler_xyx_singular_p_pi_1);
    RotationMatrix<ACTIVE, float> dcm_xzx_active_p_pi_0(euler_xzx_singular_p_pi_0);
    RotationMatrix<ACTIVE, float> dcm_xzx_active_p_pi_1(euler_xzx_singular_p_pi_1);
    RotationMatrix<ACTIVE, float> dcm_yxy_active_p_pi_0(euler_yxy_singular_p_pi_0);
    RotationMatrix<ACTIVE, float> dcm_yxy_active_p_pi_1(euler_yxy_singular_p_pi_1);
    RotationMatrix<ACTIVE, float> dcm_yzy_active_p_pi_0(euler_yzy_singular_p_pi_0);
    RotationMatrix<ACTIVE, float> dcm_yzy_active_p_pi_1(euler_yzy_singular_p_pi_1);
    RotationMatrix<ACTIVE, float> dcm_zxz_active_p_pi_0(euler_zxz_singular_p_pi_0);
    RotationMatrix<ACTIVE, float> dcm_zxz_active_p_pi_1(euler_zxz_singular_p_pi_1);
    RotationMatrix<ACTIVE, float> dcm_zyz_active_p_pi_0(euler_zyz_singular_p_pi_0);
    RotationMatrix<ACTIVE, float> dcm_zyz_active_p_pi_1(euler_zyz_singular_p_pi_1);

    RotationMatrix<PASSIVE, float> dcm_xyz_passive_p_pi_2(euler_xyz_singular_p_pi_2);
    RotationMatrix<PASSIVE, float> dcm_xyz_passive_m_pi_2(euler_xyz_singular_m_pi_2);
    RotationMatrix<PASSIVE, float> dcm_xzy_passive_p_pi_2(euler_xzy_singular_p_pi_2);
    RotationMatrix<PASSIVE, float> dcm_xzy_passive_m_pi_2(euler_xzy_singular_m_pi_2);
    RotationMatrix<PASSIVE, float> dcm_yxz_passive_p_pi_2(euler_yxz_singular_p_pi_2);
    RotationMatrix<PASSIVE, float> dcm_yxz_passive_m_pi_2(euler_yxz_singular_m_pi_2);
    RotationMatrix<PASSIVE, float> dcm_yzx_passive_p_pi_2(euler_yzx_singular_p_pi_2);
    RotationMatrix<PASSIVE, float> dcm_yzx_passive_m_pi_2(euler_yzx_singular_m_pi_2);
    RotationMatrix<PASSIVE, float> dcm_zxy_passive_p_pi_2(euler_zxy_singular_p_pi_2);
    RotationMatrix<PASSIVE, float> dcm_zxy_passive_m_pi_2(euler_zxy_singular_m_pi_2);
    RotationMatrix<PASSIVE, float> dcm_zyx_passive_p_pi_2(euler_zyx_singular_p_pi_2);
    RotationMatrix<PASSIVE, float> dcm_zyx_passive_m_pi_2(euler_zyx_singular_m_pi_2);
    RotationMatrix<PASSIVE, float> dcm_xyx_passive_p_pi_0(euler_xyx_singular_p_pi_0);
    RotationMatrix<PASSIVE, float> dcm_xyx_passive_p_pi_1(euler_xyx_singular_p_pi_1);
    RotationMatrix<PASSIVE, float> dcm_xzx_passive_p_pi_0(euler_xzx_singular_p_pi_0);
    RotationMatrix<PASSIVE, float> dcm_xzx_passive_p_pi_1(euler_xzx_singular_p_pi_1);
    RotationMatrix<PASSIVE, float> dcm_yxy_passive_p_pi_0(euler_yxy_singular_p_pi_0);
    RotationMatrix<PASSIVE, float> dcm_yxy_passive_p_pi_1(euler_yxy_singular_p_pi_1);
    RotationMatrix<PASSIVE, float> dcm_yzy_passive_p_pi_0(euler_yzy_singular_p_pi_0);
    RotationMatrix<PASSIVE, float> dcm_yzy_passive_p_pi_1(euler_yzy_singular_p_pi_1);
    RotationMatrix<PASSIVE, float> dcm_zxz_passive_p_pi_0(euler_zxz_singular_p_pi_0);
    RotationMatrix<PASSIVE, float> dcm_zxz_passive_p_pi_1(euler_zxz_singular_p_pi_1);
    RotationMatrix<PASSIVE, float> dcm_zyz_passive_p_pi_0(euler_zyz_singular_p_pi_0);
    RotationMatrix<PASSIVE, float> dcm_zyz_passive_p_pi_1(euler_zyz_singular_p_pi_1);

    // Then Convert to Euler Angle Again
    Euler<INTRINSIC, XYZ, float> euler_xyz_singular_p_pi_2_active(dcm_xyz_active_p_pi_2);
    Euler<INTRINSIC, XYZ, float> euler_xyz_singular_m_pi_2_active(dcm_xyz_active_m_pi_2);
    Euler<INTRINSIC, XZY, float> euler_xzy_singular_p_pi_2_active(dcm_xzy_active_p_pi_2);
    Euler<INTRINSIC, XZY, float> euler_xzy_singular_m_pi_2_active(dcm_xzy_active_m_pi_2);
    Euler<INTRINSIC, YXZ, float> euler_yxz_singular_p_pi_2_active(dcm_yxz_active_p_pi_2);
    Euler<INTRINSIC, YXZ, float> euler_yxz_singular_m_pi_2_active(dcm_yxz_active_m_pi_2);
    Euler<INTRINSIC, YZX, float> euler_yzx_singular_p_pi_2_active(dcm_yzx_active_p_pi_2);
    Euler<INTRINSIC, YZX, float> euler_yzx_singular_m_pi_2_active(dcm_yzx_active_m_pi_2);
    Euler<INTRINSIC, ZXY, float> euler_zxy_singular_p_pi_2_active(dcm_zxy_active_p_pi_2);
    Euler<INTRINSIC, ZXY, float> euler_zxy_singular_m_pi_2_active(dcm_zxy_active_m_pi_2);
    Euler<INTRINSIC, ZYX, float> euler_zyx_singular_p_pi_2_active(dcm_zyx_active_p_pi_2);
    Euler<INTRINSIC, ZYX, float> euler_zyx_singular_m_pi_2_active(dcm_zyx_active_m_pi_2);
    Euler<INTRINSIC, XYX, float> euler_xyx_singular_p_pi_0_active(dcm_xyx_active_p_pi_0);
    Euler<INTRINSIC, XYX, float> euler_xyx_singular_p_pi_1_active(dcm_xyx_active_p_pi_1);
    Euler<INTRINSIC, XZX, float> euler_xzx_singular_p_pi_0_active(dcm_xzx_active_p_pi_0);
    Euler<INTRINSIC, XZX, float> euler_xzx_singular_p_pi_1_active(dcm_xzx_active_p_pi_1);
    Euler<INTRINSIC, YXY, float> euler_yxy_singular_p_pi_0_active(dcm_yxy_active_p_pi_0);
    Euler<INTRINSIC, YXY, float> euler_yxy_singular_p_pi_1_active(dcm_yxy_active_p_pi_1);
    Euler<INTRINSIC, YZY, float> euler_yzy_singular_p_pi_0_active(dcm_yzy_active_p_pi_0);
    Euler<INTRINSIC, YZY, float> euler_yzy_singular_p_pi_1_active(dcm_yzy_active_p_pi_1);
    Euler<INTRINSIC, ZXZ, float> euler_zxz_singular_p_pi_0_active(dcm_zxz_active_p_pi_0);
    Euler<INTRINSIC, ZXZ, float> euler_zxz_singular_p_pi_1_active(dcm_zxz_active_p_pi_1);
    Euler<INTRINSIC, ZYZ, float> euler_zyz_singular_p_pi_0_active(dcm_zyz_active_p_pi_0);
    Euler<INTRINSIC, ZYZ, float> euler_zyz_singular_p_pi_1_active(dcm_zyz_active_p_pi_1);

    Euler<INTRINSIC, XYZ, float> euler_xyz_singular_p_pi_2_passive(dcm_xyz_passive_p_pi_2);
    Euler<INTRINSIC, XYZ, float> euler_xyz_singular_m_pi_2_passive(dcm_xyz_passive_m_pi_2);
    Euler<INTRINSIC, XZY, float> euler_xzy_singular_p_pi_2_passive(dcm_xzy_passive_p_pi_2);
    Euler<INTRINSIC, XZY, float> euler_xzy_singular_m_pi_2_passive(dcm_xzy_passive_m_pi_2);
    Euler<INTRINSIC, YXZ, float> euler_yxz_singular_p_pi_2_passive(dcm_yxz_passive_p_pi_2);
    Euler<INTRINSIC, YXZ, float> euler_yxz_singular_m_pi_2_passive(dcm_yxz_passive_m_pi_2);
    Euler<INTRINSIC, YZX, float> euler_yzx_singular_p_pi_2_passive(dcm_yzx_passive_p_pi_2);
    Euler<INTRINSIC, YZX, float> euler_yzx_singular_m_pi_2_passive(dcm_yzx_passive_m_pi_2);
    Euler<INTRINSIC, ZXY, float> euler_zxy_singular_p_pi_2_passive(dcm_zxy_passive_p_pi_2);
    Euler<INTRINSIC, ZXY, float> euler_zxy_singular_m_pi_2_passive(dcm_zxy_passive_m_pi_2);
    Euler<INTRINSIC, ZYX, float> euler_zyx_singular_p_pi_2_passive(dcm_zyx_passive_p_pi_2);
    Euler<INTRINSIC, ZYX, float> euler_zyx_singular_m_pi_2_passive(dcm_zyx_passive_m_pi_2);
    Euler<INTRINSIC, XYX, float> euler_xyx_singular_p_pi_0_passive(dcm_xyx_passive_p_pi_0);
    Euler<INTRINSIC, XYX, float> euler_xyx_singular_p_pi_1_passive(dcm_xyx_passive_p_pi_1);
    Euler<INTRINSIC, XZX, float> euler_xzx_singular_p_pi_0_passive(dcm_xzx_passive_p_pi_0);
    Euler<INTRINSIC, XZX, float> euler_xzx_singular_p_pi_1_passive(dcm_xzx_passive_p_pi_1);
    Euler<INTRINSIC, YXY, float> euler_yxy_singular_p_pi_0_passive(dcm_yxy_passive_p_pi_0);
    Euler<INTRINSIC, YXY, float> euler_yxy_singular_p_pi_1_passive(dcm_yxy_passive_p_pi_1);
    Euler<INTRINSIC, YZY, float> euler_yzy_singular_p_pi_0_passive(dcm_yzy_passive_p_pi_0);
    Euler<INTRINSIC, YZY, float> euler_yzy_singular_p_pi_1_passive(dcm_yzy_passive_p_pi_1);
    Euler<INTRINSIC, ZXZ, float> euler_zxz_singular_p_pi_0_passive(dcm_zxz_passive_p_pi_0);
    Euler<INTRINSIC, ZXZ, float> euler_zxz_singular_p_pi_1_passive(dcm_zxz_passive_p_pi_1);
    Euler<INTRINSIC, ZYZ, float> euler_zyz_singular_p_pi_0_passive(dcm_zyz_passive_p_pi_0);
    Euler<INTRINSIC, ZYZ, float> euler_zyz_singular_p_pi_1_passive(dcm_zyz_passive_p_pi_1);

    // Then Compare the Result
    for(size_t i = 0; i < 3; i++) {
        REQUIRE(fabs(euler_xyz_singular_p_pi_2(i) - euler_xyz_singular_p_pi_2_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_xyz_singular_m_pi_2(i) - euler_xyz_singular_m_pi_2_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_xzy_singular_p_pi_2(i) - euler_xzy_singular_p_pi_2_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_xzy_singular_m_pi_2(i) - euler_xzy_singular_m_pi_2_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_yxz_singular_p_pi_2(i) - euler_yxz_singular_p_pi_2_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_yxz_singular_m_pi_2(i) - euler_yxz_singular_m_pi_2_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_yzx_singular_p_pi_2(i) - euler_yzx_singular_p_pi_2_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_yzx_singular_m_pi_2(i) - euler_yzx_singular_m_pi_2_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_zxy_singular_p_pi_2(i) - euler_zxy_singular_p_pi_2_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_zxy_singular_m_pi_2(i) - euler_zxy_singular_m_pi_2_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_zyx_singular_p_pi_2(i) - euler_zyx_singular_p_pi_2_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_zyx_singular_m_pi_2(i) - euler_zyx_singular_m_pi_2_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_xyx_singular_p_pi_0(i) - euler_xyx_singular_p_pi_0_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_xyx_singular_p_pi_1(i) - euler_xyx_singular_p_pi_1_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_xzx_singular_p_pi_0(i) - euler_xzx_singular_p_pi_0_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_xzx_singular_p_pi_1(i) - euler_xzx_singular_p_pi_1_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_yxy_singular_p_pi_0(i) - euler_yxy_singular_p_pi_0_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_yxy_singular_p_pi_1(i) - euler_yxy_singular_p_pi_1_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_yzy_singular_p_pi_0(i) - euler_yzy_singular_p_pi_0_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_yzy_singular_p_pi_1(i) - euler_yzy_singular_p_pi_1_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_zxz_singular_p_pi_0(i) - euler_zxz_singular_p_pi_0_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_zxz_singular_p_pi_1(i) - euler_zxz_singular_p_pi_1_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_zyz_singular_p_pi_0(i) - euler_zyz_singular_p_pi_0_active(i)) < 1e-4f);
        REQUIRE(fabs(euler_zyz_singular_p_pi_1(i) - euler_zyz_singular_p_pi_1_active(i)) < 1e-4f);

        REQUIRE(fabs(euler_xyz_singular_p_pi_2(i) - euler_xyz_singular_p_pi_2_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_xyz_singular_m_pi_2(i) - euler_xyz_singular_m_pi_2_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_xzy_singular_p_pi_2(i) - euler_xzy_singular_p_pi_2_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_xzy_singular_m_pi_2(i) - euler_xzy_singular_m_pi_2_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_yxz_singular_p_pi_2(i) - euler_yxz_singular_p_pi_2_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_yxz_singular_m_pi_2(i) - euler_yxz_singular_m_pi_2_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_yzx_singular_p_pi_2(i) - euler_yzx_singular_p_pi_2_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_yzx_singular_m_pi_2(i) - euler_yzx_singular_m_pi_2_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_zxy_singular_p_pi_2(i) - euler_zxy_singular_p_pi_2_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_zxy_singular_m_pi_2(i) - euler_zxy_singular_m_pi_2_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_zyx_singular_p_pi_2(i) - euler_zyx_singular_p_pi_2_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_zyx_singular_m_pi_2(i) - euler_zyx_singular_m_pi_2_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_xyx_singular_p_pi_0(i) - euler_xyx_singular_p_pi_0_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_xyx_singular_p_pi_1(i) - euler_xyx_singular_p_pi_1_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_xzx_singular_p_pi_0(i) - euler_xzx_singular_p_pi_0_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_xzx_singular_p_pi_1(i) - euler_xzx_singular_p_pi_1_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_yxy_singular_p_pi_0(i) - euler_yxy_singular_p_pi_0_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_yxy_singular_p_pi_1(i) - euler_yxy_singular_p_pi_1_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_yzy_singular_p_pi_0(i) - euler_yzy_singular_p_pi_0_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_yzy_singular_p_pi_1(i) - euler_yzy_singular_p_pi_1_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_zxz_singular_p_pi_0(i) - euler_zxz_singular_p_pi_0_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_zxz_singular_p_pi_1(i) - euler_zxz_singular_p_pi_1_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_zyz_singular_p_pi_0(i) - euler_zyz_singular_p_pi_0_passive(i)) < 1e-4f);
        REQUIRE(fabs(euler_zyz_singular_p_pi_1(i) - euler_zyz_singular_p_pi_1_passive(i)) < 1e-4f);
    };
}