#include "../includes/listeners/listenerJogador.h"
#include "../includes/entidade/inimigo/esqueleto.h"
#include "../includes/entidade/npcs/npc.h"
#include "../includes/entidade/jogador/jogador.h"
#include "../includes/entidade/inimigo/slime.h"
#include "../includes/gerenciador/gerenciadorDeColisao.h"


namespace Game{

    namespace Entidade{

        namespace Personagem{

            namespace Jogador{
                    
                    /**
                     * @brief destrutora da classe Jogador 
                    */
                    Jogador::~Jogador()
                    {
                        if(listenerJogador != nullptr)
                        {
                            delete(listenerJogador);
                            listenerJogador = nullptr;
                        }
                        if(tuboVida.getTexture()){
                            delete(tuboVida.getTexture());
                        }

                        if(barraDeVida.getTexture()){
                            delete(barraDeVida.getTexture());
                        }
                    }
                    
                    /**
                     * @brief construtora da classe Jogador
                     *
                     * @param pos posicao do jogador
                     * @param arma arma do jogador
                     */
                    Jogador::Jogador(const sf::Vector2f pos,  Arma::Arma* arma, Arma::Projetil* projetil):
                    Personagem(pos,sf::Vector2f(TAM_JOGADOR_X,TAM_JOGADOR_Y), VELOCIDADE_JOGADOR_X, IDs::IDs::jogador, JOGADOR_TEMPO_LEVAR_DANO, JOGADOR_ANIMACAO_DE_MORTE, DANO_JOGADOR),noChao(false),
                    qtdPulo(0), tempoAnimacaoDash(TEMPO_DASH), velDash(VELOCIDADE_DASH_JOGADOR_X), tempoDash(0.0f), podeDash(false), emDash(false), tempoAnimacaoAtaque(JOGADOR_TEMPO_DANO), 
                    tempoAtaque(0.0f), podeRegenerarStamina(false), tempoRegStamina(0.0f),  stamina(STAMINA_MAXIMA) , furia(100.0f), emFuria(false),  entrandoEmFuria(false), tempoAnimacaoFuria(JOGADOR_TEMPO_ATE_FURIA), tempoEntrandoFuria(0.0f),
                    listenerJogador(new Listener::ListenerJogador(this)), projetil(projetil), lancandoProjetil(false), tempoAnimacaoProjetil(JOGADOR_TEMPO_PROJEIL), tempoAtaqueProjetil(0.0f)
                    {
                      
                       inicializarAnimacao();

                       inicializarBarraDeVida();

                       inicializarBarraDeStamina();

                       inicializarBarraDeFuria();

                       inicializarSom();

                       if(arma != nullptr)
                       {
                          setArma(arma);
                       }
                      
                       if(projetil != nullptr)
                       {
                          setProjetil(projetil);
                       }

                    }

