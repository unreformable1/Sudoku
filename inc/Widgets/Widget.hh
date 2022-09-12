#pragma once

#include "IWidget.hh"



class Widget: public IWidget
{
public:
    Widget(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& text = "Widget");
    virtual bool isMouseOver(const sf::RenderWindow& render_window);
    virtual void draw(sf::RenderTarget& render_target);

    virtual void setText(const std::string& text);
    virtual void setFont(const sf::Font& font);
    virtual void setTextSize(unsigned int size);
    virtual void setTextColor(const sf::Color& color);
    virtual void setBgColor(const sf::Color& color);


protected:
    virtual void centerText();


protected:
    sf::RectangleShape m_bg;
    sf::Text m_text;
};

Widget::Widget(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& text)
{
    m_bg.setFillColor(sf::Color::White);
    m_bg.setPosition(pos);
    m_bg.setSize(size);

    m_text.setFillColor(sf::Color::Black);
    m_text.setString(text);
}

bool Widget::isMouseOver(const sf::RenderWindow& render_window)
{
    const sf::Vector2i& mouse_pos = sf::Mouse::getPosition(render_window);
    
    if(m_bg.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)))
        return true;
    return false;
}

void Widget::draw(sf::RenderTarget& render_target)
{
    render_target.draw(m_bg);
    render_target.draw(m_text);
}

void Widget::setText(const std::string& text)
{
    m_text.setString(text);
    centerText();
}

void Widget::setFont(const sf::Font& font)
{
    m_text.setFont(font);
    centerText();
}

void Widget::setTextSize(unsigned int size)
{
    m_text.setCharacterSize(size);
    centerText();
}

void Widget::setTextColor(const sf::Color& color)
{
    m_text.setFillColor(color);
}

void Widget::setBgColor(const sf::Color& color)
{
    m_bg.setFillColor(color);
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