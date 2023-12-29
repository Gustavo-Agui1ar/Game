
#pragma once

#include "inimigo.h"

#define ESQUELETO_TEMPO_ANIMACAO_DE_MORTE 1.25f
#define TAM_ESQUELETO_X 30.0f
#define TAM_ESQUELETO_Y 60.0f
#define VEL_ESQUELETO 50.0f
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
                    Esqueleto(sf::Vector2f pos, Jogador::Jogador *jogador, Item::Arma* arma = nullptr);
                    Esqueleto(nlohmann::ordered_json atributos, Jogador::Jogador *jogador);
                    ~Esqueleto();
                };
            }
        }
    }
}
