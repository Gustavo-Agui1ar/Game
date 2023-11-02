
#pragma once

#include <SFML/Graphics.hpp>
#include "../gerenciador/gerenciadorGrafico.h"

namespace Game{

    namespace animador{

        class Imagem{

        private:

            Gerenciador::GerenciadorGrafico * pGrafico;
            
            //metodos relacionados as dimencoes da imagem.
            const sf::Vector2f escala;
            sf::Texture textura;
            sf::IntRect tamanho;

            //metodos relacionados ao tempo
            const unsigned int totalDeQuadrosImagem;
            unsigned int quadroAtual;
            const float tempoTroca;
            float tempoTotal;

        public:

            //construtor e destrutor.
            Imagem(const char* caminhoTextura, const unsigned int totalDeQuadrosImagem, const float tempoTroca, sf::Vector2f escala);
            ~Imagem();

            //metodos de atualizacao da imagem.
            void atualizar(bool direcao,const float dt);
            void resetar();
          
            //metodos geters dda classe
            const sf::IntRect  getTamanho() const;
            const sf::Texture* getTextura() const;
            const sf::Vector2f getEscala() const;
        };
    }

}
