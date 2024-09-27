
#include "../includes/menus/menuPausa.h"
#include "../includes/Observer/ObserverMenu.h"

namespace Game{

    namespace Menu{
        
        /**
         * @brief contrutora da classe MenuPause
         * 
         * @param fase fase a ser desenhada como fundo 
        */
        MenuPausa::MenuPausa(Level::Level* fase):
        Menu(IDs::IDs::pause_menu, sf::Vector2f(TAM_BOTAO_X, TAM_BOTAO_Y), "PAUSA", 100),
        painel(sf::Vector2f(tamJanela.x/2.0f,tamJanela.y)), fase(fase), fundoEscuro(tamJanela)
        {
            atualizarPosicaoFundo();
            this->titulo.setTextColor(sf::Color{245,170,0});
            fundoEscuro.setFillColor(sf::Color{0, 0, 0, 180});
            painel.setFillColor(sf::Color{0, 0, 0, 220});
            sf::Vector2f posFundoEscuro = sf::Vector2f(posFundo.x - tamJanela.x/2.0f , posFundo.y - tamJanela.y/2.0f );
            fundoEscuro.setPosition(posFundoEscuro);
            painel.setPosition(sf::Vector2f(posFundoEscuro.x + tamJanela.x/4.0f, posFundoEscuro.y));
            this->titulo.setPosition(sf::Vector2f(posFundo.x - titulo.getSize().x / 2.1f, posFundoEscuro.y + tamJanela.y / 5.0f));
        }

        /**
         * @brief construtora da classe MenuPausa
         * 
         * @param ID identidicador da classe
         * @param titulo titulo do menu  
         * @param fase fase a ser desenhada como fundo
        */
        MenuPausa::MenuPausa(const IDs::IDs ID, const std::string titulo, Level::Level* fase):
        Menu(ID, sf::Vector2f(TAM_BOTAO_X, TAM_BOTAO_Y), titulo, 100), fase(fase),
        fundoEscuro(tamJanela)
        {
            this->titulo.setTextColor(sf::Color{245,170,0});
            fundoEscuro.setFillColor(sf::Color{0, 0, 0, 180});
        }

        /**
         * @brief destrutora da classe MenuPausa
        */
        MenuPausa::~MenuPausa() = default;

        /**
         * @brief metodo de acesso ao atributo fase 
         * 
         * @return retorna o atributo fase da classe
        */
        Level::Level* MenuPausa::getFase()
        {
            return fase;
        }

        /**
         * @brief metodo que cria os botoes da classe MenuPausa
        */
        void MenuPausa::criarBotoes()
        {
            addBotao("Continuar", sf::Vector2f(0.0f, 0.0f), IDs::IDs::back_button, sf::Color{245, 170, 0});
            addBotao("Selecionar Level", sf::Vector2f(0.0f, 0.0f), IDs::IDs::select_menu_level_button, sf::Color{245, 170, 0});
            addBotao("Carregar", sf::Vector2f(0.0f, 0.0f), IDs::IDs::load_game_button, sf::Color{245, 170, 0});
            addBotao("Salvar", sf::Vector2f(0.0f, 0.0f), IDs::IDs::save_game_button, sf::Color{245, 170, 0});
            addBotao("Opcao", sf::Vector2f(0.0f, 0.0f), IDs::IDs::option_button, sf::Color{245, 170, 0});
            addBotao("Sair", sf::Vector2f(0.0f, 0.0f), IDs::IDs::close_button, sf::Color{245, 170, 0});
          
            posBotaoY = 1.5f;
            atualizarBotoes();
           
            inicialiarIterador();
        }

        /**
         * @brief metodo modificador do atributo fase
         * 
         * @param fase fase a ser atribuida em fase da classe
        */
        void MenuPausa::setFase(Level::Level* fase)
        {
            this->fase = fase;
        }

        /**
         * @brief metodo que atualiza a posicao dos botoes 
        */
        void MenuPausa::atualizarBotoes()
        {
            int i = 1;
            for(auto* button : listaDeBotao) {
                button->updateBoxPosition(sf::Vector2f(posFundo.x - tamBotao.x / 2.0f, posFundo.y / posBotaoY + (tamBotao.y + 20.f) * i));       
                i++;
            }

            draw();
        }

        /**
         * @brief metodo que mostra todos os elementos graficos do menu na tela
        */
         void MenuPausa::executar()
         {
            //desenha a fase sem atualizar as entidades
            fase->draw();

            //atualiza o menu 
            m_graphic->drawElement(fundoEscuro);
            m_graphic->drawElement(painel);

            //desenha o titulo 
            m_graphic->drawElement(titulo.getInfoText());

            //desenha os botoes
            draw();
        }
    }
}