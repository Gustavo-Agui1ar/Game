
#pragma once

#include "menuPausa.h"
#include "../gerenciador/gerenciadorArquivo.h"

namespace Game{

    namespace Menu{

        class MenuSalvar : public MenuPausa{

            private:
               
                Gerenciador::GerenciadorArquivo gArquivo;
                
                //atributos relacionados aos cards 

                std::list<Card*> listaCards;
                std::list<Card*>::iterator itCard;

                //metodo de inicializacao

                void inicializarCards();
                
            public:

                //construtor e destrutor

                MenuSalvar(Fase::Fase* fase);
                ~MenuSalvar();

                //metodo criador de botoes

                void criarBotoes();

                //metodo ue salva as informacoes do atributo fase da classe MenuPausa

                void salvar();

                //metodo de verificacao de eventos card

                void selecionaEsquerda();
                void selecionaDireita();

                //metodos de atualizacao e visualizacao

                void desenharCards();
                void executar();

        };
    }
}