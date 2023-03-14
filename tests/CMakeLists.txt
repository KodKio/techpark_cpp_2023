cmake_minimum_required(VERSION 3.14)
project(test_films_top)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "--coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

file(GLOB SOURCES *.cpp)

enable_testing()
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${FILMS_TOP_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${FILMS_TOP_LIBRARIES} GTest::Main)