cmake_minimum_required(VERSION 3.14)
project(cow_string_project LANGUAGES CXX)

# Стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем заголовки из папки include
include_directories(include)

# Основной исполняемый файл
add_executable(cow_string_demo 
    main.cpp 
    src/cow_string.cpp
)

# Тесты (пока закомментируем, добавим позже)
# enable_testing()
# add_subdirectory(tests)