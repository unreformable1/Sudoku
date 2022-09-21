#pragma once

#include "SudokuBoard.hh"
#include "SudokuBoardView.hh"
#include "SudokuBoardGenerator.hh"

#include <chrono>
#include <stack>


class SudokuBoardController
{
public:
    struct Action {

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
    void solveBoard();
    void clearBoard();
    void displaySolutions();
    
    void setCell(int value);
    void deleteCell();

    void getHint();
    void undoAction();


private:
    void updateView();


private:
    sf::RenderWindow& m_renderWindow;
    SudokuBoard& m_board;
    SudokuBoardView& m_boardView;

    SudokuBoard m_solvedBoard;

    std::stack<Action> m_actions;
};

SudokuBoardController::SudokuBoardController(sf::RenderWindow& render_window, SudokuBoard& board, SudokuBoardView& board_view)
:   m_renderWindow(render_window), m_board(board), m_boardView(board_view)
{
    updateView();
}

void SudokuBoardController::highlightClickedCell(const sf::Vector2i& mouse_pos)
{
    std::vector<Widget*>& cells = m_boardView.getChildren();
    for(Widget* cell : cells)
    {
        if(cell->contains(mouse_pos))
        {
            cell->setFocus(true);
        }
        else
        {
            cell->setFocus(false);
        }
    }
    
    updateView();
}

void SudokuBoardController::moveTo(Direction dir)
{
    int cellUnderFocusIndex;
    int cellUnderFocusRow;
    int cellUnderFocusCol;
    std::vector<Widget*>& cells = m_boardView.getChildren();
    for(int i = 0; i < cells.size(); ++i)
    {
        if(cells[i]->getFocus())
        {
            cellUnderFocusIndex = i;
            cellUnderFocusRow = i / 9;
            cellUnderFocusCol = i % 9;
            break;
        }
    }

    if(dir == Direction::Up)
    {
        if(cellUnderFocusRow == 0)  // can't find cell up to cell in the
            return;                 // first row so return
        
        cells[cellUnderFocusIndex]->setFocus(false);
        cellUnderFocusIndex -= 9;
        cells[cellUnderFocusIndex]->setFocus(true);
    }
    else if(dir == Direction::Down)
    {
        if(cellUnderFocusRow == 8)
            return;

        cells[cellUnderFocusIndex]->setFocus(false);
        cellUnderFocusIndex += 9;
        cells[cellUnderFocusIndex]->setFocus(true);
    }
    else if(dir == Direction::Left)
    {
        if(cellUnderFocusCol == 0)
            return;
        
        cells[cellUnderFocusIndex]->setFocus(false);
        cellUnderFocusIndex -= 1;
        cells[cellUnderFocusIndex]->setFocus(true);
    }
    else if(dir == Direction::Right)
    {
        if(cellUnderFocusCol == 8)
            return;
        
        cells[cellUnderFocusIndex]->setFocus(false);
        cellUnderFocusIndex += 1;
        cells[cellUnderFocusIndex]->setFocus(true);
    }

    updateView();
}

void SudokuBoardController::generateBoard()
{
    auto start = std::chrono::high_resolution_clock::now();
    SudokuBoardGenerator::generate(m_board);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
    std::cout << std::endl << "Board generation time: " << duration.count() << " µs" << std::endl;

    m_solvedBoard = m_board;
    SudokuBoardSolver::solve(m_solvedBoard);

    updateView();
}

void SudokuBoardController::solveBoard()
{
    if(!m_board.valid())
    {
        std::cout << std::endl << "Can't solve invalid board" << std::endl;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();
    SudokuBoardSolver::solve(m_board);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
    std::cout << std::endl << "Board solving time: " << duration.count() << " µs" << std::endl;

    updateView();
}

void SudokuBoardController::clearBoard()
{
    m_board.clear();

    updateView();
}

void SudokuBoardController::displaySolutions()
{
    if(!m_board.valid())
    {
        std::cout << std::endl << "Solutions cannot be found for the incorrect board" << std::endl;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();
    const int& solutions_count = SudokuBoardSolver::solutions(m_board);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);

    if(solutions_count == SudokuBoardSolver::MAX_SOLUTIONS)
    {
        std::cout << std::endl << "There are more than " << SudokuBoardSolver::MAX_SOLUTIONS << " solutions";
    }
    else
    {
        std::cout << std::endl << "Solutions: " << solutions_count;
    }
    std::cout << std::endl << "Solution generation time: " << duration.count() << " µs" << std::endl;
}

void SudokuBoardController::setCell(int value)
{
    if(value < 0 || value > 9)
    {
        std::cerr << "ERROR::SudokuBoarController::setCell()::Value out of (0-9) range" << std::endl;
        return;
    }

    std::vector<Widget*>& cells = m_boardView.getChildren();
    for(int i = 0; i < cells.size(); ++i)
    {
        if(cells[i]->getFocus())
        {
            m_board.set(i, value);
        }
    }

    updateView();
}

void SudokuBoardController::deleteCell()
{
    std::vector<Widget*>& cells = m_boardView.getChildren();
    for(int i = 0; i < cells.size(); ++i)
    {
        if(cells[i]->getFocus())
        {
            m_board.set(i, 0);
        }
    }

    updateView();
}

void SudokuBoardController::getHint()
{
    std::vector<Widget*>& cells = m_boardView.getChildren();
    for(int i = 0; i < cells.size(); ++i)
    {
        if(cells[i]->getFocus())
        {
            m_board.set(i, m_solvedBoard(i));
        }
    }

    updateView();
}

void SudokuBoardController::undoAction()
{

}
    
void SudokuBoardController::updateView()
{
    for(int i = 0; i < 81; ++i)
    {
        Widget* cell = m_boardView.getChild(i);

        // Update view of each cell number
        if(m_board.get(i) == 0)
            cell->setTextString("");
        else
            cell->setTextString(std::to_string(m_board.get(i)));

        // Update view of each cell background
        if(cell->getFocus())
            cell->setBgColor(sf::Color(137, 207, 240));    // baby blue :P
        else if(!m_board.valid(i))
            cell->setBgColor(sf::Color(255, 119, 121));    // baby red :P
        else
            cell->setBgColor(sf::Color::White);
    }

    m_boardView.draw(m_renderWindow);
    m_renderWindow.display();
}