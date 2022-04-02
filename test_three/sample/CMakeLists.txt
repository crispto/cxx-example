cmake_minimum_required(VERSION 3.0)
set(SOURCE_SRC main.cpp)
project(sample)
# 头文件搜索路径
include_directories(${CMAKE_SOURCE_DIR}/../install/include)
message(STATUS "CMAKE_SOURCE_DIR " ${CMAKE_SOURCE_DIR})
# 库文件搜索路径
link_directories(${CMAKE_SOURCE_DIR}/../install/lib)

add_executable(sample ${SOURCE_SRC})
#链接
# target_link_libraries(sample libhello_static.a)
target_link_libraries(sample hello)