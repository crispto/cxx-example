cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME andro)
PROJECT(${PROJECT_NAME})
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)

include_directories(${CMAKE_SOURCE_DIR}/rapidjson)

set(CMAKE_CXX_STANDARD 11)

set(SRC andro.cpp)
add_library(${PROJECT_NAME} SHARED ${SRC})

message("install dir ${CMAKE_INSTALL_PREFIX}")
install(TARGETS ${PROJECT_NAME} DESTINATION lib)

add_executable(main main.cpp)
link_directories(install/lib)
target_link_libraries(main PUBLIC andro)