
#include "../includes/botao/texto.h"

namespace Game{

    namespace Menu{

        namespace Botao{
            
            /**
             * construtora dda classe Texto
             *  
             * parametros:
             * 
             * fonte: variavel a ser atribuida em fonte
             * infoTexto: string a ser passada para texto
             * fonteTam: tamanho das palavras da fonte 
            */

            Texto::Texto(const sf::Font fonte, const std::string infoTexto, const unsigned int fonteTam):
            fonte(fonte),texto()
            {
                corBordaTexto = sf::Color::Black;
                corTexto = sf::Color::White;
                this->infoTexto = infoTexto;
                this->fonteTam = fonteTam;

                inicializa();
            }

            /**
             * destrutora da classe texto
            */

            Texto::~Texto()
            {

            }
            void Texto::inicializa()
            {
                texto.setString(infoTexto);
                texto.setCharacterSize(fonteTam);
                texto.setFont(fonte);
                texto.setOutlineThickness(5.0f);
                texto.setOutlineColor(corBordaTexto);
                texto.setFillColor(corTexto);
                tam = sf::Vector2f(texto.getGlobalBounds().width, texto.getGlobalBounds().height);
            }

            /**
             * metodo que muda a cor do texto 
             * 
             * parametros:
             * 
             * corTexto:cor a ser substituida em texto.
             * 
            */
            
            void Texto::setCorTexto(const sf::Color corTexto)
            {
                this->corTexto = corTexto;
                texto.setFillColor(corTexto);
            }

            /**
             * metodo que define o tamanho da borda em volta do texto
             * 
             * parametros:
             * 
             * tamBorda: tamanho da borda  a ser colocada em texto
            */

            void Texto::setTamanhoBorda(const float tamBorda)
            {
                texto.setOutlineThickness(tamBorda);
                tam = sf::Vector2f(texto.getGlobalBounds().width,texto.getGlobalBounds().height);
            }

            /**
             * metodo que define o que texto tera como string
             * 
             * parametros:
             * 
             * infoTexto: string a ser colocada em texto
            */

            void Texto::setString(std::string infoTexto)
            {
                this->infoTexto = infoTexto;
                texto.setString(infoTexto);
                tam = sf::Vector2f(texto.getGlobalBounds().width,texto.getGlobalBounds().height);
            }

            /**
             * metodo que define um espacamento em texto
             * 
             * parametros:
             * 
             * tamEspaco: valor a ser usado como espacamento
            */

            void Texto::setEspacamento(const float tamEspaco)
            {
                texto.setLetterSpacing(tamEspaco);
                tam = sf::Vector2f(texto.getGlobalBounds().width,texto.getGlobalBounds().height);
            }

            /**
             * metodo que define o tamanho da fonte
             * 
             * parametros:
             * 
             * tamFonte: valor a ser usado no tamanho da fonte.
            */

            void Texto::setTamFonte(const unsigned int tamFonte)
            {
                texto.setCharacterSize(tamFonte);
                tam = sf::Vector2f(texto.getGlobalBounds().width,texto.getGlobalBounds().height);
            }

            /**
             * metodo que define a posicaodo texto
             * 
             * parametros:
             * 
             * pos: posicao  onde o texto ficara
            */

            void Texto::setPos(const sf::Vector2f pos)
            {
                this->pos = pos;
                texto.setPosition(pos);
            }

            /**
             * metodo que retorna o conteudo de string de texto
            */

            const std::string Texto::getString()
            {
                return texto.getString();
            }

            /**
             * metodo que retorna a posicao atual do texto
            */

            const sf::Vector2f Texto::getPos()
            {
                return texto.getPosition();
            }

            /**
             * metodo que retorna o tamanho do texto(em pixel nao por letra)
            */

            const sf::Vector2f Texto::getTam()
            {
                return tam;
            }

            /**
             * metodo que retorna o texto
            */

            const sf::Text Texto::getTexto()
            {
                return texto;
            }
        }
    }

}