cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

set(Name "lab-10_cppio")
set(Sources "src/bin_manip.cpp" "src/employees.cpp" "src/main.cpp")
set(IncludeDirectory "include")

project(${Name})

add_executable(${Name} ${Sources})

target_include_directories(${Name} PUBLIC ${IncludeDirectory})