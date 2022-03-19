cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

set(Name "lab-08_shared-ptr")
set(Sources "main.cpp", "matrix.cpp", "shared_ptr.cpp")
set(IncludeDirectory "include")

project(${Name})

add_executable(${Name} ${Sources})

target_include_directories(${IncludeDirectory})