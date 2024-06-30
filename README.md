# tinyso3
TinySO3 is a compact and efficient library designed to handle 3D rotations using various mathematical representations including rotation matrices, quaternions, and Lie groups (SO(3)). Whether you're working on robotics, computer graphics, or aerospace applications, TinySO3 provides the essential tools for managing and manipulating 3D rotational data with precision and ease.

[Theory document](https://timetravelcat.github.io/tinyso3/)

# Features
- Rotation Matrices: Functions for creating, transforming, and composing rotation matrices.
  - Supported Convention : **Passive(Alias)** and **Active(Alibi)** 
- Quaternions: Comprehensive support for quaternion algebra, including conversion, interpolation, and normalization.
  - Supported Convention : **Hamilton** and **JPL**
- Axis Angle: Tools for representing and converting rotations using the axis-angle representation.
- Euler Angles: Support for multiple Euler angle conventions and conversion between Euler angles and other representations.
  - Supported Convention : **Intrinsic** and **Extrinsic**
  - All 12 representation of euler angles are supported, including **Tait-Bryan** and **Proper**.
- Lie Groups: Efficient methods for working with Lie group representations of rotations, specifically SO(3).
- Interoperability: Seamless conversion between different rotation representations.
- Conversion between **Euler Rate** and **Angular Velocity**
- Performance: Optimized for speed and minimal memory usage, making it suitable for real-time applications.
- C++11 [Header-Only](!https://en.wikipedia.org/wiki/Header-only) library.
- Standard C++ library is not required.
- No dynamic allocations.

# Installation
**tinyso3** has no dependencies except testing(disabled by default). 

**tinyso3** follows general steps of CMake projects.

Before installation, you can configure default template arguments.
```bash
pip install kconfiglib
make config
```
Or manually configure [config.hpp](include/tinyso3/config.hpp), [version.hpp](include/tinyso3/version.hpp)


## Option 1 (CMake)
```bash
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -- -j
cmake --install .
```
```cmake
find_package(tinyso3 REQUIRED)
add_executable(myapp main.cpp)
target_link_library(myapp PRIVATE tinyso3::tinyso3)
```
## Option 2 (CMake FetchContents)
```cmake
include(FetchContent)
FetchContent_Declare(tinyso3 GIT_REPOSITORY
https://github.com/timetravelCat/tinyso3)
FetchContent_MakeAvailable(tinyso3)
...
target_link_libraries(myapp PRIVATE tinyso3)
```
## Option 3 (Copy & Paste)
Copy include/tinyso3 folder to your project. C++11 compiler is required.

# Tutorials
See the test directory for detailed examples.
```cpp
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
```

# Development
## Running the tests
- Install [Catch2 v3.4 or higher](https://github.com/catchorg/Catch2)
```bash
mkdir -p build && cd build
cmake .. -DBUILD_TESTING=ON
cmake --build . -- -j
ctest # or make test
```

## Formatting
- Install [clang-format](https://clang.llvm.org/docs/ClangFormat.html) and [cmake-format](https://cmake-format.readthedocs.io/en/latest/)
```bash
pip install cmake-format
sudo apt install clang-format 
```
```bash
make format # all c++ files and cmake files will be formatted.
```
- If you are using vscode, install clang-format extension.

## Static Analyzers
```bash
sudo apt install cppcheck clang-tidy
```

## Documentations
```bash
sudo apt install mkdocs mkdocs-material pymdown-extensions mkdocs-dracula-theme 
mkdocs build
mkdocs serve
```

# License
This project is licensed under the [BSD-3-Clause](https://opensource.org/license/bsd-3-clause) - see the
[LICENSE](LICENSE) file for details

# Contact
timetravelCat - timetraveler930@gmail.com