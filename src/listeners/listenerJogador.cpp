
#include "../includes/listeners/listenerJogador.h"
#include "../includes/gerenciador/gerenciadorArquivo.h"

namespace Game::Listener{

    
    /**
     * @brief construtora do listener do jogador
     * 
     * @param jogador jogador a ser atribuito no atributo jogador do listenerJogador 
    */
    ListenerJogador::ListenerJogador(Entidade::Character::Player::Player* jogador):
    Listener()
    {
        this->jogador = jogador;
    }

    /**
     * @brief destrutora da classe listenerJogador
    */
    ListenerJogador::~ListenerJogador() = default;

    /**
     * @brief metodo que trata teclas pressionadas
     * 
     * @param tecla tecla a ser tratada
    */
    void ListenerJogador::teclaPressionada(sf::Keyboard::Key tecla)
    {
        if(!jogador->getDie())
        {
            switch (tecPadrao[tecla])
            {
                case 'a':
                    jogador->walk(true);
                    break;
                case 'd':
                    jogador->walk(false);
                    break;
                case 'w':
                    jogador->jump();
                    break;
                case 'k':
                    if(jogador->getOnFloor())
                        jogador->attack();
                    break;
                case 'j':
                    jogador->doDash();
                    break;
                case 'q':
                    jogador->activeRage();
                    break;
                case 'l':
                    jogador->trhowBullet();
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
        if(!jogador->getDie())
        {
            if(tecPadrao[tecla] == 'a' || tecPadrao[tecla] == 'd')
                jogador->stop();
            else if(tecPadrao[tecla] == 'w' || tecPadrao[tecla] == 'k')
                jogador->stopAttack();
            else if(tecPadrao[tecla] == 'j')
                jogador->stopDash();
            else if(tecPadrao[tecla] == 'r')
                jogador->searchIteractions();
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
            jogador->attack();
        else if(botaoMouse == sf::Mouse::Button::Right)
            jogador->trhowBullet();
    }
}