
#pragma once

#include "lista.h"
#include "../listeners/listener.h"
#include "SFML/Graphics.hpp"

namespace Game{

    namespace Lista{

        class ListaListener{

            private:

            Lista<Listener::Listener> objListaListener;

            public:

            ListaListener();
            ~ListaListener();

            void addListener(Listener::Listener* listener);

            void removerListener(Listener::Listener* listener);
            void removerListener(int pos);
            
            Listener::Listener* operator[](int pos);
            int getTam();

            void tratarTeclaPressionada(const sf::Keyboard::Key tecla);
            void tratarTeclaSolta(const sf::Keyboard::Key tecla);

        };
    }
}