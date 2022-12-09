cmake_minimum_required(VERSION 3.20)
project(cxx-lab)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)
add_subdirectory(src)

include_directories(${PROJECT_SOURCE_DIR}/src/include)
link_directories(${PROJECT_SOURCE_DIR}/install/lib)

if(TEST)
  find_package(GTest REQUIRED)
  # message(STATUS "gtest headfile:" ${GTEST_INCLUDE_DIRS})
  # message(STATUS "gtest libpath:" ${GTEST_BOTH_LIBRARIES})
  include_directories(${GTEST_INCLUDE_DIRS})
  add_executable(runTests test/main_test.cpp)
  target_link_libraries(runTests ${GTEST_BOTH_LIBRARIES} pthread)
  install(TARGETS runTests)
endif()