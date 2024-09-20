
#pragma once

#include "../States/LevelState.h"
#include "../States/MenuState.h"
#include "../States/DialogueState.h"
#include "MusicMAnager.h"
#include <stack>


namespace Game::Manager{
    class StateManager{

    private:

        
        std::stack<State::State*> m_stackState;
        
        StateManager();

        static StateManager* m_stateManager;
        static MusicManager* m_musicManager;

    public:
        
        ~StateManager();
        
        static StateManager* getStateManager();
        
        void deactivateObserver();
        void activateObserver();

        void execute();
        
        void addState(const IDs::IDs ID);
        void removeState();
        
        State::State* getCurrentState();
        State::State* getState(int qtd);
        void removeState(const int qtdStates);

    };

}
