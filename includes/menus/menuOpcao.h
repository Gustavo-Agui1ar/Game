
#pragma once 

#include "menuPrincipal.h"
#include "../includes/fases/fase.h"
#include "../menus/botao/botaoVolume.h"

#define TAMANHO_BOTAO_MENU_OPCAO_X 350.0f
#define TAMANHO_BOTAO_MENU_OPCAO_Y 80.0f

#define VELOCIDADE_BOTAO_VOLUME 100.0f

namespace Game::Menu{
    class MenuOpcao : public MenuPrincipal {

    private:

        const float velBotaoVolume;
        Gerenciador::GerenciadorDeMusica* pMusica;
        Fase::Fase* fase;
        sf::RectangleShape fundoEscuro;
        

        void addBotao(const std::string info, const sf::Vector2f pos, IDs::IDs ID, const sf::Color corSelecionado, const float posInicioFundo);
        void atualizarVolume(const float volume, Botao::BotaoVolume* botao);
        void alterarVolume(const bool aumentando);

    public:

        explicit MenuOpcao(Fase::Fase* fase = nullptr);
        ~MenuOpcao() override;

        void criarBotoes() override;
        void selecionaEsquerda() override;
        void selecionaDireita() override;
        void executar() override;
    };
}