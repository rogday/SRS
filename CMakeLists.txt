cmake_minimum_required (VERSION 3.10)

project (SRS)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(COMMON_SOURCES src/RadixSort.cpp src/Graph.cpp src/Treap.cpp)

set(TARGET_SOURCES src/main.cpp ${COMMON_SOURCES})
set(SORT_SOURCES  src/tests/sorts.cpp ${COMMON_SOURCES})
set(BRIDGES_SOURCES  src/tests/bridges.cpp ${COMMON_SOURCES})
set(TREES_SOURCES  src/tests/trees.cpp ${COMMON_SOURCES})

add_executable(main ${TARGET_SOURCES})
add_executable(sorts ${SORT_SOURCES})
add_executable(bridges ${BRIDGES_SOURCES})
add_executable(trees ${TREES_SOURCES})