cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

set(Name "lab-13_array")
set(Sources "src/smoke_compile.cpp")
set(Include "include")

project(Name)

add_executable(${Name} ${Sources})
target_include_directories(${Name} PUBLIC ${Include})