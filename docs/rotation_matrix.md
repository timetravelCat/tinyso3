# Rotation Matrix
A rotation matrix is a way to describe a relationship between cartesian coordinate system.

Reference coordinate system is referred as **Global** | **World** | **Inertial** | **Fixed**

The other one is referred as **Local** | **Body** | **Relative** | **Moving**

In this section, we refer **Inertial** as a reference coordinate system, and **Body** as the other coordinate system.

Here, we denote **Inertial** and **Body** frame as

$$
\vec{I}=
\begin{bmatrix}
\vec{I}_x \\
\vec{I}_y \\
\vec{I}_z \\
\end{bmatrix},\ 
\vec{B}=
\begin{bmatrix}
\vec{B}_x \\
\vec{B}_y \\
\vec{B}_z \\
\end{bmatrix}
$$

A (arbitrary) vector expressed in each frame, $v_I$ and $v_B$ is the component of vector expressed in each frame.

$$\vec{v}=\vec{I}^Tv_I=\vec{B}^Tv_B$$

Relationship between $v_I$ and $v_B$

$$
v_B=B \cdot \vec{I}^T v_I = R_{BI} v_I
= \begin{bmatrix}
\vec{B}_x \cdot \vec{I}_x \ \ \ \   \vec{B}_x \cdot \vec{I}_y \ \ \ \   \vec{B}_x \cdot \vec{I}_z \\
\vec{B}_y \cdot \vec{I}_x \ \ \ \   \vec{B}_y \cdot \vec{I}_y \ \ \ \   \vec{B}_y \cdot \vec{I}_z \\
\vec{B}_z \cdot \vec{I}_x \ \ \ \   \vec{B}_z \cdot \vec{I}_y \ \ \ \   \vec{B}_z \cdot \vec{I}_z \\
\end{bmatrix} v_I
$$

$$
v_I=I \cdot \vec{B}^T v_B = R_{IB} v_B
= \begin{bmatrix}
\vec{I}_x \cdot \vec{B}_x \ \ \ \   \vec{I}_x \cdot \vec{B}_y \ \ \ \   \vec{I}_x \cdot \vec{B}_z \\
\vec{I}_y \cdot \vec{B}_x \ \ \ \   \vec{I}_y \cdot \vec{B}_y \ \ \ \   \vec{I}_y \cdot \vec{B}_z \\
\vec{I}_z \cdot \vec{B}_x \ \ \ \   \vec{I}_z \cdot \vec{B}_y \ \ \ \   \vec{I}_z \cdot \vec{B}_z \\
\end{bmatrix} v_B
$$

Hence, 

$$R_{BI}=R_{IB}^T= R_{IB}^{-1}$$

$$R_{IB}=R_{BI}^T= R_{BI}^{-1}$$

------------------------------------
## ACTIVE(ALIBI) and PASSIVE(ALIAS) interpretation

### ACTIVE Interpretation
We want to rotate a vector from $\vec{v}$ to $\vec{v}'$, to have same component in body frame. 
$$
\vec{v} = \vec{I}^T\vec{v}_I
$$

$$
\vec{v}' = \vec{B}^T\vec{v}_I = \vec{I}^T\vec{v}'_I
$$

Hence, 

$$
\vec{v}'_I = \vec{I} \cdot \vec{B}^T\vec{v}_I = R_{IB} \vec{v}_I = R \vec{v}_I
$$

-----------------------------------
### PASSIVE Interpretation
We want to express a (same) vector in the body frame. 

$$
v_B=B \cdot \vec{I}^T v_I = R_{BI} v_I = R v_I
$$

Understandably, Rotation Matrix $R$ is different depend on the interpretations.

You need to properly select one of interpretation from context, when you read documents without explicit explanations. 

------------------------------------
## Principal Rotations

