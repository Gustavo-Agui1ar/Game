
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
            for(int i = 0 ; i < m_observerList.getSize() ; i++)
            {
                Observer::Observer* observer = m_observerList.operator[](i);
                
                if(observer->getActive())
                {
                    observer->keyRelease(key);
                }

                observer = nullptr;
            }
        }

         void ObserverList::notifyMouseMovement(const sf::Event::MouseMoveEvent mouse)
         {
            auto posMouse = sf::Vector2f((float)mouse.x, (float)mouse.y);
            for(int i = 0; i < m_observerList.getSize(); i++)
            {
                Observer::Observer* observer = m_observerList.operator[](i);
                if(observer->getActive())
                {
                    observer->mouseMove(posMouse);
                }
                observer = nullptr;
            }
        }
        
        void ObserverList::notifyBottonMouseRelease(const sf::Mouse::Button mouseBotton)
        {
            for(int i = 0; i < m_observerList.getSize(); i++)
            {
                Observer::Observer* observer = m_observerList.operator[](i);
                if(observer->getActive())
                {
                    observer->mouseButtonRelease(mouseBotton);
                }
                observer = nullptr;
            }
        }
}