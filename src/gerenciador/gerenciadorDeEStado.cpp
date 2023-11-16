
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
                //delete(pilhaEstados.top());
                pilhaEstados.top() = nullptr;
                pilhaEstados.pop();
            }
        }

        void GerenciadorDeEstado::addEstado(IDs::IDs ID)
        {
            Estado::Estado* estado = nullptr;

            if(ID == IDs::IDs::forest || ID == IDs::IDs::caverna)
            {
                Estado::EstadoFase* fase = new Estado::EstadoFase(ID);
               
                if(fase == nullptr)
                {
                    std::cout<<"Gerenciador::GerenciadorDeEstado: erro ao criar estado";
                    exit(1);
                }

                estado = static_cast<Estado::Estado*>(fase);

            }
            else if(ID == IDs::IDs::menu_principal || ID == IDs::IDs::menu_pause)
            {
                Estado::EstadoMenu* menu = new Estado::EstadoMenu(ID);

                if(menu == nullptr)
                {
                    std::cout<<"Gerenciador::GerenciadorDeEstado: erro ao criar estado";
                    exit(1);
                }

                estado = static_cast<Estado::Estado*>(menu);
            }

            if(!pilhaEstados.empty())
            {
                Estado::Estado* estado = getEstadoAtual();
                estado->mudarEstadoListener();
            }

            if(estado != nullptr)
                pilhaEstados.push(estado);
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
                Estado::Estado* estado = getEstadoAtual();
                estado->mudarEstadoListener();
            }
            
            else{
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
                pilhaEstados.top()->mudarEstadoListener();
            } 
            else 
            {
                GerenciadorGrafico* pGrafico = pGrafico->getGerenciadorGrafico();
                pGrafico->fechaJanela();
            }
        }

     }

}