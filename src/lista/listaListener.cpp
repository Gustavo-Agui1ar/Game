
#include "../../includes/lista/listaListener.h"

namespace Game{

    namespace Lista{

        ListaListener::ListaListener():
        objListaListener()
        {

        }

        ListaListener::~ListaListener()
        {
            objListaListener.limparLista();
        }

        void ListaListener::addListener(Listener::Listener* listener)
        {
            objListaListener.addElemento(listener);
        }

        void ListaListener::removerListener(Listener::Listener* listener)
        {
            objListaListener.removerElemento(listener);
        }
        
        void ListaListener::removerListener(int pos)
        {
            objListaListener.removerElemento(pos);
        }

        int ListaListener::getTam()
        {
            return objListaListener.getTam();
        }

        Listener::Listener* ListaListener::operator[](int pos)
        {
            return objListaListener.operator[](pos);    
        }

        void ListaListener::tratarTeclaPressionada(sf::Keyboard::Key tecla)
        {
            for(int i = 0 ; i < objListaListener.getTam() ; i++)
            {
                Listener::Listener* listener = objListaListener.operator[](i);
                
                if(listener->getAtivo())
                {
                    listener->teclaPressionada(tecla);
                }

                listener = nullptr;
            }
        }

        void ListaListener::tratarTeclaSolta(sf::Keyboard::Key tecla)
        {
            for(int i = 0 ; i < objListaListener.getTam() ; i++)
            {
                Listener::Listener* listener = objListaListener.operator[](i);
                
                if(listener->getAtivo())
                {
                    listener->teclaSolta(tecla);
                }

                listener = nullptr;
            }
        }

         void ListaListener::notificarMovimentoMouse(const sf::Event::MouseMoveEvent mouse)
         {
            sf::Vector2f posMouse = sf::Vector2f((float)mouse.x, (float)mouse.y);
            for(int i = 0; i < objListaListener.getTam(); i++)
            {
                Listener::Listener* listener = objListaListener.operator[](i);
                if(listener->getAtivo())
                {
                    listener->moveMouse(posMouse);
                }
                listener = nullptr;
            }
        }

        void ListaListener::notificarBotaoMouseSolta(const sf::Mouse::Button botaoMouse)
        {
            for(int i = 0; i < objListaListener.getTam(); i++)
            {
                Listener::Listener* listener = objListaListener.operator[](i);
                if(listener->getAtivo())
                {
                    listener->botaoMouseSolta(botaoMouse);
                }
                listener = nullptr;
            }
        }


    }


}