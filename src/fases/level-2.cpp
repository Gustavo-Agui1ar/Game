
#include "..\includes\fases\level-2.h"

#define CAMADA_1_5 "../Game/animations/backgorund/level-5/camada-1.png"
#define CAMADA_2_5 "../Game/animations/backgorund/level-5/camada-2.png"
#define CAMADA_3_5 "../Game/animations/backgorund/level-5/camada-3.png"
#define CAMADA_4_5 "../Game/animations/backgorund/level-5/camada-4.png"
#define CAMADA_5_5 "../Game/animations/backgorund/level-5/camada-5.png"
#define CAMADA_6_5 "../Game/animations/backgorund/level-5/camada-6.png"


namespace Game{

    namespace Fase{


        /**
         * @brief construtor da classe floresta
        */
        Forest::Forest():
        Fase(IDs::IDs::floresta_do_amanhecer, IDs::IDs::floresta_do_amanhecer)
        {

        }
        
        /**
         * @brief  construtora da classe floresta
         * 
         * @param entidades json contendo informacoes das entidades a serem criadas na fase
        */
        Forest::Forest(nlohmann::ordered_json entidades):
        Fase(IDs::IDs::floresta_do_amanhecer, IDs::IDs::floresta_do_amanhecer)
        {
            criarFundo();
            recuperarJogada(entidades);
        }

        /**
         * @brief metodo que cria as entidades da fase
         * 
         * @param entidades json contendo as entidades a serem criadas na fase
        */
        void Forest::recuperarJogada(nlohmann::ordered_json entidades)
        {
            nlohmann::ordered_json::iterator it;
            int i;

            for(it = entidades.begin(),  i = 0 ; it != entidades.end() ; it++, i++)
            {
                IDs::IDs ID = (*it)["ID"].template get<IDs::IDs>();

                switch(ID)
                {
                    case(IDs::IDs::jogador):
                    {
                        i++;
                        nlohmann::ordered_json entidade = (*it);
                        it++;
                        nlohmann::ordered_json arma = (*it);
                        it++;
                        nlohmann::ordered_json projetil = (*it);

                        criarEntidade(IDs::IDs::jogador, entidade, arma, projetil);
                    }
                    break;

                    case(IDs::IDs::esqueleto):
                    {
                        i++;
                        nlohmann::ordered_json entidade = (*it);
                        it++;
                        nlohmann::ordered_json arma = (*it);

                        criarEntidade(IDs::IDs::esqueleto, entidade, arma);
                    }
                    break;

                    case(IDs::IDs::arqueiro):
                    {
                        i++;
                        nlohmann::ordered_json entidade = (*it);
                        it++;
                        nlohmann::ordered_json arma = (*it);

                        criarEntidade(IDs::IDs::arqueiro, entidade, arma);
                    }
                    break;

                    case(IDs::IDs::red_slime):
                    {
                        i++;
                        nlohmann::ordered_json entidade = (*it);
                        it++;
                        nlohmann::ordered_json arma = (*it);

                        criarEntidade(IDs::IDs::red_slime, entidade, arma);
                    }
                    break;

                    case(IDs::IDs::plataforma):
                    {                
                        criarEntidade(IDs::IDs::plataforma, (*it));
                    }
                    break;

                    case(IDs::IDs::plataforma_invisivel):
                    {
                        criarEntidade(IDs::IDs::plataforma_invisivel, (*it));
                    }
                    break;

                    default:
                        break;
                } 
            }
        }
        /**
         * @brief destrutor da classe
        */
        Forest::~Forest()
        {

        }

        /**
         * @brief metodo responsavel pela criacao do fundo da fase floresta
        */
        void Forest::criarFundo()
        {
            fundo.addCamada(CAMADA_1_5,0.0f);
            fundo.addCamada(CAMADA_2_5,0.4f);
            fundo.addCamada(CAMADA_3_5,0.15f);
            fundo.addCamada(CAMADA_4_5,0.2f);
            fundo.addCamada(CAMADA_5_5,0.25f);
            fundo.addCamada(CAMADA_6_5,0.3f);
        }

         /**
         * @brief metodo  que  cria fase  com  base  em  seu arquivo txt
         * quando nescessario chama o metodo criador de entidades
        */
        void Forest::criarMapa()
        {
            std::ifstream arquivo;
            std::string linha;

            arquivo.open("..//Game//includes//fases//fase-2.txt");

            if(!arquivo.is_open())
            {
                std::cout<<"Fase::Forest: erro ao abrir arquivo da fase floresta";
                exit(1);
            }

            int j = 0;

            while(std::getline(arquivo,linha))
            {
                for(int i = 0 ; i < (int)linha.size() ; i++)
                {
                    if(linha[i] != ' ')
                    {
                        criarEntidade(linha[i],sf::Vector2i(i,j));
                    }
                }
                j++;
            }
            listaPersonagens->removerEntidade(4);
            listaPersonagens->removerEntidade(4);
            arquivo.close();
        }

        /**
         * @brief metodo que cria uma plataforma
         * 
         * @param pos posicao da plataforma
        */
        void Forest::criarPlataforma(const sf::Vector2f pos)
        {
            Entidade::Obstaculo::Plataforma* plataforma = new Entidade::Obstaculo::Plataforma(pos,sf::Vector2f(200.0f,40.0f),IDs::IDs::plataforma,  IDs::IDs::floresta_do_amanhecer);
            if(plataforma == nullptr)
            {
                std::cout<<"Fase::Forest: nao foi possivel criar uma plataforma";
                exit(1);
            }
            Entidade::Entidade* plat = static_cast<Entidade::Entidade*>(plataforma);
            listaObstaculos->addEntidade(plat);
        }
    }
}
