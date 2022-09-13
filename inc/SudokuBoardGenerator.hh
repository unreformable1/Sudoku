#pragma once

#include "SudokuBoard.hh"
#include "SudokuBoardSolver.hh"




class SudokuBoardGenerator
{
public:
    void generate(SudokuBoard& output_board);


private:
    void solve(SudokuBoard& board);


private:
    SudokuBoardSolver m_solver;
};

void SudokuBoardGenerator::generate(SudokuBoard& output_board)
{
    SudokuBoard board;

    m_solver.solve(board);

    output_board = board;
}