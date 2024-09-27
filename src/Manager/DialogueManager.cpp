
#include "../includes/Manager/DialogueManager.h"
#include "../includes/Observer/ObserverDialogue.h"

namespace Game::Manager{

        DialogueManager::DialogueManager(std::vector<std::string> names, std::vector<std::string> talks):
        m_dialogues(), m_endLastTalk(false), m_nameLeft(true), m_observerDialogue(new Observer::ObserverDialogue(this))
        {
            bootDialogues(names, talks);
        }

        DialogueManager::~DialogueManager()
        {
            if(m_observerDialogue != nullptr)
            {
                delete m_observerDialogue;
                m_observerDialogue = nullptr;
            }

            m_dialogues.clear();
        }

        void DialogueManager::bootDialogues(std::vector<std::string> names, std::vector<std::string> talks)
        {
            auto itN = names.begin();
            auto itF = talks.begin();

            while(itF != talks.end())
            {
                std::string name = (*itN);
                std::string dialogue = (*itF);

                auto* talk = new Menu::Button::TalkBalloon(dialogue, name);

                if(talk == nullptr)
                {
                    std::cout<< "Game::Manager::DialogueManager::bootDialogues: not possible to create the dialogue";
                    exit(1);
                }

                m_dialogues.push_back(talk);
                
                itF++;
                itN++;
            }

            m_currentDialogue = m_dialogues.begin();
        }

        void DialogueManager::skipDialogue()
        {
            (*m_currentDialogue)->skipDialogue();
        }

        void DialogueManager::nextTalk()
        {
            if((*m_currentDialogue)->getEndText() && !m_endLastTalk)
            {
                m_currentDialogue++;
                m_currentDialogue++;
                if(m_currentDialogue == m_dialogues.end())
                {
                    m_endLastTalk = true;
                }
                m_currentDialogue--;
               
                m_nameLeft = !m_nameLeft;
                (*m_currentDialogue)->setNameDirection(m_nameLeft);
            }
        }

        void DialogueManager::update()
        {
            (*m_currentDialogue)->update();
            draw();
        }

        void DialogueManager::draw()
        {
            (*m_currentDialogue)->draw();
        }

        const bool DialogueManager::getEndLastTalk()
        {
            return m_endLastTalk;
        }
        
        const bool DialogueManager::getEndCurrentTalk()
        {
            return (*m_currentDialogue)->getEndText();
        }

        void DialogueManager::changeObserverState(const bool ative)
        {
            m_observerDialogue->changeState(ative);
        }

       
}