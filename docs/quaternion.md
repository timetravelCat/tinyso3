# Quaternion 
A quaternion is a four-dimensional complex number used to represent rotations in 3D space. It offers a compact and efficient way to encode rotation without suffering from gimbal lock, which can occur with Euler angles. Quaternions are widely used in various applications such as computer graphics, robotics, and aerospace.

A quaternion $q$ is typically expressed as:

$$ q = w + xi + yj + zk $$

Where $w, x, y, z$ are real numbers, and $ i, j, k $ are the fundamental quaternion units.

Alternatively, it can be written in vector form as:

### HAMILTON convention

$$ q = \begin{bmatrix} w \\ \vec{v} \end{bmatrix} = \begin{bmatrix} w \\ x \\ y \\ z \end{bmatrix} $$

### JPL convention
The Jet Propulsion Laboratory (JPL) convention differs from Hamilton in the sign of the vector part of the quaternion. It is typically used in aerospace applications.

$$ q = \begin{bmatrix} \vec{v} \\ w \end{bmatrix} = \begin{bmatrix} x \\ y \\ z \\ w \end {bmatrix} $$

Here, $w$ is the scalar part, and $\vec{v} = \begin{bmatrix} x \\ y \\ z \end{bmatrix}$ is the vector part.

## Quaternion Algebra

1. **Addition**: Quaternions are added component-wise:
   $$ q_1 + q_2 = (w_1 + w_2) + (x_1 + x_2)i + (y_1 + y_2)j + (z_1 + z_2)k $$

2. **Multiplication**: Quaternion multiplication is defined as:
   $$ q_1 q_2 = (w_1 w_2 - \vec{v}_1 \cdot \vec{v}_2) + (w_1 \vec{v}_2 + w_2 \vec{v}_1 + \vec{v}_1 \times \vec{v}_2) $$
   This can also be written in matrix form.

3. **Conjugate**: The conjugate of a quaternion is:
   $$ q^* = w - xi - yj - zk $$

4. **Norm**: The norm of a quaternion is:
   $$ \|q\| = \sqrt{w^2 + x^2 + y^2 + z^2} $$

5. **Inverse**: The inverse of a quaternion is:
   $$ q^{-1} = \frac{q^*}{\|q\|^2} $$

## Rotation Representation

To represent a rotation by an angle $\theta$ around a unit vector $\hat{u}$:

$$ q = \cos\left(\frac{\theta}{2}\right) + \hat{u} \sin\left(\frac{\theta}{2}\right) $$

Where $\hat{u} = \begin{bmatrix} u_x \\ u_y \\ u_z \end{bmatrix}$ is the axis of rotation.

## Applying Rotation

To rotate a vector $\vec{v}$ using a quaternion $q$:

1. Convert the vector to a quaternion with a zero scalar part:
   $$ \vec{v} \rightarrow q_v = 0 + v_x i + v_y j + v_z k $$

2. Perform the rotation:
   $$ q' = q q_v q^{-1} $$

The resulting vector $\vec{v}'$ is extracted from $q'$.

## Composition of Multiple Quaternions

In the Hamilton convention, quaternion multiplication is used to compose rotations. If you have two quaternions, $q_1$ and $q_2$, representing two rotations, the composition of these rotations is achieved by multiplying the quaternions.

The product of two quaternions $q_1$ and $q_2$ is:

Where:

$$q_1 = w_1 + x_1 i + y_1 j + z_1 k$$

$$q_2 = w_2 + x_2 i + y_2 j + z_2 k$$

The resulting quaternion $q$ is:

$$ q = (w_1 w_2 - x_1 x_2 - y_1 y_2 - z_1 z_2) + (w_1 x_2 + x_1 w_2 + y_1 z_2 - z_1 y_2) i + (w_1 y_2 + y_1 w_2 + z_1 x_2 - x_1 z_2) j + (w_1 z_2 + z_1 w_2 + x_1 y_2 - y_1 x_2) k $$

## Spherical Linear Interpolation (SLERP)

SLERP is used to interpolate smoothly between two quaternions. It ensures constant angular velocity and produces the shortest path on the unit sphere.

Given two quaternions $q_1$ and $q_2$, SLERP between them for $t \in [0, 1]$ is defined as:

$$ \text{slerp}(q_1, q_2, t) = \frac{\sin((1 - t) \theta) q_1 + \sin(t \theta) q_2}{\sin(\theta)} $$

Where $ \theta $ is the angle between $q_1$ and $q_2$:

$$ \cos(\theta) = q_1 \cdot q_2 $$


