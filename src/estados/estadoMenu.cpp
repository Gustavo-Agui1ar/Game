
#include "../includes/estados/estadoMenu.h"
#include "../includes/menus/menuPausa.h"
#include "../includes/menus/menuGameOver.h"
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

        void EstadoMenu::mudarEstadoListener(const bool ativo)
        {
            menu->mudarEstadoListener(ativo);
        }

        void EstadoMenu::criarMenu()
        {
            Estado* estadoAtual = pEstado->getEstadoAtual();
            Fase::Fase* fase = nullptr;
            
            if(estadoAtual != nullptr)
            {
                if(estadoAtual->getID() == IDs::IDs::forest || estadoAtual->getID() == IDs::IDs::caverna)
                {
                    EstadoFase* estadoFase = static_cast<EstadoFase*>(estadoAtual);
                    fase = estadoFase->getFase();
                }
            }

            if(ID == IDs::IDs::menu_principal)
            {
                Menu::MenuPrincipal* menuP = new Menu::MenuPrincipal();

                if(menuP == nullptr)
                {
                    std::cout<<"EstadoMenu::criarMenu: nao foi possivel criar o menu principal";
                }

                this->menu = static_cast<Menu::Menu*>(menuP);
            }
            else if(ID == IDs::IDs::menu_pause)
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

                menuPause->criarBotoes();
                
                this->menu = static_cast<Menu::Menu*>(menuPause);
            }
            else if(ID == IDs::IDs::menu_gameOver)
            {
                if(fase == nullptr)
                {
                    std::cout<<"EstadoMenu:: nao foi possivel recuperar fase";
                    exit(1);
                }

                Menu::MenuGameOver* menuGO = new Menu::MenuGameOver(fase);
                
                if(menuGO == nullptr)
                {
                    std::cout<<"EstadoMenu:: nao foi possivel criar um menu de pause";
                    exit(1);
                }
                menuGO->criarBotoes();

                this->menu = static_cast<Menu::Menu*>(menuGO);
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