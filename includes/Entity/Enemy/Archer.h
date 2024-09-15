#pragma once

#include "Enemy.h"
#include "../includes/Entity/Weapon/Bullet.h"

#define ARCHER_TIME_ANIMATION_DEATH 1.25f
#define SIZE_ARCHER_X 30.0f
#define SIZE_ARCHER_Y 60.0f
#define ARCHER_SPEED 250.0f
#define ARCHER_TIME_GET_DAMAGE 0.6f
#define ARCHER_TIME_ATTACK 1.5f
#define ARCHER_DAMAGE 10.0F

#define ARCHER_SOUND_DAMAGE "Sounds/Skeleton-Sound-Effect.wav"


namespace Game::Entity::Character::Enemy{
    class Archer : public Enemy{
    
    private:

        void bootAnimation() override;
        void bootSound() override;
        
        void moveEnemy() override;
        void updateAnimation() override;
        void updateAttack() override;
        void escape(sf::Vector2f playerPos, sf::Vector2f enemyPos);
    
    public:

        Archer(sf::Vector2f pos, Player::Player *player, Weapon::Weapon* weapon = nullptr);
        Archer(nlohmann::ordered_json atributos, Player::Player *player);
        ~Archer() override;
    };
}
