cmake_minimum_required(VERSION 3.0.0)
project(ioperations)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(project)

add_executable(${PROJECT_NAME} main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${IOPERATIONS_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${IOPERATIONS_LIBRARIES})

add_subdirectory(tests)