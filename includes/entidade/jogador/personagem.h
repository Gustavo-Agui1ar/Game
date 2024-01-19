
#pragma once

#include <SFML/Graphics.hpp>
#include "../includes/entidade/entidade.h"
#include "../includes/animador/animacao.h"
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

                Animador::Animacao animacao;

                //metodos de inicializacao

                virtual void inicializarBarraDeVida() = 0;
                
                //metodos de atuallizacao da classe

                virtual void atualizarAnimacao() = 0;
                virtual void atualizarBarraDeVida();

                //atributos relacionados a velocidade 

                sf::Vector2f velocidade;
                const float velMax;
              
                //atributos de locomocao
              
                bool movendo;
                bool direcao;
                float dt;

                //atributos de vida
                sf::RectangleShape barraDeVida;
                const float vidaMaxima;
                float vida;
                
                //  atributos de controle de tempo

                const float tempoAnimacaoDeLevarDano;
                const float tempoAnimacaoDeMorrer;
                float tempoMorrer;
                float tempoDano;
                
                // atributo relacionado a vida 
                
                bool morrendo;

                //atributos de ataque
                bool levandoDano;
                bool atacando;

                //atributos reacionados aoo dano 

                Arma::Arma* arma;
                float dano;

            public:

                //construtores e destrutores
                
                Personagem(const sf::Vector2f pos, const sf::Vector2f tam, const float vel,IDs::IDs ID,const float tempoAnimacaoDeLevarDano, const float tempoAnimacaoDeMorrer,const float dano);
                virtual ~Personagem();

                //metodos setters da classe
                
                void setVelMax(sf::Vector2f vel);
                void setArma(Arma::Arma* arma);
                
                //metodos de locomocao

                void andar(bool direcao);
                void parar();

                //metodos de atualizacao de atributos da classe

                virtual void atualizarTempoDano();
                virtual void atualizarPosicao();

                //metodos de ataque
              
                void tomarDano(const float dano);

                //metodos de ataque

                void pararAtaque();
                void atacar();

                //metodos que salvam os atributos de um objeto desta classe

                nlohmann::ordered_json salvarPersonagem();
                virtual nlohmann::ordered_json salvar() = 0;

                //getters daa classe
               
                sf::Vector2f getVelocidade();
                const bool getMorrer();
                const bool getDirecao();

                //metodos de animacao e visualizacao
              
                virtual void desenhar();
            };
        }
    }
}
