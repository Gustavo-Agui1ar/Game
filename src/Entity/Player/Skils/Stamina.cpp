#include "../includes/Entity/Player/Skils/Stamina.h"
#include "../includes/Entity/Player/Player.h"

namespace Game::Entity::Character::Player::Skils{

        Stamina::Stamina(Player* player) : m_graphic(Gerenciador::GerenciadorGrafico::getGerenciadorGrafico()), m_player(player), m_canRegenarateStamina(false), 
        m_timeRegenerationStamina(0.0f), m_stamina(MAX_STAMINA) {
            bootStaminaBar();
        } 

        Stamina::~Stamina() {
            m_player = nullptr;
            m_graphic = nullptr; 
        }

        void Stamina::bootStaminaBar() {
            auto stamina = sf::Vector2f(PLAYER_LIFE_BAR_X, PLAYER_LIFE_BAR_Y / 2.0f);
            m_staminaBar.setSize(stamina);
            auto *staminaTexture = new sf::Texture();
            staminaTexture->loadFromFile("animations/Characters/Life/BarraEnergia.png");
             m_staminaBar.setTexture(staminaTexture);
        }

        void Stamina::updateStaminaRegeneration() {
            if (m_stamina != MAX_STAMINA) {
                if (m_canRegenarateStamina) {
                    if (m_stamina + QTD_REGERENATE <= MAX_STAMINA)
                        m_stamina += QTD_REGERENATE;
                    else
                        m_canRegenarateStamina = false;
                }
                else {
                    m_timeRegenerationStamina += m_graphic->getTempo();

                    if (m_timeRegenerationStamina >= TIME_REGENERATION_STAMINA) {
                        m_canRegenarateStamina = true;
                        m_timeRegenerationStamina = 0.0f;
                    }
                }
            }
        }

        void Stamina::updateStaminaBar() {
            updateStaminaRegeneration();
            sf::Vector2f screenPosition = m_graphic->getCamera().getCenter();
            sf::Vector2f screenSize = m_graphic->getTamJanela();

            auto barPosition = sf::Vector2f(screenPosition.x - screenSize.x / 2.0f + 10.0f, 60.0f);
            m_staminaBar.setSize(sf::Vector2f((PLAYER_LIFE_BAR_X - 30.0f) * (m_stamina / MAX_STAMINA), PLAYER_LIFE_BAR_Y - 13.0f));
            m_staminaBar.setPosition(sf::Vector2f(barPosition.x + 7.0f, barPosition.y - m_staminaBar.getSize().y / 2.0f));
        }
        
        bool Stamina::consumeStamina(float staminaQtd) {
            if (m_stamina - staminaQtd >= 0) {
                m_stamina -= staminaQtd;
                m_canRegenarateStamina = false;
                return true;
            }
            return false;
        }

        bool Stamina::getCanRegenarateStamina() {
            return m_canRegenarateStamina;
        }
            
        float Stamina::getTimeRegenerationStamina() {
            return m_timeRegenerationStamina;
        }       

        float Stamina::getStamina() {
            return m_stamina;
        }
        
                
        void Stamina::setCanRegenarateStamina(bool canRegenerate) {
            m_canRegenarateStamina = canRegenerate;
        }

        void Stamina::setTimeRegenerationStamina(float timeRegeneration) {
            m_timeRegenerationStamina = timeRegeneration;
        }   

        void Stamina::setStamina(float stamina) {
            m_stamina = stamina;
        }

        void Stamina::drawStaminaBar() {
            m_graphic->desenhaElemento(m_staminaBar);
        }

        nlohmann::ordered_json Stamina::saveStamina(nlohmann::ordered_json json) {
            json["stamina"] = getStamina();
            return json;
        }
}