
#include "../includes/botao/texto.h"

namespace Game{

    namespace Menu{

        namespace Botao{
            
            /**
             * @brief construtora dda classe Texto
             *  
             * @param fonte variavel a ser atribuida em fonte
             * @param infoTexto string a ser passada para texto
             * @param fonteTam tamanho das palavras da fonte 
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
             * @brief destrutora da classe texto
            */
            Texto::~Texto()
            {

            }

            /**
             * @brief metodo que inicializa os atributos relacionados ao texto
            */
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
             * @brief metodo que muda a cor do texto 
             * 
             * @param corTexto cor a ser substituida em texto.
            */
            void Texto::setCorTexto(const sf::Color corTexto)
            {
                this->corTexto = corTexto;
                texto.setFillColor(corTexto);
            }

            /**
             * @brief metodo que define o tamanho da borda em volta do texto
             * 
             * @param tamBorda tamanho da borda  a ser colocada em texto
            */
            void Texto::setTamanhoBorda(const float tamBorda)
            {
                texto.setOutlineThickness(tamBorda);
                tam = sf::Vector2f(texto.getGlobalBounds().width,texto.getGlobalBounds().height);
            }

            /**
             * @brief metodo que define o que texto ira exibir de informacao
             * 
             * @param infoTexto informacao a ser colocada em texto
            */
            void Texto::setString(std::string infoTexto)
            {
                this->infoTexto = infoTexto;
                texto.setString(infoTexto);
                tam = sf::Vector2f(texto.getGlobalBounds().width,texto.getGlobalBounds().height);
            }

            /**
             * @brief metodo que define um espacamento em texto
             * 
             * @param tamEspaco valor a ser usado como espacamento
            */
            void Texto::setEspacamento(const float tamEspaco)
            {
                texto.setLetterSpacing(tamEspaco);
                tam = sf::Vector2f(texto.getGlobalBounds().width,texto.getGlobalBounds().height);
            }

            /**
             * @brief metodo que define o tamanho da fonte
             * 
             * @param tamFonte valor a ser usado no tamanho da fonte.
            */
            void Texto::setTamFonte(const unsigned int tamFonte)
            {
                texto.setCharacterSize(tamFonte);
                tam = sf::Vector2f(texto.getGlobalBounds().width,texto.getGlobalBounds().height);
            }

            /**
             * @brief metodo que define a posicao do texto
             * 
             * @param pos posicao a ser atribuida em texto 
            */
            void Texto::setPos(const sf::Vector2f pos)
            {
                this->pos = pos;
                texto.setPosition(pos);
            }

            /**
             * @brief metodo de acesso ao conteudo de string de texto
             * 
             * @return retorna o conteudo de texto
            */
            const std::string Texto::getString()
            {
                return texto.getString();
            }

            /**
             * @brief metodo de acesso a posicao atual do texto
             * 
             * @return retorna a posicao do texto
            */
            const sf::Vector2f Texto::getPos()
            {
                return texto.getPosition();
            }

            /**
             * @brief metodo de acesso ao tamanho do texto(em pixel nao por letra)
             * 
             * @return retorna o tamanho do texto
            */
            const sf::Vector2f Texto::getTam()
            {
                return tam;
            }

            /**
             * @brief metodo de acesso ao texto
             * 
             * @return retorna o atributo texto 
            */
            const sf::Text Texto::getTexto()
            {
                return texto;
            }
        }
    }

}