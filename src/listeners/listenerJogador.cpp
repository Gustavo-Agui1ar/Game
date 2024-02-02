
#include "../includes/listeners/listenerJogador.h"
#include "../includes/gerenciador/gerenciadorArquivo.h"

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

                    case('k'):
                    {
                        if(jogador->getNoChao())
                            jogador->atacar();
                    }
                        break;

                    case('j'):
                    {
                        jogador->fazerDash();
                    }
                        break;
                  
                    case('q'):
                    {
                        jogador->ativarFuria();
                    }
                        break;
                    case('l'):
                    {
                        jogador->lancarProjetil();
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
                else if(tecPadrao[tecla] == 'w' || tecPadrao[tecla] == 'k')
                    jogador->pararAtaque();
                else if(tecPadrao[tecla] == 'j')
                    jogador->pararDash();
                else if(tecPadrao[tecla] == 'r')
                    jogador->procurarIteracoes();
            }
        }

        
        /**
         * @brief metodo que trata botao do mouse  solto
         * 
         * @param tecla botao a ser tratado
        */
        void ListenerJogador::botaoMouseSolta(const sf::Mouse::Button botaoMouse)
        {
             if(botaoMouse == sf::Mouse::Button::Left)
                jogador->atacar();
        }
        
    }
}