# tinyso3
tinsso3 is a compact and efficient library designed to handle 3D rotations using various mathematical representations including rotation matrices, quaternions, and Lie groups (SO(3)). Whether you're working on robotics, computer graphics, or aerospace applications, tinsso3 provides the essential tools for managing and manipulating 3D rotational data with precision and ease.

[repository link](https://github.com/timetravelCat/tinyso3).

tinsso3 implements and demonstrates each of these representations and their interconversions, along with practical examples and applications in 3D rotation and kinematics.

Each representation of 3D rotations has its advantages and limitations. **Rotation Matrices** are straightforward but can be redundant. **Euler Angles** are intuitive but can suffer from gimbal lock. **Axis-Angle** is compact and great for interpolation, while **Quaternions** provide a robust solution for smooth rotations without gimbal lock. Rotational Kinematics provides the framework to understand and predict rotational movements over time.

-----------------------------------

## Special advantage of tinyso3

tinyso3 try to cover all **ambiguous** conventions used by various fields. 

[**Rotation Matrix**](rotation_matrix.md)

- ***ACTIVE(ALIBI) and PASSIVE(ALIAS)*** 

[**Euler Angles**](euler_angles.md)

- ***Intrinsic and Extrinsic*** 
- ***Proper(XYX, XZX, YXY, YZY, ZXZ, ZYZ) and Tait-Bryan(XYZ, XZY, YXZ, YZX, ZXY, ZYX)***

[**Axis-Angle**](axis_angle.md)

[**Quaternion**](quaternion.md)

- ***Hamilton and JPL***

[**Rotational Kinematics**](rotational_kinematics.md)