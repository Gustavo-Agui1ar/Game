
#pragma once

#include "../includes/gerenciador/gerenciadorDeColisao.h"

#include "../listeners/listenerFase.h"

#include "../includes/Entity/Obstacle/Platform.h"

#include "../lista/listaEntidade.h"

#include "../includes/Entity/Enemy/Enemy.h"

#include "../includes/Entity/Enemy/Archer.h"

#include "../includes/Entity/Enemy/Skeleton.h"

#include "../includes/Entity/Enemy/Slime.h"

#include "../includes/Entity/Player/Player.h"

#include "../fundo/fundo.h"
namespace Game::Level{
    class Level : public Ente{

    protected:
        static Listener::ListenerFase* m_observerLevel;

        Lista::ListaEntidade* m_charactersList;
        Lista::ListaEntidade* m_obstaclesList;
        Entity::Character::Player::Player* m_player;

        Gerenciador::GerenciadorDeColisao* m_collisionManager;
        
        Fundo::Fundo m_backGround;

    public:   

        Level(const IDs::IDs level_ID, const IDs::IDs backGround_ID);
        ~Level() override;
        
        void changeStateObserver(const bool ative);

        nlohmann::ordered_json SaveLevel();

        nlohmann::ordered_json SaveEntity();

        void makeEntity(IDs::IDs ID, nlohmann::ordered_json entity , nlohmann::ordered_json weapon = nullptr, nlohmann::ordered_json weapon2 = nullptr);
        void makeEnemy(const sf::Vector2f pos, const char letter);
        virtual void makePlatform(const sf::Vector2f pos) = 0;
        void makeEntity(char letter, const sf::Vector2i pos);
        void makeInvisiblePlatform(const sf::Vector2f pos);
        void makePlayer(const sf::Vector2f pos);
        
        virtual void makeBackGround() = 0;
        virtual void makeMap() = 0;
        
        Entity::Character::Player::Player* getPlayer();
        
         virtual void execute();
        void draw() override;

    };
}
