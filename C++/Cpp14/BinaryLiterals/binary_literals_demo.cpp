// C++14 Binary Literals and Digit Separators
// Compile: g++ -std=c++14 -o binary_literals_demo binary_literals_demo.cpp
// Run: ./binary_literals_demo

#include <iostream>
#include <iomanip>
#include <bitset>
#include <string>
#include <cstdint>

void print_binary_info(const std::string& name, auto value) {
    std::cout << std::left << std::setw(20) << name 
              << "= " << std::setw(10) << value 
              << " (0b" << std::bitset<sizeof(value) * 8>(value) << ")" << std::endl;
}

int main() {
    std::cout << "=== C++14 BINARY LITERALS AND DIGIT SEPARATORS DEMO ===" << std::endl;
    
    // 1. Binary literals with 0b prefix
    std::cout << "\n1. Binary Literals (0b prefix):" << std::endl;
    
    auto bin1 = 0b1010;           // 10 in decimal
    auto bin2 = 0b11110000;       // 240 in decimal
    auto bin3 = 0b10101010;       // 170 in decimal
    auto bin4 = 0b11111111;       // 255 in decimal
    
    print_binary_info("0b1010", bin1);
    print_binary_info("0b11110000", bin2);
    print_binary_info("0b10101010", bin3);
    print_binary_info("0b11111111", bin4);
    
    // 2. Binary literals with digit separators
    std::cout << "\n2. Binary Literals with Digit Separators:" << std::endl;
    
    auto readable_bin1 = 0b1010'1010;           // Same as 0b10101010, but more readable
    auto readable_bin2 = 0b1111'0000'1111'0000; // 61680 in decimal
    auto readable_bin3 = 0b1'0000'0000;         // 256 in decimal
    auto readable_bin4 = 0b1111'1111'1111'1111; // 65535 in decimal
    
    print_binary_info("0b1010'1010", readable_bin1);
    print_binary_info("0b1111'0000'1111'0000", readable_bin2);
    print_binary_info("0b1'0000'0000", readable_bin3);
    print_binary_info("0b1111'1111'1111'1111", readable_bin4);
    
    // 3. Digit separators in other number formats
    std::cout << "\n3. Digit Separators in Different Number Formats:" << std::endl;
    
    // Decimal with separators
    auto large_decimal = 1'234'567'890;
    auto scientific = 1.234'567'89e10;
    
    // Hexadecimal with separators
    auto hex_value = 0xFF'EE'DD'CC;
    auto hex_address = 0x7FFF'FFFF;
    
    // Octal with separators
    auto octal_value = 0123'456'700;
    
    std::cout << "Decimal 1'234'567'890 = " << large_decimal << std::endl;
    std::cout << "Scientific 1.234'567'89e10 = " << scientific << std::endl;
    std::cout << "Hex 0xFF'EE'DD'CC = " << hex_value << " (decimal)" << std::endl;
    std::cout << "Hex 0x7FFF'FFFF = " << hex_address << " (decimal)" << std::endl;
    std::cout << "Octal 0123'456'700 = " << octal_value << " (decimal)" << std::endl;
    
    // 4. Bit manipulation examples
    std::cout << "\n4. Bit Manipulation with Binary Literals:" << std::endl;
    
    // Flags and masks
    constexpr auto READ_FLAG  = 0b0001;
    constexpr auto WRITE_FLAG = 0b0010;
    constexpr auto EXEC_FLAG  = 0b0100;
    constexpr auto ADMIN_FLAG = 0b1000;
    
    auto permissions = READ_FLAG | WRITE_FLAG;  // 0b0011
    
    std::cout << "Individual flags:" << std::endl;
    print_binary_info("READ_FLAG", READ_FLAG);
    print_binary_info("WRITE_FLAG", WRITE_FLAG);
    print_binary_info("EXEC_FLAG", EXEC_FLAG);
    print_binary_info("ADMIN_FLAG", ADMIN_FLAG);
    
    std::cout << "\nCombined permissions:" << std::endl;
    print_binary_info("READ | WRITE", permissions);
    
    // Check individual flags
    std::cout << "\nFlag checking:" << std::endl;
    std::cout << "Has READ: " << ((permissions & READ_FLAG) != 0) << std::endl;
    std::cout << "Has WRITE: " << ((permissions & WRITE_FLAG) != 0) << std::endl;
    std::cout << "Has EXEC: " << ((permissions & EXEC_FLAG) != 0) << std::endl;
    std::cout << "Has ADMIN: " << ((permissions & ADMIN_FLAG) != 0) << std::endl;
    
    // 5. Bit patterns and masks
    std::cout << "\n5. Common Bit Patterns and Masks:" << std::endl;
    
    constexpr auto ALL_ONES_8BIT  = 0b1111'1111;           // 0xFF
    constexpr auto ALTERNATING_1  = 0b1010'1010'1010'1010; // 0xAAAA
    constexpr auto ALTERNATING_2  = 0b0101'0101'0101'0101; // 0x5555
    constexpr auto NIBBLE_MASK    = 0b0000'1111;           // 0x0F
    constexpr auto HIGH_NIBBLE    = 0b1111'0000;           // 0xF0
    
    print_binary_info("ALL_ONES_8BIT", ALL_ONES_8BIT);
    print_binary_info("ALTERNATING_1", ALTERNATING_1);
    print_binary_info("ALTERNATING_2", ALTERNATING_2);
    print_binary_info("NIBBLE_MASK", NIBBLE_MASK);
    print_binary_info("HIGH_NIBBLE", HIGH_NIBBLE);
    
    // Extract nibbles from a byte
    uint8_t test_byte = 0b1101'0110;  // 0xD6
    uint8_t low_nibble = test_byte & NIBBLE_MASK;
    uint8_t high_nibble = (test_byte & HIGH_NIBBLE) >> 4;
    
    std::cout << "\nNibble extraction from 0b1101'0110:" << std::endl;
    print_binary_info("Original byte", test_byte);
    print_binary_info("Low nibble", low_nibble);
    print_binary_info("High nibble", high_nibble);
    
    // 6. Status registers and bit fields
    std::cout << "\n6. Status Registers and Bit Fields:" << std::endl;
    
    // Simulate a status register
    constexpr auto STATUS_OK       = 0b0000'0001;  // Bit 0
    constexpr auto STATUS_WARNING  = 0b0000'0010;  // Bit 1
    constexpr auto STATUS_ERROR    = 0b0000'0100;  // Bit 2
    constexpr auto STATUS_CRITICAL = 0b0000'1000;  // Bit 3
    constexpr auto STATUS_READY    = 0b0001'0000;  // Bit 4
    constexpr auto STATUS_BUSY     = 0b0010'0000;  // Bit 5
    constexpr auto STATUS_IDLE     = 0b0100'0000;  // Bit 6
    constexpr auto STATUS_DEBUG    = 0b1000'0000;  // Bit 7
    
    // Example status combinations
    auto system_status_1 = STATUS_OK | STATUS_READY;
    auto system_status_2 = STATUS_WARNING | STATUS_BUSY;
    auto system_status_3 = STATUS_ERROR | STATUS_CRITICAL | STATUS_DEBUG;
    
    auto print_status = [](const std::string& name, uint8_t status) {
        std::cout << name << " status: ";
        std::cout << std::bitset<8>(status) << " (";
        
        if (status & STATUS_OK)       std::cout << "OK ";
        if (status & STATUS_WARNING)  std::cout << "WARNING ";
        if (status & STATUS_ERROR)    std::cout << "ERROR ";
        if (status & STATUS_CRITICAL) std::cout << "CRITICAL ";
        if (status & STATUS_READY)    std::cout << "READY ";
        if (status & STATUS_BUSY)     std::cout << "BUSY ";
        if (status & STATUS_IDLE)     std::cout << "IDLE ";
        if (status & STATUS_DEBUG)    std::cout << "DEBUG ";
        
        std::cout << ")" << std::endl;
    };
    
    print_status("System 1", system_status_1);
    print_status("System 2", system_status_2);
    print_status("System 3", system_status_3);
    
    // 7. RGB Color representation
    std::cout << "\n7. RGB Color Representation:" << std::endl;
    
    // RGB colors as 24-bit values
    constexpr auto RED    = 0b1111'1111'0000'0000'0000'0000;  // 0xFF0000
    constexpr auto GREEN  = 0b0000'0000'1111'1111'0000'0000;  // 0x00FF00
    constexpr auto BLUE   = 0b0000'0000'0000'0000'1111'1111;  // 0x0000FF
    constexpr auto YELLOW = RED | GREEN;                       // 0xFFFF00
    constexpr auto CYAN   = GREEN | BLUE;                      // 0x00FFFF
    constexpr auto MAGENTA= RED | BLUE;                        // 0xFF00FF
    constexpr auto WHITE  = RED | GREEN | BLUE;               // 0xFFFFFF
    
    auto extract_rgb = [](uint32_t color) {
        uint8_t r = (color >> 16) & 0xFF;
        uint8_t g = (color >> 8) & 0xFF;
        uint8_t b = color & 0xFF;
        return std::make_tuple(r, g, b);
    };
    
    auto colors = {
        std::make_pair("RED", RED),
        std::make_pair("GREEN", GREEN),
        std::make_pair("BLUE", BLUE),
        std::make_pair("YELLOW", YELLOW),
        std::make_pair("CYAN", CYAN),
        std::make_pair("MAGENTA", MAGENTA),
        std::make_pair("WHITE", WHITE)
    };
    
    for (const auto& [name, color] : colors) {
        auto [r, g, b] = extract_rgb(color);
        std::cout << std::left << std::setw(8) << name 
                  << ": RGB(" << std::setw(3) << static_cast<int>(r) 
                  << ", " << std::setw(3) << static_cast<int>(g)
                  << ", " << std::setw(3) << static_cast<int>(b) << ") "
                  << "= 0x" << std::hex << std::uppercase << std::setfill('0') 
                  << std::setw(6) << color << std::dec << std::setfill(' ') << std::endl;
    }
    
    // 8. Network byte order and protocols
    std::cout << "\n8. Network Protocols and Bit Fields:" << std::endl;
    
    // Simulate TCP flags
    constexpr auto TCP_FIN = 0b0000'0001;  // Finish
    constexpr auto TCP_SYN = 0b0000'0010;  // Synchronize
    constexpr auto TCP_RST = 0b0000'0100;  // Reset
    constexpr auto TCP_PSH = 0b0000'1000;  // Push
    constexpr auto TCP_ACK = 0b0001'0000;  // Acknowledge
    constexpr auto TCP_URG = 0b0010'0000;  // Urgent
    constexpr auto TCP_ECE = 0b0100'0000;  // ECN Echo
    constexpr auto TCP_CWR = 0b1000'0000;  // Congestion Window Reduced
    
    // Common TCP flag combinations
    auto tcp_syn_packet = TCP_SYN;
    auto tcp_syn_ack = TCP_SYN | TCP_ACK;
    auto tcp_ack_packet = TCP_ACK;
    auto tcp_fin_ack = TCP_FIN | TCP_ACK;
    auto tcp_rst_packet = TCP_RST;
    
    auto print_tcp_flags = [](const std::string& packet_type, uint8_t flags) {
        std::cout << std::left << std::setw(12) << packet_type << ": ";
        std::cout << std::bitset<8>(flags) << " (";
        
        if (flags & TCP_FIN) std::cout << "FIN ";
        if (flags & TCP_SYN) std::cout << "SYN ";
        if (flags & TCP_RST) std::cout << "RST ";
        if (flags & TCP_PSH) std::cout << "PSH ";
        if (flags & TCP_ACK) std::cout << "ACK ";
        if (flags & TCP_URG) std::cout << "URG ";
        if (flags & TCP_ECE) std::cout << "ECE ";
        if (flags & TCP_CWR) std::cout << "CWR ";
        
        std::cout << ")" << std::endl;
    };
    
    print_tcp_flags("SYN", tcp_syn_packet);
    print_tcp_flags("SYN-ACK", tcp_syn_ack);
    print_tcp_flags("ACK", tcp_ack_packet);
    print_tcp_flags("FIN-ACK", tcp_fin_ack);
    print_tcp_flags("RST", tcp_rst_packet);
    
    // 9. Bit shifting and rotation examples
    std::cout << "\n9. Bit Shifting with Binary Literals:" << std::endl;
    
    auto original = 0b0000'1111;  // 15
    
    std::cout << "Original value:" << std::endl;
    print_binary_info("original", original);
    
    std::cout << "\nLeft shifts:" << std::endl;
    print_binary_info("original << 1", original << 1);
    print_binary_info("original << 2", original << 2);
    print_binary_info("original << 4", original << 4);
    
    auto shifted_value = 0b1111'0000;  // 240
    std::cout << "\nRight shifts:" << std::endl;
    print_binary_info("0b1111'0000", shifted_value);
    print_binary_info("shifted >> 1", shifted_value >> 1);
    print_binary_info("shifted >> 2", shifted_value >> 2);
    print_binary_info("shifted >> 4", shifted_value >> 4);
    
    // 10. Large integer literals with separators
    std::cout << "\n10. Large Integer Literals:" << std::endl;
    
    // Large integers with digit separators for readability
    auto large_binary = 0b1010'1010'1010'1010'1010'1010'1010'1010UL;
    auto large_decimal = 123'456'789'012'345UL;
    auto large_hex = 0x1234'5678'9ABC'DEFUL;
    
    std::cout << "Large binary: " << large_binary << std::endl;
    std::cout << "Large decimal: " << large_decimal << std::endl;
    std::cout << "Large hex: " << large_hex << std::endl;
    
    // Memory sizes
    constexpr auto ONE_KB = 1'024;
    constexpr auto ONE_MB = 1'024 * ONE_KB;
    constexpr auto ONE_GB = 1'024 * ONE_MB;
    
    std::cout << "\nMemory sizes:" << std::endl;
    std::cout << "1 KB = " << ONE_KB << " bytes" << std::endl;
    std::cout << "1 MB = " << ONE_MB << " bytes" << std::endl;
    std::cout << "1 GB = " << ONE_GB << " bytes" << std::endl;
    
    std::cout << "\n=== BINARY LITERALS & DIGIT SEPARATORS BENEFITS ===" << std::endl;
    std::cout << "✅ Binary literals (0b): Clear bit pattern representation" << std::endl;
    std::cout << "✅ Digit separators ('): Improved readability for large numbers" << std::endl;
    std::cout << "✅ Perfect for bit manipulation and flags" << std::endl;
    std::cout << "✅ Self-documenting code for hardware interfaces" << std::endl;
    std::cout << "✅ Works with all numeric literal types" << std::endl;
    std::cout << "✅ No runtime cost - purely compile-time feature" << std::endl;
    std::cout << "⚠️  Digit separators are ignored by compiler (formatting only)" << std::endl;
    std::cout << "⚠️  Binary literals still limited by integer type size" << std::endl;
    
    return 0;
}

/*
COMPILATION AND EXECUTION:

g++ -std=c++14 -Wall -Wextra -o binary_literals_demo binary_literals_demo.cpp
./binary_literals_demo

C++14 Binary Literals and Digit Separators:
1. Binary literals: 0b1010'1010 (prefix 0b or 0B)
2. Digit separators: 1'234'567 (single quote ' ignored by compiler)
3. Works with all numeric types: decimal, hex, octal, binary
4. Perfect for bit manipulation, flags, and hardware programming

Key Features:
- 0b prefix for binary literals
- Single quote (') as digit separator (purely visual)
- Works with all integer types and floating-point
- No performance impact - compile-time only

Common Use Cases:
- Bit flags and permissions
- Hardware register programming
- Network protocol implementations
- Color values (RGB, RGBA)
- Memory addresses and sizes
- Binary data patterns

Benefits:
- Self-documenting bit patterns
- Improved readability of large numbers
- Clear intent for bit-level operations
- Easier maintenance of hardware-related code
*/
