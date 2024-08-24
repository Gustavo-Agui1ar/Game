
#pragma once 

#include "listener.h"

namespace Game{

    namespace Fase{
        class Fase;
    }

    namespace Listener{

        class ListenerFase : public Listener{

        private:

            //atributo a ser observado pelo observer

            Fase::Fase* fase;

        public:

            //construtor e destrutor

            ListenerFase();
            ~ListenerFase() override;

            //metodos de tratamento de teclas

            void teclaPressionada(sf::Keyboard::Key tecla) override;
            void teclaSolta(sf::Keyboard::Key tecla) override;
        
            // metodo que modifica o atributo fase

            void setFase(Fase::Fase* fase);
        
            //metodo que notifica que o jogador morreu

            void notificarGameOver();
            
        };
    }
}