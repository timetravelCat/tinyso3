#include <tinyso3/Euler.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using namespace tinyso3;

TEST_CASE("Euler") {
    // Create Euler Angle of All Sequences
    Euler<XYZ, float> euler_xyz(0.1f, 0.2f, 0.3f);
    Euler<XZY, float> euler_xzy(0.1f, 0.2f, 0.3f);
    Euler<YXZ, float> euler_yxz(0.1f, 0.2f, 0.3f);
    Euler<YZX, float> euler_yzx(0.1f, 0.2f, 0.3f);
    Euler<ZXY, float> euler_zxy(0.1f, 0.2f, 0.3f);
    Euler<ZYX, float> euler_zyx(0.1f, 0.2f, 0.3f);
    Euler<XYX, float> euler_xyx(0.1f, 0.2f, 0.3f);
    Euler<XZX, float> euler_xzx(0.1f, 0.2f, 0.3f);
    Euler<YXY, float> euler_yxy(0.1f, 0.2f, 0.3f);
    Euler<YZY, float> euler_yzy(0.1f, 0.2f, 0.3f);
    Euler<ZXZ, float> euler_zxz(0.1f, 0.2f, 0.3f);
    Euler<ZYZ, float> euler_zyz(0.1f, 0.2f, 0.3f);

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
    Euler<XYZ, float> euler_xyz_active(dcm_active_xyz);
    Euler<XZY, float> euler_xzy_active(dcm_active_xzy);
    Euler<YXZ, float> euler_yxz_active(dcm_active_yxz);
    Euler<YZX, float> euler_yzx_active(dcm_active_yzx);
    Euler<ZXY, float> euler_zxy_active(dcm_active_zxy);
    Euler<ZYX, float> euler_zyx_active(dcm_active_zyx);
    Euler<XYX, float> euler_xyx_active(dcm_active_xyx);
    Euler<XZX, float> euler_xzx_active(dcm_active_xzx);
    Euler<YXY, float> euler_yxy_active(dcm_active_yxy);
    Euler<YZY, float> euler_yzy_active(dcm_active_yzy);
    Euler<ZXZ, float> euler_zxz_active(dcm_active_zxz);
    Euler<ZYZ, float> euler_zyz_active(dcm_active_zyz);

    Euler<XYZ, float> euler_xyz_passive(dcm_passive_xyz);
    Euler<XZY, float> euler_xzy_passive(dcm_passive_xzy);
    Euler<YXZ, float> euler_yxz_passive(dcm_passive_yxz);
    Euler<YZX, float> euler_yzx_passive(dcm_passive_yzx);
    Euler<ZXY, float> euler_zxy_passive(dcm_passive_zxy);
    Euler<ZYX, float> euler_zyx_passive(dcm_passive_zyx);
    Euler<XYX, float> euler_xyx_passive(dcm_passive_xyx);
    Euler<XZX, float> euler_xzx_passive(dcm_passive_xzx);
    Euler<YXY, float> euler_yxy_passive(dcm_passive_yxy);
    Euler<YZY, float> euler_yzy_passive(dcm_passive_yzy);
    Euler<ZXZ, float> euler_zxz_passive(dcm_passive_zxz);
    Euler<ZYZ, float> euler_zyz_passive(dcm_passive_zyz);

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
}