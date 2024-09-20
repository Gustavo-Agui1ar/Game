

#include "../includes/Observer/ObserverDialogue.h"
#include "../includes/Manager/StateManager.h"


namespace Game::Observer{


    ObserverDialogue::ObserverDialogue(Manager::DialogueManager* dialogueManager):
    Observer(), m_dialogueManager(dialogueManager)
    {

    }

    ObserverDialogue::~ObserverDialogue() = default;

    void ObserverDialogue::keyPressed(const sf::Keyboard::Key key)
    {
        //empty
    }

    void ObserverDialogue::keyRelease(const sf::Keyboard::Key key)
    {
        if(m_defaultKeys[key] == 'e')
        {
            if(m_dialogueManager->getEndLastTalk() && m_dialogueManager->getEndCurrentTalk())
                m_stateManager->removeState();
            else if(m_dialogueManager->getEndCurrentTalk())
                m_dialogueManager->nextTalk();
            else
                m_dialogueManager->skipDialogue();
        }
        else if(m_especialKeys[key] == "Escape")
            m_stateManager->addState(IDs::IDs::pause_menu);
    }

    void ObserverDialogue::setDialogueManager(Manager::DialogueManager* dialogueManager)
    {
        m_dialogueManager = dialogueManager;
    }
    
    Manager::DialogueManager* ObserverDialogue::getDialogueManager()
    {
        return m_dialogueManager;
    }

}