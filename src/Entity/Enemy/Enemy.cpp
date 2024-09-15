
#include "../includes/Entity/Enemy/Enemy.h"
#include <stdlib.h>
#include <random>
#include <algorithm>
#include <time.h>
#include <cmath>

#define VEL_INIMIGO_X 5.f
#define VEL_INIMIGO_Y 5.f

#define RAIO_DE_VISAO_X 200.0f
#define RAIO_DE_VISAO_Y 200.0f

namespace Game::Entity::Character::Enemy{

    Enemy::Enemy(sf::Vector2f pos, sf::Vector2f size, const float speed, Player::Player *player,const float animationTimeAttack ,IDs::IDs ID, const float animationTimeGetDamage, const float animationTimeDeath, float damage, Weapon::Weapon* weapon):
    Character(pos,size,speed,ID, animationTimeGetDamage, animationTimeDeath, damage),m_AnimationTimeAttack(animationTimeAttack)
    {
        m_player = player;
        m_timeMove = 0.0f;
        m_timeAttack = 0.0f;

        srand(time(NULL));
        m_move = rand()%3;

        bootLifeBar();

        if(weapon != nullptr)
            setWeapon(weapon);
    }

    void Enemy::chasePlayer(sf::Vector2f posPlayer, sf::Vector2f posEnemy)
    {
        if(posPlayer.x - posEnemy.x > 0.0f)
            walk(false);
        else
            walk(true);
    }

    void Enemy::randomMove()
    {
        if(m_timeMove > 1.5f){
            m_move = rand()%3;
            if(m_move == 0)
                walk(false);
            else if(m_move == 1)
                walk(true);
            else
                stop();
            m_timeMove = 0.0f;
        }
    }

    void Enemy::update()
    {
        moveEnemy();

        m_timeMove += m_graphic->getTempo();

        updateAttack();

        updateLifeBar();

        updatePosition();

        updateAnimation();
    }

    void Enemy::updateAnimation()
    {
        if(m_dying && m_canRemove == false)
        {
            m_animation.update(m_direction, "MORRE");
            m_timeDeath += m_graphic->getTempo();
            if(m_timeDeath > m_animationTimeDeath)
            {
                remove();
                m_timeDeath = 0.0f;
                if(m_weapon != nullptr)
                {
                    m_weapon->remove();
                    m_weapon = nullptr;
                }
            }
        }
        else if(m_getDamage)
            m_animation.update(m_direction,"TOMADANO");
        else if(m_attaking)
            m_animation.update(m_direction,"ATACA");
        else if(m_moving)
            m_animation.update(m_direction,"ANDAR");
        else
            m_animation.update(m_direction,"PARADO");
    }

    void Enemy::moveEnemy()
    {
        if(!m_attaking && !m_dying && !m_getDamage){

            sf::Vector2f posEnemy = m_body.getPosition();
            sf::Vector2f posPlayer = m_player->getBody().getPosition();

            if(fabs(posPlayer.x - posEnemy.x) <= RAIO_DE_VISAO_X && fabs(posPlayer.y - posEnemy.y) <= RAIO_DE_VISAO_Y)
                chasePlayer(posPlayer,posEnemy);
            else
                randomMove();
        } else
            m_timeMove = 0.0f;
    }

    void Enemy::updateAttack()
    {
        if(m_attaking && !m_dying)
        {
            m_timeAttack += m_graphic->getTempo();
            if(m_timeAttack > m_AnimationTimeAttack)
            {
                m_attaking = false;
                m_timeAttack = 0.0f;
            }
        }
    }

    void Enemy::bootLifeBar()
    {
        m_lifeBar.setSize((sf::Vector2f(LIFE_BAR_X, LIFE_BAR_Y)));
        auto* texture = new sf::Texture(); 
        texture->loadFromFile("../Game/animations/Characters/Life/LifeEnemy.png");
        m_lifeBar.setTexture(texture);
    }

    Enemy::~Enemy()
    {
        if(m_lifeBar.getTexture()){
            delete(m_lifeBar.getTexture());
        }
    }

    nlohmann::ordered_json Enemy::save()
    {
        nlohmann::ordered_json json = saveCharacter();
        json["timeAttack"] = m_timeAttack;
        json["timeMove"] = m_timeMove;
        json["move"] = m_move;
        json = m_animation.saveAnimation(json);

        return json;
    }

    void Enemy::updateTimeDamage()
    {
        if(m_getDamage) {
            if(m_timeDamage > m_animationTimeGetDamage){
                m_getDamage = false;
                m_timeDamage = 0.0f;
            }
            if(m_timeDamage == 0.0f)
                m_soundDamage.play();
        }
        m_timeDamage += m_graphic->getTempo();
    }

    void Enemy::collision(Entity* outraEntidade, sf::Vector2f ds)
    {
        IDs::IDs IDent = outraEntidade->getID();

        if(IDent == IDs::IDs::player_bullet)
        {
            auto* projetil = dynamic_cast<Weapon::Bullet*>(outraEntidade);

            takeDamage(projetil->getDamage());
            projetil->setCollision(true);
        } 
    }
}