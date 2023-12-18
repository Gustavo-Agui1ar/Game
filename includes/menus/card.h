
#pragma once

#include "Menu.h"
#include "../Gerenciador/gerenciadorGrafico.h"

#define CARD_FONTE "/Game/animations/backgorund/card/card-vazio.png"

namespace Game {

    namespace Menu{

        class Card {

        private:

            sf::RectangleShape* corpo;
            sf::Texture* textura;

            const std::string caminhoEntidades;
            const std::string caminhoImagem;
            const std::string caminhoFase;

            sf::Color cor;
            bool selecionado;
            bool existe;

            static Gerenciador::GerenciadorGrafico* pGrafico;

        public:

            Card(const sf::Vector2f pos, const std::string caminhoEntidades, const std::string caminhoImagem, const std::string caminhoFase);
            ~Card();

            const std::string getCaminhoEntidade();
            const std::string getCaminhoImagem();
            const std::string getCaminhoFase();

            void setColor(const sf::Color cor);
            void setSelecionado(const bool selecionado);
            const bool getSelecionado();
            const bool getExiste();
            void deletarTextura();
            void desenhar();
        };
    }
}