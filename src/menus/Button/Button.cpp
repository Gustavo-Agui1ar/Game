
#include "../includes/menus/Button/Button.h"

namespace Game::Menu::Button{       

    Button::Button(const sf::Vector2f size, const sf::Vector2f pos, const IDs::IDs ID, const float timeToChange):
    Ente(ID), m_texture(new sf::Texture()), m_position(pos), m_size(size), m_timeToChange(timeToChange), m_timeElapsed(0.0f)
    {
        m_box.setPosition(pos);
        m_box.setSize(size);
    }

    Button::~Button()
    {
        if(m_texture)
            delete m_texture;
        m_texture = nullptr;
    }

    
    void Button::updatePositionButton(const sf::Vector2f pos)
    {
        m_position = pos;
        m_box.setPosition(pos);
    }

    const sf::Vector2f Button::getPos()
    {
        return m_box.getPosition();        
    }

    void Button::setTexture(sf::Texture* texture)
    {
        m_texture = texture;
        m_box.setTexture(m_texture);
    }

    
    void Button::draw()
    {
        m_graphic->drawElement(m_box);
    }

    void Button::updateAnimation()
    {
        //nothing to do
    }

    sf::RectangleShape Button::getBox()
    {
        return m_box;
    }
}
