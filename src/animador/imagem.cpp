
#include "../../includes/animador/imagem.h"

namespace Game{

    namespace Animador{
        

        /**
         * @brief costrutora da classe imagem
         * 
         * @param caminhoTextura: onde esta a textura
         * 
         * @param totalDeQuadrosImagem:quantidade de sprites da imagem.
         * 
         * @param tempoDeTroca: tempo total entre cada troca de sprite.
         * 
         * @param escala: escala da imagem.
         * 
        */
        Imagem::Imagem(const char* caminhoTextura, const unsigned int totalDeQuadrosImagem, const float tempoTroca, sf::Vector2f escala, sf::Vector2f origem ):
        pGrafico(pGrafico->getGerenciadorGrafico()),  escala(escala), origem(origem),  textura(pGrafico->carregarTextura(caminhoTextura)),
        totalDeQuadrosImagem(totalDeQuadrosImagem),quadroAtual(0),tempoTroca(tempoTroca),tempoTotal(0)
        {
            tamanho.width = textura.getSize().x/ (float) totalDeQuadrosImagem;
            tamanho.height = textura.getSize().y;
        }

        /**
         * @brief destrutora da classe imagem.
        */
        Imagem::~Imagem()
        {

        }

        /**
         * @brief metodo que atualiza a imagem
         * 
         * @param direcao atributo que mostra a direcao do jogador.
         *
         * @param dt tempo decorrido com esta imagem.
         * 
         * @return metodo sem retorno (void)
        */
        void Imagem::atualizar(bool direcao, const float dt)
        {
            tempoTotal += dt;
            if(tempoTotal >= tempoTroca)
            {
                tempoTotal -= tempoTroca;
                this->quadroAtual = (quadroAtual + 1)%totalDeQuadrosImagem;
            }

            if(direcao)
            {
                tamanho.left = (quadroAtual + 1) * abs(tamanho.width);
                tamanho.width = -abs(tamanho.width);
            }
            else
            {
                tamanho.left = (quadroAtual) * abs(tamanho.width);
                tamanho.width = abs(tamanho.width);
            }
        }

        /**
         *  @brief metodo que reinicia aq imagem 
         *  zerando o tempo e a imagem atual.
        */
        void Imagem::resetar()
        {
            tempoTotal = 0.0f;
            quadroAtual = 0;
        }

        /**
         * @brief metodo que retorna o tamnha da imagem.
        */
        const sf::IntRect  Imagem::getTamanho() const
        {
            return tamanho;
        }

        /**
         * @brief metodo que retorna a textura da imagem.
         * 
         * @return retorna a textura da imagem
        */
        const sf::Texture* Imagem::getTextura() const
        {
            return &textura;
        }

        /**
         * @brief metodo que retorna a escala da imagem. 
         *
         * @return retorna a escala da imagem
        */
        const sf::Vector2f Imagem::getEscala() const
        {
            return escala;
        }
        
        /**
         * @brief metodo que modifica o atributo quadroAtual
         * 
         * @param imgAtual valor a ser atribuido em estadoAtual
         * 
        */
        void Imagem::setQuadroAtual(const unsigned int imgAtual)
        {
            this->quadroAtual = imgAtual;
        }

        /**
         * @brief metodo que modifica o atributo tempoTotal
         * 
         * @param tempo valor a ser atribuido em tempototal
         * 
        */
        void Imagem::setTempoTotal(const float tempo)
        {
            tempoTotal = tempo;
        }

        /**
         * @brief metodo que retorna o atributo tempoTotal
         * 
         * @return retorna o valor em tempototal
         * 
        */
        const float Imagem::getTempoTotal()
        {
            return tempoTotal;
        }
        
        /**
         * @brief metodo que retorna o atributo quadroAtual
         * 
         * @return retorna o valor em quadroAtual
         * 
        */
        const unsigned int Imagem::getQuadroAtual()
        {
            return quadroAtual;    
        }

        /**
         * @brief metodo que retorna o atributo origem
         * 
         * @return retorna o valor em origem
         * 
        */
        const sf::Vector2f Imagem::getOrigem(){
            return origem;
        }
    }
}