                    /**
                     * @brief construtora da classe jogador
                     * 
                     * @param atributos json contendo todas as informacoes da classe jogador
                    */
                    Jogador::Jogador(nlohmann::ordered_json atributos):
                    Personagem(pos,sf::Vector2f(TAM_JOGADOR_X,TAM_JOGADOR_Y), VELOCIDADE_JOGADOR_X, IDs::IDs::jogador, JOGADOR_TEMPO_LEVAR_DANO, JOGADOR_ANIMACAO_DE_MORTE, DANO_JOGADOR),
                    tempoAnimacaoDash(TEMPO_DASH), velDash(VELOCIDADE_DASH_JOGADOR_X), tempoAnimacaoAtaque(JOGADOR_TEMPO_DANO) ,tempoAtaque(0.0f), tempoAnimacaoFuria(JOGADOR_TEMPO_ATE_FURIA), listenerJogador(new Listener::ListenerJogador(this)),
                    projetil(nullptr) , tempoAnimacaoProjetil(JOGADOR_TEMPO_PROJEIL)
                    {
                        try
                        {
                            sf::Vector2f posAtual = sf::Vector2f(atributos["pos"]["x"].template get<float>(), atributos["pos"]["y"].template get<float>());
                            sf::Vector2f tamAtual = sf::Vector2f(atributos["tam"]["x"].template get<float>(), atributos["tam"]["y"].template get<float>());
                            sf::Vector2f velAtual = sf::Vector2f(atributos["velocidade"]["x"].template get<float>(), atributos["velocidade"]["y"].template get<float>());

                            setPos(posAtual);
                            setTam(tamAtual);
                            setVelMax(velAtual);

                            movendo = atributos["movendo"].template get<bool>();
                            direcao = atributos["direcao"].template get<bool>();
                            levandoDano = atributos["levandoDano"].template get<bool>();
                            atacando = atributos["atacando"].template get<bool>();
                            morrendo = atributos["morrendo"].template get<bool>();
                            vida = atributos["vida"].template get<float>();
                            tempoDano =  atributos["tempoDano"].template get<float>();
                            tempoMorrer =  atributos["tempoMorrer"].template get<float>();
                            dt =  atributos["vida"].template get<float>();
                            dano =  atributos["dano"].template get<float>();
                            stamina =  atributos["stamina"].template get<float>();
                            noChao = atributos["noChao"].template get<bool>();
                            qtdPulo = atributos["qtdPulo"].template get<int>();
                            emDash = atributos["emDash"].template get<bool>();
                            podeDash = atributos["podeDash"].template get<bool>();
                            tempoDash = atributos["tempoDash"].template get<float>();
                            furia = atributos["furia"].template get<float>();
                            emFuria = atributos["emFuria"].template get<bool>();
                            lancandoProjetil = atributos["lancandoProjetil"].template get<bool>();
                            entrandoEmFuria = atributos["entrandoEmFuria"].template get<bool>();
                            tempoAtaqueProjetil = atributos["tempoAtaqueProjetil"].template get<float>();

                            inicializarAnimacao();
                            inicializarBarraDeVida();
                            inicializarBarraDeStamina();
                            inicializarBarraDeFuria();
                            inicializarSom();

                            animacao.setImgAtual(atributos["imagemAtual"].template get<std::string>());
                            animacao.setQuadroAtual(atributos["tempoTotal"].template get<unsigned int>());
                            animacao.setTempoTotal(atributos["tempoTotal"].template get<float>());

                        }
                        catch(const std::exception& e)
                        {
                            std::cerr <<e.what() << std::endl;
                            podeRemover = true;
                        }
                    }

