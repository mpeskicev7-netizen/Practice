#include "cow_string.hpp"
#include <iostream>

int main() {
    CowString s1("hello");
    CowString s2 = s1;  // ref_count = 2

    s1[0] = 'P';  // Должен сработать detach

    std::cout << s1.c_str() << "\n";  // "Hello"
    std::cout << s2.c_str() << "\n";  // "hello" (не изменился!)
}