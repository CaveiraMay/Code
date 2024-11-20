cmake_minimum_required (VERSION 2.8.11)

project (test)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

set(HEADERS ${CMAKE_CURRENT_LIST_DIR}/include/test.h)

set(SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/test.cpp)

add_executable (test ${HEADERS} ${SOURCES})