                    /**
                     * @brief metodo que inicializa a animacao  do jogador
                    */
                    void Jogador::inicializarAnimacao()
                    {
                        const sf::Vector2f origemT = sf::Vector2f((tam.x/2),(tam.y/5));
                        animacao.addAnimacao(CAMINHO_TEXTURA_IDLE,"PARADO",8,0.2f,sf::Vector2f{2, 1.1}, sf::Vector2f(origemT.x, origemT.y/3));
                        animacao.addAnimacao(CAMINHO_TEXTURA_JUMP,"PULO",3,0.16f,sf::Vector2f{2.5, 1.25}, origemT);
                        animacao.addAnimacao(CAMINHO_TEXTURA_DOWN,"CAINDO",3,0.12f,sf::Vector2f{2.5, 1.25}, origemT);
                        animacao.addAnimacao(CAMINHO_TEXTURA_DASH,"DASH",4,0.12f,sf::Vector2f{4.5,  0.8},  sf::Vector2f(origemT.x, origemT.y/4));
                        animacao.addAnimacao(CAMINHO_TEXTURA_RUN,"CORRENDO",8,0.12f,sf::Vector2f{2.5, 1.25}, origemT);
                        animacao.addAnimacao(CAMINHO_TEXTURA_ATTACK,"ATACAR",4,0.15f,sf::Vector2f{3.0, 1.1},  sf::Vector2f(origemT.x, origemT.y/2));
                        animacao.addAnimacao(CAMINHO_TEXTURA_DEAD,"MORRE",12,0.15f,sf::Vector2f{3, 1.5}, sf::Vector2f(origemT.x - origemT.x/2, origemT.y));
                        animacao.addAnimacao(CAMINHO_TEXTURA_HIT,"TOMADANO",3,0.15f,sf::Vector2f{2.2, 1.1}, sf::Vector2f(origemT.x, origemT.y/3));
                        animacao.addAnimacao(CAMINHO_TEXTURA_PROJETIL,"LANCANDO_PROJETIL",9,0.1f,sf::Vector2f{3.5, 1.12}, sf::Vector2f(origemT.x, origemT.y/5));
                   
                        animacao.addAnimacao(CAMINHO_TEXTURA_IDLE_FIRE,"PARADO-F",8,0.2f,sf::Vector2f{2, 1.1}, sf::Vector2f(origemT.x, origemT.y/5));
                        animacao.addAnimacao(CAMINHO_TEXTURA_JUMP_FIRE,"PULO-F",3,0.16f,sf::Vector2f{2.5, 1.25}, origemT);
                        animacao.addAnimacao(CAMINHO_TEXTURA_DOWN_FIRE,"CAINDO-F",3,0.12f,sf::Vector2f{2.5, 1.25}, origemT);
                        animacao.addAnimacao(CAMINHO_TEXTURA_DASH_FIRE,"DASH-F",4,0.12f,sf::Vector2f{4.5,  0.8},  sf::Vector2f(origemT.x, origemT.y/4));
                        animacao.addAnimacao(CAMINHO_TEXTURA_RUN_FIRE,"CORRENDO-F",8,0.12f,sf::Vector2f{2.5, 1.1},  sf::Vector2f(origemT.x, origemT.y/4));
                        animacao.addAnimacao(CAMINHO_TEXTURA_ATTACK_FIRE,"ATACAR-F",4,0.15f,sf::Vector2f{3.0, 1.1},  sf::Vector2f(origemT.x, origemT.y/4));
                        animacao.addAnimacao(CAMINHO_TEXTURA_DEAD_FIRE,"MORRE-F",11,0.15f,sf::Vector2f{3, 1.5}, sf::Vector2f(origemT.x - origemT.x/2, origemT.y));
                        animacao.addAnimacao(CAMINHO_TEXTURA_HIT_FIRE,"TOMADANO-F",4,0.15f,sf::Vector2f{2.2, 1.1}, sf::Vector2f(origemT.x, origemT.y/3));
                        animacao.addAnimacao(CAMINHO_TEXTURA_PROJETIL_FIRE,"LANCANDO_PROJETIL-F",9,0.1f,sf::Vector2f{3.5, 1.12}, sf::Vector2f(origemT.x, origemT.y/5));
                        animacao.addAnimacao(CAMINHO_TEXTURA_FURIA,"ENTRANDO_FURIA",12,0.1f,sf::Vector2f{3.0, 1.12}, sf::Vector2f(origemT.x, origemT.y/5));

                    }

                    /**
                     * @brief metodo  que atualiza a poiscao,aniimacao,
                     * barra de vida e camera que seque o jogador
                     */
                    void Jogador::atualizar()
                    {
                        atualizarPosicao();

                        atualizarArma();

                        atualizarProjetil();

                        pGrafico->atualizarCamera(getPos());

                        atualizarAnimacao();
                        
                        atualizarBarraDeVida();

                        atualizarBarraDeStamina();

                        atualizarBarraDeFuria();

                        atualizarTempoDano();

                        AtualizarDash();

                        desenhar();
                    }

                    /**
                     * @brief metodo que muda o booleano que dita se o jogador pode pular ou nao
                     */
                    void Jogador::podePular()
                    {
                        noChao = true;
                        qtdPulo = 0;
                    }

                    /**
                     *@brief metodo que faz o pulo do jogador.
                     */
                    void Jogador::pular()
                    {
                        if(!atacando && !levandoDano)
                        {
                            if(noChao || qtdPulo < QTD_PULO)
                            {
                                velocidade.y = -sqrt(2.0f * GRAVIDADE * TAMANHO_PULO);
                                noChao = false;
                                qtdPulo++;
                            }
                        }
                    }

