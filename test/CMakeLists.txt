cmake_minimum_required (VERSION 3.17)

include(GoogleTest)
find_package(GTest CONFIG REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}_test "")
target_link_libraries(${CMAKE_PROJECT_NAME}_test PRIVATE ${CMAKE_PROJECT_NAME}_lib GTest::gtest GTest::gtest_main)

target_sources(${CMAKE_PROJECT_NAME}_test
    PRIVATE
        "solver/options_test.cpp"
        "solver/region_test.cpp"
    )

gtest_discover_tests(${CMAKE_PROJECT_NAME}_test)
