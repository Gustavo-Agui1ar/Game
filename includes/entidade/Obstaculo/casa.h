
#pragma once 

#include "../includes/gerenciador/gerenciadorGrafico.h"
#include "../includes/entidade/entidade.h"

namespace Game{

    namespace Entidade{

        namespace Obstaculo{

            class Casa : public Entidade{
            
                private:

                    sf::Texture textura;
                
                public:

                    Casa(const sf::Vector2f tam,const IDs::IDs ID, const sf::Vector2f pos = {0,0});
                    ~Casa();

                    void atualizar();
                    nlohmann::ordered_json salvar();
                    void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.f,0.f));
                    void setTextura(const char* caminhoTextura);
            };
        }
    }

}
