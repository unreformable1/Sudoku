cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME sudoku)

project(${PROJECT_NAME})

set(SRC_FILES
    src/main.cpp
    src/Application.cpp
    src/RNG.cpp
    src/SudokuBoard.cpp
    src/SudokuBoardController.cpp
    src/SudokuBoardGenerator.cpp
    src/SudokuBoardSolver.cpp
    src/SudokuBoardView.cpp
    src/WidgetsManager.cpp
    src/Widgets/Button.cpp
    src/Widgets/Widget.cpp
)

find_package(SFML 2 REQUIRED graphics system window)

include_directories(${SFML_INCLUDE_DIR})

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-system
    sfml-window
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/Widgets
)