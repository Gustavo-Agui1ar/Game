
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include "../includes/Entity/Weapon/Bullet.h"
#include "../includes/Entity/Player/Skils/Dash.h"
#include "../includes/Entity/Player/Skils/Rage.h"
#include "../includes/Entity/Player/Skils/Stamina.h"
#include "../includes/Entity/Player/Skils/FireBall.h"

#include "Character.h"
#include <math.h>

#define PLAYER_LIFE_BAR_X 350.0f
#define PLAYER_LIFE_BAR_Y 20.0f

#define SIZE_PLAYER_X 30.0f
#define SIZE_PLAYER_Y 60.0f

#define PLAYER_SPEED_X 250.0f

#define QTD_JUMP 2
#define JUMP_SIZE 120.f

#define PATH_SOUND_ATTACK "Sounds/Sword-Slash.wav"

#define ANIMATION_DEATH_PLAYER  1.8f
#define PLAYER_TIME_GETDAMAGE 0.5f
#define TIME_DAMAGE_PLAYER 0.6f
#define PLAYER_DAMAGE 20.0f

namespace Game {
    namespace Listener{
        class ListenerJogador;
    }
    namespace Entity::Character::Player{

        class Player : public Character {
        private:

            Skils::Dash m_dash;
            Skils::Rage m_rage;
            Skils::Stamina m_stamina;
            Skils::FireBall m_fireball;
            
            bool m_onFloor;
            int  m_qtdJump;

            void bootLifeBar() override;
            void bootAnimation();
            void bootSound();
                        
            void updateLifeBar() override;
            void updateAnimation() override;
            void selectAnimation(std::string complement);
            void updatePosition() override;
            void update() override;

            sf::RectangleShape m_lifeTube;
            const float m_timeAnimationAttack;
            float m_timeAttack;
            
            Listener::ListenerJogador* m_observerPlayer;
            
            sf::Sound m_soundAttack;
            sf::SoundBuffer m_soundAttackBuffer;

        public:
            
            Player(const sf::Vector2f pos, Weapon::Weapon* weapon = nullptr, Weapon::Bullet* bullet = nullptr);
            explicit Player(nlohmann::ordered_json atributos);
            ~Player() override;
            
            bool consumeStamina(float qtdUso);
            void stopDash();
            void doDash();
            void takeDamage(const float damage) override;
            
            void changeObserverState(const bool ative);
                        
            void collision(Entity* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.f,0.f)) override;
            
            bool getOnFloor() const;
            
            void canJump();
            void jump();

            nlohmann::ordered_json save() override;

            void updateWeapon();
            void setBullet(Weapon::Bullet* bullet);
            void trhowBullet();
            
            void draw() override;
            void searchIteractions();
            void activeRage();
            void increaseRage(float qtdRage);

        };
    }

}
