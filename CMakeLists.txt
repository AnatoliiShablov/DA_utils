cmake_minimum_required(VERSION 3.5)

project(DA LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(DA_utils include/format.hpp src/format.cpp)
target_include_directories(DA_utils PUBLIC include)

add_executable(DA_tests main.cpp)
target_link_libraries(DA_tests DA_utils)
