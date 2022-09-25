#pragma once

#include "Board.hh"



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