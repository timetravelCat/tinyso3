#include <tinyso3/tinyso3.hpp>
#include <stdio.h>

using namespace tinyso3;

int main(int argc, char const* argv[]) {
    (void)argc;
    (void)argv;

    /**
     * @brief Matrix Creation
     * 
     * Create a 4x3 matrix with float elements.
     * [1    2   3]
     * [4    5   6]
     * [7    8   9]
     * [10  11  12]
     */
    Matrix<4, 3, float> A = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f, 10.f, 11.f, 12.f};

    /**
     * @brief Square Matrix Creation
     * 
     * Create a 3x3 square matrix with float elements.
     * [1   2   3]
     * [4   5   6]
     * [7   8   9]
     */
    float data[3][3] = {{1.f, 2.f, 3.f}, {4.f, 5.f, 6.f}, {7.f, 8.f, 9.f}};
    SquareMatrix<3, float> B(data);

    // Matrix creations by static Method : Identity, Zero, NaN matrix
    SquareMatrix<3, float> Identity = SquareMatrix<3, float>::Identity();
    SquareMatrix<3, float> Zero = Matrix<3, 3, float>::Null();
    SquareMatrix<3, float> NaN = SquareMatrix<3, float>::NaN();

    // Cast to double
    SquareMatrix<3, double> IdentityDouble = Identity.cast<double>();

    // Matrix Access by Index (row, column)
    B(0, 0) = 10.f;
    B(1, 1) = 11.f;
    B(2, 2) = 12.f;

    // Matrix arithmetic operations
    Matrix<4, 3, float> C = A * B;
    C = C * (1.0f - Identity * 2.0f + Zero + 3.f);

    // Slice and col row operations
    Vector<4, float> v4 = C.slice<4, 1>(0, 0);
    C.setCol(2, v4);
    v4 = C.slice<0, 0, 4, 1>();

    Vector3<float> v3 = C.slice<3, 1>(1, 1);
    C.setRow<1>(v3.T());
    v3 = C.slice<1, 1, 3, 1>();
    v4 = C.col<2>();
    C.setBlock(0, 0, v4);
    v4 = C.col(2);
    C.setBlock(0, 2, v4);
    v3 = C.row<2>().transpose();
    C.setBlock(1, 0, v3);
    v3 = C.row(2).transpose();
    C.setBlock(1, 1, v3);

    // Vector operations
    v4.normalize();
    float squaredNorm = v3.squaredNorm();
    float norm = v3.norm();
    float dot = v4.dot(v4);
    Vector3<float> cross = v3.cross(v3);

    // Skew and vee operations
    SquareMatrix<3, float> skew = v3.hat();
    v3 = skew.vee();

    // 3D rotation representations
    Euler<INTRINSIC, ZYX, float> euler = {0.1f, 0.2f, 0.3f};
    RotationMatrix<ACTIVE, float> rotation_matrix{euler};
    AxisAngle<float> axis_angle{rotation_matrix};

    rotation_matrix = Euler<INTRINSIC, ZYX, float>{0.1f, 0.2f, 0.3f};
    euler = rotation_matrix;
    rotation_matrix = AxisAngle<float>{Vector3<float>{0.1f, 0.2f, 0.3f}, 0.4f}; // axis, angle

    // Default template parameters can be configured by "make config" on bash script or manually in the config.hpp
    Euler<> euler2 = rotation_matrix;
    AxisAngle<> axis_angle2 = euler2;
    RotationMatrix<> rotation_matrix2 = axis_angle2;

    RotationMatrix<> rotation_matrix_x = RotationMatrix<>::RotatePrincipalAxis<X>(0.1f);
    RotationMatrix<> rotation_matrix_y = RotationMatrix<>::RotatePrincipalAxis<Y>(0.2f);
    RotationMatrix<> rotation_matrix_z = RotationMatrix<>::RotatePrincipalAxis<Z>(0.3f);
    RotationMatrix<> rotation_matrix_xyz = rotation_matrix_x * rotation_matrix_y * rotation_matrix_z;
    rotation_matrix_xyz.normalize();
    rotation_matrix_xyz.interpolate(rotation_matrix2, 0.5f);

    // Conversion between angular velocity and Euler rate
    AngularVelocity<float> angular_velocity{0.1f, 0.2f, 0.3f};
    EulerRate<INTRINSIC, ZYX, float> euler_rate{angular_velocity};
    angular_velocity = euler_rate;

    return 0;
}
