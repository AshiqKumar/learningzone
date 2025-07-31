# CUDA and GPU Programming Theory

## ⚡ CUDA Architecture and Programming Model

### 1. GPU Architecture Fundamentals

#### 1.1 CUDA Hierarchy

**Hardware Hierarchy**:
```
GPU Device
├── Streaming Multiprocessors (SMs)
│   ├── CUDA Cores (ALUs)
│   ├── Special Function Units (SFUs)
│   ├── Load/Store Units
│   ├── Shared Memory
│   ├── Register File
│   └── Warp Schedulers
├── Global Memory (DRAM)
├── Constant Memory Cache
├── Texture Memory Cache
└── L2 Cache
```

**Software Hierarchy**:
```
Grid (Device)
├── Block₀ (maps to SM)
│   ├── Warp₀ (32 threads)
│   ├── Warp₁ (32 threads)
│   └── ...
├── Block₁
└── ...
```

#### 1.2 Thread Organization

**Thread Indexing**:
```cpp
// 3D thread organization
int tid_x = blockIdx.x * blockDim.x + threadIdx.x;
int tid_y = blockIdx.y * blockDim.y + threadIdx.y;
int tid_z = blockIdx.z * blockDim.z + threadIdx.z;

// Linear thread ID
int tid = tid_z * (gridDim.x * blockDim.x * gridDim.y * blockDim.y) +
          tid_y * (gridDim.x * blockDim.x) + tid_x;
```

**Optimal Block Sizes**:
- Multiple of 32 (warp size)
- Common choices: 128, 256, 512 threads per block
- Consider shared memory and register usage

### 2. Memory Model Theory

#### 2.1 Memory Types and Characteristics

| Memory Type | Location | Access Speed | Scope | Lifetime |
|-------------|----------|--------------|--------|-----------|
| Registers | On-chip | 1 cycle | Thread | Thread |
| Shared Memory | On-chip | 1-32 cycles | Block | Block |
| Global Memory | Off-chip | 200-600 cycles | Grid | Application |
| Constant Memory | Off-chip | 1-200 cycles | Grid | Application |
| Texture Memory | Off-chip | 1-600 cycles | Grid | Application |

#### 2.2 Global Memory Access Patterns

**Coalesced Access**:
```cpp
// Good: Consecutive threads access consecutive memory
__global__ void coalesced_kernel(float* data) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    data[tid] = some_computation();  // Coalesced
}

// Bad: Strided access pattern
__global__ void strided_kernel(float* data, int stride) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    data[tid * stride] = some_computation();  // Not coalesced
}
```

**Coalescing Rules**:
- 32 threads in warp access 32 consecutive 4-byte words
- Starting address must be aligned to 128 bytes
- Memory transactions of 32, 64, or 128 bytes

#### 2.3 Shared Memory

**Bank Conflicts**:
```cpp
// Shared memory is divided into 32 banks (4-byte words)
// Bank ID = (address / 4) % 32

// No conflict: Different banks
__shared__ float shared_data[32];
shared_data[threadIdx.x] = data;  // Each thread accesses different bank

// Bank conflict: Same bank, different addresses
__shared__ float shared_data[64];
shared_data[threadIdx.x * 2] = data;  // Threads 0,16 access bank 0
```

**Avoiding Bank Conflicts**:
```cpp
// Padding to avoid conflicts
__shared__ float shared_data[32][33];  // Extra column for padding

// Or use different access patterns
__shared__ float shared_data[32][32];
int col = (threadIdx.x + threadIdx.y) % 32;  // Rotate access pattern
```

### 3. CUDA Programming Patterns

#### 3.1 Reduction Pattern

**Parallel Reduction Algorithm**:
```cpp
__global__ void reduction_kernel(float* input, float* output, int n) {
    __shared__ float sdata[BLOCK_SIZE];
    
    // Load data into shared memory
    int tid = threadIdx.x;
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    
    sdata[tid] = (i < n) ? input[i] : 0;
    __syncthreads();
    
    // Reduction in shared memory
    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            sdata[tid] += sdata[tid + stride];
        }
        __syncthreads();
    }
    
    // Write result back to global memory
    if (tid == 0) {
        output[blockIdx.x] = sdata[0];
    }
}
```

