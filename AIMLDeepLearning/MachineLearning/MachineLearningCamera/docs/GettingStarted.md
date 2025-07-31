# Getting Started Guide - ML Camera Algorithms

## 🚀 Quick Start Guide

### Prerequisites Check

Before starting, ensure your system meets the minimum requirements:

```bash
# Check C++ compiler
g++ --version  # Should be GCC 8.0+ or Clang 7.0+

# Check CUDA (optional)
nvcc --version  # Should be CUDA 11.0+

# Check available memory
free -h  # Should have 8GB+ available

# Check GPU (optional)
nvidia-smi  # Should show compatible GPU
```

## 📥 Installation Steps

### 1. Basic Setup (CPU Only)

```bash
# Clone the repository
git clone https://github.com/your-repo/ml-camera-algorithms.git
cd ml-camera-algorithms

# Build CPU-only version
mkdir build && cd build
cmake .. -DUSE_CUDA=OFF -DUSE_TENSORFLOW=OFF
make -j$(nproc)

# Run basic tests
./ml_camera
```

### 2. GPU-Accelerated Setup

```bash
# Install CUDA Toolkit
wget https://developer.download.nvidia.com/compute/cuda/12.2.0/local_installers/cuda_12.2.0_535.54.03_linux.run
sudo sh cuda_12.2.0_535.54.03_linux.run

# Add to PATH and LD_LIBRARY_PATH
echo 'export PATH=/usr/local/cuda-12.2/bin:$PATH' >> ~/.bashrc
echo 'export LD_LIBRARY_PATH=/usr/local/cuda-12.2/lib64:$LD_LIBRARY_PATH' >> ~/.bashrc
source ~/.bashrc

# Build with CUDA support
cmake .. -DUSE_CUDA=ON -DUSE_TENSORFLOW=OFF
make -j$(nproc)

# Test CUDA functionality
./ml_camera --test-cuda
```

### 3. Full Installation with TensorFlow

```bash
# Download TensorFlow C++
wget https://storage.googleapis.com/tensorflow/libtensorflow/libtensorflow-gpu-linux-x86_64-2.14.0.tar.gz
sudo tar -C /usr/local -xzf libtensorflow-gpu-linux-x86_64-2.14.0.tar.gz
sudo ldconfig

# Build full version
cmake .. -DUSE_CUDA=ON -DUSE_TENSORFLOW=ON
make -j$(nproc)

# Test complete system
./ml_camera --test-all
```

## 📖 Basic Usage Examples

### Example 1: Basic Edge Detection

```cpp
#include "MLCameraAlgorithms.cpp"

int main() {
    // Generate test image
    Image test_image = generateTestImage(640, 480);
    
    // Apply Sobel edge detection
    auto edges = MLCameraAlgorithms::sobelEdgeDetection(test_image);
    
    // Save result (pseudo-code)
    saveImage(edges, "edges.png");
    
    std::cout << "Edge detection completed!" << std::endl;
    return 0;
}
```

**Expected Output:**
```
=== SOBEL EDGE DETECTION ===
✅ Sobel edge detection completed
Edge detection completed!
```

### Example 2: Corner Detection and Feature Matching

```cpp
int main() {
    Image image1 = generateTestImage(640, 480);
    Image image2 = generateTestImage(640, 480);  // Slightly different
    
    // Detect corners in both images
    auto corners1 = MLCameraAlgorithms::harrisCornerDetection(image1, 0.01f);
    auto corners2 = MLCameraAlgorithms::harrisCornerDetection(image2, 0.01f);
    
    // Compute descriptors
    auto desc1 = MLCameraAlgorithms::computeDescriptors(image1, corners1);
    auto desc2 = MLCameraAlgorithms::computeDescriptors(image2, corners2);
    
    // Match features
    auto matches = MLCameraAlgorithms::matchFeatures(desc1, desc2, 0.7f);
    
    std::cout << "Found " << matches.size() << " feature matches" << std::endl;
    return 0;
}
```

### Example 3: Real-time Video Processing

```cpp
int main() {
    // Initialize video processor
    MLCameraAlgorithms::VideoProcessor processor;
    
    // Simulate camera input
    for (int frame_id = 0; frame_id < 100; ++frame_id) {
        VideoFrame frame(1920, 1080, frame_id);
        
        // Fill frame with test data
        for (int y = 0; y < frame.image.height; ++y) {
            for (int x = 0; x < frame.image.width; ++x) {
                frame.image(x, y) = {
                    static_cast<uint8_t>((x + frame_id) % 256),
                    static_cast<uint8_t>((y + frame_id) % 256),
                    static_cast<uint8_t>((x + y + frame_id) % 256)
                };
            }
        }
        
        // Add to processing queue
        processor.addFrame(frame);
        
        // Simulate 30 FPS
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
    
    processor.stop();
    std::cout << "Video processing completed!" << std::endl;
    return 0;
}
```

## 🧪 Testing Your Installation

### Performance Benchmarks

Run the built-in benchmarks to verify your installation:

```bash
# Basic performance test
./ml_camera --benchmark

# CUDA performance test (if available)
./ml_camera --benchmark-cuda

# Memory usage test
./ml_camera --test-memory
```

### Expected Benchmark Results