|               |                                                                  ACTIVE                                                                   |                                                                  PASSIVE                                                                  |
| :-----------: | :---------------------------------------------------------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------------------------------------------------------: |
| $R_x(\theta)$ | $\begin{bmatrix} 1 &  0            &  0           \\ 0 &  \cos \theta  & -\sin \theta \\ 0 &  \sin \theta & \cos \theta \\ \end{bmatrix}$ | $\begin{bmatrix} 1 &  0            &  0           \\ 0 &  \cos \theta  & \sin \theta \\ 0 &  -\sin \theta & \cos \theta \\ \end{bmatrix}$ |
| $R_y(\theta)$ |    $\begin{bmatrix}\cos \theta & 0 & \sin \theta \\0           & 1 &  0           \\-\sin  \theta & 0 &  \cos \theta \\\end{bmatrix}$     |     $\begin{bmatrix}\cos \theta & 0 & -\sin \theta \\0           & 1 &  0           \\\sin \theta & 0 &  \cos \theta \\\end{bmatrix}$     |
| $R_z(\theta)$ |     $\begin{bmatrix}\cos \theta & -\sin \theta & 0 \\\sin \theta &  \cos \theta & 0 \\0           &  0           & 1 \\\end{bmatrix}$     |     $\begin{bmatrix}\cos \theta & \sin \theta & 0 \\-\sin \theta &  \cos \theta & 0 \\0           &  0           & 1 \\\end{bmatrix}$     |

------------------------------------
## Exponential & Logarithm 
The matrix exponential is
$\exp(A) = 1 + A + \frac{1}{2!}A^2 + \frac{1}{3!}A^3+\cdots=\sum_{n=0}^{\infty}\frac{1}{n!}A^n$

$R=\exp({\mathbf{\hat{\phi}}})=\exp(\phi \hat{a})=\cos\phi+(1-\cos\phi)aa^T+\sin\phi\hat{a}$

$\phi=\cos^{-1}(\frac{tr(R)-1}{2}) + 2\pi m$

$\hat{a}=\frac{R-R^T}{2\sin\theta}$

$R^\alpha=\exp(\hat{\phi})^{\alpha}=\exp(\alpha\hat{\phi})$

------------------------------------
## Interpolation

$R = R_1(R_1^TR_2)^{\alpha}$ (ACTIVE)

$R = (R_2R_1^T)^{\alpha}R_1$ (PASSIVE)

------------------------------------
## Normalization
$R'=(RR^T)^{-\frac{1}{2}}R$

($A^{-\frac{1}{2}}=\frac{1}{\sqrt{\lambda_1}}e_1e_1^T+\frac{1}{\sqrt{\lambda_2}}e_2e_2^T+\frac{1}{\sqrt{\lambda_3}}e_3e_3^T$)

[EigenPair of 3x3 Symmetric Matrix](https://www.geometrictools.com/Documentation/RobustEigenSymmetric3x3.pdf)

Normalization of a (perturbed) rotation matrix is, find a new rotation matrix, close to the perturbed rotation matrix.

This can be formulated by, 

maximize 

$$J(R')=tr(R'R^T)-\frac{1}{2}\sum^{3}_{i=1}\sum^{3}_{j=1}\lambda_{ij}(r^{'T}_{i} r_j^{'} - \delta_{ij})$$

$\delta_{ij}$ is Kronecker delta, $R^T=[r_1 \ \ r_2 \ \ r_3]$, $(R')^T=[r_1^{'} \ \ r_2^{'} \ \ r_3^{'}]$

Take the derivative of $J$ with respect to the three rows of $R'$ and set to Zero.

$$
[r_1^{'} \ \ r_2^{'} \ \ r_3^{'}]
\begin{bmatrix} \lambda_{11} & \lambda_{12} & \lambda_{13} \\ \lambda_{21} & \lambda_{22} & \lambda_{23} \\ \lambda_{31} & \lambda_{32} & \lambda_{33} \\ \end{bmatrix}
= [r_1 \ \ r_2 \ \ r_3]
$$

due to symmetry of lagrange multiplier terms, $\lambda_{ij}=\lambda_{ji}$

$$\lambda R' = R, \ \  \lambda = \lambda ^ T$$

$$
\lambda ^ 2 = \lambda \lambda^T = RR^T \rightarrow \lambda = (RR^T)^\frac{1}{2}
$$

$$\ \ \therefore R'=(RR^T)^{-\frac{1}{2}}R$$