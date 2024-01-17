
#pragma once

#include <SFML/Graphics.hpp>
#include "../gerenciador/gerenciadorGrafico.h"

namespace Game{

    namespace Animador{

        class Imagem{

        private:

            Gerenciador::GerenciadorGrafico * pGrafico;
            
            //metodos relacionados as dimencoes da imagem.
          
            const sf::Vector2f escala;
            const sf::Vector2f origem;
            sf::Texture textura;
            sf::IntRect tamanho;

            //metodos relacionados ao tempo
          
            const unsigned int totalDeQuadrosImagem;
            unsigned int quadroAtual;
            const float tempoTroca;
            float tempoTotal;

        public:

            //construtor e destrutor.
          
            Imagem(const char* caminhoTextura, const unsigned int totalDeQuadrosImagem, const float tempoTroca, sf::Vector2f escala, sf::Vector2f origin);
            ~Imagem();

            //metodos de atualizacao da imagem.
          
            void atualizar(bool direcao,const float dt);
            
            
            //metodos seters da classe
          
            void setQuadroAtual(const unsigned int imgAtual);
            void setTempoTotal(const float tempo);
            void resetar();
          
            //metodos geters da classe
          
            const sf::IntRect  getTamanho() const;
            const sf::Texture* getTextura() const;
            const sf::Vector2f getEscala() const;
            const unsigned int getQuadroAtual();
            const sf::Vector2f getOrigem();
            const float getTempoTotal();
        };
    }

}
