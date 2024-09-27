
#pragma once

#include "../includes/Entity/Ente.h"

namespace Game::Menu::Button{
    class Button : public Ente{

    protected:
        
        sf::RectangleShape m_box;
        sf::Texture* m_texture;
        
        sf::Vector2f m_position;
        sf::Vector2f m_size;

        const float m_timeToChange;
        float m_timeElapsed;

    public:

        Button(const sf::Vector2f size, const sf::Vector2f pos, const IDs::IDs ID, const float timeToChange = 0.0f);
        ~Button() override;

        void draw() override;

        virtual void updatePositionButton(const sf::Vector2f pos);
        virtual void updateAnimation();

        void setTexture(sf::Texture* texture);

        sf::RectangleShape getBox();
        const sf::Vector2f getPos();

    };
}