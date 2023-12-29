
#include "../includes/estados/estadoFase.h"

namespace Game{

    namespace Estado{

        EstadoFase::EstadoFase(const IDs::IDs ID):
        Estado(ID)
        {
            fase = nullptr;
        }

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

        EstadoFase::~EstadoFase()
        {
            if(fase != nullptr)
               delete(fase);
            fase = nullptr;
        }

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

        void EstadoFase::executar()
        {
            fase->executar();
        }

        void EstadoFase::mudarEstadoListener(const bool ativo)
        {
            Entidade::Personagem::Jogador::Jogador* jogador = fase->getJogador();

            if(jogador != nullptr)
            {
                jogador->mudarEstadoListener(ativo);
            }

            fase->mudarEstadoListener(ativo);

        
        }

        Fase::Fase* EstadoFase::getFase()
        {
            return fase;
        }
    }
}