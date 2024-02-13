
#include "../includes/estados/estadoDialogo.h"

namespace Game{

    namespace Estado{

        
        EstadoDialogo::EstadoDialogo(const IDs::IDs ID):
        Estado(ID), fase(nullptr), pDialogo(nullptr)
        {

        }
        EstadoDialogo::~EstadoDialogo()
        {
            if(pDialogo != nullptr)
            {
                delete(pDialogo);
                pDialogo = nullptr;
            }

            fase = nullptr;
        }

        void EstadoDialogo::inicializarFalas(std::vector<std::string> arquivoFalas)
        {
            std::vector<std::string>::iterator it = arquivoFalas.begin();
            
            std::vector<std::string> nomes; 
            std::vector<std::string> falas;

            while(it != arquivoFalas.end())
            {
                 std::string linhaDialogo = (*it);
                std::string nome = linhaDialogo.substr(0, linhaDialogo.find(":"));
                std::string fala = linhaDialogo.substr(nome.size() + 1, linhaDialogo.size());
                
                nomes.push_back(nome);
                falas.push_back(fala);
                it++;
            }

            pDialogo = new Gerenciador::GerenciadorDeDialogo(nomes, falas);
        }
        void EstadoDialogo::setFase(Fase::Fase* fase)
        {
            this->fase = fase;
        }
        void EstadoDialogo::setDialogo(const char* arquivoDialogo)
        {
            Gerenciador::GerenciadorArquivo arquivo;

            std::vector<std::string> falas = arquivo.lerArquivoDeTexto(arquivoDialogo);

            inicializarFalas(falas);
        }
        
        void EstadoDialogo::executar()
        {
            fase->desenhar();
            pDialogo->atualizar();
        }

        void EstadoDialogo::desenhar()
        {
            fase->desenhar();
            pDialogo->desenhar();
        }

        void EstadoDialogo::mudarEstadoListener(const bool ativo)
        {
            pDialogo->mudarEstadoListener(ativo);
        }
        
        Fase::Fase* EstadoDialogo::getFase()
        {
            return fase;
        }
    }
}