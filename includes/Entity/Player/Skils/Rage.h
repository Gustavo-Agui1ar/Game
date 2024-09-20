#pragma once

#include <SFML/Graphics.hpp>
#include "../../../Manager/GraphicManager.h"
#include "json.hpp"

#define TIME_RAGE_PLAYER 1.2f
#define DEFAULT_DAMAGE_PLAYER 20.0f
#define RAGE_BAR_PLAYER_Y 20.0f
#define RAGE_BAR_PLAYER_X 350.0f
#define MAX_RAGE 100.0f
#define RAGE_CONSUME 0.01f

namespace Game::Entity::Character::Player{
    
    class Player;

    namespace Skils {

        class Rage {

        private:

            Manager::GraphicManager* m_graphic;
            Player* m_player;
            sf::RectangleShape m_rageBar;
            const float m_rageTimeAnimation;
            float m_timeStartingRage;
            bool  m_startingRage;
            bool  m_inRage;
            float m_rage;

        public:

            explicit Rage(Player* player);
            ~Rage();

            void bootRageBar();
            void updateRageBar();
            void increaseRage(float rageQtd);
            bool consumeRage();
            void startRage();
            void updateStartingRage();

            const float getRageTimeAnimation();
            float getTimeStartingRage();
            void drawRageBar();
            bool  getStartingRage();
            bool  getInRage();
            float getRage();

            void setRage(float rage);
            void setInRage(bool inRage);
            void setStartingRage(bool startingRage);
            nlohmann::ordered_json saveRage(nlohmann::ordered_json json);
        };
    }
}