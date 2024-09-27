

#pragma once

#include "Text.h"
#include "../includes/Manager/GraphicManager.h"

namespace Game::Menu::Button{
    class TextTalk : public Text{

        private:

        const float m_timeToChange;
        float m_timeElapsed;
        bool m_textEnd;

        Manager::GraphicManager* m_graphicManager;
        std::string m_completeText;
        std::string::iterator m_letterIterator;

    public:

        TextTalk(const float timeToChange, const sf::Font font, const std::string textInfo, const unsigned int fontSize = 50);
        ~TextTalk();

        void increaseLetter();
        void bootIterator();
        void showCompleteText();
        const bool getEndText();
        const float getTimeToChange();
        void setCompleteText(sf::String text);
        std::string getCompleteText();
        void update();
    };

}