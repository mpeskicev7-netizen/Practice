#include "lexer.hpp"
#include <iostream>
#include <cassert>

void test(const std::string& json, const std::string& description) {
    std::cout << "=== " << description << " ===\n";
    std::cout << "Input: " << json << "\n";
    
    try {
        Lexer lexer(json);
        
        while (true) {
            Token t = lexer.nextToken();
            std::cout << "  Type: " << static_cast<int>(t.type) 
                      << ", Line: " << t.line 
                      << ", Pos: " << t.position;
            
            if (t.type == TokenType::Number) {
                std::cout << ", Value: " << std::get<double>(t.value);
            } else if (t.type == TokenType::String) {
                std::cout << ", Value: \"" << std::get<std::string>(t.value) << "\"";
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
   // ===== СТРУКТУРНЫЕ СИМВОЛЫ =====
    test("{", "Открывающая скобка объекта");
    test("}", "Закрывающая скобка объекта");
    test("[", "Открывающая скобка массива");
    test("]", "Закрывающая скобка массива");
    test(",", "Запятая");
    test(":", "Двоеточие");
    test("{ } [ ] , :", "Все структурные символы");
    
    // ===== ЧИСЛА =====
    test("42", "Простое целое");
    test("-42", "Отрицательное целое");
    test("0", "Ноль");
    test("3.14", "Дробное");
    test("-0.5", "Отрицательное дробное");
    test("1e10", "Экспонента");
    test("1.5e-3", "Дробное с отрицательной экспонентой");
    test("2E+5", "Заглавная E с плюсом");
    test("01", "Ошибка: leading zero");
    test("-01", "Ошибка: leading zero после минуса");
    test("1.", "Ошибка: точка без цифр");
    test("1e", "Ошибка: экспонента без цифр");
    
    // ===== СТРОКИ =====
    test("\"hello\"", "Простая строка");
    test("\"\"", "Пустая строка");
    test("\"hello world\"", "Строка с пробелом");
    test("\"hello \\\"world\\\"\"", "Строка с экранированными кавычками");
    test("\"line1\\nline2\"", "Строка с переносом строки");
    test("\"tab\\there\"", "Строка с табуляцией");
    test("\"backslash\\\\\"", "Строка с обратным слэшем");
    test("\"slash\\/\"", "Строка со слэшем");
    test("\"unterminated", "Ошибка: незакрытая строка");
    test("\"bad escape\\x\"", "Ошибка: неизвестное экранирование");
    
    // ===== КОМБИНИРОВАННЫЕ =====
    test("[1, 2, 3]", "Массив чисел");
    test("{\"name\": \"Vasya\"}", "Объект с ключом-строкой и значением-строкой");
    test("{\"age\": 25}", "Объект с ключом-строкой и значением-числом");
    test("[\"a\", \"b\", \"c\"]", "Массив строк");
    test("{ \"x\": [1, 2], \"y\": [3, 4] }", "Вложенные структуры");
    
    // ===== МНОГОСТРОЧНЫЕ =====
    test("{\n  \"name\": \"Vasya\",\n  \"age\": 25\n}", "Многострочный объект");

    // Ключевые слова
    test("true", "Ключевое слово true");
    test("false", "Ключевое слово false");
    test("null", "Ключевое слово null");

    // Ошибки
    test("trueeee", "Ошибка: true с лишними буквами");
    test("true123", "Ошибка: true с цифрами");
    test("tre", "Ошибка: опечатка");
    test("TRUE", "Ошибка: заглавные буквы");

    // Комбинированные
    test("[true, false, null]", "Массив с ключевыми словами");
    test("{\"active\": true, \"deleted\": false, \"data\": null}", "Объект с ключевыми словами");
    test("\u34f6", "проверка");
    
    return 0;
}

/*#include <iostream>
#include <string>
#include "lexer.hpp" // или как у тебя называется файл лексера

int main() {
    // То есть мы скармливаем лексеру ровно: "\u0041"
    std::string input = "\"\\u0041\""; 
    
    Lexer lexer(input);
    Token t = lexer.nextToken();

    // Достаем строку из варианта (твой TokenValue хранит string или double)
    if (std::holds_alternative<std::string>(t.value)) {
        std::string result = std::get<std::string>(t.value);
        std::cout << "Длина строки: " << result.length() << "\n";
        std::cout << "Содержимое: [" << result << "]\n";
    }

    return 0;
}*/