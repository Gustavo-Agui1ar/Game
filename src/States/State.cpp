
#include "../includes/States/State.h"

namespace  Game::State{
    
    State::State(IDs::IDs ID):
    Ente(ID)
    {
        m_remove = false;
    }

    State::~State() = default;

    void State::draw()
    {
        //draw
    }

    void State::setRemove()
    {
        m_remove = true;
    }
    
    const bool State::getRemove()
    {
        return m_remove;
    }
}
