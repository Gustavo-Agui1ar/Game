
#pragma once

#include "../entidade/entidade.h"

namespace Game{

    namespace Entidade{

        namespace Item{

            class Arma : public Entidade{

                protected:

                //atributo de ataque
                float dano;
                
                public:

                //construtor e destrutor
                Arma(IDs::IDs ID);
                Arma(nlohmann::ordered_json atributos);
                ~Arma();

                //metodos de ataque
                void setDano(const float dano);
                const float getDano();
                
                //metodo de colisao
                void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f));

                nlohmann::ordered_json salvar();
                
                //metodos de vizualizacao
                void desenhar();
                void atualizar();
            };
        }
    }

}