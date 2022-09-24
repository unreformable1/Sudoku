#pragma once

#include "RNG.hh"
#include "SudokuBoard.hh"



class SudokuBoardSolver
{
public:
    const static int MAX_SOLUTIONS;


public:
    static bool solve(SudokuBoard& board);
    static int solutions(const SudokuBoard& board, const int& solutions_limit = SudokuBoardSolver::MAX_SOLUTIONS);


private:
    static bool solveIterative(SudokuBoard& board);
    static bool solveRecursive(SudokuBoard& board, int pos);
    static void solutions(SudokuBoard& board, int pos, int& count, const int& solutions_limit);
};