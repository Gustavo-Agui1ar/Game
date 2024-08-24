
#pragma once

#include "../lista/elemento.h"
#include <iostream>

namespace Game::Lista{
    template<class TL>
    class Lista
    {
        
    private:

        //cabeca e cauda da lista

        Elemento<TL>* pInicio = nullptr;
        Elemento<TL>* pUltimo = nullptr;
        
        //atributo relacionado ao tamanho da lista

        unsigned int tam = 0;
    
    public:
    
        //construtor e destrutor

        Lista();
        ~Lista();
        
        //metodos de adicao

        void addElemento(TL* elemento, int pos);
        void addElemento(TL* elemento);
        
        //metodos de remocao

        void removerElemento(TL* elemento);
        void removerElemento(int pos);
        
        //metodos de passagem/percorrrer na lista

        TL* operator[](int pos);
        int getTam();
        
        // metodo que limpa a lista

        void limparLista();
    };

    /**
     * construtor da classe 
    */
    template<class TL>
    Lista<TL>::Lista() = default;

    /**
     * destrutor da classe 
    */
    template<class TL>
    Lista<TL>::~Lista() = default;

    /**
     * metodo que adiciona um elemento a lista
     * 
     * parametros:
     * 
     * elemento: elemento a ser adicionado
     * 
    */
    template<class TL>
    void Lista<TL>::addElemento(TL* elemento)
    {
        if(elemento == nullptr){
            std::cout << "ERROR::Lista elemento eh nullptr" << std::endl;
            exit(1);
        }
        auto *novoElemento = new Elemento<TL>();
        if(novoElemento == nullptr){
            std::cout << "ERROR::Lista aux eh nullptr" << std::endl;
            exit(1);
        }
        novoElemento->setElemento(elemento);
        if(pInicio == nullptr){
            pInicio = novoElemento;
            pUltimo = novoElemento;
        } else {
            pUltimo->setProx(novoElemento);
            pUltimo = novoElemento;
        }
        tam++;
    }

    /**
     * adiciona um elemento a lista
     * 
     * parametros:
     * 
     * elemento: elemento a ser adicionado
     * pos: posicao a ser adicionado
     * 
    */
    template<class TL>
    void Lista<TL>::addElemento(TL* elemento, int pos)
    {
        if(pos > (int)tam || pos < 0){
            std::cout << "ERRO::Lista::posicao nao eh compativel com o tamanho da lista" << std::endl;
            exit(1);
        }
        if(elemento == nullptr){
            std::cout << "ERROR::Lista elemento eh nullptr" << std::endl;
            exit(1);
        }
        auto *novoElemento = new Elemento<TL>();
        if(novoElemento == nullptr){
            std::cout << "ERROR::Lista novoElemento eh nullptr" << std::endl;
            exit(1);
        }
        novoElemento->setElemento(elemento);
        if(pInicio == nullptr){
            pInicio = novoElemento;
            pUltimo = novoElemento;
        } 
        else
        {
            Elemento<TL>* aux = pInicio;
            Elemento<TL>* aux2 = nullptr;
            for(int i = 0; i < pos; i++){
                aux2 = aux;
                aux = aux->getProx();
            }
            if(aux2 == nullptr){
                novoElemento->setProx(aux);
                pInicio = novoElemento;
            } else {
                aux2->setProx(novoElemento);
                novoElemento->setProx(aux);
            }
        }
        tam++;
    }

    /**
     * metodo que remove um elemento
     * 
     * parametros:
     * 
     * elemento:elemento a ser removido 
    */
    template<class TL>
    void Lista<TL>::removerElemento(TL* elemento)
    {
        if(elemento == nullptr){
            std::cout << "ERROR::Lista elemento eh nullptr" << std::endl;
            exit(1);
        }
        Elemento<TL>* aux = pInicio;
        Elemento<TL>* aux2 = nullptr;
        while (aux != nullptr && aux->getElemento() != elemento){
            aux2 = aux;
            aux = aux->getProx();
        }
        if(aux->getElemento() == elemento){
            if(aux == pInicio){
                pInicio = aux->getProx();
            } else if(aux == pUltimo){
                pUltimo = aux2;
            } else {
                aux2->setProx(aux->getProx());
            }
            delete aux;
            aux = nullptr;
            aux2 = nullptr;
            
            tam--;
        }
        
    }

        /**
     * metodo que remove um elemento
     * 
     * parametros:
     * 
     * pos:posicao do elemento a ser removido 
    */
    template<class TL>
    void Lista<TL>::removerElemento(int pos)
    {
        TL* elemento = operator[](pos);
        return removerElemento(elemento);
    }

    /**
     *metodo que retorna o tamanho da lista 
    */
    template<class TL>
    int Lista<TL>::getTam(){
        return tam;
    }

    /**
     * metodo que acessa e percorre a lista
     * com  a  vizualicao  de  um  vetor 
     * ex: minhaLista[1]
    */
    template<class TL>
    TL* Lista<TL>::operator[](int pos)
    {
        if(pos >= (int)tam || pos < 0){
            std::cout << "ERROR::Lista pos eh maior que o tamanho da lista" << std::endl;
            exit(1);
        }
        Elemento<TL>* aux = pInicio;
        for(int i = 0; i < pos; i++){
            aux = aux->getProx();
        }
        return aux->getElemento();
    }

    /**
     * metodo que zera a lista 
     * 
     * percorre a lista apagando todos os elementos 
    */
    template<class TL>
    void Lista<TL>::limparLista()
    {
        if(pInicio != nullptr)
        {
            Elemento<TL>* aux = pInicio;
            Elemento<TL>* aux2 = nullptr;
            unsigned int i = 0;
            while(aux != nullptr && i < tam)
            {
                if(TL* elemento = aux->getElemento(); elemento != nullptr)
                {
                    delete elemento;
                    elemento = nullptr;
                }

                aux2 = aux->getProx();
                delete aux;
                aux = nullptr;
                aux = aux2;
                i++;
            }
        }
        pInicio = nullptr;
        pUltimo = nullptr;
        this->tam = 0;
    }
}
