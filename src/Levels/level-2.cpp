
#include "../includes/Levels/level-2.h"

#define CAMADA_1_5 "../Game/animations/background/level-5/camada-1.png"
#define CAMADA_2_5 "../Game/animations/background/level-5/camada-2.png"
#define CAMADA_3_5 "../Game/animations/background/level-5/camada-3.png"
#define CAMADA_4_5 "../Game/animations/background/level-5/camada-4.png"
#define CAMADA_5_5 "../Game/animations/background/level-5/camada-5.png"
#define CAMADA_6_5 "../Game/animations/background/level-5/camada-6.png"


namespace Game::Level{


        Forest::Forest():
        Level(IDs::IDs::dawn_forest, IDs::IDs::dawn_forest)
        {

        }

        Forest::Forest(nlohmann::ordered_json entidades):
        Level(IDs::IDs::dawn_forest, IDs::IDs::dawn_forest)
        {
            makeBackGround();
            loadGame(entidades);
        }

        void Forest::loadGame(nlohmann::ordered_json entidades)
        {
            for(auto it = entidades.begin(); it != entidades.end(); it++)
            {
                IDs::IDs ID = (*it)["ID"].template get<IDs::IDs>();

                switch(ID)
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
            }
        }

        Forest::~Forest() = default;

        void Forest::makeBackGround ()
        {
            m_backGround.addLayer(CAMADA_1_5,0.0f);
            m_backGround.addLayer(CAMADA_2_5,0.4f);
            m_backGround.addLayer(CAMADA_3_5,0.15f);
            m_backGround.addLayer(CAMADA_4_5,0.2f);
            m_backGround.addLayer(CAMADA_5_5,0.25f);
            m_backGround.addLayer(CAMADA_6_5,0.3f);
        }

        void Forest::makeMap()
        {
            std::ifstream arquivo;
            std::string linha;

            arquivo.open("../Game/includes/Levels/level-2.txt");

            if(!arquivo.is_open())
            {
                std::cout<<"Level::Forest: error to open the file";
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

        void Forest::makePlatform(const sf::Vector2f pos)
        {
            auto* platform = new Entity::Obstacle::Platform(pos,sf::Vector2f(200.0f,40.0f),IDs::IDs::platform,  IDs::IDs::dawn_forest);
            if(platform == nullptr)
            {
                std::cout<<"Level::Forest:not possible to create the platform";
                exit(1);
            }
            auto* plat = static_cast<Entity::Entity*>(platform);
            m_obstaclesList->add(plat);
        }
}
