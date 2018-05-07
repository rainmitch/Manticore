
cmake_minimum_required (VERSION 2.6)

project (manticore)
project (libmanticore)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include_directories(src/headers/manticore)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++14 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3") # add debugging data

file(GLOB SRC
    "src/*.cpp"
)

add_subdirectory (src/core)
add_subdirectory (src/IR)
add_subdirectory (src/parser)

list(REMOVE_ITEM SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_library (libmanticore SHARED ${SRC})
add_executable (manticore ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

target_link_libraries (libmanticore parser core IR)
target_link_libraries (manticore libmanticore)

SET_TARGET_PROPERTIES (libmanticore PROPERTIES PREFIX "")
