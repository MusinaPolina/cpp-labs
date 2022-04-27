cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

set(Name "tests_run")
set(Sources "../src/reader.cpp" "../src/writer.cpp")
set(Tests "doctest.h" "test.cpp" "test_data_processing.cpp")
set(IncludeDirectory "../include")

project(${Name})

add_executable(${Name} ${Sources} ${Tests})
target_include_directories(${Name} PUBLIC ${IncludeDirectory})