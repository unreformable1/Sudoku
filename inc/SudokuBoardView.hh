#pragma once

#include "SudokuBoard.hh"
#include "TextBox.hh"

#include <vector>



class SudokuBoardView: public Widget
{
public:
    SudokuBoardView(const sf::Vector2f& pos, const sf::Vector2f& size);


private:
    void initBg(const sf::Vector2f& board_pos, const sf::Vector2f& board_size);
    void initCells(const sf::Vector2f& board_pos, const sf::Vector2f& board_size);
};

SudokuBoardView::SudokuBoardView(const sf::Vector2f& pos, const sf::Vector2f& size)
{
    initBg(pos, size);
    initCells(pos, size);
}

void SudokuBoardView::initBg(const sf::Vector2f& board_pos, const sf::Vector2f& board_size)
{
    m_bg.setFillColor(sf::Color::Black);
    m_bg.setPosition(board_pos);
    m_bg.setSize(board_size);
}

void SudokuBoardView::initCells(const sf::Vector2f& board_pos, const sf::Vector2f& board_size)
{
    m_children.reserve(81);
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
                m_children.emplace_back(new TextBox(sf::Vector2f(pos_x, pos_y), cell_size, "0"));

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