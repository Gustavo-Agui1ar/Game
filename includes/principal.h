
#pragma once

#include <SFML/Graphics.hpp>

#include "Manager/GraphicManager.h"
#include "Manager/EventManager.h"
#include "Manager/StateManager.h"
namespace Game {

        class Principal{

        private:

            Manager::GraphicManager *gerenciadorGrafico;
            Manager::EventManager* gerenciadorDeEventos;
            Manager::StateManager* pEstado;
    
        public:

            Principal();
            ~Principal();
            
            void criarEstadoInicial();
            void executar();
        };
}
