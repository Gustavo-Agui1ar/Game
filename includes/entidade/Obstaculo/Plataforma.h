
#pragma once

#include "../Player/Character.h"
#include "Obstaculo.h"

namespace Game::Entidade::Obstaculo{
    class Plataforma : public Obstaculo{

    public:
        
        //construtores e destrutor

        Plataforma(sf::Vector2f pos, sf::Vector2f tam, IDs::IDs IDplataforma, IDs::IDs IDtextura);
        Plataforma(nlohmann::ordered_json atributos, IDs::IDs IDplataforma, IDs::IDs IDtextura);
        ~Plataforma() override;

        //metodo que trata a colisao de um objeto da classe com outros objetos

        void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f)) override;
        
        //metodo que sala os atributos e estado de um objeto desta classe

        nlohmann::ordered_json salvar() override;
        
        //metod que atualiza o estado de um objeto da classe
        
        void update() override;
    };
}
