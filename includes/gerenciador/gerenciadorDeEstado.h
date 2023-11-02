
#pragma once

#include "../estados/estado.h"
#include <stack>


namespace Game{

    namespace Gerenciador{


        class GerenciadorDeEstado{

        private:

            std::stack<Estado::Estado*> pilhaEstados;
            GerenciadorDeEstado();

            static GerenciadorDeEstado* pEstado;

        public:

            ~GerenciadorDeEstado();
            static GerenciadorDeEstado* getGerenciadorDeEstado();

            void executar();
            
            void addEstado(IDs::IDs ID);
            void removerEstado();
            
            Estado::Estado* getEstadoAtual();

        };
    }

}
