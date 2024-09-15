
#pragma once

#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../npcs/npc.h"
#include "../includes/Entity/Entity.h"
#include "../includes/Animator/Animation.h"

#define PATH_TEXTURE_CAVE_PLATFORM "..\\Game\\animations\\platform\\Platform_cave.png"
#define PATH_TEXTURE_FOREST_PLATFORM "..\\Game\\animations\\platform\\Platform-forest.png"
#define PATH_TEXTURE_VILAGGE_PLATFORM "..\\Game\\animations\\platform\\Platform-vila.png"


namespace Game::Entity::Obstacle{
    class Obstacle: public Entity{

    protected:

        sf::Texture m_texture;

    public:

        Obstacle(sf::Vector2f position, sf::Vector2f size, IDs::IDs ID, IDs::IDs IDTexture);
        ~Obstacle() override;

        void collision(Entity* otherEntity, sf::Vector2f ds = sf::Vector2f(0.f,0.f)) override = 0;
        void ObstacleCollision(sf::Vector2f ds, Character::Character* pCharacter);
        
        void update() override = 0;

        nlohmann::ordered_json save() override = 0;
    };
}
