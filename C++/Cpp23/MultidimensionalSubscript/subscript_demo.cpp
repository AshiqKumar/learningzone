// C++23 Multidimensional Subscript Operator []
// Compile: g++ -std=c++23 -o subscript_demo subscript_demo.cpp
// Run: ./subscript_demo

#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <string>
#include <initializer_list>
#include <stdexcept>
#include <cassert>

// 1. Basic 2D Matrix class with multidimensional subscript
template<typename T>
class Matrix2D {
private:
    std::vector<std::vector<T>> data;
    size_t rows, cols;
    
public:
    Matrix2D(size_t r, size_t c) : rows(r), cols(c) {
        data.resize(rows);
        for (auto& row : data) {
            row.resize(cols);
        }
    }
    
    Matrix2D(std::initializer_list<std::initializer_list<T>> init) {
        rows = init.size();
        cols = init.begin()->size();
        data.reserve(rows);
        
        for (const auto& row : init) {
            data.emplace_back(row);
        }
    }
    
    // C++23: Multidimensional subscript operator
    T& operator[](size_t row, size_t col) {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data[row][col];
    }
    
    const T& operator[](size_t row, size_t col) const {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data[row][col];
    }
    
    // Traditional single-dimension access (for comparison)
    std::vector<T>& operator[](size_t row) {
        return data[row];
    }
    
    const std::vector<T>& operator[](size_t row) const {
        return data[row];
    }
    
    size_t get_rows() const { return rows; }
    size_t get_cols() const { return cols; }
    
