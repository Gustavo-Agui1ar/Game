
#include "../includes/Observer/ObserverMenu.h"
#include "../includes/Manager/StateManager.h"

namespace Game::Observer{

        ObserverMenu::ObserverMenu(Menu::Menu* menu):
        Observer(), m_menu(menu)
        {

        }

        ObserverMenu::~ObserverMenu() = default;

        void ObserverMenu::keyPressed(const sf::Keyboard::Key tecla)
        {
          
            if(m_especialKeys[tecla] == "Enter")
            {
                processSameCommand();
            }
            else if(m_especialKeys[tecla] == "Left"  && m_stateManager->getCurrentState()->getID() == IDs::IDs::option_menu)
            {
                m_menu->selecionaEsquerda();
            }
            else if(m_especialKeys[tecla] == "Right" && m_stateManager->getCurrentState()->getID() == IDs::IDs::option_menu)
            {
                m_menu->selecionaDireita();
            }
        }

        void ObserverMenu::keyRelease(const sf::Keyboard::Key tecla)
        {
            if(m_especialKeys[tecla] == "Up")
                m_menu->selecionaParaCima();
            else if(m_especialKeys[tecla] == "Down")
                m_menu->selecionaParaBaixo();
            else if(m_especialKeys[tecla] == "Left"  && m_stateManager->getCurrentState()->getID() != IDs::IDs::option_menu)
                m_menu->selecionaEsquerda();
            else if(m_especialKeys[tecla] == "Right" && m_stateManager->getCurrentState()->getID() != IDs::IDs::option_menu)
                m_menu->selecionaDireita();
        }

        void ObserverMenu::mouseMove(const sf::Vector2f posMouse)
        {
            m_menu->eventoMouse(posMouse);
        }

        void ObserverMenu::mouseButtonRelease(const sf::Mouse::Button mouseButton)
        {
            if(m_menu->getID() == IDs::IDs::option_menu && mouseButton == sf::Mouse::Left)
                static_cast<Menu::MenuOpcao*>(m_menu)->changeMouseState(false);
            if(m_menu->getMouseSelecionado() && mouseButton == sf::Mouse::Left)
            {
                processSameCommand();
            }
        }

        void ObserverMenu::closeMenu() {
            if(m_menu->getID() == IDs::IDs::pause_menu || m_menu->getID() == IDs::IDs::game_over_menu)
            {
                if(m_stateManager->getState(1)->getID() == IDs::IDs::dialogue_estate)
                    m_stateManager->removeState(3);
                else
                    m_stateManager->removeState(2);
            }
            else    
                m_stateManager->removeState();
        }

        void ObserverMenu::addNewGame() {
            m_stateManager->addState(IDs::IDs::village);
            auto* level = dynamic_cast<State::LevelState*>(m_stateManager->getCurrentState());
            level->makeLevel();
        }
        void ObserverMenu::addLoadGame() {
            m_stateManager->addState(IDs::IDs::load_menu);
        }

        void ObserverMenu::playButton() {
            auto* stateMenu = static_cast<State::MenuState*>(m_stateManager->getCurrentState());
            auto* select = static_cast<Menu::MenuDeSelecao*>(stateMenu->getMenu());

            IDs::IDs IDlevel = select->getIDdeSelecao();

            m_stateManager->removeState(2);

            if(m_stateManager->getCurrentState()->getID() == IDs::IDs::dialogue_estate)
                m_stateManager->removeState(2);
            else
                m_stateManager->removeState(1);
            
            m_stateManager->addState(IDlevel);
                
            auto* level = dynamic_cast<State::LevelState*>(m_stateManager->getCurrentState());
            level->makeLevel();
        }

        void ObserverMenu::addSelectMenuLevel() {
            m_stateManager->addState(IDs::IDs::select_fase_menu);    
        }
        void ObserverMenu::addOptionMenu() {
             m_stateManager->addState(IDs::IDs::option_menu);
        }
        
        void ObserverMenu::back() {
            m_stateManager->removeState();
        }

        void ObserverMenu::saveButton() {
            m_stateManager->addState(IDs::IDs::save_menu);
        }
        
