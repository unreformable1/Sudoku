cmake_minimum_required(VERSION 3.5)


project(tests LANGUAGES CXX)
set(TESTS
    SudokuBoardTest.cpp
)

string(REPLACE ".cpp" "" TEST_NAMES "${TESTS}")
set(TESTS ${TEST_NAMES})


find_package(Catch2 3 REQUIRED)

foreach(test_name ${TEST_NAMES})
    add_executable(${test_name}.out Sudoku/${test_name}.cpp)

    target_link_libraries(${test_name}.out PRIVATE
        Catch2::Catch2WithMain
    )

    target_include_directories(${test_name}.out PUBLIC
        ${CMAKE_SOURCE_DIR}/../inc/
    )
endforeach()