
#include "../includes/Entity/Enemy/Archer.h"

#define RAIO_DE_VISAO_X 200.0f
#define RAIO_DE_VISAO_Y 200.0f

namespace Game::Entity::Character::Enemy{

    Archer::Archer(sf::Vector2f position, Player::Player *player, Weapon::Weapon* weapon):
    Enemy(position, sf::Vector2f(SIZE_ARCHER_X, SIZE_ARCHER_Y), ARCHER_SPEED, player, ARCHER_TIME_ATTACK,
    IDs::IDs::archer, ARCHER_TIME_GET_DAMAGE, ARCHER_TIME_ANIMATION_DEATH,ARCHER_DAMAGE, weapon)
    {
        bootAnimation();
        bootSound();
    }

    Archer::Archer(nlohmann::ordered_json atributos, Player::Player* player):
    Enemy(m_position, sf::Vector2f(SIZE_ARCHER_X,SIZE_ARCHER_Y), ARCHER_SPEED, player, ARCHER_TIME_ATTACK,
    IDs::IDs::archer, ARCHER_TIME_GET_DAMAGE, ARCHER_TIME_ANIMATION_DEATH, ARCHER_DAMAGE,  nullptr)
    {
        try
        {
            auto currentPos = sf::Vector2f(atributos["position"]["x"].template get<float>(), atributos["position"]["y"].template get<float>());

            setPosition(currentPos);
            m_timeDeath = atributos["deathTime"].template get<float>();
            m_getDamage = atributos["InDamage"].template get<bool>();
            m_timeDamage = atributos["timeDamage"].template get<float>();
            m_dying = atributos["dying"].template get<bool>();
            m_attaking = atributos["attacking"].template get<bool>();
            m_moving = atributos["moving"].template get<bool>();
            m_direction = atributos["direction"].template get<bool>();
            m_damage = atributos["damage"].template get<float>();
            m_life = atributos["life"].template get<float>();
            dt = atributos["dt"].template get<float>();
            m_timeAttack = atributos["timeAttack"].template get<float>();
            m_timeMove = atributos["timeMove"].template get<float>();
            m_move = atributos["move"].template get<short>();
            
            bootAnimation();

            m_animation.setCurrentImg(atributos["currentImg"].template get<std::string>());
            m_animation.setTotalTime(atributos["totalTime"].template get<float>());
            m_animation.setCurrentFrame(atributos["currentFrame"].template get<unsigned int>());
            
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            m_canRemove = true;
        }
        
    }
    
    Archer::~Archer() = default;

    void Archer::bootAnimation()
    {
        const auto origin = sf::Vector2f(m_size.x/2.5,m_size.y/2.2);
        m_animation.addAnimation("../Game/animations/Characters/enemy/Skeleton_Archer/Idle.png","PARADO",7,0.16,sf::Vector2f{6,2},origin);
        m_animation.addAnimation("../Game/animations/Characters/enemy/Skeleton_Archer/Walk.png","ANDAR",8,0.16,sf::Vector2f{6,2}, origin);
        m_animation.addAnimation("../Game/animations/Characters/enemy/Skeleton_Archer/Shot_1.png","ATACA",15,0.1,sf::Vector2f{6,2}, origin);
        m_animation.addAnimation("../Game/animations/Characters/enemy/Skeleton_Archer/Hurt.png","TOMADANO",2,0.2,sf::Vector2f{6,2}, origin);
        m_animation.addAnimation("../Game/animations/Characters/enemy/Skeleton_Archer/Dead.png","MORRE",5,0.25,sf::Vector2f{6,2}, origin);
    }

    void Archer::updateAnimation()
    {
        if(m_dying){
            m_animation.update(m_direction, "MORRE");
            m_timeDeath += m_graphic->getTempo();
            if(m_timeDeath > m_animationTimeDeath)
            {
                m_player->increaseRage(m_weapon->getDamage());
                m_canRemove = true;
                m_timeDeath = 0.0f;
                if(m_weapon != nullptr)
                {
                    m_weapon->remove();
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
    
    void Archer::updateAttack()
    {
        if(m_attaking && !m_dying)
        {
            m_timeAttack += m_graphic->getTempo();
            if(m_timeAttack > m_AnimationTimeAttack)
            {
                auto *bullet = dynamic_cast<Weapon::Bullet*>(m_weapon);
                bullet->setPosition(sf::Vector2f(m_position.x + m_size.x ,m_position.y +  m_size.y / 3.0f));
                bullet->setCollision(false);
                bullet->setSpeed(sf::Vector2f(ARCHER_SPEED, 0.0f));
                bullet->setDirection(m_direction);
                m_attaking = false;
                m_timeAttack = 0.0f;
            }
        }
    }

    void Archer::bootSound()
    {
        if(!m_DamageBufferSound.loadFromFile(ARCHER_SOUND_DAMAGE))
        {
            std::cout<< "Esqueleto: não foi possivel carregar somAtaqueBuffer";
            exit(1);
        }
        m_soundDamage.setBuffer(m_DamageBufferSound);
        m_soundDamage.setVolume(40.0f);
    }

    void Archer::moveEnemy()
    {
        if(!m_attaking && !m_dying && !m_getDamage)
        {
            auto enemyPos = m_body.getPosition();
            auto playerPos = m_player->getBody().getPosition();

            const float x = fabs(enemyPos.x - playerPos.x);
            const float y = fabs(enemyPos.y - playerPos.y);

            if(x <= RAIO_DE_VISAO_X && y <= RAIO_DE_VISAO_Y){
                    escape(playerPos,enemyPos);
            }
            else if(x <= RAIO_DE_VISAO_X * 5 && y <= RAIO_DE_VISAO_Y)
            {
                m_direction = (playerPos.x - enemyPos.x > 0.0f) ? false : true ;
                stop();
                
                auto *bullet = dynamic_cast<Weapon::Bullet*>(m_weapon);

                if(bullet->getCollision()) { 
                    m_timeAttack += m_graphic->getTempo();
                    
                    if(m_timeAttack > m_AnimationTimeAttack) {
                        m_attaking = true;
                        m_timeAttack = 0.0f;
                    }
                }
            }
            else {
                randomMove();
                m_timeAttack = 0.0f;
            }
        }
        else
            m_timeMove = 0.0f;
    }

    void Archer::escape(sf::Vector2f playerPos, sf::Vector2f enemyPos)
    {
        if(playerPos.x - enemyPos.x > 0.0f)
            walk(true);
        else
            walk(false);
    }
}
