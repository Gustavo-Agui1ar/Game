#include "../includes/lista/listaEntidade.h"
#include <iostream>


namespace Game{

    namespace Lista{
        
        /**
         * @brief construtora da classe 
        */
        ListaEntidade::ListaEntidade():
        objListaEntidade()
        {

        }

        /**
         * @brief destrutora da classe
        */
        ListaEntidade::~ListaEntidade()
        {
            objListaEntidade.limparLista();
        }

        /**
         * @brief metodo para adicionar um elemento a lista 
         * 
         * @param entidade objeto a ser adicionado a lista
        */
        void ListaEntidade::addEntidade(Entidade::Entidade* entidade)
        {
            objListaEntidade.addElemento(entidade);
        }
        
        /**
         * @brief metodo para adiconar um elemento por posicao 
         * 
         * @param entidade objeto a ser adicionado a lista
         * @param pos posicao a ser inserido o elemento
        */
        void ListaEntidade::addEntidade(Entidade::Entidade* entidade, int pos)
        {
            objListaEntidade.addElemento(entidade, pos);
        }
        
        /**
         * @brief metodo que remove uma entidade da lista
         * 
         * @param entidade objeto a ser removido
        */
        void ListaEntidade::removerEntidade(Entidade::Entidade* entidade)
        {
            objListaEntidade.removerElemento(entidade);
        }

        /**
         * @brief metodo que remove um elemento da lista
         * 
         * @param pos posicao do elemento a ser removido
        */
        void ListaEntidade::removerEntidade(int pos)
        {
            objListaEntidade.removerElemento(pos);
        }
        
        /**
         * @brief metdo de acesso ao tamanho da lista
         * 
         * @return retorna o tamanho da lista
        */
        const int ListaEntidade::getTam(){
            return objListaEntidade.getTam();
        }

        /**
         * @brief operador de posicao para lista
         * 
         * @param pos posicao do elemento desejado
         * 
         * @return retorna um objeto do tipo entidade
        */
        Entidade::Entidade* ListaEntidade::operator[](int pos)
        {
            return objListaEntidade.operator[](pos);
        }

        /**
         * @brief metodo que apaga a lista
        */
        void ListaEntidade::limparLista()
        {
            objListaEntidade.limparLista();
        }

        /**
         * @brief metodo que atualiza o estado de todads as entidades da lista
        */
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
                    objListaEntidade.removerElemento(i);
                    delete(aux);
                    aux = nullptr;
                } 
                else 
                {
                    aux->update();
                }
            }
        }

        /**
         * @brief metodo que desenha a s entidades na tela
        */
        void ListaEntidade::desenharEntidades()
        {
            //apenas desenha as Entidades
            int tam = objListaEntidade.getTam();
            Entidade::Entidade* aux = nullptr;
            for(int i = tam - 1 ; i >= 0 ; i--)
            {
                aux = objListaEntidade.operator[](i);
                aux->draw();
            }
        }

    }
}