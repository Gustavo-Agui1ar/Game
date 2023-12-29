#include "../includes/lista/listaEntidade.h"
#include <iostream>


namespace Game{

    namespace Lista{

        ListaEntidade::ListaEntidade():
        objListaEntidade()
        {

        }

        ListaEntidade::~ListaEntidade()
        {
            objListaEntidade.limparLista();
        }

        void ListaEntidade::addEntidade(Entidade::Entidade* entidade)
        {
            objListaEntidade.addElemento(entidade);
        }

        void ListaEntidade::addEntidade(Entidade::Entidade* entidade, int pos)
        {
            objListaEntidade.addElemento(entidade, pos);
        }

        void ListaEntidade::removerEntidade(Entidade::Entidade* entidade)
        {
            objListaEntidade.removerElemento(entidade);
        }
            
        void ListaEntidade::removerEntidade(int pos)
        {
            objListaEntidade.removerElemento(pos);
        }

        const int ListaEntidade::getTam(){
            return objListaEntidade.getTam();
        }

        Entidade::Entidade* ListaEntidade::operator[](int pos)
        {
            return objListaEntidade.operator[](pos);
        }

        void ListaEntidade::limparLista()
        {
            objListaEntidade.limparLista();
        }

        void ListaEntidade::executar()
        {
            //atualiza e desenha as entidades
            int tam = objListaEntidade.getTam();
            Entidade::Entidade* aux = nullptr;
            for(int i = tam - 1; i >= 0; i--)
            {
                aux = objListaEntidade.operator[](i);
                if(aux->getRemover())
                {
                    objListaEntidade.removerElemento(aux);
                    delete(aux);
                    aux = nullptr;
                } 
                else 
                {
                    aux->atualizar();
                }
            }
        }

        void ListaEntidade::desenharEntidades()
        {
            //apenas desenha as Entidades
            int tam = objListaEntidade.getTam();
            Entidade::Entidade* aux = nullptr;
            for(int i = 0; i < tam; i++)
            {
                aux = objListaEntidade.operator[](i);
                aux->desenhar();
            }
        }

    }
}