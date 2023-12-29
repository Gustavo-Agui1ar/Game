
#include "../../includes/inimigo/esqueleto.h"

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
                 * pos: posicao onde o corpo do esqueleto tera sua posicao inicial.
                 * tam: tamanho do corpo do esqueleto
                 * vel: velocidade com que o mesmo sera movimentado.
                 * jogador: ponteiro para jogador que sera preciso para a movimentacao do esqueleto.
                 * 
                */

                Esqueleto::Esqueleto(sf::Vector2f pos, Jogador::Jogador *jogador, Item::Arma* arma):
                Inimigo(pos, sf::Vector2f(TAM_ESQUELETO_X, TAM_ESQUELETO_Y), VEL_ESQUELETO, jogador, ESQUELETO_TEMPO_DE_ATAQUE,
                IDs::IDs::esqueleto, ESQUELETO_TEMPO_LEVAR_DANO, ESQUELETO_TEMPO_ANIMACAO_DE_MORTE,DANO_ESQUELETO, arma)
                {
                    inicializaAnimacao();
                }

                Esqueleto::Esqueleto(nlohmann::ordered_json atributos, Jogador::Jogador* jogador):
                Inimigo(pos, sf::Vector2f(TAM_ESQUELETO_X,TAM_ESQUELETO_Y), VEL_ESQUELETO, jogador, ESQUELETO_TEMPO_DE_ATAQUE,
                IDs::IDs::esqueleto, ESQUELETO_TEMPO_LEVAR_DANO, ESQUELETO_TEMPO_ANIMACAO_DE_MORTE, DANO_ESQUELETO,  nullptr)
                {
                    try
                    {
                        tempoMorrer = atributos["tempoMorrer"].template get<float>();
                        levandoDano = atributos["levandoDano"].template get<bool>();
                        tempoDano = atributos["tempoDano"].template get<float>();
                        morrendo = atributos["morrendo"].template get<bool>();
                        atacando = atributos["atacando"].template get<bool>();
                        movendo = atributos["movendo"].template get<bool>();
                        direcao = atributos["direcao"].template get<bool>();
                        dano = atributos["dano"].template get<float>();
                        vida = atributos["vida"].template get<float>();
                        dt = atributos["dt"].template get<float>();
                        tempoAtaque = atributos["tempoAtaque"].template get<float>();
                        tempoMover = atributos["tempoMover"].template get<float>();
                        mover = atributos["mover"].template get<short>();
                        
                        inicializaAnimacao();

                        animacao.setImgAtual(atributos["imagemAtual"].template get<std::string>());
                        animacao.setTempoTotal(atributos["tempoTotal"].template get<float>());
                        animacao.setQuadroAtual(atributos["quadroAtual"].template get<unsigned int>());
                        
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                        podeRemover = true;
                    }
                    
                }
                
                /**
                 * destrutora da classe esqueleto
                */

                Esqueleto::~Esqueleto()
                {

                }

                 /**
                 * metodo que adiciona os sprites do 
                 * inimigo slime para que este possa ser utilizado pela animacao
                */

                void Esqueleto::inicializaAnimacao()
                {
                    animacao.addAnimacao("..\\Game\\animations\\enemy\\Skeleton_Spearman\\Idle.png","PARADO",7,0.16,sf::Vector2f{6,2});
                    animacao.addAnimacao("..\\Game\\animations\\enemy\\Skeleton_Spearman\\Walk.png","ANDAR",7,0.16,sf::Vector2f{6,2});
                    animacao.addAnimacao("..\\Game\\animations\\enemy\\Skeleton_Spearman\\Attack_1.png","ATACA",4,0.2,sf::Vector2f{6,2});
                    animacao.addAnimacao("..\\Game\\animations\\enemy\\Skeleton_Spearman\\Hurt.png","TOMADANO",3,0.2,sf::Vector2f{6,2});
                    animacao.addAnimacao("..\\Game\\animations\\enemy\\Skeleton_Spearman\\Dead.png","MORRE",5,0.25,sf::Vector2f{6,2});
                    corpo.setOrigin(sf::Vector2f(tam.x/2.5,tam.y/2.2));
                }

                /**
                 * metodo que define qual sprite sera 
                 * chamado e atualizado no momento da
                 * chamada do metodo.
                */

                 void Esqueleto::atualizarAnimacao()
                 {
                     if(morrendo){
                        animacao.atualizar(direcao, "MORRE");
                        tempoMorrer = tempoMorrer + pGrafico->getTempo();
                        if(tempoMorrer > tempoAnimacaoDeMorrer)
                        {
                            podeRemover = true;
                            tempoMorrer = 0.0f;
                            if(arma != nullptr)
                            {
                                arma->remover();
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
                 * relacionada ao ataque do esqueleto
                */

                void Esqueleto::atualizarAtaque()
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
