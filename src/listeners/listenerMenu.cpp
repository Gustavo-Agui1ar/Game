
#include "../includes/listeners/listenerMenu.h"
#include "../includes/gerenciador/gerenciadorDeEstado.h"

namespace Game{

    namespace Listener{

        ListenerMenu::ListenerMenu(Menu::Menu* menu):
        Listener(),menu(menu)
        {

        }

        ListenerMenu::~ListenerMenu()
        {

        }

        void ListenerMenu::teclaPressionada(const sf::Keyboard::Key tecla)
        {
          
            if(tecEspecial[tecla] == "Enter")
            {
                switch(menu->getIDBotaoSelecionado())
                {
                    case(IDs::IDs::botao_sair):
                    { 
                        if(menu->getID() == IDs::IDs::menu_pause || menu->getID() == IDs::IDs::menu_gameOver)
                        {
                            pEstado->removerEstado(2);
                        }
                        else
                        {
                            pEstado->removerEstado();
                        }
                    }
                    break;
                    
                    
                    case(IDs::IDs::botao_novoJogo):
                    {
                        pEstado->addEstado(IDs::IDs::forest);
                        Estado::EstadoFase* fase = dynamic_cast<Estado::EstadoFase*>(pEstado->getEstadoAtual());
                        fase->criarFase();
                    }
                    break;
                    
                    
                    case(IDs::IDs::botao_carregar_jogo):
                    {
                        pEstado->addEstado(IDs::IDs::menu_carregar);      
                        pEstado->addEstado(IDs::IDs::menu_bug);      
                    }
                    break;

                    case(IDs::IDs::botao_voltar):
                    {
                         pEstado->removerEstado();

                        if(pEstado->getEstadoAtual()->getID() == IDs::IDs::menu_pause)
                        {
                            pEstado->removerEstado();
                            pEstado->addEstado(IDs::IDs::menu_pause);
                        }
                    }
                    break;

                    case (IDs::IDs::botao_salvar):
                    {
                        Estado::Estado* estado = pEstado->getEstadoAtual();

                        if(estado->getID() == IDs::IDs::menu_salvar)
                        {
                            Estado::EstadoMenu* estadoMenu = dynamic_cast<Estado::EstadoMenu*>(estado);
                            Menu::MenuSalvar* mSalvar = dynamic_cast<Menu::MenuSalvar*>(estadoMenu->getMenu());
                            mSalvar->salvar();
                            pEstado->removerEstado(); 
                        }
                    }
                    break;
                    
                    case(IDs::IDs::botao_carregar):
                    {
                        Estado::Estado* estado = pEstado->getEstadoAtual();
                        if(estado->getID() == IDs::IDs::menu_carregar)
                        {
                            Estado::EstadoMenu* estadoMenu = dynamic_cast<Estado::EstadoMenu*>(estado);
                            Menu::Menu* pMenu = estadoMenu->getMenu();
                            Menu::MenuCarregar* mCarregar = static_cast<Menu::MenuCarregar*>(pMenu);
                            Menu::Card* card = mCarregar->getCardSelecionado();

                            if(card->getExiste())
                            {
                                pEstado->removerEstado();
                                if(pEstado->getEstadoAtual()->getID() == IDs::IDs::menu_pause)
                                {
                                    pEstado->removerEstado(2);
                                }
                                const std::string caminhoFase = card->getCaminhoFase();
                                const std::string caminhoEntidades = card->getCaminhoEntidade();

                                Gerenciador::GerenciadorArquivo gArquivo;

                                nlohmann::ordered_json jsonFase = gArquivo.lerArquivo(caminhoFase.c_str());
                                nlohmann::ordered_json jsonEntidaes = gArquivo.lerArquivo(caminhoEntidades.c_str());
                                
                                
                                IDs::IDs ID = jsonFase["ID"].template get<IDs::IDs>();

                                if(ID == IDs::IDs::forest)
                                {
                                    pEstado->addEstado(IDs::IDs::forest);
                                }
                                else 
                                {
                                    std::cout << "nao foi possivel criar uma fase" << std::endl;
                                    exit(1);
                                }
                                Estado::EstadoFase* estadoFase = dynamic_cast<Estado::EstadoFase*>(pEstado->getEstadoAtual());
                                estadoFase->criarFase(jsonEntidaes, ID);
                            }
                        }
                    }
                        break;
                    case(IDs::IDs::botao_remover):
                    {
                        Estado::Estado* estado = pEstado->getEstadoAtual();
                        if(estado == nullptr)
                        {
                            std::cout << "nao foi possivel recuperar estado atual";
                            exit(1);
                        }
                        if(estado->getID() == IDs::IDs::menu_carregar)
                        {
                            Estado::EstadoMenu* estadoMenu = dynamic_cast<Estado::EstadoMenu*>(estado);
                            Menu::MenuCarregar* mCarregar = dynamic_cast<Menu::MenuCarregar*>(estadoMenu->getMenu());
                            mCarregar->deletarArquivos();
                        }
                    }
                    break;

                    case(IDs::IDs::botao_reniciar_jogo):
                    {
                        pEstado->addContinuarGameOver(IDs::IDs::forest);
                    }
                    break;

                    case(IDs::IDs::botao_salvar_jogo):
                    {
                        pEstado->addEstado(IDs::IDs::menu_salvar);
                        pEstado->addEstado(IDs::IDs::menu_bug);
                    }
                    break;

                    
                    default:
                        break;
                }
            
            }
        }

