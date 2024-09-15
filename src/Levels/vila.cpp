
#include "../includes/Levels/vila.h"

#define CAMADA_1_VILA "../Game/animations/background/vila/background.png"
#define CAMADA_2_VILA "../Game/animations/background/vila/middleground.png"

namespace Game::Level{


    Vila::Vila():
    Level(IDs::IDs::village, IDs::IDs::village), objCenarios()
    {
        
    }

    Vila::~Vila() = default;

    void Vila::makeBackGround()
    {
        m_backGround.addCamada(CAMADA_1_VILA, 0.0f);
        m_backGround.addCamada(CAMADA_2_VILA, 0.0f);
    }

    void Vila::makeMap()
    {
        std::ifstream arquivo;
        std::string linha;  

        arquivo.open("../Game/includes/Levels/vila.txt");

        if(!arquivo.is_open())
        {
            std::cout<<"Level::Vila: erro ao abrir arquivo a village";
            exit(1);
        }
        int j = 0;
        while(std::getline(arquivo,linha))
        {
            for(int i = 0; i < (int)linha.size(); i++)
            {
                switch (linha[i])
                {
                    case ' ':
                        break;
                    case 'n':
                        criarNpc(sf::Vector2i(i,j), IDs::IDs::barman);
                        break;
                    case 'y':
                        criarNpc(sf::Vector2i(i,j), IDs::IDs::man);
                        break;
                    case 'g':
                        criarNpc(sf::Vector2i(i,j), IDs::IDs::woman);
                        break;
                    case 'v':
                        criarNpc(sf::Vector2i(i,j), IDs::IDs::old_man);
                        break;
                    case 'a':
                        criarCasaMedia(sf::Vector2i(i,j));
                        break;
                    case 'b':
                        criarCasaGrande(sf::Vector2i(i,j));
                        break;
                    case 'c':
                        criarCasaPequena(sf::Vector2i(i,j));
                        break;
                    case 'm':
                        criarCaixotes(sf::Vector2i(i,j));
                        break;
                    case 'p':
                        criarPostes(sf::Vector2i(i,j));
                        break;
                    case 'i':
                        criarCarroca(sf::Vector2i(i,j));
                        break;
                    default:
                        makeEntity(linha[i],sf::Vector2i(i,j));
                        break;
                }
            }
            j++;
        }
        arquivo.close();
    }

    void Vila::criarNpc(sf::Vector2i pos, const IDs::IDs IDnpc)
    {
        auto* npc = new Entity::Character::Npc::Npc(sf::Vector2f(pos.x * 50.f, pos.y * 50.f), IDnpc);

        if(npc == nullptr)
        {
            std::cout<<"village::erro ao criar npc";
            exit(1);
        } 

        m_charactersList->addEntidade(static_cast<Entity::Entity*>(npc));
    }

    void Vila::criarCasaPequena (sf::Vector2i pos)
    {
        auto* casa = new Entity::Obstacle::House(sf::Vector2f(300.0f, 250.0f), IDs::IDs::small_house, sf::Vector2f(pos.x * 50.f, pos.y * 50.f + 10.f)); 

        casa->setTexture("../Game/animations/background/cenarioVila/house-c.png");

        m_obstaclesList->addEntidade(static_cast<Entity::Entity*>(casa));
    }

    void Vila::criarCasaMedia (sf::Vector2i pos)
    {   
        auto* casa = new Entity::Obstacle::House(sf::Vector2f(250.0f, 300.0f), IDs::IDs::middle_house, sf::Vector2f(pos.x * 50.f - 30.f, pos.y * 50.f - 40.f)); 

        casa->setTexture("../Game/animations/background/cenarioVila/house-a.png");

        m_obstaclesList->addEntidade(static_cast<Entity::Entity*>(casa));
    }
    
    void Vila::criarCasaGrande(sf::Vector2i pos)
    {
        auto* casa = new Entity::Obstacle::House(sf::Vector2f(300.0f, 350.0f), IDs::IDs::big_house, sf::Vector2f(pos.x * 50.f - 30.f, pos.y * 50.f - 90.f)); 

        casa->setTexture("../Game/animations/background/cenarioVila/house-b.png");

        m_obstaclesList->addEntidade(static_cast<Entity::Entity*>(casa));
    }

    void Vila::makePlatform(const sf::Vector2f pos)
    {
        auto* plataforma = new Entity::Obstacle::Platform(pos,sf::Vector2f(200.0f,40.0f),IDs::IDs::platform,  IDs::IDs::village);
        if(plataforma == nullptr)
        {
            std::cout<<"Level::Vila: nao foi possivel criar uma plataforma";
            exit(1);
        }
        auto* plat = static_cast<Entity::Entity*>(plataforma);
        m_obstaclesList->addEntidade(plat);
    }
    
    void Vila::criarCaixotes(const sf::Vector2i pos)
    {
        sf::RectangleShape caixa(sf::Vector2f(50.f, 50.f));

        auto const* texCaixa = new sf::Texture(m_graphic->carregarTextura("../Game/animations/background/cenarioVila/cenario1.png"));
        
        caixa.setPosition(sf::Vector2f(pos.x * 50.f , pos.y * 50.f + 10.f));
        caixa.setTexture(texCaixa);

        objCenarios.push_back(caixa);
    }
    void Vila::criarPostes(const sf::Vector2i pos)
    {
        sf::RectangleShape poste(sf::Vector2f(50.f, 100.f));

        auto const* texPoste = new sf::Texture(m_graphic->carregarTextura("../Game/animations/background/cenarioVila/cenario2.png"));
        
        poste.setPosition(sf::Vector2f(pos.x * 50.f , pos.y * 50.f + 10.f));
        poste.setTexture(texPoste);

        objCenarios.push_back(poste);
    }
    
    void Vila::criarCarroca(const sf::Vector2i pos)
    {
        sf::RectangleShape carroca(sf::Vector2f(100.f, 100.f));

        auto const* texCarroca = new sf::Texture(m_graphic->carregarTextura("../Game/animations/background/cenarioVila/cenario3.png"));
        
        carroca.setPosition(sf::Vector2f(pos.x * 50.f , pos.y * 50.f + 10.f));
        carroca.setTexture(texCarroca);

        objCenarios.push_back(carroca);
    }
    

    /**
     * @brief atualiza a lista de entidades  juntamente com a verificacao da colisao e atulizacao do fundo da fase
    */
    void Vila::execute()
    {
        m_player = getPlayer();
        if(m_player)
        {
            m_backGround.executar();

            m_obstaclesList->executar();
            desenharObjsCenario();
            m_charactersList->executar();
            

            m_collisionManager->executar();

        }
        else{
            m_observerLevel->notificarGameOver();
        }
    }

    /**
     * @brief metodo responsavel por desenhar as
     * listas  de  personagens  e obstaculos
    */
    void Vila::draw()
    {
        m_backGround.executar();

        m_obstaclesList->desenharEntidades();
        desenharObjsCenario();
        m_charactersList->desenharEntidades();

    }

    void Vila::desenharObjsCenario()
    {
        auto it = objCenarios.begin();

        while(it != objCenarios.end())
        {
            m_graphic->desenhaElemento((*it));
            it++;
        }
    }
}