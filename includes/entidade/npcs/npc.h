
#pragma once

#include "../includes/entidade/jogador/personagem.h"

#define TAM_NPC_GENERICO_X 15.f
#define TAM_NPC_GENERICO_Y 30.f

namespace Game{

    namespace Gerenciador{

        class GerenciadorDeEstado;
    }

    namespace Entidade{

        namespace Personagem{
            
            namespace Npc{

                class Npc : public Personagem {
                    
                    protected:

                        static Gerenciador::GerenciadorDeEstado* pEstado;
                        const char* caminhoDialogo;

                        const IDs::IDs IDpersonagem;

                        void inicializarBarraDeVida(){}
                        void inicializarAnimacao();

                    public:
                        
                        Npc(sf::Vector2f pos, const IDs::IDs IDpersonagem, const char* caminhoDialogo = nullptr);
                        ~Npc();

                        virtual void atualizarAnimacao();
                        virtual void atualizarPosicao();

                        nlohmann::ordered_json salvar();
                        void iniciarDialogo();
                        const char* getCaminhoDialogo();
                        void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.f,0.f));
                        void desenhar();
                        void atualizar();
                };
            }
        }
    }
}