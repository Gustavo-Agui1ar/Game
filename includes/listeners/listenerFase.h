
#pragma once 

#include "listener.h"

namespace Game{

    namespace Fase{
        class Fase;
    }

    namespace Listener{

        class ListenerFase : public Listener{

        private:

            Fase::Fase* fase;

        public:

            ListenerFase();
            ~ListenerFase();

            void teclaPressionada(sf::Keyboard::Key tecla);
            void teclaSolta(sf::Keyboard::Key tecla);
            void setFase(Fase::Fase* fase);
            void notificarGameOver();
            
        };
    }
}