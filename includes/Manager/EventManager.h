
#pragma once

#include "../Manager/StateManager.h"
#include "../Manager/GraphicManager.h"
#include "../List/ObserverList.h"
#include <iostream>
#include <unordered_set>


namespace Game::Manager{
    class EventManager{

    private:

        GraphicManager *m_graphicManager;
        StateManager* m_stateManager;   

        static List::ObserverList* m_observerList;
        static EventManager *m_eventManager;
        EventManager();

    public:

        ~EventManager();
        
        static EventManager* getEventManager();

        void removeObserver(Observer::Observer* observer);
        void addObserver(Observer::Observer* observer);
        
        void execute();
    };
}
