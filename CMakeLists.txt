cmake_minimum_required(VERSION 3.10)
project(calculator)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_library(calc STATIC src/calculator.cpp)
add_executable(calculator src/main.cpp)

target_link_libraries(calculator calc)
