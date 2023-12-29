
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
        
        Listener::ListenerFase* Fase::listenerFase = nullptr;

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

            if(listenerFase == nullptr)
            {
                listenerFase = new Listener::ListenerFase();
                listenerFase->setFase(this);
            }

            listenerFase->mudarEstado(true);
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
            
            if(listenerFase != nullptr){
                delete(listenerFase);
                listenerFase = nullptr;
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
            Entidade::Personagem::Jogador::Jogador* jogador =  new Entidade::Personagem::Jogador::Jogador(pos);

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
           
            jogador->setArma(armaJogador);
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
            Entidade::Entidade* personagem = nullptr;
           
            if(arma == nullptr)
            {
                std::cout<<"Fase::Fase: nao foi possivel criar a arma do inimigo";
                exit(1);
            }
            
            if(letra == 'e'){
                
                Entidade::Personagem::Inimigo::Esqueleto* esqueleto = new Entidade::Personagem::Inimigo::Esqueleto(pos, this->jogador);
                if(esqueleto == nullptr)
                {
                    std::cout<<"Fase::Fase: nao foi possivel criar um slime";
                    exit(1);
                }
                
                esqueleto->setArma(arma);
                personagem = static_cast<Entidade::Entidade*>(esqueleto);
            }
            else if (letra == 's'){
                
                Entidade::Personagem::Inimigo::Slime* slime = new Entidade::Personagem::Inimigo::Slime(pos, this->jogador);
                if(slime == nullptr)
                {
                    std::cout<<"Fase::Fase: nao foi possivel criar um slime";
                    exit(1);
                }
                slime->setArma(arma);
                personagem = static_cast<Entidade::Entidade*>(slime);
            }
            
             if(personagem != nullptr){
                listaPersonagens->addEntidade(personagem);
                if(arma != nullptr){
                    listaPersonagens->addEntidade(arma);
                }
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
                case('v'):
                    criarPlataformaInvisivel(sf::Vector2f(pos.x * 50.0f, pos.y * 50.0f));
                    break;
            }
        }

        void Fase::criarEntidade(IDs::IDs ID, nlohmann::ordered_json entidade , nlohmann::ordered_json arma)
        {
            Entidade::Entidade* personagem = nullptr;
            Entidade::Entidade* armaPersonagem = nullptr;

            switch(ID)
            {
                case(IDs::IDs::jogador):
                {
                    jogador = new Entidade::Personagem::Jogador::Jogador(entidade);
                    
                    if(jogador == nullptr)
                    {
                        std::cout<<"Fase::Fase: nao foi possvel criar o jogador";
                        exit(1);
                    }

                    Entidade::Item::Arma* pArma = new Entidade::Item::Arma(arma);
                    
                    if(pArma == nullptr)
                    {
                        std::cout << "Fase::nao foi possivel criar espada do jogador" << std::endl;
                        exit(1);
                    }

                    jogador->setArma(pArma);
                    personagem = static_cast<Entidade::Entidade*>(this->jogador);
                    armaPersonagem = static_cast<Entidade::Entidade*>(pArma);
                }
                break;

                case(IDs::IDs::esqueleto):
                {
                    Entidade::Personagem::Inimigo::Esqueleto* esqueleto = new Entidade::Personagem::Inimigo::Esqueleto(entidade, this->jogador); 
                    
                     if(esqueleto == nullptr)
                    {
                        std::cout<<"Fase::Fase: nao foi possvel criar o esqueleto";
                        exit(1);
                    }

                    Entidade::Item::Arma* pArma = new Entidade::Item::Arma(arma);
                    
                    if(pArma == nullptr)
                    {
                        std::cout << "Fase::nao foi possivel criar espada do inimigo" << std::endl;
                        exit(1);
                    }

                    esqueleto->setArma(pArma);
                    personagem = static_cast<Entidade::Entidade*>(esqueleto);
                    armaPersonagem = static_cast<Entidade::Entidade*>(pArma);
                }
                break;

                case(IDs::IDs::red_slime):
                {
                    Entidade::Personagem::Inimigo::Slime* slime = new Entidade::Personagem::Inimigo::Slime(entidade, this->jogador); 
                    
                     if(slime == nullptr)
                    {
                        std::cout<<"Fase::Fase: nao foi possvel criar o slime";
                        exit(1);
                    }

                    Entidade::Item::Arma* pArma = new Entidade::Item::Arma(arma);
                    
                    if(pArma == nullptr)
                    {
                        std::cout << "Fase::nao foi possivel criar espada do inimigo" << std::endl;
                        exit(1);
                    }

                    slime->setArma(pArma);
                    personagem = static_cast<Entidade::Entidade*>(slime);
                    armaPersonagem = static_cast<Entidade::Entidade*>(pArma);
                }
                break;

                case(IDs::IDs::plataforma):
                {
                    Entidade::Obstaculo::Plataforma* plataforma = new Entidade::Obstaculo::Plataforma(entidade, IDs::IDs::plataforma, getID());

                    if(plataforma == nullptr)
                    {
                        std::cout<<"Fase::Fase: nao foi possvel criar a plataforma";
                        exit(1);
                    } 
                     personagem = static_cast<Entidade::Entidade*>(plataforma);                   
                }
                break;

                case(IDs::IDs::plataforma_invisivel):
                {
                     Entidade::Obstaculo::Plataforma* plataforma = new Entidade::Obstaculo::Plataforma(entidade, IDs::IDs::plataforma_invisivel, IDs::IDs::plataforma_invisivel);

                    if(plataforma == nullptr)
                    {
                        std::cout<<"Fase::Fase: nao foi possvel criar a plataforma";
                        exit(1);
                    } 
                     personagem = static_cast<Entidade::Entidade*>(plataforma); 
                }
                break;

                default:
                    break;
            }

            switch (ID)
            {
                case (IDs::IDs::plataforma):
                    listaObstaculos->addEntidade(personagem);
                    break;
                case (IDs::IDs::plataforma_invisivel):
                    listaObstaculos->addEntidade(personagem);
                    break;
                
                default:
                    listaPersonagens->addEntidade(personagem);
                    listaPersonagens->addEntidade(armaPersonagem);
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

                listaObstaculos->executar();
                listaPersonagens->executar();

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
            fundo.executar();

            listaObstaculos->desenharEntidades();
            listaPersonagens->desenharEntidades();

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

        void Fase::mudarEstadoListener(const bool ativo)
        {
            listenerFase->mudarEstado(ativo);
        }

        nlohmann::ordered_json Fase::salvarFase()
        {
            nlohmann::ordered_json json = salvarEnte();
          
            return json;
        }

        nlohmann::ordered_json Fase::salvarEntidades()
        {
            nlohmann::ordered_json json;

            for(int i = 0 ; i < listaPersonagens->getTam() ; i++)
            {
                Entidade::Entidade* entidade = listaPersonagens->operator[](i);
                if(entidade != nullptr)
                {
                    nlohmann::ordered_json jsonEntidade = entidade->salvar();
                    json.push_back(jsonEntidade);
                }
            }

             for(int i = 0 ; i < listaObstaculos->getTam() ; i++)
            {
                Entidade::Entidade* entidade = listaObstaculos->operator[](i);
                if(entidade != nullptr)
                {
                    nlohmann::ordered_json jsonEntidade = entidade->salvar();
                    json.push_back(jsonEntidade);
                }
            }

            return json;
        }

        void Fase::criarPlataformaInvisivel(const sf::Vector2f pos)
        {
            
            Entidade::Obstaculo::Plataforma* plataforma = new Entidade::Obstaculo::Plataforma(pos,sf::Vector2f(50.0f,50.0f), IDs::IDs::plataforma_invisivel, IDs::IDs::plataforma_invisivel);
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

