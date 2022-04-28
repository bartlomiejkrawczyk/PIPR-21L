cmake_minimum_required(VERSION 3.10.0)
project(PROI VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CXX_CLANG_TIDY clang-tidy)

add_compile_options(-Wall -Wextra -Werror -pedantic)

include_directories(lib)

enable_testing()

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(tests)