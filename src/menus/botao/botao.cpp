
#include "../includes/menus/botao/botao.h"

namespace Game{

    namespace Menu{

        namespace Botao{
            
            /**
             * @brief construtora da classe botao
             * 
             * @param tam tamanho do botao
             * @param pos posicao do botao
             * @param ID identificacao do botao
             * @param tempoTroca troca deEfeito do botao
            */
            Botao::Botao(const sf::Vector2f tam, const sf::Vector2f pos, const IDs::IDs ID, const float tempoTroca):
            Ente(ID),tempoTroca(tempoTroca)
            {
                textura = new sf::Texture();
                tempo = 0.0f;
                this->pos = pos;
                this->tam = tam;

                caixa.setPosition(pos);
                caixa.setSize(tam);
            }

            /**
             * @brief destrutora da classe botao
            */
            Botao::~Botao()
            {
                if(textura)
                    delete(textura);
                textura = nullptr;
            }

            /**
             * @brief atualiza a posicao do botao na tela 
             * 
             * @param pos posicao nova a ser definida no botao
            */
            void Botao::atualizarPosicaoBotao(const sf::Vector2f pos)
            {
                this->pos = pos;
                caixa.setPosition(pos);
            }

            /**
             * @brief metodo de acesso a posicao do botao
             * 
             * @return retorna a posicao do botao
            */
            const sf::Vector2f Botao::getPos()
            {
                return caixa.getPosition();        
            }

            /**
             * @brief metodo modificador do atributo textura
             * 
             * @param textura textura a ser aplicada no botao
            */
            void Botao::setTextura(sf::Texture* textura)
            {
                this->textura = textura;
                caixa.setTexture(textura);
            }

            /**
             * @brief metodo responsavel por mostrar o botao na tela  
            */
            void Botao::draw()
            {
                m_pGrafic->desenhaElemento(caixa);
            }

            /**
             * @brief metodo para atualizar o efeito do botao
            */
            void Botao::atualizarAnimacao()
            {
                
            }

            /**
             * @brief metodo que retorna a caixa em volta do botao
             * 
             * @return retorna um rectangleShape do botao
            */
            sf::RectangleShape Botao::getCaixa()
            {
                return caixa;
            }
        }
    }

}