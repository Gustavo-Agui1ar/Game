#pragma once
namespace Game::List{
    template<class TE>
    class Element
    {      
    private:

        Element<TE>* m_next = nullptr;
        Element<TE>* m_prev = nullptr;
        TE* m_element = nullptr;

    public:
    
        Element();
        ~Element();
        
        void setNext(Element<TE>* next);
        void setPrev(Element<TE>* prev);
        void setElement(TE* element);
        
        Element<TE>* getNext();
        Element<TE>* getPrev();
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
    void Element<TE>::setPrev(Element<TE>* prev)
    {
        m_prev = prev;
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
    Element<TE>* Element<TE>::getPrev()
    {
        return m_prev;
    }

    template<class TE>
    TE* Element<TE>::getElement()
    {
        return m_element;
    }

}
