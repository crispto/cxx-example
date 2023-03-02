cmake_minimum_required(VERSION 3.1.0)
set(PROJECT_NAME sample)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 11)

file(GLOB SRCS *.cpp)

foreach(SRC ${SRCS})
  get_filename_component(FNAME ${SRC} NAME_WE)
  
  add_executable(${FNAME} ${SRC})

endforeach()