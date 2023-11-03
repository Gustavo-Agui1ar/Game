
#pragma once 

#include "estado.h"

#include "../jogador/jogador.h"
#include "../fases/level-1.h"
#include "../fases/level-2.h"
#include "../fases/fase.h"

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
            Entidade::Personagem::Jogador::Jogador* getPlayer();
        };
    }

}