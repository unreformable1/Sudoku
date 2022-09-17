#pragma once

#include "IWidget.hh"

#include <vector>


class WidgetsManager
{
public:
    void add(IWidget* widget);
    void draw(sf::RenderTarget& render_target);


private:
    std::vector<IWidget*> m_widgets;
};

void WidgetsManager::add(IWidget* widget)
{
    m_widgets.emplace_back(widget);
}

void WidgetsManager::draw(sf::RenderTarget& render_target)
{
    for(IWidget* widget : m_widgets)
    {
        widget->draw(render_target);
    }
}