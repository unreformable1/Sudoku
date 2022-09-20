#pragma once

#include "SudokuBoard.hh"
#include "SudokuBoardView.hh"
#include "SudokuBoardGenerator.hh"

#include <chrono>


class SudokuBoardController
{
public:
    SudokuBoardController(sf::RenderWindow& render_window, SudokuBoard& board, SudokuBoardView& board_view);
    void onKey(sf::Keyboard::Key key);
    void onMouseClick(sf::Mouse::Button button, const sf::Vector2i& mouse_pos);
    void onScreenNum(int num);
    void onDeleteButton();
    void onUndoButton();
    void onHintButton();


private:
    void updateView();


private:
    sf::RenderWindow& m_renderWindow;
    SudokuBoard& m_board;
    SudokuBoardView& m_boardView;
};

SudokuBoardController::SudokuBoardController(sf::RenderWindow& render_window, SudokuBoard& board, SudokuBoardView& board_view)
:   m_renderWindow(render_window), m_board(board), m_boardView(board_view)
{
    updateView();
}

void SudokuBoardController::onKey(sf::Keyboard::Key key)
{
    if(key >= sf::Keyboard::Num1 && key <= sf::Keyboard::Num9)
    {
        std::vector<Widget*>& cells = m_boardView.getChildren();
        for(int i = 0; i < cells.size(); ++i)
        {
            if(cells[i]->getFocus())
            {
                m_board.set(i, key - 26);   // "key - 26" changes sf::Keyboard::Key enum value to (1-9) digit
            }
        }
        updateView();
        m_boardView.draw(m_renderWindow);
        m_renderWindow.display();
    }
    else if(key == sf::Keyboard::C)
    {
        m_board.clear();
        updateView();
        m_boardView.draw(m_renderWindow);
        m_renderWindow.display();
    }
    else if(key == sf::Keyboard::N)
    {
        if(!m_board.valid())
        {
            std::cout << "Cannot find solutions to a sudoku board that is not correct." << std::endl;
            return;
        }

        std::cout << std::endl;
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
        if(!m_board.valid())
        {
            std::cout << std::endl << "Can't solve invalid board" << std::endl;
            return;
        }

        std::cout << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        SudokuBoardSolver::solve(m_board);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
        std::cout << "Board solving time: " << duration.count() << " µs" << std::endl;

        updateView();
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

        updateView();
        m_boardView.draw(m_renderWindow);
        m_renderWindow.display();
    }
}

void SudokuBoardController::onMouseClick(sf::Mouse::Button button, const sf::Vector2i& mouse_pos)
{
    if(button == sf::Mouse::Left)
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
        m_boardView.draw(m_renderWindow);
        m_renderWindow.display();
    }
    else if(button == sf::Mouse::Right)
    {
        std::vector<Widget*>& cells = m_boardView.getChildren();
        for(int i = 0; i < cells.size(); ++i)
        {
            if(cells[i]->contains(mouse_pos))
            {
                cells[i]->setFocus(true);
                m_board.set(i, 0);
            }
            else
                cells[i]->setFocus(false);
        }
        updateView();
        m_boardView.draw(m_renderWindow);
        m_renderWindow.display();
    }
}

void SudokuBoardController::onScreenNum(int num)
{
    std::vector<Widget*>& cells = m_boardView.getChildren();
    for(int i = 0; i < 81; ++i)
    {
        if(cells[i]->getFocus())
        {
            m_board.set(i, num);
        }
    }
    updateView();
    m_boardView.draw(m_renderWindow);
    m_renderWindow.display();
}

void SudokuBoardController::onDeleteButton()
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
    m_boardView.draw(m_renderWindow);
    m_renderWindow.display();
}

void SudokuBoardController::onUndoButton()
{
    
}

void SudokuBoardController::onHintButton()
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
}