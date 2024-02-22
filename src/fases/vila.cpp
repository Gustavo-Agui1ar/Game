
#include "../includes/fases/vila.h"

#define CAMADA_1_VILA "../Game/animations/backgorund/vila/background.png"
#define CAMADA_2_VILA "../Game/animations/backgorund/vila/middleground.png"

namespace Game{

    namespace Fase{

        Vila::Vila():
        Fase(IDs::IDs::vila, IDs::IDs::vila), objCenarios()
        {
           
        }

        Vila::~Vila()
        {
           
        }

        void Vila::criarFundo()
        {
            fundo.addCamada(CAMADA_1_VILA, 0.0f);
            fundo.addCamada(CAMADA_2_VILA, 0.0f);
        }

        void Vila::criarMapa()
        {
             std::ifstream arquivo;
            std::string linha;

            arquivo.open("..//Game//includes//fases//vila.txt");

            if(!arquivo.is_open())
            {
                std::cout<<"Fase::Vila: erro ao abrir arquivo a vila";
                exit(1);
            }

            int j = 0;

            while(std::getline(arquivo,linha))
            {
                for(int i = 0 ; i < (int)linha.size() ; i++)
                {
                    switch (linha[i])
                    {
                        case(' '):
                            break;
                        case('n'):
                            criarNpc(sf::Vector2i(i,j), IDs::IDs::barman);
                            break;
                        case('g'):
                            criarNpc(sf::Vector2i(i,j), IDs::IDs::mulher);
                            break;
                        case('v'):
                            criarNpc(sf::Vector2i(i,j), IDs::IDs::velho);
                            break;
                        case('a'):
                            criarCasaMedia(sf::Vector2i(i,j));
                            break;
                        case('b'):
                            criarCasaGrande(sf::Vector2i(i,j));
                            break;
                        case('c'):
                            criarCasaPequena(sf::Vector2i(i,j));
                            break;
                        case('m'):
                            criarCaixotes(sf::Vector2i(i,j));
                            break;
                        case('p'):
                            criarPostes(sf::Vector2i(i,j));
                            break;
                        case('i'):
                            criarCarroca(sf::Vector2i(i,j));
                            break;
                        default:
                            criarEntidade(linha[i],sf::Vector2i(i,j));
                            break;
                    }
                }
                j++;
            }
            arquivo.close();
        }

        void Vila::criarNpc(sf::Vector2i pos, const IDs::IDs IDnpc)
        {
            //provisorio
            Entidade::Personagem::Npc::Npc* npc = new Entidade::Personagem::Npc::Npc(sf::Vector2f(pos.x * 50.f, pos.y * 50.f), IDnpc);

            if(npc == nullptr)
            {
                std::cout<<"vila::erro ao criar npc";
                exit(1);
            } 

            listaPersonagens->addEntidade(static_cast<Entidade::Entidade*>(npc));
        }

        void Vila::criarCasaPequena (sf::Vector2i pos)
        {
            Entidade::Obstaculo::Casa* casa = new Entidade::Obstaculo::Casa(sf::Vector2f(300.0f, 250.0f), IDs::IDs::casa_pequena, sf::Vector2f(pos.x * 50.f, pos.y * 50.f + 10.f)); 

            casa->setTextura("../Game/animations/cenarioVila/house-c.png");

            listaObstaculos->addEntidade(static_cast<Entidade::Entidade*>(casa));
        }
        void Vila::criarCasaMedia (sf::Vector2i pos)
        {   
            Entidade::Obstaculo::Casa* casa = new Entidade::Obstaculo::Casa(sf::Vector2f(250.0f, 300.0f), IDs::IDs::casa_media, sf::Vector2f(pos.x * 50.f - 30.f, pos.y * 50.f - 40.f)); 

            casa->setTextura("../Game/animations/cenarioVila/house-a.png");

            listaObstaculos->addEntidade(static_cast<Entidade::Entidade*>(casa));
        }
       
        void Vila::criarCasaGrande(sf::Vector2i pos)
        {
            Entidade::Obstaculo::Casa* casa = new Entidade::Obstaculo::Casa(sf::Vector2f(300.0f, 350.0f), IDs::IDs::casa_grande, sf::Vector2f(pos.x * 50.f - 30.f, pos.y * 50.f - 90.f)); 

            casa->setTextura("../Game/animations/cenarioVila/house-b.png");

            listaObstaculos->addEntidade(static_cast<Entidade::Entidade*>(casa));
        }

        void Vila::criarPlataforma(const sf::Vector2f pos)
        {
            Entidade::Obstaculo::Plataforma* plataforma = new Entidade::Obstaculo::Plataforma(pos,sf::Vector2f(200.0f,40.0f),IDs::IDs::plataforma,  IDs::IDs::vila);
            if(plataforma == nullptr)
            {
                std::cout<<"Fase::Vila: nao foi possivel criar uma plataforma";
                exit(1);
            }
            Entidade::Entidade* plat = static_cast<Entidade::Entidade*>(plataforma);
            listaObstaculos->addEntidade(plat);
        }
       
        void Vila::criarCaixotes(const sf::Vector2i pos)
        {
            sf::RectangleShape caixa(sf::Vector2f(50.f, 50.f));

            sf::Texture* texCaixa = new sf::Texture(pGrafico->carregarTextura("../Game/animations/cenarioVila/cenario1.png"));
            
            caixa.setPosition(sf::Vector2f(pos.x * 50.f , pos.y * 50.f + 10.f));
            caixa.setTexture(texCaixa);

            objCenarios.push_back(caixa);
        }
        void Vila::criarPostes(const sf::Vector2i pos)
        {
            sf::RectangleShape poste(sf::Vector2f(50.f, 100.f));

            sf::Texture* texPoste = new sf::Texture(pGrafico->carregarTextura("../Game/animations/cenarioVila/cenario2.png"));
            
            poste.setPosition(sf::Vector2f(pos.x * 50.f , pos.y * 50.f + 10.f));
            poste.setTexture(texPoste);

            objCenarios.push_back(poste);
        }
        
        void Vila::criarCarroca(const sf::Vector2i pos)
        {
            sf::RectangleShape carroca(sf::Vector2f(100.f, 100.f));

            sf::Texture* texCarroca = new sf::Texture(pGrafico->carregarTextura("../Game/animations/cenarioVila/cenario3.png"));
            
            carroca.setPosition(sf::Vector2f(pos.x * 50.f , pos.y * 50.f + 10.f));
            carroca.setTexture(texCarroca);

            objCenarios.push_back(carroca);
        }
        

        /**
         * @brief atualiza a lista de entidades  juntamente com a verificacao da colisao e atulizacao do fundo da fase
        */
        void Vila::executar()
        {
            jogador = getJogador();
            if(jogador)
            {
                fundo.executar();

                listaObstaculos->executar();
                desenharObjsCenario();
                listaPersonagens->executar();
                

                pColisao->executar();

            }
            else{
                listenerFase->notificarGameOver();
            }
        }

        /**
         * @brief metodo responsavel por desenhar as
         * listas  de  personagens  e obstaculos
        */
        void Vila::desenhar()
        {
            fundo.executar();

            listaObstaculos->desenharEntidades();
            desenharObjsCenario();
            listaPersonagens->desenharEntidades();

        }

        void Vila::desenharObjsCenario()
        {
            std::vector<sf::RectangleShape>::iterator it = objCenarios.begin();

            while(it != objCenarios.end())
            {
                pGrafico->desenhaElemento((*it));
                it++;
            }
        }
    }
}