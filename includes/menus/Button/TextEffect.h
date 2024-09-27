
#pragma once

#include "Text.h"

namespace Game::Menu::Button{
    class TextEffect : public Text{

    private:

        int m_transparency;
        bool m_turnOff;

        void update();

    public:

        TextEffect(const sf::Font font, const std::string textInfo, const unsigned int fontSize = 50);
        ~TextEffect();

        void changeTransparency();
        
        const bool getTurnOff();
        const int getTransparency();
        
        void setTransparency(int transparency);

        void reset();

    };
}