
#include "../includes/Entity/Enemy/Skeleton.h"

namespace Game::Entity::Character::Enemy{

    Skeleton::Skeleton(sf::Vector2f position, Player::Player *player, Weapon::Weapon* weapon):
    Enemy(position, sf::Vector2f(SIZE_SKELETON_X, SIZE_SKELETON_Y), SKELETON_SPEED, player, SKELETON_TIME_ATTACK,
    IDs::IDs::skeleton, SKELETON_TIME_GET_DAMAGE, SKELETON_TIME_ANIMATION_DEATH,SKELETON_DAMAGE, weapon)
    {
        bootAnimation();
        bootSound();
    }

    Skeleton::Skeleton(nlohmann::ordered_json atributos, Player::Player* player):
    Enemy(m_position, sf::Vector2f(SIZE_SKELETON_X,SIZE_SKELETON_Y), SKELETON_SPEED, player, SKELETON_TIME_ATTACK,
    IDs::IDs::skeleton, SKELETON_TIME_GET_DAMAGE, SKELETON_TIME_ANIMATION_DEATH, SKELETON_DAMAGE,  nullptr)
    {
        try
        {
            auto currentPosition = sf::Vector2f(atributos["position"]["x"].template get<float>(), atributos["position"]["y"].template get<float>());

            setPosition(currentPosition);
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
    
    Skeleton::~Skeleton() = default;

    void Skeleton::bootAnimation()
    {
        const auto origin = sf::Vector2f(m_size.x/2.5,m_size.y/2.2);
        m_animation.addAnimation("../Game/animations/Characters/enemy/Skeleton_Spearman/Idle.png","PARADO",7,0.16,sf::Vector2f{6,2},origin);
        m_animation.addAnimation("../Game/animations/Characters/enemy/Skeleton_Spearman/Walk.png","ANDAR",7,0.16,sf::Vector2f{6,2}, origin);
        m_animation.addAnimation("../Game/animations/Characters/enemy/Skeleton_Spearman/Attack_1.png","ATACA",4,0.2,sf::Vector2f{6,2}, origin);
        m_animation.addAnimation("../Game/animations/Characters/enemy/Skeleton_Spearman/Hurt.png","TOMADANO",3,0.2,sf::Vector2f{6,2}, origin);
        m_animation.addAnimation("../Game/animations/Characters/enemy/Skeleton_Spearman/Dead.png","MORRE",5,0.25,sf::Vector2f{6,2}, origin);
    }

    void Skeleton::updateAnimation()
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

    void Skeleton::updateAttack()
    {
        if(m_attaking && !m_dying)
        {
            m_timeAttack += m_graphic->getTempo();
            if(m_timeAttack > m_AnimationTimeAttack)
            {
                m_weapon->setPosition(sf::Vector2f(-1000.0f, -1000.0f));
                m_attaking = false;
                m_timeAttack = 0.0f;
            }
            else if(m_timeAttack > m_AnimationTimeAttack/2.0f)
            {
                sf::Vector2f weaponPosition = (m_direction ? sf::Vector2f(m_position.x - m_weapon->getSize().x/2.0f,m_position.y) : sf::Vector2f(m_position.x + m_weapon->getSize().x/2.0f,m_position.y));
                m_weapon->setPosition(weaponPosition);
            }
        }
    }

    void Skeleton::bootSound()
    {
        if(!m_DamageBufferSound.loadFromFile(SOUND_SKELETON_GET_DAMAGE))
        {
            std::cout<< "Skeleton: não foi possivel carregar somAtaqueBuffer";
            exit(1);
        }
        m_soundDamage.setBuffer(m_DamageBufferSound);
        m_soundDamage.setVolume(40.0f);
    }
}