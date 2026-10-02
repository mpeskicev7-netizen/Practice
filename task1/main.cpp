#include "cow_string.hpp"
#include <iostream>

int main() {
    CowString s("hello world");
    
    std::cout << "String: " << s.c_str() << "\n";
    std::cout << "Size: " << s.size() << "\n";
    
    return 0;
}