**Optimized Reduction**:
```cpp
// Avoid divergent branches
for (int stride = blockDim.x / 2; stride > 32; stride >>= 1) {
    if (tid < stride) {
        sdata[tid] += sdata[tid + stride];
    }
    __syncthreads();
}

// Unroll last warp (no __syncthreads needed)
if (tid < 32) {
    sdata[tid] += sdata[tid + 32];
    sdata[tid] += sdata[tid + 16];
    sdata[tid] += sdata[tid + 8];
    sdata[tid] += sdata[tid + 4];
    sdata[tid] += sdata[tid + 2];
    sdata[tid] += sdata[tid + 1];
}
```

#### 3.2 Stencil Pattern

**2D Stencil Computation**:
```cpp
__global__ void stencil_2d(float* input, float* output, int width, int height) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;
    
    if (i >= 1 && i < width-1 && j >= 1 && j < height-1) {
        int idx = j * width + i;
        output[idx] = 0.2f * (input[idx] + 
                              input[idx-1] + input[idx+1] + 
                              input[idx-width] + input[idx+width]);
    }
}
```

**Optimized with Shared Memory**:
```cpp
__global__ void stencil_2d_shared(float* input, float* output, int width, int height) {
    __shared__ float tile[TILE_HEIGHT][TILE_WIDTH];
    
    int tx = threadIdx.x;
    int ty = threadIdx.y;
    int i = blockIdx.x * blockDim.x + tx;
    int j = blockIdx.y * blockDim.y + ty;
    
    // Load tile with halo
    if (i < width && j < height) {
        tile[ty][tx] = input[j * width + i];
    }
    __syncthreads();
    
    // Compute stencil
    if (tx >= 1 && tx < TILE_WIDTH-1 && ty >= 1 && ty < TILE_HEIGHT-1 &&
        i < width-1 && j < height-1) {
        output[j * width + i] = 0.2f * (tile[ty][tx] + 
                                        tile[ty][tx-1] + tile[ty][tx+1] + 
                                        tile[ty-1][tx] + tile[ty+1][tx]);
    }
}
```

### 4. Convolution on GPU

#### 4.1 Basic Convolution Kernel

```cpp
__global__ void convolution_2d(float* input, float* kernel, float* output,
                              int in_width, int in_height,
                              int kernel_size, int out_width, int out_height) {
    int out_x = blockIdx.x * blockDim.x + threadIdx.x;
    int out_y = blockIdx.y * blockDim.y + threadIdx.y;
    
    if (out_x < out_width && out_y < out_height) {
        float sum = 0.0f;
        int half_kernel = kernel_size / 2;
        
        for (int ky = 0; ky < kernel_size; ky++) {
            for (int kx = 0; kx < kernel_size; kx++) {
                int in_x = out_x + kx - half_kernel;
                int in_y = out_y + ky - half_kernel;
                
                if (in_x >= 0 && in_x < in_width && in_y >= 0 && in_y < in_height) {
                    sum += input[in_y * in_width + in_x] * kernel[ky * kernel_size + kx];
                }
            }
        }
        
        output[out_y * out_width + out_x] = sum;
    }
}
```

#### 4.2 Tiled Convolution with Shared Memory

