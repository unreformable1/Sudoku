cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME sudoku)

project(${PROJECT_NAME})

set(SRC_FILES
    src/main.cpp
)

set(INC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/Widgets
)

find_package(SFML 2 REQUIRED audio graphics network system window)

include_directories(${SFML_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)

target_include_directories(${PROJECT_NAME} PUBLIC ${INC_FILES})