# Deep Learning Theory - Neural Networks and Modern AI

## 🧠 Neural Network Fundamentals

### 1. Basic Neural Network Theory

#### 1.1 Perceptron Model

**Mathematical Representation**:
```
y = f(Σ(wᵢxᵢ) + b)
    i=1

Where:
- xᵢ: input features
- wᵢ: weights
- b: bias term
- f: activation function
```

**Activation Functions**:

*Sigmoid*:
```
σ(x) = 1 / (1 + e^(-x))
σ'(x) = σ(x)(1 - σ(x))
```

*ReLU (Rectified Linear Unit)*:
```
ReLU(x) = max(0, x)
ReLU'(x) = {1 if x > 0, 0 if x ≤ 0}
```

*Tanh*:
```
tanh(x) = (e^x - e^(-x)) / (e^x + e^(-x))
tanh'(x) = 1 - tanh²(x)
```

*Leaky ReLU*:
```
LeakyReLU(x) = {x if x > 0, αx if x ≤ 0}
Where α ∈ (0, 1), typically 0.01
```

#### 1.2 Multi-layer Perceptron (MLP)

**Forward Propagation**:
```
Layer l: a^(l) = f^(l)(W^(l)a^(l-1) + b^(l))

Where:
- a^(l): activation at layer l
- W^(l): weight matrix for layer l
- b^(l): bias vector for layer l
- f^(l): activation function for layer l
```

**Universal Approximation Theorem**:
A single hidden layer MLP with finite neurons can approximate any continuous function on a compact set to arbitrary accuracy.

### 2. Backpropagation Algorithm

#### 2.1 Mathematical Derivation

**Cost Function** (Mean Squared Error):
```
J(W,b) = (1/2m) Σ ||y^(i) - ŷ^(i)||²
         i=1

Where m is number of training examples
```

**Chain Rule Application**:
```
∂J/∂W^(l) = ∂J/∂z^(l) × ∂z^(l)/∂W^(l)
∂J/∂b^(l) = ∂J/∂z^(l) × ∂z^(l)/∂b^(l)

Where z^(l) = W^(l)a^(l-1) + b^(l)
```

**Error Propagation**:
```
δ^(L) = ∇_a J ⊙ σ'(z^(L))           (output layer)
δ^(l) = ((W^(l+1))^T δ^(l+1)) ⊙ σ'(z^(l))  (hidden layers)

Where ⊙ is element-wise multiplication
```

**Weight Updates**:
```
W^(l) = W^(l) - η × δ^(l) × (a^(l-1))^T
b^(l) = b^(l) - η × δ^(l)

Where η is learning rate
```

### 3. Convolutional Neural Networks (CNNs)

#### 3.1 Convolution Operation

**2D Convolution**:
```
(I * K)(i,j) = Σ Σ I(m,n) × K(i-m, j-n)
               m n

Feature map: Y_{i,j} = σ(Σ Σ X_{i+m,j+n} × W_{m,n} + b)
                        m n
```

**Output Size Calculation**:
```
Output_height = (Input_height + 2×Padding - Kernel_height) / Stride + 1
Output_width = (Input_width + 2×Padding - Kernel_width) / Stride + 1
```

**Parameter Count**:
```
Conv Layer Parameters = (K_h × K_w × C_in + 1) × C_out

Where:
- K_h, K_w: kernel dimensions
- C_in: input channels
- C_out: output channels
- +1: bias term
```

#### 3.2 Pooling Operations

**Max Pooling**:
```
MaxPool(X)_{i,j} = max{X_{i×s+m, j×s+n} | 0 ≤ m,n < k}

Where:
- k: pooling kernel size
- s: stride
```

**Average Pooling**:
```
AvgPool(X)_{i,j} = (1/k²) × Σ Σ X_{i×s+m, j×s+n}
                            m=0 n=0
```

**Global Average Pooling**:
```
GAP(X) = (1/HW) × Σ Σ X_{i,j}
                  i=1 j=1
```

#### 3.3 CNN Architectures

**LeNet-5** (LeCun et al., 1998):
```
Input(32×32) → Conv(6@5×5) → Pool(2×2) → Conv(16@5×5) → Pool(2×2) → FC(120) → FC(84) → FC(10)
```

**AlexNet** (Krizhevsky et al., 2012):
```
Input(224×224×3) → Conv(96@11×11,s=4) → Pool → Conv(256@5×5) → Pool → 
Conv(384@3×3) → Conv(384@3×3) → Conv(256@3×3) → Pool → FC(4096) → FC(4096) → FC(1000)
```

**ResNet** (He et al., 2016):
- Skip connections: y = F(x) + x
- Solves vanishing gradient problem
- Identity mapping for gradient flow

### 4. Advanced CNN Concepts

#### 4.1 Batch Normalization

**Normalization**:
```
μ = (1/m) × Σ xᵢ          (batch mean)
        i=1

σ² = (1/m) × Σ (xᵢ - μ)²  (batch variance)
         i=1

x̂ᵢ = (xᵢ - μ) / √(σ² + ε)  (normalized)

yᵢ = γx̂ᵢ + β              (scaled and shifted)
```

