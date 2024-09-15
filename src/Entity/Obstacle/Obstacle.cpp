
#include "../includes/Entity/Obstacle/Obstacle.h"

namespace Game::Entity::Obstacle {

    Obstacle::Obstacle(sf::Vector2f position, sf::Vector2f size, IDs::IDs ID, IDs::IDs IDTexture):
    Entity(size, ID, position) {
        Gerenciador::GerenciadorGrafico* pGrafico = Gerenciador::GerenciadorGrafico::getGerenciadorGrafico();
        
        switch(IDTexture) {
            case IDs::IDs::cave:
                m_texture = pGrafico->carregarTextura(PATH_TEXTURE_CAVE_PLATFORM);
                m_body.setTexture(&m_texture);
                m_body.setFillColor(sf::Color{100,100,100});
                break;
            case IDs::IDs::dawn_forest:
                m_texture = pGrafico->carregarTextura(PATH_TEXTURE_FOREST_PLATFORM);
                m_body.setTexture(&m_texture);
                break;
            case IDs::IDs::village:
                m_texture = pGrafico->carregarTextura(PATH_TEXTURE_VILAGGE_PLATFORM);
                m_body.setTexture(&m_texture);
                m_body.setFillColor(sf::Color{170,170,170});
                break;
            case IDs::IDs::invisible_platform:
                m_body.setFillColor(sf::Color::Transparent);
                break;
            default:
                break;
        }
    }

    Obstacle::~Obstacle() = default;

    void Obstacle::ObstacleCollision(sf::Vector2f ds, Character::Character* pCharacter) {
        sf::Vector2f otherPosition = pCharacter->getPosition();
        sf::Vector2f finalSpeed = pCharacter->getSpeed();
        if(ds.x < 0.0f && ds.y < 0.0f) { //houve colisao
            if(ds.x > ds.y) {
                if(otherPosition.x < m_position.x) //colis�o em x
                    otherPosition.x += ds.x;
                else
                    otherPosition.x -= ds.x;
                finalSpeed.x = 0.0f;
            }
            else {
                if(otherPosition.y < m_position.y) { //colis�o em y
                    otherPosition.y += ds.y;

                    if(pCharacter->getID() == IDs::IDs::player) {
                        auto* pJogador = static_cast<Character::Player::Player*>(pCharacter);
                        pJogador->canJump();
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