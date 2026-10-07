cmake_minimum_required(VERSION 3.10)
project(SmallVectorTask)

# Устанавливаем стандарт C++17 (или 20, если хочешь использовать более новые фичи)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем флаги для предупреждений (помогает писать чистый код)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ВАЖНО: Так как реализация шаблона находится в .hpp, 
# нам нужно скомпилировать только main.cpp.
# Компилятор сам подставит код из .hpp при обработке main.cpp.
add_executable(small_vector_demo src/main.cpp)

# Указываем, где искать заголовочные файлы (чтобы работало #include "small_vector.hpp")
target_include_directories(small_vector_demo PRIVATE include)