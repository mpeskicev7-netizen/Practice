#include <iostream>
#include <string>
#include <cassert>
#include "small_vector.hpp"

void test_int_basic() {
    std::cout << "=== Тест 1: int — базовые операции ===\n";
    SmallVector<int, 4> vec;
    
    assert(vec.size() == 0);
    assert(vec.capacity() == 4);
    assert(vec.empty() == true);
    
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    
    assert(vec.size() == 3);
    assert(vec.empty() == false);
    assert(vec[0] == 10);
    assert(vec[1] == 20);
    assert(vec[2] == 30);
    
    vec[1] = 200;
    assert(vec[1] == 200);
    
    std::cout << "✓ Базовые операции работают\n\n";
}

void test_int_heap_transition() {
    std::cout << "=== Тест 2: int — переход в heap ===\n";
    SmallVector<int, 4> vec;
    
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    assert(vec.capacity() == 4);
    
    vec.push_back(5);  
    assert(vec.capacity() == 8);
    assert(vec.size() == 5);

    assert(vec[0] == 1);
    assert(vec[1] == 2);
    assert(vec[2] == 3);
    assert(vec[3] == 4);
    assert(vec[4] == 5);
    
    vec[0] = 100;
    assert(vec[0] == 100);
    
    std::cout << "✓ Переход в heap работает\n\n";
}

void test_int_move_inline() {
    std::cout << "=== Тест 3: int — move из inline ===\n";
    SmallVector<int, 4> vec1;
    vec1.push_back(10);
    vec1.push_back(20);
    vec1.push_back(30);
    
    SmallVector<int, 4> vec2(std::move(vec1));
    
    assert(vec2.size() == 3);
    assert(vec2[0] == 10);
    assert(vec2[1] == 20);
    assert(vec2[2] == 30);
    
    assert(vec1.size() == 0);
    
    std::cout << "✓ Move из inline работает\n\n";
}

void test_int_move_heap() {
    std::cout << "=== Тест 4: int — move из heap ===\n";
    SmallVector<int, 4> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);
    vec1.push_back(4);
    vec1.push_back(5);
    
    SmallVector<int, 4> vec2(std::move(vec1));
    
    assert(vec2.size() == 5);
    assert(vec2[0] == 1);
    assert(vec2[4] == 5);
    
    assert(vec1.size() == 0);
    
    std::cout << "✓ Move из heap работает\n\n";
}

void test_string_basic() {
    std::cout << "=== Тест 5: std::string — базовые операции ===\n";
    SmallVector<std::string, 4> vec;
    
    vec.push_back("hello");
    vec.push_back("world");
    vec.push_back("test");
    
    assert(vec.size() == 3);
    assert(vec[0] == "hello");
    assert(vec[1] == "world");
    assert(vec[2] == "test");
    
    vec[0] = "modified";
    assert(vec[0] == "modified");
    
    std::cout << "✓ Базовые операции со строками работают\n\n";
}

void test_string_heap_transition() {
    std::cout << "=== Тест 6: std::string — переход в heap ===\n";
    SmallVector<std::string, 4> vec;
    
    vec.push_back("one");
    vec.push_back("two");
    vec.push_back("three");
    vec.push_back("four");
    vec.push_back("five");  
    
    assert(vec.size() == 5);
    assert(vec[0] == "one");
    assert(vec[4] == "five");
    
    vec[4] = "FIVE";
    assert(vec[4] == "FIVE");
    
    std::cout << "✓ Переход в heap со строками работает\n\n";
}

void test_string_move_inline() {
    std::cout << "=== Тест 7: std::string — move из inline ===\n";
    SmallVector<std::string, 4> vec1;
    vec1.push_back("alpha");
    vec1.push_back("beta");
    vec1.push_back("gamma");
    
    SmallVector<std::string, 4> vec2(std::move(vec1));
    
    assert(vec2.size() == 3);
    assert(vec2[0] == "alpha");
    assert(vec2[1] == "beta");
    assert(vec2[2] == "gamma");
    
    assert(vec1.size() == 0);
    
    std::cout << "✓ Move из inline со строками работает\n\n";
}

