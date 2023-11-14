
#pragma once 

#include <SFML/Graphics.hpp>

namespace Game{

    namespace Menu{

        namespace Botao{
            
            class Texto{

            private:
                
                //atributo de fonte do texto
                const sf::Font fonte;
                
                //atributo de informacao
                std::string infoTexto;

            protected:

                void inicializa();

                //atributo pricipal da classe 
                sf::Text texto;

                //atributos de tamanho e posicao               
                unsigned int fonteTam;
                sf::Vector2f tam;
                sf::Vector2f pos;


                //atributos de cor do texto
                sf::Color corBordaTexto;
                sf::Color corTexto;

             public:

                Texto(const sf::Font fonte, const std::string infoTexto, const unsigned int fonteTam = 50);
                ~Texto();
                
                //metodos getters para atributos
                const std::string getString();
                const sf::Vector2f getPos();
                const sf::Vector2f getTam();
                const sf::Text getTexto();
                
                //metodos setters para atrbutos
                void setTamFonte(const unsigned int tamFonte);
                void setCorTexto(const sf::Color corTexto);
                void setTamanhoBorda(const float tamBorda);
                void setEspacamento(const float tamEspaco);
                void setString(std::string infoTexto);
                void setPos(const sf::Vector2f pos);
                
            };
        }
    }
}