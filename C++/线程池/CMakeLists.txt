cmake_minimum_required (VERSION 3.12)

project (ThreadPool)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

set(HEADERS 
        ${CMAKE_CURRENT_LIST_DIR}/include/Task.h
        ${CMAKE_CURRENT_LIST_DIR}/include/Thread.h
        ${CMAKE_CURRENT_LIST_DIR}/include/ThreadPool.h
)

set(SOURCES 
        ${CMAKE_CURRENT_LIST_DIR}/src/Task.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Thread.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/ThreadPool.cpp
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

add_executable (ThreadPool ${HEADERS} ${SOURCES})
