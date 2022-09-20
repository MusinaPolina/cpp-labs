cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

set(Name "lab-06_int-vector")
set(Sources "src/main.cpp" "src/my_vector.cpp")
set(IncludeDirectory "include")

project(${Name})

add_executable(${Name} ${Sources})

target_include_directories(${Name} PUBLIC ${IncludeDirectory})