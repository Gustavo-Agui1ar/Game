
#pragma once

#include "../entidade/Ente.h"

namespace Game{

    namespace Menu{

        namespace Botao{

            class Botao : public Ente{

            protected:

                sf::RetangleShape caixa;
                sf::Texture* textura;
                sf::Vector2f pos;
                sf::Vector2f tam;

                const float tempoTroca;
                float tempo;

            public:

                Botao(const sf::Vector2f tam, const sf::Vector2f pos, const IDs::IDs ID, const float tempoTroca = 0.0f);
                virtual ~Botao();

                virtual void desenhar();
                virtual void atualizarAnimacao();
                virtual void atualizarPosicaoBotao();
                void setTexture(sf::Texture* texture);
                const sf::Vector2f getPos();

            };
        }
    }
}