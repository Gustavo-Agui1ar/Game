
#pragma once

#include "../jogador/personagem.h"
#include "Obstaculo.h"

namespace Game{

    namespace Entidade{

        namespace Obstaculo{

            class Plataforma : public Obstaculo{

            public:
               
                //construtores e destrutor

                Plataforma(sf::Vector2f pos, sf::Vector2f tam, IDs::IDs IDplataforma, IDs::IDs IDtextura);
                Plataforma(nlohmann::ordered_json atributos, IDs::IDs IDplataforma, IDs::IDs IDtextura);
                ~Plataforma();

                //metodo que trata a colisao de um objeto da classe com outros objetos

                void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f));
                
                //metodo que sala os atributos e estado de um objeto desta classe

                nlohmann::ordered_json salvar();
             
                //metod que atualiza o estado de um objeto da classe
                
                void atualizar();
            };
        }
    }
}
