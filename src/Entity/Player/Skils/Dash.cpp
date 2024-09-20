#include "../includes/Entity/Player/Skils/Dash.h"
#include "../includes/Entity/Player/Player.h"

namespace Game::Entity::Character::Player::Skils{

    Dash::Dash(Player* player) : m_graphic(Manager::GraphicManager::getGraphicManager()),
    m_player(player), m_dashTimeAnimation(TIME_DASH), m_dashSpeed(SPEED_DASH_PLAYER),
    m_timeDash(0.0f), m_canDash(false), m_inDash(false)
    {
       
    }
    Dash::~Dash() {
        m_player = nullptr;
        m_graphic = nullptr;
    }

    void Dash::doDash() {
        if(m_timeDash == 0.0f && m_player->consumeStamina(MAX_STAMINA / 3.0f))
            m_canDash = true;
    }

    void Dash::stopDash() {
        m_inDash = false;
        m_canDash = false;
        m_timeDash = 0.0f;
    }

    void Dash::updateDash() {
        sf::Vector2f ds(0.0f, 0.0f);
        sf::Vector2f pos = m_player->getPosition();
        float dtAux = m_graphic->getTime();

        if (m_canDash && !m_player->getDie())
        {
            if (m_timeDash <= m_dashTimeAnimation)
            {
                m_inDash = true;
                m_timeDash += dtAux;

                ds.x = m_dashSpeed * dtAux;
                if (m_player->getDirection())
                    ds.x *= -1;

                m_player->setPosition(sf::Vector2f(pos.x + ds.x, pos.y));
            }
            else
                m_inDash = false;
        }
    }

    void Dash::setInDash(bool inDash) {
        m_inDash = inDash;
    }

    void Dash::setCanDash(bool canDash) {
        m_canDash = canDash;
    }

    void Dash::setTimeDash(float timeDash) {
        m_timeDash = timeDash;
    }
    
    bool Dash::getInDash() {
        return m_inDash;
    } 

    bool Dash::getCanDash() {
        return m_canDash;
    }
    float Dash::getTimeDash() {
        return m_timeDash;
    }

    const float Dash::getDashSpeed() {
        return m_dashSpeed;
    }

    nlohmann::ordered_json Dash::saveDash(nlohmann::ordered_json json) {
        json["inDash"] = getInDash();
        json["timeDash"] = getTimeDash();
        json["canDash"] = getCanDash();
        json["dashSpeed"] = getDashSpeed();
        return json;
    }
}