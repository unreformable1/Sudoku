#include "Button.hh"



Button::Button(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& text)
{
    setPosition(pos);
    setSize(size);
    setTextString(text);
    setBgOutlineThickness(1);
    setBgOutlineColor(sf::Color::Black);
}