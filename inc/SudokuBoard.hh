#pragma once

#include "Board.hh"

#include <vector>

#include <SFML/Graphics.hpp>


class SudokuBoard: public Board<9,9,int>
{
public:
    bool full() const;
    bool valid() const;
    bool valid(int row, int col) const;
    bool valid(int index) const;
    bool validMove(int row, int col, int value) const;
    bool validMove(int index, int value) const;


private:
    bool validRows() const;
    bool validCols() const;
    bool validChunks() const;

    bool validRow(int row) const;
    bool validCol(int col) const;
    bool validChunk(int chunk) const;

    bool validCells(int* cells, int cells_count) const;


    int countValuesInRow(int row, int value) const;
    int countValuesInCol(int col, int value) const;
    int countValuesInChunk(int chunk, int value) const;
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

bool SudokuBoard::valid(int row, int col) const
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

bool SudokuBoard::valid(int index) const
{
    // Convert index to row and col
    int row = index / 9;
    int col = index % 9;

    return valid(row, col);
}

bool SudokuBoard::validMove(int row, int col, int value) const
{
    // Calculate chunk depending on row and col values
    int chunk_row = row / 3;
    int chunk_col = col / 3;
    int chunk = 3*chunk_row + chunk_col;
    
    // Row, col and chunk cannot have given value
    return countValuesInRow(row, value) == 0
        && countValuesInCol(col, value) == 0
        && countValuesInChunk(chunk, value) == 0;
}

bool SudokuBoard::validMove(int index, int value) const
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

int SudokuBoard::countValuesInRow(int row, int value) const
{
    int count = 0;
    for(int col = 0; col < 9; ++col)
    {
        if(m_cells[9*row + col] == value)
            ++count;
    }
    return count;
}

int SudokuBoard::countValuesInCol(int col, int value) const
{
    int count = 0;
    for(int row = 0; row < 9; ++row)
    {
        if(m_cells[9*row + col] == value)
            ++count;
    }
    return count;
}

int SudokuBoard::countValuesInChunk(int chunk, int value) const
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