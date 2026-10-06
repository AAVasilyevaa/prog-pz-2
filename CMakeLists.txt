cmake_minimum_required(VERSION 3.10)

project(cpp_prac_dynamic_array LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(dynamic_array_demo src/DynamicArray.cpp src/main.cpp)
target_include_directories(dynamic_array_demo PRIVATE include)

if (MSVC)
    target_compile_options(dynamic_array_demo PRIVATE /W4)
else()
    target_compile_options(dynamic_array_demo PRIVATE -Wall -Wextra -pedantic)
endif()
