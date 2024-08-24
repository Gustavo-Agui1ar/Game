
#pragma once

#include "../includes/entidade/entidade.h"

namespace Game::Entidade::Weapon{
    class Weapon : public Entidade{

        protected:

        //atributo de ataque
        
        float m_damage;
        
        public:

        //construtores e destrutor
        
        explicit Weapon(nlohmann::ordered_json atributos);
        explicit Weapon(IDs::IDs ID);
        ~Weapon() override;

        //metodos de ataque
        
        void setDamage(const float damage);
        const float getDamage();
        
        //metodo de colisao
        
        void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f)) override;

        //metodo de salvamento da classe
        
        nlohmann::ordered_json salvar() override;
        nlohmann::ordered_json salvarArma();
        
        //metodos de vizualizacao
        
        void update() override;
        void draw() override;
    };

}