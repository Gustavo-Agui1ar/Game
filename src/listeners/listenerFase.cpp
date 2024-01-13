
#include "../includes/gerenciador/gerenciadorDeEventos.h"
#include "../includes/gerenciador/gerenciadorDeEstado.h"
#include "../includes/listeners/listenerFase.h"
#include "../includes/fases/fase.h"

namespace Game{

    namespace Listener{

        /**
         * @brief construtora da classe ListenerFase
        */
        ListenerFase::ListenerFase():
        Listener()
        {
            fase = nullptr;
        }

        /**
         * @brief destrutora da classe ListenerFase
        */
        ListenerFase::~ListenerFase()
        {

        }

        /**
         * @brief metodo de notificar que o jogador morrreu
        */
        void ListenerFase::notificarGameOver()
        {
            pEstado->addEstado(IDs::IDs::menu_gameOver);
        }        

        /**
         * @brief trata quando uma tecla eh pressionada
         * 
         * @param tecla tecla a ser tratada
        */
        void ListenerFase::teclaPressionada(sf::Keyboard::Key tecla)
        {

        }

        /**
         * @brief trata quando uma tecla eh solta
         * 
         * @param tecla tecla a ser tratada
        */
        void ListenerFase::teclaSolta(sf::Keyboard::Key tecla)
        {
            if(tecEspecial[tecla] == "Escape")
            {
                pEstado->addEstado(IDs::IDs::menu_pause);
            }
        }

        /**
         * @brief metodo de modificar o atriuto fase
         * 
         * @param fase fase a ser atribuida em fase do listener
        */
        void ListenerFase::setFase(Fase::Fase* fase)
        {
            this->fase = fase;
        }

    }
}