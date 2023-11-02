
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

            while(!pilhaEstados.empy())
            {
                delete(pilhaEstados.top());
                pilhaEstados.top() = nullptr;
                pilhasEstados.pop();
            }
        }

     }

}