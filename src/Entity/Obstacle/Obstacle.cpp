#include "../includes/Entity/Obstacle/Obstacle.h"

namespace Game::Entity::Obstacle {

    /**
     * @brief Construct a new Obstacle object.
     * 
     * @param position Initial position of the obstacle.
     * @param size Size of the obstacle.
     * @param ID ID of the obstacle entity.
     * @param IDTexture ID of the texture to be used for the obstacle.
     */
    Obstacle::Obstacle(sf::Vector2f position, sf::Vector2f size, IDs::IDs ID, IDs::IDs IDTexture):
    Entity(size, ID, position) {
        Manager::GraphicManager* pGraphic = Manager::GraphicManager::getGraphicManager();
        
        switch(IDTexture) {
            case IDs::IDs::cave:
                m_texture = pGraphic->loadTexture(PATH_TEXTURE_CAVE_PLATFORM);
                m_body.setTexture(&m_texture);
                m_body.setFillColor(sf::Color{100, 100, 100});
                break;
            case IDs::IDs::dawn_forest:
                m_texture = pGraphic->loadTexture(PATH_TEXTURE_FOREST_PLATFORM);
                m_body.setTexture(&m_texture);
                break;
            case IDs::IDs::village:
                m_texture = pGraphic->loadTexture(PATH_TEXTURE_VILAGGE_PLATFORM);
                m_body.setTexture(&m_texture);
                m_body.setFillColor(sf::Color{170, 170, 170});
                break;
            case IDs::IDs::invisible_platform:
                m_body.setFillColor(sf::Color::Transparent);
                break;
            default:
                break;
        }
    }

    /**
     * @brief Destroy the Obstacle object.
     */
    Obstacle::~Obstacle() = default;

    /**
     * @brief Handle collision between the obstacle and a character.
     * 
     * @param ds Displacement vector.
     * @param pCharacter Pointer to the character involved in the collision.
     */
    void Obstacle::ObstacleCollision(sf::Vector2f ds, Character::Character* pCharacter) {
        sf::Vector2f otherPosition = pCharacter->getPosition();
        sf::Vector2f finalSpeed = pCharacter->getSpeed();
        if(ds.x < 0.0f && ds.y < 0.0f) { // Collision occurred
            if(ds.x > ds.y) {
                if(otherPosition.x < m_position.x) // Collision in x direction
                    otherPosition.x += ds.x;
                else
                    otherPosition.x -= ds.x;
                finalSpeed.x = 0.0f;
            }
            else {
                if(otherPosition.y < m_position.y) { // Collision in y direction
                    otherPosition.y += ds.y;

                    if(pCharacter->getID() == IDs::IDs::player) {
                        auto* player = static_cast<Character::Player::Player*>(pCharacter);
                        player->canJump();
                    }
                }
                else
                    otherPosition.y -= ds.y;
                finalSpeed.y = 0.0f;
            }
        }
        pCharacter->setPosition(otherPosition);
        pCharacter->setMaxSpeed(finalSpeed);
    }
}