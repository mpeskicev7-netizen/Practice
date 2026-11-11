#include <iostream>
#include <cassert>
#include <vector>
#include "lexer.hpp"
#include "parser.hpp"

// Вспомогательная функция, чтобы собрать все токены из лексера в вектор
std::vector<Token> getAllTokens(Lexer& lexer) {
    std::vector<Token> tokens;
    while (true) {
        Token t = lexer.nextToken();
        tokens.push_back(t);
        if (t.type == TokenType::End) {
            break;
        }
    }
    return tokens;
}

void test_parse_number() {
    std::cout << "Test: parse number... ";
    std::string json = "42.5";
    Lexer lexer(json);
    Parser parser(getAllTokens(lexer));
    JsonValue result = parser.ParseValue();
    
    assert(result.is_double());
    assert(result.getDouble() == 42.5);
    std::cout << "PASSED\n";
}

void test_parse_string() {
    std::cout << "Test: parse string... ";
    std::string json = "\"hello world\"";
    Lexer lexer(json);
    Parser parser(getAllTokens(lexer));
    JsonValue result = parser.ParseValue();
    
    assert(result.is_string());
    assert(result.getString() == "hello world");
    std::cout << "PASSED\n";
}

void test_parse_boolean() {
    std::cout << "Test: parse boolean... ";
    
    // true
    std::string json1 = "true";
    Lexer lexer1(json1);
    Parser parser1(getAllTokens(lexer1));
    JsonValue result1 = parser1.ParseValue();
    assert(result1.is_bool());
    assert(result1.getBool() == true);
    
    // false
    std::string json2 = "false";
    Lexer lexer2(json2);
    Parser parser2(getAllTokens(lexer2));
    JsonValue result2 = parser2.ParseValue();
    assert(result2.is_bool());
    assert(result2.getBool() == false);
    
    std::cout << "PASSED\n";
}

void test_parse_null() {
    std::cout << "Test: parse null... ";
    std::string json = "null";
    Lexer lexer(json);
    Parser parser(getAllTokens(lexer));
    JsonValue result = parser.ParseValue();
    
    assert(result.is_null());
    std::cout << "PASSED\n";
}

void test_parse_empty_array() {
    std::cout << "Test: parse empty array... ";
    std::string json = "[]";
    Lexer lexer(json);
    Parser parser(getAllTokens(lexer));
    JsonValue result = parser.ParseValue();
    
    assert(result.is_array());
    assert(result.getJsonArray().size() == 0);
    std::cout << "PASSED\n";
}

void test_parse_array() {
    std::cout << "Test: parse array... ";
    std::string json = "[1, 2, 3]";
    Lexer lexer(json);
    Parser parser(getAllTokens(lexer));
    JsonValue result = parser.ParseValue();
    
    assert(result.is_array());
    const auto& arr = result.getJsonArray();
    assert(arr.size() == 3);
    assert(arr[0].getDouble() == 1.0);
    assert(arr[1].getDouble() == 2.0);
    assert(arr[2].getDouble() == 3.0);
    std::cout << "PASSED\n";
}

void test_parse_empty_object() {
    std::cout << "Test: parse empty object... ";
    std::string json = "{}";
    Lexer lexer(json);
    Parser parser(getAllTokens(lexer));
    JsonValue result = parser.ParseValue();
    
    assert(result.is_object());
    assert(result.getJsonObject().size() == 0);
    std::cout << "PASSED\n";
}

void test_parse_object() {
    std::cout << "Test: parse object... ";
    std::string json = "{\"name\": \"John\", \"age\": 30}";
    Lexer lexer(json);
    Parser parser(getAllTokens(lexer));
    JsonValue result = parser.ParseValue();
    
    assert(result.is_object());
    const auto& obj = result.getJsonObject();
    assert(obj.size() == 2);
    assert(obj.at("name").getString() == "John");
    assert(obj.at("age").getDouble() == 30.0);
    std::cout << "PASSED\n";
}

void test_parse_nested() {
    std::cout << "Test: parse nested structure... ";
    std::string json = "{\"users\": [{\"name\": \"Alice\"}, {\"name\": \"Bob\"}]}";
    Lexer lexer(json);
    Parser parser(getAllTokens(lexer));
    JsonValue result = parser.ParseValue();
    
    assert(result.is_object());
    const auto& obj = result.getJsonObject();
    assert(obj.at("users").is_array());
    
    const auto& users = obj.at("users").getJsonArray();
    assert(users.size() == 2);
    assert(users[0].getJsonObject().at("name").getString() == "Alice");
    assert(users[1].getJsonObject().at("name").getString() == "Bob");
    std::cout << "PASSED\n";
}

void test_parse_error_trailing_comma() {
    std::cout << "Test: parse error (trailing comma)... ";
    std::string json = "[1, 2,]";  
    Lexer lexer(json);
    Parser parser(getAllTokens(lexer));
    
    bool exceptionThrown = false;
    try {
        parser.ParseValue();
    } catch (const std::runtime_error& e) {
        exceptionThrown = true;
        // Можно раскомментировать, чтобы увидеть текст ошибки:
        // std::cout << "\n  Caught expected error: " << e.what() << "\n";
    }
    
    assert(exceptionThrown);
    std::cout << "PASSED\n";
}

void run_parser_tests() {
    std::cout << "=== Parser Tests ===\n\n";
    
    test_parse_number();
    test_parse_string();
    test_parse_boolean();
    test_parse_null();
    test_parse_empty_array();
    test_parse_array();
    test_parse_empty_object();
    test_parse_object();
    test_parse_nested();
    test_parse_error_trailing_comma();
    
    std::cout << "\n🎉 ALL PARSER TESTS PASSED! 🎉\n";

}