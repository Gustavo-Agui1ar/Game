#pragma once

#include "../entidade/entidade.h"

namespace Game{

    namespace Lista{

        class ElementoEntidade
        {
            
        private:

            //atributos de lista
            Entidade::Entidade* elemento;
            ElementoEntidade* prox;

        public:
        
            //construtora e destrutora
            ElementoEntidade();
            ~ElementoEntidade();
            
            //metodos seters
            void setEntidade(Entidade::Entidade* elemento);
            void setProxEntidade(ElementoEntidade* prox);
            
            //metodos geters
            ElementoEntidade* getProxEntidade();
            Entidade::Entidade* getEntidade();
        };
        
        /**
         * construtora da classe
        */

        ElementoEntidade::ElementoEntidade()
        {
            elemento = nullptr;
            prox = nullptr;
        }
        
        /**
         * destrutora da classe
        */

        ElementoEntidade::~ElementoEntidade()
        {
        
        }

        /**
         * metodo que seta o apontamento do proximo elemento
         * 
         * parametros:
         * 
         * prox: elemento a ser setado
        */

        void ElementoEntidade::setProxEntidade(ElementoEntidade* prox)
        {
            this->prox = prox;
        }

        /**
         * metodo que seta o apontamento do elemento
         * 
         * parametros:
         * 
         * elemento : elemento a ser setado
        */

        void ElementoEntidade::setEntidade(Entidade::Entidade* elemento)
        {
            this->elemento = elemento;
        }

        /**
         * metodo que retorna o proximo
        */

        ElementoEntidade* ElementoEntidade::getProxEntidade()
        {
            return prox;
        }

        /**
         * metodo que retorna o elemento
        */

        Entidade::Entidade* ElementoEntidade::getEntidade()
        {
            return elemento;
        }

    }
}
