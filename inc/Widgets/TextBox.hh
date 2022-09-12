#pragma once

#include "Widget.hh"



class TextBox: public Widget
{
public:
    TextBox(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& text = "Text here");

    bool hasFocus() const { return m_hasFocus; }
    void setFocus(bool focus) { m_hasFocus = focus; }


private:
    bool m_hasFocus = false;
};

TextBox::TextBox(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& text)
:   Widget(pos, size, text)
{

}