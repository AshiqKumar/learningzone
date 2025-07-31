# Computer Vision Theory - Mathematical Foundations

## 📐 Mathematical Foundations of Computer Vision

### 1. Image Processing Fundamentals

#### 1.1 Digital Image Representation

A digital image is a 2D function I(x,y) where:
- (x,y) are spatial coordinates
- I(x,y) is the intensity value at position (x,y)
- For grayscale: I(x,y) ∈ [0, 255] (8-bit)
- For color: I(x,y) = [R(x,y), G(x,y), B(x,y)]

**Pixel Neighborhood**:
- **4-connectivity**: {(x±1,y), (x,y±1)}
- **8-connectivity**: {(x±1,y±1), (x±1,y), (x,y±1)}

#### 1.2 Convolution and Filtering

**2D Convolution**:
```
(I * K)(x,y) = ΣΣ I(m,n) × K(x-m, y-n)
               m n
```

Where:
- I: Input image
- K: Convolution kernel
- *: Convolution operator

**Properties**:
- Commutative: I * K = K * I
- Associative: (I * K₁) * K₂ = I * (K₁ * K₂)
- Linear: I * (aK₁ + bK₂) = a(I * K₁) + b(I * K₂)

**Common Kernels**:

*Gaussian Blur*:
```
G(x,y) = (1/2πσ²) × e^(-(x²+y²)/2σ²)
```

*Laplacian (Edge Detection)*:
```
[ 0  1  0]
[ 1 -4  1]
[ 0  1  0]
```

*Sobel X-direction*:
```
[-1  0  1]
[-2  0  2]
[-1  0  1]
```

### 2. Feature Detection Theory

#### 2.1 Edge Detection Mathematics

**Gradient-based Methods**:
- Gradient magnitude: |∇I| = √((∂I/∂x)² + (∂I/∂y)²)
- Gradient direction: θ = arctan(∂I/∂y / ∂I/∂x)

**Canny Edge Detection Steps**:
1. **Gaussian Smoothing**: I_smooth = I * G_σ
2. **Gradient Calculation**: G_x, G_y using Sobel operators
3. **Non-maximum Suppression**: Keep only local maxima
4. **Double Thresholding**: T_low < edge < T_high
5. **Edge Linking**: Connect strong edges through weak edges

**Mathematical Framework**:
```
Step 1: Smoothing
I_smooth(x,y) = Σ Σ G(i,j,σ) × I(x+i, y+j)

Step 2: Gradient
G_x = ∂I_smooth/∂x, G_y = ∂I_smooth/∂y
Magnitude = √(G_x² + G_y²)
Direction = arctan2(G_y, G_x)

Step 3: Non-maximum suppression
For each pixel, check if it's local maximum along gradient direction
```

#### 2.2 Corner Detection Theory

**Harris Corner Detector**:

The second moment matrix (structure tensor):
```
M = [Σ(I_x²)    Σ(I_x×I_y)]
    [Σ(I_x×I_y) Σ(I_y²)   ]
```

Where summation is over local window W.

**Eigenvalue Analysis**:
- λ₁, λ₂ are eigenvalues of M
- λ₁ ≈ λ₂ ≈ 0: uniform region
- λ₁ >> λ₂ ≈ 0: edge
- λ₁ ≈ λ₂ >> 0: corner

**Harris Response**:
```
R = det(M) - k × (trace(M))²
R = λ₁λ₂ - k(λ₁ + λ₂)²

Where k ∈ [0.04, 0.06]
```

**Corner Condition**:
- R > threshold: corner
- R < -threshold: edge
- |R| < threshold: uniform

### 3. Optical Flow Theory

#### 3.1 Brightness Constancy Assumption

**Fundamental Equation**:
```
I(x, y, t) = I(x + dx, y + dy, t + dt)
```

**Taylor Expansion**:
```
I(x+dx, y+dy, t+dt) ≈ I(x,y,t) + (∂I/∂x)dx + (∂I/∂y)dy + (∂I/∂t)dt
```

**Optical Flow Constraint**:
```
I_x × u + I_y × v + I_t = 0
```

Where:
- (u,v) = (dx/dt, dy/dt) is optical flow vector
- I_x, I_y, I_t are partial derivatives

#### 3.2 Lucas-Kanade Method

**Problem**: One equation, two unknowns (aperture problem)

**Solution**: Use local window W and assume constant flow

**System of Equations**:
```
For each pixel (i,j) in window W:
I_x(i,j) × u + I_y(i,j) × v = -I_t(i,j)
```

**Matrix Form**:
```
[I_x(1,1)  I_y(1,1)]       [-I_t(1,1)]
[I_x(1,2)  I_y(1,2)]  [u] = [-I_t(1,2)]
[   ...       ...   ]  [v]   [   ...  ]
[I_x(m,n)  I_y(m,n)]       [-I_t(m,n)]

A × v = b
```

**Least Squares Solution**:
```
v = (A^T A)^(-1) A^T b

Where A^T A = [Σ(I_x²)    Σ(I_x I_y)]
              [Σ(I_x I_y) Σ(I_y²)  ]
```

### 4. Geometric Transformations

#### 4.1 Homogeneous Coordinates

**2D Point Representation**:
```
Cartesian: (x, y)
Homogeneous: [x, y, 1]^T or [wx, wy, w]^T
```

**Transformation Types**:

*Translation*:
```
[x']   [1  0  t_x] [x]
[y'] = [0  1  t_y] [y]
[1 ]   [0  0   1 ] [1]
```

