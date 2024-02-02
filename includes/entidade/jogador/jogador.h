
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../includes/entidade/arma/projetil.h"
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
#define CAMINHO_TEXTURA_ATTACK      "animations/Player/Attack.png"
#define CAMINHO_TEXTURA_IDLE        "animations/Player/Idle.png"
#define CAMINHO_TEXTURA_JUMP        "animations/Player/Jump.png"
#define CAMINHO_TEXTURA_DOWN        "animations/Player/Down.png"
#define CAMINHO_TEXTURA_DEAD        "animations/Player/Dead-test.png"
#define CAMINHO_TEXTURA_HIT         "animations/Player/Hit.png"
#define CAMINHO_TEXTURA_RUN         "animations/Player/Run.png"
#define CAMINHO_TEXTURA_DASH        "animations/Player/Dash.png"
#define CAMINHO_TEXTURA_PROJETIL    "animations/Player/Fireball.png"
#define CAMINHO_SOM_ATAQUE          "Sounds/Sword-Slash.wav"

#define CAMINHO_TEXTURA_ATTACK_FIRE "animations/Player/attack-fire.png"
#define CAMINHO_TEXTURA_IDLE_FIRE   "animations/Player/idle-fire.png"
#define CAMINHO_TEXTURA_JUMP_FIRE   "animations/Player/Jump-fire.png"
#define CAMINHO_TEXTURA_DOWN_FIRE   "animations/Player/Down-fire.png"
#define CAMINHO_TEXTURA_DEAD_FIRE   "animations/Player/Dead-fire.png"
#define CAMINHO_TEXTURA_HIT_FIRE    "animations/Player/Hit-fire.png"
#define CAMINHO_TEXTURA_RUN_FIRE    "animations/Player/Run-fire.png"
#define CAMINHO_TEXTURA_DASH_FIRE   "animations/Player/Dash-fire.png"
#define CAMINHO_TEXTURA_PROJETIL_FIRE "animations/Player/Fireball-fire.png"
#define CAMINHO_TEXTURA_FURIA "animations/Player/Furia.png"


#define JOGADOR_ANIMACAO_DE_MORTE  1.8f
#define JOGADOR_TEMPO_LEVAR_DANO 0.5f
#define JOGADOR_TEMPO_ATE_FURIA 1.2f
#define JOGADOR_TEMPO_DANO 0.6f
#define JOGADOR_TEMPO_PROJEIL 0.9f
#define DANO_JOGADOR 20.0f
#define STAMINA_MAXIMA 100.0f
#define FURIA_MAXIMA 100.0f
#define FURIA_CONSUMO 0.01f
#define TEMPO_REGENERACAO_STAMINA 1.5f
#define QTD_REGERENADA 0.05f

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
                    void inicializarBarraDeFuria();
                    void inicializarBarraDeVida();
                    void inicializarAnimacao();
                    void inicializarSom();
                    
                    //metodos de atualizacao
                    
                    void atualizarRegeneracaoStamina();
                    void atualizarBarraDeStamina();
                    void atualizarBarraDeFuria();
                    void atualizarBarraDeVida();
                    void atualizarAnimacao();
                    void atualizarPosicao();
                    void AtualizarDash();
                    void atualizar();

                    //atributo de vida

                    sf::RectangleShape tuboVida;
                   
                    //atributos de vizualizacao stamina

                    sf::RectangleShape barraStamina;
                    
                    //atributos de ataque

                    const float tempoAnimacaoAtaque;
                    float tempoAtaque;
                    

                    //atributos de stamina

                    bool podeRegenerarStamina;
                    float tempoRegStamina;                
                    float stamina;

                    sf::RectangleShape barraDeFuria;
                    float furia;
                    bool emFuria;
                    bool entrandoEmFuria;

                    const float tempoAnimacaoFuria;
                    float tempoEntrandoFuria;


                    Listener::ListenerJogador* listenerJogador;
                    
                    //atributos efeito sonoro

                    sf::Sound somAtaque;
                    sf::SoundBuffer somAtaqueBuffer;

                    //metodo de utilizacao stamina

                    bool consumirStamina(float qtdUso);
                    bool consumirFuria();

                    void tomarDano(const float dano);
                   
                    Arma::Projetil* projetil;
                    bool lancandoProjetil;
                    const float tempoAnimacaoProjetil;
                    float tempoAtaqueProjetil;

                public:
                    
                    //construtores/destrutor
                    
                    Jogador(const sf::Vector2f pos, Arma::Arma* arma = nullptr, Arma::Projetil* projetil = nullptr);
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
                    void atualizarProjetil();

                    //metodos que alteram os atributos relacionados ao dash 

                    void fazerDash();
                    void pararDash();

                    //metodos de vizualizacao na tela
                    
                    void desenhar();

                    void procurarIteracoes();

                    void setProjetil(Arma::Projetil* projetil);

                    void aumentarFuria(float qtdFuria);
                    void lancarProjetil();

                    void ativarFuria();

                };
            }
        }
    }

}
