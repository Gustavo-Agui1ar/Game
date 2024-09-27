
#pragma  once

#include "TextTalk.h"

#define TAM_NOME_X 250.0f
#define TAM_NOME_Y 35.0f

namespace Game::Menu::Button{
    class TalkBalloon{
        
    private:
        
        Manager::GraphicManager* m_graphicManager;
        TextTalk m_talk;
        Text m_name;
        sf::RectangleShape m_dialogueBox;;
        sf::RectangleShape m_nameBox;
    
        void bootDialogueBox();
        void bootName();
        void bootText();
    
    public:

        TalkBalloon(std::string textInfo, std::string nameInfo, const float timeToChange = 0.05f);
        ~TalkBalloon();

        void setText(std::string text);
        std::string getText();

        void setName(std::string name);
        std::string getName();

        const float getTimeToChange();
        const bool getEndText();

        void setNameDirection(bool esquerda);

        void skipDialogue();
        
        void updateName();
        void updateText();

        void update();
        void draw();      
    };
}