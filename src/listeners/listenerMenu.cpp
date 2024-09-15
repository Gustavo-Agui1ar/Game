
#include "../includes/listeners/listenerMenu.h"
#include "../includes/gerenciador/gerenciadorDeEstado.h"

namespace Game::Listener{

       
        /**
         * @brief contrutora da classe ListenerMenu
         * 
         * @param menu menu a ser atribuido no atributo menu
        */
        ListenerMenu::ListenerMenu(Menu::Menu* menu):
        Listener(),menu(menu)
        {

        }
        
        /**
         * @brief destrutora da classe ListenerMenu
        */
        ListenerMenu::~ListenerMenu() = default;

        /**
         * @brief metodo que trata teclas pressionadas 
         * 
         * @param tecla tecla a ser tratada
        */
        void ListenerMenu::teclaPressionada(const sf::Keyboard::Key tecla)
        {
          
            if(tecEspecial[tecla] == "Enter")
            {
                switch(menu->getIDBotaoSelecionado())
                {
                    case IDs::IDs::close_button:
                    { 
                        if(menu->getID() == IDs::IDs::pause_menu || menu->getID() == IDs::IDs::game_over_menu)
                        {
                            if(pEstado->getEstado(1)->getID() == IDs::IDs::dialogue_estate)
                                pEstado->removerEstado(3);
                            else
                                pEstado->removerEstado(2);
                        }
                        else    
                            pEstado->removerEstado();
                    }
                    break;
                    
                    
                    case IDs::IDs::new_game_button:
                    {
                        pEstado->addEstado(IDs::IDs::village);
                        auto* fase = dynamic_cast<State::LevelState*>(pEstado->getEstadoAtual());
                        fase->makeLevel();
                    }
                    break;
                    
                    
                    case IDs::IDs::load_game_button:
                    {
                        pEstado->addEstado(IDs::IDs::load_menu);      
                        pEstado->addEstado(IDs::IDs::bug_menu);      
                    }
                    break;

                    case IDs::IDs::play_button:
                    {
                        auto* menu = static_cast<State::MenuState*>(pEstado->getEstadoAtual());
                        auto* selecao = static_cast<Menu::MenuDeSelecao*>(menu->getMenu());

                        IDs::IDs IDfase = selecao->getIDdeSelecao();

                        pEstado->removerEstado(2);

                        if(pEstado->getEstadoAtual()->getID() == IDs::IDs::dialogue_estate)
                            pEstado->removerEstado(2);
                        else
                            pEstado->removerEstado(1);
                        
                        pEstado->addEstado(IDfase);
                            
                        auto* fase = dynamic_cast<State::LevelState*>(pEstado->getEstadoAtual());
                        fase->makeLevel();
                    }
                        break;
                    
                    case IDs::IDs::select_menu_level_button:
                    {
                        pEstado->addEstado(IDs::IDs::select_fase_menu);      
                        pEstado->addEstado(IDs::IDs::bug_menu);      
                    }
                    break;
                     
                    case IDs::IDs::option_button:
                    {
                        pEstado->addEstado(IDs::IDs::option_menu);
                        pEstado->addEstado(IDs::IDs::bug_menu);
                    }
                        break;

                    case IDs::IDs::back_button:
                    {
                        pEstado->removerEstado();
                    }
                    break;

                    case IDs::IDs::save_button:
                    {
                        State::State* estado = pEstado->getEstadoAtual();

                        if(estado->getID() == IDs::IDs::save_menu)
                        {
                            auto* estadoMenu = dynamic_cast<State::MenuState*>(estado);
                            auto* mSalvar = dynamic_cast<Menu::MenuSalvar*>(estadoMenu->getMenu());
                            mSalvar->salvar();
                            pEstado->removerEstado(); 
                        }
                    }
                    break;
                    
                    case IDs::IDs::load_button:
                    {
                        State::State* estado = pEstado->getEstadoAtual();
                        if(estado->getID() == IDs::IDs::load_menu)
                        {
                            auto* estadoMenu = dynamic_cast<State::MenuState*>(estado);
                            Menu::Menu* pMenu = estadoMenu->getMenu();
                            auto const* mCarregar = static_cast<Menu::MenuCarregar*>(pMenu);
                            Menu::Card* card = mCarregar->getCardSelecionado();

                            if(card->getExiste())
                            {
                                pEstado->removerEstado();
                                if(pEstado->getEstadoAtual()->getID() == IDs::IDs::pause_menu)
                                {
                                    pEstado->removerEstado(2);
                                }
                                const std::string caminhoFase = card->getCaminhoFase();
                                const std::string caminhoEntidades = card->getCaminhoEntidade();

                                Gerenciador::GerenciadorArquivo gArquivo;

                                nlohmann::ordered_json jsonFase = gArquivo.lerArquivo(caminhoFase.c_str());
                                nlohmann::ordered_json jsonEntidaes = gArquivo.lerArquivo(caminhoEntidades.c_str());
                                
                                
                                IDs::IDs ID = jsonFase["ID"].template get<IDs::IDs>();

                                pEstado->addEstado(ID);

                                auto* estadoFase = dynamic_cast<State::LevelState*>(pEstado->getEstadoAtual());
                                estadoFase->makeLevel(jsonEntidaes, ID);
                            }
                        }
                    }
                        break;
                    case IDs::IDs::remove_button:
                    {
                        State::State* estado = pEstado->getEstadoAtual();
                        if(estado == nullptr)
                        {
                            std::cout << "nao foi possivel recuperar estado atual";
                            exit(1);
                        }
                        if(estado->getID() == IDs::IDs::load_menu)
                        {
                            auto* estadoMenu = dynamic_cast<State::MenuState*>(estado);
                            auto* mCarregar = dynamic_cast<Menu::MenuCarregar*>(estadoMenu->getMenu());
                            mCarregar->deletarArquivos();
                        }
                    }
                    break;

                    case IDs::IDs::restart_button:
                    {
                        State::State* estado = pEstado->getEstadoAtual();
                        
                        if(estado->getID() == IDs::IDs::game_over_menu)
                        {
                            auto* pMenu = dynamic_cast<State::MenuState*>(estado);
                            auto* menuGO = dynamic_cast<Menu::MenuGameOver*>(pMenu->getMenu());
                            IDs::IDs IDfase = menuGO->getFase()->getID();     

                            pEstado->removerEstado(2);
                            pEstado->addEstado(IDfase); 
                            auto* pFase = dynamic_cast<State::LevelState*>(pEstado->getEstadoAtual());
                            pFase->makeLevel();
                        }
                    }
                    break;

                    case IDs::IDs::save_game_button:
                    {
                        pEstado->addEstado(IDs::IDs::save_menu);
                        pEstado->addEstado(IDs::IDs::bug_menu);
                    }
                    break;

                    default:
                        break;
                }
            
            }
            else if(tecEspecial[tecla] == "Left"  && pEstado->getEstadoAtual()->getID() == IDs::IDs::option_menu)
            {
                menu->selecionaEsquerda();
            }
            else if(tecEspecial[tecla] == "Right" && pEstado->getEstadoAtual()->getID() == IDs::IDs::option_menu)
            {
                menu->selecionaDireita();
            }
        }

