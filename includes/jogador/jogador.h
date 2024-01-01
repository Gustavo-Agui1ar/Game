
#pragma once

#include <SFML/Graphics.hpp>

#include "personagem.h"
#include <math.h>

#define BARRA_VIDA_JOGADOR_X 350.0f
#define BARRA_VIDA_JOGADOR_Y 20.0f

#define TAM_JOGADOR_X 30.0f
#define TAM_JOGADOR_Y 60.0f

#define VELOCIDADE_JOGADOR_X 250.0f

#define QTD_PULO 2

#define TAMANHO_PULO 120.f
#define CAMINHO_TEXTURA_ATTACK "animations/Player/Attack.png"
#define CAMINHO_TEXTURA_IDLE   "animations/Player/Idle.png"
#define CAMINHO_TEXTURA_JUMP   "animations/Player/Jump.png"
#define CAMINHO_TEXTURA_DOWN   "animations/Player/Down.png"
#define CAMINHO_TEXTURA_DEAD   "animations/Player/Dead.png"
#define CAMINHO_TEXTURA_HIT    "animations/Player/Hit.png"
#define CAMINHO_TEXTURA_RUN    "animations/Player/Run.png"

#define JOGADOR_ANIMACAO_DE_MORTE  0.9f
#define JOGADOR_TEMPO_LEVAR_DANO 0.5f
#define DANO_JOGADOR 20.0f

namespace Game {

    namespace Listener{
        class ListenerJogador;
    }

    namespace Entidade{

         namespace Personagem{

            namespace Jogador {

                class Jogador : public Personagem {
                private:

                    //atributo de locomocao
                    bool noChao;
                    int qtdPulo;
                    
                    //metodos de atualizacao 
                    void inicializarAnimacao();
                    void atualizarAnimacao();
                    void atualizar();

                    //atributo de vida
                    sf::RectangleShape tuboVida;

                    //metodos de vida
                    void inicializarBarraDeVida();
                    void atualizarBarraDeVida();

                    Listener::ListenerJogador* listenerJogador;


                public:
                    //construtores/destrutor
                    Jogador(const sf::Vector2f pos, Item::Arma* arma = nullptr);
                    Jogador(nlohmann::ordered_json atributos);
                    ~Jogador();
                   
                    void mudarEstadoListener(const bool ativo);
                    //metodo de colisao
                    void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.f,0.f));
                    
                    //metodos de locomocao
                    const bool getNoChao();
                    void podePular();
                    void pular();

                    nlohmann::ordered_json salvar();

                    //metodos de ataque
                    void atualizarArma();

                    //metodos de vizualizacao na tela
                    void desenhar();

                };
            }
        }
    }

}
