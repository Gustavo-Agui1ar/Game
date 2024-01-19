
#include "../includes/fases/fase.h"
#include <unistd.h>

namespace Game{

    namespace Fase{
        
        Listener::ListenerFase* Fase::listenerFase = nullptr;
        
        /**
         * @brief construtor da classe fase
         * 
         * @param ID_Fase identificador da fase
         * @param ID_Fundo identificador do fundo
        */
        Fase::Fase(const IDs::IDs ID_Fase, const IDs::IDs ID_Fundo):
        Ente(ID_Fase),fundo(ID_Fundo)
        {
            listaPersonagens = new Lista::ListaEntidade();
            listaObstaculos = new Lista::ListaEntidade();

            pColisao = Gerenciador::GerenciadorDeColisao::getGerenciadorDeColisao();

            pColisao->setListaObstaculo(listaObstaculos);
            pColisao->setListaPersonagem(listaPersonagens);

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
         * @brief destrutor da fase desaloca todos
         * os ponteiros existentes da fase 
        */
        Fase::~Fase()
        {
            if(pColisao != nullptr)
            {
                pColisao->limparListas();
                pColisao = nullptr;
            }
            
            if(listenerFase != nullptr){
                delete(listenerFase);
                listenerFase = nullptr;
            }
        }

        /**
         * @brief metodo responsavel por criar o jogador da fase
         * 
         * @param pos posicao de onde o player deve ser criado
        */
        void Fase::criarJogador(const sf::Vector2f pos)
        {
            Entidade::Arma::Arma* armaJogador = new Entidade::Arma::Arma(IDs::IDs::armaDoJogador); 
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
         * @brief metodo responsavel por criar o inimigo da fase
         * 
         * @param pos posicao de onde o inimigo deve ser criado
         * @param letra indetificador de qual inimigo deve ser criado
        */
        void Fase::criarInimigo(const sf::Vector2f pos, const char letra)
        {
            Entidade::Arma::Arma* arma = nullptr;
            Entidade::Entidade* personagem = nullptr;
           
           
            
            if(letra == 'e'){
                
                Entidade::Personagem::Inimigo::Esqueleto* esqueleto = new Entidade::Personagem::Inimigo::Esqueleto(pos, this->jogador);
                if(esqueleto == nullptr)
                {
                    std::cout<<"Fase::Fase: nao foi possivel criar um slime";
                    exit(1);
                }
                
                arma = new Entidade::Arma::Arma(IDs::IDs::armaDoIimigo);
                
                if(arma == nullptr)
                {
                    std::cout<<"Fase::Fase: nao foi possivel criar a arma do inimigo";
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

                arma = new Entidade::Arma::Arma(IDs::IDs::armaDoIimigo);

                if(arma == nullptr)
                {
                    std::cout<<"Fase::Fase: nao foi possivel criar a arma do inimigo";
                    exit(1);
                }

                slime->setArma(arma);
                personagem = static_cast<Entidade::Entidade*>(slime);
            }
            else if (letra == 'a'){
                
                Entidade::Personagem::Inimigo::Arqueiro* arqueiro = new Entidade::Personagem::Inimigo::Arqueiro(pos, this->jogador);
                if(arqueiro == nullptr)
                {
                    std::cout<<"Fase::Fase: nao foi possivel criar um arqueiro";
                    exit(1);
                }

                Entidade::Arma::Projetil* projetil = new Entidade::Arma::Projetil(IDs::IDs::projetil_inimigo);

                arma = static_cast<Entidade::Arma::Arma*>(projetil);

                if(arma == nullptr)
                {
                    std::cout<<"Fase::Fase: nao foi possivel criar a arma do inimigo";
                    exit(1);
                }


                arqueiro->setArma(arma);
                personagem = static_cast<Entidade::Entidade*>(arqueiro);
            }
            
             if(personagem != nullptr){
                listaPersonagens->addEntidade(personagem);
                if(arma != nullptr){
                    listaPersonagens->addEntidade(arma);
                }
            }
        }

        /**
         * @brief metodo responsavel por analizar qual entidade deve ser criada
         * 
         * @param letra inde3tificador para filtrar qual entidade deve ser criada
         * @param pos posicao inicial da entidade
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
                case('a'):
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

        /**
         * @brief metodo que cria uma entidade com base no id
         * 
         * @param ID identificacao da entidade a ser criada
         * @param entidade json com as informacoes da entidade
         * @param arma json com as informcaoes da arma a ser criada
        */
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

                    Entidade::Arma::Arma* pArma = new Entidade::Arma::Arma(arma);
                    
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

                    Entidade::Arma::Arma* pArma = new Entidade::Arma::Arma(arma);
                    
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
                
                case(IDs::IDs::arqueiro):
                {
                    Entidade::Personagem::Inimigo::Arqueiro* arqueiro = new Entidade::Personagem::Inimigo::Arqueiro(entidade, this->jogador); 
                    
                     if(arqueiro == nullptr)
                    {
                        std::cout<<"Fase::Fase: nao foi possvel criar o arqueiro";
                        exit(1);
                    }

                    Entidade::Arma::Projetil* projetil = new Entidade::Arma::Projetil(arma);

                    Entidade::Arma::Arma* pArma = static_cast<Entidade::Arma::Arma*>(projetil);
                    
                    if(pArma == nullptr)
                    {
                        std::cout << "Fase::nao foi possivel criar espada do inimigo" << std::endl;
                        exit(1);
                    }

                    arqueiro->setArma(pArma);
                    personagem = static_cast<Entidade::Entidade*>(arqueiro);
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

                    Entidade::Arma::Arma* pArma = new Entidade::Arma::Arma(arma);
                    
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
         * @brief atualiza a lista de entidades  juntamente com a verificacao da colisao e atulizacao do fundo da fase
        */
        void Fase::executar()
        {
            jogador = getJogador();
            if(jogador)
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
         * @brief metodo responsavel por desenhar as
         * listas  de  personagens  e obstaculos
        */
        void Fase::desenhar()
        {
            fundo.executar();

            listaObstaculos->desenharEntidades();
            listaPersonagens->desenharEntidades();

        }

        /**
         * @brief metodo que retorna o ponteiro do jogador se existir se nao retorna null
         * 
         * @return retorna o jogador se ele existir 
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

        /**
         * @brief metodo que altera o estado do observador da fase 
        */
        void Fase::mudarEstadoListener(const bool ativo)
        {
            listenerFase->mudarEstado(ativo);
        }

        /**
         * @brief salva informacoes da fase
         * 
         * @return retorna um json contendo as informacoes da fase
        */
        nlohmann::ordered_json Fase::salvarFase()
        {
            nlohmann::ordered_json json = salvarEnte();
          
            return json;
        }

        /**
         * @brief metodo que salva as informacoes da lista de personagens e obstaculos
         * 
         * @return retorna um json contendo  as informacoes da lista personagens e lista de obstaculos
        */
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

        /**
         * @brief metodo que cria uma plataforma sem textura
         * 
         * @param pos posicao da plataforma
        */
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

