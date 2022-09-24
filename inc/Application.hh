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