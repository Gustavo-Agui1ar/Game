#pragma once

#include "../../../Manager/GraphicManager.h"
#include "json.hpp"

#define SPEED_DASH_PLAYER 350.0f
#define TIME_DASH 0.48f

namespace Game::Entity::Character::Player {

    class Player;

    namespace Skils {
    
        class Dash {

            private:

                Manager::GraphicManager *m_graphic;
                Player* m_player;

                const float m_dashTimeAnimation;
                const float m_dashSpeed;
                float m_timeDash;
                bool m_canDash;
                bool m_inDash;

            public:
                
                explicit Dash(Player* player);
                ~Dash();

                void updateDash();
                void stopDash();
                void doDash();

                void setTimeDash(float timeDash);
                void setCanDash(bool canDash);
                void setInDash(bool inDash);

                const float getDashSpeed();
                float getTimeDash();
                bool getCanDash();
                bool getInDash();

                nlohmann::ordered_json saveDash(nlohmann::ordered_json json);
        };
    }
}