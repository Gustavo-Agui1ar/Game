
#include "../includes/menus/botao/textoEfeito.h"

namespace Game{

    namespace Menu{

        namespace Botao{
            
            /**
             * @brief construtora da classe TextoEfeito
             * 
             * @param fonte fonte a ser aplicada no texto
             * @param infoTexto informacao do texto
            */
            TextoEfeito::TextoEfeito(const sf::Font fonte, const std::string infoTexto):
            Texto(fonte,infoTexto)
            {
                apagando = true;
                transparencia = 255;
            }
            
            /**
             * @brief destrutora da classe TextoEfeito
            */
            TextoEfeito::~TextoEfeito()
            {

            }

            /**
             * @brief metodo que muda a transparencia do texto
            */
            void TextoEfeito::mudarTransparencia()
            {
                apagando = (apagando) ? false : true ;
            }

            /**
             * @brief metodo de acesso ao atributo apagando
             * 
             * @return retorna um boleano que informa se o texto esta apagando ou nao 
            */
            const bool TextoEfeito::getApagando()
            {
                return apagando;
            }

            /**
             * @brief metodo de modificacao do atributo transparente
             * 
             * @param transparente transparencia a ser aplicada no texto
            */
            void TextoEfeito::setTransparente(int transparente)
            {
                this->transparencia = transparente;
                atualizar();
            }

            /**
             * @brief metodo de acesso  ao atributo transparencia
             * 
             * @return retiorna o quao transparente o texto esta em uma escala de 0 (transparente) a 255 (totalmente visivel)
            */
            const int TextoEfeito::getTransparente()
            {
                return transparencia;
            }

            /**
             * @brief metodo que atualiza o estado do atributo transparencia para 255 
            */
            void TextoEfeito::resetar()
            {
                transparencia = 255;
                atualizar();
            }

            /**
             * @brief metodo que atualiza o efeito do texto
            */
            void TextoEfeito::atualizar()
            {
                corBordaTexto = sf::Color(0,0,0,(sf::Uint8)this->transparencia);
                corTexto = sf::Color(corTexto.r, corTexto.g, corTexto.b,(sf::Uint8)this->transparencia);
                texto.setOutlineColor(corBordaTexto);
                texto.setFillColor(corTexto);
            }
         }
    }
}