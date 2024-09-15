
#include "../includes/Entity/Obstacle/Platform.h"


namespace Game::Entity::Obstacle {

    Platform::Platform(sf::Vector2f pos, sf::Vector2f tam, IDs::IDs IDplataforma, IDs::IDs IDtextura):
    Obstacle(pos,tam,IDplataforma, IDtextura) {

    }

    Platform::Platform(nlohmann::ordered_json atributos,IDs::IDs IDplataforma, IDs::IDs IDtextura):
    Obstacle(sf::Vector2f(atributos["position"]["x"].get<float>(), atributos["position"]["y"].get<float>()),
    sf::Vector2f(atributos["size"]["x"].get<float>(), atributos["size"]["y"].get<float>()), 
    IDplataforma, IDtextura) {

    }

    Platform::~Platform() = default;

    void Platform::collision(Entity* otherEntity, sf::Vector2f ds) {
        IDs::IDs ID = otherEntity->getID();
        if(ID == IDs::IDs::player   ||
            ID == IDs::IDs::skeleton ||
            ID == IDs::IDs::red_slime ||
            ID == IDs::IDs::archer  ||
            ID == IDs::IDs::npc  )
        {
            ObstacleCollision(ds, static_cast<Character::Character*>(otherEntity));
        }
    }

    void Platform::update() {
        draw();
    }

    nlohmann::ordered_json Platform::save()  {
        nlohmann::ordered_json json = saveEntity();
        return json;
    }
}
