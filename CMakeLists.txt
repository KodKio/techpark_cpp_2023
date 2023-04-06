cmake_minimum_required(VERSION 3.0.0)
project(ioperations)

set(CMAKE_CXX_STANDARD 20)
add_link_options(-coverage -lgcov)

enable_testing()
add_subdirectory(project)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${IOPERATIONS_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${IOPERATIONS_LIBRARIES})

add_subdirectory(tests)
