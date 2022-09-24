#pragma once

#include "SudokuBoard.hh"
#include "SudokuBoardView.hh"
#include "SudokuBoardGenerator.hh"

#include <chrono>
#include <stack>


class SudokuBoardController
{
public:
    struct State {
        int index;
        int value;
    };

    enum Direction {
        Up,
        Down,
        Left,
        Right
    };


public:
    SudokuBoardController(sf::RenderWindow& render_window, SudokuBoard& board, SudokuBoardView& board_view);

    void highlightClickedCell(const sf::Vector2i& mouse_pos);
    void moveTo(Direction dir);

    void generateBoard();
/*     void solveBoard();
    void clearBoard();
    void displaySolutions(); */
    
    void setCell(int value);
    void deleteCell();

    void getHint();
    void undoAction();


private:
    void addLastState(int index, int value);
    void resetLastStates();
    void updateView();


private:
    sf::RenderWindow& m_renderWindow;
    SudokuBoard& m_board;
    SudokuBoardView& m_boardView;

    SudokuBoard m_solvedBoard;

    SudokuBoard m_generatedBoard;

    std::stack<State> m_lastStates;
};