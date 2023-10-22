set(EXAMPLE_PREFIX log)

set(name main)
add_executable(${EXAMPLE_PREFIX}_${name} ${name}.cpp)
target_link_libraries(${EXAMPLE_PREFIX}_${name} PRIVATE tbox::tbox_base)
set_target_properties(${EXAMPLE_PREFIX}_${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set(name time)
# add_executable(${EXAMPLE_PREFIX}_${name} ${name}.cpp)
# target_link_libraries(${EXAMPLE_PREFIX}_${name} PRIVATE tbox::tbox_base)
# set_target_properties(${EXAMPLE_PREFIX}_${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

