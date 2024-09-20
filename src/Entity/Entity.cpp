#include "../includes/Entity/Entity.h"

namespace Game::Entity{

    Entity::Entity(const sf::Vector2f size,const IDs::IDs ID, const sf::Vector2f position):
    Ente(ID)
    {
        m_body = sf::RectangleShape(size);
        m_body.setPosition(position);
        m_size = size;
        m_position = position;
        m_canRemove = false;
    }

    sf::Vector2f Entity::getPosition()
    {
        return m_position;
    }

    sf::Vector2f Entity::getSize()
    {
        return m_size;
    }

    void Entity::setPosition(sf::Vector2f position)
    {
        m_body.setPosition(position);
        m_position = position;
    }

    void Entity::draw()
    {
        m_graphic->drawElement(m_body);
    }

    const bool Entity::getRemove()
    {
        return m_canRemove;
    }

    void Entity::remove()
    {
        m_canRemove = true;
    }

    sf::RectangleShape Entity::getBody() {
        return m_body;
    }

    void Entity::setSize(const sf::Vector2f size){
        m_body.setSize(size);
        m_size = size;
    }

    Entity::~Entity() = default;

    nlohmann::ordered_json Entity::saveEntity()
    {
        nlohmann::ordered_json json = saveEnte();

        json["size"] = {{"x", getSize().x}, {"y", getSize().y}};
        json["position"] = {{"x", getPosition().x}, {"y", getPosition().y}};
        json["remove"] = getRemove();

        return json;
    }
}