
#pragma once

#include "Observer.h"
#include "../menus/menu.h"
#include "../menus/Button/Button.h"
#include  "../menus/menuCarregar.h"
#include  "../menus/menuGameOver.h"
#include  "../menus/menuSalvar.h"
#include  "../menus/menuDeSelecao.h"
#include  "../menus/menuOpcao.h"

namespace Game::Observer{
    class ObserverMenu : public Observer{

    private:

        Menu::Menu* m_menu;

    public:

        explicit ObserverMenu(Menu::Menu* menu);
        ~ObserverMenu() override;

        void keyPressed(const sf::Keyboard::Key tecla) override;
        void keyRelease(const sf::Keyboard::Key tecla) override;

        void mouseMove(const  sf::Vector2f posMouse) override;
        void mouseButtonRelease(const sf::Mouse::Button botaoMouse) override;
        void mouseButtonPressed(const sf::Mouse::Button mouseButton) override;

        void processSameCommand();

        void closeMenu();
        void addNewGame();
        void addLoadGame();
        void playButton();
        void addSelectMenuLevel();
        void addOptionMenu();
        void back();

        void saveButton();
        void loadButton();
        void removeButton();
        void restartButton();
        void saveGame();
    };
}
