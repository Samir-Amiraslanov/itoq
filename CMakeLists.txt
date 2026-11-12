cmake_minimum_required(VERSION 3.20)
project(proga)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include(FetchContent)
set(BOOST_INCLUDE_LIBRARIES program_options)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(Boost
        URL https://github.com/boostorg/boost/releases/download/boost-1.86.0/boost-1.86.0-cmake.tar.xz
        DOWNLOAD_EXTRACT_TIMESTAMP ON)
FetchContent_MakeAvailable(Boost)

add_library(geometry SHARED
        src/point.cpp
        src/triangle.cpp
        src/list.cpp
)
target_include_directories(geometry PUBLIC include)

add_executable(proga main.cpp)
target_link_libraries(proga PRIVATE geometry Boost::program_options)

file(COPY input.txt DESTINATION ${CMAKE_BINARY_DIR})

add_executable(test_proga test.cpp)
target_link_libraries(test_proga PRIVATE geometry Boost::program_options)
enable_testing()
add_test(NAME proga_tests COMMAND test_proga)
