
#include "../includes/estados/estadoFase.h"

namespace Game{

    namespace Estado{
        
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
            case(IDs::IDs::forest):
            {
                fase = static_cast<Fase::Fase*>(new Fase::Forest(entidades));
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
            if(ID == IDs::IDs::caverna)
            {
                Fase::Caverna* caverna = new Fase::Caverna();
                fase = static_cast<Fase::Fase*>(caverna);
  
            }
            else if(ID == IDs::IDs::forest)
            {
                Fase::Forest* floresta = new Fase::Forest();
                fase = static_cast<Fase::Fase*>(floresta);
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
            Entidade::Personagem::Jogador::Jogador* jogador = fase->getJogador();

            if(jogador != nullptr)
            {
                jogador->mudarEstadoListener(ativo);
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
}