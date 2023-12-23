
#pragma once

#include "menuPausa.h"
#include "../gerenciador/gerenciadorArquivo.h"

namespace Game{

    namespace Menu{

        class MenuSalvar : public MenuPausa{

            private:
               
                Gerenciador::GerenciadorArquivo gArquivo;
                
                std::list<Card*> listaCards;
                std::list<Card*>::iterator itCard;

                void inicializarCards();
                
            public:

                MenuSalvar(Fase::Fase* fase);
                ~MenuSalvar();

                void criarBotoes();
                void salvar();
                void selecionaEsquerda();
                void selecionaDireita();
                void desenharCards();
                void executar();

        };
    }
}