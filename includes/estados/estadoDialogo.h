
#pragma once 

#include <string>
#include "estado.h"
#include "../fases/fase.h"
#include "../includes/gerenciador/gerenciadorDeDialogo.h"
#include "../includes/gerenciador/gerenciadorArquivo.h"

namespace Game{
    
    namespace Estado{

        class EstadoDialogo : public Estado {

            private:

                Fase::Fase* fase;
                Gerenciador::GerenciadorDeDialogo* pDialogo;

                void inicializarFalas(std::vector<std::string> arquivoFalas);

            public:

                EstadoDialogo(const IDs::IDs ID);
                ~EstadoDialogo();

                void setFase(Fase::Fase* fase);
                void setDialogo(const char* arquivoDialogo);
                
                void executar();
                void desenhar();

                void mudarEstadoListener(const bool ativo);
        
        };
    }
}