*Rotation*:
```
[x']   [cos(θ) -sin(θ)  0] [x]
[y'] = [sin(θ)  cos(θ)  0] [y]
[1 ]   [  0       0     1] [1]
```

*Scaling*:
```
[x']   [s_x  0   0] [x]
[y'] = [ 0  s_y  0] [y]
[1 ]   [ 0   0   1] [1]
```

*General Affine*:
```
[x']   [a  b  c] [x]
[y'] = [d  e  f] [y]
[1 ]   [0  0  1] [1]
```

#### 4.2 Projective Transformations (Homography)

**Full Projective Transformation**:
```
[x']   [h₁₁ h₁₂ h₁₃] [x]
[y'] = [h₂₁ h₂₂ h₂₃] [y]
[w']   [h₃₁ h₃₂ h₃₃] [1]
```

**Normalized Form**:
```
x' = (h₁₁x + h₁₂y + h₁₃) / (h₃₁x + h₃₂y + h₃₃)
y' = (h₂₁x + h₂₂y + h₂₃) / (h₃₁x + h₃₂y + h₃₃)
```

### 5. Statistical Methods

#### 5.1 RANSAC (Random Sample Consensus)

**Algorithm Steps**:
1. Randomly select minimum sample set
2. Fit model to sample
3. Count inliers (points within threshold)
4. Repeat for N iterations
5. Return model with most inliers

**Mathematical Framework**:
- Probability of outlier: ε
- Sample size: s
- Probability of good sample: (1-ε)^s
- Probability of failure in N iterations: [1-(1-ε)^s]^N
- Required iterations: N = log(η) / log(1-(1-ε)^s)

Where η is desired probability of success.

#### 5.2 Probability Distributions in Vision

**Gaussian Distribution**:
```
N(x; μ, σ²) = (1/√(2πσ²)) × exp(-(x-μ)²/2σ²)
```

**Multivariate Gaussian**:
```
N(x; μ, Σ) = 1/√((2π)^k|Σ|) × exp(-½(x-μ)^T Σ^(-1) (x-μ))
```

**Applications**:
- Noise modeling in images
- Feature descriptor distributions
- Kalman filter state estimation
- Gaussian mixture models for background subtraction

### 6. Information Theory in Vision

#### 6.1 Entropy and Information

**Shannon Entropy**:
```
H(X) = -Σ P(x) log₂ P(x)
```

**Mutual Information**:
```
I(X;Y) = Σ Σ P(x,y) log₂(P(x,y)/(P(x)P(y)))
```

**Applications**:
- Image registration (maximize mutual information)
- Feature selection (maximum information gain)
- Compression and encoding

#### 6.2 Histogram Analysis

**Image Histogram**:
```
h(i) = number of pixels with intensity i
```

**Normalized Histogram**:
```
p(i) = h(i) / (total number of pixels)
```

**Histogram Equalization**:
```
s = T(r) = (L-1) × Σ(k=0 to r) p(k)
```

Where:
- r: input intensity level
- s: output intensity level  
- L: number of intensity levels (256 for 8-bit)

### 7. Linear Algebra in Computer Vision

#### 7.1 Singular Value Decomposition (SVD)

For matrix A (m×n):
```
A = UΣV^T
```

Where:
- U (m×m): left singular vectors
- Σ (m×n): diagonal matrix of singular values
- V (n×n): right singular vectors

**Applications**:
- Principal Component Analysis (PCA)
- Fundamental matrix estimation
- Low-rank approximations

#### 7.2 Eigenvalue Decomposition

For symmetric matrix A:
```
A = QΛQ^T
```

Where:
- Q: matrix of eigenvectors
- Λ: diagonal matrix of eigenvalues

**Applications**:
- Covariance analysis
- Principal component analysis
- Corner detection (Harris matrix)

### 8. Optimization in Computer Vision

#### 8.1 Least Squares Problems

**Linear Least Squares**:
```
min ||Ax - b||²
x

Solution: x = (A^T A)^(-1) A^T b
```

**Weighted Least Squares**:
```
min ||W(Ax - b)||²
x

Solution: x = (A^T W^T W A)^(-1) A^T W^T W b
```

#### 8.2 Non-linear Optimization

**Gauss-Newton Method**:
For f(x) = ½||r(x)||²:
```
x_{k+1} = x_k - (J^T J)^(-1) J^T r(x_k)
```

Where J is Jacobian of residuals r(x).

**Levenberg-Marquardt**:
```
x_{k+1} = x_k - (J^T J + λI)^(-1) J^T r(x_k)
```

**Applications**:
- Bundle adjustment
- Camera calibration
- Non-linear shape fitting

### 9. Multi-scale Analysis

#### 9.1 Scale-Space Theory

**Gaussian Scale Space**:
```
L(x, y, σ) = G(x, y, σ) * I(x, y)
```

Where G(x,y,σ) is Gaussian kernel with standard deviation σ.

**Properties**:
- Causality: No new structures created at coarser scales
- Scale invariance: Natural parameterization
- Linearity: Superposition principle

#### 9.2 Image Pyramids

**Gaussian Pyramid**:
- G₀ = original image
- Gᵢ = REDUCE(Gᵢ₋₁) = downsample after Gaussian blur

**Laplacian Pyramid**:
- L₀ = G₀ - EXPAND(G₁)
- Lᵢ = Gᵢ - EXPAND(Gᵢ₊₁)

**Applications**:
- Multi-resolution analysis
- Image compression
- Feature detection at multiple scales

---

This mathematical foundation provides the theoretical background needed to understand and implement the computer vision algorithms in the main codebase.
