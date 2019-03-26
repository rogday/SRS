cmake_minimum_required (VERSION 3.10)

project (SRS)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(TREE_SOURCES src/SplayTree.cpp)

set(SORT_SOURCES src/RadixSort.cpp)
set(GRAPH_SOURCES src/Graph.cpp ${SORT_SOURCES})
set(TARGET_SOURCES src/main.cpp ${GRAPH_SOURCES})

set(SORT_TEST_SOURCES  src/tests/sorts.cpp ${SORT_SOURCES})
set(BRIDGES_SOURCES  src/tests/bridges.cpp ${GRAPH_SOURCES})
set(TREES_TEST_SOURCES  src/tests/trees.cpp ${TREE_SOURCES})

add_executable(main ${TARGET_SOURCES})
add_executable(sorts ${SORT_TEST_SOURCES})
add_executable(bridges ${BRIDGES_SOURCES})
add_executable(trees ${TREES_TEST_SOURCES})