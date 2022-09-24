#pragma once

#include "Widget.hh"

#include <vector>


class WidgetsManager
{
public:
    void add(Widget* widget);
    void draw(sf::RenderTarget& target);
    void setFont(const sf::Font& font);


private:
    std::vector<Widget*> m_widgets;
};