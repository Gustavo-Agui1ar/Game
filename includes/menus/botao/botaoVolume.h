
#pragma once 

#include "botaoTexto.h"
#include "../includes/Manager/MusicManager.h"

#define TAMANHO_BARRA_VOLUME_X 450.0f
#define TAMANHO_BARRA_VOLUME_Y 30.0f

#define TAMANHO_BOTAO_VOLUME_X 50.0f
#define TAMANHO_BOTAO_VOLUME_Y 30.0f

namespace Game::Menu::Botao{
    class BotaoVolume : public BotaoTexto{

    
    private:

        sf::RectangleShape fundoVolume;
        sf::RectangleShape corpoVolume;

        Manager::MusicManager* pMusica;

        const float posInicioFundo;
        const float parametrizacao;

        float posInicioBarra;
        float posFimBarra;

        void atualizarVolume();

    public:

        BotaoVolume(const std::string info, sf::Vector2f tam, const sf::Vector2f pos, const IDs::IDs ID, const sf::Color corSelecionado, const float posInicioFundo);
        ~BotaoVolume() override;
        void draw() override;
        void alterarVolume(const float volume);
};
}