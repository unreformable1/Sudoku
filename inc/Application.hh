#pragma once

#include "SudokuBoard.hh"
#include "SudokuBoardGenerator.hh"

#define WIN_WIDTH 600
#define WIN_HEIGHT 600


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
    SudokuBoardGenerator generator;
    SudokuBoard board;

    generator.generate(board);

    m_renderWindow.clear();
    board.draw(m_renderWindow, m_font, sf::Vector2f(600, 600));
    m_renderWindow.display();
    
    while(m_renderWindow.isOpen())
    {
        sf::Event event;
        while(m_renderWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                m_renderWindow.close();
            }
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    m_renderWindow.close();
                }
            }
            else if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::G)
                {
                    generator.generate(board);

                    m_renderWindow.clear();
                    board.draw(m_renderWindow, m_font, sf::Vector2f(600, 600));
                    m_renderWindow.display();
                }
            }
        }
    }
}

void Application::initRenderWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    m_renderWindow.create(sf::VideoMode(600, 600), "Sudoku Puzzle Game", sf::Style::Close, settings);
    m_renderWindow.setVerticalSyncEnabled(true);
    sf::VideoMode screen = sf::VideoMode::getDesktopMode();
    m_renderWindow.setPosition(sf::Vector2i(screen.width/2 - WIN_WIDTH/2, screen.height/2 - WIN_HEIGHT/2));
}

void Application::initFont()
{
    m_font.loadFromFile("../fonts/arial/arial.ttf");
}