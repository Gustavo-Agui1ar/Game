
#pragma once

namespace Game::Lista{
    template<class TE>
    class Elemento
    {
        
    private:

        //atributos de lista
        Elemento<TE>* m_next = nullptr;

        TE* m_element = nullptr;

    public:
    
        //construtora e destrutora

        Elemento();
        ~Elemento();
        
        //metodos seters

        void setProx(Elemento<TE>* next);
        void setElemento(TE* element);
        
        //metodos geters

        Elemento<TE>* getProx();
        TE* getElemento();
    };
    
    /**
     * construtora da classe
    */
    template<class TE>
    Elemento<TE>::Elemento() = default;
    
    /**
     * destrutora da classe
    */
    template<class TE>
    Elemento<TE>::~Elemento() = default;

    /**
     * metodo que seta o apontamento do proximo elemento
     * 
     * parametros:
     * 
     * prox: elemento a ser setado
    */
    template<class TE>
    void Elemento<TE>::setProx(Elemento<TE>* next)
    {
        m_next = next;
    }

    /**
     * metodo que seta o apontamento do elemento
     * 
     * parametros:
     * 
     * elemento : elemento a ser setado
    */
    template<class TE>
    void Elemento<TE>::setElemento(TE* element)
    {
        m_element = element;
    }

    /**
     * metodo que retorna o proximo
    */
    template<class TE>
    Elemento<TE>* Elemento<TE>::getProx()
    {
        return m_next;
    }

    /**
     * metodo que retorna o elemento
    */
    template<class TE>
    TE* Elemento<TE>::getElemento()
    {
        return m_element;
    }

}
