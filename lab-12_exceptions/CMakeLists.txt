cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

set(Name "lab-12_exceptions")
set(Sources "src/main.cpp" "src/matrix.cpp")
set(IncludeDirectory "include")

project(${Name})

add_executable(${Name} ${Sources})

target_include_directories(${Name} PUBLIC ${IncludeDirectory})