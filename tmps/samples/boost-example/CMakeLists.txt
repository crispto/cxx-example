cmake_minimum_required(VERSION 3.1.0)
project(sample)
set(CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED COMPONENTS date_time filesystem iostreams program_options)

# include_directories(${Boost_INCLUDE_DIRS})

message(WARNING "boost include dir is ${Boost_INCLUDE_DIRS}")


add_executable(main base.cpp)

set(BOOST_COMPONENTS
Boost::date_time
Boost::filesystem
Boost::iostreams
Boost::program_options
)

target_link_libraries(main ${BOOST_COMPONENTS})

