#pragma once

#include "Widget.hh"



class TextBox: public Widget
{
public:
    TextBox(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& text = "TextBox");
};

TextBox::TextBox(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& text)
{
    setPosition(pos);
    setSize(size);
    setTextString(text);
}