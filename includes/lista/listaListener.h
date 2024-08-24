
#pragma once

#include "lista.h"
#include "../listeners/listener.h"
#include "SFML/Graphics.hpp"

namespace Game::Lista{
    class ListaListener{

    private:

        //lista a armazenar observers

        Lista<Listener::Listener> objListaListener;

    public:

        //construtor e destrutor

        ListaListener();
        ~ListaListener();

        //metodo de adicao de novos elementos

        void addListener(Listener::Listener* listener);

        //metodos de remocao de elementos

        void removerListener(Listener::Listener* listener);
        void removerListener(int pos);
        
        //sobrecarga de operador 

        Listener::Listener* operator[](int pos);
        
        //metodo de acesso ao atributo tam

        int getTam();

        //metodo para tratar eventos do teclado

        void tratarTeclaPressionada(const sf::Keyboard::Key tecla);
        void tratarTeclaSolta(const sf::Keyboard::Key tecla);
        
        //metodos de tratar eventod do mouse

        void notificarBotaoMouseSolta(const sf::Mouse::Button botaoMouse);
        void notificarMovimentoMouse(const sf::Event::MouseMoveEvent mouse);

    };
}