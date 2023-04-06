cmake_minimum_required(VERSION 3.0.0)
project(ioperations_lib)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-fprofile-arcs -ftest-coverage -fPIC -O0)
add_compile_options(-Wall -Werror -Wpedantic)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${SOURCES})

set(IOPERATIONS_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(IOPERATIONS_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
