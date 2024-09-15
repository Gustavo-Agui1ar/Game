

#include "../includes/listeners/listenerDialogo.h"
#include "../includes/gerenciador/gerenciadorDeEstado.h"


namespace Game::Listener{


    ListenerDialogo::ListenerDialogo(Gerenciador::GerenciadorDeDialogo* pGDialogo):
    Listener(), pGDialogo(pGDialogo)
    {

    }

    ListenerDialogo::~ListenerDialogo() = default;

    void ListenerDialogo::teclaPressionada(const sf::Keyboard::Key tecla)
    {
        //empty
    }

    void ListenerDialogo::teclaSolta(const sf::Keyboard::Key tecla)
    {
        if(tecPadrao[tecla] == 'e')
        {
            if(pGDialogo->getFimUltimaFala() && pGDialogo->getFimFalaAtual())
            {
                pEstado->removerEstado();
            }
            else if(pGDialogo->getFimFalaAtual())
            {
                pGDialogo->proximaFala();
            }
            else
            {
                pGDialogo->pularDialogo();
            }
        }
        else if(tecEspecial[tecla] == "Escape")
            pEstado->addEstado(IDs::IDs::pause_menu);
    }

    void ListenerDialogo::setGerenciadorDialogo(Gerenciador::GerenciadorDeDialogo* pGDialogo)
    {
        this->pGDialogo = pGDialogo;
    }
    
    Gerenciador::GerenciadorDeDialogo* ListenerDialogo::getGerenciadorDialogo(Gerenciador::GerenciadorDeDialogo* pGDialogo)
    {
        return pGDialogo;
    }

}