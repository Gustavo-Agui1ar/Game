
#pragma once 

#include "menuPausa.h"
#include "../includes/menus/botao/botaoSelecao.h"
#include "../includes/gerenciador/gerenciadorArquivo.h"

namespace Game::Menu{
    class MenuDeSelecao : public MenuPausa{
        
        private:

            Gerenciador::GerenciadorArquivo* pArquivo;
            std::list<Botao::BotaoSelecao*> listaDeSelecao;
            std::list<Botao::BotaoSelecao*>::iterator itSelecaoFase;

        public:

            explicit MenuDeSelecao(Fase::Fase* fase = nullptr);
            ~MenuDeSelecao() override;

            void criarBotoes() override;
            void criarBotoesDeSelecao();
            void selecionaEsquerda() override;
            void inicializarBotoes();
            void selecionaDireita() override;

            void executar() override;

            const IDs::IDs getIDdeSelecao();
    };
}