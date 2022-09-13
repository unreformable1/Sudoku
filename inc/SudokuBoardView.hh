#pragma once

#include "SudokuBoard.hh"
#include "Button.hh"
#include "TextBox.hh"

#include <vector>


class SudokuBoardView: public IWidget
{
public:
    SudokuBoardView(const SudokuBoard& sudoku_board, const sf::Vector2f& pos, const sf::Vector2f& size);
    bool isMouseOver(const sf::RenderWindow& render_window);
    void draw(sf::RenderTarget& render_target);
    
    void setFont(const sf::Font& font);

    std::vector<TextBox>& getCells() { return m_cells; }


private:
    void initBg(const sf::Vector2f& board_pos, const sf::Vector2f& board_size);
    void initCells(const sf::Vector2f& board_pos, const sf::Vector2f& board_size);
    void update();


private:
    const SudokuBoard& m_sudokuBoard;

    sf::RectangleShape m_bg;
    std::vector<TextBox> m_cells;
};

SudokuBoardView::SudokuBoardView(const SudokuBoard& sudoku_board, const sf::Vector2f& pos, const sf::Vector2f& size)
:   m_sudokuBoard(sudoku_board)
{
    initBg(pos, size);
    initCells(pos, size);
}

bool SudokuBoardView::isMouseOver(const sf::RenderWindow& render_window)
{
    const sf::Vector2i& mouse_pos = sf::Mouse::getPosition(render_window);
    
    if(m_bg.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)))
        return true;
    return false;
}

void SudokuBoardView::draw(sf::RenderTarget& render_target)
{
    update();

    render_target.draw(m_bg);
    for(int i = 0; i < m_cells.size(); ++i)
    {
        if(m_cells[i].hasFocus())
            m_cells[i].setBgColor(sf::Color(137, 207, 240));    // baby blue :P
        else if(!m_sudokuBoard.valid(i))
            m_cells[i].setBgColor(sf::Color(255, 119, 121));    // baby red :P
        else
            m_cells[i].setBgColor(sf::Color::White);

        m_cells[i].draw(render_target);
    }
}

void SudokuBoardView::setFont(const sf::Font& font)
{
    for(TextBox& text_box : m_cells)
    {
        text_box.setFont(font);
    }
}

void SudokuBoardView::initBg(const sf::Vector2f& board_pos, const sf::Vector2f& board_size)
{
    m_bg.setFillColor(sf::Color::Black);
    m_bg.setPosition(board_pos);
    m_bg.setSize(board_size);
}

void SudokuBoardView::initCells(const sf::Vector2f& board_pos, const sf::Vector2f& board_size)
{
    m_cells.reserve(81);
    // Set up cells
    {
        // Make reference scale for board elements
        float cell_scale = 3.0f;
        float board_frame_scale = 0.1f;
        float cell_frame_scale = 0.05f;
        float chunk_frame_scale = 0.05f;
        float scale_sum = 9*cell_scale + 2*board_frame_scale + 12*cell_frame_scale + 2*chunk_frame_scale;

        // Make sizes depending on scales of elements
        const sf::Vector2f& cell_size = cell_scale/scale_sum * board_size;
        const float& board_frame_thickness = board_frame_scale/scale_sum * ((board_size.x + board_size.y)/2);
        const float& cell_frame_thickness = cell_frame_scale/scale_sum * ((board_size.x + board_size.y)/2);
        const float& chunk_frame_thickness = chunk_frame_scale/scale_sum * ((board_size.x + board_size.y)/2);

        // Create and position cells
        float pos_x;
        float pos_y = board_frame_thickness + cell_frame_thickness;
        for(int row = 0; row < 9; ++row)
        {
            pos_x = board_frame_thickness + cell_frame_thickness;
            for(int col = 0; col < 9; ++col)
            {
                m_cells.emplace_back(TextBox(sf::Vector2f(pos_x, pos_y), cell_size, std::to_string(m_sudokuBoard.get(row, col))));

                pos_x += cell_size.x;
                pos_x += cell_frame_thickness;

                if((col + 1) % 3 == 0  &&  col != 0) // every 3 cells emplaced
                {
                    pos_x += chunk_frame_thickness;
                    pos_x += cell_frame_thickness;
                }
            }
            pos_y += cell_size.y;
            pos_y += cell_frame_thickness;

            if((row + 1) % 3 == 0  &&  row != 0) // every 3 rows of cells emplaced
            {
                pos_y += chunk_frame_thickness;
                pos_y += cell_frame_thickness;
            }
        }
    }
}

void SudokuBoardView::update()
{
    for(int i = 0; i < m_sudokuBoard.size(); ++i)
    {
        if(m_sudokuBoard(i) == 0)
            m_cells[i].setText("");
        else
            m_cells[i].setText(std::to_string(m_sudokuBoard(i)));
    }
}