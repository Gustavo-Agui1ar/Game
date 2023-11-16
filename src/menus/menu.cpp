
#include "../includes/menus/menu.h"
#include "../includes/listeners/listenerMenu.h"

namespace Game {

    namespace Menu{

        Menu::Menu(const IDs::IDs ID, const sf::Vector2f tamBotao, const std::string titulo, const unsigned int tamFonte):
        Ente(ID), listaDeBotao(), it(), tamBotao(tamBotao), tamJanela(pGrafico->getTamJanela()), posFundo(sf::Vector2f(0.0f,0.0f)),
        titulo(pGrafico->carregarFonte( "../Game/animations/botton/menu.ttf"), titulo, tamFonte), listenerMenu(new Listener::ListenerMenu(this)),
        mouseSelecionado(false)
        {
            if(listenerMenu == nullptr){
                std::cout << "Menu::MenuPrincipal::nao foi possivel criar um listener Menu Principal" << std::endl;
                exit(1);
            }
        }

        Menu::~Menu()
        {
            if(!listaDeBotao.empty())
            {
                for(it = listaDeBotao.begin(); it != listaDeBotao.end(); it++)
                {
                    delete(*it);
                    *it = nullptr;
                }
                listaDeBotao.clear();
            }
            if(listenerMenu)
            {
                delete(listenerMenu);
                listenerMenu = nullptr;
            }
        }

        void Menu::mudarEstadoListener()
        {
            listenerMenu->mudarEstado();
        }

        void Menu::addBotao(const std::string infoTexto, const sf::Vector2f pos, const IDs::IDs ID, const sf::Color corSelecionado)
        {
            Botao::BotaoTexto* botao = new Botao::BotaoTexto(infoTexto, pos,tamBotao, ID, corSelecionado);
            if(botao == nullptr)
            {
                throw("Menu::nao foi possivel criar um botao");
            }

            listaDeBotao.push_back(botao);
        }

        void Menu::atualizarPosicaoFundo()
        {
            posFundo = pGrafico->getCamera().getCenter();
        }

        void Menu::inicialiarIterador()
        {
            try 
            {
                it = listaDeBotao.begin();
                (*it)->setSelecionado(true);
            } 
            catch(const std::exception& e)
            {
                std::cerr << e.what() << std::endl;
                exit(1);
            }
        }

        void Menu::selecionaParaCima()
        {
            Botao::BotaoTexto* botao = *it;
            botao->setSelecionado(false);

            if(it == listaDeBotao.begin())
            {
                it = listaDeBotao.end();
            }
            it--;
            botao = *it;
            botao->setSelecionado(true);
        }

        void Menu::selecionaParaBaixo()
        {
            Botao::BotaoTexto* botao = *it;
            botao->setSelecionado(false);
            it++;
            if(it == listaDeBotao.end())
            {
                it = listaDeBotao.begin();
            }
            botao = *it;
            botao->setSelecionado(true);
        }

        const bool Menu::getMouseSelecionado()
        {
            return mouseSelecionado;
        }

        const IDs::IDs Menu::getIDBotaoSelecionado()
        {
            return (*it)->getID();
        }

       void Menu::eventoMouse(const sf::Vector2f posMouse){
            std::list<Botao::BotaoTexto*>::iterator aux;
            mouseSelecionado = false;
            for(aux = listaDeBotao.begin(); aux != listaDeBotao.end(); aux++)
            {
                Botao::BotaoTexto* botao = *aux;
                sf::RectangleShape caixa = botao->getCaixa();
                
                if(caixa.getGlobalBounds().contains(posMouse))
                {
                    (*it)->setSelecionado(false);
                    it = aux;
                    (*it)->setSelecionado(true);
                    mouseSelecionado = true;
                    break;
                }
            }
        }

        void Menu::desenhar()
        {
            std::list<Botao::BotaoTexto*>::iterator itAux;

            for(itAux = listaDeBotao.begin() ; itAux != listaDeBotao.end() ; itAux++)
            {
                Botao::BotaoTexto* botao = *itAux;
                botao->desenhar();
                botao = nullptr;
            }
        }

        void Menu::criarFundo()
        {
            
        }
    }
}