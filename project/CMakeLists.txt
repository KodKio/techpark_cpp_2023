cmake_minimum_required(VERSION 3.0.0)
project(films_top_lib)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0 -Wall -Werror -Wpedantic")

file(GLOB SOURCES ./src/*.cpp)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${SOURCES})

set(FILMS_TOP_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(FILMS_TOP_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

