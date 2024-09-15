
#pragma once 

#include "../includes/gerenciador/gerenciadorGrafico.h"
#include "../includes/Entity/Entity.h"

namespace Game::Entity::Obstacle{
    class House : public Entity{
    
        private:

            sf::Texture m_texture;
        
        public:

            House(const sf::Vector2f size,const IDs::IDs ID, const sf::Vector2f position = {0,0});
            ~House() override;

            void update() override;
            nlohmann::ordered_json save() override;
            void collision(Entity* otherEntity, sf::Vector2f ds = sf::Vector2f(0.f,0.f)) override;
            void setTexture(const char* pathTexture);
    };
}
