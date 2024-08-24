
#pragma once

#include "../includes/menus/botao/balaoDeFala.h"
#include <list>

namespace Game{

    namespace Listener{

        class ListenerDialogo;
    }

    namespace Gerenciador{

        class GerenciadorDeDialogo{

        private:

            std::list<Menu::Botao::BalaoDeFala*> dialogos;
            std::list<Menu::Botao::BalaoDeFala*>::iterator dialogoAtual;

            bool fimUltimaFala;
            bool nomeEsquerda;

            Listener::ListenerDialogo* pLDialogo;

            void inicializarDialogos(std::vector<std::string> nomes, std::vector<std::string> falas);

        public:

            GerenciadorDeDialogo(std::vector<std::string> nomes, std::vector<std::string> falas);
            ~GerenciadorDeDialogo();

            void mudarEstadoListener(const bool ativo);

            void pularDialogo();
            void proximaFala();

            void atualizar();
            void draw();

            const bool getFimUltimaFala();
            const bool getFimFalaAtual();

        };
    }
}