# tinyso3
TinySO3 is a compact and efficient library designed to handle 3D rotations using various mathematical representations including rotation matrices, quaternions, and Lie groups (SO(3)). Whether you're working on robotics, computer graphics, or aerospace applications, TinySO3 provides the essential tools for managing and manipulating 3D rotational data with precision and ease.

## Features
- Rotation Matrices: Functions for creating, transforming, and composing rotation matrices.
- Quaternions: Comprehensive support for quaternion algebra, including conversion, interpolation, and normalization.
- Axis Angle: Tools for representing and converting rotations using the axis-angle representation.
- Euler Angles: Support for multiple Euler angle conventions and conversion between Euler angles and other representations.
- Lie Groups: Efficient methods for working with Lie group representations of rotations, specifically SO(3).
- Interoperability: Seamless conversion between different rotation representations.
- Performance: Optimized for speed and minimal memory usage, making it suitable for real-time applications.

## Example

### WIP
- Configuration Setup
- Set floating point type : float, double, long double ...
- Default setup : RotationMatrix : Active(Alibi) / Passive()  / Hamiltonion or JPL (quaternion -wxyz, xyzw) 
...

## Testing

## Formatting

### Requirements
- **cmake-format**
- **clang-format**
- **mkdocs**, **mkdocs-material**, **pymdown-extensions**
- **kconfiglib**
```
pip install cmake-format mkdocs mkdocs-material pymdown-extensions kconfiglib
sudo apt install clang-format 
```

## License
* (BSD) The Matrix library is licensed under a permissive 3-clause BSD license. Contributions must be made under the same license.
