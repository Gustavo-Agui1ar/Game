
#pragma once

#include "../includes/entidade/Ente.h"

namespace Game::Menu::Botao{
    class Botao : public Ente{

    protected:
        
        //atributo responsavel por determinar o corpo do botao 
        
        sf::RectangleShape caixa;
        sf::Texture* textura;
        
        //atributo de posicao e tamanho
        
        sf::Vector2f pos;
        sf::Vector2f tam;

        //atributos de tempo
        
        const float tempoTroca;
        float tempo;

    public:

        //construtor e destrutor
        
        Botao(const sf::Vector2f tam, const sf::Vector2f pos, const IDs::IDs ID, const float tempoTroca = 0.0f);
        ~Botao() override;

        //metodo responsavel pela visualizacao do botao
        
        void draw() override;

        //metodos de atualizacao
        
        virtual void atualizarPosicaoBotao(const sf::Vector2f pos);
        virtual void atualizarAnimacao();

        //seters dos atributos referente a classe
        
        void setTextura(sf::Texture* texture);

        //geters dos atributos referente a classe
        
        sf::RectangleShape getCaixa();
        const sf::Vector2f getPos();

    };
}