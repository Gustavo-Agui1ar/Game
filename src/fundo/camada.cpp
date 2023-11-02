
#include "../../includes/fundo/camada.h"
#include <math.h>

namespace Game{

    namespace Fundo{

        /**
         * construtora da classe camada 
         * 
         * parametros:
         * 
         * tamjanela: tamanho desta camada.
         * textura: textura a ser usada nesta camada.
         * velociadade: velocidade com que a camada se movimentara na tela.
         * 
        */

        Camada::Camada(const sf::Vector2f tamJanela, sf::Texture textura,const float velocidade):
        tamJanela(tamJanela),textura(textura),escala(0,0,0,0),velocidade(velocidade)
        {
            escala.width = -(textura.getSize().x);
            escala.height = (textura.getSize().y);
            escala.left = (textura.getSize().x);


            fundo.setSize(tamJanela);
            fundo.setTexture(&this->textura);
            fundo.setPosition(0.0f,0.0f);

            fundoAuxiliar.setSize(tamJanela);
            fundoAuxiliar.setTexture(&this->textura);
            fundoAuxiliar.setPosition(tamJanela.x,0.0f);
        }
        
        /**
         *  destrutora da classe camada.
        */

        Camada::~Camada(){}

        /**
         * metodo que faz a troca do fundo Auxiliar 
         * e do fundo Principal.
         * 
        */

        void Camada::trocarTextura()
        {
            sf::RectangleShape auxTroca = fundo;

            fundo = fundoAuxiliar;
            fundoAuxiliar = auxTroca;
        }

        /**
         * metodo desenha a camada na tela
         * 
         * parametros:
         * 
         * window: janela a ser desenhada a camada.
         *  
        */

        void Camada::desenharCamada(sf::RenderWindow* window)
        {
            window->draw(fundo);

            if(velocidade != 0.0f){
                window->draw(fundoAuxiliar);
            }
        }


        /**
         * metodo que atualiza a posicao da camada na tela 
         * 
         * ds: variacao na distancia percorrida pelo jogador.
         * posCameraAtual: nescessario para determinar as extremidades da janela.
         *  
        */

        void Camada::atualizar(const sf::Vector2f ds, const sf::Vector2f posCameraAtual)
        {
            sf::Vector2f posFundo = fundo.getPosition();
            sf::Vector2f posFundoAux = fundoAuxiliar.getPosition();
            fundo.setPosition(sf::Vector2f(posFundo.x, 0.0f));
            fundoAuxiliar.setPosition(sf::Vector2f(posFundoAux.x, 0.0f));
            const float dx = ds.x * 0.5f;

            if(dx != 0.0f)
            {
                const float posDireita = posCameraAtual.x + tamJanela.x / 2.0f;
                const float posEsquerda = posCameraAtual.x - tamJanela.x / 2.0f;

                if(velocidade != 0.0f)
                {
                    //aplicando o movimento contr�rio para as camadas
                    fundo.move(dx * -velocidade, 0.0f);
                    fundoAuxiliar.move(dx * -velocidade, 0.0f);

                    if(ds.x > 0.0f) // camera movendo para a direita

                    {
                        if(posFundo.x + tamJanela.x < posEsquerda)
                        {
                            trocarTextura();
                            fundo.setPosition(posEsquerda, posFundo.y);
                            fundoAuxiliar.setPosition(posDireita, posFundoAux.y);
                        }

                    }
                    else // camera movendo para a esquerda
                    {
                        if(posFundo.x > posEsquerda)
                        {
                            trocarTextura();
                            fundo.setPosition(posEsquerda - tamJanela.x, posFundo.y);
                            fundoAuxiliar.setPosition(posEsquerda, posFundoAux.y);
                        }
                    }
                }
                //seta o fundo comecando na extremidade esquuerda caso o fundo nao tenha movimento.
                else
                {
                    fundo.setPosition(posEsquerda, posFundo.y);
                }
            }

        }


    }


}
