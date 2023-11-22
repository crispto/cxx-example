# find_package(OpenCV REQUIRED)
# ~~~
# if(OpenCV_FOUND)
#   message(STATUS "OpenCV found")
#   message(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
#   message(STATUS "OpenCV_LIBS:
# ${OpenCV_LIBS}")
#   message(STATUS "OpenCV_VERSION: ${OpenCV_VERSION}")
# else()
#   message(FATAL_ERROR "OpenCV not found")
# endif()
# ~~~
cmake_minimum_required(VERSION 3.10)
project(tensorrt_demo)
set(CMAKE_CXX_STANDARD 11)
set(demo_name onnx_mnist)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/common)

set(CUDART_LIB cudart)
set(CUDNN_LIB cudnn)
set(CUBLAS_LIB cublas)
set(NVINFER_LIB nvinfer)
set(NVPARSERS_LIB nvparsers)
set(NVINFER_PLUGIN_LIB nvinfer_plugin)
set(NVONNXPARSERS_LIB nvonnxparser)

file(GLOB COMMON_SRC common/*.cpp)
set(SRC sampleOnnxMNIST.cpp)
link_directories("/usr/local/lib" "/usr/local/cuda/lib64"
                 "/usr/local/tensorrt/lib")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()
set(NV_LIBS
    ${NVINFER_LIB}
    ${NVPARSERS_LIB}
    ${NVINFER_PLUGIN_LIB}
    ${NVONNXPARSERS_LIB}
    ${CUDART_LIB}
    ${CUDNN_LIB}
    ${CUBLAS_LIB})
set(EXTRA_LIBS rt dl pthread)
add_executable(${demo_name} ${SRC} ${COMMON_SRC})
target_link_libraries(${demo_name} co ${NV_LIBS} ${EXTRA_LIBS})

# set_target_properties( ${demo_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
# ${PROJECT_BINARY_DIR}/bin/tensorrt)
