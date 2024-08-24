
#pragma once

#include  "../lista/lista.h"
#include  "../entidade/entidade.h"


namespace Game::Lista{
    class ListaEntidade
    {

    private:
        //lista

        Lista<Entidade::Entidade> objListaEntidade;
    
    public:

        //construtor e detrutor

        ListaEntidade();
        ~ListaEntidade();
    
        //metodos de adicao 

        void addEntidade(Entidade::Entidade* entidade, int pos);
        void addEntidade(Entidade::Entidade* entidade);
        
        //metodos de remocao

        void removerEntidade(Entidade::Entidade* entidade);
        void removerEntidade(int pos);
        
        //metodos de percorrer a lista

        Entidade::Entidade* operator[](int pos);
        const int getTam();
        
        //metodo que limpa alista

        void limparLista();
        
        //metodos de atualizacao/visualizacao
        
        void desenharEntidades();
        void executar();

    };
}