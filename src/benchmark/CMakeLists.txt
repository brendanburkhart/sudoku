cmake_minimum_required (VERSION 3.17)

set(SOURCES
        benchmark.cpp
    )

add_executable(${CMAKE_PROJECT_NAME}_benchmark "")
target_link_libraries(${CMAKE_PROJECT_NAME}_benchmark PRIVATE ${CMAKE_PROJECT_NAME}_lib)

target_compile_features(${CMAKE_PROJECT_NAME}_benchmark PUBLIC cxx_std_17)
set_target_properties(${CMAKE_PROJECT_NAME}_benchmark PROPERTIES CXX_EXTENSIONS OFF)

target_sources(${CMAKE_PROJECT_NAME}_benchmark PRIVATE ${SOURCES})
