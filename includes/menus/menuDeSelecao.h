
#pragma once 

#include "menuPausa.h"
#include "../includes/menus/Button/SelectionButton.h"
#include "../includes/Manager/FileManager.h"

namespace Game::Menu{
    class MenuDeSelecao : public MenuPausa{
        
        private:

            Manager::FileManager* pArquivo;
            std::list<Button::SelectionButton*> listaDeSelecao;
            std::list<Button::SelectionButton*>::iterator itSelecaoFase;

        public:

            explicit MenuDeSelecao(Level::Level* fase = nullptr);
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