        void ListenerMenu::teclaSolta(const sf::Keyboard::Key tecla)
        {
            if(tecEspecial[tecla] == "Up")
            {
                menu->selecionaParaCima();
            }
            else if(tecEspecial[tecla] == "Down")
            {
                menu->selecionaParaBaixo();
            }
            else if(tecEspecial[tecla] == "Left")
            {
                menu->selecionaEsquerda();
            }
            else if(tecEspecial[tecla] == "Right")
            {
                menu->selecionaDireita();
            }
           

        }

        void ListenerMenu::moveMouse(const sf::Vector2f posMouse)
        {
            menu->eventoMouse(posMouse);
        }

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
                            case (IDs::IDs::botao_novoJogo):
                            {
                                pEstado->addEstado(IDs::IDs::forest);
                                Estado::EstadoFase* fase = dynamic_cast<Estado::EstadoFase*>(pEstado->getEstadoAtual());
                                fase->criarFase();
                            }
                                break;
                            case (IDs::IDs::botao_sair):
                            {
                                //provisorio
                                if(IDmenu == IDs::IDs::menu_pause || IDmenu == IDs::IDs::menu_gameOver)
                                    pEstado->removerEstado(2);
                                else
                                    pEstado->removerEstado();
                            }
                                break;
                            case (IDs::IDs::botao_voltar):
                            {
                                pEstado->removerEstado();

                                if(IDmenu == IDs::IDs::menu_pause)
                                {
                                    pEstado->removerEstado();
                                    pEstado->addEstado(IDs::IDs::menu_pause);
                                }
                            }
                                break;
                            case (IDs::IDs::botao_salvar):
                            {
                                Estado::Estado* estado = pEstado->getEstadoAtual();

                                if(IDmenu == IDs::IDs::menu_salvar)
                                {
                                    Estado::EstadoMenu* estadoMenu = dynamic_cast<Estado::EstadoMenu*>(estado);
                                    Menu::MenuSalvar* mSalvar = dynamic_cast<Menu::MenuSalvar*>(estadoMenu->getMenu());
                                    mSalvar->salvar();
                                    pEstado->removerEstado(); 
                                }
                            
                            }
                                break;
                            case (IDs::IDs::botao_carregar_jogo):
                            {
                                pEstado->addEstado(IDs::IDs::menu_carregar);
                            }
                                break;
                            case(IDs::IDs::botao_reniciar_jogo):
                                //por enquanto...
                                pEstado->addContinuarGameOver(IDs::IDs::forest);
                                break;

                            case(IDs::IDs::botao_salvar_jogo):
                            {
                                pEstado->addEstado(IDs::IDs::menu_salvar);
                            }
                                break;
                            case(IDs::IDs::botao_remover):
                            {
                                Estado::Estado* estado = pEstado->getEstadoAtual();
                                if(estado == nullptr)
                                {
                                    std::cout << "nao foi possivel recuperar estado atual";
                                    exit(1);
                                }
                                if(estado->getID() == IDs::IDs::menu_carregar)
                                {
                                    Estado::EstadoMenu* estadoMenu = dynamic_cast<Estado::EstadoMenu*>(estado);
                                    Menu::MenuCarregar* mCarregar = dynamic_cast<Menu::MenuCarregar*>(estadoMenu->getMenu());
                                    mCarregar->deletarArquivos();
                                }
                            }
                                break;
                            case(IDs::IDs::botao_carregar):
                            {
                                Estado::Estado* estado = pEstado->getEstadoAtual();
                                if(estado->getID() == IDs::IDs::menu_carregar)
                                {
                                    Estado::EstadoMenu* estadoMenu = dynamic_cast<Estado::EstadoMenu*>(estado);
                                    Menu::Menu* pMenu = estadoMenu->getMenu();
                                    Menu::MenuCarregar* mCarregar = static_cast<Menu::MenuCarregar*>(pMenu);
                                    Menu::Card* card = mCarregar->getCardSelecionado();

                                    if(card->getExiste())
                                    {
                                        pEstado->removerEstado();
                                        if(pEstado->getEstadoAtual()->getID() == IDs::IDs::menu_pause)
                                        {
                                            pEstado->removerEstado(2);
                                        }
                                        const std::string caminhoFase = card->getCaminhoFase();
                                        const std::string caminhoEntidades = card->getCaminhoEntidade();

                                        Gerenciador::GerenciadorArquivo gArquivo;

                                        nlohmann::ordered_json jsonFase = gArquivo.lerArquivo(caminhoFase.c_str());
                                        nlohmann::ordered_json jsonEntidaes = gArquivo.lerArquivo(caminhoEntidades.c_str());
                                        
                                     
                                        IDs::IDs ID = jsonFase["ID"].template get<IDs::IDs>();

                                        if(ID == IDs::IDs::forest)
                                        {
                                            pEstado->addEstado(IDs::IDs::forest);
                                        }
                                        else 
                                        {
                                            std::cout << "nao foi possivel criar uma fase" << std::endl;
                                            exit(1);
                                        }
                                        Estado::EstadoFase* estadoFase = dynamic_cast<Estado::EstadoFase*>(pEstado->getEstadoAtual());
                                        estadoFase->criarFase(jsonEntidaes, ID);
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
}