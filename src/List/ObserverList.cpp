
#include "../../includes/List/ObserverList.h"

namespace Game::List{

        ObserverList::ObserverList():
        m_observerList()
        {

        }

        ObserverList::~ObserverList()
        {
            m_observerList.clearList();
        }

        void ObserverList::add(Observer::Observer* observer)
        {
            m_observerList.add(observer);
        }

        void ObserverList::remove(Observer::Observer* observer)
        {
            m_observerList.remove(observer);
        }

        void ObserverList::remove(int pos)
        {
            m_observerList.remove(pos);
        }

        int ObserverList::getSize()
        {
            return m_observerList.getSize();
        }

        Observer::Observer* ObserverList::operator[](int pos)
        {
            return m_observerList.operator[](pos);    
        }

        void ObserverList::processKeyPressed(sf::Keyboard::Key key)
        {
                int const size = m_observerList.getSize();
                for(int i = 0 ; i < size ; i++)
                {
                    Observer::Observer* observer = m_observerList.operator[](i);
                    
                    if(observer->getActive())
                    {
                        observer->keyPressed(key);
                    }

                    observer = nullptr;
                }
        }

        void ObserverList::processKeyRelease(sf::Keyboard::Key key)
        {
            for(auto it = m_observerList.begin(); it != m_observerList.end(); it++)
            {
                if((*it)->getActive())
                {
                    (*it)->keyRelease(key);
                }
            }
        }

         void ObserverList::notifyMouseMovement(const sf::Event::MouseMoveEvent mouse)
         {
            auto posMouse = sf::Vector2f((float)mouse.x, (float)mouse.y);
            for(auto it = m_observerList.begin(); it != m_observerList.end(); it++)
            {
                if((*it)->getActive())
                {
                    (*it)->mouseMove(posMouse);
                }
            }
        }
        
        void ObserverList::notifyBottonMouseRelease(const sf::Mouse::Button mouseButton)
        {
            int const size = m_observerList.getSize();
            for(int i = 0 ; i < size ; i++) {
                Observer::Observer* observer = m_observerList.operator[](i);
                if(observer->getActive())
                {
                    observer->mouseButtonRelease(mouseButton);
                }
                observer = nullptr;
            }
        }
      
        void ObserverList::notifyBottonMousePressed(const sf::Mouse::Button mouseButton)
        {
            int const size = m_observerList.getSize();
            for(int i = 0 ; i < size ; i++) {
                Observer::Observer* observer = m_observerList.operator[](i);
                if(observer->getActive())
                {
                    observer->mouseButtonPressed(mouseButton);
                }
                observer = nullptr;
            }
        }
}