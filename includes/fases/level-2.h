

#pragma once

#include "fase.h"

namespace Game{

    namespace Fase{

        class Forest : public Fase{

        public:

            //contrutor e destrutor
            Forest();
            ~Forest();
           
            //metodos de criacao de mapa da fase
            void criarFundo();
            void criarMapa();
           
            //metodo que cria uma plataforma
            void criarPlataforma(const sf::Vector2f pos);

        };
    }

}

