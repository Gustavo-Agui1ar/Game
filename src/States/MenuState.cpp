
#include "../includes/States/MenuState.h"
#include "../includes/menus/menuPausa.h"
#include "../includes/menus/menuGameOver.h"
#include "../includes/menus/menuPrincipal.h"
#include "../includes/menus/menuOpcao.h"
#include "../includes/menus/menuCarregar.h"
#include "../includes/menus/menuDeSelecao.h"
#include "../includes/menus/menuSalvar.h"
#include "../includes/Manager/StateManager.h"

namespace Game:: State{
    
    Manager::StateManager* MenuState::m_stateManager = Manager::StateManager::getStateManager();

    MenuState::MenuState(const IDs::IDs ID):
    State(ID), m_menu(nullptr)
    {
        makeMenu();
    }

    MenuState::~MenuState()
    {
        if(m_menu)
        {
            delete m_menu;
            m_menu = nullptr;
        }
    }

    void MenuState::changeEstateObserver(const bool ativo)
    {
        m_menu->mudarEstadoListener(ativo);
    }

    void MenuState::makeMenu()
    {
        State* estadoAtual = m_stateManager->getCurrentState();
        Level::Level* fase = nullptr;
        
        if(estadoAtual != nullptr)
        {
            if(estadoAtual->getID() == IDs::IDs::dawn_forest || estadoAtual->getID() == IDs::IDs::cave ||
                estadoAtual->getID() == IDs::IDs::village)
            {
                auto* estadoFase = static_cast<LevelState*>(estadoAtual);
                fase = estadoFase->getLevel();
            }
            else if(estadoAtual->getID() == IDs::IDs::pause_menu){
                auto* estadoMenu = static_cast<MenuState*>(estadoAtual);
                fase = estadoMenu->getFase();
            }
            else if(estadoAtual->getID() == IDs::IDs::dialogue_estate)
            {
                auto* dialogo = static_cast<DialogueState*>(estadoAtual);
                fase = dialogo->getFase();
            }
        }

        switch(ID)
        {
            case IDs::IDs::main_menu:
                makeMainMenu();
            break;

            case IDs::IDs::pause_menu:
                makePauseMenu(fase);
            break;
            
            case IDs::IDs::select_fase_menu:
                makeSelectFaseMenu(fase);
            break;
            
            case IDs::IDs::option_menu:
                makeOptionMenu(fase);
            break;

            case IDs::IDs::game_over_menu:
               makeGameOverMenu(fase);
            break;
        
            case IDs::IDs::load_menu:
                makeLoadMenu(fase); 
            break;

            case IDs::IDs::save_menu:
                makeSaveMenu(fase);
            break;

            case IDs::IDs::bug_menu:
                makeBugMenu(fase);
            break;

            default:
                break;
        }     
    }
    
    void MenuState::execute()
    {
        m_menu->executar();
    }

    Menu::Menu* MenuState::getMenu()
    {
        return m_menu;
    }
    
    Level::Level* MenuState::getFase()
    {
        if(ID == IDs::IDs::pause_menu)
        {
            auto* menuFase = dynamic_cast<Menu::MenuPausa*>(m_menu);
            return menuFase->getFase();
        }

        return nullptr;
    }
    
    void MenuState::makeMainMenu() {
        auto* mainMenu = new Menu::MenuPrincipal();

        if(mainMenu == nullptr)
        {
            std::cout<<"MenuState::criarMenu: nao foi possivel criar o menu principal";
        }

        mainMenu->criarBotoes();
        m_menu = static_cast<Menu::Menu*>(mainMenu);
    }
    
    void MenuState::makePauseMenu(Level::Level* fase) {
        
        if(fase == nullptr)
        {
            std::cout<<"MenuState:: nao foi possivel recuperar fase";
            exit(1);
        }

        auto* menuPause = new Menu::MenuPausa(fase);

        if(menuPause == nullptr)
        {
            std::cout<<"MenuState:: nao foi possivel criar um menu de pause";
            exit(1);
        }

        menuPause->criarBotoes();
        
        m_menu = static_cast<Menu::Menu*>(menuPause);
    }

    void MenuState::makeSaveMenu(Level::Level* fase) {
        if(fase == nullptr)
        {
            std::cout<<"MenuState:: nao foi possivel recuperar fase";
            exit(1);
        }

        auto* menuSalvar = new Menu::MenuSalvar(fase);

        if(menuSalvar == nullptr)
        {
            std::cout<<"MenuState::nao foi possivel criar menuCarregar";
            exit(1);
        }

        menuSalvar->criarBotoes();
        m_menu = static_cast<Menu::Menu*>(menuSalvar);
    }

    void MenuState::makeLoadMenu(Level::Level* fase) {
        Menu::MenuCarregar* menuCarregar = nullptr; 

        if(m_stateManager->getCurrentState()->getID() == IDs::IDs::pause_menu)
                menuCarregar = new Menu::MenuCarregar(fase);
        else
            menuCarregar = new Menu::MenuCarregar();

        if(menuCarregar == nullptr)
        {
            std::cout<<"MenuState::nao foi possivel criar menuCarregar";
            exit(1);
        }

        menuCarregar->criarBotoes();
        m_menu = static_cast<Menu::Menu*>(menuCarregar);
    }
    
    void MenuState::makeBugMenu(Level::Level* fase) {
        Menu::MenuCarregar* menuCarregar = nullptr; 

        if(m_stateManager->getCurrentState()->getID() == IDs::IDs::pause_menu)
                menuCarregar = new Menu::MenuCarregar(fase);
        else
            menuCarregar = new Menu::MenuCarregar();

        if(menuCarregar == nullptr)
        {
            std::cout<<"MenuState::nao foi possivel criar menuCarregar";
            exit(1);
        }

        menuCarregar->criarBotaoBug();
        m_menu = static_cast<Menu::Menu*>(menuCarregar);
    }

    void MenuState::makeSelectFaseMenu(Level::Level* fase) {
        if(fase == nullptr)
        {
            std::cout<<"MenuState:: nao foi possivel recuperar fase";
            exit(1);
        }

        auto* menuSelect = new Menu::MenuDeSelecao(fase);

        if(menuSelect == nullptr)
        {
            std::cout<<"MenuState:: nao foi possivel criar um menu de selecao";
            exit(1);
        }
        
        m_menu = static_cast<Menu::Menu*>(menuSelect);
    }

    void MenuState::makeOptionMenu(Level::Level* fase) {
        Menu::MenuOpcao* menuOpcao = nullptr; 

        if(m_stateManager->getCurrentState()->getID() == IDs::IDs::pause_menu)
                menuOpcao = new Menu::MenuOpcao(fase);
        else
            menuOpcao = new Menu::MenuOpcao();

        if(menuOpcao == nullptr)
        {
            std::cout<<"MenuState::nao foi possivel criar menu de opcoes";
            exit(1);
        }

        menuOpcao->criarBotoes();
        m_menu = static_cast<Menu::Menu*>(menuOpcao);
    }

    void MenuState::makeGameOverMenu(Level::Level* fase) {
         if(fase == nullptr)
        {
            std::cout<<"MenuState:: nao foi possivel recuperar fase";
            exit(1);
        }

        auto* menuGameOver = new Menu::MenuGameOver(fase);
        
        if(menuGameOver == nullptr)
        {
            std::cout<<"MenuState:: nao foi possivel criar um menu de pause";
            exit(1);
        }
        menuGameOver->criarBotoes();

        m_menu = static_cast<Menu::Menu*>(menuGameOver);
    }
 }