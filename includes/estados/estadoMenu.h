
#pragma once 

#include "estado.h"
#include "../fases/fase.h"
#include "../menus/menu.h"


namespace Game{

    namespace Gerenciador{

        class GerenciadoDeEstado;
    }

    namespace Estado{

        class EstadoMenu : public Estado{

            private:

                static Gerenciador::GerenciadorDeEstado* pEstado;

                Menu::Menu* menu;

                void criarMenu();

            public:

                EstadoMenu(const IDs::IDs ID);
                ~EstadoMenu();

                void mudarEstadoListener();
                Menu::Menu* getMenu();
                Fase::Fase* getFase();
                void executar();
        };

    }

}