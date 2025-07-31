// C++23 std::mdspan - Multidimensional Array Views
// Compile: g++ -std=c++23 -o mdspan_demo mdspan_demo.cpp
// Run: ./mdspan_demo

#include <iostream>
#include <vector>
#include <array>
#include <mdspan>
#include <memory>
#include <random>
#include <iomanip>
#include <chrono>
#include <numeric>
#include <algorithm>

// 1. Basic mdspan usage with different layouts
void demonstrate_basic_usage() {
    std::cout << "1. Basic mdspan Usage:" << std::endl;
    
    // Create a 1D data array
    std::vector<int> data(12);
    std::iota(data.begin(), data.end(), 1);  // Fill with 1, 2, 3, ..., 12
    
    // Create different views of the same data
    
    // 2D view: 3x4 matrix (row-major by default)
    std::mdspan<int, std::dextents<size_t, 2>> matrix_2d(data.data(), 3, 4);
    
    std::cout << "2D Matrix (3x4):" << std::endl;
    for (size_t i = 0; i < matrix_2d.extent(0); ++i) {
        for (size_t j = 0; j < matrix_2d.extent(1); ++j) {
            std::cout << std::setw(3) << matrix_2d[i, j] << " ";
        }
        std::cout << std::endl;
    }
    
    // 3D view: 2x3x2 tensor
    std::mdspan<int, std::dextents<size_t, 3>> tensor_3d(data.data(), 2, 3, 2);
    
    std::cout << "\n3D Tensor (2x3x2):" << std::endl;
    for (size_t i = 0; i < tensor_3d.extent(0); ++i) {
        std::cout << "Layer " << i << ":" << std::endl;
        for (size_t j = 0; j < tensor_3d.extent(1); ++j) {
            for (size_t k = 0; k < tensor_3d.extent(2); ++k) {
                std::cout << std::setw(3) << tensor_3d[i, j, k] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

// 2. Different memory layouts
void demonstrate_layouts() {
    std::cout << "2. Memory Layouts:" << std::endl;
    
    std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    
    // Row-major layout (default)
    std::mdspan<int, std::dextents<size_t, 2>, std::layout_right> row_major(data.data(), 3, 4);
    
    // Column-major layout  
    std::mdspan<int, std::dextents<size_t, 2>, std::layout_left> col_major(data.data(), 3, 4);
    
    std::cout << "Original data: ";
    for (int val : data) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\nRow-major layout (layout_right):" << std::endl;
    for (size_t i = 0; i < row_major.extent(0); ++i) {
        for (size_t j = 0; j < row_major.extent(1); ++j) {
            std::cout << std::setw(3) << row_major[i, j] << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "\nColumn-major layout (layout_left):" << std::endl;
    for (size_t i = 0; i < col_major.extent(0); ++i) {
        for (size_t j = 0; j < col_major.extent(1); ++j) {
            std::cout << std::setw(3) << col_major[i, j] << " ";
        }
        std::cout << std::endl;
    }
}

// 3. Fixed-size extents
void demonstrate_fixed_extents() {
    std::cout << "\n3. Fixed-size Extents:" << std::endl;
    
    // Static array with compile-time known dimensions
    std::array<double, 20> data;
    std::iota(data.begin(), data.end(), 1.0);
    
    // Fixed 4x5 matrix - dimensions known at compile time
    std::mdspan<double, std::extents<size_t, 4, 5>> fixed_matrix(data.data());
    
    std::cout << "Fixed 4x5 matrix:" << std::endl;
    for (size_t i = 0; i < fixed_matrix.extent(0); ++i) {
        for (size_t j = 0; j < fixed_matrix.extent(1); ++j) {
            std::cout << std::setw(6) << std::fixed << std::setprecision(1) 
                      << fixed_matrix[i, j] << " ";
        }
        std::cout << std::endl;
    }
    
    // Mixed static/dynamic extents
    std::mdspan<double, std::extents<size_t, 4, std::dynamic_extent>> mixed_matrix(data.data(), 5);
    
    std::cout << "\nMixed extents (4 x dynamic):" << std::endl;
    for (size_t i = 0; i < mixed_matrix.extent(0); ++i) {
        for (size_t j = 0; j < mixed_matrix.extent(1); ++j) {
            std::cout << std::setw(6) << std::fixed << std::setprecision(1) 
                      << mixed_matrix[i, j] << " ";
        }
        std::cout << std::endl;
    }
}

// 4. Submdspan operations (C++23 feature)
void demonstrate_submdspan() {
    std::cout << "\n4. Submdspan Operations:" << std::endl;
    
    std::vector<int> data(24);
    std::iota(data.begin(), data.end(), 1);
    
    // Create a 4x6 matrix
    std::mdspan<int, std::dextents<size_t, 2>> full_matrix(data.data(), 4, 6);
    
    std::cout << "Full 4x6 matrix:" << std::endl;
    for (size_t i = 0; i < full_matrix.extent(0); ++i) {
        for (size_t j = 0; j < full_matrix.extent(1); ++j) {
            std::cout << std::setw(3) << full_matrix[i, j] << " ";
        }
        std::cout << std::endl;
    }
    
    // Extract a submatrix (rows 1-2, columns 2-4)
    auto sub_matrix = std::submdspan(full_matrix, 
                                    std::pair{1, 3},    // rows 1-2 (exclusive end)
                                    std::pair{2, 5});   // cols 2-4 (exclusive end)
    
    std::cout << "\nSubmatrix [1:3, 2:5]:" << std::endl;
    for (size_t i = 0; i < sub_matrix.extent(0); ++i) {
        for (size_t j = 0; j < sub_matrix.extent(1); ++j) {
            std::cout << std::setw(3) << sub_matrix[i, j] << " ";
        }
        std::cout << std::endl;
    }
    
    // Extract a single row
    auto row_2 = std::submdspan(full_matrix, 2, std::full_extent);
    
    std::cout << "\nRow 2:" << std::endl;
    for (size_t j = 0; j < row_2.extent(0); ++j) {
        std::cout << std::setw(3) << row_2[j] << " ";
    }
    std::cout << std::endl;
    
    // Extract a single column
    auto col_3 = std::submdspan(full_matrix, std::full_extent, 3);
    
    std::cout << "\nColumn 3:" << std::endl;
    for (size_t i = 0; i < col_3.extent(0); ++i) {
        std::cout << std::setw(3) << col_3[i] << " ";
    }
    std::cout << std::endl;
}

// 5. Mathematical operations with mdspan
template<typename T, typename Extents>
void print_matrix(const std::mdspan<T, Extents>& matrix, const std::string& name) {
    std::cout << name << ":" << std::endl;
    for (size_t i = 0; i < matrix.extent(0); ++i) {
        for (size_t j = 0; j < matrix.extent(1); ++j) {
            std::cout << std::setw(8) << std::fixed << std::setprecision(2) 
                      << matrix[i, j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Matrix multiplication using mdspan
template<typename T>
void matrix_multiply(const std::mdspan<const T, std::dextents<size_t, 2>>& A,
                    const std::mdspan<const T, std::dextents<size_t, 2>>& B,
                    std::mdspan<T, std::dextents<size_t, 2>>& C) {
    
    assert(A.extent(1) == B.extent(0));
    assert(A.extent(0) == C.extent(0));
    assert(B.extent(1) == C.extent(1));
    
    // Initialize result to zero
    for (size_t i = 0; i < C.extent(0); ++i) {
        for (size_t j = 0; j < C.extent(1); ++j) {
            C[i, j] = T{};
        }
    }
    
    // Perform multiplication
    for (size_t i = 0; i < A.extent(0); ++i) {
        for (size_t j = 0; j < B.extent(1); ++j) {
            for (size_t k = 0; k < A.extent(1); ++k) {
                C[i, j] += A[i, k] * B[k, j];
            }
        }
    }
}

void demonstrate_mathematical_operations() {
    std::cout << "\n5. Mathematical Operations:" << std::endl;
    
    // Create matrices
    std::vector<double> A_data{1.0, 2.0, 3.0,
                              4.0, 5.0, 6.0};
    std::vector<double> B_data{7.0, 8.0,
                              9.0, 10.0,
                              11.0, 12.0};
    std::vector<double> C_data(4, 0.0);  // 2x2 result matrix
    
    // Create mdspan views
    std::mdspan<const double, std::dextents<size_t, 2>> A(A_data.data(), 2, 3);
    std::mdspan<const double, std::dextents<size_t, 2>> B(B_data.data(), 3, 2);
    std::mdspan<double, std::dextents<size_t, 2>> C(C_data.data(), 2, 2);
    
    print_matrix(A, "Matrix A (2x3)");
    print_matrix(B, "Matrix B (3x2)");
    
    // Perform matrix multiplication
    matrix_multiply(A, B, C);
    
    print_matrix(C, "Result C = A * B (2x2)");
    
    // Element-wise operations
    std::vector<double> D_data(6);
    std::mdspan<double, std::dextents<size_t, 2>> D(D_data.data(), 2, 3);
    
    // Copy A to D and multiply by 2
    for (size_t i = 0; i < A.extent(0); ++i) {
        for (size_t j = 0; j < A.extent(1); ++j) {
            D[i, j] = A[i, j] * 2.0;
        }
    }
    
    print_matrix(D, "Matrix D = A * 2");
}

// 6. Working with different data types
void demonstrate_different_types() {
    std::cout << "\n6. Different Data Types:" << std::endl;
    
    // Integer matrix
    std::vector<int> int_data{1, 2, 3, 4, 5, 6};
    std::mdspan<int, std::dextents<size_t, 2>> int_matrix(int_data.data(), 2, 3);
    
    std::cout << "Integer matrix:" << std::endl;
    for (size_t i = 0; i < int_matrix.extent(0); ++i) {
        for (size_t j = 0; j < int_matrix.extent(1); ++j) {
            std::cout << std::setw(3) << int_matrix[i, j] << " ";
        }
        std::cout << std::endl;
    }
    
    // Complex number matrix (using std::complex)
    std::vector<std::complex<double>> complex_data{
        {1.0, 1.0}, {2.0, -1.0},
        {3.0, 2.0}, {4.0, -2.0}
    };
    std::mdspan<std::complex<double>, std::dextents<size_t, 2>> complex_matrix(
        complex_data.data(), 2, 2);
    
    std::cout << "\nComplex matrix:" << std::endl;
    for (size_t i = 0; i < complex_matrix.extent(0); ++i) {
        for (size_t j = 0; j < complex_matrix.extent(1); ++j) {
            auto val = complex_matrix[i, j];
            std::cout << "(" << std::setw(4) << std::fixed << std::setprecision(1) 
                      << val.real() << "," << std::setw(4) << val.imag() << "i) ";
        }
        std::cout << std::endl;
    }
    
    // Boolean matrix for bit operations
    std::vector<bool> bool_data{true, false, true, false, true, false};
    // Note: std::vector<bool> has special behavior, use array instead
    std::array<bool, 6> bool_array{true, false, true, false, true, false};
    std::mdspan<bool, std::dextents<size_t, 2>> bool_matrix(bool_array.data(), 2, 3);
    
    std::cout << "\nBoolean matrix:" << std::endl;
    for (size_t i = 0; i < bool_matrix.extent(0); ++i) {
        for (size_t j = 0; j < bool_matrix.extent(1); ++j) {
            std::cout << std::setw(2) << (bool_matrix[i, j] ? "T" : "F") << " ";
        }
        std::cout << std::endl;
    }
}

// 7. Performance comparison with traditional approaches
void performance_comparison() {
    std::cout << "\n7. Performance Comparison:" << std::endl;
    
    constexpr size_t rows = 1000;
    constexpr size_t cols = 1000;
    constexpr int iterations = 100;
    
    // Prepare data
    std::vector<double> data(rows * cols);
    std::iota(data.begin(), data.end(), 1.0);
    
    // Traditional 2D vector approach
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<std::vector<double>> vec_2d(rows, std::vector<double>(cols));
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                vec_2d[i][j] = data[i * cols + j] * 2.0;
            }
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto vec_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // mdspan approach
    start = std::chrono::high_resolution_clock::now();
    
    std::mdspan<double, std::dextents<size_t, 2>> matrix(data.data(), rows, cols);
    std::vector<double> result_data(rows * cols);
    std::mdspan<double, std::dextents<size_t, 2>> result_matrix(result_data.data(), rows, cols);
    
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result_matrix[i, j] = matrix[i, j] * 2.0;
            }
        }
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto mdspan_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Raw pointer approach (for comparison)
    start = std::chrono::high_resolution_clock::now();
    
    std::vector<double> raw_result(rows * cols);
    double* raw_data = data.data();
    double* raw_result_data = raw_result.data();
    
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                raw_result_data[i * cols + j] = raw_data[i * cols + j] * 2.0;
            }
        }
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto raw_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Performance (" << rows << "x" << cols << " matrix, " 
              << iterations << " iterations):" << std::endl;
    std::cout << "2D vector:     " << vec_time.count() << " microseconds" << std::endl;
    std::cout << "mdspan:        " << mdspan_time.count() << " microseconds" << std::endl;
    std::cout << "Raw pointers:  " << raw_time.count() << " microseconds" << std::endl;
    
    std::cout << "mdspan vs 2D vector: " 
              << (static_cast<double>(mdspan_time.count()) / vec_time.count()) << "x" << std::endl;
    std::cout << "mdspan vs raw:       " 
              << (static_cast<double>(mdspan_time.count()) / raw_time.count()) << "x" << std::endl;
}

// 8. Custom accessor for specialized memory access
template<typename T>
struct checked_accessor {
    using offset_policy = std::default_accessor<T>;
    using element_type = T;
    using reference = T&;
    using data_handle_type = T*;
    
    constexpr checked_accessor() noexcept = default;
    
    template<typename U>
    constexpr checked_accessor(const checked_accessor<U>& other) noexcept {}
    
    constexpr reference access(data_handle_type p, size_t i) const noexcept {
        // Add bounds checking or logging here
        std::cout << "Accessing index " << i << std::endl;
        return p[i];
    }
    
    constexpr data_handle_type offset(data_handle_type p, size_t i) const noexcept {
        return p + i;
    }
};

void demonstrate_custom_accessor() {
    std::cout << "\n8. Custom Accessor:" << std::endl;
    
    std::vector<int> data{1, 2, 3, 4, 5, 6};
    
    // mdspan with custom accessor that logs access
    std::mdspan<int, std::dextents<size_t, 2>, std::layout_right, checked_accessor<int>>
        logged_matrix(data.data(), 2, 3);
    
    std::cout << "Accessing elements with custom accessor:" << std::endl;
    for (size_t i = 0; i < logged_matrix.extent(0); ++i) {
        for (size_t j = 0; j < logged_matrix.extent(1); ++j) {
            std::cout << "Value: " << logged_matrix[i, j] << std::endl;
        }
    }
}

// 9. Real-world example: Image processing
struct Pixel {
    uint8_t r, g, b, a;
    
    Pixel() : r(0), g(0), b(0), a(255) {}
    Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}
};

void demonstrate_image_processing() {
    std::cout << "\n9. Image Processing Example:" << std::endl;
    
    constexpr size_t width = 8;
    constexpr size_t height = 6;
    
    // Create a simple image
    std::vector<Pixel> image_data(width * height);
    
    // Fill with a gradient pattern
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            uint8_t intensity = static_cast<uint8_t>((x + y) * 255 / (width + height - 2));
            image_data[y * width + x] = Pixel(intensity, intensity / 2, intensity / 4);
        }
    }
    
    // Create mdspan view
    std::mdspan<Pixel, std::dextents<size_t, 2>> image(image_data.data(), height, width);
    
    std::cout << "Original image (showing red channel):" << std::endl;
    for (size_t y = 0; y < image.extent(0); ++y) {
        for (size_t x = 0; x < image.extent(1); ++x) {
            std::cout << std::setw(4) << static_cast<int>(image[y, x].r);
        }
        std::cout << std::endl;
    }
    
    // Apply a simple blur filter (3x3 kernel)
    std::vector<Pixel> blurred_data(width * height);
    std::mdspan<Pixel, std::dextents<size_t, 2>> blurred(blurred_data.data(), height, width);
    
    for (size_t y = 1; y < image.extent(0) - 1; ++y) {
        for (size_t x = 1; x < image.extent(1) - 1; ++x) {
            int sum_r = 0, sum_g = 0, sum_b = 0;
            
            // 3x3 kernel
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    const auto& pixel = image[y + dy, x + dx];
                    sum_r += pixel.r;
                    sum_g += pixel.g;
                    sum_b += pixel.b;
                }
            }
            
            blurred[y, x] = Pixel(
                static_cast<uint8_t>(sum_r / 9),
                static_cast<uint8_t>(sum_g / 9),
                static_cast<uint8_t>(sum_b / 9)
            );
        }
    }
    
    std::cout << "\nBlurred image (showing red channel):" << std::endl;
    for (size_t y = 0; y < blurred.extent(0); ++y) {
        for (size_t x = 0; x < blurred.extent(1); ++x) {
            std::cout << std::setw(4) << static_cast<int>(blurred[y, x].r);
        }
        std::cout << std::endl;
    }
}

// 10. Best practices and patterns
void demonstrate_best_practices() {
    std::cout << "\n10. Best Practices:" << std::endl;
    
    // 1. Use const correctness
    std::vector<double> data{1.0, 2.0, 3.0, 4.0};
    std::mdspan<const double, std::dextents<size_t, 2>> const_matrix(data.data(), 2, 2);
    
    // 2. Use appropriate extent types
    // For compile-time known dimensions
    std::mdspan<double, std::extents<size_t, 2, 2>> static_matrix(data.data());
    
    // For runtime dimensions
    std::mdspan<double, std::dextents<size_t, 2>> dynamic_matrix(data.data(), 2, 2);
    
    // 3. Use submdspan for efficient slicing
    auto first_row = std::submdspan(dynamic_matrix, 0, std::full_extent);
    
    // 4. Prefer mdspan over raw multi-dimensional indexing
    std::cout << "Best practice examples:" << std::endl;
    std::cout << "Static matrix [1,1] = " << static_matrix[1, 1] << std::endl;
    std::cout << "Dynamic matrix [0,1] = " << dynamic_matrix[0, 1] << std::endl;
    std::cout << "First row [1] = " << first_row[1] << std::endl;
    
    // 5. Use appropriate layouts for your access patterns
    std::cout << "Layout considerations:" << std::endl;
    std::cout << "- Use layout_right (default) for row-major access" << std::endl;
    std::cout << "- Use layout_left for column-major access (Fortran-style)" << std::endl;
    std::cout << "- Consider cache efficiency for your specific use case" << std::endl;
}

int main() {
    std::cout << "=== C++23 STD::MDSPAN DEMO ===" << std::endl;
    
    demonstrate_basic_usage();
    demonstrate_layouts();
    demonstrate_fixed_extents();
    demonstrate_submdspan();
    demonstrate_mathematical_operations();
    demonstrate_different_types();
    performance_comparison();
    demonstrate_custom_accessor();
    demonstrate_image_processing();
    demonstrate_best_practices();
    
    std::cout << "\n=== STD::MDSPAN BENEFITS ===" << std::endl;
    std::cout << "✅ Zero-overhead abstraction for multidimensional arrays" << std::endl;
    std::cout << "✅ Type-safe multidimensional indexing" << std::endl;
    std::cout << "✅ Support for different memory layouts (row/column major)" << std::endl;
    std::cout << "✅ Compile-time and runtime extent specification" << std::endl;
    std::cout << "✅ Efficient subarray operations with submdspan" << std::endl;
    std::cout << "✅ Custom memory access patterns with accessors" << std::endl;
    std::cout << "✅ Interoperability with existing C++ containers" << std::endl;
    std::cout << "✅ Performance comparable to raw pointer arithmetic" << std::endl;
    std::cout << "⚠️  Requires C++23 compiler support" << std::endl;
    std::cout << "⚠️  Learning curve for advanced features" << std::endl;
    std::cout << "⚠️  Template complexity can affect compile times" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++23 -Wall -Wextra -O2 -o mdspan_demo mdspan_demo.cpp
./mdspan_demo

C++23 std::mdspan Key Features:
1. Zero-overhead multidimensional array views
2. Type-safe indexing with compile-time bounds checking
3. Multiple memory layout support (row/column major)
4. Efficient subarray operations
5. Custom memory access patterns

Basic Usage:
std::vector<int> data(12);
std::mdspan<int, std::dextents<size_t, 2>> matrix(data.data(), 3, 4);
int value = matrix[i, j];  // Multi-dimensional indexing

Extent Types:
- std::dextents<size_t, N>: All dimensions runtime
- std::extents<size_t, D1, D2, ...>: All dimensions compile-time
- std::extents<size_t, D1, std::dynamic_extent>: Mixed

Memory Layouts:
- std::layout_right: Row-major (C-style, default)
- std::layout_left: Column-major (Fortran-style)
- Custom layouts possible

Submdspan Operations:
auto sub = std::submdspan(matrix, 
                         std::pair{1, 3},        // rows 1-2
                         std::full_extent);      // all columns

Benefits over Raw Pointers:
- Type safety and bounds checking
- Self-documenting code
- No manual index calculation
- Easier to maintain and debug
- Support for different layouts

Benefits over std::vector<std::vector<T>>:
- Better cache locality
- No pointer indirection
- Smaller memory footprint
- Better optimization opportunities
- Uniform interface for different layouts

Use Cases:
- Scientific computing and linear algebra
- Image and signal processing
- Game development (matrices, tensors)
- Machine learning (multidimensional data)
- Any application with multidimensional data

Best Practices:
- Use const mdspan for read-only access
- Choose appropriate extent types (static vs dynamic)
- Consider memory layout for your access patterns
- Use submdspan for efficient slicing
- Leverage custom accessors for specialized needs
*/
