#include <catch2/catch_test_macros.hpp>

#include "Board.hh"



TEST_CASE("Board rows, cols and size is valid after instantiation", "[test]")
{
    SECTION("0x0 board")
    {
        Board<0,0,int> board;
        REQUIRE(board.rows() == 0);
        REQUIRE(board.cols() == 0);
        REQUIRE(board.size() == 0);
    }
    SECTION("9x9 board")
    {
        Board<9,9,int> board;
        REQUIRE(board.rows() == 9);
        REQUIRE(board.cols() == 9);
        REQUIRE(board.size() == 81);
    }
    SECTION("5x25 board")
    {
        Board<5,25,int> board;
        REQUIRE(board.rows() == 5);
        REQUIRE(board.cols() == 25);
        REQUIRE(board.size() == 125);
    }
}

TEST_CASE("All setters works properly", "[test]")
{
    SECTION("set(index)")
    {
        Board<3,3,int> board;
        for(int i = 0; i < 9; ++i)
        {
            board.set(i, 77);
            REQUIRE(board.get(i) == 77);
        }
    }
    SECTION("set(row,col)")
    {
        Board<3,3,int> board;
        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                board.set(i, j, 144);
                REQUIRE(board.get(i,j) == 144);
            }
        }
    }
}

TEST_CASE("All getters works properly", "[test]")
{
    // SET UP
    Board<3,3,int> board;
    for(int i = 0; i < 9; ++i)
    {
        board.set(i, i);
    }

    // TEST
    SECTION("get()")
    {
        const int* cells = board.get();
        for(int i = 0; i < 9; ++i)
        {
            REQUIRE(cells[i] == i);
        }
    }
    SECTION("get(index)")
    {
        for(int i = 0; i < 9; ++i)
        {
            REQUIRE(board.get(i) == i);
        }
    }
    SECTION("get(row, col)")
    {
        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                REQUIRE(board.get(i,j) == 3*i + j);
            }
        }
    }
}

TEST_CASE("Board filled with default value after instantiation", "[test]")
{
    SECTION("int board")
    {
        Board<3,3,int> board;
        for(int i = 0; i < 9; ++i)
            REQUIRE(board.get(i) == 0);
    }
    SECTION("char board")
    {
        Board<3,3,char> board;
        for(int i = 0; i < 9; ++i)
            REQUIRE(board.get(i) == static_cast<char>(0));
    }
    SECTION("string board")
    {
        Board<3,3,std::string> board;
        for(int i = 0; i < 9; ++i)
            REQUIRE(board.get(i) == "");
    }
    SECTION("int pointer board")
    {
        Board<3,3,int*> board;
        for(int i = 0; i < 9; ++i)
            REQUIRE(board.get(i) == nullptr);
    }
}