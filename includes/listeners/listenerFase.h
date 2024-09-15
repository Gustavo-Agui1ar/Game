
#pragma once 

#include "listener.h"

namespace Game{

    namespace Level{
        class Level;
    }

    namespace Listener{

        class ListenerFase : public Listener{

        private:

            //atributo a ser observado pelo observer

            Level::Level* fase;

        public:

            //construtor e destrutor

            explicit ListenerFase(Level::Level* level);
            ListenerFase();
            ~ListenerFase() override;

            //metodos de tratamento de teclas

            void teclaPressionada(sf::Keyboard::Key tecla) override;
            void teclaSolta(sf::Keyboard::Key tecla) override;
        
            // metodo que modifica o atributo fase

            void setFase(Level::Level* fase);
        
            //metodo que notifica que o jogador morreu

            void notificarGameOver();
            
        };
    }
}