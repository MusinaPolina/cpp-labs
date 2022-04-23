cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

set(Name "hw-02_huffman")
set(Sources "src/huffman.cpp" "src/bin_manip.cpp" "src/main.cpp")
set(IncludeDirectory "include")

project(${Name})

add_executable(${Name} ${Sources})

target_include_directories(${Name} PUBLIC ${IncludeDirectory})