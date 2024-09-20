
#pragma once

#include "../includes/Manager/DialogueManager.h"
#include "Observer.h"

namespace Game::Observer{
    class ObserverDialogue : public Observer{

    private:

        Manager::DialogueManager* m_dialogueManager;

    public:


        explicit ObserverDialogue(Manager::DialogueManager* dialogueManager);
        ~ObserverDialogue() override;

        void keyPressed(const sf::Keyboard::Key key) override;
        void keyRelease(const sf::Keyboard::Key key) override;

        void setDialogueManager(Manager::DialogueManager* dialogueManager);
        Manager::DialogueManager* getDialogueManager();
    };
}