                    /**
                     * @brief metodo que atualiza a animacao do jogador de acordo com seu estado atual.
                     */
                    void Jogador::atualizarAnimacao()
                    {
                        if(!emFuria)
                        {
                            if(morrendo){
                                animacao.atualizar(direcao, "MORRE");
                                tempoMorrer += pGrafico->getTempo();
                                if(tempoMorrer > tempoAnimacaoDeMorrer)
                                {
                                    podeRemover = true;
                                }
                            }
                            else if(entrandoEmFuria){
                                animacao.atualizar(direcao, "ENTRANDO_FURIA");
                                tempoEntrandoFuria += pGrafico->getTempo();
                                if(tempoEntrandoFuria > tempoAnimacaoFuria)
                                {
                                    emFuria = true;
                                    entrandoEmFuria = false;
                                    tempoEntrandoFuria = 0.0f;
                                }
                            }
                            else if(levandoDano)
                                animacao.atualizar(direcao,"TOMADANO");
                            else if(emDash)
                                animacao.atualizar(direcao, "DASH");
                            else if(!noChao && velocidade.y > 0.0f)
                                animacao.atualizar(direcao,"CAINDO");
                            else if(!noChao )
                                animacao.atualizar(direcao,"PULO");
                            else if(movendo)
                                animacao.atualizar(direcao,"CORRENDO");
                            else if(atacando && lancandoProjetil)
                                animacao.atualizar(direcao,"LANCANDO_PROJETIL");
                            else if(atacando)
                                animacao.atualizar(direcao,"ATACAR");
                            else
                                animacao.atualizar(direcao,"PARADO");
                        }
                        else{
                            if(morrendo){
                                animacao.atualizar(direcao, "MORRE-F");
                                tempoMorrer += pGrafico->getTempo();
                                if(tempoMorrer > (tempoAnimacaoDeMorrer/12) * 11)
                                {
                                    podeRemover = true;
                                }
                            }
                            else if(entrandoEmFuria){
                                animacao.atualizar(direcao, "ENTRANDO_FURIA");
                                tempoEntrandoFuria += pGrafico->getTempo();
                                if(tempoEntrandoFuria > tempoAnimacaoFuria)
                                {
                                    emFuria = true;
                                }
                            }
                            else if(levandoDano)
                                animacao.atualizar(direcao,"TOMADANO-F");
                            else if(emDash)
                                animacao.atualizar(direcao, "DASH-F");
                            else if(!noChao && velocidade.y > 0.0f)
                                animacao.atualizar(direcao,"CAINDO-F");
                            else if(!noChao )
                                animacao.atualizar(direcao,"PULO-F");
                            else if(movendo)
                                animacao.atualizar(direcao,"CORRENDO-F");
                            else if(atacando && lancandoProjetil)
                                animacao.atualizar(direcao,"LANCANDO_PROJETIL-F");
                            else if(atacando)
                                animacao.atualizar(direcao,"ATACAR-F");
                            else
                                animacao.atualizar(direcao,"PARADO-F");

                        }
                    }

                    /**
                     * @brief metodo que define a colisao do personagem com outras entidades  
                     * 
                     * @param outraEntidade entidade a ser analizada a colisao com o jogador
                     * @param ds distancia entre as duas entidades
                    */
                    void Jogador::colisao(Entidade* outraEntidade, sf::Vector2f ds)
                    {
                        if(outraEntidade->getID() == IDs::IDs::red_slime ||
                           outraEntidade->getID() == IDs::IDs::esqueleto)
                        {
                            Inimigo::Inimigo* inimigo = static_cast<Inimigo::Inimigo*>(outraEntidade);

                            inimigo->parar();
                            inimigo->atacar();
                        }
                        else if(outraEntidade->getID() == IDs::IDs::armaDoIimigo)
                        {
                            Arma::Arma* arma = static_cast<Arma::Arma*>(outraEntidade);
                            
                            if(emFuria)
                                tomarDano(arma->getDano()/2.0f);
                            else
                                tomarDano(arma->getDano());
                        }
                        else if(outraEntidade->getID() == IDs::IDs::projetil_inimigo)
                        {
                            Arma::Projetil* projetil = dynamic_cast<Arma::Projetil*>(outraEntidade);

                            if(emFuria)
                                tomarDano(projetil->getDano()/2.0f);
                            else
                                tomarDano(projetil->getDano());

                            projetil->setColidiu(true);
                        }

                    }

