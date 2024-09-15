#include "../includes/Entity/Weapon/Bullet.h"
#include "../includes/Entity/Enemy/Enemy.h"

namespace Game::Entity::Weapon{

    /**
     * @brief Construct a new Bullet object with a given ID.
     * 
     * @param ID The ID of the bullet.
     */
    Bullet::Bullet( IDs::IDs ID):
    Weapon(ID), m_direction(false), m_collision(true), m_speed(sf::Vector2f(0.0f, 0.0f)), m_animation(&m_body)
    {
        setPosition(sf::Vector2f(-1000.0f, -1000.0f));
        inicializarAnimacao();
    }

    /**
     * @brief Construct a new Bullet object with attributes from a JSON object.
     * 
     * @param atributos The JSON object containing the attributes.
     */
    Bullet::Bullet( nlohmann::ordered_json atributos):
    Weapon(atributos["ID"].template get<IDs::IDs>()), m_animation(&m_body)
    {
        try{
            m_damage = atributos["damage"].template get<float>();
            setPosition(sf::Vector2f(atributos["position"]["x"].template get<float>(), atributos["position"]["y"].template get<float>()));
            setSize(sf::Vector2f(atributos["size"]["x"].template get<float>(), atributos["size"]["y"].template get<float>()));
            m_direction = atributos["direction"].template get<bool>();
            m_collision = atributos["collision"].template get<bool>();

            inicializarAnimacao();

            m_animation.setCurrentImg(atributos["currentImg"].template get<std::string>());
            m_animation.setCurrentFrame(atributos["currentFrame"].template get<unsigned int>());
            m_animation.setTotalTime(atributos["totalTime"].template get<float>());

            setSpeed(sf::Vector2f(atributos["speed"]["x"].template get<float>(), atributos["speed"]["y"].template get<float>()));

        
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            m_canRemove = true;
        }
    }

    /**
     * @brief Destroy the Bullet object.
     */
    Bullet::~Bullet() = default;
    
    /**
     * @brief Initialize the animation for the bullet.
     */
    void Bullet::inicializarAnimacao()
    {
        if(getID() == IDs::IDs::enemy_bullet)
        {
            setSize(sf::Vector2f(BULLET_SIZE, BULLET_SIZE));
            m_animation.addAnimation("../Game/animations/Characters/enemy/Skeleton_Archer/Arrow.png", "ATACA", 1, 10.0f, sf::Vector2f(1.5f, 0.2f), sf::Vector2f(m_size.x / 2.0f, m_size.y / 2.0f));
        }
        else
        {
            setSize(sf::Vector2f(BULLET_SIZE_PLAYER, BULLET_SIZE_PLAYER));
            m_animation.addAnimation("../Game/animations/Characters/Player/Fire-ball.png", "ATACA", 4, 0.12f, sf::Vector2f(5.0f, 5.0f), sf::Vector2f(m_size.x / 2.0f, m_size.y / 2.0f));
        }
        m_animation.setCurrentImg("ATACA"); 
    }

    /**
     * @brief Set the speed of the bullet.
     * 
     * @param speed The speed vector.
     */
    void Bullet::setSpeed(sf::Vector2f speed)
    {
        m_speed = speed;
    }

    /**
     * @brief Set the collision state of the bullet.
     * 
     * @param collision The collision state.
     */
    void Bullet::setCollision(bool collision)
    {
        m_collision = collision;

        if(m_collision)
        {
            setPosition(sf::Vector2f(-1000.0f, -1000.0f));
            setSpeed(sf::Vector2f(0.0f, 0.0f));
        }
    }

    /**
     * @brief Get the collision state of the bullet.
     * 
     * @return true If the bullet has collided.
     * @return false Otherwise.
     */
    const bool Bullet::getCollision()
    {
        return m_collision;
    }

    /**
     * @brief Set the direction of the bullet.
     * 
     * @param direction The direction state.
     */
    void Bullet::setDirection(bool direction)
    {
        m_direction = direction;
        m_speed = direction ? sf::Vector2f(m_speed.x * -1, m_speed.y) : m_speed;
    }

    /**
     * @brief Check if the bullet is out of the screen.
     */
    void Bullet::checkOutScreen()
    {
        sf::Vector2f screenCenter = m_graphic->getCamera().getCenter();
        sf::Vector2f screenSize = m_graphic->getTamJanela();

        if(m_position.x < screenCenter.x - screenSize.x/2.0f || m_position.x > screenCenter.x + screenSize.x/2.0f ||
            m_position.y < screenCenter.y - screenSize.y/2.0f || m_position.y > screenCenter.y + screenSize.y/2.0f )
        {
            setCollision(true);
        }
    }

    /**
     * @brief Update the position of the bullet.
     */
    void Bullet::updatePosition()
    {
        const float dt = m_graphic->getTempo();
        sf::Vector2f finalPosition(0.0f, m_position.y);

        finalPosition.x = m_position.x + m_speed.x * dt;

        setPosition(finalPosition);
    }

    /**
     * @brief Update the animation of the bullet.
     */
    void Bullet::updateAnimation()
    {
        m_animation.update(m_direction, "ATACA");
    }

    /**
     * @brief Draw the bullet on the screen.
     */
    void Bullet::draw()
    {
        m_graphic->desenhaElemento(m_body);
    }

    /**
     * @brief Save the bullet's state to a JSON object.
     * 
     * @return nlohmann::ordered_json The JSON object containing the bullet's state.
     */
    nlohmann::ordered_json Bullet::save()
    {
        nlohmann::ordered_json json = saveWeapon();

        json["direction"] = m_direction;
        json["speed"] = {{"x", m_speed.x}, {"y", m_speed.y}};
        json["collision"] = m_collision;
        json = m_animation.saveAnimation(json);

        return json;
    }

    /**
     * @brief Update the bullet's state.
     */
    void Bullet::update()
    {
        if(!m_collision)
        {
            updatePosition();
            updateAnimation();
            checkOutScreen();

            m_graphic->desenhaElemento(m_body);
        }
    }

    /**
     * @brief Handle collision with another entity.
     * 
     * @param otherEntity The other entity.
     * @param ds The displacement vector.
     */
    void Bullet::collision(Entity* otherEntity, sf::Vector2f ds)
    {
        auto other_ID = static_cast<int>(otherEntity->getID());
        if(other_ID >= 2 && other_ID <= 4)
        {    
            auto* enemy = static_cast<Character::Enemy::Enemy*>(otherEntity);
            if(!enemy->getDie())
            {
                enemy->takeDamage(m_damage);
                setCollision(true);
            }
        
        }
    }
}