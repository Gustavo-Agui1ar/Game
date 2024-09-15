
#pragma once 

#include <string>
#include "State.h"
#include "../Levels/Level.h"
#include "../includes/gerenciador/gerenciadorDeDialogo.h"
#include "../includes/gerenciador/gerenciadorArquivo.h"

namespace Game::State{
        class DialogueState : public State {

        private:

            Level::Level* m_fase;
            Gerenciador::GerenciadorDeDialogo* m_dialogueManager;

            void bootTalks(std::vector<std::string> pathTalks);

        public:

            explicit DialogueState(const IDs::IDs ID);
            ~DialogueState() override;

            void setFase(Level::Level* fase);
            Level::Level* getFase();

            void setDialogue(const char* pathDialogue);
            
            void execute() override;
            void draw() override;

            void changeEstateObserver(const bool ativo) override;
    
    };
}