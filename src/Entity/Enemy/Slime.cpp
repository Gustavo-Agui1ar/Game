#include "../includes/Entity/Enemy/Slime.h"

namespace Game::Entity::Character::Enemy{

    /**
     * @brief Construct a new Slime object.
     * 
     * @param pos Initial position of the slime.
     * @param player Pointer to the player object.
     * @param weapon Pointer to the weapon object.
     */
    Slime::Slime(sf::Vector2f pos, Player::Player *player, Weapon::Weapon* weapon):
    Enemy(pos, sf::Vector2f(SIZE_SLIME_X, SIZE_SLIME_Y), SLIME_SPEED, player, SLIME_TIME_ATTACK, IDs::IDs::red_slime, 
    SLIME_TIME_GET__DAMAGE, SLIME_TIME_ANIMATION_DEATH, SLIME_DAMAGE, weapon)
    { 
        bootAnimation();
        bootSound();
    }

    /**
     * @brief Construct a new Slime object from JSON attributes.
     * 
     * @param atributos JSON object containing the attributes.
     * @param player Pointer to the player object.
     */
    Slime::Slime(nlohmann::ordered_json atributos, Player::Player *player):
    Enemy(m_position, sf::Vector2f(SIZE_SLIME_X, SIZE_SLIME_Y), SLIME_SPEED, player, SLIME_TIME_ATTACK, IDs::IDs::red_slime, 
    SLIME_TIME_GET__DAMAGE, SLIME_TIME_ANIMATION_DEATH, SLIME_DAMAGE, nullptr)
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

    /**
     * @brief Destroy the Slime object.
     */
    Slime::~Slime() = default;

    /**
     * @brief Initialize the animations for the slime.
     */
    void Slime::bootAnimation()
    {
        const auto origin = sf::Vector2f(m_size.x / 2.5, m_size.y / 2.2);
        m_animation.addAnimation("../Game/animations/Characters/enemy/Red_Slime/Idle.png", "PARADO", 8, 0.16, sf::Vector2f{6, 2}, origin);
        m_animation.addAnimation("../Game/animations/Characters/enemy/Red_Slime/Walk.png", "ANDAR", 8, 0.16, sf::Vector2f{6, 2}, origin);
        m_animation.addAnimation("../Game/animations/Characters/enemy/Red_Slime/Attack_3.png", "ATACA", 5, 0.16, sf::Vector2f{6, 2}, origin);
        m_animation.addAnimation("../Game/animations/Characters/enemy/Red_Slime/Dead.png", "MORRE", 3, 0.2, sf::Vector2f{6, 2}, origin);
        m_animation.addAnimation("../Game/animations/Characters/enemy/Red_Slime/Hurt.png", "TOMADANO", 6, 0.1, sf::Vector2f{6, 2}, origin);
    }

    /**
     * @brief Update the animation state of the slime.
     */
    void Slime::updateAnimation()
    {
        if(m_dying && !m_canRemove){
            m_animation.update(m_direction, "MORRE");
            m_timeDeath += m_graphic->getTime();
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
            m_animation.update(m_direction, "TOMADANO");
        else if(m_attaking)
            m_animation.update(m_direction, "ATACA");
        else if(m_moving)
            m_animation.update(m_direction, "ANDAR");
        else
            m_animation.update(m_direction, "PARADO");
    }

    /**
     * @brief Update the attack state of the slime.
     */
    void Slime::updateAttack()
    {
        if(m_attaking && !m_dying)
        {
            m_timeAttack += m_graphic->getTime();
            if(m_timeAttack > m_AnimationTimeAttack)
            {
                m_player->increaseRage(m_weapon->getDamage());
                m_weapon->setPosition(sf::Vector2f(-1000.0f, -1000.0f));
                m_attaking = false;
                m_timeAttack = 0.0f;
            }
            else if(m_timeAttack > m_AnimationTimeAttack / 2.0f)
            {
                auto weaponPos = (m_direction ? sf::Vector2f(m_position.x - m_weapon->getSize().x / 2.0f, m_position.y) : sf::Vector2f(m_position.x + m_weapon->getSize().x / 2.0f, m_position.y));
                m_weapon->setPosition(weaponPos);
            }
        }
    }

    /**
     * @brief Initialize the sound effects for the slime.
     */
    void Slime::bootSound()
    {
        if(!m_DamageBufferSound.loadFromFile(SLIME_SOUND_GET_DAMAGE))
        {
            std::cout << "Slime: não foi possivel carregar somAtaqueBuffer";
            exit(1);
        }
        m_soundDamage.setBuffer(m_DamageBufferSound);
        m_soundDamage.setVolume(40.0f);
    }
}