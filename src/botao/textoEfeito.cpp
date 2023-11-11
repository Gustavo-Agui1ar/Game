
#include "../includes/botao/textoEfeito.h"

namespace Game{

    namespace Menu{

        namespace Botao{

            TextoEfeito::TextoEfeito(const sf::Font fonte, const std::string infoTexto):
            Texto(fonte,infoTexto)
            {
                apagando = true;
                transparente = 255;
            }

            TextoEfeito::~TextoEfeito()
            {

            }

            void TextoEfeito::mudarTransparencia()
            {
                apagando = (apagando) ? false : true ;
            }

            const bool TextoEfeito::getApagando()
            {
                return apagando;
            }

            void TextoEfeito::setTransparente(int transparente)
            {
                this->transparente = transparente;
                atualizar();
            }

            const int TextoEfeito::getTransparente()
            {
                return transparente;
            }

            void TextoEfeito::resetar()
            {
                transparente = 255;
                atualizar();
            }

            void TextoEfeito::atualizar()
            {
                corborda = sf::Color(0,0,0,(sf::Uint8)this->transparente);
                corTexto = (texto.r, texto.g, texto.b,(sf::Uint8)this->transparente);
                texto.setOutlineColor(corBorda);
                texto.SetFillColor(corTexto);
            }
        }
    }
}