
#pragma once

#include "inimigo.h"

#define ESQUELETO_TEMPO_ANIMACAO_DE_MORTE 1.25f
#define ESQUELETO_TEMPO_LEVAR_DANO 0.6f
#define ESQUELETO_TEMPO_DE_ATAQUE 1.0f
#define DANO_ESQUELETO 10.0F


namespace Game{

    namespace Entidade{

        namespace Personagem{

            namespace  Inimigo{

                class Esqueleto : public Inimigo{
                private:

                    //metodos de inicializacao
                    void inicializaAnimacao();
                    void atualizarAnimacao();
                    void atualizarAtaque();

                public:

                    //construtor e destrutor
                    Esqueleto(sf::Vector2f pos, sf::Vector2f tam, const float vel, Jogador::Jogador *jogador, Item::Arma* arma = nullptr);
                    ~Esqueleto();
                };
            }
        }
    }
}
