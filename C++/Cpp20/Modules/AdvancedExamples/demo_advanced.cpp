// Advanced C++20 Modules Demo - Data Processing Example
import data_processor;
import <iostream>;
import <vector>;
import <string>;
import <random>;

int main() {
    std::cout << "=== ADVANCED C++20 MODULES DEMO ===" << std::endl;
    std::cout << "Demonstrating: Concepts, Advanced Templates, Fluent Interface\n" << std::endl;
    
    try {
        // 1. Basic data processor usage
        std::cout << "1. Basic Data Processing:" << std::endl;
        IntProcessor numbers("NumberProcessor", {10, 5, 8, 3, 15, 12, 7, 20});
        numbers.print();
        
        std::cout << "Sum: " << numbers.sum() << std::endl;
        std::cout << "Mean: " << numbers.mean() << std::endl;
        std::cout << "Min: " << numbers.min_value() << std::endl;
        std::cout << "Max: " << numbers.max_value() << std::endl;
        
        // 2. Fluent interface (method chaining)
        std::cout << "\n2. Fluent Interface (Method Chaining):" << std::endl;
        auto sorted_unique = numbers;
        sorted_unique.sort().unique().reverse();
        std::cout << "Original: "; numbers.print();
        std::cout << "Sorted→Unique→Reversed: "; sorted_unique.print();
        
        // 3. Advanced filtering with lambdas
        std::cout << "\n3. Advanced Filtering:" << std::endl;
        auto even_numbers = numbers.filter([](int x) { return x % 2 == 0; });
        auto greater_than_10 = numbers.filter([](int x) { return x > 10; });
        
        std::cout << "Even numbers: ";
        for (int n : even_numbers) std::cout << n << " ";
        std::cout << std::endl;
        
        std::cout << "Numbers > 10: ";
        for (int n : greater_than_10) std::cout << n << " ";
        std::cout << std::endl;
        
        // 4. Transform operations
        std::cout << "\n4. Transform Operations:" << std::endl;
        auto squared = numbers.transform([](int x) { return x * x; });
        auto doubled = numbers.transform([](int x) { return x * 2; });
        
        std::cout << "Original: "; numbers.print();
        std::cout << "Squared: ";
        for (int n : squared) std::cout << n << " ";
        std::cout << std::endl;
        
        std::cout << "Doubled: ";
        for (int n : doubled) std::cout << n << " ";
        std::cout << std::endl;
        
        // 5. Fold (reduce) operations
        std::cout << "\n5. Fold (Reduce) Operations:" << std::endl;
        int product = numbers.fold(1, [](int a, int b) { return a * b; });
        int sum_of_squares = numbers.fold(0, [](int acc, int x) { return acc + x * x; });
        
        std::cout << "Product of all numbers: " << product << std::endl;
        std::cout << "Sum of squares: " << sum_of_squares << std::endl;
        
        // 6. Partitioning
        std::cout << "\n6. Data Partitioning:" << std::endl;
        auto [small, large] = numbers.partition([](int x) { return x < 10; });
        
        std::cout << "Numbers < 10: ";
        for (int n : small) std::cout << n << " ";
        std::cout << std::endl;
        
        std::cout << "Numbers >= 10: ";
        for (int n : large) std::cout << n << " ";
        std::cout << std::endl;
        
        // 7. Grouping by key
        std::cout << "\n7. Group By Operations:" << std::endl;
        auto groups = numbers.group_by([](int x) { return x % 3; }); // Group by remainder when divided by 3
        
        for (const auto& [key, values] : groups) {
            std::cout << "Group (mod 3 = " << key << "): ";
            for (int v : values) std::cout << v << " ";
            std::cout << std::endl;
        }
        
        // 8. Working with different numeric types
        std::cout << "\n8. Different Numeric Types:" << std::endl;
        DoubleProcessor doubles("DoubleProcessor", {3.14, 2.71, 1.41, 1.73, 2.23});
        doubles.print();
        std::cout << "Mean of doubles: " << doubles.mean() << std::endl;
        
        // 9. Factory function usage
        std::cout << "\n9. Factory Functions:" << std::endl;
        auto float_processor = make_processor<float>("FloatFactory", 
                                                   std::initializer_list<float>{1.1f, 2.2f, 3.3f, 4.4f});
        float_processor.print();
        
        // 10. Sequence generation
        std::cout << "\n10. Sequence Generation:" << std::endl;
        auto sequence = generate_sequence(1, 10, 2);
        std::cout << "Generated sequence (1 to 10, step 2): ";
        for (int n : sequence) std::cout << n << " ";
        std::cout << std::endl;
        
        // 11. Advanced algorithms
        std::cout << "\n11. Advanced Algorithms:" << std::endl;
        std::vector<int> data1 = {1, 3, 5, 7, 9};
        std::vector<int> data2 = {2, 4, 6, 8, 10};
        
        std::cout << "Data1 is sorted: " << (is_sorted(data1) ? "Yes" : "No") << std::endl;
        
        auto merged = merge_sorted(data1, data2);
        std::cout << "Merged sorted data: ";
        for (int n : merged) std::cout << n << " ";
        std::cout << std::endl;
        
        // 12. Concept constraints in action
        std::cout << "\n12. Concept Constraints:" << std::endl;
        try {
            // This works because int satisfies Numeric concept
            IntProcessor valid_processor("ValidProcessor", {1, 2, 3});
            valid_processor.print();
            
            // This would cause a compilation error if attempted:
            // DataProcessor<std::string> invalid_processor("Invalid"); // Error: string is not Numeric
            
            std::cout << "✅ Concept constraints working correctly!" << std::endl;
            
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        
        // 13. Template magic with perfect forwarding
        std::cout << "\n13. Template Construction:" << std::endl;
        std::vector<int> source_data = {100, 200, 300, 400, 500};
        DataProcessor<int> from_container("FromContainer", source_data);
        from_container.print();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n=== ADVANCED MODULE FEATURES DEMONSTRATED ===" << std::endl;
    std::cout << "✅ C++20 Concepts for type safety" << std::endl;
    std::cout << "✅ Complex template metaprogramming" << std::endl;
    std::cout << "✅ Perfect forwarding and universal references" << std::endl;
    std::cout << "✅ SFINAE with requires clauses" << std::endl;
    std::cout << "✅ Fluent interfaces and method chaining" << std::endl;
    std::cout << "✅ Lambda expressions and functional programming" << std::endl;
    std::cout << "✅ Auto type deduction and decltype" << std::endl;
    std::cout << "✅ Template specializations and constraints" << std::endl;
    std::cout << "✅ Modern C++ algorithms and ranges" << std::endl;
    std::cout << "✅ All while maintaining clean module interfaces!" << std::endl;
    
    return 0;
}

/*
COMPILE AND RUN:

This example demonstrates advanced C++20 features working seamlessly with modules:

1. **Concepts**: Type safety with Numeric, Comparable, Printable concepts
2. **Complex Templates**: Multi-level template parameters with constraints
3. **Perfect Forwarding**: Factory functions with universal references
4. **SFINAE**: Sophisticated template metaprogramming
5. **Modern Algorithms**: STL algorithms with lambdas and functional style
6. **Fluent Interfaces**: Method chaining for readable code
7. **Template Deduction**: Auto and decltype magic

Windows (MSVC):
    cl /EHsc /std:c++20 /experimental:module data_processor.cppm /c
    cl /EHsc /std:c++20 data_processor.obj demo_advanced.cpp /Fe:advanced_demo.exe
    advanced_demo.exe

Linux/macOS (GCC 11+):
    g++ -std=c++20 -fmodules-ts -fconcepts -c data_processor.cppm
    g++ -std=c++20 -fmodules-ts -fconcepts -o advanced_demo demo_advanced.cpp
    ./advanced_demo

Linux/macOS (Clang 15+):
    clang++ -std=c++20 --precompile data_processor.cppm -o data_processor.pcm
    clang++ -std=c++20 -fprebuilt-module-path=. -o advanced_demo demo_advanced.cpp
    ./advanced_demo
*/
