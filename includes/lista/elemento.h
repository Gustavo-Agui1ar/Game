
#pragma once

namespace Game{

    namespace Lista{

        template<class TE>
        class Elemento
        {
            
        private:

            //atributos de lista
            Elemento<TE>* prox;
            TE* elemento;

        public:
        
            //construtora e destrutora
            Elemento();
            ~Elemento();
            
            //metodos seters
            void setProx(Elemento<TE>* prox);
            void setElemento(TE* elemento);
            
            //metodos geters
            Elemento<TE>* getProx();
            TE* getElemento();
        };
        
        /**
         * construtora da classe
        */

        template<class TE>
        Elemento<TE>::Elemento()
        {
            elemento = nullptr;
            prox = nullptr;
        }
        
        /**
         * destrutora da classe
        */

        template<class TE>
        Elemento<TE>::~Elemento()
        {
            
        }

        /**
         * metodo que seta o apontamento do proximo elemento
         * 
         * parametros:
         * 
         * prox: elemento a ser setado
        */

        template<class TE>
        void Elemento<TE>::setProx(Elemento<TE>* prox)
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

        template<class TE>
        void Elemento<TE>::setElemento(TE* elemento)
        {
            this->elemento = elemento;
        }

        /**
         * metodo que retorna o proximo
        */

        template<class TE>
        Elemento<TE>* Elemento<TE>::getProx()
        {
            return prox;
        }

        /**
         * metodo que retorna o elemento
        */

        template<class TE>
        TE* Elemento<TE>::getElemento()
        {
            return elemento;
        }

    }
}
