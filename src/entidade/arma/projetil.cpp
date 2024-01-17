
#include "../includes/entidade/arma/projetil.h"

namespace Game{

    namespace Entidade{

        namespace Arma{

            Projetil::Projetil( IDs::IDs ID):
            Arma(ID), colidiu(true),direcao(false),animcao(&corpo) velocidade(sf::Vector2f(0.0f, 0.0f))
            {
                setPos(sf::Vector2f(-1000.0f, -1000.0f));
                inicializarAnimacao();
            }

            Projetil::Projetil( nlohmann::ordered_json atributos):
            Arma(atributos["ID"].template get<IDs::IDs>())
            {
                try{
                    dano = atributos["dano"].template get<float>();
                    setPos(sf::Vector2f(atributos["pos"]["x"].template get<float>(), atributos["pos"]["y"].template get<float>()));
                    setTam(sf::Vector2f(atributos["tam"]["x"].template get<float>(), atributos["tam"]["y"].template get<float>()));
                    direcao = atributos["direcao"].template get<bool>();
                    colidiu = atributos["colidiu"].template get<bool>();

                    inicializarAnimacao();

                    animacao.setImgAtual(atributos["imagemAtual"].template get<std::string>());
                    animacao.setQuadroAtual(atributos["tempoTotal"].template get<unsigned int>());
                    animacao.setTempoTotal(atributos["tempoTotal"].template get<float>());

                    setVelocidade(sf::Vector2f(atributos["vel"]["x"].template get<float>(), atributos["vel"]["y"].template get<float>()));

                
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    podeRemover = true;
                }
            }

            Projetil::~Projetil()
            {

            }

            void Projetil::inicializarAnimacao()
            {
                if(getID() ==IDs::IDs::projetil_inimigo)
                {
                    animacao.addAnimacao("../animations/enemy/Skeleton_Archer/Arrow.png", "ATACA", 1, 10.0f, 2f, sf::Vector2f(5.0f, 5.0f), sf::Vector2f(tam.x / 2.0f, tam.y / 2.0f));
                }
                else
                {
                    animacao.addAnimacao("../animations/enemy/Player/Fire-ball.png", "ATACA", 4, 0.12f, sf::Vector2f(5.0f, 5.0f), sf::Vector2f(tam.x / 2.0f, tam.y / 2.0f));
                }
            }

            void Projetil::setVelocidade(sf::Vector2f velocidade)
            {
                this->velocidade = velocidade;
            }

            void Projetil::setColidiu(bool colidiu)
            {
                this->colidiu = colidiu;

                if(colidiu)
                {
                    setPos(sf::Vector2f(-1000.0f, -1000.0f));
                    setVelocidade(sf::Vector2f(0.0f, 0.0f));
                }
            }

            void Projetil::setDirecao(bool direcao)
            {
                this->direcao = direcao;
                velocidade = direcao ? sf::Vector2f(velocidade.x * -1, velocidade.y) : velocidade;
            }

            void Projetil::verificarSaiuTela()
            {
                sf::Vector2f centroTela = pGrafico->getCamera().getCenter();
                sf::Vector2f tamJanela = pGrafico->getTamJanela();

                if(pos.x < centroTela.x - tamJanela.x/2.0f || pos.x > centroTela.x + tamJanela.x/2.0f ||
                   pos.y < centroTela.y - tamJanela.y/2.0f || pos.y > centroTela.y + tamJanela.y/2.0f )
                {
                    setColidiu(true);
                }
            }

            void Projetil::atualizarPosicao()
            {
                const float dt = pGrafico->getTempo();
                sf::Vector2f posFinal(0.0f, 0.0f);

                posFinal.x = pos.x + velocidade.x * dt;

                setPos(posfinal);
            }

            void Projetil::atualizarAnimacao()
            {
                animacao.atualizar(direcao, "ATACA");
            }

            void Projetil::desenhar()
            {
                pGrafico->desenhaElemento(corpo);
            }

            nlohmann::ordered_json Projetil::salvar()
            {
                nlohmann::ordered_json json = salvarArma();

                json["direcao"] = direcao;
                json["velocidade"] = {{"x", velocidade.x}, {"y", velocidade.y}};
                json["colidiu"] = colidiu;
                json["imagemAtual"] = animacao.getIMagemAtual();
                json["tempoTotal"] = animacao.getTempoTotal();
                json["quadroAtual"] = animacao.getQuadroAtual();

                return json;
            }

            void Projetil::atualizar()
            {
                if(!colidiu)
                {
                    atualizarPosicao();
                    atualizarAnimacao();
                    verificarSaiuTela();

                    desenhar();
                }
            }

        }
    }
}