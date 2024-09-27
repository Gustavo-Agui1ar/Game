
#include "../includes/Manager/EventManager.h"
#include "../includes/Manager/StateManager.h"
#include <iostream>

namespace Game::Manager{

    EventManager* EventManager::m_eventManager = nullptr;
    List::ObserverList* EventManager::m_observerList = nullptr;

    EventManager::EventManager():
    m_graphicManager(Manager::GraphicManager::getGraphicManager()),
    m_stateManager(Manager::StateManager::getStateManager())
    {
        m_observerList = new List::ObserverList();
    }

    EventManager::~EventManager()
    {
        if(m_stateManager != nullptr)
            delete m_stateManager;
        m_eventManager = nullptr;
    }

    EventManager* EventManager::getEventManager()
    {
        if(m_eventManager == nullptr)
        {
            m_eventManager =  new EventManager();
        }
        return m_eventManager;
    }

    void EventManager::execute()
    {
        sf::Event event;

        while(m_graphicManager->getWindow()->pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::LostFocus:
            {
                auto ID = static_cast<int>(m_stateManager->getCurrentState()->getID());
                if(ID >= 14 && ID <= 16)
                    m_stateManager->addState(IDs::IDs::pause_menu);
            }
                break;
                
            case sf::Event::KeyPressed:
                    m_observerList->processKeyPressed(event.key.code);
                break;
                
            case sf::Event::KeyReleased:
                    m_observerList->processKeyRelease(event.key.code);
                break;
                
            case sf::Event::MouseMoved:
                m_observerList->notifyMouseMovement(event.mouseMove);
                break;
                
            case sf::Event::MouseButtonReleased:
                    m_observerList->notifyBottonMouseRelease(event.mouseButton.button);
                break;
            case sf::Event::MouseButtonPressed:
                    m_observerList->notifyBottonMousePressed(event.mouseButton.button);
                break;
                
            case sf::Event::Closed:
                m_graphicManager->closeWindow();
                break;
                
            default:
                break;
        }
    }

    }

    void EventManager::addObserver(Observer::Observer* observer)
    {
        m_observerList->add(observer);
    }

    void EventManager::removeObserver(Observer::Observer* observer)
    {
        m_observerList->remove(observer);
    }
}



