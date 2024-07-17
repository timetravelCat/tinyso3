# Euler Angles
[Representing Attitude: Euler Angles, Unit Quaternions, and Rotation Vectors](https://www.astro.rug.nl/software/kapteyn-beta/_downloads/attitude.pdf)

 * Euler angles are a way to describe the orientation of a rigid body in three-dimensional space. 
 * They are defined by three successive rotations around different axes. 
 * There are two main types of Euler angles: extrinsic and intrinsic.
 * There exists twelve possible sequences of rotation axes, divided in two groups.
    - **Proper Euler Angles (zxz, xyx, yzy, zyz, xzx, yxy)**
    - **Tait-Briyan angles (xyz, yzx, zxy, xzy, zyx, yxz)**
 * For first and last angle, the valid range could be [-$\pi$, $\pi$]
 * Second angle covers $\pi$ radians, it could be [$0$, $\pi$] or [-$\pi/2$, $\pi/2$]
    - **Proper Euler Angles** has gimbal lock on $n\pi$
    - **Tait-Briyan angles** has gimbal lock on $\pi/2 + n\pi$

---------------------------------

## Intrinsic Euler Angles
Intrinsic Euler angles describe rotations about the axes of a moving coordinate system (body frame). Here's how they work:

1. First Rotation (α): Rotate the object around its own axis.
2. Second Rotation (β): Rotate the object around its own axis, which has moved with the first rotation.
3. Third Rotation (γ): Rotate the object around its own axis, which has moved with the first two rotations.

Build **ACTIVE** Rotation matrix from **Intrinsic** Euler Angle

$R = R_{I \rightarrow \alpha \rightarrow \beta \rightarrow \gamma} = R_{\alpha}R_{\beta}R_{\gamma}$

Build **PASSIVE** Rotation matrix from **Intrinsic** Euler Angle

$R = R_{\gamma \leftarrow \beta \leftarrow \alpha \leftarrow I} = R_{\gamma}R_{\beta}R_{\alpha}$

(Be aware that $R_{?}$ is differ depends on ACTIVE or PASSIVE)

## Extrinsic Euler Angles
Extrinsic Euler angles describe rotations about the axes of a fixed coordinate system (global frame). Here's how they work:

1. First Rotation (α): Rotate the object around the fixed axis.
2. Second Rotation (β): Rotate the object around the fixed axis.
3. Third Rotation (γ): Rotate the object around the fixed axis.

Build **ACTIVE** Rotation matrix from **Extrinsic** Euler Angle

$R = R_{\gamma \leftarrow \beta \leftarrow \alpha \leftarrow I} = R_{\gamma}R_{\beta}R_{\alpha}$

Build **PASSIVE** Rotation matrix from **Extrinsic** Euler Angle

$R = R_{I \rightarrow \alpha \rightarrow \beta \rightarrow \gamma} = R_{\alpha}R_{\beta}R_{\gamma}$

(Be aware that $R_{?}$ is differ depends on ACTIVE or PASSIVE)

-----------------------------------

See [Representing Attitude: Euler Angles, Unit Quaternions, and Rotation Vectors](https://www.astro.rug.nl/software/kapteyn-beta/_downloads/attitude.pdf) for detailed derivation
   
   * This document describes about conversion between  **PASSIVE** Rotation matrix and **Intrinsic** Euler Angles.
   * This document uses $\psi$ as first angle of rotation, $\theta$ as second angle of rotation and $\phi$ as third angle of rotation.