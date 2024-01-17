
#pragma once

#include "../entidade/jogador/jogador.h"
#include "listener.h"

namespace Game{

    namespace Listener{

        class ListenerJogador : public Listener{

            private:
                
                //atributo a ser observado pelo observer

                Entidade::Personagem::Jogador::Jogador* jogador;

            public:

                //construtor e destrutor

                ListenerJogador(Entidade::Personagem::Jogador::Jogador* jogador);
                ~ListenerJogador();

                //metodos de tratamento de teclas

                void teclaPressionada(const sf::Keyboard::Key tecla);
                void teclaSolta(const sf::Keyboard::Key tecla);
                void botaoMouseSolta(const sf::Mouse::Button botaoMouse);
        

        };

    }

}