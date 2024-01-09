
#pragma once

#include "fase.h"

namespace Game{

    namespace Fase{

        class Caverna : public Fase  {

        public:

            //construtor e destrutor
            Caverna();
            ~Caverna();
            
            //metodos de criacao de mapas da fase
           
            void criarFundo();
            void criarMapa();

            //metoido que cria uma plataforma
            
            void criarPlataforma(const sf::Vector2f pos);

        };
    }

}
