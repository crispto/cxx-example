cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(main main.cpp)

target_link_libraries(main pthread)