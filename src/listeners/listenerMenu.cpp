
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
                        pEstado->removerEstado(); 
                        break;
                    case(IDs::IDs::botao_voltar):
                        pEstado->removerEstado();
                        break;
                    case(IDs::IDs::botao_novoJogo):
                        pEstado->addEstado(IDs::IDs::forest);
                        Estado::EstadoFase* fase = dynamic_cast<Estado::EstadoFase*>(pEstado->getEstadoAtual());
                        fase->criarFase();
                        break;
                    /*case(IDs::IDs::botao_opcao):
                        break;
                    case(IDs::IDs::botao_salvar_jogo):
                        break;
                    case(IDs::IDs::botao_carregar_jogo):
                        break;*/
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
                                pEstado->removerEstado();
                            }
                                break;
                            case (IDs::IDs::botao_voltar):
                            {
                                pEstado->removerEstado();
                            }
                                break;
                            case (IDs::IDs::botao_salvar_jogo):
                            {
                                //pGEstado->addEstado(IDs::IDs::estado_menu_salvar_jogada);
                            }
                                break;
                            case (IDs::IDs::botao_carregar_jogo):
                            {
                                //pGEstado->addEstado(IDs::IDs::estado_menu_carregar_jogo);
                            }
                                break;
                        }
                            break;
                    }
                }
            }
        }
    }
}