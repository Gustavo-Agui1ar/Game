
#include "../includes/Entity/Weapon/Weapon.h"
#include "../includes/Entity/Enemy/Enemy.h"

namespace Game::Entity::Weapon{

    Weapon::Weapon(IDs::IDs ID):
    Entity(sf::Vector2f(-1000.0f, -1000.0f),ID)
    {
        m_damage = 0.0f;
    }

    Weapon::Weapon(nlohmann::ordered_json atributos):
    Entity(sf::Vector2f(-1000.0f, -1000.0f), (atributos["ID"].template get<IDs::IDs>()))
    {
        try{
            m_damage = atributos["damage"].template get<float>();
            setPosition(sf::Vector2f(atributos["position"]["x"].template get<float>(), atributos["position"]["y"].template get<float>()));
            setSize(sf::Vector2f(atributos["size"]["x"].template get<float>(), atributos["size"]["y"].template get<float>()));
        
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            m_canRemove = true;
        }
    }

    Weapon::~Weapon() = default;

    void Weapon::setDamage(const float damage)
    {
        m_damage = damage;
    }

    const float Weapon::getDamage()
    {
        return m_damage;
    }

    void Weapon::collision(Entity* outraEntidade, sf::Vector2f ds)
    {
        if(ID == IDs::IDs::player_weapon && (outraEntidade->getID() == IDs::IDs::red_slime ||
        outraEntidade->getID() == IDs::IDs::skeleton))
        {      
            auto *inimigo = static_cast<Character::Enemy::Enemy*>(outraEntidade);
            if(!inimigo->getDie())
            {
                inimigo->takeDamage(m_damage);
            }
        }
    }

    void Weapon::draw()
    {
        //no visualization
    }

    void Weapon::update()
    {
        //empty update
    }

    nlohmann::ordered_json Weapon::save()
    {
        return saveWeapon();
    }

    nlohmann::ordered_json Weapon::saveWeapon()
    {
        nlohmann::ordered_json json = saveEntity();
        json["damage"] = m_damage;

        return json;
    }
}
