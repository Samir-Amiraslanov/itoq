cmake_minimum_required(VERSION 3.20)
project(proga)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
set(BOOST_INCLUDE_LIBRARIES program_options)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(Boost
        URL https://github.com/boostorg/boost/releases/download/boost-1.86.0/boost-1.86.0-cmake.tar.xz
        DOWNLOAD_EXTRACT_TIMESTAMP ON)
FetchContent_MakeAvailable(Boost)
add_executable(proga
        main.cpp
        include/point.h src/point.cpp
        include/triangle.h src/triangle.cpp
        include/list.h
)
target_link_libraries(proga PRIVATE Boost::program_options)
file(COPY input.txt DESTINATION ${CMAKE_BINARY_DIR})

add_executable(test_proga
        test.cpp
        include/point.h src/point.cpp
        include/triangle.h src/triangle.cpp
        include/list.h
)
target_link_libraries(test_proga PRIVATE Boost::program_options)