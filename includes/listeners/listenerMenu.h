
#pragma once

#include "listener.h"
#include "../menus/menu.h"
#include "../botao/botao.h"
#include  "../menus/menuCarregar.h"
#include  "../menus/menuGameOver.h"
#include  "../menus/menuSalvar.h"

namespace Game{

    namespace Listener{

        class ListenerMenu : public Listener{

        private:

            Menu::Menu* menu;

        public:

            ListenerMenu(Menu::Menu* menu);
            ~ListenerMenu();

            void teclaPressionada(const sf::Keyboard::Key tecla);
            void teclaSolta(const sf::Keyboard::Key tecla);
            void moveMouse(const  sf::Vector2f posMouse);
            void botaoMouseSolta(const sf::Mouse::Button botaoMouse);
        };
    }
}
