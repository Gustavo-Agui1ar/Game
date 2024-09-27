#include "../includes/menus/menuGameOver.h"

namespace Game::Menu{

    /**
     * @brief contrutora da classe MenuGameOver 
     * 
     * @param fase a ser desenhado o fundo
    */
    MenuGameOver::MenuGameOver(Level::Level* fase):
    MenuPausa(IDs::IDs::game_over_menu, "Game Over", fase)
    {
        atualizarPosicaoFundo();

        auto posFundoEscuro = sf::Vector2f(posFundo.x - tamJanela.x / 2.0f, posFundo.y - tamJanela.y / 2.0f);
        fundoEscuro.setPosition(posFundoEscuro);
        titulo.setPosition(sf::Vector2f(posFundo.x - titulo.getSize().x / 2.1f,  tamJanela.y / 3.0f));
        titulo.setTextColor(sf::Color::Red);
    }

    /**
     * @brief destrutora da classe MenuGameOver
    */
    MenuGameOver::~MenuGameOver() = default;

    /**
     * |@brief metodo que cria os botoes do menu game over
    */
    void MenuGameOver::criarBotoes()
    {
        addBotao("Tentar Novamente", sf::Vector2f(0.0f, 0.0f), IDs::IDs::restart_button, sf::Color{255, 0, 0});
        addBotao("Sair", sf::Vector2f(0.0f, 0.0f), IDs::IDs::close_button, sf::Color{255, 0, 0});

        posBotaoY = 0.8f;
        atualizarBotoes();
        inicialiarIterador();
    } 
}