        void ObserverMenu::loadButton() {
            State::State* state = m_stateManager->getCurrentState();
            if(state->getID() == IDs::IDs::load_menu)
            {
                auto* menuState = dynamic_cast<State::MenuState*>(state);
                Menu::Menu* menu = menuState->getMenu();
                auto const* loadMenu = static_cast<Menu::MenuCarregar*>(menu);
                Menu::Card* card = loadMenu->getCardSelecionado();

                if(card->getExiste())
                {
                    m_stateManager->removeState();
                    if(m_stateManager->getCurrentState()->getID() == IDs::IDs::pause_menu)
                    {
                        m_stateManager->removeState(2);
                    }
                    const std::string pathLevel = card->getCaminhoFase();
                    const std::string pathEntitys = card->getCaminhoEntidade();

                    Manager::FileManager fileManager;

                    nlohmann::ordered_json jsonLevel = fileManager.readFile(pathLevel.c_str());
                    nlohmann::ordered_json jsonEntitys = fileManager.readFile(pathEntitys.c_str());
                    
                    
                    IDs::IDs ID = jsonLevel["ID"].template get<IDs::IDs>();

                    m_stateManager->addState(ID);

                    auto* levelState = dynamic_cast<State::LevelState*>(m_stateManager->getCurrentState());
                    levelState->makeLevel(jsonEntitys, ID);
                }
            }
        }
      
        void ObserverMenu::removeButton() {
            State::State* state = m_stateManager->getCurrentState();
            if(state == nullptr)
            {
                std::cout << "not possible to remove state" << std::endl;
                exit(1);
            }
            if(state->getID() == IDs::IDs::load_menu)
            {
                auto* menuState = dynamic_cast<State::MenuState*>(state);
                auto* loadMenu = dynamic_cast<Menu::MenuCarregar*>(menuState->getMenu());
                loadMenu->deletarArquivos();
            }
        }
        
        void ObserverMenu::restartButton() {
            State::State* state = m_stateManager->getCurrentState();
            
            if(state->getID() == IDs::IDs::game_over_menu)
            {
                auto* menuState = dynamic_cast<State::MenuState*>(state);
                auto* gameOveMenu = dynamic_cast<Menu::MenuGameOver*>(menuState->getMenu());
                IDs::IDs IDlevel = gameOveMenu->getFase()->getID();     

                m_stateManager->removeState(2);
                m_stateManager->addState(IDlevel); 
                auto* level = dynamic_cast<State::LevelState*>(m_stateManager->getCurrentState());
                level->makeLevel();
            }
        }
       
        void ObserverMenu::saveGame() {
             State::State* state = m_stateManager->getCurrentState();

            if(state->getID() == IDs::IDs::save_menu)
            {
                auto* menuState = dynamic_cast<State::MenuState*>(state);
                auto* saveMenu = dynamic_cast<Menu::MenuSalvar*>(menuState->getMenu());
                saveMenu->salvar();
                m_stateManager->removeState(); 
            }
        }

        void ObserverMenu::processSameCommand() {
            
            switch(m_menu->getIDBotaoSelecionado())
                {
                    case IDs::IDs::close_button:
                        closeMenu();
                        break;
                    case IDs::IDs::new_game_button:
                        addNewGame();
                        break;
                    case IDs::IDs::load_game_button:
                        addLoadGame();
                        break;
                    case IDs::IDs::play_button:
                        playButton();
                        break;
                    case IDs::IDs::select_menu_level_button:
                        addSelectMenuLevel();
                        break;
                    case IDs::IDs::option_button:
                        addOptionMenu();
                        break;
                    case IDs::IDs::back_button:
                        back();
                        break;
                    case IDs::IDs::save_button:
                        saveGame();
                        break;
                    
                    case IDs::IDs::load_button:
                        loadButton();
                        break;
                    case IDs::IDs::remove_button:
                        removeButton();
                        break;

                    case IDs::IDs::restart_button:
                        restartButton();
                        break;
                    case IDs::IDs::save_game_button:
                        saveButton();
                    break;

                    default:
                        break;
                }   
        }

        void ObserverMenu::mouseButtonPressed(const sf::Mouse::Button mouseButton){
            if(mouseButton == sf::Mouse::Left && m_menu->getID() == IDs::IDs::option_menu)
            {
                auto* optionMenu = static_cast<Menu::MenuOpcao*>(m_menu);
                optionMenu->changeMouseState(true);
            }
        }
}