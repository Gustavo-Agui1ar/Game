
#pragma once 

#include "menuPrincipal.h"
#include "../includes/Levels/Level.h"
#include "../menus/Button/VolumeButton.h"

#define TAMANHO_BOTAO_MENU_OPCAO_X 350.0f
#define TAMANHO_BOTAO_MENU_OPCAO_Y 80.0f

#define VELOCIDADE_BOTAO_VOLUME 100.0f

namespace Game::Menu{
    class MenuOpcao : public MenuPrincipal {

    private:

        const float velBotaoVolume;
        Manager::MusicManager* pMusica;
        Level::Level* fase;
        sf::RectangleShape fundoEscuro;
        bool mousePressed;        

        void addBotao(const std::string info, const sf::Vector2f pos, IDs::IDs ID, const sf::Color corSelecionado, const float posInicioFundo);
        void atualizarVolume(const float volume, Button::VolumeButton* botao);
        void alterarVolume(const bool aumentando);

    public:

        explicit MenuOpcao(Level::Level* fase = nullptr);
        ~MenuOpcao() override;

        void criarBotoes() override;
        void selecionaEsquerda() override;
        void selecionaDireita() override;
        void executar() override;

        void eventoMouse(const sf::Vector2f posMouse) override;
        void changeMouseState(bool pressed);
        bool checkAndSelectButton(std::list<Button::TextButton*>::iterator& it, std::list<Button::TextButton*>::iterator& aux, sf::RectangleShape box, const sf::Vector2f& posMouseJan);
    };
} 