                    /**
                    * @brief metodo que inicializa e define a posicao da barra de vida do jogador
                    * alem disso define a textura que a barra tera jutamente com o seu tamanho.
                    */
                    void Jogador::inicializarBarraDeVida()
                    {
                        sf::Vector2f tuboDeVida = sf::Vector2f(BARRA_VIDA_JOGADOR_X, BARRA_VIDA_JOGADOR_Y);
                        tuboVida.setSize(tuboDeVida);
                        barraDeVida.setSize(tuboDeVida);
                        sf::Texture* texturaVida = new sf::Texture(); 
                        sf::Texture* texturaBarra = new sf::Texture();
                        texturaVida->loadFromFile("animations/Life/VidaJogador.png");
                        texturaBarra->loadFromFile("animations/Life/BarraVida.png");
                        barraDeVida.setTexture(texturaVida);
                        tuboVida.setTexture(texturaBarra);
                    }
                    
                    /**
                     * @brief metodo que inicializa a barra de stamina do jogador
                    */
                    void Jogador::inicializarBarraDeStamina()
                    {
                        sf::Vector2f stamina = sf::Vector2f(BARRA_VIDA_JOGADOR_X, BARRA_VIDA_JOGADOR_Y/2.0f);
                        barraStamina.setSize(stamina);
                        sf::Texture* texturaStamina = new sf::Texture(); 
                        texturaStamina->loadFromFile("animations/Life/BarraEnergia.png");
                        barraStamina.setTexture(texturaStamina);
                    }
                   
                    /**
                     * @brief metodo que inicializa a barra de furia do jogador
                    */
                    void Jogador::inicializarBarraDeFuria()
                    {
                        sf::Vector2f tamFuria = sf::Vector2f(furia, BARRA_VIDA_JOGADOR_Y/2.0f);
                        barraDeFuria.setSize(tamFuria);
                        sf::Texture* texturaFuria = new sf::Texture(); 
                        texturaFuria->loadFromFile("animations/Life/BarraEnergia.png");
                        barraDeFuria.setTexture(texturaFuria);
                        barraDeFuria.setFillColor(sf::Color::Magenta);

                    }
                    
                    /**
                     * @brief  metodo que atualiza a posicao da barra de vida do jogador
                     * assim como seu tamanho de acordo com o atributo vida do jogador. 
                    */
                    void Jogador::atualizarBarraDeVida()
                    {
                        
                        sf::Vector2f posJanela = pGrafico->getCamera().getCenter();
                        sf::Vector2f tamJanela = pGrafico->getTamJanela();

                        sf::Vector2f posBarra = sf::Vector2f(posJanela.x - tamJanela.x / 2.0f + 10.0f, 30.0f);
                        tuboVida.setPosition(posBarra);
                        barraDeVida.setSize(sf::Vector2f((BARRA_VIDA_JOGADOR_X - 40.0f) * (vida / vidaMaxima), BARRA_VIDA_JOGADOR_Y - 13.0f));
                        barraDeVida.setPosition(sf::Vector2f(posBarra.x + 7.0f, posBarra.y + tuboVida.getSize().y / 2.0f - barraDeVida.getSize().y / 2.0f));
                    }

                    /**
                     * @brief  metodo que atualiza a posicao da barra de stamina do jogador
                     * assim como seu tamanho de acordo com o atributo stamina do jogador. 
                    */
                    void Jogador::atualizarBarraDeStamina()
                    {
                        
                        atualizarRegeneracaoStamina();

                        sf::Vector2f posJanela = pGrafico->getCamera().getCenter();
                        sf::Vector2f tamJanela = pGrafico->getTamJanela();
                        
                        sf::Vector2f posBarra = sf::Vector2f(posJanela.x - tamJanela.x / 2.0f + 10.0f, 60.0f);
                        barraStamina.setSize(sf::Vector2f((BARRA_VIDA_JOGADOR_X - 30.0f) * (stamina / STAMINA_MAXIMA), BARRA_VIDA_JOGADOR_Y - 13.0f));
                        barraStamina.setPosition(sf::Vector2f(posBarra.x + 7.0f, posBarra.y - barraStamina.getSize().y / 2.0f));
                    }
                  
