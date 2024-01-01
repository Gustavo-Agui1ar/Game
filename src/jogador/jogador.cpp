#include "../includes/listeners/listenerJogador.h"
#include "../../includes/inimigo/esqueleto.h"
#include "../../includes/jogador/jogador.h"
#include "../../includes/inimigo/slime.h"


namespace Game{

    namespace Entidade{

        namespace Personagem{

            namespace Jogador{

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
                     * construtora da classe Jogador
                     *
                     * parametros:
                     *
                     * pos: atributo nescessario para inicializar a classe Entidade
                     * tam: atributo nescessario para inicializar a classe Entidade
                     * vel: atributo nescessario para inicializar a classe Personagem
                     * ID jogador : atributo de identifica��o da classe jogador.
                     */

                    Jogador::Jogador(const sf::Vector2f pos,  Item::Arma* arma):
                    Personagem(pos,sf::Vector2f(TAM_JOGADOR_X,TAM_JOGADOR_Y), VELOCIDADE_JOGADOR_X, IDs::IDs::jogador, JOGADOR_TEMPO_LEVAR_DANO, JOGADOR_ANIMACAO_DE_MORTE, DANO_JOGADOR),noChao(false),
                    qtdPulo(0), listenerJogador(new Listener::ListenerJogador(this))
                    {
                      
                       inicializarAnimacao();

                       inicializarBarraDeVida();

                       if(arma != nullptr)
                       {
                          setArma(arma);
                       }
                    }

                    Jogador::Jogador(nlohmann::ordered_json atributos):
                    Personagem(pos,sf::Vector2f(TAM_JOGADOR_X,TAM_JOGADOR_Y), VELOCIDADE_JOGADOR_X, IDs::IDs::jogador, JOGADOR_TEMPO_LEVAR_DANO, JOGADOR_ANIMACAO_DE_MORTE, DANO_JOGADOR),
                    listenerJogador(new Listener::ListenerJogador(this))
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
                            noChao = atributos["noChao"].template get<bool>();
                            qtdPulo = atributos["qtdPulo"].template get<int>();

                            inicializarAnimacao();
                            inicializarBarraDeVida();

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

                    void Jogador::inicializarAnimacao()
                    {
                        const sf::Vector2f origemT = sf::Vector2f((tam.x/2),(tam.y/5));
                        animacao.addAnimacao(CAMINHO_TEXTURA_IDLE,"PARADO",8,0.2,sf::Vector2f{2, 1.1}, sf::Vector2f(origemT.x, origemT.y/3));
                        animacao.addAnimacao(CAMINHO_TEXTURA_JUMP,"PULO",3,0.16,sf::Vector2f{2.5, 1.25}, origemT);
                        animacao.addAnimacao(CAMINHO_TEXTURA_DOWN,"CAINDO",3,0.12,sf::Vector2f{2.5, 1.25}, origemT);
                        animacao.addAnimacao(CAMINHO_TEXTURA_RUN,"CORRENDO",8,0.12,sf::Vector2f{2.5, 1.25}, origemT);
                        animacao.addAnimacao(CAMINHO_TEXTURA_ATTACK,"ATACAR",4,0.15,sf::Vector2f{2.5, 1.25},  sf::Vector2f(origemT.x, origemT.y/2));
                        animacao.addAnimacao(CAMINHO_TEXTURA_DEAD,"MORRE",6,0.1,sf::Vector2f{2.5, 1.25}, origemT);
                        animacao.addAnimacao(CAMINHO_TEXTURA_HIT,"TOMADANO",3,0.15,sf::Vector2f{2.2, 1.1}, sf::Vector2f(origemT.x, origemT.y/3));

                    }

                    /**
                     * metodo  que atualiza a pois��o,aniimacao,
                     * barra de vida e camera que seque o jogador
                     */

                    void Jogador::atualizar()
                    {
                        atualizarPosicao();

                        atualizarArma();

                        pGrafico->atualizarCamera(getPos());

                        atualizarAnimacao();
                        
                        atualizarBarraDeVida();
                    }

                    /**
                     * metodo que muda o booleano que dita se o jogador pode pular ou n�o
                     */

                    void Jogador::podePular()
                    {
                        noChao = true;
                        qtdPulo = 0;
                    }

                    /**
                     *metodo que faz o pulo do jogador.
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
                     * metodo que atulaiza a anima��o do jogador de acordo com seu estado atual.
                     */