```cpp
#define TILE_WIDTH 16
#define KERNEL_SIZE 5

__global__ void tiled_convolution(float* input, float* kernel, float* output,
                                 int in_width, int in_height) {
    __shared__ float input_tile[TILE_WIDTH + KERNEL_SIZE - 1][TILE_WIDTH + KERNEL_SIZE - 1];
    __shared__ float kernel_shared[KERNEL_SIZE][KERNEL_SIZE];
    
    int tx = threadIdx.x;
    int ty = threadIdx.y;
    int out_x = blockIdx.x * TILE_WIDTH + tx;
    int out_y = blockIdx.y * TILE_WIDTH + ty;
    
    // Load kernel into shared memory
    if (tx < KERNEL_SIZE && ty < KERNEL_SIZE) {
        kernel_shared[ty][tx] = kernel[ty * KERNEL_SIZE + tx];
    }
    
    // Load input tile with halo
    int in_x = out_x - KERNEL_SIZE/2;
    int in_y = out_y - KERNEL_SIZE/2;
    
    // Load multiple elements per thread for halo
    for (int dy = 0; dy < (TILE_WIDTH + KERNEL_SIZE - 1 + blockDim.y - 1) / blockDim.y; dy++) {
        for (int dx = 0; dx < (TILE_WIDTH + KERNEL_SIZE - 1 + blockDim.x - 1) / blockDim.x; dx++) {
            int load_x = tx + dx * blockDim.x;
            int load_y = ty + dy * blockDim.y;
            int global_x = in_x + dx * blockDim.x;
            int global_y = in_y + dy * blockDim.y;
            
            if (load_x < TILE_WIDTH + KERNEL_SIZE - 1 && load_y < TILE_WIDTH + KERNEL_SIZE - 1) {
                if (global_x >= 0 && global_x < in_width && global_y >= 0 && global_y < in_height) {
                    input_tile[load_y][load_x] = input[global_y * in_width + global_x];
                } else {
                    input_tile[load_y][load_x] = 0.0f;  // Zero padding
                }
            }
        }
    }
    
    __syncthreads();
    
    // Compute convolution
    if (out_x < in_width - KERNEL_SIZE + 1 && out_y < in_height - KERNEL_SIZE + 1) {
        float sum = 0.0f;
        for (int ky = 0; ky < KERNEL_SIZE; ky++) {
            for (int kx = 0; kx < KERNEL_SIZE; kx++) {
                sum += input_tile[ty + ky][tx + kx] * kernel_shared[ky][kx];
            }
        }
        output[out_y * (in_width - KERNEL_SIZE + 1) + out_x] = sum;
    }
}
```

### 5. Matrix Operations

#### 5.1 Matrix Multiplication

**Naive Implementation**:
```cpp
__global__ void matrix_mult_naive(float* A, float* B, float* C, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++) {
            sum += A[row * N + k] * B[k * N + col];
        }
        C[row * N + col] = sum;
    }
}
```

**Tiled Matrix Multiplication**:
```cpp
#define TILE_SIZE 16

__global__ void matrix_mult_tiled(float* A, float* B, float* C, int N) {
    __shared__ float As[TILE_SIZE][TILE_SIZE];
    __shared__ float Bs[TILE_SIZE][TILE_SIZE];
    
    int bx = blockIdx.x; int by = blockIdx.y;
    int tx = threadIdx.x; int ty = threadIdx.y;
    
    int row = by * TILE_SIZE + ty;
    int col = bx * TILE_SIZE + tx;
    
    float sum = 0.0f;
    
    for (int m = 0; m < (N + TILE_SIZE - 1) / TILE_SIZE; m++) {
        // Load tiles into shared memory
        if (row < N && m * TILE_SIZE + tx < N)
            As[ty][tx] = A[row * N + m * TILE_SIZE + tx];
        else
            As[ty][tx] = 0.0f;
            
        if (col < N && m * TILE_SIZE + ty < N)
            Bs[ty][tx] = B[(m * TILE_SIZE + ty) * N + col];
        else
            Bs[ty][tx] = 0.0f;
            
        __syncthreads();
        
        // Compute partial product
        for (int k = 0; k < TILE_SIZE; k++)
            sum += As[ty][k] * Bs[k][tx];
            
        __syncthreads();
    }
    
    if (row < N && col < N)
        C[row * N + col] = sum;
}
```

### 6. Performance Optimization Techniques

#### 6.1 Memory Optimization

**Memory Coalescing Patterns**:
```cpp
// Structure of Arrays (SoA) - Better for coalescing
struct ParticlesSoA {
    float* x;  // All x coordinates
    float* y;  // All y coordinates
    float* z;  // All z coordinates
};

// Array of Structures (AoS) - May not coalesce well
struct Particle {
    float x, y, z;
};
struct ParticlesAoS {
    Particle* particles;
};
```

