
#pragma once

#include "Level.h"

namespace Game::Level{
    class Caverna : public Level{

    public:

        explicit Caverna(nlohmann::ordered_json entidades);
        Caverna();
        ~Caverna() override;
        
        void makeBackGround() override;
        void makeMap() override;

        void makePlatform(const sf::Vector2f pos) override;
        
        void loadGame(nlohmann::ordered_json entidades);
    };

}