                    void Jogador::atualizarAnimacao()
                    {
                        if(morrendo){
                            animacao.atualizar(direcao, "MORRE");
                            tempoMorrer += dt;
                            if(tempoMorrer > tempoAnimacaoDeMorrer)
                            {
                                podeRemover = true;
                             }
                        }
                        else if(levandoDano)
                            animacao.atualizar(direcao,"TOMADANO");
                        else if(!noChao && velocidade.y > 0.0f)
                            animacao.atualizar(direcao,"CAINDO");
                        else if(!noChao )
                            animacao.atualizar(direcao,"PULO");
                        else if(movendo)
                            animacao.atualizar(direcao,"CORRENDO");
                        else if(atacando)
                             animacao.atualizar(direcao,"ATACAR");
                        else
                            animacao.atualizar(direcao,"PARADO");
                    }

                    /**
                     * metodo que define a colisao do personnagem com outras entidades  
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
                            Item::Arma* arma = static_cast<Item::Arma*>(outraEntidade);
                            tomarDano(arma->getDano());
                        }

                    }

                    /**
                    * metodo que inicializa e define a posicao da barra de vida do jogador
                    * alem disso define a textura que a barra tera jutamente com o seu tamanho.
                    */
                   
                    void Jogador::inicializarBarraDeVida()
                    {
                        sf::Vector2f tuboDeVida = sf::Vector2f(BARRA_VIDA_JOGADOR_X, BARRA_VIDA_JOGADOR_Y);
                        tuboVida.setSize(tuboDeVida);
                        barraDeVida.setSize(tuboDeVida);
                        sf::Texture* texturaVida = new sf::Texture(); 
                        sf::Texture* texturaBarra = new sf::Texture();
                        texturaVida->loadFromFile("..\\Game\\animations\\Life\\VidaJogador.png");
                        texturaBarra->loadFromFile("..\\Game\\animations\\Life\\BarraVida.png");
                        barraDeVida.setTexture(texturaVida);
                        tuboVida.setTexture(texturaBarra);
                    }
                    
                    /**
                     * metodo que atualiza a posicaoda barra de vida do jogador
                     * tanto atualizando a sua posicao como seu tamanho de acordo
                     * com o atributo vida do jogador. 
                    */

                    void Jogador::atualizarBarraDeVida(){
                        sf::Vector2f posJanela = pGrafico->getCamera().getCenter();
                        sf::Vector2f tamJanela = pGrafico->getTamJanela();
                        sf::Vector2f posBarra = sf::Vector2f(posJanela.x - tamJanela.x / 2.0f + 10.0f, 30.0f);
                        tuboVida.setPosition(posBarra);
                        barraDeVida.setSize(sf::Vector2f((BARRA_VIDA_JOGADOR_X - 40.0f) * (vida / vidaMaxima), BARRA_VIDA_JOGADOR_Y - 13.0f));
                        barraDeVida.setPosition(sf::Vector2f(posBarra.x + 7.0f, posBarra.y + tuboVida.getSize().y / 2.0f - barraDeVida.getSize().y / 2.0f));
                    }

                    /**
                    * metodo responsavel por desenhar a vida e o personagem na tela 
                    * com a ajuda do metodo desenhar elemento.
                    */
                    void Jogador::desenhar()
                    {
                        pGrafico->desenhaElemento(corpo);
                        pGrafico->desenhaElemento(tuboVida);
                        pGrafico->desenhaElemento(barraDeVida);
                    }

                    /**
                     * metodo  responsavel  por   atualizar   a  posicao 
                     * da arma do jogador dependendo de seu estado atual
                    */

                    void Jogador::atualizarArma()
                    {
                        if(atacando)
                        {
                            sf::Vector2f tamEspada = arma->getTam();
                            sf::Vector2f posEspada = (direcao ? sf::Vector2f(pos.x - tamEspada.x, pos.y) : sf::Vector2f(pos.x + tamEspada.x, pos.y));
                            arma->setPos(posEspada);
                        }
                        else
                        {
                            arma->setPos(sf::Vector2f(-1000.0f,-1000.f));
                        }
                    }

                    const bool Jogador::getNoChao()
                    {
                        return noChao;
                    }

                    void Jogador::mudarEstadoListener(const bool ativo)
                    {
                        listenerJogador->mudarEstado(ativo);
                    }

                    nlohmann::ordered_json Jogador::salvar()
                    {
                        nlohmann::ordered_json json = salvarPersonagem();

                        json["noChao"] = noChao;
                        json["qtdPulo"] = qtdPulo;
                        json["imagemAtual"] = animacao.getIMagemAtual();
                        json["tempoTotal"] = animacao.getTempoTotal();
                        json["quadroAtual"] = animacao.getQuadroAtual();

                        return json;
                    }

            }
        }
    }
}
