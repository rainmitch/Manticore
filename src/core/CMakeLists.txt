
cmake_minimum_required (VERSION 2.6)

project (core)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include_directories(src/headers/manticore)

file(GLOB SRC
    "*.cpp"
)

add_library (core SHARED ${SRC})

target_link_libraries (core)
