#include "../includes/Entity/Player/Skils/Rage.h"
#include "../includes/Entity/Player/Player.h"

namespace Game::Entity::Character::Player::Skils {

    Rage::Rage(Player* player): m_graphic(Gerenciador::GerenciadorGrafico::getGerenciadorGrafico()),m_player(player), m_rageTimeAnimation(TIME_RAGE_PLAYER), 
    m_timeStartingRage(0.0f), m_startingRage(false), m_inRage(false), m_rage(100.f)   
    {
        bootRageBar();
    }
    
    Rage::~Rage() = default;

    void Rage::bootRageBar() {
        
        auto rageSize = sf::Vector2f(m_rage, RAGE_BAR_PLAYER_Y / 2.0f);
        m_rageBar.setSize(rageSize);
        auto *rageTexture = new sf::Texture();
        rageTexture->loadFromFile("animations/Characters/Life/BarraEnergia.png");
        m_rageBar.setTexture(rageTexture);
        m_rageBar.setFillColor(sf::Color::Magenta);
    }

    void Rage::updateRageBar() {
         if (m_inRage)
            consumeRage();

        sf::Vector2f screenPos = m_graphic->getCamera().getCenter();
        sf::Vector2f screenSize = m_graphic->getTamJanela();

        auto barPosition = sf::Vector2f(screenPos.x - screenSize.x / 2.0f + 10.0f, 80.0f);
        m_rageBar.setSize(sf::Vector2f((RAGE_BAR_PLAYER_X - 30.0f) * (m_rage / MAX_RAGE), RAGE_BAR_PLAYER_Y - 13.0f));
        m_rageBar.setPosition(sf::Vector2f(barPosition.x + 7.0f, barPosition.y - m_rageBar.getSize().y / 2.0f));
    }
    
    bool Rage::consumeRage() {
        if (m_rage - RAGE_CONSUME >= 0)
        {
            m_rage -= RAGE_CONSUME;
            return true;
        }
        else
        {
            m_player->setWeaponDamage(DEFAULT_DAMAGE_PLAYER);
            m_inRage = false;
            return false;
        }
    }

    const float Rage::getRageTimeAnimation() {
        return m_rageTimeAnimation;
    }

    float Rage::getTimeStartingRage() {
        return m_timeStartingRage;
    }
    bool Rage::getStartingRage() {
        return m_startingRage;
    }
    bool Rage::getInRage() {
        return m_inRage;
    }
    float Rage::getRage() {
        return m_rage;
    }

    void Rage::drawRageBar(){
        m_graphic->desenhaElemento(m_rageBar);
    }

    void Rage::startRage() {
        if (m_rage == MAX_RAGE && !m_startingRage && !m_player->getDie())
        {
            m_player->setWeaponDamage(DEFAULT_DAMAGE_PLAYER * 2);
            m_startingRage = true;
        }
    }

    void Rage::increaseRage(float rageQtd){
        
        if (m_rage + rageQtd <= MAX_RAGE)
        {
            m_rage += rageQtd;
        }
    } 

    void Rage::updateStartingRage() {
        m_timeStartingRage += m_graphic->getTempo();
        m_player->setMoving(false);

        if (m_timeStartingRage > m_rageTimeAnimation)
        {
            m_inRage = true;
            m_startingRage = false;
            m_timeStartingRage = 0.0f;
        }
    }

    void Rage::setRage(float rage) {
        m_rage = rage;
    }
    
    void Rage::setInRage(bool inRage) {
        m_inRage = inRage;
    }

    void Rage::setStartingRage(bool startingRage) {
        m_startingRage = startingRage;
    }

    nlohmann::ordered_json Rage::saveRage(nlohmann::ordered_json json) {
        json["rage"] = getRage();
        json["inRage"] = getInRage();
        json["startingRage"] = getStartingRage();
        json["timeStartingRage"] = getTimeStartingRage();
        return json;
    }
}