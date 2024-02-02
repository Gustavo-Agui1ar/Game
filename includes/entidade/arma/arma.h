
#pragma once

#include "../includes/entidade/entidade.h"

namespace Game{

    namespace Entidade{

        namespace Arma{

            class Arma : public Entidade{

                protected:

                //atributo de ataque
                
                float dano;
                
                public:

                //construtores e destrutor
                
                Arma(nlohmann::ordered_json atributos);
                Arma(IDs::IDs ID);
                virtual ~Arma();

                //metodos de ataque
                
                void setDano(const float dano);
                const float getDano();
                
                //metodo de colisao
                
                virtual void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f));

                //metodo de salvamento da classe
                
                nlohmann::ordered_json salvar();
                nlohmann::ordered_json salvarArma();
                
                //metodos de vizualizacao
                
                virtual void atualizar();
                virtual void desenhar();
            };
        }
    }

}