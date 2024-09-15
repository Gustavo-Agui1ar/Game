
#pragma once

#include "Enemy.h"

#define SKELETON_TIME_ANIMATION_DEATH 1.25f
#define SIZE_SKELETON_X 30.0f
#define SIZE_SKELETON_Y 60.0f
#define SKELETON_SPEED 50.0f
#define SKELETON_TIME_GET_DAMAGE 0.6f
#define SKELETON_TIME_ATTACK 1.0f
#define SKELETON_DAMAGE 10.0F

#define SOUND_SKELETON_GET_DAMAGE "Sounds/Skeleton-Sound-Effect.wav"


namespace Game::Entity::Character::Enemy{
    class Skeleton : public Enemy{
        
    private:

        void bootAnimation() override;
        void bootSound() override;
        
        void updateAnimation() override;
        void updateAttack() override;

    public:

        Skeleton(sf::Vector2f pos, Player::Player *player, Weapon::Weapon* weapon = nullptr);
        Skeleton(nlohmann::ordered_json atributos, Player::Player *player);
        ~Skeleton() override;
    };
}
