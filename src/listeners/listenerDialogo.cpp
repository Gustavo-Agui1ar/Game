

#include "../includes/listeners/listenerDialogo.h"
#include "../includes/gerenciador/gerenciadorDeEstado.h"


namespace Game{

    namespace Listener{

        ListenerDialogo::ListenerDialogo(Gerenciador::GerenciadorDeDialogo* pGDialogo):
        Listener(), pGDialogo(pGDialogo)
        {

        }

        ListenerDialogo::~ListenerDialogo()
        {

        }

        void ListenerDialogo::teclaPressionada(const sf::Keyboard::Key tecla)
        {

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
                pEstado->addEstado(IDs::IDs::menu_pause);
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
}