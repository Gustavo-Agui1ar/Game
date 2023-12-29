
#include "../includes/gerenciador/gerenciadorDeEstado.h"


namespace Game{

    namespace Gerenciador{

         GerenciadorDeEstado* GerenciadorDeEstado::pEstado = nullptr;

         GerenciadorDeEstado::GerenciadorDeEstado():
         pilhaEstados()
         {

         }

        GerenciadorDeEstado* GerenciadorDeEstado::getGerenciadorDeEstado()
        {
            if(pEstado == nullptr)
                pEstado = new GerenciadorDeEstado();
            return pEstado;
        }

        GerenciadorDeEstado::~GerenciadorDeEstado()
        {
            if(pEstado != nullptr)
                delete(pEstado);
            
            pEstado = nullptr;

            while(!pilhaEstados.empty())
            {
                delete(pilhaEstados.top());
                pilhaEstados.top() = nullptr;
                pilhaEstados.pop();
            }

            if(pEstado){
                delete(pEstado);
                pEstado = nullptr;
            }
        }

        void GerenciadorDeEstado::addEstado(IDs::IDs ID)
        {
            Estado::Estado* estado = nullptr;

            if(ID == IDs::IDs::forest || ID == IDs::IDs::caverna)
            {
                estado = static_cast<Estado::Estado*>(new Estado::EstadoFase(ID));
            }
            else if(ID == IDs::IDs::menu_principal ||
                    ID == IDs::IDs::menu_pause     ||
                    ID == IDs::IDs::menu_gameOver  ||
                    ID == IDs::IDs::menu_carregar  ||
                    ID == IDs::IDs::menu_salvar)
            {
                Estado::EstadoMenu* mEstado = new Estado::EstadoMenu(ID);
                estado = static_cast<Estado::Estado*>(mEstado);
            }

            if(estado == nullptr)
            {
                std::cout << ":Gerenciador::GerenciadorEstado::estado nulo" << std::endl;
                exit(1);
            }
            if(!pilhaEstados.empty())
            {
                desativarListener();
            }
            
            pilhaEstados.push(estado);
        }

        void GerenciadorDeEstado::addEstado(Estado::Estado* estado)
        {
             if(estado == nullptr)
            {
                std::cout << ":Gerenciador::GerenciadorEstado::estado nulo" << std::endl;
                exit(1);
            }
            if(!pilhaEstados.empty())
            {
                desativarListener();
            }
            
            pilhaEstados.push(estado);
        }

        void GerenciadorDeEstado::addContinuarGameOver(const IDs::IDs ID)
        {
            removerEstado(2);
            addEstado(ID);
        }

        void GerenciadorDeEstado::removerEstado()
        {
            if(pilhaEstados.top() != nullptr && !pilhaEstados.empty())
            {
                delete(pilhaEstados.top());
                pilhaEstados.top() = nullptr;
                pilhaEstados.pop();
            }

            if(!pilhaEstados.empty())
            {
               ativarListener();
            }
            else
            {
                Gerenciador::GerenciadorGrafico* pGrafico = pGrafico->getGerenciadorGrafico();
                pGrafico->fechaJanela();
            }
        }


        void GerenciadorDeEstado::ativarListener()
        {
            Estado::Estado* estadoAtual = getEstadoAtual();

            estadoAtual->mudarEstadoListener(true);
        }


        void GerenciadorDeEstado::desativarListener()
        {
            Estado::Estado* estadoAtual = getEstadoAtual();

            estadoAtual->mudarEstadoListener(false);
        }

        Estado::Estado* GerenciadorDeEstado::getEstadoAtual()
        {
            if(!pilhaEstados.empty())
            {
                return pilhaEstados.top();
            }
            return nullptr;
        }

        Estado::Estado* GerenciadorDeEstado::getEstado(int qtd)
        {
            std::stack<Estado::Estado*> pilhaAux = pilhaEstados;

            int i = 0;

            while( i  < qtd && !pilhaAux.empty())
            {
                pilhaAux.pop();
                i++;
            }

            if(!pilhaAux.empty())
                return pilhaAux.top();
            
            return nullptr;
        }

        void GerenciadorDeEstado::executar()
        {
            if(!pilhaEstados.empty())
            {
                Estado::Estado* estado = pilhaEstados.top();
                estado->executar();
            }
        }
        void GerenciadorDeEstado::removerEstado(const int quantidade)
        {
            int i = 0;
            while(!pilhaEstados.empty() && i < quantidade)
            {
                Estado::Estado* estado = pilhaEstados.top();
                if(estado != nullptr){
                    delete(estado);
                    estado = nullptr; 
                }
                pilhaEstados.pop();
                i++;
            }
            if(!pilhaEstados.empty())
            {
                ativarListener();
            } 
            else 
            {
                GerenciadorGrafico* pGrafico = pGrafico->getGerenciadorGrafico();
                pGrafico->fechaJanela();
            }
        }
    }
}
