
#pragma once

#include "imagem.h"
#include <map>

namespace Game{

    namespace animador{

        class Animacao{

        private:

            //atributo com referencia ao corpo para evitar chamadas de metodos.
            sf::RectangleShape *corpo;
            
            //atributos relaciondos a imagem
            std::map<std::string, Imagem*> mapImagem;
            std::string estadoAtual;
            
            //atributos de tempo
            sf::Clock relogio;

        public:
        
            // construtor e destrutor
            Animacao(sf::RectangleShape* corpo);
            ~Animacao();

            //metodo de atualizacao de animacao
            void atualizar(bool direcao, std::string estadoAtual);

            //metodo de adicionar a animacao
            void addAnimacao(const char* caminhoTextura, std::string nomeDaAnimacao, const unsigned int qtdImagem, const float tempoTroca, sf::Vector2f escala);
            void setTempoTotal(const float tempo);
            void setImgAtual(std::string img);
            void setQuadroAtual(const unsigned int quadro);

            const float getTempoTotal();
            const unsigned int getQuadroAtual();
            const std::string getIMagemAtual();
        };
    }
}
