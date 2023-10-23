set(EXAMPLE_PREFIX io)
list(APPEND SRCS main)

foreach(SRC ${SRCS})
    set(DEMO_NAME ${EXAMPLE_PREFIX}_${SRC})
    add_executable(${DEMO_NAME} ${SRC}.cpp)
    target_link_libraries(${DEMO_NAME} PRIVATE tbox::tbox_base)
    set_target_properties(${DEMO_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endforeach()
