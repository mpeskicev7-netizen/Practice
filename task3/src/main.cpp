#include <iostream>
#include <functional>

#include "../tests/test_json_value.cpp"
#include "../tests/test_lexer.cpp"
#include "../tests/test_parser.cpp"
#include "../tests/test_path.cpp"

int main() {
    std::cout << "╔════════════════════════════════════════╗\n";
    std::cout << "║       RUNNING ALL TESTS                ║\n";
    std::cout << "╚════════════════════════════════════════╝\n\n";

    try {
        run_json_value_tests();
        std::cout << "\n";
        
        run_lexer_tests();
        std::cout << "\n";
        
        run_parser_tests();
        std::cout << "\n";
        
        run_path_tests();
        
        std::cout << "\n╔════════════════════════════════════════╗\n";
        std::cout << "║   ✅ ALL TESTS PASSED SUCCESSFULLY!    ║\n";
        std::cout << "╚════════════════════════════════════════╝\n";
        
    } catch (const std::exception& e) {
        std::cerr << "\n❌ TEST FAILED WITH ERROR: " << e.what() << "\n";
        return 1;
    }

    return 0;
}