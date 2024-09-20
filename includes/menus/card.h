
#pragma once

#include "Menu.h"
#include "../Manager/GraphicManager.h"

#define CARD_FONTE "/Game/animations/backgorund/card/card-vazio.png"

namespace Game::Menu {


    class Card {

    private:

        //atributos visuais

        sf::RectangleShape* corpo;
        sf::Texture* textura;
        bool selecionado;
        sf::Color cor;
        bool existe;

        //atributos de informacao

        const std::string caminhoEntidades;
        const std::string caminhoImagem;
        const std::string caminhoFase;


        static Manager::GraphicManager* pGrafico;

    public:

        //coonstrutor e destrutor

        Card(const sf::Vector2f pos, const std::string caminhoEntidades, const std::string caminhoImagem, const std::string caminhoFase);
        ~Card();

        //getters da classe

        const std::string getCaminhoEntidade();
        const std::string getCaminhoImagem();
        const std::string getCaminhoFase();
        const bool getSelecionado();
        const bool getExiste();
        sf::Vector2f getPos();

        //setters da classe

        void setColor(const sf::Color cor);
        void setSelecionado(const bool selecionado);

        //metodo de delecao dos atributos que contem caminho a um arquivo

        void deletarTextura();

        //metodo que mostraa na tela o card

        void draw();
    };
}