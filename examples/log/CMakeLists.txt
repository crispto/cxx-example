set(EXAMPLE_PREFIX log)
add_executable(${EXAMPLE_PREFIX}_main main.cpp)
target_link_libraries(${EXAMPLE_PREFIX}_main PRIVATE tbox::tbox_base)
