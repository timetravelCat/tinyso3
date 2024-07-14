/**
 * @file tutorial.cpp
 * 
 * A simple tutorial for TinySO(3).
 */
#include <tinyso3/tinyso3.hpp>

using namespace tinyso3;

int main(int argc, char const* argv[]) {
    /**
     * Basic Matrix and Vector operations
     */
    float matrix_43_data[4][3] = {
      {01.f, 02.f, 03.f},
      {04.f, 05.f, 06.f},
      {07.f, 08.f, 09.f},
      {10.f, 11.f, 12.f}};

    float matrix_34_data[3][4] = {
      {01.f, 02.f, 03.f, 04.f},
      {05.f, 06.f, 07.f, 08.f},
      {09.f, 10.f, 11.f, 12.f}};

    Matrix<4, 3, float> matrix_43(matrix_43_data);
    Matrix<3, 4, float> matrix_34(matrix_34_data);

    SquareMatrix<4, float> matrix_44 = matrix_43 * matrix_34;
    Vector<4, float> vector_4 = matrix_44.slice<4, 1>(0, 2);
    Vector3<float> vector3 = vector_4.slice<3, 1>(1, 0);
    vector3 -= SquareMatrix<3, float>::Identity().diag() * 2.f;
    vector3.normalize();
    vector3 = vector3.hat().vee();

    /**
     * 3D Rotation Representations
     */
    Euler<INTRINSIC, ZYX, float> euler{0.1f, 0.2f, 0.3f};
    Quaternion<HAMILTON, float> quaternion = euler;
    AxisAngle<float> axis_angle = quaternion;
    RotationMatrix<ACTIVE, float> rotation_matrix = axis_angle;

    /**
     * Rotate vectors
     */
    vector3 = rotation_matrix * vector3;
    vector3 = quaternion * vector3;

    /**
     * Normalize quaternion or rotation matrix
     */
    quaternion.normalize();
    rotation_matrix.normalize();

    /**
     * Interpolation between two rotations
     */
    Euler<INTRINSIC, ZYX, float> euler_compare{0.2f, 0.3f, 0.4f};
    Quaternion<HAMILTON, float> quaternion_compare = euler_compare;
    Quaternion<HAMILTON, float> quaternion_interpolated = quaternion.slerp(quaternion_compare, 0.5f);
    RotationMatrix<ACTIVE, float> rotation_matrix_compare = euler_compare;
    RotationMatrix<ACTIVE, float> rotation_matrix_interpolated = rotation_matrix.interpolate(rotation_matrix_compare, 0.5f);

    /**
     * Conversion between angular velocity and Euler rate
     */
    AngularVelocity<float> angular_velocity(Vector3<float>{0.1f, 0.2f, 0.3f});
    EulerRate<INTRINSIC, ZYX, float> euler_rate = angular_velocity;
    angular_velocity = euler_rate;

    return 0;
}
