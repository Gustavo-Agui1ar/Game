
#pragma once 

#include "menuPrincipal.h"
#include "../gerenciador/gerenciadorArquivo.h"
#include "../fases/fase.h"

namespace Game {

    namespace Menu {

        class MenuCarregar : public MenuPrincipal {

            private:

                Gerenciador::GerenciadorArquivo gerenciadorArquivo;
                std::list<Card*> listaCards;
                std::list<Card*>::iterator itCards;
                Fase::Fase* fase;
                sf::RectangleShape fundoEscuro;

                void inicializarCards();

            public:

                MenuCarregar(Fase::Fase* fase = nullptr);
                ~MenuCarregar();

                void selecionaEsquerda();
                void selecionaDireita();
                
                void deletarArquivos();
                Card* getCardSelecionado()const;
                void criarBotoes();
                void desenharCards();
                void executar();
        };
    }
}