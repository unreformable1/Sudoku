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
    bool found = false;
    for(int i = 0; i < cells.size(); ++i)
    {
        if(cells[i]->getFocus())
        {
            cellUnderFocusIndex = i;
            cellUnderFocusRow = i / 9;
            cellUnderFocusCol = i % 9;
            found = true;
            break;
        }
    }
    if(!found)
        return;

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

    // Assing solved version of generated board
    m_solvedBoard = m_board;
    SudokuBoardSolver::solve(m_solvedBoard);

    // Assign board after generation
    m_generatedBoard = m_board;
    std::vector<Widget*>& cells = m_boardView.getChildren();
    for(int i = 0; i < 81; ++i)
    {
        if(m_generatedBoard(i) != 0)
        {
            cells[i]->setTextColor(sf::Color::Blue);
        }
        else
        {
            cells[i]->setTextColor(sf::Color::Black);
        }
    }

    resetLastStates();

    updateView();
}

/* void SudokuBoardController::solveBoard()
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
} */

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
            if(m_generatedBoard(i) != 0)
                return;
            
            addLastState(i, m_board(i));
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
            if(m_generatedBoard(i) != 0)
                return;
            
            addLastState(i, m_board(i));
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
    if(m_lastStates.empty())
        return;

    const State& state = m_lastStates.top();
    std::vector<Widget*>& cells = m_boardView.getChildren();
    for(int i = 0; i < cells.size(); ++i)
    {
        if(cells[i]->getFocus())
        {
            cells[i]->setFocus(false);
        }
    }
    cells[state.index]->setFocus(true);
    m_board.set(state.index, state.value);
    m_lastStates.pop();

    updateView();
}

void SudokuBoardController::addLastState(int index, int value)
{
    State last_state;
    last_state.index = index;
    last_state.value = value;

    m_lastStates.emplace(last_state);
}

void SudokuBoardController::resetLastStates()
{
    while(!m_lastStates.empty())
    {
        m_lastStates.pop();
    }
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