cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
project(minimal_smoke_test)
add_executable(minimal_smoke_test tests/minimal_smoke_test.cpp)
target_include_directories(minimal_smoke_test PUBLIC include)

project(smoke_test)
add_executable(smoke_test tests/smoke_test.cpp)
target_include_directories(smoke_test PUBLIC include)

