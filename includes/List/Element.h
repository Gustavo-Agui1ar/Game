#pragma once
namespace Game::List{
    template<class TE>
    class Element
    {      
    private:

        Element<TE>* m_next = nullptr;
        TE* m_element = nullptr;

    public:
    
        Element();
        ~Element();
        
        void setNext(Element<TE>* next);
        void setElement(TE* element);
        
        Element<TE>* getNext();
        TE* getElement();
    };
    
    template<class TE>
    Element<TE>::Element() = default;
    
    template<class TE>
    Element<TE>::~Element() = default;

    template<class TE>
    void Element<TE>::setNext(Element<TE>* next)
    {
        m_next = next;
    }

    template<class TE>
    void Element<TE>::setElement(TE* element)
    {
        m_element = element;
    }

    template<class TE>
    Element<TE>* Element<TE>::getNext()
    {
        return m_next;
    }

    template<class TE>
    TE* Element<TE>::getElement()
    {
        return m_element;
    }

}
