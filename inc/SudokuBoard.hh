#pragma once

#include "Board.hh"

#include <vector>

#include <SFML/Graphics.hpp>


class SudokuBoard: public Board<9,9,int>
{
public:
    bool full() const;
    bool valid() const;
    bool valid(const int& row, const int& col) const;
    bool valid(const int& index) const;
    bool validMove(const int& row, const int& col, const int& value) const;
    bool validMove(const int& index, const int& value) const;


private:
    bool validRows() const;
    bool validCols() const;
    bool validChunks() const;

    bool validRow(const int& row) const;
    bool validCol(const int& col) const;
    bool validChunk(const int& chunk) const;

    bool validCells(int* cells, int cells_count) const;


    int countValuesInRow(const int& row, const int& value) const;
    int countValuesInCol(const int& col, const int& value) const;
    int countValuesInChunk(const int& chunk, const int& value) const;

    bool isInRow(const int& row, const int& value) const;
    bool isInCol(const int& col, const int& value) const;
    bool isInChunk(const int& chunk, const int& value) const;
};

bool SudokuBoard::full() const
{
    for(int i = size() - 1; i >= 0; --i)
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

bool SudokuBoard::valid(const int& row, const int& col) const
{
    int value = m_cells[9*row + col];

    if(value == 0)
        return true;

    // Calculate chunk depending on row and col values
    int chunk_row = row / 3;
    int chunk_col = col / 3;
    int chunk = 3*chunk_row + chunk_col;

    return countValuesInRow(row, value) < 2
        && countValuesInCol(col, value) < 2
        && countValuesInChunk(chunk, value) < 2;
}

bool SudokuBoard::valid(const int& index) const
{
    // Convert index to row and col
    int row = index / 9;
    int col = index % 9;

    return valid(row, col);
}

bool SudokuBoard::validMove(const int& row, const int& col, const int& value) const
{
    // Calculate chunk depending on row and col values
    int chunk_row = row / 3;
    int chunk_col = col / 3;
    int chunk = 3*chunk_row + chunk_col;
    
    // Row, col and chunk cannot have given value
    return isInRow(row, value) == false
        && isInCol(col, value) == false
        && isInChunk(chunk, value) == false;
}

bool SudokuBoard::validMove(const int& index, const int& value) const
{
    // Convert index to row and col
    int row = index / 9;
    int col = index % 9;

    return validMove(row, col, value);
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

bool SudokuBoard::validRow(const int& row) const
{
    int row_cells[9];

    for(int col = 0; col < 9; ++col)
    {
        row_cells[col] = m_cells[9*row + col];
    }
    return validCells(row_cells, 9);
}

bool SudokuBoard::validCol(const int& col) const
{
    int col_cells[9];

    for(int row = 0; row < 9; ++row)
    {
        col_cells[row] = m_cells[9*row + col];
    }
    return validCells(col_cells, 9);
}

bool SudokuBoard::validChunk(const int& chunk) const
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

int SudokuBoard::countValuesInRow(const int& row, const int& value) const
{
    int count = 0;
    for(int col = 0; col < 9; ++col)
    {
        if(m_cells[9*row + col] == value)
            ++count;
    }
    return count;
}

int SudokuBoard::countValuesInCol(const int& col, const int& value) const
{
    int count = 0;
    for(int row = 0; row < 9; ++row)
    {
        if(m_cells[9*row + col] == value)
            ++count;
    }
    return count;
}

int SudokuBoard::countValuesInChunk(const int& chunk, const int& value) const
{
    // Calculate chunk "starting" row and col
    int chunk_row = 3*(chunk / 3);
    int chunk_col = 3*(chunk % 3);

    int count = 0;
    for(int row = chunk_row; row < chunk_row + 3; ++row)
    {
        for(int col = chunk_col; col < chunk_col + 3; ++col)
        {
            if(m_cells[9*row + col] == value)
                ++count;
        }
    }
    return count;
}

bool SudokuBoard::isInRow(const int& row, const int& value) const
{
    for(int col = 0; col < 9; ++col)
    {
        if(m_cells[9*row + col] == value)
            return true;
    }
    return false;
}

bool SudokuBoard::isInCol(const int& col, const int& value) const
{
    for(int row = 0; row < 9; ++row)
    {
        if(m_cells[9*row + col] == value)
            return true;
    }
    return false;
}

bool SudokuBoard::isInChunk(const int& chunk, const int& value) const
{
    // Calculate chunk "starting" row and col
    int chunk_row = 3*(chunk / 3);
    int chunk_col = 3*(chunk % 3);

    for(int row = chunk_row; row < chunk_row + 3; ++row)
    {
        for(int col = chunk_col; col < chunk_col + 3; ++col)
        {
            if(m_cells[9*row + col] == value)
                return true;
        }
    }
    return false;
}