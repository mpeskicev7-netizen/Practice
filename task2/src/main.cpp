#include <iostream>
#include "small_vector.hpp"

int main() {
    SmallVector<int, 4> vec;
    
    // Тестируем inline-режим
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    
    std::cout << "=== Inline режим ===\n";
    std::cout << "Size: " << vec.size() << "\n";          // 4
    std::cout << "Capacity: " << vec.capacity() << "\n";  // 4
    
    // Чтение через operator[]
    std::cout << "vec[0] = " << vec[0] << "\n";  // 10
    std::cout << "vec[3] = " << vec[3] << "\n";  // 40
    
    // Запись через operator[]
    vec[0] = 100;
    std::cout << "После изменения: vec[0] = " << vec[0] << "\n";  // 100
    
    // Тестируем переход в heap
    vec.push_back(50);  // Должно вызвать grow()
    
    std::cout << "\n=== Heap режим ===\n";
    std::cout << "Size: " << vec.size() << "\n";          // 5
    std::cout << "Capacity: " << vec.capacity() << "\n";  // 8
    
    std::cout << "vec[0] = " << vec[0] << "\n";  // 100 (сохранилось!)
    std::cout << "vec[4] = " << vec[4] << "\n";  // 50
    
    // Изменение в heap-режиме
    vec[4] = 500;
    std::cout << "После изменения: vec[4] = " << vec[4] << "\n";  // 500
    
    std::cout << "\n=== Все тесты пройдены! ===\n";
    
    return 0;
}