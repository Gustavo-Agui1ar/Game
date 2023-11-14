
#include "../includes/estados/estadoMenu.h"
#include "../includes/menus/menuPrincipal.h"

namespace Game{

    namespace Estado{


        EstadoMenu::EstadoMenu(const IDs::IDs ID):
        Estado(ID), menu(nullptr)
        {
            criarMenu();
        }

        EstadoMenu::~EstadoMenu()
        {
            if(menu)
            {
                delete(menu);
                menu = nullptr;
            }
        }

        void EstadoMenu::mudarEstadoListener()
        {
            menu->mudarEstadoListener();
        }

        void EstadoMenu::criarMenu()
        {
            switch(ID)
            {
                case(IDs::IDs::menu_principal):
                {
                    Menu::MenuPrincipal* menuP = new Menu::MenuPrincipal();

                    if(menuP == nullptr)
                    {
                        std::cout<<"EstadoMenu::criarMenu: nao foi possivel criar o menu principal";
                    }

                    this->menu = static_cast<Menu::Menu*>(menuP);
                }
            }
        }

        void EstadoMenu::executar()
        {
            menu->executar();
        }

        Menu::Menu* EstadoMenu::getMenu()
        {
            return menu;
        }
    }
}