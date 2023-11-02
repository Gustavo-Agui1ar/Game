
#pragma once

#include <SFML/Graphics.hpp>

#include "personagem.h"
#include <math.h>

#define BARRA_VIDA_JOGADOR_X 350.0f
#define BARRA_VIDA_JOGADOR_Y 20.0f

#define TAMANHO_PULO 120.f
#define CAMINHO_TEXTURA_IDLE "..\\Game\\animations\\Player\\Idle.png"
#define CAMINHO_TEXTURA_RUN "..\\Game\\animations\\Player\\run.png"
#define CAMINHO_TEXTURA_JUMP "..\\Game\\animations\\Player\\jump.png"
#define CAMINHO_TEXTURA_DOWN "..\\Game\\animations\\Player\\teste-cair.png"
#define CAMINHO_TEXTURA_ATTACK "..\\Game\\animations\\Player\\attack_1.png"
#define CAMINHO_TEXTURA_DEAD "..\\Game\\animations\\Player\\Dead.png"
#define CAMINHO_TEXTURA_HIT "..\\Game\\animations\\Player\\Hurt.png"

#define JOGADOR_ANIMACAO_DE_MORTE  0.9f
#define JOGADOR_TEMPO_LEVAR_DANO 0.5f
#define DANO_JOGADOR 100.0f

namespace Game {

    namespace Entidade{

         namespace Personagem{

            namespace Jogador {

                class Jogador : public Personagem {
                private:

                    //atributo de locomocao
                    bool noChao;
                    
                    //metodos de atualizacao 
                    void atualizarAnimacao();
                    void atualizar();

                    //atributo de vida
                    sf::RectangleShape tuboVida;

                    //metodos de vida
                    void inicializarBarraDeVida();
                    void atualizarBarraDeVida();

                public:
                    //construtores/destrutor
                    Jogador(const sf::Vector2f pos, const sf::Vector2f tam, const float vel, Item::Arma* arma = nullptr);
                    ~Jogador();
                   
                    //metodo de colisao
                    void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.f,0.f));
                    
                    //metodos de locomocao
                    void podePular();
                    void pular();
                    
                    //metodos de ataque
                    void atualizarArma();

                    //metodos de vizualizacao na tela
                    void desenhar();

                };
            }
        }
    }

}
