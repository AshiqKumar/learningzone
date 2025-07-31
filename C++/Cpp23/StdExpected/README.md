# C++23 std::expected Documentation

## Overview
`std::expected<T, E>` is a C++23 library feature that provides type-safe error handling without exceptions. It represents a value that can either be successful (containing a value of type `T`) or contain an error (of type `E`).

## Why std::expected?

### Problems with Traditional Error Handling

1. **Exceptions**: Hidden control flow, performance overhead, can be forgotten
2. **Error codes**: Easy to ignore, no type safety, pollute return values  
3. **Optional**: Limited error information, just "success" or "no value"

### std::expected Benefits

- ✅ **Type Safety**: Errors are part of the type system
- ✅ **Performance**: No exception overhead, zero-cost when successful
- ✅ **Explicit**: Function signatures document possible errors
- ✅ **Composable**: Monadic operations for chaining error-prone code
- ✅ **Forced Handling**: Compiler ensures you check for errors

## Basic Usage

```cpp
#include <expected>
#include <iostream>

enum class Error {
    DIVISION_BY_ZERO,
    INVALID_INPUT
};

std::expected<double, Error> divide(double a, double b) {
    if (b == 0.0) {
        return std::unexpected(Error::DIVISION_BY_ZERO);
    }
    return a / b;  // Success case
}

int main() {
    auto result = divide(10.0, 2.0);
    
    if (result) {
        std::cout << "Result: " << *result << std::endl;  // 5.0
    } else {
        std::cout << "Error occurred" << std::endl;
    }
}
```

## Creating Expected Values

```cpp
// Success cases
std::expected<int, Error> success1 = 42;
std::expected<int, Error> success2{42};
auto success3 = std::expected<int, Error>(42);

// Error cases  
std::expected<int, Error> error1 = std::unexpected(Error::INVALID_INPUT);
auto error2 = std::unexpected(Error::DIVISION_BY_ZERO);
```

## Value Access Methods

```cpp
std::expected<int, Error> result = get_value();

// Check if successful
if (result.has_value()) { /* success */ }
if (result) { /* success */ }            // Implicit conversion to bool
if (!result) { /* error */ }

// Get value (throws std::bad_expected_access if error)
int value = result.value();
int value = *result;                      // Same as above

// Get value or default
int value = result.value_or(0);           // Returns 0 if error

// Get error (only valid if has error)
if (!result) {
    Error err = result.error();
}
```

## Monadic Operations (C++23)

Monadic operations allow chaining operations while handling errors gracefully:

```cpp
auto pipeline = parse_string(input)
    .and_then([](int x) -> std::expected<int, Error> {
        if (x < 0) return std::unexpected(Error::INVALID_INPUT);
        return x * 2;
    })
    .transform([](int x) { return x + 1; })  // Only if successful
    .or_else([](Error e) -> std::expected<int, Error> {
        // Handle error, return default or propagate
        return 0;  // Default value
    });
```

### Monadic Operation Details

- **`and_then(func)`**: Chain operations that return `expected`. Short-circuits on error.
- **`transform(func)`**: Transform the success value. Short-circuits on error.
- **`or_else(func)`**: Handle errors, potentially recovering with a default value.

## Error Handling Patterns

### Pattern 1: Simple Check and Handle
```cpp
auto result = risky_operation();
if (result) {
    use_value(*result);
} else {
    handle_error(result.error());
}
```

### Pattern 2: Early Return
```cpp
auto process_data() -> std::expected<ProcessedData, Error> {
    auto parsed = parse_input();
    if (!parsed) return std::unexpected(parsed.error());
    
    auto validated = validate(*parsed);  
    if (!validated) return std::unexpected(validated.error());
    
    return process(*validated);
}
```

### Pattern 3: Monadic Chain
```cpp
auto result = parse_input()
    .and_then(validate)
    .and_then(process)
    .transform(format_output)
    .or_else(handle_error);
```

### Pattern 4: Multiple Error Types
```cpp
// Union of error types
using AnyError = std::variant<ParseError, ValidationError, ProcessError>;

auto convert_error = [](ParseError e) -> AnyError { return e; };

auto result = parse_input()
    .or_else(convert_error)
    .and_then(validate_and_process);
```

## Performance Considerations

### vs Exceptions
- **Expected**: ~2-3x faster for error cases, similar for success cases
- **No stack unwinding**: Predictable performance
- **Better optimization**: Compilers can optimize expected paths better

### vs Optional  
- **Similar performance** for success cases
- **Richer error information** without performance penalty
- **Better debugging** with detailed error context

### Memory Layout
```cpp
// Typical layout (implementation-dependent)
std::expected<T, E> {
    union {
        T value;
        E error;  
    };
    bool has_value;
};
```

## Best Practices

