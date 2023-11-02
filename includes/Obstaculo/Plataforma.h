
#pragma once

#include "../jogador/personagem.h"
#include "Obstaculo.h"

namespace Game{

    namespace Entidade{

        namespace Obstaculo{

            class Plataforma : public Obstaculo{

            public:
                Plataforma(sf::Vector2f pos, sf::Vector2f tam, IDs::IDs ID);
                ~Plataforma();
                void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f));
                void atualizar();
            };
        }
    }
}
