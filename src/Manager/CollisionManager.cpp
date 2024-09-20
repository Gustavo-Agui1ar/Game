
#include "../../includes/Manager/CollisionManager.h"


namespace Game::Manager{


    Manager::CollisionManager* CollisionManager::m_collisionManager = nullptr;


    CollisionManager* CollisionManager::getCollisionManager()
    {
        if(m_collisionManager == nullptr)
            m_collisionManager = new CollisionManager();
        return m_collisionManager;
    }

    CollisionManager::CollisionManager():
    m_characterList(), m_obstacleList()
    {

    }

    CollisionManager::~CollisionManager()
    {
            delete m_obstacleList;
            delete m_characterList;

            m_obstacleList = nullptr;
            m_characterList = nullptr;
    }

    const sf::Vector2f CollisionManager::calculusCollision(Entity::Entity* ent1, Entity::Entity* ent2)
    {

        sf::Vector2f pos1 = ent1->getPosition();
        sf::Vector2f pos2 = ent2->getPosition();

        sf::Vector2f tam1 = ent1->getSize();
        sf::Vector2f tam2 = ent2->getSize();

        sf::Vector2f distanciaEntreCentros(
            fabs((pos1.x + tam1.x/2.0f) - (pos2.x + tam2.x/2.0f)),
            fabs((pos1.y + tam1.y/2.0f) - (pos2.y + tam2.y/2.0f))
        );

        sf::Vector2f somaMetadeRetangulo(tam1.x/2.0f + tam2.x/2.0f, tam1.y/2.0f + tam2.y/2.0f);
        sf::Vector2f distanciaEntreCentrosDasEntidades(distanciaEntreCentros.x - somaMetadeRetangulo.x, distanciaEntreCentros.y - somaMetadeRetangulo.y);

        return distanciaEntreCentrosDasEntidades;
    }

    void CollisionManager::execute()
    {

        //personagem e personagem.
        for(int i = 0 ; i < m_characterList->getSize() - 1 ; i++)
        {
            Entity::Entity* ent1 = m_characterList->operator[](i);

            for(int j = i + 1 ; j < m_characterList->getSize() ; j++)
            {
                Entity::Entity* ent2 = m_characterList->operator[](j);
                sf::Vector2f ds = calculusCollision(ent1, ent2);

                if(ds.x < 0.0f && ds.y < 0.0f)
                {
                    ent1->collision(ent2,ds);
                }
            }
        }

        //personagem e obstaculo
            for(int i = 0 ; i < m_characterList->getSize(); i++)
        {
            Entity::Entity* ent1 = m_characterList->operator[](i);

            for(int j = 0 ; j < m_obstacleList->getSize() ; j++)
            {
                Entity::Entity* ent2 = m_obstacleList->operator[](j);

                sf::Vector2f ds = calculusCollision(ent1, ent2);

                if(ds.x < 0.0f && ds.y < 0.0f)
                {
                    ent2->collision(ent1,ds);
                }
            }
        }
    }

    Entity::Entity* CollisionManager::searchEntity(sf::Vector2f posPersonagem, sf::Vector2f raioDeDistancia, IDs::IDs objProcurado)
    {
        int tam = m_characterList->getSize();
        
        Entity::Entity* entMaisProxima = nullptr;
        
        float posXmaisProximo = 0.f;
        float posYmaisProximo = 0.f;

        for(int i = 0 ; i < tam ; i++)
        {

            Entity::Entity* ent = m_characterList->operator[](i);

            if(ent->getID() == objProcurado)
            {
                float posX = fabs(posPersonagem.x - ent->getPosition().x);
                float posY = fabs(posPersonagem.y - ent->getPosition().y);
                
                if((posX <= raioDeDistancia.x && posY <= raioDeDistancia.y) && 
                   (entMaisProxima == nullptr || (posX < posXmaisProximo && posY < posYmaisProximo)))
                {
                    posXmaisProximo = posX;
                    posYmaisProximo = posY;

                    entMaisProxima = ent;
                }
            }
        }

        return entMaisProxima;
    }

    void CollisionManager::setCharacterList(List::EntityList* characters)
    {
        m_characterList = characters;
    }

    void CollisionManager::setObstacleList( List::EntityList* obstacles)
    {
        m_obstacleList = obstacles;
    }

    void CollisionManager::clearList()
    {
        delete m_obstacleList;
        delete m_characterList;

        m_obstacleList = nullptr;
        m_characterList = nullptr;
    }
}
