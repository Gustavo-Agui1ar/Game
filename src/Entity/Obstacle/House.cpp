
#include "../includes/Entity/Obstacle/House.h"

namespace Game::Entity::Obstacle{

    House::House(const sf::Vector2f size, const IDs::IDs ID, const sf::Vector2f position):
    Entity(size, ID, position)
    {

    }

    House::~House() = default;

    void House::update()
    {
        m_graphic->desenhaElemento(m_body);
    }

    void House::setTexture(const char* pathTexture)
    {
        m_texture = m_graphic->carregarTextura(pathTexture);

        m_body.setTexture(&m_texture);
    }

    nlohmann::ordered_json House::save()
    {
        nlohmann::ordered_json json = saveEntity();
        return json;
    }
    
    void House::collision(Entity* otherEntity, sf::Vector2f ds)
    {
        //
    }
}