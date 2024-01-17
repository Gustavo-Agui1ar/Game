
#include "../includes/entidade/inimigo/slime.h"

namespace Game{

    namespace Entidade{

        namespace Personagem{

            namespace Inimigo{

                /**
                 * @brief contrutora da classe slime 
                 * 
                 * 
                 * @param pos posicao onde o corpo do slime tera sua posicao inicial.
                 * @param tam tamanho do corpo do slime.
                 * @param vel velocidade com que o mesmo sera movimentado.
                 * @param jogador ponteiro para jogador que sera preciso para a movimentacao do slime.
                 * 
                */
                Slime::Slime(sf::Vector2f pos, Jogador::Jogador *jogador, Arma::Arma* arma):
                Inimigo(pos,  sf::Vector2f(TAM_SLIME_X, TAM_SLIME_Y), VEL_SLIME, jogador, SLIME_TEMPO_DE_ATAQUE, IDs::IDs::red_slime, 
                SLIME_TEMPO_DE_TOMAR_DANO, SLIME_TEMPO_ANIMACAO_DE_MORTE, DANO_SLIME, arma)
                {
                    inicializaAnimacao();
                    inicializarSom();
                }
                
                /**
                 * @brief construtora da classe Slime
                 * 
                 * @param atributos json contendo todas as informcoes da classe
                 * @param jogador ponteiro para o jogador
                */
                Slime::Slime(nlohmann::ordered_json atributos, Jogador::Jogador *jogador):
                Inimigo(pos,  sf::Vector2f(TAM_SLIME_X, TAM_SLIME_Y), VEL_SLIME, jogador, SLIME_TEMPO_DE_ATAQUE, IDs::IDs::red_slime, 
                SLIME_TEMPO_DE_TOMAR_DANO, SLIME_TEMPO_ANIMACAO_DE_MORTE, DANO_SLIME, nullptr)
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
                 * @brief destrutora da classe slime
                */
                Slime::~Slime()
                {

                }

                /**
                 * @brief metodo que adiciona os sprites do 
                 * inimigo slime para que este possa ser utilizado pela animacao
                */
                void Slime::inicializaAnimacao()
                {
                    const sf::Vector2f origem = sf::Vector2f(tam.x/2.5,tam.y/2.2);
                    animacao.addAnimacao("..\\Game\\animations\\enemy\\Red_Slime\\Idle.png","PARADO",8,0.16,sf::Vector2f{6,2}, origem);
                    animacao.addAnimacao("..\\Game\\animations\\enemy\\Red_Slime\\Walk.png","ANDAR",8,0.16,sf::Vector2f{6,2}, origem);
                    animacao.addAnimacao("..\\Game\\animations\\enemy\\Red_Slime\\Attack_3.png","ATACA",5,0.16,sf::Vector2f{6,2}, origem);
                    animacao.addAnimacao("..\\Game\\animations\\enemy\\Red_Slime\\Dead.png","MORRE",3,0.2,sf::Vector2f{6,2}, origem);
                    animacao.addAnimacao("..\\Game\\animations\\enemy\\Red_Slime\\Hurt.png","TOMADANO",6,0.1,sf::Vector2f{6,2}, origem);
                  
                }

                /**
                 * @brief metodo que define qual sprite sera 
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
                 * @brief metodo que atualiza a parte 
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

                /**
                 * @brief metodo que inicializa os efeitos sonoros da classe
                */
                void Slime::inicializarSom()
                {
                    if(!somDeDanoBuffer.loadFromFile(SOM_DE_DANO_SLIME))
                    {
                        std::cout<< "Slime: não foi possivel carregar somAtaqueBuffer";
                        exit(1);
                    }
                    somDeDano.setBuffer(somDeDanoBuffer);
                    somDeDano.setVolume(40.0f);
                }
            }
        }
    }
}

