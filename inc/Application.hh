#pragma once

#include "Button.hh"
#include "SudokuBoard.hh"
#include "SudokuBoardGenerator.hh"
#include "SudokuBoardController.hh"
#include "SudokuBoardView.hh"
#include "WidgetsManager.hh"

#define WIN_WIDTH 900
#define WIN_HEIGHT 600

#define BOARD_WIDTH 600
#define BOARD_HEIGHT 600



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

    SudokuBoardController board_controller(m_renderWindow, board, board_view);

    m_renderWindow.clear(sf::Color(140, 140, 140));

    board_view.draw(m_renderWindow);

    //Button undo_button(sf::Vector2f(BOARD_WIDTH + 25, 25), sf::Vector2f(100, 50), "Undo");
    Button delete_button(sf::Vector2f(BOARD_WIDTH + 25, 100), sf::Vector2f(100, 50), "Delete");
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
    delete_button.setFont(m_font);
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
    widgets_manager.add(&delete_button);
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
                        board_controller.onMouseClick(sf::Mouse::Left);
                    }
                    else if(delete_button.isMouseOver(m_renderWindow))
                    {
                        board_controller.onDeleteButton();
                    }
                    else if(num1_button.isMouseOver(m_renderWindow))
                    {
                        board_controller.onScreenNum(1);
                    }
                    else if(num2_button.isMouseOver(m_renderWindow))
                    {
                        board_controller.onScreenNum(2);
                    }
                    else if(num3_button.isMouseOver(m_renderWindow))
                    {
                        board_controller.onScreenNum(3);
                    }
                    else if(num4_button.isMouseOver(m_renderWindow))
                    {
                        board_controller.onScreenNum(4);
                    }
                    else if(num5_button.isMouseOver(m_renderWindow))
                    {
                        board_controller.onScreenNum(5);
                    }
                    else if(num6_button.isMouseOver(m_renderWindow))
                    {
                        board_controller.onScreenNum(6);
                    }
                    else if(num7_button.isMouseOver(m_renderWindow))
                    {
                        board_controller.onScreenNum(7);
                    }
                    else if(num8_button.isMouseOver(m_renderWindow))
                    {
                        board_controller.onScreenNum(8);
                    }
                    else if(num9_button.isMouseOver(m_renderWindow))
                    {
                        board_controller.onScreenNum(9);
                    }
                }
                else if(event.mouseButton.button == sf::Mouse::Right)
                {
                    if(board_view.isMouseOver(m_renderWindow))
                    {
                        board_controller.onMouseClick(sf::Mouse::Right);
                    }
                }
            }
            else if(event.type == sf::Event::KeyReleased)
            {
                board_controller.onKey(event.key.code);
                
                if(event.key.code == sf::Keyboard::Escape)
                {
                    m_renderWindow.close();
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