cmake_minimum_required (VERSION 3.10)

project (SRS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Ofast -march=native")

set(Boost_INCLUDE_DIR 3rdparty/boost_1_69_0)
set(Boost_LIBRARY_DIR /3rdparty/boost_1_69_0/stage/lib)
#find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories(include)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

set(TARGET_SOURCES src/mainline/main.cpp)
set(TEST_SOURCES  src/tests/RadixSort.cpp)

add_executable(main ${TARGET_SOURCES})
target_link_libraries(main ${Boost_LIBRARIES})
add_executable(tests ${TEST_SOURCES})