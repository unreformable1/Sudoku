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

    Button new_game(sf::Vector2f(BOARD_WIDTH + 25, 25), sf::Vector2f(175, 50), "New Game");
    Button erase_button(sf::Vector2f(BOARD_WIDTH + 25, 100), sf::Vector2f(100, 50), "Erase");
    Button hint_button(sf::Vector2f(BOARD_WIDTH + 25, 175), sf::Vector2f(100, 50), "Hint");
    Button undo_button(sf::Vector2f(BOARD_WIDTH + 25, 250), sf::Vector2f(100, 50), "Undo");

    Button num1_button(sf::Vector2f(BOARD_WIDTH + 25, 325),  sf::Vector2f(65, 65), "1");
    Button num2_button(sf::Vector2f(BOARD_WIDTH + 100, 325), sf::Vector2f(65, 65), "2");
    Button num3_button(sf::Vector2f(BOARD_WIDTH + 175, 325), sf::Vector2f(65, 65), "3");
    Button num4_button(sf::Vector2f(BOARD_WIDTH + 25, 400),  sf::Vector2f(65, 65), "4");
    Button num5_button(sf::Vector2f(BOARD_WIDTH + 100, 400), sf::Vector2f(65, 65), "5");
    Button num6_button(sf::Vector2f(BOARD_WIDTH + 175, 400), sf::Vector2f(65, 65), "6");
    Button num7_button(sf::Vector2f(BOARD_WIDTH + 25, 475),  sf::Vector2f(65, 65), "7");
    Button num8_button(sf::Vector2f(BOARD_WIDTH + 100, 475), sf::Vector2f(65, 65), "8");
    Button num9_button(sf::Vector2f(BOARD_WIDTH + 175, 475), sf::Vector2f(65, 65), "9");

    WidgetsManager widgets_manager;
    
    widgets_manager.add(&board_view);

    widgets_manager.add(&new_game);
    widgets_manager.add(&erase_button);
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

    // bool value to determine if should check for sudoku completition (look below event loop)
    bool was_cell_added = false;

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
                    else if(new_game.contains(mouse_pos))
                    {
                        board_controller.generateBoard();
                    }
                    else if(erase_button.contains(mouse_pos))
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
                        was_cell_added = true;
                    }
                    else if(num2_button.contains(mouse_pos))
                    {
                        board_controller.setCell(2);
                        was_cell_added = true;
                    }
                    else if(num3_button.contains(mouse_pos))
                    {
                        board_controller.setCell(3);
                        was_cell_added = true;
                    }
                    else if(num4_button.contains(mouse_pos))
                    {
                        board_controller.setCell(4);
                        was_cell_added = true;
                    }
                    else if(num5_button.contains(mouse_pos))
                    {
                        board_controller.setCell(5);
                        was_cell_added = true;
                    }
                    else if(num6_button.contains(mouse_pos))
                    {
                        board_controller.setCell(6);
                        was_cell_added = true;
                    }
                    else if(num7_button.contains(mouse_pos))
                    {
                        board_controller.setCell(7);
                        was_cell_added = true;
                    }
                    else if(num8_button.contains(mouse_pos))
                    {
                        board_controller.setCell(8);
                        was_cell_added = true;
                    }
                    else if(num9_button.contains(mouse_pos))
                    {
                        board_controller.setCell(9);
                        was_cell_added = true;
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

                    was_cell_added = true;
                }
                else if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
                {
                    board_controller.moveTo(SudokuBoardController::Direction::Up);
                }
                else if(event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
                {
                    board_controller.moveTo(SudokuBoardController::Direction::Down);
                }
                else if(event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
                {
                    board_controller.moveTo(SudokuBoardController::Direction::Left);
                }
                else if(event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
                {
                    board_controller.moveTo(SudokuBoardController::Direction::Right);
                }
                else if(event.key.code == sf::Keyboard::H)
                {
                    std::cout << std::endl;
                    std::cout << "AVAILABLE KEYBOARD COMMANDS:" << std::endl;
                    std::cout << "Arrows/WASD - moving over the board" << std::endl;
                    std::cout << "LMB + (1-9) - place digit on the board" << std::endl;
                    std::cout << "RMB - delete clicked cell" << std::endl;
                }
            }

            // After completing sudoku
            if(was_cell_added)
            {
                was_cell_added = false;

                if(!board.full() || !board.valid())
                    return;
                
                // Endgame button
                Button exit_button(sf::Vector2f(BOARD_WIDTH/2 - 125, BOARD_HEIGHT/2 - 25), sf::Vector2f(250, 50), "Congratulations!");
                exit_button.setBgColor(sf::Color(50, 50, 50, 200));
                exit_button.setTextColor(sf::Color::Red);
                exit_button.setTextFont(m_font);
                exit_button.draw(m_renderWindow);
                m_renderWindow.display();

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
                                if(exit_button.contains(mouse_pos))
                                {
                                    m_renderWindow.close();
                                }
                            }
                        }
                        else if(event.type == sf::Event::KeyReleased)
                        {
                            if(event.key.code == sf::Keyboard::Escape)
                            {
                                m_renderWindow.close();
                            }
                        }
                    }
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