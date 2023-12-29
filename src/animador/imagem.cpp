
#include "../../includes/animador/imagem.h"

namespace Game{

    namespace animador{
        

        /**
         * costrutora da classe imagem
         * 
         * parametros:
         * 
         * caminhoTextura: onde esta a textura
         * totalDeQuadrosImagem:quantidade de sprites da imagem.
         * tempoDeTroca: tempo total entre cada troca de sprite.
         * escala: escala da imagem.
         * 
        */

        Imagem::Imagem(const char* caminhoTextura, const unsigned int totalDeQuadrosImagem, const float tempoTroca, sf::Vector2f escala):
        pGrafico(pGrafico->getGerenciadorGrafico()),  escala(escala), textura(pGrafico->carregarTextura(caminhoTextura)),
        totalDeQuadrosImagem(totalDeQuadrosImagem),quadroAtual(0),tempoTroca(tempoTroca),tempoTotal(0)
        {
            tamanho.width = textura.getSize().x/ (float) totalDeQuadrosImagem;
            tamanho.height = textura.getSize().y;
        }

        /**
         * destrutora da classe imagem.
        */

        Imagem::~Imagem()
        {

        }

        /**
         * metodo que atualiza a imagem
         * 
         * parametros:
         * 
         * direcao: atributo que mostra a direcao do jogador.
         * dt: tempo decorrido com esta imagem.
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
         * metodo que reinicia aq imagem 
         * zerando o tempo e a imagem atual.
        */

        void Imagem::resetar()
        {
            tempoTotal = 0.0f;
            quadroAtual = 0;
        }

        /**
         * metodo que retorna o tamnha da imagem.
        */

        const sf::IntRect  Imagem::getTamanho() const
        {
            return tamanho;
        }

        /**
         * metodo que retorna a textura da imagem.
        */

        const sf::Texture* Imagem::getTextura() const
        {
            return &textura;
        }

        /**
         *metodo que retorna a escala da imagem. 
        */

        const sf::Vector2f Imagem::getEscala() const
        {
            return escala;
        }

        void Imagem::setQuadroAtual(const unsigned int imgAtual)
        {
            this->quadroAtual = imgAtual;
        }

        
        void Imagem::setTempoTotal(const float tempo)
        {
            tempoTotal = tempo;
        }

        const float Imagem::getTempoTotal()
        {
            return tempoTotal;
        }
        
        const unsigned int Imagem::getQuadroAtual()
        {
            return quadroAtual;    
        }
    }
}
