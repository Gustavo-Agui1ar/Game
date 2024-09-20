
#pragma once

#include <SFML/Graphics.hpp>
#include "../List/EntityList.h"
#include <cmath>

namespace Game::Manager{
    class CollisionManager{
    
    private:

        List::EntityList* m_characterList;
        List::EntityList* m_obstacleList;
        
        static CollisionManager* m_collisionManager;
        CollisionManager();
    
    public:

        static CollisionManager* getCollisionManager();
        ~CollisionManager();

        void setCharacterList(List::EntityList* character);
        void setObstacleList( List::EntityList* obstacle);
        void clearList();

        const sf::Vector2f calculusCollision(Entity::Entity* ent1, Entity::Entity* ent2);
        Entity::Entity* searchEntity(sf::Vector2f positionCharacter, sf::Vector2f distanceRadius, IDs::IDs IDSearch);
        void execute();
    };
}
