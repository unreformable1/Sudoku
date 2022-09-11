#pragma once

#include "RNG.hh"
#include "SudokuBoard.hh"




class SudokuBoardGenerator
{
public:
    void generate(SudokuBoard& output_board);


private:
    RNG rng;
};

void SudokuBoardGenerator::generate(SudokuBoard& output_board)
{
    SudokuBoard board;
    int combinations_count[board.size()]{};
    int pos = 0;

    while(!board.full())
    {
        board.set(pos, rng.get(1, 9));

        while(!board.valid())
        {
            combinations_count[pos]++;

            if(combinations_count[pos] == 9)
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

    output_board = board;
    
    /*
    stack<PossibleNum> possible_nums;
    pos = 0;
    Board<9,9,PossibleBoard> board;
    0. create possible_num variable
    1. possible_num.num = random number in range (1, 9)
    2. put num inside board at pos
    3. check if board is vaid
        if yes:
            pos++;
            goto 0.;
        if no:
            num had all 1-9 values?
            if yes:
                pos--;
                num = value at that pos;
                num ++;

                num++;
                goto 1.;



    */
}