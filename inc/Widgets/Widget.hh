#pragma once

#include <SFML/Graphics.hpp>



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