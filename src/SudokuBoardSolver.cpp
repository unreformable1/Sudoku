#include "SudokuBoardSolver.hh"



const int SudokuBoardSolver::MAX_SOLUTIONS = 100;

bool SudokuBoardSolver::solve(SudokuBoard& board)
{
    return solveRecursive(board, 0);
}

int SudokuBoardSolver::solutions(const SudokuBoard& board, const int& solutions_limit)
{
    SudokuBoard tmp(board);             // Create modifable copy of input board

    int solutions_count = 0;

    solutions(tmp, 0, solutions_count, solutions_limit);

    return solutions_count;
}

bool SudokuBoardSolver::solveIterative(SudokuBoard& board)
{
    bool was_filled[81];        // array of not filled, before this method execution, tiles
    for(int i = 0; i < 81; ++i)
    {
        if(board(i) == 0)
            was_filled[i] = false;
        else
            was_filled[i] = true;
    }
    int pos = 0;


    while(true)
    {
        if(pos == 81)                   // board is full and valid
            return true;
        else if(was_filled[pos])        // skip if cell was filled before this method execution
        {
            ++pos;
        }
        else
        {
            board.set(pos, board(pos) + 1);

            if(board(pos) < 10 && board.valid(pos))
            {
                ++pos;
            }
            else
            {
                if(board(pos) >= 9)     // out of combinations for this tree
                {
                    // Seek for new position of not filled, before this method execution, tile
                    for(int new_pos = pos - 1; new_pos >= 0; --new_pos)
                    {
                        if(was_filled[new_pos] == false)
                        {
                            board.set(pos, 0);
                            pos = new_pos;
                            break;
                        }

                        if(new_pos <= 0)
                            return false;
                    }
                }
            }
        }
    }
}

bool SudokuBoardSolver::solveRecursive(SudokuBoard& board, int pos)
{
    if(pos == 81)                   // board is full and valid
        return true;
    else if(board(pos) != 0)        // skip already set cells (before this method execution)
        return solveRecursive(board, pos+1);
    else
    {
        for(int val = 1; val < 10; ++val)
        {
            if(board.validMove(pos, val))
            {
                board.set(pos, val);
                    
                if(solveRecursive(board, pos+1))
                    return true;
                board.set(pos, 0);
            }
        }
        return false;
    }
}

void SudokuBoardSolver::solutions(SudokuBoard& board, int pos, int& count, const int& solutions_limit)
{
    if(count == solutions_limit || count == SudokuBoardSolver::MAX_SOLUTIONS)
        return;
    else if(pos == 81)
        ++count;
    else if(board(pos) != 0)
        solutions(board, pos + 1, count, solutions_limit);
    else
    {
        for(int val = 1; val < 10; ++val)
        {
            if(board.validMove(pos, val))
            {
                board.set(pos, val);
                solutions(board, pos + 1, count, solutions_limit);
            }
        }
        board.set(pos, 0);
    }
}