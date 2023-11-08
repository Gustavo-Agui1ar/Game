
#include "../includes/fases/fase.h"
#include <unistd.h>

namespace Game{

    namespace Fase{
        
        /**
         * construtor da classe fase
         * 
         * parametros:
         * 
         * ID_Fase: identificador da fase
         * ID_Fundo: identificador do fundo
        */
        
        Fase::Fase(const IDs::IDs ID_Fase, const IDs::IDs ID_Fundo):
        Ente(ID_Fase),fundo(ID_Fundo)
        {
            listaPersonagens = new Lista::ListaEntidade();
            listaObstaculos = new Lista::ListaEntidade();

            pColisao = new Gerenciador::GerenciadorDeColisao(listaPersonagens, listaObstaculos);

            if(pColisao == nullptr)
            {
                std::cout<<"Fase::Fase: nao foi possivel iniciar o pColisao";
                exit(1);
            }

           
            listenerFase = new Listener::ListenerFase();

             if(listenerFase == nullptr)
             {
                std::cout<<"Fase::Fase: nao foi possivel criar o listener da fase";
                exit(1);
             }

             listenerFase->setFase(this);
            

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
                if(getJogador() != nullptr && jogador != nullptr)
                {
                    delete(listaPersonagens);
                    jogador = nullptr;
                }
                else 
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
            Entidade::Item::Arma* armaJogador = new Entidade::Item::Arma(IDs::IDs::armaDoJogador); 
            Entidade::Personagem::Jogador::Jogador* jogador =  new Entidade::Personagem::Jogador::Jogador(pos,sf::Vector2f(30,60),250);

            if(jogador == nullptr)
            {
                std::cout<<"Fase::Fase: nao foi possvel criar o jogador";
                exit(1);
            }
            if(armaJogador == nullptr)
            {
                std::cout<<"Fase::Fase: nao foi possvel criar a arma do jogador";
                exit(1);
            }
            if(armaJogador != nullptr)
            {
                jogador->setArma(armaJogador);
            }

            this->jogador = jogador;

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
            Entidade::Item::Arma* arma = new Entidade::Item::Arma(IDs::IDs::armaDoIimigo);
            Entidade::Entidade* inimigo = nullptr;
           
            if(arma == nullptr)
            {
                std::cout<<"Fase::Fase: nao foi possivel criar a arma do inimigo";
                exit(1);
            }
            
            if(letra == 'e'){
                
                Entidade::Personagem::Inimigo::Esqueleto* esqueleto = new Entidade::Personagem::Inimigo::Esqueleto(pos,sf::Vector2f(30,60),50,this->jogador);
                esqueleto->setArma(arma);
                inimigo = static_cast<Entidade::Entidade*>(esqueleto);
            }
            else if (letra == 's'){
                
                Entidade::Personagem::Inimigo::Slime* slime = new Entidade::Personagem::Inimigo::Slime(pos,sf::Vector2f(30,60),50,this->jogador);
                slime->setArma(arma);
                inimigo = static_cast<Entidade::Entidade*>(slime);
            }


            if(inimigo == nullptr) 
            {
                std::cout<<"Fase::Fase: nao foi possivel criar o inimigo";
                exit(1);
            }
            
            listaPersonagens->addEntidade(inimigo);
            listaPersonagens->addEntidade(static_cast<Entidade::Entidade*>(arma));
            
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
                listenerFase->notificarGameOver();
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

         Entidade::Personagem::Jogador::Jogador* Fase::getJogador()
         {
            for(int i = 0; i < listaPersonagens->getTam(); i++)
            {
                Entidade::Entidade* aux = listaPersonagens->operator[](i);
                if(aux->getID() == IDs::IDs::jogador)
                {
                    return dynamic_cast<Entidade::Personagem::Jogador::Jogador*>(aux);
                }
            }
            return nullptr;
        }

        void Fase::mudarEstadoListener()
        {
            listenerFase->mudarEstado();
        }
    }
}

