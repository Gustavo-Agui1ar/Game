
#pragma once

#include "../entidade/Player/Player.h"
#include "listener.h"

namespace Game::Listener{
    class ListenerJogador : public Listener{

    private:
        
        //atributo a ser observado pelo observer

        Entidade::Character::Player::Player* jogador;

    public:

        //construtor e destrutor

        explicit ListenerJogador(Entidade::Character::Player::Player* jogador);
        ~ListenerJogador() override;

        //metodos de tratamento de teclas

        void teclaPressionada(const sf::Keyboard::Key tecla) override;
        void teclaSolta(const sf::Keyboard::Key tecla) override;
        void botaoMouseSolta(const sf::Mouse::Button botaoMouse) override;
    
    };
}