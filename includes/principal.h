
#pragma once

#include <SFML/Graphics.hpp>

#include "gerenciador/gerenciadorGrafico.h"
#include "gerenciador/gerenciadorDeEventos.h"
#include "fases/fase.h"
#include "fases/level-1.h"
#include "fases/level-2.h"

namespace Game {

        class Principal{

        private:

            Gerenciador::GerenciadorDeEventos *gerenciadorDeEventos;
            Gerenciador::GerenciadorGrafico *gerenciadorGrafico;
            Fase::Fase* fase;

        public:

            Principal();
            ~Principal();
            
            void criarFase();
            void executar();
        };
}
