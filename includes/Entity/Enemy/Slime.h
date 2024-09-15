
#pragma once

#include "Enemy.h"

#define SLIME_TIME_ANIMATION_DEATH 0.5F
#define SLIME_TIME_GET__DAMAGE 0.6F
#define SLIME_TIME_ATTACK 0.8F
#define SLIME_SPEED 50.0f
#define SIZE_SLIME_X 30.0f
#define SIZE_SLIME_Y 60.0f
#define SLIME_DAMAGE 5.0F

#define SLIME_SOUND_GET_DAMAGE "Sounds/Slime-Sound-Effect.wav"

namespace Game::Entity::Character::Enemy{
    class Slime : public Enemy{
    private:

        void bootAnimation() override;
        void bootSound() override;
        
        void updateAnimation() override;
        void updateAttack() override;

    public:

        Slime(sf::Vector2f pos, Player::Player *player, Weapon::Weapon* weapon = nullptr);
        Slime(nlohmann::ordered_json atributos, Player::Player *player);
        ~Slime() override;
    };
}

