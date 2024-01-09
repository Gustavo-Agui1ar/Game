
#pragma once

#include <SFML/Graphics.hpp>
#include "../jogador/personagem.h"
#include "../jogador/jogador.h"
#include <iostream>

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


                    //atributos de efeito sonoro da classe

                    sf::SoundBuffer somDeDanoBuffer;
                    sf::Sound somDeDano;

                    //metodo que inicializa aos atriibutos de efeito sonoro

                    virtual void inicializarSom(){};

                    //metodos de animacao
                 
                    virtual void inicializaAnimacao() = 0;
                    virtual void atualizarAnimacao();

                    //metodos de movimento
                
                    void moveInimigo();

                    //metodos de ataque
                   
                    virtual void atualizarAtaque();
                    void atualizarTempoDano();

                    //metodo responsavel por salvar o estado de um objeto desta classe

                    nlohmann::ordered_json salvar();
                    
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
