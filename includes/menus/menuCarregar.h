
#pragma once 

#include "menuPrincipal.h"

namespace Game {

    namespace Menu {

        class MenuCarregar : public MenuPrincipal {

            private:

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