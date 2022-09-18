#pragma once

#include "Button.hh"
#include "TextBox.hh"
#include "SudokuBoard.hh"
#include "SudokuBoardGenerator.hh"
#include "SudokuBoardView.hh"
#include "WidgetsManager.hh"

#define WIN_WIDTH 900
#define WIN_HEIGHT 600

#define BOARD_WIDTH 600
#define BOARD_HEIGHT 600

#include <chrono>


class Application
{
public:
    Application();
    void run();


private:
    void initRenderWindow();
    void initFont();


private:
    sf::RenderWindow m_renderWindow;
    sf::Font m_font;
};

Application::Application()
{
    initRenderWindow();
    initFont();
}

void Application::run()
{
    WidgetsManager widgets_manager;
    SudokuBoard board;

    SudokuBoardView board_view(board, sf::Vector2f(0, 0), sf::Vector2f(BOARD_WIDTH, BOARD_HEIGHT));
    board_view.setFont(m_font);

    m_renderWindow.clear(sf::Color(140, 140, 140));

    board_view.draw(m_renderWindow);

    //Button undo_button(sf::Vector2f(BOARD_WIDTH + 25, 25), sf::Vector2f(100, 50), "Undo");
    Button erase_button(sf::Vector2f(BOARD_WIDTH + 25, 100), sf::Vector2f(100, 50), "Delete");
    //Button hint_button(sf::Vector2f(BOARD_WIDTH + 25, 175), sf::Vector2f(100, 50), "Hint");

    Button num1_button(sf::Vector2f(BOARD_WIDTH + 25, 250),  sf::Vector2f(65, 65), "1");
    Button num2_button(sf::Vector2f(BOARD_WIDTH + 100, 250), sf::Vector2f(65, 65), "2");
    Button num3_button(sf::Vector2f(BOARD_WIDTH + 175, 250), sf::Vector2f(65, 65), "3");
    Button num4_button(sf::Vector2f(BOARD_WIDTH + 25, 325),  sf::Vector2f(65, 65), "4");
    Button num5_button(sf::Vector2f(BOARD_WIDTH + 100, 325), sf::Vector2f(65, 65), "5");
    Button num6_button(sf::Vector2f(BOARD_WIDTH + 175, 325), sf::Vector2f(65, 65), "6");
    Button num7_button(sf::Vector2f(BOARD_WIDTH + 25, 400),  sf::Vector2f(65, 65), "7");
    Button num8_button(sf::Vector2f(BOARD_WIDTH + 100, 400), sf::Vector2f(65, 65), "8");
    Button num9_button(sf::Vector2f(BOARD_WIDTH + 175, 400), sf::Vector2f(65, 65), "9");

    //undo_button.setFont(m_font);
    erase_button.setFont(m_font);
    //hint_button.setFont(m_font);

    num1_button.setFont(m_font);
    num2_button.setFont(m_font);
    num3_button.setFont(m_font);
    num4_button.setFont(m_font);
    num5_button.setFont(m_font);
    num6_button.setFont(m_font);
    num7_button.setFont(m_font);
    num8_button.setFont(m_font);
    num9_button.setFont(m_font);

    //widgets_manager.add(&undo_button);
    widgets_manager.add(&erase_button);
    //widgets_manager.add(&hint_button);
    widgets_manager.add(&num1_button);
    widgets_manager.add(&num2_button);
    widgets_manager.add(&num3_button);
    widgets_manager.add(&num4_button);
    widgets_manager.add(&num5_button);
    widgets_manager.add(&num6_button);
    widgets_manager.add(&num7_button);
    widgets_manager.add(&num8_button);
    widgets_manager.add(&num9_button);

    widgets_manager.draw(m_renderWindow);

    m_renderWindow.display();

    std::cout << std::endl << "Click H to get some help" << std::endl;

    while(m_renderWindow.isOpen())
    {
        sf::Event event;
        while(m_renderWindow.waitEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                m_renderWindow.close();
            }
            else if(event.type == sf::Event::MouseButtonReleased)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    if(board_view.isMouseOver(m_renderWindow))
                    {
                        std::vector<TextBox>& cells = board_view.getCells();
                        for(TextBox& cell : cells)
                        {
                            if(cell.isMouseOver(m_renderWindow))
                            {
                                cell.setFocus(true);
                            }
                            else
                                cell.setFocus(false);
                        }
                        board_view.draw(m_renderWindow);
                        m_renderWindow.display();
                        // check which cell is clicked
                        // make this cell has focus
                    }
                    else if(erase_button.isMouseOver(m_renderWindow))
                    {
                        std::vector<TextBox>& cells = board_view.getCells();
                        for(int i = 0; i < cells.size(); ++i)
                        {
                            if(cells[i].hasFocus())
                            {
                                board.set(i, 0);
                            }
                        }
                        board_view.draw(m_renderWindow);
                        m_renderWindow.display();
                    }
                    else if(num1_button.isMouseOver(m_renderWindow))
                    {
                        std::vector<TextBox>& cells = board_view.getCells();
                        for(int i = 0; i < 81; ++i)
                        {
                            if(cells[i].hasFocus())
                            {
                                board.set(i, 1);
                            }
                        }
                        board_view.draw(m_renderWindow);
                        m_renderWindow.display();
                    }
                    else if(num2_button.isMouseOver(m_renderWindow))
                    {
                        std::vector<TextBox>& cells = board_view.getCells();
                        for(int i = 0; i < 81; ++i)
                        {
                            if(cells[i].hasFocus())
                            {
                                board.set(i, 2);
                            }
                        }
                        board_view.draw(m_renderWindow);
                        m_renderWindow.display();
                    }
                    else if(num3_button.isMouseOver(m_renderWindow))
                    {
                        std::vector<TextBox>& cells = board_view.getCells();
                        for(int i = 0; i < 81; ++i)
                        {
                            if(cells[i].hasFocus())
                            {
                                board.set(i, 3);
                            }
                        }
                        board_view.draw(m_renderWindow);
                        m_renderWindow.display();
                    }
                    else if(num4_button.isMouseOver(m_renderWindow))
                    {
                        std::vector<TextBox>& cells = board_view.getCells();
                        for(int i = 0; i < 81; ++i)
                        {
                            if(cells[i].hasFocus())
                            {
                                board.set(i, 4);
                            }
                        }
                        board_view.draw(m_renderWindow);
                        m_renderWindow.display();
                    }
                    else if(num5_button.isMouseOver(m_renderWindow))
                    {
                        std::vector<TextBox>& cells = board_view.getCells();
                        for(int i = 0; i < 81; ++i)
                        {
                            if(cells[i].hasFocus())
                            {
                                board.set(i, 5);
                            }
                        }
                        board_view.draw(m_renderWindow);
                        m_renderWindow.display();
                    }
                    else if(num6_button.isMouseOver(m_renderWindow))
                    {
                        std::vector<TextBox>& cells = board_view.getCells();
                        for(int i = 0; i < 81; ++i)
                        {
                            if(cells[i].hasFocus())
                            {
                                board.set(i, 6);
                            }
                        }
                        board_view.draw(m_renderWindow);
                        m_renderWindow.display();
                    }
                    else if(num7_button.isMouseOver(m_renderWindow))
                    {
                        std::vector<TextBox>& cells = board_view.getCells();
                        for(int i = 0; i < 81; ++i)
                        {
                            if(cells[i].hasFocus())
                            {
                                board.set(i, 7);
                            }
                        }
                        board_view.draw(m_renderWindow);
                        m_renderWindow.display();
                    }
                    else if(num8_button.isMouseOver(m_renderWindow))
                    {
                        std::vector<TextBox>& cells = board_view.getCells();
                        for(int i = 0; i < 81; ++i)
                        {
                            if(cells[i].hasFocus())
                            {
                                board.set(i, 8);
                            }
                        }
                        board_view.draw(m_renderWindow);
                        m_renderWindow.display();
                    }
                    else if(num9_button.isMouseOver(m_renderWindow))
                    {
                        std::vector<TextBox>& cells = board_view.getCells();
                        for(int i = 0; i < 81; ++i)
                        {
                            if(cells[i].hasFocus())
                            {
                                board.set(i, 9);
                            }
                        }
                        board_view.draw(m_renderWindow);
                        m_renderWindow.display();
                    }
                }
                else if(event.mouseButton.button == sf::Mouse::Right)
                {
                    if(board_view.isMouseOver(m_renderWindow))
                    {
                        std::vector<TextBox>& cells = board_view.getCells();
                        for(int i = 0; i < cells.size(); ++i)
                        {
                            if(cells[i].isMouseOver(m_renderWindow))
                            {
                                cells[i].setFocus(true);
                                board.set(i, 0);
                            }
                            else
                                cells[i].setFocus(false);
                        }
                        board_view.draw(m_renderWindow);
                        m_renderWindow.display();
                    }
                }
            }
            else if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    m_renderWindow.close();
                }
                else if(event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num9)
                {
                    std::vector<TextBox>& cells = board_view.getCells();
                    for(int i = 0; i < cells.size(); ++i)
                    {
                        if(cells[i].hasFocus())
                        {
                            board.set(i, event.key.code - 26);
                        }
                    }
                    board_view.draw(m_renderWindow);
                    m_renderWindow.display();
                }
                else if(event.key.code == sf::Keyboard::H)
                {
                    std::cout << std::endl;
                    std::cout << "AVAILABLE KEY COMMANDS:" << std::endl;
                    std::cout << "LMB + (1-9) - place digit on the board" << std::endl;
                    std::cout << "RMB - delete clicked cell" << std::endl;
                    std::cout << "C - clear the board" << std::endl;
                    std::cout << "N - compute number of solutions" << std::endl;
                    std::cout << "S - solve the board" << std::endl;
                    std::cout << "G - generate random board (may take up to over 15 sec)" << std::endl;
                    std::cout << std::endl;
                }
                else if(event.key.code == sf::Keyboard::C)
                {
                    board.clear();
                    board_view.draw(m_renderWindow);
                    m_renderWindow.display();
                }
                else if(event.key.code == sf::Keyboard::N)
                {
                    std::cout << std::endl;
                    if(!board.valid())
                    {
                        std::cout << "Cannot find solutions to a sudoku board that is not correct.";
                        break;
                    }
                    else
                    {
                        auto start = std::chrono::high_resolution_clock::now();
                        const int& solutions_count = SudokuBoardSolver::solutions(board);
                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
                        std::cout << "Solution generation time: " << duration.count() << " µs" << std::endl;

                        if(solutions_count == SudokuBoardSolver::MAX_SOLUTIONS)
                        {
                            std::cout << "There are more than " << SudokuBoardSolver::MAX_SOLUTIONS << " solutions.";
                        }
                        else
                        {
                            std::cout << "Solutions: " << solutions_count;
                        }
                    }
                    std::cout << std::endl;
                }
                else if(event.key.code == sf::Keyboard::S)
                {
                    std::cout << std::endl;
                    auto start = std::chrono::high_resolution_clock::now();
                    SudokuBoardSolver::solve(board);
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
                    std::cout << "Board solving time: " << duration.count() << " µs" << std::endl;

                    board_view.draw(m_renderWindow);
                    m_renderWindow.display();
                }
                else if(event.key.code == sf::Keyboard::G)
                {
                    std::cout << std::endl;
                    auto start = std::chrono::high_resolution_clock::now();
                    SudokuBoardGenerator::generate(board);
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
                    std::cout << "Board generation time: " << duration.count() << " µs" << std::endl;

                    board_view.draw(m_renderWindow);
                    m_renderWindow.display();
                }
            }
            else if(event.type == sf::Event::TextEntered)
            {
                
            }
        }
    }
}

void Application::initRenderWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    m_renderWindow.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Sudoku Puzzle Game", sf::Style::Close, settings);
    m_renderWindow.setVerticalSyncEnabled(true);
    sf::VideoMode screen = sf::VideoMode::getDesktopMode();
    m_renderWindow.setPosition(sf::Vector2i(screen.width/2 - WIN_WIDTH/2, screen.height/2 - WIN_HEIGHT/2));
}

void Application::initFont()
{
    m_font.loadFromFile("../assets/fonts/arial/arial.ttf");
}