**Texture Memory Usage**:
```cpp
texture<float, 2, cudaReadModeElementType> tex_input;

__global__ void kernel_with_texture(float* output, int width, int height) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    
    if (x < width && y < height) {
        // Texture fetch with automatic interpolation and caching
        float value = tex2D(tex_input, x + 0.5f, y + 0.5f);
        output[y * width + x] = value;
    }
}
```

#### 6.2 Occupancy Optimization

**Occupancy Calculator**:
```cpp
// Check occupancy
int blockSize = 256;
int minGridSize, blockSizeOpt;
cudaOccupancyMaxPotentialBlockSize(&minGridSize, &blockSizeOpt, kernel, 0, 0);

printf("Suggested block size: %d\n", blockSizeOpt);
printf("Minimum grid size: %d\n", minGridSize);

// Calculate occupancy
int maxActiveBlocks;
cudaOccupancyMaxActiveBlocksPerMultiprocessor(&maxActiveBlocks, kernel, blockSize, 0);
printf("Max active blocks per SM: %d\n", maxActiveBlocks);
```

**Resource Usage Limits**:
- Registers per thread: 255
- Shared memory per block: 48KB (compute capability 7.x)
- Threads per block: 1024
- Blocks per SM: 16-32 (depending on compute capability)

#### 6.3 Warp-level Optimizations

**Warp Shuffle Operations**:
```cpp
__device__ float warp_reduce_sum(float val) {
    for (int offset = warpSize/2; offset > 0; offset /= 2) {
        val += __shfl_down_sync(0xFFFFFFFF, val, offset);
    }
    return val;
}

__global__ void reduction_with_shuffle(float* input, float* output, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    float val = (idx < n) ? input[idx] : 0;
    
    // Reduce within warp
    val = warp_reduce_sum(val);
    
    // First thread in warp writes to shared memory
    __shared__ float warp_results[32];
    int lane = threadIdx.x % warpSize;
    int warp = threadIdx.x / warpSize;
    
    if (lane == 0) warp_results[warp] = val;
    __syncthreads();
    
    // Reduce across warps
    if (threadIdx.x < blockDim.x / warpSize) {
        val = warp_results[threadIdx.x];
        val = warp_reduce_sum(val);
    }
    
    if (threadIdx.x == 0) output[blockIdx.x] = val;
}
```

### 7. Stream and Asynchronous Execution

#### 7.1 CUDA Streams

**Stream Creation and Usage**:
```cpp
cudaStream_t stream1, stream2;
cudaStreamCreate(&stream1);
cudaStreamCreate(&stream2);

// Asynchronous memory transfers and kernel launches
cudaMemcpyAsync(d_data1, h_data1, size, cudaMemcpyHostToDevice, stream1);
cudaMemcpyAsync(d_data2, h_data2, size, cudaMemcpyHostToDevice, stream2);

kernel1<<<grid, block, 0, stream1>>>(d_data1, d_result1);
kernel2<<<grid, block, 0, stream2>>>(d_data2, d_result2);

cudaMemcpyAsync(h_result1, d_result1, size, cudaMemcpyDeviceToHost, stream1);
cudaMemcpyAsync(h_result2, d_result2, size, cudaMemcpyDeviceToHost, stream2);

cudaStreamSynchronize(stream1);
cudaStreamSynchronize(stream2);
```

#### 7.2 Pipeline Optimization

**Overlapping Computation and Communication**:
```cpp
const int num_streams = 4;
const int chunk_size = n / num_streams;

cudaStream_t streams[num_streams];
for (int i = 0; i < num_streams; i++) {
    cudaStreamCreate(&streams[i]);
}

for (int i = 0; i < num_streams; i++) {
    int offset = i * chunk_size;
    int size = (i == num_streams - 1) ? n - offset : chunk_size;
    
    // Asynchronous pipeline
    cudaMemcpyAsync(&d_data[offset], &h_data[offset], 
                    size * sizeof(float), cudaMemcpyHostToDevice, streams[i]);
    
    process_kernel<<<(size + 255) / 256, 256, 0, streams[i]>>>
                   (&d_data[offset], &d_result[offset], size);
    
    cudaMemcpyAsync(&h_result[offset], &d_result[offset], 
                    size * sizeof(float), cudaMemcpyDeviceToHost, streams[i]);
}

// Synchronize all streams
for (int i = 0; i < num_streams; i++) {
    cudaStreamSynchronize(streams[i]);
    cudaStreamDestroy(streams[i]);
}
```

