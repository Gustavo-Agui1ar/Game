

#pragma once

#include "texto.h"
#include "../includes/gerenciador/gerenciadorGrafico.h"

namespace Game::Menu::Botao{
    class TextoFala : public Texto{

        private:

        const float tempoDeTroca;
        float tempo;
        bool fimTexto;

        Gerenciador::GerenciadorGrafico* pGrafico;
        const int m_numenberOfLetters = 82;
        int m_currentNumberOfLetter;

        std::string falaCompleta;
        std::string::iterator letraFala;

    public:

        TextoFala(const float tempoTroca, const sf::Font fonte, const std::string infoTexto, const unsigned int fonteTam = 50);
        ~TextoFala();

        void incrementarFala();
        void inicializarIterador();
        void mostrarFalaInteira();
        const bool getFimTexto();
        const float getTempoTroca();
        void setTexto(sf::String texto);
        std::string getFalaCompleta();
        void atualizar();

    };

}