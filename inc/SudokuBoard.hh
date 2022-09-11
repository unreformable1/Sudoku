#pragma once

#include "Board.hh"

#include <vector>

#include <SFML/Graphics.hpp>


class SudokuBoard: public Board<9,9,int>
{
public:
    void draw(sf::RenderTarget& render_target, const sf::Font& font, const sf::Vector2f& size, const sf::Vector2f& pos = sf::Vector2f()) const;
    bool full() const;
    bool valid() const;
    bool valid(int row, int col) const;


private:
    bool validRows() const;
    bool validCols() const;
    bool validChunks() const;

    bool validRow(int row) const;
    bool validCol(int col) const;
    bool validChunk(int chunk) const;

    bool validCells(int* cells, int cells_count) const;
};

void SudokuBoard::draw(sf::RenderTarget& render_target, const sf::Font& font, const sf::Vector2f& size, const sf::Vector2f& pos) const
{
    // Setup board's background
    sf::RectangleShape background;
    background.setPosition(pos);
    background.setSize(size);
    background.setFillColor(sf::Color::Black);

    // Set up digits onto cells
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Black);

    // Draw background
    render_target.draw(background);

    // Set up cells
    {
        // Make reference scale for board elements
        float cell_scale = 3.0f;
        float board_frame_scale = 0.1f;
        float cell_frame_scale = 0.05f;
        float chunk_frame_scale = 0.05f;
        float scale_sum = 9*cell_scale + 2*board_frame_scale + 12*cell_frame_scale + 2*chunk_frame_scale;

        // Make sizes depending on scales of elements
        const sf::Vector2f& cell_size = cell_scale/scale_sum * size;
        const float& board_frame_thickness = board_frame_scale/scale_sum * ((size.x + size.y)/2);
        const float& cell_frame_thickness = cell_frame_scale/scale_sum * ((size.x + size.y)/2);
        const float& chunk_frame_thickness = chunk_frame_scale/scale_sum * ((size.x + size.y)/2);

        // Setup cells
        sf::RectangleShape rect;
        rect.setFillColor(sf::Color::White);
        rect.setSize(cell_size);

        // Create and position cells
        float pos_x;
        float pos_y = board_frame_thickness + cell_frame_thickness;
        for(int row = 0; row < 9; ++row)
        {
            pos_x = board_frame_thickness + cell_frame_thickness;
            for(int col = 0; col < 9; ++col)
            {
                if(valid(row, col))
                    rect.setFillColor(sf::Color::White);
                else
                    rect.setFillColor(sf::Color::Red);  
                rect.setPosition(pos_x, pos_y);
                render_target.draw(rect);

                text.setString(std::to_string(m_cells[9 * row + col]));
                const sf::FloatRect& text_bounds = text.getLocalBounds();
                const float& text_x = pos_x + cell_size.x/2 - text_bounds.left - text_bounds.width/2;
                const float& text_y = pos_y + cell_size.y/2 - text_bounds.top - text_bounds.height/2;
                text.setPosition(text_x, text_y);
                render_target.draw(text);

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

bool SudokuBoard::full() const
{
    for(int i = 0; i < size(); ++i)
    {
        if(m_cells[i] == 0)
        {
            return false;
        }
    }
    return true;
}

bool SudokuBoard::valid() const
{
    return validRows() && validCols() && validChunks();
}

bool SudokuBoard::valid(int row, int col) const
{
    int chunk;
    if(row < 3)
    {
        if(col < 3)
        {
            chunk = 0;
        }
        else if(col < 6)
        {
            chunk = 1;
        }
        else
        {
            chunk = 2;
        }
    }
    else if(row < 6)
    {
        if(col < 3)
        {
            chunk = 3;
        }
        else if(col < 6)
        {
            chunk = 4;
        }
        else
        {
            chunk = 5;
        }
    }
    else
    {
        if(col < 3)
        {
            chunk = 6;
        }
        else if(col < 6)
        {
            chunk = 7;
        }
        else
        {
            chunk = 8;
        }
    }
    return validRow(row) && validCol(col) && validChunk(chunk);
}

bool SudokuBoard::validRows() const
{
    for(int row = 0; row < 9; ++row)
    {
        if(!validRow(row))
            return false;
    }
    return true;
}

bool SudokuBoard::validCols() const
{
    for(int col = 0; col < 9; ++col)
    {
        if(!validCol(col))
            return false;
    }
    return true;
}

bool SudokuBoard::validChunks() const
{
    for(int chunk = 0; chunk < 9; ++chunk)
    {
        if(!validChunk(chunk))
            return false;
    }
    return true;
}

bool SudokuBoard::validRow(int row) const
{
    int row_cells[9];

    for(int col = 0; col < 9; ++col)
    {
        row_cells[col] = m_cells[9*row + col];
    }
    return validCells(row_cells, 9);
}

bool SudokuBoard::validCol(int col) const
{
    int col_cells[9];

    for(int row = 0; row < 9; ++row)
    {
        col_cells[row] = m_cells[9*row + col];
    }
    return validCells(col_cells, 9);
}

bool SudokuBoard::validChunk(int chunk) const
{
    // Compute chunk starting row and col (left top corner)
    int chunk_row = 0;
    int chunk_col = 0;
    {
        int tmp = chunk;
        while(tmp > 2)
        {
            tmp -= 3;
            chunk_row += 3;
        }
        while(tmp > 0)
        {
            tmp -= 1;
            chunk_col += 3;
        }
    }

    int index = 0;
    int chunk_cells[9];
    for(int row = chunk_row; row < chunk_row + 3; ++row)
    {
        for(int col = chunk_col; col < chunk_col + 3; ++col)
        {
            chunk_cells[index] = m_cells[9 * row + col];
            index++;
        }
    }
    return validCells(chunk_cells, 9);
}

bool SudokuBoard::validCells(int* cells, int cells_count) const
{
    bool num_occurred[cells_count];
    for(int i = 0; i < cells_count; ++i)
        num_occurred[i] = false;

    for(int i = 0; i < cells_count; ++i)
    {
        const int& cell_value = cells[i];
        if(cell_value != 0)
        {
            if(num_occurred[cell_value - 1] == true)      // second occurrence of number
                return false;
            else
                num_occurred[cell_value - 1] = true;      // first occurrence of number
        }
    }
    return true;
}