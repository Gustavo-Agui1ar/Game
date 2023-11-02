
#include "../../includes/inimigo/inimigo.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>

#define VEL_INIMIGO_X 5.f
#define VEL_INIMIGO_Y 5.f

#define RAIO_DE_VISAO_X 200.0f
#define RAIO_DE_VISAO_Y 200.0f

namespace Game{

    namespace Entidade{

        namespace Personagem{

            namespace Inimigo{

                /**
                 * construtor da classe inimigo
                 *
                 * parametros:
                 *
                 * pos,tam,vel,ID::inimigo: parametros nescessarios para inicializar a classe Personagem.
                 * jogador: ponteiro para um objeto da classe jogador.
                 */

                Inimigo::Inimigo(sf::Vector2f pos, sf::Vector2f tam, const float vel, Jogador::Jogador *jogador,const float tempoAnimacaoAtaque ,IDs::IDs ID, const float tempoAnimacaoDeLevarDano, const float tempoAnimacaoDeMorrer, float dano, Item::Arma* arma):
                Personagem(pos,tam,vel,ID, tempoAnimacaoDeLevarDano, tempoAnimacaoDeMorrer, dano),tempoAnimacaoAtaque(tempoAnimacaoAtaque)
                {
                    this->jogador = jogador;
                    tempoMover = 0.0f;
                    tempoAtaque = 0.0f;

                     srand(time(NULL));
                     mover = rand()%3;

                    inicializarBarraDeVida();

                    if(arma != nullptr)
                    {
                        setArma(arma);
                    }
                }

                /**
                 * metodo que faz o inimigo perseguir o jogador atualizando a movimenta��o do inimigo de acordo com a pos do jogador.
                 *
                 * parametros:
                 *
                 * posJogador: posi��o atual do jogador
                 * posInimigo: posi��o atual do inimigo
                 */

                void Inimigo::persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo)
                {
                    if(posJogador.x - posInimigo.x > 0.0f){
                        andar(false);
                    }else{
                        andar(true);
                    }
                }

                /**
                 * metodo que faz com que o inimigo ande euma dire��o aleatoria
                 * sendo as dire��es possiveis esquerda direita e parado.
                 */

                void Inimigo::movimentoAleatorio()
                {
                    if(tempoMover > 1.5f){
                        mover = rand()%3;
                        if(mover == 0){
                            andar(false);
                        }else if(mover == 1){
                            andar(true);
                        }else{
                            parar();
                        }
                        tempoMover = 0.0f;
                    }
                }

                /**
                 * metodo que serve para atualizar  a movimenta��o  do  inimigo
                 * atualizando esta de acordo se o jogador esta ou n�o no campo
                 * campo de vis�o do inimigo(se  sim  ele  persegue  se n�o ele
                 * se move aleatoriamente).
                 */
                void Inimigo::atualizar()
                {
                    moveInimigo();

                    tempoMover += pGrafico->getTempo();

                    atualizarAtaque();

                    atualizarBarraDeVida();

                    atualizarPosicao();

                    atualizarAnimacao();
                }
                /**
                 * metodo  que  atualiza  a  anima��o  do  inimigo   de  acordo  com  o
                 * que ele esta fazendo exemplo: movendo = true e paraEsquerda = true
                 * a anima��o resultante  e  o sprite  de andar  no sentido da esquerdajo
                 */

                void Inimigo::atualizarAnimacao()
                {
                    if(morrendo && podeRemover == false)
                    {
                        animacao.atualizar(direcao, "MORRE");
                        tempoMorrer += pGrafico->getTempo();
                        if(tempoMorrer > tempoAnimacaoDeMorrer)
                        {
                            remover();
                            tempoMorrer = 0.0f;
                            if(arma != nullptr)
                            {
                                arma->remover();
                                arma = nullptr;
                            }
                        }
                    }
                    else if(levandoDano)
                        animacao.atualizar(direcao,"TOMADANO");
                    else if(atacando)
                        animacao.atualizar(direcao,"ATACA");
                    else if(movendo)
                        animacao.atualizar(direcao,"ANDAR");
                    else
                        animacao.atualizar(direcao,"PARADO");
                }

                /**
                 * metodo que move o inimigo de acordo com os atributos 
                 * atacando e posicao do jogador.
                */

                void Inimigo::moveInimigo()
                {
                     if(!atacando && !morrendo && !levandoDano)
                     {

                        sf::Vector2f posInimigo = corpo.getPosition();
                        sf::Vector2f posJogador = jogador->getCorpo().getPosition();

                        if(fabs(posJogador.x - posInimigo.x) <= RAIO_DE_VISAO_X && fabs(posJogador.y - posInimigo.y) <= RAIO_DE_VISAO_Y){
                                persegueJogador(posJogador,posInimigo);
                        }
                        else
                        {
                            movimentoAleatorio();
                        }
                    }
                    else
                    {
                        tempoMover = 0.0f;
                    }
                }

                /**
                 * metodo que verifica se o inimigo  esta atacando 
                 * se estiver atualiza o tempo decorrido da animacao de ataque.
                */
                void Inimigo::atualizarAtaque()
                {
                    if(atacando && !morrendo)
                    {
                        tempoAtaque += pGrafico->getTempo();
                        if(tempoAtaque > tempoAnimacaoAtaque)
                        {
                            atacando = false;
                            tempoAtaque = 0.0f;
                        }
                    }
                }
                
                /**
                 * metodo que inicializa a barra de vida do inimigo
                 * definido posicao, tamanho e textura a mesma.
                */
                void Inimigo::inicializarBarraDeVida()
                {
                    barraDeVida.setSize((sf::Vector2f(BARRA_VIDA_X, BARRA_VIDA_Y)));
                    sf::Texture* textura = new sf::Texture(); 
                    textura->loadFromFile("..\\Game\\animations\\Life\\VidaInimigo.png");
                    barraDeVida.setTexture(textura);
                }

                /**
                 * destrutora da classe desaloca a textura da barra de vida e retira o apontamento de arma
                */

                Inimigo::~Inimigo()
                {
                    if(barraDeVida.getTexture()){
                        delete(barraDeVida.getTexture());
                    }
                    if(arma != nullptr)
                        arma = nullptr;
                }

            }
        }
    }
}


