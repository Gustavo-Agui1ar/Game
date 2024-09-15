
#include "../includes/gerenciador/gerenciadorDeEventos.h"
#include "../includes/gerenciador/gerenciadorDeEstado.h"
#include "../includes/listeners/listenerFase.h"
#include "../includes/Levels/Level.h"

namespace Game::Listener{

        ListenerFase::ListenerFase():
        Listener()
        {
            fase = nullptr;
        }
       
        ListenerFase::ListenerFase(Level::Level* level):
        Listener()
        {
            fase = level;
        }

        ListenerFase::~ListenerFase() = default;

        void ListenerFase::notificarGameOver()
        {
            pEstado->addEstado(IDs::IDs::game_over_menu);
        }        

        void ListenerFase::teclaPressionada(sf::Keyboard::Key tecla)
        {
            //empty method
        }

        void ListenerFase::teclaSolta(sf::Keyboard::Key tecla)
        {
            if(tecEspecial[tecla] == "Escape")
            {
                pEstado->addEstado(IDs::IDs::pause_menu);
            }
        }

        void ListenerFase::setFase(Level::Level* fase)
        {
            this->fase = fase;
        }

}