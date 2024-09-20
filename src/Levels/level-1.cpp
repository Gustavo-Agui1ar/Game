
#include "../includes/Levels/level-1.h"

#define CAMADA_1_1 "../Game/animations/background/level-1/camada-1.png"
#define CAMADA_2_1 "../Game/animations/background/level-1/camada-2.png"
#define CAMADA_3_1 "../Game/animations/background/level-1/camada-3.png"
#define CAMADA_4_1 "../Game/animations/background/level-1/camada-4.png"
#define CAMADA_5_1 "../Game/animations/background/level-1/camada-5.png"
#define CAMADA_6_1 "../Game/animations/background/level-1/camada-6.png"
#define CAMADA_7_1 "../Game/animations/background/level-1/camada-7.png"
#define CAMADA_8_1 "../Game/animations/background/level-1/camada-8.png"


namespace Game::Level{

    
    Caverna::Caverna():
    Level(IDs::IDs::cave, IDs::IDs::cave)
    {

    }

    Caverna::Caverna(nlohmann::ordered_json entidades):
    Level(IDs::IDs::cave, IDs::IDs::cave)
    {
        makeBackGround();
        loadGame(entidades);
    }

    void Caverna::loadGame(nlohmann::ordered_json entidades)
    {
        auto it = entidades.begin();
        while(it != entidades.end())
        {
            switch((*it)["ID"].template get<IDs::IDs>())
            {
                case IDs::IDs::player:
                {
                    
                    nlohmann::ordered_json entidade = (*it);
                    it++;
                    nlohmann::ordered_json arma = (*it);
                    it++;
                    nlohmann::ordered_json projetil = (*it);

                    makeEntity(IDs::IDs::player, entidade, arma, projetil);
                }
                break;

                case IDs::IDs::skeleton:
                {
                    
                    nlohmann::ordered_json entidade = (*it);
                    it++;
                    nlohmann::ordered_json arma = (*it);

                    makeEntity(IDs::IDs::skeleton, entidade, arma);
                }
                break;

                case IDs::IDs::archer:
                {
                    
                    nlohmann::ordered_json entidade = (*it);
                    it++;
                    nlohmann::ordered_json arma = (*it);

                    makeEntity(IDs::IDs::archer, entidade, arma);
                }
                break;

                case IDs::IDs::red_slime:
                {
                    
                    nlohmann::ordered_json entidade = (*it);
                    it++;
                    nlohmann::ordered_json arma = (*it);

                    makeEntity(IDs::IDs::red_slime, entidade, arma);
                }
                break;

                case IDs::IDs::platform:
                {                
                    makeEntity(IDs::IDs::platform, (*it));
                }
                break;

                case IDs::IDs::invisible_platform:
                {
                    makeEntity(IDs::IDs::invisible_platform, (*it));
                }
                break;

                default:
                    break;
            }
            it++;
        }
    }

    Caverna::~Caverna() = default;

    void Caverna::makeBackGround()
    {
        m_backGround.addLayer(CAMADA_8_1,0.0f);
        m_backGround.addLayer(CAMADA_7_1,0.3f);
        m_backGround.addLayer(CAMADA_6_1,0.05f);
        m_backGround.addLayer(CAMADA_5_1,0.1f);
        m_backGround.addLayer(CAMADA_4_1,0.15f);
        m_backGround.addLayer(CAMADA_3_1,0.2f);
        m_backGround.addLayer(CAMADA_2_1,0.4f);
        m_backGround.addLayer(CAMADA_1_1,0.6f);
    }

    void Caverna::makeMap()
    {
        std::ifstream arquivo;
        std::string linha;

        arquivo.open("../Game/includes/Levels/level-1.txt");

        if(!arquivo.is_open())
        {
            std::cout<<"Level::Caverna:: error to open the file";
            exit(1);
        }

        int j = 0;

        while(std::getline(arquivo,linha))
        {
            for(int i = 0 ; i < (int)linha.size() ; i++)
            {
                if(linha[i] != ' ')
                {
                    makeEntity(linha[i],sf::Vector2i(i,j));
                }
            }
            j++;
        }

    m_charactersList->remove(4);    
    m_charactersList->remove(4);    

        arquivo.close();
    }

    void Caverna::makePlatform(const sf::Vector2f pos)
    {
        auto* platform = new Entity::Obstacle::Platform(pos,sf::Vector2f(200.0f,40.0f), IDs::IDs::platform, IDs::IDs::cave);
        if(platform == nullptr)
        {
            std::cout<<"Level::Caverna: not possible to create the platform";
            exit(1);
        }
        auto* plat = static_cast<Entity::Entity*>(platform);
        m_obstaclesList->add(plat);
    }
}