    void print() const {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

// 2. 3D Tensor class
template<typename T>
class Tensor3D {
private:
    std::vector<T> data;
    size_t dim_x, dim_y, dim_z;
    
    size_t get_index(size_t x, size_t y, size_t z) const {
        return x * (dim_y * dim_z) + y * dim_z + z;
    }
    
public:
    Tensor3D(size_t x, size_t y, size_t z) : dim_x(x), dim_y(y), dim_z(z) {
        data.resize(x * y * z);
    }
    
    // C++23: 3D subscript operator
    T& operator[](size_t x, size_t y, size_t z) {
        if (x >= dim_x || y >= dim_y || z >= dim_z) {
            throw std::out_of_range("Tensor indices out of range");
        }
        return data[get_index(x, y, z)];
    }
    
    const T& operator[](size_t x, size_t y, size_t z) const {
        if (x >= dim_x || y >= dim_y || z >= dim_z) {
            throw std::out_of_range("Tensor indices out of range");
        }
        return data[get_index(x, y, z)];
    }
    
    size_t size_x() const { return dim_x; }
    size_t size_y() const { return dim_y; }
    size_t size_z() const { return dim_z; }
    
    void fill(const T& value) {
        std::fill(data.begin(), data.end(), value);
    }
    
    void print_slice(size_t x) const {
        if (x >= dim_x) return;
        
        std::cout << "Slice x=" << x << ":" << std::endl;
        for (size_t y = 0; y < dim_y; ++y) {
            for (size_t z = 0; z < dim_z; ++z) {
                std::cout << data[get_index(x, y, z)] << " ";
            }
            std::cout << std::endl;
        }
    }
};

// 3. Multidimensional map/associative container
template<typename... Keys>
class MultiMap {
private:
    using KeyTuple = std::tuple<Keys...>;
    std::map<KeyTuple, std::string> data;
    
public:
    // C++23: Variable number of keys
    std::string& operator[](Keys... keys) {
        return data[std::make_tuple(keys...)];
    }
    
    const std::string& operator[](Keys... keys) const {
        auto it = data.find(std::make_tuple(keys...));
        if (it != data.end()) {
            return it->second;
        }
        static const std::string empty;
        return empty;
    }
    
    bool contains(Keys... keys) const {
        return data.contains(std::make_tuple(keys...));
    }
    
    void erase(Keys... keys) {
        data.erase(std::make_tuple(keys...));
    }
    
    size_t size() const { return data.size(); }
    
    void print() const {
        for (const auto& [key, value] : data) {
            std::cout << "Key: (";
            print_tuple(key);
            std::cout << ") -> " << value << std::endl;
        }
    }
    
private:
    template<size_t I = 0, typename Tuple>
    void print_tuple(const Tuple& t) const {
        if constexpr (I < std::tuple_size_v<Tuple>) {
            if constexpr (I > 0) std::cout << ", ";
            std::cout << std::get<I>(t);
            print_tuple<I + 1>(t);
        }
    }
};

// 4. Image class with pixel access
class Image {
private:
    std::vector<std::array<uint8_t, 3>> pixels;  // RGB pixels
    size_t width, height;
    
public:
    Image(size_t w, size_t h) : width(w), height(h) {
        pixels.resize(w * h, {0, 0, 0});
    }
    
    // Access individual color channels
    uint8_t& operator[](size_t x, size_t y, size_t channel) {
        if (x >= width || y >= height || channel >= 3) {
            throw std::out_of_range("Image access out of bounds");
        }
        return pixels[y * width + x][channel];
    }
    
    const uint8_t& operator[](size_t x, size_t y, size_t channel) const {
        if (x >= width || y >= height || channel >= 3) {
            throw std::out_of_range("Image access out of bounds");
        }
        return pixels[y * width + x][channel];
    }
    
    // Access whole pixel (RGB array)
    std::array<uint8_t, 3>& operator[](size_t x, size_t y) {
        if (x >= width || y >= height) {
            throw std::out_of_range("Image access out of bounds");
        }
        return pixels[y * width + x];
    }
    
    const std::array<uint8_t, 3>& operator[](size_t x, size_t y) const {
        if (x >= width || y >= height) {
            throw std::out_of_range("Image access out of bounds");
        }
        return pixels[y * width + x];
    }
    
    size_t get_width() const { return width; }
    size_t get_height() const { return height; }
    
    void set_pixel(size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b) {
        if (x < width && y < height) {
            pixels[y * width + x] = {r, g, b};
        }
    }
    
    void print_ascii() const {
        for (size_t y = 0; y < height; ++y) {
            for (size_t x = 0; x < width; ++x) {
                const auto& pixel = pixels[y * width + x];
                // Simple grayscale conversion for ASCII display
                uint8_t gray = (pixel[0] + pixel[1] + pixel[2]) / 3;
                char c = ' ';
                if (gray > 200) c = '#';
                else if (gray > 150) c = '*';
                else if (gray > 100) c = '+';
                else if (gray > 50) c = '.';
                std::cout << c;
            }
            std::cout << std::endl;
        }
    }
};

// 5. Sparse matrix with coordinate access
template<typename T>
class SparseMatrix {
private:
    std::map<std::pair<size_t, size_t>, T> data;
    size_t rows, cols;
    T default_value;
    
public:
    SparseMatrix(size_t r, size_t c, T def = T{}) 
        : rows(r), cols(c), default_value(def) {}
    
    // Proxy class for assignment
    class Proxy {
        SparseMatrix& matrix;
        size_t row, col;
        
    public:
        Proxy(SparseMatrix& m, size_t r, size_t c) : matrix(m), row(r), col(c) {}
        
        operator T() const {
            auto it = matrix.data.find({row, col});
            return (it != matrix.data.end()) ? it->second : matrix.default_value;
        }
        
        Proxy& operator=(const T& value) {
            if (value != matrix.default_value) {
                matrix.data[{row, col}] = value;
            } else {
                matrix.data.erase({row, col});
            }
            return *this;
        }
    };
    
    // C++23: Multidimensional subscript returning proxy
    Proxy operator[](size_t row, size_t col) {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("SparseMatrix indices out of range");
        }
        return Proxy(*this, row, col);
    }
    
    T operator[](size_t row, size_t col) const {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("SparseMatrix indices out of range");
        }
        auto it = data.find({row, col});
        return (it != data.end()) ? it->second : default_value;
    }
    
    size_t get_rows() const { return rows; }
    size_t get_cols() const { return cols; }
    size_t get_non_zero_count() const { return data.size(); }
    