### 8. Error Handling and Debugging

#### 8.1 Error Checking

**Macro for Error Checking**:
```cpp
#define CUDA_CHECK(call) \
    do { \
        cudaError_t err = call; \
        if (err != cudaSuccess) { \
            fprintf(stderr, "CUDA error at %s:%d: %s\n", \
                    __FILE__, __LINE__, cudaGetErrorString(err)); \
            exit(1); \
        } \
    } while(0)

// Usage
CUDA_CHECK(cudaMalloc(&d_data, size));
CUDA_CHECK(cudaMemcpy(d_data, h_data, size, cudaMemcpyHostToDevice));
kernel<<<grid, block>>>(d_data);
CUDA_CHECK(cudaGetLastError());
CUDA_CHECK(cudaDeviceSynchronize());
```

#### 8.2 Performance Profiling

**NVTX Annotations**:
```cpp
#include <nvToolsExt.h>

void profile_function() {
    nvtxRangePush("Data Transfer");
    cudaMemcpy(d_data, h_data, size, cudaMemcpyHostToDevice);
    nvtxRangePop();
    
    nvtxRangePush("Kernel Execution");
    kernel<<<grid, block>>>(d_data);
    cudaDeviceSynchronize();
    nvtxRangePop();
}
```

**CUDA Events for Timing**:
```cpp
cudaEvent_t start, stop;
cudaEventCreate(&start);
cudaEventCreate(&stop);

cudaEventRecord(start);
kernel<<<grid, block>>>(d_data);
cudaEventRecord(stop);

cudaEventSynchronize(stop);
float milliseconds = 0;
cudaEventElapsedTime(&milliseconds, start, stop);

printf("Kernel execution time: %f ms\n", milliseconds);
```

### 9. Advanced GPU Algorithms

#### 9.1 Parallel Prefix Sum (Scan)

**Hillis-Steele Scan**:
```cpp
__global__ void scan_hillis_steele(float* input, float* output, int n) {
    __shared__ float temp[BLOCK_SIZE];
    
    int tid = threadIdx.x;
    int pout = 0, pin = 1;
    
    temp[pout * BLOCK_SIZE + tid] = (tid > 0) ? input[tid - 1] : 0;
    __syncthreads();
    
    for (int offset = 1; offset < BLOCK_SIZE; offset *= 2) {
        pout = 1 - pout;
        pin = 1 - pout;
        
        if (tid >= offset) {
            temp[pout * BLOCK_SIZE + tid] = 
                temp[pin * BLOCK_SIZE + tid] + temp[pin * BLOCK_SIZE + tid - offset];
        } else {
            temp[pout * BLOCK_SIZE + tid] = temp[pin * BLOCK_SIZE + tid];
        }
        __syncthreads();
    }
    
    output[tid] = temp[pout * BLOCK_SIZE + tid];
}
```

#### 9.2 Radix Sort

**Counting Sort for Single Digit**:
```cpp
__global__ void radix_sort_digit(int* input, int* output, int* counts, 
                                int n, int digit) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (tid < n) {
        int value = input[tid];
        int digit_value = (value >> (digit * 4)) & 0xF;  // 4-bit radix
        
        // Count occurrences
        atomicAdd(&counts[digit_value], 1);
    }
    
    __syncthreads();
    
    // Compute positions and scatter
    if (tid < n) {
        int value = input[tid];
        int digit_value = (value >> (digit * 4)) & 0xF;
        
        int pos = atomicAdd(&counts[digit_value], -1) - 1;
        output[pos] = value;
    }
}
```

---

This CUDA theory provides the foundation for understanding GPU programming and optimization techniques used in the camera algorithms implementation.
