# find openv find_package(OpenCV REQUIRED) if(OpenCV_FOUND) message(STATUS
# "OpenCV found") message(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
# message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}") message(STATUS "OpenCV_VERSION:
# ${OpenCV_VERSION}") else() message(FATAL_ERROR "OpenCV not found") endif()
cmake_minimum_required(VERSION 3.10)
project(tensorrt_demo)
set(CMAKE_CXX_STANDARD 11)
set(demo_name tensorrt_demo)

file(GLOB SRC tensorrt/*.cpp)
add_executable(${demo_name} ${SRC})
target_link_directories(${demo_name} PUBLIC "/usr/local/lib")
target_link_libraries(${demo_name} co)
# set_target_properties( ${demo_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
# ${PROJECT_BINARY_DIR}/bin/tensorrt)
