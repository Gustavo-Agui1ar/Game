
#pragma once

#include "inimigo.h"

#define SLIME_TEMPO_ANIMACAO_DE_MORTE 0.5F
#define SLIME_TEMPO_DE_TOMAR_DANO 0.6F
#define SLIME_TEMPO_DE_ATAQUE 0.8F
#define VEL_SLIME 50.0f
#define TAM_SLIME_X 30.0f
#define TAM_SLIME_Y 60.0f
#define DANO_SLIME 5.0F

namespace Game{

    namespace Entidade{

        namespace Personagem{

            namespace  Inimigo{

                class Slime : public Inimigo{
                private:

                    //metodos de inicializacao
                    void inicializaAnimacao();
                    void atualizarAnimacao();
                    void atualizarAtaque();

                public:

                    //construtor e destrutor
                    Slime(sf::Vector2f pos, Jogador::Jogador *jogador, Item::Arma* arma = nullptr);
                    Slime(nlohmann::ordered_json atributos, Jogador::Jogador *jogador);
                    ~Slime();
                };
            }
        }
    }
}

