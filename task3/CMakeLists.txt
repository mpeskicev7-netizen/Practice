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