void test_string_move_heap() {
    std::cout << "=== Тест 8: std::string — move из heap ===\n";
    SmallVector<std::string, 4> vec1;
    vec1.push_back("one");
    vec1.push_back("two");
    vec1.push_back("three");
    vec1.push_back("four");
    vec1.push_back("five");
    
    SmallVector<std::string, 4> vec2(std::move(vec1));
    
    assert(vec2.size() == 5);
    assert(vec2[0] == "one");
    assert(vec2[4] == "five");
    
    assert(vec1.size() == 0);
    
    std::cout << "✓ Move из heap со строками работает\n\n";
}

void test_string_destructors() {
    std::cout << "=== Тест 9: std::string — проверка деструкторов ===\n";
    {
        SmallVector<std::string, 4> vec;
        vec.push_back("test1");
        vec.push_back("test2");
        vec.push_back("test3");
        vec.push_back("test4");
        vec.push_back("test5");  
    }
    std::cout << "✓ Деструкторы работают корректно\n\n";
}

void test_copy_assign_int_inline_to_inline() {
    std::cout << "=== Тест 10: int — copy assignment inline → inline ===\n";
    
    SmallVector<int, 4> vec1;
    vec1.push_back(10);
    vec1.push_back(20);
    
    SmallVector<int, 4> vec2;
    vec2.push_back(100);
    vec2.push_back(200);
    
    vec2 = vec1;

    assert(vec2.size() == 2);
    assert(vec2[0] == 10);
    assert(vec2[1] == 20);

    assert(vec1.size() == 2);
    assert(vec1[0] == 10);
    assert(vec1[1] == 20);

    vec2[0] = 999;
    assert(vec1[0] == 10);  
    
    std::cout << "✓ Copy assignment inline → inline работает\n\n";
}

void test_copy_assign_int_heap_to_heap() {
    std::cout << "=== Тест 11: int — copy assignment heap → heap ===\n";
    
    SmallVector<int, 4> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);
    vec1.push_back(4);
    vec1.push_back(5);  
    
    SmallVector<int, 4> vec2;
    vec2.push_back(100);
    vec2.push_back(200);
    vec2.push_back(300);
    vec2.push_back(400);
    vec2.push_back(500);  
    
    vec2 = vec1;
    
    assert(vec2.size() == 5);
    assert(vec2[0] == 1);
    assert(vec2[4] == 5);

    vec2[0] = 999;
    assert(vec1[0] == 1);
    
    std::cout << "✓ Copy assignment heap → heap работает\n\n";
}

void test_copy_assign_int_heap_to_inline() {
    std::cout << "=== Тест 12: int — copy assignment heap → inline ===\n";
    
    SmallVector<int, 4> vec1;
    vec1.push_back(10);
    vec1.push_back(20);
    vec1.push_back(30);
    vec1.push_back(40);
    vec1.push_back(50);  
    
    SmallVector<int, 4> vec2;
    vec2.push_back(100); 
    
    vec2 = vec1; 
    
    assert(vec2.size() == 5);
    assert(vec2[0] == 10);
    assert(vec2[4] == 50);

    assert(vec1.size() == 5);
    assert(vec1[0] == 10);
    
    std::cout << "✓ Copy assignment heap → inline работает\n\n";
}

void test_copy_assign_int_inline_to_heap() {
    std::cout << "=== Тест 13: int — copy assignment inline → heap ===\n";
    
    SmallVector<int, 4> vec1;
    vec1.push_back(10);
    vec1.push_back(20);  
    
    SmallVector<int, 4> vec2;
    vec2.push_back(100);
    vec2.push_back(200);
    vec2.push_back(300);
    vec2.push_back(400);
    vec2.push_back(500);  
    
    vec2 = vec1;  
    
    assert(vec2.size() == 2);
    assert(vec2[0] == 10);
    assert(vec2[1] == 20);

    assert(vec1.size() == 2);
    
    std::cout << "✓ Copy assignment inline → heap работает\n\n";
}

