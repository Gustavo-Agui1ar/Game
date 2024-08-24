
#pragma once 

#include <string>
#include "estado.h"
#include "../fases/fase.h"
#include "../includes/gerenciador/gerenciadorDeDialogo.h"
#include "../includes/gerenciador/gerenciadorArquivo.h"

namespace Game::Estado{
        class EstadoDialogo : public Estado {

        private:

            Fase::Fase* fase;
            Gerenciador::GerenciadorDeDialogo* pDialogo;

            void inicializarFalas(std::vector<std::string> arquivoFalas);

        public:

            explicit EstadoDialogo(const IDs::IDs ID);
            ~EstadoDialogo() override;

            void setFase(Fase::Fase* fase);
            Fase::Fase* getFase();

            void setDialogo(const char* arquivoDialogo);
            
            void executar() override;
            void draw() override;

            void mudarEstadoListener(const bool ativo) override;
    
    };
}