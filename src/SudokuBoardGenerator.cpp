#include "SudokuBoardGenerator.hh"



void SudokuBoardGenerator::generate(SudokuBoard& board)
{
    // First phase - generate full board and make copy of it
    board.clear();
    generateFull(board);

    SudokuBoard full_board(board);

    // Second phase - keep removing cells to the moment when there is barely 1 solution
    {
        int index;
        while(SudokuBoardSolver::solutions(board, 2) == 1)
        {
            index = RNG::get(0, 80);
            while(board(index) == 0)
            {
                if(++index == 81)
                    index = 0;
            }
            board.remove(index);
        }
        board.set(index, full_board(index));
    }
    // Third phase - remove as much as possible cells so there is still 1 unique solution
    {
        for(int i = 0; i < 81; ++i)
        {
            if(board(i) == 0)
                continue;
            
            board.remove(i);

            if(SudokuBoardSolver::solutions(board, 2) > 1)
            {
                board.set(i, full_board(i));
            }
        }
    }
}

void SudokuBoardGenerator::generateFull(SudokuBoard& board)
{
    int pos = 0;
    int combinations_count[board.size()];
    for(int i = 0; i < board.size(); ++i)
        combinations_count[i] = 0;

    while(!board.full())
    {
        board.set(pos, RNG::get(1, 9));

        while(!board.valid(pos))
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