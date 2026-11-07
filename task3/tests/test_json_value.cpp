#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include "json.hpp" // Твой файл с JsonValue

void test_simple_types() {
    std::cout << "Running test_simple_types...\n";
    
    JsonValue j_null(nullptr);
    assert(j_null.is_null() == true);
    
    JsonValue j_num(42.5);
    assert(j_num.is_double() == true);
    assert(j_num.getDouble() == 42.5);
    
    JsonValue j_bool(false);
    assert(j_bool.is_bool() == true);
    assert(j_bool.getBool() == false);
    
    JsonValue j_str(std::string("hello world"));
    assert(j_str.is_string() == true);
    assert(j_str.getString() == "hello world");
    
    std::cout << "test_simple_types PASSED\n\n";
}

void test_complex_types() {
    std::cout << "Running test_complex_types...\n";
    
    // 1. Тестируем Массив
    JsonArray arr;
    arr.push_back(JsonValue(10.0));
    arr.push_back(JsonValue(std::string("test")));
    
    // ИСПРАВЛЕНИЕ: используем std::move, чтобы передать владение
    JsonValue j_arr(std::move(arr)); 
    assert(j_arr.is_array() == true);
    assert(j_arr.getJsonArray().size() == 2);
    
    // 2. Тестируем Объект
    JsonObject obj;
    obj["name"] = JsonValue(std::string("Vasya")); // Теперь это работает благодаря дефолтному конструктору
    obj["age"] = JsonValue(25.0);
    
    // ИСПРАВЛЕНИЕ: используем std::move
    JsonValue j_obj(std::move(obj)); 
    assert(j_obj.is_object() == true);
    assert(j_obj.getJsonObject().size() == 2);
    
    std::cout << "test_complex_types PASSED\n\n";
}

void test_equality_operator() {
    std::cout << "Running test_equality_operator...\n";
    
    // 1. Простые типы
    JsonValue a(10.0);
    JsonValue b(10.0);
    JsonValue c(20.0);
    assert(a == b);
    assert(!(a == c));
    
    JsonValue s1(std::string("hello"));
    JsonValue s2(std::string("hello"));
    assert(s1 == s2);
    assert(!(a == s1)); // Разные типы
    
    // 2. Массивы (Самый важный тест! Проверяем, что сравнивается содержимое, а не адреса)
    JsonArray arr1;
    arr1.push_back(JsonValue(1.0));
    arr1.push_back(JsonValue(2.0));
    JsonValue j_arr1(std::move(arr1)); // Забираем владение через std::move
    
    JsonArray arr2;
    arr2.push_back(JsonValue(1.0));
    arr2.push_back(JsonValue(2.0));
    JsonValue j_arr2(std::move(arr2)); // Забираем владение через std::move
    
    assert(j_arr1 == j_arr2); // Должно быть true, содержимое одинаковое!
    
    // Создаем третий, отличающийся массив для проверки неравенства
    JsonArray arr3;
    arr3.push_back(JsonValue(1.0));
    arr3.push_back(JsonValue(2.0));
    arr3.push_back(JsonValue(3.0)); // Лишний элемент
    JsonValue j_arr3(std::move(arr3));
    
    assert(!(j_arr1 == j_arr3)); // Должно быть false, размеры и содержимое разные
    
    // 3. Объекты
    JsonObject obj1;
    obj1["key"] = JsonValue(std::string("value"));
    JsonValue j_obj1(std::move(obj1)); // Забираем владение через std::move
    
    JsonObject obj2;
    obj2["key"] = JsonValue(std::string("value"));
    JsonValue j_obj2(std::move(obj2)); // Забираем владение через std::move
    
    assert(j_obj1 == j_obj2); // Должно быть true
    
    std::cout << "test_equality_operator PASSED\n\n";
}

void test_exceptions() {
    std::cout << "Running test_exceptions...\n";
    
    JsonValue j_str(std::string("hello"));
    
    // Проверяем, что выбрасывается исключение при неправильном геттере
    bool caught = false;
    try {
        j_str.getDouble(); // Ошибка: это строка, а не double
    } catch (const std::runtime_error& e) {
        caught = true;
    }
    assert(caught == true);
    
    std::cout << "test_exceptions PASSED\n\n";
}

int main() {
    std::cout << "=== Starting JsonValue Tests ===\n\n";
    
    test_simple_types();
    test_complex_types();
    test_equality_operator();
    test_exceptions();
    
    std::cout << "================================\n";
    std::cout << "🎉 ALL JSON VALUE TESTS PASSED! 🎉\n";
    std::cout << "================================\n";
    
    return 0;
}