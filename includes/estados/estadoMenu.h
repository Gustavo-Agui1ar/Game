
#pragma once 

#include "estado.h"
#include "../menus/menu.h"


namespace Game{

    namespace Estado{

        class EstadoMenu : public Estado{

            private:

                Menu::Menu* menu;

                void criarMenu();

            public:

                EstadoMenu(const IDs::IDs ID);
                ~EstadoMenu();

                void mudarEstadoListener();
                Menu::Menu* getMenu();
                void executar();
        };

    }

}