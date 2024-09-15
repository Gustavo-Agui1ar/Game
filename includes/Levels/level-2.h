

#pragma once

#include "Level.h"

namespace Game::Level{
    class Forest : public Level{

    public:

        explicit Forest(nlohmann::ordered_json entidades);
        Forest();
        ~Forest() override;
        
        void makeBackGround() override;
        void makeMap() override;
        
        void makePlatform(const sf::Vector2f pos) override;
        
        void loadGame(nlohmann::ordered_json entidades);

    };

}