**CPU Performance (Intel i7-10700K)**:
```
=== PERFORMANCE BENCHMARKS ===
Sobel Edge Detection (1920x1080): 15.2 ms
Harris Corner Detection: 52.3 ms
Feature Matching (100 features): 8.7 ms
Optical Flow (50 points): 12.1 ms
```

**GPU Performance (RTX 3070)**:
```
=== CUDA BENCHMARKS ===
CUDA Convolution (1920x1080): 3.8 ms
CUDA Max Pooling: 1.2 ms
Memory Transfer (Host->Device): 2.1 ms
Memory Transfer (Device->Host): 2.3 ms
```

### Troubleshooting Common Issues

#### Issue 1: CUDA Not Found
```bash
# Error: "CUDA runtime not found"
# Solution: Check CUDA installation
nvidia-smi
export PATH=/usr/local/cuda/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH
```

#### Issue 2: Memory Allocation Errors
```bash
# Error: "cudaMalloc failed"
# Solution: Reduce batch size or check GPU memory
nvidia-smi  # Check available GPU memory
# Modify BATCH_SIZE in code if needed
```

#### Issue 3: Slow Performance
```bash
# Check CPU governor
cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
# Should be "performance" for benchmarking

# Set performance mode
sudo cpupower frequency-set -g performance
```

## 📁 Project Structure Walkthrough

```
ml-camera-algorithms/
├── src/
│   ├── MLCameraAlgorithms.cpp      # Main implementation
│   └── utils/
│       ├── image_utils.h           # Image handling utilities
│       ├── timing.h                # Performance measurement
│       └── memory_manager.h        # Memory management
├── docs/
│   ├── README.md                   # This file
│   ├── ComputerVisionTheory.md     # Mathematical foundations
│   ├── DeepLearningTheory.md       # Neural network theory
│   ├── CudaGpuTheory.md           # GPU programming concepts
│   └── RealTimeProcessingTheory.md # Real-time systems theory
├── examples/
│   ├── basic_cv_example.cpp        # Simple computer vision
│   ├── real_time_example.cpp       # Video processing
│   └── cuda_example.cpp            # GPU acceleration
├── test/
│   ├── unit_tests.cpp              # Algorithm unit tests
│   ├── performance_tests.cpp       # Benchmark tests
│   └── integration_tests.cpp       # End-to-end tests
└── models/
    ├── yolo_weights.bin            # Pre-trained YOLO model
    └── cnn_classifier.bin          # CNN classification model
```

## ⚙️ Configuration Options

### Build Configuration

Edit `CMakeLists.txt` to customize build options:

```cmake
# Feature flags
option(USE_CUDA "Enable CUDA acceleration" ON)
option(USE_TENSORFLOW "Enable TensorFlow support" ON)
option(USE_OPENCV "Enable OpenCV integration" OFF)
option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_BENCHMARKS "Build performance benchmarks" ON)

# Performance settings
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -march=native")
set(CUDA_ARCH "75" CACHE STRING "CUDA architecture (75 for RTX series)")
```

### Runtime Configuration

Create `config.ini` file for runtime settings:

```ini
[performance]
max_threads = 8
gpu_memory_limit = 4096  # MB
frame_buffer_size = 10

[algorithms]
edge_detection_threshold = 50
corner_detection_threshold = 0.01
nms_threshold = 0.4

[video]
target_fps = 30
max_frame_drop_rate = 0.1
adaptive_quality = true
```

## 🎯 Next Steps

### Learning Path

1. **Start with Basics** (1-2 weeks)
   - Run basic computer vision examples
   - Understand image processing pipeline
   - Read ComputerVisionTheory.md

2. **Explore Deep Learning** (2-3 weeks)
   - Experiment with CNN classification
   - Try YOLO object detection
   - Study DeepLearningTheory.md

3. **GPU Acceleration** (1-2 weeks)
   - Enable CUDA support
   - Compare CPU vs GPU performance
   - Read CudaGpuTheory.md

4. **Real-time Systems** (2-3 weeks)
   - Implement video processing pipeline
   - Optimize for low latency
   - Study RealTimeProcessingTheory.md

### Advanced Projects

1. **Custom Object Detection**
   - Train your own YOLO model
   - Implement custom loss functions
   - Deploy on edge devices

2. **Real-time Face Recognition**
   - Build complete pipeline
   - Optimize for mobile deployment
   - Add live video streaming

3. **Surveillance System**
   - Multi-camera setup
   - Motion detection and tracking
   - Alert system integration

4. **Autonomous Vehicle Vision**
   - Lane detection algorithms
   - Traffic sign recognition
   - Depth estimation

### Community and Support

- **Documentation**: Read theory documents for deep understanding
- **Issues**: Report bugs and feature requests on GitHub
- **Examples**: Check `examples/` directory for more use cases
- **Testing**: Run unit tests to verify your changes

### Performance Optimization Tips

1. **Profile First**: Use built-in performance monitoring
2. **Memory Patterns**: Optimize data layout for cache efficiency
3. **Parallel Processing**: Utilize all CPU cores and GPU
4. **Algorithm Selection**: Choose appropriate algorithms for your use case

Ready to start building? Run your first example:

```bash
cd build
./ml_camera
```

Happy coding! 🚀
