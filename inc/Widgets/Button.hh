#pragma once

#include "Widget.hh"



class Button: public Widget
{
public:
    Button(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& text = "Button");
};