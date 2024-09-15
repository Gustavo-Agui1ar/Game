
#pragma once

#include "../includes/Entity/Entity.h"

namespace Game::Entity::Weapon{
    class Weapon : public Entity{

        protected:

        float m_damage;
        
        public:

        explicit Weapon(nlohmann::ordered_json atributos);
        explicit Weapon(IDs::IDs ID);
        ~Weapon() override;

        void setDamage(const float damage);
        const float getDamage();
        
        void collision(Entity* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f)) override;

        nlohmann::ordered_json save() override;
        nlohmann::ordered_json saveWeapon();
        
        void update() override;
        void draw() override;
    };

}