# Rotational Kinematics
Here, Three topics are described.

 * Definition of angular velocity
 * Derivative of Rotation Matrix 
 * Relationship between **Angular Velocity** and **Euler Rate**

-----------------------------
## Definition of angular velocity

Let frame $\vec{B}$ rotate with respect to frame $\vec{I}$.

The angular velocity of frame $\vec{B}$ respect to frame $\vec{I}$ is denoted by $\vec{\omega}_{BI} = -\vec{\omega}_{IB}$

Starts with a basic theorem, without demonstration, 

$$
\dot{\vec{I}}^T =  0, \ \ \dot{\vec{B}}^T =  \vec{\omega}_{BI} \times \vec{B}^T
$$

---------------------------
## Derivative of Rotation Matrix

$$B^T R_{BI} = I^T$$

Take derivative of both side,

$$\vec{\omega}_{BI} \times \vec{B}^TR_{BI} + \vec{B}^T \dot{R}_{BI} = \vec{B}^T \vec{\omega}_{BI}^B \times \vec{B}^TR_{BI} + \vec{B}^T \dot{R}_{BI} = 0$$

$$\therefore \ \ \dot{R}_{BI}= R_{BI} [\vec{\omega}_{BI}^B]^\times$$

or, from

$$I^T R_{IB} = B^T$$

derive 

$$\therefore \ \ \dot{R}_{IB}= - [\vec{\omega}_{BI}^B]^\times R_{IB}$$

-----------------------------
## Relationship between **Angular Velocity** and **Euler Rate**

1. PASSIVE or ACTIVE does not affects relationship between **Angular Velocity** and **Euler Rate**.

2. However, **Intrinsic** or **Extrinsic** affects relationship between **Angular Velocity** and **Euler Rate**.

3. Here we derive relationship between **Angular Velocity** and **Euler Rate** of generalized euler angle $\alpha \rightarrow \beta \rightarrow \gamma$ with arbitrary axis of rotation.

### Case of Intrinsic Euler Angle

$R = R_{\gamma \leftarrow \beta \leftarrow \alpha \leftarrow I} = R_{\gamma}R_{\beta}R_{\alpha}$ (PASSIVE)

In case of principal axis rotation, 

$$\therefore \ \ -\dot{R_i}R_i^T= [1_i]^\times{\dot{\theta}}_i$$

and using,

$$[Rv]^\times=Rv^\times R^T$$

$$
\dot{R}=\dot{R}_\gamma R_\beta R_\alpha + R_\gamma \dot{R}_\beta R_\alpha + R_\gamma R_\beta \dot{R}_\alpha = - [\omega]^\times (R_\gamma R_\beta R_\alpha)
$$

$$
\therefore \ \ \omega = [R_\gamma R_\beta 1_1 \ \ R_\gamma 1_2 \ \ 1_3]
\begin{bmatrix}
\dot{\alpha} \\
\dot{\beta} \\ 
\dot{\gamma} 
\end{bmatrix}
$$

### Case of Extrinsic Euler Angle

$R = R_{I \rightarrow \alpha \rightarrow \beta \rightarrow \gamma} = R_{\alpha}R_{\beta}R_{\gamma}$ (PASSIVE)

$$
\therefore \ \ \omega = [1_1 \ \ R_\alpha 1_2 \ \ R_\alpha R_\beta 1_1]
\begin{bmatrix}
\dot{\alpha} \\
\dot{\beta} \\ 
\dot{\gamma} 
\end{bmatrix}
$$
