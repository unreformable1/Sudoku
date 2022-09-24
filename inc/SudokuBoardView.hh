#pragma once

#include "SudokuBoard.hh"
#include "Button.hh"

#include <vector>



class SudokuBoardView: public Widget
{
public:
    SudokuBoardView(const sf::Vector2f& pos, const sf::Vector2f& size);


private:
    void initBg(const sf::Vector2f& board_pos, const sf::Vector2f& board_size);
    void initCells(const sf::Vector2f& board_pos, const sf::Vector2f& board_size);
};