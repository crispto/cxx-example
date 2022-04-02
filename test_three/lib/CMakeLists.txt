set(LIBHELLO_SRC hello.cpp)
add_library(hello SHARED ${LIBHELLO_SRC})
add_library(hello_static STATIC ${LIBHELLO_SRC})
message(STATUS "cmake source dir " ${CMAKE_SOURCE_DIR}/install)
#设置环境变量
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)
#安装静态库和动态库
install(TARGETS hello hello_static
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
#安装文件
install(FILES hello.h DESTINATION include)
