
#include "../includes/gerenciador/gerenciadorArquivo.h"

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
                exit(1);
            }
        }

        void GerenciadorArquivo::fecharArquivoLeitura()
        {
            arquivoLeitura.close();
        }

        void GerenciadorArquivo::abrirArquivoGravar(const char* caminhoArquivo)
        {
            arquivoGravar.open(caminhoArquivo, std::ios::app);

            if(!arquivoGravar.is_open())
            {
                std::cout << "GerenciadorArquivo:: nao foi possivel abrir o arquivo " << caminhoArquivo << std::endl;
                exit(1);
            }
        }

        void GerenciadorArquivo::fecharArquivoGravar()
        {
            arquivoLeitura.close();
        }

        nlohmann::ordered_json  GerenciadorArquivo::lerArquivo(const char* caminhoArquivo)
        {
            abrirArquivoLeitura(caminhoArquivo);
            
            nlohmann::ordered_json json;

            json = nlohmann::ordered_json::parse(arquivoLeitura);

            fecharArquivoLeitura();

            return json;
        }

        void GerenciadorArquivo::gravarConteudo(const char* caminhoArquivo, nlohmann::ordered_json json)
        {
            abrirArquivoGravar(caminhoArquivo);

            arquivoGravar << std::setw(2) << json;

            fecharArquivoGravar();
        }

        void GerenciadorArquivo::removeArquivo(const char* caminhoArquivo)
        {
            remove(caminhoArquivo);
        }
    }
}