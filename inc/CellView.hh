#pragma once

#include "TextBox.hh"




class CellView: public TextBox
{
public:
    CellView(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& text = "Text here");

    
};

CellView::CellView(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& text)
:   TextBox(pos, size, text)
{

}