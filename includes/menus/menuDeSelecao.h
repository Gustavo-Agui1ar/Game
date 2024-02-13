
#pragma once 

#include "menuPausa.h"
#include "../includes/menus/botao/botaoSelecao.h"
#include "../includes/gerenciador/gerenciadorArquivo.h"

namespace Game{

    namespace Menu{

        class MenuDeSelecao : public MenuPausa{
            
            private:

                Gerenciador::GerenciadorArquivo* pArquivo;
                std::list<Botao::BotaoSelecao*> listaDeSelecao;
                std::list<Botao::BotaoSelecao*>::iterator itSelecaoFase;

            public:

                MenuDeSelecao(Fase::Fase* fase = nullptr);
                ~MenuDeSelecao();

                void criarBotoes();
                void criarBotoesDeSelecao();
                void selecionaEsquerda();
                void inicializarBotoes();
                void selecionaDireita();

                void executar();

                const IDs::IDs getIDdeSelecao();
        };
    }
}