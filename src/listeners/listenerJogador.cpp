
#include "../includes/listeners/listenerJogador.h"

namespace Game{

    namespace Listener{
        
        /**
         * @brief construtora do listener do jogador
         * 
         * @param jogador jogador a ser atribuito no atributo jogador do listenerJogador 
        */
        ListenerJogador::ListenerJogador(Entidade::Personagem::Jogador::Jogador* jogador):
        Listener()
        {
            this->jogador = jogador;
        }

        /**
         * @brief destrutora da classe listenerJogador
        */
        ListenerJogador::~ListenerJogador()
        {
            
        }

        /**
         * @brief metodo que trata teclas pressionadas
         * 
         * @param tecla tecla a ser tratada
        */
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

        /**
         * @brief metodo que trata teclas soltas
         * 
         * @param tecla tecla a ser tratada
        */
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