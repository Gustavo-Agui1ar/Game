#include "../includes/Entity/Obstacle/House.h"

namespace Game::Entity::Obstacle{

    /**
     * @brief Construct a new House object.
     * 
     * @param size Size of the house.
     * @param ID ID of the house entity.
     * @param position Initial position of the house.
     */
    House::House(const sf::Vector2f size, const IDs::IDs ID, const sf::Vector2f position):
    Entity(size, ID, position)
    {
        // Constructor implementation
    }

    /**
     * @brief Destroy the House object.
     */
    House::~House() = default;

    /**
     * @brief Update the house state.
     */
    void House::update()
    {
        m_graphic->drawElement(m_body);
    }

    /**
     * @brief Set the texture of the house.
     * 
     * @param pathTexture Path to the texture file.
     */
    void House::setTexture(const char* pathTexture)
    {
        m_texture = m_graphic->loadTexture(pathTexture);
        m_body.setTexture(&m_texture);
    }

    /**
     * @brief Save the current state of the house to a JSON object.
     * 
     * @return nlohmann::ordered_json The JSON object with the saved house state.
     */
    nlohmann::ordered_json House::save()
    {
        nlohmann::ordered_json json = saveEntity();
        return json;
    }
    
    /**
     * @brief Handle collision with another entity.
     * 
     * @param otherEntity Pointer to the other entity.
     * @param ds Displacement vector.
     */
    void House::collision(Entity* otherEntity, sf::Vector2f ds)
    {
        // Handle collision
    }
}