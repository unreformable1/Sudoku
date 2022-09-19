#pragma once

#include "SudokuBoard.hh"
#include "SudokuBoardView.hh"

#include <chrono>


class SudokuBoardController
{
public:
    SudokuBoardController(sf::RenderWindow& render_window, SudokuBoard& board, SudokuBoardView& board_view);
    void onKey(sf::Keyboard::Key key);
    void onMouseClick(sf::Mouse::Button button);
    void onScreenNum(int num);
    void onDeleteButton();
    void onUndoButton();
    void onHintButton();


private:
    sf::RenderWindow& m_renderWindow;
    SudokuBoard& m_board;
    SudokuBoardView& m_boardView;
};

SudokuBoardController::SudokuBoardController(sf::RenderWindow& render_window, SudokuBoard& board, SudokuBoardView& board_view)
:   m_renderWindow(render_window), m_board(board), m_boardView(board_view)
{

}

void SudokuBoardController::onKey(sf::Keyboard::Key key)
{
    if(key >= sf::Keyboard::Num1 && key <= sf::Keyboard::Num9)
    {
        std::vector<CellView>& cells = m_boardView.getCells();
        for(int i = 0; i < cells.size(); ++i)
        {
            if(cells[i].hasFocus())
            {
                m_board.set(i, key - 26);   // "key - 26" changes sf::Keyboard::Key enum value to (1-9) digit
            }
        }
        m_boardView.draw(m_renderWindow);
        m_renderWindow.display();
    }
    else if(key == sf::Keyboard::C)
    {
        m_board.clear();
        m_boardView.draw(m_renderWindow);
        m_renderWindow.display();
    }
    else if(key == sf::Keyboard::N)
    {
        std::cout << std::endl;
        if(!m_board.valid())
        {
            std::cout << "Cannot find solutions to a sudoku board that is not correct.";
            return;
        }

        auto start = std::chrono::high_resolution_clock::now();
        const int& solutions_count = SudokuBoardSolver::solutions(m_board);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
        std::cout << "Solution generation time: " << duration.count() << " µs" << std::endl;

        if(solutions_count == SudokuBoardSolver::MAX_SOLUTIONS)
        {
            std::cout << "There are more than " << SudokuBoardSolver::MAX_SOLUTIONS << " solutions.";
        }
        else
        {
            std::cout << "Solutions: " << solutions_count;
        }
        std::cout << std::endl;
    }
    else if(key == sf::Keyboard::S)
    {
        std::cout << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        SudokuBoardSolver::solve(m_board);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
        std::cout << "Board solving time: " << duration.count() << " µs" << std::endl;

        m_boardView.draw(m_renderWindow);
        m_renderWindow.display();
    }
    else if(key == sf::Keyboard::G)
    {
        std::cout << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        SudokuBoardGenerator::generate(m_board);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
        std::cout << "Board generation time: " << duration.count() << " µs" << std::endl;

        m_boardView.draw(m_renderWindow);
        m_renderWindow.display();
    }
}

void SudokuBoardController::onMouseClick(sf::Mouse::Button button)
{
    if(button == sf::Mouse::Left)
    {
        std::vector<CellView>& cells = m_boardView.getCells();
        for(CellView& cell : cells)
        {
            if(cell.isMouseOver(m_renderWindow))
            {
                cell.setFocus(true);
            }
            else
                cell.setFocus(false);
        }
        m_boardView.draw(m_renderWindow);
        m_renderWindow.display();
    }
    else if(button == sf::Mouse::Right)
    {
        std::vector<CellView>& cells = m_boardView.getCells();
        for(int i = 0; i < cells.size(); ++i)
        {
            if(cells[i].isMouseOver(m_renderWindow))
            {
                cells[i].setFocus(true);
                m_board.set(i, 0);
            }
            else
                cells[i].setFocus(false);
        }
        m_boardView.draw(m_renderWindow);
        m_renderWindow.display();
    }
}

void SudokuBoardController::onScreenNum(int num)
{
    std::vector<CellView>& cells = m_boardView.getCells();
    for(int i = 0; i < 81; ++i)
    {
        if(cells[i].hasFocus())
        {
            m_board.set(i, num);
        }
    }
    m_boardView.draw(m_renderWindow);
    m_renderWindow.display();
}

void SudokuBoardController::onDeleteButton()
{
    std::vector<CellView>& cells = m_boardView.getCells();
    for(int i = 0; i < cells.size(); ++i)
    {
        if(cells[i].hasFocus())
        {
            m_board.set(i, 0);
        }
    }
    m_boardView.draw(m_renderWindow);
    m_renderWindow.display();
}

void SudokuBoardController::onUndoButton()
{
    
}

void SudokuBoardController::onHintButton()
{

}