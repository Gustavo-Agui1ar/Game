
#include "../includes/Levels/Level.h"
#include <unistd.h>

namespace Game::Level{

    
    Listener::ListenerFase* Level::m_observerLevel = nullptr;
    
    Level::Level(const IDs::IDs ID_Fase, const IDs::IDs ID_Fundo):
    Ente(ID_Fase),m_backGround(ID_Fundo)
    {
        m_charactersList = new Lista::ListaEntidade();
        m_obstaclesList = new Lista::ListaEntidade();

        m_collisionManager = Gerenciador::GerenciadorDeColisao::getGerenciadorDeColisao();

        m_collisionManager->setListaObstaculo(m_obstaclesList);
        m_collisionManager->setListaPersonagem(m_charactersList);

        if(m_collisionManager == nullptr)
        {
            std::cout<<"Level::Level: not possible to create the collision manager";
            exit(1);
        }

        m_observerLevel = new Listener::ListenerFase(this);
        
        if(m_observerLevel == nullptr)
        {
            std::cout<<"Level::Level: not possible to create the observer";
            exit(1);
        }

        m_observerLevel->mudarEstado(true);
    }

    Level::~Level()
    {
        if(m_collisionManager != nullptr)
        {
            m_collisionManager->limparListas();
            m_collisionManager = nullptr;
        }
        
        if(m_observerLevel != nullptr){
            delete m_observerLevel;
            m_observerLevel = nullptr;
        }
    }

    void Level::makePlayer(const sf::Vector2f pos)
    {
        auto* weaponPlayer = new Entity::Weapon::Weapon(IDs::IDs::player_weapon); 
        auto* bulletPlayer = new Entity::Weapon::Bullet(IDs::IDs::player_bullet); 
        auto* player =  new Entity::Character::Player::Player(pos);

        if(player == nullptr)
        {
            std::cout<<"Level::Level: not possible to create the player";
            exit(1);
        }
        if(weaponPlayer == nullptr)
        {
            std::cout<<"Level::Level:not possible to create the player weapon";
            exit(1);
        }
        
        if(bulletPlayer == nullptr)
        {
            std::cout<<"Level::Level:not possible to create the player bullet";
            exit(1);
        }
        
        player->setWeapon(weaponPlayer);
        player->setBullet(bulletPlayer);
        m_player = player;

        m_charactersList->addEntidade(static_cast<Entity::Entity*>(m_player));
        m_charactersList->addEntidade(static_cast<Entity::Entity*>(weaponPlayer));
        m_charactersList->addEntidade(static_cast<Entity::Entity*>(bulletPlayer));

    }

    void Level::makeEnemy(const sf::Vector2f pos, const char letra)
    {
        Entity::Weapon::Weapon* weapon = nullptr;
        Entity::Character::Enemy::Enemy* enemy = nullptr;
        
        switch(letra)
        {
            case 'e':
                enemy  = new Entity::Character::Enemy::Skeleton(pos, m_player);
                weapon = new Entity::Weapon::Weapon(IDs::IDs::enemy_weapon);
                enemy->setWeapon(weapon);
                break;
            case 's':
                enemy  = new Entity::Character::Enemy::Slime(pos, m_player);
                weapon = new Entity::Weapon::Weapon(IDs::IDs::enemy_weapon);
                enemy->setWeapon(weapon);
                break;
            case 'a':
                enemy  = new Entity::Character::Enemy::Archer(pos, m_player);
                weapon = new Entity::Weapon::Bullet(IDs::IDs::enemy_bullet);
                enemy->setWeapon(weapon);
                break;
            default:
                break;
        }
        
        if(enemy == nullptr) {
            std::cout<<"Level::Level: not possible to create the enemy";
            exit(1);
        }

        if(weapon == nullptr){
            std::cout<<"Level::Level: not possible to create the enemy weapon";
            exit(1);
        }

        if(enemy && weapon) {
            m_charactersList->addEntidade(enemy);
            m_charactersList->addEntidade(weapon);
        }
    }

    void Level::makeEntity(char letra, const sf::Vector2i pos)
    {
        switch(letra)
        {
            case 'e':
                makeEnemy(sf::Vector2f(pos.x * 50.0f, pos.y * 50.0f),letra);
                break;
            case 's':
                makeEnemy(sf::Vector2f(pos.x * 50.0f, pos.y * 50.0f),letra);
                break;
            case 'a':
                makeEnemy(sf::Vector2f(pos.x * 50.0f, pos.y * 50.0f),letra);
                break;
            case '#':
                makePlatform(sf::Vector2f(pos.x * 50.0f, pos.y * 50.0f + 10.f));
                break;
            case 'j':
                makePlayer(sf::Vector2f(pos.x * 50.0f, pos.y * 50.0f));
                break;
            case 'v':
                makeInvisiblePlatform(sf::Vector2f(pos.x * 50.0f, pos.y * 50.0f));
                break;
            default:
                break;
        }
    }

