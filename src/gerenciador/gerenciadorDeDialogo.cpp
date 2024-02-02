
#include "../includes/gerenciador/gerenciadorDeDialogo.h"
#include "../includes/listeners/listenerDialogo.h"

namespace Game{

    namespace Gerenciador{

        GerenciadorDeDialogo::GerenciadorDeDialogo(std::vector<std::string> nomes, std::vector<std::string> falas):
        dialogos(), fimUltimaFala(false), nomeEsquerda(true), pLDialogo(new Listener::ListenerDialogo(this))
        {
            inicializarDialogos(nomes, falas);
        }

        GerenciadorDeDialogo::~GerenciadorDeDialogo()
        {
            if(pLDialogo != nullptr)
            {
                delete(pLDialogo);
                pLDialogo = nullptr;
            }

            dialogos.clear();
        }

        void GerenciadorDeDialogo::inicializarDialogos(std::vector<std::string> nomes, std::vector<std::string> falas)
        {
            std::vector<std::string>::iterator itN = nomes.begin();
            std::vector<std::string>::iterator itF = falas.begin();

            while(itF != falas.end())
            {
                std::string nome = (*itN);
                std::string dialogo = (*itF);

                Menu::Botao::BalaoDeFala* fala = new Menu::Botao::BalaoDeFala(dialogo, nome);

                if(fala == nullptr)
                {
                    std::cout<< "Game::Gerenciador::GerenciadordeDialogo erro ao iniciar falas";
                    exit(1);
                }

                dialogos.push_back(fala);
                
                itF++;
                itN++;
            }

            dialogoAtual = dialogos.begin();
        }

        void GerenciadorDeDialogo::pularDialogo()
        {
            (*dialogoAtual)->pularDialogo();
        }

        void GerenciadorDeDialogo::proximaFala()
        {
            if((*dialogoAtual)->getFimTexto() && !fimUltimaFala)
            {
                dialogoAtual++;
                dialogoAtual++;
                if(dialogoAtual == dialogos.end())
                {
                    fimUltimaFala = true;
                }
                dialogoAtual--;
               
                nomeEsquerda = !nomeEsquerda;
                (*dialogoAtual)->setDirecaoNome(nomeEsquerda);
            }
        }

        void GerenciadorDeDialogo::atualizar()
        {
            (*dialogoAtual)->atualizar();
            desenhar();
        }

        void GerenciadorDeDialogo::desenhar()
        {
            (*dialogoAtual)->desenhar();
        }

        const bool GerenciadorDeDialogo::getFimUltimaFala()
        {
            return fimUltimaFala;
        }
        
        const bool GerenciadorDeDialogo::getFimFalaAtual()
        {
            return (*dialogoAtual)->getFimTexto();
        }

        void GerenciadorDeDialogo::mudarEstadoListener(const bool ativo)
        {
            pLDialogo->mudarEstado(ativo);
        }
    }
}