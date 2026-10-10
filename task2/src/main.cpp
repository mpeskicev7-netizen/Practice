#include <iostream>
#include "small_vector.hpp"

int main() {
    std::cout << "=== Тест 1: Move из inline-режима ===\n";
    {
        SmallVector<int, 4> vec1;
        vec1.push_back(10);
        vec1.push_back(20);
        vec1.push_back(30);
        
        std::cout << "vec1 size: " << vec1.size() << ", capacity: " << vec1.capacity() << "\n";
        std::cout << "vec1[0] = " << vec1[0] << ", vec1[2] = " << vec1[2] << "\n";
        
        // Move конструктор
        SmallVector<int, 4> vec2(std::move(vec1));
        
        std::cout << "\nПосле move:\n";
        std::cout << "vec2 size: " << vec2.size() << ", capacity: " << vec2.capacity() << "\n";
        std::cout << "vec2[0] = " << vec2[0] << ", vec2[2] = " << vec2[2] << "\n";
        
        std::cout << "\nvec1 (источник) size: " << vec1.size() << "\n";
        std::cout << "vec1 должен быть пустым (size = 0)\n";
        
        // vec1 и vec2 выходят из области видимости — деструкторы не должны крашиться!
    }
    std::cout << "✓ Тест 1 пройден (деструкторы не крашнулись)\n\n";

    std::cout << "=== Тест 2: Move из heap-режима ===\n";
    {
        SmallVector<int, 4> vec1;
        vec1.push_back(10);
        vec1.push_back(20);
        vec1.push_back(30);
        vec1.push_back(40);
        vec1.push_back(50);  // Переход в heap
        
        std::cout << "vec1 size: " << vec1.size() << ", capacity: " << vec1.capacity() << "\n";
        std::cout << "vec1[0] = " << vec1[0] << ", vec1[4] = " << vec1[4] << "\n";
        
        // Move конструктор
        SmallVector<int, 4> vec2(std::move(vec1));
        
        std::cout << "\nПосле move:\n";
        std::cout << "vec2 size: " << vec2.size() << ", capacity: " << vec2.capacity() << "\n";
        std::cout << "vec2[0] = " << vec2[0] << ", vec2[4] = " << vec2[4] << "\n";
        
        std::cout << "\nvec1 (источник) size: " << vec1.size() << "\n";
        std::cout << "vec1 должен быть пустым (size = 0)\n";
    }
    std::cout << "✓ Тест 2 пройден (деструкторы не крашнулись)\n\n";

    std::cout << "=== Тест 3: Move assignment (опционально) ===\n";
    {
        SmallVector<int, 4> vec1;
        vec1.push_back(100);
        vec1.push_back(200);
        
        SmallVector<int, 4> vec2;
        vec2.push_back(1);
        vec2.push_back(2);
        vec2.push_back(3);
        
        std::cout << "До move assignment:\n";
        std::cout << "vec1 size: " << vec1.size() << "\n";
        std::cout << "vec2 size: " << vec2.size() << "\n";
        
        // Move assignment (если уже реализовал)
        // vec2 = std::move(vec1);
        
        // std::cout << "\nПосле move assignment:\n";
        // std::cout << "vec2 size: " << vec2.size() << "\n";
        // std::cout << "vec2[0] = " << vec2[0] << "\n";
    }
    std::cout << "✓ Тест 3 (закомментирован — сделаем после move assignment)\n\n";

    std::cout << "=== Все тесты move пройдены! ===\n";
    
    return 0;
}