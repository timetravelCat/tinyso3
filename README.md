<p align="center">
  <img src="docs/tinyso3.jpg" style="width: 30%;"/>
</p>

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

[tutorial.cpp](tutorial.cpp)

```cpp
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
pip3 install mkdocs mkdocs-material pymdown-extensions mkdocs-dracula-theme 
mkdocs build
mkdocs serve
```

# License
This project is licensed under the [BSD-3-Clause](https://opensource.org/license/bsd-3-clause) - see the
[LICENSE](LICENSE) file for details

# Contact
timetravelCat - timetraveler930@gmail.com

# Contributors 
Special thanks to [@lightAxis](https://github.com/lightAxis) who implemented the quaternion functionality.