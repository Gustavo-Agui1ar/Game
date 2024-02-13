
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "../includes/json.hpp"

namespace Game {

    namespace Gerenciador{

        class GerenciadorArquivo{
            
            private:

                //atributos responsaveis pela leitura e salvamento de dados
              
                std::ifstream arquivoLeitura; 
                std::ofstream arquivoGravar; 

                //metodo de abrir e fechar o arquivo de leitura
             
                void abrirArquivoLeitura(const char* caminhoArquivo);
                void fecharArquivoLeitura();
                
                //metodo de abrir e fechar o arquivo de gravar

                void abrirArquivoGravar(const char* caminhoArquivo);
                void fecharArquivoGravar();

            public:
                
                //contrutor e destrutor

                GerenciadorArquivo();
                ~GerenciadorArquivo();

                //metodo que le e devolve o arquivo solicitado

                nlohmann::ordered_json lerArquivo(const char* caminhoArquivo);
                std::vector<std::string> lerArquivoDeTexto(const char* caminhoArquivo);
               
                //metodo que grava o conteudo json no arquivo

                void gravarConteudo(const char* caminhoArquivo, nlohmann::ordered_json json);
                
                ///metodo que remove um arquivo

                void removeArquivo(const char* caminhoArquivo);
        };
    }
}