                    /**
                     * @brief  metodo que atualiza a posicao da barra de furia do jogador
                     * assim como seu tamanho de acordo com o atributo furia do jogador. 
                    */
                    void Jogador::atualizarBarraDeFuria()
                    {
                        if(emFuria)
                            consumirFuria();

                        sf::Vector2f posJanela = pGrafico->getCamera().getCenter();
                        sf::Vector2f tamJanela = pGrafico->getTamJanela();
                        
                        sf::Vector2f posBarra = sf::Vector2f(posJanela.x - tamJanela.x / 2.0f + 10.0f, 80.0f);
                        barraDeFuria.setSize(sf::Vector2f((BARRA_VIDA_JOGADOR_X - 30.0f) * (furia / FURIA_MAXIMA), BARRA_VIDA_JOGADOR_Y - 13.0f));
                        barraDeFuria.setPosition(sf::Vector2f(posBarra.x + 7.0f, posBarra.y - barraDeFuria.getSize().y / 2.0f));
                    }

                    /**
                    * @brief metodo responsavel por desenhar a vida, stamina e o personagem na tela 
                    * com a ajuda do metodo desenhar elemento.
                    */
                    void Jogador::desenhar()
                    {
                        pGrafico->desenhaElemento(corpo);
                        pGrafico->desenhaElemento(tuboVida);
                        pGrafico->desenhaElemento(barraDeVida);
                        pGrafico->desenhaElemento(barraStamina);
                        pGrafico->desenhaElemento(barraDeFuria);
                    }

                    /**
                     * @brief metodo  responsavel  por   atualizar   a  posicao 
                     * da arma do jogador dependendo de seu estado atual
                    */
                    void Jogador::atualizarArma()
                    {
                        if(atacando && !morrendo && !lancandoProjetil)
                        {
                            tempoAtaque += pGrafico->getTempo();
                            if(tempoAtaque > tempoAnimacaoAtaque)
                            {
                                arma->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                                tempoAtaque = 0.0f;
                                atacando = false;
                            }
                            else if(tempoAtaque > (tempoAnimacaoAtaque/3.0f)*2)
                            {
                                sf::Vector2f posArma = (direcao ? sf::Vector2f(pos.x - arma->getTam().x/2.0f,pos.y) : sf::Vector2f(pos.x + arma->getTam().x/2.0f,pos.y));
                                arma->setPos(posArma);
                            }
                            else if(tempoAtaque > tempoAnimacaoAtaque/3.0f)
                            {
                                somAtaque.play();
                            }
                        }
                    }
                    
                    /**
                     * @brief metodo  responsavel  por   atualizar   a  posicao 
                     * o prpjetil do jogador dependendo de seu estado atual
                    */
                    void Jogador::atualizarProjetil()
                    {
                        if(atacando && !morrendo && lancandoProjetil)
                        {
                            tempoAtaqueProjetil += pGrafico->getTempo();
                            if(tempoAtaqueProjetil > tempoAnimacaoProjetil)
                            {
                                atacando = false;
                                lancandoProjetil = false;
                                tempoAtaqueProjetil = 0.0f;
                            }
                            else if(tempoAtaqueProjetil > (tempoAnimacaoProjetil/4) * 3)
                            {
                                float x = direcao ? pos.x - 29.0f : pos.x + tam.x + 15.0f;
                                projetil->setPos(sf::Vector2f(x, (pos.y +  tam.y / 3.0f) + 10.0f));
                                projetil->setColidiu(false);
                                projetil->setVelocidade(sf::Vector2f(350.0f, 0.0f));
                                projetil->setDirecao(direcao);
                            }

                        }
                    }

