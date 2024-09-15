
#pragma once

#include  "../lista/lista.h"
#include  "../Entity/Entity.h"


namespace Game::Lista{
    class ListaEntidade
    {

    private:
        //lista

        Lista<Entity::Entity> objListaEntidade;
    
    public:

        //construtor e detrutor

        ListaEntidade();
        ~ListaEntidade();
    
        //metodos de adicao 

        void addEntidade(Entity::Entity* entidade, int pos);
        void addEntidade(Entity::Entity* entidade);
        
        //metodos de remocao

        void removerEntidade(Entity::Entity* entidade);
        void removerEntidade(int pos);
        
        //metodos de percorrer a lista

        Entity::Entity* operator[](int pos);
        const int getTam();
        
        //metodo que limpa alista

        void limparLista();
        
        //metodos de atualizacao/visualizacao
        
        void desenharEntidades();
        void executar();

    };
}