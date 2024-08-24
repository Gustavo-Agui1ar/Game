
#include "../includes/fases/fase.h"
#include <unistd.h>

namespace Game::Fase{

    
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
            delete listenerFase;
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
        auto* armaJogador = new Entidade::Weapon::Weapon(IDs::IDs::armaDoJogador); 
        auto* projetilJogador = new Entidade::Weapon::Bullet(IDs::IDs::projetil_jogador); 
        auto* player =  new Entidade::Character::Player::Player(pos);

        if(player == nullptr)
        {
            std::cout<<"Fase::Fase: nao foi possvel criar o player";
            exit(1);
        }
        if(armaJogador == nullptr)
        {
            std::cout<<"Fase::Fase: nao foi possvel criar a arma do player";
            exit(1);
        }
        
        if(projetilJogador == nullptr)
        {
            std::cout<<"Fase::Fase: nao foi possvel criar o projetil do player";
            exit(1);
        }
        
        player->setWeapon(armaJogador);
        player->setProjetil(projetilJogador);
        jogador = player;

        listaPersonagens->addEntidade(static_cast<Entidade::Entidade*>(jogador));
        listaPersonagens->addEntidade(static_cast<Entidade::Entidade*>(armaJogador));
        listaPersonagens->addEntidade(static_cast<Entidade::Entidade*>(projetilJogador));

    }

    /**
     * @brief metodo responsavel por criar o inimigo da fase
     * 
     * @param pos posicao de onde o inimigo deve ser criado
     * @param letra indetificador de qual inimigo deve ser criado
    */
    void Fase::criarInimigo(const sf::Vector2f pos, const char letra)
    {
        Entidade::Weapon::Weapon* arma = nullptr;
        Entidade::Entidade* personagem = nullptr;
        
        
        
        if(letra == 'e'){
            
            auto* esqueleto = new Entidade::Character::Enemy::Skeleton(pos, this->jogador);
            if(esqueleto == nullptr)
            {
                std::cout<<"Fase::Fase: nao foi possivel criar um slime";
                exit(1);
            }
            
            arma = new Entidade::Weapon::Weapon(IDs::IDs::armaDoIimigo);
            
            if(arma == nullptr)
            {
                std::cout<<"Fase::Fase: nao foi possivel criar a arma do inimigo";
                exit(1);
            }

            esqueleto->setWeapon(arma);
            personagem = static_cast<Entidade::Entidade*>(esqueleto);
        }
        else if (letra == 's'){
            
            auto* slime = new Entidade::Character::Enemy::Slime(pos, this->jogador);
            if(slime == nullptr)
            {
                std::cout<<"Fase::Fase: nao foi possivel criar um slime";
                exit(1);
            }

            arma = new Entidade::Weapon::Weapon(IDs::IDs::armaDoIimigo);

            if(arma == nullptr)
            {
                std::cout<<"Fase::Fase: nao foi possivel criar a arma do inimigo";
                exit(1);
            }

            slime->setWeapon(arma);
            personagem = static_cast<Entidade::Entidade*>(slime);
        }
        else if (letra == 'a'){
            
            auto* arqueiro = new Entidade::Character::Enemy::Archer(pos, this->jogador);
            if(arqueiro == nullptr)
            {
                std::cout<<"Fase::Fase: nao foi possivel criar um arqueiro";
                exit(1);
            }

            auto* projetil = new Entidade::Weapon::Bullet(IDs::IDs::projetil_inimigo);

            arma = static_cast<Entidade::Weapon::Weapon*>(projetil);

            if(arma == nullptr)
            {
                std::cout<<"Fase::Fase: nao foi possivel criar a arma do inimigo";
                exit(1);
            }


            arqueiro->setWeapon(arma);
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
            case 'e':
                criarInimigo(sf::Vector2f(pos.x * 50.0f, pos.y * 50.0f),letra);
                break;
            case 's':
                criarInimigo(sf::Vector2f(pos.x * 50.0f, pos.y * 50.0f),letra);
                break;
            case 'a':
                criarInimigo(sf::Vector2f(pos.x * 50.0f, pos.y * 50.0f),letra);
                break;
            case '#':
                criarPlataforma(sf::Vector2f(pos.x * 50.0f, pos.y * 50.0f + 10.f));
                break;
            case 'j':
                criarJogador(sf::Vector2f(pos.x * 50.0f, pos.y * 50.0f));
                break;
            case 'v':
                criarPlataformaInvisivel(sf::Vector2f(pos.x * 50.0f, pos.y * 50.0f));
                break;
            default:
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
    void Fase::criarEntidade(IDs::IDs ID, nlohmann::ordered_json entidade , nlohmann::ordered_json arma, nlohmann::ordered_json arma2)
    {
        Entidade::Entidade* personagem = nullptr;
        Entidade::Entidade* armaCharacter = nullptr;
        Entidade::Entidade* armaProjetilJogador = nullptr;

        switch(ID)
        {
            case IDs::IDs::jogador:
            {
                jogador = new Entidade::Character::Player::Player(entidade);
                
                if(jogador == nullptr)
                {
                    std::cout<<"Fase::Fase: nao foi possvel criar o jogador";
                    exit(1);
                }

                auto* pArma = new Entidade::Weapon::Weapon(arma);
                
                if(pArma == nullptr)
                {
                    std::cout << "Fase::nao foi possivel criar espada do jogador" << std::endl;
                    exit(1);
                }

                auto* pProjetil = new Entidade::Weapon::Bullet(arma2);
                
                if(pProjetil == nullptr)
                {
                    std::cout << "Fase::nao foi possivel criar o projetil do jogador" << std::endl;
                    exit(1);
                }

                jogador->setWeapon(pArma);
                jogador->setProjetil(pProjetil);
                personagem = static_cast<Entidade::Entidade*>(this->jogador);
                armaCharacter = static_cast<Entidade::Entidade*>(pArma);
                armaProjetilJogador = static_cast<Entidade::Entidade*>(pProjetil);
            }
            break;

            case IDs::IDs::esqueleto:
            {
                auto* esqueleto = new Entidade::Character::Enemy::Skeleton(entidade, this->jogador); 
                
                    if(esqueleto == nullptr)
                {
                    std::cout<<"Fase::Fase: nao foi possvel criar o esqueleto";
                    exit(1);
                }

                auto* pArma = new Entidade::Weapon::Weapon(arma);
                
                if(pArma == nullptr)
                {
                    std::cout << "Fase::nao foi possivel criar espada do inimigo" << std::endl;
                    exit(1);
                }

                esqueleto->setWeapon(pArma);
                personagem = static_cast<Entidade::Entidade*>(esqueleto);
                armaCharacter = static_cast<Entidade::Entidade*>(pArma);
            }
            break;
            
            case IDs::IDs::arqueiro:
            {
                auto* arqueiro = new Entidade::Character::Enemy::Archer(entidade, this->jogador); 
                
                    if(arqueiro == nullptr)
                {
                    std::cout<<"Fase::Fase: nao foi possvel criar o arqueiro";
                    exit(1);
                }

                auto* projetil = new Entidade::Weapon::Bullet(arma);

                auto* pArma = static_cast<Entidade::Weapon::Weapon*>(projetil);
                
                if(pArma == nullptr)
                {
                    std::cout << "Fase::nao foi possivel criar espada do inimigo" << std::endl;
                    exit(1);
                }

                arqueiro->setWeapon(pArma);
                personagem = static_cast<Entidade::Entidade*>(arqueiro);
                armaCharacter = static_cast<Entidade::Entidade*>(pArma);
            }
            break;

            case IDs::IDs::red_slime:
            {
                auto* slime = new Entidade::Character::Enemy::Slime(entidade, this->jogador); 
                
                    if(slime == nullptr)
                {
                    std::cout<<"Fase::Fase: nao foi possvel criar o slime";
                    exit(1);
                }

                auto* pArma = new Entidade::Weapon::Weapon(arma);
                
                if(pArma == nullptr)
                {
                    std::cout << "Fase::nao foi possivel criar espada do inimigo" << std::endl;
                    exit(1);
                }

                slime->setWeapon(pArma);
                personagem = static_cast<Entidade::Entidade*>(slime);
                armaCharacter = static_cast<Entidade::Entidade*>(pArma);
            }
            break;

            case IDs::IDs::plataforma:
            {
                auto* plataforma = new Entidade::Obstaculo::Plataforma(entidade, IDs::IDs::plataforma, getID());

                if(plataforma == nullptr)
                {
                    std::cout<<"Fase::Fase: nao foi possvel criar a plataforma";
                    exit(1);
                } 
                    personagem = static_cast<Entidade::Entidade*>(plataforma);                   
            }
            break;

            case IDs::IDs::plataforma_invisivel:
            {
                auto* plataforma = new Entidade::Obstaculo::Plataforma(entidade, IDs::IDs::plataforma_invisivel, IDs::IDs::plataforma_invisivel);

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
            case IDs::IDs::plataforma:
                listaObstaculos->addEntidade(personagem);
                break;
            case IDs::IDs::plataforma_invisivel:
                listaObstaculos->addEntidade(personagem);
                break;
            case IDs::IDs::jogador:
                listaPersonagens->addEntidade(personagem);
                listaPersonagens->addEntidade(armaCharacter);
                listaPersonagens->addEntidade(armaProjetilJogador);
                break;
            
            default:
                listaPersonagens->addEntidade(personagem);
                listaPersonagens->addEntidade(armaCharacter);
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
    void Fase::draw()
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
        Entidade::Character::Player::Player* Fase::getJogador()
        {
        for(int i = 0; i < listaPersonagens->getTam(); i++)
        {
            Entidade::Entidade* aux = listaPersonagens->operator[](i);
            if(aux->getID() == IDs::IDs::jogador)
            {
                return dynamic_cast<Entidade::Character::Player::Player*>(aux);
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
        
        auto* plataforma = new Entidade::Obstaculo::Plataforma(pos,sf::Vector2f(50.0f,50.0f), IDs::IDs::plataforma_invisivel, IDs::IDs::plataforma_invisivel);
        if(plataforma == nullptr)
        {
            std::cout<<"Fase::Forest: nao foi possivel criar uma plataforma";
            exit(1);
        }
        auto* plat = static_cast<Entidade::Entidade*>(plataforma);
        listaObstaculos->addEntidade(plat);
    }
}

