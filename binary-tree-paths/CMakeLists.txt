cmake_minimum_required(VERSION 3.14)
project(BinaryTreePaths LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Solution library
add_library(solution_lib src/solution.cpp)

# Test executable
add_executable(run_tests tests/test_main.cpp)
target_link_libraries(run_tests PRIVATE solution_lib)