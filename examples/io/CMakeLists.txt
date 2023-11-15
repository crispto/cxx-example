# set(EXAMPLE_PREFIX io) list(APPEND SRCS main test) find_package(Threads)

# set(CONAN_INCLUDE_DIRS_EIGEN "${CMAKE_SOURCE_DIR}/third-party")
# include_directories(${CONAN_INCLUDE_DIRS_EIGEN}) find_package(OpenCV REQUIRED)
# message(WARNING "OpenCV_INCLUDE_DIRS IS :${OpenCV_INCLUDE_DIRS}")
# include_directories(${OpenCV_INCLUDE_DIRS}) set(EXTRA_LIBS) list(APPEND
# EXTRA_LIBS ${OpenCV_LIBS})

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# add_executable(${EXAMPLE_PREFIX}_main main.cpp)
# target_link_libraries(${EXAMPLE_PREFIX}_main PRIVATE tbox::tbox_base
# Threads::Threads) set_target_properties(${DEMO_NAME} PROPERTIES
# RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# add_executable(${EXAMPLE_PREFIX}_test test.cpp)
# target_link_libraries(${EXAMPLE_PREFIX}_test PRIVATE tbox::tbox_base atomic
# pthread)

# add_executable(${EXAMPLE_PREFIX}_cv opencv_demo.cpp)
# target_link_libraries(${EXAMPLE_PREFIX}_cv PRIVATE ${OpenCV_LIBS})

# add_executable(${EXAMPLE_PREFIX}_eigen eigen_demo.cpp) #
# target_link_libraries(${EXAMPLE_PREFIX}_eigen PRIVATE ${OpenCV_LIBS})

# add_executable(${EXAMPLE_PREFIX}_raphael raphael_demo.cpp)
# target_link_libraries(${EXAMPLE_PREFIX}_raphael PRIVATE ${OpenCV_LIBS})

# include_directories(/usr/local/cuda/include) set(demoname
# ${EXAMPLE_PREFIX}_cuda) add_executable(${demoname} cuda_demo.cpp)
