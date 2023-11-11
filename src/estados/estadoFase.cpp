
#include "../includes/estados/estadoFase.h"

namespace Game{

    namespace Estado{

        EstadoFase::EstadoFase(const IDs::IDs ID):
        Estado(ID)
        {
            fase = nullptr;

            criarFase();
        }

        EstadoFase::~EstadoFase()
        {
            if(fase != nullptr)
               //delete(fase);
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

        Entidade::Personagem::Jogador::Jogador* EstadoFase::getPlayer()
        {
            return fase->getJogador();
        }

        void EstadoFase::mudarEstadoListener()
        {
            Entidade::Personagem::Jogador::Jogador* jogador = fase->getJogador();

            if(jogador == nullptr)
            {
                std::cout<<"Estados::EstadoFase: nao foi possivel recuperar jogador";
                exit(1);
            }

            jogador->mudarEstadoListener();

            fase->mudarEstadoListener();
        
        }
    }
}