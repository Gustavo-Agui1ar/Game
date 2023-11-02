
#pragma once

#include "inimigo.h"

#define SLIME_TEMPO_ANIMACAO_DE_MORTE 0.5F
#define SLIME_TEMPO_DE_TOMAR_DANO 0.6F
#define SLIME_TEMPO_DE_ATAQUE 0.8F
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
                    Slime(sf::Vector2f pos, sf::Vector2f tam, const float vel, Jogador::Jogador *jogador, Item::Arma* arma = nullptr);
                    ~Slime();
                };
            }
        }
    }
}

