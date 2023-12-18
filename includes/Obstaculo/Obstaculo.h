
#pragma once

#include "../jogador/jogador.h"
#include "../inimigo/inimigo.h"
#include "../entidade/entidade.h"
#include "../animador/animacao.h"

#define CAMINHO_TEXTURA_PLATAFORMA_CAVERNA "..\\Game\\animations\\platform\\Platform-cave.png"
#define CAMINHO_TEXTURA_PLATAFORMA_FOREST "..\\Game\\animations\\platform\\Platform-forest.png"


namespace Game{

    namespace Entidade{

        namespace Obstaculo{

            class Obstaculo: public Entidade{

            protected:

                sf::Texture textura;

            public:

                Obstaculo(sf::Vector2f pos, sf::Vector2f tam, IDs::IDs ID);
                ~Obstaculo();
                virtual void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.f,0.f)) = 0;
                void colisaoObstaculo(sf::Vector2f ds, Personagem::Personagem* pPersonagem);
                virtual void atualizar() = 0;
                virtual nlohmann::ordered_json salvar() = 0;
            };
        }
    }
}
