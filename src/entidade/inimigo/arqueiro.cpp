
#include "../includes/entidade/inimigo/arqueiro.h"

#define RAIO_DE_VISAO_X 200.0f
#define RAIO_DE_VISAO_Y 200.0f

namespace Game{

    namespace Entidade{

        namespace Personagem{

            namespace Inimigo{
                
                /**
                 * @brief contrutora da classe arqueiro 
                 * 
                 * @param pos posicao onde o corpo do esqueleto tera sua posicao inicial.
                 * @param tam tamanho do corpo do esqueleto
                 * @param vel velocidade com que o mesmo sera movimentado.
                 * @param jogador ponteiro para jogador que sera preciso para a movimentacao do esqueleto.
                 * 
                */
                Arqueiro::Arqueiro(sf::Vector2f pos, Jogador::Jogador *jogador, Arma::Arma* arma):
                Inimigo(pos, sf::Vector2f(TAM_ARQUEIRO_X, TAM_ARQUEIRO_Y), VEL_ARQUEIRO, jogador, ARQUEIRO_TEMPO_DE_ATAQUE,
                IDs::IDs::arqueiro, ARQUEIRO_TEMPO_LEVAR_DANO, ARQUEIRO_TEMPO_ANIMACAO_DE_MORTE,DANO_ARQUEIRO, arma)
                {
                    inicializaAnimacao();
                    inicializarSom();
                }

                /**
                 * @brief construtora da classe Esqueleto 
                 * 
                 * @param atributos json contendo as informacoes da classe
                 * @param jogador ponteiro do jogador
                */
                Arqueiro::Arqueiro(nlohmann::ordered_json atributos, Jogador::Jogador* jogador):
                Inimigo(pos, sf::Vector2f(TAM_ARQUEIRO_X,TAM_ARQUEIRO_Y), VEL_ARQUEIRO, jogador, ARQUEIRO_TEMPO_DE_ATAQUE,
                IDs::IDs::arqueiro, ARQUEIRO_TEMPO_LEVAR_DANO, ARQUEIRO_TEMPO_ANIMACAO_DE_MORTE, DANO_ARQUEIRO,  nullptr)
                {
                    try
                    {
                        sf::Vector2f posAtual = sf::Vector2f(atributos["pos"]["x"].template get<float>(), atributos["pos"]["y"].template get<float>());

                        setPos(posAtual);
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
                 * @brief destrutora da classe esqueleto
                */
                Arqueiro::~Arqueiro()
                {

                }

                 /**
                 * @brief metodo que adiciona os sprites do inimigo esqueoeto para que este possa ser utilizado pela animacao
                */
                void Arqueiro::inicializaAnimacao()
                {
                    const sf::Vector2f origem = sf::Vector2f(tam.x/2.5,tam.y/2.2);
                    animacao.addAnimacao("../Game/animations/enemy/Skeleton_Archer/Idle.png","PARADO",7,0.16,sf::Vector2f{6,2},origem);
                    animacao.addAnimacao("../Game/animations/enemy/Skeleton_Archer/Walk.png","ANDAR",8,0.16,sf::Vector2f{6,2}, origem);
                    animacao.addAnimacao("../Game/animations/enemy/Skeleton_Archer/Shot_1.png","ATACA",15,0.1,sf::Vector2f{6,2}, origem);
                    animacao.addAnimacao("../Game/animations/enemy/Skeleton_Archer/Hurt.png","TOMADANO",2,0.2,sf::Vector2f{6,2}, origem);
                    animacao.addAnimacao("../Game/animations/enemy/Skeleton_Archer/Dead.png","MORRE",5,0.25,sf::Vector2f{6,2}, origem);
                }

                /**
                 * @brief metodo que define qual sprite sera chamado e atualizado no momento da chamada do metodo.
                */
                 void Arqueiro::atualizarAnimacao()
                 {
                     if(morrendo){
                        animacao.atualizar(direcao, "MORRE");
                        tempoMorrer = tempoMorrer + pGrafico->getTempo();
                        if(tempoMorrer > tempoAnimacaoDeMorrer)
                        {
                            jogador->aumentarFuria(arma->getDano());
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
                 * @brief metodo que atualiza a parte relacionada ao ataque do arqueiro
                */
                void Arqueiro::atualizarAtaque()
                {
                    if(atacando && !morrendo)
                    {
                        tempoAtaque += pGrafico->getTempo();
                        if(tempoAtaque > tempoAnimacaoAtaque)
                        {
                            Arma::Projetil* projetil = dynamic_cast<Arma::Projetil*>(arma);
                            projetil->setPos(sf::Vector2f(pos.x + tam.x ,pos.y +  tam.y / 3.0f));
                            projetil->setColidiu(false);
                            projetil->setVelocidade(sf::Vector2f(250.0f, 0.0f));
                            projetil->setDirecao(direcao);
                            atacando = false;
                            tempoAtaque = 0.0f;
                        }
                    }
                }

                /**
                 * @brief metodo que inicializa os efeitos sonoros do esqueleto
                */
                void Arqueiro::inicializarSom()
                {
                    if(!somDeDanoBuffer.loadFromFile(SOM_DE_DANO_ARQUEIRO))
                    {
                        std::cout<< "Esqueleto: não foi possivel carregar somAtaqueBuffer";
                        exit(1);
                    }
                    somDeDano.setBuffer(somDeDanoBuffer);
                    somDeDano.setVolume(40.0f);
                }

                void Arqueiro::moveInimigo()
                {
                     if(!atacando && !morrendo && !levandoDano)
                     {

                        sf::Vector2f posInimigo = corpo.getPosition();
                        sf::Vector2f posJogador = jogador->getCorpo().getPosition();

                        const float x = fabs(posInimigo.x - posJogador.x);
                        const float y = fabs(posInimigo.y - posJogador.y);

                        if(x <= RAIO_DE_VISAO_X * 5 && y <= RAIO_DE_VISAO_Y)
                        {
                            direcao = (posJogador.x - posInimigo.x > 0.0f) ? false : true ;
                            parar();
                            
                            Arma::Projetil* projetil = dynamic_cast<Arma::Projetil*>(arma);

                            if(projetil->getColidiu())
                            { 
                                tempoAtaque += pGrafico->getTempo();
                                
                                if(tempoAtaque > tempoAnimacaoAtaque)
                                {
                                    atacando = true;
                                    tempoAtaque = 0.0f;
                                }
                            }
                        }
                        else if(x <= RAIO_DE_VISAO_X && y <= RAIO_DE_VISAO_Y){
                                fugir(posJogador,posInimigo);
                        }
                        else
                        {
                            movimentoAleatorio();
                            tempoAtaque = 0.0f;
                        }
                    }
                    else
                    {
                        tempoMover = 0.0f;
                    }
                }

                /**
                 * @brief metodo que faz o inimigo fugir do jogador atualizando a movimentacao do inimigo de acordo com a pos do jogador.
                 *
                 * @param posJogador posicao atual do jogador
                 * @param posInimigo posicao atual do inimigo
                 */
                void Arqueiro::fugir(sf::Vector2f posJogador, sf::Vector2f posInimigo)
                {
                    if(posJogador.x - posInimigo.x > 0.0f){
                        andar(true);
                    }else{
                        andar(false);
                    }
                }
            }
        }
    }
}
