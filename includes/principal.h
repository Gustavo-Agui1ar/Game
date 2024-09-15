
#pragma once

#include <SFML/Graphics.hpp>

#include "gerenciador/gerenciadorGrafico.h"
#include "gerenciador/gerenciadorDeEventos.h"
#include "gerenciador/gerenciadorDeEstado.h"
namespace Game {

        class Principal{

        private:

            Gerenciador::GerenciadorGrafico *gerenciadorGrafico;
            Gerenciador::GerenciadorDeEventos* gerenciadorDeEventos;
            Gerenciador::GerenciadorDeEstado* pEstado;
    
        public:

            Principal();
            ~Principal();
            
            void criarEstadoInicial();
            void executar();
        };
}
