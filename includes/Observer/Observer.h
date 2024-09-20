
#pragma once

#include "SFML/Graphics.hpp"
#include <map>

namespace Game{

    namespace Manager
    {
        class StateManager;
        class EventManager;
    }

    namespace Observer{
        class Observer{

            protected:

                static Manager::EventManager* m_eventManager;

                static Manager::StateManager* m_stateManager;

                std::map<sf::Keyboard::Key, char> m_defaultKeys;
                std::map<sf::Keyboard::Key, std::string> m_especialKeys;

            private:

                bool m_active;

                void bootKeyboardComands();

            public:

                Observer();
                virtual ~Observer();

                const bool getActive();
                void changeState(const bool ativo);

                void removeObserver();
                
                virtual void keyPressed(const sf::Keyboard::Key key) = 0;
                virtual void keyRelease(const sf::Keyboard::Key key) = 0;
                virtual void mouseMove(const sf::Vector2f posMouse);
                virtual void mouseButtonRelease(const sf::Mouse::Button mouseButton);
        
        };

    }
}