### 1. Use Meaningful Error Types
```cpp
// ❌ Poor: Generic error
std::expected<Data, int> parse_file(const std::string& filename);

// ✅ Good: Specific error enum
enum class FileError { NOT_FOUND, PERMISSION_DENIED, INVALID_FORMAT };
std::expected<Data, FileError> parse_file(const std::string& filename);
```

### 2. Chain Operations Safely
```cpp
// ❌ Nested checks
auto step1 = parse_input();
if (!step1) return handle_error(step1.error());

auto step2 = validate(*step1);
if (!step2) return handle_error(step2.error());

// ✅ Monadic chain
return parse_input()
    .and_then(validate)
    .and_then(process);
```

### 3. Provide Good Error Context
```cpp
enum class ValidationError {
    EMPTY_INPUT,
    TOO_LONG,
    INVALID_CHARACTER,
    OUT_OF_RANGE
};

// Include position information, expected vs actual, etc.
struct DetailedError {
    ValidationError type;
    size_t position;
    std::string message;
};
```

### 4. Use value_or() for Simple Defaults
```cpp
// Simple default values
auto config = parse_config().value_or(get_default_config());
int port = parse_port().value_or(8080);
```

### 5. Document Error Conditions
```cpp
/// Parse configuration file
/// @returns Configuration on success
/// @error FileError::NOT_FOUND if file doesn't exist  
/// @error FileError::PERMISSION_DENIED if no read access
/// @error ParseError::INVALID_FORMAT if malformed content
std::expected<Config, std::variant<FileError, ParseError>> 
parse_config_file(const std::string& path);
```

## Common Patterns

### Resource Management
```cpp
class FileHandle {
public:
    static std::expected<FileHandle, FileError> open(const std::string& path) {
        FILE* f = fopen(path.c_str(), "r");
        if (!f) return std::unexpected(FileError::CANNOT_OPEN);
        return FileHandle{f};
    }
    
    std::expected<std::string, FileError> read_line() {
        char buffer[1024];
        if (!fgets(buffer, sizeof(buffer), file_)) {
            if (feof(file_)) return std::unexpected(FileError::END_OF_FILE);
            return std::unexpected(FileError::READ_ERROR);
        }
        return std::string{buffer};
    }
    
private:
    FileHandle(FILE* f) : file_(f) {}
    FILE* file_;
};
```

### Validation Pipeline
```cpp
auto validate_user_input(const std::string& input) 
    -> std::expected<ValidatedInput, ValidationError> {
    
    return check_not_empty(input)
        .and_then(check_length)
        .and_then(check_format)
        .and_then(check_business_rules)
        .transform([](const auto& validated) {
            return ValidatedInput{validated};
        });
}
```

### Configuration Loading
```cpp
auto load_configuration(const std::string& config_path)
    -> std::expected<Config, ConfigError> {
    
    return read_file(config_path)
        .and_then(parse_json)
        .and_then(validate_config_schema)
        .and_then(apply_defaults)
        .transform([](const auto& json) {
            return Config::from_json(json);
        });
}
```

## Migration from Exceptions

### Before (Exceptions)
```cpp
Config load_config(const std::string& path) {
    try {
        auto content = read_file(path);  // May throw
        auto json = parse_json(content); // May throw  
        return Config::from_json(json);  // May throw
    } catch (const FileError& e) {
        // Handle file errors
        throw ConfigError("File error: " + e.message());
    } catch (const ParseError& e) {
        // Handle parse errors
        throw ConfigError("Parse error: " + e.message());
    }
}
```

### After (Expected)
```cpp
auto load_config(const std::string& path) 
    -> std::expected<Config, ConfigError> {
    
    return read_file(path)
        .and_then(parse_json)
        .transform([](const auto& json) {
            return Config::from_json(json);
        })
        .or_else([](const auto& error) -> std::expected<Config, ConfigError> {
            return std::unexpected(ConfigError{error});
        });
}
```

## Compiler Support

- **GCC**: 13+ (with `-std=c++23`)
- **Clang**: 16+ (with `-std=c++23`) 
- **MSVC**: Visual Studio 2022 17.6+

## Common Pitfalls

1. **Forgetting to check**: Always check result before using
2. **Using value() without checking**: Can throw `std::bad_expected_access`
3. **Mixing error types**: Be consistent with error type hierarchies
4. **Over-nesting**: Use monadic operations instead of deep nesting
5. **Performance assumptions**: Profile error-heavy vs exception-heavy code

## Summary

`std::expected` provides a modern, type-safe approach to error handling that:
- Makes errors explicit in function signatures
- Provides better performance than exceptions
- Enables functional programming patterns
- Forces proper error handling at compile time
- Maintains zero-cost abstraction principles

It's particularly valuable for systems programming, parsing, I/O operations, and any domain where errors are common and should be handled explicitly.
