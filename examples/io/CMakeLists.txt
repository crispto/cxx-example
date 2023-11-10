set(EXAMPLE_PREFIX io)
list(APPEND SRCS main test)
find_package(Threads)
set(CONAN_EIGEN_ROOT
    "/home/SENSETIME/yangchengwei/.conan/data/Eigen/3.4.0/raphael/v2x/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9"
)
set(CONAN_INCLUDE_DIRS_EIGEN
    "/home/SENSETIME/yangchengwei/.conan/data/Eigen/3.4.0/raphael/v2x/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include"
)
include_directories(${CONAN_INCLUDE_DIRS_EIGEN})
find_package(OpenCV REQUIRED)
message(WARNING "OpenCV_INCLUDE_DIRS IS :${OpenCV_INCLUDE_DIRS}")
include_directories(${OpenCV_INCLUDE_DIRS})
set(EXTRA_LIBS)
list(APPEND EXTRA_LIBS ${OpenCV_LIBS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(${EXAMPLE_PREFIX}_main main.cpp)
target_link_libraries(${EXAMPLE_PREFIX}_main PRIVATE tbox::tbox_base
                                                     Threads::Threads)
set_target_properties(${DEMO_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                              ${CMAKE_BINARY_DIR}/bin)

add_executable(${EXAMPLE_PREFIX}_test test.cpp)
target_link_libraries(${EXAMPLE_PREFIX}_test PRIVATE tbox::tbox_base atomic
                                                     pthread)

add_executable(${EXAMPLE_PREFIX}_cv opencv_demo.cpp)
target_link_libraries(${EXAMPLE_PREFIX}_cv PRIVATE ${OpenCV_LIBS})

add_executable(${EXAMPLE_PREFIX}_eigen eigen_demo.cpp)
# target_link_libraries(${EXAMPLE_PREFIX}_eigen PRIVATE ${OpenCV_LIBS})

add_executable(${EXAMPLE_PREFIX}_raphael raphael_demo.cpp)
target_link_libraries(${EXAMPLE_PREFIX}_raphael PRIVATE ${OpenCV_LIBS})
