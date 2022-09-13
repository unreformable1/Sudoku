#pragma once

#include "RNG.hh"
#include "SudokuBoard.hh"


class SudokuBoardSolver
{
public:
    void solve(SudokuBoard& board);
    bool solvable(const SudokuBoard& board);


private:
    RNG m_rng;
};

void SudokuBoardSolver::solve(SudokuBoard& board)
{
    int pos = 0;
    int combinations_count[board.size()];
    for(int i = 0; i < board.size(); ++i)
        combinations_count[i] = 0;

    while(!board.full())
    {
        board.set(pos, m_rng.get(1, 9));

        while(!board.valid(pos, board.get(pos)))
        {
            combinations_count[pos]++;

            if(combinations_count[pos] == 9)    // out of number combinations for current cell
            {
                // Reset actual cell and return to previous cell
                board.set(pos, 0);
                combinations_count[pos] = 0;
                pos--;
            }

            board.set(pos, board.get(pos) + 1);
            if(board.get(pos) > 9)
                board.set(pos, 1);
        }

        pos++;
    }
}