cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(A8)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(A8 src/main.cpp)

add_executable(
    my_test 
    tests/test_linked_list.cpp
)

enable_testing()
add_test(NAME my_test COMMAND my_test)