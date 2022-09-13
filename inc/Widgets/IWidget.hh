#pragma once

#include <SFML/Graphics.hpp>



class IWidget
{
public:
    virtual ~IWidget() = default;
    virtual bool isMouseOver(const sf::RenderWindow& render_window) = 0;
    virtual void draw(sf::RenderTarget& render_target) = 0;
};