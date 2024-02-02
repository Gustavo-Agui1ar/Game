
#pragma once

#include "../includes/gerenciador/gerenciadorDeDialogo.h"
#include "listener.h"

namespace Game{

    namespace Listener{

        class ListenerDialogo : public Listener{

            
            private:

                Gerenciador::GerenciadorDeDialogo* pGDialogo;

            public:


                ListenerDialogo(Gerenciador::GerenciadorDeDialogo* pGDialogo);
                ~ListenerDialogo();

                void teclaPressionada(const sf::Keyboard::Key tecla);
                void teclaSolta(const sf::Keyboard::Key tecla);

                void setGerenciadorDialogo(Gerenciador::GerenciadorDeDialogo* pGDialogo);
                Gerenciador::GerenciadorDeDialogo* getGerenciadorDialogo(Gerenciador::GerenciadorDeDialogo* pGDialogo);


        };
    }
}