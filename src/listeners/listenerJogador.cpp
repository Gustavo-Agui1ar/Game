
#include "../includes/listeners/listenerJogador.h"

namespace Game{

    namespace Listener{

        ListenerJogador::ListenerJogador(Entidade::Personagem::Jogador::Jogador* jogador):
        Listener()
        {
            this->jogador = jogador;
        }

        ListenerJogador::~ListenerJogador()
        {
            
        }

        void ListenerJogador::teclaPressionada(sf::Keyboard::Key tecla)
        {
            if(!jogador->getMorrer())
            {
                if(tecPadrao[tecla] == 'a')
                    jogador->andar(true);
                else if(tecPadrao[tecla] == 'd')
                    jogador->andar(false);
                else if(tecPadrao[tecla] == 'w')
                    jogador->pular();
                else if(tecPadrao[tecla] == 'e')
                    if(jogador->getNoChao())
                        jogador->atacar();
            }
        }

        void ListenerJogador::teclaSolta(sf::Keyboard::Key tecla)
        {
            if(!jogador->getMorrer())
            {
                if(tecPadrao[tecla] == 'a' || tecPadrao[tecla] == 'd')
                    jogador->parar();
                else if(tecPadrao[tecla] == 'w' || tecPadrao[tecla] == 'e')
                    jogador->pararAtaque();
            }
        }
    }
}