
#pragma once 

#include "menuPrincipal.h"
#include "../gerenciador/gerenciadorArquivo.h"

namespace Game {

    namespace Menu {

        class MenuCarregar : public MenuPrincipal {

            private:

                Gerenciador::GerenciadorArquivo gerenciadorArquivo;
                std::list<Card*> listaCards;
                std::list<Card*>::iterator itCards;

                void inicializarCards();

            public:

                MenuCarregar();
                ~MenuCarregar();

                void selecionaEsquerda();
                void selecionaDireita();
                
                void deletarArquivos();
                Card* getCardSelecionado();
                void criarBotoes();
                void executar();
        };
    }
}