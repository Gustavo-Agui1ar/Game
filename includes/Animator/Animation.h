
#pragma once

#include "Image.h"
#include "json.hpp"
#include <map>

namespace Game::Animator{


    class Animation{

    private:

        sf::RectangleShape *m_body;
        
        std::map<std::string, Image*> m_mapImage;
        std::string m_currentState;
        
        sf::Clock m_clock;

    public:
    
        explicit Animation(sf::RectangleShape* body);
        ~Animation();

        void update(bool direction, std::string currentState);

        void addAnimation(const char* texturePath, std::string const & animationName, const unsigned int qtdImage, const float swapTime, sf::Vector2f scale, sf::Vector2f origin);
        
        void setTotalTime(const float time);
        void setCurrentImg(std::string_view img);
        void setCurrentFrame(const unsigned int frame);

        float getTotalTime();
        unsigned int getCurrentFrame();
        std::string getCurrentImg() const;
        nlohmann::ordered_json saveAnimation(nlohmann::ordered_json json);
    };
}
