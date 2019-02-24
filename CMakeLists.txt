cmake_minimum_required (VERSION 3.13)

project (SRS)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Ofast -march=native")

include_directories(include)

set(TARGET_SOURCES src/mainline/main.cpp)
set(TEST_SOURCES  src/tests/RadixSort.cpp)

add_executable(main ${TARGET_SOURCES})
add_executable(tests ${TEST_SOURCES})