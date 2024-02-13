
#pragma once

#include "listener.h"
#include "../menus/menu.h"
#include "../menus/botao/botao.h"
#include  "../menus/menuCarregar.h"
#include  "../menus/menuGameOver.h"
#include  "../menus/menuSalvar.h"
#include  "../menus/menuDeSelecao.h"
#include  "../menus/menuOpcao.h"

namespace Game{

    namespace Listener{

        class ListenerMenu : public Listener{

        private:

            //atributo a ser observado pelo observer

            Menu::Menu* menu;

        public:

            //destrutor e destrutor

            ListenerMenu(Menu::Menu* menu);
            ~ListenerMenu();

            //metodos de tratamento de teclas

            void teclaPressionada(const sf::Keyboard::Key tecla);
            void teclaSolta(const sf::Keyboard::Key tecla);

            //metodos de tratamento de eventos do mouse

            void moveMouse(const  sf::Vector2f posMouse);
            void botaoMouseSolta(const sf::Mouse::Button botaoMouse);
        };
    }
}
