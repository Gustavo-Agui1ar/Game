
#include "../includes/Observer/ObserverPlayer.h"
#include "../includes/Manager/FileManager.h"

namespace Game::Observer{

    ObserverPlayer::ObserverPlayer(Entity::Character::Player::Player* player):
    Observer()
    {
        m_player = player;
    }

    ObserverPlayer::~ObserverPlayer() = default;

    void ObserverPlayer::keyPressed(sf::Keyboard::Key key)
    {
        if(!m_player->getDie())
        {
            switch (m_defaultKeys[key])
            {
                case 'a':
                    m_player->walk(true);
                    break;
                case 'd':
                    m_player->walk(false);
                    break;
                case 'w':
                    m_player->jump();
                    break;
                case 'k':
                    if(m_player->getOnFloor())
                        m_player->attack();
                    break;
                case 'j':
                    m_player->doDash();
                    break;
                case 'q':
                    m_player->activeRage();
                    break;
                case 'l':
                    m_player->trhowBullet();
                    break;
                default:
                    break;
            }
        }
    }

    void ObserverPlayer:: keyRelease(sf::Keyboard::Key key)
    {
        if(!m_player->getDie())
        {
            if(m_defaultKeys[key] == 'a' || m_defaultKeys[key] == 'd')
                m_player->stop();
            else if(m_defaultKeys[key] == 'w' || m_defaultKeys[key] == 'k')
                m_player->stopAttack();
            else if(m_defaultKeys[key] == 'j')
                m_player->stopDash();
            else if(m_defaultKeys[key] == 'r')
                m_player->searchIteractions();
        }
    }

    void ObserverPlayer::mouseButtonRelease(const sf::Mouse::Button botaoMouse)
    {
        if(botaoMouse == sf::Mouse::Button::Left)
            m_player->attack();
        else if(botaoMouse == sf::Mouse::Button::Right)
            m_player->trhowBullet();
    }
}