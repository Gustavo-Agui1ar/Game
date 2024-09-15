
#include "../includes/States/LevelState.h"

namespace Game::State{

    LevelState::LevelState(const IDs::IDs ID):
    State(ID)
    {
        m_level = nullptr;
    }

    void LevelState::makeLevel(nlohmann::ordered_json entidades, IDs::IDs IDfase)
    {
        switch (IDfase)
        {
            case IDs::IDs::dawn_forest:
                m_level = static_cast<Level::Level*>(new Level::Forest(entidades));
                break;
            case IDs::IDs::cave:
                m_level = static_cast<Level::Level*>(new Level::Caverna(entidades));
                break;
            
            default:
                break;
        }
    }

    LevelState::~LevelState()
    {
        if(m_level != nullptr)
            delete m_level;
        m_level = nullptr;
    }

    void LevelState::makeLevel()
    {
        switch (ID)
        {
            case IDs::IDs::dawn_forest:
                m_level = static_cast<Level::Level*>(new Level::Forest());
                break;
            case IDs::IDs::cave:
                m_level = static_cast<Level::Level*>(new Level::Caverna());
                break;
            case IDs::IDs::village:
                m_level = static_cast<Level::Level*>(new Level::Vila());
                break;
            default:
                break;
        }

        if(m_level == nullptr)
        {
            std::cout<<"Estados::LevelState: nao foi possivel criar um estadoFase";
            exit(1);
        }

        m_level->makeBackGround();
        m_level->makeMap();
    }

    void LevelState::execute()
    {
        m_level->execute();
    }

    void LevelState::changeEstateObserver(const bool ativo)
    {

        if(Entity::Character::Player::Player* player = m_level->getPlayer(); player != nullptr)
        {
            player->changeObserverState(ativo);
        }

        m_level->changeStateObserver(ativo);

    
    }

    Level::Level* LevelState::getLevel()
    {
        return m_level;
    }
}