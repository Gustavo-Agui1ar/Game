#include "../includes/menus/menuGameOver.h"

namespace Game{

    namespace Menu{

        /**
         * @brief contrutora da classe MenuGameOver 
         * 
         * @param fase a ser desenhado o fundo
        */
        MenuGameOver::MenuGameOver(Fase::Fase* fase):
        MenuPausa(IDs::IDs::menu_gameOver, "Game Over", fase)
        {
            atualizarPosicaoFundo();

            sf::Vector2f posFundoEscuro = sf::Vector2f(posFundo.x - tamJanela.x / 2.0f, posFundo.y - tamJanela.y / 2.0f);
            fundoEscuro.setPosition(posFundoEscuro);
            titulo.setPos(sf::Vector2f(posFundo.x - titulo.getTam().x / 2.1f,  tamJanela.y / 3.0f));
            titulo.setCorTexto(sf::Color::Red);
        }

        /**
         * @brief destrutora da classe MenuGameOver
        */
        MenuGameOver::~MenuGameOver(){

        }

        /**
         * |@brief metodo que cria os botoes do menu game over
        */
        void MenuGameOver::criarBotoes()
        {
            addBotao("Tentar Novamente", sf::Vector2f(0.0f, 0.0f), IDs::IDs::botao_reniciar_jogo, sf::Color{255, 0, 0});
            addBotao("Sair", sf::Vector2f(0.0f, 0.0f), IDs::IDs::botao_sair, sf::Color{255, 0, 0});

            posBotaoY = 0.8f;
            atualizarBotoes();
            inicialiarIterador();
        } 
    }
}