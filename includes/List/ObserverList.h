
#pragma once

#include "List.h"
#include "../Observer/Observer.h"
#include "../Manager/GraphicManager.h"
#include "SFML/Graphics.hpp"

namespace Game::List{
    class ObserverList {

    private:

        List<Observer::Observer> m_observerList;

    public:

        ObserverList();
        ~ObserverList();

        void add(Observer::Observer* listener);

        void remove(Observer::Observer* listener);
        void remove(int pos);
        
        Observer::Observer* operator[](int pos);
        
        int getSize();

        void processKeyPressed(const sf::Keyboard::Key key);
        void processKeyRelease(const sf::Keyboard::Key key);
        
        void notifyBottonMouseRelease(const sf::Mouse::Button mouseBotton);
        void notifyBottonMousePressed(const sf::Mouse::Button mouseBotton);
        void notifyMouseMovement(const sf::Event::MouseMoveEvent mouse);

    };
}