
#include "../includes/fases/level-1.h"

#define CAMADA_1_1 "../Game/animations/backgorund/level-1/camada-1.png"
#define CAMADA_2_1 "../Game/animations/backgorund/level-1/camada-2.png"
#define CAMADA_3_1 "../Game/animations/backgorund/level-1/camada-3.png"
#define CAMADA_4_1 "../Game/animations/backgorund/level-1/camada-4.png"
#define CAMADA_5_1 "../Game/animations/backgorund/level-1/camada-5.png"
#define CAMADA_6_1 "../Game/animations/backgorund/level-1/camada-6.png"
#define CAMADA_7_1 "../Game/animations/backgorund/level-1/camada-7.png"
#define CAMADA_8_1 "../Game/animations/backgorund/level-1/camada-8.png"


namespace Game{

    namespace Fase{
        
        /**
         * construtor da classe caverna
        */

        Caverna::Caverna():
        Fase(IDs::IDs::caverna, IDs::IDs::caverna)
        {

        }

        /**
         * destrutor da classe
        */

        Caverna::~Caverna()
        {

        }

        /**
         * metodo responsavel pela criacao do fundo da fase caverna
        */

        void Caverna::criarFundo()
        {
            fundo.addCamada(CAMADA_8_1,0.0f);
            fundo.addCamada(CAMADA_7_1,0.3f);
            fundo.addCamada(CAMADA_6_1,0.05f);
            fundo.addCamada(CAMADA_5_1,0.1f);
            fundo.addCamada(CAMADA_4_1,0.15f);
            fundo.addCamada(CAMADA_3_1,0.2f);
            fundo.addCamada(CAMADA_2_1,0.4f);
            fundo.addCamada(CAMADA_1_1,0.6f);
        }


        /**
         * metodo  que  cria  fase  com  base  em seu arquivo txt
         * quando nescessario chama o metodo criador de entidades
        */

        void Caverna::criarMapa()
        {
            std::ifstream arquivo;
            std::string linha;

            arquivo.open("..//Game//includes//fases//fase-1.txt");

            if(!arquivo.is_open())
            {
                std::cout<<"Fase::Caverna: erro ao abrir arquivo da fase caverna";
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

        listaPersonagens->removerEntidade(2);    
        listaPersonagens->removerEntidade(3);    

            arquivo.close();
        }

        /**
         * metodo que cria uma plataforma
        */

        void Caverna::criarPlataforma(const sf::Vector2f pos)
        {
            Entidade::Obstaculo::Plataforma* plataforma = new Entidade::Obstaculo::Plataforma(pos,sf::Vector2f(200.0f,40.0f),IDs::IDs::caverna);
            if(plataforma == nullptr)
            {
                std::cout<<"Fase::Caverna: nao foi possivel criar uma plataforma";
                exit(1);
            }
            Entidade::Entidade* plat = static_cast<Entidade::Entidade*>(plataforma);
            listaObstaculos->addEntidade(plat);
        }

    }

}

