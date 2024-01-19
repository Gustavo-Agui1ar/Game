#pragma once

#include "inimigo.h"
#include "../includes/entidade/arma/projetil.h"

#define ARQUEIRO_TEMPO_ANIMACAO_DE_MORTE 1.25f
#define TAM_ARQUEIRO_X 30.0f
#define TAM_ARQUEIRO_Y 60.0f
#define VEL_ARQUEIRO 50.0f
#define ARQUEIRO_TEMPO_LEVAR_DANO 0.6f
#define ARQUEIRO_TEMPO_DE_ATAQUE 1.5f
#define DANO_ARQUEIRO 10.0F

#define SOM_DE_DANO_ARQUEIRO "Sounds/Skeleton-Sound-Effect.wav"


namespace Game{

    namespace Entidade{

        namespace Personagem{

            namespace  Inimigo{

                class Arqueiro : public Inimigo{
                
                private:

                    //metodos de inicializacao
                  
                    void inicializaAnimacao();
                    void inicializarSom();
                  
                    //metodos de atualizacao

                    void moveInimigo();
                    void atualizarAnimacao();
                    void atualizarAtaque();
                    void fugir(sf::Vector2f posJogador, sf::Vector2f posInimigo);
                
                public:

                    //construtor e destrutor
                  
                    Arqueiro(sf::Vector2f pos, Jogador::Jogador *jogador, Arma::Arma* arma = nullptr);
                    Arqueiro(nlohmann::ordered_json atributos, Jogador::Jogador *jogador);
                    ~Arqueiro();
                };
            }
        }
    }
}
