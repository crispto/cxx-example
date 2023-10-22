cmake_minimum_required(VERSION 3.20)
project(cxx-lab)
# In your CMakeLists.txt
# list(APPEND CMAKE_PREFIX_PATH "/usr/local/lib/cmake")
include(cmake/utils.cmake)

set(CMAKE_INSTALL_INCLUDEDIR "include") # 设置头文件安装的目录



find_package(tbox COMPONENTS base util alarm event eventx)
if(NOT tbox_FOUND)
    message(WARNING "PCAKGE NOT FOUND")
endif()

add_subdirectory(modules)
add_subdirectory(examples)


if(TEST)
  find_package(GTest REQUIRED)
  # message(STATUS "gtest headfile:" ${GTEST_INCLUDE_DIRS}) message(STATUS
  # "gtest libpath:" ${GTEST_BOTH_LIBRARIES})
  include_directories(${GTEST_INCLUDE_DIRS})
  add_executable(runTests test/main_test.cpp)
  target_link_libraries(runTests ${GTEST_BOTH_LIBRARIES} pthread)
  install(TARGETS runTests)
endif()
