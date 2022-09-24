#include "WidgetsManager.hh"



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