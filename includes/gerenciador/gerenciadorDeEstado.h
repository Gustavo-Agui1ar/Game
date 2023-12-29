
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
            void desativarListener();
            void ativarListener();


            void executar();
            
            void addEstado(const IDs::IDs ID);
            void addEstado(Estado::Estado* estado);
            void addContinuarGameOver(const IDs::IDs ID);
            void removerEstado();
            
            Estado::Estado* getEstadoAtual();
            Estado::Estado* getEstado(int qtd);
            void removerEstado(const int quantidade);

        };
    }

}
