
#pragma once

#include "../includes/entidade/Player/Character.h"

#define TAM_NPC_GENERICO_X 15.f
#define TAM_NPC_GENERICO_Y 30.f

namespace Game{

    namespace Gerenciador{

        class GerenciadorDeEstado;
    }

    namespace Entidade::Character::Npc{
        class Npc : public Character {
            
            protected:

                static Gerenciador::GerenciadorDeEstado* pEstado;
                const char* caminhoDialogo;

                const IDs::IDs IDpersonagem;

                void bootLifeBar() override{/**/}
                void inicializarAnimacao();

            public:
                
                Npc(sf::Vector2f pos, const IDs::IDs IDpersonagem, const char* caminhoDialogo = nullptr);
                ~Npc() override;

                void updateAnimation() override;
                void updatePosition() override;

                nlohmann::ordered_json salvar() override;
                void iniciarDialogo();
                const char* getCaminhoDialogo();
                void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.f,0.f)) override;
                void draw() override;
                void update() override;
        };
}
}