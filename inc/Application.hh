#pragma once

#include <SFML/Graphics.hpp>


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