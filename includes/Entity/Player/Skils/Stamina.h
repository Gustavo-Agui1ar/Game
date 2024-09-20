#pragma once

#include <SFML/Graphics.hpp>
#include "../../../Manager/GraphicManager.h"
#include "json.hpp"

#define MAX_STAMINA 100.0f
#define TIME_REGENERATION_STAMINA 1.5f
#define QTD_REGERENATE 0.05f

namespace Game::Entity::Character::Player{
    
    class Player;

    namespace Skils {

        class Stamina {

        private:

            Manager::GraphicManager* m_graphic;
            Player* m_player;
           
            bool  m_canRegenarateStamina;
            float m_timeRegenerationStamina;                
            float m_stamina;
            sf::RectangleShape m_staminaBar;

        public:

            explicit Stamina(Player* player);
            ~Stamina();

            bool consumeStamina(float staminaQtd);
            void updateStaminaRegeneration();
            void updateStaminaBar();
            void bootStaminaBar();
            
            float getTimeRegenerationStamina();                
            bool getCanRegenarateStamina();
            void drawStaminaBar();
            float getStamina();
                
            void setTimeRegenerationStamina(float timeRegeneration);                
            void setCanRegenarateStamina(bool canRegenerate);
            void setStamina(float stamina);

            nlohmann::ordered_json saveStamina(nlohmann::ordered_json json);
        };
    }
}