
#pragma once

#include "../estados/estadoFase.h"
#include "../estados/estadoMenu.h"
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
            
            void addEstado(const IDs::IDs ID);
            void removerEstado();
            
            Estado::Estado* getEstadoAtual();

        };
    }

}
