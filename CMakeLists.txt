cmake_minimum_required (VERSION 3.10)

project (SRS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Ofast -march=native")

include_directories(include)

set(COMMON_SOURCES src/RadixSort.cpp src/Graph.cpp)
set(TARGET_SOURCES src/main.cpp ${COMMON_SOURCES})
#set(TEST_SOURCES  src/tests/RadixSort.cpp ${COMMON_SOURCES})

add_executable(main ${TARGET_SOURCES})
#add_executable(tests ${TEST_SOURCES})