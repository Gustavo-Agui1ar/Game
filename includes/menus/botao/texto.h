
#pragma once 

#include <SFML/Graphics.hpp>

namespace Game::Menu::Botao{


    
    class Texto{

    protected:
        
        
        const sf::Font fonte;
        
        std::string infoTexto;

        void inicializa();

        sf::Text texto;

        unsigned int fonteTam;
        sf::Vector2f tam;
        sf::Vector2f pos;

        sf::Color corBordaTexto;
        sf::Color corTexto;

    public:

        Texto(const sf::Font fonte, const std::string infoTexto, const unsigned int fonteTam = 50);
        ~Texto();
        
        const std::string getString();
        const sf::Vector2f getPos();
        const sf::Vector2f getTam();
        const sf::Text getTexto();
        
        void setTamFonte(const unsigned int tamFonte);
        void setCorTexto(const sf::Color corTexto);
        void setTamanhoBorda(const float tamBorda);
        void setEspacamento(const float tamEspaco);
        void setString(sf::String infoTexto);
        void setPos(const sf::Vector2f pos);
        
    };
}