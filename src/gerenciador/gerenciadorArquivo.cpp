
#include "../includes/gerenciador/gerenciadorArquivo.h"

namespace Game{

    namespace Gerenciador{
        
        /**
         * @brief construtora da classe GerenciadorArquivo
        */
        GerenciadorArquivo::GerenciadorArquivo():
        arquivoLeitura(), arquivoGravar()
        {

        }

        /**
         * @brief destrutora da classe GerenciadorArquivo
        */
        GerenciadorArquivo::~GerenciadorArquivo()
        {
            if(arquivoGravar.is_open())
                arquivoGravar.close();

            if(arquivoLeitura.is_open())
                arquivoLeitura.close();
        }

        /**
         * @brief metodo que abre um arquivo para leitura
         * 
         * @param caminhoArquivo caminho ate o arquivo a ser aberto
        */
        void GerenciadorArquivo::abrirArquivoLeitura(const char* caminhoArquivo)
        {
            arquivoLeitura.open(caminhoArquivo);

            if(!arquivoLeitura.is_open())
            {
                std::cout<<"GerenciadorArquivo:: nao foi possivel abrir o arquivo";
                exit(1);
            }
        }

        /**
         * @brief metodo que fecha o arquivo de leitura aberto
        */
        void GerenciadorArquivo::fecharArquivoLeitura()
        {
            arquivoLeitura.close();
        }

        /**
         * @brief metodo que abre um arquivo de gravar
         * 
         * @param caminhoArquivo caminho ate o arquivo a ser aberto
        */
        void GerenciadorArquivo::abrirArquivoGravar(const char* caminhoArquivo)
        {
            arquivoGravar.open(caminhoArquivo, std::ios::app);

            if(!arquivoGravar.is_open())
            {
                std::cout << "GerenciadorArquivo:: nao foi possivel abrir o arquivo " << caminhoArquivo << std::endl;
                exit(1);
            }
        }

        /**
         * @brief metodo que fecha o arquivo de gravar aberto
        */
        void GerenciadorArquivo::fecharArquivoGravar()
        {
            arquivoGravar.close();
        }

        /**
         * @brief metodo que le um arquivo
         * 
         * @param caminhoArquivo caminho do arquivo a ser lido
         * 
         * @return retorna um json com as informacoes do arquivo
        */
        nlohmann::ordered_json  GerenciadorArquivo::lerArquivo(const char* caminhoArquivo)
        {
            abrirArquivoLeitura(caminhoArquivo);
            
            nlohmann::ordered_json json;

            json = nlohmann::ordered_json::parse(arquivoLeitura);

            fecharArquivoLeitura();

            return json;
        }
       
        /**
         * @brief metodo que le um arquivo
         * 
         * @param caminhoArquivo caminho do arquivo a ser lido
         * 
         * @return retorna uma string com as informacoes do arquivo
        */
        std::vector<std::string>  GerenciadorArquivo::lerArquivoDeFala(const char* caminhoArquivo)
        {
            abrirArquivoLeitura(caminhoArquivo);
            
            std::vector<std::string> falas;

            std::string fala = "";

            while(std::getline(arquivoLeitura, fala))
                falas.push_back(fala);

            fecharArquivoLeitura();

            return falas;
        }
        
        /**
         * @brief metodo que grava um conteudo em um arquivo
         * 
         * @param caminhoArquivo caminho do arquivo a ser gravado
         * 
         * @param json conteudo a ser gravado no arquivo
        */
        void GerenciadorArquivo::gravarConteudo(const char* caminhoArquivo, nlohmann::ordered_json json)
        {
            abrirArquivoGravar(caminhoArquivo);

            arquivoGravar << std::setw(2) << json;

            fecharArquivoGravar();
        }

        /**
         * @brief metodo que remove um arquivo 
         * 
         * @param caminhoArquivo arquivo a ser deletado
        */
        void GerenciadorArquivo::removeArquivo(const char* caminhoArquivo)
        {
            remove(caminhoArquivo);
        }
    }
}