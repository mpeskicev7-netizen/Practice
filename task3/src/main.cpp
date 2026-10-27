#include "lexer.hpp"
#include <iostream>

void test(const std::string& json) {
    std::cout << "Тестируем: " << json << "\n";
    
    try {
        Lexer lexer(json);
        
        while (true) {
            Token t = lexer.nextToken();
            std::cout << "  Type: " << static_cast<int>(t.type) 
                      << ", Line: " << t.line 
                      << ", Pos: " << t.position;
            
            if (t.type == TokenType::Number) {
                std::cout << ", Value: " << std::get<double>(t.value);
            }
            
            std::cout << "\n";
            
            if (t.type == TokenType::End) break;
        }
    } catch (const std::exception& e) {
        std::cout << "  ОШИБКА: " << e.what() << "\n";
    }
    
    std::cout << "\n";
}

int main() {
    test("42");
    test("-42");
    test("3.14");
    test("1e10");
    test("01");  // Должна быть ошибка
    test("[ 1, 2, 3 ]");
    
    return 0;
}