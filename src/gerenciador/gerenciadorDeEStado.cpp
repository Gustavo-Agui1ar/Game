
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
        }

        void GerenciadorDeEstado::addEstado(IDs::IDs ID)
        {
            if(ID == IDs::IDs::forest || ID == IDs::IDs::caverna)
            {
                Estado::EstadoFase* fase = new Estado::EstadoFase(ID);
               
                if(fase == nullptr)
                {
                    std::cout<<"estado nao criado";
                    exit(1);
                }
                pilhaEstados.push(static_cast<Estado::Estado*>(fase));
            }
        }

        void GerenciadorDeEstado::removerEstado()
        {
            if(pilhaEstados.top() != nullptr && !pilhaEstados.empty())
            {
               // delete(pilhaEstados.top());
                pilhaEstados.top() = nullptr;
                pilhaEstados.pop();
            }

            if(pilhaEstados.empty())
            {
                Gerenciador::GerenciadorGrafico* pGrafico = pGrafico->getGerenciadorGrafico();
                pGrafico->fechaJanela();
            }
        }

        Estado::Estado* GerenciadorDeEstado::getEstadoAtual()
        {
            return pilhaEstados.top();
        }

        void GerenciadorDeEstado::executar()
        {
            if(!pilhaEstados.empty())
            {
                pilhaEstados.top()->executar();
            }
        }

     }

}