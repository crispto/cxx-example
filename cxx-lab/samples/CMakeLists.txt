cmake_minimum_required(VERSION 3.1.0)
set(PROJECT_NAME sample)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
include_directories(../install/include)
link_directories(../install/lib)

file(GLOB SRCS *.cpp)


foreach(SRC ${SRCS})
  get_filename_component(FNAME ${SRC} NAME_WE)
  add_executable(${FNAME} ${SRC})
  target_link_libraries(${FNAME} labor_static)
endforeach()
