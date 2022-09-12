#pragma once

#include <SFML/Graphics.hpp>



class IWidget
{
public:
    virtual ~IWidget() = default;
    virtual bool isMouseOver(const sf::RenderWindow& render_window) = 0;
    virtual void draw(sf::RenderTarget& render_target) = 0;

    virtual void setFont(const sf::Font& font) = 0;
    virtual void setTextSize(unsigned int size) = 0;
    virtual void setTextColor(const sf::Color& color) = 0;
    virtual void setBgColor(const sf::Color& color) = 0;
};