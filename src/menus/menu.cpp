
#include "../includes/menus/menu.h"
#include "../includes/listeners/listenerMenu.h"

namespace Game {

    namespace Menu{

        /**
         * @brief construtora da classe Menu
         * 
         * @param ID identificador da classe 
         * @param tamBotao tamanho dos botoes do menu 
         * @param titulo texto  principal do menu
         * @param tamFonte tamanho do texto
        */
        Menu::Menu(const IDs::IDs ID, const sf::Vector2f tamBotao, const std::string titulo, const unsigned int tamFonte):
        Ente(ID), listaDeBotao(), it(),  titulo(m_pGrafic->carregarFonte( "../Game/animations/botton/menu.ttf"), titulo, tamFonte), 
        tamJanela(m_pGrafic->getTamJanela()), tamBotao(tamBotao), posFundo(sf::Vector2f(0.0f,0.0f)), listenerMenu(new Listener::ListenerMenu(this)),
        mouseSelecionado(false)
        {
            if(listenerMenu == nullptr){
                std::cout << "Menu::MenuPrincipal::nao foi possivel criar um listener Menu Principal" << std::endl;
                exit(1);
            }
        }
        
        /**
         * @brief destrutora da classe Menu
        */
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
        
        /**
         * @brief muda o estado do observador do menu
         * 
         * @param ativo boleano que dita se o observador sera ativo ou desativado
        */
        void Menu::mudarEstadoListener(const bool ativo)
        {
            listenerMenu->mudarEstado(ativo);
        }

        /**
         * @brief metodo que adiciona um botao ao menu
         * 
         * @param infoTexto informacao do texto do botao
         * @param pos posicao do botao
         * @param ID identificador do botao 
         * @param corSelecionado cor do botao ao ser selecionado
        */
        void Menu::addBotao(const std::string infoTexto, const sf::Vector2f pos, const IDs::IDs ID, const sf::Color corSelecionado)
        {
            Botao::BotaoTexto* botao = new Botao::BotaoTexto(infoTexto, pos,tamBotao, ID, corSelecionado);
            if(botao == nullptr)
            {
                throw("Menu::nao foi possivel criar um botao");
            }

            listaDeBotao.push_back(botao);
        }

        /**
         * @brief atualiza a posicao do fundo do menu caso este tenha um fundo movel
        */
        void Menu::atualizarPosicaoFundo()
        {
            posFundo = m_pGrafic->getCamera().getCenter();
        }

        /**
         * @brief metodo que inicializa o iterador da lista de botoes 
        */
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

        /**
         * @brief metodo que troca o botao selecionado para o anterior da lista caso este esteja no inicio da lista na hora de chamar o metodo voltasse ao final da lista
        */
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

        /**
         * @brief metodo que troca o botao selecionado para o proximo da lista caso este esteja no final da lista na hora de chamar o metodo voltasse ao inicio da lista
        */
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

        /**
         * @brief metodo de acesso ao boleano mouseSelecionado 
         * 
         * @return retorna um boleano se o mouse selecionou algo
        */
        const bool Menu::getMouseSelecionado()
        {
            return mouseSelecionado;
        }

        /**
         * @brief metodo de acesso ao identificador do botao selecionado
         * 
         * @return retorna o id do botao selecionado
        */
        const IDs::IDs Menu::getIDBotaoSelecionado()
        {
            return (*it)->getID();
        }

        /**
         * @brief  metodo que trata do movimento do mouse 
         * 
         * @param poMouse posicao atual do mouse
        */
        void Menu::eventoMouse(const sf::Vector2f posMouse){
            std::list<Botao::BotaoTexto*>::iterator aux;
            mouseSelecionado = false;
            for(aux = listaDeBotao.begin(); aux != listaDeBotao.end(); aux++)
            {
                Botao::BotaoTexto* botao = *aux;
                sf::RectangleShape caixa = botao->getCaixa();
                sf::Vector2f posMouseJan = m_pGrafic->getWindow()->mapPixelToCoords((sf::Vector2i)posMouse);
                
                if(caixa.getGlobalBounds().contains(posMouseJan))
                {
                    (*it)->setSelecionado(false);
                    it = aux;
                    (*it)->setSelecionado(true);
                    mouseSelecionado = true;
                    break;
                }
            }
        }

        /**
         * @brief metodo que desenha todos os elemntos graficos do menu
        */
        void Menu::draw()
        {
            std::list<Botao::BotaoTexto*>::iterator itAux;

            for(itAux = listaDeBotao.begin() ; itAux != listaDeBotao.end() ; itAux++)
            {
                Botao::BotaoTexto* botao = *itAux;
                botao->draw();
                botao = nullptr;
            }
        }

        /**
         * @brief metodo que cria o fundo do menu
        */
        void Menu::criarFundo()
        {
            
        }

        /**
         * @brief metodo que seleciona para a esquerda
        */
        void Menu::selecionaEsquerda()
        {

        }


        /**
         * @brief metodo que seleciona para a direita
        */
        void Menu::selecionaDireita()
        {

        }
    }
}