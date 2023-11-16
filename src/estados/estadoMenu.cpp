
#include "../includes/estados/estadoMenu.h"
//#include "../includes/menus/menuPausa.h"
#include "../includes/menus/menuPrincipal.h"
#include "../includes/gerenciador/gerenciadorDeEstado.h"

namespace Game{

    namespace Estado{
        
        Gerenciador::GerenciadorDeEstado* EstadoMenu::pEstado = Gerenciador::GerenciadorDeEstado::getGerenciadorDeEstado();

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
                break;
                /*case(IDs::IDs::menu_pause):
                {
                    if(fase == nullptr)
                    {
                        std::cout<<"EstadoMenu:: nao foi possivel recuperar fase";
                        exit(1);
                    }

                    Menu::MenuPausa* menuPause = new Menu::MenuPausa(fase);

                    if(menuPause == nullptr)
                    {
                        std::cout<<"EstadoMenu:: nao foi possivel criar um menu de pause";
                        exit(1);
                    }

                    this->menu = static_cast<Menu::Menu*>(menuPause);
                }
                break;*/
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

        Fase::Fase* EstadoMenu::getFase()
        {
           /* if(ID == IDs::IDs::menu_pause)
            {
                Menu::MenuPausa* menuFase = dynamic_cast<Menu::MenuPausa*>(menu);
                return menuFase->getFase();
            }*/
            return nullptr;
        }
    }
}