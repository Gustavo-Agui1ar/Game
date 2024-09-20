
#pragma once 

#include "Observer.h"

namespace Game{

    namespace Level{
        class Level;
    }

    namespace Observer{

        class ObserverLevel : public Observer{

        private:

            Level::Level* m_level;

        public:

            explicit ObserverLevel(Level::Level* level);
            ObserverLevel();
            ~ObserverLevel() override;

            void keyPressed(sf::Keyboard::Key key) override;
            void keyRelease(sf::Keyboard::Key key) override;
        
            void setLevel(Level::Level* level);
        
            void notifyGameOver();
            
        };
    }
}