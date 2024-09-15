
#pragma once

#include <SFML/Graphics.hpp>
#include "Ente.h"

namespace Game::Entity{


    class Entity : public Ente{

    protected:

        sf::RectangleShape m_body;
        sf::Vector2f m_position;
        sf::Vector2f m_size;
    
        bool m_canRemove;

    public:

        Entity(const sf::Vector2f size,const IDs::IDs ID, const sf::Vector2f position = {0,0});
        ~Entity() override;

        sf::RectangleShape getBody();
        
        void setSize(const sf::Vector2f size);
        
        sf::Vector2f getSize();

        nlohmann::ordered_json saveEntity();
        virtual nlohmann::ordered_json save() = 0;

        void setPosition(sf::Vector2f position);

        sf::Vector2f getPosition();

        virtual void collision(Entity* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.f,0.f)) = 0;
        
        const bool getRemove();
        void remove();

        virtual void update() = 0;
        void draw() override;
    };
}


