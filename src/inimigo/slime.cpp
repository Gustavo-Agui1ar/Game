
#include "../../includes/inimigo/slime.h"

namespace Game{

    namespace Entidade{

        namespace Personagem{

            namespace Inimigo{

                /**
                 * contrutora da classe slime 
                 * 
                 * parametros:
                 * 
                 * (nescessarios para a costrutora do inimigo)
                 * 
                 * pos: posicao onde o corpo do slime tera sua posicao inicial.
                 * tam: tamanho do corpo do slime.
                 * vel: velocidade com que o mesmo sera movimentado.
                 * jogador: ponteiro para jogador que sera preciso para a movimentacao do slime.
                 * 
                */

                Slime::Slime(sf::Vector2f pos, sf::Vector2f tam, const float vel, Jogador::Jogador *jogador, Item::Arma* arma):
                Inimigo(pos, tam, vel,jogador,SLIME_TEMPO_DE_ATAQUE, IDs::IDs::red_slime, 
                SLIME_TEMPO_DE_TOMAR_DANO, SLIME_TEMPO_ANIMACAO_DE_MORTE, DANO_SLIME, arma)
                {
                    inicializaAnimacao();
                }

                /**
                 * destrutora da classe slime
                */

                Slime::~Slime()
                {

                }

                /**
                 * metodo que adiciona os sprites do 
                 * inimigo slime para que este possa ser utilizado pela animacao
                */

                void Slime::inicializaAnimacao()
                {
                    animacao.addAnimacao("..\\Game\\animations\\enemy\\Red_Slime\\Idle.png","PARADO",8,0.16,sf::Vector2f{6,2});
                    animacao.addAnimacao("..\\Game\\animations\\enemy\\Red_Slime\\Walk.png","ANDAR",8,0.16,sf::Vector2f{6,2});
                    animacao.addAnimacao("..\\Game\\animations\\enemy\\Red_Slime\\Attack_3.png","ATACA",5,0.16,sf::Vector2f{6,2});
                    animacao.addAnimacao("..\\Game\\animations\\enemy\\Red_Slime\\Dead.png","MORRE",3,0.2,sf::Vector2f{6,2});
                    animacao.addAnimacao("..\\Game\\animations\\enemy\\Red_Slime\\Hurt.png","TOMADANO",6,0.1,sf::Vector2f{6,2});
                    corpo.setOrigin(sf::Vector2f(tam.x/2.5,tam.y/2.2));
                }

                /**
                 * metodo que define qual sprite sera 
                 * chamado e atualizado no momento da
                 * chamada do metodo.
                */

                void Slime::atualizarAnimacao()
                {
                     if(morrendo && !podeRemover){
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
                 * metodo  que   atualiza   a   parte 
                 * relacionada ao ataque do slime
                */

                void Slime::atualizarAtaque()
                {
                    if(atacando && !morrendo)
                    {
                        tempoAtaque += pGrafico->getTempo();
                        if(tempoAtaque > tempoAnimacaoAtaque)
                        {
                            arma->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                            atacando = false;
                            tempoAtaque = 0.0f;
                        }
                        else if(tempoAtaque > tempoAnimacaoAtaque/2.0f)
                        {
                            sf::Vector2f posArma = (direcao ? sf::Vector2f(pos.x - arma->getTam().x/2.0f,pos.y) : sf::Vector2f(pos.x + arma->getTam().x/2.0f,pos.y));
                            arma->setPos(posArma);
                        }
                    }

                   
                }
            }
        }
    }
}

