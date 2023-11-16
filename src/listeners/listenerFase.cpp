
#include "../includes/gerenciador/gerenciadorDeEventos.h"
#include "../includes/gerenciador/gerenciadorDeEstado.h"
#include "../includes/listeners/listenerFase.h"
#include "../includes/fases/fase.h"

namespace Game{

    namespace Listener{


        ListenerFase::ListenerFase():
        Listener()
        {
            fase = nullptr;
        }

        ListenerFase::~ListenerFase()
        {

        }

        void ListenerFase::notificarGameOver()
        {
            //provisorio
            std::cout<<"Game Over :(";
            exit(1);
        }        

        void ListenerFase::teclaPressionada(sf::Keyboard::Key tecla)
        {

        }

        void ListenerFase::teclaSolta(sf::Keyboard::Key tecla)
        {
            if(tecEspecial[tecla] == "Escape")
            {
              //  pEstado->addEstado(IDs::IDs::menu_pause);
            }
        }

        void ListenerFase::setFase(Fase::Fase* fase)
        {
            this->fase = fase;
        }

    }
}