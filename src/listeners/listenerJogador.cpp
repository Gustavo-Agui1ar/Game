
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
                switch (tecPadrao[tecla])
                {
                    case('a'):
                    {
                        jogador->andar(true);
                    }
                        break;

                    case('d'):
                    {
                        jogador->andar(false);
                    }
                        break;

                    case('w'):
                    {
                        jogador->pular();
                    }
                        break;

                    case('e'):
                    {
                        if(jogador->getNoChao())
                            jogador->atacar();
                    }
                        break;

                    case('r'):
                    {
                        jogador->fazerDash();
                    }
                        break;
                
                    default:
                        break;
                }
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
                else if(tecPadrao[tecla] == 'r')
                    jogador->pararDash();
            }
        }
    }
}