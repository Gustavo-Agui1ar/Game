
#pragma once

#include <SFML/Graphics.hpp>
#include "../jogador/personagem.h"
#include "../jogador/jogador.h"
#include <iostream>

#define CAMINHO_TEXTURA_IDLE_INIMIGO "..\\Game\\animations\\enemy\\Skeleton_Spearman\\Idle.png"
#define CAMINHO_TEXTURA_WALK_INIMIGO "..\\Game\\animations\\enemy\\Skeleton_Spearman\\Walk.png"

namespace Game{

    namespace Entidade{

         namespace Personagem{

            namespace Inimigo{

                class Inimigo : public Personagem{

                protected:

                    Jogador::Jogador *jogador;

                    //atributos de ataque
                    const float tempoAnimacaoAtaque;
                    float tempoAtaque;
                    
                    //atributos de movimento
                    float tempoMover;
                    short mover;

                    //metodos de animacao
                    virtual void inicializaAnimacao() = 0;
                    virtual void atualizarAnimacao();

                    //metodos de movimento
                    void moveInimigo();

                    //metodos de ataque
                    virtual void atualizarAtaque();
                    
                    //metodos de vida
                    void inicializarBarraDeVida();

                public:

                    //construtor e destrutor
                    Inimigo(sf::Vector2f pos, sf::Vector2f tam, const float vel, Jogador::Jogador *jogador,const float tempoAnimacaoAtaque, IDs::IDs ID, const float tempoAnimacaoDeLevarDano, const float tempoAnimacaoDeMorrer, float dano, Item::Arma* arma);
                    ~Inimigo();

                    //metodos de movimento
                    void persegueJogador(sf::Vector2f posJogador, sf::Vector2f posInimigo);
                    void movimentoAleatorio();
                    
                    //metodo de colisao
                    void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.f,0.f)){}
                   
                    // metodos de atualizar inimigo
                    void atualizar();
                };
            }
        }
    }

}
