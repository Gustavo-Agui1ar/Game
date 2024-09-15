
#pragma once

#include <SFML/Graphics.hpp>
#include "../includes/Entity/Entity.h"
#include "../includes/Animator/Animation.h"
#include "../Weapon/Weapon.h"


#define GRAVITY 1200.0f

#define LIFE_BAR_X 60.0f
#define LIFE_BAR_Y 6.0f

namespace Game::Entity::Character {
    class Character : public Entity {

    protected:

        Animator::Animation m_animation;

        virtual void bootLifeBar() = 0;

        virtual void updateAnimation() = 0;
        virtual void updateLifeBar();

        sf::Vector2f m_speed;
        const float  m_maxSpeed;
        
        bool m_moving;
        bool m_direction;
        float dt;

        sf::RectangleShape m_lifeBar;
        const float m_maxLife;
        float m_life;
        
        const float m_animationTimeGetDamage;
        const float m_animationTimeDeath;
        float m_timeDeath;
        float m_timeDamage;
        
        bool m_dying;

        bool m_getDamage;
        bool m_attaking;

        Weapon::Weapon* m_weapon;
        float m_damage;

    public:

        Character(const sf::Vector2f pos, const sf::Vector2f size, const float speed,IDs::IDs ID,const float animationTimeGetDamage, const float animationTimeDeath,const float damage);
        ~Character() override;

        void setMaxSpeed(sf::Vector2f speed);
        void setMoving(bool moving);
        void setWeapon(Weapon::Weapon* weapon);
        void setWeaponDamage(float damage);
        void setAttacking(bool attacking);
        bool getAttacking();

        void walk(bool direction);
        void stop();

        virtual void updateTimeDamage();
        virtual void updatePosition();

        virtual void takeDamage(const float damage);

        void stopAttack();
        void attack();

        nlohmann::ordered_json saveCharacter();
        nlohmann::ordered_json save() override = 0;

        sf::Vector2f getSpeed();
        const bool getDie();
        const bool getDirection();

        void draw() override;
        bool checkInsideScreen();
    };
}
