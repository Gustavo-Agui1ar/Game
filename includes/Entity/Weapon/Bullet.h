
#pragma once

#include "Weapon.h"
#include "../includes/Animator/Animation.h"

#define BULLET_SIZE 25.0f
#define BULLET_SIZE_PLAYER 8.0f

namespace Game::Entity::Weapon{
    
    class Bullet : public Weapon {

        private:

            bool m_direction;
            bool m_collision;

            sf::Vector2f m_speed;
            Animator::Animation m_animation;

            void updateAnimation();
            void checkOutScreen();
            void updatePosition();

        public:

            explicit Bullet( IDs::IDs ID);
            explicit Bullet( nlohmann::ordered_json atributos);
            ~Bullet() override;

            void inicializarAnimacao();
            void setDirection(bool direction);
            void setSpeed(sf::Vector2f speed);
            void setCollision(bool colision);
            const bool getCollision();

            nlohmann::ordered_json save() override;

            void collision(Entity* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f)) override;

            void draw() override;
            void update() override;
    };
}