void test_copy_assign_self() {
    std::cout << "=== Тест 14: int — self assignment ===\n";
    
    SmallVector<int, 4> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    
    vec = vec;  
    
    assert(vec.size() == 3);
    assert(vec[0] == 10);
    assert(vec[1] == 20);
    assert(vec[2] == 30);
    
    std::cout << "✓ Self assignment работает\n\n";
}

void test_copy_assign_string_basic() {
    std::cout << "=== Тест 15: std::string — copy assignment ===\n";
    
    SmallVector<std::string, 4> vec1;
    vec1.push_back("hello");
    vec1.push_back("world");
    vec1.push_back("test");
    
    SmallVector<std::string, 4> vec2;
    vec2.push_back("old");
    vec2.push_back("data");
    
    vec2 = vec1;
    
    assert(vec2.size() == 3);
    assert(vec2[0] == "hello");
    assert(vec2[1] == "world");
    assert(vec2[2] == "test");

    assert(vec1.size() == 3);
    assert(vec1[0] == "hello");

    vec2[0] = "modified";
    assert(vec1[0] == "hello");
    
    std::cout << "✓ Copy assignment со строками работает\n\n";
}

void test_copy_assign_string_heap() {
    std::cout << "=== Тест 16: std::string — copy assignment heap → heap ===\n";
    
    SmallVector<std::string, 4> vec1;
    vec1.push_back("one");
    vec1.push_back("two");
    vec1.push_back("three");
    vec1.push_back("four");
    vec1.push_back("five"); 
    
    SmallVector<std::string, 4> vec2;
    vec2.push_back("old1");
    vec2.push_back("old2");
    vec2.push_back("old3");
    vec2.push_back("old4");
    vec2.push_back("old5"); 
    
    vec2 = vec1;
    
    assert(vec2.size() == 5);
    assert(vec2[0] == "one");
    assert(vec2[4] == "five");

    assert(vec1[0] == "one");
    
    std::cout << "✓ Copy assignment heap → heap со строками работает\n\n";
}

void test_copy_assign_destructors() {
    std::cout << "=== Тест 17: std::string — проверка деструкторов после copy assignment ===\n";
    {
        SmallVector<std::string, 4> vec1;
        vec1.push_back("test1");
        vec1.push_back("test2");
        vec1.push_back("test3");
        vec1.push_back("test4");
        vec1.push_back("test5");  
        
        SmallVector<std::string, 4> vec2;
        vec2.push_back("old1");
        vec2.push_back("old2");
        vec2.push_back("old3");
        vec2.push_back("old4");
        vec2.push_back("old5");
        vec2.push_back("old6");  
        
        vec2 = vec1;  
    }
    std::cout << "✓ Деструкторы после copy assignment работают корректно\n\n";
}

int main() {
    std::cout << "🚀 Начинаем тестирование SmallVector\n\n";

    test_int_basic();
    test_int_heap_transition();
    test_int_move_inline();
    test_int_move_heap();
    
    test_string_basic();
    test_string_heap_transition();
    test_string_move_inline();
    test_string_move_heap();
    test_string_destructors();

    test_copy_assign_int_inline_to_inline();
    test_copy_assign_int_heap_to_heap();
    test_copy_assign_int_heap_to_inline();
    test_copy_assign_int_inline_to_heap();
    test_copy_assign_self();
    test_copy_assign_string_basic();
    test_copy_assign_string_heap();
    test_copy_assign_destructors();
    
    std::cout << "🎉 ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО! 🎉\n";
    
    return 0;
}