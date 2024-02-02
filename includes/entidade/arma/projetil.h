
#pragma once

#include "arma.h"
#include "../includes/animador/animacao.h"

#define TAMANHO_PROJETIL 25.0f
#define TAMANHO_PROJETIL_JOGADOR 8.0f

namespace Game{

    namespace Entidade{
        
        namespace Arma{

            class Projetil : public Arma {

                private:

                    bool direcao;
                    bool colidiu;

                    sf::Vector2f velocidade;
                    Animador::Animacao animacao;

                    void atualizarAnimacao();
                    void verificarSaiuTela();
                    void atualizarPosicao();

                public:

                    Projetil( IDs::IDs ID);
                    Projetil( nlohmann::ordered_json atributos);
                    ~Projetil();

                    void inicializarAnimacao();
                    void setDirecao(bool direcao);
                    void setVelocidade(sf::Vector2f velocidade);
                    void setColidiu(bool colidiu);
                    const bool getColidiu();

                    nlohmann::ordered_json salvar();

                    void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f));

                    void desenhar();
                    void atualizar();
            };
        } 
    }
}