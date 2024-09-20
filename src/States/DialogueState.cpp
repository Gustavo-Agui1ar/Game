
#include "../includes/States/DialogueState.h"

namespace Game::State{

    
    DialogueState::DialogueState(const IDs::IDs ID):
    State(ID), m_fase(nullptr), m_dialogueManager(nullptr)
    {

    }
    DialogueState::~DialogueState()
    {
        if(m_dialogueManager != nullptr)
        {
            delete m_dialogueManager;
            m_dialogueManager = nullptr;
        }

        m_fase = nullptr;
    }

    void DialogueState::bootTalks(std::vector<std::string> pathTalks)
    {
        auto it = pathTalks.begin();
        
        std::vector<std::string> names; 
        std::vector<std::string> talks;

        while(it != pathTalks.end())
        {
            std::string dialogueLine = (*it);
            std::string name = dialogueLine.substr(0, dialogueLine.find(":"));
            std::string talk = dialogueLine.substr(name.size() + 1, dialogueLine.size());
            
            names.push_back(name);
            talks.push_back(talk);
            it++;
        }

        m_dialogueManager = new Manager::DialogueManager(names, talks);
    }
    void DialogueState::setFase(Level::Level* fase)
    {
        m_fase = fase;
    }
    void DialogueState::setDialogue(const char* pathDialogue)
    {
        Manager::FileManager arquivo;

        std::vector<std::string> talks = arquivo.readFileText(pathDialogue);

        bootTalks(talks);
    }
    
    void DialogueState::execute()
    {
        m_fase->draw();
        m_dialogueManager->update();
    }

    void DialogueState::draw()
    {
        m_fase->draw();
        m_dialogueManager->draw();
    }

    void DialogueState::changeEstateObserver(const bool ative)
    {
        m_dialogueManager->changeObserverState(ative);
    }
    
    Level::Level* DialogueState::getFase()
    {
        return m_fase;
    }
}