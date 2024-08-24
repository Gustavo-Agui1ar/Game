
#include "../includes/estados/estadoFase.h"

namespace Game::Estado{

    
    /**
     * @brief construtora da classe EstadoFase
     * 
     * @param ID identificacao da fase
    */
    EstadoFase::EstadoFase(const IDs::IDs ID):
    Estado(ID)
    {
        fase = nullptr;
    }

    /**
     * @brief metodo que cria a fase apartir do json 
     * 
     * @param entidades json contendo as infomacoes da fase
     * @param IDfase fase a ser criada
    */
    void EstadoFase::criarFase(nlohmann::ordered_json entidades, IDs::IDs IDfase)
    {
        switch (IDfase)
        {
            case(IDs::IDs::floresta_do_amanhecer):
            {
                fase = static_cast<Fase::Fase*>(new Fase::Forest(entidades));
            }
                break;
            case(IDs::IDs::caverna):
            {
                fase = static_cast<Fase::Fase*>(new Fase::Caverna(entidades));
            }
                break;
            
            default:
                break;
        }
    }

    /**
     * destrutora da classe EstadoFase
    */
    EstadoFase::~EstadoFase()
    {
        if(fase != nullptr)
            delete(fase);
        fase = nullptr;
    }

    /**
     * @brief metodo que cria a fase de acordo com o id atribuido na contrutora
    */
    void EstadoFase::criarFase()
    {
        switch (ID)
        {
            case(IDs::IDs::floresta_do_amanhecer):
                fase = static_cast<Fase::Fase*>(new Fase::Forest());
                break;
            case(IDs::IDs::caverna):
                fase = static_cast<Fase::Fase*>(new Fase::Caverna());
                break;
            case(IDs::IDs::vila):
                fase = static_cast<Fase::Fase*>(new Fase::Vila());
                break;
            default:
                break;
        }

        if(fase == nullptr)
        {
            std::cout<<"Estados::EstadoFase: nao foi possivel criar um estadoFase";
            exit(1);
        }

        fase->criarFundo();
        fase->criarMapa();
    }

    /**
     * @brief metodo que executa a fase atualizando o estado das entidades
    */
    void EstadoFase::executar()
    {
        fase->executar();
    }

    /**
     * @brief metodo que altera o estado do  observador da fase
    */
    void EstadoFase::mudarEstadoListener(const bool ativo)
    {
        Entidade::Character::Player::Player* jogador = fase->getJogador();

        if(jogador != nullptr)
        {
            jogador->changeObserverEstate(ativo);
        }

        fase->mudarEstadoListener(ativo);

    
    }

    /**
     * @brief metodo e acesso ao atributo fase
     * 
     * @return retorna o atributo fase 
    */
    Fase::Fase* EstadoFase::getFase()
    {
        return fase;
    }
}