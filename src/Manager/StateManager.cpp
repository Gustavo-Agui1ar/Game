
#include "../includes/Manager/StateManager.h"


namespace Game::Manager{


        StateManager* StateManager::m_stateManager = nullptr;
        MusicManager* StateManager::m_musicManager = MusicManager::getMusicManager();

        StateManager::StateManager():
        m_stackState()
        {

        }

    StateManager* StateManager::getStateManager()
    {
        if(m_stateManager == nullptr)
            m_stateManager = new StateManager();
        return m_stateManager;
    }

    StateManager::~StateManager()
    {
        if(m_musicManager != nullptr)
            delete m_musicManager;
        
        m_musicManager = nullptr;

        while(!m_stackState.empty())
        {
            delete(m_stackState.top());
            m_stackState.top() = nullptr;
            m_stackState.pop();
        }

        if(m_stateManager){
            m_stateManager = nullptr;
        }
    }

    void StateManager::addState(IDs::IDs ID)
    {
        State::State* estado = nullptr;

        if(auto numID = static_cast<int>(ID); numID >= 14 && numID <= 16)
        {
            estado = static_cast<State::State*>(new State::LevelState(ID));
        }
        else if(numID >= 40 && numID <= 47)
        {
            auto* mEstado = new State::MenuState(ID);
            estado = static_cast<State::State*>(mEstado);
        }
        else if(ID == IDs::IDs::dialogue_estate)
        {
            State::State* estadoAtual = getCurrentState();

            auto* eFase = static_cast<State::LevelState*>(estadoAtual);
            auto* mEstado = new State::DialogueState(ID);

            mEstado->setFase(eFase->getLevel());

            estado = static_cast<State::State*>(mEstado);
        }

        if(estado == nullptr)
        {
            std::cout << ":Gerenciador::GerenciadorEstado::estado nulo" << std::endl;
            exit(1);
        }
        if(!m_stackState.empty())
            deactivateObserver();
        
        m_musicManager->changeMusic(ID);
        m_stackState.push(estado);
    }

    void StateManager::removeState()
    {
        if(m_stackState.top() != nullptr && !m_stackState.empty())
        {
            delete(m_stackState.top());
            m_stackState.top() = nullptr;
            m_stackState.pop();
        }

        if(!m_stackState.empty())
        {
            m_musicManager->changeMusic(m_stackState.top()->getID());
            activateObserver();
        }
        else
        {
            auto* m_pGrafic = Manager::GraphicManager::getGraphicManager();
            m_pGrafic->closeWindow();
        }
    }

    void StateManager::activateObserver()
    {
        State::State* estadoAtual = getCurrentState();

        estadoAtual->changeEstateObserver(true);
    }

    void StateManager::deactivateObserver()
    {
        State::State* estadoAtual = getCurrentState();

        estadoAtual->changeEstateObserver(false);
    }

    State::State* StateManager::getCurrentState()
    {
        if(!m_stackState.empty())
        {
            return m_stackState.top();
        }
        return nullptr;
    }

    State::State* StateManager::getState(int qtd)
    {
        std::stack<State::State*> pilhaAux = m_stackState;

        int i = 0;

        while( i  < qtd && !pilhaAux.empty())
        {
            pilhaAux.pop();
            i++;
        }

        if(!pilhaAux.empty())
            return pilhaAux.top();
        
        return nullptr;
    }

    void StateManager::execute()
    {
        if(!m_stackState.empty())
        {
            State::State* estado = m_stackState.top();
            estado->execute();
        }
    }

    void StateManager::removeState(const int quantidade)
    {
        int i = 0;
        while(!m_stackState.empty() && i < quantidade)
        {
            if(State::State* estado = m_stackState.top(); estado != nullptr){
                delete estado;
                estado = nullptr; 
            }
            m_stackState.pop();
            i++;
        }
        if(!m_stackState.empty())
        {
            m_musicManager->changeMusic(m_stackState.top()->getID());
            activateObserver();
        } 
        else 
        {
            auto* pGrafico = Manager::GraphicManager::getGraphicManager();
            pGrafico->closeWindow();
        }
    }
}
