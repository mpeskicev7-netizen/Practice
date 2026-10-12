#include <cassert>
#include <cstring>
#include <iostream>
#include "cow_string.hpp"

using namespace std;

void test_constructor() {
    CowString s("hello");
    assert(s.size() == 5);
    assert(strcmp(s.c_str(), "hello") == 0);
    cout << "test_constructor PASSED\n";
}

void test_copy_constructor() {
    CowString s1("hello");
    CowString s2 = s1;
    
    assert(s2.size() == 5);
    assert(strcmp(s2.c_str(), "hello") == 0);

    s1[0] = 'H';
    assert(strcmp(s1.c_str(), "Hello") == 0);
    assert(strcmp(s2.c_str(), "hello") == 0);  
    
    cout << "test_copy_constructor PASSED\n";
}

void test_move_constructor() {
    CowString s1("hello");
    CowString s2 = std::move(s1);
    
    assert(s2.size() == 5);
    assert(strcmp(s2.c_str(), "hello") == 0);

    assert(s1.size() == 0);
    assert(strcmp(s1.c_str(), "") == 0);
    
    cout << "test_move_constructor PASSED\n";
}

void test_copy_assignment() {
    CowString s1("hello");
    CowString s2("world");
    
    s1 = s2;
    
    assert(strcmp(s1.c_str(), "world") == 0);
    assert(strcmp(s2.c_str(), "world") == 0);

    s2[0] = 'W';
    assert(strcmp(s1.c_str(), "world") == 0);  
    assert(strcmp(s2.c_str(), "World") == 0);
    
    cout << "test_copy_assignment PASSED\n";
}

void test_move_assignment() {
    CowString s1("hello");
    CowString s2("world");
    
    s1 = std::move(s2);
    
    assert(strcmp(s1.c_str(), "world") == 0);
    assert(s2.size() == 0); 
    
    cout << "test_move_assignment PASSED\n";
}

void test_const_operator_bracket() {
    CowString s("hello");
    
    assert(s[0] == 'h');
    assert(s[4] == 'o');
    
    cout << "test_const_operator_bracket PASSED\n";
}

void test_non_const_operator_bracket() {
    CowString s("hello");
    
    s[0] = 'H';
    assert(strcmp(s.c_str(), "Hello") == 0);
    
    s[4] = 'O';
    assert(strcmp(s.c_str(), "HellO") == 0);
    
    cout << "test_non_const_operator_bracket PASSED\n";
}

void test_detach_cow_behavior() {
    CowString s1("hello");
    CowString s2 = s1;  

    s1[0] = 'H';
    
    assert(strcmp(s1.c_str(), "Hello") == 0);
    assert(strcmp(s2.c_str(), "hello") == 0);  

    s2[0] = 'X';
    assert(strcmp(s1.c_str(), "Hello") == 0); 
    assert(strcmp(s2.c_str(), "Xello") == 0);
    
    cout << "test_detach_cow_behavior PASSED\n";
}

void test_comparison() {
    CowString s1("hello");
    CowString s2("hello");
    CowString s3("world");
    CowString s4 = s1;  
    
    assert(s1 == s2);
    assert(!(s1 == s3));
    assert(s1 != s3);
    assert(!(s1 != s2));

    assert(s1 == s4);
    
    cout << "test_comparison PASSED\n";
}

void test_plus_assign() {
    CowString s1("hello");
    s1 += " world";
    
    assert(strcmp(s1.c_str(), "hello world") == 0);
    assert(s1.size() == 11);

    CowString s2("hello");
    CowString s3 = s2;
    s2 += " world";
    
    assert(strcmp(s2.c_str(), "hello world") == 0);
    assert(strcmp(s3.c_str(), "hello") == 0);  
    
    cout << "test_plus_assign PASSED\n";
}

void test_plus() {
    CowString s1("hello");
    CowString s2(" world");
    CowString s3 = s1 + s2;
    
    assert(strcmp(s3.c_str(), "hello world") == 0);

    assert(strcmp(s1.c_str(), "hello") == 0);
    assert(strcmp(s2.c_str(), " world") == 0);
    
    cout << "test_plus PASSED\n";
}

void test_output() {
    CowString s("hello");

    cout << "test_output: " << s << "\n";
    
    cout << "test_output PASSED\n";
}

int main() {
    test_constructor();
    test_copy_constructor();
    test_move_constructor();
    test_copy_assignment();
    test_move_assignment();
    test_const_operator_bracket();
    test_non_const_operator_bracket();
    test_detach_cow_behavior();
    test_comparison();
    test_plus_assign();
    test_plus();
    test_output();
    
    cout << "\n=== ALL TESTS PASSED! ===\n";
    return 0;
}