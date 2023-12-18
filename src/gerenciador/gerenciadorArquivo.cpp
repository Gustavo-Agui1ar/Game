
#include "includes\gerenciador\gerenciadorArquivo.h"

namespace Game{

    namespace Gerenciador{

        GerenciadorArquivo::GerenciadorArquivo():
        arquivoLeitura(), arquivoGravar()
        {

        }

        GerenciadorArquivo::~GerenciadorArquivo()
        {
            if(arquivoGravar.is_open())
                arquivoGravar.close();
            if(arquivoLeitura.is_open())
                arquivoLeitura.close();
        }

        void GerenciadorArquivo::abrirArquivoLeitura(const char* caminhoArquivo)
        {
            arquivoLeitura.open(caminhoArquivo);

            if(!arquivoLeitura.is_open())
            {
                std::cout<<"GerenciadorArquivo:: nao foi possivel abrir o arquivo";
                extit(1);
            }
        }

        void GerenciadorArquivo::fecharArquivoLeitura()
        {
            arquivoLeitura.close();
        }
    }
}