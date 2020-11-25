cmake_minimum_required (VERSION 3.17)

include(GoogleTest)
find_package(GTest CONFIG REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}_test "")
target_link_libraries(${CMAKE_PROJECT_NAME}_test PRIVATE ${CMAKE_PROJECT_NAME}_lib GTest::gtest GTest::gtest_main)

target_compile_features(${CMAKE_PROJECT_NAME}_test PUBLIC cxx_std_17)
set_target_properties(${CMAKE_PROJECT_NAME}_test PROPERTIES CXX_EXTENSIONS OFF)

target_sources(${CMAKE_PROJECT_NAME}_test
    PRIVATE
        "common/sudoku_test.cpp"
        "solver/options_test.cpp"
        "solver/region_test.cpp"
        "solver/sudoku_test.cpp"
        "solver/super_region_test.cpp"
      )

gtest_discover_tests(${CMAKE_PROJECT_NAME}_test)
