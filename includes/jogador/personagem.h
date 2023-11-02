
#pragma once

#include <SFML/Graphics.hpp>
#include "../entidade/entidade.h"
#include "../animador/animacao.h"
#include "../arma/arma.h"


#define GRAVIDADE 1200.0f

#define BARRA_VIDA_X 60.0f
#define BARRA_VIDA_Y 6.0f

namespace Game {

    namespace Entidade{

        namespace Personagem {

           class Personagem : public Entidade {

            protected:

                //atributos de animacao e visualizacao
                animador::Animacao animacao;

                //metodos de vida
                virtual void inicializarBarraDeVida() = 0;
                virtual void atualizarAnimacao() = 0;
                virtual void atualizarBarraDeVida();

                //atributos de locomocao
                sf::Vector2f velocidade;
                const float velMax;
                bool movendo;
                bool direcao;
                float dt;

                //atributos de vida
                const float tempoAnimacaoDeLevarDano;
                const float tempoAnimacaoDeMorrer;
                sf::RectangleShape barraDeVida;
                const float vidaMaxima;
                float tempoMorrer;
                float tempoDano;
                bool morrendo;
                float vida;

                //atributos de ataque
                bool levandoDano;
                Item::Arma* arma;
                bool atacando;
                float dano;

            public:

                //construtores e destrutores
                Personagem(const sf::Vector2f pos, const sf::Vector2f tam, const float vel,IDs::IDs ID,const float tempoAnimacaoDeLevarDano, const float tempoAnimacaoDeMorrer,const float dano);
                virtual ~Personagem();

                //metodos de locomocao
                void setVelMax(sf::Vector2f vel);
                sf::Vector2f getVelocidade();
                void andar(bool direcao);
                void atualizarPosicao();
                void parar();


                //metodos de ataque
                void tomarDano(const float dano);
                void setArma(Item::Arma* arma);
                void atualizarTempoDano();
                void pararAtaque();
                void atacar();

                //metodos de vida
                const bool getMorrer();

                //metodos de animacao e visualizacao
                virtual void desenhar();
            };
        }
    }
}