    void Level::makeEntity(IDs::IDs ID, nlohmann::ordered_json entidade , nlohmann::ordered_json arma, nlohmann::ordered_json arma2)
    {
        Entity::Entity* character = nullptr;
        Entity::Entity* weaponCharacter = nullptr;
        Entity::Entity* bulletPlayer = nullptr;

        switch(ID)
        {
            case IDs::IDs::player:
            {
                m_player = new Entity::Character::Player::Player(entidade);

                  new Entity::Weapon::Weapon(arma);
                auto* playerBullet = new Entity::Weapon::Bullet(arma2);
                
                m_player->setWeapon(playerWepon);
                m_player->setBullet(playerBullet);

                character = static_cast<Entity::Entity*>(m_player);
                weaponCharacter = static_cast<Entity::Entity*>(playerWepon);
                bulletPlayer = static_cast<Entity::Entity*>(playerBullet);
            }
            break;

            case IDs::IDs::skeleton:
            {
                auto* skeleton = new Entity::Character::Enemy::Skeleton(entidade, m_player); 
                auto* skeletonWeapon = new Entity::Weapon::Weapon(arma);

                skeleton->setWeapon(skeletonWeapon);
                character = static_cast<Entity::Entity*>(skeleton);
                weaponCharacter = static_cast<Entity::Entity*>(skeletonWeapon);
            }
            break;
            
            case IDs::IDs::archer:
            {
                auto* archer = new Entity::Character::Enemy::Archer(entidade, m_player);
                auto* bulletArcher = new Entity::Weapon::Bullet(arma);
                auto* archerWeapon = static_cast<Entity::Weapon::Weapon*>(bulletArcher);

                archer->setWeapon(archerWeapon);
                character = static_cast<Entity::Entity*>(archer);
                weaponCharacter = static_cast<Entity::Entity*>(archerWeapon);
            }
            break;

            case IDs::IDs::red_slime:
            {
                auto* slime = new Entity::Character::Enemy::Slime(entidade, m_player); 
                auto* pArma = new Entity::Weapon::Weapon(arma);
            
                slime->setWeapon(pArma);
                character = static_cast<Entity::Entity*>(slime);
                weaponCharacter = static_cast<Entity::Entity*>(pArma);
            }
            break;

            case IDs::IDs::platform:
            {
                auto* platform = new Entity::Obstacle::Platform(entidade, IDs::IDs::platform, getID());

                character = static_cast<Entity::Entity*>(platform);                   
            }
            break;

            case IDs::IDs::invisible_platform:
            {
                auto* platform = new Entity::Obstacle::Platform(entidade, IDs::IDs::invisible_platform, IDs::IDs::invisible_platform);
                character = static_cast<Entity::Entity*>(platform); 
            }
            break;

            default:
                break;
        }

        switch (ID)
        {
            case IDs::IDs::platform:
            case IDs::IDs::invisible_platform:
                m_obstaclesList->addEntidade(character);
                break;
            case IDs::IDs::player:
                m_charactersList->addEntidade(character);
                m_charactersList->addEntidade(weaponCharacter);
                m_charactersList->addEntidade(bulletPlayer);
                break;
            default:
                m_charactersList->addEntidade(character);
                m_charactersList->addEntidade(weaponCharacter);
                break;
        }
    }

    void Level::execute()
    {
        if(getPlayer())
        {
            m_backGround.executar();

            m_obstaclesList->executar();
            m_charactersList->executar();

            m_collisionManager->executar();
        }
        else{
            m_observerLevel->notificarGameOver();
        }
    }

    void Level::draw()
    {
        m_backGround.executar();

        m_obstaclesList->desenharEntidades();
        m_charactersList->desenharEntidades();

    }
  
    Entity::Character::Player::Player* Level::getPlayer()
    {
        for(int i = 0; i < m_charactersList->getTam(); i++)
        {
            Entity::Entity* aux = m_charactersList->operator[](i);
            if(aux->getID() == IDs::IDs::player)
            {
                return dynamic_cast<Entity::Character::Player::Player*>(aux);
            }
        }
        return nullptr;
    }

    void Level::changeStateObserver(const bool ativo)
    {
        m_observerLevel->mudarEstado(ativo);
    }

    nlohmann::ordered_json Level::SaveLevel()
    {
        nlohmann::ordered_json json = saveEnte();
        
        return json;
    }

    nlohmann::ordered_json Level::SaveEntity()
    {
        nlohmann::ordered_json json;

        for(int i = 0 ; i < m_charactersList->getTam() ; i++)
        {
            Entity::Entity* entidade = m_charactersList->operator[](i);
            if(entidade != nullptr)
            {
                nlohmann::ordered_json jsonEntidade = entidade->save();
                json.push_back(jsonEntidade);
            }
        }

            for(int i = 0 ; i < m_obstaclesList->getTam() ; i++)
        {
            Entity::Entity* entidade = m_obstaclesList->operator[](i);
            if(entidade != nullptr)
            {
                nlohmann::ordered_json jsonEntidade = entidade->save();
                json.push_back(jsonEntidade);
            }
        }

        return json;
    }

    void Level::makeInvisiblePlatform(const sf::Vector2f pos)
    {
        
        auto* platform = new Entity::Obstacle::Platform(pos,sf::Vector2f(50.0f,50.0f), IDs::IDs::invisible_platform, IDs::IDs::invisible_platform);
        if(platform == nullptr)
        {
            std::cout<<"Level::Level:: not possible to create the invisible platform";
            exit(1);
        }
        auto* plat = static_cast<Entity::Entity*>(platform);
        m_obstaclesList->addEntidade(plat);
    }
}