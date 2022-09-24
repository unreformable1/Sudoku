#include "Widget.hh"



Widget::Widget()
{
    m_bg.setFillColor(sf::Color::White);

    m_text.setFillColor(sf::Color::Black);
}

Widget::~Widget()
{
    deleteRecursive(this);
}

bool Widget::contains(const sf::Vector2i& point) const
{
    if(!m_enabled)
        return false;

    if(m_bg.getGlobalBounds().contains(static_cast<sf::Vector2f>(point)))
        return true;
    return false;
}

void Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    drawRecursive(this, target, states);
}

void Widget::setTextFont(const sf::Font& font)
{
    setTextFontRecursive(this, font);
}

void Widget::setTextString(const std::string& string)
{
    m_text.setString(string);
    centerText();
}

void Widget::setTextCharacterSize(unsigned int size)
{
    m_text.setCharacterSize(size);
    centerText();
}

void Widget::centerText()
{
    const sf::FloatRect& text_bounds = m_text.getLocalBounds();
    const sf::Vector2f& widget_pos = m_bg.getPosition();
    const sf::Vector2f& widget_size = m_bg.getSize();
    const float& text_x = widget_pos.x + widget_size.x/2 - text_bounds.left - text_bounds.width/2;
    const float& text_y = widget_pos.y + widget_size.y/2 - text_bounds.top - text_bounds.height/2;
    m_text.setPosition(text_x, text_y);
}

void Widget::deleteRecursive(Widget* widget)
{
    for(Widget* child : widget->getChildren())
    {
        child->deleteRecursive(child);
        delete child;
    }
}

void Widget::drawRecursive(const Widget* widget, sf::RenderTarget& target, sf::RenderStates states) const
{
    if(!widget->getVisible())
        return;
    
    target.draw(m_bg);
    target.draw(m_text);
    for(Widget* child : widget->getChildren())
    {
        child->drawRecursive(child, target, states);
    }
}

void Widget::setTextFontRecursive(Widget* widget, const sf::Font& font)
{
    m_text.setFont(font);
    widget->centerText();
    for(Widget* child : widget->getChildren())
    {
        child->setTextFontRecursive(child, font);
    }
}