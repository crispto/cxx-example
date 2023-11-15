set(EXAMPLE_PREFIX log)

# message(NOTICE "CMAKE_CURRENT_SOURCE_DIR IS ${CMAKE_CURRENT_SOURCE_DIR}")
# message(NOTICE "CMAKE_SOURCE_DIR IS ${CMAKE_SOURCE_DIR}") message(NOTICE
# "CMAKE_INSTALL_INCLUDEDIR IS ${CMAKE_INSTALL_INCLUDEDIR}") message(NOTICE
# "CMAKE_INSTALL_PREFIX IS ${CMAKE_INSTALL_PREFIX}") 打印结果
# CMAKE_CURRENT_SOURCE_DIR IS /home/coding/github/laboratory/examples/log
# CMAKE_SOURCE_DIR IS /home/coding/github/laboratory CMAKE_INSTALL_INCLUDEDIR IS
# include CMAKE_INSTALL_PREFIX IS /home/coding/github/laboratory/install
list(APPEND SRCS main time)

foreach(SRC ${SRCS})
  set(DEMO_NAME ${EXAMPLE_PREFIX}_${SRC})
  add_executable(${DEMO_NAME} ${SRC}.cpp)
  target_link_libraries(${DEMO_NAME} PRIVATE tbox::tbox_base)
  # set_target_properties(${DEMO_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
  # ${CMAKE_BINARY_DIR}/bin)/
endforeach()

# set(name time) add_executable(${EXAMPLE_PREFIX}_${name} ${name}.cpp)
# target_link_libraries(${EXAMPLE_PREFIX}_${name} PRIVATE tbox::tbox_base)
# set_target_properties(${EXAMPLE_PREFIX}_${name} PROPERTIES
# RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
