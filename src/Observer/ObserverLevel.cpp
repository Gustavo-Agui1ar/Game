
#include "../includes/Manager/EventManager.h"
#include "../includes/Manager/StateManager.h"
#include "../includes/Observer/ObserverLevel.h"
#include "../includes/Levels/Level.h"

namespace Game::Observer{

        ObserverLevel::ObserverLevel():
        Observer(), m_level(nullptr){}
       
        ObserverLevel::ObserverLevel(Level::Level* level):
        Observer(), m_level(level){}

        ObserverLevel::~ObserverLevel() = default;

        void ObserverLevel::notifyGameOver()
        {
            m_stateManager->addState(IDs::IDs::game_over_menu);
        }        

        void ObserverLevel::keyPressed(sf::Keyboard::Key tecla)
        {
            //empty method
        }

        void ObserverLevel::keyRelease(sf::Keyboard::Key tecla)
        {
            if(m_especialKeys[tecla] == "Escape")
            {
                m_stateManager->addState(IDs::IDs::pause_menu);
            }
        }

        void ObserverLevel::setLevel(Level::Level* level)
        {
            m_level = level;
        }

}