    void print() const {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::cout << (*this)[i, j] << " ";
            }
            std::cout << std::endl;
        }
    }
    
    void print_sparse() const {
        std::cout << "Non-zero elements:" << std::endl;
        for (const auto& [coord, value] : data) {
            std::cout << "(" << coord.first << "," << coord.second << ") = " << value << std::endl;
        }
    }
};

// 6. Multi-level configuration system
class Config {
private:
    std::map<std::string, std::map<std::string, std::string>> sections;
    
public:
    // Access configuration value by section and key
    std::string& operator[](const std::string& section, const std::string& key) {
        return sections[section][key];
    }
    
    const std::string& operator[](const std::string& section, const std::string& key) const {
        static const std::string empty;
        auto section_it = sections.find(section);
        if (section_it != sections.end()) {
            auto key_it = section_it->second.find(key);
            if (key_it != section_it->second.end()) {
                return key_it->second;
            }
        }
        return empty;
    }
    
    bool has_section(const std::string& section) const {
        return sections.contains(section);
    }
    
    bool has_key(const std::string& section, const std::string& key) const {
        auto section_it = sections.find(section);
        if (section_it != sections.end()) {
            return section_it->second.contains(key);
        }
        return false;
    }
    
    void print() const {
        for (const auto& [section_name, section_data] : sections) {
            std::cout << "[" << section_name << "]" << std::endl;
            for (const auto& [key, value] : section_data) {
                std::cout << "  " << key << " = " << value << std::endl;
            }
        }
    }
};

// 7. Game board with piece access
enum class Piece { Empty, Pawn, Rook, Knight, Bishop, Queen, King };
enum class Color { White, Black };

struct ChessPiece {
    Piece piece = Piece::Empty;
    Color color = Color::White;
    
    friend std::ostream& operator<<(std::ostream& os, const ChessPiece& p) {
        if (p.piece == Piece::Empty) {
            os << ".";
            return os;
        }
        
        char symbols[] = {'.', 'P', 'R', 'N', 'B', 'Q', 'K'};
        char symbol = symbols[static_cast<int>(p.piece)];
        if (p.color == Color::Black) {
            symbol = std::tolower(symbol);
        }
        os << symbol;
        return os;
    }
};

class ChessBoard {
private:
    std::array<std::array<ChessPiece, 8>, 8> board;
    
public:
    ChessBoard() {
        // Initialize empty board
        for (auto& row : board) {
            for (auto& piece : row) {
                piece = {Piece::Empty, Color::White};
            }
        }
    }
    
    // C++23: Access by chess notation or numeric coordinates
    ChessPiece& operator[](char file, int rank) {
        if (file < 'a' || file > 'h' || rank < 1 || rank > 8) {
            throw std::out_of_range("Invalid chess coordinates");
        }
        return board[8 - rank][file - 'a'];
    }
    
    const ChessPiece& operator[](char file, int rank) const {
        if (file < 'a' || file > 'h' || rank < 1 || rank > 8) {
            throw std::out_of_range("Invalid chess coordinates");
        }
        return board[8 - rank][file - 'a'];
    }
    
    // Numeric access
    ChessPiece& operator[](int row, int col) {
        if (row < 0 || row >= 8 || col < 0 || col >= 8) {
            throw std::out_of_range("Invalid board coordinates");
        }
        return board[row][col];
    }
    
    const ChessPiece& operator[](int row, int col) const {
        if (row < 0 || row >= 8 || col < 0 || col >= 8) {
            throw std::out_of_range("Invalid board coordinates");
        }
        return board[row][col];
    }
    
    void setup_initial_position() {
        // Set up initial chess position
        // White pieces
        board[7][0] = {Piece::Rook, Color::White};
        board[7][1] = {Piece::Knight, Color::White};
        board[7][2] = {Piece::Bishop, Color::White};
        board[7][3] = {Piece::Queen, Color::White};
        board[7][4] = {Piece::King, Color::White};
        board[7][5] = {Piece::Bishop, Color::White};
        board[7][6] = {Piece::Knight, Color::White};
        board[7][7] = {Piece::Rook, Color::White};
        
        for (int i = 0; i < 8; ++i) {
            board[6][i] = {Piece::Pawn, Color::White};
        }
        
        // Black pieces
        board[0][0] = {Piece::Rook, Color::Black};
        board[0][1] = {Piece::Knight, Color::Black};
        board[0][2] = {Piece::Bishop, Color::Black};
        board[0][3] = {Piece::Queen, Color::Black};
        board[0][4] = {Piece::King, Color::Black};
        board[0][5] = {Piece::Bishop, Color::Black};
        board[0][6] = {Piece::Knight, Color::Black};
        board[0][7] = {Piece::Rook, Color::Black};
        
        for (int i = 0; i < 8; ++i) {
            board[1][i] = {Piece::Pawn, Color::Black};
        }
    }
    
