
#pragma once

#include <SFML/Graphics.hpp>
#include "../Player/Character.h"
#include "../Player/Player.h"
#include <iostream>

namespace Game::Entity::Character::Enemy{
    class Enemy : public Character{

    protected:

        Player::Player *m_player;

        const float m_AnimationTimeAttack;
        float m_timeAttack;
        
        float m_timeMove;
        short m_move;


        sf::SoundBuffer m_DamageBufferSound;
        sf::Sound m_soundDamage;

        virtual void bootSound(){
            //
        };

        virtual void bootAnimation() = 0;
        void updateAnimation() override;

        virtual void moveEnemy();

        virtual void updateAttack();
        void updateTimeDamage() override;

        nlohmann::ordered_json save() override;
        
        void bootLifeBar() override;

    public:

        Enemy(sf::Vector2f pos, sf::Vector2f size, const float speed, Player::Player *player,const float animationTimeAttack, IDs::IDs ID, const float animationTimeGetDamage, const float animationTimeDeath, float damage, Weapon::Weapon* weapon);
        ~Enemy() override;

        void chasePlayer(sf::Vector2f playerPos, sf::Vector2f enemyPos);
        void randomMove();
        
        void collision(Entity* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.f,0.f)) override;
        
        void update() override;
    };

}
