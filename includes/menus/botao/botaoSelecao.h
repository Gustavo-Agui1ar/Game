

#pragma once

#include "botaoTexto.h"
#include <SFML/Graphics.hpp>

#define TAM_V_FASE_X 800.f
#define TAM_V_FASE_Y 400.f

namespace Game{

    namespace Menu{

        namespace Botao{

            class BotaoSelecao : public BotaoTexto {

                private:

                    sf::RectangleShape visualizacaoFase;
                    sf::Texture texture;
                    IDs::IDs IDFase;

                public:

                BotaoSelecao(const std::string infoTexto, const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs ID, const sf::Color corSelecionado, IDs::IDs IDFase);
                ~BotaoSelecao();

                const IDs::IDs getIDFase();
                void setImagemFase(const char* caminhoImagem);
                void desenhar();

            };
        }
    }
}