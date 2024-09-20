
#pragma once

#include "../Entity/Player/Player.h"
#include "Observer.h"

namespace Game::Observer{
    class ObserverPlayer : public Observer{

    private:
        
        Entity::Character::Player::Player* m_player;

    public:

        explicit ObserverPlayer(Entity::Character::Player::Player* player);
        ~ObserverPlayer() override;

        void keyPressed(const sf::Keyboard::Key key) override;
        void keyRelease(const sf::Keyboard::Key key) override;
        void mouseButtonRelease(const sf::Mouse::Button mouseButton) override;
    
    };
}