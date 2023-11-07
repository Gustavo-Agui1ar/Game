
#pragma once

#include "../jogador/jogador.h"
#include "listener.h"

namespace Game{

    namespace Listener{

        class ListenerJogador : public Listener{

            private:
                
                Entidade::Personagem::Jogador::Jogador* jogador;

            public:

                ListenerJogador(Entidade::Personagem::Jogador::Jogador* jogador);
                ~ListenerJogador();

                void teclaPressionada(const sf::Keyboard::Key tecla);
                void teclaSolta(const sf::Keyboard::Key tecla);

        };

    }

}