        /**
         * @brief metodo que trata uma tecla solta
         * 
         * @param tecla tecla ser tratada
        */
        void ListenerMenu::teclaSolta(const sf::Keyboard::Key tecla)
        {
            if(tecEspecial[tecla] == "Up")
                menu->selecionaParaCima();
            else if(tecEspecial[tecla] == "Down")
                menu->selecionaParaBaixo();
            else if(tecEspecial[tecla] == "Left"  && pEstado->getEstadoAtual()->getID() != IDs::IDs::option_menu)
                menu->selecionaEsquerda();
            else if(tecEspecial[tecla] == "Right" && pEstado->getEstadoAtual()->getID() != IDs::IDs::option_menu)
                menu->selecionaDireita();
        }

        /**
         * @brief metodo que trata quando eventod de movimento do mouse
         * 
         * @param posMOuse posicao Atual do mouse 
        */
        void ListenerMenu::moveMouse(const sf::Vector2f posMouse)
        {
            menu->eventoMouse(posMouse);
        }

        /**
         * @brief metodo que trata quando um botao do mouse eh solto
         * 
         * @param botaoMouse botao do mouse que foi solto
        */
        void ListenerMenu::botaoMouseSolta(const sf::Mouse::Button botaoMouse)
        {
            if(menu->getMouseSelecionado())
            {
                switch (botaoMouse)
                {
                    case (sf::Mouse::Left):
                    {
                        IDs::IDs IDmenu = menu->getID();
                        switch (menu->getIDBotaoSelecionado())
                        {
                            case IDs::IDs::new_game_button:
                            {
                                pEstado->addEstado(IDs::IDs::village);
                                auto* fase = dynamic_cast<State::LevelState*>(pEstado->getEstadoAtual());
                                fase->makeLevel();
                            }
                                break;
                            case IDs::IDs::close_button:
                            {
                               if(menu->getID() == IDs::IDs::pause_menu || menu->getID() == IDs::IDs::game_over_menu)
                                {
                                    if(pEstado->getEstado(1)->getID() == IDs::IDs::dialogue_estate)
                                        pEstado->removerEstado(3);
                                    else
                                        pEstado->removerEstado(2);
                                }
                                else    
                                    pEstado->removerEstado();
                            }
                                break;
                          
                            case IDs::IDs::play_button:
                            {
                                auto* menu = static_cast<State::MenuState*>(pEstado->getEstadoAtual());
                                auto* selecao = static_cast<Menu::MenuDeSelecao*>(menu->getMenu());

                                IDs::IDs IDfase = selecao->getIDdeSelecao();

                                pEstado->removerEstado(2);

                                if(pEstado->getEstadoAtual()->getID() == IDs::IDs::dialogue_estate)
                                    pEstado->removerEstado(2);
                                else
                                    pEstado->removerEstado(1);
                                
                                pEstado->addEstado(IDfase);
                                    
                                auto* fase = dynamic_cast<State::LevelState*>(pEstado->getEstadoAtual());
                                fase->makeLevel();
                            }
                                break;

                            case IDs::IDs::back_button:
                            {
                                pEstado->removerEstado();
                            }
                                break;
                            case IDs::IDs::save_button:
                            {
                                State::State* estado = pEstado->getEstadoAtual();

                                if(IDmenu == IDs::IDs::save_menu)
                                {
                                    auto* estadoMenu = dynamic_cast<State::MenuState*>(estado);
                                    auto* mSalvar = dynamic_cast<Menu::MenuSalvar*>(estadoMenu->getMenu());
                                    mSalvar->salvar();
                                    pEstado->removerEstado(); 
                                }
                            
                            }
                                break;
                            case IDs::IDs::select_menu_level_button:
                            {
                                pEstado->addEstado(IDs::IDs::select_fase_menu);      
                            }
                                break;
                            case IDs::IDs::load_game_button:
                            {
                                pEstado->addEstado(IDs::IDs::load_menu);
                            }
                                break;
                           
                            case IDs::IDs::option_button:
                            {
                                pEstado->addEstado(IDs::IDs::option_menu);
                            }
                                break;
                           
                            case IDs::IDs::restart_button:
                            {
                                State::State* estado = pEstado->getEstadoAtual();
                        
                                if(estado->getID() == IDs::IDs::game_over_menu)
                                {
                                    auto* pMenu = dynamic_cast<State::MenuState*>(estado);
                                    auto* menuGO = dynamic_cast<Menu::MenuGameOver*>(pMenu->getMenu());
                                    IDs::IDs IDfase = menuGO->getFase()->getID();     

                                    pEstado->removerEstado(2);
                                    pEstado->addEstado(IDfase); 
                                    auto* pFase = dynamic_cast<State::LevelState*>(pEstado->getEstadoAtual());
                                    pFase->makeLevel();
                                }
                            }
                            break;

                            case IDs::IDs::save_game_button:
                            {
                                pEstado->addEstado(IDs::IDs::save_menu);
                            }
                                break;
                            case IDs::IDs::remove_button:
                            {
                                State::State* estado = pEstado->getEstadoAtual();
                                if(estado == nullptr)
                                {
                                    std::cout << "nao foi possivel recuperar estado atual";
                                    exit(1);
                                }
                                if(estado->getID() == IDs::IDs::load_menu)
                                {
                                    auto* estadoMenu = dynamic_cast<State::MenuState*>(estado);
                                    auto* mCarregar = dynamic_cast<Menu::MenuCarregar*>(estadoMenu->getMenu());
                                    mCarregar->deletarArquivos();
                                }
                            }
                                break;
                            case IDs::IDs::load_button:
                            {
                                State::State* estado = pEstado->getEstadoAtual();
                                if(estado->getID() == IDs::IDs::load_menu)
                                {
                                    auto* estadoMenu = dynamic_cast<State::MenuState*>(estado);
                                    Menu::Menu* pMenu = estadoMenu->getMenu();
                                    auto const* mCarregar = static_cast<Menu::MenuCarregar*>(pMenu);
                                    Menu::Card* card = mCarregar->getCardSelecionado();

                                    if(card->getExiste())
                                    {
                                        pEstado->removerEstado();
                                        if(pEstado->getEstadoAtual()->getID() == IDs::IDs::pause_menu)
                                        {
                                            pEstado->removerEstado(2);
                                        }
                                        const std::string caminhoFase = card->getCaminhoFase();
                                        const std::string caminhoEntidades = card->getCaminhoEntidade();

                                        Gerenciador::GerenciadorArquivo gArquivo;

                                        nlohmann::ordered_json jsonFase = gArquivo.lerArquivo(caminhoFase.c_str());
                                        nlohmann::ordered_json jsonEntidaes = gArquivo.lerArquivo(caminhoEntidades.c_str());
                                        
                                     
                                        IDs::IDs ID = jsonFase["ID"].template get<IDs::IDs>();

                                        pEstado->addEstado(ID);

                                        auto* estadoFase = dynamic_cast<State::LevelState*>(pEstado->getEstadoAtual());
                                        estadoFase->makeLevel(jsonEntidaes, ID);
                                    }
                                }
                            }
                                break;

                            default:
                                break;
                        }
                            break;
                    }
                    default:
                        break;
                }
            }
        }
}