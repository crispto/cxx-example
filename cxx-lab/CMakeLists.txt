cmake_minimum_required(VERSION 3.0)
project(cxx-lab)


set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)
add_subdirectory(src)

if (USE_TEST)
include_directories(${PROJECT_SOURCE_DIR}/src/include)
link_directories(${PROJECT_SOURCE_DIR}/install/lib)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
  quick_sort_test
  test/main_test.cpp
)
target_link_libraries(
  quick_sort_test
  gtest_main labor_static
)

include(GoogleTest)
gtest_discover_tests(quick_sort_test)

install(TARGETS quick_sort_test DESTINATION ${CMAKE_SOURCE_DIR}/test/bin)
endif ()