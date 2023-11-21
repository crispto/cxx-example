sub_dir_list(demo_dir ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "demo_dir: ${demo_dir}")
foreach(subdir ${demo_dir})
  if(${subdir} MATCHES "^libtorch")
    continue()
  endif()
  message(STATUS "subdir: ${subdir}")
  set(subdir ${CMAKE_CURRENT_SOURCE_DIR}/${subdir}) # 必须使用绝对路径
  # exclude kestrel
  if(EXISTS ${subdir}/CMakeLists.txt)
    message(STATUS "add_subdirectory: ${subdir}")
    add_subdirectory(${subdir})
  endif()
endforeach()
