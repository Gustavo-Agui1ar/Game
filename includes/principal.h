
#pragma once

#include <SFML/Graphics.hpp>

#include "gerenciador/gerenciadorGrafico.h"
#include "gerenciador/gerenciadorDeEventos.h"
#include "gerenciador/gerenciadorDeEstado.h"
#include "fases/level-1.h"
#include "fases/level-2.h"

namespace Game {

        class Principal{

        private:

            Gerenciador::GerenciadorDeEventos *gerenciadorDeEventos;
            Gerenciador::GerenciadorGrafico *gerenciadorGrafico;
            Gerenciador::GerenciadorDeEstado* pEstado;

        public:

            Principal();
            ~Principal();
            
            void criarEstadoInicial();
            void executar();
        };
}
