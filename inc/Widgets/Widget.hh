#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>




class Widget
{
public:
    Widget();
    ~Widget();

    virtual bool contains(const sf::Vector2i& point) const;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;
    
    
    virtual void setParent(Widget* parent) { m_parent = parent; }
    virtual void addChild(Widget* child) { m_children.emplace_back(child); }
    virtual void removeChild(int index) { m_children.erase(m_children.begin() + index); }

    virtual void setPosition(const sf::Vector2f& pos) { m_bg.setPosition(pos); }
    virtual void setSize(const sf::Vector2f& size) { m_bg.setSize(size); }
    virtual void setRotation(float rotation) { m_bg.setRotation(rotation); m_text.setRotation(rotation); }

    virtual void setBgColor(const sf::Color& color) { m_bg.setFillColor(color); }
    virtual void setBgOutlineColor(const sf::Color& color) { m_bg.setOutlineColor(color); }
    virtual void setBgOutlineThickness(float thickness) { m_bg.setOutlineThickness(thickness); }

    virtual void setTextFont(const sf::Font& font);
    virtual void setTextString(const std::string& string);
    virtual void setTextCharacterSize(unsigned int size);
    virtual void setTextColor(const sf::Color& color) { m_text.setFillColor(color);}

    virtual void setVisible(bool visible) { m_visible = visible; }
    virtual void setEnabled(bool enabled) { m_enabled = enabled; }
    virtual void setFocus(bool focus) { m_focus = focus; }


    virtual const Widget* getParent() const { return m_parent; }
    virtual Widget* getParent() { return m_parent; }
    virtual const Widget* getChild(int index) const { return m_children[index]; }
    virtual Widget* getChild(int index) { return m_children[index]; }
    virtual const std::vector<Widget*>& getChildren() const { return m_children; }
    virtual std::vector<Widget*>& getChildren() { return m_children; }
    virtual int getChildrenCount() const { return m_children.size(); }

    virtual const sf::Vector2f& getPosition() const { return m_bg.getPosition(); }
    virtual const sf::Vector2f& getSize() const { return m_bg.getSize(); }
    virtual const float getRotation() const { return m_bg.getRotation(); }

    virtual const sf::Color& getBgColor() const { return m_bg.getFillColor(); }
    virtual const sf::Color& getBgOutlineColor() const { return m_bg.getOutlineColor(); }
    virtual float getBgOutlineThickness() const { return m_bg.getOutlineThickness(); }

    virtual const sf::Font* getTextFont() const { return m_text.getFont(); }
    virtual std::string getTextString() const { return m_text.getString(); }
    virtual unsigned int getTextCharacterSize() const { return m_text.getCharacterSize(); }
    virtual const sf::Color& getTextColor() const { return m_text.getFillColor(); }

    virtual bool getVisible() const { return m_visible; }
    virtual bool getEnabled() const { return m_enabled; }
    virtual bool getFocus() const { return m_focus; }


protected:
    virtual void centerText();


private:
    void deleteRecursive(Widget* widget);
    void drawRecursive(const Widget* widget, sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates()) const;
    void setTextFontRecursive(Widget* widget, const sf::Font& font);

protected:
    sf::RectangleShape m_bg;
    sf::Text m_text;

    Widget* m_parent = nullptr;
    std::vector<Widget*> m_children;

    bool m_visible = true;
    bool m_enabled = true;
    bool m_focus = false;
};

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