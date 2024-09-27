#pragma once

#include "../List/Element.h"
#include <iostream>
#include <stdexcept>

namespace Game::List {
    template<class TL>
    class List {
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

        void clearList();

        class Iterator {
        private:
            Element<TL>* m_current; // Ponteiro para o elemento atual
        public:
            explicit Iterator(Element<TL>* element) : m_current(element) {}

            Iterator& operator++() {
                if (m_current != nullptr) {
                    m_current = m_current->getNext();
                }
                return *this;
            }

            Iterator operator++(int) {
                Iterator temp = *this;
                if (m_current != nullptr) {
                    m_current = m_current->getNext();
                }
                return temp;
            }

            Iterator& operator--() {
                if (m_current != nullptr) {
                    m_current = m_current->getPrev();
                }
                return *this;
            }

            Iterator operator--(int) {
                Iterator temp = *this;
                if (m_current != nullptr) {
                    m_current = m_current->getPrev();
                }
                return temp;
            }

            friend bool operator!=(const Iterator& it, const Iterator& other) {
                return !(it.m_current == other.m_current);
            }

            TL* operator*() const {
                return m_current->getElement();
            }
        };

        Iterator begin() const {
            return Iterator(m_begin);
        }

        Iterator end() const {
            return Iterator(nullptr);
        }
    };

    template<class TL>
    List<TL>::List() = default;

    template<class TL>
    List<TL>::~List() {
        clearList();
    }

    template<class TL>
    void List<TL>::add(TL* element) {
        if (element == nullptr) {
            throw std::invalid_argument("ERROR::List element is null");
        }

        auto* newElement = new Element<TL>();
        newElement->setElement(element);
        if (m_begin == nullptr) {
            m_begin = newElement;
            m_end = newElement;
        } else {
            m_end->setNext(newElement);
            newElement->setPrev(m_end);
            m_end = newElement;
        }
        m_size++;
    }

    template<class TL>
    void List<TL>::add(TL* element, int pos) {
        if (pos > static_cast<int>(m_size) || pos < 0) {
            throw std::out_of_range("ERROR::List the position is out of range");
        }
        if (element == nullptr) {
            throw std::invalid_argument("ERROR::List element is null");
        }

        auto* newElement = new Element<TL>();
        newElement->setElement(element);
        if (m_begin == nullptr) {
            m_begin = newElement;
            m_end = newElement;
        } else {
            Element<TL>* current = m_begin;
            for (int i = 0; i < pos; i++) {
                current = current->getNext();
            }
            if (current->getPrev() == nullptr) {
                newElement->setNext(current);
                m_begin = newElement;
            } else {
                newElement->setPrev(current->getPrev());
                current->getPrev()->setNext(newElement);
                newElement->setNext(current);
                current->setPrev(newElement);
            }
        }
        m_size++;
    }

    template<class TL>
    void List<TL>::remove(TL* element) {
        if (element == nullptr) {
            throw std::invalid_argument("ERROR::List element is null");
        }
        Element<TL>* current = m_begin;
        while (current != nullptr && current->getElement() != element) {
            current = current->getNext();
        }
        if (current != nullptr && current->getElement() == element) {
            if (current == m_begin) {
                m_begin = current->getNext();
                if (m_begin != nullptr) {
                    m_begin->setPrev(nullptr);
                }
            } else if (current == m_end) {
                m_end = current->getPrev();
                if (m_end != nullptr) {
                    m_end->setNext(nullptr);
                }
            } else {
                current->getPrev()->setNext(current->getNext());
                current->getNext()->setPrev(current->getPrev());
            }
            delete current;
            m_size--;
        }
    }

    template<class TL>
    void List<TL>::remove(int pos) {
        TL* element = operator[](pos);
        remove(element);
    }

    template<class TL>
    int List<TL>::getSize() {
        return m_size;
    }

    template<class TL>
    TL* List<TL>::operator[](int pos) {
        if (pos > static_cast<int>(m_size) || pos < 0) {
            throw std::out_of_range("ERROR::List the position is out of range");
        }
        Element<TL>* currentPos = m_begin;
        for (int i = 0; i < pos; i++) {
            currentPos = currentPos->getNext();
        }
        return currentPos->getElement();
    }

    template<class TL>
    void List<TL>::clearList() {
        Element<TL>* current = m_begin;
        while (current != nullptr) {
            Element<TL>* next = current->getNext();
            delete current;
            current = next;
        }
        m_begin = nullptr;
        m_end = nullptr;
        m_size = 0;
    }
}