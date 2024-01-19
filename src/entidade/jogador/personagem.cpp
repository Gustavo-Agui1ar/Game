#include "../includes/entidade/jogador/personagem.h"
#include <iostream>
#include <math.h>

namespace Game{

    namespace Entidade{

        namespace Personagem{

            /**
             * @brief destrutora da classe personagem.
             */
            Personagem::~Personagem(){}

            /**
             * @brief costrutora da classe personagem.
             *
             * @param pos posicao do corpo nescessario para construtora de entidade.
             * @param tam tamanho do corpo nescessario para construtora de entidade.
             * @param ID  ID a ser enviado nescessario para de entidade.
             * @param vel velocidade de movimento do personagem.
             */
            Personagem::Personagem(const sf::Vector2f pos, const sf::Vector2f tam, const float vel, const IDs::IDs ID, const float tempoAnimacaoDeLevarDano, const float tempoAnimacaoDeMorrer, const float dano):
            Entidade(tam,ID, pos),animacao(&corpo),velocidade(sf::Vector2f(vel,0)) , velMax(vel),
             movendo(false),direcao(false), dt(0.0f), vidaMaxima(100.0f), vida(100.0f), tempoAnimacaoDeLevarDano(tempoAnimacaoDeLevarDano),
             tempoAnimacaoDeMorrer(tempoAnimacaoDeMorrer), tempoMorrer(0.0f), tempoDano(0.0f), morrendo(false), levandoDano(false), atacando(false)
            {
                this->dano = dano;
                arma = nullptr;
            }

            /**
             * @brief metodo que muda o atributo booleano movendo para false.
             */
            void Personagem::parar()
            {
                movendo = false;
            }

            /**
             * @brief metodo que altera o estado do atributo direcao e movendo.
             *
             * @param direcao booleano que diz qual direcao o personagem esta olhando.
             */
            void Personagem::andar(bool direcao)
            {
                this->direcao = direcao;
                movendo = true;
            }

            /**
             * @brief metodo que move o personagem nas 4 direcoes esquerda direita cima e baixo.
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
             * @brief metodo de acesso a velocidade do personagem.
             * 
             * @return retorna a velocidade do personagem
            */
            sf::Vector2f Personagem::getVelocidade()
            {
                return velocidade;
            }

            /**
             * @brief metodo que seta a velocidade do personagem(este metodo altera tanto a velocidade em x quanto em y).
             *
             * @param vel valor a ser inserido em velocidade.
            */
            void Personagem::setVelMax(sf::Vector2f vel)
            {
                velocidade = vel;
            }
            
            /**
             * @brief metodo que altera o estado do boleano de ataque do personagem
            */
            void Personagem::atacar()
            {
                atacando = true;
                movendo = false;
            }


            /**
             * @brief metodo que altera o estado do boleano de ataque do personagem
            */
            void Personagem::pararAtaque()
            {
                atacando = false;
                arma->setPos(sf::Vector2f(-1000.0f, -1000.f));
            }

            /**
             * @brief metodo que atualiza a barra de vida do personagem
             * de acordo com sua posicao
            */
            void Personagem::atualizarBarraDeVida()
            {
                sf::Vector2f posVida(sf::Vector2f(pos.x + tam.x/2.0f - corpo.getSize().x/2.0f, pos.y - 20.0f));
                barraDeVida.setPosition(posVida);
                barraDeVida.setSize((sf::Vector2f((vida/vidaMaxima)* BARRA_VIDA_X, BARRA_VIDA_Y)));
            }
            
            /**
             * @brief metodo que mostra o corpo e a barra de vida na tela.
            */
            void Personagem::desenhar()
            {
                pGrafico->desenhaElemento(barraDeVida);
                pGrafico->desenhaElemento(corpo);
              
            }

            /**
             * @brief metodo que  retorna o estado do 
             * boleano de morrer do personagem
            */
            const bool Personagem::getMorrer()
            {
                return morrendo;
            }
           
            /**
             * @brief metodo que  retorna o estado do 
             * boleano de morrer do personagem
            */
            const bool Personagem::getDirecao()
            {
                return direcao;
            }
            
            /**
             * @brief metodo que auxilia na tomada de dano.
             * 
             * @param dano valor a ser descontado da vida do jogador.
            */
            void Personagem::tomarDano(const float dano)
            {
                if(!levandoDano)
                {
                    levandoDano = true;
                    atacando = false;
                    movendo = false;
                    vida -= dano;
                    if(vida <= 0.0f)
                    {
                        morrendo = true;
                        levandoDano = false;
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
             * @brief metodo responsavel por atualiar o
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
             * @brief metodo que seta a arma do personagem atribuindo a ela: dano e tamanho.
             * ( posicao  é  inicializada  no  construtor  do  objeto  arma )
            */
            void Personagem::setArma(Arma::Arma* arma)
            {
                this->arma = arma;
                this->arma->setDano(dano);
                this->arma->setTam(tam);
            }

            /**
             * @brief metodo que salva o estado de um objeto desta classe 
             * 
             * @return retorna um json contendo o estado atual de um objeto desta classe
            */
            nlohmann::ordered_json Personagem::salvarPersonagem()
            {
                nlohmann::ordered_json json = salvarEntidade();

                json["velocidade"] = {{"x", velocidade.x}, {"y", velocidade.y}};
                json["tempoMorrer"] = (float)tempoMorrer;
                json["levandoDano"] = levandoDano;
                json["tempoDano"] = tempoDano;
                json["morrendo"] = morrendo;
                json["atacando"] = atacando;
                json["movendo"] = movendo;
                json["direcao"] = direcao;
                json["dano"] = dano;
                json["vida"] = vida;
                json["dt"] = dt;

                return json;
            }

        }

    }
}

