
#include "../includes/botao/botao.h"

namespace Game{

    namespace Menu{

        namespace Botao{

            Botao::Botao(const sf::Vector2f tam, const sf::Vector2f pos, const IDs::IDs ID, const float tempoTroca)
            Ente(ID),tempoTroca(tempoTroca)
            {
                textura = new sf::Texture();
                tempo = 0.0f;
                this->pos = pos;
                this->tam = tam;

                caixa.setPosition(pos);
                caixa.setSize(tam);
            }

            Botao::~Botao()
            {
                if(textura)
                    delete(textura);
                textura = nullptr;
            }

            void Botao::atualizarPosicaoBotao(const sf::Vector2f pos)
            {
                this->pos = pos;
                caixa.setPosition(pos);
            }

            const sf::Vector2f Botao::getPosition()
            {
                return caixa.getPosition();        
            }

            void Botao::setTextura(sf::Texture* textura)
            {
                this->testura = textura;
                caixa.setTexture(textura);
            }

            void Botao::desenhar()
            {
                pGrafico->desenharElemento(caixa);
            }

            void Botao::atualizarAnimacao()
            {
                
            }
        }
    }

}