
#pragma once

#include "../Player/Character.h"
#include "Obstacle.h"

namespace Game::Entity::Obstacle{
    class Platform : public Obstacle{

    public:
        
        Platform(sf::Vector2f pos, sf::Vector2f tam, IDs::IDs IDplataforma, IDs::IDs IDtextura);
        Platform(nlohmann::ordered_json atributos, IDs::IDs IDplataforma, IDs::IDs IDtextura);
        ~Platform() override;

        void collision(Entity* otherEntity, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f)) override;
        
        nlohmann::ordered_json save() override;
        
        void update() override;
    };
}
