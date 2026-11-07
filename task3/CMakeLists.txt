cmake_minimum_required(VERSION 3.14)
project(json_parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 1. Основная утилита
add_executable(json_parser
    src/main.cpp
    src/json.cpp
    src/lexer.cpp
    src/parser.cpp
    src/path.cpp
)
target_include_directories(json_parser PRIVATE include)

# 2. Тесты для JsonValue (собираем всегда, чтобы проверять базу)
add_executable(test_json_value 
    tests/test_json_value.cpp
    src/json.cpp 
)
target_include_directories(test_json_value PRIVATE include)

# 3. Остальные тесты (собираем только если включена опция BUILD_TESTS)
option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
    enable_testing()
    
    # Тесты для Лексера
    add_executable(test_lexer tests/test_lexer.cpp src/lexer.cpp)
    target_include_directories(test_lexer PRIVATE include)
    add_test(NAME LexerTests COMMAND test_lexer)
    
    # Тесты для Парсера
    add_executable(test_parser tests/test_parser.cpp src/lexer.cpp src/parser.cpp src/json.cpp)
    target_include_directories(test_parser PRIVATE include)
    add_test(NAME ParserTests COMMAND test_parser)
    
    # Тесты для Path Query
    add_executable(test_path tests/test_path.cpp src/lexer.cpp src/parser.cpp src/json.cpp src/path.cpp)
    target_include_directories(test_path PRIVATE include)
    add_test(NAME PathTests COMMAND test_path)
endif()