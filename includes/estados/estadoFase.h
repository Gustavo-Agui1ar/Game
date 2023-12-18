
#pragma once 

#include "estado.h"

#include "../gerenciador/GerenciadorGrafico.h"

#include "../fases/level-1.h"
#include "../fases/level-2.h"

namespace Game{

    namespace Estado{

        class EstadoFase : public Estado{

        private:

        Fase::Fase* fase;

        public:

            EstadoFase(const IDs::IDs ID);
            ~EstadoFase();

            void criarFase();
            void executar();
            Fase::Fase* getFase();

            void mudarEstadoListener(const bool ativo);

        };
    }

}
