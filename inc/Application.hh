#pragma once

#include "Button.hh"
#include "SudokuBoardController.hh"
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
    SudokuBoard board;
    SudokuBoardView board_view(sf::Vector2f(0, 0), sf::Vector2f(BOARD_WIDTH, BOARD_HEIGHT));
    SudokuBoardController board_controller(m_renderWindow, board, board_view);


    Button delete_button(sf::Vector2f(BOARD_WIDTH + 25, 100), sf::Vector2f(100, 50), "Delete");
    Button hint_button(sf::Vector2f(BOARD_WIDTH + 25, 175), sf::Vector2f(100, 50), "Hint");
    Button undo_button(sf::Vector2f(BOARD_WIDTH + 25, 25), sf::Vector2f(100, 50), "Undo");

    Button num1_button(sf::Vector2f(BOARD_WIDTH + 25, 250),  sf::Vector2f(65, 65), "1");
    Button num2_button(sf::Vector2f(BOARD_WIDTH + 100, 250), sf::Vector2f(65, 65), "2");
    Button num3_button(sf::Vector2f(BOARD_WIDTH + 175, 250), sf::Vector2f(65, 65), "3");
    Button num4_button(sf::Vector2f(BOARD_WIDTH + 25, 325),  sf::Vector2f(65, 65), "4");
    Button num5_button(sf::Vector2f(BOARD_WIDTH + 100, 325), sf::Vector2f(65, 65), "5");
    Button num6_button(sf::Vector2f(BOARD_WIDTH + 175, 325), sf::Vector2f(65, 65), "6");
    Button num7_button(sf::Vector2f(BOARD_WIDTH + 25, 400),  sf::Vector2f(65, 65), "7");
    Button num8_button(sf::Vector2f(BOARD_WIDTH + 100, 400), sf::Vector2f(65, 65), "8");
    Button num9_button(sf::Vector2f(BOARD_WIDTH + 175, 400), sf::Vector2f(65, 65), "9");

    WidgetsManager widgets_manager;
    
    widgets_manager.add(&board_view);

    widgets_manager.add(&delete_button);
    widgets_manager.add(&hint_button);
    widgets_manager.add(&undo_button);
    widgets_manager.add(&num1_button);
    widgets_manager.add(&num2_button);
    widgets_manager.add(&num3_button);
    widgets_manager.add(&num4_button);
    widgets_manager.add(&num5_button);
    widgets_manager.add(&num6_button);
    widgets_manager.add(&num7_button);
    widgets_manager.add(&num8_button);
    widgets_manager.add(&num9_button);


    m_renderWindow.clear(sf::Color(140, 140, 140));
    widgets_manager.setFont(m_font);
    widgets_manager.draw(m_renderWindow);

    m_renderWindow.display();

    std::cout << std::endl << "Click H to see available options" << std::endl;

    board_controller.generateBoard();

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
                const sf::Vector2i& mouse_pos = sf::Mouse::getPosition(m_renderWindow);

                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    if(board_view.contains(mouse_pos))
                    {
                        board_controller.highlightClickedCell(mouse_pos);
                    }
                    else if(delete_button.contains(mouse_pos))
                    {
                        board_controller.deleteCell();
                    }
                    else if(hint_button.contains(mouse_pos))
                    {
                        board_controller.getHint();
                    }
                    else if(undo_button.contains(mouse_pos))
                    {
                        board_controller.undoAction();
                    }
                    else if(num1_button.contains(mouse_pos))
                    {
                        board_controller.setCell(1);
                    }
                    else if(num2_button.contains(mouse_pos))
                    {
                        board_controller.setCell(2);
                    }
                    else if(num3_button.contains(mouse_pos))
                    {
                        board_controller.setCell(3);
                    }
                    else if(num4_button.contains(mouse_pos))
                    {
                        board_controller.setCell(4);
                    }
                    else if(num5_button.contains(mouse_pos))
                    {
                        board_controller.setCell(5);
                    }
                    else if(num6_button.contains(mouse_pos))
                    {
                        board_controller.setCell(6);
                    }
                    else if(num7_button.contains(mouse_pos))
                    {
                        board_controller.setCell(7);
                    }
                    else if(num8_button.contains(mouse_pos))
                    {
                        board_controller.setCell(8);
                    }
                    else if(num9_button.contains(mouse_pos))
                    {
                        board_controller.setCell(9);
                    }
                }
                else if(event.mouseButton.button == sf::Mouse::Right)
                {
                    if(board_view.contains(mouse_pos))
                    {
                        board_controller.highlightClickedCell(mouse_pos);
                        board_controller.deleteCell();
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
                    // Transform sf::Keyboard::Key enum value to (1-9) digit
                    int digit = static_cast<int>(event.key.code) - 26;
                    board_controller.setCell(digit);
                }
                else if(event.key.code == sf::Keyboard::Up)
                {
                    board_controller.moveTo(SudokuBoardController::Direction::Up);
                }
                else if(event.key.code == sf::Keyboard::Down)
                {
                    board_controller.moveTo(SudokuBoardController::Direction::Down);
                }
                else if(event.key.code == sf::Keyboard::Left)
                {
                    board_controller.moveTo(SudokuBoardController::Direction::Left);
                }
                else if(event.key.code == sf::Keyboard::Right)
                {
                    board_controller.moveTo(SudokuBoardController::Direction::Right);
                }
                else if(event.key.code == sf::Keyboard::G)
                {
                    board_controller.generateBoard();
                }
                else if(event.key.code == sf::Keyboard::S)
                {
                    board_controller.solveBoard();
                }
                else if(event.key.code == sf::Keyboard::C)
                {
                    board_controller.clearBoard();
                }
                else if(event.key.code == sf::Keyboard::N)
                {
                    board_controller.displaySolutions();
                }
                else if(event.key.code == sf::Keyboard::H)
                {
                    std::cout << std::endl;
                    std::cout << "AVAILABLE KEY COMMANDS:" << std::endl;
                    std::cout << "Arrows - moving over the board" << std::endl;
                    std::cout << "LMB + (1-9) - place digit on the board" << std::endl;
                    std::cout << "RMB - delete clicked cell" << std::endl;
                    std::cout << "G - generate random board (may take up to over 15 sec)" << std::endl;
                    std::cout << "S - solve the board" << std::endl;
                    std::cout << "C - clear the board" << std::endl;
                    std::cout << "N - compute number of solutions" << std::endl;
                }
            }
            // board has to be full and valid so its win
            // some notes:
            // - checking must only occur while user is putting number on board (?when input manager states number is added?)
            // - after win plays some animation
            // - pops up window with new game and shows game time
            /* if(board.full() && board.valid())
                std::cout << "yeee"; */
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