**Benefits**:
- Reduces internal covariate shift
- Allows higher learning rates
- Acts as regularization

#### 4.2 Dropout Regularization

**Training Phase**:
```
yᵢ = {xᵢ/p with probability p
     {0     with probability 1-p
```

**Test Phase**:
```
yᵢ = xᵢ  (no dropout, scaling handled by training)
```

**Mathematical Analysis**:
- Reduces overfitting
- Approximates model averaging
- Forces redundant representations

### 5. Object Detection Theory

#### 5.1 YOLO (You Only Look Once)

**Grid-based Detection**:
- Divide image into S×S grid
- Each cell predicts B bounding boxes
- Each box: (x, y, w, h, confidence)
- Each cell: C class probabilities

**Mathematical Formulation**:
```
Bounding Box: (bₓ, b_y, bᵨ, b_h)
bₓ = σ(tₓ) + cₓ    (center x relative to cell)
b_y = σ(t_y) + c_y  (center y relative to cell)
bᵨ = pᵨ × e^(tᵨ)    (width relative to anchor)
b_h = p_h × e^(t_h)  (height relative to anchor)

Where σ is sigmoid, (cₓ, c_y) is cell coordinates
```

**Loss Function**:
```
L = λ_coord Σ Σ 𝟙ᵢⱼᵒᵇʲ[(xᵢ - x̂ᵢ)² + (yᵢ - ŷᵢ)²]
    + λ_coord Σ Σ 𝟙ᵢⱼᵒᵇʲ[(√wᵢ - √ŵᵢ)² + (√hᵢ - √ĥᵢ)²]
    + Σ Σ 𝟙ᵢⱼᵒᵇʲ(Cᵢ - Ĉᵢ)²
    + λ_noobj Σ Σ 𝟙ᵢⱼⁿᵒᵒᵇʲ(Cᵢ - Ĉᵢ)²
    + Σ 𝟙ᵢᵒᵇʲ Σ (pᵢ(c) - p̂ᵢ(c))²

Where 𝟙ᵢⱼᵒᵇʲ = 1 if object appears in cell i,j
```

#### 5.2 Non-Maximum Suppression (NMS)

**Algorithm**:
1. Sort detections by confidence score
2. Select highest scoring detection
3. Remove detections with IoU > threshold
4. Repeat until no detections remain

**Intersection over Union (IoU)**:
```
IoU = Area(Box₁ ∩ Box₂) / Area(Box₁ ∪ Box₂)

Area(A ∩ B) = max(0, min(x₁ᴬ, x₁ᴮ) - max(x₀ᴬ, x₀ᴮ)) × 
              max(0, min(y₁ᴬ, y₁ᴮ) - max(y₀ᴬ, y₀ᴮ))
```

### 6. Face Recognition Deep Learning

#### 6.1 Siamese Networks

**Architecture**:
```
Twin networks with shared weights:
f(x₁) and f(x₂) → distance measure → similarity score
```

**Contrastive Loss**:
```
L = ½ Σ [y × D² + (1-y) × max(0, m - D)²]
Where:
- y = 1 if same identity, 0 if different
- D = ||f(x₁) - f(x₂)||₂
- m = margin parameter
```

#### 6.2 Triplet Loss

**Triplet Selection**:
- Anchor: reference image
- Positive: same identity as anchor
- Negative: different identity from anchor

**Loss Function**:
```
L = Σ max(0, ||f(a) - f(p)||² - ||f(a) - f(n)||² + α)

Where:
- a: anchor
- p: positive
- n: negative
- α: margin
```

#### 6.3 ArcFace Loss

**Angular Margin**:
```
L = -log(e^(s·cos(θ_yᵢ + m)) / (e^(s·cos(θ_yᵢ + m)) + Σ e^(s·cos(θⱼ))))
                                                      j≠yᵢ

Where:
- s: scale parameter
- m: angular margin
- θ_yᵢ: angle between feature and weight
```

### 7. Optimization Theory

#### 7.1 Gradient Descent Variants

**Stochastic Gradient Descent (SGD)**:
```
θ = θ - η × ∇θ J(θ; x^(i), y^(i))
```

**Mini-batch Gradient Descent**:
```
θ = θ - η × (1/B) Σ ∇θ J(θ; x^(i), y^(i))
                  i∈B
```

**Momentum**:
```
v_t = γv_{t-1} + η∇θ J(θ)
θ = θ - v_t

Where γ ∈ [0,1] is momentum coefficient
```

#### 7.2 Adaptive Learning Rate Methods

**AdaGrad**:
```
G_t = G_{t-1} + (∇θ J(θ))²
θ = θ - (η/√(G_t + ε)) × ∇θ J(θ)
```

