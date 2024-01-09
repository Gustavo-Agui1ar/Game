
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "personagem.h"
#include <math.h>

#define BARRA_VIDA_JOGADOR_X 350.0f
#define BARRA_VIDA_JOGADOR_Y 20.0f

#define TAM_JOGADOR_X 30.0f
#define TAM_JOGADOR_Y 60.0f

#define VELOCIDADE_JOGADOR_X 250.0f
#define VELOCIDADE_DASH_JOGADOR_X 350.0f
#define TEMPO_DASH 0.48f

#define QTD_PULO 2

#define TAMANHO_PULO 120.f
#define CAMINHO_TEXTURA_ATTACK "animations/Player/Attack.png"
#define CAMINHO_TEXTURA_IDLE   "animations/Player/Idle.png"
#define CAMINHO_TEXTURA_JUMP   "animations/Player/Jump.png"
#define CAMINHO_TEXTURA_DOWN   "animations/Player/Down.png"
#define CAMINHO_TEXTURA_DEAD   "animations/Player/Dead-test.png"
#define CAMINHO_TEXTURA_HIT    "animations/Player/Hit.png"
#define CAMINHO_TEXTURA_RUN    "animations/Player/Run.png"
#define CAMINHO_TEXTURA_DASH   "animations/Player/Dash.png"
#define CAMINHO_SOM_ATAQUE     "Sounds/Sword-Slash.wav"

#define JOGADOR_ANIMACAO_DE_MORTE  1.8f
#define JOGADOR_TEMPO_LEVAR_DANO 0.5f
#define JOGADOR_TEMPO_DANO 0.6f
#define DANO_JOGADOR 20.0f
#define STAMINA_MAXIMA 100.0f
#define TEMPO_REGENERACAO_STAMINA 1.5f
#define QTD_REGERENADA 0.1f

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

                    //atributos de dash

                    const float tempoAnimacaoDash;
                    const float velDash;
                    float tempoDash;
                    bool podeDash;
                    bool emDash;

                    //metodos de inicializacao

                    void inicializarBarraDeStamina();
                    void inicializarBarraDeVida();
                    void inicializarAnimacao();
                    void inicializarSom();
                    
                    //metodos de atualizacao
                    
                    void atualizarRegeneracaoStamina();
                    void atualizarBarraDeStamina();
                    void atualizarBarraDeVida();
                    void atualizarAnimacao();
                    void atualizarPosicao();
                    void AtualizarDash();
                    void atualizar();

                    //atributo de vida

                    sf::RectangleShape tuboVida;
                   
                    //atributos de vizualizacao stamina

                    sf::RectangleShape barraStamina;
                    sf::RectangleShape tuboStamina;
                    
                    //atributos de ataque

                    const float tempoAnimacaoAtaque;
                    float tempoAtaque;
                    

                    //atributos de stamina

                    bool podeRegenerarStamina;
                    float tempoRegStamina;                
                    float stamina;


                    Listener::ListenerJogador* listenerJogador;
                    
                    //atributos efeito sonoro

                    sf::Sound somAtaque;
                    sf::SoundBuffer somAtaqueBuffer;

                    //metodo de utilizacao stamina

                    bool usarStamina(float qtdUso);


                public:
                    
                    //construtores/destrutor
                    
                    Jogador(const sf::Vector2f pos, Item::Arma* arma = nullptr);
                    Jogador(nlohmann::ordered_json atributos);
                    ~Jogador();
                    
                    //metodo quer altera  o estado do observador

                    void mudarEstadoListener(const bool ativo);
                  
                    //metodo de colisao
                  
                    void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.f,0.f));
                    
                    //metodos de acesso ao atributo noChao

                    const bool getNoChao();
                   
                    //metodos usados para a mecanica de pulo

                    void podePular();
                    void pular();

                    //metodo que salva os atributos de um objeto desta classe

                    nlohmann::ordered_json salvar();

                    //metodos de ataque

                    void atualizarArma();

                    //metodos que alteram os atributos relacionados ao dash 

                    void fazerDash();
                    void pararDash();

                    //metodos de vizualizacao na tela
                    
                    void desenhar();

                };
            }
        }
    }

}
