
#include "../../includes/lista/listaListener.h"

namespace Game{

    namespace Lista{
        
        /**
         * @brief construtora da classe
        */
        ListaListener::ListaListener():
        objListaListener()
        {

        }

        /**
         * @brief destrutora da classe
        */
        ListaListener::~ListaListener()
        {
            objListaListener.limparLista();
        }

        
        /**
         * @brief metodo para adicionar um elemento a lista 
         * 
         * @param listener objeto a ser adicionado a lista
        */
        void ListaListener::addListener(Listener::Listener* listener)
        {
            objListaListener.addElemento(listener);
        }

         /**
         * @brief metodo que remove um elemento da lista
         * 
         * @param listener objeto a ser removido
        */
        void ListaListener::removerListener(Listener::Listener* listener)
        {
            objListaListener.removerElemento(listener);
        }
        
        /**
         * @brief metodo que remove um elemento da lista
         * 
         * @param pos posicao do elemento a ser removido
        */
        void ListaListener::removerListener(int pos)
        {
            objListaListener.removerElemento(pos);
        }

        /**
         * @brief metdo de acesso ao tamanho da lista
         * 
         * @return retorna o tamanho da lista
        */
        int ListaListener::getTam()
        {
            return objListaListener.getTam();
        }

         /**
         * @brief operador de posicao para lista
         * 
         * @param pos posicao do elemento desejado
         * 
         * @return retorna um objeto do tipo listener
        */
        Listener::Listener* ListaListener::operator[](int pos)
        {
            return objListaListener.operator[](pos);    
        }

        /**
         * @brief metodo que notifica aos listener que uma tecla foi pressionada
         * 
         * @param tecla tecla pressionada
        */
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

        /**
         * @brief metodo que notifica aos listener que uma tecla foi solta
         * 
         * @param tecla tecla solta
        */
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

        /**
         * @brief metodo que notifica o movimento do mouse aos listeners ativos
         * 
         * @param mouse informacoes do mouse
        */
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
        
        /**
         * @brief metodo que notifica aos listener que um botao do mouse foi solto
         * 
         * @param botaoMouse botao solto
        */
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