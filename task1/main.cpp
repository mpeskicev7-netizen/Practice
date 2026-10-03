#include "cow_string.hpp"
#include <iostream>

int main() {
    CowString s1("hello");
    std::cout << "s1: " << s1.c_str() << ", size: " << s1.size() << "\n";
    
    // Вызываем твой новый copy-конструктор
    CowString s2 = s1; 
    
    std::cout << "s2: " << s2.c_str() << ", size: " << s2.size() << "\n";
    
    // Если у тебя есть метод ref_count() для тестов, выведи его:
    // std::cout << "s1 ref_count: " << s1.ref_count() << "\n"; // Должно быть 2
    // std::cout << "s2 ref_count: " << s2.ref_count() << "\n"; // Должно быть 2

    return 0;
}