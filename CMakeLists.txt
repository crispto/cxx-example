cmake_minimum_required(VERSION 3.20)
project(cxx-lab)
# list(APPEND CMAKE_PREFIX_PATH "/usr/local/lib/cmake")

include(cmake/utils.cmake)
# 设置 modules中头文件安装的目录
set(CMAKE_INSTALL_INCLUDEDIR "include/lab")

find_package(tbox COMPONENTS base util alarm event eventx)
if(NOT tbox_FOUND)
  message(WARNING "PCAKGE NOT FOUND")
endif()

add_subdirectory(modules)
# add_subdirectory(examples)

# build examples 目录
option(BUILD_EXAMPLES "build examples 目录" OFF)
if(BUILD_EXAMPLES)
  # 让examples 能直接引用 modules中的头文件
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/modules)
  file(GLOB subdirectories "${CMAKE_SOURCE_DIR}/examples/*")
  include_directories(${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR})
  message(
    NOTICE
    "include_directories ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
  foreach(item ${subdirectories})
    if(IS_DIRECTORY ${item})
      add_subdirectory(${item})
    endif()
  endforeach()
endif()

if(TEST)
  find_package(GTest REQUIRED)
  # message(STATUS "gtest headfile:" ${GTEST_INCLUDE_DIRS}) message(STATUS
  # "gtest libpath:" ${GTEST_BOTH_LIBRARIES})
  include_directories(${GTEST_INCLUDE_DIRS})
  add_executable(runTests test/main_test.cpp)
  target_link_libraries(runTests ${GTEST_BOTH_LIBRARIES} pthread)
  install(TARGETS runTests)
endif()
