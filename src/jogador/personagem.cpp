#include "../../includes/jogador/personagem.h"
#include <iostream>
#include <math.h>

namespace Game{

    namespace Entidade{

        namespace Personagem{

            /**
             * destrutora da classe personagem.
             */

            Personagem::~Personagem(){}

            /**
             * costrutora da classe personagem.
             *
             * parametros:
             *
             * pos: posi��o do corpo nescessario para construtora de entidade.
             * tam: tamanho do corpo nescessario para construtora de entidade.
             * ID:  ID a ser enviado nescessario para de entidade.
             * vel: velocidade de movimento do personagem.
             */

            Personagem::Personagem(const sf::Vector2f pos, const sf::Vector2f tam, const float vel, const IDs::IDs ID, const float tempoAnimacaoDeLevarDano, const float tempoAnimacaoDeMorrer, const float dano):
            Entidade(tam,ID, pos),animacao(&corpo),velocidade(sf::Vector2f(vel,0)) , velMax(vel), movendo(false),direcao(false), dt(0.0f),tempoAnimacaoDeLevarDano(tempoAnimacaoDeLevarDano),tempoAnimacaoDeMorrer(tempoAnimacaoDeMorrer), vidaMaxima(100.0f)
            {
                levandoDano = false;
                this->dano = dano;
                tempoDano = 0.0f;
                atacando = false;
                morrendo = false;
                arma = nullptr;
                vida = 100.0f;
            }

            /**
             * metodo que muda o atributo booleano movendo para false.
             */

            void Personagem::parar()
            {
                movendo = false;
            }

            /**
             * matodo que altera o estado do atributo direcao e movendo.
             *
             * parametros:
             *
             * paraEsqurda: booleano que diz qual dire��o o personagem esta.
             */

            void Personagem::andar(bool direcao)
            {
                this->direcao = direcao;
                movendo = true;
            }

            /**
             * metodo que move o personagem nas 4 dire��es esquerda direita cima e baixo.
             *
             * explica��o longa: o metodo pega a varia��o do tempo e atualiza a posi��o x
             * em uma das 2 dire��es esquerda(distancia negativa) ou direita(distancia positiva)
             * apos isto aplica um efeito que simula o efeito da gravidade assim alterando a posi�a� em y.
             *
             */

            void Personagem::atualizarPosicao()
            {
                dt = pGrafico->getTempo();

                sf::Vector2f ds(0.f,0.f);
              
                if(movendo && !morrendo && !levandoDano){
                    ds.x = velocidade.x * dt;

                if(direcao)
                    ds.x *= -1;
                }

                //efeito da gravidade
                const float Vy = velocidade.y;
                velocidade.y = velocidade.y + GRAVIDADE * dt;
                ds.y = Vy * dt + (GRAVIDADE * dt * dt) / 2.0f;

                setPos(sf::Vector2f(pos.x + ds.x, pos.y + ds.y ));

                velocidade.x = velMax;

                atualizarTempoDano();

                desenhar();
            }

            /**
             * metodo que retorna a velocidade do personagem.
            */

            sf::Vector2f Personagem::getVelocidade()
            {
                return velocidade;
            }

            /**
             * metodo que seta a velocidade do personagem(este metodo altera tanto a velocidade em x quanto em y).
             *
             * parametros:
             *
             * vel: valor a ser inserido em velocidade.
            */

            void Personagem::setVelMax(sf::Vector2f vel)
            {
                velocidade = vel;
            }
            
            /**
             * metodo que altera o estado do boleano de ataque do personagem
             * 
            */

            void Personagem::atacar()
            {
                atacando = true;
                movendo = false;
            }


            /**
             * metodo que altera o estado do boleano de ataque do personagem
             * 
            */

            void Personagem::pararAtaque()
            {
                atacando = false;
            }

            /**
             * metodo que atualiza a barra de vida do personagem
             * de acordo com sua posicao
            */
            void Personagem::atualizarBarraDeVida()
            {
                sf::Vector2f posVida(sf::Vector2f(pos.x + tam.x/2.0f - corpo.getSize().x/2.0f, pos.y - 20.0f));
                barraDeVida.setPosition(posVida);
                barraDeVida.setSize((sf::Vector2f((vida/vidaMaxima)* BARRA_VIDA_X, BARRA_VIDA_Y)));
            }
            
            /**
             * metodo que mostra o corpo e a barra de vida na tela.
            */
           
            void Personagem::desenhar()
            {
                pGrafico->desenhaElemento(barraDeVida);
                pGrafico->desenhaElemento(corpo);
              
            }

            /**
             * metodo que  retorna o estado do 
             * boleano de morrer do personagem
            */

            const bool Personagem::getMorrer()
            {
                return morrendo;
            }
            
            /**
             * metodo que auxilia na tomada de dano.
             * 
             * parametros:
             * 
             * dano: valor a ser descontado da vida do jogador.
            */

            void Personagem::tomarDano(const float dano)
            {
                if(!levandoDano)
                {
                    levandoDano = true;
                    movendo = false;
                    vida -= dano;
                    if(vida <= 0.0f)
                    {
                        morrendo = true;
                        vida = 0.0f;
                        
                        if(arma != nullptr)
                        {
                            arma->remover();
                        }
                    }
                    tempoDano = 0.0f;
                }
            }

            /**
             * metodo responsavel por atualiar o
             * estado de tomarDano do personagem
            */

            void Personagem::atualizarTempoDano()
            {
                tempoDano += pGrafico->getTempo();

                if(levandoDano && tempoDano > tempoAnimacaoDeLevarDano)
                {
                    levandoDano = false;
                    tempoDano = 0.0f;
                }
            }

            /**
             * metodo que seta a arma do personagem atribuindo a ela: dano e tamanho.
             * ( posicao  é  inicializada  no  construtor  do  objeto  arma )
            */
            
            void Personagem::setArma(Item::Arma* arma)
            {
                this->arma = arma;
                this->arma->setDano(dano);
                this->arma->setTam(tam);
            }

            nlohmann::ordered_json Personagem::salvarPersonagem()
            {
                nlohmann::ordered_json json = salvarEntidade();

                json["velocidade"] = {{"x", velocidade.x}, {"y", velocidade.y}};
                json["tempoMorrer"] = this->tempoMorrer;
                json["levandoDano"] = this->levandoDano;
                json["tempoDano"] = this->tempoDano;
                json["morrendo"] = this->morrendo;
                json["atacando"] = this->atacando;
                json["movendo"] = this->movendo;
                json["direcao"] = this->direcao;
                json["dano"] = this->dano;
                json["vida"] = this->vida;
                json["dt"] = this->dt;

                return json;
            }

        }

    }
}

