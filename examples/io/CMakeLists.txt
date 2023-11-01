set(EXAMPLE_PREFIX io)
list(APPEND SRCS main test)
find_package(Threads)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(${EXAMPLE_PREFIX}_main main.cpp)
target_link_libraries(${EXAMPLE_PREFIX}_main PRIVATE tbox::tbox_base
                                                     Threads::Threads)
set_target_properties(${DEMO_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                              ${CMAKE_BINARY_DIR}/bin)

add_executable(${EXAMPLE_PREFIX}_test test.cpp)
target_link_libraries(${EXAMPLE_PREFIX}_test PRIVATE tbox::tbox_base atomic
                                                     pthread)
