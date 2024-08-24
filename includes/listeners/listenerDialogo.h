
#pragma once

#include "../includes/gerenciador/gerenciadorDeDialogo.h"
#include "listener.h"

namespace Game::Listener{
    class ListenerDialogo : public Listener{

    private:

        Gerenciador::GerenciadorDeDialogo* pGDialogo;

    public:


        explicit ListenerDialogo(Gerenciador::GerenciadorDeDialogo* pGDialogo);
        ~ListenerDialogo() override;

        void teclaPressionada(const sf::Keyboard::Key tecla) override;
        void teclaSolta(const sf::Keyboard::Key tecla) override;

        void setGerenciadorDialogo(Gerenciador::GerenciadorDeDialogo* pGDialogo);
        Gerenciador::GerenciadorDeDialogo* getGerenciadorDialogo(Gerenciador::GerenciadorDeDialogo* pGDialogo);
    };
}