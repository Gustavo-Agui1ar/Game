#include "../includes/Entity/Player/Character.h"
#include <iostream>
#include <math.h>

namespace Game::Entity::Character{

    Character::~Character() = default;

    Character::Character(const sf::Vector2f pos, const sf::Vector2f size, const float speed, const IDs::IDs ID, const float animationTimeGetDamage, const float animationTimeDeath, const float damage):
    Entity(size,ID, pos),m_animation(&m_body),m_speed(sf::Vector2f(speed,0)) , m_maxSpeed(speed),
        m_moving(false),m_direction(false), dt(0.0f), m_maxLife(100.0f), m_life(100.0f), m_animationTimeGetDamage(animationTimeGetDamage),
        m_animationTimeDeath(animationTimeDeath), m_timeDeath(0.0f), m_timeDamage(0.0f), m_dying(false), m_getDamage(false), m_attaking(false)
    {
        m_damage = damage;
        m_weapon = nullptr;
    }

    void Character::stop()
    {
        m_moving = false;
    }

    void Character::walk(bool direction)
    {
        m_direction = direction;
        m_moving = true;
    }

    void Character::updatePosition()
    {
        dt = m_graphic->getTempo();

        sf::Vector2f ds(0.f,0.f);
        
        if(m_moving && !m_dying && !m_getDamage){
            ds.x = m_speed.x * dt;

        if(m_direction)
            ds.x *= -1;
        }

        //gravity effect
        const float Vy = m_speed.y;
        m_speed.y = m_speed.y + GRAVITY * dt;
        ds.y = Vy * dt + (GRAVITY * dt * dt) / 2.0f;

        setPosition(sf::Vector2f(m_position.x + ds.x, m_position.y + ds.y ));

        m_speed.x = m_maxSpeed;

        updateTimeDamage();

        draw();
    }

    sf::Vector2f Character::getSpeed()
    {
        return m_speed;
    }

    void Character::setMaxSpeed(sf::Vector2f speed)
    {
        m_speed = speed;
    }

    void Character::attack()
    {
        m_attaking = true;
        m_moving = false;
    }

    void Character::stopAttack()
    {
        m_attaking = false;
        m_weapon->setPosition(sf::Vector2f(-1000.0f, -1000.f));
    }

    void Character::updateLifeBar()
    {
        auto lifePosition(sf::Vector2f(m_position.x + m_size.x/2.0f - m_body.getSize().x/2.0f, m_position.y - 20.0f));
        m_lifeBar.setPosition(lifePosition);
        m_lifeBar.setSize((sf::Vector2f((m_life/m_maxLife)* LIFE_BAR_X, LIFE_BAR_Y)));
    }

    void Character::draw()
    {
        m_graphic->desenhaElemento(m_lifeBar);
        m_graphic->desenhaElemento(m_body);
        
    }

    const bool Character::getDie()
    {
        return m_dying;
    }
    
    const bool Character::getDirection()
    {
        return m_direction;
    }
    
    void Character::takeDamage(const float damage)
    {
        if(!m_getDamage)
        {
            m_getDamage = true;
            m_attaking = false;
            m_moving = false;
            m_life -= damage;
            if(m_life <= 0.0f)
            {
                m_dying = true;
                m_getDamage = false;
                m_life = 0.0f;
                
                if(m_weapon != nullptr)
                {
                    m_weapon->remove();
                }
            }
            m_timeDamage = 0.0f;
        }
    }

    void Character::updateTimeDamage()
    {
        m_timeDamage += m_graphic->getTempo();

        if(m_getDamage && m_timeDamage > m_animationTimeGetDamage)
        {
            m_getDamage = false;
            m_timeDamage = 0.0f;
        }
        
    }

    void Character::setWeapon(Weapon::Weapon* weapon)
    {
        m_weapon = weapon;
        m_weapon->setDamage(m_damage);
        m_weapon->setSize(m_size);
    }

    nlohmann::ordered_json Character::saveCharacter()
    {
        nlohmann::ordered_json json = saveEntity();

        json["speed"] = {{"x", m_speed.x}, {"y", m_speed.y}};
        json["deathTime"] = m_timeDeath;
        json["InDamage"] = m_getDamage;
        json["timeDamage"] = m_timeDamage;
        json["dying"] = m_dying;
        json["attacking"] = m_attaking;
        json["moving"] = m_moving;
        json["direction"] = m_direction;
        json["damage"] = m_damage;
        json["life"] = m_life;
        json["dt"] = dt;

        return json;
    }

    bool Character::checkInsideScreen()
    {
        sf::Vector2f screenCenter = m_graphic->getCamera().getCenter();

        if(sf::Vector2f screenSize = m_graphic->getTamJanela(); 
            m_position.x < screenCenter.x - screenSize.x/2.0f || m_position.x > screenCenter.x + screenSize.x/2.0f ||
            m_position.y < screenCenter.y - screenSize.y/2.0f || m_position.y > screenCenter.y + screenSize.y/2.0f  )
        {
            return false;
        }

        return true;
    }

    void Character::setWeaponDamage(float damage) {
        m_weapon->setDamage(damage);
    }

    void Character::setMoving(bool moving) {
        m_moving = moving;
    }

    void Character::setAttacking(bool attacking) {
        m_attaking = attacking;
    }
    
    bool Character::getAttacking() {
       return m_attaking;
    }
}