**Adam** (Adaptive Moment Estimation):
```
m_t = β₁m_{t-1} + (1-β₁)∇θ J(θ)       (first moment)
v_t = β₂v_{t-1} + (1-β₂)(∇θ J(θ))²    (second moment)

m̂_t = m_t / (1-β₁^t)    (bias correction)
v̂_t = v_t / (1-β₂^t)    (bias correction)

θ = θ - η × m̂_t / (√v̂_t + ε)
```

**Parameters**:
- β₁ = 0.9 (first moment decay)
- β₂ = 0.999 (second moment decay)
- ε = 1e-8 (small constant)

### 8. Regularization Techniques

#### 8.1 L1 and L2 Regularization

**L1 Regularization (Lasso)**:
```
J_reg = J + λ Σ |wᵢ|
           i

Gradient: ∂J_reg/∂w = ∂J/∂w + λ × sign(w)
```

**L2 Regularization (Ridge)**:
```
J_reg = J + λ Σ wᵢ²
           i

Gradient: ∂J_reg/∂w = ∂J/∂w + 2λw
```

**Elastic Net**:
```
J_reg = J + λ₁ Σ |wᵢ| + λ₂ Σ wᵢ²
           i        i
```

#### 8.2 Early Stopping

**Validation-based Stopping**:
1. Monitor validation loss during training
2. Stop when validation loss stops decreasing
3. Restore weights from best validation epoch

**Mathematical Criterion**:
```
Stop if: val_loss(epoch) > val_loss(epoch - patience)
```

### 9. Loss Functions

#### 9.1 Classification Losses

**Cross-Entropy Loss**:
```
L = -Σ yᵢ log(ŷᵢ)
    i

For binary: L = -[y log(ŷ) + (1-y) log(1-ŷ)]
```

**Focal Loss** (for imbalanced datasets):
```
FL(p_t) = -α_t(1-p_t)^γ log(p_t)

Where:
- α_t: weighting factor
- γ: focusing parameter
- p_t: predicted probability for true class
```

#### 9.2 Regression Losses

**Mean Squared Error (MSE)**:
```
MSE = (1/n) Σ (yᵢ - ŷᵢ)²
           i
```

**Mean Absolute Error (MAE)**:
```
MAE = (1/n) Σ |yᵢ - ŷᵢ|
           i
```

**Huber Loss** (robust to outliers):
```
L_δ(y, ŷ) = {½(y - ŷ)²           if |y - ŷ| ≤ δ
           {δ|y - ŷ| - ½δ²       otherwise
```

### 10. Transfer Learning Theory

#### 10.1 Feature Extraction vs Fine-tuning

**Feature Extraction**:
- Freeze pre-trained layers
- Train only classifier layers
- Fast training, less data required

**Fine-tuning**:
- Initialize with pre-trained weights
- Train all layers with small learning rate
- Better performance, requires more data

#### 10.2 Domain Adaptation

**Mathematical Framework**:
```
Source domain: DS = {(xˢᵢ, yˢᵢ)}ⁿˢᵢ₌₁
Target domain: DT = {xᵗᵢ}ⁿᵗᵢ₌₁

Goal: Learn f: XT → YT using labeled DS and unlabeled DT
```

**Domain Discrepancy Measures**:
- Maximum Mean Discrepancy (MMD)
- Correlation Alignment (CORAL)
- Adversarial domain adaptation

### 11. Attention Mechanisms

#### 11.1 Self-Attention

**Scaled Dot-Product Attention**:
```
Attention(Q, K, V) = softmax(QKᵀ/√d_k)V

Where:
- Q: queries matrix
- K: keys matrix
- V: values matrix
- d_k: dimension of keys
```

**Multi-Head Attention**:
```
MultiHead(Q, K, V) = Concat(head₁, ..., headₕ)Wᵒ

head_i = Attention(QWᵢQ, KWᵢK, VWᵢV)
```

#### 11.2 Vision Transformer (ViT)

**Patch Embedding**:
```
Input image: H × W × C
Patch size: P × P
Number of patches: N = HW/P²
Patch embedding: N × (P²C)
```

**Position Encoding**:
```
Add learnable position embeddings to patch embeddings
```

### 12. Generative Models

#### 12.1 Variational Autoencoders (VAE)

**Encoder**: q_φ(z|x) ≈ p(z|x)
**Decoder**: p_θ(x|z)

**ELBO (Evidence Lower Bound)**:
```
log p(x) ≥ E_{q_φ(z|x)}[log p_θ(x|z)] - KL(q_φ(z|x) || p(z))
```

**Reparameterization Trick**:
```
z = μ + σ ⊙ ε, where ε ~ N(0, I)
```

#### 12.2 Generative Adversarial Networks (GANs)

**Minimax Game**:
```
min max V(D, G) = E_{x~p_data}[log D(x)] + E_{z~p_z}[log(1 - D(G(z)))]
 G   D
```

**Training Algorithm**:
1. Update Discriminator: maximize V(D, G)
2. Update Generator: minimize V(D, G)

---

This deep learning theory provides the mathematical foundation for understanding the neural network implementations in the camera algorithms project.
