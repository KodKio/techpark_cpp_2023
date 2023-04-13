cmake_minimum_required(VERSION 3.14)
project(test_ioperations)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-coverage)
add_link_options(-coverage -lgcov)

file(GLOB SOURCES *.cpp)

enable_testing()
find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${IOPERATIONS_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${IOPERATIONS_LIBRARIES} GTest::gtest_main)

add_test(test_io test_ioperations)