                    void Jogador::lancarProjetil()
                    {
                        if(projetil->getColidiu())
                        {
                            parar();
                            consumirStamina((STAMINA_MAXIMA/5) * 2);
                            lancandoProjetil = true;
                            atacando = true;
                        }
                    }
                    
                    /**
                     * @brief metodo de acesso ao atributo noChao do jogador 
                     * 
                     * @return retorna o atributo noChao do jogador
                    */
                    const bool Jogador::getNoChao()
                    {
                        return noChao;
                    }

                    /**
                     * @brief metodo que muda o estado do observador do jogador
                    */
                    void Jogador::mudarEstadoListener(const bool ativo)
                    {
                        listenerJogador->mudarEstado(ativo);
                    }

                    /**
                     * @brief metodo que salva o estado de um objeto da classe jogador
                     * 
                     * @return retorna um json contendo as informacoes de um objeto jogador
                    */
                    nlohmann::ordered_json Jogador::salvar()
                    {
                        nlohmann::ordered_json json = salvarPersonagem();

                        json["noChao"] = noChao;
                        json["qtdPulo"] = qtdPulo;
                        json["tempoAtaque"] = tempoAtaque;
                        json["emDash"] = emDash;
                        json["stamina"] = stamina;
                        json["podeDash"] = podeDash;
                        json["tempoDash"] = tempoDash;
                        json["velDash"] = velDash;
                        json["furia"] = furia;
                        json["emFuria"] = emFuria;
                        json["entrandoEmFuria"] = entrandoEmFuria;
                        json["tempoEntrandoFuria"] = tempoEntrandoFuria;
                        json["lancandoProjetil"] = lancandoProjetil;
                        json["tempoAtaqueProjetil"] = tempoAtaqueProjetil;
                        json["tempoAnimacaoAtaque"] = tempoAnimacaoAtaque;
                        json["imagemAtual"] = animacao.getIMagemAtual();
                        json["tempoTotal"] = animacao.getTempoTotal();
                        json["quadroAtual"] = animacao.getQuadroAtual();

                        return json;
                    }

                    /**
                     * @brief metodo que inicializa os efeitos sonoros do jogador
                    */
                    void Jogador::inicializarSom()
                    {
                        if(!somAtaqueBuffer.loadFromFile(CAMINHO_SOM_ATAQUE))
                        {
                            std::cout<< "Jogador: não foi possivel carregar somAtaqueBuffer";
                            exit(1);
                        }
                        somAtaque.setBuffer(somAtaqueBuffer);
                    }

                    /**
                     * @brief metodo que atualiza a posicao do jogador
                    */
                    void Jogador::atualizarPosicao()
                    {
                        dt = pGrafico->getTempo();
                        sf::Vector2f ds(0.f,0.f);
                        
                        if(movendo && !morrendo && !levandoDano && !emDash)
                        {
                            ds.x = velocidade.x * dt;
                            if(direcao)
                                ds.x *= -1;
                        }

                        //efeito da gravidade
                        if(!emDash)
                        {
                            const float Vy = velocidade.y;
                            velocidade.y = velocidade.y + GRAVIDADE * dt;
                            ds.y = Vy * dt + (GRAVIDADE * dt * dt) / 2.0f;
                        }

                        setPos(sf::Vector2f(pos.x + ds.x, pos.y + ds.y ));

                        velocidade.x = velMax;
                    }

                    /**
                     * @brief metodo que atualiza o dash do jogador
                    */
                    void Jogador::AtualizarDash()
                    {
                        sf::Vector2f ds(0.0f, 0.0f);
                       
                        float dtAux = pGrafico->getTempo();

                        if(podeDash && !morrendo)
                        {
                            if(tempoDash <= tempoAnimacaoDash)
                            {
                                emDash = true;
                                tempoDash += dtAux;

                                ds.x = velDash * dtAux;
                                if(direcao)
                                    ds.x *= -1;

                                setPos(sf::Vector2f(pos.x + ds.x, pos.y));
                            }
                            else
                                emDash = false;
                        }
                    }

                    /**
                     * @brief muda o estado dos atributos relacionados ao dash
                    */
                    void Jogador::pararDash()
                    {
                        emDash = false;
                        podeDash = false;
                        tempoDash = 0.0f;
                    }

