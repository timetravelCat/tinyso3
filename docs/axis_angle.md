# Axis-Angle
[Rodrigues' rotation formula](https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula)

We denote a vector, $\vec{v}'$ from a vector, $\vec{v}$ rotated with a given axis of rotation $\vec{k}$ by an angle $\theta$. 

$$
\vec{v}'=\vec{v}\cos\theta+(\vec{k} \times \vec{v})\sin\theta + \vec{k}(\vec{k} \cdot \vec{v})(1-\cos\theta)=(I+\sin\theta(\vec{k}^\times)+(1-\cos\theta)(\vec{k}^\times)^2)\vec{v}
$$

$$
((\vec{k}^\times)^2 = \vec{k}\vec{k}^T - I)
$$

And this is exactly same context of **ACTIVE(ALIBI)** rotation matrix.

$$
R_{active}=I+\sin\theta(\vec{k}^\times)+(1-\cos\theta)(\vec{k}^\times)^2 
$$

As a **PASSIVE(ALIAS)** rotation matrix, you need to transpose the ACTIVE rotation matrix.

$$
R_{passive}=I-\sin\theta(\vec{k}^\times)+(1-\cos\theta)(\vec{k}^\times)^2 
$$

-------------------------
## Derive Axis-Angle from Rotation Matrix

$\theta=\cos^{-1}(\frac{tr(R)-1}{2}) + 2\pi m$

$\vec{k}^{\times}=\frac{R-R^T}{2\sin\theta}$ (ACTIVE)

$\vec{k}^{\times}=\frac{R^T-R}{2\sin\theta}$ (PASSIVE)


