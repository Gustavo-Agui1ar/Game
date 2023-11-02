
#include "../../includes/fases/fase.h"
#include <unistd.h>

namespace Game{

    namespace Fase{

        using namespace Entidade;
        using namespace Personagem;

        /**
         * construtor da classe fase
         * 
         * parametros:
         * 
         * ID_Fase: identificador da fase
         * ID_Fundo: identificador do fundo
        */
        
        Fase::Fase::Fase(const IDs::IDs ID_Fase, const IDs::IDs ID_Fundo):
        Ente(ID_Fase),fundo(ID_Fundo)
        {
            listaPersonagens = new Lista::ListaEntidade();
            listaObstaculos = new Lista::ListaEntidade();

            pColisao = new Gerenciador::GerenciadorDeColisao(listaPersonagens, listaObstaculos);

            if(pColisao == nullptr)
            {
                std::cout<<"n�o foi possivel iniciar o pColisao";
                exit(1);
            }
        }

        /**
         * destrutor da fase desaloca todos
         * os  ponteiros existentes da fase 
        */

        Fase::~Fase()
        {
            if(pColisao != nullptr)
            {
                delete(pColisao);
            }
            
            if(listaPersonagens != nullptr)
            {
                if(getJogador() != nullptr)
                {
                    delete(listaPersonagens);
                } 

                listaPersonagens = nullptr;
            }

            if(listaObstaculos != nullptr)
            {
                delete(listaObstaculos);
                listaObstaculos = nullptr;
            }

        }

        /**
         * metodo responsavel por criar o jogador da fase
         * 
         * parametros:
         * 
         * pos: posicao de onde o player deve ser criado
        */

        void Fase::criarJogador(const sf::Vector2f pos)
        {
            Item::Arma* armaJogador = new Item::Arma(IDs::IDs::armaDoJogador); 
            Jogador::Jogador* jogador =  new Jogador::Jogador(pos,sf::Vector2f(30,60),250);

            if(jogador == nullptr)
            {
                std::cout<<"nao foi possvel criar o jogador";
                exit(1);
            }
            if(armaJogador == nullptr)
            {
                std::cout<<"nao foi possvel criar a arma";
                exit(1);
            }
            if(armaJogador != nullptr)
            {
                jogador->setArma(armaJogador);
            }

            Gerenciador::GerenciadorDeEventos* pEvento = pEvento->getGerenciadorDeEventos();
            pEvento->setJogador(jogador);

            listaPersonagens->addEntidade(static_cast<Entidade::Entidade*>(jogador));
            listaPersonagens->addEntidade(static_cast<Entidade::Entidade*>(armaJogador));

        }

        /**
         * metodo rtesponsavel por criar o inimigo da fase
         * 
         * parametros:
         * 
         * pos: posicao de onde o inimigo deve ser criado
         * letra: indetificador de qual inimigo deve ser criado
        */

        void Fase::criarInimigo(const sf::Vector2f pos, const char letra)
        {
            Jogador::Jogador* jogador = getJogador();
            Item::Arma* arma = new Item::Arma(IDs::IDs::armaDoIimigo);
            Entidade::Entidade* inimigo = nullptr;
            if(arma == nullptr){
                std::cout<<"nao foi possivel criar uma arma";
                exit(1);
            }

            if(letra == 'e'){
                
                Inimigo::Esqueleto* esqueleto = new Inimigo::Esqueleto(pos,sf::Vector2f(30,60),50,jogador);
                esqueleto->setArma(arma);
                inimigo = static_cast<Entidade::Entidade*>(esqueleto);
            }
            else if (letra == 's'){
                
                Inimigo::Slime* slime = new Inimigo::Slime(pos,sf::Vector2f(30,60),50,jogador);
                slime->setArma(arma);
                inimigo = static_cast<Entidade::Entidade*>(slime);
            }


            if(inimigo != nullptr) 
            {
                listaPersonagens->addEntidade(inimigo);
                listaPersonagens->addEntidade(static_cast<Entidade::Entidade*>(arma));
            }
            
            
        }

        /**
         * metodo responsavel por analizar qual entidade deve ser criada
         * 
         * parametros:
         * 
         * letra: inde3tificador para filtrar qual entidade deve ser criada
         * pos: posicao inicial da entidade
        */

        void Fase::criarEntidade(char letra, const sf::Vector2i pos)
        {
            switch(letra)
            {
                case('e'):
                    criarInimigo(sf::Vector2f(pos.x * 50.0f, pos.y * 50.0f),letra);
                    break;
                case('s'):
                    criarInimigo(sf::Vector2f(pos.x * 50.0f, pos.y * 50.0f),letra);
                    break;
                case('#'):
                    criarPlataforma(sf::Vector2f(pos.x * 50.0f, pos.y * 50.0f));
                    break;
                case('j'):
                    criarJogador(sf::Vector2f(pos.x * 50.0f, pos.y * 50.0f));
                    break;
            }
        }

        /**
         * atualiza a lista de entidades  juntamente com a verificacao da colisao e atulizacao do fundo da fase
        */

        void Fase::executar()
        {
            
            if(getJogador() != nullptr)
            {
                fundo.executar();

                desenhar();

                pColisao->executar();
            }
            else{
                std::cout<<"game over";
                sleep(2);
                exit(1);
            }
        }

        /**
         * metodo responsascvel por atualizar as
         * listas  de  personagens  e obstaculos
        */

        void Fase::desenhar()
        {
            listaObstaculos->executar();
            listaPersonagens->executar();

        }

        /**
         * metodo   que  retorna  o  ponteiro  do
         * jogador se existir se nao retorna null
        */

         Jogador::Jogador* Fase::getJogador()
         {
            for(int i = 0; i < listaPersonagens->getTam(); i++)
            {
                Entidade::Entidade* ent = listaPersonagens->operator[](i);
                if(ent->getID() == IDs::IDs::jogador)
                {
                    return dynamic_cast<Jogador::Jogador*>(ent);
                }
            }
            return nullptr;
        }
    }
}