                    /**
                     * @brief muda o estado dos atributos relacionados ao dash
                    */
                    void Jogador::fazerDash()
                    {
                        if(tempoDash == 0.0f)
                        {
                            if(consumirStamina(STAMINA_MAXIMA/3.0f))
                                podeDash = true;
                        }
                    }
                    
                    /**
                     * @brief metodo que altera o atributo stamina
                     * 
                     * @param qtdUso quantidade de stamina a ser consumida
                     * 
                     * @return retorna um boleano dizendo se foi possivel consumir a quantidade de estamina recebida
                    */
                    bool Jogador::consumirStamina(float qtdUso)
                    {
                        if(stamina - qtdUso >= 0)
                        {
                            stamina -= qtdUso;
                            podeRegenerarStamina = false;
                            return true;
                        }
                        return false;
                    }
                   
                    /**
                     * @brief metodo que altera o atributo furia
                     * 
                     * @return retorna um boleano dizendo se foi possivel consumir a quantidade de furia
                    */
                    bool Jogador::consumirFuria()
                    {
                        if(furia - FURIA_CONSUMO >= 0)
                        {
                            furia -= FURIA_CONSUMO;
                            return true;
                        }
                        else
                        {
                            arma->setDano(dano);
                            projetil->setDano(dano);
                            emFuria = false; 
                            return false;
                        }
                    }

                    /**
                     * @brief metodo que atualiza os atributos relacionados a stamina
                    */
                    void Jogador::atualizarRegeneracaoStamina()
                    {
                        if(stamina != STAMINA_MAXIMA)
                        {
                            if(podeRegenerarStamina)
                            {
                                if(stamina + QTD_REGERENADA <= STAMINA_MAXIMA)
                                {
                                    stamina += QTD_REGERENADA;
                                }
                                else
                                {
                                    podeRegenerarStamina = false;
                                }
                            }
                            else
                            {
                                dt = pGrafico->getTempo();

                                tempoRegStamina += dt;

                                if( tempoRegStamina >= TEMPO_REGENERACAO_STAMINA)
                                {
                                    podeRegenerarStamina = true;
                                    tempoRegStamina = 0.0f;
                                }
                            }
                        }
                    }

                    void Jogador::procurarIteracoes()
                    {
                        Gerenciador::GerenciadorDeColisao* pColisao = pColisao->getGerenciadorDeColisao();
                        Entidade* ent =  pColisao->procurarEntidade(getPos(), sf::Vector2f(100.0f, 100.0f), IDs::IDs::npc);

                        if(ent != nullptr)
                        {
                            Npc::Npc* npc = static_cast<Npc::Npc*>(ent);
                            movendo = false;
                            atacando = false; 
                            levandoDano = false;
                            noChao = true;
                            atualizarAnimacao();
                            desenhar();
                            npc->iniciarDialogo();
                        }
                    }

                    void Jogador::setProjetil(Arma::Projetil* projetil)
                    {
                        this->projetil = projetil;
                        this->projetil->setDano(dano * 1.5f);
                    }

                    /**
                     * @brief metodo que auxilia na tomada de dano.
                     * 
                     * @param dano valor a ser descontado da vida do jogador.
                    */
                    void Jogador::tomarDano(const float dano)
                    {
                        if(!levandoDano)
                        {
                            levandoDano = true;
                            atacando = false;
                            entrandoEmFuria = false;
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
                            tempoAtaqueProjetil = 0.0f;
                            aumentarFuria(dano / 2.0f);
                        }
                    }

                    void Jogador::aumentarFuria(float qtdFuria)
                    {
                        if(furia + qtdFuria <= FURIA_MAXIMA)
                        {
                            furia += qtdFuria;
                        }
                    }

                    void Jogador::ativarFuria()
                    {
                        if(furia == FURIA_MAXIMA && !entrandoEmFuria && !morrendo)
                        {
                            arma->setDano(dano*2);
                            projetil->setDano(dano*2);
                            entrandoEmFuria = true;
                        }
                    }

            }
        }
    }
}
