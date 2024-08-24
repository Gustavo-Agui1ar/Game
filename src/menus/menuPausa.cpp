
#include "../includes/menus/menuPausa.h"
#include "../includes/listeners/listenerMenu.h"

namespace Game{

    namespace Menu{
        
        /**
         * @brief contrutora da classe MenuPause
         * 
         * @param fase fase a ser desenhada como fundo 
        */
        MenuPausa::MenuPausa(Fase::Fase* fase):
        Menu(IDs::IDs::menu_pause, sf::Vector2f(TAM_BOTAO_X, TAM_BOTAO_Y), "PAUSA", 100),
        painel(sf::Vector2f(tamJanela.x/2.0f,tamJanela.y)), fase(fase), fundoEscuro(tamJanela)
        {
            atualizarPosicaoFundo();
            this->titulo.setCorTexto(sf::Color{245,170,0});
            fundoEscuro.setFillColor(sf::Color{0, 0, 0, 180});
            painel.setFillColor(sf::Color{0, 0, 0, 220});
            sf::Vector2f posFundoEscuro = sf::Vector2f(posFundo.x - tamJanela.x/2.0f , posFundo.y - tamJanela.y/2.0f );
            fundoEscuro.setPosition(posFundoEscuro);
            painel.setPosition(sf::Vector2f(posFundoEscuro.x + tamJanela.x/4.0f, posFundoEscuro.y));
            this->titulo.setPos(sf::Vector2f(posFundo.x - titulo.getTam().x / 2.1f, posFundoEscuro.y + tamJanela.y / 5.0f));
        }

        /**
         * @brief construtora da classe MenuPausa
         * 
         * @param ID identidicador da classe
         * @param titulo titulo do menu  
         * @param fase fase a ser desenhada como fundo
        */
        MenuPausa::MenuPausa(const IDs::IDs ID, const std::string titulo, Fase::Fase* fase):
        Menu(ID, sf::Vector2f(TAM_BOTAO_X, TAM_BOTAO_Y), titulo, 100), fase(fase),
        fundoEscuro(tamJanela)
        {
            this->titulo.setCorTexto(sf::Color{245,170,0});
            fundoEscuro.setFillColor(sf::Color{0, 0, 0, 180});
        }

        /**
         * @brief destrutora da classe MenuPausa
        */
        MenuPausa::~MenuPausa()
        {

        }

        /**
         * @brief metodo de acesso ao atributo fase 
         * 
         * @return retorna o atributo fase da classe
        */
        Fase::Fase* MenuPausa::getFase()
        {
            return fase;
        }

        /**
         * @brief metodo que cria os botoes da classe MenuPausa
        */
        void MenuPausa::criarBotoes()
        {
            addBotao("Continuar", sf::Vector2f(0.0f, 0.0f), IDs::IDs::botao_voltar, sf::Color{245, 170, 0});
            addBotao("Selecionar Fase", sf::Vector2f(0.0f, 0.0f), IDs::IDs::botao_menu_selecao_fase, sf::Color{245, 170, 0});
            addBotao("Carregar", sf::Vector2f(0.0f, 0.0f), IDs::IDs::botao_carregar_jogo, sf::Color{245, 170, 0});
            addBotao("Salvar", sf::Vector2f(0.0f, 0.0f), IDs::IDs::botao_salvar_jogo, sf::Color{245, 170, 0});
            addBotao("Opcao", sf::Vector2f(0.0f, 0.0f), IDs::IDs::botao_opcao, sf::Color{245, 170, 0});
            addBotao("Sair", sf::Vector2f(0.0f, 0.0f), IDs::IDs::botao_sair, sf::Color{245, 170, 0});
          
            posBotaoY = 1.5f;
            atualizarBotoes();
           
            inicialiarIterador();
        }

        /**
         * @brief metodo modificador do atributo fase
         * 
         * @param fase fase a ser atribuida em fase da classe
        */
        void MenuPausa::setFase(Fase::Fase* fase)
        {
            this->fase = fase;
        }

        /**
         * @brief metodo que atualiza a posicao dos botoes 
        */
        void MenuPausa::atualizarBotoes()
        {
            std::list<Botao::BotaoTexto*>::iterator aux;
            int i = 1;
            for(aux = listaDeBotao.begin(); aux != listaDeBotao.end(); aux++, i++){
                Botao::BotaoTexto* botao = *aux;
                botao->atualizarPosicaoDaCaixa(sf::Vector2f(posFundo.x - tamBotao.x / 2.0f, posFundo.y / posBotaoY + (tamBotao.y + 20.f) * i));       
                botao = nullptr;
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
            m_pGrafic->desenhaElemento(fundoEscuro);
            m_pGrafic->desenhaElemento(painel);

            //desenha o titulo 
            m_pGrafic->desenhaElemento(titulo.getTexto());

            //desenha os botoes
            draw();
        }
    }
}