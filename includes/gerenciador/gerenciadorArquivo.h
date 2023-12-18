
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "../json.hpp"

namespace Game {

    namespace Gerenciador{

        class GerenciadorArquivo{
            
            private:

                std::ifstream arquivoLeitura; 
                std::ofstream arquivoGravar; 

                void abrirArquivoLeitura(const char* caminhoArquivo);
                void fecharArquivoLeitura();
                void abrirArquivoGravar(const char* caminhoArquivo);
                void fecharArquivoGravar();

            public:

                GerenciadorArquivo();
                ~GerenciadorArquivo();

                nlohmann::ordered_json lerArquivo(const char* caminhoArquivo);
                void gravarConteudo(const char* caminhoArquivo, nlohmann::ordered_json json);
                void removeArquivo(const char* caminhoArquivo);
        };
    }
}