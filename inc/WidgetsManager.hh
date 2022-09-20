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

void WidgetsManager::add(Widget* widget)
{
    m_widgets.emplace_back(widget);
}

void WidgetsManager::draw(sf::RenderTarget& target)
{
    for(Widget* widget : m_widgets)
    {
        widget->draw(target);
    }
}

void WidgetsManager::setFont(const sf::Font& font)
{
    for(Widget* widget : m_widgets)
    {
        widget->setTextFont(font);
    }
}