    void print() const {
        std::cout << "  abcdefgh" << std::endl;
        for (int rank = 8; rank >= 1; --rank) {
            std::cout << rank << " ";
            for (char file = 'a'; file <= 'h'; ++file) {
                std::cout << (*this)[file, rank];
            }
            std::cout << " " << rank << std::endl;
        }
        std::cout << "  abcdefgh" << std::endl;
    }
};

int main() {
    std::cout << "=== C++23 MULTIDIMENSIONAL SUBSCRIPT OPERATOR DEMO ===" << std::endl;
    
    // 1. Basic 2D Matrix
    std::cout << "\n1. 2D Matrix with Multidimensional Subscript:" << std::endl;
    
    Matrix2D<int> matrix(3, 4);
    
    // Fill matrix using new syntax
    for (size_t i = 0; i < matrix.get_rows(); ++i) {
        for (size_t j = 0; j < matrix.get_cols(); ++j) {
            matrix[i, j] = i * 10 + j;  // C++23 multidimensional subscript
        }
    }
    
    std::cout << "Matrix filled with multidimensional subscript:" << std::endl;
    matrix.print();
    
    // Compare with traditional access
    std::cout << "Access comparison - matrix[1,2] = " << matrix[1, 2] << std::endl;
    std::cout << "Traditional access - matrix[1][2] = " << matrix[1][2] << std::endl;
    
    // Initialize with initializer list
    Matrix2D<int> init_matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::cout << "\nInitialized matrix:" << std::endl;
    init_matrix.print();
    
    // 2. 3D Tensor
    std::cout << "\n2. 3D Tensor:" << std::endl;
    
    Tensor3D<double> tensor(2, 3, 4);
    
    // Fill tensor
    double value = 1.0;
    for (size_t x = 0; x < tensor.size_x(); ++x) {
        for (size_t y = 0; y < tensor.size_y(); ++y) {
            for (size_t z = 0; z < tensor.size_z(); ++z) {
                tensor[x, y, z] = value++;  // C++23 3D subscript
            }
        }
    }
    
    std::cout << "3D Tensor slices:" << std::endl;
    tensor.print_slice(0);
    std::cout << std::endl;
    tensor.print_slice(1);
    
    std::cout << "Direct access - tensor[1,2,3] = " << tensor[1, 2, 3] << std::endl;
    
    // 3. Multidimensional Map
    std::cout << "\n3. Multidimensional Associative Container:" << std::endl;
    
    MultiMap<std::string, int, std::string> multi_map;
    
    // Store data with multiple keys
    multi_map["user", 123, "name"] = "Alice";
    multi_map["user", 123, "email"] = "alice@example.com";
    multi_map["user", 456, "name"] = "Bob";
    multi_map["user", 456, "email"] = "bob@example.com";
    multi_map["config", 1, "debug"] = "true";
    multi_map["config", 2, "timeout"] = "30";
    
    std::cout << "MultiMap contents:" << std::endl;
    multi_map.print();
    
    std::cout << "\nDirect access:" << std::endl;
    std::cout << "User 123 name: " << multi_map["user", 123, "name"] << std::endl;
    std::cout << "Config 1 debug: " << multi_map["config", 1, "debug"] << std::endl;
    
    // 4. Image with RGB access
    std::cout << "\n4. Image with Multidimensional Pixel Access:" << std::endl;
    
    Image img(10, 6);
    
    // Draw some patterns
    for (size_t x = 0; x < img.get_width(); ++x) {
        for (size_t y = 0; y < img.get_height(); ++y) {
            // Create a gradient pattern
            img[x, y, 0] = (x * 255) / img.get_width();      // Red channel
            img[x, y, 1] = (y * 255) / img.get_height();     // Green channel  
            img[x, y, 2] = ((x + y) * 255) / (img.get_width() + img.get_height()); // Blue channel
        }
    }
    
    // Access individual channels
    std::cout << "Pixel (5,3) RGB values: " 
              << static_cast<int>(img[5, 3, 0]) << ", "
              << static_cast<int>(img[5, 3, 1]) << ", " 
              << static_cast<int>(img[5, 3, 2]) << std::endl;
    
    // Access whole pixel
    auto pixel = img[5, 3];
    std::cout << "Whole pixel (5,3): [" << static_cast<int>(pixel[0]) << ", "
              << static_cast<int>(pixel[1]) << ", " << static_cast<int>(pixel[2]) << "]" << std::endl;
    
    std::cout << "\nImage as ASCII art:" << std::endl;
    img.print_ascii();
    
    // 5. Sparse Matrix
    std::cout << "\n5. Sparse Matrix:" << std::endl;
    
    SparseMatrix<int> sparse(5, 5, 0);  // 5x5 matrix, default value 0
    
    // Set some values
    sparse[0, 0] = 1;
    sparse[1, 2] = 5;
    sparse[2, 4] = 10;
    sparse[4, 1] = 7;
    
    std::cout << "Sparse matrix (full view):" << std::endl;
    sparse.print();
    
    std::cout << "\nSparse representation:" << std::endl;
    sparse.print_sparse();
    
    std::cout << "Non-zero elements: " << sparse.get_non_zero_count() 
              << "/" << sparse.get_rows() * sparse.get_cols() << std::endl;
    
    // 6. Configuration System
    std::cout << "\n6. Multi-level Configuration:" << std::endl;
    
    Config config;
    
    // Set configuration values
    config["database", "host"] = "localhost";
    config["database", "port"] = "5432";
    config["database", "name"] = "myapp";
    config["logging", "level"] = "debug";
    config["logging", "file"] = "/var/log/app.log";
    config["server", "threads"] = "4";
    config["server", "timeout"] = "30";
    
    std::cout << "Configuration:" << std::endl;
    config.print();
    
    std::cout << "\nDirect access:" << std::endl;
    std::cout << "Database host: " << config["database", "host"] << std::endl;
    std::cout << "Server threads: " << config["server", "threads"] << std::endl;
    std::cout << "Missing value: '" << config["missing", "key"] << "'" << std::endl;
    
    // 7. Chess Board
    std::cout << "\n7. Chess Board with Chess Notation:" << std::endl;
    
    ChessBoard board;
    board.setup_initial_position();
    
    std::cout << "Initial chess position:" << std::endl;
    board.print();
    
    // Access using chess notation
    std::cout << "\nPiece access using chess notation:" << std::endl;
    std::cout << "Piece at e1: " << board['e', 1] << std::endl;
    std::cout << "Piece at e8: " << board['e', 8] << std::endl;
    std::cout << "Piece at d4: " << board['d', 4] << std::endl;
    
    // Make some moves
    auto piece_e2 = board['e', 2];
    board['e', 2] = {Piece::Empty, Color::White};
    board['e', 4] = piece_e2;
    
    auto piece_e7 = board['e', 7];
    board['e', 7] = {Piece::Empty, Color::Black};
    board['e', 5] = piece_e7;
    
    std::cout << "\nAfter moving e2-e4 and e7-e5:" << std::endl;
    board.print();
    
    // 8. Performance comparison
    std::cout << "\n8. Performance Comparison:" << std::endl;
    
    const size_t SIZE = 1000;
    Matrix2D<int> perf_matrix(SIZE, SIZE);
    
    // Time traditional access
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            perf_matrix[i][j] = i + j;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto traditional_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Time multidimensional access
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            perf_matrix[i, j] = i + j;  // C++23 multidimensional subscript
        }
    }
    end = std::chrono::high_resolution_clock::now();
    auto multidim_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Performance test (" << SIZE << "x" << SIZE << " matrix):" << std::endl;
    std::cout << "Traditional access: " << traditional_time.count() << " microseconds" << std::endl;
    std::cout << "Multidimensional access: " << multidim_time.count() << " microseconds" << std::endl;
    
    if (traditional_time.count() > 0 && multidim_time.count() > 0) {
        double ratio = static_cast<double>(multidim_time.count()) / traditional_time.count();
        std::cout << "Performance ratio: " << ratio << "x" << std::endl;
    }
    
    // 9. Error handling
    std::cout << "\n9. Error Handling:" << std::endl;
    
    Matrix2D<int> small_matrix(2, 2);
    small_matrix[0, 0] = 1;
    small_matrix[0, 1] = 2;
    small_matrix[1, 0] = 3;
    small_matrix[1, 1] = 4;
    
    std::cout << "Small matrix:" << std::endl;
    small_matrix.print();
    
    try {
        // This should work
        std::cout << "Valid access [0,1]: " << small_matrix[0, 1] << std::endl;
        
        // This should throw
        std::cout << "Invalid access [2,2]: " << small_matrix[2, 2] << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== MULTIDIMENSIONAL SUBSCRIPT BENEFITS ===" << std::endl;
    std::cout << "✅ More natural syntax for multidimensional containers" << std::endl;
    std::cout << "✅ Cleaner code - no nested bracket chains" << std::endl;
    std::cout << "✅ Better error checking - single bounds check point" << std::endl;
    std::cout << "✅ Consistent with mathematical notation" << std::endl;
    std::cout << "✅ Enables more sophisticated indexing schemes" << std::endl;
    std::cout << "✅ Better integration with domain-specific types" << std::endl;
    std::cout << "✅ No performance overhead compared to traditional methods" << std::endl;
    std::cout << "✅ Supports arbitrary number of dimensions" << std::endl;
    std::cout << "⚠️  Requires C++23 compiler support" << std::endl;
    std::cout << "⚠️  Need to maintain both single and multidimensional versions" << std::endl;
    std::cout << "⚠️  Potential ambiguity with comma operator (use parentheses)" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++23 -Wall -Wextra -o subscript_demo subscript_demo.cpp
./subscript_demo

C++23 Multidimensional Subscript Operator Key Features:
1. Natural syntax for accessing multidimensional containers
2. Single operator[] can accept multiple arguments
3. Cleaner alternative to chained subscript operators
4. Better integration with domain-specific indexing

Traditional C++:
matrix[i][j] = value;           // Chained subscript
tensor[x][y][z] = value;        // Multiple dereferences

C++23 Multidimensional Subscript:
matrix[i, j] = value;           // Single multidimensional access
tensor[x, y, z] = value;        // Natural 3D indexing
config[section, key] = value;   // Hierarchical access

Syntax:
class MyContainer {
public:
    T& operator[](Index1 i1, Index2 i2, ...) {
        // Implementation
    }
    
    const T& operator[](Index1 i1, Index2 i2, ...) const {
        // Const version
    }
};

Use Cases:
- Mathematical matrices and tensors
- Image processing (x, y, channel)
- Game boards (row, column)
- Configuration systems (section, key)
- Sparse data structures
- Geographic data (lat, lon, elevation)

Benefits:
- More readable and maintainable code
- Single point for bounds checking
- Consistent with mathematical notation
- Enables sophisticated indexing schemes
- Better error messages
- Domain-specific syntax

Design Considerations:
- Provide both const and non-const versions
- Consider proxy objects for complex assignment
- Handle bounds checking appropriately
- Maintain compatibility with traditional access
- Consider performance implications

Performance:
- Same performance as traditional chained access
- Potentially better optimization opportunities
- Single bounds check instead of multiple
- Better cache locality in some cases

Common Patterns:
1. Direct Access: return reference to element
2. Proxy Pattern: return proxy object for complex operations
3. Range Checking: validate all indices at once
4. Coordinate Systems: support different indexing schemes

Best Practices:
- Provide clear documentation for index ordering
- Use meaningful parameter names
- Consider providing multiple overloads
- Handle edge cases and invalid indices
- Test with various index combinations
*/
