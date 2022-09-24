#pragma once

#include "SudokuBoardSolver.hh"



class SudokuBoardGenerator
{
public:
    static void generate(SudokuBoard& board);


private:
    static void generateFull(SudokuBoard& board);
};