add_library(geometry SHARED
        point.cpp
        triangle.cpp
        list.cpp
)

target_include_directories(geometry PUBLIC ${CMAKE_SOURCE_DIR}/include)