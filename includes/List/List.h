
#pragma once

#include "../List/Element.h"
#include <iostream>

namespace Game::List{
    template<class TL>
    class List
    {
        
    private:

        Element<TL>* m_begin = nullptr;
        Element<TL>* m_end = nullptr;
        unsigned int m_size = 0;
    
    public:
    
        List();
        ~List();
        
        void add(TL* element, int pos);
        void add(TL* element);
        
        void remove(TL* element);
        void remove(int pos);
        
        TL* operator[](int pos);
        int getSize();
        TL* getEnd();
        TL* getBegin();
        
        void clearList();
    };

    template<class TL>
    List<TL>::List() = default;

    template<class TL>
    List<TL>::~List() = default;

    template<class TL>
    void List<TL>::add(TL* element)
    {
        if(element == nullptr){
            std::cout << "ERROR::List element is null" << std::endl;
            exit(1);
        }
        auto *newElement = new Element<TL>();
        if(newElement == nullptr){
            std::cout << "ERROR::List element is null" << std::endl;
            exit(1);
        }
        newElement->setElement(element);
        if(m_begin == nullptr){
            m_begin = newElement;
            m_end = newElement;
        } else {
            m_end->setNext(newElement);
            m_end = newElement;
        }
        m_size++;
    }

    template<class TL>
    void List<TL>::add(TL* element, int pos)
    {
        if(pos > (int)m_size || pos < 0){
            std::cout << "ERRO::List the position is larger than the size list" << std::endl;
            exit(1);
        }
        if(element == nullptr){
            std::cout << "ERROR::List element is null" << std::endl;
            exit(1);
        }
        auto *newElement = new Element<TL>();
        if(newElement == nullptr){
            std::cout << "ERROR::List new element is null" << std::endl;
            exit(1);
        }
        newElement->setElement(element);
        if(m_begin == nullptr){
            m_begin = newElement;
            m_end = newElement;
        } 
        else
        {
            Element<TL>* current = m_begin;
            Element<TL>* previous = nullptr;
            for(int i = 0; i < pos; i++){
                previous = current;
                current = current->getNext();
            }
            if(previous == nullptr){
                newElement->setNext(current);
                m_begin = newElement;
            } else {
                previous->setNext(newElement);
                newElement->setNext(current);
            }
        }
        m_size++;
    }

    template<class TL>
    void List<TL>::remove(TL* element)
    {
        if(element == nullptr){
            std::cout << "ERROR::List element is null" << std::endl;
            exit(1);
        }
        Element<TL>* current = m_begin;
        Element<TL>* previous = nullptr;
        while (current != nullptr && current->getElement() != element){
            previous = current;
            current = current->getNext();
        }
        if(current->getElement() == element){
            if(current == m_begin){
                m_begin = current->getNext();
            } else if(current == m_end){
                m_end = previous;
            } else {
                previous->setNext(current->getNext());
            }
            delete current;
            current = nullptr;
            previous = nullptr;
            
            m_size--;
        }
        
    }

    template<class TL>
    void List<TL>::remove(int pos)
    {
        TL* element = operator[](pos);
        return remove(element);
    }

    template<class TL>
    int List<TL>::getSize(){
        return m_size;
    }

    template<class TL>
    TL* List<TL>::operator[](int pos)
    {
        if(pos >= (int)m_size || pos < 0){
            std::cout << "ERROR::List the position is larger than the size list" << std::endl;
            exit(1);
        }
        Element<TL>* currentPos = m_begin;
        for(int i = 0; i < pos; i++){
            currentPos = currentPos->getNext();
        }
        return currentPos->getElement();
    }

    template<class TL>
    void List<TL>::clearList()
    {
        if(m_begin != nullptr)
        {
            Element<TL>* current = m_begin;
            Element<TL>* previous = nullptr;
            unsigned int i = 0;
            while(current != nullptr && i < m_size)
            {
                if(TL* element = current->getElement(); element != nullptr)
                {
                    delete element;
                    element = nullptr;
                }

                previous = current->getNext();
                delete current;
                current = nullptr;
                current = previous;
                i++;
            }
        }
        m_begin = nullptr;
        m_end = nullptr;
        this->m_size = 0;
    }

    template<class TL>
    TL* List<TL>::getEnd()
    {
        return m_end->getElement();
    }

    template<class TL>
    TL* List<TL>::getBegin()
    {
        return m_begin->getElement();
    }
}
