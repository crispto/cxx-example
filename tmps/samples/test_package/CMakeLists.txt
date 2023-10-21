cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(conan-exp2 CONFIG REQUIRED)

add_executable(example src/example.cpp)
target_link_libraries(example conan-exp2::conan-exp2)
