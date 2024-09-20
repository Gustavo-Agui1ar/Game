
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

        static std::unordered_map<sf::Keyboard::Key, bool> keyStates;
        static std::unordered_map<sf::Mouse::Button, bool> mouseButtonStates;

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
                if (!keyStates[event.key.code]) // Somente processar se não estava pressionada antes
                {
                    keyStates[event.key.code] = true;
                    m_observerList->processKeyPressed(event.key.code);
                }
                break;
                
            case sf::Event::KeyReleased:
                if (keyStates[event.key.code]) // Somente processar se estava pressionada antes
                {
                    keyStates[event.key.code] = false;
                    m_observerList->processKeyRelease(event.key.code);
                }
                break;
                
            case sf::Event::MouseMoved:
                m_observerList->notifyMouseMovement(event.mouseMove);
                break;
                
            case sf::Event::MouseButtonReleased:
                if (mouseButtonStates[event.mouseButton.button]) // Somente processar se estava pressionado antes
                {
                    mouseButtonStates[event.mouseButton.button] = false;
                    m_observerList->notifyBottonMouseRelease(event.mouseButton.button);
                }
                break;
                
            case sf::Event::MouseButtonPressed:
                if (!mouseButtonStates[event.mouseButton.button]) // Somente processar se não estava pressionado antes
                {
                    mouseButtonStates[event.mouseButton.button] = true;
                }
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



