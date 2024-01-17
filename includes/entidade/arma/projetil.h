
#pragma once

#include "arma.h"
#include "../includes/animador/animacao.h"

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
                    void atualiarPosicao();

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

                    void desenhar();
                    void atualizar();
            };
        } 
    }
}